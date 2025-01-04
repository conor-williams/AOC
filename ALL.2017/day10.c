#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
unsigned long long tot = 0;
#define SIZE 20000
char line1[SIZE];
int theInts[100];
/*#define N 5*/
#define N 256
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day10.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
int leny = 0;
int pos = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1: %s\n", line1);
	
	char * first = strtok(line1, ",");
	
	do {
		theInts[pos] = atoi(first);
		pos++;
	} while ((first = strtok(NULL, ",")) != NULL);
	tot = 0;
	leny++;
}

	printf("LENGTHS: ");
	for (int j = 0; j < pos; j++) {
		printf(" %d ", theInts[j]);
	}
	printf("\n");

	int initial[260];
	int initial2[10000];
	for (int k = 0; k < N; k++) {
		initial[k] = k;
	}
	int startpos; int skip = 0;
	startpos = 0;
	int len;
	for (int z = 0; z < N ; z++) {
		len = theInts[z];
		printf("len is %d\n", len);
		memset(initial2, 0, N*(sizeof(int)));
		for (int k = 0; k <  len; k++) {
			int p = (startpos+k)%N;
			initial2[p] = initial[p];
		}
//		for (int k = startpos; k <  startpos + len; k++) 
		for (int k = 0 ; k < len; k++) {
			int p = (startpos+k)%N;
			int q = (startpos+((len-k-1)))%N;
			printf("swap p V q (pos %d V pos %d\n", p, q);
			printf("swap p V q (actual %d V actual %d\n", initial[p], initial2[q]);
			initial[p] = initial2[q];
		}
		startpos = (startpos+len+skip)%N;
		skip++;
		printf("NUMS: ");
		for (int j = 0; j < N; j++) {
			printf(" %d ", initial[j]);
		}
		printf("\n");
		printf("new start %d\n", startpos);
		printf("skip %d\n", skip);
	}
	
	dup2(fd, 1);
	printf("***mul %d*%d =  %d\n", initial[0], initial[1], initial[0] * initial[1]);
	printf("\nEND\n");

}
