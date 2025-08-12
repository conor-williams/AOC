#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <map>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm> 

#include <unistd.h>

#define getchar()
using namespace std;
//deque <int> b1Q;
int other = 0;

FILE *a;
#define LINE 1000
#define getchar()
//f(char*s){for(s+=9;(*s+=*s-57?1:8)>90;*s--=48);}
//char var_orient[] = "0000000000";
struct al_s {
	int p1b2;
	int p2b2;
};
struct al_s al[3000];
int alPos = 0;

map <tuple<int, int, int>, int> mp2;
bool determinant(int l);
///////////////////
unordered_set<int> vis;
unordered_map<int, vector<int>> adj;
int pairZ();
void dfs(int u, vector<int>& cur_group);
///////////////////

void next(char *as); int numit(int pos);
int lineI[10][32];
int lineI2[32];
long lineIPos = 0;
struct beacon_s {
	int scannerx;
	int scannery;
	int scannerz;

	int mapx;
	int mapy;
	int mapz;

	int orient;

	int x[50][25];
	int y[50][25];
	int z[50][25];

	/// should really switch the 25s
	int distxx[25][50][50];
	int distyy[25][50][50];
	int distzz[25][50][50];

	int beaconPos;
};
struct done_s {
	int bea;
};
int beaPos = 0;

struct pairs_s {
	int b1;
	int b2;
	int o1;
	int o2;
};
int same(int o1, int o2);
/////////////////////////////////////////

struct beacon_s beacon[30];
vector <int> deters;

void matmul(int ma[3][3], int threebyone[3], int beaconPos, int jpos, int pos);

int m[48][3][3] =
{
	{{1, 0, 0}, {0,1,0}, {0,0,1}},
	{{1, 0, 0}, {0,1,0}, {0,0,-1}},
	{{1, 0, 0}, {0,-1,0}, {0,0,1}},
	{{1, 0, 0}, {0,-1,0}, {0,0,-1}},
	{{-1, 0, 0}, {0,1,0}, {0,0,1}},
	{{-1, 0, 0}, {0,1,0}, {0,0,-1}},
	{{-1, 0, 0}, {0,-1,0}, {0,0,1}},
	{{-1, 0, 0}, {0,-1,0}, {0,0,-1}},
	//xzy
	{{1, 0, 0}, {0,0,1}, {0,1,0}},
	{{1, 0, 0}, {0,0,1}, {0,-1,0}},
	{{1, 0, 0}, {0,0,-1}, {0,1,0}},
	{{1, 0, 0}, {0,0,-1}, {0,-1,0}},
	{{-1, 0, 0}, {0,0,1}, {0,1,0}},
	{{-1, 0, 0}, {0,0,1}, {0,-1,0}},
	{{-1, 0, 0}, {0,0,-1}, {0,1,0}},
	{{-1, 0, 0}, {0,0,-1}, {0,-1,0}},
	//yxz
	{{0, 1, 0}, {1,0,0}, {0,0,1}},
	{{0, 1, 0}, {1,0,0}, {0,0,-1}},
	{{0, 1, 0}, {-1,0,0}, {0,0,1}},
	{{0, 1, 0}, {-1,0,0}, {0,0,-1}},
	{{0, -1, 0}, {1,0,0}, {0,0,1}},
	{{0, -1, 0}, {1,0,0}, {0,0,-1}},
	{{0, -1, 0}, {-1,0,0}, {0,0,1}},
	{{0, -1, 0}, {-1,0,0}, {0,0,-1}},
	//yzx
	{{0, 1, 0}, {0,0,1}, {1,0,0}},
	{{0, 1, 0}, {0,0,1}, {-1,0,0}},
	{{0, 1, 0}, {0,0,-1}, {1,0,0}},
	{{0, 1, 0}, {0,0,-1}, {-1,0,0}},
	{{0, -1, 0}, {0,0,1}, {1,0,0}},
	{{0, -1, 0}, {0,0,1}, {-1,0,0}},
	{{0, -1, 0}, {0,0,-1}, {1,0,0}},
	{{0, -1, 0}, {0,0,-1}, {-1,0,0}},
	//zxy
	{{0, 0, 1}, {1,0,0}, {0,1,0}},
	{{0, 0, 1}, {1,0,0}, {0,-1,0}},
	{{0, 0, 1}, {-1,0,0}, {0,1,0}},
	{{0, 0, 1}, {-1,0,0}, {0,-1,0}},
	{{0, 0, -1}, {1,0,0}, {0,1,0}},
	{{0, 0, -1}, {1,0,0}, {0,-1,0}},
	{{0, 0, -1}, {-1,0,0}, {0,1,0}},
	{{0, 0, -1}, {-1,0,0}, {0,-1,0}},
	//zyx
	{{0, 0, 1}, {0,1,0}, {1,0,0}},
	{{0, 0, 1}, {0,1,0}, {-1,0,0}},
	{{0, 0, 1}, {0,-1,0}, {1,0,0}},
	{{0, 0, 1}, {0,-1,0}, {-1,0,0}},
	{{0, 0, -1}, {0,1,0}, {1,0,0}},
	{{0, 0, -1}, {0,1,0}, {-1,0,0}},
	{{0, 0, -1}, {0,-1,0}, {1,0,0}},
	{{0, 0, -1}, {0,-1,0}, {-1,0,0}}
};

int main(int argc, char **argv)
{
	FILE *a = fopen(argv[1], "r"); printf("		2021 Day19.1\n"); fflush(stdout);
	printf("	SLOW ~1minute10seconds (try -O2)\n");

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	int pos = 0;
	int numB = 0;
	vector<tuple<int, int, int>> veFirst;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);

		int ret = 0;
		if (line1[0] == '\0') {
			beacon[pos].beaconPos = numB; pos++; numB = 0;
			continue;
		} if (line1[0] == '-' && line1[1] == '-') {
			continue;
		} else {
			int one, two, three;
			sscanf(line1, "%d,%d,%d", &one, &two, &three);
			beacon[pos].x[numB][0] = one;
			beacon[pos].y[numB][0] = two;
			beacon[pos].z[numB][0] = three;
			if (pos == 0) {
				veFirst.push_back(make_tuple(one, two, three));
			}
			numB++;
		}
		leny++;

	}
	fclose(a);
	beacon[pos].beaconPos = numB;
	pos++;


	int numBeacons = pos;
	for (int l = 0; l < 48; l++) {
		if (determinant(l)) {
			deters.push_back(l);
		}
	}
	//rotate all beacons...
	for (int jj = 0; jj < numBeacons; jj++) {
		for (int kk = 0; kk < beacon[jj].beaconPos; kk++) {
			int threebyone[3];
			threebyone[0] = beacon[jj].x[kk][0];
			threebyone[1] = beacon[jj].y[kk][0];
			threebyone[2] = beacon[jj].z[kk][0];
			for (int ii = 0; ii < deters.size(); ii++) {
				matmul(m[deters[ii]], threebyone, jj, kk, ii);
			}
		}
	}
	vector <tuple <int, int, int>> allBeacons;
	vector <int> found;
	vector<int> distances[numBeacons];
	printf("numBeacons is %d\n", numBeacons);

	for (int ii = 0; ii < numBeacons; ii++) {
		for (int one = 0; one < beacon[ii].beaconPos; one++) {
			int distXone = beacon[ii].x[one][0];
			int distYone = beacon[ii].y[one][0];
			int distZone = beacon[ii].z[one][0];

			for (int two = 0; two < beacon[ii].beaconPos; two++) {
				if (one == two) {continue;}
				int distXtwo = beacon[ii].x[two][0];
				int distYtwo = beacon[ii].y[two][0];
				int distZtwo = beacon[ii].z[two][0];

				distances[ii].push_back(abs(distXone-distXtwo) + abs(distYone-distYtwo) + abs(distZone-distZtwo));
			}
		}
	}

	vector <pair <int, int>> pairs;
	for (int ii = 0; ii < numBeacons; ii++) {
		for (int jj = 0; jj < numBeacons; jj++) {
			if (ii == jj) {continue;}
			vector <int> d1 = distances[ii];

			vector <int> d2 = distances[jj];

			sort(d1.begin(), d1.end());
			sort(d2.begin(), d2.end());
			vector<int> inter;
			//d1.retainAll(d2);
			set_intersection(d1.begin(), d1.end(), d2.begin(), d2.end(), back_inserter(inter));

			if (inter.size() >= 121) {
				pairs.push_back(make_pair(ii, jj));
				printf("%d %d\n", ii, jj);
			}
		}
	}


	vector <int> found2;
	found2.push_back(0);
	do {
		veFirst.clear();
		int which = found2[0];
		for (int zz = 0; zz < beacon[which].beaconPos; zz++) {
			veFirst.push_back(make_tuple(beacon[which].x[zz][0], beacon[which].y[zz][0], beacon[which].z[zz][0]));
		}

		for (int zzz = 0; zzz < veFirst.size(); zzz++) {
			auto tu1 = veFirst[zzz];
			int sX = get<0>(tu1);
			int sY = get<1>(tu1);
			int sZ = get<2>(tu1);

			for (int qqqq = 0; qqqq < pairs.size(); qqqq++) {
				int i = -1;
				if (pairs[qqqq].first == found2[0]) {
					i = pairs[qqqq].second;

					if (find(found.begin(), found.end(), i) != found.end()) {continue;}
					int end2 = beacon[i].beaconPos;
					for (int k = 0; k < 24; k++) {
						for (int j = 0; j < end2-11; j++) {
							int distX = (sX - beacon[i].x[j][k]);
							int distY = (sY - beacon[i].y[j][k]);
							int distZ = (sZ - beacon[i].z[j][k]);

							//apply that dist to every beacon in i
							for (int kk = 0; kk < 24; kk++) {
								vector <tuple <int, int, int>> veNext;
								//int end1 = beacon[i].beaconPos;
								for (int jj = 0; jj < end2; jj++) {
									int newDistX = beacon[i].x[jj][kk] + distX;
									int newDistY = beacon[i].y[jj][kk] + distY;
									int newDistZ = beacon[i].z[jj][kk] + distZ;

									veNext.push_back(make_tuple(newDistX, newDistY, newDistZ));
								}
								vector <tuple<int, int, int>> intersection;
								//intersection.retainAll(veNext);
								sort(veNext.begin(), veNext.end());
								sort(veFirst.begin(), veFirst.end());
								set_intersection(veFirst.begin(), veFirst.end(), veNext.begin(), veNext.end(), 
										back_inserter(intersection));
								if (intersection.size() == 12) {
									for (int qqq = 0; qqq < veNext.size(); qqq++) {
										if (find(allBeacons.begin(), allBeacons.end(), veNext[qqq]) == allBeacons.end()) {
											allBeacons.push_back(veNext[qqq]);
										}
									}
									for (int jj = 0; jj < beacon[i].beaconPos; jj++) {
										auto tu2 = veNext[jj];
										beacon[i].x[jj][0] = get<0>(tu2);
										beacon[i].y[jj][0] = get<1>(tu2);
										beacon[i].z[jj][0] = get<2>(tu2);
									}
									found.push_back(i);
									found2.push_back(i);
									goto after;
								}
							}
						}
					}
after:
					continue;
				}
			}
		}
		found2.erase(found2.begin()+0);
	} while (found2.size() > 0);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	printf("%d", allBeacons.size());
	printf("\n");
}

void matmul(int ma[3][3], int threebyone[3], int beaconPos, int jpos, int pos) {

	beacon[beaconPos].x[jpos][pos] = 0;
	beacon[beaconPos].y[jpos][pos] = 0;
	beacon[beaconPos].z[jpos][pos] = 0;
	int result[3] = {0};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0) {
				beacon[beaconPos].x[jpos][pos] += ma[i][j] * threebyone[j];
			} else if (i==1) {
				beacon[beaconPos].y[jpos][pos] += ma[i][j] * threebyone[j];
			} else if (i==2) {
				beacon[beaconPos].z[jpos][pos] += ma[i][j] * threebyone[j];
			}
			result[i] +=  ma[i][j] * threebyone[j];
		}
	}
	assert(result[0] ==  beacon[beaconPos].x[jpos][pos]);
	assert(result[1] ==  beacon[beaconPos].y[jpos][pos]);
	assert(result[2] ==  beacon[beaconPos].z[jpos][pos]);
}

bool determinant(int l) {
	//              a             e          i           g          h
	int a1 = m[l][0][0] * (m[l][1][1] * m[l][2][2] - m[l][1][2] * m[l][2][1]);
	//             b              d         l          g             f
	int b1 = m[l][0][1] * (m[l][1][0] * m[l][2][2] - m[l][2][0] * m[l][1][2]);
	//           c              d           h                 e        g
	int c1 = m[l][0][2] * (m[l][1][0] * m[l][2][1] - m[l][1][1] * m[l][2][0]);
	int det = a1 - b1 + c1;
	if (det == 1) {return true;}
	else {return false;}
}

