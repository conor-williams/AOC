#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>

#include <unistd.h>

#define getchar()
using namespace std;

deque <int> circle2;
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


int tot = 0;
#define SIZE 50
char line1[SIZE];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day17.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

int leny = 0;
int spin;
	circle2.clear();
	circle2.push_back(0);
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
// 	printf("line1 %s\n", line1);
	
	spin = atoi(line1);
	leny++;
}
	fclose(a);
	int newSpin;
	for (int i = 1; i < 2018; i++) {
		if (i < spin) {
			newSpin = spin % circle2.size();
		} else {
			newSpin = spin;
		}
		rotateClock(newSpin);
		circle2.push_back(i);
	}
//for (auto it = circle2.begin(); it != circle2.end(); it++) { printf(" [%d] ", *it); } printf("\n"); getchar();
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d \n", circle2.front());

	return 0;
}
