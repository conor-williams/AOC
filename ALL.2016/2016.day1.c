#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
struct dire {
    int N;
    int S;
    int E;
    int W;
};
int main(int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("		2016 Day1.1\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

        char line1[1000];
        fgets(line1, 1000, a);
        fclose(a);
printf("line1 %s\n", line1);

int pointing = 0;
struct dire dirE = {0};
//int nextisdigit = 0;
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
	         if (pointing == 0) /*N*/ {
		    dirE.N += dig;
		 } else if (pointing == 2) /*S*/ {
		    dirE.S += dig;
	         } else if (pointing == 1) /*E*/ {
		    dirE.E += dig;
	         } else if (pointing == 3) /*W*/ {
		    dirE.W += dig;
                 }
             }
        }

     int northsouth = dirE.N - dirE.S;
     int eastwest = dirE.E - dirE.W;

printf("pointing: %d\n", pointing);
printf("N: %d S: %d E: %d W:%d\n", dirE.N, dirE.S, dirE.E, dirE.W);
      printf("****ns: %d ew: %d*****\n", northsouth, eastwest);
      fflush(stdout); dup2(fd, 1);
      printf("**ans: %d\n", abs(northsouth) + abs(eastwest));

}
