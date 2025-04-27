#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>

#include <unistd.h>

#define getchar()
using namespace std;

#undef _DEBUG_
#define SIZE 200
char line1[SIZE];
long tot = 0;
struct plant_s {
	char from[6];
	char to;
};

struct plant_s plant[200];


struct nn_s {
	char from[100];
	char to[4300];
};
struct nn_s nn[1000000];
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day12.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char initial3[900];
	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[(int)strlen(line1)-1] = '\0';
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

	printf("initial3 is %s\n", initial3);
	unsigned long long tot = 0;
	for (int i = 0; i < 186; i++) {
		unsigned long long pos = (unsigned long long) 50000000000  -87 + i;
		tot+= pos;
	}
	
	printf("**tot %llu\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", tot);
	exit(0);

	getchar();
	char initial[2000];
	sprintf(initial, "............................................................................................................................................................................................................................................................................................................%s..................................................", initial3);
			char *s = (char*)malloc(100000000);
			if (s==NULL) {printf("s NULL\n"); exit(0);}
			char *initial2 = (char*)malloc(5000000000);
			if (initial2==NULL) {printf("s NULL\n"); exit(0);}
			strcpy(s, initial);
			for (long long z = 0; z <= 5000000000; z++) {
				if (z % 10000 == 0) {printf("z %lld \n", z);}
				printf("loop is z %lld \n", z);
				for (int q = 0; q < (int)strlen(s); q++) {
					if (s[q] == '#') {printf("first # is %d\n", q-300); break;}
				}
				for (int q = (int)strlen(s) -1; q >= 0; q--) {
					if (s[q] == '#') {printf("last # is %d\n", q-300); break;}
				} 
				int end1 = (int)strlen(s);
				if (s[end1-1] == '#' && s[end1-2] == '#') {
					s[end1] = '.';
					s[end1+1] = '.';
					s[end1+2]  = '\0';
				} else if (s[end1-1] == '.' && s[end1-2] == '#') {
					s[end1] = '.';
					s[end1+1]  = '\0';
				} else if (s[end1-1] == '#' && s[end1-2] == '.') {
					s[end1] = '.';
					s[end1+1] = '.';
					s[end1+2]  = '\0';
				}
				for (int i = 0; i < (int)strlen(s); i++) {
					char note[6];
					if (i-2 < 0) {note[0] = '.';} else {note[0] = s[i-2];}
					if (i-1 < 0) {note[1] = '.';} else {note[1] = s[i-1];}
					note[2] = s[i];
					if (i+1 > (int)strlen(s) -1) {note[3] = '.';} else {note[3] = s[i+1];}
					if (i+2 > (int)strlen(s) -1) {note[4] = '.';} else {note[4] = s[i+2];}
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
				initial2[strlen(s)+5] = '\0';
				strcpy(s, initial2);
				//printf("next s is %s\n", s);// getchar();
			}
			printf("s after is %s\n", s);
/*
	int cou = 0;
			
	for (int z = 0; z < 1000; z++) {
		char initial2[5000];
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
	}
*/
	tot = 0;
	for (int i = 0; i < (int)strlen(s); i++) {
		if (s[i] == '#') {
			tot+=i-300;
		}
	}
		
	free(s);
}
