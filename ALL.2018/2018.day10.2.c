#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <map>
#include <assert.h>
#include <vector>
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
struct point {
	int x = 0;
	int y = 0;
	int vx = 0;
	int vy = 0;
	point(int x, int y, int vx, int vy) {
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
	};

};


int main(int argc, char **argv)
{
	///printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day10.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); //close(1);
	int leny = 0;
	vector <struct point> po;
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
		//printf("%d %d %d %d\n", x1, y1, vx, vy);
		struct point tmp1 = point(x1, y1, vx, vy);
		po.push_back(tmp1);

	}
	fclose(a);

	int time = 0;
	int minminy = 0;
	int minminx = 0;
	while (1 == 1) {
		int maxy = -1000000;
		int miny = 9999999;
		int minx = 9999999;
		for (int qq = 0; qq < po.size(); qq++) {
			point tmp1 = po[qq];
			int yy = tmp1.y + (time * tmp1.vy);
			int xx = tmp1.x + (time * tmp1.vx);

			if (yy > maxy) {maxy = yy;}
			if (yy < miny) {miny = yy;}
			if (xx < minx) {minx = xx;}
		}
		if (maxy - miny + 1 < 11) {
			minminy = miny;
			minminx = minx;
			break;
		}
		time++;
	}
	printf("**ans:\n");
	printf("%d", time);
	printf("\n");





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
