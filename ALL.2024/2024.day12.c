#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
char grid[1000][1000];
char gridN[1002][1002];
struct count_s {
	int regions;
	int area[100];
	int perimeter[100];
};
struct count_s count[100];
int already[1000][1000];
int already2[1000][1000];
void flood(int x, int y, char wat);
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
	memset(already, 0, sizeof(already));
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2024 Day 12 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	strcpy(grid[leny], line1);
	leny++;
}
	lenx = strlen(grid[0]);
fclose(a);
	char tmp[1000];
	for (int i = 0; i < lenx; i++) {
		tmp[i] = '0';
	}
	tmp[lenx] = '0';
	sprintf(gridN[0], "0%s0", tmp);
	for (int y = 0; y < leny; y++) {
		sprintf(gridN[y+1], "0%s0\n", grid[y]);
	}
	sprintf(gridN[leny+2], "0%s0", tmp);
	leny += 2;
	lenx += 2;
	
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			char wat = gridN[y][x];
			if (already[y][x] == 0) {
				memset(already2, 0, sizeof(already2));
				flood(x, y, wat);
				count[wat-'A'].regions++;
				already[y][x] = 1;
			}
		 
		}
	}

	unsigned long long ans = 0;
	for (int i = 0; i < 26; i++) {
			int totArea = 0;
			for (int j = 0; j < count[i].regions; j++) {
				totArea += count[i].area[j];
			}
			for (int j = 0; j < count[i].regions; j++) {
				if (count[i].area[j] != 0) {
					printf("%c regions: %d area:%d per: %d (totArea: %d)\n", i+'A', count[i].regions, count[i].area[j], count[i].perimeter[j], totArea);
					ans += count[i].area[j] * count[i].perimeter[j];	
				}
			}

	}
	
	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", ans);
}

void flood(int x, int y, char wat) {
	if (y > leny-1 || x < 0 || y < 0 || x > lenx-1) {
		return;
	}
	if (already2[y][x] != 0) {return;} /*else {already2[y][x] = 1;}*/
	if (gridN[y][x] != wat) { count[wat - 'A'].perimeter[count[wat-'A'].regions]++; return; } else {
		already2[y][x] = 1;
		already[y][x] = 1;
		count[wat - 'A'].area[count[wat -'A'].regions]++;
	}
	
	flood(x, y+1, wat);
	flood(x+1, y, wat);
	flood(x, y-1, wat);
	flood(x-1, y, wat);
}




/*
			count[wat].area++;
			
			if (gridN[y-1][x] != wat) {count[wat-'A'].perimeter++;}
			if (gridN[y][x+1] != wat) {count[wat-'A'].perimeter++;}
			if (gridN[y+1][x] != wat) {count[wat-'A'].perimeter++;}
			if (gridN[y][x-1] != wat) {count[wat-'A'].perimeter++;}
			already[y][x] = 1;
*/

