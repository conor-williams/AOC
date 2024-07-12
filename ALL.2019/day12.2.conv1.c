#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <numeric>
#include <map>
#include <string>
#include <vector>


using namespace std;
int lenx, leny;
#define DAY "2019 day12 part2\n"
#undef _DEBUG_
#define MAX 50

int SV = 32000000;
//#define SV 3000
#define getchar()

struct pos_s {
	int x;
	int y;
	int z;
	int vx;
	int vy;
	int vz;

	map <tuple<int, int, int, int, int, int>, int> mp;

	vector <int> states;
	vector <int> matches;
	int first;
};
struct pos_s pos[4];
struct pos_s posOrig[4];

int main(int argc, char **argv)
{
	//if (argc < 3) {printf("give a size\n"); exit(0);} SV = atoi(argv[2]);
	lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);


	char line1[MAX] = "";
	char linePrev[MAX] = "";
	char prevNums[100];
	char nums[100] = "";
	int first = 0;
	int times = 0;
	while(1) {
		strcpy(prevNums, nums);
		strcpy(linePrev, line1);
		fgets(line1, MAX -1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
		//printf("LINE: %s getchar\n", line1); getchar();
		sscanf(line1, "%[^ ] ", nums);
		if (first == 1) {
			int same = strcmp(nums, prevNums);
			//printf("compare %s V %s \n", nums, prevNums);
			if (same == 0) {
				times++;
				printf("%s\n", linePrev);
			} else if (same != 0) {
				if (times == 0) {
					//dont print
				} else {
					printf("%s\n", linePrev);
				}
				times = 0;
			}
		} else if (first == 0) {
			//printf("%s\n", line1);
			first = 1;
		}
				
		leny++;
	}
	fclose(a);

	exit(0);
	for (int i = 0; i < leny; i++) {
		posOrig[i].x = pos[i].x;
		posOrig[i].y = pos[i].y;
		posOrig[i].z = pos[i].z;
		posOrig[i].vx = pos[i].vx;
		posOrig[i].vy = pos[i].vy;
		posOrig[i].vz = pos[i].vz;
	}
	for (int i = 0; i < leny; i++) {
		pos[i].first = 0;
	}
	FILE *b = fopen("out", "w");
	for (int i = 0; i < leny; i++) {
		char out1[1000];
		sprintf(out1, "%d,%d,%d,%d,%d,%d  %d pos:(%d)\n", pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz, 0, i);
		fputs(out1, b);
	}

	int t;
	for (t = 1; t < SV; t++) {
		//if (t % 1000000 == 0) {printf("t: %d\n", t);}
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
			char out1[1000];
			sprintf(out1, "%d,%d,%d,%d,%d,%d  %d pos:(%d)\n", pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz, t, i);
			fputs(out1, b);
		}
	}

	fclose(b); printf("FIN to out\n"); exit(0);
}
