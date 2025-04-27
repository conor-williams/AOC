#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2015 day3 part2\n"
#define _DEBUG_
int tot;
struct xyHouse {
	int x;
	int y;
	int num;
};
struct xyHouse myxyHouses[10000];
int myxyHousesLen;
void writeit(int x, int y);

int main(int argc, char **argv)
{
	myxyHousesLen = 0;
	tot = 0;lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
       
        char line1[9000];
while(1) {
        fgets(line1, 9000, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
        leny++;
}
//elf
{
	int x = 0; int y = 0;
	writeit(x, y);
	for (int pos=0; pos < lenx; pos +=2) {
		printf("CHECKING [%c]\n", line1[pos]);
		switch(line1[pos]) {
			case '^':
				y--;
				break;
			case 'v':
				y++;
				break;
			case '>':
				x++;
				break;
			case '<':
				x--;
				break;
			default:
				printf("ERROR getchar getchar\n");
				break;
		}
		writeit(x, y);
	}
}
// santa
{
	int x = 0; int y = 0;
	writeit(x, y);
	for (int pos=1; pos < lenx; pos +=2) {
		printf("CHECKING [%c]\n", line1[pos]);
		switch(line1[pos]) {
			case '^':
				y--;
				break;
			case 'v':
				y++;
				break;
			case '>':
				x++;
				break;
			case '<':
				x--;
				break;
			default:
				printf("ERROR getchar getchar\n");
				break;
		}
		writeit(x, y);
	}
}

	fflush(stdout); dup2(fd, 1);
	printf("***tot %d\n", myxyHousesLen);


fclose(a);
}
void writeit(int x, int y)
{
	int found = 0;
	for (int i = 0; i < myxyHousesLen; i++) {
		if (myxyHouses[i].x == x && myxyHouses[i].y == y) {
			printf("FOUND %d, %d\n", x, y);
			found = 1;
			myxyHouses[i].num++;
		}
	}
	if (found == 0) {
		myxyHouses[myxyHousesLen].x = x;
		myxyHouses[myxyHousesLen].y = y;
		myxyHouses[myxyHousesLen].num = 1;
		printf("NOT FOUND adding: %d, %d\n", x, y );
		myxyHousesLen++;
	}
}
