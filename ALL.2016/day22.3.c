#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>

using namespace std;

int lenx, leny;
#define DAY "2016 day22 part1 \n"
#define _DEBUG_
long tot;
long tot1;
#define SIZE 200
int BEGX, BEGY;

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
//#define MAXX 32
///#define MAXY 20
struct fs_s grid[MAXY+2][MAXX+2];
struct fs_s gridOrig[MAXY+2][MAXX+2];
struct fs_s checkpoint[10000][MAXY+1][MAXX+1];
int checkpointPos = 0;
int mymax = 0;
int already[MAXY+2][MAXX+2];
int cpoint();
void restore(int mypos);
void remove(int mypos);
void savespath(char path[1000]);
char saves[10000][1000];
int savesPos = 0;
void savespathBEG(char path[1000]);
char savesBEG[500000][1000];
int savesBEGPos = 0;
void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, char path[1000], int STX, int STY);
void savespathBEG2(char path[1000]);
char savesBEG2[10000][1000];
int savesBEG2Pos = 0;
void nextBEG2(int x, int y, int steps, char DIR, int frX, int frY, char path[1000]);

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
	for (int y = 0; y < MAXY; y++) {
		for (int x = 0; x < MAXX; x++) {
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
		if (used[strlen(used)-1] != 'T') {
			printf("here1\n"); getchar();
		}
		if (avail[strlen(avail)-1] != 'T') {
			printf("here2\n"); getchar();
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
		int sX = MAXX;
		int sY = 0;
		already[0][MAXX] = 0;
		/*can i move */
		char mypath[1000];

		strcpy(mypath, "U"); if (sY-1 >= 0)    {next(sX, sY-1, 1, 'U', sX, sY, mypath);}
		strcpy(mypath, "R"); if (sX+1 <= MAXX) {next(sX+1, sY, 1, 'R', sX, sY, mypath);}
		strcpy(mypath, "D"); if (sY+1 <= MAXY) {next(sX, sY+1, 1, 'D', sX, sY, mypath);}
		strcpy(mypath, "L"); if (sX-1 >= 0)    {next(sX-1, sY, 1, 'L', sX, sY, mypath);}
	}

printf("end of first part...\n"); getchar(); getchar();
	long tot3 = 0;
	for (int i = 0; i < savesPos; i++) {
		int sX = MAXX;
		int sY = 0;
		int x = sX; int y = sY;
		for (int j = 0; j < (int)strlen(saves[i]-1); j++) {
			int xprev = x; int yprev = y;
			for (int y = 0; y < MAXY; y++) {
				for (int x = 0; x < MAXX; x++) {
					already[y][x] = -1;	
				}
			}

			switch (saves[i][j]) {
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
			tot1 = 0;
			if (grid[y][x].avail < grid[prev][prevx].used) {
				for (int y1 = 0; y1 <= MAXY; y1++) {
					for (int x1 = 0; x1 <= MAXX; x1++) {
						//if (x == 0 && y==0 ) {continue;}
						for (int y2 = 0; y2 < MAXY; y2++) {
							for (int x2 = 0; x2 < MAXX; x2++) {
								already[y2][x2] = -1;	
							}
						}

						int sX = x;
						int sY = y;
						already[y][x] = 0;
						/*can i move */
						char mypath[1000];
						strcpy(mypath, "U");
						if (sY-1 >= 0)    {nextBEG(sX, sY-1, 1, 'U', sX, sY, mypath, sX, sY);}
						strcpy(mypath, "R");
						if (sX+1 <= MAXX) {nextBEG(sX+1, sY, 1, 'R', sX, sY, mypath, sX, sY);}
						strcpy(mypath, "D");
						if (sY+1 <= MAXY) {nextBEG(sX, sY+1, 1, 'D', sX, sY, mypath, sX, sY);}
						strcpy(mypath, "L");
						if (sX-1 >= 0)    {nextBEG(sX-1, sY, 1, 'L', sX, sY, mypath, sX, sY);}
					}
				}
			}
			printf("savesBEGPos is %d\n", savesBEGPos);
		}
	}
	printf("tot3 is %ld\n", tot3); getchar(); getchar();
/*
	{
		tot1 = 0;
		for (int y = 0; y <= MAXY; y++) {
			for (int x = 0; x <= MAXX; x++) {
				if (x == 0 && y==0 ) {continue;}
				for (int y = 0; y < MAXY; y++) {
					for (int x = 0; x < MAXX; x++) {
						already[y][x] = -1;	
					}
				}

				int sX = x;
				int sY = y;
				already[y][x] = 0;
				/*can i move */
				char mypath[1000];
				strcpy(mypath, "U");
				if (sY-1 >= 0)    {nextBEG(sX, sY-1, 1, 'U', sX, sY, mypath, sX, sY);}
				strcpy(mypath, "R");
				if (sX+1 <= MAXX) {nextBEG(sX+1, sY, 1, 'R', sX, sY, mypath, sX, sY);}
				strcpy(mypath, "D");
				if (sY+1 <= MAXY) {nextBEG(sX, sY+1, 1, 'D', sX, sY, mypath, sX, sY);}
				strcpy(mypath, "L");
				if (sX-1 >= 0)    {nextBEG(sX-1, sY, 1, 'L', sX, sY, mypath, sX, sY);}
			}
		}
	}	
*/



	printf("***tot1 %ld \n", tot1); fflush(stdout);
	printf("***tot %ld \n", tot); fflush(stdout);
	printf("mymax: %d\n", mymax);
	printf("ENd...\n");
} 

void savepathBEG2(char path[1000]) {
	strcpy(savesBEG2[savesBEG2Pos], path);
	savesBEG2Pos++;
}

void savepathBEG(char path[1000]) {
	strcpy(savesBEG[savesBEGPos], path);
	savesBEGPos++;
}

void savepath(char path[1000]) {
	strcpy(saves[savesPos], path);
	savesPos++;
}

/*
void nextBEG2(int x, int y, int steps, char DIR, int frX, int frY, char path[1000]) {
	
	if (x == BEGX && y == BEGY) {printf("BEGreached end steps %d, %s [%ld]\n", steps, path, tot1); tot1++; savepathBEG2(path); return;}

		for (int y = 0; y <= MAXY; y++) {
			for (int x = 0; x <= MAXX; x++) {
				if (x == 0 && y==0 ) {continue;}
				for (int y = 0; y < MAXY; y++) {
					for (int x = 0; x < MAXX; x++) {
						already[y][x] = -1;	
					}
				}
	
	if (grid[y][x].size >= grid[frY][frX].used && (steps < already[y][x]  || already[y][x] == -1)) {
		//printf("already[y][x] %d steps %d\n", already[y][x], steps);
		already[y][x] = steps;
//		printf("pot yes %c\n", DIR);
		char newpath[1000];
		sprintf(newpath, "%s%c", path, 'U');
		if (y-1 >= 0)    {nextBEG2(x, y-1, steps+1, 'U', x, y, newpath);}
		sprintf(newpath, "%s%c", path, 'R');
		if (x+1 <= MAXX) {nextBEG2(x+1, y, steps+1, 'R', x, y, newpath);}
		sprintf(newpath, "%s%c", path, 'D');
		if (y+1 <= MAXY) {nextBEG2(x, y+1, steps+1, 'D', x, y, newpath);}
		sprintf(newpath, "%s%c", path, 'L');
		if (x-1 >= 0)    {nextBEG2(x-1, y, steps+1, 'L', x, y, newpath);}
	} else {
		return;
	}
		}
	}
}
*/

void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, char path[1000], int STX, int STY) {
	
	if (x == STX && y == STY) {/*printf("BEGreached end steps %d, %s [%ld]\n", steps, path, tot1); */tot1++; savepathBEG(path); return;}

	if (grid[y][x].size >= grid[frY][frX].used && (steps < already[y][x]  || already[y][x] == -1)) {
		//printf("already[y][x] %d steps %d\n", already[y][x], steps);
		already[y][x] = steps;
//		printf("pot yes %c\n", DIR);
		char newpath[1000];
		sprintf(newpath, "%s%c", path, 'U');
		if (y-1 >= 0)    {nextBEG(x, y-1, steps+1, 'U', x, y, newpath, STX, STY);}
		sprintf(newpath, "%s%c", path, 'R');
		if (x+1 <= MAXX) {nextBEG(x+1, y, steps+1, 'R', x, y, newpath, STX, STY);}
		sprintf(newpath, "%s%c", path, 'D');
		if (y+1 <= MAXY) {nextBEG(x, y+1, steps+1, 'D', x, y, newpath, STX, STY);}
		sprintf(newpath, "%s%c", path, 'L');
		if (x-1 >= 0)    {nextBEG(x-1, y, steps+1, 'L', x, y, newpath, STX, STY);}
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
void remove(int mypos) {
	for (int i = mypos; i  < checkpointPos-1; i++) {
		for (int y = 0; y < MAXY; y++) {
			for (int x = 0; x < MAXX; x++) {
				checkpoint[i][y][x] = checkpoint[i+1][y][x];
			}
		}
	}
	checkpointPos--;
}
void restore(int mypos) {
	for (int y = 0; y < MAXY; y++) {
		for (int x = 0; x < MAXX; x++) {
			grid[y][x] = checkpoint[mypos][y][x];
		}
	}
}
int cpoint() {
	for (int y = 0; y < MAXY; y++) {
		for (int x = 0; x < MAXX; x++) {
			checkpoint[checkpointPos][y][x] = grid[y][x];
		}
	}
	checkpointPos++;
	if (checkpointPos > mymax) {mymax = checkpointPos;}
	return checkpointPos;
}
/*
	for (int a = 0; a < numFS; a++) {
		if (fs[a].used == 0) {continue;}
		for (int b = 0; b < numFS; b++) {
			if (a == b) {continue;}
			//printf("%d\n", fs[b].used);
			if (strcmp(fs[a].name, fs[b].name) == 0) {continue; }
			if (fs[b].avail >= fs[a].used) {tot++;} 
		}
	}
*/

/*
	if (x <= MAXX && x >= 0 && y <= MAXY && y>= 0) {
		if (grid[y][x].avail >= grid[frY][frX].used) {
			printf("YES %c\n", DIR);
		} else {
			printf("NO %c\n", DIR);
*/
