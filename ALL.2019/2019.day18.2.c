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

using namespace std;

int lenx, leny;
#define DAY "2019 day18 part1\n"
#undef _DEBUG_
#define IN 100
#define assert(asdf)
#define PALEN 10000
int guptoPos = 0;
char gupto[2][27];
int calcLen(char var_newup[27]);
int calcLenPart(char cit1, char cit2);
int var_minPathLen = 99999;
char minminP[27];

char var_last3[53];

struct igs_s {
	int ig;
	int quad;
};

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
void signal_handler(int x) {
	printf("signal_handler: -- var_minPathLen:(%d)\n",
		var_minPathLen);
}
map <pair<char, char>, int> mplen[4];
map <pair<char, char>, string> mppat;
map <pair<char, char>, string> mppat2[4];
typedef struct letters_s lets_s;
#define getchar()
struct lettersminpa_s {
	char minpa[PALEN];
};
int stx[4], sty[4];

char minpa[PALEN];
lets_s letters[27];
struct lettersminpa_s lettersminpa[27];
void ne(int x, int y, int endx, int endy, int path);
void neBlocked(int x, int y, int endx, int endy, int path, char pa[PALEN]);
int numlets;

void process(int ig, struct letters_s letters[], char upto[4][27], int uptoPos[4], int var_len2, int quad);
int minPath;
int main(int argc, char **argv)
{
	signal(SIGTSTP, &signal_handler);
	lenx = 0; leny = 0;
        printf("%d ", argc); printf("%s", argv[1]);
	printf("\nBROKEN\n"); exit(0);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY);
	if (argc == 3) {printf("setting MAX to %d\n", atoi(argv[2])); var_minPathLen = atoi(argv[2]);}
       
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
				stx[0] = x; sty[0] = y; goto aft;
			}
		}
	}
aft:
	stx[1] = stx[0] + 2; 
	sty[1] = sty[0];

	stx[2] = stx[0];
	sty[2] = sty[0]+2;

	stx[3] = stx[0] + 2;
	sty[3] = sty[0]+2;

	printf("stx[0] is %d\n", stx[0]);
	printf("stx[1] is %d\n", stx[1]);
	printf("stx[2] is %d\n", stx[2]);
	printf("stx[3] is %d\n", stx[3]);

	printf("sty[0] is %d\n", sty[0]);
	printf("sty[1] is %d\n", sty[1]);
	printf("sty[2] is %d\n", sty[2]);
	printf("sty[3] is %d\n", sty[3]);

	assert(grid[sty[0]][stx[0]] == '@');
	assert(grid[sty[1]][stx[1]] == '@');
	assert(grid[sty[2]][stx[2]] == '@');
	assert(grid[sty[3]][stx[3]] == '@');
			
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
								printf("int val is %d\n", frm-97); getchar();
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
						printf("int val is %d\n", frm-97); getchar();
					}
				}
			}
		}
	}

	for (int qu = 0; qu < 4; qu++) {
		for (int i = 0; i < numlets; i++) {
			for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
			//printf("-------\n");
			minPath = 99999;
			char pat[10000];
			neBlocked(stx[qu], sty[qu], letters[i].keyx, letters[i].keyy, 0, pat); 
			if (minPath == 99999) {
				continue;
				minPath = 0;
				strcpy(minpa, "");
			}
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
			printf("qu [[%d]] here 2 @@@ minpa after is [%s]\n", qu, minpa); getchar();
			mplen[qu].insert({{'@', letters[i].letkey}, minPath}); 
			mplen[qu].insert({{'@', letters[i].letlock}, minPath}); 
			string mine = minpa;
				
			mppat2[qu].insert({{letters[i].letkey, '@'}, path2}); 
			mppat2[qu].insert({{'@', letters[i].letkey}, path2}); 
			mppat2[qu].insert({{letters[i].letlock, '@'}, path2}); 
			mppat2[qu].insert({{'@', letters[i].letlock}, path2}); 
		  }
	}

	for (int qu = 0; qu < 4; qu++) {
		for (int i = 0; i < numlets; i++) {
			for (int j = 0; j < numlets; j++) {
				//printf("-------\n");
				if (i == j) {continue;}
				for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
				minPath = 99999;
			
				char pat[10000];
				neBlocked(letters[i].keyx, letters[i].keyy, letters[j].keyx, letters[j].keyy, 0, pat); 
				//printf("minpa before %s minPath is %d\n", minpa, minPath); getchar();
				if (minPath == 99999) {
					continue;
					minPath = 0;
					strcpy(minpa, "");
				}
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
				printf("here1 minpa after is [%s]\n", minpa);
				mplen[qu].insert({{letters[i].letkey, letters[j].letkey}, minPath}); 
				mplen[qu].insert({{letters[i].letlock, letters[j].letlock}, minPath}); 
				mplen[qu].insert({{letters[j].letkey, letters[i].letkey}, minPath}); 
				mplen[qu].insert({{letters[j].letlock, letters[i].letlock}, minPath}); 
				string mine = minpa;
				
				mppat2[qu].insert({{letters[i].letkey, letters[j].letkey}, path2}); 
				mppat2[qu].insert({{letters[i].letlock, letters[j].letlock}, path2}); 
				mppat2[qu].insert({{letters[j].letkey, letters[i].letkey}, path2}); 
				mppat2[qu].insert({{letters[j].letlock, letters[i].letlock}, path2}); 
			}
		}
	}
	char upto[4][27];
	strcpy(upto[0], "");
	strcpy(upto[1], "");
	strcpy(upto[2], "");
	strcpy(upto[3], "");
	int uptoPos[4] = {0};
	int var_len = 0;
	process(-1, letters, upto, uptoPos, var_len, 0);
	
	printf("** ans %d\n", var_minPathLen); fflush(stdout);
	printf("** ans %d (%s)\n", var_minPathLen, minminP);
	getchar();

}
int calcLenPart(char cit1, char cit2) {
	//return mplen[{cit1, cit2}];
	return 1;
}
int calcLen(char var_newup[27]) {
/*
	int var_PathLen;
	{
		var_PathLen = mplen[{'@', var_newup[0]}];
		for (int j = 0; j < (int) strlen(var_newup)-1; j++) {
			var_PathLen += mplen[{var_newup[j], var_newup[j+1]}];
		}
		return var_PathLen;
	}
*/
	return 0;
}

int ind = 0;
void process(int ig, struct letters_s letters[], char upto[4][27], int uptoPos[4], int var_len1, int quad) {
	ind++;
	
	for (int qu = 0; qu < 4; qu++) {
		/*if (ind == 2)*/ //{printf("qu:%d ig is %d, upto is %s uptoPos is %d\n", qu, ig, upto[qu], uptoPos[qu]);getchar();}
	}
	if (ig != -1) {
		//for (int i = 0; i < ind; i++) {printf("  ");} printf("p:%c\n", letters[ig].letlock);
		letters[ig].ignore = 1;
	}
again:

	upto[quad][uptoPos[quad]] = '\0';
	switch(uptoPos[quad]) {
		case 0:
			break;
		case 1:
			if (mplen[quad].find({'@', upto[quad][uptoPos[quad]-1]}) == mplen[quad].end()) {ind--; return;}
			var_len1 += mplen[quad][{'@', upto[quad][uptoPos[quad]-1]}];
			if (var_len1 >= var_minPathLen) {ind--; return;}
			break;
		default:
			if (mplen[quad].find({upto[quad][uptoPos[quad]-2], upto[quad][uptoPos[quad]-1]}) == mplen[quad].end()) {ind--; return;}
			var_len1 += mplen[quad][{upto[quad][uptoPos[quad]-2], upto[quad][uptoPos[quad]-1]}];
			if (var_len1 >= var_minPathLen) {ind--;return;}
			break;
	}

	struct igs_s igs[27]; //memset(igs, -1, 27*sizeof(int));
	for (int i = 0; i < 26; i++) {
		igs[i].ig = -1;
		igs[i].quad = -1;
	}
	int igsPos = 0;
	int numfound = 0;

	//printf("ind is %d\n", ind);
	for (int qu = 0; qu < 4; qu++) {
		for (int i = 0; i < numlets; i++) {
			if (letters[i].ignore == 1) {continue;}
			string path2;
			if (upto[qu][0] == '\0') {
				if( mppat2[qu].find({'@', letters[i].letkey}) == mppat2[qu].end()) {continue;}
				path2 = mppat2[qu][{'@', letters[i].letkey}];
			} else {
				if (mppat2[qu].find({upto[qu][uptoPos[qu]-1], letters[i].letlock}) == mppat2[qu].end()) {continue;}
				path2 = mppat2[qu][{upto[qu][uptoPos[qu]-1], letters[i].letlock}];
			}
			//cout << "***path2 is: " << path2 << " " << " qu: " << qu << " intval:" << letters[i].intval << endl;
			
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
				igs[igsPos].quad = qu;
				igs[igsPos].ig = i;
				igsPos++;
				//igs[igsPos++] = i;
				numfound++;
			}
		}
	}

	if (numfound == 1) {
		//printf("one found %c\n", letters[igs[0].ig].letlock);
		letters[igs[0].ig].ignore = 1;
		upto[igs[0].quad][uptoPos[igs[0].quad]++] = letters[igs[0].ig].letlock;
		upto[igs[0].quad][uptoPos[igs[0].quad]] = '\0';
		quad = igs[0].quad;
		goto again;
	} else if (numfound == 0) {
		//printf("zero found\n");
		int sum = 0;
		for (int qu = 0; qu < 4; qu++) {
			upto[qu][uptoPos[qu]] = '\0';
			sum += uptoPos[qu];
		}

		if (sum == numlets) {
			//strcpy(var_last3, upto);
			if (var_len1 < var_minPathLen) {var_minPathLen = var_len1; /*strcpy(minminP, upto); */}
		}
		ind--;
		return;
	} else if (numfound > 1) {
		/*if (ind == 1) *///{for (int q = 0; q < ind; q++) {printf("  ");} printf("numfound more than one...[[%d]]: \n", numfound);}

                for (int z = 0; z < igsPos; z++) {
                        if (ind == 1) {for (int q = 0; q < ind; q++) {printf("  ");} printf("SEND: %d of %d %d:%d :%d :%c --\n", z, igsPos, igs[z].ig, igs[z].quad, letters[igs[z].ig].letlock, letters[igs[z].ig].letlock);fflush(stdout);}
			if (ind == 1 && (z == 0 || z==1 || z == 2 || z ==3)) {continue;}
                	lets_s let2ormore[numlets];
			for (int m = 0; m < numlets; m++) { let2ormore[m] = letters[m]; }
                	char uptos[4][27]; for (int qu2 = 0; qu2 < 4; qu2++) { strcpy(uptos[qu2], upto[qu2]); }
			int uptosPos[4]; for (int qu2 = 0; qu2 < 4; qu2++) { uptosPos[qu2] = uptoPos[qu2]; }

                        uptos[igs[z].quad][uptosPos[igs[z].quad]++] = letters[igs[z].ig].letlock;
                        uptos[igs[z].quad][uptosPos[igs[z].quad]] = '\0';
                        process(igs[z].ig, let2ormore, uptos, uptosPos, var_len1, igs[z].quad);

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
