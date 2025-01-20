#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define getchar()
struct acard {
	char card[6];
	int bid ;
};

int posmap[7];
struct acard *cmap[7];
int whatsin[17];
bool compdec(int a, int b);

vector <string> ve[10];
map <string, int> mp;
bool comp123(string a, string b);

int main(int argc, char **argv)
{
	printf("%d", argc);
	printf("%s", argv[1]);
	fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("Day7.2\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	//int done = 1;
	while (1) {
		int TYPE = 0; //int POS = 0; //done = 1;
		fgets(line1, 1000, a); if (feof(a)) {break;}
		char cards[20] = ""; int bid = 0;
		sscanf(line1, "%s %d", cards, &bid);
		for (int ii = 0; ii < 5; ii++) {
			switch (cards[ii]) {
				case 'T':
					cards[ii] = 'a';
					break;
				case 'J':
					cards[ii] = '1';
					break;
				case 'Q':
					cards[ii] = 'c';
					break;
				case 'K':
					cards[ii] = 'd';
					break;
				case 'A':
					cards[ii] = 'e';
					break;
			}
		}
		mp[cards] = bid;
		printf("GOT cards: %s bid: %d\n", cards, bid);
		memset(whatsin, 0, sizeof(whatsin));
		for (int k = 0; k <= 4; k++) {
			switch(cards[k]) {
				case '1': whatsin[1]++;
					  break;
				case '2': whatsin[2]++;
					  break;
				case '3': whatsin[3]++;
					  break;
				case '4': whatsin[4]++;
					  break;
				case '5': whatsin[5]++;
					  break;
				case '6': whatsin[6]++;
					  break;
				case '7': whatsin[7]++;
					  break;
				case '8': whatsin[8]++;
					  break;
				case '9': whatsin[9]++;
					  break;
				case 'a': whatsin[10]++;
					  break;
				case 'c': whatsin[12]++;
					  break;
				case 'd': whatsin[13]++;
					  break;
				case 'e': whatsin[14]++;
					  break;
				default:
					  printf("ERR"); exit(0);
			}
		}
		int max = 0;
		int maxii;
		if (whatsin[1] > 0) {
			for (int ii = 2; ii <= 14; ii++) {
				if (whatsin[ii] > max) {max = whatsin[ii]; maxii = ii;}
			}
		}
		if (max > 0) {
			whatsin[maxii] += whatsin[1];
			whatsin[1] = 0;
		}

		sort(whatsin, whatsin+15);
	
		for (int j = 14; j>=1; j--) {
			if (whatsin[j] == 5) {
				assert(j == 14);
				printf("GOT FIVE of a KIND\n"); fflush(stdout);
				TYPE = 6; goto aft2;
			} else if (whatsin[j] == 4) {
				assert(j == 14);
				printf("got FOUR OF A KIND\n");
				TYPE = 5; goto aft2;
			} else if (whatsin[j] == 3) {
				assert(j == 14);
				for (int k = j-1; k>=1; k--) {
					if (whatsin[k] == 2) {
						assert(k == 13);
						printf("GOT FULL HOUSE\n"); fflush(stdout);
						TYPE = 4;
						goto aft2;
					}
				}
				printf("GOT THREE OF A KIND\n"); fflush(stdout);
				TYPE = 3;
				goto aft2;
			} else if (whatsin[j] == 2) {
				assert(j == 14);
				for (int k = j-1; k>=1; k--) {
					if (whatsin[k] == 2) {
						printf("GOT TWO pair\n");
						TYPE = 2;
						goto aft2;
					}
				}
				printf("GOT ONE pair\n");
				TYPE = 1; goto aft2;
			} else {
				{printf("GOT high card\n"); TYPE = 0; goto aft2;} 
			}
		}
aft2:
		ve[TYPE].push_back(cards);
	}
	fclose(a);

	printf("before sort zero\n"); fflush(stdout);

	//sort(ve[0].begin(), ve[0].end(), comp123);
	printf("after sort zero\n");fflush(stdout);
	for (int i = 0; i <= 6; i++) {
		sort(ve[i].begin(), ve[i].end());
		printf("aftersort\n");
	}

	long long tot = 0;
	int pos = 1;
	for (int k = 0; k <= 6; k++ ) {
		for (auto ca: ve[k]) {
			tot += pos * mp[ca];
			pos++;
		}
	}
	printf("pos is %d\n", pos);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", tot);

}
bool compdec(int a, int b) {
	return a > b;
}
bool comp123(string a, string b) {
	char hia='0'; char hib='0';
	printf("a: %s\n", a.c_str());
	printf("b: %s\n", b.c_str()); fflush(stdout);
	for (int ii = 0; ii < 5; ii++) {
		if (a[ii] > hia) {hia = a[ii];}
		printf("here1\n"); fflush(stdout);
	}
	for (int ii = 0; ii < 5; ii++) {
		if (b[ii] > hib) {hib = b[ii];}
		printf("here2\n"); fflush(stdout);
	}
		
	printf("%c v %c\n", hia, hib); fflush(stdout);
	if (hia > hib) {
		printf("here3\n"); fflush(stdout);
		return false;
		//return a > b;
	} else if (hib > hia) {
		printf("here4\n"); fflush(stdout);
		return true;
		//return hib>hia;
		//return b > a;
	} else if (hia == hib) {
		printf("here5\n"); fflush(stdout);
		for (int kk = 0; kk < 5; kk++) {
			if (a[kk] > b[kk]) {
				return false;
			} else if (b[kk] > a[kk]) {
				return true;
			} else {
				continue;
			}
		} 
		printf("nevere here1\n");
		return true;
	}
	printf("never three.2..\n");
	return true;
}
