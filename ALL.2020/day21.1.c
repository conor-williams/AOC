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
#include <map>

using namespace std;

int lenx = 0;
int leny = 0;

#define LINE 2000
struct foods_s {
	string foods[100];
	int foodsNum;
	string allergies[100];
	int allergiesNum;
	string both[200];
	int bothNum;
};
struct foods_s foods[200];
map <string, int> mp;
map <string, int> mpf1;
map <string, int> mpf2;
map <string, int> mpIgnore;
map <string, int> mpAll;
//map <string, string> mpMatch;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day21\n"); fflush(stdout);
        char line1[LINE];
	string allergens1[] = {"dairy", "eggs", "fish", "nuts", "peanuts", "sesame",
			"shellfish", "wheat", "soy"};
/*

mxmxvkd kfcds sqjhc nhms (contains dairy, fish)
trh fvjkl sbzzf mxmxvkd (contains dairy)
sqjhc fvjkl (contains soy)
sqjhc mxmxvkd sbzzf (contains fish)

*/

while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);

	char *fud = strtok(line1, " ),");
	int fudPos = 0;
	int gotAl = 0;
	do {
		if (fud[0] == '(') {gotAl = 1; continue;}
		foods[leny].both[fudPos++] = fud;
		if (gotAl == 1) {
			mp[fud] = 1;
		} else {
			if (mpAll.find(fud) == mp.end()) {
				mpAll[fud] = 1;
			} else {
				mpAll[fud]++;
			}
		}
	} while ((fud = strtok(NULL, " ),")) != NULL);
	
	sort(foods[leny].both, foods[leny].both + fudPos);
	foods[leny].bothNum = fudPos;
	leny++;
	printf("leny now %d\n", leny);
}

	printf("after....\n"); fflush(stdout);
	cout << "mpAll.size() : " << mpAll.size() << endl; getchar();
	int goAgain;
	do {
		goAgain = 0;
		string f1, f2;
		for (int i = 0; i < leny; i++) {
			mpf1.clear(); mpf2.clear();
			sort(foods[i].both, foods[i].both + foods[i].bothNum);
			int count3 = 0;
			int szAl2 = 0;
			int szNAl2 = 0;
			int pit = 0;
			for (int k = 0; k < foods[i].bothNum; k++) {
				string what = foods[i].both[k];
				if (i == 2) {cout << what << endl;}
				if (what == "soy") {
					cout << "got soy...\n"; 
					pit = 1;
				}
				if (mpIgnore.find({what}) == mpIgnore.end()) {
					count3++;
				} else {
					continue;
				}
				if (mp.find(what) == mp.end()) {
					//f2 = what;
					mpf2[what] = 1;
					szNAl2++;
				} else {
					///f1 = what;
					mpf1[what] = 1;
					szAl2++;
				}
			}
			if (pit == 1) {
				cout << "szNAl2: " << szNAl2 << endl;
				cout << "szAl2:" << szAl2 << endl;
				cout << "count3: " << count3 << endl; 
			}
			if (szNAl2 == szAl2 && szNAl2 != 0) {
				//printf("i is %d-- HERE f1: %s f2: %s\n", i, f1.c_str(), f2.c_str()); getchar();
				printf("here1 szNAl2: %d\n", szNAl2); getchar();
				goAgain = 1;
			
				for (auto it2 = mpf1.begin(); it2 != mpf1.end(); it2++) {
					mpIgnore[it2->first] = 1;
				}
				for (auto it2 = mpf2.begin(); it2 != mpf2.end(); it2++) {
					mpIgnore[it2->first] = 1;
				}
				//mpIgnore[f2] = 1;
				//mpMatch[f1] = f2;
			}
			mpf1.clear(); mpf2.clear();

			for (int m = 0; m < leny; m++) {
				int found = 0;
				for (int j = 0; j < foods[m].bothNum; j++) {
					if (foods[m].both[j] == f2) {
						//cout << "found... " << f2 << endl; getchar();
						found = 1;
						break;
					}
				}
				if (found == 1) {
					int found2 = 0;
					for (int j = 0; j < foods[m].bothNum; j++) {
						if (foods[m].both[j] == f1) {
							found2 = 1;
							break;
						}
					}
					if (found2 == 0) {
						//printf("adding f1:%s\n", f1.c_str()); getchar();
						foods[m].both[foods[m].bothNum++] = f1;
						goAgain = 1;
					}
				}
			}
				
			for (int j = 0; j < leny; j++) {
				if (i == j) {continue;}
				vector<string> v(300);
				vector<string>::iterator it, st;	
				it = set_intersection(foods[i].both, foods[i].both+foods[i].bothNum,
					foods[j].both, foods[j].both+foods[j].bothNum, v.begin());

				cout << "foods in both " << i << " and " << j << endl;
				int szAl = 0;
				int szNAl = 0;
				for (st = v.begin(); st != it; ++st) {
					if (mpIgnore.find({*st}) != mpIgnore.end()) {
						continue;
					}
					
					if (mp.find({*st}) == mp.end()) {
						szNAl++;
					} else {
						szAl++;
					}
					cout << " " << *st; 
				}
				cout << endl;
				cout << "sizes: " << szNAl << " " << szAl << endl;
				int first = 0;
				if (szNAl == szAl && szNAl != 0) {
					if (szNAl != 1) {cout << szNAl << " < szNal" << endl;}
					cout << "here3\n"; getchar();
					goAgain = 1;
					for (st = v.begin(); st != it; ++st) {
						mpIgnore[*st] = 1;
						if (first == 0) {
							//mpf1[*st] = 1;
							f1 = *st;
							first = 1;
						} else {
							//mpf2[*st] = 1;
							f2 = *st;
						}
					}
					//cout << "f1 is " << f1 << endl; getchar();
					//mpMatch[f1] = f2;
				}	
				//cout << endl;
			}
		}
		for (int i = 0; i < leny; i++) {
			int found = 0;
			
			for (int j = 0; j < foods[i].bothNum; j++) {
				if (foods[i].both[j] == f2) {
					//cout << "found... " << f2 << endl; getchar();
					found = 1;
					break;
				}
			}
			if (found == 1) {
				int found2 = 0;
				for (int j = 0; j < foods[i].bothNum; j++) {
					if (foods[i].both[j] == f1) {
						found2 = 1;
						break;
					}
				}
				if (found2 == 0) {
					//printf("adding f1:%s\n", f1.c_str()); getchar();
					foods[i].both[foods[i].bothNum++] = f1;
					goAgain = 1;
				}
			}
		}
			
		cout << "--------" << endl;
		cout << "IGNORE: " << endl;
		for (auto it3 = mpIgnore.begin(); it3 !=mpIgnore.end(); it3++) {
			cout << "Ignore: " << it3->first << endl;
		}
		getchar();
	{
		cout << "--------" << endl;
		int count = 0;
		int count1 = 0;
		for (auto it2 = mpAll.begin(); it2 != mpAll.end(); it2++) {
			if (mpIgnore.find({it2->first}) == mpIgnore.end()) {
				count += mpAll[it2->first];
				count1++;
				cout << it2->first << endl;
			}
		}
		printf("count1 %d\n", count1);
		printf("interim ans count %d\n", count); getchar();
		goAgain = 1; getchar();
	}
	} while (goAgain == 1);
	
	cout << "--------" << endl;
	int count = 0;
	int count1 = 0;
	for (auto it2 = mpAll.begin(); it2 != mpAll.end(); it2++) {
		if (mpIgnore.find({it2->first}) == mpIgnore.end()) {
			count += mpAll[it2->first];
			count1++;
			cout << it2->first << endl;
		}
	}
	printf("count1 %d\n", count1);
	printf("**ans count %d\n", count);
}
