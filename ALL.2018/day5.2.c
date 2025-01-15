#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>

using namespace std;

#include <unistd.h>

#define getchar()
int ReplaceString(string &subject, const string search, const string replace);
string rep;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("2018 Day5.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int SIZE = 60000;
	char line1[SIZE];

	int leny = 0;
	while (1) 
	{
		fgets(line1, SIZE, a);
		if (feof(a)) break;
		printf("line1 %s\n", line1);
		line1[(int)strlen(line1)-1] = '\0';
		leny++;
	}

	//rep = line1;
	int min = 99999999;
	for (int kk = 0; kk<26; kk++) {
		rep = line1;
		string se1; se1.push_back(65+kk);
		ReplaceString(rep, se1, "");
		string se2; se2.push_back(97+kk);
		ReplaceString(rep, se2, "");
ag:
		int mark =0;
		for (int i = 0; i < 26; i++) {
			char se1[4];
			sprintf(se1, "%c%c", 65+i, 97+i);	
			int ch = ReplaceString(rep, se1, "");
			if (ch == 0) {mark=1;}
			char se2[4];
			sprintf(se2, "%c%c", 97+i, 65+i);	
			printf("se2 %s\n", se2); printf("se1 %s\n", se1);
			ch = ReplaceString(rep, se2, "");
			if (ch == 0) {mark=1;}
		}
		if (mark == 1) {goto ag;}

		if ((int)rep.length() < min) {min = (int)rep.length();}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", min);
}


int ReplaceString(string &subject, const string search, const string replace) {
	size_t pos = 0;
	int none = 1;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		//pos += replace.length();
		pos--;
		if (none == 1) {none = 0;}
	}
	return none;
}
