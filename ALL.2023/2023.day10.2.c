#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
char pipes[300][300];
char pipesPATH[300][300];
long tot = 0;
int X, Y;
int chright(const char *forwhat);
int chleft(const char *forwhat);
int chtop(const char *forwhat);
int chbtm(const char *forwhat);
void printmaze();
int leny = 0;
int lenx = 0;
void floodfill(int x, int y);
int main(int argc, char **argv)
{
	//int r = 0;
	//char starts[100][5];
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2023 Day10.2\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	while(1) {
		fgets(line1, 1000, a);
		if (feof(a)) break;
		strcpy(pipes[leny], line1);
		strcpy(pipesPATH[leny], line1);

		leny++;
	}
	lenx = (int)strlen(pipes[leny-1]);
	printf("lenx %d - leny %d\n", lenx, leny);
	fclose(a);
	int startx, starty;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < leny; x++) {
			if (pipes[y][x] == 'S') {startx = x; starty = y; break;} 
		}
	}
	printf("Start at %d, %d\n", startx, starty);

	for (int  k = 0; k < 10; k++) {
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				X=x; Y=y;
				switch(pipes[y][x]) {
					case 'S': {break;}
					case '.': {pipes[y][x] = 'B'; break;}
					case '|': {if (chbtm   ("LJS|") && chtop   ("|7FS"))   break; pipes[y][x] = 'B'; break;}
					case '-': {if (chleft  ("-FLS") && chright ("-J7S"))   break; pipes[y][x] = 'B'; break;}
					case 'L': {if (chtop   ("|7FS") && chright ("-J7S"))   break; pipes[y][x] = 'B'; break;}
					case 'J': {if (chleft  ("-FLS") && chtop   ("|7FS"))   break; pipes[y][x] = 'B'; break;}
					case '7': {if (chleft  ("-FLS") && chbtm   ("|JLS"))   break; pipes[y][x] = 'B'; break;}
					case 'F': {if (chright ("-7JS") && chbtm   ("|LJS"))   break; pipes[y][x] = 'B'; break;}
				}
			}
		}    
	}
	printf("\nN: %c\n", pipes[starty-1][startx]);
	printf("S: %c\n", pipes[starty+1][startx]);
	printf("E: %c\n", pipes[starty][startx+1]);
	printf("W: %c\n", pipes[starty][startx-1]);

	//startx starty
	int moves = 0;
	int nx1, ny1, nx2, ny2;
	int fin = 0;
	{
		// go east  by moving x...
		int prevx = startx; int prevy = starty;
		int x = startx +1; int y = starty;
		while (1) {
			switch(pipes[y][x]) {
				case 'S': {pipesPATH[y][x] = 'Q'; fin = 1; printf("back home... or starting...");getchar(); break;}
				case '.': {fin = 1; printf("broke.."); getchar(); break;}
				case '|': {pipesPATH[y][x] = 'Q'; nx1 = x;   ny1 = y-1; nx2 = x; ny2 = y+1; break;}
				case '-': {pipesPATH[y][x] = 'Q'; nx1 = x-1; ny1 = y  ; nx2 = x+1; ny2 = y; break;}
				case 'L': {pipesPATH[y][x] = 'Q'; nx1 = x+1; ny1 = y  ; nx2 = x; ny2 = y-1; break;}
				case 'J': {pipesPATH[y][x] = 'Q'; nx1 = x-1; ny1 = y  ; nx2 = x; ny2 = y-1; break;}
				case '7': {pipesPATH[y][x] = 'Q'; nx1 = x;   ny1 = y+1; nx2 = x-1; ny2 = y; break;}
				case 'F': {pipesPATH[y][x] = 'Q'; nx1 = x+1; ny1 = y  ; nx2 = x; ny2 = y+1; break;}
			}

			if (prevx == nx1 && prevy == ny1) {
				prevx = x; prevy = y;
				x=nx2; y=ny2;
			} else {
				prevx = x; prevy = y; x = nx1; y = ny1;
			}

			moves++;
			if (fin == 1) break;
		}
		printf("****moves/2 %d\n", moves/2);
		//part1: printf("**ans: %d\n", moves/2);
	}
	//floodfill
	printmaze();

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (x == 0 && pipes[y][x] == 'B') {
				floodfill(x, y);
			}
		}
	}
	printmaze();
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (pipesPATH[y][x] != 'Q') {
				pipes[y][x] = 'B';
			}
		}
	}

	int count = 0;
	for (int y = 0; y < leny; y++) {
		int outside = 1;
		char prev;
		printf("%s\n", pipes[y]);
		prev = pipes[y][0];
		for (int x = 0; x < lenx; x++) {
			//prev = pipes[y][x];
			switch (pipes[y][x]) {
				case 'S': {
					  printf("found S\n"); printf("%s\n", pipes[y]); getchar();break;}
				//case '.': {if (outside == 0) {count++;}break;}
				case '|': {outside = outside==1?0:1; prev='|';break;}
				case '-': {break;}
				case 'L': {
					prev='L';
					break;}
				case 'J': {
					if (prev == 'F') {outside = outside==1?0:1;}
					prev='J';
					break;}
				case '7': {
					if (prev == 'L') {outside = outside==1?0:1;}
					prev='7';
					break;}
				case 'F': {
					prev = 'F';
					break;}
				case 'B': {if (outside == 0) {count++;pipes[y][x] = 'I'; break;}}
				//case 'Z': {if (outside == 0) {count++;break;}}
			}
		}
	}


	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);

}
void floodfill(int x, int y) {
	if (x >= 0 && x < lenx && y >=0 && y < leny) {
		//ok
	} else {return;}
	if (pipes[y][x] == 'B') {
		pipes[y][x] = 'Z';
		floodfill(x, y-1);
		floodfill(x+1, y);
		floodfill(x, y+1);
		floodfill(x-1, y);
	}
}
void printmaze() 
{
	for (int y = 0; y < 20/*leny*/; y++)
	{
		printf("%s", pipes[y]);
	}
}
int chright(const char *forwhat)
{
	int found=0;
	for (int i = 0; i< (int)strlen(forwhat); i++) {
		if (pipes[Y][X+1] == forwhat[i]) {
			found = 1; break;
		}
	}
	return found;

}
int chleft(const char *forwhat)
{
	int found=0;
	for (int i = 0; i< (int)strlen(forwhat); i++) {
		if (pipes[Y][X-1] == forwhat[i]) {
			found = 1; break;
		}
	}
	return found;
}

int chtop(const char *forwhat)
{
	int found=0;
	for (int i = 0; i< (int)strlen(forwhat); i++) {
		if (pipes[Y-1][X] == forwhat[i]) {
			found = 1; break;
		}
	}
	return found;
}
int chbtm(const char *forwhat)
{
	int found=0;
	for (int i = 0; i< (int)strlen(forwhat); i++) {
		if (pipes[Y+1][X] == forwhat[i]) {
			found = 1; break;
		}
	}
	return found;
}
