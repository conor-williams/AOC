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

int SV;
//#define SV 3000
#define getchar()

struct pos_s {
	int x;
	int y;
	int z;
	int vx;
	int vy;
	int vz;
	int ax;
	int ay;
	int az;

	map <tuple<int, int>, int> mpX;
	map <tuple<int, int>, int> mpY;
	map <tuple<int, int>, int> mpZ;

	vector <int> statesX;
	vector <int> statesY;
	vector <int> statesZ;
	vector <int> matchesX;
	vector <int> matchesY;
	vector <int> matchesZ;
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
		pos[i].mpX[make_pair(pos[i].x, pos[i].vx)] = 0;
		pos[i].mpY[make_pair(pos[i].y, pos[i].vy)] = 0;
		pos[i].mpZ[make_pair(pos[i].z, pos[i].vz)] = 0;
	}

	int t;
	for (int which = 0; which < leny; which++) {

		printf("which is %d -- getchar\n", which); getchar();
		for (int i = 0; i < leny; i++) {
			pos[i].x = posOrig[i].x;
			pos[i].y = posOrig[i].y;
			pos[i].z = posOrig[i].z;
			pos[i].vx = posOrig[i].vx;
			pos[i].vy = posOrig[i].vy;
			pos[i].vz = posOrig[i].vz;
		}

		for (int i = 0; i < leny; i++) {
			pos[i].mpX.clear();
			pos[i].mpY.clear();
			pos[i].mpZ.clear();
			for (int i = 0; i < leny; i++) { pos[i].mpX[make_pair(pos[i].x, pos[i].vx)] = 0; }
			for (int i = 0; i < leny; i++) { pos[i].mpY[make_pair(pos[i].y, pos[i].vy)] = 0; }
			for (int i = 0; i < leny; i++) { pos[i].mpZ[make_pair(pos[i].z, pos[i].vz)] = 0; }
		}
		for (t = 1; t < SV; t++) {
			if (t % 1000000 == 0) {printf("t: %d\n", t);}
			for (int i = 0; i < leny; i++) {
				pos[i].ax = 0;
				pos[i].ay = 0;
				pos[i].az = 0;
				for (int j = 0; j < leny; j++) {
					if (i == j) {continue;}
					if (pos[i].x > pos[j].x) {
						pos[i].vx--;
						pos[i].ax--;
					} else if (pos[i].x < pos[j].x) {
						pos[i].vx++;
						pos[i].ax++;
					}

					if (pos[i].y > pos[j].y) {
						pos[i].vy--;
						pos[i].ay--;
					} else if (pos[i].y < pos[j].y) {
						pos[i].vy++;
						pos[i].ay++;
					}

					if (pos[i].z > pos[j].z) {
						pos[i].vz--;
						pos[i].az--;
					} else if (pos[i].z < pos[j].z) {
						pos[i].vz++;
						pos[i].az++;
					}
				}
			}
			for (int i = 0; i < leny; i++) {
				pos[i].x += pos[i].vx;
				pos[i].y += pos[i].vy;
				pos[i].z += pos[i].vz;
			}

			for (int i = which; i <= which ; i++) {
				if (pos[i].mpX.find({pos[i].x, pos[i].vx}) == pos[i].mpX.end()) {
					pos[i].mpX[{pos[i].x, pos[i].vx}] = t;
				} else {
					//pos[i].mpX[{pos[i].x, pos[i].vx}] = t;
					pos[i].statesX.push_back(t);
					pos[i].matchesX.push_back(pos[i].mpX[{pos[i].x, pos[i].vx}]);
				}

				if (pos[i].mpY.find({pos[i].y, pos[i].vy}) == pos[i].mpY.end()) {
					pos[i].mpY[{pos[i].y, pos[i].vy}] = t;
				} else {
					//pos[i].mpY[{pos[i].y, pos[i].vy}] = t;
					pos[i].statesY.push_back(t);
					pos[i].matchesY.push_back(pos[i].mpY[{pos[i].y, pos[i].vy}]);
				}

				if (pos[i].mpZ.find({pos[i].z, pos[i].vz}) == pos[i].mpZ.end()) {
					pos[i].mpZ[{pos[i].z, pos[i].vz}] = t;
				} else {
					//pos[i].mpZ[{pos[i].z, pos[i].vz}] = t;
					pos[i].statesZ.push_back(t);
					pos[i].matchesZ.push_back(pos[i].mpZ[{pos[i].z, pos[i].vz}]);
				}
			}
		}

	}

	//unsigned long long minAns = (unsigned long long)9999999999999999;
	int got = 0;

	for (int i = 0; i < leny; i++) {
		pos[i].mpX.clear();
		pos[i].mpY.clear();
		pos[i].mpZ.clear();
	}

	unsigned long long minAns[4];
	minAns[0] = (unsigned long long)9999999999999999;
	minAns[1] = (unsigned long long)9999999999999999;
	minAns[2] = (unsigned long long)9999999999999999;
	minAns[3] = (unsigned long long)9999999999999999;
	int stateX;
	int matchX;
	int stateY;
	int matchY;
	int stateZ;
	int matchZ;
	for (int i = 0; i < leny; i++) {
		for (int ix = 0; ix < (int)pos[i].statesX.size()-100; ix++) {
			//if (pos[i].matchesX[ix] != 0) {continue;}
			for (int iy = 0; iy < (int)pos[i].statesY.size()-100; iy++) {
				//if (pos[i].matchesY[iy] != 0) {continue;}
				if (pos[i].matchesX[ix] != pos[i].matchesY[iy]) {continue;}
				for (int iz = 0; iz < (int)pos[i].statesZ.size()-100; iz++) {
					if (pos[i].matchesX[ix] == pos[i].matchesY[iy] && pos[i].matchesX[ix] == pos[i].matchesZ[iz]) {
			
						for (int q = 0; q < 100; q++) {
							if (pos[i].matchesX[ix+q] == pos[i].matchesY[iy+q] && pos[i].matchesX[ix+q] == pos[i].matchesZ[iz+q] && pos[i].statesX[ix+q] == pos[i].statesY[iy+q] && pos[i].statesX[ix+q] == pos[i].statesZ[iz+q] /*&& pos[i].matchesX[ix+q] == 0*/ ) 
							{
								printf("found cycle %d,%d\n", pos[i].matchesX[ix], pos[i].statesX[ix]);

								unsigned long long ans =  lcm((unsigned long long)pos[i].statesX[ix], (unsigned long long)lcm(pos[i].statesY[iy], (unsigned long long)pos[i].statesZ[iz]));
								if (ans < minAns[i]) {matchX = pos[i].matchesX[ix]; matchY = pos[i].matchesY[iy]; matchZ = pos[i].matchesZ[iz]; stateX = pos[i].statesX[ix]; stateY = pos[i].statesY[iy]; stateZ = pos[i].statesZ[iz]; minAns[i] = ans;}
								ix+=99;
								iy+=99;
								iz+=99;
							} else {
								break;
							}
						}

					}
				}
			}
		}
		printf("(%d) minAns[i]: %llu (%d, %d %d,%d %d,%d)\n", i, minAns[i], stateX, matchX, stateY, matchY, stateZ, matchZ);
	}

	unsigned long long ans2 =  lcm((unsigned long long)minAns[0], lcm((unsigned long long)minAns[1], (unsigned long long)lcm(minAns[2], (unsigned long long)minAns[3])));
	
	printf("ans2: [[ %llu ]]\n", ans2);
//	exit(0);


	unsigned long long minAns2 = 99999999999999;

		printf("LEFT MAIN LOOP SV: %d -- checking common states %d %d %d %d\n", SV, (int)pos[0].statesX.size(), (int)pos[1].statesX.size(), (int)pos[2].statesX.size(), (int)pos[3].statesX.size());
		for (int i = 0; i < (int)pos[0].statesX.size(); i++) {
			if (pos[0].matchesX[i] != 0) {continue;}
			for (int j = 0; j < (int)pos[1].statesX.size(); j++) {
				if (pos[0].matchesX[i] != pos[1].matchesX[j]) {continue;}
				for (int k = 0; k < (int)pos[2].statesX.size(); k++) {
					if (pos[0].matchesX[i] != pos[2].matchesX[k]) {continue;}
					for (int l = 0; l < (int)pos[3].statesX.size(); l++) {	
						if (pos[0].matchesX[i] == pos[1].matchesX[j] && pos[0].matchesX[i] == pos[2].matchesX[k] && 
								pos[0].matchesX[i] == pos[3].matchesX[l]) {
							printf("ma: %d %d %d %d\n", pos[0].matchesX[i], pos[1].matchesX[j], pos[2].matchesX[k], pos[3].matchesX[l]);
							printf("st: %d %d %d %d\n", pos[0].statesX[i], pos[1].statesX[j], pos[2].statesX[k], pos[3].statesX[l]);
							unsigned long long ans =  lcm((unsigned long long)pos[3].statesX[l], lcm((unsigned long long)pos[0].statesX[i], (unsigned long long)lcm(pos[1].statesX[j], (unsigned long long)pos[2].statesX[k])));
							//printf("%llu\n", ans);
							if (ans < minAns2) {minAns2 = ans;}
							got = 1;
						}
					}
				}
			}
		}
		unsigned long long ansX = minAns2;
		printf("ANSX:[[[ %llu ]]]\n", minAns2);
		minAns2 = (unsigned long long)9999999999999999;
		printf("LEFT MAIN LOOP SV: %d -- checking common states %d %d %d %d\n", SV, (int)pos[0].statesY.size(), (int)pos[1].statesY.size(), (int)pos[2].statesY.size(), (int)pos[3].statesY.size());
		for (int i = 0; i < (int)pos[0].statesY.size(); i++) {
			if (pos[0].matchesY[i] != 0) {continue;}
			for (int j = 0; j < (int)pos[1].statesY.size(); j++) {
				if (pos[0].matchesY[i] != pos[1].matchesY[j]) {continue;}
				for (int k = 0; k < (int)pos[2].statesY.size(); k++) {
					if (pos[0].matchesY[i] != pos[2].matchesY[k]) {continue;}
					for (int l = 0; l < (int)pos[3].statesY.size(); l++) {	
						if (pos[0].matchesY[i] == pos[1].matchesY[j] && pos[0].matchesY[i] == pos[2].matchesY[k] && 
								pos[0].matchesY[i] == pos[3].matchesY[l]) {
							//printf("ma: %d %d %d %d\n", pos[0].matchesY[i], pos[1].matchesY[j], pos[2].matchesY[k], pos[3].matchesY[l]);
							//printf("st: %d %d %d %d\n", pos[0].statesY[i], pos[1].statesY[j], pos[2].statesY[k], pos[3].statesY[l]);
							unsigned long long ans =  lcm((unsigned long long)pos[3].statesY[l], lcm((unsigned long long)pos[0].statesY[i], (unsigned long long)lcm(pos[1].statesY[j], (unsigned long long)pos[2].statesY[k])));
							//printf("%llu\n", ans);
							if (ans < minAns2) {minAns2 = ans;}
							got = 1;
						}
					}
				}
			}
		}
		printf("ANSY:[[[ %llu ]]]\n", minAns2);

		unsigned long long ansY = minAns2;
		minAns2 = (unsigned long long)9999999999999999;
		printf("LEFT MAIN LOOP SV: %d -- checking common states %d %d %d %d\n", SV, (int)pos[0].statesZ.size(), (int)pos[1].statesZ.size(), (int)pos[2].statesZ.size(), (int)pos[3].statesZ.size());
		for (int i = 0; i < (int)pos[0].statesZ.size(); i++) {
			if (pos[0].matchesZ[i] != 0) {continue;}
			for (int j = 0; j < (int)pos[1].statesZ.size(); j++) {
				if (pos[0].matchesZ[i] != pos[1].matchesZ[j]) {continue;}
				for (int k = 0; k < (int)pos[2].statesZ.size(); k++) {
					if (pos[0].matchesZ[i] != pos[2].matchesZ[k]) {continue;}
					for (int l = 0; l < (int)pos[3].statesZ.size(); l++) {	
						if (pos[0].matchesZ[i] == pos[1].matchesZ[j] && pos[0].matchesZ[i] == pos[2].matchesZ[k] && 
								pos[0].matchesZ[i] == pos[3].matchesZ[l]) {
							//printf("ma: %d %d %d %d\n", pos[0].matchesZ[i], pos[1].matchesZ[j], pos[2].matchesZ[k], pos[3].matchesZ[l]);
							//printf("st: %d %d %d %d\n", pos[0].statesZ[i], pos[1].statesZ[j], pos[2].statesZ[k], pos[3].statesZ[l]);
							unsigned long long ans =  lcm((unsigned long long)pos[3].statesZ[l], lcm((unsigned long long)pos[0].statesZ[i], (unsigned long long)lcm(pos[1].statesZ[j], (unsigned long long)pos[2].statesZ[k])));
							//printf("%llu\n", ans);
							if (ans < minAns2) {minAns2 = ans;}
							got = 1;
						}
					}
				}
			}
		}
		unsigned long long ansZ = minAns2;
		printf("ANSZ:[[[ %llu ]]]\n", minAns2);

		unsigned long long ans3 =  lcm((unsigned long long)ansY, (unsigned long long)lcm(ansX, (unsigned long long)ansZ));
		printf("END ANS:[[[ %llu ]]]\n", ans3);
		if (got == 0) {
			printf("time to inc SV from %d\n", SV);
		}
	}
