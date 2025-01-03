#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#define getchar()

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("2015 Day1 Part1\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[8000];
        fgets(line1, 7999, a);
//build maps
int e = 0;
char lrrb;
int level = 0;
        while ((lrrb = line1[e]) != '\0' && lrrb != '\n') {
            if (lrrb == '(') level++; else level--;
            e++;
        }
      fclose(a);
      
      dup2(fd, 1);
      printf("****LEVEL:***** %d\n", level);

}
