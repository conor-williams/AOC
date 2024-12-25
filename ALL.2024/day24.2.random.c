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
#include <deque>

using namespace std;
// NOTE: (cw) am still looking for the answer -- but this should work

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
deque <tuple <string, int, int>>::iterator itG1;
void sigfunc(int a) { fflush(stdout); printf("book (%s)\n", (get<0>(*itG1)).c_str()); fflush(stdout); }
unsigned long long moditVal = 0;
deque <tuple <string, int, int>> mpBookQ;
void eraseMPExceptXY();
void swapRule(deque <tuple<string, int, int>>::iterator a, deque<tuple<string, int, int>>::iterator b);
int main(int argc, char **argv)
{
	srand(time(NULL));   // Initialization, should only be called once.
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
			mpBookQ.push_back({sums[leny].r1, leny, 1});
			mpBookQ.push_back({sums[leny].r2, leny, 2});
			mpBookQ.push_back({sums[leny].r3, leny, 3});
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

	itG1 = mpBookQ.begin();
	map <string, int> mpOrig = mp;
	auto mpBookOrig = mpBookQ;
	int stuck234 = 0;
	unsigned long long Z1_1 = runSumAgainDifferentArrangement(stuck234);
	cout << Z1_1 << endl;
	vector <string> ansVec;
	long long count = 0;
	start = clock();
randomagain:

	int size = (int)mpBookQ.size();
	int rand1 = rand() % size;  
	int rand2 = rand() % size;  
	int rand3 = rand() % size;  
	int rand4 = rand() % size;  
	int rand5 = rand() % size;  
	int rand6 = rand() % size;  
	int rand7 = rand() % size;  
	int rand8 = rand() % size;  
	itG1 = mpBookQ.begin();
	advance(itG1, rand1);
	auto it2 = mpBookQ.begin();
	advance(it2, rand2);
	auto it3 = mpBookQ.begin();
	advance(it3, rand3);
	deque <tuple <string, int, int>>::iterator it4 = mpBookQ.begin();
	advance(it4, rand4);
	auto it5 = mpBookQ.begin();
	advance(it5, rand5);
	auto it6 = mpBookQ.begin();
	advance(it6, rand6);
	auto it7 = mpBookQ.begin();
	advance(it7, rand7);
	auto it8 = mpBookQ.begin();
	advance(it8, rand8);
	//tuple <string, int, int> tu = (*it4); printf("%s %d %d\n", (get<0>(tu)).c_str(), get<1>(tu), get<2>(tu)); fflush(stdout);
if (count % 5000 == 0) {
	printf("RANDOM: %d %d %d %d %d %d %d %d (%d)\n", rand1, rand2, rand3, rand4, rand5, rand6, rand7, rand8, size);
}
/*
	auto itG1end = itG1;
	itG1end++;
	auto it2end = it2;
	it2end++;
	auto it3end = it3;
	it3end++;
	auto it4end = it3;
	it4end++;
	auto it5end = it5;
	it5end++;
	auto it6end = it6;
	it6end++;
	auto it7end = it7;
	it7end++;
	auto it8end = it8;
	it8end++;
*/
	//printf("Starting main search size:(%d) 4 levels):\n", (int)mpBookQ.size());
	{
		int sz = (int)mpBookQ.size();
		{
			auto it1 = itG1;
			{
				if (it2 == it1) {goto randomagain;}
				{
					if (it3 == it2 || it3 == it1) {goto randomagain;}
					{
						if (it4 == it3 || it4 == it2 || it4 == it1) {goto randomagain;}
						{
							if (it5 == it4 ||  it5 == it3 || it5 == it2 || it5 == it1) {goto randomagain;}
							{
								if (it6 == it5 || it6 == it4 || it6 == it3 || it6 == it2 || it6 == it1) {goto randomagain;}
								{
									if (it7 == it6 || it7 == it5 || it7 == it4 || it7 == it3 || it7 == it2 || it7 == it1) {goto randomagain;}
									{
										if (it8 == it7 || it8 == it6 || it8 == it5 || it8 == it4 || it8 == it3 || it8 == it2 || it8 == it1) {goto randomagain;}

										{
											for (int i = 0; i < leny; i++) { sums[i] = sumsOrig[i]; }
											swapRule(itG1, it2);
											swapRule(it3, it4);
											swapRule(it5, it6);
											swapRule(it7,  it8);

											eraseMPExceptXY();

											int found = 0;
											for (unsigned long long inX = 0; inX < 3 /* moditVal*/; inX++) {
												for (unsigned long long inY = 0; inY < 3/*moditVal*/; inY++) {
													//printf("%llu && %llu\n", inX, inY);
													setTheX(inX); setTheY(inY);

													//unsigned long long ans = (inX & inY) % moditVal; //example simple AND: (ex4.txt)
													unsigned long long ans = (inX + inY) % moditVal;

#ifdef _DEBUG_
													unsigned long long X = grabTheX();
													assert(X==inX);
													unsigned long long Y = grabTheY();
													assert(Y==inY);
													assert(X == inX);
													assert(Y == inY);

#endif
													resetAllComplete();
													int stuck123 = 0;
													unsigned long long Z1 = runSumAgainDifferentArrangement(stuck123);
													if (stuck123 == 0) {
#ifdef _DEBUG_
														unsigned long long Z = grabTheZ();
														printf("grab:%llu V %llu:runSum\n", Z, Z1);
														assert(Z == Z1);
#endif

														if (ans == Z1) {
															continue;
														} else {
															//cout << "BAD: " << Z << endl;
															found = 1; goto next;
														}
													} else {
														found = 1; goto next;
													}
												}
											}
next:

											if (found == 0) {
												vector <string> BB;
												BB.push_back(get<0>(*itG1)); BB.push_back(get<0>(*it2));
												BB.push_back(get<0>(*it3)); BB.push_back(get<0>(*it4));
												BB.push_back(get<0>(*it5)); BB.push_back(get<0>(*it6));
												BB.push_back(get<0>(*it7)); BB.push_back(get<0>(*it8));
												sort(BB.begin(), BB.end());
												string an = "";
												for (auto bbone: BB) {
													an+= bbone + ",";
												}
												an.pop_back(); 
												printf("good: %s\n", an.c_str());
												ansVec.push_back(an);

											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
if (count % 5000 == 0) {
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("        time(%20lld): %f seconds\n", count, cpu_time_used);
		start = clock();
}
		if (count > 10000000000) {count = 0;}
		count++;

		goto randomagain;
// never here
		printf("ansVec size before unique: %d\n", (int)ansVec.size());
		sort(ansVec.begin(), ansVec.end());
		auto it77 = unique(ansVec.begin(), ansVec.end());
		ansVec.resize(distance(ansVec.begin(), it77));
		cout << "**Answers: " << endl;
		for (auto st99: ansVec) {
			cout << st99 << endl;
		}
		cout << endl;
	}
}
void printit() {
	printf("Rules: \n");
	for (int i = 0; i < leny; i++) {
		printf("%s %c %s -> %s\n", sums[i].r1.c_str(), sums[i].type, sums[i].r2.c_str(), sums[i].r3.c_str());
	}
}
//void swapRule(string a, string b) 
void swapRule(deque <tuple<string, int, int>>::iterator a, deque<tuple<string, int, int>>::iterator b) {
	//printf("in swap %s %s\n", a.c_str(), b.c_str());

	if (a == b){return;}
	tuple <string, int, int> atup = (*a);
	string astr = get<0>(atup);
	tuple <string, int, int> btup = (*b);
	string bstr = get<0>(btup);

	{
		int ipos = get<1>(atup);
		int which = get<2>(atup);

		switch (which) {
			case 1:
#ifdef _DEBUG_
				printf("changing (left)r1 %s to %s\n", sums[ipos].r1.c_str(), bstr.c_str());
#endif
				sums[ipos].r1 = bstr;
				break;
			case 2:
#ifdef _DEBUG_
				printf("changing (left)r2 %s to %s\n", sums[ipos].r2.c_str(), bstr.c_str());
#endif
				sums[ipos].r2 = bstr;
				break;
			case 3:
#ifdef _DEBUG_
				printf("changing (left)r3 %s to %s\n", sums[ipos].r3.c_str(), bstr.c_str());
#endif
				sums[ipos].r3 = bstr;
				break;
			default:
				perror("ERR1\n"); exit(0);
		}
	}

	{
		int ipos = get<1>(btup);
		int which = get<2>(btup);

		switch (which) {
			case 1:
#ifdef _DEBUG_
				printf("changing (right) r1 %s to %s\n", sums[ipos].r1.c_str(), astr.c_str());
#endif
				sums[ipos].r1 = astr;
				break;
			case 2:
#ifdef _DEBUG_
				printf("changing (right) r2 %s to %s\n", sums[ipos].r2.c_str(), astr.c_str());
#endif
				sums[ipos].r2 = astr;
				break;
			case 3:
#ifdef _DEBUG_
				printf("changing (right)r3 %s to %s\n", sums[ipos].r3.c_str(), astr.c_str());
#endif
				sums[ipos].r3 = astr;
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
				printf("%s: %d\n", regg.c_str(), (*it).second);
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
