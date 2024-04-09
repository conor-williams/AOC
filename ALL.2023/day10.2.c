#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char pipes[200][200];
long tot = 0;
int X, Y;
void cright(char forwhat);
void cleft(char forwhat);
void ctop(char forwhat);
void cbtm(char forwhat);
int main(int argc, char **argv)
{
        int r = 0;
        char starts[100][5];
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("Day8.2\n"); fflush(stdin); fflush(stdout);
       
        char line1[1000];
int pos = 0;
while(1) {
        fgets(line1, 1000, a);
        if (feof(a)) break;
        strcpy(pipes[pos], line1);
	pos++;
}
fclose(a);
int startx, starty;
for (int y = 0; y < pos; y++) {
    for (int x = 0; x < pos; x++) {
        if (pipes[y][x] == 'S') {startx = x; starty = y; break;} 
    }
}
printf("S at %d, %d\n", startx, starty);

/* btm is x, y+1 top is x, y-1 left is x-1, y right is x+1, y*/
for (int y = 0; y < pos; y++) {
    for (int x = 0; x < pos; x++) {
X=x; Y=y;
        switch(pipes[y][x]) {
        case '.': {pipes[y][x] = 'B'; break;}
        case '|': {cbtm('L'); cbtm('J'); ctop('7'); ctop('F'); break;}
        case '-': {cleft('F'); cleft('L'); cright('J'); cright('7'); break;}
        case 'L': {ctop('|'); ctop('7'); ctop('F'); cright('-');cright('J'); cright('7'); break;}
        case 'J': {cleft('-'); cleft('F'); cleft('L'); ctop('|'); ctop('7');ctop('F'); break;}
        case '7': {cleft('-'); cleft('F'); cleft('L'); cbtm('|'); cbtm('J'); cbtm('L'); break;}
        case 'F': {cright('-'); cright('7'); cright('J'); cbtm('|'); cbtm('L');cbtm('J'); break;}
        }
    }
}    
	printf("N: %c\n", pipes[starty-1][startx]);
	printf("S: %c\n", pipes[starty+1][startx]);
	printf("E: %c\n", pipes[starty][startx+1]);
	printf("W: %c\n", pipes[starty][startx-1]);

      fclose(a);
      printf("****TOT:***** %ld\n", tot/r);

}
void cright(char forwhat)
{
     if (pipes[Y][X+1] != forwhat) {
          pipes[Y][X+1] = 'B';
     }

}
void cleft(char forwhat)
{
     if (pipes[Y][X-1] != forwhat) {
          pipes[Y][X-1] = 'B';
     }
}
void ctop(char forwhat)
{
     if (pipes[Y-1][X] != forwhat) {
          pipes[Y-1][X] = 'B';
     }
}
void cbtm(char forwhat)
{
     if (pipes[Y+1][X] != forwhat) {
          pipes[Y+1][X] = 'B';
     }
}
//        if (pipes[y][x] == '|') {/*LJ at btm*//*7F at top*/ cbtm("LJ"); ctop("7F");}
 //       if (pipes[y][x] == '-') {/*FL at left*//*J7 at right*/ cleft("FL"); cright("J7");}
  //      if (pipes[y][x] == 'L') {/*|7F at top *//*-J7 at right*/} ctop("|7F"); cright("-J7");
   //     if (pipes[y][x] == 'J') {/*-FL at left *//*|7F at top*/} cleft("-FL"); ctop("|7F");
    //    if (pipes[y][x] == '7') {/*-FL at left *//*|JL at btm*/} cleft("-FL"); cbtm("|JL");
     //   if (pipes[y][x] == 'F') {/*-7J at right *//*|LJ at btm*/} cright("-7J"); cbtm("|LJ");
