#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char pipes[200][200];
int X, Y;
int chright(char *forwhat);
int chleft(char *forwhat);
int chtop(char *forwhat);
int chbtm(char *forwhat);
void printmaze();
int leny = 0;
int lenx = 0;
int distfun(int y1, int x1, int y2, int x2);
#define DAY "2023 Day12 Part2"
void builditX(int pos, int mainnumtimes, int *r);
void matchit (char *ans, char *hashcode);
char ans[1000];
void mulnumsFiveTimes();
void mulhashcodeFiveTimes();
void dofor(int from, int numtimes, char **buildup2str);
void outerfor(int from, int numtimes, int pos);
int r[1000];
int mainfrom;
int mainnumtimes;
int lenwithdots;
int *numsPlusdots;
long matches;
char hashcode[5000];
int pos;
int nums[500]; 
#undef _DEBUG_ 
int maxifromright, maxifromleft;
int builditUp2(int numtimes, char **localA);
int LENHASHCODE;
int main(int argc, char **argv)
{
pos = 0;
matches = 0;
mainfrom = 0;
mainnumtimes = 0;
        printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);
       
        char line1[1000];
	int linenum = 0;

while(1) {
printf("---------NEXT----------\n");
	pos = 0;
        fgets(line1, 999, a);
        if (feof(a)) break;
#ifdef _DEBUG_
	printf("LINE: %s", line1); fflush(stdout);
#endif
	linenum++;

	char numsS[1000];
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
	numsPlusdots = malloc(sizeof(int) *(lenwithdots+1) * 4);
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
	
{ printf("nums are now \n"); for (int i = 0; i < lenwithdots; i++) { printf("%d |", numsPlusdots[i]); } }
#ifdef _DEBUG_ 
#endif
	
#ifdef _DEBUG_
	printf("hashcode: |%s| len %d tot2: %d numdots left over %d\n", hashcode, 
		LENHASHCODE, tot2, LENHASHCODE - tot2);
#endif
	int distrib = LENHASHCODE - tot2;
	int mynumdots = pos+1;

long prematches = matches;
	outerfor(distrib, mynumdots, pos);
	free(numsPlusdots);
	numsPlusdots = NULL;
	printf("matches currently %ld\n", matches);
printf("mymatch %ld\n", matches - prematches);
}
fclose(a);
printf("*********matches: %ld\n", matches);
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
	printf("pos a kind of totnums: %d\n",pos);
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
	printf("hashcode now %s strlen: %d\n", hashcode, LENHASHCODE); //getchar();
}
void outerfor(int from, int numtimes, int pos)
{
printf("IN OUTER FOR....\n");
	if (from == 0){printf("----1match\n"); matches++; return;}
	for (int i = 0; i <= numtimes; i++) {
		r[i] = 0;
	}
	LENHASHCODE = strlen(hashcode);
	mainnumtimes = numtimes;
	mainfrom = from;

		maxifromright = -1;
		for (int i = LENHASHCODE - 1; i > 0; i--) {
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
//printf("ONCE... max: %d %d\n", maxifromleft, maxifromright); getchar();
	char *localA;/* = malloc(200);*/
	dofor(from, numtimes, &localA);
	//free(localA);
}

void dofor(int from, int numtimes, char **buildup2str)
{
	numtimes--;
	if (numtimes == 0) {
		r[0] = mainfrom; for (int i = mainnumtimes -1; i >= 1; i--) {r[0] -= r[i];}
#ifdef _DEBUG_
         	printf("X"); for (int i = mainnumtimes -1; i >= 0; i--) { printf("|%d|", r[i]); } printf("\n");
#endif
		//printf("r[0] is %d\n", r[0]); if (r[0] != 0) {/*getchar();*/}
		if (r[0] <= maxifromright) {
			builditX(pos, mainnumtimes, r);
			matchit(ans, hashcode);
		}
		return;
	}

	for (int s = from; s >= 0; s--) {
		//left most??
		if (numtimes+1 == mainnumtimes) {
			if (s>maxifromleft) {
				//printf("outer loop: not doing s:%d\n", s);
			} else {
				//printf("outer loop: doing s:%d\n", s);
//build up to...
				r[numtimes] = s;
				char *tmpPtr;
				if (builditUp2(numtimes, &tmpPtr) == 1) {
				} else {	
					/*printf("got back localA: %s\n", *buildup2str); getchar(); */
					dofor(from - s, numtimes, buildup2str);
				}
			}
		} else {
//build up to...
			r[numtimes] = s;
			char *letsC2;/* = malloc(100);*/
			//strcpy(letsC2, *buildup2str);
			if (builditUp2(numtimes, &letsC2) == 1) {} else {
				dofor(from - s, numtimes, &letsC2);
			} /*free(letsC2);	*/
		}
	}
/////////////matchit as u go...
}
int builditUp2(int MYnumtimes, char **localA)
{
	/*for (int i = 0; i < 100; i++){mylocal[i] = '\0';}*/
	int sub = 0;
	char mylocal[200];
	int start = mainnumtimes - MYnumtimes -1;
//printf("start %d\n", start); getchar();
	for (int i = 0; i < mainnumtimes - MYnumtimes; i++) {
		for (int j = 0; j < r[mainnumtimes-1-i] + numsPlusdots[2*i]; j++) {
			mylocal[sub++] = '.';
		}
		for (int j = 0; j < numsPlusdots[(2*i)+1]; j++) {
			mylocal[sub++] = '#';
		}
	}
/*
	for (int i = 0; i < start+1; i++) {
		for (int j = 0; j < r[mainnumtimes-1-i] + numsPlusdots[2*i]; j++) {
			mylocal[sub++] = '.';
		}
		for (int j = 0; j < numsPlusdots[(2*i)+1]; j++) {
			mylocal[sub++] = '#';
		}
	}
*/
	mylocal[sub] = '\0';
//	strcat(*localA, mylocal);
//	strcpy(*localA, mylocal);
//	printf("built: [%s] \n", mylocal);
	for (int i = 0; i < sub; i++) {
		/*if (sub < 10) {printf("sub is %d\n", sub);}*/
		if ((hashcode[i] == '.' && (mylocal)[i] == '#' ) || (hashcode[i] == '#' && (mylocal)[i] == '.' )) {
			/*printf("throwing away hc [%s] V [%s] mylocal\n",  hashcode, mylocal);*/ return 1; } }
//	printf("OK::: checked... %s\n", mylocal);
	return 0;
}

void matchit (char *ans, char *hashcode)
{
	//printf("matching |%s| with |%s|\n", ans, hashcode);
	if ( strlen(ans) != LENHASHCODE) {printf("Lengths ERROR...."); getchar();}

	for (int i = 0; i < strlen(ans); i++) {
		if (ans[i] == hashcode[i]) { /*great...*/
		} else if (hashcode[i] == '?') {
			 if (ans[i] == '#') {
			 } else if (ans[i] == '.') {
			 }
		} else {
			//printf("ans: |%s| not a match\n", ans);
			return;
		}

	}
	matches++;
	return;
}
void builditX(int pos, int mainnumtimes, int *r)
{
	for (int i = 0; i < 600; i++){ans[i] = '\0';}
	int sub = 0;

	for (int i = 0; i < mainnumtimes; i++) {
		for (int j = 0; j < r[mainnumtimes-1-i] + numsPlusdots[2*i]; j++) {
			ans[sub++] = '.';
		}
		for (int j = 0; j < numsPlusdots[(2*i)+1]; j++) {
			ans[sub++] = '#';
		}
	}
#ifdef _DEBUG_
printf("ANS: %s\n", ans);
#endif
	ans[sub] = '\0';
}
