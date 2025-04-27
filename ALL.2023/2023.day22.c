#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define getchar()

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
struct brick bricks[1300];
int wall[299][10][10];
int wallOrig[299][10][10];
int maxX = 0, maxY=0, maxZ=0;

int main (int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("		2023 Day22 Part 1\n"); fflush(stdin); fflush(stdout);
	int fd = dup(1); close(1);
        char line1[1000];
	leny = 0;
	for (int x=0; x<=9; x++) { for (int y=0; y<= 9; y++) { for (int z=0; z<=298; z++) {
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
	printf("\nmaxX,Y,Z: %d %d %d\n", maxX, maxY, maxZ); getchar();
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
	printit(); 
	printf("maxbricknum is %d\n", maxBrickNum);
/////////////////////////after Q it//////////////
for (int q = 0; q < 500; q++) {
	int bT[2000]; int bTi;
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
					goto out9;
				}
			}
		}

		out9:
		if (dealoff == 0) {
			once++;	
			//printf("dropping... z -> z-1: [%d] -> [%d]\n", z, z-1); 
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
	    if (once) {
		z = z-2;
		if (z < 2) {z = 2;}
	    }
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
	printf("maxZ is now %d\n", maxZ);  getchar();
	printit(); 
         
	for (int z = 0; z <= maxZ; z++) {
		for (int y = 0; y <= maxY; y++) {
			for (int x = 0; x <= maxX; x++) {
				wallOrig[z][y][x] = wall[z][y][x];
			}
		}
	}
	printitOrig(); 

	int disintegrate = 0;
	int integ = 0;
//////////////////////////
	for (int bN = 1; bN < leny+1; bN++) { 
/////////////
		//printf("brick %d\n", bN);  
		for (int z = 0; z <= maxZ; z++) {
			for (int y = 0; y <= maxY; y++) {
				for (int x = 0; x <= maxX; x++) {
					wall[z][y][x] = wallOrig[z][y][x];
				}
			}
		}
		int changed = 0;
		for (int z = 0; z <= maxZ; z++) {
			for (int y = 0; y <= maxY; y++) {
				for (int x = 0; x <= maxX; x++) {
					if (wall[z][y][x] == bN) {
						changed = 1;
						wall[z][y][x] = 0;
					}
				}
			}
		}
		if (changed == 0) {printf("ERROR changed brick %d\n", bN); getchar();}

///////////////
	for (int z = 2; z <= maxZ; z++) {
		int bTi = 0; int bT[1000];
		for (int y = 0; y <= maxY; y++) {
			for (int x = 0; x <= maxX; x++) {
				//for all brick types
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

	   for (int k = 0; k < bTi; k++) {
		int first = 1;
	   	int breakout = 0;
		int dealoff = 0;
			for (int y = 0; y <= maxY; y++) {
				for (int x = 0; x <= maxX; x++) {
					if (wall[z][y][x] == bT[k] && wall[z-1][y][x] != 0) {
						dealoff = 1;		
						goto out10;
					}
				}
			}

		out10:
		if (dealoff == 0) {
				//printf("could drop... z -> z-1: [%d] -> [%d]\n", z, z-1); 
				if (first == 1) { first++; disintegrate++; }
				break;
		} else {
			integ++;
		}
			
		if (breakout == 1) {break;}
	    }
	}
    }

/////////////////



//////////////////////////

	printf("leny is %d\n", leny);
	printf("DISINTEGRATE = %d integ %d (leny - %d) = %d\n", 
		disintegrate, integ, disintegrate, leny-disintegrate);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", leny-disintegrate);
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
