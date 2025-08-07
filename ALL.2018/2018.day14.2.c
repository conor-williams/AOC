#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>

using namespace std;
#define getchar()
int END;
int tot = 0;
#define SIZE 299
char line1[SIZE];

int main(int argc, char **argv)
{
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day14.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1);
	int after = 0;
	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[(int)strlen(line1)-1] = '\0';

		after = atoi(line1);
	}
	fclose(a);

	vector <char> var_ans;
	int after2 = after;
	for (int ii = 0; ; ii++) {
		if (after > pow(10, ii)) {
			var_ans.push_back((char)((int)((after/(int)pow(10, ii)) % 10)+48));
		} else {
			break;
		}
	}

	reverse(var_ans.begin(), var_ans.end());
	int numnums = var_ans.size();

	vector <char> var_chars;
	var_chars.push_back((char)(3+48));
	var_chars.push_back((char)(7+48));

	int pos1 = 0;
	int pos2 = 1;

	int ansans = 0;
	for (int zzz = 0; zzz < 40000000 ; zzz++) {
		int val = var_chars[pos1]-48 + var_chars[pos2]-48;
		if (val < 10) {
			var_chars.push_back((char)(val+48));
		} else {
			int singles = val % 10;
			int tens = (val/10)%10;

			var_chars.push_back((char)(tens+48));
			var_chars.push_back((char)(singles+48));
		}
		int sz = var_chars.size();
		int timesPos1 = (var_chars[pos1] + 1 -48) % sz;
		int timesPos2 = (var_chars[pos2] + 1 -48) % sz; 

		pos1 = (pos1 += timesPos1) % sz;
		pos2 = (pos2 += timesPos2) % sz;


		if (sz > numnums+1) {
			int found = 0;
			for (int kk = 0; kk < numnums; kk++) {
				if (var_chars[sz-numnums-1+kk] != var_ans[kk]) {
					found = 1;
					break;
				}
			}
			if (found == 0) {
				ansans = sz-numnums-1;
				break;
			}
		}

	}

	printf("**ans: ");
	printf("%d", ansans);
	printf("\n");
}
