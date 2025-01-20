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
};
struct pos_s pos[4];
struct pos_s posOrig[4];

int main(int argc, char **argv)
{
	if (argc < 3) {printf("give a size\n"); exit(0);}
	SV = atoi(argv[2]);
	lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);


	char line1[MAX] = {0};
	while(1) {
		fgets(line1, MAX -1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
		//printf("LINE: %s getchar\n", line1); getchar();
		sscanf(line1, "<x=%d, y=%d, z=%d", &pos[leny].x, &pos[leny].y, &pos[leny].z);
		leny++;
	}
	fclose(a);
	
	for (int i = 0; i < leny; i++) {
		posOrig[i].x = pos[i].x;
		posOrig[i].y = pos[i].y;
		posOrig[i].z = pos[i].z;
		posOrig[i].vx = pos[i].vx;
		posOrig[i].vy = pos[i].vy;
		posOrig[i].vz = pos[i].vz;
	}

	for (int i = 0; i < leny; i++) {
		pos[i].mp[make_tuple(pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz)] = 0;
	}
	for (int i = 0; i < leny; i++) {
		printf("(%d,%d) %d %d %d %d %d %d\n", i, 0, pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz);
	}

	int t;
	for (int which = 0; which < leny; which++) {

		for (int i = 0; i < leny; i++) {
			pos[i].x = posOrig[i].x;
			pos[i].y = posOrig[i].y;
			pos[i].z = posOrig[i].z;
			pos[i].vx = posOrig[i].vx;
			pos[i].vy = posOrig[i].vy;
			pos[i].vz = posOrig[i].vz;
		}
			
		for (int i = 0; i < leny; i++) {
			pos[i].mp.clear();
			for (int i = 0; i < leny; i++) { pos[i].mp[make_tuple(pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz)] = 0; }
			for (int i = 0; i < leny; i++) { printf("(%d,%d) %d %d %d %d %d %d\n", i, 0, pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz); }
		}
		for (t = 1; t < SV; t++) {
			if (t % 1000000 == 0) {printf("t: %d\n", t);}
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

			for (int i = which; i <= which ; i++) {
				if (pos[i].mp.find({pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz}) == pos[i].mp.end()) {
					pos[i].mp[make_tuple(pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz)] =  t;
				} else {
					pos[i].states.push_back(t);
					pos[i].matches.push_back(pos[i].mp[make_tuple(pos[i].x, pos[i].y, pos[i].z, pos[i].vx, pos[i].vy, pos[i].vz)]);
				}
			}
		}
	}

	printf("LEFT MAIN LOOP SV: %d -- maps %d %d %d %d\n", SV, (int)pos[0].mp.size(), (int)pos[1].mp.size(), (int)pos[2].mp.size(), (int)pos[3].mp.size());
	for (int i = 0; i < leny; i++) {
		pos[i].mp.clear();
	}
	printf("LEFT MAIN LOOP SV: %d -- checking common states %d %d %d %d\n", SV, (int)pos[0].states.size(), (int)pos[1].states.size(), (int)pos[2].states.size(), (int)pos[3].states.size());
	unsigned long long minAns = (unsigned long long)9999999999999999;
	int got = 0;
	for (int i = 0; i < (int)pos[0].states.size(); i++) {
		for (int j = 0; j < (int)pos[1].states.size(); j++) {
			if (pos[0].matches[i] != pos[1].matches[j]) {continue;}
			for (int k = 0; k < (int)pos[2].states.size(); k++) {
				if (pos[0].matches[i] != pos[2].matches[k]) {continue;}
				for (int l = 0; l < (int)pos[3].states.size(); l++) {	
					if (pos[0].matches[i] == pos[1].matches[j] && pos[0].matches[i] == pos[2].matches[k] && 
							pos[0].matches[i] == pos[3].matches[l]) {
						printf("ma: %d %d %d %d\n",
								pos[0].matches[i],
								pos[1].matches[j],
								pos[2].matches[k],
								pos[3].matches[l]);
						printf("st: %d %d %d %d\n",
								pos[0].states[i],
								pos[1].states[j],
								pos[2].states[k],
								pos[3].states[l]);
						unsigned long long ans =  lcm((unsigned long long)pos[3].states[l], lcm((unsigned long long)pos[0].states[i], (unsigned long long)lcm(pos[1].states[j], (unsigned long long)pos[2].states[k])));
						printf("%llu\n", ans);
						if (ans < minAns) {minAns = ans;}
						got = 1;
					}
				}
			}
		}
	}
	printf("END t is %d ANS:[[[ %llu ]]]\n", t, minAns);
	if (got == 0) {
		printf("time to inc SV from %d\n", SV);
	}
}
