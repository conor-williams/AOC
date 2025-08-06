#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/time.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
//////////////////////
#include <stdio.h>
#include <string.h>
#include <mbedtls/md5.h>
mbedtls_md5_context ctx;
#define UPTO 50000

void TimerStop(int signum);
void TimerSet(int interval);

void TimerSet(int interval) {
    //printf("starting timer\n");
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
	fprintf(f, "Timer ran out! Stopping timer @%s\n", "out.tim");
	fclose(f);
    exit(10);
}
#define getchar()
void print_hash(unsigned char hash[16]) {
	for (int i = 0; i < 16; i++) {
		printf("%02x", hash[i]);
	}
	printf("\n");
}
struct three5 {
	int three;
	int theThree;
	int five;
	int theFive;
};
struct three5 threefive[UPTO];

char out5[50];
int compute_md5(const char *input, int timerOn, int pr, int inputPos) {
	unsigned char output[16]; // MD5 output is 16 bytes
	mbedtls_md5_context ctx;

	mbedtls_md5_init(&ctx);
	mbedtls_md5_starts_ret(&ctx);
	mbedtls_md5_update_ret(&ctx, (const unsigned char*) input, strlen(input));
	mbedtls_md5_finish_ret(&ctx, output);
	mbedtls_md5_free(&ctx);

	sprintf(out5, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", output[0], output[1], output[2], output[3], output[4], output[5], output[6], output[7], output[8], output[9], output[10], output[11], output[12], output[13], output[14], output[15]);

	if (timerOn == 3) {
		unsigned char the;
		int found3Pos = 0;
		for (int k = 0; k < 32-2; k++) {
			if (out5[k] == out5[k+1] && out5[k+1] == out5[k+2]) {
				found3Pos = k;
				the = out5[k];
				threefive[inputPos].three = 1; 
				threefive[inputPos].theThree = the; break;
			}
		}

		if (threefive[inputPos].three == 1) {
			{
				int j =  found3Pos;
				if (out5[j] == the && out5[j] == out5[j+1] && out5[j+1] == out5[j+2] && out5[j+2] == out5[j+3] && out5[j+3] == out5[j+4]) {
					threefive[inputPos].five = 1;
					threefive[inputPos].theFive = the;
				}
			}
		}
		return 3;

	} else if (timerOn == 2) {
		return 2;
	}
	return 0;
}
	

//////////////////////
int main(int argc, char **argv)
{

	TimerSet(1200);
	printf("		2016 day14 part 2\n");
	printf("	SLOW ~3mins\n");
	fflush(stdout); fd = dup(1); close(1);
	for (int i = 0; i < UPTO; i++) {
		threefive[i].five =0;
		threefive[i].three =0;
	}

	//unsigned long i = 0; 
	char buf[100];
	FILE * a = fopen(argv[1], "r");
        char line1[1000];
        char input[50];
while(1)
{
        fgets(line1, 999, a);
        if (feof(a)) break;
        line1[strlen(line1) -1]='\0';
        strcpy(input, line1);
}


	//char *input = "ihaygndm";
	//char *input = "abc";
	for (int i = 0; i < UPTO; i++) {
                snprintf(buf, 50, "%s%d", input, i);
		compute_md5(buf, 2, 0, i);
		for (int z = 0; z < 2015; z++) {
			compute_md5(out5, 2, 0, i);
		}
		compute_md5(out5, 3, 0, i);
	}
	
	//system("date");
	//printf("after...\n"); fflush(stdout); 
	int pos = 0;
	for (int i = 0; i < UPTO-2000; i++) {
		if (threefive[i].three == 1 && threefive[i].five == 0) {
			for (int j = i+1; j < 1000+i+1; j++) {
				if (threefive[j].five == 1 && threefive[i].theThree == threefive[j].theFive) {
					pos++;
					//printf("gotONE... @ j == %d **i is %d pos: %d\n", j, i, pos); getchar();
					if (pos == 64) {
						//printf("gotcha... @ j == %d **i is %d pos: %d\n", j, i, pos); getchar();
						fflush(stdout); dup2(fd, 1);
						printf("**ans: %d\n", i);
						exit(0);
					}
					goto cont;
				}
			}
		}
cont:
		continue;
	}
}


