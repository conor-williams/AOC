#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <iostream>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

map <string, char> mp;
string polymer;
string polymerTo;

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day Day14 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			continue;
		} else if (leny == 0) {
			polymer = line1;
		} else {
			char from[10]; char to;
			sscanf(line1, "%s -> %c", from, &to);
			string Sfrom = from;
			mp[from] = to;
		}
		leny++;
	}
	fclose(a);
	cout << "Template:    " << polymer << endl;
	for (int r = 0; r < 10; r++) {
		for (int i = 0; i < (int)polymer.length(); i++) {
			char tmp1 = polymer[i];
			string tmp2 = polymer.substr(i, 2);
			char out = mp[tmp2];
			polymerTo.push_back(tmp1);
			polymerTo.push_back(out);
		}
		polymer = polymerTo;
		polymerTo = "";
		//cout << "After step " << r+1 << ":[" << polymer << "]" << endl;
	}

	int count[27] = {0};
	for (int i = 0; i < (int)polymer.length(); i++) {
		count[polymer[i]-65]++;
	}

	int minCount = 99999;
	int maxCount = 0;
	for (int i = 0; i < 26; i++) {
		if (count[i] > maxCount) {maxCount = count[i];}
		if (count[i] < minCount && count[i]!=0) {minCount = count[i];}
	}

	printf("** ans %d (%d-%d)\n", maxCount-minCount, maxCount, minCount);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d \n", maxCount-minCount);

}
