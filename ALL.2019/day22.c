#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <unistd.h>

using namespace std;

#define getchar()

int lenx, leny;
#define DAY "2019 day22 part1\n"
#undef _DEBUG_
#define LINE 200
#define END 10007

vector <int> deck;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); 
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	for (int i = 0; i < END; i++) {
		deck.push_back(i);
	}

	for (auto it1 = deck.begin(); it1 != deck.end(); it1++) { printf("%d ", *it1); }
	printf("\n");
while(1) {
	printf("start of while...\n"); fflush(stdout);
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	printf("LINE: %s getchar\n", line1); getchar();
#ifdef _DEBUG_
#endif
	if (strcmp(line1, "deal into new stack") == 0) {
		printf("got deal into new stack...\n");
		reverse(deck.begin(), deck.end());
		continue;
	} 

	int cutNum;
	int ret1 = sscanf(line1, "cut %d", &cutNum);
	if (ret1 == 1) {
		printf("cutNum is %d\n", cutNum);
		vector <int> tmpV(END);
		int cut1 = cutNum;
		if (cutNum < 0) {
			cut1 = END+cutNum;
		}
		vector<int>::iterator itm; itm = deck.begin() + cut1;

		copy(itm, deck.end(), tmpV.begin());
		copy(deck.begin(), itm, tmpV.begin()+(END-cut1));
		deck = tmpV;
		continue;
		
	}
	
	int dealInc;
	int ret2 = sscanf(line1, "deal with increment %d", &dealInc);
	if (ret2 == 1) {
		printf("got deal with inc...\n");
		vector<int> tmpVe(END);
		for (int i = 0; i < END; i++) {
			int pos = (i*dealInc)%END;
			tmpVe[pos] = deck[i];
		}
		deck = tmpVe;
for (auto it1 = deck.begin(); it1 != deck.end(); it1++) { printf("%d ", *it1); }
		continue;
	}
	leny++;
	printf("lenx %d - leny %d\n", lenx, leny);
}
fclose(a);

	printf("Result: "); fflush(stdout);
	int pos1 = 0;

	int pos2 = 0;
	int i = 0;
	for (auto it1 = deck.begin(); it1 != deck.end(); it1++) {
		printf("%d ", *it1);
		if (*it1 == 2019) {pos1 = it1 - deck.begin(); pos2 = i;}
		i++;
		
	}
	printf("\n");
	assert(pos1 == pos2);
	fflush(stdout); dup2(fd, 1);
	printf("******** pos1 %d\n", pos1);

}
