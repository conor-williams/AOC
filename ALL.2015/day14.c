#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <map>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2015 day14 part1\n"
#define _DEBUG_
int tot = 0;
struct deer {
	int num;
	char name[20];
	int speed;
	int t1;
	int rest;
};
map <string, struct deer> mp;
map <int, struct deer> mpB;
	
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[200];
	int dNum = 0;
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	
	char dName[20]; int speed; int t1; int rest;
	sscanf(line1, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", dName, &speed, &t1, &rest);
	string dN = dName;
	struct deer tmpD;
	tmpD.num = dNum;
	strcpy(tmpD.name , dName);
	tmpD.speed = speed;
	tmpD.t1 = t1;	
	tmpD.rest = rest;
	mp.insert({dN, tmpD}); 
	mpB.insert({dNum, tmpD}); 
	dNum++;
	leny++;
/*
Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.
*/
}
fclose(a);

	int maxDist = 0;
	int theTime = 2503;
	for (auto iter = mp.begin(); iter != mp.end(); iter++) {
		struct deer tmp = iter->second;
		int norm = tmp.t1 + tmp.rest; 
		int times = theTime / norm; 
		int dist = times * tmp.speed * tmp.t1;

		int extra = theTime % norm;

		if (extra < tmp.t1) {
			dist += tmp.speed*extra;
		} else if (extra > tmp.t1) {
			dist += tmp.speed*tmp.t1;
		}	
		printf("dist is %d\n", dist);
		if (dist > maxDist){maxDist = dist;}

	}

	dup2(fd, 1);
	printf("***max %d\n", maxDist);
}
