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

#include <unistd.h>

#define getchar()
using namespace std;

int lenx = 0;
int leny = 0;
int LINE = 1000;

char rules[200][50];
int numRules = 0;
char matches[400][150];
int numMatches = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day19 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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

	string rule0 = rules[0];

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

	int count = 0;
	for (int i = 0; i < numMatches; i++) {
		string match = matches[i];
		if (regex_match(match, regex(rule0))) {
			count++;
		}
	}
	//cout << "rule0 is: " << rule0 << endl;
	cout << "** count is: " << count << endl;

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);
}































/*
	for (int i = 0; i < numRules; i++) {
		int rule1, rule2;
		int ret;
		ret = sscanf(rules[i], "(%d)", &rule1);
		if (ret == 1) {
			if (rule1 == arule || rule1 == brule) {
			}
		}	
		ret = sscanf(rules[i], "(%d %d)", &rule1, &rule2);
		if (ret == 2) {
			if (rule1 == arule || rule1 == brule) {
			
		}
		if (ret == 4) {
		}
		ret = sscanf(rules[i], "(%d %d | %d %d)", &rule1, &rule2, &rule3, &rule4);
	}
*/
/*
	//rule0 = "Example_45-3";
	//rule0 = regex_replace(rule0, regex("[^0-9]*([0-9]+).*"), string("$1"));
	smatch sm;
	while (regex_search(rule0, sm, regex(R"(\d+)"))) { 
		cout << "the matches are: ";
		int intVal = stoi(sm.str());
		cout << "[" << stoi(sm.str()) << "]" << endl;
		//rule0 = sm.suffix();

		//rule0.replace(rule0.find(sm.str()), sizeof(sm.str()) - 1, rules[intVal]);
		//cout << "sizeof is " << sizeof(sm.str()) << endl;
		//cout << "length is " << sm.length() << endl;
		rule0.replace(rule0.find(sm.str()), sm.length(), rules[intVal]);
		//rule0.replace(rule0.begin(), rule0.end(), sm.str(), rules[intVal]);
		cout << "rule0 now: " << rule0 << endl;
		getchar();
	}
	
	//auto it = find_if(rule0.begin(), rule0.end(), ::isdigit);

	do {
		cout << rule0.substr(rule0.find_first_of("0123456789")) << endl;
		getchar();
	} while (find_if(rule0.begin(), rule0.end(), ::isdigit) != rule0.end());
	//printf("numRules is %d\n", numRules);
	//printf("matches is %d\n", numMatches);
*/
/*
		sscanf(line1, "%[^:]: %[^\0]", numS, rest); 
		string rep = rest;
		int qpos1 = rep.find("\"");
		printf("qpos is %d\n", qpos1);
		if (qpos1 != -1) {
			rep.replace(rep.begin() + qpos1, rep.begin() + qpos1+1, "");
			qpos1 = rep.find("\"");
			rep.replace(rep.begin() + qpos1, rep.begin() + qpos1+1, "");
		}
		sprintf(rules[leny], "(%s)", rep.c_str());
*/
/*
	int arule, brule;
	for (int i = 0; i < numRules; i++) {
		//printf("%s\n", rules[i]);
		if (strcmp(rules[i], "(\"a\")") == 0) {
			arule = i;
		} else if (strcmp(rules[i], "(b)") == 0) {
			brule = i;
		}
	}
*/
