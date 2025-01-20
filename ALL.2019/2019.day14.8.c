#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;

int lenx, leny;
#define DAY "2019 day14 part1\n"
#define _DEBUG_

struct Fnode {
	char to[50];
	double toCost;
	char from[300][50];	
	double fromCost[300];
	double oreSize;
	double rhsSize;
	int numNodes;
};
struct val_s {
	double val;
	double cost;
};
	
map<string, struct Fnode> mp;
int search(char *start, char *end, double val);
map <string, double> mptot;
map <string, struct val_s> mpingred;
#define SIZE 300

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
       
        char line1[SIZE];

//2 JNLZG => 7 SJTKF
while(1) {
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: [%s]\n", line1);
#endif
	char f[300]; char t[50]; int toCost;
	sscanf(line1, "%[^=]=> %d %s", f, &toCost, t);

	string tS = t;
	//string fS = f;

	cout << "tS: " << tS << endl;
	if (mp.find(tS) == mp.end()) { 
		struct Fnode n;
		strcpy(n.to, t);
		n.toCost = 1;// toCost;

		n.rhsSize = toCost;
		n.numNodes = 0;
		char *first = strtok(f, ",\0");
		do {
			double cost; char wat[50];
			sscanf(first, "%lf %s", &cost, wat);
			strcpy(n.from[n.numNodes], wat);
			if (strcmp(wat, "ORE") == 0) {n.oreSize = cost;}
			n.fromCost[n.numNodes] = cost/toCost;
			printf("writing to node: %lf %s\n", n.fromCost[n.numNodes], n.from[n.numNodes]);
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
	for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) 
	{
		printf("RHS: %s\n", iter2->first.c_str());
		if (strcmp(iter2->first.c_str(), "FUEL") == 0) {
			for (int i = 0; i < iter2->second.numNodes; i++) {
				printf("%lf %s\n", iter2->second.fromCost[i], iter2->second.from[i]);
				double val = iter2->second.fromCost[i];
				search(iter2->second.from[i], (char *)"ORE", val);
			}
		//	getchar();
			break;
		}
	}
/*
	for (auto iter4 = mpingred.begin(); iter4 != mpingred.end(); iter4++) {
		//struct val_s mine = iter4->second;
		if (iter4->first != "ORE" && iter4->first != "FUEL") {
			for (int k = 1; k < 30000; k++) {
				double ans = mp[iter4->first].rhsSize * k;
				printf("(%s) ans is %lf V iter4->second.val %lf\n", iter4->first.c_str(), ans, iter4->second.val);
				if (ans >= iter4->second.val) {
					//iter4->second = ans;
					printf("updating mptot from %lf to %lf\n", mptot[iter4->first],
						ans*iter4->second.cost);
					mptot[iter4->first] = ans*iter4->second.cost;
					
					break;
				}
			}
		}
	}
*/

	for (auto iter3 = mptot.begin(); iter3 != mptot.end(); iter3++) {
		printf("-- %lf\n", mp[iter3->first].oreSize);
		int i;
		for (i = 1; i < 30000; i++) {
			double ans = mp[iter3->first].oreSize * i;
	
			if (ans >= iter3->second) {printf("was: %lf\n", iter3->second); iter3->second = ans; break;}
		}
		printf("%s == %lf\n", iter3->first.c_str(), iter3->second);
	}

	double tot2 = 0;
	for (auto iter3 = mptot.begin(); iter3 != mptot.end(); iter3++) {
		tot2 += iter3->second;
	}
	
	printf("**%lf\n", tot2); 
}

int search(char *start, char *end, double val) {
	//for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) 
	{
		auto iter2 = mp.find(start);
		//struct Fnode = iter2->second;
		printf("in search... RHS: %s\n", iter2->first.c_str());

		if (strcmp(iter2->first.c_str(), start) == 0) {
			for (int i = 0; i < iter2->second.numNodes; i++) {
				if (strcmp(iter2->second.from[i], end) == 0) {
					
					if (mptot.find(iter2->first) == mptot.end()) {
						mptot.insert({iter2->first, val*iter2->second.fromCost[i]});
					} else {
						mptot[iter2->first] += val*iter2->second.fromCost[i];
					}
					printf("found %s...val: %lf.\n", end, val*iter2->second.fromCost[i]);
				} else {
/*
					string s1 = iter2->second.from[i];
					struct val_s myval;	
					myval.val = val;
					myval.cost = iter2->second.fromCost[i];
					if (mpingred.find(s1) == mpingred.end()) {
						mpingred.insert({s1, myval});
						printf("new set val to %lf\n", myval.val);
					} else {
						mpingred[s1].val += myval.val;
						printf("set val to %lf\n", myval.val);
					}
					printf("SEarch %s, %lf,%lf\n", iter2->second.from[i], val, iter2->second.fromCost[i]);
*/
					search(iter2->second.from[i], end, val*iter2->second.fromCost[i]);

				}
			}
		//	getchar();
			//break;
		}
	}
	return 0;
}
/*
					for (int k = 1; k < 30000; k++) {
						double ans = mp[iter2->first].rhsSize * k;
						printf("ans is %lf V val %lf\n", ans, val);
						if (ans >= val) {
							//mptot[iter2->first] += ans*iter2->second.fromCost[i];
							search(iter2->second.from[i], end, ans*iter2->second.fromCost[i]);
							break;
						}
					}
*/
