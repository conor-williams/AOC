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
void countthemGroup1(string s1);
void countthemGroup2(string s1);
unordered_map <string, vector<string>> mp;
unordered_map <string, vector<string>> mpBoth;
unordered_map <string, vector<string>> mpBothTmp;
unordered_map <string, vector<string>> mpBothOrig;
map <pair<string, string>, int> mpValid;
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
int countCCC = 0;
int countDD = 0;
void sigfunc(int a) { printf("countCCC: [[ %d ]] countDD: [ %d ]\n", countCCC, countDD); }
int lenx;
int leny;
unordered_map <string, int> group1;
unordered_map <string, int> group2;
void addit(string one, string two);
int removeRule(string Rone, string Rtwo);
void checkAnswers();
clock_t startMain, endMain;
int checkRule(string Rone, string Rtwo);
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
	printf("2023 Day 25 Part 1 (bruteforce)\n"); fflush(stdout);

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
			mpValid[{fir, sec}] = 1;
			mpValid[{sec, fir}] = 1;
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
			mpValid[{(*itv), (*it).first}] = 1;
			mpValid[{(*it).first, (*itv)}] = 1;
		}
	}

	////////////////////////////
	mpBothOrig = mpBoth;

	/*
	countDD = 0;
	for (auto itxx = mpBoth.begin(); itxx != mpBoth.end(); itxx++) {
		auto itxy = itxx;
		itxy++;
		for (; itxy != mpBoth.end(); itxy++) {

			mpBothTmp = mpBoth;
			if (checkRule((*itxx).first, (*itxy).first) == 1) {
				countDD++;
				if ((countDD % 50) == 0 ) {printf("PRE_check: cur: %d (%d of %d)\n", countDD, (int)distance(mpBoth.begin(), itxx), (int)mpBoth.size());}
				mpValid[{(*itxx).first, (*itxy).first}] = 1;
				mpValid[{(*itxy).first, (*itxx).first}] = 1;
			}
		}
	}
	printf("There are %d valid pairs\n", countDD);
	*/
	printf("there are %d valid pairs\n", (int)mpValid.size());
	printf("Starting main search size:(%d) 4 levels):\n", (int)mpBoth.size());
	startMain = clock();
	{
		mpBoth = mpBothOrig;
		int count = 0;
		//int sz = (int)mpBoth.size();

		//auto itBegin = mpBoth.begin();;
		auto itEND = mpBoth.end();;
		auto itENDLess = mpBoth.end(); //itENDLess--;
		for (auto itG1 = mpBoth.begin(); itG1 != itENDLess; itG1++) {
			end = clock();
			if (count != 0) {
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printf("        time: %f seconds\n", cpu_time_used);
			}
			//cout << count << " of " << sz << endl;
			start = clock();

			auto ittmp1 = itG1;
			auto it1 = itG1;
			ittmp1++;
			//int count2 = 0;

			for (auto it2 = ittmp1; it2 != itEND; it2++) {
				//cout << " Level 2: " << count2++ << endl; fflush(stdout);
				if (it2 == it1) {continue;}
				if (mpValid.find({(*itG1).first, (*it2).first}) == mpValid.end()) {continue;}
				auto ittmp2 = it2;
				ittmp2++;
				//int count3 = 0;

				for (auto it3 = ittmp1; it3 != itENDLess; it3++) {
					//cout << " Level 3: " << count3++ << endl; fflush(stdout);
					if (it3 == it2 || it3 == it1) {continue;}
					auto ittmp3 = it3;
					ittmp3++;

					//int count4 = 0;
					for (auto it4 = ittmp3; it4 != itEND; it4++) {
						//cout << " Level 4: " << count4++ << endl; fflush(stdout);
						if (it4 == it3 || it4 == it2 || it4 == it1) {continue;}
						if (mpValid.find({(*it3).first, (*it4).first}) == mpValid.end()) {continue;}
						auto ittmp4 = it4;
						ittmp4++;

						for (auto it5 = ittmp3; it5 != itENDLess; it5++) {
							if (it5 == it4 ||  it5 == it3 || it5 == it2 || it5 == it1) {continue;}
							auto ittmp5 = it5;
							ittmp5++;

							for (auto it6 = ittmp5; it6 != itEND; it6++) {
								if (it6 == it5 || it6 == it4 || it6 == it3 || it6 == it2 || it6 == it1) {continue;}
								if (mpValid.find({(*it5).first, (*it6).first}) == mpValid.end()) {continue;}


								{
									mpBothTmp = mpBothOrig;
									int r1 = removeRule((*itG1).first, (*it2).first);
									if (r1 == 0) {continue;}
									int r2 = removeRule((*it3).first, (*it4).first);
									if (r2 == 0) {continue;}
									int r3 = removeRule((*it5).first, (*it6).first);
									if (r3 == 0) {continue;}
									checkAnswers();
									//mpBoth = mpBothOrig;
								}
							}
						}
					}
				}
			}
		}
	}
	//////////////////////////////
}
void checkAnswers() {
	group1.clear();
	group2.clear();
	countCCC++;
	if (countCCC % 10000 == 0) {printf("In checkAnswers, checked: %d (of a lot)\n", countCCC); countCCC=0;}
	auto it = mpBothTmp.begin();
	//printf("*it.first.c_str() is %s\n", (*it).first.c_str());
	group1[(*it).first] = 1;
	countthemGroup1((*it).first);
	//printf("group1 .size == %d\n", (int)group1.size());

	if ((int)group1.size() != (int)mpBothTmp.size()) {
		for (auto it4 = mpBothTmp.begin(); it4 != mpBothTmp.end(); it4++) {
			//printf("counting group2\n");
			countthemGroup2((*it4).first);
		}
		printf("group2 .size == %d\n", (int)group2.size());
		//printf("**ans: %d\n", (int)((int)group1.size() * (int)group2.size()));
		int check = (int)((int)group1.size() + (int)group2.size()) - (int)mpBothTmp.size();
		if (check == 0) {
			printf("\n");
			system("date");
			endMain = clock();
			double cpu_time_usedMain = ((double) (endMain - startMain)) / CLOCKS_PER_SEC;
			printf("        time: %f seconds\n", cpu_time_usedMain);
			printf("**ans: %d\n", (int)((int)group1.size() * (int)group2.size()));
		}
		exit(0);
	} 

}
int checkRule(string Rone, string Rtwo) {

	char splits[3][10];
	strcpy(splits[0], Rone.c_str());
	strcpy(splits[1], Rtwo.c_str());

	int removed = 0;
	for (int kk = 0; kk < 2; kk+=2) {
		if (mpBothTmp.find(splits[kk]) != mpBothTmp.end()) {
			vector <string> ve3 = mpBothTmp[splits[kk]];
			vector <string>::iterator it4;
			if ((it4 = find(ve3.begin(), ve3.end(), splits[kk+1])) != ve3.end()) {
				//printf("erasingin mpBothTmp %s\n", (*it4).c_str());
				removed = 1;
				//ve3.erase(it4);
			} else {
				//printf("not found %s\n", splits[kk+1]);
			}
			//mpBothTmp[splits[kk]] = ve3;
		} else {
			//printf("not found..%s.\n", splits[kk]);
		}
	}
	return removed;
}
int removeRule(string Rone, string Rtwo) {

	char splits[3][10];
	strcpy(splits[0], Rone.c_str());
	strcpy(splits[1], Rtwo.c_str());

	int removed = 0;
	for (int kk = 0; kk < 2; kk+=2) {
		if (mpBothTmp.find(splits[kk]) != mpBothTmp.end()) {
			vector <string> ve3 = mpBothTmp[splits[kk]];
			vector <string>::iterator it4;
			if ((it4 = find(ve3.begin(), ve3.end(), splits[kk+1])) != ve3.end()) {
				//printf("erasingin mpBothTmp %s\n", (*it4).c_str());
				removed = 1;
				ve3.erase(it4);
			} else {
				//printf("not found %s\n", splits[kk+1]);
			}
			mpBothTmp[splits[kk]] = ve3;
		} else {
			//printf("not found..%s.\n", splits[kk]);
		}
	}

	char splits2[3][10];
	strcpy(splits2[0], Rtwo.c_str());
	strcpy(splits2[1], Rone.c_str());

	for (int kk = 0; kk < 2; kk+=2) {
		if (mpBothTmp.find(splits2[kk]) != mpBothTmp.end()) {
			vector <string> ve3 = mpBothTmp[splits2[kk]];
			vector <string>::iterator it4;
			if ((it4 = find(ve3.begin(), ve3.end(), splits2[kk+1])) != ve3.end()) {
				//printf("erasing in mpBothTmp %s\n", (*it4).c_str());
				removed = 1;
				ve3.erase(it4);
			} else {
				//printf("not found %s\n", splits[kk+1]);
			}
			mpBothTmp[splits2[kk]] = ve3;
		} else {
			//printf("not found..%s.\n", splits2[kk]);
		}
	}
	return removed;
}

void countthemGroup2(string s1) {
	auto it = mpBothTmp.find(s1);
	if (it != mpBothTmp.end()) 

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
void countthemGroup1(string s1) {
	auto it = mpBothTmp.find(s1);
	if (it != mpBothTmp.end()) 
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
