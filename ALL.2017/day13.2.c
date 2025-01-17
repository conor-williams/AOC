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
	int num1;
	int num2;
	int len;
};
struct ar_s ar[2000];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day13.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	for (int i = 0; i < 2000; i++) {
		ar[i].num1 = 0;
		ar[i].num2 = 0;
		ar[i].len = 0;
	}
int leny = 0;
int max = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	//printf("line1 %s\n", line1);

//0: 5
	int num1, num2;
	
	sscanf(line1, "%d:%d", &num1, &num2);
	printf("%d @ %d\n", num1, num2);
	if (num1 > max) {max = num1;}
	ar[num1].num1 = num1;
	ar[num1].num2 = num2;
	ar[num1].len = num2+num2-2;
	leny++;
}
	printf("max is %d\n", max); getchar();
	int tot = 0;
	int delay = 0;
	do {
		printf("delay %d\n", delay); 
		int numClash = 0;
		for (int t = 0; t <= max; t++) {
			if (ar[t].num2 != 0) {
				if (((t+delay) % ar[t].len) == 0) {
					numClash++;
					break;
					//printf("clash at %d\n", t);
					//tot+=ar[t].num1*ar[t].num2;
				}
			}
		}
		if (numClash == 0) {
			printf("no clash at del %d\n", delay);
			fflush(stdout); dup2(fd, 1);
			printf("**ans: %d\n", delay);
			exit(0);
			break;
			//getchar();
		}
		delay++;
	} while (1);
	printf("**tot is %d\n", tot);
	dup2(fd, 1);
	printf("**ans: %d\n", tot);
}
