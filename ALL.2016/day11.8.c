#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <map>

struct count123_s {
	long long val;
	int qs[10];
	int steps;
};
count123_s count123[100];
using namespace std;
int ind = -1;
void printit2();
void printit3(int *qss);
void printit4(unsigned long long key, int *qs, int steps);
int CPOINTPOS = 0;

int CHECK = 200;
int lenx, leny;
#define DAY "2016 day11 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 1000
//#define getchar()
map <unsigned long long, int> mp;
char grid[5][12][4];
int posX = 0;
void makemove(int steps, int first, int lastfloor);
unsigned long long cpoint(int steps);
int al(int steps);
void restore(unsigned long long ps, int *steps);
unsigned long long genkey(int steps);
int docheckQs(int one, int two);
int docheck();
int docheck2();

struct tosort_s {
	int floor[4];
};
struct tosort_s tosort[10];
int docheck3(int qss[10], int end, int lastfloor, tosort_s Orig);

int maxc = 0;
void printit(int qs[], int steps, int ind);

int minSteps = 999;
void sig_handler(int signum){
        printf("CONOR ctrl-z minSteps is:: %d\n", minSteps); getchar();
}

int main(int argc, char **argv)
{
	//int fd = dup(1); close(1);
         signal(SIGTSTP, sig_handler);

	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	if (argc > 2) {CHECK = atoi(argv[2]);}
	printf("CHECK is %d\n", CHECK); //getchar();
	char line1[SIZE];
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			for (int i = 0; i < 4; i++) {
				grid[y][x][i] = '0';
			}
		}
	}
	grid[0][posX][0] = 'E'; grid[0][posX][1] = '\0'; posX++;
	while(1) 
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		//	printf("LINE: %s\n", line1);
#endif
		char rest[200];
		char floor[20];

		int ret1 = sscanf(line1, "The %s floor contains %[^\0]", floor, rest);

		string fl = floor;
		int fintY;
		if (fl == "first") {
			fintY = 0;
		} else if (fl == "second") {
			fintY = 1;
		} else if (fl == "third") {
			fintY = 2;
		} else if (fl == "fourth") {
			fintY = 3;
		} else {
			printf("ERROR floor. %s..\n", floor);
		}

		if (ret1 == 2) {
			char *first = strtok(rest, " ");
			int count = 0;
			do {
				if (strcmp(first, "a") == 0) {
					//ignore
				} else if (strcmp(first, "nothing") == 0) {
					//ignore
				} else if (strcmp(first, "relevant.") == 0) {
					//ignore
				} else if (strcmp(first, "and") == 0) {
					//ignore
				} else {
					count++;
					//printf("%c", first[0]);	
					if (count % 2 != 0) {grid[fintY][posX][0] = toupper(first[0]); grid[fintY][posX][1] = toupper(first[1]); }
					if (count % 2 == 0) {grid[fintY][posX][2] = toupper(first[0]); grid[fintY][posX][3] = '\0'; posX++;}
				}
			} while ((first = strtok(NULL, " ")) != NULL);
		}
		ret1 = 0; 
		leny++;
	}
	fclose(a);
	printf("START: \n");
	for (int y = leny-1; y >= 0; y--) {
		printf("F%d: ", y);
		for (int x = 0; x < posX; x++) {
			if (grid[y][x][0] != '0') {
				printf("%s ", grid[y][x]);
			} else {
				printf("    ");
			}
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < 10; i++) {
		for (int fl = 0; fl < 4; fl++) {
			tosort[i].floor[fl] = 0;
		}
	}
	tosort[0].floor[0] = 1;
	tosort[1].floor[0] = 1;
	tosort[2].floor[0] = 1;
	tosort[3].floor[0] = 1;
	tosort[4].floor[1] = 1;
	tosort[5].floor[1] = 1;
	tosort[6].floor[2] = 1;
	tosort[7].floor[2] = 1;
	tosort[8].floor[2] = 1;
	tosort[9].floor[2] = 1;
	
	makemove(0, 1, 0);
	tot = 0;

	//fflush(stdout); dup2(fd, 1);
	printf("minSteps: [%d] END\n", minSteps);
	printf("maxc: [%d] END\n", maxc);
	//printf("count123: [%d] \n", count123);
} 
/*
START:
F3:
F2:                             PRG *PRM RUG *RUM
F1:                     *PLM *STM
F0: E THG *THM PLG STG
*/


int docheck() {
	int THG; for (THG = 0; THG < 4; THG++) {
		if (tosort[0].floor[THG] == 1) {break;} 
	}
	int THM; for(THM = 0; THM < 4; THM++) {
		if (tosort[1].floor[THM] == 1) {break;} 
	}
	int PLG; for (PLG = 0; PLG < 4; PLG++) {
		if (tosort[2].floor[PLG] == 1) {break;} 
	}
	int STG; for (STG = 0; STG < 4; STG++) {
		if (tosort[3].floor[STG] == 1) {break;} 
	}
	int PLM; for (PLM = 0; PLM < 4; PLM++) {
		if (tosort[4].floor[PLM] == 1) {break;}
	}
	int STM; for (STM = 0; STM < 4; STM++) {
		if (tosort[5].floor[STM] == 1) {break;}
	}
	int PRG; for (PRG = 0; PRG < 4; PRG++) {
		if (tosort[6].floor[PRG] == 1) {break;}
	}
	int PRM; for (PRM = 0; PRM < 4; PRM++) {
		if (tosort[7].floor[PRM] == 1) {break;} 
	}
	int RUG; for (RUG = 0; RUG < 4; RUG++) {
		if (tosort[8].floor[RUG] == 1) {break;} 
	}
	int RUM; for (RUM = 0; RUM < 4; RUM++) {
		if (tosort[9].floor[RUM] == 1) {break;}
	}
/*
START:
F3:
F2:                             PRG *PRM RUG *RUM
F1:                     *PLM *STM
F0: E THG *THM PLG STG
*/
	struct both_s {
		int M;
		int G;
	};
	struct both_s both[5];
//----------
	both[0].M = THM;
	both[0].G = THG;
//----------
	both[1].M = PLM;
	both[1].G = PLG;
//----------
	both[2].M = STM;
	both[2].G = STG;
//----------
	both[3].M = PRM;
	both[3].G = PRG;
//----------
	both[4].M = RUM;
	both[4].G = RUG;
//----------

	int pos = 0;
	struct both_s lookat[5];

	for (int it = 0; it < 5; it++) {
		if (both[it].M == both[it].G) {
			//ok
		} else {
			lookat[pos].M = both[it].M;
			lookat[pos].G = both[it].G;
			pos++;
			//lookat[pos++] = both[it];
		}
	}
	
	if (pos != 0) {
		for (int it = 0; it < pos; it++) {
			for (int it2 = 0; it2 < pos; it2++) {
				if (it == it2) {continue;}
				if (lookat[it].G == lookat[it2].M) {
					//printf("blown...\n");
					//chips blown
					return 0;
				} else if (lookat[it2].G == lookat[it].M) {
					//printf("blown...\n");
					return 0;
				}
			}
		}
	}
			
/*
START:
F3:
F2:                             PRG *PRM RUG *RUM
F1:                     *PLM *STM
F0: E THG *THM PLG STG
*/
	//printit2();	
	return 1;

}
int docheckQs(int Ione, int Itwo) {
	if (Ione == 0 && Itwo != 1) {
		return 0;
	} else if (Ione == 2 && Itwo != 4) {
		return 0;
	}  else if (Ione == 3 && Itwo != 5) {
		return 0;
	} else if (Ione == 6 && Itwo != 7) {
		return 0;
	} else if (Ione == 8 && Itwo != 9) {
		return 0;
	} else {
		return 1;
	}

}
void makemove(int steps, int first, int lastfloor) {
	ind++;
	if (steps >= CHECK) {ind--; return;}
	if (steps >= minSteps) {ind--; return;}
	unsigned long long mainPos;
	///if ((mainPos = cpoint(steps)) == 1) {ind--; return;}
//	if ((mainPos = cpoint(steps)) == 1) {ind--; return;}
	mainPos = cpoint(steps);
	int qs[10];
	int end;
	int prevlastfloor = lastfloor;
	for (end = 2; end >=1; end--) {
		for (int o = 0; o < end; o++) {
			qs[o] = 1;
		}
		for (int z = end; z < 10; z++) {
			qs[z] = 0;
		}
		sort(qs, qs+10);
		do {
			restore(mainPos, &steps);

			if (qs[1] == 1 || qs[4] == 1 || qs[5] == 1 || qs[7] == 1 || qs[9] == 1) {} else {continue;}
			if (first == 1) { if (qs[0] == 1 || qs[1] == 1 || qs[2] == 1 || qs[3] == 1) {} else {continue;} }

			int qpos[2]; int myp = 0;
			if (end == 2) { for (int i = 0; i < 10; i++) { if (qs[i] == 1) { qpos[myp++] = i; } if (myp == 2) {break;} } }
					
			if (end == 2) { 
				int found66 = 0;
				for (int fl = 0; fl < 4; fl++) {
					if (tosort[qpos[0]].floor[fl] == tosort[qpos[1]].floor[fl]) {
						found66++;
					} else {
						break;
					}
				}
				if (found66 != 4) {continue;}	
			} else if (end == 1) { for (int i = 0; i < 10; i++) { if (qs[i] == 1) {qpos[0] = i; break;} } }
			if (end == 2) {
				if (docheckQs(qpos[0], qpos[1]) ==  0) {continue;}
				if (docheckQs(qpos[1], qpos[0]) ==  0) {continue;}
			}
			struct tosort_s Orig;
			for (int fl = 0; fl < 4; fl++) {
				Orig.floor[fl] = tosort[qpos[0]].floor[fl];
			}
			if (docheck2() == 0) {continue;};
			if (docheck3(qs, end, prevlastfloor, Orig) == 0) {continue;};
			//if (docheck() == 0) {continue;};
			
			if (tosort[qpos[0]].floor[lastfloor] == 1) {} else {continue;}
			//int vPos; for (int fl = 0; fl < 4; fl++) { if (tosort[qpos[0]].floor[fl] == 1) { vPos = fl; break; } }
			//if (vPos != lastfloor) {printf("ERR vPos\n"); exit(0);}	
			int vPos = lastfloor;
			for (int x = 3; x >=0; x--) {
				restore(mainPos, &steps);
				struct tosort_s tmpsort;
				int lastfloor;
				if (x == 0) {
					tmpsort.floor[0] = 0; tmpsort.floor[1] = 0; tmpsort.floor[2] = 0; tmpsort.floor[3] = 1;
					lastfloor = 3;
				} else if (x == 1) {
					tmpsort.floor[0] = 0; tmpsort.floor[1] = 0; tmpsort.floor[2] = 1; tmpsort.floor[3] = 0;
					lastfloor = 2;
				} else if (x == 2) {
					tmpsort.floor[0] = 0; tmpsort.floor[1] = 1; tmpsort.floor[2] = 0; tmpsort.floor[3] = 0;
					lastfloor = 1;
				} else if (x == 3) {
					tmpsort.floor[0] = 1; tmpsort.floor[1] = 0; tmpsort.floor[2] = 0; tmpsort.floor[3] = 0;
					lastfloor = 0;
				}
				if (end == 2) {
					for (int fl = 0; fl < 4; fl++) {
						tosort[qpos[0]].floor[fl] = tmpsort.floor[fl];  
						tosort[qpos[1]].floor[fl] = tmpsort.floor[fl];  
					}
				} else {
					for (int fl = 0; fl < 4; fl++) {
						tosort[qpos[0]].floor[fl] = tmpsort.floor[fl];  
					}
				}
				if (docheck3(qs, end, prevlastfloor, Orig) == 0) {continue;};
				int dist = abs(lastfloor - vPos);
				if (dist == 0) {continue;}
				if (dist != 1) {continue;}
				//if (al(steps) == 1) {continue;}
				if (docheck2() == 0) {continue;}
				if (docheck3(qs, end, prevlastfloor, Orig) == 0) {continue;};
				if (docheck() == 0) {printf("NEVER"); printit2(); continue;}
				int found33 = 0; for (int i = 0; i < 10; i++) { if (tosort[i].floor[3] == 1) { found33++; } }
				if (found33 == 10) {	
					if (steps+1 < minSteps) {minSteps = steps+1;}
					//printit(qs, steps, ind);
					count123[ind].val = mainPos;
					count123[ind].steps = steps;
					for (int i = 0; i < 10; i++) {
						count123[ind].qs[i] = qs[i];
					}
					for (int i = 0; i <= ind; i++) {
						printf("---------\n");
						printit4(count123[i].val, count123[i].qs, count123[i].steps);
						printf("---------\n");
					}
					printf("END reached.^^.. %d %d ------ret----(ind:%d)-\n", steps, minSteps, ind); ind--; return; //exit(0);
				} else {
					//if (docheck() == 0) {continue;}
					printit(qs, steps, ind);
					if (docheck2() == 0) {continue;}
					//docheck3(qs, end, prevlastfloor, Orig);
					count123[ind].val = mainPos;
					count123[ind].steps = steps;
					for (int i = 0; i < 10; i++) {
						count123[ind].qs[i] = qs[i];
					}
					makemove(steps+dist, 2, lastfloor);
					//printf("calling vvvvvv restore:\n");
					//restore(mainPos, &steps);
					//printit(qs, steps, ind);
					//printf("after --- ^^^^^ restore\n");
				}
			}
		} while (next_permutation(qs, qs+10));
	}
	ind--;
}
int comp(int i1, int i2) {

	int found = 0;
	for (int fl = 0; fl < 4; fl++) {
		if (tosort[i1].floor[fl] == tosort[i2].floor[fl]) {
			found++;
		} else {
			break;
		}
	}
	if (found == 4) {
		return 0;
	} else {
		return 1;
	}
}
int docheck3(int qss[10], int end, int prevlastfloor, struct tosort_s Orig) {
	int qpos[2]; int pos = 0;
	if (end == 1) {
		for (int i = 0; i < 10; i++) {
			if (qss[i] == 1) {
				qpos[0] = i; pos++; goto after1;
			}
		}
	} else if (end == 2) {
		for (int i = 0; i < 10; i++) {
			if (qss[i] == 1) {
				qpos[pos++] = i; 
				if (pos == 2) {goto after1;}
			}
		}
	}
after1:
	if (end == 1) {
		if (qpos[0] == 1 || qpos[0] == 4 || qpos[0] == 5 || qpos[0] == 7 || qpos[0] == 9) {} else {/*printf("PROBS10"); printit3(qss); */return 0;}
	} else if (end == 2) {
		switch (qpos[0]) {
			case 1:
				if (qpos[1] == 4 || qpos[1] == 5 || qpos[1] == 7 || qpos[1] == 9 ) {/*ok*/} else {/*printf("PROBS11"); printit3(qss); */ return 0;}
				break;
			case 4:
				if (qpos[1] == 5 || qpos[1] == 7 || qpos[1] == 9 ) {/*ok*/} else {/*printf("PROBS12"); printit3(qss);*/ return 0;}
				break;
			case 5:
				if (qpos[1] == 7 || qpos[1] == 9 ) {/*ok*/} else {/*printf("PROBS13"); printit3(qss);*/ return 0;}
				break;
			case 7:
				if (qpos[1] == 9 ) {/*ok*/} else {/*printf("PROBS14"); printit3(qss);*/ return 0;}
				break;
			case 9:
				{/*printf("PROBS15"); printit3(qss);*/ return 0;}
				break;
		}	
	}
/*
F2:                             PRG *PRM RUG *RUM
F1:                     *PLM *STM
F0: E THG *THM PLG STG
*/

	if (end == 2) {
		switch (qpos[0]) {
			case 0:
				if (qpos[1] == 1) {} else {/*printf("PROBS20");*/ return 0;}
				break;
			case 2:
				if (qpos[1] == 4) {} else {/*printf("PROBS21"); */return 0;}
				break;	
			case 3:
				if (qpos[1] == 5) {} else {/*printf("PROBS22"); */return 0;}
				break;
			case 6:
				if (qpos[1] == 7) {} else {/*printf("PROBS23"); */return 0;}
				break;
			case 8:
				if (qpos[1] == 9) {} else {/*printf("PROBS24"); */return 0;}
				break;
		}

	}
	if (Orig.floor[prevlastfloor] != 1) {
		/*printf("PROBS30"); */return 0;
	}
	return 1;
}
int docheck2() {
	int remove[10]; int pos = 0;
	for (int i = 0 ; i < 10; i++) {
		switch (i) {
			case 0:
				if (comp(0, 1) == 0) {remove[pos++] = 0; remove[pos++] = 1;}
				break;
			case 2:
				if (comp(2, 4) == 0) {remove[pos++] = 2; remove[pos++] = 4; }
				break;
			case 3:
				if (comp(3, 5) == 0) {remove[pos++] = 3; remove[pos++] = 5; }
				break;
			case 6:
				if (comp(6, 7) == 0) {remove[pos++] = 6; remove[pos++] = 7; }
				break;
			case 8:
				if (comp(8, 9) == 0) {remove[pos++] = 8; remove[pos++] = 9; }
				break;
		}
	}
	
	for (int i = 0 ; i < 10; i++) {
		for (int x = 0; x < pos; x++) {
			if (remove[x] == i) {goto nextI;}
		}
		switch (i) {
			case 1:
				for (int j = 0 ; j < 10; j++) {
					for (int x = 0; x < pos; x++) {
						if (remove[x] == j) {goto nextJ;}  else {}
					}
					if (j == 2 || j==3 || j == 6 || j == 8) {
						if (comp(1, j) ==0) {/*printf("PROBS"); printit2(); */return 0;}
					}
nextJ:
					continue;
				}
				break;
			case 4:
				for (int j = 0 ; j < 10; j++) {
					for (int x = 0; x < pos; x++) {
						if (remove[x] == j) {goto nextJ2;}
					}
					if (j == 0 ||  j==3 || j==6 || j == 8) {
						if (comp(4, j) ==0) {/*printf("PROBS2 [%d %d]", 4, j); printit2(); */return 0;}
					}
nextJ2:
					continue;
				}
				break;
			case 5:
				for (int j = 0 ; j < 10; j++) {
					for (int x = 0; x < pos; x++) {
						if (remove[x] == j) {goto nextJ3;}  else {}
					}
					if (j== 0 || j == 2 || j == 6 || j == 8) {
						if (comp(5, j) ==0) {/*printf("PROBS3"); printit2();*/ return 0;}
					}
nextJ3:
					continue;
				}
				break;
			case 7:
				for (int j = 0 ; j < 10; j++) {
					for (int x = 0; x < pos; x++) {
						if (remove[x] == j) {goto nextJ4;}  else {}
					}
					if (j == 0 || j == 2 || j==3 || j == 8) {
						if (comp(7, j) ==0) {/*printf("PROBS4"); printit2(); */return 0;}
					}
nextJ4:
					continue;
				}
				break;
			case 9:
				for (int j = 0 ; j < 10; j++) {
					for (int x = 0; x < pos; x++) {
						if (remove[x] == j) {goto nextJ5;}  else {}
					}
					if (j == 0 || j == 2 || j==3 || j == 6 ) {
						if (comp(9, j) ==0) {/*printf("PROBS5"); printit2(); */return 0;}
					}
nextJ5:
					continue;
				}
				break;

		}
nextI:
	continue;
	}
	return 1;
}
void printit3(int *qss) {
	return;
	printf("-----VV\n");

	for (int fl = 3; fl >=0; fl--) { 
		for (int i = 0; i < 10; i++) { 
			printf("%d ", tosort[i].floor[fl]);
		}
		printf("\n"); 
	} 
	printf("\n"); 
	for (int i = 0; i < 10; i++) {
		printf("%d ", qss[i]);
	}
	printf("\n==============\n");
}
void printit2() {
	printf("-----VV\n");

	for (int fl = 3; fl >=0; fl--) { 
		for (int i = 0; i < 10; i++) { 
			printf("%d ", tosort[i].floor[fl]);
		}
		printf("\n"); 
	} 
	printf("\n==============\n");
}
void printit(int qs[], int steps, int ind) {
	return;
	printf("------------------VVVVV VVVV------------\n");
	for (int fl = 3; fl >=0; fl--) { 
		for (int i = 0; i < 10; i++) { 
			printf("%d ", tosort[i].floor[fl]);
		}
		printf("\n"); 
	} 
	printf("\n");

	printf("Q: ");
	for (int i = 0; i < 10; i++) {
		printf("%d ", qs[i]);
	} 
	printf("\n");	
	printf("steps: %d\n", steps);
	printf("ind: %d\n", ind);
	printf("------------------^^^^^^^^^^^^^^^------------\n");
}

void printit4(unsigned long long key, int *qss, int steps) {
	unsigned long long origKey = key;
	for (int fl = 0; fl < 4; fl++) {
		for (int i = 0; i < 10; i++) {
			tosort[i].floor[fl] = (key >> ((fl*10)+i)) & (unsigned long long)1;
			key = origKey;
		}
	}
	printit2();

	printf("\nQueue:\n"); 
	for (int i = 0; i < 10; i++) {
		printf("%d ", qss[i]);
	}
	printf("\nSteps: %d\n", steps);
	printf("-----------\n");
	
}
void restore(unsigned long long key, int *steps) {
	unsigned long long origKey = key;
	for (int fl = 0; fl < 4; fl++) {
		for (int i = 0; i < 10; i++) {
			tosort[i].floor[fl] = (key >> ((fl*10)+i)) & (unsigned long long)1;
			key = origKey;
		}
	}
	
	//*steps = mp.at(key);
}

int al(int steps) {
	long long key = genkey(steps);
	map <unsigned long long, int> ::iterator iter3;
	if ((iter3 = mp.find(key)) == mp.end()) {
		//not there
		return 0;
	} else {
		if (steps < iter3->second || iter3->second == -1) {
			iter3->second = steps;
			return 0;
		} else {
			return 1;
		}
	}
}

unsigned long long genkey(int steps) {
//	unsigned long long key = steps;
	unsigned long long key = 0;
	for (int fl = 0; fl < 4; fl++) {
		for (int i = 0; i < 10; i++) {
			if (tosort[i].floor[fl] == 1) {
				key |= (unsigned long long)1 << ((fl*10) + i);
			}
		}
	}
	return key;
}

unsigned long long cpoint(int steps) {
	long long key = genkey(steps);
	
	map <unsigned long long, int>::iterator iter3;
	if ((iter3 = mp.find(key)) == mp.end()) {
		mp.insert({key, steps});
		return key;
	} else {
		if (steps < iter3->second || iter3->second == -1) {
			iter3->second = steps;
			return key;
		} else {
			return key;
			//return 1;
		}
	}
	return 1;
}

