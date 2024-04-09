#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char pipes[200][200];
long tot = 0;
int X, Y;
int chright(char *forwhat);
int chleft(char *forwhat);
int chtop(char *forwhat);
int chbtm(char *forwhat);
void printmaze();
int leny = 0;
int lenx = 0;
int distfun(int y1, int x1, int y2, int x2);
#define DAY "2023 Day12 Part1"
char *buildit3(int *nums, int pos, int one, int two, int three);
char *buildit4(int *nums, int pos, int one, int two, int three, int four);
char *buildit5(int *nums, int pos, int one, int two, int three, int four, int five);
char *buildit6(int *nums, int pos, int one, int two, int three, int four, int five, int six);
char *buildit7(int *nums, int pos, int one, int two, int three, int four, int five, int six, int seven);
char *buildit() ;
int matchit (char *ans, char *hashcode);
        char ans[1000];

int main(int argc, char **argv)
{
        int zzz = 0;
        char starts[100][5];
        printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);
       
        char line1[1000];
	int linenum = 0;

long matches = 0;
while(1) {
        fgets(line1, 1000, a);
        if (feof(a)) break;
	printf("LINE: %s", line1); fflush(stdout);
	linenum++;

	int nums[10]; 
	char numsS[1000]; char hashcode[1000];
	sscanf(line1, "%s %s\n", hashcode, numsS);
	printf("hashcode: %s -- numsS: %s\n", hashcode, numsS);

	int pos = 0;
	char *token = strtok(numsS, ",");
	while (token != NULL) {
	 	nums[pos] = atoi(token);
		pos++; token = strtok(NULL, ",");
	}	

	printf("nums are \n");
	for (int i = 0; i < pos; i++) {
		printf("%d |", nums[i]);
	}
int tot = 0;
	for (int i = 0; i < pos; i++) {
		tot += nums[i];
	}
printf("total %d\n", tot);
	int lenwithdots = (pos*2) + 1;;
	int numsPlusdots[lenwithdots];
	int howmany = 0;
	for (int i = 0; i < pos; i++) {
		if (i == 0) { numsPlusdots[i*2] = 0;}
		else { numsPlusdots[i*2] = 1;}
		numsPlusdots[i*2 + 1] = nums[i];	
	}
	numsPlusdots[pos * 2] = 0;
int tot2 = 0;
	for (int i = 0; i < lenwithdots; i++) {
		tot2 += numsPlusdots[i];
	}

	
	printf("nums are now \n");
	for (int i = 0; i < lenwithdots; i++) {
		printf("%d |", numsPlusdots[i]);
	}
	
	printf("hashcode: |%s| len %d numdots %d\n", hashcode, 
		strlen(hashcode), strlen(hashcode) - tot2);
	//distribute (strlen(hashcode) - tot2) over (pos+1)

	int distrib = strlen(hashcode) - tot2;
	int mynumdots = pos+1;
	if (mynumdots == 7) {
		for (int e = distrib; e >= 0; e--) {
			for (int f = distrib - e; f >= 0; f--) {
				for (int g = distrib - e - f; g >= 0; g--) {
					for (int h = distrib - e - f -g ; h >= 0; h--) {
						for (int i = distrib - e - f -g -h ; i >= 0; i--) {
							for (int j = distrib - e - f -g -h -i; j >= 0; j--) {
					    			printf("e, f, g, h, i, j, x: %d, %d, %d, %d, %d, %d, %d\n", e, f, g, h, i, j, distrib - e-f-g-h-i-j);
								buildit7(numsPlusdots, pos, e, f, g, h, i, j, distrib - e -f -g -h-i-j);
								matches += matchit(ans, hashcode);
							}
						}
					}
				}
			}
		}
	} else if (mynumdots == 6) {
		for (int e = distrib; e >= 0; e--) {
			for (int f = distrib - e; f >= 0; f--) {
				for (int g = distrib - e - f; g >= 0; g--) {
					for (int h = distrib - e - f -g ; h >= 0; h--) {
						for (int i = distrib - e - f -g -h ; i >= 0; i--) {
				    			printf("e, f, g, h, i, x: %d, %d, %d, %d, %d, %d\n", e, f, g, h, i, distrib - e-f-g-h-i);
							buildit6(numsPlusdots, pos, e, f, g, h, i, distrib - e -f -g -h-i);
							matches += matchit(ans, hashcode);
						}
					}
				}
			}
		}
	} else if (mynumdots == 5) {
		for (int e = distrib; e >= 0; e--) {
			for (int f = distrib - e; f >= 0; f--) {
				for (int g = distrib - e - f; g >= 0; g--) {
					for (int h = distrib - e - f -g ; h >= 0; h--) {
				    		printf("e, f, g, h, x: %d, %d, %d, %d, %d\n", e, f, g, h, distrib - e-f-g-h);
						buildit5(numsPlusdots, pos, e, f, g, h, distrib - e -f -g -h);
						matches += matchit(ans, hashcode);
					}
				}
			}
		}
	} else if (mynumdots == 4) {
		for (int e = distrib; e >= 0; e--) {
			for (int f = distrib - e; f >= 0; f--) {
				for (int g = distrib - e - f; g >= 0; g--) {
				    printf("e, f, g, x: %d, %d, %d, %d\n", e, f, g, distrib - e-f-g);
				    buildit4(numsPlusdots, pos, e, f, g, distrib - e -f -g);
				    matches += matchit(ans, hashcode);
				}
			}
		}
	} else if (mynumdots == 3) {
		for (int e = distrib; e >= 0; e--) {
			for (int f = distrib - e; f >= 0; f--) {
			    printf("e, f, x: %d, %d, %d\n", e, f, distrib - e-f);
			    buildit3(numsPlusdots, pos, e, f, distrib - e -f);
			    matches += matchit(ans, hashcode);
			}
		}
	} else if (mynumdots == 2) {
		printf("is an ERORp\n"); getchar();	
		for (int e = distrib; e >= 0; e--) {
			printf("e, x: %d, %d, %d\n", e, distrib - e);
			buildit();
			matches += matchit(ans, hashcode);
		}
	} else {printf("ERROR %d \n", mynumdots); getchar();}
	printf("hashcode: |%s| len %d\n", hashcode, strlen(hashcode));
	
	//printf("getchar\n"); getchar();
}
fclose(a);
printf("*********matches: %ld\n", matches);
}
int matchit (char *ans, char *hashcode)
{
	printf("matching |%s| with |%s|\n", ans, hashcode);
	if ( strlen(ans) != strlen(hashcode)) {printf("ERROR...."); getchar();}

/*
matching |###.##.#....| with |?###????????|
strlen ans v strlen hashcode 12 v 12
hashcode: |?###????????| len 12
*/
	for (int i = 0; i < strlen(ans); i++) {
		if (ans[i] == hashcode[i]) { /*great...*/
		} else if (hashcode[i] == '?') {
			 if (ans[i] == '#') {
			 } else if (ans[i] == '.') {
			 }
		} else {
			printf("ans: |%s| not a match\n", ans);
			return 0;
		}

	}
	return 1;
}
char *buildit3(int *nums, int pos, int one, int two, int three)
{
	for (int i = 0; i < 999; i++){ans[i] = '\0';}
	int sub = 0;
	for (int i = 0; i < one + nums[0]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[1]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < two + nums[2]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[3]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < three + nums[4]; i++) {
		printf("."); ans[sub++] = '.';
	}
	printf("\n");
}
char *buildit4(int *nums, int pos, int one, int two, int three, int four)
{
	for (int i = 0; i < 999; i++){ans[i] = '\0';}
	int sub = 0;
	for (int i = 0; i < one + nums[0]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[1]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < two + nums[2]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[3]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < three + nums[4]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[5]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < four + nums[6]; i++) {
		printf("."); ans[sub++] = '.';
	}
	printf("\n");
}
char *buildit5(int *nums, int pos, int one, int two, int three, int four, int five)
{
	for (int i = 0; i < 999; i++){ans[i] = '\0';}
	int sub = 0;
	for (int i = 0; i < one + nums[0]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[1]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < two + nums[2]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[3]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < three + nums[4]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[5]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < four + nums[6]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[7]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < five + nums[8]; i++) {
		printf("."); ans[sub++] = '.';
	}
	printf("\n");
}
char *buildit7(int *nums, int pos, int one, int two, int three, int four, int five, int six, int seven)
{
	for (int i = 0; i < 999; i++){ans[i] = '\0';}
	int sub = 0;
	for (int i = 0; i < one + nums[0]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[1]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < two + nums[2]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[3]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < three + nums[4]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[5]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < four + nums[6]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[7]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < five + nums[8]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[9]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < six + nums[10]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[11]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < seven + nums[12]; i++) {
		printf("."); ans[sub++] = '.';
	}
	printf("\n");
}
char *buildit6(int *nums, int pos, int one, int two, int three, int four, int five, int six)
{
	for (int i = 0; i < 999; i++){ans[i] = '\0';}
	int sub = 0;
	for (int i = 0; i < one + nums[0]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[1]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < two + nums[2]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[3]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < three + nums[4]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[5]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < four + nums[6]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[7]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < five + nums[8]; i++) {
		printf("."); ans[sub++] = '.';
	}
	for (int i = 0; i < nums[9]; i++) {
		printf("#"); ans[sub++] = '#';
	}
	for (int i = 0; i < six + nums[10]; i++) {
		printf("."); ans[sub++] = '.';
	}
	printf("\n");
}
char *buildit() {
	printf("NOT IMPLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");	
	printf("\n");
}
