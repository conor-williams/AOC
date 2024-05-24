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
void TimerStop(int signum);
void TimerSet(int interval);

#define INTERVAL 4

void TimerStop(int signum);
void TimerSet(int interval);


int maxifromright;
int maxifromleft;

#define MAX 29800000
#undef _MEMOPT_

int leny = 0;
int lenx = 0;
#define DAY "2023 Day12 Part2 OMG"

void builditX(int pos, int MYnumtimes, int mainnumtimes, int *r, char *, int);
int builditUp2(int numtimes, int *r, char *localA, char **outgoing, int);
void mulnumsFiveTimes();
void mulhashcodeFiveTimes();
int dofor(int from, int numtimes, int *r, char *buildup2str, int);
void outerfor(int from, int numtimes, int pos);

int r[200];
int mainfrom;
int mainnumtimes;
int lenwithdots;
int *numsPlusdots;
unsigned long long int matches;
char *hashcode;
int pos;
int nums[150]; 
#undef _DEBUG_ 
unsigned long int LENHASHCODE;
char **freelist; unsigned long long freelistpoint;
void dofree(void);
FILE *a;
char FILENAME[100];
void TimerStop(int signum) {
    printf("Timer ran out! Stopping timer\n");
	FILE *f = fopen("out.tim", "a");
	fprintf(f, "Timer ran out! Stopping timer %s\n", FILENAME);
	fclose(f);
if (numsPlusdots != NULL) {free(numsPlusdots);}
//freelist free
if (hashcode != NULL) {free(hashcode);}
fclose(a);
    exit(10);
}
int main(int argc, char **argv)
{
if (argc == 3) {printf("SETTING TIME TO [%d]\n", atoi(argv[2])); TimerSet(atoi(argv[2]));}

hashcode = (char *)malloc(200);

pos = 0;
matches = 0;
mainfrom = 0;
mainnumtimes = 0;
#ifdef _MEMOPT_
	freelist = (char **)malloc  (MAX *sizeof(char *));
	if (freelist == NULL) {printf("ERROR NO MEM\n"); exit(0);}
	freelistpoint = 0;
#endif
	numsPlusdots = (int *)malloc(sizeof(int) * 200 * 4);
        printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
	strcpy(FILENAME, argv[1]);
        a = fopen(argv[1], "r"); 
	FILE *x3 = fopen("out.tim", "a");
	fprintf(x3, "%s\n", argv[1]);
	fclose(x3);
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

while(1) {
//printf("---------NEXT----------\n");
	pos = 0;
        fgets(line1, 999, a);
        if (feof(a)) break;
	leny++;       
#ifdef _DEBUG_
	printf("LINE: %s", line1); fflush(stdout);
#endif
	char numsS[300];
	sscanf(line1, "%s %s\n", hashcode, numsS);
#ifdef _DEBUG_
	printf("hashcode: %s -- numsS: %s\n", hashcode, numsS);
#endif
{
	char *token = strtok(numsS, ",");
	while (token != NULL) {
	 	nums[pos] = atoi(token);
		pos++; token = strtok(NULL, ",");
	}	
}
#ifdef _DEBUG_ 
	{ printf("nums are \n"); for (int i = 0; i < pos; i++) { printf("%d |", nums[i]); } }
#endif

{
	mulhashcodeFiveTimes();
}

{
	mulnumsFiveTimes();
}
#ifdef _DEBUG_ 
{ printf("nums now are:\n"); for (int i = 0; i < pos; i++) { printf("%d |", nums[i]); } }
printf("----------------\n");
#endif
	
	lenwithdots = (pos*2) + 1;;
	for (int i = 0; i < lenwithdots+1; i++) {numsPlusdots[i] = 0;}

	for (int i = 0; i < pos; i++) {
		if (i == 0) { numsPlusdots[i*2] = 0;}
		else { numsPlusdots[i*2] = 1;}
		numsPlusdots[i*2 + 1] = nums[i];	
	}
	numsPlusdots[pos*2] = 0;
	numsPlusdots[(pos*2) + 1] = 0;

	int tot2 = 0;
	for (int i = 0; i < lenwithdots; i++) {
		tot2 += numsPlusdots[i];
	}
	LENHASHCODE = strlen(hashcode);
	
#ifdef _DEBUG_ 
	{ printf("nums are now \n"); for (int i = 0; i < lenwithdots; i++) { printf("%d |", numsPlusdots[i]); } }
#endif
	
/*
#ifdef _DEBUG_
	printf("hashcode: |%s| len %ld tot2: %d numdots left over %ld\n", hashcode, 
		LENHASHCODE, tot2, LENHASHCODE - tot2);
#endif
*/
	int distrib = LENHASHCODE - tot2;
	int mynumdots = pos+1;

	//unsigned long long int prematches = matches;
	matches = 0;
	outerfor(distrib, mynumdots, pos);
	FILE *x2 = fopen("out.tim", "a");
	fprintf(x2, "[%s] THIS: [%llu]\n", argv[1], matches);
	fclose(x2);
	printf(" [%s] THIS: [%lld]\n", argv[1], matches);
///	printf(" CURRENTLY: [%lld] THIS: [%lld]\n", matches, matches - prematches);
//	printf(" THIS: [%lld]\n", matches - prematches);
///	printf("ADDED mymatch %lld\n", matches - prematches);
}
	free(numsPlusdots);
#ifdef _MEMOPT_
	free(freelist);
#endif
fclose(a);
free(hashcode);
//printf("*********matches: %lld\n", matches);
}
void mulnumsFiveTimes()
{
	for (int i = 0; i < pos; i++) {
		nums[i+pos] = nums[i];
		nums[i+(2*pos)] = nums[i];
		nums[i+(3*pos)] = nums[i];
		nums[i+(4*pos)] = nums[i];
	}
	pos = 5*pos;
#ifdef _DEBUG_
	printf("pos a kind of totnums: %d\n",pos);
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
	LENHASHCODE = strlen(hashcode);
//	printf("hashcode now %s strlen: %ld\n", hashcode, LENHASHCODE); //getchar();
	printf("hashcode [%s] ", hashcode);
}
void outerfor(int from, int numtimes, int pos)
{
//printf("IN OUTER FOR....\n");
	if (from == 0){matches++; return; /*printf(" [%d] matches CURENTLY: [%lld] - THIS: [%d]\n", leny, matches, 1); return;*/}
//	printf(" [%d] matches CURRENTLY: [%lld] - THIS: [%lld]\n", leny, matches, matches - prematches);
	for (int i = 0; i <= numtimes; i++) {
		r[i] = 0;
	}
	LENHASHCODE = strlen(hashcode);
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
		for (long unsigned int i = 0; i < LENHASHCODE; i++) {
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

void dofree(void) {
	printf("FREEING-------CHAR STAR---------\n"); fflush(stdout);
	printf("CHAR STAR free %lld\n", freelistpoint);
		for (unsigned long long int i = 0; i < freelistpoint; i++) {fflush(stdout); if (freelist[i] != NULL) {free(freelist[i]);} else {printf("NULL");}}
	
	freelistpoint = 0;
	printf("AFTER freeing-----CHAR STAR-----------\n"); fflush(stdout);
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
			builditX(pos, numtimes, mainnumtimes, r, buildup2str, startsub);
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
				if ((mysubret = builditUp2(numtimes, r, buildup2str, &tmpPtr, startsub)) != -1) {
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
			if ((mysubret = builditUp2(numtimes, r, buildup2str, (char **)&tmpPtr, startsub)) != -1) {
					char localstr[200];
					strcpy(localstr, tmpPtr);
					dofor(from - s, numtimes, r, localstr, mysubret);
					free(tmpPtr);
			}
		}
	}
	return -1;
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
	return sub;
}

void builditX(int pos, int MYnumtimes, int mainnumtimes, int *r, char *tmpstring, int sub1)
{
	int sub = sub1;
	char mylocal2[150];
	strcpy(mylocal2, tmpstring);
//printf("FULL INCOMING %s\n", tmpstring);

	for (int i = mainnumtimes - 1; i < mainnumtimes; i++) {
		for (int j = 0; j < r[mainnumtimes-1-i] + numsPlusdots[2*i]; j++) {
			mylocal2[(sub)++] = '.';
		}
		for (int j = 0; j < numsPlusdots[(2*i)+1]; j++) {
			mylocal2[(sub)++] = '#';
		}
	} mylocal2[sub] = '\0';
//printf("CREATED %s\n", mylocal2); 
	for (int i = sub1; i < sub; i++) {
		if ((hashcode[i] == '.' && (mylocal2)[i] == '#' ) || (hashcode[i] == '#' && (mylocal2)[i] == '.' )) {
			
#ifdef _DEBUG_
			printf("throwing away hc [%s] V [%s] mylocal2\n",  hashcode, mylocal2);
#endif
			 return; } }
#ifdef _DEBUG_
	printf("OK::: checked... %s\n", mylocal2); 
#endif
	matches++;
	if ( strlen(mylocal2) != LENHASHCODE) {printf("%ld V %ld builditX Lengths ERROR....", strlen(mylocal2), LENHASHCODE); getchar();}
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


