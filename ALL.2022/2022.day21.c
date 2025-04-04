#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <map>
#include <iostream>

using namespace std;
map <string, pair<string, int>> mp;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

struct inst_s {
	char s1[20];
	char s2[10000];
	char s3[10000];
	char op;
	long long num1;
};
struct inst_s inst[2000];

string doCalc(string ch);
long long hasOp(string ch);
long long alldigitsAndOp(string ch); 
long long alldigits(string ch); 

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 21 part1\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	long long leny = 0;
	//long long instr = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		//char s1[20], s2[20], s3[20];
		char rest[100];
		//char rest2[120];
		long long ret;//, num1;
			      //ret = sscanf(line1, "%s: %s %c %s", inst[leny].s1, inst[leny].s2, inst[leny].op, inst[leny].s3);
		ret = sscanf(line1, "%[^:]:%[^\0]", inst[leny].s1, rest);
		printf("ret is %lld\n", ret);
		//sprintf(rest2, "( %s)", rest); //string re = rest2; //if (strcmp(inst[leny].s1, "root") == 0) {first = leny;}
		mp[inst[leny].s1] = make_pair(rest, 0);

		//assert(ret == 2);
		leny++;
	}
	fclose(a);

again:
	for (auto it = mp.begin(); it != mp.end(); it++) {
		if (it->second.second==0 && alldigitsAndOp(it->second.first) == 1 && hasOp(it->second.first)) {
			//printf("calling doCalc\n");
			it->second.first = doCalc(it->second.first);
		} else if (it->second.second == 0 && alldigits(it->second.first)) {
			for (auto it2 = mp.begin(); it2 != mp.end(); it2++) {
				long long ind = 0;
				if ((ind = it2->second.first.find(it->first)) != -1 ) {
					it2->second.first.replace(ind, 4, it->second.first);
					it->second.second = 1;
					break;
				}
			}
		}
	}
	if (alldigits(mp["root"].first)) { 
		//cout << "not going again" << endl;
		fflush(stdout); dup2(fd, 1);
		cout << "**ans: " << mp["root"].first << endl;
		exit(0);
		//getchar();
	} else {
		//cout << "interim ans: " << mp["root"].first << endl;
		goto again;
	}

}
string doCalc(string ch) {
	char blah[100];
	strcpy(blah, ch.c_str());
	long long num1, num2; char op;

	long long ret = sscanf(blah, "%lld %c %lld", &num1, &op, &num2);
	if (ret != 3) {
		return "-99";
		//printf("err:%s\n", blah); exit(0);
	}
	long long ans = 0;
	switch (op) {
		case '+':
			ans = num1 + num2;
			break;
		case '-':
			ans = num1 - num2;
			break;
		case '*':
			ans = num1 * num2;
			break;
		case '/':
			ans = num1 / num2;
			break;
	}
	printf("tmp)ans is %lld\n", ans);
	char anS[100];
	sprintf(anS, "%lld", ans);
	string an = anS;
	return an;
}

long long hasOp(string ch) 
{
	long long found = 0;
	for (long long i = 0; i < (long long)ch.length(); i++) {
		if (ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/') {
			found = 1;
			break;
		}
	}
	return found;
}



long long alldigitsAndOp(string ch) 
{
	long long found = 1;
	for (long long i = 0; i < (long long)ch.length(); i++) {

		if (ch[i] == ' ' || (ch[i]>='0' && ch[i] <= '9') || ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/') {
			//ok
		} else {
			found = 0;
			break;
		}
	}
	return found;
}

long long alldigits(string ch) 
{
	long long found = 1;
	for (long long i = 0; i < (long long)ch.length(); i++) {
		if (ch[i] == ' ' || ch[i] == '-' || (ch[i] >= '0' && ch[i] <= '9')) {
			//ok
		} else {
			found = 0;
			break;
		}
	}
	return found;
}
