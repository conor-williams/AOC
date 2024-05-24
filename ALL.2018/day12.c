#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#undef _DEBUG_
#define SIZE 200
char line1[SIZE];
long tot = 0;
struct plant_s {
	char from[6];
	char to;
};

struct plant_s plant[200];

int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day9.1\n"); fflush(stdout);

	char initial3[300];
	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		int ret = 0;
		ret = sscanf(line1, "initial state: %s", initial3);
		if (ret == 1) {continue;}
		if ((int)strlen(line1) == 0) {
			continue;
		}
		sscanf(line1, "%s => %c", plant[leny].from, &plant[leny].to);
		leny++;
	}
	fclose(a);

	char initial[400];
	printf("initial is %s\n", initial3);

	sprintf(initial, "..............................%s.............................................", initial3);
	tot = 0;
	for (int k = 0; k < (int)strlen(initial); k++) {
		if (initial[k] == '#') {
			tot++;
		}
	}
	for (int z = 0; z < 20; z++) {
		char initial2[200];
		for (int i = 0; i < (int)strlen(initial); i++) {
			char note[6];
			if (i-2 < 0) {note[0] = '.';} else {note[0] = initial[i-2];}
			if (i-1 < 0) {note[1] = '.';} else {note[1] = initial[i-1];}
			note[2] = initial[i];
			if (i+1 > (int)strlen(initial) -1) {note[3] = '.';} else {note[3] = initial[i+1];}
			if (i+2 > (int)strlen(initial) -1) {note[4] = '.';} else {note[4] = initial[i+2];}
			note[5] = '\0';
			
			int found = 0;
			for (int k = 0; k < leny; k++) {
				if (strcmp(plant[k].from, note) == 0) {
					found = 1;
					initial2[i] = plant[k].to; break;
				}	
			}
			if (found == 0) {
				initial2[i] = '.';
			}
		}
		initial2[(int)strlen(initial)] = '\0';
		strcpy(initial, initial2);
		printf("%d : %s\n", z+1, initial); 
	}
	tot = 0;
	for (int i = 0; i < (int)strlen(initial); i++) {
		if (initial[i] == '#') {
			tot+=i-30;
		}
	}
		
	printf("**tot %ld\n", tot);
}
