#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;

int lenx = 0;
int leny = 0;
int LINE = 1000;

char rules[200][50];
int numRules = 0;
char matches[400][150];
int numMatches = 0;
string getTheRule(string rule0);
int main(int argc, char **argv)
{
	//	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("		2020 Day19 Part2\n"); fflush(stdout);
	printf("SLOW ~24 seconds\n");
	char line1[LINE];


	/*
0: 1 2
1: "a"
2: 1 3 | 3 1
3: "b"

aab
aba
*/

	int readingRules = 1;
	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);
		if (readingRules == 1 && line1[0] == '\0') {
			readingRules = 0;
			numRules = leny;
			leny = 0;
			continue;
		} else if (readingRules == 1) {
			char numS[10], rest[20];
			sscanf(line1, "%[^:]: %[^\0]", numS, rest); 
			int ruleNum = atoi(numS);
			sprintf(rules[ruleNum], "(%s)", rest);
		} else {
			strcpy(matches[leny], line1);
		}

		leny++;
	}
	numMatches = leny;

	string rule0 = rules[42];
	string rule42 = getTheRule(rule0);
	//cout << "rule42: " << rule42 << endl;
	rule0 = rules[31];
	string rule31 = getTheRule(rule0);
	//cout << "rule31: " << rule31 << endl;

	strcpy(rules[8], "(FOURTYTWOEIGHT)");
	strcpy(rules[11], "(FOURTYTWOELEVEN THIRTYONE)");
	rule0 = rules[0];
	//cout << "rule0 is " << rule0 << endl;
	rule0 = getTheRule(rule0);
	//cout << "rule0@end" << rule0 << endl;

	string rule0Orig = rule0;
	int count = 0;
	for (int ii = 1; ii < 6; ii++) {//42.8
		rule0 = rule0Orig;
		//cout << "rule0 is " << rule0 << endl;
		string rrii;
		for (int zz = 0; zz<ii; zz++) {
			rrii += rule42;
		}
		//cout << "rrii " << rrii << endl;
		string wat1 = "FOURTYTWOEIGHT";
		int pos = rule0.find(wat1);
		rule0.replace(pos, wat1.length(), rrii);
		//cout << "rule0 is level1" << rule0 << endl;
		string rule0tmp = rule0;
		for (int jj = 1; jj < 6; jj++) {//42.11
			rule0 = rule0tmp;
			string rrjj;
			for (int zz = 0; zz<jj; zz++) {
				rrjj += rule42;
			}
			string wat2 = "FOURTYTWOELEVEN";
			int pos = rule0.find(wat2);
			rule0.replace(pos, wat2.length(), rrjj);
			//cout << "rule0 is level2" << rule0 << endl;

			int kk = jj;
			{//31.11
				string rrkk;
				for (int zz = 0; zz<kk; zz++) {
					rrkk += rule31;
				}
				string wat3 = "THIRTYONE";
				int pos = rule0.find(wat3);
				rule0.replace(pos, wat3.length(), rrkk);
				//cout << "rule0 is level3" << rule0 << endl;
				{
					for (int i = 0; i < numMatches; i++) {
						string match = matches[i];
						if (matches[i][0] != 'Q') {
							if (regex_match(match, regex(rule0))) {
								matches[i][0] = 'Q';
								count++;
							}
						}
					}
				}
			}
		}
	}
	//cout << "** count is: " << count << endl;
	printf("**ans: %d\n", count);
}

string getTheRule(string rule0) 
{
	smatch sm;
	while (regex_search(rule0, sm, regex(R"(\d+)"))) { 
		int intVal = stoi(sm.str());
		rule0.replace(rule0.find(sm.str()), sm.length(), rules[intVal]);
	}
	while (regex_search(rule0, sm, regex(R"(\(\"a\"\))"))) { 
		rule0.replace(rule0.find(sm.str()), sm.length(), "a");
	}
	while (regex_search(rule0, sm, regex(R"(\(\"b\"\))"))) { 
		rule0.replace(rule0.find(sm.str()), sm.length(), "b");
	}
	while (regex_search(rule0, sm, regex(R"( )"))) { 
		rule0.replace(rule0.find(sm.str()), sm.length(), "");
	}
	return rule0;
}

