#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <functional>
#include <deque>

using namespace std;
FILE *a;
#define LINE 1000
#define getchar()
int maxmaxGeode = 0;
int maxGeode = 0;
char maxCombo[100];
int currentN = 0;
long long qualTot = 0;
int maxPosition = 0;
char CUR[100];
void sigfunc(int a) { printf("CUR[%s] maxGeode: [%d] currentN: %d (%d)maxCombo: [%s] maxmaxGeode: [[%d]](ans) qualTot [%lld]\n", CUR, maxGeode, currentN, currentN+1, maxCombo, maxmaxGeode, qualTot); }

//f(char*s){for(s+=8;(*s+=*s-58?1:8)>80;*s--=48);}

#define ORE 0
#define CLAY 1
#define OBSIDIAN 2
#define GEODE 3

//#define TWELVELEN 11

set <string> refset[20];
deque<string> combos[20];

struct blue_s {
	int num;
	int costOreRobot[5];
	int costClayRobot[5];
	int costObsidianRobot[5];
	int costGeodeRobot[5];
};

struct blue_s blue[100];
inline void functoa(int n, char s[]);
void reverseit(char arr[]);
inline void botit(char strit[], int n, int END);
void queueit(int xyz);

char line1[LINE];
char line2[LINE];
//Blueprint 1: Each ore robot costs 2 ore. Each clay robot costs 2 ore. Each obsidian robot costs 2 ore and 20 clay. Each geode robot costs 2 ore and 14 obsidian.
int main(int argc, char **argv)
{

        signal(SIGTSTP, &sigfunc);
	memset(blue, '0', sizeof(blue));
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day 18 - part 1\n"); fflush(stdout);
int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	int num = 0;
	int ret = sscanf(line1, "Blueprint %d: Each ore robot costs %d ore. Each clay robot" \
		" costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot" \
		" costs %d ore and %d obsidian.",
			&num,
			&blue[leny].costOreRobot[ORE],
			&blue[leny].costClayRobot[ORE],
			&blue[leny].costObsidianRobot[ORE],
			&blue[leny].costObsidianRobot[CLAY],
			&blue[leny].costGeodeRobot[ORE],
			&blue[leny].costGeodeRobot[OBSIDIAN]);
	assert(ret == 7);
	blue[leny].num = num-1;
	sprintf(line2, "Blueprint %d: Each ore robot costs %d ore. Each clay robot" \
		" costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot" \
		" costs %d ore and %d obsidian.",
			blue[leny].num+1,
			blue[leny].costOreRobot[ORE],
			blue[leny].costClayRobot[ORE],
			blue[leny].costObsidianRobot[ORE],
			blue[leny].costObsidianRobot[CLAY],
			blue[leny].costGeodeRobot[ORE],
			blue[leny].costGeodeRobot[OBSIDIAN]);
	assert(strcmp(line1, line2) == 0);
	leny++;
}
fclose(a);
if (strcmp(argv[1], "ex1.txt") == 0) {assert(leny==2);}
if (strcmp(argv[1], "i1.txt") == 0) {assert(leny==30);}
	
	for (int zz = 2; zz <= 12; zz++) {
		queueit(zz);
	}

	int MAINSTR = 10;
	if (argc == 3) {MAINSTR = atoi(argv[2]);}
	printf("Using initial MAINSTR (length)(%d)\n", MAINSTR);
	for (int n = 0; n < leny; n++) {
		currentN = n; maxGeode = 0; strcpy(maxCombo, "");
		
		for (auto it2 = combos[MAINSTR].begin(); it2 != combos[MAINSTR].end(); it2++) {
			//strcpy(CUR, (char*)(*it2).c_str());
			botit((char*)(*it2).c_str(), n, MAINSTR);
		}
		qualTot += (n+1)*maxGeode;
		printf("maxes (n:%d): (%d) maxCombo [%s] qualTot: %lld\n", n, maxGeode, maxCombo, qualTot);
	}
	printf("**ans is[[[qualTot:[[ %lld ]]]]] (maxmaxGeode:%d) maxPosition:: %d\n", qualTot, maxmaxGeode, maxPosition);

}

void queueit(int xyz) {
	printf("in queueit %d --- ", xyz); fflush(stdout);
	for (unsigned long long i = 0; i < pow(4, xyz); i++) {
		char var_s[30];
		functoa(i, var_s);

		char v2[60]; 
		char s1[10];
		sprintf(s1, "0%ds", xyz);
		char s2[12] = "%";
		strcat(s2, s1);
		sprintf(v2, s2, var_s);
		if (refset[xyz].find(v2) == refset[xyz].end()) {
			combos[xyz].push_back(v2);
			refset[xyz].insert(v2);
		}
		if ((int)strlen(var_s) != xyz) {
			reverseit(v2);
			if (refset[xyz].find(v2) == refset[xyz].end()) {
				combos[xyz].push_back(v2);
				refset[xyz].insert(v2);
			}
		}
	}
	printf(" -- leaving queueit %d\n", (int)combos[xyz].size()); fflush(stdout);
}
const char digits[] = "01234";
int base = 4;
inline void functoa(int n, char s[]) {
	int i = 0;
	do {
		s[i++] = digits[n % base];
	} while ((n /= base) > 0);
	s[i] = '\0';
}

void reverseit(char arr[])
{
    int len= strlen(arr) - 1;

    for(int i=0; i<=len/2; i++)
    {
        char temp=arr[i];
        arr[i]=arr[len-i];
        arr[len-i]=temp;
    }
}

inline void botit(char str[], int n, int END) {
	char strit[30];
	strcpy(strit, str);
	//printf("strit: %s n %d \n", strit, n);
	int have[5];
	//Robots
	have[ORE] = 1;	
	have[CLAY] = 0;
	have[OBSIDIAN] = 0;
	have[GEODE] = 0;

	// Produce
	int produce[5] = {0};
	int position = 0;
	char toBe = strit[position];
	int havePOT[5] = {0};
	int minute;
	for (minute = 1; minute <= 24; minute++) {
		if (position < END && minute < 24) {
			switch(toBe) {
				case '0': //ORE
					if (produce[ORE] >= blue[n].costOreRobot[ORE]) {
						havePOT[ORE]++;
						produce[ORE] -= blue[n].costOreRobot[ORE];
						if (position+1 < END) {
							toBe = strit[++position];
						} else {
							position++;
						}
					} 
					break;
				case '1': //CLAY
					if (produce[ORE] >= blue[n].costClayRobot[ORE]) {
						havePOT[CLAY]++;
						produce[ORE] -= blue[n].costClayRobot[ORE];
						if (position+1 < END) {
							toBe = strit[++position];
						} else {
							position++;
						}
						//changed = 1;
					} 
					break;
				case '2': //OBSIDIAN
					if (produce[ORE] >= blue[n].costObsidianRobot[ORE] && 
							produce[CLAY] >= blue[n].costObsidianRobot[CLAY]) {
						havePOT[OBSIDIAN]++;
						produce[ORE] -= blue[n].costObsidianRobot[ORE];
						produce[CLAY] -= blue[n].costObsidianRobot[CLAY];
						if (position+1 < END) {
							toBe = strit[++position];
						} else {
							position++;
						}
					} 
					break;
				case '3': //GEODE
					if (produce[ORE] >= blue[n].costGeodeRobot[ORE] && 
							produce[OBSIDIAN] >= blue[n].costGeodeRobot[OBSIDIAN]) {
						havePOT[GEODE]++;
						produce[ORE] -= blue[n].costGeodeRobot[ORE];
						produce[OBSIDIAN] -= blue[n].costGeodeRobot[OBSIDIAN];
						if (position+1 < END) {
							toBe = strit[++position];
						} else {
							position++;
						}
					} 
					break;
			}
		}
		for (int i = 0; i < 4; i++) {//harvest
			produce[i] += have[i]; 
		}
		for (int i = 0; i < 4; i++) {//move the POT over to have
			have[i] += havePOT[i];
			havePOT[i] = 0;
		}
		if (position == END) {
			//if (produce[GEODE] > 5) { printf("end p1 %d -- %s\n", produce[GEODE], strit); }
			break;
		}
	}

	char stritOrig[100];
	strcpy(stritOrig, strit);
	strcpy(strit, "BBB");
	if (produce[GEODE] > maxGeode) {maxGeode = produce[GEODE]; char m2[200]; maxPosition = position; sprintf(m2, "%s %s", stritOrig, strit); strcpy(maxCombo, m2);}	
	int haveOrig[5];
	//Robots
	haveOrig[ORE] = have[ORE];
	haveOrig[CLAY] = have[CLAY];
	haveOrig[OBSIDIAN] = have[OBSIDIAN];
	haveOrig[GEODE] = have[GEODE];

	// Produce
	int produceOrig[5];
	produceOrig[ORE] = produce[ORE];
	produceOrig[CLAY] = produce[CLAY];
	produceOrig[OBSIDIAN] = produce[OBSIDIAN];
	produceOrig[GEODE] = produce[GEODE];
	//minute - 14 ->  23
	int minuteOrig = minute+1;
	deque<string> COM;

	if (       minuteOrig >= 22) {
		END = 2; COM=combos[2];
	} else if (minuteOrig >= 21) {
		END = 3; COM=combos[3];
	} else if (minuteOrig >= 20) {
		END = 4; COM=combos[4];
	} else if (minuteOrig >= 19) {
		END = 5; COM=combos[5];
	} else if (minuteOrig >= 18) {
		END = 6; COM=combos[6];
	} else if (minuteOrig >= 17) {
		END = 7; COM=combos[7];
	} else if (minuteOrig >= 16) {
		END = 8; COM=combos[8];
	} else if (minuteOrig >= 15) {
		END = 9; COM=combos[9];
	} else if (minuteOrig >= 14) {
		END = 10; COM=combos[10];
	} else if (minuteOrig >= 13) {
		END = 11; COM=combos[11];
	} else if (minuteOrig >= 12) {
		//END = 12; COM=combos[12];
		perror("121212\n"); exit(0);
	} else if (minuteOrig >= 11) {
		//END = 13; COM=combos[13];
		perror("131313\n"); exit(0);
	} else {
		perror("OUT"); exit(0);
	}
	for (auto dd = COM.begin(); dd != COM.end(); dd++) { 
		position = 0;
		strcpy(strit, (char*)(*dd).c_str());

		have[ORE] = haveOrig[ORE]; have[CLAY] = haveOrig[CLAY];
		have[OBSIDIAN] = haveOrig[OBSIDIAN]; have[GEODE] = haveOrig[GEODE];
		
		produce[ORE] = produceOrig[ORE]; produce[CLAY] = produceOrig[CLAY];
		produce[OBSIDIAN] = produceOrig[OBSIDIAN]; produce[GEODE] = produceOrig[GEODE];
		memset(havePOT, 0, sizeof(havePOT));
		toBe = strit[position];
		for (minute=minuteOrig; minute <= 24; minute++) {
			if (position < END && minute < 24) {
				switch(toBe) {
					case '0': //ORE
						if (produce[ORE] >= blue[n].costOreRobot[ORE]) {
							havePOT[ORE]++;
							produce[ORE] -= blue[n].costOreRobot[ORE];
							if (position + 1 < END) {
								toBe = strit[++position];
							} else {
								position++;
							}
						} 
						break;
					case '1': //CLAY
						if (produce[ORE] >= blue[n].costClayRobot[ORE]) {
							havePOT[CLAY]++;
							produce[ORE] -= blue[n].costClayRobot[ORE];
							if (position + 1 < END) {
								toBe = strit[++position];
							} else {
								position++;
							}
							//changed = 1;
						} 
						break;
					case '2': //OBSIDIAN
						if (produce[ORE] >= blue[n].costObsidianRobot[ORE] && 
								produce[CLAY] >= blue[n].costObsidianRobot[CLAY]) {
							havePOT[OBSIDIAN]++;
							produce[ORE] -= blue[n].costObsidianRobot[ORE];
							produce[CLAY] -= blue[n].costObsidianRobot[CLAY];
							if (position + 1 < END) {
								toBe = strit[++position];
							} else {
								position++;
							}
						} 
						break;
					case '3': //GEODE
						if (produce[ORE] >= blue[n].costGeodeRobot[ORE] && 
								produce[OBSIDIAN] >= blue[n].costGeodeRobot[OBSIDIAN]) {
							havePOT[GEODE]++;
							produce[ORE] -= blue[n].costGeodeRobot[ORE];
							produce[OBSIDIAN] -= blue[n].costGeodeRobot[OBSIDIAN];
							if (position + 1 < END) {
								toBe = strit[++position];
							} else {
								position++;
							}
						} 
						break;
				}
			}
			for (int i = 0; i < 4; i++) {//harvest
				produce[i] += have[i]; 
			}
			for (int i = 0; i < 4; i++) {//move the POT over to have
				have[i] += havePOT[i];
				havePOT[i] = 0;
			}
		}
		if (produce[GEODE] > maxGeode) {maxGeode = produce[GEODE]; char m2[200]; maxPosition = position; sprintf(m2, "%s %s", stritOrig, strit); strcpy(maxCombo, m2);}	
	}
}
