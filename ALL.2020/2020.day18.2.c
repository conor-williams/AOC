#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <stack>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <unistd.h>

#include <bigintclass.h>
#include <bigint_function_definitions.h>


using namespace std;

int lenx = 0;
int leny = 0;

int LINE = 1000;

#define GX 200

stack<bigint> st[100];
string firstParseHandlePlus(string lineX);
string firstParseHandleMul(string lineX);

#define getchar()
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("		2020 Day18 Part2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];
	bigint tot = 0;


	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);

		int depth = 0;
		string lineX = line1;
		//cout << "was: " << lineX << endl;
		lineX = firstParseHandlePlus(lineX);
		lineX = firstParseHandleMul(lineX);
		//cout << "now: " << lineX << endl;

		lineX.replace(0, 0, "(");
		lineX.replace(lineX.length()-1, 0, ")");
		strcpy(line1, lineX.c_str());
		int len = (int)strlen(line1);
		printf("line1 is %s\n", line1);
		for (int i = 0; i < len; i++) {
			if (isdigit(line1[i])) {
				st[depth].push((bigint)(line1[i]-48));
				printf("pushing %d\n", line1[i]-48);
			} else if (line1[i] == '+') {
				printf("pushing +(-1)\n");
				st[depth].push(-1);
			} else if (line1[i] == '*') {
				printf("pushing *(-2)\n");
				st[depth].push(-2);
			} else if (line1[i] == '(') {
				depth++;
				printf("new depth...\n");
			} else if (line1[i] == ')' || i==len-1) {
				printf("close brace...depth now %d\n", depth); 
				bigint i1 = st[depth].top();
				st[depth].pop();
				cout << "i1 is " << i1 << endl;
				//printf("end brack i1 is %lld\n", i1);
				if (st[depth].empty()) {printf("depth is empty...\n"); if (depth != 0) {depth--;}st[depth].push(i1); continue;}
				bigint op = st[depth].top();
				st[depth].pop();
				{
					bigint i2 = st[depth].top();
					st[depth].pop();
					if (op == -1) {
						while (!st[depth].empty()) {
							st[depth].pop();
						}
						depth--;
						st[depth].push(i2 + i1);
						printf("push of i2+i1\n");
						cout << i2+i1 << endl;
						printf("depth now %d\n", depth);
					} else if (op == -2) {
						while (!st[depth].empty()) {
							st[depth].pop();
						}
						depth--;
						st[depth].push(i2 * i1);
						printf("mul of i2*i1\n");
						cout << i2*i1 << endl;
						printf("depth now %d\n", depth);
					}
				}
			} else if (line1[i] == ' ') {
				continue;
			}
		}

		tot += st[depth].top();

		cout << st[depth].top() << endl;
		st[depth].pop();
		assert(st[depth].size() == 0);
		//1 + 2 * 3 + 4 * 5 + 6
		leny++;
	}

	//printf("**ans %llu\n", tot);
	cout << "**ans " << tot << endl;
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %s\n", tot.str.c_str());
}

string firstParseHandleMul(string lineX)
{
	//int len = (int)lineX.length();

	string newLine = lineX+lineX;
	newLine = "";
	while (1) {
		auto pluPos = lineX.find("*");
		//int pos = distance(lineX.begin(), plu);
		if (pluPos != string::npos) {
			lineX[pluPos] = '%';
			string left = lineX.substr(0, pluPos);
			reverse(left.begin(), left.end());
			if (isdigit(left[1])) {
				string with;
				with.push_back(left[1]); with.push_back('(');
				left.replace(1, 1, with);
			} else if (left[1] == ')') {
				int numBr = 0;
				int le = left.length();
				for (int i = 1; i < le; i++) {
					if (left[i] == '(') {
						numBr--;
					} else if (left[i] == ')') {
						numBr++;
					}
					if (numBr == 0) {
						string with = "((";
						left.replace(i, 1, with);
						break;
					}
				}
			} else {
				printf("oops\n"); exit(0);
			}
			reverse(left.begin(), left.end());

			string right = lineX.substr(pluPos);
			if (isdigit(right[2])) {
				string with;
				with.push_back(right[2]);
				with.push_back(')');
				right.replace(2, 1, with);
			} else if (right[2] == '(') {
				int numBr = 0;
				int re = right.length();
				for (int i = 2; i < re; i++) {
					if (right[i] == '(') {
						numBr++;
					} else if (right[i] == ')') {
						numBr--;
					}
					if (numBr == 0) {
						string with = "))";
						right.replace(i, 1, with);
						break;
					}
				}
			} else {
				printf("oox2\n"); exit(0);

			}
			getchar();
			lineX = left+right;
		} else {
			break;
		}

	}
	size_t pos;
	do {
		pos = lineX.find('%');
		if (pos != string::npos) {
			lineX.replace(pos, 1, "*");
		}
	} while (pos != string::npos);
	return lineX;
}

string firstParseHandlePlus(string lineX)
{
	//int len = (int)lineX.length();

	string newLine = lineX+lineX;
	newLine = "";
	while (1) {
		auto pluPos = lineX.find("+");
		//int pos = distance(lineX.begin(), plu);
		if (pluPos != string::npos) {
			lineX[pluPos] = '%';
			string left = lineX.substr(0, pluPos);
			reverse(left.begin(), left.end());
			if (isdigit(left[1])) {
				string with;
				with.push_back(left[1]); with.push_back('(');
				left.replace(1, 1, with);
			} else if (left[1] == ')') {
				int numBr = 0;
				int le = left.length();
				for (int i = 1; i < le; i++) {
					if (left[i] == '(') {
						numBr--;
					} else if (left[i] == ')') {
						numBr++;
					}
					if (numBr == 0) {
						string with = "((";
						left.replace(i, 1, with);
						break;
					}
				}
			} else {
				printf("oops\n"); exit(0);
			}
			reverse(left.begin(), left.end());

			string right = lineX.substr(pluPos);
			if (isdigit(right[2])) {
				string with;
				with.push_back(right[2]);
				with.push_back(')');
				right.replace(2, 1, with);
			} else if (right[2] == '(') {
				int numBr = 0;
				int re = right.length();
				for (int i = 2; i < re; i++) {
					if (right[i] == '(') {
						numBr++;
					} else if (right[i] == ')') {
						numBr--;
					}
					if (numBr == 0) {
						string with = "))";
						right.replace(i, 1, with);
						break;
					}
				}
			} else {
				printf("oox2\n"); exit(0);

			}
			getchar();
			lineX = left+right;
		} else {
			break;
		}

	}
	size_t pos;
	do {
		pos = lineX.find('%');
		if (pos != string::npos) {
			lineX.replace(pos, 1, "+");
		}
	} while (pos != string::npos);
	return lineX;
}
