#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <map>

#include <unistd.h>
using namespace std;
map <int, unsigned long long> mp;

//#define getchar()

FILE *a;
int aR[1200];
int leny = 0;
void recur(int st);
unsigned long long count123 = 0;
int jMax = 0;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2020 Day10 Part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	while (1) {
		fgets(line1, 500, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		int ret;
		int num; 
		ret = sscanf(line1, "%d", &num);
		if (ret == 1) {
			aR[leny] = num;
		}
		leny++;
	}
	aR[leny] = 0;
	leny++;
	fclose(a);
	sort(aR, aR+leny);
	jMax = aR[leny-1]+3;
	aR[leny] = jMax; leny++;
	printf("aR[0] is %d jMax is %d\n", aR[0], jMax);
	printf("leny is %d\n", leny);

	recur(0);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", count123);
}

void recur(int st) {
	//printf("-----%d-----\n", aR[i]);
	for (int yy = st+1; yy < leny && yy < st+4; yy++) {
		if (aR[yy] - aR[st] <= 3) {
			if (mp.find(yy) == mp.end()) {
				unsigned long long countBef = count123;
				if (aR[yy] != jMax) {recur(yy);}
				unsigned long long countAft = count123;
				mp[yy] = countAft - countBef;
				if (aR[yy] == jMax) {count123++; /*printf("end reached...\n");*/}
			} else {
				count123 += mp[yy];
			}
			
		}
	}
}
