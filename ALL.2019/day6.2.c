#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>

using namespace std;

int lenx, leny;
#define DAY "2019 day6 part1\n"
#define _DEBUG_
char already[1000][20];
int alreadyPos = 0;
struct Fnode {
	char from[5];
	char to[30][5];	
	int numNodes;
};
	
map<string, struct Fnode> mp;
map<string, struct Fnode> Bmp;
map<string, struct Fnode> mpBOTH;
int traverse(string tra, string endPoint);
int traverse2(string tra, string endPoint);
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

	map<string, struct Fnode>::iterator mpBOTHIter;
	if ((mpBOTHIter = mpBOTH.find(fS)) == mpBOTH.end()) { //first
		struct Fnode n;
		strcpy(n.from, f);
		n.numNodes = 1;
		strcpy(n.to[0], t);
		mpBOTH.insert({fS, n});

		struct Fnode dummy;
		strcpy(dummy.from, t);
		dummy.numNodes = 0;
		mpBOTH.insert({tS, dummy});
	} else {
		strcpy(mpBOTHIter->second.to[mpBOTHIter->second.numNodes], t);
		mpBOTHIter->second.numNodes++;	

		struct Fnode dummy;
		strcpy(dummy.from, t);
		dummy.numNodes = 0;
		mpBOTH.insert({tS, dummy});
	}
		
	map<string, struct Fnode>::iterator mpBOTHIter3;
	if ((mpBOTHIter3 = mpBOTH.find(tS)) == mpBOTH.end()) { //first
		struct Fnode n;
		strcpy(n.from, t);
		n.numNodes = 1;
		strcpy(n.to[0], f);
		mpBOTH.insert({tS, n});
	} else {
		strcpy(mpBOTHIter3->second.to[mpBOTHIter3->second.numNodes], f);
		mpBOTHIter3->second.numNodes++;	
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
			//printf("FROM: %s", iter->first.c_str()); getchar();
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
	string search = "W54";
	string ENDPOINT = "2JB";

	//for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) {
	//	printf("%s\n", iter2->first.c_str());
	//}
	tot = 0;
	traverse2(search, ENDPOINT); //getchar();

/*
	for (auto iter2 = mp.begin(); iter2 != mp.end(); iter2++) {
		foundEND = 0;
		if (iter2->first != search) {
			int totbefore = tot;
			printf("_____%s____->__ %s__________\n", search.c_str(), iter2->first.c_str());
			traverse(search, iter2->first); break;
			if (foundEND == 0) {
			printf("__BEF:%d_____AFT:%d____________\n", totbefore, tot); 
		}
	}
*/
	printf("**%d\n", tot); 
}

int traverse2(string tra, string endPoint) {
	ind++; tot++; int found = 0;
	for (int i = 0; i < alreadyPos; i++) {
		if (strcmp(already[i], tra.c_str()) == 0) {
			found = 1; break;
		}
	}
	if (found == 0) {
		strcpy(already[alreadyPos], tra.c_str()); alreadyPos++;
	} else {
		ind--;
		return 0;
	}

	auto iter = mpBOTH.find(tra);
			for (int j = 0; j< ind; j++) {printf("	");}
 printf("FROM: [%s]\n", tra.c_str()); 
			for (int j = 0; j< ind; j++) {printf("	");} printf("TO:\n");
	if (endPoint == tra) {
		tot--; ind--;
		printf("FOUND endPoint [%s] tot %d \n", endPoint.c_str(), tot); getchar();
		return 22;
	}

	for (int i = 0; i < iter->second.numNodes; i++)  {
//	for (int i = iter->second.numNodes -1 ; i>=0 ; i--)  
		int ret;
		if ((ret = traverse2(iter->second.to[i], endPoint)) == 33) {
			tot--;
			for (int j = 0; j< ind; j++) {printf("	");} printf("ret (END) 33 TOT is %d\n", tot); // and on...
		} else if (ret == 22) { /*dont worrry about this one*/
			for (int j = 0; j< ind; j++) {printf("	");} printf("ret (ENDpoint) 22 TOT is %d\n", tot); 
			ind--;
			return 44;
		} else if (ret == 44) { /*dont worry about this one */
			for (int j = 0; j< ind; j++) {printf("	");} printf("ret 44 TOT is %d\n", tot);
			ind--;
			return 44;
		} else {
			tot--;
			for (int j = 0; j< ind; j++) {printf("	");} printf("ret: %d **K?continue (of %s) *** TOT is [%d]\n", ret, iter->second.to[i], tot);
			continue;
		}
	}	
	if (iter->second.numNodes == 0) {
		for (int j = 0; j< ind; j++) {printf("	");} printf("EVER HERE????"); getchar(); getchar();
		for (int j = 0; j< ind; j++) {printf("	");} printf("%s\n", "AN END REACHED"); 
		ind--;
		return 33;
	}
	ind--;
	return 0;
}
int traverse(string tra, string endPoint) {
	ind++;
	tot++;
	auto iter = mp.find(tra);
	for (int j = 0; j< ind; j++) {printf("	");} printf("FROM: [%s]\n", tra.c_str());
	for (int j = 0; j< ind; j++) {printf("	");} printf("TO:\n");
	if (endPoint == tra) {
		printf("FOUND endPoint [%s]\n", endPoint.c_str());
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
			ind--;
			return 44;
		} else if (ret == 44) {
			//printf("ret 44 TOT is %d split(%d)\n", tot, split[splitCounters]);
			ind--;
			return 44;
		} else {
			//printf("ret **K?***%d TOT is [%d] split(%d)\n", ret, tot, split[splitCounters]);
			tot--;
			continue;
		}
	}	
	if (iter->second.numNodes == 0) {
		//for (int j = 0; j< ind; j++) {printf("	");} printf("%s\n", "END"); 
		ind--;
		return 33;
	}
//	printf("returning 000000 [%s]\n", iter->first.c_str());
	ind--;
	return 0;
}
