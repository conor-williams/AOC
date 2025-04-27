#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#undef _DEBUG_
#define SIZE 400
char line1[SIZE];
unsigned long tot = 0;

struct point_s {
	int x;
	int y;
	int z;
	int w;
	int done;
};
struct point_s point[1300];
struct point_s group[1000][1300];
int groupPos[1000] = {0};
int leny = 0;
void groupit(int grp);
#define getchar()
int main(int argc, char **argv)
{
	///printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day25.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		sscanf(line1, "%d,%d,%d,%d", &point[leny].x, &point[leny].y, &point[leny].z, &point[leny].w);
		leny++;
		
	}
	fclose(a);
	for (int i = 0; i < leny; i++) {
		printf("%d -- %d -- %d -- %d\n", point[i].x, point[i].y, point[i].z, point[i].w);
	}

	int grp1 = 0;
	int count;
	do {
		groupit(grp1); grp1++;
		printf("after groupit"); fflush(stdout);
		count = 0;
		for (int i = 0; i < leny; i++) {
			if (point[i].done == -1) {
				count++;
			}
		}
		printf("groupPos[%d]: %d\n", grp1-1, groupPos[grp1-1]); getchar();
		printf("groups: %d\n", grp1); getchar();
		for (int i = 0; i < groupPos[grp1-1]; i++) {
			printf("%d -- %d -- %d -- %d --- %d\n", group[grp1-1][i].x, group[grp1-1][i].y, group[grp1-1][i].z, group[grp1-1][i].w, group[grp1-1][i].done);
		}
		printf("----------\n");
	} while (count != leny); 
	

	printf("**tot %lu\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("ans: %d\n", grp1);
}

void groupit(int grp) {
	int nex = -1;
	for (int i = 0; i < leny; i++) {
		if (point[i].done != -1) {
			nex = i; break;
		}
	}
	if (nex ==  -1) {printf("ERR\n");exit(0);}
	group[grp][0].x = point[nex].x;
	group[grp][0].y = point[nex].y;
	group[grp][0].z = point[nex].z;
	group[grp][0].w = point[nex].w;
	group[grp][0].done = -1;
	point[nex].done = -1;
	groupPos[grp]++;
	printf("%d -- %d -- %d -- %d --- %d\n", point[nex].x, point[nex].y, point[nex].z, point[nex].w, point[nex].done);
again:
	for (int i = 0; i < leny; i++) {
		if (nex == i) {continue;}
		if (point[i].done == -1) {continue;}
		for (int j = 0; j < groupPos[grp]; j++) {
			if (abs(group[grp][j].x - point[i].x) + abs(group[grp][j].y - point[i].y) +
				abs(group[grp][j].z - point[i].z) +
				abs(group[grp][j].w - point[i].w) <= 3 && (point[i].done != -1)) 
			{

				printf("**adding %d\n", point[i].x); getchar();
				group[grp][groupPos[grp]] = point[i]; point[i].done = -1;
				groupPos[grp]++;
				goto again;
			}
		}
	}
}
