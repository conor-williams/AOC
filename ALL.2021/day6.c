#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>

using namespace std;
FILE *a;
vector<int> starfish;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day6\n"); fflush(stdout);
        char line1[5000];
while (1) {
        fgets(line1, 4999, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	for (int i = 0; i < (int)strlen(line1); i++) {
		if (isdigit(line1[i])) {
			starfish.push_back(line1[i] -48);
		} else if (line1[i] == ',') {
		}
	}
}
fclose(a);

int loop1 = 0;
vector<int>::iterator iter1;
vector<int>::iterator iter2;
while (1) {
	loop1++; 
#ifdef _DEBUG_
	printf("loop1 %d\n", loop1); fflush(stdout);
#endif
	int iterPos = 0;
	int numnew = 0;
	for (iter1 = starfish.begin(); iter1 != starfish.end(); ++iter1) {
		if (*iter1 == 0) {
			numnew++;
			starfish.at(iterPos) = 6;
		} else {
			starfish.at(iterPos)--;
		}
		iterPos++;
	}
	for (int z = 0; z < numnew; z++) {
		starfish.push_back(8);
	}

#ifdef _DEBUG_
	printf("starfish now (%d): ", loop1); fflush(stdout);
	for (iter2 = starfish.begin(); iter2 != starfish.end(); ++iter2) {
		printf("%d ", *iter2); fflush(stdout);
	}
#endif
	if (loop1 == 18 || loop1 == 80) {
		printf("END loop1(%d) tot: (%ld)\n", loop1, starfish.size()); fflush(stdout);
		getchar();
	}
	if (loop1 == 81) {
		printf("END loop1(%d) tot (%ld)\n", loop1, starfish.size()); fflush(stdout);
		break;
	}
	
}
}
