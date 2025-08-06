#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <unistd.h>
#include <set>

#define getchar()
using namespace std;
#define SIZE 500
char line1[SIZE];

map <string, vector<string>> mpAft;
map <string, vector<string>> mpBef;
map <string, int> mpVals;
set <string> seElems;
set <string> under;

int calcAllUnder(string xx2);
int calcAllUnder2(string xx2);
int calc2(string xx2);

int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2017 Day7.2\n"); fflush(stdout);
	int fd = dup(1);// close(1);

	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//yjmbbu (75)
		//zdhvqrl (40) -> fpbsu, fwpfjjd, viqhfi

		string l1 = line1;
		if (l1.find("->") != -1) {

			char restC[100];
			int value;
			char elemC[20];
			sscanf(line1, "%s (%d) -> %[^\0]\0", elemC, &value, restC);
			string elem = elemC;

			vector <string> ve;
			char *ne = strtok(restC, "	 ,");
			while (ne != NULL) {
				ve.push_back(ne);
				vector <string> ve2;
				if (mpBef.find(ne) != mpBef.end()) {
					ve2 = mpBef[ne];
				}
				if (find(ve2.begin(), ve2.end(), elem) != ve2.end()) {
					ve2.push_back(elem);
				}
				mpBef[ne] = ve2;
				ne = strtok(NULL, "	 ,");

			}
			mpAft[elem] = ve;
			mpVals[elem] = value;
			seElems.insert(elem);
		} else {
			char elem[20];
			int value;
			sscanf(line1, "%s (%d)", elem, &value);

			vector <string> ve;
			mpAft[elem] = ve;
			mpVals[elem] = value;
			seElems.insert(elem);
		}


	}
	fclose(a);
	///////////////////
	///
	///
	///

	string root = "";
	for (string elem: seElems) {
		if (mpBef.find(elem) == mpBef.end()) {
			root = elem;
			break;
		}
	}

	int ans22 = 0;
	{
		auto ve1 = mpAft[root];
		int xx[ve1.size()];
		for (int ii = 0; ii < ve1.size(); ii++) {
			xx[ii] = calcAllUnder(ve1[ii]);
		}
		sort(xx, xx+ve1.size());

		int dif = 0;
		int actualVal = 0;
		int shouldBe = 0;
		string actual = "";
		if (xx[0] - xx[1] != 0) {
			actualVal = xx[0];
			shouldBe = xx[1];
			dif = xx[1] - xx[0];
		} else {
			actualVal = xx[ve1.size()-1];
			shouldBe = xx[ve1.size()-2];
			dif = xx[ve1.size()-2] - xx[ve1.size()-1];

		}

		for (int ii = 0; ii < ve1.size(); ii++) {
			int tmp1 = calcAllUnder2(ve1[ii]);
			if (tmp1 == actualVal) {
				actual = ve1[ii];
				break;
			}
		}
		map<string, int> mpValOrig = mpVals;
		for (string ss: under) {
			mpVals = mpValOrig;
			mpVals[ss] = mpVals[ss]+dif;
			if (calc2(actual) == shouldBe) {
				ans22 = mpVals[ss];
				goto after;
			}
		}
	}
after:

	printf("**ans: %d\n", ans22);
}

int calc2(string xx2) {
	int tot = 0;
	tot += mpVals[xx2];
	vector <string> und = mpAft[xx2];

	int yy[und.size()];
	for (int ii = 0; ii < und.size(); ii++) {
		int vv = calc2(und[ii]);
		yy[ii] = vv;
		tot += vv;
	}
	if (und.size() > 0) {
		for (int ii = 0; ii < und.size()-1; ii++) {
			if (yy[ii] != yy[ii+1]) {
				return -1000;
			}
		}
	}
	return tot;
}

int calcAllUnder2(string xx2) {
	int tot = 0;
	tot += mpVals[xx2];
	vector <string> und = mpAft[xx2];

	for (int ii = 0; ii < und.size(); ii++) {
		tot += calcAllUnder2(und[ii]);
	}
	return tot;
}
int calcAllUnder(string xx2) {
	int tot = 0;
	tot += mpVals[xx2];
	under.insert(xx2);
	vector <string> und = mpAft[xx2];

	for (int ii = 0; ii < und.size(); ii++) {
		under.insert(und[ii]);
		tot += calcAllUnder(und[ii]);
	}
	return tot;
}


/////////////////////


