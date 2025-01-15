#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <unistd.h>
//#define assert(asf)
#define getchar()
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;
int count1 = 0;
int count2 = 0;
int countthemGroup1(string s1);
int countthemGroup2(string s1);
map <string, vector<string>> mp;
map <string, vector<string>> mpBoth;
struct hash_function
{
	size_t operator()(const tuple<int , int , int, int>&x) const
	{
		unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
	}
};

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
map <string, int> group1;
map <string, int> group2;
void addit(string one, string two);
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
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); if (a == NULL) {printf("BAD file %s\n", argv[1]); exit(0);}
	//printf("2023 Day 1 Part 1\n"); fflush(stdout);

	//fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	char fir1[20];
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		char * fir = strtok(line1, ":");
		strcpy(fir1, fir);
		fir = strtok(NULL, ":");
		char *sec = strtok(fir, " \0");
		vector <string> ve;
		do {
			ve.push_back(sec);	
		} while ((sec = strtok(NULL, " \0")) != NULL);
		mp[fir1] = ve;
		leny++;
	}
	fclose(a);

	mpBoth = mp;
	
	for (auto it = mp.begin(); it != mp.end(); it++) {
		for (auto itv = (*it).second.begin(); itv != (*it).second.end(); itv++) {
			addit(*itv, (*it).first);
		}
	}

	if (argc != 8) {
		printf("need the splits run eg: ./xyz input.txt hhj sck  abc def  ijk lmn\n");
		exit(0);
	}
	char splits[7][10];
	strcpy(splits[0], argv[2]);
	strcpy(splits[1], argv[3]);
	strcpy(splits[2], argv[4]);
	strcpy(splits[3], argv[5]);
	strcpy(splits[4], argv[6]);
	strcpy(splits[5], argv[7]);

	for (int kk = 0; kk < 6; kk+=2) {
		if (mp.find(splits[kk]) != mp.end()) {
			vector <string> ve3 = mp[splits[kk]];
			vector <string>::iterator it4;
			if ((it4 = find(ve3.begin(), ve3.end(), splits[kk+1])) != ve3.end()) {
				printf("erasing %s\n", (*it4).c_str());
				ve3.erase(it4);
			} else {
				printf("not found %s\n", splits[kk+1]);
			}
			mp[splits[kk]] = ve3;
		} else {
			printf("not found..%s.\n", splits[kk]);
		}

		if (mpBoth.find(splits[kk]) != mpBoth.end()) {
			vector <string> ve3 = mpBoth[splits[kk]];
			vector <string>::iterator it4;
			if ((it4 = find(ve3.begin(), ve3.end(), splits[kk+1])) != ve3.end()) {
				printf("erasingin mpBoth %s\n", (*it4).c_str());
				ve3.erase(it4);
			} else {
				printf("not found %s\n", splits[kk+1]);
			}
			mpBoth[splits[kk]] = ve3;
		} else {
			printf("not found..%s.\n", splits[kk]);
		}
	}

	char splits2[7][10];
	strcpy(splits2[0], argv[3]);
	strcpy(splits2[1], argv[2]);
	strcpy(splits2[2], argv[5]);
	strcpy(splits2[3], argv[4]);
	strcpy(splits2[4], argv[7]);
	strcpy(splits2[5], argv[6]);

	for (int kk = 0; kk < 6; kk+=2) {
		if (mp.find(splits2[kk]) != mp.end()) {
			vector <string> ve3 = mp[splits2[kk]];
			vector <string>::iterator it4;
			if ((it4 = find(ve3.begin(), ve3.end(), splits2[kk+1])) != ve3.end()) {
				printf("erasing %s\n", (*it4).c_str());
				ve3.erase(it4);
			} else {
				printf("not found %s\n", splits[kk+1]);
			}
			mp[splits2[kk]] = ve3;
		} else {
			printf("not found..%s.\n", splits2[kk]);
		}
		if (mpBoth.find(splits2[kk]) != mpBoth.end()) {
			vector <string> ve3 = mpBoth[splits2[kk]];
			vector <string>::iterator it4;
			if ((it4 = find(ve3.begin(), ve3.end(), splits2[kk+1])) != ve3.end()) {
				printf("erasing in mpBoth %s\n", (*it4).c_str());
				ve3.erase(it4);
			} else {
				printf("not found %s\n", splits[kk+1]);
			}
			mpBoth[splits2[kk]] = ve3;
		} else {
			printf("not found..%s.\n", splits2[kk]);
		}
	}


	auto it = mpBoth.begin();
	printf("*it.first.c_str() is %s\n", (*it).first.c_str());
	group1[(*it).first] = 1;
	countthemGroup1((*it).first);
	printf("group1 .size == %d\n", (int)group1.size());

	for (auto it4 = mpBoth.begin(); it4 != mpBoth.end(); it4++) {
		countthemGroup2((*it4).first);
	}
	printf("group2 .size == %d\n", (int)group2.size());
	printf("**ans: %d\n", (int)((int)group1.size() * (int)group2.size()));
	int check = (int)((int)group1.size() + (int)group2.size()) - (int)mpBoth.size();
	assert(check == 0);

	/*
	for (int i = 0; i < 900; i++) {
		for (int j = 0; j < 900; j++) {
			if (j*i == 583338) {printf("58338: %d * %d\n", i, j);}
		}
	}
	*/
	/*
	for (auto it = mp.begin(); it!= mp.end(); it++) {
		group1[(*it).first] = 1;
		countthem((*it).first);
	}
	*/
	//leave in gen of output
	//fflush(stdout); dup2(fd, 1);
}

void addit(string one, string two) {
	
	if (mpBoth.find(one) == mpBoth.end()) {
		vector <string> ve77;
		ve77.push_back(two);
		mpBoth[one] = ve77;
	} else {
		vector <string> ve88 = mpBoth[one];
		if (find(ve88.begin(), ve88.end(), two) == ve88.end()) {
			ve88.push_back(two);
			mpBoth[one] = ve88;
		}
	}

}
int countthemGroup2(string s1) {
	auto it = mpBoth.find(s1);
	if (it != mpBoth.end()) 
	{
		vector <string> ve2 = (*it).second;	
		for (auto it2 = ve2.begin(); it2!= ve2.end(); it2++) {
			//printf("%s %s\n", (*it).first.c_str(), (*it2).c_str());
			if (group1.find(*it2) == group1.end()) {
				if (group2.find(*it2) == group2.end()) { 
					group2[*it2] = 1;
					countthemGroup2((*it2));
				}
			}
		}
	}	
}
int countthemGroup1(string s1) {
	auto it = mpBoth.find(s1);
	if (it != mpBoth.end()) 
	{
		vector <string> ve2 = (*it).second;	
		for (auto it2 = ve2.begin(); it2!= ve2.end(); it2++) {
			//printf("%s %s\n", (*it).first.c_str(), (*it2).c_str());
			if (group1.find(*it2) == group1.end()) {
				group1[*it2] = 1;
				countthemGroup1((*it2));
			}
		}
	}	
}
