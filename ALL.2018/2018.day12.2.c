#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>

#include <vector>
#include <map>
#include <unistd.h>

#define getchar()
using namespace std;

#undef _DEBUG_
#define SIZE 200
char line1[SIZE];
long tot = 0;
struct plant_s {
	char from[6];
	char to;
};

struct plant_s plant[200];


struct nn_s {
	char from[100];
	char to[4300];
};
struct nn_s nn[1000000];
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day12.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1);// close(1);
	string initial = "";
	int leny = 0;
	map <string, char> mp;
	char initial3[SIZE];
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[(int)strlen(line1)-1] = '\0';
		int ret = 0;
		ret = sscanf(line1, "initial state: %s", initial3);
		initial = initial3;
		if (ret == 1) {continue;}
		if ((int)strlen(line1) == 0) {
			continue;
		}
		sscanf(line1, "%s => %c", plant[leny].from, &plant[leny].to);
		mp[plant[leny].from] = plant[leny].to;
		leny++;
	}
	fclose(a);

	int theZero = 400;
	string dots(theZero, '.');
	initial = dots + initial;
	initial = initial + dots;

	//string dots = ".".repeat(6);
	vector <string> repeatChecker;
	int repeatStart = 0;
	for (int ii = 0; ii < 200; ii++) {
		int ind1 = initial.find_first_of('#');
		int ind2 = initial.find_last_of('#')+1;

		if (find(repeatChecker.begin(), repeatChecker.end(), initial.substr(ind1, ind2-ind1)) != repeatChecker.end()) {
			auto it = find(repeatChecker.begin(), repeatChecker.end(), initial.substr(ind1, ind2-ind1));
			repeatStart = it - repeatChecker.begin();
			break;

		}
		repeatChecker.push_back(initial.substr(ind1, ind2-ind1));
		//initial = dots + initial.substring(ind1, ind2) + dots;


		string tmp1((int)initial.length()+10, '.');

		for (int kk = 0; kk < (int)initial.length()-4; kk++) {
			string sub1 = initial.substr(kk, kk+5-kk);
			char to = '.';

			if (mp.find(sub1) != mp.end()) {
				to = mp[sub1];
			}
			tmp1[kk+2] = to;
		}
		initial = tmp1; 
	}

	int counthash = 0;
	for (int jj = 0; jj < (int)initial.length(); jj++) {
		if (initial[jj] == '#') {
			counthash++;
		}
	}

	long num = 50000000000L - repeatStart-1;
	long tot = 0;
	for (int ii = 0; ii < (int)initial.length(); ii++) {
		if (initial[ii] == '#') {
			tot += ii-theZero;
		}
	}



	printf("**ans: ");
	printf("%ld\n", (tot + (num*counthash)));
}
