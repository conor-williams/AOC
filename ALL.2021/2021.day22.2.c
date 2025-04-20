#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

//vector <tuple <int, int, int, int, int, int, bool>> vecAll;
struct T {
	int ar[4][3];
};
vector <tuple <struct T, bool>> vecAll;

FILE *a;
#define LINE 1000
#define getchar()


int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day 22 Part2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	char Sxfrom[10], Sxto[10], Syfrom[10], Syto[10], Szfrom[10], Szto[10];
	int xfrom, xto, yfrom, yto, zfrom, zto;

	bool off;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);

		off = false;
		int ret = sscanf(line1, "on x=%[^.]..%[^,],y=%[^.]..%[^,],z=%[^.]..%[^\0]", Sxfrom, Sxto, Syfrom, Syto, Szfrom, Szto);
		if (ret != 6) {
			off = true;
			sscanf(line1, "off x=%[^.]..%[^,],y=%[^.]..%[^,],z=%[^.]..%[^\0]", Sxfrom, Sxto, Syfrom, Syto, Szfrom, Szto);
		}
		printf("read %s %s %s %s %s %s\n", Sxfrom, Sxto, Syfrom, Syto, Szfrom, Szto);// getchar();
		xfrom = atoi(Sxfrom); xto = atoi(Sxto)+1;
		yfrom = atoi(Syfrom); yto = atoi(Syto)+1;
		zfrom = atoi(Szfrom); zto = atoi(Szto)+1;
		int tmp1[4][3] = {{xfrom, xto}, {yfrom, yto}, {zfrom, zto}};
		struct T pos_array;
		memcpy(pos_array.ar, tmp1, sizeof(tmp1));
		vecAll.push_back(make_tuple(pos_array, !off));
		leny++;
	}
	fclose(a);

	printf("vecAll.size() is %d\n", (int)vecAll.size());

	vector <tuple <struct T, bool>> done;
	done.push_back(vecAll.front());
	vecAll.erase(vecAll.begin());

	long long area = 0;
	{
		auto p_arr = get<0>(done[0]);
		if (get<1>(done[0]) == true) {
			//area += (long long)(abs(p_arr.ar[0][1]-p_arr.ar[0][0])+1) * (long long)(abs(p_arr.ar[1][1]-p_arr.ar[1][0])+1) * (long long)(abs(p_arr.ar[2][1]-p_arr.ar[2][0])+1);
			area += (long long)(abs(p_arr.ar[0][1]-p_arr.ar[0][0])) * (long long)(abs(p_arr.ar[1][1]-p_arr.ar[1][0])) * (long long)(abs(p_arr.ar[2][1]-p_arr.ar[2][0]));
		}
	}

	printf("area now %lld\n", area);
	vector <int> cors[4];
	int kkcounter = 0;
	for (auto tuA: vecAll) {
		printf("kkcounter: %d of %d\n", kkcounter, (int)vecAll.size());
		kkcounter++;
		///
		///intersect with all in done	
		auto p2 = get<0>(tuA);
		bool intersectionOffOnNew = get<1>(tuA);
		if (intersectionOffOnNew == true) {
			//area += (long long)(abs(p2.ar[0][0]-p2.ar[0][1])+1) * (long long)(abs(p2.ar[1][0]-p2.ar[1][1])+1) * (long long)(abs(p2.ar[2][0]-p2.ar[2][1])+1);
			area += (long long)(abs(p2.ar[0][0]-p2.ar[0][1])) * (long long)(abs(p2.ar[1][0]-p2.ar[1][1])) * (long long)(abs(p2.ar[2][0]-p2.ar[2][1]));
		}
		int nointer = 0;
		vector <tuple <struct T, bool>> shapes;
		for (auto tuD: done) {
			//intersect
			nointer = 0;
			auto p3 = get<0>(tuD);
			int intersectionSecondOffOn = get<1>(tuD);

			struct T inters;
			for (int ii = 0; ii < 3; ii++) {
				//p2 is the old list
				//p3 is the incoming new one
				if (p2.ar[ii][0] <= p3.ar[ii][0] && p2.ar[ii][1] <= p3.ar[ii][0]) {
					nointer = 1;
					goto end;
				} else if (p3.ar[ii][0] <= p2.ar[ii][0] && p3.ar[ii][1] <= p2.ar[ii][0]) {
					nointer = 1;
					goto end;
				} else if (p2.ar[ii][0] <= p3.ar[ii][0] && p2.ar[ii][1] <= p3.ar[ii][1]) {
					inters.ar[ii][0] = p3.ar[ii][0];
					inters.ar[ii][1] = p2.ar[ii][1];
				} else if (p3.ar[ii][0] <= p2.ar[ii][0] && p3.ar[ii][1] <= p2.ar[ii][1]) {
					inters.ar[ii][0] = p2.ar[ii][0];
					inters.ar[ii][1] = p3.ar[ii][1];
				} else if (p2.ar[ii][0] <= p3.ar[ii][0] && p3.ar[ii][1] <= p2.ar[ii][1]) {
					inters.ar[ii][0] = p3.ar[ii][0];
					inters.ar[ii][1] = p3.ar[ii][1];
				} else if (p3.ar[ii][0] <= p2.ar[ii][0] && p2.ar[ii][1] <= p3.ar[ii][1]) {
					inters.ar[ii][0] = p2.ar[ii][0];
					inters.ar[ii][1] = p2.ar[ii][1];
				} else {
					goto end;
				}
			}

			cors[0].clear(); cors[1].clear(); cors[2].clear();
			{ //max 4 xes, 4 yes 4 zes 
				for (int ii = 0; ii < 3; ii++) {
					for (int jj = 0; jj < 2; jj++) {
						if (p3.ar[ii][jj] != inters.ar[ii][jj]) {
							if (find(cors[ii].begin(), cors[ii].end(), p3.ar[ii][jj]) == cors[ii].end()) {cors[ii].push_back(p3.ar[ii][jj]);}
						}
						if (find(cors[ii].begin(), cors[ii].end(), inters.ar[ii][jj]) == cors[ii].end()) {cors[ii].push_back(inters.ar[ii][jj]);}
					}
					sort(cors[ii].begin(), cors[ii].end());
				}

			}
			//make all the shapes from the nearest x,y,z
			{
				for (int xx = 0; xx < (int)cors[0].size()-1; xx++) {
					int firstx = cors[0][xx];
					int secondx = cors[0][xx+1];
					for (int yy = 0; yy < (int)cors[1].size()-1; yy++) {
						int firsty = cors[1][yy];
						int secondy = cors[1][yy+1];
						for (int zz = 0; zz < (int)cors[2].size()-1; zz++) {
							int firstz = cors[2][zz];
							int secondz = cors[2][zz+1];

							if (intersectionOffOnNew == true && intersectionSecondOffOn == true) {
								if (firstx == inters.ar[0][0] && firsty == inters.ar[1][0] && firstz == inters.ar[2][0] &&
										secondx == inters.ar[0][1] && secondy == inters.ar[1][1] && secondz == inters.ar[2][1]) {
									//area -= (unsigned long long)(abs(secondx-firstx)+1) * (unsigned long long)(abs(secondy-firsty)+1) * (unsigned long long)(abs(secondz-firstz)+1);
									area -= (unsigned long long)(abs(secondx-firstx)) * (unsigned long long)(abs(secondy-firsty)) * (unsigned long long)(abs(secondz-firstz));
								} else {
									int poses[4][3] = {{firstx, secondx}, {firsty, secondy}, {firstz, secondz}};
									struct T tmp2;
									memcpy(tmp2.ar, poses, sizeof(poses));
									shapes.push_back({tmp2, intersectionSecondOffOn});
								}
							} else if (intersectionOffOnNew == false && intersectionSecondOffOn == true) {
								if (firstx == inters.ar[0][0] && firsty == inters.ar[1][0] && firstz == inters.ar[2][0] &&
										secondx == inters.ar[0][1] && secondy == inters.ar[1][1] && secondz == inters.ar[2][1]) {
									//area -= (long long)(abs(secondx-firstx)+1) * (long long)(abs(secondy-firsty)+1) * (long long)(abs(secondz-firstz)+1);
									area -= (long long)(abs(secondx-firstx)) * (long long)(abs(secondy-firsty)) * (long long)(abs(secondz-firstz));
								} else {
									int poses[4][3] = {{firstx, secondx}, {firsty, secondy}, {firstz, secondz}};
									struct T tmp2;
									memcpy(tmp2.ar, poses, sizeof(poses));
									shapes.push_back({tmp2, intersectionSecondOffOn});
								}
							} else {
								printf("ERR: never here\n"); exit(0);
							}
						}
					}
				}

			}
end:
			if (nointer == 1) {
				//printf("no intersection.... \n"); getchar();
				shapes.push_back(tuD);
			}
			continue;
		}
		if (get<1>(tuA) == true) {
			shapes.push_back(tuA);
		}
		done = shapes;
		shapes.clear();

		printf("done.size() is %d area:%lld\n", (int)done.size(), area); getchar();
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", area);
}
