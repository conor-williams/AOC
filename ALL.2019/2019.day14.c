#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <unordered_map>
#include <unistd.h>
#include <vector>
#define getchar()
using namespace std;

#define getchar()
int lenx, leny;
#define DAY "		2019 day14 part1\n"
#define _DEBUG_

struct Fnode {
	char to[100];
	double toCost;
	char from[300][100];
	double fromCost[300];
	double oreSize;
	double rhsSize;
	int numNodes;
};

unordered_map<string, struct Fnode> mp;
int search(char *start, double startCost, char *end);
unordered_map <string, double> mpingred;
unordered_map <string, double> mpspare;

#define SIZEL 400
int fd;
int main(int argc, char **argv)
{

	lenx = 0; leny = 0;
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[SIZEL];

	//2 JNLZG => 7 SJTKF
	map <string, vector<pair <double, string>>> mp;
	map <string, int> mpRound;
	map <string, double> mpSpare;
	map <string, pair <int, int>> mpOre;
	while(1) {
		fgets(line1, SIZEL-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		printf("LINE: [%s]\n", line1);
#endif
		char f[300]; char t[100]; int toCost;
		sscanf(line1, "%[^=]=> %d %s", f, &toCost, t);
		int rsize = toCost;
		string relem = t;
		mpRound[relem] = rsize;
		mpSpare[relem] = 0.0;

		vector <pair<double, string>> var_elems;
		char * tokker = strtok(f, " ");
		while (tokker != NULL) {
			string tmp1 = tokker;

			double dou = stod(tmp1)/(double)rsize;
			tokker = strtok(NULL, " ");

			string wat = tokker;
			if (wat[wat.length()-1] == ',') {
				wat = wat.substr(0, wat.length()-1);
			}
			var_elems.push_back(make_pair(dou, wat));
			if (wat == "ORE") {
				mpOre[relem] = make_pair(rsize, atoi(tmp1.c_str()));
			}
			tokker = strtok(NULL, " ");
		}
		mp[relem] = var_elems;

	}
	fclose(a);

	auto list = mp["FUEL"];
	int go = 1;

	map <string, double> mpTot;
	do {
		vector <pair <double, string>> ve1;
		for (int ii = 0; ii < (int)list.size(); ii++) {
			auto tu1 = list[ii];
			if (tu1.second == "ORE") {
				ve1.push_back(tu1);
			} else {
				mpTot[tu1.second] += tu1.first;
				double was = tu1.first;
				if (mpSpare[tu1.second] >= tu1.first) {
					mpSpare[tu1.second] -= tu1.first;
					tu1.first = 0.0;
				} else {
					for (int zzz = 1; ;zzz++) {
						if ((double)tu1.first <= ((double)zzz * (double)mpRound[tu1.second])+mpSpare[tu1.second]) {
							tu1.first = ((double)zzz * (double)mpRound[tu1.second]);

							if (was-tu1.first > 0) {
								mpSpare[tu1.second] += tu1.first-was; 
							} else {
								mpSpare[tu1.second] += tu1.first -was;
							}
							break;
						}
					}

					auto ve2 = mp[tu1.second];
					for (int kkk = 0; kkk < (int)ve2.size(); kkk++) {
						auto tu2 = ve2[kkk];
						double do2 = tu2.first;
						string el2 = tu2.second;
						do2 *= tu1.first;
						ve1.push_back(make_pair(do2, el2));
					}
				}
			}
		}
		list = ve1;
		int found = 0;
		for (int ii = 0; ii < (int)list.size(); ii++) {
			auto li2 = list[ii];
			if (li2.second != "ORE") {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			go = 0;
		}

	} while (go == 1);
	double sum = 0.0;
	printf("ALL ore");
	for (int ii = 0; ii < (int)list.size(); ii++) {
		auto li2 = list[ii];
		sum += li2.first;
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	printf("%d\n", (int)round(sum));

}
