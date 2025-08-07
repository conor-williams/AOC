#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;
#define getchar()
int END;
int tot = 0;
#define SIZE 299
char line1[SIZE];

int main(int argc, char **argv)
{
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day14.1\n"); fflush(stdout);

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

	vector <int> var_ints;
	var_ints.push_back(3);
	var_ints.push_back(7);

	int pos1 = 0;
	int pos2 = 1;


	while (var_ints.size() <= after+10) {
		int val = var_ints[pos1] + var_ints[pos2];
		if (val < 10) {
			var_ints.push_back(val);
		} else {
			int singles = val % 10;
			int tens = (val/10)%10;

			var_ints.push_back(tens);
			var_ints.push_back(singles);
		}
		int timesPos1 = var_ints[pos1] + 1 % var_ints.size();
		int timesPos2 = var_ints[pos2] + 1 % var_ints.size(); 

		pos1 = (pos1 += timesPos1) % var_ints.size();
		pos2 = (pos2 += timesPos2) % var_ints.size();

	}

	vector <int> var_ans;
	for (int ii = 0; ii < 10; ii++) {
		var_ans.push_back(var_ints[after+ii]);
	}


	printf("**ans: ");
	for (int ii = 0; ii < 10; ii++) {
		printf("%d", (var_ans[ii]));
	}
	printf("\n");
}
