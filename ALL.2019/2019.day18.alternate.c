#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <algorithm>
#include <sys/time.h>

#include <deque>

using namespace std;

int lenx, leny;
#define DAY "2019 day18 part1\n"
#undef _DEBUG_
#define IN 100
//#define assert(asdf)

//unordered_map <tuple<char, string>, int, hash_function> minThrees;
struct hash_function
{
	///unordered_map <tuple<char, string>, int, hash_function> minThrees;
	size_t operator()(const tuple<char , string>  &x) const
	{
		unsigned int hash = 0;
		return hash;
		//unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 37; hash += get<2>(x); hash *= 37; hash += get<3>(x); return hash;
	}
};


char grid[82][82];
char gridOrig[82][82];
int already[82][82];

struct letters_s {
	char letlock;
	char letkey;
	int intval;
	int keyx;
	int keyy;
	int lockx;
	int locky;
	int path;
	int ignore;
};
int fd;

typedef struct letters_s lets_s;
lets_s letters[26];

#define getchar()
struct pos_s {
	int keyx;
	int keyy;
	int lockx;
	int locky;
	char let;
};
map <char, struct pos_s> mp2;

void ne(int x, int y, int endx, int endy, int path);

int numlets;

int minP;
void next(int x, int y, int ex, int ey, int path);
int doCheck3(char frm, char le);

string allLetters;
int allLettersLength;

unordered_map <tuple<char, string>, int, hash_function> minThrees;
void buildThrees();
unordered_map <tuple<char, string>, int, hash_function> allPaths[30];
int getEndMin ();
void buildAllPaths(int incoming);
deque <int> allLettersDEQ;
int main(int argc, char **argv)
{
	//signal(SIGQUIT, &signal_handler);
	lenx = 0; leny = 0;
	//note -- does not work with all examples aAbCc being one

	FILE * a = fopen(argv[1], "r"); 
	printf(DAY);
	printf("quick with all the part1 examples VV slow + loads mem for other\n");

	fd = dup(1); close(1);

	memset(letters, -1, sizeof(letters));
	char line1[IN];

	while(1) {
		fgets(line1, IN-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s getchar\n", line1); getchar();
#endif
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);

	int cat = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '@') {
				cat++;
				mp2['@'].keyx = x;
				mp2['@'].keyy = y;
			}
		}
	}
	if (cat != 1) {
		perror("CAT not 1\n"); exit(0);
	}

	numlets = 0;
	for (int i = 0; i < 26; i++) {
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (grid[y][x] == i+97) {
					letters[numlets].letlock = i+65;
					letters[numlets++].letkey = i+97;
					goto cont;
				}
			}
		}
cont:
		continue;
	}

	printf("numlets is %d\n", numlets); getchar();

	for (int i = 0; i < numlets; i++) {
		char frm = letters[i].letkey;
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (grid[y][x] == frm) {
					int found = 0;
					for (int y1 = 0; y1 < leny; y1++) {
						for (int x1 = 0; x1 < lenx; x1++) {
							if (grid[y1][x1] == frm-(97-65)) {
								found = 1;
								printf("frm is %c\n", frm);
								mp2[frm].keyx = x;
								mp2[frm].keyy = y;
								mp2[frm].lockx = x1;
								mp2[frm].locky = y1;
								mp2[frm].let = frm;
							}
						}
					}
					allLetters.push_back(frm);
					if (found == 0) {

						printf("frm is %c\n", frm);
						mp2[frm].keyx = x;
						mp2[frm].keyy = y;
						mp2[frm].lockx = x;
						mp2[frm].locky = y;
						mp2[frm].let = frm;
					}
				}
			}
		}
	}

	allLettersLength = allLetters.length();
	for (auto let1: allLetters) {
		allLettersDEQ.push_back(let1);
	}

	memcpy(gridOrig, grid, sizeof(grid));

	fflush(stdout); dup2(fd, 1);
	printf("buildThrees\n");
	close(1);
	buildThrees();
	fflush(stdout); dup2(fd, 1);
	printf("after buildThrees\n");
	close(1);
	allPaths[3] = minThrees;

	for (int i = 4; i < allLettersLength; i++) {
		sort (allLetters.begin(), allLetters.end());
		fflush(stdout); dup2(fd, 1);
		printf("calling buildAllPaths %d\n", i);
		close(1);
		buildAllPaths(i);
		fflush(stdout); dup2(fd, 1);
		printf("i is %d\n", i); fflush(stdout);
		printf("allPaths[%d].size() %d\n", i, (int)allPaths[i].size());
		close(1);
	}

	fflush(stdout); dup2(fd, 1);
	int ans2 = getEndMin();
	printf("ans2 is %d\n", ans2);
	exit(0);
}

void buildThrees()
{
	clock_t start, end; double cpu_time_used; 
	start = clock();
	for (auto itii = allLettersDEQ.begin(); itii != allLettersDEQ.end(); itii++) {
		for (auto itjj = allLettersDEQ.begin(); itjj != allLettersDEQ.end(); itjj++) {
			if (itii == itjj) {continue;}
			for (auto itkk = allLettersDEQ.begin(); itkk != allLettersDEQ.end(); itkk++) {
				if (itkk == itjj || itkk == itii) {continue;}
				char c1 = *itii;
				char c2 = *itjj;
				char c3 = *itkk;
				for (auto bla: allLetters) {
					if (bla == c1 || bla == c2 || bla == c3) {continue;}
					else {
						memcpy(grid, gridOrig, sizeof(grid));
						grid[mp2['@'].keyy][mp2['@'].keyx] = '.';
						for (auto sin: allLetters) {
							if (sin != c1 && sin != c2 && sin != c3) {
								//assert(sin == mp2[sin].let);

								grid[mp2[sin].keyy ][mp2[sin].keyx ] = '.';
								grid[mp2[sin].locky][mp2[sin].lockx] = '.';
							}

						}
						int tot = doCheck3(bla, c1);
						if (tot < 99999) {
							tot += doCheck3(c1, c2);
							if (tot < 99999) {
								tot += doCheck3(c2, c3);

								if (tot < 99999) {
									string bla2;
									bla2.push_back(c1); bla2.push_back(c2);
									bla2.push_back(c3); bla2.push_back(bla);
									sort(bla2.begin(), bla2.end());

									//assert(tot < 99999);
									if (minThrees.find({bla, bla2}) == minThrees.end() || tot < minThrees[{bla, bla2}]) {
										minThrees[{bla, bla2}] = tot;
									}
								}
							}
						}
					}

				}

			}
		}
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	dup2(fd, 1); 
	printf("        time: %f seconds\n", cpu_time_used);
	printf("minThrees.size() is %d\n", (int)minThrees.size());
	close(1);

}

void buildAllPaths(int incoming) {
	for (auto it = allPaths[incoming-1].begin(); it != allPaths[incoming-1].end(); it++) {
		auto tu = it->first;
		char ch = get<0>(tu);
		string donegal =  get<1>(tu);

		for (auto it11 = allLettersDEQ.begin(); it11 != allLettersDEQ.end(); it11++) {
			char var_it11 = *it11;
			if (find(donegal.begin(), donegal.end(), var_it11) != donegal.end()) {
				continue;
			} else {
				memcpy(grid, gridOrig, sizeof(grid));
				grid[mp2['@'].keyy][mp2['@'].keyx] = '.';
				for (auto it12 = allLettersDEQ.begin(); it12 != allLettersDEQ.end(); it12++) {
					char var_it12 = *it12;
					if (find(donegal.begin(), donegal.end(), var_it12) == donegal.end()) {
						//assert(var_it12 == mp2[var_it12].let);
						grid[mp2[var_it12].keyy ][mp2[var_it12].keyx ]   = '.';
						grid[mp2[var_it12].locky][mp2[var_it12].lockx] = '.';
					}
				}

				int tot = doCheck3(var_it11, ch);

				if (tot+it->second < 99999) { ///NB NB NB
					string bla22 = donegal; bla22.push_back(var_it11);
					sort(bla22.begin(), bla22.end());
					//assert(tot+it->second < 99999);


					if (allPaths[incoming].find({var_it11, bla22}) == allPaths[incoming].end() || 
							tot+it->second < allPaths[incoming][{var_it11, bla22}]) {
						allPaths[incoming][{var_it11, bla22}] = tot+it->second;
					}
				}
			}
		}

	}
	allPaths[incoming-1].clear();
	//assert((int)allPaths[incoming-1].size() == 0);
}

int doCheck3(char frm, char le) {
	memset(already, -1, sizeof(already));
	minP = 99999;
	grid[mp2[frm].keyy][mp2[frm].keyx] = '.';
	grid[mp2[frm].locky][mp2[frm].lockx] = '.';
	next(mp2[frm].keyx, mp2[frm].keyy, mp2[le].keyx, mp2[le].keyy, 0);
	//if (minP != 99999) {
	//	grid[mp2[le].locky][mp2[le].lockx] = '.';
	//}

	return minP;
}

void next(int x, int y, int ex, int ey, int path) {

	//printf("next %d %d %d %d %d\n", x, y, ex, ey, path);
	if (x < 0 || y < 0 || y >= leny || x >= lenx) {
		return;
	}

	if (x == ex && y == ey) {
		//printf("path reached\n");
		if (path < minP) {minP = path;} 
		return;
	}
	if (grid[y][x] != '.') {return;}
	//if (isupper(grid[y][x])) {return;}
	//if (islower(grid[y][x])) {return;}

	if (path < already[y][x] || already[y][x] == -1) {
		already[y][x] = path;

		next(x, y-1, ex, ey, path+1);
		next(x+1, y, ex, ey, path+1);
		next(x, y+1, ex, ey, path+1);
		next(x-1, y, ex, ey, path+1);
	}

}

int getEndMin () {
	int tot2 = 99999;
	string minS;
	//int SZ = 3;
	for (auto it = allPaths[allLettersLength-1].begin(); it != allPaths[allLettersLength-1].end(); it++) {
		auto tu = it->first;
		char ch = get<0>(tu);
		string bla2 = get<1>(tu);

		int tot = doCheck3('@', ch);
		//fflush(stdout); dup2(fd, 1); printf("tot %d\n", tot); printf("tot+it->second %d\n", tot+it->second); close(1);
		if (tot != 99999 && tot + it->second < tot2) {minS=bla2; tot2 = tot+it->second;}
	}
	fflush(stdout); dup2(fd, 1);
	printf("minS: %s\n", minS.c_str());
	return tot2;
}
