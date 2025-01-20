#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>

using namespace std;
FILE *a;
vector<int> starfish;
#define getchar()
unsigned long loop1Holder[260];
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
	loop1Holder[loop1] = starfish.size();
	printf("%d \n", loop1); fflush(stdout);
	if (loop1 == 80) {
		printf("END loop1(%d) tot: (%lu)\n", loop1, starfish.size()); fflush(stdout);
		getchar();
	} else if (loop1 == 81) {
		printf("END loop1(%d) tot (%lu)\n", loop1, starfish.size()); fflush(stdout);
	} else if (loop1 == 256) {
		printf("END loop1(%d) tot: (%lu)\n", loop1, starfish.size()); fflush(stdout);
		getchar();
	} else if (loop1 == 257) {
		printf("END loop1(%d) tot (%lu)\n", loop1, starfish.size()); fflush(stdout);
		break;
	} else if (loop1 == 218) {
		for (int z = loop1; z >= 16; z--) {
			for (int x = 17; x < z; x++) {
				unsigned long int big   =  loop1Holder[z];
				unsigned long int small  = loop1Holder[x];
				if (big % small == 0) {
					printf("diff: pos(%3d) - pos(%3d) == %8lu --- ", z, x, big-small);
					printf("(%8lu) / (%8lu) == ((%8lu))\n", big, small, big/small);
				}
			}
		}

		for (int z = loop1; z >= 16; z--) {
			int found = 0;
			for (int x = 17; x < z; x++) {
				if (loop1Holder[z] % loop1Holder[x] == 0) {
					//printf("starfish:(%3d):(%8lu) div pos(%3d)((%8lu)) = %15lu\n", loop1, starfish.size(), z, loop1Holder[z], starfish.size()/loop1Holder[z]);	fflush(stdout);
					found++;
					printf("%3d/%3d = %8lu\n", z, x, loop1Holder[z]/loop1Holder[x]);	fflush(stdout);
				}
			}
			if (found > 0) {
				printf("-----------(%d)^^^^^^^^^^\n", found);
			}
		}
		
		printf("200 end...\n"); fflush(stdout); break;
	} 
	
}
}
