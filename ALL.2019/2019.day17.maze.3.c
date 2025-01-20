#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <algorithm>

using namespace std;

int lenx, leny;
#define DAY "2019 day2 part1\n"
#undef _DEBUG_
#define getchar()

char grid[100][100];
int x = 0;
int y = 0;
int dir;
int applya(int);
int applyb(int);
int applyc(int);
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
		leny++;

	}
	fclose(a);

	lenx = (int)strlen(grid[0]);

	//again:
	srand(time(NULL));
	//int a1 = rand() %20; int b1 = rand() %20; int c1 = rand() %20;

	int xb; int yb; int dirb;
	int xa; int ya; int dira;

	x = 0; y = 0; dir = 1;
	
/*
	for (int cm = 0; cm < 50; cm++) {
		x = 0; y = 0; dir = 1;
		myints[cm] == 3;
		if (applyc(cm) == 99) {continue;}
		xb = x; yb = y; dirb = dir;
		printf("here2\n");
		for (int bm = 0; bm <50; bm++) {
			x = xb; y = yb; dir = dirb;
			if (applyb(bm) == 99) {continue;}
			xa = x; ya = y; dira = dir;
			for (int am = 0; am < 50; am++) {
				x = xa; y = ya; dir = dira;
				if (applya(cm) == 99) {continue;}
				
				if ((x == 60 && y == 9)) {
	//			if ((x == 54 && y == 9) || (x == 66 && y == 9) ||(x == 60 && y == 3) || (x == 60 && y == 15) ) {
					printf("wahoo... am,bm,cm %d,%d,%d\n", am,bm,cm); getchar();
				}
			}
		}
	}
*/


	int qs[200];

	int destX = 58; int destY = 12;
	for (int vend = 1; vend < 200; vend++) {
		for (int end2 = 0; end2 <= vend; end2++) {
			for (int i = 0; i < end2; i++) {
				qs[i] = 3;
			}
			for (int end = end2; end <= vend ; end++) {
				for (int i = end2; i < end; i++) {
					qs[i] = 2;
				}
				for (int i = end; i <= vend; i++) {
					qs[i] = 1;
				}
				//printf("qs: \n"); for (int i = 0; i < vend; i++) { printf("%d ", qs[i]); } printf("\n");
				sort(qs, qs+vend);
				//printf("qs[vend-1] is %d\n", qs[vend-1]);
				char ans[100];
				do {
						strcpy(ans, "");
						x = 60; y = 18; dir = 3; int b = 0;
						
						for (int i = 0; i < vend; i++) {
							if (qs[i] == 3) {
								snprintf(ans, 50, "%s%c", ans, 'C');
								//printf("C"); fflush(stdout);
								if (applyc(1) == 99) {b=1; break;}
								if ((x == destX && y == destY)) {
									printf("wahey [[ %s ]]\n", ans); getchar();
								}
							} else if (qs[i] == 2) {
								snprintf(ans, 50, "%s%c", ans, 'B');
								//printf("B"); fflush(stdout);
								if (applyb(1) == 99) {b=1;break;}
								if ((x == destX && y == destY)) {
									printf("wahey %s\n", ans); getchar();
								}
							} else if (qs[i] == 1) {
								snprintf(ans, 50, "%s%c", ans, 'A');
								//printf("A"); fflush(stdout);
								if (applya(1) == 99) {b=1; break;}
								if ((x == destX && y == destY)) {
									printf("wahey == %s\n", ans); getchar();
								}
							}
		
						}
						//if (b == 1) {printf("\n");} else {printf("\n");}
						if ((x == destX && y == destY)) {
							//printf("wahey %s\n", ans); getchar();
						}
				} while (next_permutation(qs, qs+vend));
			}
		}
	}
	//goto again;

}

int applya(int ti) {
	// R:6 L:10 R:8 R:8
	for (int i = 0; i < ti; i++) {
		if (dir == 0) {
			x+=6;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y-=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x+=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y+=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 2;
		} else if (dir == 1) {
			y+=6;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x+=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y+=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x-=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 3;
		} else if (dir == 2) {
			x-=6;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y+=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x-=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y-=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 0;
		} else if (dir == 3){
			y-=6;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x-=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y-=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x+=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 1;
		}
	}

	return 0;
}

int applyb(int ti) {
	//--L:10 R:6
	// L:10
	for (int i = 0; i < ti; i++) {
		if (dir == 0) {
			x-=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 3;
		} else if (dir == 1) {
			y-=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 0;
		} else if (dir == 2) {
			x+=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 1;
		} else if (dir == 3) {
			y+=10;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 2;
		}
	}
	return 0;
}
int applyc(int ti) {
	//C==                 -- R:12 L:8

	for (int i = 0; i < ti; i++) {
		if (dir == 0) {
			x+=12;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y-=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 0;

		} else if (dir == 1) {
			y+=12;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x+=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 1;

		} else if (dir == 2) {
			x-=12;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			y+=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 2;
		} else if (dir == 3) {
			y-=12;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			x-=8;
			if (x<0 || x > lenx || y< 0 || y>leny) {return 99;}
			dir = 3;

		}
	}
	return 0;

}


int applya1(int ti) {
	//--L:10 R:8 R:8 R:12 L:8
	for (int i = 0; i < ti; i++) {
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
	//--L:10 R:8 R:8 R:12 L:8
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

	return 0;
}

int applyb1(int ti) {
	//--L:10 R:6
	for (int i = 0; i < ti; i++) {
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
	return 0;
}
int applyc1(int ti) {
	//C==                 -- S:2 R:6 L:10 R:12 L:8 L:10 R:12

	for (int i = 0; i < ti; i++) {
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
	//C==                 -- S:2 R:6 L:10 R:12 L:8 L:10 R:12
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
	return 0;

}

