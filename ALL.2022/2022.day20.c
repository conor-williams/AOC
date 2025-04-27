#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <deque>
#include <vector>
#include <list>
#include <iostream>
#include <unistd.h>
#include <algorithm>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
int gPo1 = 0;
int fd;
void sigfunc(int a) { fflush(stdout); dup2(fd, 1); printf("[[ %s ]] %d\n", "signal hand..\n", gPo1); fd=dup(1); close(1); }

int sz;
vector<int> left_rotate(const vector<int>& v);

list <int> veOrig;
vector <int> ve3;
vector <int> vePos;
vector <int> vePosTmp;
int getCurrentPositionOf(int val);
int hide = 0;

int main(int argc, char **argv)
{
	if (argc == 3) {hide = 1;}	
	signal(SIGTSTP, &sigfunc);
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day 20 Part 1\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[LINE];

	if (hide == 1) {fd = dup(1); close(1);}
	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		veOrig.push_back(atoi(line1));
		ve3.push_back(atoi(line1));
		leny++;

	}
	fclose(a);

	sz = veOrig.size();
	for (int i = 0; i < (int)veOrig.size(); i++) {
		vePos.push_back(i);	
		vePosTmp.push_back(i);	
	}

	//printf("za list 1st):::::::::::::\n"); for (int za = 0; za < (int)vePos.size(); za++) { printf("%d", vePos[za]);} cout << endl;
	//printf("Should: //0 1 2 3 4 5 6\n"); 

	auto it = veOrig.begin();
	printf("sz is %d\n", sz);

	printf("sz is %d\n", sz);
	for (int po1 = 0; po1 < sz; po1++) {
		gPo1 = po1;
		vePosTmp = vePos;
		int mv1 = *it;
		int position1;
		for (int zz = 0; zz < sz; zz++) {
			//printf("position %d is %d value %d\n", zz, vePos[zz], ve3[vePos[zz]]);
			if (vePos[zz] == po1) {position1 = zz; break;}
		}
		for (int qq = 0; qq < position1; qq++) {
			rotate(vePos.begin(), vePos.begin()+1, vePos.end());
		}
		for (int zz = 0; zz < sz; zz++) {
			//printf("position %d is %d value %d\n", zz, vePos[zz], ve3[vePos[zz]]);
			if (vePos[zz] == po1) {position1 = zz; break;}
		}

		assert(position1 == 0);
		vePosTmp = vePos;

		if (mv1 > 0) {
			int mv1Orig = mv1;
			printf("moving %d (@ position zero) mv1 forward: positions: mv1:%d\n", *it, mv1);
			if (mv1 >= sz-2) {mv1 %= sz-1;}

			if (mv1 != mv1Orig) {
				printf("mv1 forward: now %d\n", mv1);
			}
			assert (mv1 >= 0 && mv1 < sz-1);
		} else if (mv1 < 0) {
			int mv1Orig = mv1;
			printf("moving %d (@ position zero) mv1 backward: positions: mv1:%d\n", *it, mv1);
			while (mv1 < 0) {mv1 += sz-1;}
			//mv1 = ((sz + mv1-1) + 2*sz) % sz;
			//if (mv1 != 0) { mv1--; }
			if (mv1 != mv1Orig) {
				printf("mv1 forward: now %d\n", mv1);
			}
			assert(mv1 >= 0 && mv1 < sz-1);
		}

		if (mv1 == 0 || mv1 == sz || mv1 == sz-1) {
			it++;
			continue;
		}

		{
			assert(mv1 >= 1 && mv1 < sz-1);
			for (int zzz = 1; zzz <= mv1; zzz++) {
				vePosTmp[zzz-1] = vePos[zzz];
			}
			vePosTmp[mv1] = vePos[0];
			vePos = vePosTmp;
			it++;
		}
		for (int kk = 0; kk < sz; kk++) { printf("[%d]", ve3[vePosTmp[kk]]); } printf("\n");getchar();
	}

	if (hide == 1) {fflush(stdout); dup2(fd, 1);}
	//if (argc != 3) {end = 1000;} else {end = atoi(argv[2]);}
	int end = 0;
	int endings[] = {1000, 2000, 3000};
	int sum = 0;
	int var_pos = getCurrentPositionOf(0);
	printf("var_pos is %d\n", var_pos);
	for (int i = 0; i < 3; i++) {
		int endMod = endings[i] % sz;
		int var2 = (var_pos + endMod) % sz;
		printf("end:%d endMod is %d\n", end, endMod);
		sum += ve3[vePos[var2]];
	}

	if (strcmp(argv[1], "i1.txt")==0) {
		int sum2;
		int tmp2;
		for (int zz = 0; zz < sz; zz++) {
			//printf("position %d is %d value %d\n", zz, vePos[zz], ve3[vePos[zz]]);
			if (ve3[vePos[zz]] == 0) {tmp2 = zz; break;}
		}
		for (int qq = 0; qq < tmp2; qq++) {
			rotate(vePos.begin(), vePos.begin()+1, vePos.end());
		}

		for (int zz = 0; zz < sz; zz++) {
			//printf("position %d is %d value %d\n", zz, vePos[zz], ve3[vePos[zz]]);
			if (ve3[vePos[zz]] == 0) {tmp2 = zz; break;}
		}
		assert(tmp2 == 0);
		sum2 = ve3[vePos[1000]] + ve3[vePos[2000]] + ve3[vePos[3000]];
		assert (sum2 == sum);
	}
	printf("var_pos is %d\n", var_pos);

	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", sum);

}


int getCurrentPositionOf(int val) 
{
	printf("getCu of %d\n", val);
	for (int i = 0; i < sz; i++) {
		if (ve3[vePos[i]] == val) {
			return i;
		}
	}
	perror("NOT FOUND\n"); exit(0);
	return -1;

}


/*
   vector<int> left_rotate(const vector<int>& v)
   {
   vector<int> result;
   int size = v.size(); // this way you are able to rotate vectors of any size
   for (auto i = 1; i < size; ++i)
   result.push_back(v.at(i));

// adding first element of v at end of result
result.push_back(v.front());
return result;
}

*/
/*
   if (tmp1+mv1 < sz || tmp1 + mv1 > sz) {
   int zz;
   mv1 %= sz;
   for (zz = 1; zz < sz; zz++) {
   if (zz > tmp1 && zz <= tmp1+mv1) {
   vePosTmp[zz-1] = vePos[zz];
//printf("**moving value: ve3[vePosTmp[%d]]: %d to where?? zz-1:%d?\n", zz, ve3[vePosTmp[zz]], zz-1); getchar();
//for (int kk = 0; kk < sz; kk++) { printf("[%d]", ve3[vePosTmp[kk]]); } printf("\n");getchar();
}
if (zz == tmp1+mv1) {break;}
}
vePosTmp[tmp1+mv1] = vePos[tmp1];
}
*/
//
//				//for (zzz = 1; zzz < sz; zzz++) 
//				for (zzz = 1; zzz <= mv1; zzz++) {
//					vePosTmp[zzz-1] = vePos[zzz];
////
//					if (zzz <= mv1) {
//						vePosTmp[zzz-1] = vePos[zzz];
//					}
//					if (zzz == mv1) {break;}
/////
//				}
//				vePosTmp[mv1] = vePos[0];
//
