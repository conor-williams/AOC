#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
struct line {
	char x[20];
	double Ix;
	char y[20];
	double Iy;
	char z[20];
	double Iz;
	char sx[20];
	double Isx;
	char sy[20];
	double Isy;
	char sz[20];
	double Isz;
	double slopexy;
	double cxy;
};
#define MAX_LINES 320
struct line l[MAX_LINES];
int leny;
void printall();
void intersect();
int tot = 0;
int ans123 =0;
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("		2023 Day24.1\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	leny = 0;
	while (1) {

		fgets(line1, 1000, a); if (feof(a)) {break;}
		//		printf("line1 %s", line1); 
		sscanf(line1, "%[^,], %[^,], %s @ %[^,], %[^,], %s", l[leny].x, l[leny].y, l[leny].z, l[leny].sx, 
				l[leny].sy, l[leny].sz);
		char *p;
		l[leny].Ix = strtod(l[leny].x, &p);
		l[leny].Iy = strtod(l[leny].y, &p);
		l[leny].Iz = strtod(l[leny].z, &p);
		l[leny].Isx = strtod(l[leny].sx, &p);
		l[leny].Isy = strtod(l[leny].sy, &p);
		l[leny].Isz = strtod(l[leny].sz, &p);
		l[leny].slopexy = (double)((double)l[leny].Isy/(double)l[leny].Isx);
		l[leny].cxy = (double)l[leny].Iy - (double)((double)l[leny].slopexy*(double)l[leny].Ix);
		leny++;

	} //while
	fclose(a);
	printall();

	intersect();


	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", ans123);
}
void intersect() {

	tot = 0;
	//y = mx +c ; c = y/mx; x = y-c/m
	for (int i = 0; i < leny-1; i++ ) {
		for (int sec = i+1; sec < leny; sec++) {
			if (l[i].slopexy != l[sec].slopexy) {
				//printf("intersect [%d] with [%d]\n", i, sec);
				int ignore = 0;
				double interX =  (double)(l[sec].cxy - l[i].cxy) / (double)(l[i].slopexy - l[sec].slopexy);
				double interY =  (interX*l[i].slopexy) + (double)l[i].cxy;
				printf("%d V %d: inter %f, %f\n", i, sec, interX, interY);
				printf("comparing %f v %f,%f\n", l[i].Isx, interX, l[i].Ix); 
				if (interX == l[i].Ix) {printf("same getchar"); getchar(); }
				if (interX == l[sec].Ix) {printf("same getchar"); getchar(); }
				if (interY == l[i].Iy) {printf("same getchar"); getchar(); }
				if (interY == l[sec].Iy) {printf("same getchar"); getchar(); }
				if (l[i].Isx < 0 && interX > l[i].Ix)  {ignore = 1;}
				if (l[i].Isx > 0 && interX < l[i].Ix)  {ignore = 1;}
				if (l[sec].Isx < 0 && interX > l[sec].Ix)  {ignore = 1;}
				if (l[sec].Isx > 0 && interX < l[sec].Ix)  {ignore = 1;}

				if (l[i].Isy < 0 && interY > l[i].Iy)  {ignore = 1;}
				if (l[i].Isy > 0 && interY < l[i].Iy)  {ignore = 1;}
				if (l[sec].Isy < 0 && interY > l[sec].Iy)  {ignore = 1;}
				if (l[sec].Isy > 0 && interY < l[sec].Iy)  {ignore = 1;}
				if (ignore == 0 && interX >= 200000000000000 && interX <= 400000000000000 &&
						interY >= 200000000000000 && interY <= 400000000000000) {
					tot++;
				}
				/*
				   if (ignore == 0 && interX >= 7 && interX <= 27 &&
				   interY >= 7 && interY <= 27) {
				   tot++;
				   }
				   */
			} else {
				printf("intersect [%d] with [%d] PARALLEL ignoring\n", i, sec);
			}
		}
	}
	printf("total lines %d\n", leny);
	printf("--------tot %d------\n", tot); fflush(stdout);
	ans123 = tot;
}
void printall() {

	for (int i = 0; i < leny; i++ ) {
		printf("%f %f @ %f %f: %f %f\n", l[i].Ix, l[i].Iy, l[i].Isx, l[i].Isy, l[i].slopexy, l[i].cxy);
	}
	printf("total l %d\n", leny);

}
