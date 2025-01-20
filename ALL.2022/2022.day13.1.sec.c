#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <iterator>
#include <regex>
#include <iostream>
#include <string>
#include <deque>
#include <bits/stdc++.h>
//vta w...---rer
using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

int compareSQ(vector <string> fir, vector <string> sec);
vector <string> putIntoVectors(string s);

deque <string> Q1, Q2;
int countOrder = 0;
string sA1[1000];
string sA2[1000];

std::string replaceAll(std::string str, const std::string& from, const std::string& to);
std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 13 - 1\n"); fflush(stdout);
	char line1[LINE];

	int leny = 0;
	int first = 1;
	string fir;
	string sec;
	int index = 1;
	int tot = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			first = 1;
			continue;
		} else if (first == 1) {
			first = 0;
			fir = line1;
			continue;
		} else if (first == 0) {
			first = 1;
			sec = line1;
			printf("____________________________\n");
			vector <string> f1 = putIntoVectors(fir);
			vector <string> f2 = putIntoVectors(sec);
			getchar();
			int ret1 = compareSQ(f1, f2);
			if (ret1 < 0) {
				//printf("%d\n", index);
				tot+= index;
			}

			index++;
		}
		leny++;
		//printf("index [%d] tot [%d]\n", index-1, tot);
	}
	fclose(a);

	printf("**ans %d\n", tot);
}

vector <string> putIntoVectors(string s10) //putIntoVectors the input into different vector based on []
{
        string str = s10.substr(1, s10.length()-2);
        int depth = 0;
        string part = "";
        vector <string> allthevecs;

        for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
            //do_things_with(*it);
                if (*it == ']') {
                        depth--;
                } else if (*it == '[') {
                        depth++;
                } else if (*it == ',' && depth == 0) {
                        allthevecs.push_back(part);
                        part.clear();
                }
                if ((*it == ',' && depth != 0) || (*it != ',')) {
                        part.push_back(*it);
                }

        }
        if (part.size() != 0) {allthevecs.push_back(part);}
	int jj = 0;
	for (auto it = allthevecs.begin();  it != allthevecs.end(); it++) {
		cout << jj << ": " << *it << " ";
		jj++;
	}
	getchar();
        return allthevecs;

}

int compareSQ(vector <string> fir, vector <string> sec)
{
	//w[a-z]+r
	for (int kk = 0; kk < (int)min(fir.size(), sec.size()); kk++) //lengths
	{
		if (sec[kk][0] != '[' && fir[kk][0] != '[') {
			if (stoi(fir[kk]) - stoi(sec[kk]) != 0) {
				return atoi(fir[kk].c_str()) - atoi(sec[kk].c_str());
			}
		} else if (sec[kk][0] != '[' && fir[kk][0] == '[') {
			int rV = compareSQ(putIntoVectors(fir[kk]), putIntoVectors("[" + sec[kk] + "]"));
			if (rV != 0) { return rV; }
		} else if (sec[kk][0] == '[' && fir[kk][0] != '[') {
			int rV = compareSQ(putIntoVectors("[" + fir[kk] + "]"), putIntoVectors(sec[kk]));
			if (rV != 0) { return rV; }
		} else if (sec[kk][0] == '[' && sec[kk][0] == '[') {
			int rV = compareSQ(putIntoVectors(fir[kk]), putIntoVectors(sec[kk]));
			if (rV != 0) { return rV; }
		} else {
			perror("Should not be here\n"); exit(0);
		}
	}
	return fir.size() - sec.size();

}
