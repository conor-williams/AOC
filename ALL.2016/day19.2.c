#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <deque>
#include <algorithm>
#include <string>

using namespace std;
//int END = 3014387;
//int END = 21;
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


int lenx, leny;
#define DAY "2016 day19 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 20
#define getchar()

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif

//3014387
	int END = atoi(line1);
	for (int i = 1; i <= END; i++) {
		circle2.push_back(i);
	}
//	for (auto it = circle2.begin(); it != circle2.end(); it++) { printf(" [%d] ", *it); } printf("\n");
	int endElf = atoi(line1);
	printf("endElf is [%d]\n", endElf);
//	int fd = dup(1); close(1);

	int mv = circle2.size()/2;
	rotateClock(mv);
	for (int i = 0; i < endElf; i++) {
		if (circle2.size() == 1) {printf("breaking...\n"); break;}
		circle2.pop_front();
		int rem = circle2.size()/2 % 2;
		rotateClock(rem);
	}
	//dup2(fd,1);
	printf("** size: %d -- \n***ANS is %d\n", (int)circle2.size(), (int)circle2.front());
	leny++;
}
fclose(a);
	printf("***tot %ld END\n", tot); fflush(stdout);
} 
