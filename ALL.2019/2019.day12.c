#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2019 day12 part1\n"
#undef _DEBUG_
#define MAX 50

struct pos_s {
	int x;
	int y;
	int z;
	int vx;
	int vy;
	int vz;
	int pe;
	int ke;

};
struct pos_s pos[10];

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[MAX] = {0};
while(1) {
        fgets(line1, MAX -1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	printf("LINE: %s getchar\n", line1); getchar();
	sscanf(line1, "<x=%d, y=%d, z=%d", &pos[leny].x, &pos[leny].y, &pos[leny].z);
	leny++;
}
fclose(a);

	int totProper;
	for (int t = 1; t <= 1000; t++) {
		for (int i = 0; i < leny; i++) {
			for (int j = 0; j < leny; j++) {
				if (i == j) {continue;}
				if (pos[i].x > pos[j].x) {
					pos[i].vx--;
				} else if (pos[i].x < pos[j].x) {
					pos[i].vx++;
				}
	
				if (pos[i].y > pos[j].y) {
					pos[i].vy--;
				} else if (pos[i].y < pos[j].y) {
					pos[i].vy++;
				}

				if (pos[i].z > pos[j].z) {
					pos[i].vz--;
				} else if (pos[i].z < pos[j].z) {
					pos[i].vz++;
				}
			}
		}
		for (int i = 0; i < leny; i++) {
			pos[i].x += pos[i].vx;
			pos[i].y += pos[i].vy;
			pos[i].z += pos[i].vz;
		}
		
		for (int i = 0; i < leny; i++) {
			pos[i].pe = abs(pos[i].x) + abs(pos[i].y) + abs(pos[i].z);
			pos[i].ke = abs(pos[i].vx) + abs(pos[i].vy) + abs(pos[i].vz);
		}
		
		printf("After %d steps:\n", t);
		int tot = 0;
		for (int i = 0; i < leny; i++) {
			printf("pos= %3d %3d %3d -- vel: %3d %3d %3d pe:%3d ke:%3d\n", pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz, pos[i].pe, pos[i].ke);
			tot += pos[i].pe * pos[i].ke;
		}


		printf("*inter tot is %d\n", tot);
		totProper = tot;
		//getchar();
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", totProper);
}
