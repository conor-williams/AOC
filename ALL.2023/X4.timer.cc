#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#define INTERVAL 400
void TimerStop(int signum);
void TimerSet(int interval);

void printALREADY(void);

int maxifromright;
int maxifromleft;

#define MAX 2980
#undef _MEMOPT_

int leny = 0;
int lenx = 0;
#define DAY "2023 Day12 Part2 OMG"

void builditX(int MYnumtimes, int mainnumtimes, int *r, char *, int);
int builditUp2(int numtimes, int *r, char *localA, char **outgoing, int);
void mulnumsFiveTimes();
void mulhashcodeFiveTimes();
int dofor(int from, int numtimes, int *r, char *buildup2str, int);
void outerfor(int from, int numtimes);

int r[120];
#define _TRY_ALREADY_
#ifdef _TRY_ALREADY_
	int pophere;
	int alreadyI;
	int yatzeecount;
	int ALREADY[800000][100];
	int ADDTOTABLE(int MYnumtimes, int *r, int *lineofALREADY, char *mylocal, int UPTO);
	int checkALREADYthere (int mainnumtimes, int MYnumtimes, char *mylocal);
#endif

int mainfrom;
int mainnumtimes;
int lenwithdots;
int numsPlusdots[150];
long int matches;
char *hashcode;
int MYpos;
int nums[200]; 
#undef _DEBUG_ 
int LENHASHCODE;
FILE *a;
void TimerStop(int signum) {
    printf("Timer ran out! Stopping timer\n"); fflush(stdout);
//if (numsPlusdots != NULL) {free(numsPlusdots);}
//freelist free
if (hashcode != NULL) {free(hashcode);}
fclose(a);
    exit(10);
}
int main(int argc, char **argv)
{
if (argc == 3) {printf("SETTING TIME TO [%d]\n", atoi(argv[2])); TimerSet(atoi(argv[2]));}

hashcode = (char *)malloc(200);
#ifdef _TRY_ALREADY_
#endif
MYpos = 0;
matches = 0;
mainfrom = 0;
mainnumtimes = 0;
#ifdef _MEMOPT_
	freelist = (char **)malloc  (MAX *sizeof(char *));
	if (freelist == NULL) {printf("ERROR NO MEM\n"); exit(0);}
	freelistpoint = 0;
#endif
	//numsPlusdots = (int *)malloc(sizeof(int) * 200);
        printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
        a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

char numsS[300];
while(1) {
//printf("---------NEXT----------\n");
#ifdef _TRY_ALREADY_
	alreadyI = 0;
	pophere = 0;
#endif
        fgets(line1, 999, a);
        if (feof(a)) break;
	leny++;       
#ifdef _DEBUG_
	printf("LINE: %s", line1); fflush(stdout);
#endif
	sscanf(line1, "%s %s\n", hashcode, numsS);
#ifdef _DEBUG_
	printf("hashcode: %s -- numsS: %s\n", hashcode, numsS);
#endif
{
	MYpos = 0;
	char *token = strtok(numsS, ",");
	while (token != NULL) {
	 	nums[MYpos] = atoi(token);
		MYpos++;
		token = strtok(NULL, ",");
	}	
}
#ifdef _DEBUG_ 
	{ printf("nums are: "); for (int i = 0; i < MYpos; i++) { printf("%d |", nums[i]); } printf("\n"); fflush(stdout); }
	
#endif
{
	mulhashcodeFiveTimes();
}

{
	mulnumsFiveTimes();
}
fflush(stdout);
#ifdef _DEBUG_ 
printf("----------------\n");
#endif
	
	lenwithdots = (MYpos*2) + 1;;
	for (int i = 0; i < lenwithdots+1; i++) {numsPlusdots[i] = 0;}

//printf("lenwithdots:%d pos: %d\n",lenwithdots, MYpos);
	for (int i = 0; i < MYpos; i++) {
		if (i == 0) { numsPlusdots[i*2] = 0;}
		else { numsPlusdots[i*2] = 1;}
		numsPlusdots[i*2 + 1] = nums[i];	
	}
	numsPlusdots[MYpos*2] = 0;
	numsPlusdots[(MYpos*2) + 1] = 0;

	int tot2 = 0;
	for (int i = 0; i < lenwithdots; i++) {
		tot2 += numsPlusdots[i];
	}
	LENHASHCODE = (int)strlen(hashcode);
	
#ifdef _DEBUG_ 
	{ printf("nums are now \n"); for (int i = 0; i < lenwithdots; i++) { printf("%d |", numsPlusdots[i]); fflush(stdout);} }
	
#endif
	
#ifdef _DEBUG_
	printf("hashcode: |%s| len %d tot2: %d numdots left over %d\n", hashcode, 
		LENHASHCODE, tot2, (int)LENHASHCODE - tot2); fflush(stdout);
#endif
	int distrib = LENHASHCODE - tot2;
	int mynumdots = MYpos+1;

	//long int prematches = matches;
	matches = 0;
#ifdef _TRY_ALREADY_
	yatzeecount = 0;
#endif
	outerfor(distrib, mynumdots);
	printf(" THIS: [%ld]\n", matches);
#ifdef _TRY_ALREADY_
	printf("pophere: [%d]\n", pophere);
	printf("after YATZEE: [%d]\n", yatzeecount);
#endif
///	printf(" CURRENTLY: [%ld] THIS: [%ld]\n", matches, matches - prematches);
//	printf(" THIS: [%ld]\n", matches - prematches);
///	printf("ADDED mymatch %ld\n", matches - prematches);
}
//free(numsPlusdots);

#ifdef _MEMOPT_
	free(freelist);
#endif
fclose(a);
free(hashcode);
//printf("*********matches: %ld\n", matches);
}
void mulnumsFiveTimes()
{
	for (int i = 0; i < MYpos; i++) {
		nums[i+MYpos] = nums[i];
		nums[i+(2*MYpos)] = nums[i];
		nums[i+(3*MYpos)] = nums[i];
		nums[i+(4*MYpos)] = nums[i];
	}
	MYpos = 5*MYpos;
#ifdef _DEBUG_
	printf("pos a kind of totnums: %d\n", MYpos);
#endif
}

void mulhashcodeFiveTimes() {
	strcat(hashcode, "?");
	
	char newhashcode[1000];
	strcpy(newhashcode, hashcode);
	char tmphashcode[1000];
	strcpy(tmphashcode, hashcode); 

	strcat(newhashcode, tmphashcode);
	strcat(newhashcode, tmphashcode);
	strcat(newhashcode, tmphashcode);
	strcat(newhashcode, tmphashcode);
	strcpy(hashcode, newhashcode);
	hashcode[strlen(hashcode) - 1] ='\0';
//	printf("hashcode now %s strlen: %d\n", hashcode, LENHASHCODE); 
//	printf("hashcode [%s] ", hashcode);
}
void outerfor(int from, int numtimes)
{
//printf("IN OUTER FOR....\n");
	if (from == 0){matches++; return; /*printf(" [%d] matches CURENTLY: [%ld] - THIS: [%d]\n", leny, matches, 1); return;*/}
//	printf(" [%d] matches CURRENTLY: [%ld] - THIS: [%ld]\n", leny, matches, matches - prematches);
	for (int i = 0; i <= numtimes; i++) {
		r[i] = 0;
	}
	mainnumtimes = numtimes;
	mainfrom = from;

		maxifromright = -1;
		for (long unsigned int i = LENHASHCODE - 1; i > 0; i--) {
			if (hashcode[i] == '#') { 
				maxifromright = LENHASHCODE - 1 -i;	
				break;
			}
		}
		maxifromleft = 1000;
		for (int i = 0; i < LENHASHCODE; i++) {
			if (hashcode[i] == '#') {
				maxifromleft = i;
				break;
		  	}
		}
#ifdef _DEBUG_
	printf("ONCE... max: %d %d\n", maxifromleft, maxifromright); //getchar();
#endif
	char *localA = (char *)malloc(150);
	char *origlA = localA;
	strcpy(localA, "");
	dofor(mainfrom, numtimes, r, localA, 0);

	free(origlA);
#ifdef _MEMOPT_
	//dofree();
#endif
	//free(freelist);
}

int dofor(int from, int numtimes, int *r, char *buildup2str, int startsub)
{
	numtimes--;
	if (numtimes == 0) {
		r[0] = mainfrom; for (int i = mainnumtimes -1; i >= 1; i--) {r[0] -= r[i];}
#ifdef _DEBUG_
         	printf("X"); for (int i = mainnumtimes -1; i >= 0; i--) { printf("|%d|", r[i]); } printf("\n");
#endif
#ifdef _DEBUG_
		printf("r[0] is %d\n", r[0]); if (r[0] != 0) {/*getchar();*/}
#endif
		if (r[0] <= maxifromright) {
			builditX(numtimes, mainnumtimes, r, buildup2str, startsub);
		}
		return -1;
	}

	for (int s = from; s >= 0; s--) {
		//left most??
		if (numtimes+1 == mainnumtimes) {
			if (s > maxifromleft) {
			} else {	
#ifdef _DEBUG_
				printf("outer loop: doing s:%d\n", s);
#endif
				r[numtimes] = s;
				int mysubret;
				char *tmpPtr;
				mysubret = builditUp2(numtimes, r, buildup2str, &tmpPtr, startsub);
				if (mysubret == -1) {
				} else if (mysubret == -2) {
					free(tmpPtr);
				} else {
					char localstr[200];
					strcpy(localstr, tmpPtr);
					dofor(from - s, numtimes, r, localstr, mysubret);
					free(tmpPtr);
				}
			}
		} else {
			r[numtimes] = s;
			
			int mysubret;
			char *tmpPtr;
			mysubret = builditUp2(numtimes, r, buildup2str, (char **)&tmpPtr, startsub);
			if (mysubret == -1) {
			} else if (mysubret == -2) {
				free(tmpPtr);
			} else {
				char localstr[200];
				strcpy(localstr, tmpPtr);
				dofor(from - s, numtimes, r, localstr, mysubret);
				free(tmpPtr);
			}
		}
	}
	return -1;
}
void printALREADY(void)
{
#ifdef _TRY_ALREADY_
        for (int j = 0; j < alreadyI; j++) {
//		if (j == 0) {/printf("aLREADY elems (cols:mainnumtimes: %d):\n", mainnumtimes);}
		for (int k = 0; k < (mainnumtimes*2)-1; k++)
		{
			printf("%d ", ALREADY[j][k]);
		}
		printf("\n");

		for (int k = 0; k < (mainnumtimes*2)-1; k++)
		{
			if (k % 2 == 0) {
				for (int z = 0; z < ALREADY[j][k]; z++) {
					printf(".");
				}
			} else {
				for (int z = 0; z < ALREADY[j][k]; z++) {
					printf("#");
				}
			}
		}
		printf("\n");
	}
	fflush(stdout);
	//getchar();
#endif
}
int builditUp2(int MYnumtimes, int *r, char *localA, char **outgoing, int startsub)
{
	int sub = startsub;
	char mylocal[200]; strcpy(mylocal, localA);

	int start = mainnumtimes - MYnumtimes -1;
	for (int i = start; i < mainnumtimes - MYnumtimes; i++) {
		for (int j = 0; j < r[mainnumtimes-1-i] + numsPlusdots[2*i]; j++) {
			
			mylocal[(sub)++] = '.';
		}
		for (int j = 0; j < numsPlusdots[(2*i)+1]; j++) {
			mylocal[(sub)++] = '#';
		}
	} mylocal[sub] = '\0';


	for (int i = startsub; i < (sub); i++) {
		if ((hashcode[i] == '.' && (mylocal)[i] == '#' ) || (hashcode[i] == '#' && (mylocal)[i] == '.' )) {
			
#ifdef _DEBUG_
			printf("throwing away hc [%s] V [%s] mylocal\n",  hashcode, mylocal);
#endif
			 return -1; } }
#ifdef _DEBUG_
	printf("OK::: checked... %s LEVEL %d\n", mylocal, MYnumtimes); 
#endif
			char *outgoingFromHere = (char*)malloc(140);
			if (outgoingFromHere == NULL) {printf("NO MEM QUITTING\n"); fflush(stdout); exit(0);}
#ifdef _MEMOPT_
				if (freelistpoint > MAX-10000) {printf("LENY: %d  WARNING WARNING ********************************** WARNING QUITTING.BIG CHAR START.ONE.\n", leny); dofree(); exit(0);}
				freelist[freelistpoint++] = outgoingFromHere; 
#endif

	strcpy(outgoingFromHere, mylocal);
	*outgoing = outgoingFromHere;
#ifdef _TRY_ALREADY_
{
	if (alreadyI > 0) {
		if (checkALREADYthere(mainnumtimes, MYnumtimes, mylocal) > 0) { 
			//printf("%s already checked.... mod of matches\n", mylocal);
			return -2;
		} else {
			//printf("%s good match so far but not already in ALREADY...\n", mylocal);
		}
	}
}
#endif
	return sub;
}

int ADDTOTABLE(int MYnumtimes, int *r, int *lineofALREADY, char *myLocal, int UPTO) 
{
#ifdef _TRY_ALREADY_
//void dupcheck()
{
	int dupscount=0; int myLEVEL = mainnumtimes - MYnumtimes -1;
	for (int i = 0; i < alreadyI; i++) {
		char tmpbuildstr[160]; int sub13 = 0;
		for (int j = 0; j < 2*(myLEVEL+1) ; j++) {
			if (j % 2 == 0) {
				for (int q = 0; q < ALREADY[i][j]; q++) {
					tmpbuildstr[sub13++] = '.';
				}
			} else if (j % 2 == 1) {
				for (int q = 0; q < ALREADY[i][j]; q++) {
					tmpbuildstr[sub13++]  = '#';
				}
			}
		} 
		tmpbuildstr[sub13] = '\0';
		if (strcmp(myLocal, tmpbuildstr) == 0) {
			printf("ERROR - DUP FOUND - getchar \n[%s] V \n[%s]\n", myLocal, tmpbuildstr); fflush(stdout); 
			//printALREADY();
			dupscount++;
		} else {
			//printf("DEFO NOT THERE SO FAR...\n"); 
		}	
	}
	if (dupscount == 0) {
	} else if (dupscount > 1) {
		printf("if dupscount > 1 [%d]\n", dupscount); fflush(stdout); return 22;
	} else if (dupscount == 1)  {
		return 22; 
	}
	
}
	//checkfordups();

	for (int z = 0; z < (2*mainnumtimes) - 1; z++) {
		ALREADY[alreadyI][z] = lineofALREADY[z];

	}

	//printf("%d %d %d\n", lineofALREADY[29], lineofALREADY[30], lineofALREADY[31]);

int myLEVEL = mainnumtimes - MYnumtimes -1;
#ifdef _DEBUG_
	printf("mainnumtimes %d\n", mainnumtimes);
	printf("MYnumtimes %d\n", MYnumtimes); 
	printf("myLEVEL %d\n", myLEVEL); 
#endif

	for (int z = ((myLEVEL+1)*2)-1; z < (2*mainnumtimes); z++) {
		//printf("z is %d\n", z); 
#ifdef _DEBUG_
printf("in already...\n"); printf("%d %d\n", lineofALREADY[z], z); getchar();
#endif
		ALREADY[alreadyI][z] = lineofALREADY[z];
	}

	for (int i = 0; i < 2*(myLEVEL)+1; i++) {
		//printf("i is %d\n", i);
	     if (i % 2 == 0) {
		for (int j = 0; j < r[mainnumtimes - (i/2+1)] + numsPlusdots[i]; j++) {
			ALREADY[alreadyI][i] = 0;
		}
	    } else {
		for (int j = 0; j < numsPlusdots[i]; j++) {
			ALREADY[alreadyI][i] = 0;
		}
	    }
	}
	for (int i = 0; i < 2*(myLEVEL+1)+1; i++) {
	     if (i % 2 == 0) {
		for (int j = 0; j < r[mainnumtimes - (i/2+1)] + numsPlusdots[i]; j++) {
			ALREADY[alreadyI][i]++;
		}
	    } else {
		for (int j = 0; j < numsPlusdots[i]; j++) {
			ALREADY[alreadyI][i]++;
		}
	    }
	}

	//if (found) {printf("ERROR DUPS size: alreadyI: [%d] found in ALREADY [%d] getchar\n", alreadyI, found); }

	/*for (int j = (2*(MYnumtimes)-1)); j < ((mainnumtimes-MYnumtimes)*2)-1; j++) */



	alreadyI++;
	matches++;
	//printf("MYnumtimes [%d] alreadyI [%d] matches: [%ld]\n", MYnumtimes, alreadyI, matches);
	return 0;
#endif
}

int checkALREADYthere (int mainnumtimes, int MYnumtimes, char *mylocal) {
#ifdef _TRY_ALREADY_
	
int myLEVEL = mainnumtimes - MYnumtimes - 1;
	int numdotstotheleftCurrent2 = 0;
	int numhashestotheleftCurrent2 = 0;
for (int i = 0; i < (int)strlen(mylocal); i++) {if (mylocal[i] == '.') { numdotstotheleftCurrent2++;}}
for (int i = 0; i < (int)strlen(mylocal); i++) {if (mylocal[i] == '#') { numhashestotheleftCurrent2++;}}
//printf("[%d] [%d]\n", numdotstotheleftCurrent2, numhashestotheleftCurrent2);

	for (int i = 0; i < alreadyI; i++) {
		char tmpbuildstr[160]; int sub13 = 0;
		for (int j = 0; j < 2*(myLEVEL+1) ; j++) {
			if (j % 2 == 0) {
				for (int q = 0; q < ALREADY[i][j]; q++) {
					tmpbuildstr[sub13++] = '.';
				}
			} else if (j % 2 == 1) {
				for (int q = 0; q < ALREADY[i][j]; q++) {
					tmpbuildstr[sub13++]  = '#';
				}
			}
		} 
		tmpbuildstr[sub13] = '\0';
		if (strcmp(mylocal, tmpbuildstr) == 0) {
			//printf("ITS EXACTLY there -- great\n"); fflush(stdout); 
			// the other processing is to speed up searches...
			// its exactly there
			//printf("its exactly there -- great\n"); fflush(stdout);
			return 10;
		} else {
			//printf("DEFO NOT THERE SO FAR...\n"); 
		}	
#ifdef _DEBUG_
		printf("CONOR\n%s V \n%s\n", mylocal, tmpbuildstr);
#endif
	}
/*
	for (int i =0; i < mainnumtimes - myLEVEL ; i++) {
		for (int j = 0; j < r[mainnumtimes-1-i] + numsPlusdots[2*i]; j++) {
			numdotstotheleftCurrent2++;
		}
		for (int j = 0; j < numsPlusdots[(2*i)+1]; j++) {
			numhashestotheleftCurrent2++;
		}
	}
*/

	int numdotstotheleftInTable = 0;
	int numhashestotheleftInTable = 0;
	int tmpcount = 0;
	int tmpalreadyI = alreadyI;
	for (int i = 0; i < tmpalreadyI; i++) {
		numdotstotheleftInTable = 0;
		numhashestotheleftInTable = 0;

		char tmpbuildstr[200]; int sub12 = 0;
		for (int j = 0; j < 2*(myLEVEL+1) ; j++) {
			if (j % 2 == 0) {
				for (int q = 0; q < ALREADY[i][j]; q++) {
					tmpbuildstr[sub12++] = '.';
				}
			} else if (j % 2 == 1) {
				for (int q = 0; q < ALREADY[i][j]; q++) {
					tmpbuildstr[sub12++]  = '#';
				}
			}
		} 
		tmpbuildstr[sub12] = '\0';
		for (int j = 0; j < 2*(myLEVEL+1) ; j++) {
			if (j % 2 == 0) {
				numdotstotheleftInTable += ALREADY[i][j];
			} else if (j % 2 == 1) {
				numhashestotheleftInTable += ALREADY[i][j];
			}
		} 

#ifdef _DEBUG_
		printf("[%d] %d v %d -- %d v %d\n", tmpalreadyI, numdotstotheleftCurrent2, numdotstotheleftInTable, numhashestotheleftInTable, numhashestotheleftCurrent2); fflush(stdout);
#endif

#ifdef _DEBUG_
		if (numdotstotheleftCurrent2 == numdotstotheleftInTable) {printf("num dots same...\n"); fflush(stdout);}
		if (numhashestotheleftInTable == numhashestotheleftCurrent2) {printf("num hashes same...\n"); fflush(stdout);}
#endif
		if (numdotstotheleftCurrent2 == numdotstotheleftInTable && numhashestotheleftInTable == numhashestotheleftCurrent2) {
			//printf("YATZEEE....\n"); 
			yatzeecount++;
			//printf("yatzeecount is %d\n", yatzeecount);
			if (myLEVEL == 15) {printf("15\n"); fflush(stdout);}
			if (myLEVEL < 15) {
				//printf("strcmp \n%s| v \n%s|\n", mylocal, tmpbuildstr); printf("[%d]\n", strcmp(mylocal, tmpbuildstr));
#ifdef _DEBUG_
#endif
				if (strcmp(mylocal, tmpbuildstr) != 0) {
					if (ADDTOTABLE(MYnumtimes, r, ALREADY[i], mylocal, 0) == 22) {return 0;}
					//printf("here...[%d]", i);
					//if (tmpalreadyI == i+1) {/*printf("yes..");*/ /*just added*/break;} else {/*printf("no....");*/ break;}
					//is it finding itself...
				} else {
					printf("DUPS...\n");
				}
			} 
			tmpcount++;
			//if (tmpcount > 1) {printf("tmpcount is %d\n", tmpcount); 
		}
	}
	return tmpcount;
#endif
	return 0;
}

void builditX(int MYnumtimes, int mainnumtimes, int *r, char *tmpstring, int sub1)
{
	int sub = sub1;
	char mylocal2[300];
	strcpy(mylocal2, tmpstring);

	for (int i = mainnumtimes - 1; i < mainnumtimes; i++) {
		for (int j = 0; j < r[mainnumtimes-1-i] + numsPlusdots[2*i]; j++) {
			mylocal2[(sub)++] = '.';
		}
		for (int j = 0; j < numsPlusdots[(2*i)+1]; j++) {
			mylocal2[(sub)++] = '#';
		}
	} mylocal2[sub] = '\0';

	for (int i = sub1; i < sub; i++) {
		if ((hashcode[i] == '.' && (mylocal2)[i] == '#' ) || (hashcode[i] == '#' && (mylocal2)[i] == '.' )) {
			
#ifdef _DEBUG_
			printf("throwing away hc [%s] V [%s] mylocal2\n",  hashcode, mylocal2);
#endif
			 return; } }
#ifdef _DEBUG_
	printf("OK::: checked... %s\n", mylocal2); 
#endif

#ifdef _TRY_ALREADY_
	//POPULATE PERFECT
pophere++;

        for (int i = 0; i < (mainnumtimes*2)-1; i++) {
		if (i %2 == 0) {
			ALREADY[alreadyI][i] += r[(mainnumtimes - 1) -i/2];
		}
		ALREADY[alreadyI][i] += numsPlusdots[i];
	}
	alreadyI++;
#endif

	matches++;
	if ( (int)strlen(mylocal2) != (int)LENHASHCODE) {printf("%d V %d builditX Lengths ERROR....", (int)strlen(mylocal2), (int)LENHASHCODE); getchar();}
#ifdef _DEBUG_
#endif
}
void TimerSet(int interval) {
    printf("starting timer\n");
    struct itimerval it_val;

    it_val.it_value.tv_sec = interval;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;

    if (signal(SIGALRM, TimerStop) == SIG_ERR) {
        perror("Unable to catch SIGALRM");
        exit(1);
    }
    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
        perror("error calling setitimer()");
        exit(1);
    }
}


