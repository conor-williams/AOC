#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <unistd.h>
#include <pthread.h>

using namespace std;
int sendCount =0;
int tot = 0;
#define SIZE 20
#undef _DEBUG_
char line1[SIZE];
char inst[100][20];

deque<long long> Q0;
deque<long long> Q1;
void *program0(void *); void *program1(void *);
pthread_mutex_t lock;

int leny = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.1\n"); fflush(stdout);


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
	printf("sendCount here here here is %d\n", sendCount);
	return 0;
}
void *program1(void *x) {
	char reg1, reg2; int num1; int ret; long long regs[26] = {0};
	long long lastSound;
	regs['p'-97] = 1;
	deque<long long> rcvQ1;
	for (int i = 0; i < leny; i++) {
		pthread_mutex_lock(&lock); printf("sendCount is %d\n", sendCount); pthread_mutex_unlock(&lock);

		ret = sscanf(inst[i], "snd %d", &num1);
		if (ret == 1) {pthread_mutex_lock(&lock); sendCount++; lastSound = num1;
			Q1.push_back(lastSound); pthread_mutex_unlock(&lock); continue;}
		ret = sscanf(inst[i], "snd %c", &reg1);
		if (ret == 1) {pthread_mutex_lock(&lock); sendCount++; lastSound = regs[reg1-97];
			Q1.push_back(lastSound); pthread_mutex_unlock(&lock); continue;}

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
		if (ret == 1) {pthread_mutex_lock(&lock);
			rcvQ1.push_back(reg1-97);
			
			if (Q0.size() == 0) {
				pthread_mutex_unlock(&lock); continue;
			}  else {
				int reg;
				int size = rcvQ1.size();
				int size1 = Q0.size();
				for (int i = 0, j = 0; i < size; i++, j++) {
					if (j < size1) {
						reg = rcvQ1.front(); rcvQ1.pop_front();
						regs[reg] = Q0.front(); Q0.pop_front();
					}
				}
				pthread_mutex_unlock(&lock); continue;
			}

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
	deque<long long> rcvQ0;
	for (int i = 0; i < leny; i++) {
		pthread_mutex_lock(&lock);
		printf("sendCount is %d\n", sendCount);
		pthread_mutex_unlock(&lock);

		ret = sscanf(inst[i], "snd %d", &num1);
		if (ret == 1) {pthread_mutex_lock(&lock); lastSound = num1;
		         Q0.push_back(lastSound); pthread_mutex_unlock(&lock); continue;}
		ret = sscanf(inst[i], "snd %c", &reg1);
		if (ret == 1) {pthread_mutex_lock(&lock); lastSound = regs[reg1-97];
			 Q0.push_back(lastSound); pthread_mutex_unlock(&lock);continue;}

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
		if (ret == 1) {pthread_mutex_lock(&lock); 
			rcvQ0.push_back(reg1-97);
			
			if (Q1.size() == 0) {
				pthread_mutex_unlock(&lock); continue;
			}  else {
				int reg;
				int size = rcvQ0.size();
				int size1 = Q1.size();
				for (int i = 0, j = 0; i < size; i++, j++) {
					if (j < size1) {
						reg = rcvQ0.front(); rcvQ0.pop_front();
						regs[reg] = Q1.front(); Q1.pop_front();
					}
				}
				pthread_mutex_unlock(&lock); continue;
			}

		}

		ret = sscanf(inst[i], "jgz %c %d", &reg1, &num1);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += num1 -1; continue;} else {continue;}}
		ret = sscanf(inst[i], "jgz %c %c", &reg1, &reg2);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += regs[reg2-97] -1; continue;} else {continue;}}
		printf("ERROR [%s]\n", inst[i]);
	}
	return 0;
}
