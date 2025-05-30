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

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
int lenx;
int leny;
map <pair<string, string>, int> mp;
map <string, int> mpOne;
int recSearch(string justadded, vector <string> oldList, int numConnected, vector <pair<string, int>>::iterator incomingIt);
int maxNumConnected = 0;
vector <string> maxOldList;
vector <pair <string, int>> A;

void sigfunc(int a) {
	printf("----------\n");
	vector <string> tmpV = maxOldList;
	sort(tmpV.begin(), tmpV.end());
	for (auto st1: tmpV) { cout << st1 << " - "; } cout << endl;
	for (auto st1: tmpV) { cout << st1; } cout <<  endl;
	printf("[[ %d ]]\n", maxNumConnected); 
	printf("----------\n");
}
bool cmp(pair<string, int>& a, pair<string, int>& b);

bool cmp(pair<string, int>& a, pair<string, int>& b)
{
	if(a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

int fd = 0;
int main(int argc, char **argv)
{
	clock_t start, end; double cpu_time_used;
	start = clock();
	//DO
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2024 Day 23 Part 2\n"); fflush(stdout);
	printf("	SLOW ~20seconds\n");

	fflush(stdout); fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
		char fir[10], sec[10];
		sscanf(line1, "%[^-]-%s", fir, sec);

#ifdef _DEBUG_
		printf(" %s --- %s\n", fir, sec);
#endif
		mp[{fir, sec}] = 1;
		mp[{sec, fir}] = 1;
		mpOne[{fir}]++;
		mpOne[{sec}]++;
		leny++;
	}
	fclose(a);

	//printf("cc:(%d)\n", mpOne["cc"]);
	/*
	   for (auto it = mpOne.begin(); it != mpOne.end(); it++) {
	   printf("grep %s i1.txt\n", (*it1).first);
	   }
	 */
	//int count = 0;
	for (auto& it : mpOne) { A.push_back(it); }
	sort(A.begin(), A.end(), cmp);

	//DO
	printf("Main Loop:\n");
	start = clock();
	vector <string> old;
	int numConnected;
	printf("A.size() is %d\n", (int)A.size());
	//printf("A[0].first is %s - %d\n", A[0].first.c_str(), A[0].second);
	for (auto it: A) { if (it.second != 13) {printf("%d\n", it.second);} }
//all are 13
	for (auto it1 = A.begin(); it1 != A.end(); it1++) {
		//cout << (*it1).first << endl;
		if ((*it1).second <= maxNumConnected) {printf("here1"); goto after;} //becuase it is sorted now
		//auto ittmp = it1; ittmp += maxNumConnected; if ((*ittmp).second < maxNumConnected) {goto after;}
		if (distance(it1, A.end()) <= maxNumConnected) {goto after;}
		string st1 = (*it1).first;
		auto it3 = it1; it3++;
		for (auto it2 = it3; it2 != A.end(); it2++) {
			if ((*it2).second <= maxNumConnected) {goto after;}
			if (distance(it2, A.end()) <= maxNumConnected-1) {goto ne2;}
			string st2 = (*it2).first;
			old.clear();
			if (mp.find({st1, st2}) != mp.end()) {
				old.push_back(st1); old.push_back(st2);
				auto it55 = it2; it55++;
				for (auto it10 = it55; it10 != A.end(); it10++) {
					string st10 = (*it10).first;
					if ((*it10).second <= maxNumConnected) {printf("here3"); goto after;}
					numConnected = 2;
					if ((distance(it10, A.end())) <= maxNumConnected-2) {goto ne1;}
					//if (recSearch(st10, old, numConnected, it10) == -2) {goto after;}
					recSearch(st10, old, numConnected, it10);
				}
			}
			continue;
ne1:
			continue;
		}
ne2:
		continue;
	}
after:
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("        time: %f seconds\n", cpu_time_used);

	printf("maxNumConnected %d\n", maxNumConnected);

	sort(maxOldList.begin(), maxOldList.end());

	fflush(stdout); dup2(fd, 1);

	printf("**ans: [ ");
	string ans1;
	for (auto st1: maxOldList) { ans1 += st1 + ","; }
	ans1.pop_back();
	cout << ans1 + " ] " << endl;
}


int recSearch(string justadded, vector <string> oldList, int numConnected, vector <pair<string, int>>::iterator incomingIt) {
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
	for (auto it4 = incomingIt; it4 != A.end(); it4++) {
		//all tricks slow it down
		//if ((*it4).second <= maxNumConnected) {return -2;}
		if ((numConnected + distance(it4, A.end())) <= maxNumConnected) {return -3;}
		//string nextOne = (*it4).first;
		//if (recSearch(nextOne, oldList, numConnected, it4) == -2) {return -2;}
		recSearch((*it4).first, oldList, numConnected, it4);
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
/*
   for (auto it1 = mpOne.begin(); it1 != mpOne.end(); it1++) {
   cout << (*it1).first << endl;
   if ((*it1).second <= maxNumConnected) {goto after;}
   if (distance(it1, mpOne.end()) <= maxNumConnected) {goto after;}
   string st1 = (*it1).first;
   auto it3 = it1; it3++;
   for (auto it2 = it3; it2 != mpOne.end(); it2++) {
   if ((*it2).second <= maxNumConnected) {break;}
   if (distance(it2, mpOne.end()) <= maxNumConnected-1) {goto after;}
   string st2 = (*it2).first;
   old.clear();
   if (mp.find({st1, st2}) != mp.end()) {
   old.push_back(st1); old.push_back(st2);
   auto it55 = it2; it55++;
   for (auto it10 = it55; it10 != mpOne.end(); it10++) {
   if ((*it10).second <= maxNumConnected) {goto after;}
   string st10 = (*it10).first;
   numConnected = 2;
   if ((distance(it10, mpOne.end())) <= maxNumConnected-2) {break;}
   if (recSearch(st10, old, numConnected, it10) != -1) {}
   }
   }
   }
   }
 */
