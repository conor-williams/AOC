
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#undef _DEBUG_
#define getchar()
#define SIZE 400
char line1[SIZE];
unsigned long tot = 0;
enum TYPE {RAD, BLU, FIR, SLA, COL};
struct atk_s {
	int itsI;
	int atk;
	int atkr;
	int power;
	int ini;
};
int STALE = 0;
struct group_s {
	int units;
	int hitPoints;
	int weaks[10];  //radiation //bludgeoning //fire //slashing //cold
	int immune[10]; //radiation //bludgeoning //fire //slashing //cold
	int attack[10];
	int damage;
	int power;
	int ini;
	int type;
	int itsI;
	int alAttr;
	int alAttd;
	int atkDam;
	int ignore;
	struct atk_s toattack;
};
struct group_s immune[100];
int immunePos = 0;
struct group_s both[100];
int bothPos = 0;
struct group_s bothOrig[100];
int bothOrigPos = 0;
struct group_s infection[100];
int infectionPos = 0;
int conv(char type[]);
void decode(char what[], int immuneorinfection, int pos);
int nextAttrSortByPowerThenInitiativeNotMe();
int nextAttrSortByInitiativeNotMe();
struct atk_s  targetSelectionByMostDamageHighestPower(int attr);
void printit();
void attack(int attr, struct atk_s attd);

int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day24.1\n"); fflush(stdout);

	int leny = 0;
	int part = -1;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		if (strcmp(line1, "Immune System:") == 0) {
			part = 1;
			continue;
		} else if (strcmp(line1, "Infection:") == 0) {
			part = 2;
			continue;
		} else if (line1[0] == '\0') {
			continue;
		}

		int units; int hitPoints; char weaksimmune[220];
		int attack; char attackType[100]; int ini;

		int wi = 1;
		int ret = sscanf(line1, "%d units each with %d hit points (%[^)]) with an attack that does %d %s damage at initiative %d", &units, &hitPoints, weaksimmune, &attack, attackType, &ini);
		if (ret != 6) {
			ret = sscanf(line1, "%d units each with %d hit points with an attack that does %d %s damage at initiative %d", &units, &hitPoints, &attack, attackType, &ini);
			wi = 0;
			if (ret != 5) {exit(0);}
		}


		printf("line1 is %s\n", line1);
		printf("initiative is %d\n", ini); getchar();
		printf("weaksimmune: [[%s]]\n", weaksimmune);
		if (part == 1) {
			immune[immunePos].units = units;
			immune[immunePos].hitPoints = hitPoints;
			immune[immunePos].attack[conv(attackType)] = attack;
			immune[immunePos].damage = attack;
			immune[immunePos].ini = ini;
			if (wi == 1) {
				char *first = strtok(weaksimmune, ";\0");
				do {printf("first: [%s]\n", first); decode(first, 1, immunePos);} while((first = strtok(NULL, ";\0")) != NULL);
			} else {
				immune[immunePos].weaks[RAD] = 0;	
				immune[immunePos].weaks[BLU] = 0;	
				immune[immunePos].weaks[FIR] = 0;	
				immune[immunePos].weaks[SLA] = 0;	
				immune[immunePos].weaks[COL] = 0;	
				immune[immunePos].immune[RAD] = 0;	
				immune[immunePos].immune[BLU] = 0;	
				immune[immunePos].immune[FIR] = 0;	
				immune[immunePos].immune[SLA] = 0;	
				immune[immunePos].immune[COL] = 0;	
			}
			immunePos++;
		} else if (part == 2) {
			infection[infectionPos].units = units;
			infection[infectionPos].hitPoints = hitPoints;
			infection[infectionPos].attack[conv(attackType)] = attack;
			infection[infectionPos].damage = attack;
			infection[infectionPos].ini = ini;
			if (wi == 1) {
				char *first = strtok(weaksimmune, ";\0");
				do {decode(first, 2, infectionPos);} while((first = strtok(NULL, ";\0")) != NULL);
			} else {
				immune[immunePos].weaks[RAD] = 0;	
				immune[immunePos].weaks[BLU] = 0;	
				immune[immunePos].weaks[FIR] = 0;	
				immune[immunePos].weaks[SLA] = 0;	
				immune[immunePos].weaks[COL] = 0;	
				immune[immunePos].immune[RAD] = 0;	
				immune[immunePos].immune[BLU] = 0;	
				immune[immunePos].immune[FIR] = 0;	
				immune[immunePos].immune[SLA] = 0;	
				immune[immunePos].immune[COL] = 0;	
			}
			infectionPos++;
		}

		leny++;
	}

	fclose(a);
	printit();

	for (int i = 0; i < immunePos; i++) {
		both[bothPos] = immune[i];
		both[bothPos].type = 1;
		bothPos++;
	}
	for (int i = 0; i < infectionPos; i++) {
		both[bothPos] = infection[i];
		both[bothPos].type = 2;
		bothPos++;
	}

	for (int i = 0; i < bothPos; i++) {
		bothOrig[i] = both[i];
	}
	bothOrigPos = bothPos;
	for (int zz = 31; zz < 32; zz++) {
		//639
		bothPos = bothOrigPos;
		for (int i = 0; i < bothPos; i++) {
			both[i] = bothOrig[i];
		}

		for (int i = 0; i < bothPos; i++) {
			if (both[i].type == 1) {
				both[i].damage += zz;
				for (int j = RAD; j <= COL; j++) {
					if (both[i].attack[j] != 0) {
						both[i].attack[j] += zz;
						break;
					}
				}
			}
		}
		printf("bothPos is %d\n", bothPos);
		int round123 = 0;
fightAgain:
		for (int i = 0; i < bothPos; i++) {both[i].alAttr = 0; both[i].alAttd = 0;}
		int changed55;

again44:
		changed55 = 0;
		for (int i = 0; i < bothPos;i++) {
			if (both[i].units <= 0) {
				for (int j = i; j < bothPos-1; j++) {
					both[j] = both[j+1];
					both[j].itsI = j;
				}
				bothPos--;
				changed55 = 1;
			}
		}
		if (changed55 == 1) {
			goto again44;
		}

		for (int i = 0; i < bothPos; i++) {
			both[i].itsI = i;
		}
		int tot = 0;
		int immCount = 0, infCount =0;
		for (int i = 0; i < bothPos; i++) {
			if (both[i].type == 1 && both[i].units>0) {
				printf("IMM: %d (ini:%d) (power:%d)\n", both[i].units, both[i].ini, both[i].units*both[i].damage);
				immCount++;
				tot+= both[i].units;
			} else if (both[i].type == 2 && both[i].units > 0) {
				printf("INF: %d (ini:%d) (power:%d)\n", both[i].units, both[i].ini, both[i].units*both[i].damage);
				infCount++;
				tot+= both[i].units;
			}
			both[i].itsI = i;
		}
		if (immCount == 0 || infCount == 0) {
			printf("game over **tot: %d zz is %d im:%d V inf:%d\n", tot, zz, immCount, infCount);
			if (infCount == 0) {
				printf("game over FOR GOOD **tot: %d zz is %d im%d V inf%d\n", tot, zz, immCount, infCount);
				printf("for GOOD ROUND:  %d \n", zz);
				printf("for GOOD ANS: [[ %d ]]\n", tot);
				exit(0);
			}
			continue;
		}

		////////////////////////////////
		///////MAIN LOOP 


		//printf("---------- round %d --------\n", round123);

		for (int i = 0; i < bothPos; i++) {
			both[i].ignore = 0;
		}

		if (bothPos == 2) {
		}
			
		for (int i = 0; i < bothPos; i++) {
			//getchar();
			int attr = nextAttrSortByPowerThenInitiativeNotMe();
			printf("both[%d].type is %d\n", attr, both[attr].type);
			struct atk_s attd = targetSelectionByMostDamageHighestPower(attr);
			if (bothPos == 2 && attd.itsI == -1) { perror("ERR444\n"); exit(0);}
			if (attd.itsI > 40 ) { printf("%d\n", attd.atk); exit(0); }
			//printf("ATTR SEL is %d ATTD is %d\n", attr, attd.itsI);
			//printf("ATTR SEL is %d ATTD is %d\n", both[attr].units, both[attd.itsI].units);


			both[attr].alAttr = 1;
			if (attd.atk == -1) {
				//printf("ATTR SEL is %d ATTD is %d\n", both[attr].units, both[attd.itsI].units);
				printf("SETTING ignore for ^^^^^^ %d\n", attr);
				both[attr].ignore = 1;continue;
			} else {
				printf("ALL OK bothPos is %d\n", bothPos);
				both[attd.itsI].alAttd = 1;
				both[attr].alAttr = 1;
				both[attr].toattack = attd;
				//both[attr].toattack.atk = attd.atk;
				//both[attr].toattack.atkr = both[attr].hitPoints;
			}

		}
		for (int i = 0; i < bothPos; i++) {
			both[i].alAttd = 0; both[i].alAttr = 0;
		}
		for (int i = 0; i < bothPos; i++) {
			//getchar();
			int attr = nextAttrSortByInitiativeNotMe();
			if (attr == -1) {printf("already attacked (%d) continue\n", both[attr].units); continue;}
			if (both[attr].ignore == 1) {perror("ATTR ERR224\n"); exit(0);}

			//if (round123 > 0) {if (attr == 2) {both[2].alAttr = 1; continue;}}

			//printf("attacker: is %d (%d %d)\n", attr, both[attr].units, both[attr].damage);
			//struct atk_s attd = targetSelectionByMostDamageHighestPower(attr);
			if (both[attr].toattack.atk == -1) {/*printf("already...(%d)\n", both[attr].units); */continue;}
			if (bothPos == 2) {
//				printf("attacked: is %d [[[%d]]] (%d %d)\n", attd.itsI, attd.atk, both[attd.itsI].units, both[attd.itsI].damage);
				printf("attacker: is %d \n", attr);
				printf("attacking: is %d \n", both[attr].toattack.itsI);
			}
			attack(attr, both[attr].toattack);
			if (bothPos == 2) {getchar();}
		}
		round123++;

		{ goto fightAgain;}

	}
}

void attack(int attr, struct atk_s attd) {
	int origU = both[attd.itsI].units;
	struct atk_s rejig;
	int found = 0;
	for (int j = RAD; j <= COL; j++) {
		if (both[attr].attack[j] != 0) {
			if (both[attd.itsI].immune[j] == 1) {
				//printf("here2 zero\n");
	printf("WARNING attack is zero\n");
				rejig.atk = 0;
				goto end;
			}
			if (both[attd.itsI].weaks[j] == 1) {
	printf("NO WARNING attack double\n");
				rejig.atk = both[attr].attack[j] * both[attr].units *2;
				goto end;
			}
	printf("NO WARNING attack norm\n");
			rejig.atk = both[attr].attack[j] * both[attr].units;
			goto end;
		} else {
			found++;
		}
	}	
end:
	//printf("rejig.atk is %d was attd.atk %d\n", rejig.atk, attd.atk); 
	printf("BEFORE %d \n", both[attd.itsI].units);
	printf("BEFORE %d \n", both[attd.itsI].units);
	int BEF = both[attd.itsI].units;
	both[attd.itsI].units -=
		rejig.atk / both[attd.itsI].hitPoints;

	printf("AFTER %d -= %d / %d\n", both[attd.itsI].units, rejig.atk, both[attd.itsI].hitPoints);
	int AFT = both[attd.itsI].units;
	if (bothPos == 2 && AFT == BEF && rejig.atk != 0) { STALE++; printf("STALEMATE AFT == BEF === %d == %d\n", BEF, AFT);}
	if (STALE == 1000) {printf("stopping coz of stale\n"); exit(0);}
	
		
	if (both[attd.itsI].units <= 0) {
		//printf("%d attacks %d killing (ALL) %d units\n", attr, attd.itsI, origU);
	} else {
		//printf("%d attacks %d killing %d units\n", attr, attd.itsI, rejig.atk/both[attd.itsI].hitPoints);
	}getchar();

	both[attd.itsI].alAttd = 1;
	both[attr].alAttr = 1;

}
struct atk_s targetSelectionByHighestPowerThenIni(int attr)
{
	struct atk_s atk_RET2; atk_RET2.atk = -1; 
	if (both[attr].alAttr == 1) {perror("alreadyATTR\n"); return atk_RET2;}

	struct atk_s atk[40]; int atkPos = 0;
	for (int i = 0; i < bothPos; i++) {
		if (both[i].type == both[attr].type) {continue;}	
		if (both[i].alAttd == 1) {continue;}	
		if (i == attr) {continue;}	
		for (int j = RAD; j <= COL; j++) {
			if (both[attr].attack[j] != 0) {
				if (both[i].immune[j] == 1) {
					atk[atkPos].atk = 0;
					atk[atkPos].itsI = both[i].itsI;
					atk[atkPos].power = both[i].damage*both[i].units;
					atk[atkPos].ini = both[i].ini;
					atkPos++;
					goto next;
				}
				if (both[i].weaks[j] == 1) {
					atk[atkPos].atk = both[attr].attack[j] * both[attr].units *2;
					atk[atkPos].itsI = both[i].itsI;
					atk[atkPos].power = both[i].damage*both[i].units;
					atk[atkPos].ini = both[i].ini;
					atkPos++;
					goto next;
				}

				atk[atkPos].atk = both[attr].attack[j] * both[attr].units;
				atk[atkPos].itsI = both[i].itsI;
				atk[atkPos].power = both[i].damage*both[i].units;
				atk[atkPos].ini = both[i].ini;
				atkPos++;
				goto next;
			}
		}	
next:
		continue;
	}

	struct atk_s retAtk; retAtk.atk = -1;
	if (atkPos == 0) {/*printf("no sel -- AT END...\n"); */return retAtk;}
	////////////////////////////
	//// arrange by damage
	int continue2;
again4:
	continue2 = 0;
	for (int i = 0; i < atkPos-1; i++) {
		if (atk[i].atk < atk[i+1].atk) {
			struct atk_s tmp;
			tmp = atk[i+1];
			atk[i+1] = atk[i];
			atk[i] = tmp;
			continue2 = 1;
		}
	}
	if (continue2 == 1) {
		goto again4;
	}

	if (atkPos < 2 || atk[0].atk != atk[1].atk) {
		return atk[0];
	}
	/////////////////////////////////////////
	//// arrange by effective power
	struct atk_s atkEq[40]; int atkEqPos = 0;
	atkEq[0] = atk[0]; atkEqPos++;
	for (int i = 1; i < atkPos; i++) {
		if (atk[0].atk == atk[i].atk) {
			atkEq[atkEqPos++] = atk[i];
		}
	}

	int continue5;
again6:
	continue5 = 0;
	for (int i = 0; i < atkEqPos-1; i++) {
		if (atkEq[i].power < atkEq[i+1].power) {
			struct atk_s tmp;
			tmp = atkEq[i+1];
			atkEq[i+1] = atkEq[i];
			atkEq[i] = tmp;
			continue5 = 1;
		}
	}
	if (continue5 == 1) {
		goto again6;
	}

	if (atkEqPos < 2 || atkEq[0].power != atkEq[1].power) {
		return atkEq[0];
	}

	//////////////////////////
	/// arrange by ini
	struct atk_s atkEq2[40]; int atkEq2Pos = 0;
	atkEq2[0] = atkEq[0]; atkEq2Pos++;
	for (int i = 1; i < atkEqPos; i++) {
		if (atkEq[0].power == atkEq[i].power) {
			atkEq2[atkEq2Pos++] = atkEq[i];
		}
	}

	int continue6;
again7:
	continue6 = 0;
	for (int i = 0; i < atkEq2Pos-1; i++) {
		if (both[atkEq2[i].itsI].ini < 
				both[atkEq2[i+1].itsI].ini) {
			struct atk_s tmp;
			tmp = atkEq2[i+1];
			atkEq2[i+1] = atkEq2[i];
			atkEq2[i] = tmp;
			continue6 = 1;
		}
	}
	if (continue6 == 1) {
		goto again7;
	}

	if (atkEq2[0].ini ==  atkEq2[1].ini) {
		perror("ERR225"); exit(0);
	}
	return atkEq2[0];

}
struct atk_s targetSelectionByMostDamageHighestPower(int attr)
{
	struct atk_s atkR2;
	atkR2.atk = -1;
	atkR2.itsI = -1;
	atkR2.power = -1;
	atkR2.ini = -1;
	if (both[attr].alAttr == 1) {atkR2.atk = -1; perror("alreadyATTR\n"); return atkR2;}

	struct atk_s atk[40]; int atkPos = 0;
	for (int i = 0; i < bothPos; i++) {
		//printf("both[i].type %d V %d both[attr].type (%d V %d)\n", both[i].type, both[attr].type, i, attr);
		if (both[i].units <= 0) {continue;}	
		if (both[i].type == both[attr].type) {continue;}	
		if (both[i].alAttd == 1) {continue;}	
		if (i == attr) {continue;}	
		for (int j = RAD; j <= COL; j++) {
			if (both[attr].attack[j] != 0) {
				if (both[i].immune[j] == 1) {
					atk[atkPos].atk = 0;
					atk[atkPos].itsI = both[i].itsI;
					atk[atkPos].power = both[i].damage*both[i].units;
					atk[atkPos].ini = both[i].ini;
					atkPos++;
					goto next;
				}
				if (both[i].weaks[j] == 1) {
					atk[atkPos].atk = both[attr].attack[j] * both[attr].units *2;
					atk[atkPos].itsI = both[i].itsI;
					atk[atkPos].power = both[i].damage*both[i].units;
					atk[atkPos].ini = both[i].ini;
					atkPos++;
					goto next;
				}

				atk[atkPos].atk = both[attr].attack[j] * both[attr].units;
				atk[atkPos].itsI = both[i].itsI;
				atk[atkPos].power = both[i].damage*both[i].units;
				atk[atkPos].ini = both[i].ini;
				atkPos++;
				goto next;
			}
		}	
next:
		continue;
	}

	struct atk_s retAtk; retAtk.atk = -1;
	if (atkPos == 0) {printf("no sel -- AT END...\n"); return retAtk;}
	////////////////////////////
	//// arrange by damage
	int continue2;
again4:
	continue2 = 0;
	for (int i = 0; i < atkPos-1; i++) {
		if (atk[i].atk < atk[i+1].atk) {
			struct atk_s tmp;
			tmp = atk[i+1];
			atk[i+1] = atk[i];
			atk[i] = tmp;
			continue2 = 1;
		}
	}
	if (continue2 == 1) {
		goto again4;
	}

	if (atkPos < 2 || atk[0].atk != atk[1].atk) {
		return atk[0];
	}
	/////////////////////////////////////////
	//// arrange by effective power
	struct atk_s atkEq[40]; int atkEqPos = 0;
	atkEq[0] = atk[0]; atkEqPos++;
	for (int i = 1; i < atkPos; i++) {
		if (atk[0].atk == atk[i].atk) {
			atkEq[atkEqPos++] = atk[i];
		}
	}

	int continue5;
again6:
	continue5 = 0;
	for (int i = 0; i < atkEqPos-1; i++) {
		if (atkEq[i].power < atkEq[i+1].power) {
			struct atk_s tmp;
			tmp = atkEq[i+1];
			atkEq[i+1] = atkEq[i];
			atkEq[i] = tmp;
			continue5 = 1;
		}
	}
	if (continue5 == 1) {
		goto again6;
	}

	if (atkEqPos < 2 || atkEq[0].power != atkEq[1].power) {
		return atkEq[0];
	}

	//////////////////////////
	/// arrange by ini
	struct atk_s atkEq2[40]; int atkEq2Pos = 0;
	atkEq2[0] = atkEq[0]; atkEq2Pos++;
	for (int i = 1; i < atkEqPos; i++) {
		if (atkEq[0].power == atkEq[i].power) {
			atkEq2[atkEq2Pos++] = atkEq[i];
		}
	}

	int continue6;
again7:
	continue6 = 0;
	for (int i = 0; i < atkEq2Pos-1; i++) {
		if (both[atkEq2[i].itsI].ini < 
				both[atkEq2[i+1].itsI].ini) {
			struct atk_s tmp;
			tmp = atkEq2[i+1];
			atkEq2[i+1] = atkEq2[i];
			atkEq2[i] = tmp;
			continue6 = 1;
		}
	}
	if (continue6 == 1) {
		goto again7;
	}

	if (atkEq2[0].ini ==  atkEq2[1].ini) {
		perror("ERR228"); exit(0);
	}
	return atkEq2[0];

}

int nextAttrSortByInitiativeNotMe() {
	///////////////////////////
	/////////arrange by initiative
	struct group_s possTYP[40];
	int possTYPPos = 0;
	for (int i = 0; i < bothPos; i++) {
		if (both[i].units > 0 && both[i].alAttr == 0 && both[i].ignore == 0) {
			possTYP[possTYPPos++] = both[i];
		}
		if (both[i].ignore == 1) {
			//printf("got an 			ignore\n"); continue;
		}
	}

	if (possTYPPos == 0) {/*printf("none\n"); */return -1;}
	int changed2;

again3:
	changed2 = 0;
	for (int i = 0; i < possTYPPos-1; i++) {
		if (possTYP[i].ini < possTYP[i+1].ini) {
			struct group_s tmp;
			tmp = possTYP[i+1];
			possTYP[i+1] = possTYP[i];
			possTYP[i] = tmp;
			changed2 = 1;
		}
	}
	if (changed2 == 1) {
		goto again3;
	}

	if (possTYPPos > 1 && possTYP[0].ini == possTYP[1].ini) {
		//printf("possTYPE[0].ini is %d units:%d\n", possTYP[0].ini, both[possTYP[0].itsI].units);
		//printf("possTYPE[1].ini is %d units:%d\n", possTYP[0].ini, both[possTYP[1].itsI].units);

		perror("ERR223\n"); exit(0);
	}
	//printf("possTYP[0].ini is %d\n", possTYP[0].ini);
	return possTYP[0].itsI;
}

int nextAttrSortByPowerThenInitiativeNotMe() {
	for (int i = 0; i < bothPos; i++) {
		both[i].power = both[i].units * both[i].damage;
	}
	for (int i = 0; i < bothPos; i++) { both[i].itsI = i; }

	int changed;

	struct group_s poss3[40];
	for (int i = 0; i < bothPos; i++) {
		poss3[i] = both[i];
	}
again2:
	changed = 0;
	for (int i = 0; i < bothPos-1; i++) {
		if (poss3[i].power < poss3[i+1].power) {
			struct group_s tmp;		
			tmp = poss3[i+1];
			poss3[i+1] = poss3[i];
			poss3[i] = tmp;
			changed = 1;
		}
	}
	if (changed == 1) { goto again2; }

	struct group_s poss[40];
	int possPos = 0;
	for (int i = 0; i < bothPos; i++) {
		if (poss3[i].alAttr == 0) {
			poss[possPos++] = poss3[i];
		}
	}
	if (possPos == 1 || poss[0].power != poss[1].power) {
		return poss[0].itsI;
	}

	struct group_s possEq[40];
	int possEqPos = 0;
	possEq[0] = poss[0]; possEqPos++;
	for (int i = 1; i < possPos; i++) {
		if (poss[0].power == poss[i].power) {
			possEq[possEqPos++] = poss[i];
		}
	}

	int changed2;

again3:
	changed2 = 0;
	for (int i = 0; i < possEqPos-1; i++) {
		if (possEq[i].ini < possEq[i+1].ini) {
			struct group_s tmp;
			tmp = possEq[i+1];
			possEq[i+1] = possEq[i];
			possEq[i] = tmp;
			changed2 = 1;
		}
	}
	if (changed2 == 1) {
		goto again3;
	}

	return possEq[0].itsI;
}

void printit()
{
	for (int i = 0; i < immunePos; i++) {
		printf("Immune %d: ", i);

		printf("units: %d\n", immune[i].units);
		printf("hitPoints: %d\n", immune[i].hitPoints);
		printf("ATTACk:\n");
		for (int j = RAD; j <= COL; j++) {
			printf("%d: %d\n", j, immune[i].attack[j]);
		}
		printf("IMMUNE:\n");
		for (int j = RAD; j <= COL; j++) {
			printf("%d: %d\n", j, immune[i].immune[j]);
		}
		printf("WEAKS:\n");
		for (int j = RAD; j <= COL; j++) {
			printf("%d: %d\n", j, immune[i].weaks[j]);
		}
		printf("intitiative: %d\n", immune[i].ini);
	} 
	for (int i = 0; i < infectionPos; i++) {
		printf("Infection %d: ", i);

		printf("units: %d\n", infection[i].units);
		printf("hitPoints: %d\n", infection[i].hitPoints);
		printf("ATTACK:\n");
		for (int j = RAD; j <= COL; j++) {
			printf("%d: %d\n", j, infection[i].attack[j]);
		}
		printf("IMMUNE:\n");
		for (int j = RAD; j <= COL; j++) {
			printf("%d: %d\n", j, infection[i].immune[j]);
		}
		printf("WEAKS:\n");
		for (int j = RAD; j <= COL; j++) {
			printf("%d: %d\n", j, infection[i].weaks[j]);
		}
		printf("intitiative: %d\n", infection[i].ini);
	} 
}

void decode(char what[], int immuneorinfection, int pos) {
	///	printf("%s %d %d\n", what, immuneorinfection, pos); printf("[[[%s\n", strstr(what, "weak"));
	if (strstr(what, "weak") != NULL) {
		if (immuneorinfection == 1) {//immune
			printf("got immune\n");
			if (strstr(what, "radiation") != NULL) {
				immune[pos].weaks[RAD] = 1;	
			}
			if (strstr(what, "slashing") != NULL) {
				immune[pos].weaks[SLA] = 1;	
			}
			if (strstr(what, "bludgeoning") != NULL) {
				immune[pos].weaks[BLU] = 1;	
			}
			if (strstr(what, "fire") != NULL) {
				immune[pos].weaks[FIR] = 1;	
			}
			if (strstr(what, "cold") != NULL) {
				immune[pos].weaks[COL] = 1;	
			}
		} else {
			if (strstr(what, "radiation") != 0) {
				infection[pos].weaks[RAD] = 1;	
			}
			if (strstr(what, "slashing") != 0) {
				infection[pos].weaks[SLA] = 1;	
			}
			if (strstr(what, "bludgeoning") != 0) {
				infection[pos].weaks[BLU] = 1;	
			}
			if (strstr(what, "fire") != 0) {
				infection[pos].weaks[FIR] = 1;	
			}
			if (strstr(what, "cold") != 0) {
				infection[pos].weaks[COL] = 1;	
			}
		}
	} else if (strstr(what, "immune") != NULL) {
		if (immuneorinfection == 1) {//immune
			if (strstr(what, "radiation") != 0) {
				immune[pos].immune[RAD] = 1;	
			}
			if (strstr(what, "slashing") != 0) {
				immune[pos].immune[SLA] = 1;	
			}
			if (strstr(what, "bludgeoning") != 0) {
				immune[pos].immune[BLU] = 1;	
			}
			if (strstr(what, "fire") != 0) {
				immune[pos].immune[FIR] = 1;	
			}
			if (strstr(what, "cold") != 0) {
				immune[pos].immune[COL] = 1;	
			}
		} else {
			if (strstr(what, "radiation") != 0) {
				infection[pos].immune[RAD] = 1;	
			}
			if (strstr(what, "slashing") != 0) {
				infection[pos].immune[SLA] = 1;	
			}
			if (strstr(what, "bludgeoning") != 0) {
				infection[pos].immune[BLU] = 1;	
			}
			if (strstr(what, "fire") != 0) {
				infection[pos].immune[FIR] = 1;	
			}
			if (strstr(what, "cold") != 0) {
				infection[pos].immune[COL] = 1;	
			}
		}
	}
}

int conv(char type[]) {
	if (strcmp(type, "fire") == 0) {
		return FIR;
	} else if (strcmp(type, "bludgeoning") == 0) {
		return BLU;
	} else if (strcmp(type, "radiation") == 0) {
		return RAD;
	} else if (strcmp(type, "cold") == 0) {
		return COL;
	} else if (strcmp(type, "slashing") == 0) {
		return SLA;
	}

	return -1;
}
