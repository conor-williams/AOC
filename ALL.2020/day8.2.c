#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

FILE *a;

struct instruction {
	char inst;
	int val;
	int pos;
};
struct instruction allInst[1000];
struct instruction allInstOrig[1000];
int curInst = 0;
#define getchar()
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day3\n"); fflush(stdout);
        char line1[1000];
	
int leny = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        //line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int ret;
	ret = sscanf(line1, "nop +%d", &allInst[curInst].val);
	if (ret == 1) {
		allInst[curInst].inst = 'n';
		allInst[curInst].pos = curInst;
		goto end;
	}
	ret = sscanf(line1, "nop -%d", &allInst[curInst].val);
	if (ret == 1) {
		allInst[curInst].val -= 2*allInst[curInst].val;
		allInst[curInst].inst = 'n';
		allInst[curInst].pos = curInst;
		goto end;
	}
	ret = sscanf(line1, "acc +%d", &allInst[curInst].val);
	if (ret == 1) {
		allInst[curInst].inst = 'a';
		allInst[curInst].pos = curInst;
		goto end;
	}
	ret = sscanf(line1, "acc -%d", &allInst[curInst].val);
	if (ret == 1) {
		allInst[curInst].val -= 2*allInst[curInst].val;
		allInst[curInst].inst = 'a';
		allInst[curInst].pos = curInst;
		goto end;
	}
	ret = sscanf(line1, "jmp +%d", &allInst[curInst].val);
	if (ret == 1) {
		allInst[curInst].inst = 'j';
		allInst[curInst].pos = curInst;
		goto end;
	}
	ret = sscanf(line1, "jmp -%d", &allInst[curInst].val);
	if (ret == 1) {
		allInst[curInst].val -= 2*allInst[curInst].val;
		allInst[curInst].inst = 'j';
		allInst[curInst].pos = curInst;
		goto end;
	}
end:
	curInst++;
	leny++;
}
fclose(a);
	for (int k = 0; k < curInst; k++) {
		allInstOrig[k].val  = allInst[k].val;
		allInstOrig[k].inst = allInst[k].inst;
		allInstOrig[k].pos  = allInst[k].pos;
	}


	int mypos = 0;
	int infin = 0;
    while (1) {
	for (int k = 0; k < curInst; k++) {
		allInst[k].val  = allInstOrig[k].val;
		allInst[k].inst = allInstOrig[k].inst;
		allInst[k].pos  = allInstOrig[k].pos;
	}
	for (int p = mypos; p < curInst; p++) {
		if (allInst[p].inst == 'j') {
			allInst[p].inst = 'n';
			mypos = p+1;
			break;
		}
	}
	if (mypos >= curInst) {
		printf("no more changes...\n");
		exit(0);
	}
	
	if (infin == 1) {printf("infin is one %d\n", mypos-1); getchar();}		
	if (infin == 0) {printf("infin is ZERO %d\n", mypos-1); getchar();}		
	infin = 0;
	int instNUM = 0; int accum = 0;
	int instMEM[10000]; int instMEMPos = 0;
	while (1) {
		instMEM[instMEMPos] = instNUM;
		instMEMPos++;
		switch (allInst[instNUM].inst) {
			case 'n': {
				instNUM++;
				break;
			}
			case 'a': {
				accum += allInst[instNUM].val;
				instNUM++;
				break;
			}
			case 'j': {
				instNUM += allInst[instNUM].val;
				break;
			}
		}
///////////////
printf("PREV: ");
for (int i = 0; i < instMEMPos; i++) {
	printf("[%d:%c,%d]  ", instMEM[i], allInst[instMEM[i]].inst, allInst[instMEM[i]].val);
}
printf("\n");
printf("compare with %d\n", allInst[instNUM].pos);
///////////////
		if (instNUM < curInst) { 
			int found = 0;
			for (int j = 0; j < instMEMPos; j++) {
				if (instMEM[j] == allInst[instNUM].pos) {
					printf("found j:%d instMEM[j] %d at new pos %d allInst[instNUM].pos: %d\n", j, instMEM[j], instNUM, allInst[instNUM].pos);
					found = 1; break;
				}
			}
			if (found == 1) {
				printf("thats all folks - Infinite Loop detected [ %d ]\n", accum); infin = 1; break;
			}
		} else {
			printf("no infin... **accum %d\n", accum); exit(0); getchar();
		}
	}
    }
}
