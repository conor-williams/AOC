#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

#include <unistd.h>

#define getchar()
int nums[1000][1000];
long tot = 0;
int TOTNUMSM1 = 20;
//int TOTNUMSM1 = 5;
int LEVEL;
int done;
int notallzeroes = 0;
char one[4];
string oneS[4];
char two[4];
char tre[4];
void subnums();
void transferandcalc();

struct lr {
	char left[4];
	char rite[4];
};
int main(int argc, char **argv)
{
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("		2023 Day8.1\n"); fflush(stdin); fflush(stdout);
	fflush(stdout); int fd = dup(1); close(1);
	map<string, struct lr> mp;

	char line1[1000];
	char instructs[1000];
	fgets(instructs, 1000, a);
	fgets(line1, 1000, a);
	//build maps
	while (1) {
		done = 0;
		fgets(line1, 1000, a); if (feof(a)) {break;}
		one[0] = line1[0]; one[1] = line1[1]; one[2] = line1[2]; one[3] = '\0';
		string oneS = one;
		two[0] = line1[7]; two[1] = line1[8]; two[2] = line1[9]; two[3] = '\0';
		tre[0] = line1[12]; tre[1] = line1[13]; tre[2] = line1[14]; tre[3] = '\0';
		struct lr tmplr; strcpy(tmplr.left, two); strcpy(tmplr.rite, tre);
		//mp.insert({one, tmplr}); 
		mp[oneS] = tmplr;

		//printf("0: %s\n", one); cout << "oneS: " << oneS << endl; printf("1: %s\n", two); printf("2: %s\n", tre);
		//printf("FOUND: %s left: %s right: %s\n", one, mp.at(oneS).left, mp.at(oneS).rite);

	}

	int tot = 0;
	cout << "strarting parse" << endl;

	string inst = "AAA";
restart:
	cout << "here restart" << endl;
	for (int i = 0; i < 999; i++) {
		printf("next %c ", instructs[i]);
		if (instructs[i] == '\n') {cout << "GOTO..."; goto restart;}
		else {
			tot++;
			if (instructs[i] == 'L') { inst = (string)mp.at(inst).left; }
			else {inst = (string)mp.at(inst).rite;}
			cout << "new inst: " << inst << endl; 
			if (inst == "ZZZ") {printf("found ZZZ..."); break;} 
		}
	}
	fclose(a);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);

}
