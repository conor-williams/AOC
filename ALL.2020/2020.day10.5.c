#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

FILE *a;
int aR[1200];
int aROrig[1200];
int already[2000][1000];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2020 Day9\n"); fflush(stdout);
        char line1[1000];
	
int leny = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	int ret; int num; 
	ret = sscanf(line1, "%d", &num);
	if (ret == 1) {
		aR[leny] = num;
	}
	leny++;
}
fclose(a);
	sort(aR, aR+leny);
	int jMax = aR[leny-1]+3;
	aR[leny] = jMax; leny++;
	int lenyOrig = leny;
	for (int i = 0; i < leny; i++) {
		aROrig[i] = aR[i];
	}
	for (int i = 0; i < leny; i++) {printf("%d, ", aR[i]);} printf("\n");
	
	int firstGone[100];
	int numRebegin = -1;
	char outStrPrev[2000] = "";
	int firstGonePos = 0;	
rebegin:
	leny = lenyOrig;
	for (int i = 0; i < leny; i++) {
		aR[i] = aROrig[i];
	}
	numRebegin++;
	
	int numRestart = -1;
	int tosort[1000];
	int lenyStart;
////////////
	char outStr[2000];
	int first = 0;
				
	for (int q = 0; q <= firstGonePos; q++) {
		for (int r = 0; r < firstGonePos; r++) {
			tosort[r] = firstGone[r];
		}

		int alreadyPos = 0;
		do {
			int onee[2000];
			for (int t = 0; t < q; t++) {
				onee[t] = tosort[t];
			}
			sort(onee, onee+q);
			int found1 = 0;
			for (int s = 0; s < alreadyPos; s++)  {
				for (int t = 0; t<q; t++) {
					if (already[s][t] != onee[t]) {
						goto next;
					} else {
						if (t==q) {
							found1 = 1;
						}
					}
				}
next:
				printf("");
			}
			if (found1 == 0) {
				for (int t = 0; t < q; t++) {
					already[alreadyPos][t] = onee[t];
				} alreadyPos++;				
			} else { 
				continue;
			}
restart:
			numRestart++;
			first = 0;
			lenyStart = leny;
			sprintf(outStr, "%d", aR[0]);
			for (int p = 0; p < q; p++) {
				 //printf("tosort[%d] is %d\n", p, tosort[p]);
			}
			//printf("-------\n");
			for (int i = 1; i < leny-1; i++) {
				
				for (int p = 0; p < q; p++) {
					if (aR[i] == tosort[p]) {sprintf(outStr, "%s, %d", outStr, aR[i]); goto cont;}
				}
					
				int diff;
				if ((first == 0) && (diff = (aR[i+1] - aR[i-1])) <= 3) {
					int remove = aR[i];
					for (int k = i; k < leny; k++) {
						aR[k] = aR[k+1];
					}
					//printf("remove %d:%d numRestart is %d\n", i, remove, numRestart); 
					if (numRestart == 0) {
						int found = 0;
						for (int s = 0; s < firstGonePos; s++) {
							if (remove == firstGone[s]) {
								found = 1;
							}
						}
						if (found == 0) { firstGone[firstGonePos] = remove; firstGonePos++;}
					}
					leny--;
					//sprintf(outStr, "%s, %d", outStr, aR[i]);
					first = 1;
					i--;
				} else {
					sprintf(outStr, "%s, %d", outStr, aR[i]);
					//printf("%d, ", aR[i]); getchar();
				}
cont:
			
				printf("");
			}
			sprintf(outStr, "%s, %d", outStr, aR[leny-1]);
			if (lenyStart != leny) {
				//printf("%s", outStr);// getchar();
				//printf("going to restart\n"); getchar();
				printf("%s\n", outStr);
				goto restart;
			} else {
	leny = lenyOrig;
	for (int i = 0; i < leny; i++) {
		aR[i] = aROrig[i];
	}
	numRebegin++;
	numRestart = -1;
				//if (strcmp(outStrPrev, outStr) == 0) {
				///	exit(0);
				//}
				///strcpy(outStrPrev, outStr);
				//printf("going to rebegin...\n"); getchar();
				//goto rebegin;
			}
		} while(next_permutation(tosort, tosort+firstGonePos));
	}
	//getchar();
}


void comb(int N, int K)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
 
    // print integers and permute bitmask
    do {
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) std::cout << " " << i;
        }
        std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}
 
