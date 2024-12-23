#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <time.h>
#include <algorithm>

using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
int lenx;
int leny;
map <pair<string, string>, int> mp;
map <string, int> mpOne;
int recSearch(string justadded, vector <string> oldList, int numConnected, map <string, int>::iterator incomingIt);
int maxNumConnected = 0;
vector <string> maxOldList;
void sigfunc(int a) {
	printf("----------\n");
	vector <string> tmpV = maxOldList;
	sort(tmpV.begin(), tmpV.end());
	for (auto st1: tmpV) { cout << st1 << " - "; } cout << endl;
	for (auto st1: tmpV) { cout << st1; } cout <<  endl;
	printf("[[ %d ]]\n", maxNumConnected); 
	printf("----------\n");
}
int main(int argc, char **argv)
{
        clock_t start, end; double cpu_time_used;
        start = clock();
        //DO
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("        time: %f seconds\n", cpu_time_used);

        //signal(SIGTSTP, &sigfunc);
        signal(SIGQUIT, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 23 Part 2\n"); fflush(stdout);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	char fir[10], sec[10];
	sscanf(line1, "%[^-]-%s", fir, sec);
	printf(" %s --- %s\n", fir, sec);
	mp[{fir, sec}] = 1;
	mp[{sec, fir}] = 1;
	mpOne[{fir}]++;
	mpOne[{sec}]++;
	leny++;
}
fclose(a);

/*
	for (auto it = mpOne.begin(); it != mpOne.end(); it++) {
		printf("grep %s i1.txt\n", (*it1).first);
	}
*/
	//int count = 0;
        start = clock();
        //DO
	printf("Main Loop:\n");
	vector <string> old;
	int numConnected = 2;
	for (auto it1 = mpOne.begin(); it1 != mpOne.end(); it1++) {
		if (distance(it1, mpOne.end()) <= maxNumConnected) {break;}
		string st1 = (*it1).first;
		auto it3 = it1; it3++;
		for (auto it2 = it3; it2 != mpOne.end(); it2++) {
			string st2 = (*it2).first;
			old.clear();
			if (distance(it2, mpOne.end()) <= maxNumConnected-1) {break;}
			if (mp.find({st1, st2}) != mp.end()) {
				old.push_back(st1); old.push_back(st2);
				auto it55 = it2; it55++;
				for (auto it10 = it55; it10 != mpOne.end(); it10++) {
					numConnected = 2;
					if ((distance(it10, mpOne.end())) <= maxNumConnected-2) {break;}
					if (recSearch((*it10).first, old, numConnected, it10) != -1) {}
				}
			}
		}
	}
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("        time: %f seconds\n", cpu_time_used);

	printf("maxNumConnected %d\n", maxNumConnected);

	sort(maxOldList.begin(), maxOldList.end());

	printf("**ans: [ ");
	string ans1;
	for (auto st1: maxOldList) { ans1 += st1 + ","; }
	ans1.pop_back();
	cout << ans1 + " ] " << endl;
}


int recSearch(string justadded, vector <string> oldList, int numConnected, map <string, int>::iterator incomingIt) {
	//if ((numConnected + distance(incomingIt, mpOne.end())) <= maxNumConnected) {return -1;} //slows it here
	for (auto st1: oldList) {
		if (mp.find({justadded, st1}) == mp.end()) {
			return -1;
		}
	}
	oldList.push_back(justadded);
	numConnected++;
	if (numConnected > maxNumConnected) {maxOldList = oldList; maxNumConnected = numConnected;}

	incomingIt++;
	for (auto it4 = incomingIt; it4 != mpOne.end(); it4++) {
		string nextOne = (*it4).first;
		recSearch(nextOne, oldList, numConnected, it4);
	}
	return 0;
}






		//if ((numConnected + distance(it4, mpOne.end())) < maxNumConnected) {level--;return -1;}















/*
				for (auto it3 = it2; it3 != mpOne.end(); it3++) {
					if (it1 == it3) {continue;} if (it2 == it3) {continue;}
					string st3 = (*it3).first;
					if (mp.find({st1, st3}) != mp.end() && mp.find({st2, st3}) != mp.end()) {
						if (st1[0] == 't' || st2[0] == 't' || st3[0] == 't') {
							count++;
#ifdef _DEBUG_
							printf("%s %s %s\n", st1.c_str(), st2.c_str(), st3.c_str()); 
#endif
						}
					}
*/
//		if (recSearch(nextOne, oldList, numConnected, it4) == -1) {continue;}
/*
		if (find(oldList.begin(), oldList.end(), nextOne) == oldList.end()) {
			if (recSearch(nextOne, oldList, numConnected, it4) == -1) {continue;}
				auto itt = find(oldList.begin(), oldList.end(), nextOne);
				if (itt != oldList.end()) {
					oldList.erase(itt);
				}
		} else {
			//already there
			continue;
		}
*/
