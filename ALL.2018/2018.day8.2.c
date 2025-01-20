#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define _DEBUG_
int loopit();
char *first;
int ind = 0;
#define SIZE 40000
char line1[SIZE];
unsigned long totmetadata = 0;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day8.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		first = strtok(line1, " ");
		int count = 0;
		while (first != NULL) {
			printf("BACK IN WHILE?? [%d]\n", count); fflush(stdout);
			if (count == 1) {
				printf("BREAKING (first check strtok)... count: [%d]\n", count); 
				if (strtok(line1, " ") == NULL) {
					printf("STRTOK1 NULL\n");
				} else {
					printf("STRTOK1 NOT NULL %s\n", first);
					if (strtok(line1, " ") == NULL) {
						printf("STRTOK2 NULL\n");
					} else {
						printf("STRTOK2 NOT NULL %s\n", first);
					}
				}
				break;
			}
			count++;
			int children = atoi(first);
			printf("children: %d\n", children); fflush(stdout);
			first = strtok(NULL, " ");
			int metadata = atoi(first);
	int meta[1000];
	int metaPos = 0;
			for (int i = 0; i < children; i++) {
				meta[i] = loopit(); metaPos++;
				printf("meta[i] is %d metaPos is %d\n", meta[i], metaPos);
			}
			if (children == 0) {
				for (int k = 0; k < metadata; k++) {
					first = strtok(NULL, " ");
					int metadata = atoi(first);
					printf("metadata: %d\n", metadata); fflush(stdout);
					totmetadata+=metadata;
				}
			} else {
				for (int k = 0; k < metadata; k++) {
					first = strtok(NULL, " ");
					int metadata = atoi(first) -1;
					printf("metadata: %d\n", metadata); fflush(stdout);
					if (metadata < children) {
						totmetadata+=meta[metadata];
					}
				}
			}
				
		}
		leny++;
	}

	fflush(stdout); dup2(fd, 1);
	printf("**tot %lu\n", totmetadata);
	fclose(a);
}

int loopit() {
	ind++;
	first = strtok(NULL, " ");
	int children = atoi(first);
	first = strtok(NULL, " ");
	int metadata = atoi(first);
	int meta[1000];
	int metaPos = 0;
	for (int i = 0; i < children; i++) {
		meta[metaPos] = loopit(); metaPos++;
	}
	if (children == 0) {
		int localtot = 0;
		for (int k = 0; k < metadata; k++) {
			first = strtok(NULL, " "); fflush(stdout);
			int metadata = atoi(first);
			for (int p = 0; p < ind; p++) {printf("	");}
			printf("Hmetadata: %d\n", metadata); fflush(stdout);
			localtot += metadata;
			//totmetadata+=metadata;
		}
		return localtot;
	} else {
		int localtot = 0;
		for (int k = 0; k < metadata; k++) {
			first = strtok(NULL, " "); fflush(stdout);
			int metadata = atoi(first) -1;
			if (metadata < children) {
				localtot += meta[metadata];
				//totmetadata += meta[metadata];
			}
			for (int p = 0; p < ind; p++) {printf("	");}
			printf("Hmetadata: %d\n", metadata); fflush(stdout);
			//totmetadata+=metadata;
		}
		return localtot;
	}
	ind--;
}
