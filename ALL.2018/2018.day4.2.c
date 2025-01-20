#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
int gardaSleep[100][100][61] = {0};
int gardaPos2[100] = {0};
struct baseG {
	int hashnum;
	int position;
} gardaMAP[30];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	char newFileSorted[200];
	sprintf(newFileSorted, "%s.sorted", argv[1]);
	char sortCmd[500];
	sprintf(sortCmd, "sort %s > %s", argv[1], newFileSorted);		
	system(sortCmd);
        //FILE * a = fopen(argv[1], "r"); printf("Day4.1\n"); fflush(stdout);
        FILE * a = fopen(newFileSorted, "r"); printf("2018 Day4.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	
        char line1[1000];
	int leny = 0;
	//int valid = 0;
	//int fiveone2 = 512;
	int d1, d2, t1, t2, guardnum;
	int curGarda = -1;
	int startSleep;
	int gardaPos = 0;
	int numGardai = 0;
        while (1) {
		printf("here1...");fflush(stdout);
		fgets(line1, 1000, a); if (feof(a)) {break;}
		line1[strlen(line1) -1] = '\0';
		printf("line1 %s\n", line1); fflush(stdout);
		int ret = 0;
		int first, second, third;
		for (int i = 0; i < strlen(line1); i++ ) {
			       if (line1[i] == 'G') {
				first = 1; second = 0; third = 0;
				break;
			} else if (line1[i] == 'w') {
				first = 0; second = 0; third = 1;
				break;
			} else if (line1[i] == 'l') {
				first = 0; second = 1; third = 0;
				break;
			}
		}
	if (first == 1) {
		ret = sscanf(line1, "\[1518-%d-%d %d:%d] Guard #%d begins shift", &d1, &d2, &t1, &t2, &guardnum);
		printf("here1"); fflush(stdout);
		if (ret == 5) {
			if (curGarda != -1) {gardaPos2[curGarda]++;}
			printf("guardnum is %d\n", guardnum);
			int found = 0;
			for (int i = 0; i < gardaPos; i++) {
				if (gardaMAP[i].hashnum == guardnum) {
					found = 1;
					curGarda = i;
					break;
				}
			}
			if (found == 0) {
				printf("new GARDA..\n");
				gardaMAP[gardaPos].hashnum = guardnum; gardaMAP[gardaPos].position = gardaPos;
				printf("gardaMap: %d == %d\n", gardaMAP[gardaPos].hashnum, gardaMAP[gardaPos].position);
				curGarda = gardaPos;
				gardaPos++;
				numGardai++;
			}
		}
	} else if (second == 1) {
		printf("here2"); fflush(stdout);
		ret = sscanf(line1, "\[1518-%d-%d %d:%d] falls asleep", &d1, &d2, &t1, &t2);
		if (ret == 4) {
			startSleep = t2;
			printf("setting startSleep for garda %d @ %d\n", gardaMAP[curGarda].hashnum, startSleep);
		}
	} else if (third == 1) {
		printf("here3"); fflush(stdout);
		ret = sscanf(line1, "\[1518-%d-%d %d:%d] wakes up", &d1, &d2, &t1, &t2);
		printf("here5"); fflush(stdout);
		if (ret == 4) {
			printf("ret 4... %d\n", curGarda); fflush(stdout);
			//printf("loop for garda %d (%d -> %d)\n", gardaMAP[curGarda].hashnum, startSleep, t2); fflush(stdout);
			for (int i = startSleep; i < t2; i++) {
				gardaSleep[curGarda][gardaPos2[curGarda]][i] = 1;
			}
		}	
	}
		leny++;

	} //while
	fclose(a);
	gardaPos2[curGarda]++;

	int maxMinuteOverall = 0;
	int maxMinute = 0;
	int gardaMax = 0;
	for (int i = 0; i < numGardai; i++) {
		//printf("\nhereXXX i is %d gardaPos2[i](hours): %d\n", i, gardaPos2[i]);
		int countMin[61] = {0};
		int totsleep = 0;
		for (int k = 0; k < 60; k++) {
			for (int j = 0; j < gardaPos2[i]; j++) {
				if (gardaSleep[i][j][k] == 1) {
					countMin[k]++;
					totsleep++;
				}
			}
		}
		int max = 0; int countMinMax = 0;
		for (int z = 0; z < 60; z++) {
			if (countMin[z] > max) {max = countMin[z]; countMinMax = z;}
		}
		printf("garda (%4d):%4d is %4d (max times == %4d) (totsleep: %4d) (tothours: %4d)\n", i, gardaMAP[i].hashnum, countMinMax, max, totsleep, gardaPos2[i]);

		if (max > maxMinuteOverall) {maxMinute = countMinMax; gardaMax = gardaMAP[i].hashnum; maxMinuteOverall = max;}
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d * %d == %d\n", maxMinute, gardaMax, maxMinute * gardaMax);
}
