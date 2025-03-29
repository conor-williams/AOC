#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
int lenx, leny;
#define DAY "2023 day16 part2\n"
#undef _DEBUG_
int tot;
struct inst {
	int stop;
	int x;
	int y;
	int direction;
};

char puzzle[200][200];
char puzzlecopy[200][200];
void getNextXY(struct inst *myinst);
void mymove(struct inst *myinst);
void printpuzzle();
void printpuzzlecopy();
struct inst myinstarray[150000];
int myinstarrayLen;
void saveit(struct inst myinst);
int isthereP(struct inst myinst);
int doit(int x, int y, int dir);

#include <sys/time.h>
#include <signal.h>
void TimerStop(int signum);
void TimerSet(int interval);

void TimerSet(int interval) {
    printf("starting timer\n");
    struct itimerval it_val;

    it_val.it_value.tv_sec = interval;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;

    if (signal(SIGALRM, TimerStop) == SIG_ERR) {
        perror("Unable to catch SIGALRM");
        exit(1);
    }
    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
        perror("error calling setitimer()");
        exit(1);
    }
}

int fd;
void TimerStop(int signum) {

	fflush(stdout); dup2(fd, 1);
    printf("Timer ran out! Stopping timer\n");
	FILE *f = fopen("out.tim", "a");
	fprintf(f, "Timer ran out! Stopping timer timestamp@%s\n", "out.tim");
	fclose(f);
    exit(10);
}
//main:::if (argc == 3) {printf("SETTING TIME TO [%d]\n", atoi(argv[2])); TimerSet(atoi(argv[2]));}
int main(int argc, char **argv)
{
	printf("SLOW ~3minutes\n");
	TimerSet(55*60);
	myinstarrayLen = 0;
	tot = 0;lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[200];
	while(1) {
		fgets(line1, 150, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
		strcpy(puzzle[leny], line1);
		leny++;
	}
	fclose(a);

	doit(3, 0, 2);
	//top row y is 0 // dir down = 2
	int maxtot = 0;
	int ret;
	for (int x = 0; x < lenx; x++) 
	{
		int y = 0;
		int dir = 2;

		ret = doit(x, y, dir);
		if (ret > maxtot) {maxtot = ret;}
	}
	//bottom row y is leny-1 // dir up = 0
	for (int x = 0; x < lenx; x++) 
	{
		int y = leny - 1;
		int dir = 0;
		ret = doit(x, y, dir);
		if (ret > maxtot) {maxtot = ret;}
	}

	//left row x is 0 // dir right = 1
	for (int y = 0; y < leny; y++)
	{

		int x = 0;
		int dir = 1;
		ret = doit(x, y, dir);
		if (ret > maxtot) {maxtot = ret;}

	}
	//right row // dir = 3
	for (int y = 0; y < leny; y++)
	{
		int x = lenx - 1;
		int dir = 3;
		ret = doit(x, y, dir);
		if (ret > maxtot) {maxtot = ret;}
	}
	printf("****MAX: %d\n", maxtot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", maxtot);
}

int doit(int x, int y, int direction) {
	tot = 0;
	myinstarrayLen = 0;
	for (int y1=0; y1<leny; y1++) {
		strcpy(puzzlecopy[y1], puzzle[y1]);
	}

	{
		///first MOVE 
		struct inst amyinst;
		amyinst.direction = direction;
		amyinst.x = x;
		amyinst.y = y;
		amyinst.stop = 0;
		mymove(&amyinst);
		printf("START %03d,%03d dir=%d ", x, y, direction);
		//printpuzzlecopy();
	}

	tot = 0;

	for (int y2 = 0; y2 < leny; y2++) {
		for (int x2 = 0; x2 < lenx; x2++) {
			if (puzzlecopy[y2][x2] == 'Q') {
				tot++;
			}
		}
	}
	printf("**tot %d\n", tot);

	return tot;
}
void printpuzzle()
{
	for (int y = 0; y < 10; y++) {
		printf("%s\n", puzzle[y]);
	}
	printf("______________________________\n");
}
void printpuzzlecopy()
{
	for (int y = 0; y < 10; y++) {
		printf("%s\n", puzzlecopy[y]);
	}
	printf("______________________________\n");
}
void saveit(struct inst myinst) {
	int found = 0;
	for (int i = 0; i < myinstarrayLen; i++) {
		if (myinst.stop == myinstarray[i].stop
				&& myinst.x == myinstarray[i].x
				&& myinst.y == myinstarray[i].y
				&& myinst.direction == myinstarray[i].direction) {
			found = 1;
#ifdef _DEBUG_
			printf("NOT SAVING: POS %d@ %d, %d dir: %d\n", i, myinst.x, myinst.y, myinst.direction); break;
#endif
		}
	}
	if (found == 0) {
#ifdef _DEBUG_
		printf("SAVING: %d, %d dir: %d\n", myinst.x, myinst.y, myinst.direction);
#endif
		myinstarray[myinstarrayLen] = myinst;
		myinstarrayLen++;
	}
}

int isthereP(struct inst myinst)
{
	int found = 0;
	for (int i = 0; i < myinstarrayLen; i++) {
		if (myinst.stop == myinstarray[i].stop
				&& myinst.x == myinstarray[i].x
				&& myinst.y == myinstarray[i].y
				&& myinst.direction == myinstarray[i].direction) {
			found = 1; 
#ifdef _DEBUG_
			printf("FOUND: POS %d@ %d, %d dir: %d\n", i, myinst.x, myinst.y, myinst.direction); break;
#endif

		}
	}
	return found;
}

void mymove(struct inst *myinst)
{
#ifdef _DEBUG_
	printf("in mymove...\n"); fflush(stdout);
#endif
	myinst->direction = myinst->direction % 4;
	if (myinst->stop==0) {
		puzzlecopy[myinst->y][myinst->x] = 'Q';
#ifdef _DEBUG_
		//----------
		printf("CHECKING [%c] @ [%d,%d] dir %d\n", puzzle[myinst->y][myinst->x], myinst->x, myinst->y, myinst->direction); fflush(stdout);
		char saved = puzzle[myinst->y][myinst->x];
		puzzle[myinst->y][myinst->x] = 'Q';
		printpuzzle();
		puzzle[myinst->y][myinst->x] = saved;
		getchar();
		//----------
#endif

		switch (puzzle[myinst->y][myinst->x]) {
			case '|':
				if (myinst->direction == 0 || myinst->direction == 2) {
				} else if (myinst->direction == 1 || myinst->direction == 3) {
					{
						struct inst myinst2;
						myinst2.stop = 0;
						myinst2.x = myinst->x;
						myinst2.y = myinst->y;
						myinst2.direction = 2;
						getNextXY(&myinst2);
					} 
					myinst->direction = 0;
				}
				break;
			case '-':
				if (myinst->direction == 1 || myinst->direction == 3) {
				} else if (myinst->direction == 0 || myinst->direction == 2) {
					{
						struct inst myinst3;
						myinst3.stop = 0;
						myinst3.x = myinst->x;
						myinst3.y = myinst->y;
						myinst3.direction = 1;
						getNextXY(&myinst3);
					}
					myinst->direction = 3;
				}
				break;
			case '\\':
				if (myinst->direction == 2) {
					myinst->direction = 1;
				} else if (myinst->direction == 3) {
					myinst->direction = 0;
				} else if (myinst->direction == 0) {
					myinst->direction = 3;
				} else if (myinst->direction == 1) {
					myinst->direction = 2;
				}
				break;
			case '/':
				if (myinst->direction == 2) {
					myinst->direction = 3;
				} else if (myinst->direction == 3) {
					myinst->direction = 2;
				} else if (myinst->direction == 0) {
					myinst->direction = 1;
				} else if (myinst->direction == 1) {
					myinst->direction = 0;
				}
				break;
			case '.':
				break;
			default:
				printf("ERORRORRRR. BAD CHAR.. getchar"); getchar();
				break;
		}
		getNextXY(myinst);
	} else {
		//printf("got stop\n"); fflush(stdout);
	}
#ifdef _DEBUG_
	printf("Leaving mymove\n"); fflush(stdout);
#endif
}

void getNextXY(struct inst *myinst)
{
	if (!isthereP(*myinst)) {saveit(*myinst);} else {myinst->stop = 1;}
	if (myinst->stop != 1) {
		switch (myinst->direction) {
			case 0:
				if (myinst->y -1 == -1) {myinst->stop = 1;} else {myinst->y--;}
				break;
			case 1:
				if (myinst->x + 1== lenx) {myinst->stop = 1;} else {myinst->x++;}
				break;
			case 2:
				if (myinst->y + 1 == leny) {myinst->stop = 1;} else {myinst->y++;}
				break;
			case 3:
				if (myinst->x - 1 == -1) {myinst->stop = 1;} else {myinst->x--;}
				break;
			default:
				printf("ERROR DIR... getchar\n"); getchar();
				break;

		}
		mymove(myinst);
	}
}
