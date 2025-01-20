#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2016 day16 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 200
#define CDISK 272
#define SIZES 4000
	
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[SIZE];
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	char buf[SIZES+10]; char in[SIZES];
	strcpy(in, line1);
	do {
		string b = in;	
		reverse(b.begin(), b.end());
		for (int i = 0; i < (int)b.length(); i++)  {
			if (b[i] == '1') {
				b[i] = '0';
			} else {
				b[i] = '1';
			}
		}
		sprintf(buf, "%s0%s", in, b.c_str());
		//printf("*** buf is %s (%s) strlen(buf) is %d\n", buf, line1, (int)strlen(buf));
		strcpy(in, buf);
	} while ((int)strlen(buf) < CDISK);

	buf[CDISK] =  '\0';
	printf(" here1 buffer is %s (%s)\n", buf, line1); getchar();
again:
	char cSum[SIZES];
	for (int i = 0; i < (int) strlen(buf); i++) {
		if (buf[i] == buf[i+1]) {
			cSum[i/2] = '1';
		} else {
			cSum[i/2] = '0';
		}
		cSum[(i/2)+1] = '\0';
		i++;
	}
	if (strlen(cSum) %2 == 0) {
		strcpy(buf, cSum);
		printf("going again %s\n", cSum);
		goto again;
	}
		
	fflush(stdout); dup2(fd, 1);
	printf("*** cSum %s\n", cSum);
	exit(0);
	leny++;
	
}
fclose(a);
		
	printf("***tot %ld END\n", tot); fflush(stdout);
} 

