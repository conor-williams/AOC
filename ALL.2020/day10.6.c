#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <deque>
#include <vector>

using namespace std;

FILE *a;
vector <int> aR;
vector <int> aROrig;
deque<int> circle2;
vector<deque<int>> already;
int alreadyPos = 0;
void rotateClock(int d);
void rotateClock(int d)
{
    for (int i = 0; i < d; i++) {
        int val = circle2.front();
        circle2.pop_front();
        circle2.push_back(val);
    }
}
void rotate(int d);
void rotate(int d)
{
    // Push first d elements
    // from last to the beginning
    for (int i = 0; i < d; i++) {
        int val = circle2.back();
        circle2.pop_back();
        circle2.push_front(val);
    }
}

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2020 Day9\n"); fflush(stdout);
        char line1[1000];
	
int leny = 0;
aR.insert(aR.end(), 0);
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	int ret; int num; 
	ret = sscanf(line1, "%d", &num);
	if (ret == 1) {
		aR.insert(aR.end(), num);
	}
	leny++;
}
fclose(a);
	sort(aR.begin(), aR.end());
	auto iter = aR.end();
	int jMax = *iter+3;
	aR.insert(aR.end(), jMax);
	leny++;
	int lenyOrig = leny;
	aROrig = aR;
	for (int i = 0; i < leny; i++) {printf("%d, ", aR[i]);} printf("\n");
	
	int firstGone[100];
	int firstGonePos = 0;	

	leny = lenyOrig;
	//aR = aROrig;
	int lenyStart;
////////////
	deque <int> outStr;
	int first = 0;

	int one = 1;
	int dummy = 0;
	int dummyB4 = dummy;
onelast:
	dummyB4 = dummy;
	int numRestart = -1;
	int end = firstGonePos;
	for (int q = 0; q <= end; q++) {
		int N = firstGonePos; 
    		string bitmask(N-q, 0);
		bitmask.resize(N, 1); 
		do {
restart:
			outStr.clear();
			numRestart++;
			first = 0;
			lenyStart = leny;
			outStr.push_back(aR[0]);
			for (int i = 1; i < leny-1; i++) {
				
				for (int p = 0; p < N; p++) {
					if (bitmask[p] && aR[i] == firstGone[p]) {
						outStr.push_back(aR[i]); goto cont;
					}
				}
				if (bitmask[q-1] == 0) {goto cont;}
					
				int diff;
				if ((first == 0) && (diff = (aR[i+1] - aR[i-1])) <= 3) {
					int remove = aR[i];	
					aR.erase(aR.begin()+i);
					//printf("remove %d:%d numRestart is %d\n", i, remove, numRestart); getchar();
					if (numRestart == 0) {
						int found = 0;
						for (int s = 0; s < firstGonePos; s++) {
							if (remove == firstGone[s]) {
								found = 1;
							}
						}
						if (found == 0) { dummy++; first=1; firstGone[firstGonePos] = remove; firstGonePos++;}
					
					}
					leny--;
					i--;
				} else {
					outStr.push_back(aR[i]);
				}
cont:
			
				continue;
			}
			outStr.push_back(aR[leny-1]);
			if (lenyStart != leny) {
				int cnt = count(already.begin(), already.end(), outStr);
				if (cnt == 0) {
					already.insert(already.end(), outStr); alreadyPos++;
				}
//				for (auto iter = outStr.begin(); iter != outStr.end(); iter++) {
//					printf("%d, ", *iter);
//					outStr.pop_front();
//				}
//				printf("\n");
				goto restart;
			} else {
				leny = lenyOrig;
				aR = aROrig;
				numRestart = -1;
			}
		} while(next_permutation(bitmask.begin(), bitmask.end()));
	}
	one++;
	if (one < 200 && dummyB4 != dummy) {
		goto onelast;
	}
	printf("***** alreadyPos is %d\n", alreadyPos+1); //+1 for the first...
	printf("***** already.size() is %d\n", already.size()+1);
	printf("dummy is %d\n", dummy);
}


/*
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
 
*/
