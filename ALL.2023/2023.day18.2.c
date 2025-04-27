#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2023 day18 part2\n"
#undef _DEBUG_
long long tot;

#define GRIDX 100000000
#define GRIDY 100000000


struct instruction {
	char inst;
	long long nummoves;
};	
struct instruction instructionArray[1000];
int startx; int starty;
int Istartx; int Istarty;

typedef struct{
	long long x,y;
} point;

point pointSet[1000];
int numpoints;
long long perimeter;
void getpoints();
long long shoelace();
void setpoints();

long long shoelace(){
	long long leftSum = 0,rightSum = 0;
	//	printf("numpoints %d\n", numpoints); fflush(stdout);

	//printf("Point %d:%lld,%lld == Point 0: %lld,%lld\n", numpoints -1, pointSet[numpoints-1].x, pointSet[numpoints-1].y, pointSet[0].x, pointSet[0].y); //getchar();	
	pointSet[numpoints] = pointSet[0];
	for(int i=0; i<numpoints;i++){
		leftSum += (pointSet[i].x)*(pointSet[i+1].y);
		rightSum += (pointSet[i+1].x)*(pointSet[i].y);
	}
	return 0.5*fabs(leftSum - rightSum);
}


int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
	fflush(stdout); int fd = dup(1); close(1);

	char line1[220];
	startx = 15000001; starty = 9000000;
	Istartx = startx; Istarty = starty;

	while(1) 
	{
		fgets(line1, 200, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif

		//-------------------------
		//	lenx = GRIDX; leny = GRIDY;
#ifdef _DEBUG_
		printf("lenx: %d leny: %d\n", lenx, leny);
#endif
		char hexdist[10];
		int newinst;
		sscanf(line1, "%c %lld (#%c%c%c%c%c%d)", &instructionArray[leny].inst, &instructionArray[leny].nummoves, &hexdist[0], &hexdist[1], &hexdist[2], &hexdist[3], &hexdist[4], &newinst);
		hexdist[5] = '\0'; long long tmpdist = strtol(hexdist, NULL, 16);
		if (newinst == 0) {instructionArray[leny].inst = 'R';} else if (newinst == 1) {instructionArray[leny].inst = 'D';} else if (newinst == 2) {instructionArray[leny].inst = 'L';} else if (newinst == 3) {instructionArray[leny].inst = 'U';}
		instructionArray[leny].nummoves = tmpdist;
		//	printf("hexdist: %s decimal: %lld newinst: %d (%c, %lld)\n", hexdist, tmpdist, newinst, instructionArray[leny].inst, instructionArray[leny].nummoves);
		leny++;
	}
	getpoints();
	//setpoints();

	long long val = shoelace();
	printf("shoelace + pseudo perimeter %lld\n", val + (perimeter/2) +1);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", val + (perimeter/2) +1);
	//printf("shoelace + perimeter %lld\n", val + perimeter);
	//printf("shoelace without perimeter %lld\n", val);
	fclose(a); return 0;
} 

void setpoints() 
{
	numpoints = 4;
	pointSet[0].x = 0; pointSet[0].y = 0;
	pointSet[1].x = 5; pointSet[1].y = 0;
	pointSet[2].x = 5; pointSet[2].y = 5;
	pointSet[3].x = 0; pointSet[3].y = 5;

	/*
	   numpoints = 5;
	   pointSet[0].x = 3; pointSet[0].y = 4;
	   pointSet[1].x = 5; pointSet[1].y = 11;
	   pointSet[2].x = 12; pointSet[2].y = 8;
	   pointSet[3].x = 9; pointSet[3].y = 5;
	   pointSet[4].x = 5; pointSet[4].y = 6;
	   */
}

void getpoints()
{
	int Istartx = startx; int Istarty = starty;

	//    printf("INCOMING: startx, [%d] starty: [%d]\n", startx, starty);
	perimeter = 0;
	for (int k = 0; k < leny; k++) {
		struct instruction instr = instructionArray[k];
		//printf("Processing inst %c: %lld: ", instr.inst, instr.nummoves);
		switch (instr.inst) {
			case 'L':
				for (long long i = 1; i <= instr.nummoves; i++) {
					if (startx - 1 > -1) {startx--; perimeter++;
					} else {printf("hit the edge L\n"); getchar(); break;}
				} 
				break;
			case 'R':
				for (long long i = 1; i <= instr.nummoves; i++) {
					if (startx + 1 < GRIDX + Istartx) {startx++; perimeter++;
					} else {printf("hit the edge R\n"); getchar(); break;}
				} 
				break;
			case 'U':
				for (long long i = 1; i <= instr.nummoves; i++) {
					if (starty - 1 > -1) {starty--; perimeter++;
					} else {printf("hit the edge.. U \n"); getchar();break;}
				} 
				break;
			case 'D':
				for (long long i = 1; i <= instr.nummoves; i++) {
					if (starty + 1 < GRIDY +Istarty) {starty++; perimeter++;
					} else {printf("hit the edeg D\n"); getchar(); break;}
				} 
				break;
			default:
				printf("ERROR: Unknown instruction - getchar"); getchar();
				break;
		}
		//	printf("AFTER: startx, [%d] starty: [%d]\n", startx, starty);
		pointSet[k].x = startx; pointSet[k].y = starty;
		numpoints++;
	}
	//printf("numpoints ====== %d\n", numpoints);
	if (pointSet[0].x == pointSet[numpoints-1].x && pointSet[0].y == pointSet[numpoints-1].y) {
		numpoints--; //printf("ALL Good...\n");
	} else {
		printf("ERRORp - points dont match\n");
	}
}
