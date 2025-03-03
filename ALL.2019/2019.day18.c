#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <map>
#include <string>
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

int lenx, leny;
#define DAY "2019 day18 part1\n"
#undef _DEBUG_
#define IN 100
#define PALEN 10000
int guptoPos = 0;
char gupto[2][27];
int calcLen(char var_newup[27]);
int calcLenPart(char cit1, char cit2);
int var_minPathLen = 99999;
char minminP[27];

char var_last3[53];

char grid[82][82];
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
void signal_handler(int x) {
	fflush(stdout); dup2(fd, 1); 
	printf("signal_handler: -- var_minPathLen:(%d) var_last3:[[%s]]\n",
			var_minPathLen, var_last3);
	close(1);
}
map <pair<char, char>, int> mplen;
map <pair<char, char>, string> mppat;
map <pair<char, char>, string> mppat2;
typedef struct letters_s lets_s;
#define getchar()
struct lettersminpa_s {
	char minpa[PALEN];
};
int stx, sty;

char minpa[PALEN];
lets_s letters[27];
struct lettersminpa_s lettersminpa[27];
void ne(int x, int y, int endx, int endy, int path);
void neBlocked(int x, int y, int endx, int endy, int path, char pa[PALEN]);
int numlets;

void process(int ig, struct letters_s letters[], char upto[], int uptoPos, int var_len2);
int minPath;
int main(int argc, char **argv)
{
	signal(SIGQUIT, &signal_handler);
	lenx = 0; leny = 0;
	//printf("%d ", argc); printf("%s", argv[1]);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY);
	printf("SLOW ~1hour maybe 2\n");
	if (argc == 3) {printf("setting MAX to %d\n", atoi(argv[2])); var_minPathLen = atoi(argv[2]);}

	fd = dup(1); close(1);
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

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '@') {
				stx = x; sty = y; break;
			}
		}
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
								//letters[i].key = frm; 
								//letters[i].lock = frm-(97-65);
								letters[i].keyx = x;
								letters[i].keyy = y;
								letters[i].lockx = x1;
								letters[i].locky = y1;
								//printf("int val is %d\n", frm-97); getchar();
								letters[i].intval = frm-97;
							}
						}
					}
					if (found == 0) {
						letters[i].keyx = x;
						letters[i].keyy = y;
						letters[i].lockx = x;
						letters[i].locky = y;
						letters[i].intval = frm-97;
						//printf("int val is %d\n", frm-97); getchar();
					}
				}
			}
		}
	}

	for (int i = 0; i < numlets; i++) {
		for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
		//printf("-------\n");
		minPath = 99999;
		char pat[10000];
		neBlocked(stx, sty, letters[i].keyx, letters[i].keyy, 0, pat); 
		int end = (int)strlen(minpa);
		for (int k = 0; k < end; k++) {
			if (minpa[k] == '@' || minpa[k] == '.' || islower(minpa[k])) {
				for (int l = k; l < end-1; l++) {
					minpa[l] = minpa[l+1];
				}
				end--;
				k--;
			}
		}
		//strcpy(in3.path, minpa);
		minpa[end] = '\0';
		string path2 = "00000000000000000000000000";
		for (int u = 0; u < (int)strlen(minpa); u++) {
			path2[minpa[u]-65] = '1';
			//printf("pos %d minpa[u]-65\n", minpa[u]-65);
		}		
		//printf("minpa after is [%s]\n", minpa); getchar();
		mplen.insert({{'@', letters[i].letkey}, minPath}); 
		mplen.insert({{'@', letters[i].letlock}, minPath}); 
		string mine = minpa;
		mppat.insert({{letters[i].letkey, '@'}, mine}); 
		mppat.insert({{'@', letters[i].letkey}, mine}); 
		mppat.insert({{letters[i].letlock, '@'}, mine}); 
		mppat.insert({{'@', letters[i].letlock}, mine}); 

		mppat2.insert({{letters[i].letkey, '@'}, path2}); 
		mppat2.insert({{'@', letters[i].letkey}, path2}); 
		mppat2.insert({{letters[i].letlock, '@'}, path2}); 
		mppat2.insert({{'@', letters[i].letlock}, path2}); 
	}

	for (int i = 0; i < numlets; i++) {
		for (int j = 0; j < numlets; j++) {
			//printf("-------\n");
			if (i == j) {continue;}
			for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
			minPath = 99999;

			char pat[10000];
			neBlocked(letters[i].keyx, letters[i].keyy, letters[j].keyx, letters[j].keyy, 0, pat); 
			//printf("minpa before %s minPath is %d\n", minpa, minPath); getchar();
			int end = (int)strlen(minpa);
			for (int k = 0; k < end; k++) {
				if (minpa[k] == '@' || minpa[k] == '.' || islower(minpa[k])) {
					for (int l = k; l < end-1; l++) {
						minpa[l] = minpa[l+1];
					}
					end--;
					k--;
				}
			}
			minpa[end] = '\0';
			string path2 = "00000000000000000000000000";
			for (int u = 0; u < (int)strlen(minpa); u++) {
				path2[minpa[u]-65] = '1';
				//printf("pos %d minpa[u]-65\n", minpa[u]-65);
			}		
			//printf("minpa after is [%s]\n", minpa);
			mplen.insert({{letters[i].letkey, letters[j].letkey}, minPath}); 
			mplen.insert({{letters[i].letlock, letters[j].letlock}, minPath}); 
			mplen.insert({{letters[j].letkey, letters[i].letkey}, minPath}); 
			mplen.insert({{letters[j].letlock, letters[i].letlock}, minPath}); 
			string mine = minpa;
			mppat.insert({{letters[i].letkey, letters[j].letkey}, mine}); 
			mppat.insert({{letters[i].letlock, letters[j].letlock}, mine}); 
			mppat.insert({{letters[j].letkey, letters[i].letkey}, mine}); 
			mppat.insert({{letters[j].letlock, letters[i].letlock}, mine}); 

			mppat2.insert({{letters[i].letkey, letters[j].letkey}, path2}); 
			mppat2.insert({{letters[i].letlock, letters[j].letlock}, path2}); 
			mppat2.insert({{letters[j].letkey, letters[i].letkey}, path2}); 
			mppat2.insert({{letters[j].letlock, letters[i].letlock}, path2}); 
		}
	}
	char upto[27] = "";
	int uptoPos = 0;
	int var_len = 0;
	process(-1, letters, upto, uptoPos, var_len);

	fflush(stdout); dup2(fd, 1);
	printf("** ans %d (%s)\n", var_minPathLen, minminP);
	getchar();

}
int calcLenPart(char cit1, char cit2) {
	return mplen[{cit1, cit2}];
}
int calcLen(char var_newup[27]) {
	int var_PathLen;
	{
		var_PathLen = mplen[{'@', var_newup[0]}];
		for (int j = 0; j < (int) strlen(var_newup)-1; j++) {
			var_PathLen += mplen[{var_newup[j], var_newup[j+1]}];
		}
		return var_PathLen;
	}
	return 0;
}

int ind = 0;
void process(int ig, struct letters_s letters[], char upto[], int uptoPos, int var_len1) {
	ind++;

	if (ind == 2) {printf("ig is %d, upto is %s uptoPos is %d\n", ig, upto, uptoPos);getchar();}
	if (ig != -1) {
		//for (int i = 0; i < ind; i++) {printf("  ");} printf("p:%c\n", letters[ig].letlock);
		letters[ig].ignore = 1;
	}
again:

	upto[uptoPos] = '\0';
	switch(uptoPos) {
		case 0:
			break;
		case 1:
			var_len1 += mplen[{'@', upto[uptoPos-1]}];
			if (var_len1 >= var_minPathLen) {return;}
			break;
		default:
			var_len1 += mplen[{upto[uptoPos-2], upto[uptoPos-1]}];
			if (var_len1 >= var_minPathLen) {return;}
			break;
	}

	int igs[27]; memset(igs, -1, 27*sizeof(int));
	int igsPos = 0;
	int numfound = 0;

	for (int i = 0; i < numlets; i++) {
		if (letters[i].ignore == 1) {continue;}
		string path2;
		if (upto[0] == '\0') {
			path2 = mppat2[{'@', letters[i].letkey}];
		} else {
			path2 = mppat2[{upto[uptoPos-1], letters[i].letlock}];
		}
		//cout << "***path2 is: " << path2 << " " << letters[i].intval << endl;

		int found = 0;
		for (int k = 0; k < numlets; k++) {
			if (k == i) {continue;}
			if (letters[k].ignore == 1) {continue;}
			if (path2[letters[k].intval] == '1') {
				found++; goto after;
			}
		}
after:

		if (found == 0) {
			igs[igsPos++] = i;
			numfound++;
		}
	}

	if (numfound == 1) {
		letters[igs[0]].ignore = 1;
		upto[uptoPos++] = letters[igs[0]].letlock;
		upto[uptoPos] = '\0';
		goto again;
	} else if (numfound == 0) {
		upto[uptoPos] = '\0';
		if (uptoPos == numlets) {
			strcpy(var_last3, upto);
			if (var_len1 < var_minPathLen) {var_minPathLen = var_len1; /*strcpy(minminP, upto); */}
		}
		ind--;
		return;
	} else if (numfound > 1) {
		if (ind == 1) {for (int q = 0; q < ind; q++) {printf("  ");} printf("numfound more than one...igs %d: \n", numfound);}
		lets_s let2ormore[numfound+1][numlets];
		char uptos[numfound+1][27];
		for (int z = 0; z < igsPos; z++) {
			for (int m = 0; m < numlets; m++) {
				let2ormore[z][m] = letters[m];
			}
			strcpy(uptos[z], upto);
		}

		for (int z = 0; z < igsPos; z++) {
			if (ind == 1) {for (int q = 0; q < ind; q++) {printf("  ");} printf("SEND:%d :%d :%c --", igs[z], letters[igs[z]].letlock, letters[igs[z]].letlock);}
			uptos[z][uptoPos] = letters[igs[z]].letlock;
			uptos[z][uptoPos+1] = '\0';
			process(igs[z], let2ormore[z], uptos[z], uptoPos+1, var_len1);

		}
	}
	ind--;
}
void neBlocked(int x, int y, int endx, int endy, int path, char pa[PALEN]) {
	if (x == endx && y == endy) {
		pa[path] = '\0';
		//printf("dest reached... path is %d pa is %s\n", path, pa);
		//		if (path < minPath) {strcpy(minpa, pa); minPath = path; letters[let].path = path;}
		if (path < minPath) {strcpy(minpa, pa); minPath = path; }
		return;
	}

	if (x < 0 || y < 0 || y >= leny || x >= lenx) {
		return;
	}
	if (grid[y][x] == '#') {return;}

	if (already[y][x] == -1 || path < already[y][x]) {
		already[y][x] = path;
		pa[path] = grid[y][x];
		neBlocked(x+1, y, endx, endy, path+1, pa);
		neBlocked(x-1, y, endx, endy, path+1, pa);
		neBlocked(x, y+1, endx, endy, path+1, pa);
		neBlocked(x, y-1, endx, endy, path+1, pa);
	}
}

void ne(int x, int y, int endx, int endy, int path) {
	if (x == endx && y == endy) {
		//printf("dest reached... path is %d\n", path);
		if (path < minPath) {minPath = path;}
		return;
	}

	if (x < 0 || y < 0 || y >= leny || x >= lenx) {
		return;
	}
	if (grid[y][x] == '#') {return;}

	if (already[y][x] == -1 || path < already[y][x]) {
		already[y][x] = path;
		ne(x+1, y, endx, endy, path+1);
		ne(x-1, y, endx, endy, path+1);
		ne(x, y+1, endx, endy, path+1);
		ne(x, y-1, endx, endy, path+1);
	}
}
