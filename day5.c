#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("2018 Day5.1\n"); fflush(stdout);

	int SIZE = 60000;
        char line1[SIZE];

int leny = 0;
while (1) 
{
        fgets(line1, SIZE, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
 	line1[strlen(line1)-1] = '\0';
	leny++;
}
	
	while(1) {
		int change = 0;
		for (int i = 0; i < strlen(line1) -1; i++) {
				if (i < 0) {i = 0;}
				int f = 0;
				for (f = 0; f < strlen(line1) - 1; f++) {
					if (line1[f] != '0') {break;}
				}
				int s;
				for (s = f+1; s < strlen(line1) - 1; s++) {
					if (line1[s] != '0') {break;}
				}
			       if (islower((int)line1[i]) && isupper((int)line1[i+1])) {
				if (line1[f] == tolower(line1[s])) {
//					printf("here1... line1[i] %c V %c line1[i+1]", line1[i], line1[i+1]);
					line1[f] = '0'; line1[s] = '0';
					/*int j = 0;
					for (j = i; j < strlen(line1)-2; j++) {
						line1[j] = line1[j+2];
					}
					line1[j] = '\0';
					*/
//			printf("after1 [%s]\n", line1);
					//i = i - 3;
					change=1;
				}
			} else if (isupper((int)line1[i]) && islower((int)line1[i+1])) {
				if (line1[i] == toupper(line1[i+1])) {
//					printf("here2... line1[i] %c V %c line1[i+1]", line1[i], line1[i+1]);
					line1[f] = '0'; line1[s] = '0';
					/*int j = 0;
					for (j = i; j < strlen(line1)-2; j++) {
						line1[j] = line1[j+2];
					}
					line1[j] = '\0';
					*/
//			printf("after2 [%s]\n", line1);
					i = i - 3;
					change=1;
				}
			}
		}
		if (change == 0) {break;}
	}
	printf("***polymer len [%d]\n", (int)strlen(line1));
}

