#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <bits/stdc++.h>
#include <string>
#include <vector>

#include <unistd.h>
using namespace std;

int lenx, leny;
#define DAY "		2015 day19 part2\n"
#undef _DEBUG_
multimap <string, string> mp;
map <string, string> mpStore;
map <string, string> mpB;
char mol[1000];
#define getchar()
vector <string> V;
vector <string> e_ans;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
	int fd = dup(1); close(1);

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
			printf(" from %s ---- to %s\n", from, to1);
			mp.insert({fr, to});
			mpB.insert({to, fr});
			if (strcmp(from, "e") == 0) {
				e_ans.push_back(to);
			}
		}

		if (line1[0] == '\0') {
			readMol = 1;
		}

		leny++;
	}

	printf("mp.size() is %d\n", (int)mp.size());
	printf("mpB.size() is %d\n", (int)mpB.size());
	getchar();
	string orig = molString;
	printf("molstring is %s\n", molString.c_str());
	string prev;
	for (auto it = mpB.rbegin(); it != mpB.rend(); it++) {
		V.insert(V.end(), it->first);
	}

	int tot = 1;
restart:
	prev = molString;
	int found = -1;

	for (int i =0; i < (int)V.size(); i++) {
		if (mpB[V.at(i)] != "e") {
			//printf("searching for %s\n", V.at(i).c_str()); fflush(stdout);
			found = -1;
			while ((found = (int)molString.rfind(V.at(i))) != (int)string::npos) {
				molString.replace(found, V.at(i).length(), mpB[V.at(i)]);	
				tot++;
			}
		}
	}
	if (prev != molString) {
		//printf("mo2: %s\n", molString.c_str()); 
		//printf("going to restart...\n"); //getchar();
		goto restart;
	} 

	//only one solution
	printf("molString is %s\n", molString.c_str());
	if (find(e_ans.begin(), e_ans.end(), molString) != e_ans.end()) {
		printf("found tot: %d yatzee..\n", tot);
		//getchar();
		//random_shuffle(V.begin(), V.end());
		//molString = orig;
	} else {
	//if (prev == molString) 
		//printf("molString is %s\n", molString.c_str());
		//printf("SHUFFLE...\n");
		//printf("mo3: %s\n", molString.c_str()); 
		//system("grep \"e =>\" i1.txt");
		random_shuffle(V.begin(), V.end());
		//printf("V.at(0) is %s\n", V.at(0).c_str());
		molString = orig;
		//tot++;
		//printf("****tot %d\n", tot);
		tot = 1;
		//getchar();
		goto restart;
	}
		
	fflush(stdout); dup2(fd, 1);
	//printf("mo2: %s\n", molString.c_str()); 
	printf("**ans: %d\n", tot);
}
