#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <bits/stdc++.h>
#include <string>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

int lenx, leny;
#define DAY "2015 day19 part2\n"
#undef _DEBUG_
multimap <string, string> mp;
map <string, string> mpStore;
map <string, string> mpB;
char mol[1000];
#define getchar()
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
	printf("broken\n"); exit(0);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	int readMol = 0;
	string molString;
	while(1) {
		fgets(line1, 999, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
		if (readMol == 1) {	
			molString = line1;
		} else if (line1[0] != '\0') {
			char from[20]; char to1[20];
			sscanf(line1, "%s => %s", from, to1);
			string fr = from; string to = to1;
			mp.insert({fr, to});
			mpB.insert({to, fr});
			printf(" from %s ---- to %s\n", from, to1);
		}

		if (line1[0] == '\0') {
			readMol = 1;
		}

		leny++;
	}

	printf("molstring is %s\n", molString.c_str());
	string prev;
	int tot = 0;
restart:
	prev = molString;
	string lens[50]; int lensPos = 0;
	int found = -1;
	lensPos = 0;
	/*
	   for (auto it = mpB.rbegin(); it != mpB.rend(); it++) {
	   printf("%s %s\n", it->first.c_str(), it->second.c_str());
	   }
	   getchar();
	   */
	for (auto it = mpB.rbegin(); it != mpB.rend(); it++) {
		if (it->second != "e") {
			printf("searching for %s\n", it->first.c_str()); fflush(stdout);
			found = -1;
			if ((int)molString.rfind(it->first) != (int)string::npos) {
				lens[lensPos] = it->first; lensPos++;
			}
			//while ((found = molString.rfind(it->first)) != (int)string::npos) {

			//string molTmp = molString;
			//molString.replace(found, it->first.length(), it->second);	
			//mpStore.insert({molTmp, it->first});
			//printf("molTmp %s\n", molTmp.c_str());
			///printf("found is %d of %s\n", found, it->first.c_str()); getchar();
			//printf("mo: %s\n", molString.c_str()); 
			//tot++;
			//}
		}
	}
	int max = 0; int maxPos = 0;
	printf("lensPos is %d\n", lensPos);
	for (int i = 0; i < lensPos; i++) {
		int mylen =((int)lens[i].length() - (int)mpB[lens[i]].length()); 
		if (mylen >= max) {max = mylen; maxPos = i;}
	}
	printf("conv %s to %s\n", lens[maxPos].c_str(), mpB[lens[maxPos]].c_str());
	printf("moString: %s\n", molString.c_str()); getchar();
	found = molString.find(lens[maxPos]);
	molString.replace(found, lens[maxPos].length(), mpB[lens[maxPos]]);	
	/*
	   do {
	   if (lens[maxPos] == "") {break;}
	   found = molString.rfind(lens[maxPos]);
	   printf("found is %d: [%s]\n", found, lens[maxPos].c_str()); getchar();
	   if (found != -1) {
	   molString.replace(found, lens[maxPos].length(), mpB[lens[maxPos]]);	
	   }
	   } while (found != -1);
	   */
	if (prev != molString) {
		printf("mo2: %s\n", molString.c_str()); 
		printf("going to restart...\n"); getchar();
		goto restart;
	} 
	//if (prev != molString) {
	//	goto restart;
	//}

	fflush(stdout); dup2(fd, 1);
	printf("mo2: %s\n", molString.c_str()); 
	printf("****tot %d\n", tot);
}
