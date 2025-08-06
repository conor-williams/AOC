#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
int tot = 0;
#define SIZE 200
char line1[SIZE];
#define TIME 100000
int same();

struct it_s {
	long long posX;
	long long posY;
	long long posZ;

	long long velX;
	long long velY;
	long long velZ;

	long long accX;
	long long accY;
	long long accZ;
	int flag;
};

struct it_s it[1001];
struct it_s itLast[1001];
int leny = 0;

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
	TimerSet(1200);
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2017 Day20.2\n"); fflush(stdout);


	fflush(stdout); fd = dup(1); close(1);
	for (int i = 0; i < 1001;i++) {
		it[i].flag = 0;
		itLast[i].flag = 0;
	}
	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("line1 %s\n", line1);

		sscanf(line1, "p=<%lld,%lld,%lld>, v=<%lld,%lld,%lld>, a=<%lld,%lld,%lld>",
				&it[leny].posX, &it[leny].posY, &it[leny].posZ, 
				&it[leny].velX, &it[leny].velY, &it[leny].velZ, 
				&it[leny].accX, &it[leny].accY, &it[leny].accZ);
		leny++;
	}
	fclose(a);

	int countNoCol = 0;
	for (int t = 1; t < TIME; t++) {
		long velX = 0, velY = 0, velZ = 0;
		long posX = 0, posY = 0, posZ = 0;
		for (int i = 0; i < leny; i++) {
			if (it[i].flag == 0) {
				velX = it[i].velX + it[i].accX;
				velY = it[i].velY + it[i].accY;
				velZ = it[i].velZ + it[i].accZ;
				posX = it[i].posX + velX;
				posY = it[i].posY + velY;
				posZ = it[i].posZ + velZ;

				it[i].velX = velX; it[i].velY = velY; it[i].velZ = velZ;
				it[i].posX = posX; it[i].posY = posY; it[i].posZ = posZ;
			}
		}

		if (same() == 0) {
			countNoCol++;
		} else {
			countNoCol = 0;
		}
		if (countNoCol == 200) {break;}
	}
	long  tot = 0; for (int i = 0; i < leny; i++) { if (it[i].flag == 0) { tot++; } }

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);
	return 0;

}
        int same() {
                int ch = 0;
                for (int i = 0; i < leny; i++) {
                        if (it[i].flag == 1) {continue;}
                        for (int j = i+1; j < leny; j++) {
                                if (it[j].flag == 1) {continue;}
                                if (it[i].posX == it[j].posX && it[i].posY == it[j].posY && it[i].posZ == it[j].posZ) {
                                        it[i].flag = 1;
                                        it[j].flag = 1;
                                        ch =1;
                                }
                        }
                }
                return ch;
        }

