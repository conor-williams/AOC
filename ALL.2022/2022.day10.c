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
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2022 Day10.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];

int leny = 0;
while (1) {
        fgets(line1, 999, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1)-1] = '\0';	
	
	int addit;
	if (strcmp(line1, "noop") == 0) {
		checkit();
		cycles++;
		checkit();
	} else {
		sscanf(line1, "addx %d\n", &addit);		
		checkit();
		cycles++;
		int once = 0;
switchagain:
		checkit();
		if (once == 0) {
			cycles++;
			//printf("adding %d\n", addit);
			checkit();
			reg += addit;
			once++;
		} else if (once == 1) {
			goto switchagain;
		}
	}
//	printf("cycles is %d after\n", cycles);
	leny++;
}
fclose(a);
	checkit();
	printf("****tot %lld\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", tot);
}
void checkit() {
	if (cycles >= 179 && cycles <= 225) {
//		printf("regX %lld\n", reg); getchar();
	}
	switch(cycles) {
		case 20:
			if (checked[0] == 0) {
				checked[0] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
			}
			break;
		case 60:
			if (checked[1] == 0) {
				checked[1] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
			}
			break;
		case 100:
			if (checked[2] == 0) {
				checked[2] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
			}
			break;
		case 140:
			if (checked[3] == 0) {
				checked[3] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
			}
			break;
		case 180:
			if (checked[4] == 0) {
				checked[4] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
			}
			break;
		case 220:
			if (checked[5] == 0) {
				checked[5] = 1;
				printf("cycles(%d) * reg(%lld) = %lld\n", cycles, reg, cycles*reg);
				tot+= cycles*reg;
			}
			break;

	}	
}
