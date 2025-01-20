#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2016 day9 part2\n"
#define _DEBUG_
unsigned long long tot;
#define SIZE 12000

struct fs {
	int f;
	int s;
	int newI;
};

struct fs bracket(int i);
char line1[SIZE];
unsigned long long loop(int from, int to);
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
       
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	unsigned long long newLinePos = 0;
	newLinePos = loop(0, (int)strlen(line1));
	printf("deCOMP len %llu\n", newLinePos);
	tot += newLinePos;

}
fclose(a);
	printf("***tot %llu END\n", tot); fflush(stdout);
} 
int ind = 0;
unsigned long long loop(int from, int to) {
ind++;
	unsigned long long tot1 = 0;
	unsigned long long totfromloop = 0;
	for (int i = from; i < to && i < (int)strlen(line1); i++) {

	if (i % 200 == 0) {printf(" %d ", i);}
#ifdef _DEBUG_
#endif
		if (line1[i] == '\(') {
			struct fs FS; int mul = 1;
			while (line1[i] == '\(') {
				totfromloop = 0;
				FS = bracket(i);
				mul = FS.s;
				i = FS.newI;
#ifdef _DEBUG_
	for (int q = 0; q < ind; q++) {printf("	");} printf("LOOP: (%d * %d) (i->i+i+FS.f) (%d %d)\n", FS.f, FS.s, i, i+FS.f+1); //getchar();
#endif
				if (i > to) {goto end;}
				totfromloop = loop(i, i+FS.f);
#ifdef _DEBUG_
	for (int q = 0; q < ind; q++) {printf("	");} printf("totfromloop %llu\n", totfromloop);
#endif
				tot1 += mul * totfromloop; mul = 1;
				i = i+FS.f;
			}
#ifdef _DEBUG_
	for (int q = 0; q < ind; q++) {printf("	");} printf("tot1 %llu\n", tot1);
#endif
#ifdef _DEBUG_
	for (int q = 0; q < ind; q++) {printf("	");} printf("here2 | %c | %c | %c |\n", line1[i-1], line1[i], line1[i+1]);
	fflush(stdout); //getchar();
#endif
			i--;
		} else if (line1[i] == ')') {
#ifdef _DEBUG_
	for (int q = 0; q < ind; q++) {printf("	");}
#endif
			printf("ERROR\n"); getchar();			
		} else {
#ifdef _DEBUG_
	for (int q = 0; q < ind; q++) {printf("	");} printf("here1 %c%c%c\n", line1[i-1], line1[i], line1[i+1]);
#endif
			fflush(stdout);
#ifdef _DEBUG_
	//getchar();
#endif
			tot1++;
		}
	}
end:
ind--;
	return tot1;
}

struct fs bracket(int i) {
	int fI = 0; int sI = 0;
	char f[SIZE]; char s[SIZE];
	int fPos = 0; int j; 
	for (j = i+1; line1[j] != 'x'; j++) {
		f[fPos] = line1[j]; fPos++;
	}
	f[fPos] = '\0'; fI = atoi(f);
	int k; int sPos = 0;
	for (k = j+1; line1[k] != ')'; k++) {
		s[sPos] = line1[k]; sPos++;
		
	}
	i = k+1;
	s[sPos] = '\0'; sI = atoi(s);
	struct fs blah;
	blah.f = fI;
	blah.s = sI;
	blah.newI = i;
	return blah;
}
