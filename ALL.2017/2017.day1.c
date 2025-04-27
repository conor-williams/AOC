#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int pos = 0;
int main(int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("		2017 Day1.1\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

        char line1[4000];
        char line2[5000];
        char line3[4500];
        fgets(line1, 3000, a);
        fclose(a);
printf("line1 %s\n", line1);

	line1[(int)strlen(line1)-1] = '\0';
printf("line1 %s\n", line1);
	int kk;
	for (kk = 0; kk < (int)strlen(line1); kk++) {
		if (line1[kk] == line1[(int)strlen(line1) -1]) {
			//good
		} else {
			break;
		}
	}
	strcpy(line2, line1);
	for (int zz = 0; zz < kk; zz++) {
		strcpy(line3, line2);
		sprintf(line2, "%s%c", line3, line1[(int)strlen(line1)-1]);
	}
	strcpy(line1, line2);

int tot = 0;
        int bprev = line1[0] - '0';
        for (int f = 1; f < 3000; f++)  {
	     char bChar = line1[f];
	     if (bChar == '\0' || bChar == '\n') {break;}
	     int bNum = line1[f] - '0';
	     if (bprev == bNum) {
		tot += bprev;
	     }
             bprev = bNum;
        }

	fflush(stdout); dup2(fd, 1);
        printf("******TOT: %d\n", tot);
}

