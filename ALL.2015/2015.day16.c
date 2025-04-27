#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2015 day16 part1\n"
#undef _DEBUG_
struct sue {
	int children;
	int cats;
	int samoyeds;
	int pomeranians;
	int akitas;
	int vizslas;
	int goldfish;
	int trees;
	int cars;
	int perfumes;
};

struct sue sues[510];
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
       
	struct sue real1;
	real1.children = 3;
	real1.cats = 7;
	real1.samoyeds = 2;
	real1.pomeranians = 3;
	real1.akitas = 0;
	real1.vizslas = 0;
	real1.goldfish = 5;
	real1.trees = 3;
	real1.cars = 2;
	real1.perfumes = 1;
        char line1[1000];
/*
Sue 1: goldfish: 9, cars: 0, samoyeds: 9
Sue 2: perfumes: 5, trees: 8, goldfish: 8
*/
	for (int i = 0; i < 500; i++) {
		sues[i].children = -1;
		sues[i].cats = -1;
		sues[i].samoyeds = -1;
		sues[i].pomeranians = -1;
		sues[i].akitas = -1;
		sues[i].vizslas = -1;
		sues[i].goldfish = -1;
		sues[i].trees = -1;
		sues[i].cars = -1;
		sues[i].perfumes = -1;
	}
while(1) {
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	char *sue1 = strtok(line1, ":"); 
	int sueNum;
	sscanf(sue1, "Sue %d", &sueNum);
	//printf("sue %d\n", sueNum);
	sue1 = strtok(NULL, "\0"); 
	//printf("sue1 is %s\n", sue1); getchar();
	char *after = strtok(sue1, ",\0");
	//printf("after is %s\n", after); getchar();
	do {
		char comod[25]; int amt;
		sscanf(after, "%s %d", comod, &amt);
		//printf("after: %s::: %d\n", comod, amt); getchar();
		comod[strlen(comod) - 1] = '\0';
		if (strcmp(comod, "children") == 0) {
			sues[sueNum].children = amt;
		} else if (strcmp(comod, "cats") == 0) {
			sues[sueNum].cats = amt;
		} else if (strcmp(comod, "samoyeds") == 0) {
			sues[sueNum].samoyeds = amt;
		} else if (strcmp(comod, "pomeranians") == 0) {
			sues[sueNum].pomeranians = amt;
		} else if (strcmp(comod, "akitas") == 0) {
			sues[sueNum].akitas = amt;
		} else if (strcmp(comod, "vizslas") == 0) {
			sues[sueNum].vizslas = amt;
		} else if (strcmp(comod, "goldfish") == 0) {
			sues[sueNum].goldfish = amt;
		} else if (strcmp(comod, "trees") == 0) {
			sues[sueNum].trees = amt;
		} else if (strcmp(comod, "cars") == 0) {
			sues[sueNum].cars = amt;
		} else if (strcmp(comod, "perfumes") == 0) {
			sues[sueNum].perfumes = amt;
		} else {printf("ERROR %s", comod); exit(0);}
	} while ((after = strtok(NULL, ",\0")) != NULL);
	
}
fclose(a);
	for (int i = 1; i < 500; i++) {
		int found = 0;
		if (real1.children == sues[i].children || sues[i].children == -1) { } else {found = 1; continue;}
		if (real1.cats == sues[i].cats || sues[i].cats == -1) { } else {found = 1; continue;}
		if (real1.samoyeds == sues[i].samoyeds || sues[i].samoyeds == -1) { } else {found = 1; continue;}
		if (real1.pomeranians == sues[i].pomeranians || sues[i].pomeranians == -1) { } else {found = 1; continue;}
		if (real1.akitas == sues[i].akitas || sues[i].akitas == -1) { } else {found = 1; continue;}
		if (real1.vizslas == sues[i].vizslas || sues[i].vizslas == -1) { } else {found = 1; continue;}
		if (real1.goldfish == sues[i].goldfish || sues[i].goldfish == -1) { } else {found = 1; continue;}
		if (real1.trees == sues[i].trees || sues[i].trees == -1) { } else {found = 1; continue;}
		if (real1.cars == sues[i].cars || sues[i].cars == -1) { } else {found = 1; continue;}
		if (real1.perfumes == sues[i].perfumes || sues[i].perfumes == -1) { } else {found = 1; continue;}
		printf("**possible Sue is %d (%d)\n", i, found);
		fflush(stdout); dup2(fd, 1);
		printf("**ans %d\n", i);
	}
		
}
