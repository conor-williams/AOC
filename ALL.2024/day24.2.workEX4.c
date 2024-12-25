#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;


FILE *a;
#define LINE 1000
#define getchar()
int lenx;
int leny;
struct sums_s {
	string r1;
	string r2;
	string r3;
	char type;
	int complete;
};
struct sums_s sums[400];
struct sums_s sumsCache[10][400];
struct sums_s sumsOrig[400];
map <string, vector <pair<int, int>>> mpBook;
map <string, int> mp;
//unsigned long long doSum();
unsigned long long grabTheX(); 
unsigned long long grabTheY(); 
unsigned long long grabTheZ(); 
void setTheX(unsigned long long val);
void setTheY(unsigned long long val);
void setTheZ(unsigned long long val);
unsigned long long runSumAgainDifferentArrangement(int &stuck);
void resetAllComplete();
void swapRule(string a, string b);
int numZREGS = 0;
map <string, vector <pair<int, int>>> ::iterator itG1;
void sigfunc(int a) { printf("here1"); fflush(stdout); printf("book distance[[ %d ]] (%s)\n", (int)distance(mpBook.begin(), itG1), ((*itG1).first).c_str()); fflush(stdout); }
unsigned long long moditVal = 0;
void eraseMPExceptXY();
void eraseMPExceptXY() {
	vector <int> poses;
	for (auto it = mp.cbegin(), next_it = it; it != mp.cend(); it = next_it) {
		++next_it;
		string ke1 = (*it).first;
		if (ke1[0] == 'x') {
			//leave
		} else if (ke1[0] == 'y') {
			//leave
		} else {
			mp.erase(it);
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
	printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 24 Part 2\n"); fflush(stdout);
	char line1[LINE];

	leny = 0;
	int go = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			go = 1;
			leny=0;
			continue;
		} else if (go == 1) {
			char r1[10], r2[10], r3[10];
			char type[10];
			sscanf(line1, "%s %s %s -> %s", r1, type, r2, r3);
			sums[leny].r1 = r1;
			sums[leny].r2 = r2;
			sums[leny].r3 = r3;
			if (strcmp(type, "XOR") == 0) {sums[leny].type = '^';}
			else if (strcmp(type, "OR") == 0) {sums[leny].type = '|';}
			else if (strcmp(type, "AND") == 0) {sums[leny].type = '&';}
			sums[leny].complete = 0;

			mpBook[sums[leny].r1].push_back({leny, 1});
			mpBook[sums[leny].r2].push_back({leny, 2});
			mpBook[sums[leny].r3].push_back({leny, 3});
		} else if (go == 0) {
			char regName[10]; int regval;
			sscanf(line1, "%[^:]: %d\n", regName, &regval);
			mp[regName] = regval;
			numZREGS++;
		}
		leny++;
	}
	fclose(a);
	numZREGS /= 2;
	moditVal = pow(2, numZREGS);
	for (int i = 0; i < leny; i++) {
		sumsOrig[i] = sums[i];
	}

	itG1 = mpBook.begin();
	map <string, int> mpOrig = mp;
	auto mpBookOrig = mpBook;
	int stuck234 = 0;
	unsigned long long Z1_1 = runSumAgainDifferentArrangement(stuck234);
	cout << Z1_1 << endl;
	vector <string> ansVec;
	int notZCount = 0;
	printf("Starting main search size:(%d) 4 levels):\n", (int)mpBook.size());

	{
		int count = 0;
		int sz = (int)mpBook.size();
		for (/*auto itG1 = mpBook.begin()*/; itG1 != mpBook.end(); itG1++) {
			cout << ++count << " of " << sz << endl;
			auto ittmp1 = itG1;
			auto it1 = itG1;
			ittmp1++;
			for (auto it2 = ittmp1; it2 != mpBook.end(); it2++) {
				//for (auto it2 = mpBook.begin(); it2 != mpBook.end(); it2++) 

				if (it2 == it1) {continue;}

				auto ittmp2 = it2;
				ittmp2++;
				for (auto it3 = ittmp2; it3 != mpBook.end(); it3++) {
					//for (auto it3 = mpBook.begin(); it3 != mpBook.end(); it3++) 
					if (it3 == it2 || it3 == it1) {continue;}
					auto ittmp3 = it3;
					ittmp3++;

					//jfor (auto it4 = mpBook.begin(); it4 != mpBook.end(); it4++) 
					for (auto it4 = ittmp3; it4 != mpBook.end(); it4++) {
						if (it4 == it3 || it4 == it2 || it4 == it1) {continue;}
						for (int kk = 0; kk < 3; kk++) {
							for (int i = 0; i < leny; i++) { sums[i] = sumsOrig[i]; }
							if (kk == 0) {
								swapRule((*itG1).first, (*it2).first);
								swapRule((*it3).first, (*it4).first);
							} else if (kk == 1) {
								swapRule((*itG1).first, (*it3).first);
								swapRule((*it2).first, (*it4).first);
							} else if (kk == 2) {
								swapRule((*itG1).first, (*it4).first);
								swapRule((*it2).first, (*it3).first);
							}

							/*
							   printf("Rules: \n");
							   for (int i = 0; i < leny; i++) {
							   printf("%s %c %s -> %s\n", sums[i].r1.c_str(), sums[i].type, sums[i].r2.c_str(), sums[i].r3.c_str());
							   }
							 */

							//if (sums[0].r3 == "z00" && sums[5].r3 == "z05") {printf("here1\n");}
							//if (sums[1].r3 == "z01" && sums[2].r3 == "z02") {printf("here2\n");}
							int got3 = 0;
							if (sums[0].r3 == "z00" && sums[5].r3 == "z05" && sums[1].r3 == "z01" && sums[2].r3 == "z02") {got3 = 1; printf("here3 -- line up\n"); getchar();}
							auto ittmp4 = it4;
							ittmp4++;
							eraseMPExceptXY();

							int found = 0;
							for (unsigned long long inX = 0; inX < 3/*moditVal*/; inX++) {
								for (unsigned long long inY = 0; inY < 3/*moditVal*/; inY++) {
									//printf("%llu && %llu\n", inX, inY);
									setTheX(inX); setTheY(inY);
									unsigned long long ans = (inX & inY) % moditVal;

									unsigned long long X = grabTheX();
									assert(X==inX);
									unsigned long long Y = grabTheY();
									assert(Y==inY);
									assert(X == inX);
									assert(Y == inY);

									resetAllComplete();
									int stuck123 = 0;
									unsigned long long Z1 = runSumAgainDifferentArrangement(stuck123);
									if (stuck123 == 0) {
										unsigned long long Z = grabTheZ();
										//printf("grab:%llu V %llu:runSum\n", Z, Z1);
										assert(Z == Z1);

										if (got3 == 1) {cout << ans << " " << Z << endl;}
										if (ans == Z) {
											//cout << "GOOD" << endl;
											if (got3 == 1){printf("good good\n");}
											continue;
										} else {
											//cout << "BAD: " << Z << endl;
											if (got3 == 1) {printf("oops...\n");}
											found = 1; goto next;
										}
									}
								}
							}
next:
							//continue;

							if (got3 == 1) {printf("found is %d\n", found);}
							if (found == 0) {
								//printf("here22\n"); fflush(stdout);
								if (((*itG1).first)[0] == 'z' && ((*it2).first)[0] == 'z' && ((*it3).first)[0] == 'z' && ((*it4).first)[0] == 'z') {
									vector <string> BB;
									BB.push_back((*itG1).first); BB.push_back((*it2).first);
									BB.push_back((*it3).first); BB.push_back((*it4).first);
									sort(BB.begin(), BB.end());
									//cout << "**ANS (one of): ";
									string an = "";
									for (auto bbone: BB) {
										an+= bbone + ",";
									}
									an.pop_back(); 
									ansVec.push_back(an);
								} else {
									notZCount++;
								}
							}
						}
					}
				}
			}
		}
		cout << "num before sortuniq: " << ansVec.size() << endl;
		sort(ansVec.begin(), ansVec.end());
		auto it77 = unique(ansVec.begin(), ansVec.end());
		ansVec.resize(distance(ansVec.begin(), it77));
		cout << "**Answers: " << endl;
		for (auto st99: ansVec) {
			cout << st99 << endl;
		}
		printf("%d not beginning with z ignored\n", notZCount);
		cout << endl;
	}
}
void printit() {
	printf("Rules: \n");
	for (int i = 0; i < leny; i++) {
		printf("%s %c %s -> %s\n", sums[i].r1.c_str(), sums[i].type, sums[i].r2.c_str(), sums[i].r3.c_str());
	}
}
void swapRule(string a, string b) {
	//if ((a == "z00" && b == "z05") || (a=="z05" && b == "z00")) {printf(" z00, z05\n");} 
	//if ((a == "z02" && b == "z01") || (a=="z01" && b == "z02")) {printf(" z01, z02\n");} 
	//printf("in swap %s %s\n", a.c_str(), b.c_str());
	//if (a == b){return;}
	//if (a[0] == 'z' || b[0] == 'z') {printf("zzzzzzzzzzz\n");}
	if (mpBook.find(a) == mpBook.end()) {
		perror("ERR4\n"); exit(0);
	}
	vector <pair<int, int>> vea = mpBook[a];
	//string tmpS = "999";
	for (auto pa: vea) {
		int ipos = pa.first;
		int which = pa.second;

		switch (which) {
			case 1:
				//printf("changing (left)r1 %s to %s\n", sums[ipos].r1.c_str(), b.c_str());
				sums[ipos].r1 = b;
				break;
			case 2:
				//printf("changing (left)r2 %s to %s\n", sums[ipos].r2.c_str(), b.c_str());
				sums[ipos].r2 = b;
				break;
			case 3:
				//printf("changing (left)r3 %s to %s\n", sums[ipos].r3.c_str(), b.c_str());
				sums[ipos].r3 = b;
				break;
			default:
				perror("ERR1\n"); exit(0);
		}
	}

	if (mpBook.find(b) == mpBook.end()) {
		perror("ERR3\n"); exit(0);
	}
	vector <pair<int, int>> veb = mpBook[b];
	for (auto pa: veb) {
		int ipos = pa.first;
		int which = pa.second;

		switch (which) {
			case 1:
				//printf("changing (right) r1 %s to %s\n", sums[ipos].r1.c_str(), a.c_str());
				sums[ipos].r1 = a;
				break;
			case 2:
				//printf("changing (right) r2 %s to %s\n", sums[ipos].r2.c_str(), a.c_str());
				sums[ipos].r2 = a;
				break;
			case 3:
				//printf("changing (right)r3 %s to %s\n", sums[ipos].r3.c_str(), a.c_str());
				sums[ipos].r3 = a;
				break;
			default:
				perror("ERR2\n"); exit(0);
		}
	}
}

void setTheX(unsigned long long val) {
	char regName[20];

	for (int ii = 0; ii < 64; ii++) {
		sprintf(regName, "x%02d", ii);
		if (mp.find(regName) != mp.end()) {
			//printf("regName: %s -- was:%d\n", regName, mp[regName]);
			//val |= (mp[regName] & 1) << ii;
			unsigned long long res = val & (1ull <<ii);
			mp[regName] = res == 0? 0: 1;
			//printf("setting %s to %d\n", regName, mp[regName]);
		}
	}
}
void setTheY(unsigned long long val) {
	char regName[20];

	for (int ii = 0; ii < 64; ii++) {
		sprintf(regName, "y%02d", ii);
		if (mp.find(regName) != mp.end()) {
			//printf("regName: %s -- %d\n", regName, mp[regName]);
			//val |= (mp[regName] & 1) << ii;
			unsigned long long res = val & (1ull <<ii);
			mp[regName] = res == 0? 0: 1;
			//printf("setting %s to %d\n", regName, mp[regName]);
		}
	}
}
void setTheZ(unsigned long long val) {
	char regName[20];

	for (int ii = 0; ii < 64; ii++) {
		sprintf(regName, "z%02d", ii);
		if (mp.find(regName) != mp.end()) {
			//printf("regName: %s -- %d\n", regName, mp[regName]);
			//val |= (mp[regName] & 1) << ii;
			unsigned long long res = val & (1ull <<ii);
			mp[regName] = res == 0? 0: 1;
		}
	}
}
unsigned long long grabTheY() {
	unsigned long long val = 0;
	char regName[20];
	for (int ii = 0; ii < 64; ii++) {
		sprintf(regName, "y%02d", ii);
		if (mp.find(regName) != mp.end()) {
			//printf("regName: %s -- %d\n", regName, mp[regName]);
			val |= (mp[regName] & 1ull) << ii;
		}
	}
	return val;
}
unsigned long long grabTheX() {
	unsigned long long val = 0;
	char regName[20];
	for (int ii = 0; ii < 64; ii++) {
		sprintf(regName, "x%02d", ii);
		//printf("regName: %s\n", regName);
		if (mp.find(regName) != mp.end()) {
			//printf("regName: %s -- %d\n", regName, mp[regName]);
			val |= (mp[regName] & 1ull) << ii;
		}
	}
	return val;
}
unsigned long long grabTheZ() {
	unsigned long long val = 0;
	char regName[20];
	for (int ii = 0; ii < 64; ii++) {
		sprintf(regName, "z%02d", ii);
		//printf("regName: %s\n", regName);
		if (mp.find(regName) != mp.end()) {
			//printf("regName: %s -- %d\n", regName, mp[regName]);
			val |= (mp[regName] & 1ull) << ii;
		}
	}
	return val;
}
void resetAllComplete() {
	for (int i = 0; i < leny; i++) {
		sums[i].complete = 0;
	}
}

unsigned long long runSumAgainDifferentArrangement(int &stuck) {
	//printf("in runSumAgainDifferentArrangement()\n");
	int restartCount = 0;
	stuck = 0;
restart:
	restartCount++;
	if (restartCount > 100) { stuck = 1;}
	if (stuck == 0) {
		for (int i = 0; i < leny; i++) {
			if (sums[i].complete != 1) { 
				if (mp.find(sums[i].r1) == mp.end() || mp.find(sums[i].r2) == mp.end()) {	
					//printf("not ready...\n");
					//not ready
				} else {
					switch (sums[i].type) {
						case '^':
							mp[sums[i].r3] = mp[sums[i].r1] ^ mp[sums[i].r2]; 
							//printf("bitwise xor %s -> %d", sums[i].r3.c_str(), mp[sums[i].r3]);
							break;
						case '|':
							mp[sums[i].r3] = mp[sums[i].r1] | mp[sums[i].r2]; 
							//printf("bitwise | %s -> %d", sums[i].r3.c_str(), mp[sums[i].r3]);
							break;
						case '&':
							mp[sums[i].r3] = mp[sums[i].r1] & mp[sums[i].r2]; 
							//printf("bitwise & %s -> %d", sums[i].r3.c_str(), mp[sums[i].r3]);
							break;
					}
					sums[i].complete = 1;
					goto restart;
				}
			} else {
				continue;
			}
		}

		for (int i = 0; i < leny; i++) {
			if (sums[i].complete != 1) {
				goto restart;
			}
		}
		//printf("done the sum.. sending back val.\n");

		vector <int> ve;
		for (auto it = mp.begin(); it!=mp.end();it++) {
			string regg = (*it).first;
			if (regg[0] == 'z') {
				//printf("debug...%s: %d\n", regg.c_str(), (*it).second);
				ve.push_back((*it).second);
			} else {
				//printf("%s\n", regg.c_str());
			}
		}
		//cout << endl;
		string deci;
		for (auto it2 = ve.rbegin(); it2 != ve.rend(); it2++) {
			deci += to_string(*it2);
			//cout << *it2;
		}
		char *bla;
		unsigned long long conved = strtoull(deci.c_str(), &bla, 2);

		//cout << deci << endl;
		//cout << "inSum: Sub: [ "; cout << conved; cout << " ] " << endl;
		//printf("restartCount is %d\n", restartCount);
		//printf("moditVal is %llu\n", moditVal);
		//return conved%moditVal; ///todo %2^numregs
		return conved;
	} else if (stuck == 1) {
		///printf("jumped stuck...\n");
		return 0;
	}
	return 0;
}
/*
   string convertToBitString(long long value)
   {
   string str(64, '0');

   for(int i = 0; i < 64; i++)
   {
   if( (1ll << i) & value)
   str[63-i] = '1';
   }

   return str;
   }

 */
