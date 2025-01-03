#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2015 day8 part2\n"
#define _DEBUG_

int tot = 0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[200];
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	int inmem = 0;
	for (int i = 0; i < strlen(line1); i++) {
		if (i == (strlen(line1) -2) && line1[i] == '\"') { //ignore
			printf("HERE1");
			inmem+= 3;
		} else if (line1[i] == '\"') {  //ignore
			printf("HERE2");
			inmem+= 3;
		} else if (line1[i] == '\\') { //the magic
			if (line1[i+1] == '\\') {
				inmem += 4;
				i++;
			} else if (line1[i+1] == '\"') {
				inmem += 4;
				i++;
			} else if (line1[i+1] == 'x') {
				inmem += 5;
				printf("HERE 4..");
				//esc = line1[i+2] with line1[i+3]
				i+=3;
			}
		} else {
			inmem++;
		}
		
	}
	printf("inmem == %d\n", inmem);
	printf("strlen == %d\n", (int)strlen(line1));
	printf("line1 == %s\n", line1);
	tot += inmem - strlen(line1);
	leny++;
}
fclose(a);

	dup2(fd, 1);
	printf("***tot %d\n", tot); fflush(stdout);
}
