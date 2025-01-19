#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <map>
#include <assert.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>

#define assert(asdf)
#define getchar()
using namespace std;

#undef _DEBUG_
#define SIZE 400
char line1[SIZE];
unsigned long tot = 0;
#define Y 60000
#define X 60000
#define XAND -50 
#define YAND -150 
#define SCALE 60000

#define UP 30000
struct pos {
	int x1;
	int y1;
	int vx;
	int vy;
	int xs[UP];
	int ys[UP];
};
struct pos posit[500] = {0};
void curs();
int termsize (void);
int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day10.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		int x1, y1, vx, vy;
		char sx1[10], sy1[10], svx[10], svy[10];
		int ret = sscanf(line1, "position=< %[^,], %[^>]> velocity=< %[^,], %[^>]>", sx1, sy1, svx, svy);
		if (ret != 4) {printf("ERROR"); exit(0);}
		x1 = atoi(sx1); vx = atoi(svx);
		y1 = atoi(sy1); vy = atoi(svy);

		//printf("%d: %d %d, %d %d\n", leny, x1, y1, vx, vy);

		posit[leny].x1 = XAND + ((double)x1*SCALE/(double)X);// printf("x1 is %d\n", posit[leny].x1);
		posit[leny].y1 = YAND + ((double)y1*SCALE/(double)Y);// printf("y1 is %d\n", posit[leny].y1); //getchar();
		posit[leny].vx = vx;
		posit[leny].vy = vy;
		leny++;
	}
	fclose(a);

	for (int z = 0; z < leny; z++) {
		for (int i = 0; i < UP-2; i++) {
			posit[z].ys[i] = posit[z].y1 + (posit[z].vy*i);
			posit[z].xs[i] = posit[z].x1 + (posit[z].vx*i);
			//if (posit[z].ys[i] < 0) {printf("error1\n");}
			//if (posit[z].xs[i] < 0) {printf("error2\n");}
		}
	}


	//	for (int i = 10887; i < UP; i++) {
	map <int, int> countx;
	int boardCon;
	for (int i = 0; i < UP; i++) {
		countx.clear();
		//printf("AGAINTOP? %d:", i);
		for (int z = 0; z < leny; z++) {
			///printf("\x1b[H#");
			//printf("%d \n", posit[z].xs[i]);
			countx[posit[z].ys[i]]++;
			//if (posit[z].xs[i] > sz1) {printf("too big.. \n"); fflush(stdout);exit(0);}
			//if (posit[z].xs[i] < 0) {printf("too small.. \n"); fflush(stdout);exit(0);}
			//countx[posit[z].xs[i]]++;
			if (countx[posit[z].ys[i]] > 40) {
				boardCon = i;
				printf("boardCon is %d\n", boardCon);
				goto after;
			}
			///printf("\x1b[%dB", posit[z].ys[i]); //printf("%d", posit[z].ys[i]); getchar();
			///printf("\x1b[%dC#", posit[z].xs[i]);
			//			printf(";%dH#", posit[z].ys[i], posit[z].xs[i]);
		}
		//printf("BOTTOM? %d:", i);
		//printf("\x1b[H#");
		//printf("TOP?:", i);
		//getchar();
		//printf("\x1b[2J");
	}
after:
	printf("after...\n");
	int minX = 999999999;
	int maxX = 0;
	int minY = 999999999;
	int maxY = 0;
	for (int z = 0; z < leny; z++) {
		if (posit[z].xs[boardCon] > maxX) {maxX = posit[z].xs[boardCon];}
		if (posit[z].xs[boardCon] < minX) {minX = posit[z].xs[boardCon];}
		if (posit[z].ys[boardCon] > maxY) {maxY = posit[z].ys[boardCon];}
		if (posit[z].ys[boardCon] < minY) {minY = posit[z].ys[boardCon];}
	}
	printf("%d,%d -> %d,%d\n", minX, minY, maxX, maxY);
	//curs();
	//printf("\x1b[2J");

	int ROWS = termsize();
	printf("ROWS:%d\n", ROWS);
	int height = maxY - minY+2;
	int width = maxX - minX+2;
	int adjusterY = ROWS-height-1;
	
	for (int ii = 0; ii < height+1;ii++) {
		//printf("\n\n");
	}
	//char (*output)[100] = (char (*)[100]) malloc(sizeof(char[height][100]));
	char (*output)[width+10] = (char (*)[width+10]) malloc(sizeof(char[height+5][width+10]));
	
	//printf("height is %d\n", height);
	for (int y1 = 0; y1 < height; y1++) {
		for (int x1 = 0; x1 < width; x1++) {
			//output[y1][x1] = ' ';
			//printf("%d,%d ", x1, y1);
		}
	}

	memset (output, ' ', (width+10)*(height+5));
	assert(output[3][3] == ' ');
	for (int z = 0; z < leny; z++) {
		output[posit[z].ys[boardCon]-minY][posit[z].xs[boardCon]-minX] = 'X';
		assert(posit[z].ys[boardCon]-minY < height+5);
		assert(posit[z].xs[boardCon]-minX < width+10);
	}
	
	fflush(stdout); dup2(fd, 1);
	printf("**ans: \n");
	for (int y = 0; y < height; y++) {
		output[y][width+1] = '\n';
		output[y][width+2] = '\0';
		printf("%s", output[y]);
	}
	free(output);
}

void curs() {
	int ttyfd = open ("/dev/tty", O_RDWR);
	if (ttyfd < 0)
	{
		printf ("Cannot open /devv/tty: errno = %d, %s\r\n",
				errno, strerror (errno));
		exit (1);
	}

	write (ttyfd, "\x1B[6n\n", 5);

	unsigned char answer[16];
	size_t answerlen = 0;
	while (answerlen < sizeof (answer) - 1 &&
			read (ttyfd, answer + answerlen, 1) == 1)
		if (answer [answerlen ++] == 'R') break;
	answer [answerlen] = '\0';

	printf ("Answerback = \"");
	//char bla[20] = "";
	for (size_t i = 0; i < answerlen; ++ i)
		if (answer [i] < ' ' || '~' < answer [i]) {
			printf ("\\x%02X", (unsigned char) answer [i]);
			//sprintf(bla, "%s%02X", bla, (unsigned char)answer[i]);
		} else {
			printf ("%c", answer [i]);
			//sprintf(bla, "%s%02X", bla, (unsigned char)answer[i]);
		}
	printf ("\"\r\n");
	//printf("bla is %s\n", bla);

	return;
}

int termsize (void)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	printf ("lines %d\n", w.ws_row);
	printf ("columns %d\n", w.ws_col);
	return w.ws_row;
}
	/*
		for (int x =0; x < width; x++) {
			printf("%c", output[y][x]);
		}
		printf("\n");
	}
	*/
	

	//printf("\n\n\n");
	//printf("**tot %lu\n", tot);
	/*
	{
		//printf("\x1b[H");
		//printf("\x1b[%dB", minY+adjusterY-1);
		//printf("\x1b[%dC#", 0);
		for (int ii = 0; ii < height+1; ii++) {
			for (int i = 0; i < width+2; i++) {
				printf(" "); 
			}
			printf("\n");
		}
	}
	*/
