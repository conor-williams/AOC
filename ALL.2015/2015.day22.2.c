#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
struct spells_s { int cost; int damage; int armor; int hit; int turns; int getCost;};
struct vals2 { int cost; int damage; int armor; int hit; int turns; int getCost; int timerCount;


	vals2() {
                cost = 0;
                damage = 0;
                armor = 0;
                hit = 0;
                turns = 0;
                getCost = 0;
                timerCount = -1;
        }

        vals2& operator=(const vals2& o) {
                //printf("vals2                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
                if (this != &o) { // Avoid self-assignment
                        cost = o.cost;
                        damage = o.damage;
                        armor = o.armor;
                        hit = o.hit;
                        turns = o.turns;
                        getCost = o.getCost;
                        timerCount = o.timerCount;
                }
                return *this;
        }
        vals2(const vals2& o) {
                cost = o.cost;
                damage = o.damage;
                armor = o.armor;
                hit = o.hit;
                turns = o.turns;
                getCost = o.getCost;
                timerCount = o.timerCount;
        }




};


struct spells_s spells[] = { {53, 4, 0, 0, 1, 0}, {73, 2, 0, 2, 1, 0}, {113, 0, 7, 0, 6, 0}, {173, 3, 0, 0, 6, 0}, {229, 0, 0, 0, 5, 101}, {-1, -1, -1, -1, -1, -1}};
//0 == MagicMissile(53) 1==Drain(73) 2=Shield(113) 3=Poison(173) 4==Recharge=229
int spellsTot = 5;
void printit(struct game xx);

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


	game& operator=(const game& o) {
                //printf("game                                     assig \n game assssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n");
                if (this != &o) { // Avoid self-assignment
                        pMana = o.pMana;
                        pCost = o.pCost;
                        pDamage = o.pDamage;
                        pArmor = o.pArmor;
                        pHit = o.pHit;
                        for (int ii = 0; ii < spellsTot; ii++) {
                                pCounters[ii] = o.pCounters[ii];
                        }
                        pGetCost = o.pGetCost;

                        bHit = o.bHit;
                        bDamage = o.bDamage;
                        bArmor = o.bArmor;
                        bMana = o.bMana;
                }
                return *this;
        };
	game() {
                pMana = 0;
                pCost = 0;
                pDamage = 0;
                pArmor = 0;
                pHit = 0;
                struct vals2 pCounters[5];
		for (int ii = 0; ii < 5; ii++) {
			pCounters[ii] = vals2();
		}
                pGetCost = 0;

                bHit = 0;
                bDamage = 0;
                bArmor = 0;
                bMana = 0;
        };
	game(const game& o) {
                pMana = o.pMana;
                pCost = o.pCost;
                pDamage = o.pDamage;
                pArmor = o.pArmor;
                pHit = o.pHit;
                for (int ii = 0; ii < spellsTot; ii++) {
                        pCounters[ii] = o.pCounters[ii];
                }
                pGetCost = o.pGetCost;

                bHit = o.bHit;
                bDamage = o.bDamage;
                bArmor = o.bArmor;
                bMana = o.bMana;
        }


};
void applySpells();
void apply();

struct game games[300000];
int gamesPos = 0;

struct game newGames[300000];
int newGamesPos = 0;

int taketurn();
void cast();


//#define MATRIX_

#ifdef MATRIX_
	int playerHitOrig = 10; int playerManaOrig = 250;  int playerDamageOrig = 0; int playerArmorOrig = 0;
#else
	int playerHitOrig = 50; int playerManaOrig = 500;  int playerDamageOrig = 0; int playerArmorOrig = 0;
#endif
int bossHitOrig = 0; int bossDamageOrig = 0; int bossArmorOrig = 0;
int minManaSpent = 10000;
#ifdef MATRIX_
int spellsMatrixPos = 0;
#endif
#ifdef MATRIX_
/* ex1.txt*/ int spellsMatrix[] = {3, 0};

/*ex2.txt*/ //int spellsMatrix[] = {4, 2, 1, 3, 0};
#endif
void turns();
int bossTurn();
int playerTurn();
int main(int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("		2015 Day22.2\n"); fflush(stdout);

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

	games[0] = game();

        games[0].pMana = playerManaOrig;
        games[0].pArmor = playerArmorOrig;
        games[0].pHit = playerHitOrig;
        games[0].bHit = bossHitOrig;
        games[0].bDamage = bossDamageOrig;
        games[0].bArmor = bossArmorOrig;
        gamesPos = 1;

#ifdef MATRIX_
	spellsMatrixPos = 0;
#endif
	int count = -1;
	int max;
	do {
		count++;
///////////////////////CAST
		if (gamesPos > max) {
			max = gamesPos;
		}
		while (gamesPos != 0 ) {
			cast(); 
		}
		printf("**************cast count\n", gamesPos);
		getchar();
////
		printf("-------------- CAST v vv v%d-------- \n", count);
		for (int i = 0; i < newGamesPos; i++) {
			games[i] = newGames[i];
			//printit(games[i]);
			gamesPos++;
		}
		if (gamesPos > max) {
			max = gamesPos;
		}
		getchar();
		newGamesPos = 0;
		
///////////////////////TAKE TURN
		while (gamesPos != 0){
			turns();
		}
////
		printf("-------TURN v v v v v----- %d -- \n", count);
		for (int i = 0; i < newGamesPos; i++) {
			games[i] = newGames[i];
			//printit(games[i]);
			gamesPos++;
		}
		getchar();
		newGamesPos = 0;
#ifdef MATRIX_
		spellsMatrixPos++;
#endif
	} while (gamesPos != 0);
		

        printf("***minManaSpent: %d\n", minManaSpent);
	fflush(stdout);	fflush(stdout); dup2(fd, 1);
        printf("***ans: %d\n", minManaSpent);
}

/*
void printit(struct game xx) {
        printf("%d %d %d %d %d %d ", xx.pMana, xx.pCost, xx.pDamage, xx.pArmor, xx.pHit, xx.pGetCost);
        printf("%d %d %d %d\n", xx.bHit, xx.bDamage, xx.bArmor, xx.bMana);
        for (int i  =0; i < 5; i++) {
		if (i != 0) {printf(" ");
                printf("%d %d %d %d %d %d %d\n",
                        xx.pCounters[i].cost,
                        xx.pCounters[i].damage,
                        xx.pCounters[i].armor,
                        xx.pCounters[i].hit,
                        xx.pCounters[i].turns,
                        xx.pCounters[i].getCost,
                        xx.pCounters[i].timerCount);
        }
	printf("\n");
}
*/

void cast() {
//PLAYER
	gamesPos--;

	struct game xx = games[gamesPos];
	/*
	int pMana=games[gamesPos].pMana;
	int pCost=games[gamesPos].pCost;
	int pDamage=games[gamesPos].pDamage;
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
	*/
	
	xx.pHit--;
	if (xx.pHit <= 0) {
		printf("player loses\n");
		return;
	}
	
	int notafford = 0;
	int notyet = 0;
	for (int sp = 0; sp < spellsTot; sp++) {
		//if (pCounters[sp].timerCount == 0 ) {printf("EQUAL ZERO game %d spell %d\n", gamesPos, sp); getchar();}
		
		if (xx.pCounters[sp].timerCount < 0 && minManaSpent > xx.pCost ) {
			struct game tmpGame = xx;

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
			tmpGame.pMana = xx.pMana - spells[sp].cost;// + spells[sp].getCost;
			if (tmpGame.pMana <= 0) {notafford++; printf("cannot afford\n"); continue;}
			tmpGame.pCost = xx.pCost + spells[sp].cost;
			//tmpGame.pArmor = xx.pArmor;// + spells[sp].armor;
			//tmpGame.pDamage = xx.pDamage;
			//tmpGame.pHit = xx.pHit;
			tmpGame.pCounters[sp].cost = spells[sp].cost;
			tmpGame.pCounters[sp].damage = spells[sp].damage;
			tmpGame.pCounters[sp].armor = spells[sp].armor;
			tmpGame.pCounters[sp].hit = spells[sp].hit;
			tmpGame.pCounters[sp].getCost = spells[sp].getCost;
			tmpGame.pCounters[sp].timerCount = spells[sp].turns;
			//tmpGame.pGetCost = spells[sp].getCost;

			/*
			tmpGame.bHit = bHit;
			tmpGame.bDamage = bDamage;
			tmpGame.bMana = bMana;
			tmpGame.bArmor = bArmor;
			*/
			
			if (sp == 1) {
				tmpGame.bHit -= spells[sp].damage;
				tmpGame.pHit = xx.pHit + spells[sp].hit;
				///tmpGame.pCounters[sp].timerCount = -1;
			} else if (sp == 0) {
				tmpGame.bHit -= spells[sp].damage;
				///tmpGame.pCounters[sp].timerCount = -1;
			} else if (sp == 3) {
				tmpGame.pDamage = xx.pDamage/* + spells[sp].damage*/;
			} else if (sp == 2) {
				tmpGame.pArmor = xx.pArmor + spells[sp].armor;
			}
			newGames[newGamesPos] = tmpGame; newGamesPos++;
		} else if (xx.pCounters[sp].timerCount >= 0) {
			notyet++;
		}

	}
	if (notafford == spellsTot) {
		printf("cant afford all...\n player loses...\n");// getchar();
	}
	if (notyet == spellsTot) {
		//newGames[newGamesPos] = games[gamesPos]; newGamesPos++;
		newGames[newGamesPos] = xx; newGamesPos++;
		printf("not yet...\n"); getchar();
	}
}
void turns() {
	int ret1 = bossTurn();
#ifdef MATRIX_
	getchar();
#endif 
	if (ret1 != 0) {
		gamesPos--;
		return;
	}

	int ret2 = playerTurn();
#ifdef MATRIX_
	getchar();
#endif 
	if (ret2 == 0) {
		newGames[newGamesPos] = games[gamesPos-1]; newGamesPos++;
	}
	gamesPos--;
	if (gamesPos < 0) {printf("zero"); exit(0);}
}

int bossTurn() {
	printf("\n-- Boss turn --\n");
	int c = gamesPos-1;

	printf("- Player has %d hit points, %d armor, %d mana - dam(%d)\n", games[c].pHit, games[c].pArmor, games[c].pMana, games[c].pDamage);
	printf("- Boss has %d hit points\n", games[c].bHit);
	applySpells();
	if (games[c].bHit <= 0) {
		if (games[c].pCost < minManaSpent) {minManaSpent = games[c].pCost;}
		printf("**player wins... game over\n");
		return 1;
	}
	printf("Boss attacks for %d damage\n", games[c].bDamage - games[c].pArmor);
	games[c].pHit -= games[c].bDamage - games[c].pArmor > 0? games[c].bDamage - games[c].pArmor : 1;	
	if (games[c].pHit <= 0) {
		printf("***boss wins...\n");
		return 2;
	}
	return 0;
}

int playerTurn() {//play
	printf("\n-- Player turn --\n");
	int c = gamesPos -1;

	printf("- Player has %d hit points, %d armor, %d mana - dam(%d)\n", games[c].pHit, games[c].pArmor, games[c].pMana, games[c].pDamage);
	printf("- Boss has %d hit points\n", games[c].bHit);
	applySpells();
	if (games[c].pDamage > 0) {
		games[c].bHit -= games[c].pDamage;
	}

	if (games[c].bHit <= 0) {
		printf("***player wins...\n");
		if (games[c].pCost < minManaSpent) {minManaSpent = games[c].pCost;}
		return 1;
	}

	return 0;
}

void applySpells() {
	int c = gamesPos-1;
	for (int i = 0; i < spellsTot; i++) {
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
					games[c].pMana += games[c].pCounters[i].getCost;
					printf("Recharge provides %d mana; its timer is now %d.\n", games[c].pCounters[i].getCost,
						games[c].pCounters[i].timerCount);
					printf(" Recharge is now");
					break;

			}
			printf(" %d\n", games[c].pCounters[i].timerCount);
			if (games[c].pCounters[i].timerCount == 0) {
				if (games[c].pCounters[i].armor > 0) {
				} else {
					games[c].pCounters[i].timerCount--;
				}
				if (games[c].pCounters[i].armor != 0) {
					printf("reducting armor... by %d\n", games[c].pCounters[i].armor);
				}
				//games[c].pArmor  -= games[c].pCounters[i].armor;
			}
		} else if (games[c].pCounters[i].timerCount == 0) {
			games[c].pCounters[i].timerCount--;
			games[c].pArmor  -= games[c].pCounters[i].armor;
		}
	}
}
