#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <map>

using namespace std;
//deque <int> b1Q;

FILE *a;
#define LINE 1000
#define getchar()
//f(char*s){for(s+=9;(*s+=*s-57?1:8)>90;*s--=48);}
//char var_orient[] = "0000000000";

void next(char *as); int numit(int pos);
int lineI[1000000][5];
int lineIPos = 0;
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
struct pairs_s pairs[1000];
int pairsPos = 0;
struct allB_s {
	int x;
	int y;
	int z;
};

struct tmp_s {
	int b1;
	int p1;
	int o11;
	int b11;
	int pos1;
	int pos_1;

	int o22;
	int b22;
	int b2;
	int p2;
	int pos2;
	int pos_2;

	int mapx;
	int mapy;
	int mapz;
	int x1;
	int y1;
	int z1;

	int x_1;
	int y_1;
	int z_1;

	int x2;
	int y2;
	int z2;

	int x_2;
	int y_2;
	int z_2;
};
struct tmp_s tmpxyz[100];
struct pa_s {
	int b1;
	int b2;
};
map<pair<int, int>, int> mp;
int paPos = 0;


#define MAXALLB 10000
struct allB_s allB[MAXALLB];

int allBPos = 0;
struct beacon_s beacon[100];
struct beacon_s beaconOrig[100];

void matmul(int ma[3][3], int threebyone[3], int beaconPos, int jpos, int pos);

int m1[3][3] = {{+1, 0, 0}, {0, 0, +1}, {0, -1, 0}};
//int m1[3][3] = {{+1, 0, 0}, {0, 0, -1}, {0, 1, 0}};
int m2[3][3] = {{0, +1, 0}, {0, 0, +1}, {+1, 0, 0}};
//int m2[3][3] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};
int m3[3][3] = {{0, +1, 0}, {+1, 0, 0}, {0, 0, -1}};
//int m3[3][3] = {{0, +1, 0}, {+1, 0, 0}, {0, 0, -1}};
//--- beacon 0 ---
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("2021 Day19\n"); fflush(stdout);
	char line1[LINE];

	int leny = 0;
	int beaconNum = 0;
	int beaconPos = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);

		int ret = 0;
		if (line1[0] == '\0') {
			continue;
		} else {
			ret = sscanf(line1, "--- scanner %d ---", &beaconNum);
			if (ret == 1) {
				if (beaconNum > 100) {perror("too big\n"); exit(0);}
				beaconPos = 0;
				continue;
			} else {
				char Sx1[10], Sy1[10], Sz1[10];
				int x1, y1, z1;
				ret =  sscanf(line1, "%[^,],%[^,],%[^\0]", Sx1, Sy1, Sz1);
				if (ret == 3) {
					beacon[beaconNum].x[beaconPos][0] = atoi(Sx1);
					beacon[beaconNum].y[beaconPos][0] = atoi(Sy1);
					beacon[beaconNum].z[beaconPos][0] = atoi(Sz1);

					beacon[beaconNum].x[beaconPos][3] = -atoi(Sx1);
					beacon[beaconNum].y[beaconPos][3] = atoi(Sy1);
					beacon[beaconNum].z[beaconPos][3] = atoi(Sz1);

					beacon[beaconNum].x[beaconPos][6] = atoi(Sx1);
					beacon[beaconNum].y[beaconPos][6] = -atoi(Sy1);
					beacon[beaconNum].z[beaconPos][6] = atoi(Sz1);

					beacon[beaconNum].x[beaconPos][9] = -atoi(Sx1);
					beacon[beaconNum].y[beaconPos][9] = -atoi(Sy1);
					beacon[beaconNum].z[beaconPos][9] = atoi(Sz1);


					beacon[beaconNum].x[beaconPos][12] = atoi(Sx1);
					beacon[beaconNum].y[beaconPos][12] = atoi(Sy1);
					beacon[beaconNum].z[beaconPos][12] = -atoi(Sz1);

					beacon[beaconNum].x[beaconPos][15] = -atoi(Sx1);
					beacon[beaconNum].y[beaconPos][15] = atoi(Sy1);
					beacon[beaconNum].z[beaconPos][15] = -atoi(Sz1);

					beacon[beaconNum].x[beaconPos][18] = atoi(Sx1);
					beacon[beaconNum].y[beaconPos][18] = -atoi(Sy1);
					beacon[beaconNum].z[beaconPos][18] = -atoi(Sz1);


					beacon[beaconNum].x[beaconPos][21] = -atoi(Sx1);
					beacon[beaconNum].y[beaconPos][21] = -atoi(Sy1);
					beacon[beaconNum].z[beaconPos][21] = -atoi(Sz1);

					beacon[beaconNum].x[beaconPos][24] = atoi(Sx1);
					beacon[beaconNum].y[beaconPos][24] = atoi(Sy1);
					beacon[beaconNum].z[beaconPos][24] = atoi(Sz1);
					if (beaconPos == 0) {
						beacon[beaconPos].scannerx = 0;
						beacon[beaconPos].scannery = 0;
						beacon[beaconPos].scannerz = 0;
					}
					beaconPos++;
					beacon[beaconNum].beaconPos = beaconPos;
				} else {
					printf("%s\n", line1);
					perror("not 3 \n"); exit(0);
				}
			}
		}

		leny++;

	}
	fclose(a);

	beaconNum++;
	printf("beaconNum is %d\n", beaconNum); getchar();
	beacon[0].scannerx = 0;
	beacon[0].scannery = 0;
	beacon[0].scannerz = 0;

	beacon[0].mapx = 0;
	beacon[0].mapy = 0;
	beacon[0].mapz = 0;

	beacon[0].orient = 0;

	for (int i = 1; i < beaconNum; i++) {
		beacon[i].scannerx = -999;
		beacon[i].scannery = -999;
		beacon[i].scannerz = -999;
	}

	for (int i = 0; i < beaconNum; i++) {
		for (int j = 0; j < beacon[i].beaconPos; j++) {
			printf("%d %d %d -- ", beacon[i].x[j][0], beacon[i].y[j][0], beacon[i].z[j][0]);
		}
		printf("\n");
	} getchar();

	int threebyone[3];
	for (int i = 0; i < beaconNum; i++) {
		for (int j = 0; j < beacon[i].beaconPos; j++) {
			threebyone[0] = beacon[i].x[j][0];
			threebyone[1] = beacon[i].y[j][0];
			threebyone[2] = beacon[i].z[j][0];
			matmul(m1, threebyone,i, j, 0);
			matmul(m2, threebyone,i, j, 1);
			matmul(m3, threebyone,i, j, 2);

			threebyone[0] = beacon[i].x[j][3];
			threebyone[1] = beacon[i].y[j][3];
			threebyone[2] = beacon[i].z[j][3];
			matmul(m1, threebyone,i, j, 3);
			matmul(m2, threebyone,i, j, 4);
			matmul(m3, threebyone,i, j, 5);

			threebyone[0] = beacon[i].x[j][6];
			threebyone[1] = beacon[i].y[j][6];
			threebyone[2] = beacon[i].z[j][6];
			matmul(m1, threebyone,i, j, 6);
			matmul(m2, threebyone,i, j, 7);
			matmul(m3, threebyone,i, j, 8);

			threebyone[0] = beacon[i].x[j][9];
			threebyone[1] = beacon[i].y[j][9];
			threebyone[2] = beacon[i].z[j][9];
			matmul(m1, threebyone,i, j, 9);
			matmul(m2, threebyone,i, j, 10);
			matmul(m3, threebyone,i, j, 11);

			threebyone[0] = beacon[i].x[j][12];
			threebyone[1] = beacon[i].y[j][12];
			threebyone[2] = beacon[i].z[j][12];
			matmul(m1, threebyone,i, j, 12);
			matmul(m2, threebyone,i, j, 13);
			matmul(m3, threebyone,i, j, 14);

			threebyone[0] = beacon[i].x[j][15];
			threebyone[1] = beacon[i].y[j][15];
			threebyone[2] = beacon[i].z[j][15];
			matmul(m1, threebyone,i, j, 15);
			matmul(m2, threebyone,i, j, 16);
			matmul(m3, threebyone,i, j, 17);

			threebyone[0] = beacon[i].x[j][18];
			threebyone[1] = beacon[i].y[j][18];
			threebyone[2] = beacon[i].z[j][18];
			matmul(m1, threebyone,i, j, 18);
			matmul(m2, threebyone,i, j, 19);
			matmul(m3, threebyone,i, j, 20);

			threebyone[0] = beacon[i].x[j][21];
			threebyone[1] = beacon[i].y[j][21];
			threebyone[2] = beacon[i].z[j][21];
			matmul(m1, threebyone,i, j, 21);
			matmul(m2, threebyone,i, j, 22);
			matmul(m3, threebyone,i, j, 23);

			printf("%d %d %d -- ", beacon[i].x[j][0], beacon[i].y[j][0], beacon[i].z[j][0]);
		}
		for (int j = 0; j < beacon[i].beaconPos; j++) {
			for (int q = 0; q < 25; q++) {
				printf("XYZ -- %d %d %d\n", beacon[i].x[j][q], beacon[i].y[j][q], beacon[i].z[j][q]); 
				if (beacon[i].x[j][q] == 0 && beacon[i].y[j][q] == 0 && beacon[i].z[j][q] == 0) {
					printf("ERROR\n"); getchar();
				}
			}
		}
	}

	for (int i = 0; i < beaconNum; i++) {
		for (int k = 0; k < 25; k++) {
			for (int j = 0; j < beacon[i].beaconPos-1; j++) {
				beaconOrig[i].x[j][k] = beacon[i].x[j][k];
				beaconOrig[i].y[j][k] = beacon[i].y[j][k];
				beaconOrig[i].z[j][k] = beacon[i].z[j][k];
			}
		}
	}

	for (int i = 0; i < beaconNum; i++) {
		for (int k = 0; k < 25; k++) {
			for (int j = 0; j < beacon[i].beaconPos-1; j++) {
				for (int l = j+1; l < beacon[i].beaconPos; l++) {
					if (j == l) {continue;}
					beacon[i].distxx[k][j][l] = abs(beacon[i].x[j][k] - beacon[i].x[l][k]);
					beacon[i].distyy[k][j][l] = abs(beacon[i].y[j][k] - beacon[i].y[l][k]);
					beacon[i].distzz[k][j][l] = abs(beacon[i].y[j][k] - beacon[i].y[l][k]);
				}
			}
		}
	}

	for (int two = 0; two < beacon[0].beaconPos; two++) {
		int found = 0;
		for (int z = 0; z < allBPos; z++) {
			if (allB[z].x == beacon[0].x[two][15] + beacon[0].mapx &&
					allB[z].y == beacon[0].y[two][15] + beacon[0].mapy &&
					allB[z].z == beacon[0].z[two][15] + beacon[0].mapz)  {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			allB[allBPos].x = beacon[0].x[two][15] + beacon[0].mapx;
			allB[allBPos].y = beacon[0].y[two][15] + beacon[0].mapy;
			allB[allBPos].z = beacon[0].z[two][15] + beacon[0].mapz;
			allBPos++;
		}
	}
	//printf("allBPos: %d\n", allBPos); getchar();


	//int b1_1[] = {0, 1, 1, 4};
	//int b2_2[] = {1, 3, 4, 2};
	{
		//for (int b1_1Pos = 0; b1_1Pos < beaconNum-1; b1_1Pos++) 
		//int b1 = b1_1[b1_1Pos];
		//int b2 = b2_2[b1_1Pos];

		for (int b1= 0; b1< beaconNum; b1++)
		{
			for (int b2 = 0; b2 < beaconNum; b2++)
			{
				if (b1 == b2) {continue;}
				int found3 = 0;

				for (int q1 = 0; q1 < pairsPos; q1++) { 
					if ((pairs[q1].b1 == b1 && pairs[q1].b2 == b2) || (pairs[q1].b2 == b1 && pairs[q1].b1 == b2)) {
						found3 = 1; break;
					}
				}
				if (found3 == 1) {continue;}
				//printf("***beacon [%d] v [%d] or:[%s]\n", b1, b2, var_orient); getchar();

				for (int o1 = 0; o1 < 25; o1++) 
				{
					//printf("using orient o1:%d for b1:%d\n", o1, b1); getchar();
					for (int o2 = 0; o2 < 25; o2++) {
						for (int p1b1 = 0; p1b1 < beacon[b1].beaconPos-1; p1b1++) {
							int most[100] = {0};
							int count = 0;
							for (int p2b1 = p1b1+1; p2b1 < beacon[b1].beaconPos; p2b1++) {
								for (int p1b2 = 0; p1b2 < beacon[b2].beaconPos-1; p1b2++) {
									for (int p2b2 = p1b2+1; p2b2 < beacon[b2].beaconPos; p2b2++) {

										if (beacon[b1].distxx[o1][p1b1][p2b1]  == beacon[b2].distxx[o2][p1b2][p2b2] &&
												beacon[b1].distyy[o1][p1b1][p2b1] == beacon[b2].distyy[o2][p1b2][p2b2] &&
												beacon[b1].distzz[o1][p1b1][p2b1] == beacon[b2].distzz[o2][p1b2][p2b2]) {
											tmpxyz[count].b1 = b1;
											tmpxyz[count].pos1 = p1b1;
											tmpxyz[count].pos_1 = p2b1;
											tmpxyz[count].o11 = o1;

											tmpxyz[count].b2 = b2;
											tmpxyz[count].pos2 = p1b2;
											tmpxyz[count].pos_2 = p2b2;
											tmpxyz[count].o22 = o2;

											count++;
											most[p1b2]++;

											if (count == 11) {
												int max = 0;
												int maxI = -1;
												for (int i = 0; i < 30; i++) {
													if (most[i] > max) {max = most[i]; maxI = i;}
												}


												//printf("C O UNT11: maps: %d %d %d V %d %d %d", beacon[b1].scannerx, beacon[b1].scannery, beacon[b1].scannerz,
												//		beacon[b2].scannerx, beacon[b2].scannery, beacon[b2].scannerz); fflush(stdout);
												//printf("allBPos n ow %d\n", allBPos); fflush(stdout);
												for (int r = 0; r < 11; r++) {
													tmpxyz[r].b11 = b1;
													tmpxyz[r].o11 = o1;
													tmpxyz[r].b22 = b2;
													tmpxyz[r].o22 = o2;
													tmpxyz[r].p1 = tmpxyz[r].pos_1;
													tmpxyz[r].p2 = tmpxyz[r].pos_2 == maxI ? tmpxyz[r].pos2 : tmpxyz[r].pos_2;
												}
												for (int r = 0; r < 11; r++) {
													//printf("r:%d p1,p2 == %d,%d\n", r, tmpxyz[r].p1, tmpxyz[r].p2);
													tmpxyz[r].mapx = beacon[b1].x[tmpxyz[r].p1][o1] - beacon[b2].x[tmpxyz[r].p2][o2];
													tmpxyz[r].mapy = beacon[b1].y[tmpxyz[r].p1][o1] - beacon[b2].y[tmpxyz[r].p2][o2];
													tmpxyz[r].mapz = beacon[b1].z[tmpxyz[r].p1][o1] - beacon[b2].z[tmpxyz[r].p2][o2];
												}

												int found2 = 0;
												for (int r = 0; r < 11-1; r++) {
													if (tmpxyz[r].mapx == tmpxyz[r+1].mapx && tmpxyz[r].mapy == tmpxyz[r+1].mapy &&
															tmpxyz[r].mapz == tmpxyz[r+1].mapz) {
													} else {
														found2 = 1;
													}
												}
												int xmain = beacon[b1].x[p1b1][o1] - beacon[b2].x[maxI][o2]; 
												int ymain = beacon[b1].y[p1b1][o1] - beacon[b2].y[maxI][o2];
												int zmain = beacon[b1].z[p1b1][o1] - beacon[b2].z[maxI][o2];
												if (found2 == 0) {
													if (xmain == tmpxyz[0].mapx && ymain == tmpxyz[0].mapy && zmain == tmpxyz[0].mapz) {
														found2 = 0;
													} else {
														found2 = 1;
													}
												}
												if (found2 == 0) {
													printf("MAPS SAME: b:%d V %d -- o: %d V %d\n", b1, b2, o1, o2);
													if (b1 == 0 && b2 == 1) {getchar();}
													count = 0;
													pairs[pairsPos].b1 = b1;	
													pairs[pairsPos].b2 = b2;	
													pairs[pairsPos].o1 = o1;	
													pairs[pairsPos].o2 = o2;	
													pairsPos++;
													if (b1 < b2) {
														mp[{b1,b2}] = 1;
													} else {
														mp[{b2,b1}] = 1;
													}
												} else {
													//printf("MAPS NOT SAME b:%dV%d o:%dV%d\n", b1, b2, o1, o2);
												}

											}
										}
									}
								}
							}
						}
					}
				}

			}
		}
	}

	printf("PPPPPPPPPPPPPP %d\n", (int)mp.size());
	for (auto it = mp.begin(); it != mp.end(); it++) {
		pair one = it->first;
		printf("%d %d\n", one.first, one.second);

	} 
	printf("END PPPPPPPPPPPPPP\n");
	//for (int i = 0; i < beaconNum; i++) { printf("scanner: %d => %d %d %d\n", i, beacon[i].scannerx, beacon[i].scannery, beacon[i].scannerz);	}
	//int b1_1[] = {0, 1, 1, 4};
	//int b2_2[] = {1, 3, 4, 2};
	//             k l m n
	//int b1_11[] = {0,1,1,4}; //o1
	//int b2_22[] = {1,3,4,2}; //o2
	int b1_11[] = {0,  0,  0,  0,  0, 2,  18, 3,  8, 8, 12, 12, 16, 16, 20, 23, 23, 15, 20, 2, 1, 4, 4,  4,  4, 15, 5, 12, 6, 25, 16, 7, 7, 10, 10, 10, 16, 17, 17, 12, 26, 22};
	int b2_22[] = {2,  3,  4, 18, 27, 9,   9, 8, 12,16, 15, 28, 20, 23, 26, 25, 27, 16, 26, 1, 4, 6, 8, 19, 23,  5,28,  6,25, 15,  7,10,26, 17, 22, 23, 20, 27, 13, 11, 21, 24};
/*
14 29 ****
*/
/*
0 2
0 3
0 4
0 18
0 27
1 2
1 4
2 9
3 8
4 6
4 8
4 19
4 23
5 15
5 28
6 12
6 25
7 10
7 16
7 26
8 12
8 16
9 18
10 17
10 22
10 23
11 12
12 15
12 28
13 17
14 29
15 16
15 25
16 20
16 23
17 27
20 26
21 26
22 24
23 25
23 27
*/

	printf("pairsPos is %d\n", pairsPos);
	struct res_s {
		int one;
		int two;
		int three;
		int four;
		int five;
	};
	//struct res_s results[200]; int resultsPos = 0;
	lineIPos = 0;
//	for (int k = 0; k < pairsPos; k++) {
//		if (pairs[k].b1 == b1_11[0] && pairs[k].b2 == b2_22[0])  { // k= 0  1
//			for (int l = 0; l < pairsPos; l++) {
//				if (pairs[l].b1 == b1_11[1] && pairs[l].b2 == b2_22[1])  { // l 1 =  3
//					for (int m = 0; m < pairsPos; m++) {
//						if (pairs[m].b1 == b1_11[2] && pairs[m].b2 == b2_22[2])  { // m 1 =  4
//							for (int n = 0; n < pairsPos; n++) { 
//								if (pairs[n].b1 == b1_11[3] && pairs[n].b2 == b2_22[3])  { // n 4 2
//									if (pairs[k].o2 == pairs[l].o1 && pairs[k].o2 == pairs[l].o1 && pairs[l].o1 == pairs[m].o1 && pairs[m].o2 == pairs[n].o1 ) {
//										printf("%d %d %d %d %d\n", pairs[k].o1, pairs[l].o1, pairs[n].o2, pairs[l].o2, pairs[n].o1);
//										lineI[lineIPos][0] = pairs[k].o1;
//										lineI[lineIPos][1] = pairs[l].o1;
//										lineI[lineIPos][2] = pairs[n].o2;
//										lineI[lineIPos][3] = pairs[l].o2;
//										lineI[lineIPos][4] = pairs[n].o1;
//										lineIPos++;
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
	//printf("END data gathering..%d.\n", lineIPos); getchar();
	int count4 = 0;
	for (int A = 0; A < pairsPos; A++) {
	for (int B = 0; B < pairsPos; B++) {
	for (int C = 0; C < pairsPos; C++) {
	for (int D = 0; D < pairsPos; D++) {
	for (int E = 0; E < pairsPos; E++) {
	for (int F = 0; F < pairsPos; F++) {
	for (int G = 0; G < pairsPos; G++) {
	for (int H = 0; H < pairsPos; H++) {
	for (int I = 0; I < pairsPos; I++) {
	for (int J = 0; J < pairsPos; J++) {
	for (int K = 0; K < pairsPos; K++) {
	for (int L = 0; L < pairsPos; L++) {
	for (int M = 0; M < pairsPos; M++) {
	for (int N = 0; N < pairsPos; N++) {
	for (int O = 0; O < pairsPos; O++) {
	for (int P = 0; P < pairsPos; P++) {
	for (int Q = 0; Q < pairsPos; Q++) {
	for (int R = 0; R < pairsPos; R++) {
	for (int S = 0; S < pairsPos; S++) {
	for (int T = 0; T < pairsPos; T++) {
	for (int U = 0; U < pairsPos; U++) {
	for (int V = 0; V < pairsPos; V++) {
	for (int W = 0; W < pairsPos; W++) {
	for (int X = 0; X < pairsPos; X++) {
	for (int Y = 0; Y < pairsPos; Y++) {
	for (int Z = 0; Z < pairsPos; Z++) {
	for (int b = 0; b < pairsPos; b++) {
	for (int c = 0; c < pairsPos; c++) {
	for (int d = 0; d < pairsPos; d++) {
	for (int e = 0; e < pairsPos; e++) {
	for (int f = 0; f < pairsPos; f++) {
	for (int g = 0; g < pairsPos; g++) {
	for (int h = 0; h < pairsPos; h++) {
	for (int i = 0; i < pairsPos; i++) {
	for (int j = 0; j < pairsPos; j++) {
	for (int k = 0; k < pairsPos; k++) {
	for (int l = 0; l < pairsPos; l++) {
	for (int m = 0; m < pairsPos; m++) {
	for (int n = 0; n < pairsPos; n++) {
	for (int o = 0; o < pairsPos; o++) {
	for (int p = 0; p < pairsPos; p++) {
	for (int q = 0; q < pairsPos; q++) {
				if (pairs[A].b1 == b11_1[0] && pairs[A].b2 == b22_2[0]) {
				if (pairs[B].b1 == b11_1[1] && pairs[B].b2 == b22_2[1]) {
				if (pairs[C].b1 == b11_1[2] && pairs[C].b2 == b22_2[2]) {
				if (pairs[D].b1 == b11_1[3] && pairs[D].b2 == b22_2[3]) {
				if (pairs[E].b1 == b11_1[4] && pairs[E].b2 == b22_2[4]) {
				if (pairs[F].b1 == b11_1[5] && pairs[F].b2 == b22_2[5]) {
				if (pairs[G].b1 == b11_1[6] && pairs[G].b2 == b22_2[6]) {
				if (pairs[H].b1 == b11_1[7] && pairs[H].b2 == b22_2[7]) {
				if (pairs[I].b1 == b11_1[8] && pairs[I].b2 == b22_2[8]) {
				if (pairs[J].b1 == b11_1[9] && pairs[J].b2 == b22_2[9]) {
				if (pairs[K].b1 == b11_1[10] && pairs[K].b2 == b22_2[10]) {
				if (pairs[L].b1 == b11_1[11] && pairs[L].b2 == b22_2[11]) {
				if (pairs[M].b1 == b11_1[12] && pairs[M].b2 == b22_2[12]) {
				if (pairs[N].b1 == b11_1[13] && pairs[N].b2 == b22_2[13]) {
				if (pairs[O].b1 == b11_1[14] && pairs[O].b2 == b22_2[14]) {
				if (pairs[P].b1 == b11_1[15] && pairs[P].b2 == b22_2[15]) {
				if (pairs[Q].b1 == b11_1[16] && pairs[Q].b2 == b22_2[16]) {
				if (pairs[R].b1 == b11_1[17] && pairs[R].b2 == b22_2[17]) {
				if (pairs[S].b1 == b11_1[18] && pairs[S].b2 == b22_2[18]) {
				if (pairs[T].b1 == b11_1[19] && pairs[T].b2 == b22_2[19]) {
				if (pairs[U].b1 == b11_1[20] && pairs[U].b2 == b22_2[20]) {
				if (pairs[V].b1 == b11_1[21] && pairs[V].b2 == b22_2[21]) {
				if (pairs[W].b1 == b11_1[22] && pairs[W].b2 == b22_2[22]) {
				if (pairs[X].b1 == b11_1[23] && pairs[X].b2 == b22_2[23]) {
				if (pairs[Y].b1 == b11_1[24] && pairs[Y].b2 == b22_2[24]) {
				if (pairs[Z].b1 == b11_1[25] && pairs[Z].b2 == b22_2[25]) {
				if (pairs[b].b1 == b11_1[26] && pairs[b].b2 == b22_2[26]) {
				if (pairs[c].b1 == b11_1[27] && pairs[c].b2 == b22_2[27]) {
				if (pairs[d].b1 == b11_1[28] && pairs[d].b2 == b22_2[28]) {
				if (pairs[e].b1 == b11_1[39] && pairs[e].b2 == b22_2[29]) {
				if (pairs[f].b1 == b11_1[30] && pairs[f].b2 == b22_2[30]) {
				if (pairs[g].b1 == b11_1[31] && pairs[g].b2 == b22_2[31]) {
				if (pairs[h].b1 == b11_1[32] && pairs[h].b2 == b22_2[32]) {
				if (pairs[i].b1 == b11_1[33] && pairs[i].b2 == b22_2[33]) {
				if (pairs[j].b1 == b11_1[34] && pairs[j].b2 == b22_2[34]) {
				if (pairs[k].b1 == b11_1[35] && pairs[k].b2 == b22_2[35]) {
				if (pairs[l].b1 == b11_1[36] && pairs[l].b2 == b22_2[36]) {
				if (pairs[m].b1 == b11_1[37] && pairs[m].b2 == b22_2[37]) {
				if (pairs[n].b1 == b11_1[38] && pairs[n].b2 == b22_2[38]) {
				if (pairs[o].b1 == b11_1[39] && pairs[o].b2 == b22_2[39]) {
				if (pairs[p].b1 == b11_1[40] && pairs[p].b2 == b22_2[40]) {
				if (pairs[q].b1 == b11_1[41] && pairs[q].b2 == b22_2[41]) {
	//             A   B   C   D   E  F    G*  H   I  J  K   L    M  N   O   P   Q*  R*  S*  T U*  V  W   X  Y*  Z  b*  c  d  e   f   g  h  i    j   k  l   m   n   o   p   q
	int b11_1[] = {0,  0,  0,  0,  0, 2,  18, 3,  8, 8, 12, 12, 16, 16, 20, 23, 23, 15, 20, 2, 1, 4, 4,  4,  4, 15, 5, 12, 6, 25, 16, 7, 7, 10, 10, 10, 16, 17, 17, 12, 26, 22};
	int b22_2[] = {2,  3,  4, 18, 27, 9,   9, 8, 12,16, 15, 28, 20, 23, 26, 25, 27, 16, 26, 1, 4, 6, 8, 19, 23,  5,28,  6,25, 15,  7,10,26, 17, 22, 23, 20, 27, 13, 11, 21, 24};

					if (pairs[A].b2 == pairs[F].b1) {
					if (pairs[A].b2 == pairs[T].b1) {
					if (pairs[B].b2 == pairs[H].b1) {
					if (pairs[C].b2 == pairs[V].b1) {
					if (pairs[C].b2 == pairs[W].b1) {
					if (pairs[C].b2 == pairs[X].b1) {
					if (pairs[C].b2 == pairs[Y].b1) {
					if (pairs[D].b2 == pairs[G].b1) {
					if (pairs[F].b2 == pairs[F].b1) {
					if (pairs[H].b2 == pairs[I].b1) {
					if (pairs[H].b2 == pairs[J].b1) {
					if (pairs[I].b2 == pairs[K].b1) {
					if (pairs[I].b2 == pairs[L].b1) {
					if (pairs[I].b2 == pairs[c].b1) {
					if (pairs[I].b2 == pairs[o].b1) {
					if (pairs[J].b2 == pairs[M].b1) {
					if (pairs[J].b2 == pairs[N].b1) {
					if (pairs[J].b2 == pairs[f].b1) {
					if (pairs[J].b2 == pairs[l].b1) {
					if (pairs[K].b2 == pairs[R].b1) {
					if (pairs[K].b2 == pairs[Z].b1) { 
					if (pairs[M].b2 == pairs[O].b1) {
					if (pairs[M].b2 == pairs[S].b1) {
					if (pairs[N].b2 == pairs[P].b1) {
					if (pairs[N].b2 == pairs[Q].b1) {
					if (pairs[O].b2 == pairs[p].b1) {
					if (pairs[P].b2 == pairs[e].b1) {
					if (pairs[R].b2 == pairs[f].b1) {
					if (pairs[R].b2 == pairs[l].b1) {
					if (pairs[S].b2 == pairs[p].b1) {
					if (pairs[T].b2 == pairs[U].b1) {
					if (pairs[U].b2 == pairs[V].b1) {
					if (pairs[U].b2 == pairs[W].b1) {
					if (pairs[U].b2 == pairs[X].b1) {
					if (pairs[U].b2 == pairs[Y].b1) {
					if (pairs[Z].b2 == pairs[b].b1) {
					if (pairs[c].b2 == pairs[d].b1) {
					if (pairs[d].b2 == pairs[e].b1) {
					if (pairs[f].b2 == pairs[g].b1) {
					if (pairs[f].b2 == pairs[h].b1) {
					if (pairs[g].b2 == pairs[i].b1) {
					if (pairs[g].b2 == pairs[j].b1) {
					if (pairs[g].b2 == pairs[k].b1) {
					if (pairs[h].b2 == pairs[p].b1) {
					if (pairs[i].b2 == pairs[m].b1) {
					if (pairs[i].b2 == pairs[n].b1) {
						count4++;
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}
					}

				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}
				}

	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	printf("count4: %d\n", count4);
	exit(0);
	//             A   B   C   D   E  F    G  H   I  J  K   L    M  N   O   P   Q    R   S  T  U  V  W   X   Y  Z   b   c  d  e   f   g  h  i   j   k    l   m  n   o   p   q
	int b11_1[] = {0,  0,  0,  0,  0, 2,  18, 3,  8, 8, 12, 12, 16, 16, 20, 23, 23, 15, 20, 2, 1, 4, 4,  4,  4, 15, 5, 12, 6, 25, 16, 7, 7, 10, 10, 10, 16, 17, 17, 12, 26, 22};
	int b22_2[] = {2,  3,  4, 18, 27, 9,   9, 8, 12,16, 15, 28, 20, 23, 26, 25, 27, 16, 26, 1, 4, 6, 8, 19, 23,  5,28,  6,25, 15,  7,10,26, 17, 22, 23, 20, 27, 13, 11, 21, 24};
	int arPos = -1;

restart:
	arPos++;
	pairsPos = 0;
	//b1Q.push_back(b1);
	//////////////
	//if (f1 == 1) { next(var_orient); } else { f1 = 1; }
	allBPos = 0;

	//sets the first score...
	for (int two = 0; two < beacon[0].beaconPos; two++) {
		int found = 0;
		for (int z = 0; z < allBPos; z++) {
			if (allB[z].x == beacon[0].x[two][lineI[arPos][0]] + beacon[0].mapx &&
					allB[z].y == beacon[0].y[two][lineI[arPos][0]] + beacon[0].mapy &&
					allB[z].z == beacon[0].z[two][lineI[arPos][0]] + beacon[0].mapz)  {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			allB[allBPos].x = beacon[0].x[two][lineI[arPos][0]] + beacon[0].mapx;
			allB[allBPos].y = beacon[0].y[two][lineI[arPos][0]] + beacon[0].mapy;
			allB[allBPos].z = beacon[0].z[two][lineI[arPos][0]] + beacon[0].mapz;
			allBPos++;
		}
	}
	//printf("allBPos: %d\n", allBPos); getchar();
	for (int i = 0; i < beaconNum; i++) {
		for (int k = 0; k < 25; k++) {
			for (int j = 0; j < beacon[i].beaconPos-1; j++) {
				beacon[i].x[j][k] = beaconOrig[i].x[j][k];
				beacon[i].y[j][k] = beaconOrig[i].y[j][k];
				beacon[i].z[j][k] = beaconOrig[i].z[j][k];
			}
		}
	}
	beacon[0].scannerx = 0;
	beacon[0].scannery = 0;
	beacon[0].scannerz = 0;

	beacon[0].mapx = 0;
	beacon[0].mapy = 0;
	beacon[0].mapz = 0;

	beacon[0].orient = 0;

	for (int i = 1; i < beaconNum; i++) {
		beacon[i].scannerx = -999;
		beacon[i].scannery = -999;
		beacon[i].scannerz = -999;
	}


	//CONOR
	
	for (int b1_1Pos = 0; b1_1Pos < beaconNum-1; b1_1Pos++) {
		int b1 = b11_1[b1_1Pos];
		int b2 = b22_2[b1_1Pos];
		{
			//if (b1 == b2) {continue;}
			int found3 = 0;

			/*
			   for (int q1 = 0; q1 < pairsPos; q1++) {
			   if ((pairs[q1].b1 == b1 && pairs[q1].b2 == b2) || (pairs[q1].b2 == b1 && pairs[q1].b1 == b2)) {
			   found3 = 1; break;
			   }
			   }
			 */
			if (found3 == 1) {continue;}

			int o1;
			o1 = lineI[arPos][b1];
			{
				int o2;
				{
					o2 = lineI[arPos][b2];
					printf("b1_1Pos : %d\n", b1_1Pos);
					printf("b:[%d,%d] b1_1Pos: [%d] arPos:[%d] zero: %d %d %d %d %d o1,o2:[%d,%d]\n", b1, b2, b1_1Pos, arPos, lineI[arPos][0], lineI[arPos][1], lineI[arPos][2], lineI[arPos][3], lineI[arPos][4], o1, o2); getchar();
					{
						//printf("beacon [%d] v [%d] -- [%d] V [%d]\n", b1, b2, o1,o2); getchar();
						for (int p1b1 = 0; p1b1 < beacon[b1].beaconPos-1; p1b1++) {
							int most[100] = {0};
							int count = 0;
							for (int p2b1 =p1b1+1; p2b1 < beacon[b1].beaconPos; p2b1++) {
								for (int p1b2 = 0; p1b2 < beacon[b2].beaconPos-1; p1b2++) {
									for (int p2b2 = p1b2+1; p2b2 < beacon[b2].beaconPos; p2b2++) {

										if (beacon[b1].distxx[o1][p1b1][p2b1]  == beacon[b2].distxx[o2][p1b2][p2b2] &&
												beacon[b1].distyy[o1][p1b1][p2b1] == beacon[b2].distyy[o2][p1b2][p2b2] &&
												beacon[b1].distzz[o1][p1b1][p2b1] == beacon[b2].distzz[o2][p1b2][p2b2]) {
											tmpxyz[count].b1 = b1;
											tmpxyz[count].pos1 = p1b1;
											tmpxyz[count].pos_1 = p2b1;
											tmpxyz[count].o11 = o1;

											tmpxyz[count].b2 = b2;
											tmpxyz[count].pos2 = p1b2;
											tmpxyz[count].pos_2 = p2b2;
											tmpxyz[count].o22 = o2;

											count++;
											most[p1b2]++;

											printf("found [[count:%d]] b1:%d o1:%d p1b1:%d p2b1:%d V b2:%d o2:%d p1b2:%d p2b2:%d [%d V %d]\n", count, b1, o1, p1b1, p2b1, b2, o2, p1b2, p2b2, o1, o2);

											if (count == 11) {
												int max = 0;
												int maxI = -1;
												for (int i = 0; i < 30; i++) {
													if (most[i] > max) {max = most[i]; maxI = i;}
												}


												printf("COUNT11: maps: %d %d %d V %d %d %d\n", beacon[b1].scannerx, beacon[b1].scannery, beacon[b1].scannerz,
														beacon[b2].scannerx, beacon[b2].scannery, beacon[b2].scannerz); fflush(stdout);

												//printf("allBPos now %d\n", allBPos); fflush(stdout);
												for (int r = 0; r < 11; r++) {
													tmpxyz[r].b11 = b1;
													tmpxyz[r].o11 = o1;
													tmpxyz[r].b22 = b2;
													tmpxyz[r].o22 = o2;
													tmpxyz[r].p1 = tmpxyz[r].pos_1;
													tmpxyz[r].p2 = tmpxyz[r].pos_2 == maxI ? tmpxyz[r].pos2 : tmpxyz[r].pos_2;
												}
												for (int r = 0; r < 11; r++) {
													//printf("r:%d p1,p2 == %d,%d\n", r, tmpxyz[r].p1, tmpxyz[r].p2);
													tmpxyz[r].mapx = beacon[b1].x[tmpxyz[r].p1][o1] - beacon[b2].x[tmpxyz[r].p2][o2];
													tmpxyz[r].mapy = beacon[b1].y[tmpxyz[r].p1][o1] - beacon[b2].y[tmpxyz[r].p2][o2];
													tmpxyz[r].mapz = beacon[b1].z[tmpxyz[r].p1][o1] - beacon[b2].z[tmpxyz[r].p2][o2];
												}

												int found2 = 0;
												for (int r = 0; r < 11-1; r++) {
													if (tmpxyz[r].mapx == tmpxyz[r+1].mapx && tmpxyz[r].mapy == tmpxyz[r+1].mapy &&
															tmpxyz[r].mapz == tmpxyz[r+1].mapz) {
													} else {
														printf("first %d\n", r);
														found2 = 1;
														break;
													}
												}

												int xmain = beacon[b1].x[p1b1][o1] - beacon[b2].x[maxI][o2]; 
												int ymain = beacon[b1].y[p1b1][o1] - beacon[b2].y[maxI][o2];
												int zmain = beacon[b1].z[p1b1][o1] - beacon[b2].z[maxI][o2];
												if (found2 == 0) {
													printf("most maps same -- checking last one\n");
													if (xmain == tmpxyz[0].mapx && ymain == tmpxyz[0].mapy && zmain == tmpxyz[0].mapz) {
														found2 = 0;
													} else {
														found2 = 1;
													}
												}
												if (found2 == 0) {
													//beacon[b2].orient = o2;
													//printf("setting orient for beacon:%d to %d\n", b2, beacon[b2].orient); getchar();
													//printf("COUNT11: orient: %d V %d\n", o1, o2);

													//printf("MAPS all same\n");
													//printf("setting scanner for %d\n", b2);
													beacon[b2].scannerx = tmpxyz[0].mapx;
													beacon[b2].scannery = tmpxyz[0].mapy;
													beacon[b2].scannerz = tmpxyz[0].mapz;
													printf("SAME [[arPos:%d]] b:[%d,%d] map:[%d %d %d] o:[%d][%d]\n", arPos,
															b1, b2, tmpxyz[0].mapx, tmpxyz[0].mapy, tmpxyz[0].mapz, o1, o2);

													for (int one = 0; one < beacon[b2].beaconPos; one++) {
														int found = 0;
														for (int z = 0; z < allBPos; z++) {
															if (allB[z].x == beacon[b2].x[one][o2] + tmpxyz[0].mapx &&
																	allB[z].y == beacon[b2].y[one][o2] + tmpxyz[0].mapy &&
																	allB[z].z == beacon[b2].z[one][o2] + tmpxyz[0].mapz) {
																found = 1;
																break;
															}
														}
														if (found == 0) {
															allB[allBPos].x = beacon[b2].x[one][o2] + tmpxyz[0].mapx;
															allB[allBPos].y = beacon[b2].y[one][o2] + tmpxyz[0].mapy;
															allB[allBPos].z = beacon[b2].z[one][o2] + tmpxyz[0].mapz;
															//printf("adding %d %d %d map: %d %d %d\n", allB[allBPos].x, allB[allBPos].y, allB[allBPos].z,
															//		beacon[b2].mapx, beacon[b2].mapy, beacon[b2].mapz);
															allBPos++;
															beacon[b2].x[one][o2] = beacon[b2].x[one][o2] + tmpxyz[0].mapx;
															beacon[b2].y[one][o2] = beacon[b2].y[one][o2] + tmpxyz[0].mapy;
															beacon[b2].z[one][o2] = beacon[b2].z[one][o2] + tmpxyz[0].mapz;
														} else {
															beacon[b2].x[one][o2] = beacon[b2].x[one][o2] + tmpxyz[0].mapx;
															beacon[b2].y[one][o2] = beacon[b2].y[one][o2] + tmpxyz[0].mapy;
															beacon[b2].z[one][o2] = beacon[b2].z[one][o2] + tmpxyz[0].mapz;
														}
													}
													printf("allBPos: %d\n", allBPos);

													count = 0;
													//pairs[pairsPos].b1 = b1; pairs[pairsPos].b2 = b2; pairsPos++;
													goto start123;
												} else {
													printf("MAPS NOT SAME b:%dV%d o:%dV%d\n", b1, b2, o1, o2);
													goto end;											
												}

											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
start123:
		continue;

	}
end:
	/*
	   for (int i = 0; i < beaconNum; i++) {
	   printf("scanner: %d => %d %d %d\n", i, beacon[i].scannerx, beacon[i].scannery, beacon[i].scannerz);	
	   }
	 */
	int found4 = 0;
	for (int i = 0; i < beaconNum; i++) {
		if (beacon[i].scannerx == -999 && beacon[i].scannery == -999 && beacon[i].scannerz == -999) {
			found4 = 1;
			break;
		}
	}
	if (found4 == 0) {
		printf("good run**allBPos is %d \n", allBPos);
	}
	if (arPos+1 >= lineIPos) {
	} else {
		goto restart;
	}
	//if (strcmp(var_orient, "NNNNN") != 0) { //printf("going to restart...\n"); goto restart; }
	//printf("%s %d\n", var_orient, allBPos);
	printf("Thats a wrap\n"); fflush(stdout);

}


int numit(int pos) {
	/*
	   switch(var_orient[pos]) {
	   case '0':
	   case '1':
	   case '2':
	   case '3':
	   case '4':
	   case '5':
	   case '6':
	   case '7':
	   case '8':
	   case '9': return var_orient[pos] - 48;
	   case 'A':
	   case 'B':
	   case 'C':
	   case 'D':
	   case 'E':
	   case 'F':
	   case 'G':
	   case 'H':
	   case 'I':
	   case 'J':
	   case 'K':
	   case 'L':
	   case 'M':
	   case 'N': return var_orient[pos] - 55;
	   default:
	   perror("ERR numit"); exit(0);
	   }
	 */
	return 0;
}
void next(char *s) {

	//for(s+=10;*--s>89;)*s=48;*s+=*s-57?1:8;	
	//for(aS+=5;*--aS>77;)*aS=48;*aS+=*aS-57?1:8;	
	//worksfor10{for(s+=9;(*s+=*s-57?1:8)>90;*s--=48);}
	{for(s+=9;(*s+=*s-57?1:8)>78;*s--=48);}
	//for(as+=;(*as+=*as-57?1:8)>90;*as--=48);

	//aI++;
	//sprintf(aS, "%05d", aI);
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

//--- beacon 0 ---
//-880,-557,778

/*
   int distx1 = beacon[i].x
   int disty1
   int distz1
   for (int j = 1; j < 2; j++) {
   if (i == j) {continue;}
   for  (int k = 0; k < 25; k++) {
   int distx2 
   int disty2
   int distz2
   printf("%d %d %d -- ", beacon[i].x[j][k], beacon[i].y[j][k], beacon[i].z[j][k]);
   }
   }
   printf("\n");
   }
 */
