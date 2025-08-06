#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
unsigned long long tot = 0;
#define SIZE 500
char line1[SIZE];
struct rules_s {
	char from[10];
	int weight;
	char to[20][10];
	int toPos;
};

struct rules_s rules[2000];
void next(char from[], int weightIn);
int leny = 0;
char bottom[30];
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day7.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);
	
	char *first = strtok(line1, " (");
	strcpy(rules[leny].from, first);
	first = strtok(NULL, ")");
	rules[leny].weight = atoi(first);
	strtok(NULL, ">");
	while ((first = strtok(NULL, " ,\0")) != NULL) {
		strcpy(rules[leny].to[rules[leny].toPos++], first);
		printf("cp %s\n", rules[leny].to[rules[leny].toPos-1]);
	}
	leny++;
}
fclose(a);
	for (int i = 0; i < leny; i++) {
		printf("[%s]\n", rules[i].from);
		for (int k = 0; k < rules[i].toPos; k++) {
			printf("	[%s]\n", rules[i].to[k]);
		}
	}
	getchar();

	int weight = 0;
	for (int i = 0; i < leny; i++) {
		
		if (rules[i].toPos == 0) {
			weight+=rules[i].weight;
			printf("[%s]\n", rules[i].from);
			printf("calling next\n");
			char bottomPrev[50];
			if (i > 0) {strcpy(bottomPrev, bottom);}
			next(rules[i].from, weight);
			if (i > 0) {if (strcmp(bottom, bottomPrev) != 0) {fflush(stdout); dup2(fd, 1); printf("not found...\n"); exit(0);}}
			printf("bottom: %s\n", bottom);
			weight = 0;
		}
	}
	//printf("***tot is ^^ [%llu]\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %s\n", bottom);
	return 0;
}
int ind = 0;
void next(char from[], int weightIn) {
	ind++;
	int weight = weightIn;
	for (int i = 0; i < leny; i++) {
		for (int k = 0; k < rules[i].toPos; k++) {
			if (strcmp(rules[i].to[k], from) == 0) {
				strcpy(bottom, rules[i].from);
				for (int j = 0; j< ind; j++) {printf("	");} printf("h1[%s]\n", rules[i].from);
				weight += rules[i].weight;
				next(rules[i].from, weight);
				weight = weightIn;
			}
		}
	}
	ind--;
}
