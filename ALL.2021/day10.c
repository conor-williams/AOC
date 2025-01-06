#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#include <deque>

using namespace std;

deque <char> angles;
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day10.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[5000];
	int tot = 0;
	int leny = 0;
	int lenx = 0;
	int bad;
	int tot2 = 0;
while (1) {
	angles.clear();
        fgets(line1, 4999, a);
        if (feof(a)) break;
        line1[(int)strlen(line1)-1] = '\0';
	bad = 0;
	for (int i = 0; i < (int)strlen(line1); i++) {
		switch (line1[i]) {
			case '{':
				angles.push_front('}');
				break;
			case '(':
				angles.push_front(')');
				break;
			case '[':
				angles.push_front(']');
				break;
			case '<':
				angles.push_front('>');
				break;
			default:
				char ang = angles.front();
				angles.pop_front();
				if (ang == line1[i]) {
					
					break;
				} else {
					printf("BAD %s\n", line1);
					bad = 1;
					switch (line1[i])  {
						case(')'):
							tot += 3;
							break;
						case(']'):
							tot += 57;
							break;
						case('}'):
							tot += 1197;
							break;
						case('>'):
							tot += 25137;
							break;
					}
					goto out;
				}
			}
	}
out:
	if (bad == 0) {
		int size = angles.size();
		for (int j = 0; j < size; j++) {
			char ang = angles.front();
			angles.pop_front();
			switch (ang)  {
				case(')'):
					tot2 *= 2;
					tot2 + 1;
					break;
				case(']'):
					tot2 *= 2;
					tot2 += 3;
					break;
				case('}'):
					tot2 *= 2;
					tot2 += 3;
					break;
				case('>'):
					tot2 *= 2;
					tot2 += 4;
					break;
			}
		}
	}
	leny++;
}
fclose(a);
	lenx = (int)strlen(line1);
	printf("**** tot %d\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);
}

