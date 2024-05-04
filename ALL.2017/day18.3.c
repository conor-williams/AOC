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
int pos1 = 0;
int pos2 = 0;
int tot = 0;
#define SIZE 20
#undef _DEBUG_
char line1[SIZE];
char inst[100][20];
deque<long long> Q1;
deque<long long> Q2;
void *program1(void *);
void *program2(void *);
int leny = 0;
int pos1sent = 0;
int pos2sent = 0;
pthread_mutex_t lock;
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

	pthread_t tid1;
	pthread_t tid2;

	//printf("before thread");
	if (pthread_mutex_init(&lock, NULL) != 0) { 
        	printf("\n mutex init has failed\n"); 
	        return 1; 
    	} 

	pthread_create(&tid1, NULL, program1, (void *)&tid1);	
	pthread_create(&tid2, NULL, program2, (void *)&tid2);	

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	//printf("after thread");
	printf("sendCount is %d\n", sendCount);
	return 0;
}
void *program2(void *x) {
	char reg1, reg2; int num1; int ret; long long regs[26] = {0};
	long long lastSound;
	regs['p'-97] = 1;
	//waiting2[200] = {0};
	for (int i = 0; i < leny; i++) {
		//if (pos1sent == 1 && pos2sent == 1 && pos2 == 0 && pos1 == 0) { break; }
		//printf("BEFORE: regs[a] :%ld\n", regs[0]); getchar();
		//printf("inst[%d] is [%s]\n", i, inst[i]); getchar();


		printf("sendCount is %d\n", sendCount);
		ret = sscanf(inst[i], "snd %d", &num1);
		if (ret == 1) {pthread_mutex_lock(&lock);pos1sent = 1; pos1++; sendCount++; /*printf("send [%d] from prog2\n", num1);*/lastSound = num1;                  Q2.push_back(lastSound); pthread_mutex_unlock(&lock);continue;}
		ret = sscanf(inst[i], "snd %c", &reg1);
		if (ret == 1) {pthread_mutex_lock(&lock);pos1sent = 1; pos1++; sendCount++; /*printf("send [%lld] from prog2\n", regs[reg1-97]); */ lastSound = regs[reg1-97]; Q2.push_back(lastSound); pthread_mutex_unlock(&lock);continue;}


		
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
		if (ret == 1) {if (Q1.size() == 0) {pthread_mutex_lock(&lock); /*printf("sendCount %d\n", sendCount);*/ /*printf("nothing in Q1\n"); */pthread_mutex_unlock(&lock);continue;}  else { pthread_mutex_lock(&lock);regs[reg1-97] = Q1.front(); Q1.pop_front(); /*printf("rcv %lld from prog1\n", regs[reg1-97]);*/ /*pos2--; */pthread_mutex_unlock(&lock); continue;}}

		ret = sscanf(inst[i], "jgz %c %d", &reg1, &num1);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += num1 -1; continue;} else {continue;}}
		ret = sscanf(inst[i], "jgz %c %c", &reg1, &reg2);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += regs[reg2-97] -1; continue;} else {continue;}}
		printf("ERROR [%s]\n", inst[i]);
	}
	return 0;
}

void *program1(void *y) {
	//waiting1 = 0;
	char reg1, reg2; int num1; int ret; long long regs[26] = {0};
	long long lastSound;
	regs['p'-97] = 0;
	for (int i = 0; i < leny; i++) {
		printf("sendCount is %d\n", sendCount);
		//printf("BEFORE: regs[a] :%ld\n", regs[0]); getchar();
		//printf("inst[%d] is [%s]\n", i, inst[i]); getchar();
		//if (pos1sent == 1 && pos2sent == 1 && pos2 == 0 && pos1 == 0) { break; }

		ret = sscanf(inst[i], "snd %d", &num1);
		if (ret == 1) {pthread_mutex_lock(&lock);/*pos2sent = 1; pos2++; */ lastSound = num1;         Q1.push_back(lastSound); /*printf("snd from prog1 %lld\n", lastSound); */pthread_mutex_unlock(&lock); continue;}
		ret = sscanf(inst[i], "snd %c", &reg1);
		if (ret == 1) {pthread_mutex_lock(&lock);/*pos2sent = 1; pos2++; */ lastSound = regs[reg1-97]; Q1.push_back(lastSound); /*printf("snd from prog1 %lld\n", lastSound); */ pthread_mutex_unlock(&lock);continue;}

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
		if (ret == 1) {pthread_mutex_lock(&lock);if (Q2.size() == 0) {/*printf("nothing in Q2\n"); */pthread_mutex_unlock(&lock);continue;}  else {pthread_mutex_lock(&lock);/*printf("rcv from prog2: %lld\n", Q2.front()); */ regs[reg1-97] = Q2.front(); Q2.pop_front(); /*pos1--;*/pthread_mutex_unlock(&lock);continue;}}

		ret = sscanf(inst[i], "jgz %c %d", &reg1, &num1);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += num1 -1; continue;} else {continue;}}
		ret = sscanf(inst[i], "jgz %c %c", &reg1, &reg2);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += regs[reg2-97] -1; continue;} else {continue;}}
		printf("ERROR [%s]\n", inst[i]);
	}
	return 0;
}
