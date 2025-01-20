#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>

using namespace std;

//#define getchar()
//int path = 0;
int minPath;
int lenx, leny;
#define DAY "2016 day22 part1 \n"
#define _DEBUG_
long tot;
long tot1;
#define SIZE 200
int BEGX, BEGY;
int pathsNUM = 0;
int pathsLen[100] = {0};
struct fs_s {
	int size;
	int used;
	int avail;
	int percU;
	char name[25];
};
struct fs_s fs[1000];
map <string, struct fs_s> mp;
char goal[100]; 
void next(int x, int y, int steps, char DIR, int frX, int frY, char path[1000]);

#define MAXX 2
#define MAXY 2
int sX = MAXX; int sY = 0; 
//#define MAXX 32
///#define MAXY 20
struct fs_s grid[MAXY+2][MAXX+2];
struct fs_s gridOrig[MAXY+2][MAXX+2];
int mymax = 0;
int already[MAXY+2][MAXX+2];
int alreadyBEG[MAXY+2][MAXX+2];
void savespath(char path[1000]);
char saves[10000][1000];
int savesPos = 0;
void savepathBEG(char path[1000], int x1, int y1, int letpos);
char savesBEG[500][1000][1000];
int savesBEGPos[500] = {0};
struct xtra_s {
	int x1;
	int y1;
	int x;
	int y;
	int sX;
	int sY;
};
struct xtra_s xtraBEG[500][5000];

void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, char path[1000], int STX, int STY, int igx, int igy, int vx1, int vy1, int letpos);
int carryitout(int myp, int letpos, int *pathLen);

struct fs_s checkpoint[10000][MAXY+1][MAXX+1];
int checkpointAL[10000][MAXY+1][MAXX+1];
int checkpointPos = 0;

struct xtra_xtra_s {
	int sX;
	int sY;
};
struct  xtra_xtra_s cp[10000];
int cpoint();
void restore(int mypos);
void remove(int mypos);
void loop(int sv, int let, int first, int *pathLen);
void generateSAVESFORlettterPos(int sv, int thepos);


void remove(int mypos) {
	for (int i = mypos; i  < checkpointPos-1; i++) {
		for (int y = 0; y <= MAXY; y++) {
			for (int x = 0; x <= MAXX; x++) {
				checkpoint[i][y][x] = checkpoint[i+1][y][x];
			}
		}
	}
	checkpointPos--;
}
void restore(int mypos) {
	for (int y = 0; y <= MAXY; y++) {
		for (int x = 0; x <= MAXX; x++) {
			alreadyBEG[y][x] = checkpointAL[mypos][y][x];
			grid[y][x] = checkpoint[mypos][y][x];
		}
	}
	sX = cp[mypos].sX;
	sY = cp[mypos].sY;
}
int cpoint() {
	for (int y = 0; y <= MAXY; y++) {
		for (int x = 0; x <= MAXX; x++) {
			checkpoint[checkpointPos][y][x] = grid[y][x];
			checkpointAL[checkpointPos][y][x] = alreadyBEG[y][x];
		}
	}
	cp[checkpointPos].sX = sX;
	cp[checkpointPos].sY = sY;
	checkpointPos++;
	return checkpointPos;
}
int main(int argc, char **argv)
{
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
	for (int y = 0; y <= MAXY; y++) {
		for (int x = 0; x <= MAXX; x++) {
			already[y][x] = -1;	
			alreadyBEG[y][x] = -1;	
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

for (int y = 0; y <= MAXY; y++) {
	for (int x = 0; x <= MAXX; x++) {
		gridOrig[y][x] = grid[y][x];
		printf(" %d/%d", grid[y][x].used, grid[y][x].size);
	}
	printf("\n");
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
		char mypath[1000];
		sX = MAXX; sY = 0;
		strcpy(mypath, "U"); if (sY-1 >= 0)    {next(sX, sY-1, 1, 'U', sX, sY, mypath);}
		sX = MAXX; sY = 0;
		strcpy(mypath, "R"); if (sX+1 <= MAXX) {next(sX+1, sY, 1, 'R', sX, sY, mypath);}
		sX = MAXX; sY = 0;
		strcpy(mypath, "D"); if (sY+1 <= MAXY) {next(sX, sY+1, 1, 'D', sX, sY, mypath);}
		sX = MAXX; sY = 0;
		strcpy(mypath, "L"); if (sX-1 >= 0)    {next(sX-1, sY, 1, 'L', sX, sY, mypath);}
	}

printf("end of first part...\n"); 

	long tot3 = 0;
	int pos = cpoint();
	minPath = 9999;
	for (int i = 0; i < savesPos; i++) {
		for (int y5 = 0; y5 <= MAXY; y5++) { for (int x5 = 0; x5 <= MAXX; x5++) { grid[y5][x5] = gridOrig[y5][x5]; } }
		for (int y = 0; y <= MAXY; y++)    { for (int x = 0; x <= MAXX; x++)    { already[y][x] = -1;	alreadyBEG[y][x] = -1;	} }
		printf("here %d  [%s]\n", i, saves[i]); getchar();
		restore(pos-1);
		if (strcmp(saves[i], "LL") != 0) {continue;}
		for (int i = 0; i < 500; i++) {savesBEGPos[i] = 0;}
		//////////////////////
		//int x = sX; int y = sY;
		printf("saves[i] is %s\n", saves[i]); getchar();
		
		for (int j = 0; j < (int)strlen(saves[i]); j++) {
			int mypathlen = 0;
			loop(i, j, 1, &mypathlen);
		}
	}
	printf("tot3 is %ld\n", tot3); getchar(); getchar();

	printf("**minPath %d \n", minPath); fflush(stdout);
	printf("***pathsNUM %d \n", pathsNUM); fflush(stdout);
	printf("***tot1 %ld \n", tot1); fflush(stdout);
	printf("***tot %ld \n", tot); fflush(stdout);
	printf("mymax: %d\n", mymax);
	printf("ENd...\n");
} 
void loop(int sv, int let, int first, int *pathLen) {
	
	int pos = cpoint();
	generateSAVESFORlettterPos(sv, let);
	int r;
	int mypath = *pathLen;
	int ret;
	for (r = 0; r < savesBEGPos[let]; r++) {
		*pathLen = mypath;
		if (first == 1) {*pathLen = 0;}
		restore(pos-1);
		if ((ret = carryitout(r, let, pathLen)) == 0) {continue;} else if (ret == 1) {*pathLen = ret; loop(sv, let+1, 2, pathLen);}
		if (ret == 2) {
			printf("path is %d (plus len of saves(sv)\n", *pathLen+(int)strlen(saves[sv]) ); getchar();
			if ((*pathLen + (int)strlen(saves[sv])) < minPath) {minPath = *pathLen+(int)strlen(saves[sv]);}
		}
		
	}
	return;
}
void generateSAVESFORlettterPos(int sv, int thepos) 
{
			///int sX = MAXX; int sY = 0; 
			int x = sX; int y = sY;
			sX = x; sY = y;
			//printf("thepos is %d\n", thepos); if (thepos==1) {break;}
			int prevx = x; int prevy = y;
			for (int y = 0; y <= MAXY; y++) { for (int x = 0; x <= MAXX; x++) { already[y][x] = -1;	} }

			printf ("look: (%c) ", saves[sv][thepos]); 
			switch (saves[sv][thepos]) {
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
					printf("got L\n"); getchar();
					 x--;
					break;
			}
			tot1 = 0;
			//if (alreadyBEG[y][x] == 1) {return;}
			//if (x == sY && x == sX) {return;}
			
			if (grid[y][x].avail < grid[prevy][prevx].used) {
				for (int y1 = 0; y1 <= MAXY; y1++) {
					for (int x1 = 0; x1 <= MAXX; x1++) {
						//if (y1 == y && x1 == x) {continue;}
						//if (y1 == sY && x1 == sX) {continue;}
						for (int y2 = 0; y2 <= MAXY; y2++) { for (int x2 = 0; x2 <= MAXX; x2++) { already[y2][x2] = -1;	} }

						already[y1][x1] = 0;
						/*can i move */ //printf("sX: %d sY: %d\n", sX, sY);
						char mypath[1000];
						strcpy(mypath, "U");
						if (y1-1 >= 0)    {nextBEG(x1, y1-1, 1, 'U', x1, y1, mypath, x, y, sX, sY, x1, y1, thepos);}
						strcpy(mypath, "R");
						if (x1+1 <= MAXX) {nextBEG(x1+1, y1, 1, 'R', x1, x1, mypath, x, y, sX, sY, x1, y1, thepos);}
						strcpy(mypath, "D");
						if (y1+1 <= MAXY) {nextBEG(x1, y1+1, 1, 'D', x1, y1, mypath, x, y, sX, sY, x1, y1, thepos);}
						strcpy(mypath, "L");
						if (x1-1 >= 0)    {nextBEG(x1-1, y1, 1, 'L', x1, y1, mypath, x, y, sX, sY, x1, y1, thepos);}
					}
				}
				printf("savesBEGPos[thepos] is %d\n", savesBEGPos[thepos]);//getchar();
				//carryitout(thepos);
			} else {
				printf("ok continueing...\n");
			}
			//theposust do first char...
}

int carryitout(int myp, int letpos, int *pathLen1) {
//	for (int z = 0; z < savesBEGPos[letpos]; z++) 
	int z = myp; 
	{
		//for (int y5 = 0; y5 <= MAXY; y5++) { for (int x5 = 0; x5 <= MAXX; x5++) { grid[y5][x5] = gridOrig[y5][x5]; } }
			
		printf("z is %d\n", z);
		int myX = xtraBEG[letpos][z].x1; int myY = xtraBEG[letpos][z].y1;
		int prevx = xtraBEG[letpos][z].x1; int prevy = xtraBEG[letpos][z].y1;
		sX = xtraBEG[letpos][z].sX; sY = xtraBEG[letpos][z].sY;

		printf ("looking @ PATH: [%s] from: %d %d\n", savesBEG[letpos][z], myX, myY); //getchar(); 
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
			printf("already P path %d %d (my)\n", myX, myY);
			printf("already P path %d %d (prev)\n", prevx, prevy);
			printf("current sX sY is %d %d\n", sX, sY);
			//if (alreadyBEG[prevy][prevx] == 1) { printf("path already\n"); return 0; }
			//if (prevx == sX && prevy == sY) {printf("**already\n"); return 0;}
			if (myX == sX && myY == sY) {printf("**already\n"); return 0;}
			
			//printf("myX: %d myY: %d\n", myX, myY); //getchar();
			//printf("prevx2: %d prevy2: %d\n", prevx2, prevy2); getchar();
			//printf("avail:[%d][%d] %d V used[%d][%d] : %d\n", prevy, prevx, grid[prevy][prevx].avail, myY, myX, grid[myY][myX].used);
			if (grid[prevy][prevx].avail >= grid[myY][myX].used) {
				printf("(not end)BEFORE:\n");
				for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }
				grid[prevy][prevx].avail -= grid[myY][myX].used;
				grid[prevy][prevx].used  += grid[myY][myX].used;
				grid[myY][myX].avail = grid[myY][myX].size;
				grid[myY][myX].used = 0;
				printf("(not end)AFTER:\n");
				for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }
				alreadyBEG[myY][myX] = 1;
				(*pathLen1) = *pathLen1 + 1;

			} else {
				printf("path no good ... break\n");
				printit = 0; break;
			}
		}
		if (printit == 1) {
			//if (alreadyBEG[sY][sX] == 1) { printf("path already\n"); return 0; }
			printf("\nxy(%d %d) sXY(%d %d) x1y1 (%d %d) G(%d %d)\n", xtraBEG[letpos][z].x, xtraBEG[letpos][z].y, xtraBEG[letpos][z].sX, xtraBEG[letpos][z].sY, xtraBEG[letpos][z].x1, xtraBEG[letpos][z].y1, sX, sY); getchar();
			int mysY = xtraBEG[letpos][z].y; int mysX = xtraBEG[letpos][z].x;
			printf("(end BEFORE)\n");
			for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }
			grid[xtraBEG[letpos][z].y1][xtraBEG[letpos][z].x1].avail -= grid[mysY][mysX].used;
			grid[xtraBEG[letpos][z].y1][xtraBEG[letpos][z].x1].used  += grid[mysY][mysX].used;
			grid[mysY][mysX].avail = grid[mysY][mysX].size;
			grid[mysY][mysX].used = 0;
			printf("(end)slot over:\n ");
			for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); }
			//pathsNUM++;
			printf("\n"); 
			sX = xtraBEG[letpos][z].x;
			sY = xtraBEG[letpos][z].y;
			printf("path good ** setting sX sY to %d %d:\n", sX, sY); getchar();
			if (xtraBEG[letpos][z].x == 0 && xtraBEG[letpos][z].y == 0) {
				printf("(end end)thats the end:::\n");
				for (int y6 = 0; y6 <= MAXY; y6++) { for (int x6 = 0; x6 <= MAXX; x6++) { printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size); } printf("\n"); } getchar();
				return 2;
			}
			return 1;
		} else {
			printf("ret zero from carryitout\n");
			return 0;
		}
	}
	return 0;
}

void savepathBEG(char path[1000], int x1, int y1, int letpos, int x, int y) {
	int found = 0;
	for (int i = 0; i < savesBEGPos[letpos]; i++) {
		if (strcmp(savesBEG[letpos][i], path) == 0) {
			found = 1; break;
		}
	}
	if (found == 0) {
		xtraBEG[letpos][savesBEGPos[letpos]].sX = sX;
		xtraBEG[letpos][savesBEGPos[letpos]].sY = sY;
		xtraBEG[letpos][savesBEGPos[letpos]].x = x;
		xtraBEG[letpos][savesBEGPos[letpos]].y = y;
		xtraBEG[letpos][savesBEGPos[letpos]].x1 = x1;
		xtraBEG[letpos][savesBEGPos[letpos]].y1 = y1;
		strcpy(savesBEG[letpos][savesBEGPos[letpos]], path); savesBEGPos[letpos]++;
	}
}

void savepath(char path[1000]) {
	int found = 0;
	for (int i = 0; i < savesPos; i++) {
		if (strcmp(saves[i], path) == 0) {
			found = 1; break;
		}
	}
	if (found == 0) { strcpy(saves[savesPos], path); savesPos++;}
}


void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, char path[1000], int DTX, int DTY, int igx, int igy, int vx1, int vy1, int letpos) {
	
	//if (x == igx && y == igy) {/*printf("IGNORING %d %d\n", igx, igy); getchar();*/ return;}
	if (x == DTX && y == DTY) {/*printf("BEGreached end steps %d, %s [%ld]\n", steps, path, tot1); */tot1++; 
		savepathBEG(path, vx1, vy1, letpos, DTX, DTY); return;}

	if (grid[y][x].size >= grid[frY][frX].used && (steps < already[y][x]  || already[y][x] == -1)) {
		//printf("already[y][x] %d steps %d\n", already[y][x], steps);
		already[y][x] = steps;
		char newpath[1000];
		sprintf(newpath, "%s%c", path, 'U');
		if (y-1 >= 0)    {nextBEG(x, y-1, steps+1, 'U', x, y, newpath, DTX, DTY, igx, igy, vx1, vy1, letpos);}
		sprintf(newpath, "%s%c", path, 'R');
		if (x+1 <= MAXX) {nextBEG(x+1, y, steps+1, 'R', x, y, newpath, DTX, DTY, igx, igy, vx1, vy1, letpos);}
		sprintf(newpath, "%s%c", path, 'D');
		if (y+1 <= MAXY) {nextBEG(x, y+1, steps+1, 'D', x, y, newpath, DTX, DTY, igx, igy, vx1, vy1, letpos);}
		sprintf(newpath, "%s%c", path, 'L');
		if (x-1 >= 0)    {nextBEG(x-1, y, steps+1, 'L', x, y, newpath, DTX, DTY, igx, igy, vx1, vy1, letpos);}
	} else {
		return;
	}
}
void next(int x, int y, int steps, char DIR, int frX, int frY, char path[1000]) {
	
	if (x == 0 && y == 0) {printf("reached end steps %d, %s\n", steps, path); savepath(path);tot++; return;}
	if (grid[y][x].size >= grid[frY][frX].used && (steps < already[y][x]  || already[y][x] == -1)) {
		printf("already[y][x] %d steps %d\n", already[y][x], steps);
		already[y][x] = steps;
		printf("pot yes %c\n", DIR);
		char newpath[1000];
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

