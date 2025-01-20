#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>

#include <unistd.h>

#define getchar()
#include <unistd.h>

using namespace std;
#define _DEBUG_
vector <int> ve2[30];
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day7.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int SIZE = 1000; char line1[SIZE];

	//Step J must be finished before step H can begin.
	int leny = 0;

	while (1)
	{
		fgets(line1, SIZE, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		char F, T;
		sscanf(line1, "Step %c must be finished before step %c can begin.", &F, &T);
		ve2[T-65].push_back(F-65);
		leny++;
	}

	vector <int> pas;
	vector <int> ans;
ag: //one letter at a time - lowest letter first - a topological sort
	for (int i = 0; i < 26; i++) {
		if ((int)ve2[i].size() == 0 && find(pas.begin(), pas.end(), i) == pas.end()) {
			if (find(ans.begin(), ans.end(), i) == ans.end()) {ans.push_back(i);}
		}
	}

	sort(ans.begin(), ans.end());
	int found = 0;
	auto first = ans.begin();
	int onelet = *first;
	ans.erase(first);
       	{
		printf("for removal: %c ", onelet+65);
		pas.push_back(onelet);
		for (int i = 0; i < 26; i++) {
			vector <int>::iterator it;
			if ((it = find(ve2[i].begin(), ve2[i].end(), onelet)) == ve2[i].end()) {
				//ok
			} else {
				if (found == 0) {found = 1;}
				printf("in %c -- was looking %c - removing %c\n", i+65, onelet+65, (*it)+65);
				ve2[i].erase(it);
			}
		}
	}
	printf("pas now: "); for (auto ii: pas) { printf("%c", ii+65);} printf("\n");

	if (found == 1) {
		goto ag;
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	for (auto ii: pas) {
		printf("%c", ii+65);
	}
	printf("\n");

}









	/*
	printf("ansBef: ");
	for (auto bb: ans) {
		printf(" %c ", bb+65);
	}
	printf("erase first %c\n", *first);
	ans.erase(first);
	printf("ansNow: ");
	for (auto bb: ans) {
		printf(" %c ", bb+65);
	}
	printf("\n");
	*/
	/*
	for (int i = 0; i < 26; i++) {
		int b = (int)ve2[i].size();
		sort (ve2[i].begin(), ve2[i].end());
		auto it = unique(ve2[i].begin(), ve2[i].end());
		ve2[i].resize(distance(ve2[i].begin(), it));
		int a = (int)ve2[i].size();
		assert(b - a == 0);
	}
	*/
