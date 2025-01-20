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
void savespath(char path[1000]);
char saves[10000][1000];
int savesPos = 0;
void savespathBEG(char path[1000]);
char savesBEG[500000][1000];
int savesBEGPos = 0;
void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, char path[1000], int STX, int STY);

struct fs_s checkpoint[10000][MAXY+1][MAXX+1];
int checkpointPos = 0;

int cpoint();
void restore(int mypos);
void remove(int mypos);


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

printf("end of first part...\n"); 

	long tot3 = 0;
	for (int i = 0; i < savesPos; i++) {
		printf("here %d  [%s]\n", i, saves[i]); getchar();
		int sX = MAXX;
		int sY = 0;
		int x = sX; int y = sY;
		for (int j = 0; j < (int)strlen(saves[i])-1; j++) {
			printf("j is %d\n", j);
			int prevx = x; int prevy = y;
			for (int y = 0; y < MAXY; y++) {
				for (int x = 0; x < MAXX; x++) {
					already[y][x] = -1;	
				}
			}

			printf ("look: (%c) ", saves[i][j]); 
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

			if (grid[y][x].avail < grid[prevy][prevx].used) {
				for (int y1 = 0; y1 <= MAXY; y1++) {
					for (int x1 = 0; x1 <= MAXX; x1++) {
						for (int y2 = 0; y2 < MAXY; y2++) {
							for (int x2 = 0; x2 < MAXX; x2++) {
								already[y2][x2] = -1;	
							}
						}

						int sX = x1;
						int sY = y1;
						already[y][x] = 0;
						/*can i move */
						//printf("sX: %d sY: %d\n", sX, sY);
						char mypath[1000];
						strcpy(mypath, "U");
						if (sY-1 >= 0)    {nextBEG(sX, sY-1, 1, 'U', sX, sY, mypath, x, y);}
						strcpy(mypath, "R");
						if (sX+1 <= MAXX) {nextBEG(sX+1, sY, 1, 'R', sX, sY, mypath, x, y);}
						strcpy(mypath, "D");
						if (sY+1 <= MAXY) {nextBEG(sX, sY+1, 1, 'D', sX, sY, mypath, x, y);}
						strcpy(mypath, "L");
						if (sX-1 >= 0)    {nextBEG(sX-1, sY, 1, 'L', sX, sY, mypath, x, y);}
					}
				}

				printf("savesBEGPos is %d\n", savesBEGPos);getchar();
				for (int z =0; z < savesBEGPos; z++) {
					for (int y5 = 0; y5 <= MAXY; y5++) {
						for (int x5 = 0; x5 <= MAXX; x5++) {
							grid[y5][x5] = gridOrig[y5][x5];
						}
					}
						
					printf("z is %d\n", z);
					int myX = x; int myY = y;
					int prevx2 = x; int prevy2 = y;

					printf ("looking @ PATH: [%s]\n", savesBEG[z]); getchar(); 
					for (int q = 0; q < (int)strlen(savesBEG[z]); q++) {
						
						printf ("looking @: %c\n", savesBEG[z][q]); 
						switch (savesBEG[z][q]) {
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
						
						printf("myX: %d myY: %d\n", myX, myY); getchar();
						printf("prevx2: %d prevy2: %d\n", prevx2, prevy2); getchar();
						if (grid[myY][myX].avail >= grid[prevy2][prevx2].used && q != (int)strlen(savesBEG[z])-1) {
							grid[myY][myX].avail -= grid[prevy2][prevx2].used;
							grid[myY][myX].used += grid[prevy2][prevx2].used;
							grid[prevy2][prevx2].avail = grid[prevy2][prevx2].used;
							grid[prevy2][prevx2].used = 0;

							int x4 = myX; int y4 = myY;
							int prevx3 = prevx; int prevy3 = prevy;
							printf("start of:. found a way -- retracing\n");
							///stop here ///move and retrace
							for (int r = q-1; r>=0; r--) {
								printf("in here...\n");
								prevy3 = y4; prevx3 = x4;
								switch (savesBEG[z][r]) {
									case 'U':
										y4++;
										break;
									case 'R':
										x4--;
										break;
									case 'D':
										y4--;
										break;
									case 'L':
										x4++;
										break;
								}
								grid[y4][x4].avail -= grid[prevy3][prevx3].used;
								grid[y4][x4].used += grid[prevy3][prevx3].used;
								grid[prevy3][prevx3].avail = grid[prevy3][prevx3].used;
								grid[prevy3][prevx3].used = 0;
							}
							for (int y6 = 0; y6 <= MAXY; y6++) {
								for (int x6 = 0; x6 <= MAXX; x6++) {
									printf(" %d/%d", grid[y6][x6].used, grid[y6][x6].size);
								}
								printf("\n");
							}
							printf("\n"); getchar();
							break;
						}
						
					
					}
				}
			} else {
				printf("ok continueing...\n");
			}
		}
	}
	printf("tot3 is %ld\n", tot3); getchar(); getchar();

	printf("***tot1 %ld \n", tot1); fflush(stdout);
	printf("***tot %ld \n", tot); fflush(stdout);
	printf("mymax: %d\n", mymax);
	printf("ENd...\n");
} 

void savepathBEG(char path[1000]) {
	int found = 0;
	for (int i = 0; i < savesBEGPos; i++) {
		if (strcmp(savesBEG[i], path) == 0) {
			found = 1; break;
		}
	}
	if (found == 0) {
		strcpy(savesBEG[savesBEGPos], path); savesBEGPos++;
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


void nextBEG(int x, int y, int steps, char DIR, int frX, int frY, char path[1000], int STX, int STY) {
	
	if (x == 0 && y==2) {return;}
	if (x == STX && y == STY) {/*printf("BEGreached end steps %d, %s [%ld]\n", steps, path, tot1); */tot1++; 
		savepathBEG(path); return;}

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

