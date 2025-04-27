#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2020 day2 part2\n"
#define _DEBUG_
int tot = 0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[3000];
while(1) {
        fgets(line1, 2990, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif

	int min = 0; int max = 0; char letter; char password[200];
	sscanf(line1, "%d-%d %c: %s", &min, &max, &letter, password);
printf("%d -- %d %c %s\n", min, max, letter, password);
	if (letter == password[min-1] && letter == password[max-1]) {
	} else if (letter == password[min-1] || letter == password[max-1]) {
		tot++;
		printf("valid: %s\n", password);
	}
		leny++;
	printf("lenx %d - leny %d\n", lenx, leny);
}
fclose(a);

	fflush(stdout); dup2(fd, 1);
	printf("** tot %d\n", tot);
}
