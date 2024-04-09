#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

FILE *a;
struct pass {
	char ecl[30];
	char pid[30];
	char eyr[30];
	char hcl[30];
	char byr[30];
	char iyr[30];
	char cid[30];
	char hgt[30];
};

struct pass people[500];

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day3\n"); fflush(stdout);
        char line1[1000];
	for (int i = 0; i < 500; i++) {
		people[i].ecl[0] = '\0';
		people[i].pid[0] = '\0';
		people[i].eyr[0] = '\0';
		people[i].hcl[0] = '\0';
		people[i].byr[0] = '\0';
		people[i].iyr[0] = '\0';
		people[i].cid[0] = '\0';
		people[i].hgt[0] = '\0';
	}

int leny = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        //line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	char what[100];
	if (line1[0] != '\n') {
		int j = 0;
		for (int i = 0; i < strlen(line1); i++) {
			if (line1[i] == ' ' || line1[i] == '\n') {
				what[j] = '\0';
				j = 0;
			} else {
				what[j] = line1[i];
				j++;
			}
			if (j==0) {printf("what is [%s]\n", what);}
			if (j==0) {
				char *firstpart = strtok(what, ":");
				char *secondpart = strtok(NULL, ":");

				       if (strcmp(firstpart, "ecl") == 0) {
						strcpy(people[leny].ecl, secondpart);
				} else if (strcmp(firstpart, "pid") == 0) {
						strcpy(people[leny].pid, secondpart);
				} else if (strcmp(firstpart, "eyr") == 0) {
						strcpy(people[leny].eyr, secondpart);
				} else if (strcmp(firstpart, "hcl") == 0) {
						strcpy(people[leny].hcl, secondpart);
				} else if (strcmp(firstpart, "byr") == 0){
						strcpy(people[leny].byr, secondpart);
				} else if (strcmp(firstpart, "iyr") == 0) {
						strcpy(people[leny].iyr, secondpart);
				} else if (strcmp(firstpart, "cid") == 0) {
						strcpy(people[leny].cid, secondpart);
				} else if (strcmp(firstpart, "hgt") == 0) {
						strcpy(people[leny].hgt, secondpart);
				}
				printf("**%s** **%s**\n", firstpart, secondpart);
			}
		}
	} else {
		leny++;
	}
}
if (line1[0] != '\0') {leny++;}
fclose(a);
int tot = 0;
	for (int i = 0; i < leny; i++) {
		if (	people[i].ecl[0] != '\0' &&
			people[i].pid[0] != '\0' &&
			people[i].eyr[0] != '\0' &&
			people[i].hcl[0] != '\0' &&
			people[i].byr[0] != '\0' &&
			people[i].iyr[0] != '\0' &&
			people[i].hgt[0] != '\0') {
				printf("valid %d\n", i);
				tot++;
		}

	}
	printf("tot is  %d of (%d)\n", tot, leny);
}
