#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <iostream>

using namespace std;
FILE *a;
deque <unsigned long long> starfish;
int initial[10] = {0};
#define getchar()
void rotateClock(int d);
void rotateClock(int d)
{
    for (int i = 0; i < d; i++) {
        unsigned long long val = starfish.front();
        starfish.pop_front();
        starfish.push_back(val);
    }
}
unsigned long long loop1Holder[300];
void rotate(int d);
void rotate(int d)
{
    // Push first d elements
    // from last to the beginning
    for (int i = 0; i < d; i++) {
        unsigned long long val = starfish.back();
        starfish.pop_back();
        starfish.push_front(val);
    }
}

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
			initial[line1[i] -48]++;
		} else if (line1[i] == ',') {
		}
	}
}
fclose(a);

int loop1 = 0;
for (int i = 0; i < 9; i++) {
	printf("push back of %d\n", initial[i]);
	starfish.push_back(initial[i]);
}
for (auto it = starfish.begin(); it != starfish.end(); ++it) {
        cout << ' ' << *it;
}

getchar();
while (1) {
	loop1++; 

	unsigned long long val = starfish.front();
	rotate(2); 
	//cout << "BEF: "; for (auto it = starfish.begin(); it != starfish.end(); ++it) { cout << ' ' << *it; } cout << endl;
	unsigned long long val2 = starfish.front();
	starfish.pop_front();
	starfish.push_front(val+val2);
	rotateClock(3);
	//cout << "AFT: "; for (auto it = starfish.begin(); it != starfish.end(); ++it) { cout << ' ' << *it; } cout << endl;

	getchar();
	unsigned long long mysum = 0;
	for (auto it = starfish.begin(); it != starfish.end(); ++it) { mysum+= *it; }
	loop1Holder[loop1] = mysum;
	if (loop1 == 256) {
		  for (int z = loop1; z >= 16; z--) {
			int found = 0;
                        for (int x = 17; x < z; x++) {
                                unsigned long long int big   =  loop1Holder[z];
                                unsigned long long int small  = loop1Holder[x];
                                if (big % small == 0) {
                                        printf("(%3d)/(%3d) == (%8llu)\n", z, x, big/small);
					found++;
                                }
                        }
			if (found > 0) {
				printf("---------------------------^^^^ %d ^^^^^^^-----------\n", found);
			}
                }

		unsigned long long sum = 0;
		for (auto it = starfish.begin(); it != starfish.end(); ++it) { cout << ' ' << *it; sum+= *it; } cout << endl;
		printf("\nsum (%d) is %llu\n", loop1, sum);
		break;
	} else if (loop1 == 80) {
		unsigned long long sum = 0;
		for (auto it = starfish.begin(); it != starfish.end(); ++it) { cout << ' ' << *it; sum+= *it; } cout << endl;
		printf("\nsum (%d) is %llu\n", loop1, sum);
		getchar();
	} 
	
}
}
