#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <map>
#include <unistd.h>

#include <unistd.h>

#define getchar()
using namespace std;

int tot = 0;
struct vals { int cost; int damage; int armor; };

struct vals weapons[] { {8, 4, 0}, {10, 5, 0}, {25, 6, 0}, {40, 7, 0}, {74, 8, 0}, {-1,-1,-1}};
int weaponsTot = 5;
struct vals armor[] { {13, 0, 1}, {31, 0, 2}, {53, 0, 3}, {75, 0, 4}, {102, 0, 5} , {-1,-1,-1}};
int armorTot = 5;
struct vals rings[] { {25, 1, 0}, {50, 2, 0}, {100, 3, 0}, {20, 0, 1}, {40, 0, 1}, {80, 0, 3}, {-1,-1,-1}};
int ringsTot = 6;
	
#define getchar()
int bossHit; int bossDamage; int bossArmor;
int bossHitOrig; int bossDamageOrig; int bossArmorOrig;
//int playerHit = 8; int playerDamage = 5; int playerArmor = 5;
int playerHitOrig = 100; int playerDamageOrig = 0; int playerArmorOrig = 0; int playerCostOrig = 0;
int playerHit, playerDamage, playerArmor, playerCost;
int play();
int main(int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("		2015 Day21.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
        int leny = 0;
        while (1) {

                fgets(line1, 1000, a); if (feof(a)) {break;}
                line1[strlen(line1) -1] = '\0';
//              printf("line1 %s", line1);

		sscanf(line1, "Hit Points: %d\n", &bossHitOrig);
		sscanf(line1, "Damage: %d\n", &bossDamageOrig);
		sscanf(line1, "Armor: %d\n", &bossArmorOrig);
		leny++;
        } //while
        fclose(a);
	
	
	//int minPlayerCost = 99999;
	int maxPlayerCost = 0;
	int arrWe[10];
	for (int weEnd = 1; weEnd < 2; weEnd++) {
//	for (int weEnd = 1; weEnd < 3; weEnd++) {
		for (int j = 0; j < weEnd; j++) {
			arrWe[j] = 1;
		}
		for (int k = weEnd; k < weaponsTot; k++) {
			arrWe[k] = 0;
		}
		sort(arrWe, arrWe+weaponsTot);
///////////////WEAPONS
		do {
			for (int z = 0; z < weaponsTot; z++) { printf("%d ", arrWe[z]); } getchar();
			playerHit = playerHitOrig;
			playerCost = playerCostOrig;
			playerDamage = playerDamageOrig;
			playerArmor = playerArmorOrig;
	
			for (int we = 0; we < weaponsTot; we++) {
				if (arrWe[we] == 1) {
					playerCost += weapons[we].cost;
					playerDamage += weapons[we].damage;
					playerArmor += weapons[we].armor;
				}
			}
		
			int pH1 = playerHit;
			int pC1 = playerCost;
			int pD1 = playerDamage;
			int pA1 = playerArmor;

	///////////////////////ARMOR
			int arrArm[10];
			for (int arEnd = 0; arEnd < 2; arEnd++) {
				for (int j = 0; j < arEnd; j++) {
					arrArm[j] = 1;
				}
				for (int k = arEnd; k < armorTot; k++) {
					arrArm[k] = 0;
				}
				sort(arrArm, arrArm+armorTot);
				do {
					//for (int z = 0; z < armorTot; z++) { printf("%d ", arrArm[z]); } getchar();
					playerHit = pH1;
					playerCost = pC1;
					playerDamage = pD1;
					playerArmor = pA1;

					for (int ar = 0; ar < armorTot; ar++) {
						if (arrArm[ar] == 1) {
							playerCost += armor[ar].cost;
							playerDamage += armor[ar].damage;
							playerArmor += armor[ar].armor;
						}
					}
					int pH = playerHit;
					int pC = playerCost;
					int pD = playerDamage;
					int pA = playerArmor;
	/////////////////////////RINGS

					int arrRi[10];

					for (int riEnd = 0; riEnd < 3; riEnd++) {
						for (int j = 0; j < riEnd; j++) {
							arrRi[j] = 1;
						}
						for (int k = riEnd; k < ringsTot; k++) {
							arrRi[k] = 0;
						}

						sort(arrRi, arrRi+ringsTot);
						do {
							playerHit = pH;
							playerCost = pC;
							playerDamage = pD;
							playerArmor = pA;
							//for (int z = 0; z < ringsTot; z++) { printf("%d ", arrRi[z]); } printf("\n"); getchar();
							for (int ri = 0; ri < ringsTot; ri++) {
								if (arrRi[ri] == 1) {
									playerCost += rings[ri].cost;
									playerDamage += rings[ri].damage;
									playerArmor += rings[ri].armor;
								}
							}
							int ret = play();
							if (ret == 2) {
								printf("player Cost %d\n", playerCost);
								if (playerCost > maxPlayerCost) {maxPlayerCost = playerCost;}
							}
						
						} while (next_permutation(arrRi, arrRi+ringsTot));
					}
				} while (next_permutation(arrArm, arrArm+armorTot));
			}
		} while (next_permutation(arrWe, arrWe+weaponsTot));
	
	}
        printf("***maxPlayerCost: %d\n", maxPlayerCost);
        printf("***tot: %d\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", maxPlayerCost);
}

int play() 
	{//play
						tot++;
		bossHit = bossHitOrig; bossDamage = bossDamageOrig; bossArmor = bossArmorOrig;
		do {
			printf("Boss: %d %d %d\n", bossHit, bossDamage, bossArmor);
			printf("Player: %d %d %d\n", playerHit, playerDamage, playerArmor);
			printf("next..."); //getchar();
			bossHit -= playerDamage - bossArmor > 0? playerDamage -bossArmor: 1;	
			if (bossHit <= 0) {
				printf("***player wins...\n");
				return 1;
			}
			playerHit -= bossDamage - playerArmor > 0? bossDamage - playerArmor : 1;	
			if (playerHit <= 0) {
				printf("***boss wins...\n");
				return 2;
			}
		} while (1);

	}
