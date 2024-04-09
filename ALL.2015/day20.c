#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tot = 0;
int elves = 1000;
int house[29000100] = {0};
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day20.1\n"); fflush(stdout);
        char line1[1000];
        int leny = 0;
        while (1) {

                fgets(line1, 1000, a); if (feof(a)) {break;}
                line1[strlen(line1) -1] = '\0';
//              printf("line1 %s", line1);



        } //while
        fclose(a);
        for (int i = 1; i < 29000000; i++) {
                for (int j = 1; j <= i; j++) {
                        if (i % j == 0 ) {
                                house[i] += 10 * j;
                        }
                }
                if (house[i] >= 29000000) {
                        printf("House: %d\n", i);
                        exit(0);
                }

        }
        for (int i = 1; i < 10; i++) {
                printf("house %d got %d presents\n", i, house[i]);
        }
        printf("***tot: %d\n", tot);
}

