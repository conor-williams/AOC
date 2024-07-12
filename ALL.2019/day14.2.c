#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <assert.h>
#include <algorithm>

using namespace std;
unsigned long long onetrill = 1000000000000llu;
#define getchar()
int lenx, leny;
#define DAY "2019 day14 part2\n"
#define _DEBUG_
struct got_s {
	unsigned long long fuel;
	unsigned long long mytot;
};
#define GOTCHA 6000
struct got_s got[GOTCHA];

struct Fnode {
	char to[100];
	double toCost;
	char from[300][100];
	double fromCost[300];
	double oreSize;
	double rhsSize;
	int numNodes;
};

map<string, struct Fnode> mp;
int search(char *start, double startCost, char *end);
map <string, double> mpingred;
map <string, double> mpspare;

//#define arLIM 1000000
map <map <string, double>, int> arspare;


unsigned long long oreore;
unsigned long long mytot;
void signal_handler(void *v) {
	printf ("oreore %llu mytot %llu\n", oreore, mytot);
}
#define SIZEL 400

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);

	char line1[SIZEL];

	//2 JNLZG => 7 SJTKF
	while(1) {
		fgets(line1, SIZEL-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		printf("LINE: [%s]\n", line1);
#endif
		char f[300]; char t[100]; int toCost;
		sscanf(line1, "%[^=]=> %d %s", f, &toCost, t);

		string tS = t;
		//string fS = f;

		cout << "tS: " << tS << endl;
		if (mp.find(tS) == mp.end()) { 
			struct Fnode n;
			strcpy(n.to, t);
			n.toCost = 1; //1;// toCost;
			n.rhsSize = toCost;
			n.numNodes = 0;
			char *first = strtok(f, ",\0");
			do {
				double cost; char wat[100];
				sscanf(first, "%lf %s", &cost, wat);
				strcpy(n.from[n.numNodes], wat);
				if (strcmp(wat, "ORE") == 0) {n.oreSize = cost;}
				n.fromCost[n.numNodes] = cost/toCost; ////toCost;
								      //printf("writing to node: %lf %s\n", n.fromCost[n.numNodes], n.from[n.numNodes]);
				n.numNodes++;
			} while ((first = strtok(NULL, ",\0")) != NULL);

			mp.insert({tS, n});
		} else {
			printf("already there ERROR\n"); exit(0);
		}

		leny++;
	}
	fclose(a);
	printf("mp.size is %d\n", (int)mp.size()); getchar();


	int SIZE = mp["FUEL"].numNodes;
/*
	for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) {
		if (strcmp(iter2->first.c_str(), "FUEL") == 0) {
			SIZE = iter2->second.numNodes;
		}
	}
*/

#ifdef _I1_
	printf("compiled with _I1_\n");
	int list2[] = {0, 1, 2, 3, 5, 4, 6, 7};
#else
	printf("not compiled with _I1_\n");
#endif

	oreore = 0;
	mytot = 0;

	int fuel = 0;
	auto iter2 = mp.find("FUEL");
	int gotcha = 0;
	do {
		mpingred.clear(); //mpspare.clear();
		for (int i = 0; i < SIZE; i++) {
#ifdef _I1_
			search(iter2->second.from[list2[i]], iter2->second.fromCost[list2[i]], (char *)"ORE");
#else
			search(iter2->second.from[i], iter2->second.fromCost[i], (char *)"ORE");
#endif
		}

		mytot += mpingred["ORE"];
		oreore = mpingred["ORE"];
		fuel++;

/*
		auto it3 = arspare.find(mpspare);
		if (it3 != arspare.end()) {
			if (gotcha == 0) {printf("gotcha FIRST: %d at pos %d\n", (int)it3->second, fuel); fflush(stdout);}
			got[gotcha].fuel = fuel;
			got[gotcha].mytot = mytot;
			gotcha++;
			if (gotcha == GOTCHA) { goto after;}
		}
		if (fuel < GOTCHA * 3) { arspare.insert({mpspare, fuel});}
*/
		if (fuel % 10000 == 0) {printf("fuel : %d\n", fuel);}
	} while (mytot < onetrill);

after:
	if (gotcha != GOTCHA) {
		if (mytot > onetrill) {
			printf("**ans is (no cycle(minus)) fuel: %d\n", fuel-1);
		} else {
			printf("**ans is (no cycle()) fuel: %d\n", fuel);
		}
		exit(0);
	}
	printf("ans?? -- %llu \n", (unsigned long long)fuel * (onetrill / mytot));

	unsigned long long max = 0;
	for (int i = 0; i < GOTCHA; i++) {
		if (got[i].fuel *(onetrill) / got[i].mytot > max) {
			max = got[i].fuel *onetrill / got[i].mytot;}
	}
	printf("** max %llu \n", max);
}


int ind = 0;
int search(char *start, double startCost, char *end) {
	ind++;
	{
		auto iter2 = mp.find(start);
		//for (int q = 0; q < ind; q++) {printf("  ");} printf("in search... RHS: %s %lf\n", iter2->first.c_str(), iter2->second.rhsSize);

		int k; double spare;
		if (mpspare.find(iter2->second.to) == mpspare.end()) {
			spare = 0;
		} else {
			spare = mpspare[iter2->second.to];
		}

		//for (int q = 0; q < ind; q++) {printf("  ");} printf("**spare before: %lf for (%s)\n", spare, iter2->second.to); 
#define LOOP 100000
		for (k = 0; k < LOOP; k++) {
			//for (int q = 0; q < ind; q++) {printf("  ");} printf("k is %d, startCost %lf V %lf\n", k,  startCost, (k*iter2->second.rhsSize)+spare);
			if (startCost <= (k*iter2->second.rhsSize)+spare) {
				mpspare[iter2->second.to] = ((k*iter2->second.rhsSize)+spare) - startCost;
				//for (int q = 0; q < ind; q++) {printf("  ");} printf("k is %d spare == %lf for (%s)\n", k, mpspare[iter2->second.to], iter2->second.to);
				break;
			}
		}
		if (k == LOOP) {perror("LOOP overspill ERR\n"); exit(0);}

		for (int i = 0; i < iter2->second.numNodes; i++) {
			mpingred[iter2->second.to] += (k*iter2->second.rhsSize);
			if (strcmp(iter2->second.from[i], end) == 0) {
				mpingred[iter2->second.from[i]] += (k*iter2->second.oreSize);
			} else {
				search(iter2->second.from[i], (k*iter2->second.fromCost[i]*iter2->second.rhsSize), end);
			}
		}
	}
	ind--;
	return 0;
}

/*
   double mytot2 = 0;
   for (auto iter4 = mpingred.begin(); iter4 != mpingred.end(); iter4++) {
//printf("**%s %lf\n", iter4->first.c_str(), iter4->second);
if (strcmp(mp[iter4->first.c_str()].from[0], "ORE") == 0) {
//printf("USING: %s %lf\n", iter4->first.c_str(), iter4->second);
mytot2 += (iter4->second * mp[iter4->first].oreSize)/ mp[iter4->first].rhsSize ;
}
}
//printf("** mytot2 [[ %lf ]]\n", mytot2);
assert (mytot2 == mytot);
 */
