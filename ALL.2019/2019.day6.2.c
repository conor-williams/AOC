#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>

//#define getchar()
using namespace std;

int lenx, leny;
#define DAY "		2019 day6 part2\n"
#define _DEBUG_
int fd;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);

	fflush(stdout); fd = dup(1);// close(1);
	char line1[20];

	map<string, string> mp;
	while(1) {
		fgets(line1, 19, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';

		char l[5]; char r[5];
		sscanf(line1, "%[^)])%s\n", l, r);
		mp[r] = l;

		leny++;
	}
	fclose(a);

	int totOrbits = 0;
	string key1 = "YOU";
	int orbYOU = 1;
	vector <string> stepsYOU;
	{
		string left = mp[key1];
		while (left.compare("COM") != 0) {
			stepsYOU.push_back(left);
			orbYOU++;
			left = mp[left];
		}
	}

	string key2 = "SAN";
	vector <string> stepsSAN;
	int orbSAN = 1;
	{
		string left = mp[key2];
		while (left.compare("COM") != 0) {
			stepsSAN.push_back(left);
			orbSAN++;
			left = mp[left];
		}
	}

	sort(stepsSAN.begin(), stepsSAN.end());
    	sort(stepsYOU.begin(), stepsYOU.end());

	vector<string> result;
    	set_intersection(stepsSAN.begin(), stepsSAN.end(),
                          stepsYOU.begin(), stepsYOU.end(),
                          back_inserter(result));
	int max = 0;
	string maxInter;
	for (int ii = 0; ii <result.size(); ii++) {
		if (result[ii] == "COM") {continue;}
		int orbits = 1;
		string left = mp[result[ii]];
		while (left != "COM") {
			orbits++;
			left = mp[left];
		}
		if (orbits > max) {max = orbits; maxInter = result[ii];}

	}
	string common = maxInter;
	int orbCommon = 1;
	{
		string left = mp[common];
		while (left.compare("COM") != 0) {
			orbCommon++;
			left = mp[left];
		}
	}
	int totPath = orbSAN -1 - orbCommon + orbYOU -1 - orbCommon;
	printf("**ans: ");
	printf("%d", totPath);
	printf("\n");

}
