#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;
struct send_s {
	long long sendCount;
	int lastSound;
};
long long sendCount =0;
int tot = 0;
#define SIZE 20
#undef _DEBUG_
char line1[SIZE];
char inst[100][20];
int waiting0 = 0;
int waiting1 = 0;

deque<struct send_s> Q0;
deque<struct send_s> Q1;

void *program0(void *); void *program1(void *);
pthread_mutex_t lock;
#define getchar()

void TimerStop(int signum);
void TimerSet(int interval);

#define INTERVAL 12 

void TimerStop(int signum);
void TimerSet(int interval);
FILE *a;
int REG0 = 0;

void sig_handler(int signum){
        printf("CONOR ctrl-z sendCount is:: %lld\n", sendCount); getchar();
}
int fd;

void TimerStop(int signum) {
        //printf("\x1b[H");
        //printf("\x1b[%dB", 4);
        //printf("Timer ran out! Stopping timer %d\n", REG0);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", sendCount);
        fclose(a);
	exit(0);
}

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


int leny = 0;
int main(int argc, char **argv)
{
        signal(SIGTSTP, sig_handler);
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day18.2\n"); fflush(stdout);
	printf("SLOW ~30seconds\n");
	TimerSet(28);
	fd = dup(1); close(1);	

while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	strcpy(inst[leny], line1);	
	leny++;
}
fclose(a);

	pthread_t tid0;
	pthread_t tid1;

	//printf("before thread");
	if (pthread_mutex_init(&lock, NULL) != 0) { printf("\n mutex init has failed\n"); return 1; } 

	int error;
	error = pthread_create(&tid0, NULL, program0, (void *)&tid0);	
	if (error != 0) { printf("\nThread can't be created :[%s]", strerror(error)); }
	error = pthread_create(&tid1, NULL, program1, (void *)&tid1);	
	if (error != 0) { printf("\nThread can't be created :[%s]", strerror(error)); }

	pthread_join(tid0, NULL);
	pthread_join(tid1, NULL);
	//printf("after thread");
	printf("sendCount here here here is [ %lld ]\n", sendCount);
	return 0;
}
void *program1(void *x) {
	char reg1, reg2; int num1; int ret; long long regs[26] = {0};
	long long lastSound;
	regs['p'-97] = 1;
	long long lastRcv1Count = 0;
	for (int i = 0; i < leny; i++) {

		ret = sscanf(inst[i], "snd %d", &num1);
		if (ret == 1) {pthread_mutex_lock(&lock); lastSound = num1;
			struct send_s send;
			send.sendCount = sendCount;
			send.lastSound = lastSound;
			sendCount++;
			Q1.push_back(send); pthread_mutex_unlock(&lock); continue;}
		ret = sscanf(inst[i], "snd %c", &reg1);
		if (ret == 1) {pthread_mutex_lock(&lock); lastSound = regs[reg1-97];
			struct send_s send;
			send.sendCount = sendCount;
			send.lastSound = lastSound;
			sendCount++;
			Q1.push_back(send); pthread_mutex_unlock(&lock); continue;}


		ret = sscanf(inst[i], "set %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] = num1; continue;}
		ret = sscanf(inst[i], "set %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] = regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "add %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] += num1; continue;}
		ret = sscanf(inst[i], "add %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] += regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "mul %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] *= num1; continue;}
		ret = sscanf(inst[i], "mul %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] *= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "mod %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] %= num1; continue;}
		ret = sscanf(inst[i], "mod %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] %= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "rcv %c", &reg1);
		if (ret == 1) {
			while (Q0.size() == 0) {
				sleep(0.33);
				pthread_mutex_lock(&lock);
				waiting1 = 1;
				pthread_mutex_unlock(&lock);
				pthread_mutex_lock(&lock);
				if (waiting0 == 1) {
					//{printf("sendCount is %lld\n", sendCount);}
					//{printf("sendCount is %lld\n", sendCount);}
					//{printf("sendCount is %lld\n", sendCount);}
				}
				pthread_mutex_unlock(&lock);
			}
			pthread_mutex_lock(&lock);
			waiting1 = 0;
			pthread_mutex_unlock(&lock);
				sleep(0.44);

			pthread_mutex_lock(&lock);
			struct send_s myrcv1;
			myrcv1 = Q0.front();
			if (myrcv1.sendCount != lastRcv1Count+1) {printf("ERR");}
			regs[reg1-97] = myrcv1.lastSound; 
			lastRcv1Count = myrcv1.sendCount;
			Q0.pop_front();
			pthread_mutex_unlock(&lock); continue;
		}

		ret = sscanf(inst[i], "jgz %c %d", &reg1, &num1);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += num1 -1; continue;} else {continue;}}
		ret = sscanf(inst[i], "jgz %c %c", &reg1, &reg2);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += regs[reg2-97] -1; continue;} else {continue;}}
		printf("ERROR [%s]\n", inst[i]);
	}
	return 0;
}

void *program0(void *y) {
	char reg1, reg2; int num1; int ret; long long regs[26] = {0};
	long long lastSound;
	regs['p'-97] = 0;
	long long lastRcv0Count = 0;
	long long mySendCount = 0;
	for (int i = 0; i < leny; i++) {

		ret = sscanf(inst[i], "snd %d", &num1);
		if (ret == 1) {pthread_mutex_lock(&lock); lastSound = num1;
			struct send_s send;
			send.sendCount = mySendCount;
			send.lastSound = lastSound;
		        Q0.push_back(send); 
			mySendCount++;
			pthread_mutex_unlock(&lock); continue;}
		ret = sscanf(inst[i], "snd %c", &reg1);
		if (ret == 1) {pthread_mutex_lock(&lock); lastSound = regs[reg1-97];
			struct send_s send;
			send.sendCount = mySendCount;
			send.lastSound = lastSound;
			Q0.push_back(send); 
			mySendCount++;
			pthread_mutex_unlock(&lock);continue;}

		ret = sscanf(inst[i], "set %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] = num1; continue;}
		ret = sscanf(inst[i], "set %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] = regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "add %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] += num1; continue;}
		ret = sscanf(inst[i], "add %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] += regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "mul %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] *= num1; continue;}
		ret = sscanf(inst[i], "mul %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] *= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "mod %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] %= num1; continue;}
		ret = sscanf(inst[i], "mod %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] %= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "rcv %c", &reg1);
		if (ret == 1) {
			while (Q1.size() == 0) {
				sleep(0.001);
				pthread_mutex_lock(&lock);
				waiting0 = 1;
				pthread_mutex_unlock(&lock);
			}
			pthread_mutex_lock(&lock);
			waiting0 = 0;
			pthread_mutex_unlock(&lock);
				sleep(0.001);

			struct send_s myrcv0;
			myrcv0 = Q1.front();
			if (myrcv0.sendCount != lastRcv0Count+1) {printf("ERR0");}
			regs[reg1-97] = myrcv0.lastSound;
			lastRcv0Count = myrcv0.sendCount;
			Q1.pop_front();
			pthread_mutex_unlock(&lock); continue;
		}

		ret = sscanf(inst[i], "jgz %c %d", &reg1, &num1);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += num1 -1; continue;} else {continue;}}
		ret = sscanf(inst[i], "jgz %c %c", &reg1, &reg2);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += regs[reg2-97] -1; continue;} else {continue;}}
		printf("ERROR [%s]\n", inst[i]);
	}
	return 0;
}
