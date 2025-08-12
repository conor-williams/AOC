#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <vector>
#include <string>
#include <unistd.h>

#define getchar()
#include <unistd.h>


using namespace std;
int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
int checkAround(vector <pair <int, int>> ve, int xlen, int ylen);
bool charOk(char gg);
char grid[200][200];
int leny = 0;
int main(int argc, char **argv)
{
	FILE * a = fopen(argv[1], "r");
	printf("		2023 Day3.1\n");

	fflush(stdout); int fd = dup(1); close(1);

	fflush(stdin); fflush(stdout);
	int sum = 0;
	vector <string> blah;
	char line1[1000];
	while (1) {
		fgets(line1, 1000, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		blah.push_back(line1);
		strcpy(grid[leny], line1);
		leny++;

	}
	int totGood = 0;
	for (int i = 0; i < blah.size(); i++) {
		string line1 = blah[i];
		vector <pair <int, int>> pointdigit;
		for (int kk = 0; kk < line1.length(); kk++) {
			char ch = line1[kk];
			if (isdigit(ch)) {
				pair <int, int> tu = make_pair(kk, i);
				pointdigit.push_back(tu);
			} else if (!isdigit(ch) && pointdigit.size() > 0) {
				totGood += checkAround(pointdigit, line1.length(), blah.size());
				pointdigit.clear();
			}
			if (pointdigit.size() > 0 && kk==line1.length()-1) {
				totGood += checkAround(pointdigit, line1.length(), blah.size());
				pointdigit.clear();
			}
		}
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	printf("%d", totGood);
	printf("\n");
}

int checkAround(vector <pair <int, int>> ve, int xlen, int ylen) {
	char thechars[20];
	for (int ii = 0; ii < ve.size(); ii++) {
		pair <int, int> tu = ve[ii];
		int x = tu.first; int y = tu.second;
		thechars[ii] = grid[y][x];
	}
	int found = 0;
	for (int ii = 0; ii < ve.size(); ii++) {
		pair <int, int> tu = ve[ii];
		int x = tu.first; int y = tu.second;


		if (x-1 >= 0 && y-1 >=0       && !charOk(grid[y-1][x-1])) {
			found = 1;
			break;
		}
		if (y-1 >= 0                  && !charOk(grid[y-1][x])) {
			found = 1;
			break;
		}
		if (x+1 < xlen && y-1 >= 0    && !charOk(grid[y-1][x+1])) {
			found = 1;
			break;
		}
		if (x+1 < xlen                && !charOk(grid[y][x+1])) {
			found = 1;
			break;
		}
		if (x+1 < xlen && y+1 < ylen  && !charOk(grid[y+1][x+1])) {
			found = 1;
			break;
		}
		if (y+1 < ylen                && !charOk(grid[y+1][x])) {
			found = 1;
			break;
		}
		if (x-1 >= 0 && y+1 < ylen    && !charOk(grid[y+1][x-1])) {
			found = 1;
			break;
		}
		if (x-1 >= 0                  && !charOk(grid[y][x-1])) {
			found = 1;
			break;
		}

	}
	if (found == 0) {return 0;}
	else {
		string ss = thechars;
		ss = ss.substr(0, ve.size());
		//return int.valueOf(new string(thechars, 0, ve.size()));
		return atoi(ss.c_str());
	}
}
bool charOk(char gg) {
	bool ok = true;

	switch (gg) {
		case '.':
			break;
		case '#':
		case '$':
		case '%':
		case '&':
		case '*':
		case '+':
		case '-':
		case '/':
		case '=':
		case '@':
			ok = false;
			break;
	}
	return ok;
}
