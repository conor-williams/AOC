#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <deque>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sys/time.h>
#include <thread>
#include <mutex>

#include <unistd.h>

#define getchar()
unsigned long long totTime = 0;
using namespace std;
int prevMax = 0;
int ex1;
FILE *a;
#define LINE 1000
deque <string> Q;
int ind = 0;
void threadittask(int);
void spawnThread(int n);
mutex mtx;
int vecSize;

map <string, deque<string>> mp;
map <string, int> mpRate;
//map <string, tuple <int, deque<string>>> mpPrv;
map <string, deque<string>> mpPrv;
//map <string, deque<string>> mp;
//void doit(deque <string> Q1);
map <deque<string>, int> QMap;
void doit(deque <string> Q1, map <string, int> mp123, map <string, tuple <int, deque<string>>> mp);
void next(string abcd, string just);
#define getchar()
void fourfour(vector <string>valvsElse2, int totMinute, int path, string v);

void TimerStop(int signum);
void TimerSet(int interval);
int usingFoundIt = 0;
int foundit = 0;
int minPath = 99999;
void next2(string from, string to, int path, string fromPrv);
map <string, map<string, int>> matrix;
map <tuple<string, string, string, int>, int> tried;
vector <string> valvs;
int maxPath = 0;
long long prunes = 0;
vector <string>valvsTmp;
vector <string>valvsElse;
int count1 = 0;
int count2 = 0;
void sigfunc(int a) { for (auto elem: valvsTmp){ printf("[%s]", elem.c_str()); } cout << "--"; for (auto elem: valvsElse) { printf("[%s]", elem.c_str()); }  printf("-- max(sofar): %d == count1:%d == count2:%d", maxPath, count1, count2);  cout << endl;}
void spawnThread(int n) {
	thread thr[n];
	for (int i = 0; i < 10; i++) {
		printf("starting thread %d\n", i);
		thr[i] = thread(threadittask, i);
	}

	for (auto &th: thr) {
		th.join();
	}
}

int main(int argc, char **argv)
{
	printf("SLOW ~5 mins\n");
	ex1 = strcmp(argv[1], "ex1.txt") == 0 ? 1 : 0;

	if (ex1 == 1) {
		//TimerSet(20);
	} else {
		//TimerSet(35);
	}
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2022 Day 16 part1 \n"); fflush(stdout);
	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		char from[20]; char rest[100]; int rate;
		int ret = sscanf(line1, "Valve %s has flow rate=%d; tunnels lead to valves %[^\0]", from, &rate, rest);
		if (ret != 3) {
			sscanf(line1, "Valve %s has flow rate=%d; tunnel leads to valve %[^\0]", from, &rate, rest);
			printf("here1 rest is %s\n", rest);

			deque <string> td;
			td.push_back(rest);
			mp[from] = td;
			mpRate[from] = rate;
		} else {
			char *str = strtok(rest, " ,\0");
			deque <string> td;
			do {
				td.push_back(str);
				printf("td is %s\n", str);
			} while ((str = strtok(NULL, " ,\0")) != NULL);
			mpRate[from] = rate;
			mp[from] = td;
		}
		leny++;
	}
	fclose(a);
	for (auto it = mp.begin(); it != mp.end(); it++) {
		deque td2 = it->second;
		cout << "Valve: " << it->first << " -- " << mpRate[it->first] << endl;
		for (auto it2 = td2.begin(); it2 != td2.end(); it2++) {
			cout << *it2 << endl;
		}
	}
	for (auto it2 = mpRate.begin(); it2 != mpRate.end(); it2++) {
		int rate = it2->second;
		cout << "ValveRate: " << it2->first << " -- " << rate << endl;
	}

	mpPrv = mp;
	string startS = "AA";

	cout << startS << " " <<endl;
	auto it3 = mp.find(startS);
	deque <string> td = it3->second;
	for (auto it2 = td.begin(); it2 != td.end(); it2++) {
		cout << *it2 << " ";
		next(*it2, startS);
	}

	cout << endl << "Building Matrix-----------" << endl;
	for (auto it1 = mp.begin(); it1 != mp.end(); it1++) {
		for (auto it2 = mp.begin(); it2 != mp.end(); it2++) {
			if (it1->first == it2->first) {continue;}
			minPath = 99999;
			//cout << it1->first << " -> " << it2->first << " " << "Trying" << endl;
			tried.clear();
			next2(it1->first, it2->first, 1, it1->first);
			if (minPath == 99999) {
				perror("99999\n"); exit(0);
			} else {
				//cout << it1->first << " " << it2->first << " " << minPath << endl;
				matrix[it1->first][it2->first] = minPath;
			}
		}
	}
	cout << "After Building Matrix" << endl;
	//vector <string> valvs;
	for (auto it1 = mp.begin(); it1!= mp.end(); it1++) {
		if (mpRate[it1->first] != 0) {
			valvs.push_back(it1->first);
		}
	}
	sort(valvs.begin(), valvs.end());

	vecSize = valvs.size();
	minPath = 99999;
	maxPath = 0;
	prunes = 0;
	vector <string> valvsPrv = valvs;

	//spawnThread(10);

	//int end1 = vecSize;
	//int end1 = vecSize <10 ? vecSize: ;
	printf("vecSize %d\n", vecSize);
	int end1; int start;
	if (ex1 == 1) {
		start = 2;
		end1 = 2;
	} else {
		start = 7;
		end1 = 7;
	}

	printf("start:%d\nn", start);
	//	maxPath = 0;
	vector <string> valvsM;
	for (int N = start; N <= end1; N++) {
		maxPath = 0;
		string bitmask(vecSize-N, 0);
		bitmask.resize(vecSize, 1);
		cout << "bitmask: "; for (auto elem1: bitmask) { if (elem1 == 0) { cout << "0";} else if (elem1 == 1) {cout << "1";} } cout << endl;

		do {
			valvsTmp.clear();
			valvsElse.clear();
			for (int i = 0; i < vecSize; i++) {
				if (bitmask[i] == 1) {
					valvsTmp.push_back(valvs[i]);
				} else {
					valvsElse.push_back(valvs[i]);
				}
			}
			if (ex1 == 1) {
				assert((int)valvsTmp.size() == 2);
				assert((int)valvsElse.size() == 4);
			} else if (ex1 == 0) {
				assert((int)valvsTmp.size() == 7);
				assert((int)valvsElse.size() == 8);
			}

			sort(valvsTmp.begin(), valvsTmp.end());
			string lastvt;
			int path;
			int totMinute;
			do {
				totMinute = matrix["AA"][valvsTmp[0]];
				if (totMinute > 30) {goto ag5;}
				path = (30-totMinute)*mpRate[valvsTmp[0]];
				if (path > maxPath) {maxPath = path;}
				for (int i = 1; i < (int)valvsTmp.size(); i++) {
					int tm = totMinute;
					totMinute += matrix[valvsTmp[i-1]][valvsTmp[i]];
					//if (totMinute > 30) {printf("here1");totMinute = tm; lastvt = valvsTmp[i-1];goto ag5; }
					if (totMinute > 30) {totMinute = tm; lastvt = valvsTmp[i-1]; goto ag5; }
					path += (30-totMinute)*mpRate[valvsTmp[i]];
					lastvt = valvsTmp[i];
					//if (i == 1) { //cout << valvsTmp[0] << " " << valvsTmp[1] << " path: " << path << " totMinute: " << totMinute << endl; }
					if (path > maxPath) {maxPath = path;}
				}
				count1++;
				//for (auto elem: valvsTmp) {cout << elem << " ";} cout << "--- ";
				sort(valvsElse.begin(), valvsElse.end());
				fourfour(valvsElse, totMinute, path, lastvt);
				//if (path > maxPath) {maxPath = path;}
ag5:
				continue;
			} while (next_permutation(valvsTmp.begin(), valvsTmp.end()));

		} while (next_permutation(bitmask.begin(), bitmask.end()));
		printf("maxPath:%d for N:%d\n", maxPath, N); fflush(stdout);
	}

	cout << endl <<"ValvsM: "; for (int i = 0; i < (int)valvsM.size(); i++) { cout << valvsM[i] << " "; } cout << endl;
	cout << "count1: " << count1 << endl;
	cout << "maxPath: " << maxPath << endl;

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", maxPath);
}

void fourfour(vector <string>valvsElse2, int totMinutePrv, int pathPrv, string valvsLast) {
	//for (auto elem: valvsElse2) {cout << elem << " ";} cout << endl;
	//cout << "in four four" << endl;
	vector <string> valvsTmp222;
	vector <string> valvsElse222;
	vector <string> valvsWin;
	int X = (int)valvsElse2.size();
	if (ex1 == 1) {
		assert(X == 4);
	} else {	
		assert(X == 8);
	}
	//sort(valvsElse2.begin(), valvsElse2.end());
	for (int N = X/2; N <= X/2; N++) {
		string bitmask(X-N, 0); bitmask.resize(X, 1);
		if (ex1 == 1) {
			assert(N==2);
		} else {
			assert(N==4);
		}
		do {
			valvsTmp222.clear();
			valvsElse222.clear();

			for (int i = 0; i < (int)bitmask.size(); i++) {
				if (bitmask[i] == 1) {
					valvsTmp222.push_back(valvsElse2[i]);
				} else {
					valvsElse222.push_back(valvsElse2[i]);
				}
			}
			if (ex1 == 1) {
				assert((int)valvsTmp222.size() == 2);
				assert((int)valvsElse222.size() == 2);
				assert((int)bitmask.size() == 4);
			} else {
				assert((int)valvsTmp222.size() == 4);
				assert((int)valvsElse222.size() == 4);
				assert((int)bitmask.length() == 8);
			}

			//sort(valvsTmp222.begin(), valvsTmp222.end());

			int path2;
			int totMinute2;
			int totMinute; int path;
			string lastElse222;
			do {
				totMinute = totMinutePrv + matrix[valvsLast][valvsTmp222[0]];
				if (totMinute > 30) {goto ag6;}
				path = pathPrv + (30-totMinute)*mpRate[valvsTmp222[0]];
				if (path > maxPath) {maxPath = path;}
				for (int i = 1; i < (int)valvsTmp222.size(); i++) {
					int tm = totMinute;
					totMinute += matrix[valvsTmp222[i-1]][valvsTmp222[i]];
					if (totMinute > 30) {
						totMinute = tm;
						lastElse222 = valvsTmp222[i-1];
						goto ag6;
					} else {
						lastElse222 = valvsTmp222[i];
					}
					path += (30-totMinute)*mpRate[valvsTmp222[i]];
					if (path > maxPath) {maxPath = path;}
				}

				sort(valvsElse222.begin(), valvsElse222.end());
				path2 = path; totMinute2 = totMinute;
				do {
					//path = path2; totMinute = totMinute2;
					//totMinute = totMinute2 + matrix[valvsTmp222.back()][valvsElse222[0]];
					//path = path2 + (30-totMinute)*mpRate[valvsElse222[0]];
					totMinute = totMinute2 + matrix[lastElse222][valvsElse222[0]];
					if (totMinute > 30) {goto ag7;}
					path = path2 + (30-totMinute)*mpRate[valvsElse222[0]];
					if (path > maxPath) {maxPath = path;}

					for (int i = 1; i < (int)valvsElse222.size(); i++) {
						totMinute += matrix[valvsElse222[i-1]][valvsElse222[i]];
						if (totMinute > 30) {goto ag7;}
						path += (30-totMinute)*mpRate[valvsElse222[i]];
						if (path > maxPath) {maxPath = path;}
					}
					if (path > maxPath) {maxPath = path;}
ag7:
					continue;
				} while (next_permutation(valvsElse222.begin(), valvsElse222.end()));
ag6:
				continue;
			} while (next_permutation(valvsTmp222.begin(), valvsTmp222.end()));
		} while (next_permutation(bitmask.begin(), bitmask.end()));
	}
}
void threadittask(int thnum) {
	printf("kicking off %d\n", thnum);
	vector<string> valvsLocal = valvs;
	do {
		int totMinute = matrix["AA"][valvsLocal[0]];
		int path = (30-totMinute)*mpRate[valvsLocal[0]];
		for (int i = 1; i < vecSize; i++) {
			totMinute += matrix[valvsLocal[i-1]][valvsLocal[i]];
			if (totMinute > 30) {
				goto ag;
			}
			path += (30-totMinute)*mpRate[valvsLocal[i]];
		}

		mtx.lock();
		if (path > maxPath) {maxPath = path;}
		mtx.unlock();

		if (ex1 == 1) {
			usingFoundIt = 1;
			if (maxPath == 1651) {printf("found it... %d\n", maxPath); foundit = 1; fflush(stdout);break;}
		} else {
			usingFoundIt = 1;
			if (maxPath == 1595) {printf("found it... %d\n", maxPath); foundit = 1; fflush(stdout); break;}
		}
ag:

		random_shuffle(valvsLocal.begin(), valvsLocal.end());
		continue;
	} while (1);
}
void next2(string from, string to, int path, string fromPrv) 
{
	if (path > 17) {return;}
	if (from == to) {
		//printf("here 10 from is to\n"); getchar();
		if (path < minPath) {minPath = path;}

		return;
	}
	auto it3 = mp.find(from);
	deque <string> td = it3->second;
	for (auto it2 = td.begin(); it2 != td.end(); it2++)
	{
		if (tried.find({*it2, to, fromPrv, path}) == tried.end()) {
			tried[{*it2, to, fromPrv, path}] = 1;
			//printf("calling nex2 %s->%s=>%s\n", fromPrv.c_str(), (*it2).c_str(), to.c_str());
			next2(*it2, to, path+1, fromPrv);
		} else {
			//printf("already tried %s->%s=>%s\n", fromPrv.c_str(), (*it2).c_str(), to.c_str());
		}
	}
}

void next(string abcd, string just) 
{
	ind++;
	if (ind > 20) {return;}
	auto it3 = mp.find(abcd);
	deque <string> td = it3->second;
	for (auto it2 = td.begin(); it2 != td.end(); it2++)
	{
		if (*it2 != just) {
			cout << *it2 << " ";
			next(*it2, abcd);
		}
	}
	ind--;
}
void TimerSet(int interval) {
	//printf("starting timer\n");
	struct itimerval it_val;

	it_val.it_value.tv_sec = interval;
	it_val.it_value.tv_usec = 0;
	it_val.it_interval.tv_sec = 0;
	it_val.it_interval.tv_usec = 0;

	if (signal(SIGALRM, TimerStop) == SIG_ERR) {
		perror("Unable to catch SIGALRM");
		exit(1);
	}
	if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
		perror("error calling setitimer()");
		exit(1);
	}
}

void TimerStop(int signum) {
	printf("in TimerStop\n");
	if (usingFoundIt == 1) {
		if (foundit == 1) {
			printf("Timer sucessfully Over.\n");
			printf("**ans %d\n", maxPath);
			exit(0);
		} else if (foundit == 0) {
			prevMax = maxPath;
			printf("another 20 seconds maxPath now %d\n", maxPath);
			TimerSet(20);
		}
	} else {
		if (maxPath == 0 || prevMax != maxPath) {
			int t11 = 60*5;
			prevMax = maxPath;
			totTime+=t11;
			printf("another [%d] seconds ((%llu)) current maxPath:%d\n", t11, totTime, maxPath);
			TimerSet(t11);
		} else {
			time_t rawtime;
			struct tm * timeinfo;

			time ( &rawtime );
			timeinfo = localtime ( &rawtime );
			printf ( "Current local time and date: %s", asctime (timeinfo) );

			printf("Timer sucessfully Over.\n");
			printf("**ans %d\n", maxPath);
			exit(0);
		}
	}
}

/*
   Valve AA ZERO    has flow rate=0; tunnels lead to valves DD, II, BB
   Valve BB has flow rate=13; tunnels lead to valves CC, AA
   Valve CC has flow rate=2; tunnels lead to valves DD, BB
   Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE
   Valve EE has flow rate=3; tunnels lead to valves FF, DD
   Valve FF ZERO    has flow rate=0; tunnels lead to valves EE, GG
   Valve GG ZERO    has flow rate=0; tunnels lead to valves FF, HH
   Valve HH has flow rate=22; tunnel leads to valve GG
   Valve II ZERO    has flow rate=0; tunnels lead to valves AA, JJ
   Valve JJ has flow rate=21; tunnel leads to valve II
   */

/*
   int score(map<string, int> mp123) {
   for (int i = 1; i <= 10; i++) {
   for (auto it = mp123.begin(); it != mp123.end(); it++) {
   if (it->second == i) {
   tuple tup2 = mpPrv[it->first]->second;
   int rate = get<0>(tup2);
   deque td2 = get<1>(tup2);
   if (rate == 0) {} else {minute+=2;}
   break;
   }

   }
   }
   }
   */
/*
   do {
   int path = 0;
   int totMinute = matrix["AA"]["DD"];
   path += (30-totMinute)*mpRate["DD"];
   cout << " totMinute is " << totMinute << endl;
   for (int i = 1; i < vecSize; i++) {
   totMinute += matrix[valvs[i-1]][valvs[i]];
   cout << "totMinute: " << totMinute << " -- " << valvs[i] << endl;
   path += (30-totMinute)*mpRate[valvs[i]];
   }
   if (path < minPath) {minPath = path;}
   if (path > maxPath) {maxPath = path;}
   } while (1!=1);//while (next_permutation(valvs.begin(), valvs.end()));
   */
/*
ag:
printf("prunePos V vecSize %d V %d\n", prunePos, vecSize);
if (prunePos != vecSize) {
for (int k = prunePos-1; k < vecSize; k++) {
valvs[k] = valvsPrv[k];
}
printf("mod with loop from %d from %s\n", prunePos-1, valvs[prunePos-1].c_str());
for (auto element: valvs) {
cout << element << " ";
}
cout << endl;
}
*/

/*
   auto it10 = valvs.begin()+pSt;
   valvs.erase(it10);
   valvs.push_back(tmp1);
   cout << "moved to end" << endl;
   for (auto element: valvs) {
   cout << element << " ";
   }
   cout << endl;
   */

/*
   if (prunePos == vecSize) {pSt = 0; pEn = prunePos;} else {

   pSt = prunePos-1; pEn = prunePos+1;
//string tmp1 = valvs[pSt]; string tmp2 = valvs[pSt+1]; valvs[pSt] = tmp2; valvs[pSt+1] = tmp1;
string tmp1 = valvs[pSt];
auto it10 = valvs.begin()+pSt;
valvs.erase(it10);
valvs.push_back(tmp1);
//cout << "moved to end" << endl; for (auto element: valvs) { cout << element << " "; } cout << endl;
//sort(valvs.begin()+pSt+1, valvs.end());
//cout << "sort to end\n"; for (auto element: valvs) { cout << element << " "; } cout << endl;
prev_permutation(valvs.begin(), valvs.end());
}
*/
/*
   void eight(vector <string>valvsElse) {
   sort(valvsElse.begin(), valvsElse.end());
   do {
   for (int i = 1; i < (int)valvsElse.size(); i++) {
   totMinute += matrix[valvsElse[i-1]][valvsElse[i]];
   if (totMinute > 30) {
   goto ag5;
   }
   path += (30-totMinute)*mpRate[valvsElse[i]];
   }
   if (path > maxPath) {maxPath = path;}
   count2++;
   } while (next_permutation(valvsElse.begin(), valvsElse.end()));
   }
   }
   */
/*
   int maxV = 0;
   maxPath = 0;
   string maxValv;
   for (int i = 1; i < vecSize; i++) {
   int path = 0;
   int totMinute = matrix["AA"][valvs[i]];
   path += (30-totMinute)*mpRate[valvs[i]];
   if (path > maxPath) {maxV = i; maxValv = valvs[i]; maxPath = path;}
   }
   cout << "maxPath:" << maxPath << " maxV:" << maxV << " valv:" << maxValv << endl;
   */
//vector <string> valvsMax;
//while (next_permutation(valvs.begin(), valvs.end());

//do {} while (1);
//printf("**ans %d\n", maxPath);
/*
   int N = 4;

   string bitmask(vecSize-N, 0);
   bitmask.resize(vecSize, 1);
   cout << "bitmask: ";
   for (auto elem1: bitmask) {
   if (elem1 == 0) { cout << "0";}
   else if (elem1 == 1) {cout << "1";}
   }
   do {


   for (int i = 0; i < vecSize; i++){
   if (bitmask[i] == 1) {
   cout << valvs[i] << " ";

   } 
   }
   printf("\n");
   } while (next_permutation(bitmask.begin(), bitmask.end()));

   getchar();
   */


