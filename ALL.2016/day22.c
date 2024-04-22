#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2016 day22 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 200

struct fs_s {
	int size;
	int used;
	int avail;
	int percU;
	char name[40];
};
struct fs_s fs[1000];
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
	int numFS;
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	//printf("LINE: %s\n", line1); 
#endif
	if (leny > 1) {
		char size[10], used[10], avail[10], percU[10], name[40];
		int ret = sscanf(line1, "%s %s %s %s %s", name, size, used, avail, percU);
		if (ret != 5 || leny == 992) {
			printf("ERROR %s\n", line1);
		}
		if (used[strlen(used)-1] != 'T') {
			printf("here1\n"); getchar();
		}
		if (avail[strlen(avail)-1] != 'T') {
			printf("here2\n"); getchar();
		}
		size[strlen(size)-1] = '\0';
		used[strlen(used)-1] = '\0';
		avail[strlen(avail)-1] = '\0';
		percU[strlen(percU)-1] = '\0';
		fs[numFS].size = atoi(size);
		fs[numFS].used = atoi(used);
		fs[numFS].avail = atoi(avail);
		fs[numFS].percU = atoi(percU);
		strcpy(fs[numFS].name, name);
		numFS++;
	}
	leny++;
}
fclose(a);


//Filesystem              Size  Used  Avail  Use%
////dev/grid/node-x32-y29   90T   65T    25T   72%
printf("leny is %d\n", leny); getchar();
for (int i = 0; i < numFS; i++) {
	printf("%d: %d %d %d %d\n", i, fs[i].size, fs[i].used, fs[i].avail, fs[i].percU);
	if (i % 900 == 0) {};
}
getchar();
	tot = 0;
	for (int a = 0; a < numFS; a++) {
		if (fs[a].used == 0) {continue;}
		for (int b = 0; b < numFS; b++) {
			if (a == b) {continue;}
			//printf("%d\n", fs[b].used);
			if (strcmp(fs[a].name, fs[b].name) == 0) {continue; }
			if (fs[b].avail >= fs[a].used) {tot++;} 
		}
	}


	printf("***tot %ld END \n", tot); fflush(stdout);
} 
