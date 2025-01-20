#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2019 day6 part1\n"
#define _DEBUG_

struct Fnode {
	char from[5];
	char to[30][5];	
	int numNodes;
};
	
map<string, struct Fnode> mp;
map<string, struct Fnode> Bmp;
int traverse(string tra, string endPoint);
int ind = 0;
int tot = 0;
int split[100] = {0};
int splitCounters = 0;
int foundEND = 0;

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
       
        char line1[20];

while(1) {
        fgets(line1, 19, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1);
#endif
	char f[5]; char t[5];
	sscanf(line1, "%[^)])%s\n", f, t);
	string fS = f;
	string tS = t;
	map<string, struct Fnode>::iterator mpIter;

	if ((mpIter = mp.find(fS)) == mp.end()) { //first
		struct Fnode n;
		strcpy(n.from, f);
		n.numNodes = 1;
		strcpy(n.to[0], t);
		mp.insert({fS, n});

		struct Fnode dummy;
		strcpy(dummy.from, t);
		dummy.numNodes = 0;
		mp.insert({tS, dummy});
	} else {
		strcpy(mpIter->second.to[mpIter->second.numNodes], t);
		mpIter->second.numNodes++;	

		struct Fnode dummy;
		strcpy(dummy.from, t);
		dummy.numNodes = 0;
		mp.insert({tS, dummy});
	}
		
	map<string, struct Fnode>::iterator mpIter3;
	if ((mpIter3 = Bmp.find(tS)) == Bmp.end()) { //first
		struct Fnode n;
		strcpy(n.from, t);
		n.numNodes = 1;
		strcpy(n.to[0], f);
		Bmp.insert({tS, n});
	} else {
		strcpy(mpIter3->second.to[mpIter3->second.numNodes], f);
		mpIter3->second.numNodes++;	
	}

	leny++;
}
fclose(a);
	char searchStr[10];
	for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) 
	{
		strcpy(searchStr, iter2->first.c_str());
		int found = 0;
		for (auto iter = mp.begin(); iter != mp.end(); iter++) {
			//printf("FROM: %s", iter->first.c_str()); 	
			//printf("TO: \n");
			if (strcmp(searchStr, iter->first.c_str()) == 0) {continue;}
			for (int i = 0; i < iter->second.numNodes; i++) {
				//printf("	%s\n", iter->second.to[i]);
				if (strcmp(iter->second.to[i], searchStr) == 0) {
					found = 1; goto restart;
				}
			}	
		}
restart:
		if (found == 0) {
			printf("Start is %s\n", searchStr);
			break;
		}
	}

	printf("------------\n"); 
	string search = searchStr;
	string endPoint = "L";

	tot = 0;
	for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) {
		printf("%s\n", iter2->first.c_str());
	}

	for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) {
		foundEND = 0;
		if (iter2->first != search) {
			//int totbefore = tot;
			//printf("_____%s____->__ %s__________\n", search.c_str(), iter2->first.c_str());
			traverse(search, iter2->first);
			if (foundEND == 0) {/*printf("***found is zero\n");*/ }
			//printf("__BEF:%d_____AFT:%d____________\n", totbefore, tot); 
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**%d\n", tot); 
}

/*
int whatsafter(string tra) {
	ind++;
	tot++;
	auto iter = mp.find(tra);

	for (int i = 0; i < iter->second.numNodes; i++) {
		int ret;
		if ((ret = traverse(iter->second.to[i], endPoint)) == 33) {
		} else if (ret == 22) {
			return 44;
		} else if (ret == 44) {
			return 44;
		} else {
			tot--;
			continue;
		}
	}	
	if (iter->second.numNodes == 0) {
		//for (int j = 0; j< ind; j++) {printf("	");} printf("%s\n", "END"); 
		ind--;
		return 33;
	}
	ind--;	
	return 0;
}
*/

int traverse(string tra, string endPoint) {
	tot++;
	auto iter = mp.find(tra);
	//for (int j = 0; j< ind; j++) {printf("	");} printf("FROM: [%s]\n", tra.c_str());
	//for (int j = 0; j< ind; j++) {printf("	");} printf("TO:\n");
	if (endPoint == tra) {
		//printf("FOUND endPoint [%s]\n", endPoint.c_str());
		tot--;
		ind--;
		foundEND = 1;
		return 22;
	}

	for (int i = 0; i < iter->second.numNodes; i++) {
		//for (int j = 0; j < ind; j++) {printf("	");} printf("%s\n", iter->second.to[i]);
		int ret;
		if ((ret = traverse(iter->second.to[i], endPoint)) == 33) {
			tot--;
			//printf("ret (END) 33 TOT is %d split was (%d)\n", tot, split[splitCounters]);
			//printf("sub of  is %d\n", split[splitCounters]);
			//printf("splitCounters is %d\n", splitCounters);
		} else if (ret == 22) {
			//printf("ret (ENDpoint) 22 TOT is %d split(%d)\n", tot, split[splitCounters]);
			return 44;
		} else if (ret == 44) {
			//printf("ret 44 TOT is %d split(%d)\n", tot, split[splitCounters]);
			return 44;
		} else {
			//printf("ret **K?***%d TOT is [%d] split(%d)\n", ret, tot, split[splitCounters]);
			tot--;
			continue;
		}
	}	
	if (iter->second.numNodes == 0) {
		//for (int j = 0; j< ind; j++) {printf("	");} printf("%s\n", "END"); 
		return 33;
	}
//	printf("returning 000000 [%s]\n", iter->first.c_str());
	return 0;
}
