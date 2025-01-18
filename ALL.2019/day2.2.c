#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2019 day2 part2\n"
#undef _DEBUG_
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
       
        char line1[3000];
	int nums[300];
	int numsOrig[300];
for (int i = 0; i < 300; i++) {nums[i] = 0;}
while(1) {

        fgets(line1, 2990, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	char *token = strtok(line1, ",\n");
#ifdef _DEBUG_
	printf("TOKEN %s\n", token);
#endif
	while (token != NULL) {
#ifdef _DEBUG_
	printf("TOKEN %s\n", token);
#endif
		nums[leny] = atoi(token);
#ifdef _DEBUG_
	printf("nums[%d] %d\n", leny, nums[leny]);
#endif
		token = strtok(NULL, ",\n");
		leny++;
	}
#ifdef _DEBUG_
	printf("Token: %s\n", token);
#endif
	printf("lenx %d - leny %d\n", lenx, leny);
}
fclose(a);

for (int i = 0; i < leny; i++) {numsOrig[i] = nums[i];}

    for (int noun = 0; noun < 100; noun++) {
     for (int verb = 0; verb < 100; verb++) {
for (int i = 0; i < leny; i++) {nums[i] = numsOrig[i];}
	nums[1] = noun; nums[2] = verb;
	for (int i = 0; i < leny; i++) {
		if (i % 4 == 0) {
#ifdef _DEBUG_
			printf("OPCODE %d: %d\n", i, nums[i]);
#endif
			if (nums[i] == 1) {
#ifdef _DEBUG_
				printf("PLUS: %d + %d\n", nums[nums[i+1]], nums[nums[i+2]]);
#endif
				nums[nums[i+3]] = nums[nums[i+1]] + nums[nums[i+2]];
			} else if (nums[i] == 2) {
#ifdef _DEBUG_
				printf("MUL: %d * %d\n", nums[nums[i+1]], nums[nums[i+2]]); 
#endif
				nums[nums[i+3]] = nums[nums[i+1]] * nums[nums[i+2]];
			} else if (nums[i] == 99) {
#ifdef _DEBUG_
				printf("END breaking getchar\n"); //getchar();
#endif
				break;
			} else {
#ifdef _DEBUG_
				printf("ERROR: unknown OPCODE %d getchar\n", nums[i]); 
#endif
				//getchar();
			}
		} else {
#ifdef _DEBUG_
			printf("NUM %d: %d\n", i, nums[i]);
#endif
		}
	
	}
	printf("STACK: %d %d\n", noun, verb);
#ifdef _DEBUG_
	for (int i = 0; i < leny; i++) {
		printf("%d,", nums[i]);
	} 
#endif
	if (nums[0] == 19690720) {fflush(stdout); dup2(fd, 1); printf("**ans %d%d\n" , noun, verb); exit(0);getchar(); break;}
#ifdef _DEBUG_
	printf("nums[0] %d\n", nums[0]);
#endif
    }}

	//printf("******** tot %ld\n", tot);
}
