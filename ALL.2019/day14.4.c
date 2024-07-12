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
int search(char *start, double startCost, char *end, double val);
map <string, double> mptot;
map <string, double> mpingred;
map <string, double> mpspare;
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
		n.toCost = 1; //1;// toCost;
		n.rhsSize = toCost;
		n.numNodes = 0;
		char *first = strtok(f, ",\0");
		do {
			double cost; char wat[50];
			sscanf(first, "%lf %s", &cost, wat);
			strcpy(n.from[n.numNodes], wat);
			if (strcmp(wat, "ORE") == 0) {n.oreSize = cost;}
			n.fromCost[n.numNodes] = cost/toCost; ////toCost;
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
				if (mpingred.find(iter2->second.from[i]) == mpingred.end()) {
					mpingred.insert({iter2->second.from[i], iter2->second.fromCost[i]});
				}
				printf("search out: %s\n", iter2->second.from[i]); getchar();
				search(iter2->second.from[i], iter2->second.fromCost[i], (char *)"ORE", val);
			}
		//	getchar();
			break;
		}
	}
	double mytot = 0;
	for (auto iter4 = mpingred.begin(); iter4 != mpingred.end(); iter4++) {
		printf("%s %lf\n", iter4->first.c_str(), iter4->second);
		if (strcmp(mp[iter4->first].from[0], "ORE") == 0) {
			printf("USING: %s %lf\n", iter4->first.c_str(), iter4->second);
			for (int i = 1; i < 3000 ; i++) {
				if (i * mp[iter4->first].rhsSize >= iter4->second) {
					iter4->second = i*mp[iter4->first].rhsSize;
					break;
				}
			}
			printf("AFTER USING: %s %lf\n", iter4->first.c_str(), iter4->second);
			mytot += (double)iter4->second/(double)mp[iter4->first].rhsSize * (double) mp[iter4->first].oreSize;	
				
		}
	}
	printf("** mytot [[ %lf ]]\n", mytot);
	exit(0);

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
int ind = 0;
int search(char *start, double startCost, char *end, double val) {
	{
		ind++;
		auto iter2 = mp.find(start);
		for (int q = 0; q < ind; q++) {printf("  ");}
		printf("in search... RHS: %s %lf\n", iter2->first.c_str(), iter2->second.rhsSize);

		getchar();
		if (strcmp(iter2->first.c_str(), start) == 0) {
			for (int i = 0; i < iter2->second.numNodes; i++) {
				if (strcmp(iter2->second.from[i], end) == 0) {
					string s1 = iter2->second.from[i];
					double cost = iter2->second.fromCost[i];
					int k;
					double spare;
					if (mpspare.find(iter2->second.to) == mpspare.end()) {
						spare = 0;
					} else {
						spare = mpspare[iter2->second.to];
					}

					spare = 0;
					printf("spare is %lf\n", spare);

/*
					for (k = 1; k < 3000; k++) {
						
						if (startCost <= (k*iter2->second.rhsSize)+spare) {
							//mpspare[iter2->second.to] = ((k*iter2->second.rhsSize)+spare) - startCost;
							printf("spare == %lf for (%s)\n", mpspare[iter2->second.to], iter2->second.to); getchar();
							break;
						}
					}
*/
/*
					if (mpingred.find(iter2->second.to) == mpingred.end()) {
						mpingred.insert({iter2->second.to, (iter2->second.rhsSize)});
					} else {
						mpingred[iter2->second.to] += (iter2->second.rhsSize);
					}
*/
				} else {
					string s1 = iter2->second.from[i];
					double cost = iter2->second.fromCost[i];
					int k;
					double spare;
					if (mpspare.find(iter2->second.to) == mpspare.end()) {
						spare = 0;
					} else {
						spare = mpspare[iter2->second.to];
					}

					spare = 0;

					
	//				for (int q = 0; q < ind; q++) {printf("  ");} printf("spare is %lf\n", spare);
	//				for (int q = 0; q < ind; q++) {printf("  ");} printf("%s...\n", iter2->second.from[i]); getchar();
	//				for (int q = 0; q < ind; q++) {printf("  ");} printf("--k is %d comparing (startCost): %lf with k*rhs+spare: %lf\n", k, startCost, (k*iter2->second.rhsSize)+spare); 
	//				getchar();
/*
					for (k = 1; k < 3000; k++) {
						if (startCost <= (k*iter2->second.rhsSize)+spare) {
							for (int q = 0; q < ind; q++) {printf("  ");} printf("k is %d\n", k);
							getchar();
							//mpspare[iter2->second.to] =
                                                         //       ((k*iter2->second.rhsSize)+spare) - startCost;
							for (int q = 0; q < ind; q++) {printf("  ");} printf("spare == %lf for (%s)\n", mpspare[iter2->second.to], iter2->second.to); getchar();
							break;
						}
					}
*/
					if (mpingred.find(iter2->second.to) == mpingred.end()) {
						mpingred.insert({iter2->second.to, (iter2->second.rhsSize)});
					} else {
						mpingred[iter2->second.to] += (iter2->second.rhsSize);
					}
					search(iter2->second.from[i], iter2->second.fromCost[i], end, val*iter2->second.fromCost[i]);
					getchar();
				}
			}
		}
	}
	ind--;
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
