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
#include <vector>
#include <unistd.h>

//#define getchar()
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
struct foods_s foods2;
map <string, int> mp;
map <string, int> mpf1;
map <string, int> mpf2;
map <string, int> mpIgnore;
map <string, int> mpAll;
//map <string, string> mpMatch;

vector <string> allofem;
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("		2020 Day21 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];
	vector <string> allfoods2;
        map <string, vector<string>> mpAller2;

	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);
		char foods2[1000];
		char allergy2[1000];
		sscanf(line1, "%[^(](contains %[^)])", foods2, allergy2);

		printf("foods2 %s\n", foods2);
		printf("allergy2 %s\n", allergy2);
		allfoods2.clear();
		char *fud = strtok(foods2, " \0");
		do {
			//if (mpIgnore.find(fud) != mpIgnore.end()) {
				allfoods2.push_back(fud);
				printf("%s\n", fud);
			//}
			allofem.push_back(fud);
		} while ((fud = strtok(NULL, " \0")) != NULL);

		fud = strtok(allergy2, ", ");
		do {
			if ((int)mpAller2[fud].size() != 0) {
				printf("here22\n"); //fflush(stdout);
				vector <string> tmp1;
				sort(mpAller2[fud].begin(), mpAller2[fud].end());
				sort(allfoods2.begin(), allfoods2.end());
				set_intersection(mpAller2[fud].begin(), mpAller2[fud].end(), 
						allfoods2.begin(), allfoods2.end(), back_inserter(tmp1));
				mpAller2[fud] = tmp1;
			} else {
				printf("here3\n"); //fflush(stdout);
				for (auto st: allfoods2) {
					if (find(mpAller2[fud].begin(), mpAller2[fud].end(), st) == mpAller2[fud].end()) {
						mpAller2[fud].push_back(st);
						printf("%s -> %s\n", st.c_str(), fud);
						if ((int)st.length() > 10) {
							printf("st: %s st.length() : %d\n", st.c_str(), (int)st.length());
							exit(0);
						} 

					}
				}
			}
		} while ((fud = strtok(NULL, ", ")) != NULL);

	}
	fclose(a);
	printf("--------------\n");
	vector <string> ans1;
	for (auto it = mpAller2.begin(); it != mpAller2.end(); it++) {
		auto aller = it->first;
		auto ve = it->second;
		printf("aller: %s\n", aller.c_str());
		for (auto st: ve) {
			printf("%s ", st.c_str());
			if (find(ans1.begin(), ans1.end(), st) == ans1.end()) {
				ans1.push_back(st);
			}
		}
		printf("\n");
	}

	for (auto it = mpAller2.begin(); it != mpAller2.end(); it++) {
		for (int ii = 0; ii < (int)it->second.size(); ii++) {
			if (mpAller2[it->first][ii].length() > 10) {
				printf("greater...\n"); exit(0);
			}
		}
	}


	map <string, string> ans123;
aga:
	for (auto it = mpAller2.begin(); it != mpAller2.end(); it++) {
		if ((int)it->second.size() == 1) {
			printf("%s -> %s\n", it->first.c_str(), it->second[0].c_str());

			string removeStr = it->second[0];
			ans123[it->first] = removeStr;
			for (auto it2 = mpAller2.begin(); it2 != mpAller2.end(); it2++) {
				auto vec = mpAller2[it2->first];
				for (int ii = 0; ii < (int)it2->second.size(); ii++) {
					cout << "<" << vec[ii] <<">" << endl;
					cout << "<" << removeStr <<">" << endl;
					printf("%d V %d\n", (int)vec[ii].length(), (int)removeStr.length());
					printf("[%s] V [%s]\n", vec[ii].c_str(), removeStr.c_str()); //getchar();
					if (vec[ii] == removeStr) {
						mpAller2[it2->first].erase(mpAller2[it2->first].begin()+ii);
						printf("erase yes...\n");
						break;
					} else {
						printf("erase no..%s V %s.\n", vec[ii].c_str(), removeStr.c_str());
					}
				}
			}
		} else {
			//printf("size is %d\n", (int)it->second.size());
		}
	}

	for (auto it = mpAller2.begin(); it != mpAller2.end(); it++) {
		if ((int)it->second.size() != 0) {
			goto aga;
		}
	}
			
	string ans1234;
	vector <string> var_allers;
	for (auto it4 = ans123.begin(); it4 != ans123.end(); it4++) {
		//cout << it4->second << ",";
		ans1234+=it4->second+",";
		var_allers.push_back(it4->second);
	}
	ans1234.pop_back();
	///printf("**ans: %s\n", ans1234.c_str());

	int count124 = 0;
	for (auto it = allofem.begin(); it != allofem.end(); it++) {
		if (find(var_allers.begin(), var_allers.end(), *it) == var_allers.end()) {
			count124++;
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count124);
	fflush(stdout);

}
