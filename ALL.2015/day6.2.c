#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2015 day6 part2\n"
#define _DEBUG_

int lights[1000][1000] = {0};
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[200];
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	int ret = 0;
	int inst = 0;
	int x1, y1, x2, y2;
	ret = sscanf(line1, "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2);
	inst = 1;
	if (ret != 4) {
		ret = sscanf(line1, "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2);
		inst = 2;
		if (ret != 4) {
			sscanf(line1, "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2);
			inst = 3;
		}
	}
	if (x1 > x2 || y1 > y2) {
		printf("ERROR"); exit(0);
	}
	for (int x = x1; x <= x2; x++) {
		for (int y = y1; y <= y2; y++) {
			if (inst == 1) {
				lights[y][x] += 1;
			} else if (inst == 2) {
				//lights[y][x] = lights[y][x] == 0 ? 1 : 0;
				lights[y][x] += 2;
			} else if (inst == 3) {
				lights[y][x] -= 1;
				if (lights[y][x] < 0) {lights[y][x] = 0;}
			}
		}
	}
	
}
int count = 0;
for (int x = 0; x < 1000; x++) {
	for (int y = 0; y < 1000; y++) {
		if (lights[y][x] > 0) {
			count += lights[y][x];
		}
	}
}
fclose(a);

	dup2(fd, 1);
printf("***count %d\n", count);
}
