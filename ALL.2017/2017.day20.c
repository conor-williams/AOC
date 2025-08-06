#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 200
char line1[SIZE];
#define TIME 1000000
struct it_s {
	long long posX;
	long long posY;
	long long posZ;

	long long velX;
	long long velY;
	long long velZ;

	long long accX;
	long long accY;
	long long accZ;
};

struct it_s it[1001];
struct it_s itLast[1001];
//#define SZ 1000
//struct it2_s itPos[SZ][1001];
int whichMinOverall;
int main(int argc, char **argv)
{
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2017 Day20.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int leny = 0;
	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("line1 %s\n", line1);

		sscanf(line1, "p=<%lld,%lld,%lld>, v=<%lld,%lld,%lld>, a=<%lld,%lld,%lld>",
				&it[leny].posX, &it[leny].posY, &it[leny].posZ, 
				&it[leny].velX, &it[leny].velY, &it[leny].velZ, 
				&it[leny].accX, &it[leny].accY, &it[leny].accZ);
		leny++;
	}
	fclose(a);
	for (int i = 0; i < leny; i++) {
		itLast[i].posX = it[i].posX;
		itLast[i].posY = it[i].posY;
		itLast[i].posZ = it[i].posZ;
		itLast[i].velX = it[i].velX;
		itLast[i].velY = it[i].velY;
		itLast[i].velZ = it[i].velZ;

		//itPos[0][i].distO = abs(itPos[0][i].posX) + 
		//		abs(itPos[0][i].posY) +
		//		abs(itPos[0][i].posZ);
	}

	int www = 0;
	int wwwPrev = -1;
	int count2 = 0;
	for (int zz = 1; ; zz++) {
		long min2 = LONG_MAX;
		long dMan = 0;
		for (int i = 0; i < leny; i++) {
			long dX = ((it[i].velX * (TIME * zz)) + (it[i].accX * (long)pow((TIME*zz), 2)) /2) + it[i].posX;
			long dY = ((it[i].velY * (TIME * zz)) + (it[i].accY * (long)pow((TIME*zz), 2)) /2) + it[i].posY;
			long dZ = ((it[i].velZ * (TIME * zz)) + (it[i].accZ * (long)pow((TIME*zz), 2)) /2) + it[i].posZ;
			dMan = abs(dX) + abs(dY) + abs(dZ);
			if (dMan < min2) {min2 = dMan; www = i; }
		}
		if (wwwPrev == www) {
			count2++;
		} else {
			count2 = 0;
		}
		if (count2 == 100) {
			break;
		}
		wwwPrev = www;
	}


	printf("***tot is ^^ [%d]\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", www);
	return 0;
}
