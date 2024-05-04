#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tot = 0;
#define SIZE 200
char line1[SIZE];
#define TIME 1000000
struct it2_s {
	long long posX;
	long long posY;
	long long posZ;

	long long velX;
	long long velY;
	long long velZ;
};
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
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.1\n"); fflush(stdout);

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

	long long origWhichMin = -1;
	int count = 0;
	for (int t = 1; t < TIME; t++) {
		long long min = 99999999;
		long long distO;
		int whichMin;
		long long velX, velY, velZ;
		long long posX, posY, posZ;
		for (int i = 0; i < leny; i++) {
			velX = itLast[i].velX + it[i].accX;
			velY = itLast[i].velY + it[i].accY;
			velZ = itLast[i].velZ + it[i].accZ;
			posX = itLast[i].posX + velX;
			posY = itLast[i].posY + velY; 
			posZ = itLast[i].posZ + velZ;
			//printf("%lld\n", posX);

			distO = abs(posX) + abs(posY) + abs(posZ);
			if (distO < min) {min = distO; whichMin = i;}
			itLast[i].velX = velX; itLast[i].velY = velY; itLast[i].velZ = velZ;
			itLast[i].posX = posX; itLast[i].posY = posY; itLast[i].posZ = posZ;
			
		}
		//printf("- whichMin: [ %d ]---\n", whichMin);
		if (whichMin == origWhichMin) {
			count++;
			if (count > 1000) {
				printf("Looks like it:- whichMin: [ %d ]---\n", whichMin);
			}
		} else {
			count = 0;
		}
		
		origWhichMin = whichMin;
	}
	printf("***tot is ^^ [%d]\n", tot);
	return 0;
}
