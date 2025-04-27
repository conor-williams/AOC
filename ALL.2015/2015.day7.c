#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "		2015 day7 part1\n"
#define _DEBUG_
struct instruction {
	int type;
	char reg1[10];
	char reg2[10];
	char reg3[10];
	int num;
};
struct instruction insts[500];

map <string, int> mp;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[200];
	int curinst = 0;
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	int ret = 0;
	int inst = 0;
	int num = 0; char reg1[10], reg2[10], reg3[10];
	strcpy(reg1, "");
	strcpy(reg2, "");
	strcpy(reg3, "");
	ret = sscanf(line1, "%d -> %s", &num, reg3); inst = 1;
	if (ret != 2) {
		ret = sscanf(line1, "%d AND %s -> %s", &num, reg1, reg3); inst = 2;
		if (ret != 3) {
			ret = sscanf(line1, "%s OR %s -> %s", reg1, reg2, reg3); inst = 3;
			if (ret != 3) {
				ret = sscanf(line1, "%s LSHIFT %d -> %s", reg1, &num, reg3); inst = 4;
				if (ret != 3) {
					ret = sscanf(line1, "%s RSHIFT %d -> %s", reg1, &num, reg3); inst = 5;
					if (ret != 3) {
						ret = sscanf(line1, "NOT %s -> %s", reg1, reg3); inst = 6;
						if (ret != 2) {
							ret = sscanf(line1, "%s -> %s", reg1, reg3); inst = 7;
							if (ret != 2) {
								ret = sscanf(line1, "%s AND %s -> %s", reg1, reg2, reg3); inst = 8;
								if (ret != 3) {
									printf("ERROR"); exit(0);
								}
							}
						}
					}
				}
			}
		}
	}
	insts[curinst].type = inst;
	strcpy(insts[curinst].reg1, reg1);
	strcpy(insts[curinst].reg2, reg2);
	strcpy(insts[curinst].reg3, reg3);
	insts[curinst].num = num;
/*
	printf("[%s] [%s] [%s] [%d] [%d]\n",
		insts[curinst].reg1,
		insts[curinst].reg2, 
		insts[curinst].reg3,
		insts[curinst].num,
		insts[curinst].type);
*/
	curinst++;
}
fclose(a);

int maxInst = curinst;
curinst = 0;
int times = 0;
while (1) {
	int ans = 0;
	char reg1[10], reg2[10], reg3[10]; int num;
/*
	printf("[%s] [%s] [%s] [%d] [%d]\n",
		insts[curinst].reg1,
		insts[curinst].reg2, 
		insts[curinst].reg3,
		insts[curinst].num,
		insts[curinst].type);
*/
	strcpy(reg1, insts[curinst].reg1);
	strcpy(reg2, insts[curinst].reg2);
	strcpy(reg3, insts[curinst].reg3);
	num = insts[curinst].num;
	int inst = insts[curinst].type;
/*
	printf("[%s] [%s] [%s] [%d] [%d]\n",
		reg1,
		reg2, 
		reg3,
		num,
		inst);
*/
	int v1, v2; string r1, r2, r3;
	int sixt = (int)strtol  ("1111111111111111", NULL, 2);

	int notYet = 0;
	switch (inst) {
		case 1: 
			if (times == 0) {
				ans = num;
			} else {
				notYet = 1;
			}
			break;
		case 2: 
			r1 = reg1;
			if (mp.find(r1) == mp.end()) {notYet=1;}
			if (notYet == 0) {
				v1 = mp[r1]; 
				ans = (num & v1) & sixt;
			}
			break;
		case 3: 
			r1 = reg1; r2 = reg2;
			if (mp.find(r1) == mp.end() || mp.find(r2) == mp.end()) {
				notYet = 1;
			}
			if (notYet == 0) {
				v1 = mp[r1]; v2 = mp[r2];
				ans = (v1 | v2) & sixt;
			}
			break;
		case 4: 
			r1 = reg1;
			if (mp.find(r1) == mp.end()) {
				notYet = 1;
			}
			if (notYet == 0) {
				v1 = mp[r1];
				ans = (v1 << num) & sixt;
			}
			break;
		case 5: 
			r1 = reg1;
			if (mp.find(r1) == mp.end()) {notYet = 1;}
			if (notYet == 0) {
				v1 = mp[r1];
				ans = (v1 >> num) & sixt;
			}
			break;
		case 6: 
			r1 = reg1;
			if (mp.find(r1) == mp.end()) {notYet = 1;}
			if (notYet == 0) {
				v1 = mp[r1];
				ans = (~v1 )  & sixt;
			}
			break;
		case 7: 
			r1 = reg1;
			if (mp.find(r1) == mp.end()) {notYet = 1;}
			if (notYet == 0) {
				v1 = mp[r1];
				ans = v1;
			}
			break;
		case 8: 
			r1 = reg1; r2 = reg2;
			if (mp.find(r1) == mp.end() || mp.find(r2) == mp.end()) {
				notYet = 1;
			}
			if (notYet == 0) {
				v1 = mp[r1]; v2 = mp[r2];
				ans = (v1 & v2) & sixt;
			}
			break;
		case 0: 
			printf("ERROR casezero");
			break;
	}
	if (inst > 0) {
		//printf("ans is %d\n", ans); getchar();
		r3 = reg3;
		if (notYet == 0) {
			if (mp.find(r3) != mp.end()) {
				mp[r3] = ans;
			} else {
				mp.insert({r3, ans});
			}
		}
	////
		string tofinda = "a";
		if (mp.find(tofinda) != mp.end()) {
			if (mp[tofinda] != 0) {
				printf("wire a: [%d]\n", mp[tofinda]);
				break;
			}
		} else {
			//printf("NO A???");
		}
	}
	///////
	curinst++;
	if (curinst == maxInst) {times++; curinst = curinst %maxInst; if (times %1000 == 0){printf("times... %d\n", times);}}
	
	
}
	string tofinda = "a";

	fflush(stdout); dup2(fd, 1);
	if (mp.find(tofinda) != mp.end()) {
		printf("wire a: [%d]\n", mp[tofinda]);
	} else {
		printf("NO A???");
	}
	//printf("end...\n"); fflush(stdout);
}
