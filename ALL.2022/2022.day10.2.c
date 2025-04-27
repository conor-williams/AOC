#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
long long tot = 0;
long long reg = 1;
int cycles = 0;
void checkit();
int checked[10] = {0};
char screen[10][50];
int row = 0;
int pos = 0;
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day10 part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 50; x++) {
			screen[y][x] = '.';
		}
	}
	int leny = 0;
	checkit();
	while (1) {
		fgets(line1, 999, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';	

		int addit;
		if (strcmp(line1, "noop") == 0) {
			cycles++;
			checkit();
		} else {
			sscanf(line1, "addx %d\n", &addit);		
			cycles++;
			checkit();
			cycles++;
			reg += addit;
			checkit();
		}
		leny++;
	}
	fclose(a);
	fflush(stdout); dup2(fd, 1);
	printf("**ans:\n");
	printf("*****************************************\n");
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 40; x++) {
			if (screen[y][x] == '.') {
				printf(" ");
			} else {
				printf("%c", screen[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("*****************************************\n");
	//printf("****tot %lld\n", tot);

}
void checkit() {
	if (reg > 40) {printf("ERROR\n"); exit(0);}
	int pos = cycles%40;
	if (reg == pos-1 || reg == pos || reg == pos+1) {screen[row][pos]   = '#';}


	switch(cycles) {
		case 39:
			if (checked[0] == 0) {
				checked[0] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
				row++;
				pos = 0;
			}
			break;
		case 79:
			if (checked[1] == 0) {
				checked[1] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
				row++;
				pos = 0;
			}
			break;
		case 119:
			if (checked[2] == 0) {
				checked[2] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
				row++;
				pos = 0;
			}
			break;
		case 159:
			if (checked[3] == 0) {
				checked[3] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
				row++;
				pos = 0;
			}
			break;
		case 199:
			if (checked[4] == 0) {
				checked[4] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
				row++;
				pos = 0;
			}
			break;
		case 239:
			if (checked[5] == 0) {
				checked[5] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
				row++;
				pos = 0;
			}
			break;

	}	
}
