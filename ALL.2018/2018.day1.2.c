#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <set>
#include <vector>
#include <unistd.h>

using namespace std;

#define getchar()
long tot = 0;
FILE *a;
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2018 Day1.2\n"); fflush(stdin); fflush(stdout);

	char line1[1000];

	vector <string> ins;
	while (1) {
		fgets(line1, 50, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		ins.push_back(line1);

	}
	set <int> se;
	int tot = 0;
	se.insert(0);
	for (int i = 0; i < (int)ins.size(); i++) {
		int val = atoi(ins[i].c_str());
		tot += val;
		if (se.find(tot) != se.end()) {
			printf("**ans: ");
			printf("%d\n", tot);
			exit(0);
		}

		se.insert(tot);
		if (i == (int)ins.size() -1) {i = -1;}


	}
}


