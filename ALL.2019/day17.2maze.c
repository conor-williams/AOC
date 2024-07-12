#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

int lenx, leny;
#define DAY "2019 day2 part1\n"
#undef _DEBUG_

char grid[100][100];
int x = 0;
int y = 0;
int dir;
int applya();
int applyb();
int applyc();
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	char line1[300];
	while(1) {

		fgets(line1, 299, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s getchar\n", line1); getchar();
#endif
		strcpy(grid[leny], line1);

	}
	fclose(a);

	lenx = (int)strlen(grid[0]);

again:
	srand(time(NULL));
	int a1 = rand() %20;
	int b1 = rand() %20;
	int c1 = rand() %20;

	for (int am = 1; am < 200; am++) {
		x = 0; y = 0; dir = 1;
		if (applya() == 99) {continue;}
		for (int bm = 0; bm <200; bm++) {
			if (applyb() == 99) {continue;}
			for (int cm = 0; cm < 200; cm++) {
				if (applyc() == 99) {continue;}	
				printf("x,y is now %d,%d\n", x, y);
				if (x == 60 && y == 9) {
					printf("wahoo... am,bm,cm %d,%d,%d\n", am,bm,cm); getchar();
				}
			}
		}
	}
	//goto again;

}

int applya() {
	//--L:10 R:8 R:8 R:12 L:8
	if (dir == 0) {
		x-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 1;
	} else if (dir == 1) {
		y-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 1;
		x+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 1;
		y+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 1;
		x-=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 1;
		y+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 2;
	} else if (dir == 2) {
		x+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 3;
	} else if (dir == 3){
		y+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 0;
	}

}

int applyb() {
	//--L:10 R:6
	if (dir == 0) {
		x-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 0;
	} else if (dir == 1) {
		y-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 1;
	} else if (dir == 2) {
		x+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 2;
	} else if (dir == 3) {
		y+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		dir = 3;
	}
}
int applyc() {
	//C==                 -- S:2 R:6 L:10 R:12 L:8 L:10 R:12

	if (dir == 0) {
		y-=2;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}

		dir = 0;

	} else if (dir == 1) {
		x+=2;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}

		dir = 1;

	} else if (dir == 2) {
		y+=2;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}

		dir = 2;

	} else if (dir == 3) {
		x-=2;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=6;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y-=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=8;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		y+=10;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
		x-=12;
		if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}

		dir = 3;

	}

}
