#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;
int lenx, leny;
#define DAY "2015 day10 part2\n"
#define _DEBUG_

int tot = 0;
#define SIZE 100
string looksay(string &s);
int TIMES = 50;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[SIZE];
	if (argc == 3) {TIMES = atoi(argv[2]);}
while(1) {
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	string anstmp = line1;
	for (int z = 0; z < TIMES; z++) {
		printf("z: %d of 40\n", z);
		anstmp = looksay(anstmp);
	}
	//printf("ans: %s\n", anstmp.c_str());

	fflush(stdout); dup2(fd, 1);
	printf("ans: %d\n", (int)anstmp.length());

}
fclose(a);

}
string looksay(string &s) {
	string r;
	r.reserve(s.length() * 2);
	for (int i = 0; i < (int)s.length(); ) {
		char c = s[i];
		int n = s.find_first_not_of(c, i);
		int len = 0;
		if (n == (int)string::npos) {
			len = s.length() -i;
		} else {
			len = n - i;
		}
		r.push_back('0' + len);
		r.push_back(c);
		i += len;
	}
	return r;
}
