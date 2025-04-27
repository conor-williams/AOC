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

#include <unistd.h>

#define getchar()
using namespace std;
FILE *a;
#define LINE 1000
//#define getchar()
int maxmaxGeode = 0;
int maxGeode = 0;
char maxCombo[100];
int currentN = 0;
long long qualTot = 0;
int maxPosition = 0;
char CUR[500];
char CUR1[500];
#define COMBOSLEN 1
//void sigfunc(int a) { printf("CUR[%s] maxGeode: [%d] currentN: %d (%d)maxCombo: [%s] maxmaxGeode: [[%d]](ans) qualTot [%lld]\n", CUR, maxGeode, currentN, currentN+1, maxCombo, maxmaxGeode, qualTot); }
void sigfunc(int a) { printf("CUR[%s] CUR1[%s] maxGeode: [%d] currentN: %d (%d)maxCombo: [%s] maxmaxGeode: [[%d]](ans) qualTot [%lld]\n", CUR, CUR1, maxGeode, currentN, currentN+1, maxCombo, maxmaxGeode, qualTot); }

//f(char*s){for(s+=8;(*s+=*s-58?1:8)>80;*s--=48);}
long long ansOverall;
#define ORE 0
#define CLAY 1
#define OBSIDIAN 2
#define GEODE 3
//int have[5] = {0};
int have[5] = {0};
int produce[5] = {0};
deque<string> COM[24];
int minuteOrig[24] = {0};
int haveOrig[24][5];
int produceOrig[24][5];
int minute;
int havePOT[5] = {0};
//int produce[5] = {0};
void doit(int mO, char * stritIn, int n, int *, int *);

//#define TWELVELEN 11

set <string> refset[24];
deque<string> combos[24];

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
void recur(int pos, int n);

char line1[LINE];
char line2[LINE];
//Blueprint 1: Each ore robot costs 2 ore. Each clay robot costs 2 ore. Each obsidian robot costs 2 ore and 24 clay. Each geode robot costs 2 ore and 14 obsidian.
int main(int argc, char **argv)
{

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	memset(blue, '0', sizeof(blue));
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day 19.1\n"); fflush(stdout);
	printf("	SLOW ~1minute 30 seconds\n");

	fflush(stdout); int fd = dup(1); close(1);
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

	int MAINSTR = 1;
	if (argc == 3) {MAINSTR = atoi(argv[2]);}
	for (int zz = 1; zz <= MAINSTR; zz++) {
		queueit(zz);
	}

	printf("Using initial MAINSTR (length)(%d)\n", MAINSTR);
	//int E = leny >= 3 ? 3 : leny;
	//long long mul = 1;
	for (int i = 0; i < 24; i++) {
		COM[i] = combos[COMBOSLEN];
	}
	for (int n = 0; n < /*E*/leny; n++) {
		currentN = n; maxGeode = 0; strcpy(maxCombo, "");


		for (auto it2 = combos[MAINSTR].begin(); it2 != combos[MAINSTR].end(); it2++) {
			botit((char*)(*it2).c_str(), n, MAINSTR);
		}
		qualTot += (n+1)*maxGeode;
		printf("maxes (n:%d): (%d) maxCombo [%s] qualTot: %lld\n", n, maxGeode, maxCombo, qualTot);
		ansOverall = qualTot;
		//mul *= maxGeode;
	}
	//printf("**ans is[[[qualTot:[[ %lld ]]]]] (maxmaxGeode:%d) maxPosition:: %d\n", qualTot, maxmaxGeode, maxPosition);
	//printf("**ans (mulof3) is %lld\n", mul);


	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", ansOverall);
}

void queueit(int xyz) {
#ifdef _DEBUG_
	printf("in queueit %d --- ", xyz); fflush(stdout);
#endif
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
	sort(combos[xyz].begin(), combos[xyz].end());
#ifdef _DEBUG_
	printf(" -- leaving queueit %d\n", (int)combos[xyz].size()); fflush(stdout);
#endif
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
	char strit[500];
	strcpy(strit, str);

	//robots
	have[ORE] = 1;	
	have[CLAY] = 0;
	have[OBSIDIAN] = 0;
	have[GEODE] = 0;

	//the produce
	memset(produce, 0, sizeof(produce));
	memset(haveOrig, 0, sizeof(haveOrig));
	//Robots
	haveOrig[0][ORE] = have[ORE]; haveOrig[0][CLAY] = have[CLAY];
	haveOrig[0][OBSIDIAN] = have[OBSIDIAN]; haveOrig[0][GEODE] = have[GEODE];

	// Produce
	memset(produceOrig, 0, sizeof(produceOrig));
	produce[ORE] = 0;
	produce[CLAY] = 0;
	produce[OBSIDIAN] = 0;
	produce[GEODE] = 0;
	produceOrig[0][ORE] = produce[ORE]; produceOrig[0][CLAY] = produce[CLAY];
	produceOrig[0][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[0][GEODE] = produce[GEODE];
	//minute - 14 ->  23
#ifdef _DEBUG_
	printf("minute is %d\n", minute);
#endif
	minuteOrig[0] = 0;

	recur(1, n);


}

void recur(int pos, int n) {
	if (pos > 24) {perror("too deep\n"); exit(0);}
	for (auto dd1 = COM[pos].begin(); dd1 != COM[pos].end(); dd1++) {
		doit(minuteOrig[pos-1]+1, (char *) (*dd1).c_str(), n, haveOrig[pos-1], produceOrig[pos-1]);
		if (minute >= 24) {continue;}
		haveOrig[pos][ORE] = have[ORE]; haveOrig[pos][CLAY] = have[CLAY];
		haveOrig[pos][OBSIDIAN] = have[OBSIDIAN]; haveOrig[pos][GEODE] = have[GEODE];
		produceOrig[pos][ORE] = produce[ORE]; produceOrig[pos][CLAY] = produce[CLAY];
		produceOrig[pos][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[pos][GEODE] = produce[GEODE];
		minuteOrig[pos] = minute;
		recur(pos+1, n);
		//if (minute >= 24) {perror("out"); exit(0);}
	}
}

void doit(int minuteOrig, char * stritIn, int n, int haveSav[5], int produceSav[5])
{
	char strit[100];
	strcpy(strit, stritIn);
	have[ORE] = haveSav[ORE]; have[CLAY] = haveSav[CLAY];
	have[OBSIDIAN] = haveSav[OBSIDIAN]; have[GEODE] = haveSav[GEODE];

	produce[ORE] = produceSav[ORE]; produce[CLAY] = produceSav[CLAY];
	produce[OBSIDIAN] = produceSav[OBSIDIAN]; produce[GEODE] = produceSav[GEODE];
	int position = 0;
	char toBe = strit[position];
	int END = COMBOSLEN;

	{
		int haveCheck[5] = {0}, produceCheck[5] = {0}, havePOTCheck[5] = {0};
		haveCheck[ORE] = haveSav[ORE]; haveCheck[CLAY] = haveSav[CLAY];
		haveCheck[OBSIDIAN] = haveSav[OBSIDIAN]; haveCheck[GEODE] = haveSav[GEODE];

		produceCheck[ORE] = produceSav[ORE]; produceCheck[CLAY] = produceSav[CLAY];
		produceCheck[OBSIDIAN] = produceSav[OBSIDIAN]; produceCheck[GEODE] = produceSav[GEODE];

		int positionCheck = position;
		int ENDCheck = 24;

		for (int minuCheck=minuteOrig; minuCheck <= 24; minuCheck++) {
			if (positionCheck < ENDCheck && minuCheck < 24) {
				havePOTCheck[GEODE]++;
				positionCheck++;
			}
			for (int i = 0; i < 4; i++) {//harvest
				produceCheck[i] += haveCheck[i];
			}
			for (int i = 0; i < 4; i++) {//move the POT over to have
				haveCheck[i] += havePOTCheck[i];
				havePOTCheck[i] = 0;
			}
		}
		if (produceCheck[GEODE] <= maxGeode) {minute=25; return;}
	}

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
		if (position == COMBOSLEN) {break;}
	}
	//if (produce[GEODE] == 9) {printf("%s\n", stritIn);}
	if (produce[GEODE] > maxGeode) {maxGeode = produce[GEODE]; /*char m2[240]; maxPosition = position; sprintf(m2, "%s %s", stritOrig, strit); strcpy(maxCombo, m2);*/}
}






































/*
   for (auto dd2 = COM[2].begin(); dd2 != COM[2].end(); dd2++) {
   doit(minuteOrig[1], (char *) ( *dd2).c_str(), n, haveOrig[1], produceOrig[1]); if (minute >= 24) {return;}
   haveOrig[2][ORE] = have[ORE]; haveOrig[2][CLAY] = have[CLAY]; haveOrig[2][OBSIDIAN] = have[OBSIDIAN]; haveOrig[2][GEODE] = have[GEODE];
   produceOrig[2][ORE] = produce[ORE]; produceOrig[2][CLAY] = produce[CLAY]; produceOrig[2][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[2][GEODE] = produce[GEODE];
   minuteOrig[2] = minute;
   for (auto dd3 = COM[3].begin(); dd3 != COM[3].end(); dd3++) {
   doit(minuteOrig[2], (char *) ( *dd3).c_str(), n, haveOrig[2], produceOrig[2]); if (minute >= 24) {return;}
   haveOrig[3][ORE] = have[ORE]; haveOrig[3][CLAY] = have[CLAY]; haveOrig[3][OBSIDIAN] = have[OBSIDIAN]; haveOrig[3][GEODE] = have[GEODE];
   produceOrig[3][ORE] = produce[ORE]; produceOrig[3][CLAY] = produce[CLAY]; produceOrig[3][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[3][GEODE] = produce[GEODE];
   minuteOrig[3] = minute;
   for (auto dd4 = COM[4].begin(); dd4 != COM[4].end(); dd4++) {
   doit(minuteOrig[3], (char *) ( *dd4).c_str(), n, haveOrig[3], produceOrig[3]); if (minute >= 24) {return;}
   haveOrig[4][ORE] = have[ORE]; haveOrig[4][CLAY] = have[CLAY]; haveOrig[4][OBSIDIAN] = have[OBSIDIAN]; haveOrig[4][GEODE] = have[GEODE];
   produceOrig[4][ORE] = produce[ORE]; produceOrig[4][CLAY] = produce[CLAY]; produceOrig[4][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[4][GEODE] = produce[GEODE];
   minuteOrig[4] = minute;
   for (auto dd5 = COM[5].begin(); dd5 != COM[5].end(); dd5++) {
   doit(minuteOrig[4], (char *) ( *dd5).c_str(), n, haveOrig[4], produceOrig[4]); if (minute >= 24) {return;}
   haveOrig[5][ORE] = have[ORE]; haveOrig[5][CLAY] = have[CLAY]; haveOrig[5][OBSIDIAN] = have[OBSIDIAN]; haveOrig[5][GEODE] = have[GEODE]; 
   produceOrig[5][ORE] = produce[ORE]; produceOrig[5][CLAY] = produce[CLAY]; produceOrig[5][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[5][GEODE] = produce[GEODE];
   minuteOrig[5] = minute;
   for (auto dd6 = COM[6].begin(); dd6 != COM[6].end(); dd6++) {
   doit(minuteOrig[5], (char *) ( *dd6).c_str(), n, haveOrig[5], produceOrig[5]); if (minute >= 24) {return;}
   haveOrig[6][ORE] = have[ORE]; haveOrig[6][CLAY] = have[CLAY]; haveOrig[6][OBSIDIAN] = have[OBSIDIAN]; haveOrig[6][GEODE] = have[GEODE];
   produceOrig[6][ORE] = produce[ORE]; produceOrig[6][CLAY] = produce[CLAY]; produceOrig[6][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[6][GEODE] = produce[GEODE];
   minuteOrig[6] = minute;
   for (auto dd7 = COM[7].begin(); dd7 != COM[7].end(); dd7++) {
   doit(minuteOrig[6], (char *) ( *dd7).c_str(), n, haveOrig[6], produceOrig[6]); if (minute >= 24) {return;}
   haveOrig[7][ORE] = have[ORE]; haveOrig[7][CLAY] = have[CLAY]; haveOrig[7][OBSIDIAN] = have[OBSIDIAN]; haveOrig[7][GEODE] = have[GEODE];
   produceOrig[7][ORE] = produce[ORE]; produceOrig[7][CLAY] = produce[CLAY]; produceOrig[7][OBSIDIAN] = produce[OBSIDIAN]; produceOrig[7][GEODE] = produce[GEODE];
   minuteOrig[7] = minute;
   for (auto dd8 = COM[8].begin(); dd8 != COM[8].end(); dd8++) {

   doit(minuteOrig[7], (char *) ( *dd8).c_str(), n, haveOrig[7], produceOrig[7]); if (minute >= 24) {return;}
   if (minute < 24) {perror("SMALL"); exit(0);}
   if (minute >= 24) {perror("out"); exit(0);}
   }
   }
   }
   }
   }
   }
   }
   }
   */
