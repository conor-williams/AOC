#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>
#include <unistd.h>
#include <algorithm>

#include <limits.h>
#include <stdint.h>

using namespace std;
int watch = 0;
int mycount = 0;

#define getchar()
#undef _DEBUG_
//int path = 0;
int minPathLen;
int lenx, leny;
#define DAY "2016 day22 part1 \n"
#define _DEBUG_
long tot;
long tot1;
#define SIZE 200
int pathsNUM = 0;
struct fs_s {
	int size;
	int used;
	int avail;
	int percU;
	char name[28];
};
struct fs_s fs[1800];
map <string, struct fs_s> mp;
char goal[100]; 
void next(int x, int y, int steps, char DIR, int frX, int frY, char path[]);


#ifdef EX1
	#define MAXX 2
	#define MAXY 2
#else
	#define MAXX 32 
	#define MAXY 29
#endif
//int sX = MAXX; int sY = 0; 

struct fs_s grid[MAXY+2][MAXX+2];
struct fs_s gridTmp[MAXY+2][MAXX+2];
struct fs_s gridOrig[MAXY+2][MAXX+2];
int mymax = 0;
int already[MAXY+2][MAXX+2];
void savepath(char path[]);
char saves[1800][1800];
int savesPos = 0;
void savepathBEG(char path[], int x1, int y1, int letpos, int sX, int sY);
//char savesBEG[1800][1800][1800]; //needs to be 1800 for 2nd last
char (*savesBEG)[1800][1800];
int savesBEGPos[2000] = {0};
struct xtra_s {
	int x1;
	int y1;
	int x;
	int y;
	int sX;
	int sY;
	int frslotX;
	int frslotY;
	int toslotX;
	int toslotY;
	int pathLen;
};
struct xtra_s xtraBEG[1800][3000];

void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, int DTX, int DTY, int igx, int igy, int vx1, int vy1, int letpos, int sZ, int sY, int frslotX, int frslotY, int toslotX, int toslotY, char path[]);
int carryitout(int myp, int letpos, int *pathLen, int theEnd, int *sX, int *sY);

int cpoint(int r, int pathLen);
void restore(int mypos, int *pathLen);
struct fs_s checkpoint[3500][MAXY+2][MAXX+2];
int checkpointPos = 0;

struct xtra_xtra_s {
	int sX;
	int sY;
	int x;
	int y;
	int pathLen;
};
struct  xtra_xtra_s cp[18000];
void loop(int sv, int let, int first, int *pathLen, int theEnd, int sX, int sY, int myr, int myrTot);
int generateSAVESFORlettterPos(int sv, int thepos, int sX, int sY);


void restore(int mypos, int *pathLen) {
	for (int y = 0; y <= MAXY; y++) {
		for (int x = 0; x <= MAXX; x++) {
			grid[y][x] = checkpoint[mypos][y][x];
		}
	}
	*pathLen = cp[mypos].pathLen;
	//sX = cp[mypos].sX;
	//sY = cp[mypos].sY;
}
int cpoint(int let, int r, int pathLen, int SAME) {
	if (checkpointPos >= 3500) {printf("ERROR cpoint\n"); exit(0);}

	if (SAME == 0) {
		for (int y = 0; y <= MAXY; y++) {
			for (int x = 0; x <= MAXX; x++) {
				checkpoint[checkpointPos][y][x] = grid[y][x];
			}
		}
		cp[checkpointPos].sX = xtraBEG[let][r].sX;
		cp[checkpointPos].sY = xtraBEG[let][r].sY;
		cp[checkpointPos].x  = xtraBEG[let][r].x;
		cp[checkpointPos].y  = xtraBEG[let][r].y;
		cp[checkpointPos].pathLen  = pathLen;
		checkpointPos++;
		return checkpointPos;
	} else {
		return checkpointPos;
	} 
}
/*
int cpoint(int let, int r, int pathLen, int SAME) {
	if (checkpointPos >= 3500) {printf("ERROR cpoint\n"); exit(0);}

	int found = 0;
	int usepos = 0;
	for (int i = 0; i < checkpointPos; i++) {
		
		int found1 = 0;
		for (int y = 0; y <= MAXY; y++) {
			for (int x = 0; x <= MAXX; x++) {
				if (checkpoint[i][y][x].used == grid[y][x].used && checkpoint[i][y][x].avail == grid[y][x].avail) {
					found1++;
				}
			}
		}	
		if (found1 == MAXX*MAXY) {
			if (cp[i].sX == xtraBEG[let][r].sX && cp[i].sY == xtraBEG[let][r].sY && cp[i].x  == xtraBEG[let][r].x && cp[i].y  == xtraBEG[let][r].y && cp[i].pathLen  == pathLen) {
	printf("here1...\n");
					usepos = i;
					found = 1; break;
			}
		}
		
	}
	if (found == 0) {
		for (int y = 0; y <= MAXY; y++) {
			for (int x = 0; x <= MAXX; x++) {
				checkpoint[checkpointPos][y][x] = grid[y][x];
			}
		}
		cp[checkpointPos].sX = xtraBEG[let][r].sX;
		cp[checkpointPos].sY = xtraBEG[let][r].sY;
		cp[checkpointPos].x  = xtraBEG[let][r].x;
		cp[checkpointPos].y  = xtraBEG[let][r].y;
		cp[checkpointPos].pathLen  = pathLen;
		checkpointPos++;
		return checkpointPos;
	} else {
		return usepos;
	} 
}
*/
int main(int argc, char **argv)
{
	savesBEG = (char (*)[1800][1800])malloc(901*sizeof(*savesBEG));
	
	if (savesBEG == NULL) {
		printf("NO MEM\n");
	 	exit(0);
	}

	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
	int numFS;
	if (strcmp(argv[1], "ex1.txt") == 0) {
		strcpy(goal, "/dev/grid/node-x2-y0");
		//MAXX = 2; MAXY = 2;
	} else {
		strcpy(goal, "/dev/grid/node-x32-y0");
		//MAXX = 32; MAXY = 29;
	}
	//int fd = dup(1); close(1);
	for (int y = 0; y <= MAXY; y++) {
		for (int x = 0; x <= MAXX; x++) {
			already[y][x] = -1;	
		}
	}
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	//printf("LINE: %s\n", line1); 
#endif
	if (leny > 1) {
		char size[10], used[10], avail[10], percU[10], name[40];
		int ret = sscanf(line1, "%s %s %s %s %s", name, size, used, avail, percU);
		if (ret != 5 || leny == 992) {
			printf("ERROR %s\n", line1);
		}
		size[strlen(size)-1] = '\0';
		used[strlen(used)-1] = '\0';
		avail[strlen(avail)-1] = '\0';
		percU[strlen(percU)-1] = '\0';
		fs[numFS].size = atoi(size);
		fs[numFS].used = atoi(used);
		fs[numFS].avail = atoi(avail);
		fs[numFS].percU = atoi(percU);
		strcpy(fs[numFS].name, name);
		string nm = name;
		mp.insert({nm, fs[numFS]});
		char *first = strtok(name, "-");
		char theX[10], theY[10];
		first = strtok(NULL, "-");
		strcpy(theX, first);
		theX[0] = ' ';
		first = strtok(NULL, "-");
		strcpy(theY, first);
		theY[0] = ' ';
		grid[atoi(theY)][atoi(theX)] = fs[numFS];
		
		numFS++;
	}
	leny++;
}
fclose(a);

printf("at start:\n"); for (int y = 0; y <= MAXY; y++) { for (int x = 0; x <= MAXX; x++) { gridOrig[y][x] = grid[y][x]; printf(" %d/%d", grid[y][x].used, grid[y][x].size);
	}
	printf("\n");
}
printf("\n");
printf("at start Orig:\n"); for (int y = 0; y <= MAXY; y++) { for (int x = 0; x <= MAXX; x++) { printf(" %d/%d", gridOrig[y][x].used, gridOrig[y][x].size); } printf("\n");
}
printf("\n");

//Filesystem              Size  Used  Avail  Use%
////dev/grid/node-x32-y29   90T   65T    25T   72%
printf("leny is %d\n", leny); getchar();
for (int i = 0; i < numFS; i++) {
	//printf("%d: %d %d %d %d\n", i, fs[i].size, fs[i].used, fs[i].avail, fs[i].percU);
	if (i % 900 == 0) {};
}
//getchar();
	tot = 0;

	{
		already[0][MAXX] = 0;
		/*can i move */
		char mypath[1800];
		int mysX; int mysY;
		mysX = MAXX; mysY = 0;
		strcpy(mypath, "U"); if (mysY-1 >= 0)    {next(mysX, mysY-1, 1, 'U', mysX, mysY, mypath);}
		mysX = MAXX; mysY = 0;
		strcpy(mypath, "R"); if (mysX+1 <= MAXX) {next(mysX+1, mysY, 1, 'R', mysX, mysY, mypath);}
		mysX = MAXX; mysY = 0;
		strcpy(mypath, "D"); if (mysY+1 <= MAXY) {next(mysX, mysY+1, 1, 'D', mysX, mysY, mypath);}
		mysX = MAXX; mysY = 0;
		strcpy(mypath, "L"); if (mysX-1 >= 0)    {next(mysX-1, mysY, 1, 'L', mysX, mysY, mypath);}
	}

printf("end of first part..%d.\n", savesPos); 

	long tot3 = 0;
	minPathLen = 9999;
	for (int i = 0; i < savesPos; i++) {
		for (int y5 = 0; y5 <= MAXY; y5++) { for (int x5 = 0; x5 <= MAXX; x5++) { grid[y5][x5] = gridOrig[y5][x5]; } }
		for (int y = 0; y <= MAXY; y++)    { for (int x = 0; x <= MAXX; x++)    { already[y][x] = -1;} }
		if ((int)strlen(saves[i]) > mymax) {mymax = (int)strlen(saves[i]);}
	}
	int start; int end;
	if (strcmp(argv[1], "ex1.txt") == 0) {
		start = 0;
		end = savesPos;
	} else {
#ifdef SECONDLAST
		start = 897;
		end = 898;
#else 
		start = 898;
		end = savesPos;
#endif
	}
	int max = 0;
	for (int i = 0; i < savesPos; i++) {
		if ((int)strlen(saves[i]) > max) {max = (int)strlen(saves[i]);}
	}
	for (int i = start; i < end; i++) {/*so far37*/
		/*if (i % 10 == 0) */{printf("savesPos %d of %d (minPathLen %d)\n", i, savesPos, minPathLen);}
		for (int y5 = 0; y5 <= MAXY; y5++) { for (int x5 = 0; x5 <= MAXX; x5++) { grid[y5][x5] = gridOrig[y5][x5]; } }
		for (int y = 0; y <= MAXY; y++)    { for (int x = 0; x <= MAXX; x++)    { already[y][x] = -1;} }
		//printf("here %d  [%s]\n", i, saves[i]); getchar();

		for (int i = 0; i < 2000; i++) {savesBEGPos[i] = 0;}
		//////////////////////
				//if  (strcmp("LL", saves[i]) != 0) {continue;}
		checkpointPos = 0;
		int sX = MAXX; int sY = 0;
		//for (int j = 0; j < (int)strlen(saves[i]); j++) {
			//printf("(minPathLen: %d) HERE (%d of %d ) charPos: (%d of %d)\n", minPathLen, i, savesPos, j, (int)strlen(saves[i]));
			printf("saves[%d]: [%s]\n", i, saves[i]);
			int mypathLen = 0;
			loop(i, 0, 1, &mypathLen, 0, sX, sY, 0, 0);
		//}
	}
	//fflush(stdout); dup2(fd, 1);
	free(savesBEG);
	printf("tot3 is %ld\n", tot3); getchar(); getchar();

	printf("**minPathLen %d \n", minPathLen); fflush(stdout);
	printf("***pathsNUM %d \n", pathsNUM); fflush(stdout);
	printf("***tot1 %ld \n", tot1); fflush(stdout);
	printf("***tot %ld \n", tot); fflush(stdout);
	printf("mymax: %d\n", mymax);
	printf("ENd...\n");
} 
int ind = 0;
void loop(int sv, int let, int first, int *pathLen, int theEnd, int sX, int sY, int myr, int myrTot) {
	
	ind++;
	if (let >= (int)strlen(saves[sv])) {return;}
	int check[1800];
	for (int i = let; i < (int)strlen(saves[sv]); i++) {
		savesBEGPos[i] = 0;
	}
	mycount = 0;
	generateSAVESFORlettterPos(sv, let, sX, sY);
	if (watch == 1) {printf("ERR: mycount is %d\n", mycount); exit(0);}
	{printf("after generate %d (%d of %d)\n", let, myr, myrTot); fflush(stdout);}
	int mypath = *pathLen;
	int ret;
	for (int r = 0; r < savesBEGPos[let]; r++) {
		//printf(".");
		if (r == 0) {
			check[r] = cpoint(let, r, *pathLen, 0);
		} else {
			check[r] = cpoint(let, r, *pathLen, 1);
		}
	}

	int lens[2000];
	for (int q = 0; q < savesBEGPos[let]; q++) {
		lens[q] = (int)strlen(savesBEG[let][q]);
	}
	sort(lens, lens+savesBEGPos[let]);

	int greater = check[0];
	for (int r = 0; r < 4 /*savesBEGPos[let]*/; r++) {
		int newR;
		printf("lens[0] is %d lens[%d] is %d\n", lens[0], savesBEGPos[let]-1, lens[savesBEGPos[let]-1]);
		for (int i = 0; i < savesBEGPos[let]; i++) {
			if ((int)strlen(savesBEG[let][i]) == lens[r]) {
				newR = r; break;
			}
		}
		*pathLen = mypath;
		if (first == 1) {sX = MAXX; sY = 0; *pathLen = 0;}
		restore(check[newR]-1, pathLen);

		if (let == (int)strlen(saves[sv])-1) {
			ret = carryitout(newR, let, pathLen, 1, &sX, &sY);
		} else {
			ret = carryitout(newR, let, pathLen, 0, &sX, &sY);
		}
			
		if (ret == 0) {continue;} else if (ret == 1) {if (*pathLen < minPathLen); {check[newR] = cpoint(let, newR, *pathLen, 0); loop(sv, let+1, 2, pathLen, (let+1)==(int)(strlen(saves[sv])-1), sX, sY, newR, savesBEGPos[let]);}}
		if (ret == 2) {
			printf("path is %d (includes len of saves(sv))\n", *pathLen+(int)strlen(saves[sv]) );
//			if ((*pathLen + (int)strlen(saves[sv])) < minPathLen) {minPathLen = *pathLen+(int)strlen(saves[sv]);}
		}
		
	}
	//blastAwayCpointsGreaterThan(greater);
	checkpointPos = greater;
	ind--;
	return;
}
int generateSAVESFORlettterPos(int sv, int thepos, int sX, int sY) 
{
			sX = MAXX; sY = 0; 
			int x = sX; int y = sY;
			///sX = x; sY = y;
			//printf("thepos is %d\n", thepos); getchar(); //if (thepos==1) {break;}
			int prevx = x; int prevy = y;
			for (int y = 0; y <= MAXY; y++) { for (int x = 0; x <= MAXX; x++) { already[y][x] = -1;	} }

			//printf("generating paths with sX: %d, sY, %d\n", sX, sY); getchar();
			if (thepos >= (int)strlen(saves[sv])) {/*printf("end of line saves[%d] reached..\n", sv);*/ return -1;}
			//printf ("look: pos:%d (%c) saves[%d]: [%s]\n", thepos, (char)saves[sv][thepos], sv, saves[sv]); 
			for (int i = 0; i <= thepos; i++) {
				prevx = x; prevy = y;
				switch (saves[sv][i]) {
					case 'U':
						y--;
						break;
					case 'R':
						x++;
						break;
					case 'D':
						y++;
						break;
					case 'L':
						 x--;
						break;
				}
			}
			tot1 = 0;
			if (x == sY && x == sX) {return -1;}
			if (grid[y][x].avail < grid[prevy][prevx].used) {
				int myy1, myx1;
				for (int y1 = 0; y1 <= MAXY; y1++) {
					for (int x1 = 0; x1 <= MAXX; x1++) {
					
						if (grid[y1][x1].used == 0) {myy1 = y1; myx1 = x1; goto next;}
						
					}
				}
next:
				//for (int y1 = 0; y1 <= MAXY; y1++) 
				{
					int y1 = myy1;
					//for (int x1 = 0; x1 <= MAXX; x1++) 
					{
						int x1 = myx1;
						//if (x1 == 0 && y1 == 0) { if ((sX == 0 && sY==1) || (sX == 1 && sY == 0)) {} else {continue;} }
						/*NB*///if (y1 == y && x1 == x) {continue;}
						/*NB*///if (y1 == sY && x1 == sX) {continue;}
						///if (y1 == y && x1 == x) {return -1;}
						///if (y1 == sY && x1 == sX) {return -1;}
						for (int y2 = 0; y2 <= MAXY; y2++) { for (int x2 = 0; x2 <= MAXX; x2++) { already[y2][x2] = -1;	} }

						already[y1][x1] = 0;
						/*can i move */ //printf("sX: %d sY: %d\n", sX, sY);
						char mypath[1800];

						for (int y2 = 0; y2 <= MAXY; y2++) { for (int x2 = 0; x2 <= MAXX; x2++) { already[y2][x2] = -1; gridTmp[y2][x2] = grid[y2][x2]; } }
						already[y1][x1] = 0; //start	
						strcpy(mypath, "U");
						if (y1-1 >= 0)    {nextBEG(x1, y1-1, 1, 'U', x1, y1, x, y, sX, sY, x1, y1, thepos, sX, sY, prevx, prevy, x, y, mypath);}
						strcpy(mypath, "R");
						if (x1+1 <= MAXX) {nextBEG(x1+1, y1, 1, 'R', x1, x1, x, y, sX, sY, x1, y1, thepos, sX, sY, prevx, prevy, x, y, mypath);}
						strcpy(mypath, "D");
						if (y1+1 <= MAXY) {nextBEG(x1, y1+1, 1, 'D', x1, y1, x, y, sX, sY, x1, y1, thepos, sX, sY, prevx, prevy, x, y, mypath);}
						strcpy(mypath, "L");
						if (x1-1 >= 0)    {nextBEG(x1-1, y1, 1, 'L', x1, y1, x, y, sX, sY, x1, y1, thepos, sX, sY, prevx, prevy, x, y, mypath);}
					}
				}
				if (savesBEGPos[thepos] != 0) {
					//printf("savesBEGPos[%d] is %d\n", thepos, savesBEGPos[thepos]);//getchar();
				}
			} else {
				//printf("ok continueing...\n");
			}
			return savesBEGPos[thepos];
			//theposust do first char...
}

int carryitout(int myp, int letpos, int *pathLen1, int theEnd, int *sX, int *sY) {
//	for (int z = 0; z < savesBEGPos[letpos]; z++) 
	int z = myp; 
	{
		//for (int y5 = 0; y5 <= MAXY; y5++) { for (int x5 = 0; x5 <= MAXX; x5++) { grid[y5][x5] = gridOrig[y5][x5]; } }
			
		//printf("z is %d\n", z);
		int myX = xtraBEG[letpos][z].x1; int myY = xtraBEG[letpos][z].y1;
		int prevx = xtraBEG[letpos][z].x1; int prevy = xtraBEG[letpos][z].y1;
//printf("setting sX and sY... was %d %d\n", *sX, *sY);
		*sX = xtraBEG[letpos][z].sX; *sY = xtraBEG[letpos][z].sY;

		//printf ("looking @ (saved) PATH: [%s] from: %d %d\n", savesBEG[letpos][z], myX, myY); getchar(); 
		int printit = 1;
		for (int q = 0; q < (int)strlen(savesBEG[letpos][z]); q++) {
			prevx = myX; prevy = myY;	
			switch (savesBEG[letpos][z][q]) {
				case 'U':
					myY--;
					break;
				case 'R':
					myX++;
					break;
				case 'D':
					myY++;
					break;
				case 'L':
					myX--;
					break;
			}
			//printf("already P path %d %d (my)\n", myX, myY);
			//printf("already P path %d %d (prev)\n", prevx, prevy);
			//printf("current sX sY is %d %d\n", *sX, *sY);
			//if (prevx == *sX && prevy == *sY) {printf("**already\n"); return 0;}
			//if (myX == *sX && myY == *sY) {printf("**already\n"); return 0;}
			if (myX == xtraBEG[letpos][z].frslotX && myY == xtraBEG[letpos][z].frslotY) {/*printf("**alaready\n");*/ return 0;}
			//printf("myX: %d myY: %d\n", myX, myY); //getchar();
			//printf("prevx2: %d prevy2: %d\n", prevx2, prevy2); getchar();
			//printf("avail:[%d][%d] %d V used[%d][%d] : %d\n", prevy, prevx, grid[prevy][prevx].avail, myY, myX, grid[myY][myX].used);
			if (grid[prevy][prevx].avail >= grid[myY][myX].used) {
				//printf("(not end)BEFORE:\n");for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }
				grid[prevy][prevx].avail -= grid[myY][myX].used;
				grid[prevy][prevx].used  += grid[myY][myX].used;
				grid[myY][myX].avail = grid[myY][myX].size;
				grid[myY][myX].used = 0;
				//printf("grid[myY][myX] is %d zerop (myX:%d) (myY:%d)\n", grid[myY][myX].used, myX, myY); getchar();
				//printf("(not end)AFTER:\n"); for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }
				(*pathLen1) = *pathLen1 + 1;

			} else {
				//printf("path no good ... break\n");
				printit = 0; break;
			}
		}
		if (printit == 1) {
			int myfrslotY = xtraBEG[letpos][z].toslotY; int myfrslotX = xtraBEG[letpos][z].toslotX;
			int mytoslotY = xtraBEG[letpos][z].frslotY; int mytoslotX = xtraBEG[letpos][z].frslotX;

			//int mysY = xtraBEG[letpos][z].y; int mysX = xtraBEG[letpos][z].x;
			//printf("(end BEFORE)\n"); for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }

			grid[myfrslotY][mytoslotX].avail -= grid[mytoslotY][mytoslotX].used;
			grid[myfrslotY][myfrslotX].used  += grid[mytoslotY][mytoslotX].used;
			grid[mytoslotY][mytoslotX].avail = grid[mytoslotY][mytoslotX].size;
			grid[mytoslotY][mytoslotX].used = 0;
			//printf("(end)slot over:\n "); for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }
			pathsNUM++;
			//printf("path good ** setting sX sY to %d %d:\n", sX, sY); getchar();
			//if (xtraBEG[letpos][z].x == 0 && xtraBEG[letpos][z].y == 0 && ((sX == 0 && sY == 1) || (sX==1 && sY==0))) {
			//printf("\nCONxy(%d %d) sXY(%d %d) x1y1 (%d %d) G(%d %d)\n", xtraBEG[letpos][z].x, xtraBEG[letpos][z].y, xtraBEG[letpos][z].sX, xtraBEG[letpos][z].sY, xtraBEG[letpos][z].x1, xtraBEG[letpos][z].y1, *sX, *sY); getchar();
			if (theEnd) {// && ((xtraBEG[letpos][z].sX == 1 && xtraBEG[letpos][z].sY == 0) || (xtraBEG[letpos][z].sX == 0 && xtraBEG[letpos][z].sY == 1))) {
				//printf("(end end)thats the end:::\n"); for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); } getchar();
				xtraBEG[letpos][z].sX = xtraBEG[letpos][z].x;
				xtraBEG[letpos][z].sY = xtraBEG[letpos][z].y;
				*sX = xtraBEG[letpos][z].x;
				*sY = xtraBEG[letpos][z].y;
				return 2;
			}
			xtraBEG[letpos][z].sX = xtraBEG[letpos][z].x;
			xtraBEG[letpos][z].sY = xtraBEG[letpos][z].y;
			*sX = xtraBEG[letpos][z].x;
			*sY = xtraBEG[letpos][z].y;
			return 1;
		} else {
			//printf("ret zero from carryitout\n");
			return 0;
		}
	}
	return 0;
}
void savepathBEG(char path[], int x1, int y1, int letpos, int x, int y, int sX, int sY, int frslotX, int frslotY, int toslotX, int toslotY) {
	//printf("savespathBEG: [%s]\n", path);
	int found = 0;
	for (int i = 0; i < savesBEGPos[letpos]; i++) {
		if (strcmp(savesBEG[letpos][i], path) == 0) {
			found = 1; break;
		}
	}
	if (found == 0) {
if (savesBEGPos[letpos] >= 1800) {printf("ERROR too large...\n"); watch = 1;}
		xtraBEG[letpos][savesBEGPos[letpos]].frslotY = frslotY;
		xtraBEG[letpos][savesBEGPos[letpos]].toslotY = toslotY;
		xtraBEG[letpos][savesBEGPos[letpos]].frslotX = frslotX;
		xtraBEG[letpos][savesBEGPos[letpos]].toslotX = toslotX;
		xtraBEG[letpos][savesBEGPos[letpos]].sX = sX;
		xtraBEG[letpos][savesBEGPos[letpos]].sY = sY;
		xtraBEG[letpos][savesBEGPos[letpos]].x = x;
		xtraBEG[letpos][savesBEGPos[letpos]].y = y;
		xtraBEG[letpos][savesBEGPos[letpos]].x1 = x1;
		xtraBEG[letpos][savesBEGPos[letpos]].y1 = y1;
		strcpy(savesBEG[letpos][savesBEGPos[letpos]], path); if (watch == 0) {savesBEGPos[letpos]++;mycount++;} else if (watch == 1) {mycount++;}
	}
}

void savepath(char path[]) {
	int found = 0;
	for (int i = 0; i < savesPos; i++) {
		if (strcmp(saves[i], path) == 0) {
			found = 1; break;
		}
	}
	if (found == 0) { strcpy(saves[savesPos], path); savesPos++;}
}


void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, int DTX, int DTY, int igx, int igy, int vx1, int vy1, int letpos, int sX, int sY, int frslotX, int frslotY, int toslotX, int toslotY, char path[]) {
	
	//printf("in nextBEG");
	if (x == igx && y == igy) {/*printf("IGNORING %d %d\n", igx, igy); getchar(); */return;}
	if (x == DTX && y == DTY) {/*printf("BEGreached end steps %d, %s [%ld]\n", steps, path, tot1); */tot1++; 
		///printf("**SAVING... path %s\n", path);
		savepathBEG(path, vx1, vy1, letpos, DTX, DTY, sX, sY, frslotX, frslotY, toslotX, toslotY); return;}
//printf("x:%d y:%d --- %d %d\n", x, y, DTX, DTY);
	int prevx = frX;
	int prevy = frY;
	int myX = x;
	int myY = y;
/*
	if (grid[prevy][prevx].avail >= grid[myY][myX].used && (steps < already[y][x]  || already[y][x] == -1)) {
		already[y][x] = steps;
*/

//	if (gridTmp[prevy][prevx].avail >= gridTmp[myY][myX].used && (steps < already[myY][myX]  || already[myY][myX] == -1)) {
	//printf("steps: %d already[myY][myX] %d\n", steps, already[myY][myX]);
	if (gridTmp[prevy][prevx].size >= gridTmp[myY][myX].used && (steps < already[myY][myX]  || already[myY][myX] == -1)) {
		already[myY][myX] = steps;
		//gridTmp[prevy][prevx].avail -= gridTmp[myY][myX].used;
		//gridTmp[prevy][prevx].used  += gridTmp[myY][myX].used;
		//gridTmp[myY][myX].avail = gridTmp[myY][myX].size;
		//gridTmp[myY][myX].used = 0;

		char newpath[1800];
		sprintf(newpath, "%s%c", path, 'U');
	if (strlen(newpath)>= 1800) {printf("ERR"); exit(0);}
		if (y-1 >= 0)    {nextBEG(x, y-1, steps+1, 'U', x, y, DTX, DTY, igx, igy, vx1, vy1, letpos, sX, sY, frslotX, frslotY, toslotX, toslotY, newpath);}
		sprintf(newpath, "%s%c", path, 'R');
		if (x+1 <= MAXX) {nextBEG(x+1, y, steps+1, 'R', x, y, DTX, DTY, igx, igy, vx1, vy1, letpos, sX, sY, frslotX, frslotY, toslotX, toslotY, newpath);}
		sprintf(newpath, "%s%c", path, 'D');
		if (y+1 <= MAXY) {nextBEG(x, y+1, steps+1, 'D', x, y, DTX, DTY, igx, igy, vx1, vy1, letpos, sX, sY, frslotX, frslotY, toslotX, toslotY, newpath);}
		sprintf(newpath, "%s%c", path, 'L');
		if (x-1 >= 0)    {nextBEG(x-1, y, steps+1, 'L', x, y, DTX, DTY, igx, igy, vx1, vy1, letpos, sX, sY, frslotX, frslotY, toslotX, toslotY, newpath);}
	} else {
		return;
	}
}
void next(int x, int y, int steps, char DIR, int frX, int frY, char path[]) {
	
	if (x == 0 && y == 0) {/*printf("reached end steps %d, %s\n", steps, path); */savepath(path);tot++; return;}
	if (grid[y][x].size >= grid[frY][frX].used && (steps < already[y][x]  || already[y][x] == -1)) {
		///printf("already[y][x] %d steps %d\n", already[y][x], steps);
		already[y][x] = steps;
		//printf("pot yes %c\n", DIR);
		char newpath[1800];
		sprintf(newpath, "%s%c", path, 'U');
		if (y-1 >= 0)    {next(x, y-1, steps+1, 'U', x, y, newpath);}
		sprintf(newpath, "%s%c", path, 'R');
		if (x+1 <= MAXX) {next(x+1, y, steps+1, 'R', x, y, newpath);}
		sprintf(newpath, "%s%c", path, 'D');
		if (y+1 <= MAXY) {next(x, y+1, steps+1, 'D', x, y, newpath);}
		sprintf(newpath, "%s%c", path, 'L');
		if (x-1 >= 0)    {next(x-1, y, steps+1, 'L', x, y, newpath);}
	} else {
		return;
	}
}

