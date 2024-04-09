#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct dire {
    int N;
    int S;
    int E;
    int W;
};

struct xy {
    int x;
    int y;
};

void checkWereYouThereBefore(int curx, int cury);
struct xy xytracks[10000];
int pos = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day8.2\n"); fflush(stdin); fflush(stdout);

        char line1[1000];
        fgets(line1, 1000, a);
        fclose(a);
printf("line1 %s\n", line1);

int pointing = 0;
struct dire dirE = {0};
int nextisdigit = 0;
int currentNS = 0;
int currentEW = 0;
        for (int f = 0; f < 1000; f++)  {

             char b = line1[f];
             if (b == '\0' || b == '\n') {break;}
             if (b == 'R') {
                 pointing++;
		 pointing %= 4;
             } else if (b == 'L') {
                 pointing--;
		 if (pointing == -1) {pointing = 3;}
		 pointing %= 4;
             } else if (b == ',' || b == ' ') {/*ignore*/
             } else if (isdigit(b)) {
int inum = 0; char num[10]; num[0] = b; f++;
int q = 0; while (isdigit(line1[f])) {q++; num[q] = line1[f]; f++;}  
num[q+1] = '\0'; f--;
if ((inum = atoi(num)) > 10) {printf("%d\n", inum);}

                 int dig = atoi(num); /* - '0';*/
currentEW = dirE.E - dirE.W;
currentNS = dirE.N - dirE.S;
xytracks[pos].x = currentEW; xytracks[pos].y = currentNS;
printf("current point x,y: %d,%d\n", currentEW, currentNS);
	         if (pointing == 0) /*N*/ {
for (int d = 1; d <= dig; d++) {
    currentNS = dirE.N - dirE.S + d;
    checkWereYouThereBefore(currentEW, currentNS);
    xytracks[pos].x = currentEW; xytracks[pos].y = currentNS; pos++;
    printf("point x,y: %d,%d\n", currentEW, currentNS);
}
		    dirE.N += dig;
		 } else if (pointing == 2) /*S*/ {
for (int d = 1; d <= dig; d++) {
    currentNS = dirE.N -dirE.S - d;
    checkWereYouThereBefore(currentEW, currentNS); 
    xytracks[pos].x = currentEW; xytracks[pos].y = currentNS; pos++;
    printf("point x,y: %d,%d\n", currentEW, currentNS);
}
		    dirE.S += dig;
	         } else if (pointing == 1) /*E*/ {
for (int d = 1; d <= dig; d++) {
    currentEW = dirE.E -dirE.W + d;
    checkWereYouThereBefore(currentEW, currentNS);
    xytracks[pos].x = currentEW; xytracks[pos].y = currentNS; pos++;
    printf("point x,y: %d,%d\n", currentEW, currentNS);
}
		    dirE.E += dig;
	         } else if (pointing == 3) /*W*/ {
for (int d = 1; d <= dig; d++) {
    currentEW = dirE.E -dirE.W - d;
    checkWereYouThereBefore(currentEW, currentNS);
    xytracks[pos].x = currentEW; xytracks[pos].y = currentNS; pos++;
    printf("point x,y: %d,%d\n", currentEW, currentNS);
}
		    dirE.W += dig;
                 }
             }
        }

     int northsouth = dirE.N - dirE.S;
     int eastwest = dirE.E - dirE.W;
printf("pointing: %d\n", pointing);
printf("N: %d S: %d E: %d W:%d\n", dirE.N, dirE.S, dirE.E, dirE.W);
      printf("****ns: %d ew: %d*****\n", northsouth, eastwest);

}
void checkWereYouThereBefore(int curx, int cury) {
      for (int e = 0; e < pos; e++) {
	if (curx == xytracks[e].x && cury == xytracks[e].y) {
		printf("There before: %d, %d\n", curx, cury);
	        fflush(stdout);
		exit(0);
        }
      }

}
