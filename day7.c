#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define _DEBUG_
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day6.1\n"); fflush(stdout);
	int SIZE = 20000; char line1[SIZE];

	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		char *first;
		first = strtok(line1, " ");
		while (first != NULL) {
			printf("%s,", first); getchar();
			int children = atoi(first);
			printf("children: %d\n", children);
			first = strtok(NULL, " ");
			int metadata = atoi(first);
			//loop the children
again:
			for (int i = 0; i < children; i++) {
				loopit();
				first = strtok(NULL, " ");
				int children = atoi(first);
				first = strtok(NULL, " ");
				int metadata = atoi(first);
				for (int i = 0; i < children; i++) {
					first = strtok(NULL, " ");
					int children = atoi(first);
					first = strtok(NULL, " ");
					int metadata = atoi(first);
					for (int i = 0; i < children; i++) {
						first = strtok(NULL, " ");
						int children = atoi(first);
						first = strtok(NULL, " ");
						int metadata = atoi(first);
					}
					for (int k = 0; k < metadata; k++) {
						first = strtok(NULL, " ");
						int metadata = atoi(first);
						printf("metadata: %d\n", metadata);	
					}
				}
				for (int k = 0; k < metadata; k++) {
					first = strtok(NULL, " ");
					int metadata = atoi(first);
					printf("metadata: %d\n", metadata);	
				}
			}
			for (int k = 0; k < metadata; k++) {
				first = strtok(NULL, " ");
				int metadata = atoi(first);
				printf("metadata: %d\n", metadata);	
			}
		}
		
		leny++;

	}
}

void loopit() {
	first = strtok(NULL, " ");
	int children = atoi(first);
	first = strtok(NULL, " ");
	int metadata = atoi(first);
	for (int i = 0; i < children; i++) {
		loopit();
	}
	for (int k = 0; k < metadata; k++) {
		first = strtok(NULL, " ");
		int metadata = atoi(first);
		printf("metadata: %d\n", metadata);	
	}
}
