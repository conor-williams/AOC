#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 20
char line1[SIZE];
struct port_s {
	int from;
	int to;
};

struct port_s port[60];
void next(int from, int to);
int leny = 0;
struct port_s already[1000];
int alreadyPos = 0;
int tot2 = 0;
int max = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day24.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);


//50/41
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	int num1, num2;
	sscanf(line1, "%d/%d", &num1, &num2);
	
	//port[leny].to = num1;
	//port[leny].from = num2;
	//leny++;
	port[leny].from = num1;
	port[leny].to = num2;
	leny++;
	
}
fclose(a);
	
	for (int i = 0; i < leny; i++) {
		if (port[i].from == 0) {
			tot2 = port[i].to;
			next(0, port[i].to);
		
		}
	}

	printf("***tot is ^^ [%d]\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**max is %d\n", max);
}
int ind = 0;
void next(int from, int to) {
ind++;
	int found = 0;
	for (int i = 0; i < alreadyPos; i++) {
		if ((already[i].from == from && already[i].to == to) || (already[i].from == to && already[i].to == from)) {
			found = 1; break;
		}
	}
	if (found == 1) {
		ind--;
		return;	
	} else {
		already[alreadyPos].from = from;
		already[alreadyPos].to = to;
		alreadyPos++;
	}
	for (int i = 0; i < ind; i++) {printf("	");} printf("f:%d/%d\n", from, to);
	int remAlreadyPos = alreadyPos;
	int totrem = tot2;
	printf("tot2 %d\n", tot2);
	if (tot2 > max) {max = tot2;}
	for (int i = 0; i < leny; i++) {
		if (port[i].from == to) {
			tot2 += port[i].from + port[i].to;
			next(port[i].from, port[i].to);
			alreadyPos = remAlreadyPos;
			tot2 = totrem;
		} else if (port[i].to == to) {
			tot2 += port[i].from + port[i].to;
			next(port[i].to, port[i].from);
			alreadyPos = remAlreadyPos;
			printf("tot2 %d\n", tot2);
			tot2 = totrem;
		}
	
	}
ind--;
}
