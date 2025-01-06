#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

#include <unistd.h>

#define getchar()
#include <deque>

using namespace std;

deque <char> angles;
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day10 Part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[5000];
	int tot = 0;
	int leny = 0;
	int lenx = 0;
	int bad;
	unsigned long tot2[200] = {0};
	int pos = 0;
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
		tot2[pos] = 0;
		int size = angles.size();
		for (int j = 0; j < size; j++) {
			char ang = angles.front();
			angles.pop_front();
			printf("%c", ang);
			switch (ang)  {
				case(')'):
					tot2[pos] *= 5;
					tot2[pos] += 1;
					break;
				case(']'):
					tot2[pos] *= 5;
					tot2[pos] += 2;
					break;
				case('}'):
					tot2[pos] *= 5;
					tot2[pos] += 3;
					break;
				case('>'):
					tot2[pos] *= 5;
					tot2[pos] += 4;
					break;
			}
			printf("tot2[pos] %ld\n", tot2[pos]);
		}
		printf("\n");
		pos++;
	}
	leny++;
}
fclose(a);
	lenx = (int)strlen(line1);
	for (int i = 0; i < pos; i++) {
		printf("%d: %ld\n", i, tot2[i]);
	}
	sort(tot2, tot2+pos);
	printf("pos is %d\n", pos);
	printf("***tot2 middle is %ld\n", tot2[pos/2]);
	printf("**** tot %d\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", tot2[pos/2]);
}

