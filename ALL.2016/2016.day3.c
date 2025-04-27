#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2016 day3 part1 \n"
#undef _DEBUG_
long tot;

#define GRIDX 100000000
#define GRIDY 100000000


struct instruction {
	char inst;
	long nummoves;
};	
struct instruction instructionArray[1000];
int startx; int starty;
int Istartx; int Istarty;

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[220];
        //char line2[220];
        //char line3[220];
	int valid = 0;
while(1) 
{
        fgets(line1, 200, a);
        //fgets(line2, 200, a);
        //fgets(line3, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
        
//-------------------------
	int num11, num21, num31;
	//int num12, num22, num32;
	//int num13, num23, num33;
	sscanf(line1, "%d %d %d\n", &num11, &num21, &num31);
	//sscanf(line2, "%d %d %d\n", &num12, &num22, &num32);
	//sscanf(line3, "%d %d %d\n", &num13, &num23, &num33);
	if (num11+num21 > num31 && num21+num31 > num11 && num11+num31 > num21) {
		valid++;
	}
	//if (num21+num22 > num23 && num22+num23 > num21 && num21+num23 > num22) {
	//	valid++;
	//}
	//if (num31+num32 > num33 && num32+num33 > num31 && num31+num33 > num32) {
	//	valid++;
	//}
    }

	fflush(stdout); dup2(fd, 1);
    printf("VALID %d\n", valid);
    fclose(a);
    return 0;

} 
