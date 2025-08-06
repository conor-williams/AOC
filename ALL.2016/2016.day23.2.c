#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int32_t a = 0;
int32_t b = 0;
int32_t c = 0;
int32_t d = 0;
bool toggledTheJump = false;
//williewillus on reddit
void toggle(int32_t target) {
	// tgl c with c = 2 means toggle pc 18, which is the jump back to lbl
	// is this horrible or what :D
	if (target == 2) {
		toggledTheJump = true;
	}
}

int main(int argc, char** argv) {
	printf("		2016 Day 23 Part 2\n");
	FILE * a = fopen(argv[1], "r");

	int linenum = 0;
	char line1[200];

	int num_nineteen = 0;
	int num_twenty = 0;
        while(1)
        {
                fgets(line1, 999, a);
                if (feof(a)) break;
                line1[strlen(line1) -1]='\0';
		if (linenum == 19) {
			sscanf(line1, "cpy %d c", &num_nineteen);
		} else if (linenum == 20) {
			sscanf(line1, "jnz %d d", &num_twenty);
		}
		linenum++;
        }

	long ans = 1;
	for (int ii = 1; ii <= 12; ii++) {
		ans *= ii;
	}
	ans += num_nineteen*num_twenty;

	printf("**ans: %d\n", ans);
}
