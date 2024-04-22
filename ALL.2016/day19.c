#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

int lenx, leny;
#define DAY "2016 day19 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 20
#define getchar()

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
	int elfP = -1;
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	int presents[3020000];
	for (int i = 0; i < 3020000; i++) {
		presents[i] = 1;
	}
	int endElf = atoi(line1);
	printf("endElf is [%d]\n", endElf);
	int fd = dup(1);
	close(1);
	do {
		for (int i = 1; i <= endElf; i++) {
			if (presents[i] == 0) {
				printf("elf %d has no presents and is skipped\n", i); fflush(stdout); getchar();
				continue;
			}
			int from;
			if (i == endElf) {from = 1;} else {from = i+1;}
			while (presents[from] == 0) {
				from++;
				if (from == endElf+1) {from = 1;}
				if (from == i) {break;}
			}
			printf("elf %d takes elf %d present\n", i, from); fflush(stdout); getchar();
			if (presents[from] > 0) {
				presents[i] += presents[from];
				presents[from] = 0;
			}
		}
		{
			int found = 0; elfP = -1;
			for (int e = 1; e <= endElf; e++) {
				if (presents[e] == 0) {
					found++;
				} else {
					elfP = e;
				}
			}
			if (found == endElf -1) {
				printf("**elfP is %d\n", elfP);
				goto end;
			} else {
				printf("no...");
			}
		}
	} while (1);
end:
	dup2(fd,1);
	printf("**elfP is %d\n", elfP);
	leny++;
}
fclose(a);
	printf("***tot %ld END\n", tot); fflush(stdout);
} 
