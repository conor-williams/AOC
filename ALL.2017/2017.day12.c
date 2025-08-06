#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define SIZE 200
char line1[SIZE];
struct ar_s {
	int num;
	int numnums;
	int nums[10];
};

struct ar_s ar[2000];
struct ar_s arBack[10000];
int check(int num);
int errors[3000];
int errorsPos = 0;
int already[3000];
int alreadyPos = 0;
int groups[2000][2000];
int groupsPos[2000];
int groupPos = 0;
int main(int argc, char **argv)
{
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day12.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
for (int i = 0; i < 10000; i++) {
	arBack[i].numnums = 0;
}
int leny = 0;
int max = 0;
int notfail = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	//printf("line1 %s\n", line1);

	int num; char rest[50];
	sscanf(line1, "%d <-> %[^\0]", &num, rest);
	if (num != leny) {printf("ERR"); exit(0);}
	ar[num].num = num;
	char * first = strtok(rest, ",\0");
	int pos = 0;
	do {
		ar[num].nums[pos] = atoi(first);
		if (atoi(first) > max) {max = atoi(first);}
		pos++;
	} while ((first = strtok(NULL, ",\0")) != NULL);
		
	ar[num].numnums = pos;

	for (int i = 0; i < pos; i++) {
		int lNum = ar[num].nums[i];
		arBack[lNum].num = lNum;
		arBack[lNum].nums[arBack[lNum].numnums++] = num;
		printf("lNum is %d num is %d\n", lNum, num);
	}
	printf("leny: %d\n", leny);
	leny++;
}
	for (int i = 0; i < leny; i++) {
		printf("%d:: ", ar[i].num);
		for (int j = 0; j < ar[i].numnums; j++) {
			printf("%d; ", ar[i].nums[j]);
		}
		printf("\n");
	}
	printf("---------------\n");
	for (int i = 0; i <= max; i++) {
		printf("%d:: ", arBack[i].num);
		for (int j = 0; j < arBack[i].numnums; j++) {
			printf("%d; ", arBack[i].nums[j]);
		}
		printf("\n");
	}
	printf("---------------\n");

	for (int i = 1; i <= max; i++) {
		alreadyPos = 0;
		printf("Checking NUm: %d:: ", arBack[i].num); fflush(stdout);
		int found = 0;
		for (int j = 0; j < arBack[i].numnums; j++) {
			printf("checking its: %d\n", arBack[i].nums[j]); fflush(stdout);
			if (check(arBack[i].nums[j]) == 0) {
				found = 1; break;
			}
		}
		if (found == 0) {
			errors[errorsPos++] = i;
			printf("%d failed zero test\n", i);
		} else {
			printf("not fail"); notfail++;
		}
		//getchar();
		printf("\n");
	}
	

	printf("max is %d\n", max);
	for (int i = 0; i < errorsPos; i++) {
		printf("%d failed zero test\n", errors[i]);
	}
	printf("notfail is (not inc 0)%d\n", notfail);
	printf("notfail is (inc 0)%d\n", notfail+1);
	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", notfail+1);
	return 0;
}
int check(int num) {
	printf("loop through %d\n", arBack[num].num);
	for (int i = 0; i < alreadyPos; i++) {
		if (already[i] == num) {
			return 2;
		}
	}
	already[alreadyPos++] = arBack[num].num;
	for (int j = 0; j < arBack[num].numnums; j++) {
		if (arBack[num].nums[j] == 0) {
			printf("found zero\n");
			return 0;
		} else {
			printf("running check on %d\n", arBack[num].nums[j]);
			if (arBack[num].num == arBack[num].nums[j]) {
				printf("ignoring %d\n", arBack[num].nums[j]);
				continue;
			}
			int ret = check(arBack[num].nums[j]);
			if (ret == 0) {return 0;} else if (ret == 2) {continue;}
		}
	}
	return -1;
}
