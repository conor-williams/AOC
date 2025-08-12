#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>

#define getchar()

using namespace std;
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r");
	printf("		2023 Day4.2\n");

	fflush(stdout); int fd = dup(1); close(1);


	//	Pattern p = Pattern.compile("Card[\\s]+(\\d+): ([\\s\\d]+) \\| ([\\s\\d]+)");

	map <int, int> mp;
	vector<string> blah;

	char line1[1000];
	while (1) {
		fgets(line1, 1000, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		blah.push_back(line1);
	}

	int maxCardNum = 0;
	for (int i = 0; i < blah.size(); i++) {

		char cNum[100];
		char f1[100];
		char f2[100];
		sscanf(blah[i].c_str(), "Card%[^:]: %[^|] %[^\0]", cNum, f1, f2);
		int cardNum = atoi(cNum);
		mp[cardNum] = 1;
		if (cardNum > maxCardNum) {
			maxCardNum = cardNum;
		}
	}
	for (int i = 0; i < blah.size(); i++) {
		vector <int> var_wins;
		vector <int> var_play;

		char cNum[100];
		char winningNums[300];
		char playNums[300];
		sscanf(blah[i].c_str(), "Card%[^:]: %[^|] %[^\0]", cNum, winningNums, playNums);
		int cardNum = atoi(cNum);

		{
			char *bl = strtok(winningNums, "	 ");
			while (bl != NULL) {
				var_wins.push_back(atoi(bl));
				bl = strtok(NULL, "	 ");
			}
		}
		{
			char *bl2 = strtok(playNums, "	 ");
			while (bl2 != NULL) {
				var_play.push_back(atoi(bl2));
				bl2 = strtok(NULL, "	 ");
			}
		}
		vector <int> inter;
		sort(var_wins.begin(), var_wins.end());
		sort(var_play.begin(), var_play.end());
		set_intersection(var_wins.begin(), var_wins.end(), var_play.begin(), var_play.end(), back_inserter(inter));

		if (inter.size() != 0) {
			int wi = inter.size();
			for (int zz = cardNum+1; zz < cardNum+1+wi; zz++) {
				if (zz > maxCardNum) {
					break;
				} else {
					mp[zz] = mp[cardNum]+mp[zz];

				}
			}
		}

	}
	int tot = 0;
	for (auto pa : mp) {
		tot += mp[pa.first];
	}


	fflush(stdout); dup2(fd, 1);
	printf("***ans:  %d\n", tot);
}

