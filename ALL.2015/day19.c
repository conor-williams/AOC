#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <bits/stdc++.h>
#include <string>

using namespace std;

int lenx, leny;
#define DAY "2015 day18 part1\n"
#undef _DEBUG_
multimap <string, string> mp;
map <string, string> mpStore;
char mol[1000];
#define getchar()
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	//printf(DAY); fflush(stdin); fflush(stdout);
       
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
		printf(" from %s ---- to %s\n", from, to1);
	}

	if (line1[0] == '\0') {
		readMol = 1;
	}

	leny++;
}
	
	printf("molstring is %s\n", molString.c_str());
	for (auto it = mp.begin(); it != mp.end(); it++) {
		int found = -1;
		printf("searching for %s\n", it->first.c_str());
		while ((found = molString.find(it->first, found+1)) != (int)string::npos) {
			string molTmp = molString;
			molTmp.replace(found, it->first.length(), it->second);	
			mpStore.insert({molTmp, it->first});
			printf("molTmp %s\n", molTmp.c_str());
			printf("found is %d of %s\n", found, it->first.c_str()); getchar();
		}
			
	}
	int tot = 0;
	printf("****tot %d\n", (int)mpStore.size());
}
