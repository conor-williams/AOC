#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <map>
#include <unistd.h>

using namespace std;

int leny;
int printit();
int printitOrig();
struct brick {
	int IfromX;
	int IfromY;
	int IfromZ;
	int ItoX;
	int ItoY;
	int ItoZ;
/////////////
	char fromX[10];
	char fromY[10];
	char toX[10];
	char toY[10];
};
#define getchar()
#define mX  40
#define mY  40
#define mZ  1300
int wall[mZ][mY][mX];
int wallOrig[mZ][mY][mX];
struct brick bricks[mZ];
int maxX = 0, maxY=0, maxZ=0;
int main (int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	printf("SLOW ~1hour\n");
        FILE * a = fopen(argv[1], "r"); printf("2023 Day22.2\n"); fflush(stdout);
	int fd = dup(1); close(1);
        char line1[1000];
	leny = 0;
	for (int x=0; x<=mX; x++) { for (int y=0; y<=mY; y++) { for (int z=0; z<=mZ; z++) {
				wall[z][y][x] = 0;
				wallOrig[z][y][x] = 0;
			} } }
        while (1) {
		fgets(line1, 999, a); if (feof(a)) {break;}
		line1[strlen(line1) -1] = '\0';
		printf("line1 %s -- ", line1); 
		sscanf(line1, "%[^,],%[^,],%d~%[^,],%[^,],%d", bricks[leny].fromX, bricks[leny].fromY, &bricks[leny].IfromZ, bricks[leny].toX, bricks[leny].toY, &bricks[leny].ItoZ); 
		bricks[leny].IfromX = atoi(bricks[leny].fromX);	
		bricks[leny].IfromY = atoi(bricks[leny].fromY);	
		bricks[leny].ItoX = atoi(bricks[leny].toX);	
		bricks[leny].ItoY = atoi(bricks[leny].toY);	
		printf("Brick[%d] = [%d],[%d],[%d] -> [%d],[%d],[%d]  \n", leny,
			bricks[leny].IfromX, bricks[leny].IfromY, bricks[leny].IfromZ,
			bricks[leny].ItoX, bricks[leny].ItoY, bricks[leny].ItoZ);
		//printf("     getchar\n"); getchar();
		leny++;
	} //while
	fclose(a);

	printf("\n-----------------------------------\n");	
	for (int i = 0; i < leny; i++) {
		if (bricks[i].ItoZ > maxZ) {maxZ = bricks[i].ItoZ;}
		if (bricks[i].IfromZ > maxZ) {maxZ = bricks[i].IfromZ;}
	}
	for (int i = 0; i < leny; i++) {
		if (bricks[i].ItoY > maxY) {maxY = bricks[i].ItoY;}
		if (bricks[i].IfromY > maxY) {maxY = bricks[i].IfromY;}
	}
	for (int i = 0; i < leny; i++) {
		if (bricks[i].ItoX > maxX) {maxX = bricks[i].ItoX;}
		if (bricks[i].IfromX > maxX) {maxX = bricks[i].IfromX;}
	}
	printf("\nmaxX,Y,Z: %d %d %d\n", maxX, maxY, maxZ); //getchar();
	printf("\n-----------------------------------\n");	

	int maxBrickNum = 0;
	for (int i = 0; i < leny; i++) {
		if (bricks[i].ItoX < bricks[i].IfromX) {printf("ERRORX getchar\n"); getchar();}
		for (int x = bricks[i].IfromX; x <= bricks[i].ItoX; x++) {
			if (bricks[i].ItoY < bricks[i].IfromY) {printf("ERRORY getchar\n"); getchar();}
			for (int y = bricks[i].IfromY; y <= bricks[i].ItoY; y++) {
				if (bricks[i].ItoZ < bricks[i].IfromZ) {printf("ERRORZ getchar\n"); getchar();}
				for (int z = bricks[i].IfromZ; z <= bricks[i].ItoZ; z++) {
					wall[z][y][x] = i+1;
					maxBrickNum = i+1;
				}
			}
		}
	}
	//printit(); 
	printf("maxbricknum is %d\n", maxBrickNum);
/////////////////////////after Q it//////////////
for (int q = 0; q < 1000; q++) {
	int bT[mZ]; int bTi;
//	printf("q is %d\n", q); getchar();
	for (int z = 2; z <= maxZ; z++) {
		bTi = 0;
		for (int y = 0; y <= maxY; y++) {
			for (int x = 0; x <= maxX; x++) {
				if (wall[z][y][x] != 0) {
					int end = bTi;
					int found = 0;
					for (int r = 0; r < end; r++) {
						if (bT[r] == wall[z][y][x]) {
							found = 1;
							break;
						}
					}
					if (found == 0) {
						bT[bTi] = wall[z][y][x];
						bTi++;
					}
				}
			}
		}

	   int once = 0;
	   for (int k = 0; k < bTi; k++) {
		int dealoff = 0;
		for (int y = 0; y <= maxY; y++) {
			for (int x = 0; x <= maxX; x++) {
				if (wall[z][y][x] == bT[k] && wall[z-1][y][x] != 0) {
					dealoff = 1;		
					goto out11;
				}
			}
		}

		out11:
		if (dealoff == 0) {
			once++;	
			printf("dropping.br.[%d]. z -> z-1: [%d] -> [%d]\n", bT[k], z, z-1); 
			for (int y = 0; y <= maxY; y++) {
				for (int x = 0; x <= maxX; x++) {
					if (wall[z][y][x] == bT[k]) {
						wall[z-1][y][x] = wall[z][y][x];
						wall[z][y][x] = 0;
					}	
				}
			}
		}
			
	    }
/*
	    if (once) {
		z = z-2;
		if (z < 2) {z = 2;}
	    }
*/
	}
}

	for (int z = maxZ; z >= 3 ; z--) {
		int allzeroes = 0;
		for (int y = 0; y <= maxY; y++) {
			for (int x = 0; x <= maxX; x++) {
				if (wall[z][y][x] != 0) {
					allzeroes = 1;	
					goto out5;
				}
			}

		}

		out5:
		if (allzeroes == 0) {
			maxZ--;
		}

	}
	printit(); 
         
	for (int z = 0; z <= maxZ; z++) {
		for (int y = 0; y <= maxY; y++) {
			for (int x = 0; x <= maxX; x++) {
				wallOrig[z][y][x] = wall[z][y][x];
			}
		}
	}
	//printitOrig(); 

	int dropped = 0;
//////////////////////////
	map <int, int> mp;
	printf("maxZ maxY maxX %d %d %d\n", maxZ, maxY, maxX); 
	for (int bN = 1; bN < leny+1; bN++) { 
printf("entering loop... bN %d\n", bN);
		int foundAtLastZ1 = 0;
		int first = 1; int zFIR = 1;
/////////////
		for (int z = 1; z <= maxZ; z++) {
			for (int y = 0; y <= maxY; y++) {
				for (int x = 0; x <= maxX; x++) {
					wall[z][y][x] = wallOrig[z][y][x];
				}
			}
		}
		for (int y = 0; y <= maxY; y++) {
			for (int x = 0; x <= maxX; x++) {
				wall[0][y][x] = -1;
			}
		}
		int changed = 0;
		for (int z = 1; z <= maxZ; z++) {
			for (int y = 0; y <= maxY; y++) {
				for (int x = 0; x <= maxX; x++) {
					if (wall[z][y][x] == bN) {
						changed = 1;
						wall[z][y][x] = 0;
						foundAtLastZ1 = z;
						if (first==1) {first++; zFIR = z;}
					}
				}
			}
			if (foundAtLastZ1 != 0 && foundAtLastZ1 < z) {break;}
		}
		if (changed == 0) {printf("ERROR changed brick %d\n", bN); getchar();}

///////////////
           mp.clear();
printf("entering second loop..\n");
	   for (int bN2 = 1; bN2 < leny+1; bN2++) { 
		if (bN == bN2) {continue;}
		if (mp.find(bN2) != mp.end()) {continue;} 
		int dealoff = 0;
		int found = 0;
		int foundAtLastZ = 0;
		
		for (int z = 1; z <= maxZ; z++) {
			for (int y = 0; y <= maxY; y++) {
				for (int x = 0; x <= maxX; x++) {
					if (wall[z][y][x] == bN2) {foundAtLastZ=z; found = 1;}
					if (wall[z][y][x] == bN2 && wall[z-1][y][x] != 0) {
					        if (wall[z-1][y][x] != bN2) {
							dealoff = 1;
							goto out10;
						} 
					} 
				}
			}
			if (foundAtLastZ != 0 && foundAtLastZ < z) {break;}
	        }

		out10:
		if (dealoff == 0 && found == 1) {
			dropped++;
			//printf(" dropped: %d \n", dropped);
			int foundAtLastZ2 = 0;
			mp.insert({bN2, 1});
			for (int z1 = 1; z1 <= maxZ; z1++) {
				for (int y1 = 0; y1 <= maxY; y1++) {
					for (int x1 = 0; x1 <= maxX; x1++) {
						if (wall[z1][y1][x1] == bN2) {
							wall[z1][y1][x1] = 0;
							foundAtLastZ2=z1;
						}
					}
				}
				if (foundAtLastZ2 != 0 && foundAtLastZ2 < z1) {bN2 = 0; break;}
			}
			bN2 = 0;
		}
           }
      }

/////////////////



//////////////////////////

	printf("leny is %d\n", leny);
	printf("*** dropped: %d\n", dropped);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", dropped);
}

int printitOrig() {
	printf("Z X Orig\n");
	for (int z=maxZ; z >= 0; z--) {
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][0][x]);
		}
		printf("        ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][1][x]);
		}
		printf("  ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][2][x]);
		}
		printf("  ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][3][x]);
		}
		printf("  ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][4][x]);
		}
		printf("  ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][5][x]);
		}
		printf("  ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][6][x]);
		}
		printf("  ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][7][x]);
		}
		printf("  ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wallOrig[z][8][x]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Z Y Orig\n");
	for (int z = maxZ; z>= 0; z--) {
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][0]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][1]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][2]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][3]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][4]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][5]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][6]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][7]);
		}
		printf("  ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wallOrig[z][y][8]);
		}
		printf("\n");
	}
	printf("\n");

	return 1;
}
int printit() {
	printf("Z X Orig\n");
	for (int z=maxZ; z >= 0; z--) {
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][0][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][1][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][2][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][3][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][4][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][5][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][6][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][7][x]);
		}
		printf("      ");
		for (int x = 0; x <= maxX; x++) {
			printf("[%4d]", wall[z][8][x]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Z Y Orig\n");
	for (int z = maxZ; z>= 0; z--) {
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][0]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][1]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][2]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][3]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][4]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][5]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][6]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][7]);
		}
		printf("      ");
		for (int y = 0; y <= maxY; y++) {
			printf("[%4d]", wall[z][y][8]);
		}
		printf("\n");
	}
	printf("\n");

	return 1;
}
