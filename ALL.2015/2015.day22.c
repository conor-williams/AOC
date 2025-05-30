#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
struct vals { int cost; int damage; int armor; int hit; int turns; int getCost;};
struct vals2 { int cost; int damage; int armor; int hit; int turns; int getCost; int timerCount;};

struct vals spells[] = { {53, 4, 0, 0, 1, 0}, {73, 2, 0, 2, 1, 0}, {113, 0, 7, 0, 6, 0}, {173, 3, 0, 0, 6, 0}, {229, 0, 0, 0, 5, 101}, {-1, -1, -1, -1, -1, -1}};
//0 == MagicMissile(53) 1==Drain(73) 2=Shield(113) 3=Poison(173) 4==Recharge=229
int spellsTot = 5;

#define getchar()
struct game {
	int pMana;
	int pCost;
	int pDamage;
	int pArmor;
	int pHit;
	struct vals2 pCounters[6];
	int pGetCost;

	int bHit;
	int bDamage;
	int bArmor;
	int bMana;
};

struct game games[10000];
int gamesPos = 0;

struct game newGames[10000];
int newGamesPos = 0;

int taketurn();
void cast();

int playerHitOrig = 50; int playerManaOrig = 500;  int playerDamageOrig = 0; int playerArmorOrig = 0;
int bossHitOrig = 0; int bossDamageOrig = 0; int bossArmorOrig = 0;
int minManaSpent = 10000;
int spellsMatrixPos = 0;
/// ex1.txt int spellsMatrix[] = {3, 0};
/*ex2.txt*/ int spellsMatrix[] = {4, 2, 1, 3, 0};
void turns();
int bossTurn();
int playerTurn();
int main(int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("		2015 Day22.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
        int leny = 0;
        while (1) {

                fgets(line1, 1000, a); if (feof(a)) {break;}
                line1[strlen(line1) -1] = '\0';
//              printf("line1 %s", line1);

		sscanf(line1, "Hit Points: %d\n", &bossHitOrig);
		sscanf(line1, "Damage: %d\n", &bossDamageOrig);
		//sscanf(line1, "Armor: %d\n", &bossArmorOrig);
		leny++;
        } //while
        fclose(a);
	
	

	//int minPlayerCost = 99999;

	games[0].pMana = playerManaOrig;
	games[0].pCost = 0;
	games[0].pDamage = 0;
	games[0].pArmor = playerArmorOrig;
	games[0].pHit = playerHitOrig;
	for (int i = 0; i < spellsTot; i++) {
		for (int j; j < spellsTot; j++) {
			games[0].pCounters[i].cost = 0;
			games[0].pCounters[i].damage = 0;
			games[0].pCounters[i].armor = 0;
			games[0].pCounters[i].hit = 0;
			games[0].pCounters[i].turns = 0;
			games[0].pCounters[i].getCost = 0;
			games[0].pCounters[i].timerCount = -1;
		}
	}
	games[0].pGetCost = 0;
	games[0].bHit = bossHitOrig;
	games[0].bDamage = bossDamageOrig;
	games[0].bArmor = bossArmorOrig;
	gamesPos = 1;

	spellsMatrixPos = 0;
	do {
///////////////////////CAST
		do {
			cast(); 
		} while (gamesPos != 0);
////
		for (int i = 0; i < newGamesPos; i++) {
			games[i] = newGames[i];
			gamesPos++;
		}
		newGamesPos = 0;
		
///////////////////////TAKE TURN
		do {
			turns();
		} while (gamesPos != 0);
////
		for (int i = 0; i < newGamesPos; i++) {
			games[i] = newGames[i];
			gamesPos++;
		}
		newGamesPos = 0;
		//spellsMatrixPos++;
	} while (gamesPos != 0);
		

	fflush(stdout); dup2(fd, 1);
        printf("***minManaSpent: %d\n", minManaSpent);
}

void cast() {
//PLAYER
	gamesPos--;
	int pMana=games[gamesPos].pMana;
	int pCost=games[gamesPos].pCost;
	//int pDamage=games[gamesPos].pDamage;
	int pArmor=games[gamesPos].pArmor;
	int pHit=games[gamesPos].pHit;
	struct vals2 pCounters[6];
	for (int i = 0; i < spellsTot; i++) {
		pCounters[i] = games[gamesPos].pCounters[i];
	}
		
	//int pGetCost = games[gamesPos].pGetCost;
////BOSS
	int bHit = games[gamesPos].bHit;
	int bDamage = games[gamesPos].bDamage;
	int bMana = games[gamesPos].bMana;
	int bArmor = games[gamesPos].bArmor;
	
	
	for (int sp = 0; sp < spellsTot; sp++) {
		struct game tmpGame;
		if (pCounters[sp].timerCount <= 0 /*&& spellsMatrix[spellsMatrixPos] == sp*/) {

			printf("Player casts ");
			switch (sp) {
				case 0:
					printf(" Magic Missile\n");	
					break;
				case 1:
					printf(" Drain\n");	
					break;
				case 2:
					printf(" Shield\n");
					break;
				case 3:
					printf(" Poisin\n");
					break;
				case 4:
					printf(" Recharge\n");
					break;

			}
			tmpGame.pMana = pMana - spells[sp].cost;// + spells[sp].getCost;
			if (tmpGame.pMana <= 0) {printf("cannot afford\n"); continue;}
			tmpGame.pCost = pCost + spells[sp].cost;
			//tmpGame.pDamage = pDamage + spells[sp].damage;
			tmpGame.pArmor = pArmor + spells[sp].armor;
			tmpGame.pHit = pHit + spells[sp].hit;
			for (int j = 0; j < spellsTot; j++) {
				tmpGame.pCounters[j] = pCounters[j];
			}
			tmpGame.pCounters[sp].cost = spells[sp].cost;
			tmpGame.pCounters[sp].damage = spells[sp].damage;
			tmpGame.pCounters[sp].armor = spells[sp].armor;
			tmpGame.pCounters[sp].hit = spells[sp].hit;
			tmpGame.pCounters[sp].getCost = spells[sp].getCost;
			tmpGame.pCounters[sp].timerCount = spells[sp].turns;
			//tmpGame.pGetCost = spells[sp].getCost;

			tmpGame.bHit = bHit;
			tmpGame.bDamage = bDamage;
			tmpGame.bMana = bMana;
			tmpGame.bArmor = bArmor;
			
			if (sp == 1) {
				tmpGame.bHit -= spells[sp].damage;
				tmpGame.pCounters[sp].timerCount = -1;
			} else if (sp == 0) {
				tmpGame.bHit -= spells[sp].damage;
				tmpGame.pCounters[sp].timerCount = -1;
			}
				
			newGames[newGamesPos] = tmpGame; newGamesPos++;
		}

	}
}
void turns() {
	//int ret1 = playerTurn();
	//if (ret1 != 0) {
	//	gamesPos--;
	//	return;
	//}// 
	int ret2 = bossTurn(); getchar();
	if (ret2 != 0) {
		gamesPos--;
		return;
	}
	int ret3 = playerTurn(); getchar();
	if (ret3 == 0) {
		newGames[newGamesPos] = games[gamesPos-1]; newGamesPos++;
	}
	gamesPos--;
}

	//printf("Boss(before)(%d):        H:%d D:%d A:%d\n", c, games[c].bHit, games[c].bDamage, games[c].bArmor);
	//printf("Player(before)(%d): M:%d H:%d D:%d A:%d\n", c, games[c].pMana, games[c].pHit, games[c].pDamage, games[c].pArmor);
int bossTurn() {//play
	//printf("taking turn... of Boss\n");
	printf("\n-- Boss turn --\n");
	int c = gamesPos-1;

	printf("- Player has %d hit points, %d armor, %d mana - dam(%d)\n", games[c].pHit, games[c].pArmor, games[c].pMana, games[c].pDamage);
	printf("- Boss has %d hit points\n", games[c].bHit);

	for (int i = 0; i < spellsTot; i++) {
		if (games[c].pCounters[i].getCost != 0 && games[c].pCounters[i].timerCount > 0) {
			games[c].pMana += games[c].pCounters[i].getCost;
			games[c].pCounters[i].timerCount--;
			printf("Recharge provides %d mana; its timer is now %d.\n", 
				games[c].pCounters[i].getCost, games[c].pCounters[i].timerCount);
			continue;
		}
		if (games[c].pCounters[i].timerCount > 0) {
			games[c].pCounters[i].timerCount--;
			switch (i) {
				case 0:
					printf(" Magic Missile timer is now");	
					break;
				case 1:
					printf(" Drain timer is now");	
					break;
				case 2:
					printf(" Shield timer is now");
					break;
				case 3:
					//tmpGame.bHit -= spells[sp].damage;
					games[c].bHit -= games[c].pCounters[i].damage;
					printf("(%d) Poisin timer is now", games[c].pCounters[i].damage);
					printf("bHit now %d", games[c].bHit);
					break;
				case 4:
					printf(" Recharge is now");
					break;

			}
			printf(" %d\n", games[c].pCounters[i].timerCount);

			if (games[c].pCounters[i].timerCount == 0) {
				games[c].pCounters[i].timerCount--;
				games[c].pDamage -= games[c].pCounters[i].damage;
printf("reducting armor... by %d\n", games[c].pCounters[i].armor);
				games[c].pArmor  -= games[c].pCounters[i].armor;
				games[c].pHit    -= games[c].pCounters[i].hit;
			}
		} else if (games[c].pCounters[i].timerCount == 0) {
			games[c].pCounters[i].timerCount--;
			games[c].pDamage -= games[c].pCounters[i].damage;
printf("reducting armor... by %d\n", games[c].pCounters[i].armor);
			games[c].pArmor  -= games[c].pCounters[i].armor;
			games[c].pHit    -= games[c].pCounters[i].hit;
		}
	}
	if (games[c].bHit <= 0) {
		if (games[c].pCost < minManaSpent) {minManaSpent = games[c].pCost;}
		printf("**player wins... games over\n"); return 2;
	}
	printf("Boss attacks for %d damage\n", games[c].bDamage - games[c].pArmor);
	games[c].pHit -= games[c].bDamage - games[c].pArmor > 0? games[c].bDamage - games[c].pArmor : 1;	
	if (games[c].pHit <= 0) {
		printf("***boss wins...\n");
		//if (games[c].pCost < minManaSpent) {minManaSpent = games[c].pCost;}
		return 2;
	}
	return 0;
}

int playerTurn() {//play
	//printf("taking turn...of Player\n");
	printf("\n-- Player turn --\n");
	int c = gamesPos -1;

	printf("- Player has %d hit points, %d armor, %d mana - dam(%d)\n", games[c].pHit, games[c].pArmor, games[c].pMana, games[c].pDamage);
	printf("- Boss has %d hit points\n", games[c].bHit);
	for (int i = 0; i < spellsTot; i++) {
		if (games[c].pCounters[i].getCost != 0 && games[c].pCounters[i].timerCount > 0) {
			games[c].pMana += games[c].pCounters[i].getCost;
			games[c].pCounters[i].timerCount--;
			printf("Recharge provides %d mana; its timer is now %d.\n", 
				games[c].pCounters[i].getCost, games[c].pCounters[i].timerCount);
			continue;
		}
		if (games[c].pCounters[i].timerCount > 0) {
			games[c].pCounters[i].timerCount--;
			switch (i) {
				case 0:
					printf(" Magic Missile timer is now");	
					break;
				case 1:
					printf(" Drain timer is now");	
					break;
				case 2:
					printf(" Shield timer is now");
					break;
				case 3:
					games[c].bHit -= games[c].pCounters[i].damage;
					printf("(%d) Poisin timer is now", games[c].pCounters[i].damage);
					break;
				case 4:
					printf(" Recharge is now");
					break;

			}
			printf(" %d\n", games[c].pCounters[i].timerCount);
			if (games[c].pCounters[i].timerCount == 0) {
				games[c].pCounters[i].timerCount--;
				games[c].pDamage -= games[c].pCounters[i].damage;
printf("reducting armor... by %d\n", games[c].pCounters[i].armor);
				games[c].pArmor  -= games[c].pCounters[i].armor;
				games[c].pHit    -= games[c].pCounters[i].hit;
			}
		} else if (games[c].pCounters[i].timerCount == 0) {
			games[c].pCounters[i].timerCount--;
			games[c].pDamage -= games[c].pCounters[i].damage;
			games[c].pArmor  -= games[c].pCounters[i].armor;
			games[c].pHit    -= games[c].pCounters[i].hit;
		}
	}
	if (games[c].pDamage > 0) {
		games[c].bHit -= games[c].pDamage - games[c].bArmor > 0? games[c].pDamage - games[c].bArmor: 1;	
	}
	if (games[c].bHit <= 0) {
		printf("***player wins...\n");
		if (games[c].pCost < minManaSpent) {minManaSpent = games[c].pCost;}
		return 1;
	}

	return 0;
}
