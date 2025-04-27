#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <map>

#include <unistd.h>

#define getchar()
using namespace std;

int buckets[100];
int lenx, leny;
#define DAY "		2015 day17 part2\n"
#undef _DEBUG_
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	char line1[1000];
	while(1) {
		fgets(line1, 999, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
		buckets[leny] = atoi(line1);
		leny++;
	}
	fclose(a);
	int ar[100];
	int vol = 150;
	int tot = 0;
	int minEnd = 1000;
	for (int end = 0; end < leny; end++) {
		if (end == minEnd+1) {break;}
		for (int i = 0; i < end; i++) {
			ar[i] = 1;
		}
		for (int i = end; i < leny; i++) {
			ar[i] = 0;
		}

		sort(ar, ar+leny);
		do {
			int sumB = 0;
			for (int i = 0; i < leny; i++) {
				if (ar[i] == 1) {
					sumB += buckets[i];
				}
			}
			if (sumB == vol) {
				tot++;
				//printf("%d is min\n", end);
				minEnd = end;
			}
		} while (next_permutation(ar, ar+leny));
	}

	printf("****tot %d\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);
}
