#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

int lenx, leny;
#define DAY "2016 day16 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 200
#define getchar()
struct di {
	int discNum;
	int totPos;
	int startPos;
};
struct di discs[10];
	
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
	for (int i = 0; i < 10; i++) {
		discs[i].discNum = -1;
		discs[i].totPos = -1;
		discs[i].startPos = -1;
	}
	int max = 0;
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	line1[strlen(line1) -1]='\0'; //the fs
	int discNum, totPos, startPos;
	sscanf(line1, "Disc #%d has %d positions; at time=0, it is at position %d", &discNum, &totPos, &startPos); 
	discs[discNum].discNum = discNum;
	discs[discNum].totPos = totPos;
	discs[discNum].startPos = startPos;
	
	if (discNum > max) {max = discNum;}
	leny++;
	
}
fclose(a);
	int timeAns = 0;
	int t = 0;	
	int fd = dup(1);
	close(1);
	do {
	//for (int t = 0; t < 1000000; t++) {
		int ans[100] = {0};
		for (int p = 1; p <= max; p++) {
			ans[p] = -1;
			//printf("%d %d %d\n", discs[p].discNum, discs[p].totPos, discs[p].startPos);
			int dtime = discs[p].discNum+t;
			ans[p] = (((dtime % discs[p].totPos)) + discs[p].startPos) % discs[p].totPos;
			printf("ans %d t = %d for disc %d\n", ans[p], t, p);  getchar();
		}
		int found = 0;
		for (int p = 1; p <= max; p++) {
			if (ans[p] == 0) {
				found++;
			}
		}
		if (found == leny) {
			//printf("yatzee @ time t... %d\n", t);
			timeAns = t;
			break;
		}
	
		t++;
	} while (1);
		
	
	dup2(fd, 1);
	printf("***timeAns %d END\n", timeAns); fflush(stdout);
} 


/*
Disc #1 has 5 positions; at time=0, it is at position 2.
Disc #2 has 13 positions; at time=0, it is at position 7.
Disc #3 has 17 positions; at time=0, it is at position 10.
Disc #4 has 3 positions; at time=0, it is at position 2.
Disc #5 has 19 positions; at time=0, it is at position 9.
Disc #6 has 7 positions; at time=0, it is at position 0.
*/
