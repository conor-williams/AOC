#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

int lenx, leny;
#define DAY "2019 day18 part1\n"
#undef _DEBUG_
#define IN 100
#define PALEN 10000
int guptoPos = 0;
char gupto[10000][30];

char grid[82][82];
int already[82][82];
struct letters_s {
	char letlock;
	char letkey;
	int keyx;
	int keyy;
	int lockx;
	int locky;
	int path;
	int ignore;
};

typedef struct letters_s lets_s;

#define getchar()
struct lettersminpa_s {
	char minpa[PALEN];
};

char minpa[PALEN];
lets_s letters[30];
struct lettersminpa_s lettersminpa[30];
void ne(int x, int y, int endx, int endy, int path);
void neBlocked(int x, int y, int endx, int endy, int path, char pa[PALEN]);
int numlets;

void process(int ig, struct letters_s letters[], char upto[], int uptoPos, int lastx, int lasty);
int minPath;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d ", argc); printf("%s", argv[1]);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY);
       
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

	int stx, sty;
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
							}
						}
					}
					if (found == 0) {
						letters[i].keyx = x;
						letters[i].keyy = y;
						letters[i].lockx = x;
						letters[i].locky = y;
					}
				}
			}
		}
	}

	char upto[30] = "";
	int uptoPos = 0;
	process(-1, letters, upto, uptoPos, stx, sty);
	
	getchar();
	printf("\nGLOB: \n");
	for (int i = 0; i < guptoPos; i++) {
		printf("%s\n", gupto[i]);
	}
	getchar();

	
	int myminPathLen = 99999;
	//strcpy(gupto[0], "BACDFEG"); guptoPos = 1;
	//strcpy(gupto[0], "ABCEFD"); guptoPos = 1;
	char minminP[30];
	for (int i = 0; i < guptoPos; i++) {
		printf("**%s\n", gupto[i]); getchar();
		int myPathLen = 0;
		//@ a
		//a A
		//A b
		//b B 
		//B c
		//c C
		int xx, yy;
		auto void getPos(int pos, int uplow, int which) {
			char mychar;
			if (uplow == 1) { //uppper
				mychar = gupto[which][pos];
			} else if (uplow == 0) { //lower
				mychar = gupto[which][pos]-65+97;
			}
			//printf("getPos mychar is %c\n", mychar);
			for (int y = 0; y < leny; y++) {
				for (int x = 0; x < lenx; x++) {
					if (grid[y][x] == mychar) {
						xx = x; yy = y;
						return;
					}
				}
			}
		}

			
		
		minPath = 99999;
		getPos(0, 0, i);
		for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
		ne(stx, sty, xx, yy, 0); 
		myPathLen += minPath;
		//printf("minPath1 is %d\n", minPath);
		//printf("stx, sty %d,%d xx,yy, %d,%d\n", stx, sty, xx, yy);
		for (int j = 0; j < (int) strlen(gupto[i])-1; j++) {
			for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
			minPath = 99999;
			getPos(j, 0, i);
			int fx = xx; int fy = yy;
			xx = -1; yy = -1;
			getPos(j, 0, i);

			int px; int py;
			if (xx == -1 && yy == -1) {
				//printf("here1"); getchar();
				px = fx; py = fy;
			} else {
				//minPath = 99999;
				//for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
				//ne(fx, fy, xx, yy, 0); //getchar();
				//assert(minPath != 99999);
				//myPathLen += minPath;
				//printf("minPath2 is %d\n", minPath);
				//px = xx; py = yy;
				px = fx; py = fy;
			}
			
			getPos(j+1, 0, i);
			for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
			minPath = 99999;
			ne(px, py, xx, yy, 0);
			//printf("minPath3 is %d\n", minPath);
			//assert(minPath != 99999);
			myPathLen += minPath;
			
		}
		printf("myPathLen is %d (%s)\n", myPathLen, gupto[i]);
		if (myPathLen < myminPathLen) {myminPathLen = myPathLen; strcpy(minminP, gupto[i]); }
	}
	printf("** ans %d (%s)\n", myminPathLen, minminP);
	getchar();

/*
	for (int i = 0; i < numlets; i++) {
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				already[y][x] = -1;
			}
		}
	
		minPath = 99999;
		//printf("let %c--%c--------\n", letters[i].letlock, letters[i].letkey);
		ne(letters[i].keyx, letters[i].keyy, letters[i].lockx, letters[i].locky, 0); //getchar();
	}


	
	for (int i = 0; i < numlets; i++) {
		printf("%c %d,%d %c %d,%d path:[[%d]]\n", letters[i].letkey, letters[i].keyx, letters[i].keyy,
			letters[i].letlock, letters[i].lockx, letters[i].locky, letters[i].path);
	}
*/

}
int ind = 0;
void process(int ig, struct letters_s letters[], char upto[], int uptoPos, int lastPosx, int lastPosy) {
	ind++;
	
	if (ig != -1) {
		//for (int i = 0; i < ind; i++) {printf("  ");} printf("p:%c\n", letters[ig].letlock);
		letters[ig].ignore = 1;
	}
again:

	int igs[30];
	for (int i = 0; i < 30; i++) {
		igs[i] = -1;
	}
	int igsPos = 0;
	int numfound = 0;
	for (int i = 0; i < numlets; i++) {
		if (letters[i].ignore == 1) {continue;}
		for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { already[y][x] = -1; } }
	
		minPath = 99999;
		//printf("let %c---%c-------\n", letters[i].letlock, letters[i].letkey);
		strcpy(minpa, "");
		char pa[PALEN] = "";
		//neBlocked(letters[i].keyx, letters[i].keyy, letters[i].lockx, letters[i].locky, 0, pa);
		neBlocked(lastPosx, lastPosy, letters[i].keyx, letters[i].keyy, 0, pa);
		if (letters[i].keyx == letters[i].lockx && letters[i].keyy == letters[i].locky) {
			printf("***minpa %s\n", minpa);
		}
		strcpy(lettersminpa[i].minpa, minpa);
		printf("minpa is [%s]\n", minpa); getchar();
		int found = 0;
		for (int j = 0;  j < (int)strlen(minpa); j++) {
			for (int k = 0; k < numlets; k++) {
				if (letters[k].ignore == 1) {continue;}

				if (minpa[j] == letters[k].letlock) {
					found++;
					//printf("%c blocked by %c\n", letters[i].letkey, minpa[j]);
					//if (letters[i].letkey == 'd' && minpa[j] == 'E') {printf("ddd\n"); getchar();getchar(); getchar();}
				}
			}	
		}
		if (found == 0) {
			printf("%c not blocked\n", letters[i].letkey);
			igs[igsPos++] = i;
			numfound++;
		}
		//getchar();
	}

	if (numfound == 1) {
		letters[igs[0]].ignore = 1;
		lastPosx = letters[igs[0]].keyx; lastPosy = letters[igs[0]].keyy;
		upto[uptoPos++] = letters[igs[0]].letlock;
		upto[uptoPos] = '\0';

		//for (int q = 0; q < ind; q++) {printf("  ");}printf("ignoring %c\n", letters[igs[0]].letlock);
		//for (int q = 0; q < ind; q++) {printf("  ");} printf("again %c\n", igs[0]);
		//printf("----------%s---------------\n", upto); getchar();
		goto again;
	} else if (numfound == 0) {
		upto[uptoPos] = '\0';
		printf("Upto: %s\n", upto);
		if ((int)strlen(upto) == numlets) {
			strcpy(gupto[guptoPos++], upto);
		}
		ind--;
		return;
		//for (int q = 0; q < ind; q++) {printf("  ");} printf("OOPS zero numfound\n");
	} else if (numfound > 1) {
		//for (int q = 0; q < ind; q++) {printf("  ");} printf("numfound more than one...igs: \n");
		lets_s let2ormore[numfound][numlets];
		char uptos[numfound][30];
		for (int z = 0; z < igsPos; z++) {
			for (int m = 0; m < numlets; m++) {
				let2ormore[z][m] = letters[m];
			}
			strcpy(uptos[z], upto);
		}

		for (int z = 0; z < igsPos; z++) {
			for (int q = 0; q < ind; q++) {printf("  ");} printf("SEND:%d ", igs[z]);
			//printf("here2222\n");
			uptos[z][uptoPos] = letters[igs[z]].letlock;
			uptos[z][uptoPos+1] = '\0';
			lastPosx = letters[igs[z]].keyx; lastPosy = letters[igs[z]].keyy;
			process(igs[z], let2ormore[z], uptos[z], uptoPos+1, lastPosx, lastPosy);
				
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
