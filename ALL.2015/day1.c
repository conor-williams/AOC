#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day8.2\n"); fflush(stdin); fflush(stdout);

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
      printf("****LEVEL:***** %d\n", level);

}
