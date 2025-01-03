#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day20 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 200
//sort -n i1.txt
struct ran {
	unsigned long long from;
	unsigned long long to;
};
struct ran ranges[1100];
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
	printf("LINE: %s\n", line1);
#endif

	//919958672-920375477
	char from[100]; char to[100];
	sscanf(line1, "%[^-]-%s", from, to);
	char *end;
	ranges[leny].from = strtoull(from, &end, 10);
	ranges[leny].to = strtoull(to, &end, 10);
	//printf("from: %llu to: %llu\n", ranges[leny].from, ranges[leny].to);
	//system("head -1 i1.txt");
	//getchar();
	leny++;
}
fclose(a);

/*
5-8
0-2
4-7
*/
	for (unsigned long long i = 0; ; i++) {
		int found = 0;
		for (int z = 0; z < leny; z++) {
			if (i >= ranges[z].from  && i <= ranges[z].to) {
				found = 1; break;
			}	
		}
		if (found == 0) {
			dup2(fd, 1);
			printf("**lowest is %llu\n", i);
			exit(0);
		}

	}

	dup2(fd, 1);
	printf("***tot %ld END\n", tot); fflush(stdout);
} 
