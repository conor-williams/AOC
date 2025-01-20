#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define LINE 100
#define GX 1400
char grid[GX][GX];
#define getchar()

struct along_s {
	int val;
	int x;
	int y;
};
struct along_s along[100];
int alongPos = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day13.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			grid[y][x] = '.';
		}
	}

int leny = 0;
int pos = 1;
while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
	if (line1[0] == '\0') {
		pos = 0; continue;
	} else if (pos == 1) {
		char *x1 = strtok(line1, ",\0");
		char *y1 = strtok(NULL, ",\0");
		if (atoi(y1) >= GX || atoi(x1) >= GX) {
			perror("OUT\n"); exit(0);
		}
		grid[atoi(y1)][atoi(x1)] = '#';
	} else if (pos == 0) {
		int v;
		int ret = sscanf(line1, "fold along y=%d\n", &v);
		if (ret != 1) {
			ret = sscanf(line1, "fold along x=%d\n", &v);
			printf("x fold %d\n", v);
			along[alongPos].val = v;
			along[alongPos].y = 0;
			along[alongPos].x = 1;
		} else {
			printf("y fold %d\n", v);
			along[alongPos].val = v;
			along[alongPos].y = 1;
			along[alongPos].x = 0;
		}
		if (alongPos > 99) {perror("along"); exit(0);}
		alongPos++;
	}

	leny++;
}
fclose(a);

	printf("after load...\n");
	int maxx = 0, maxy = 0;
	int count1 = 0;
	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			//printf("%c", grid[y][x]);
			if (grid[y][x] == '#') {
				count1++;
				if (y > maxy) {maxy = y;}
				if (x > maxx) {maxx = x;}
			}
		}
		//printf("\n");
	}

	//printf("\n");
	printf("count1 is %d\n", count1);
	printf("maxx: %d -- maxy: %d\n", maxx, maxy); getchar();

	for (int i = 0; i < alongPos; i++) {
		if (along[i].y == 1) {
			printf("yyyy -- %d V %d\n", along[i].val, maxy/2);
			assert(along[i].val == (maxy/2));
			for (int x = 0; x <= maxy; x++) {
				assert(grid[along[i].val][x] == '.');
			}
			
			int y2 = maxy; 
			for (int y1 = 0; y1 < along[i].val; y1++) {
				for (int x = 0; x <= maxx; x++) {
					if (grid[y2][x] == '#') {
						grid[y1][x] = '#';
					}
				}
				printf("%d V %d\n", y1, y2);
				y2--;
			}
			maxy = along[i].val - 1;
		} else if (along[i].x == 1) {
			{{{
					int count3 = 0;
					for (int x1 = 0; x1 < along[i].val; x1++) {
						for (int y = 0; y <= maxy; y++) {
							if (grid[y][x1] == '#') {
								count3++;
							}
						}
					}
			
					int x3 = along[i].val-1;
					for (int x1 = along[i].val+1; x1 <= maxx; x1++) {
						
						for (int y = 0; y <= maxy; y++) {
							if (grid[y][x1] == '#' && grid[y][x3] != '#') {
								count3++;
							}
						}
						x3--;
					}
					printf("count3 is %d\n", count3);
			}}}



			printf("xxxx -- %d V %d\n", along[i].val, maxx/2); getchar();
			assert(along[i].val == (maxx/2));
			for (int y = 0; y <= maxy; y++) {
				assert(grid[y][along[i].val] == '.');
			}
			int x2 = maxx;
			for (int x1 = 0; x1 < along[i].val; x1++) {
				for (int y = 0; y <= maxy; y++) {
					if (grid[y][x2] == '#') {
						grid[y][x1] = '#';
					}
				}
				printf("%d V %d\n", x1, x2);
				x2--;
			}
			maxx = along[i].val - 1;
		}
		int count = 0;
		for (int y = 0; y <= maxy; y++) {
			for (int x = 0; x <= maxx; x++) {
				if (grid[y][x] == '#') {
					count++;
				}
			}
		}
		printf("R: %d count: %d\n", i, count); getchar();

		fflush(stdout); dup2(fd, 1);
		printf("**ans: %d\n", count);
		exit(0);
					
	}
	for (int y = 0; y <= maxy; y++) {
		for (int x = 0; x <= maxx; x++) {
			if (grid[y][x] == '.') {
				printf(" ");
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
			
	
}
