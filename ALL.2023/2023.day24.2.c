#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/resource.h>

using  namespace std;
#define getchar()
void multi_intersection(int n, int **arrays, int *lengths, int *out);
void intersection(int arr1[], int arr2[], int m, int n, int *out);

struct line {
	char x[20];
	long long  Ix;
	char y[20];
	long long  Iy;
	char z[20];
	long long  Iz;
	char sx[20];
	long long  Isx;
	char sy[20];
	long long  Isy;
	char sz[20];
	long long  Isz;
};
#undef _DEBUG_
#define MAX_LINES 320
struct line l[MAX_LINES];
int leny;
void printall();
void intersect();
int tot = 0;
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("2024 Day24.2\n"); fflush(stdout);
	char line1[1000];
	struct rlimit limit;
        getrlimit (RLIMIT_STACK, &limit);
        printf ("\nStack Limit = %ld and %ld max\n", limit.rlim_cur, limit.rlim_max);
        if (limit.rlim_cur < 900000000) {printf("need to widen stack with -Wl,--stack,999777666\n"); exit(10);}


	int fd = dup(1); close(1);
	leny = 0;
	while (1) {

		fgets(line1, 1000, a); if (feof(a)) {break;}
		//		printf("line1 %s", line1); 
		sscanf(line1, "%[^,], %[^,], %s @ %[^,], %[^,], %s", l[leny].x, l[leny].y, l[leny].z, l[leny].sx, 
				l[leny].sy, l[leny].sz);
		l[leny].Ix = stoll(l[leny].x);
		l[leny].Iy = stoll(l[leny].y);
		l[leny].Iz = stoll(l[leny].z);
		l[leny].Isx = stoll(l[leny].sx);
		l[leny].Isy = stoll(l[leny].sy);
		l[leny].Isz = stoll(l[leny].sz);
		leny++;

	} //while
	fclose(a);
	printall();

	int nums[(5*leny)];
	for (int i = 0; i < (5*leny); i++) {
		nums[i] = i;
	}
	/*
	   for (int i = leny; i < (5*leny); i++) {
	   nums[i] = (5*leny)-i+leny-1;
	   }
	   for (int i = 0; i < (5*leny); i++) {
	//printf("nums %d is %d\n", i, nums[i]);
	} 
	*/

	struct Nxyz {long long x; long long y; long long z;};
	struct Nxyz next[(5*leny)][(5*leny)+1];
	for (int i = 0; i < leny; i++) {
		for (int j = 0; j < (5*leny)+1; j++) {
			next[i][j].x = l[i].Ix + j*l[i].Isx;
			next[i][j].y = l[i].Iy + j*l[i].Isy;
			next[i][j].z = l[i].Iz + j*l[i].Isz;
			//cout << "next " << next[i][j].x << "," << next[i][j].y << "," << next[i][j].z << " " << endl;  getchar();
		}
	}
	for (int i = leny; i < (5*leny); i++) {
		for (int j = 0; j < (5*leny)+1; j++) {
			next[i][j].x = 0;
			next[i][j].y = 0;
			next[i][j].z = 0;
		}
	}

	//sort(nums, nums+(5*leny));

	/*
	   for (int j = 0; j < leny; j++) {
	   for (int k = 0; k < leny; k++) {
	   cout << " " << next[nums[j]][k].x ;
	   }
	   cout << endl;
	   }
	   cout << endl;
	   */

	int potX[5][200];
	int potXpos[5] = {0};
	int lineX = 0;
	int potY[5][200];
	int potYpos[5] = {0};
	int lineY = 0;
	int potZ[200];
	int potZpos = 0;
	for (int i = 0; i < leny-1; i++) {
		for (int j = i+1; j < leny; j++) {
			if (l[i].Isx == l[j].Isx && l[i].Isy == l[j].Isy) {
				for (int z = -1000; z < 1000; z++) {
					if (abs(z) > 100) {
						if (abs(z-l[i].Isx) != 0) {
							long long xmove = abs((long long)l[i].Ix - (long long) l[j].Ix) % abs(z-l[i].Isx);
							if (xmove == 0) {potX[lineX][potXpos[lineX]] = z; potXpos[lineX]++;}
						}
					}
					if (abs(z) > 100) {
						if (abs(z-l[i].Isy) != 0) {
							long long ymove = abs((long long)l[i].Iy - (long long) l[j].Iy) % abs(z-l[i].Isy);
							if (ymove == 0) { potY[lineY][potYpos[lineY]] = z; potYpos[lineY]++; }
						}
					}
				}

				lineX++;
				lineY++;
			}

		}
	}

	printf("lineX is %d\n", lineX);
	printf("lineY is %d\n", lineY); 
	int outY[100] = {0};
	int outYPos =0;
	for (int i = 0; i < potYpos[0]; i++) {
		for (int j = 0; j < potYpos[1]; j++) {
			if (potY[0][i] == potY[1][j]) {
				int found = 0;
				for (int k = 0; k < outYPos; k++) {
					if (outY[k] ==  potY[0][i]) {found = 1; break;}
				}
				if (found == 0) {
					outY[outYPos] = potY[0][i];
					outYPos++;
				}
			}
		}
	}
	int outX[100] = {0};
	int outXPos =0;
	for (int i = 0; i < potXpos[0]; i++) {
		for (int j = 0; j < potXpos[1]; j++) {
			if (potX[0][i] == potX[1][j]) {
				int found = 0;
				for (int k = 0; k < outXPos; k++) {
					if (outX[k] ==  potX[0][i]) {found = 1; break;}
				}
				if (found == 0) {
					outX[outXPos] = potX[0][i];
					outXPos++;
				}
			}
		}
	}
	printf("intersectY: ");
	for (int i = 0; i < outYPos; i++) {
		printf(" %d \n", outY[i]);
	}
	printf("intersectX: ");
	for (int i = 0; i < outXPos; i++) {
		printf(" %d \n", outX[i]);
	}
	int  sameY[100] = {0};
	int sameYPos =0;
	int  sameX[100] = {0};
	int sameXPos =0;
	getchar();

	int interX[400][400];
	int interXpos[400] = {0};
	int interXposLine = 0;
	int interY[400][400];
	int interYpos[400] = {0};
	int interYposLine = 0;
	int interZ[400][400];
	int interZpos[400] = {0};
	int interZposLine = 0;
	for (int i = 0; i < leny-1; i++) {
		for (int j = i+1; j < leny; j++) {
			if (l[i].Isx ==  l[j].Isx) {
				for (int z = -1000; z < 1000; z++) {
					//if (abs(l[i].Isx) > 100 && abs(z) > 100) 
					if (z-l[i].Isx != 0) {
						long long xmove = ((long long)l[i].Ix - (long long) l[j].Ix) % abs(z-l[i].Isx);
						if (xmove == 0) {
							int found = 0;
							for (int q=0; q<interXpos[interXposLine]; q++) {
								if (interX[interXposLine][q] == z) {
									found =  1; break;
								}
							}
							if (found == 0) {
								interX[interXposLine][interXpos[interXposLine]] = z; 
								interXpos[interXposLine]++;
							}
						}
					}

				}
				interXposLine++;
			}
			if (l[i].Isy ==  l[j].Isy) {
				for (int y = -1000; y < 1000; y++) {
					//if (abs(l[i].Isx) > 100 && abs(y) > 100) 
					if (y-l[i].Isy != 0) {
						long long ymove = ((long long)l[i].Iy - (long long) l[j].Iy) % abs(y-l[i].Isy);
						if (ymove == 0) {
							int found = 0;
							for (int q=0; q<interYpos[interYposLine]; q++) {
								if (interY[interYposLine][q] == y) {
									found =  1; break;
								}
							}
							if (found == 0) {
								interY[interYposLine][interYpos[interYposLine]] = y; 
								interYpos[interYposLine]++;
							}
						}
					}

				}
				interYposLine++;
			}
			if (l[i].Isz ==  l[j].Isz) {
				for (int z = -1000; z < 1000; z++) {
					//if (abs(l[i].Isx) > 100 && abs(z) > 100) 
					if (z-l[i].Isz != 0) {
						long long zmove = ((long long)l[i].Iz - (long long) l[j].Iz) % abs(z-l[i].Isz);
						if (zmove == 0) {
							int found = 0;
							for (int q=0; q<interZpos[interZposLine]; q++) {
								if (interZ[interZposLine][q] == z) {
									found =  1; break;
								}
							}
							if (found == 0) {
								interZ[interZposLine][interZpos[interZposLine]] = z; 
								interZpos[interZposLine]++;
							}
						}
					}

				}
				interZposLine++;
			}
		}
	}

	int outX2[100] = {0};
	int outX2Pos =0;

	printf("interXposLine: %d ", interXposLine);
	printf("interYposLine: %d ", interYposLine);
	printf("interZposLine: %d ", interZposLine);
	printf("\n");
	int counter = 0;
	for (int i = 0; i < interXposLine; i++) {
		for (int j = 0; j < interXpos[i]; j++) {
			if (interX[i][j] == 214) {
				counter++;
			}
		}
	}
	printf("counterX is %d\n", counter);
	int counterY = 0;
	for (int i = 0; i < interYposLine; i++) {
		for (int j = 0; j < interYpos[i]; j++) {
			if (interY[i][j] == -168) {
				counterY++;
			}
		}
	}
	printf("counterY is %d\n", counterY);
	int counterZ = 0;
	for (int i = 0; i < interZposLine; i++) {
		for (int j = 0; j < interZpos[i]; j++) {
			if (interZ[i][j] == 249) {
				counterZ++;
			}
		}
	}
	printf("counterZ is %d\n", counterZ);
	getchar();
	printf("before X L1: ");
	for (int i = 0; i < interXpos[0]; i++) {
		printf(":%d ", interX[0][i]);
	}
	printf("\n");
	printf("before X L2: ");
	for (int i = 0; i < interXpos[1]; i++) {
		printf(":%d ", interX[1][i]);
	}
	printf("\n");
	printf("before Y L1: ");
	for (int i = 0; i < interYpos[0]; i++) {
		printf(":%d ", interY[0][i]);
	}
	printf("\n");
	printf("before Y L2: ");
	for (int i = 0; i < interYpos[1]; i++) {
		printf(":%d ", interY[1][i]);
	}
	printf("\n");

	{
		int l1 = 0;
		for (int l2 = 1; l2 < interZposLine; l2++) {
			for (int z1=0; z1 < interZpos[l1]; z1++) {
				if (interZ[l1][z1] == 0) {continue;}
				int found = 0;
				for (int z2=0; z2 < interZpos[l2]; z2++) {
					if (interZ[l1][z1] == interZ[l2][z2]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					interZ[l1][z1] = 0;
					break;
				}
			}	
		}

	}
	int cZ = 0;
	for (int i = 0; i < interZpos[0]; i++) {
		if (interZ[0][i] != 0) {
			printf("common Z : %d\n", interZ[0][i]);
			cZ = interZ[0][i];
		}
	}
	{
		int l1 = 0;
		for (int l2 = 1; l2 < interXposLine; l2++) {
			for (int x1=0; x1 < interXpos[l1]; x1++) {
				if (interX[l1][x1] == 0) {continue;}
				int found = 0;
				for (int x2=0; x2 < interXpos[l2]; x2++) {
					if (interX[l1][x1] == interX[l2][x2]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					interX[l1][x1] = 0;
					break;
				}
			}	
		}

	}

	int cX = 0;
	for (int i = 0; i < interXpos[0]; i++) {
		if (interX[0][i] != 0) {
			printf("common X : %d\n", interX[0][i]);
			cX = interX[0][i];
		}
	}

	{
		int l1 = 0;
		for (int l2 = 1; l2 < interYposLine; l2++) {
			for (int x1=0; x1 < interYpos[l1]; x1++) {
				if (interY[l1][x1] == 0) {continue;}
				int found = 0;
				for (int x2=0; x2 < interYpos[l2]; x2++) {
					if (interY[l1][x1] == interY[l2][x2]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					interY[l1][x1] = 0;
					break;
				}
			}	
		}

	}
	int cY;
	for (int i = 0; i < interYpos[0]; i++) {
		if (interY[0][i] != 0) {
			printf("common Y : %d\n", interY[0][i]);
			cY = interY[0][i];
		}
	}
	int ind1 = -1;
	int ind2 = -1;
	int ind3 = -1;
	long long Xt1Mt2;
	long long Xt1Mt3;
	long long Xt2Pt3;
	int b = 0;
	for (int i = 0; i < leny-1; i++) {
		for (int j = i+1; j < leny; j++) {
			for (int k = j+1; k < leny; k++) {
				if (l[i].Isx ==  l[j].Isx && l[i].Isx == l[k].Isx) {
					printf("found...\n");
					//t1t2 = ((long long)l[i].Ix - (long long) l[j].Ix) / abs(cX-l[i].Isx);
					ind1 = i; ind2 = j; ind3 = k; goto end;
					//printf("t1t2 is %lld\n", t1t2);
					//conor
				}
			}
		}
	}
end:
	printf("ind1: %d ind2: %d ind3: %d\n", ind1, ind2, ind3);
	printf("mod1 %llu\n", ((long long)l[ind1].Ix - (long long) l[ind2].Ix) % (cX-l[ind1].Isx));
	printf("mod2 %llu\n", ((long long)l[ind1].Ix - (long long) l[ind3].Ix) % (cX-l[ind1].Isx));
	printf("mod3 %llu\n", ((long long)l[ind2].Ix - (long long) l[ind3].Ix) % (cX-l[ind2].Isx));
	Xt1Mt2 = ((long long)l[ind1].Ix - (long long) l[ind2].Ix) / (cX-l[ind1].Isx);
	Xt1Mt3 = ((long long)l[ind1].Ix - (long long) l[ind3].Ix) / (cX-l[ind1].Isx);
	Xt2Pt3 = ((long long)l[ind2].Ix - (long long) l[ind3].Ix) / (cX-l[ind2].Isx);
	//	if (Xt1Mt2 == Xt1Mt3-Xt2Pt3) {printf("AYE\n");}
	long long Xt3 = (long long) Xt1Mt2 - Xt1Mt3 + Xt2Pt3 / 2 ;
	printf("Xt3: %lld\n", Xt3);

	long long stX = l[ind3].Ix + Xt3*l[ind3].Isx - Xt3*cX;
	//printf("stX: %lld\n", stX);

	/////////////////////////////////////////////////////////////
	double q2 = l[1].Isx - cX;
	double q1 = l[1].Isy - cY;
	double q4 = l[2].Isx - cX;
	double q3 = l[2].Isy - cY;
	double q5 = l[2].Ix - l[1].Ix;
	double B = (double)(q4*q1)/(double)(q2*q3);
	double B2 = (double)(q5*q1)/(double)q2;

	double Yst = (double)(l[1].Iy - B*l[2].Iy +B2) / (double) (1-B);
	printf("Yst: %F\n", Yst);


	double Xst = (double)((Yst - l[1].Iy)*(l[1].Isx-cX))/(double)(l[1].Isy - cY) + l[1].Ix;
	printf("Xst: %F\n", Xst);
	double Zst = (double)((Yst - l[1].Iy)*(l[1].Isz-cZ))/(double)(l[1].Isy - cY) + l[1].Iz;
	printf("Zst: %F\n", Zst);


	printf("\n****tot: %lld\n", (long long)Xst+(long long)Yst+(long long)Zst);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", (long long)Xst+(long long)Yst+(long long)Zst);
	/*
	   for (int i = 0; i < leny-1; i++) {
	   for (int j = i+1; j < leny; j++) {
	   if (l[i].Isx ==  l[j].Isx && !(l[i].Isx == l[j].Isx && l[i].Isy == l[j].Isy)) {
	   for (int z = -1000; z < 1000; z++) {
	   if (abs(l[i].Isx) > 100 && abs(z) > 100) {
	   if (z-l[i].Isx != 0) {
	   long long xmove = ((long long)l[i].Ix - (long long) l[j].Ix) % abs(z-l[i].Isx);
	   if (xmove == 0) {
	   for (int i=0; i<outXPos; i++) {
	   if (outX[i] == z) {
	   int found = 0;
	   for (int q=0; q < sameXPos; q++) {
	   if (sameX[q] == outX[i]) {found = 1; break;}
	   }
	   if (found == 0) {
	   sameX[sameXPos] = z; sameXPos++;
	   }
	//printf("X:i(z) is %d\n", z);
	} else {
	//printf("New X is %d\n", z);
	}
	}
	}
	}
	}
	}
	}
	if (l[i].Isy ==  l[j].Isy && !(l[i].Isx == l[j].Isx && l[i].Isy == l[j].Isy)) {
	for (int z = -1000; z < 1000; z++) {
	if (abs(l[i].Isy) > 100 && abs(z) > 100) {
	if (z-l[i].Isy != 0) {
	long long ymove = ((long long)l[i].Iy - (long long) l[j].Iy) % abs(z-l[i].Isy);
	if (ymove == 0) {
	for (int i=0; i<outYPos; i++) {
	if (outY[i] == z) {
	int found = 0;
	for (int q=0; q < sameYPos; q++) {
	if (sameY[q] == outY[i]) {found = 1; break;}
	}
	if (found == 0) {
	sameY[sameYPos] = z; sameYPos++;
	}
	//printf("Y:i(z) is %d\n", z);
	} else {
	//printf("New Y is %d\n", z);
	}
	}
	}
	}

	if (z-l[i].Isz != 0) {
	long long zmove = ((long long)l[i].Iz - (long long) l[j].Iz) % abs(l[i].Isz - z);
	if (zmove == 0) {
	for (int i=0; i<potZpos; i++) {
	if (potZ[i] == z) {
	//printf("Z:i(z) is %d\n", z);
	} else {
	potZ[potZpos] = z;
	potZpos++;
	//printf("Z: i(z) %d\n",z);
	}
	}
	}
	}

	}
	}
	}
	}
	}
	*/

		/*
		   printf("SameY:");
		   for (int i = 0; i < sameYPos; i++) {
		   printf(" %d \n", sameY[i]);
		   }
		   cout << endl;
		   getchar();
		   printf("SameX:");
		   for (int i = 0; i < sameXPos; i++) {
		   printf(" %d \n", sameX[i]);
		   }
		   cout << endl;
		   getchar();
		   */
		/*
		   while (1) {
		   for (int i = 0; i < leny-1; i++) {
		   for (int j = 0; j < leny-i-1; j++) {
		   if (next[j][j].x <= next[j+1][j+1].x) {
		   cout << "less - swapping..." << next[j][j].x << "with " << next[j+1][j+1].x << endl;
		   for (int k = 0; k < leny; k++) {
		   long long tmp = next[j+1][k].x;
		   next[j+1][k].x = next[j][k].x;
		   next[j][k].x = tmp;
		   }
		   }
		   }
		   }

		   for (int j = 0; j < leny; j++) {
		   for (int k = 0; k < leny; k++) {
		   cout << " " << next[nums[j]][k].x ;
		   }
		   cout << endl;
		   }
		   cout << "getchar " << endl;
		   getchar();
		   }
		   */
		//printf("fin.new..\n");
		exit(0);
	/*
	   struct Nxyz diffA[(5*leny)];
	   do
	   {
	   printf("with END: %d\n", END);
	   int xval = 0, yval = 0, zval = 0;
	   int lastProper = 0; int nogood = 0;
	   do {
	   for (int i = leny; i < leny+END+1; i++) {
	   for (int j = 0; j < (leny+END)+2; j++) {
	   next[i][j].x = 0; next[i][j].y = 0; next[i][j].z = 0;
	   }
	   diffA[i].x = 0; diffA[i].y = 0; diffA[i].z = 0;
	   }

	   xval = 0; yval = 0; zval = 0;
	   lastProper = 0; nogood = 0;
	   for (int i = 0; i < leny+END+1; i++) {
	   int nP = 0;
	   while (next[nums[i+1+nP]][i].x - next[nums[i+1+nP]][i+1].x == 0) {
	   nP++;
	   if (i+1+nP > (leny+END+1)) {break;}
	   }

	   if (nP > 0) {
	   if (i+nP+1 > (leny+END+1)) {break;}
	   xval = (next[nums[i]][i+1].x - next[nums[i+nP+1]][i+nP+2].x)/(nP+1);
	   yval = (next[nums[i]][i+1].y - next[nums[i+nP+1]][i+nP+2].y)/(nP+1);
	   zval = (next[nums[i]][i+1].z - next[nums[i+nP+1]][i+nP+2].z)/(nP+1);
	   diffA[i].x = xval;
	   diffA[i].y = yval;	
	   diffA[i].z = zval;	
	   for (int l = 0; l < nP; l++) {
	   next[nums[i+l+1]][i+l+2].x = next[nums[i]][i+1].x - diffA[i].x;
	   next[nums[i+l+1]][i+l+2].y = next[nums[i]][i+1].y - diffA[i].y;
	   next[nums[i+l+1]][i+l+2].z = next[nums[i]][i+1].z - diffA[i].z;
	   }
	   continue;
	   }
	   lastProper = i;

	   xval = next[nums[i]][i+1].x - next[nums[i+1]][i+2].x;
	   yval = next[nums[i]][i+1].y - next[nums[i+1]][i+2].y;
	   zval = next[nums[i]][i+1].z - next[nums[i+1]][i+2].z;

	   diffA[i].x = xval;
	   diffA[i].y = yval;	
	   diffA[i].z = zval;	

	   for (int k = i; k <= lastProper; k++) {
	   if (diffA[k].x == diffA[0].x && diffA[k].y==diffA[0].y && diffA[k].z==diffA[0].z) {
	   continue;
	   } else {
	   nogood = 1;
	   break;
	   }

	   }
	   if (nogood == 1) {break;}
	   }
	   if (nogood == 0) {
	   for (int k = 0; k <= lastProper; k++) {
	   if (diffA[k].x == diffA[0].x && diffA[k].y==diffA[0].y && diffA[k].z==diffA[0].z) {
	   if (k==lastProper-1) {
	   cout << "Total match..." << endl;
	   for (int i = 0; i < (5*leny); i++) {
	   cout << nums[i] << ",";		
	   }
	   cout << endl;
	   printf("next[nums[0]][1].x is %lld\n", next[nums[0]][1].x); 
	   printf("next[nums[0]][1].y is %lld\n", next[nums[0]][1].y); 
	printf("next[nums[0]][1].z is %lld\n", next[nums[0]][1].z); 
	long long tot = next[nums[0]][1].x + next[nums[0]][1].y + next[nums[0]][1].z + diffA[0].x + diffA[0].y + diffA[0].z; 
	cout << "Slope: " << diffA[0].x << "," << diffA[0].y << "," << diffA[0].z << endl;
	cout << "Tot: " << tot << " ***" << endl;
	getchar();
	if (tot == 47 && diffA[0].x == 3 && diffA[0].y == -1 && diffA[0].z==-2) { getchar(); }
}
} else {
	//cout << "no match..." << k << ": " << leny<< endl; getchar();
	break;
}
}
}
} while (next_permutation(nums, nums+(leny+END)));
END++;

} while (END < (5*leny)-leny);
*/

printf("fin...\n");
}
/*
   void intersection(int arr1[], int arr2[], int m, int n, int *out)
   {
   int i = 0, j = 0;
   while(i < m && j < n)
   {
   if(arr1[i] < arr2[j])
   i++;
   else if(arr2[j] < arr1[i])
   j++;
   else 
   {
 *out++ = arr2[j++];
 i++;
 }
 }
 }

 void multi_intersection(int n, int **arrays, int *lengths, int *out) 
 {
 if (n == 2) {
 intersection(arrays[0], arrays[1], lengths[0], lengths[1], out);
 } else if (n == 1) {
 memcpy(out, arrays[0], lengths[0] * sizeof (int));
 } else {
 int *buf[2];
 int len[2] = { INT_MAX, INT_MAX };
 int i;
 for (i = 0; i < n; ++i) {
 int which = i < n / 2;
 if (lengths[i] < len[which]) len[which] = lengths[i];
 }
 buf[0] = malloc(len[0] * sizeof (int));
 buf[1] = malloc(len[1] * sizeof (int));

 multi_intersection(n / 2, arrays, lengths, buf[0]);
 multi_intersection(n - n / 2, arrays + n / 2, lengths + n / 2, buf[1]);

 intersection(buf[0], buf[1], len, out);

 free(buf[0]);
 free(buf[1]);
 }
 }
 */
void printall() {

	for (int i = 0; i < leny; i++ ) {
		printf("%lld %lld %lld @ %lld %lld %lld\n", l[i].Ix, l[i].Iy, l[i].Iz, l[i].Isx, l[i].Isy, l[i].Isz);
	}
	printf("total l %d\n", leny);
}
