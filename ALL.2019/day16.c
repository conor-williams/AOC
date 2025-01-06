#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <vector>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2019 day16 part1\n"
#undef _DEBUG_
#define SIZE 1000
//int base[] = {0,1,0,-1};
vector <int> base = {0,1,0,-1};
int phases = 4;
//vector <int>newbase;
int len = 0;
void genbase(int k, vector <int>base);
vector <int>newbase[1010];
int fd;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); fd = dup(1); close(1);
        char line1[SIZE];
while(1) {
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = (int)strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif

	int itot;
	char ans[2000];
	strcpy(ans, "");
	
	printf("before genbase\n");
	for (int i = 0; i < 1002; i++) {
		genbase(i, base);
	}
	printf("after genbase\n");
		
	for (int z = 0; z < 100; z++) {
		for (int k = 0; k < lenx ; k++) {
			int i;
			itot = 0;
			for (i = 0; i < lenx; i++) {
				//printf("line1[%d] is %c\n", i, line1[i]);
				int q1 = line1[i] -48;
				//printf("q1 is %d\n", q1);
				int q2 = newbase[k][i % (int)newbase[k].size()];
				//printf("q2 is %d\n", q2);
				int vali = (q1 * q2);
				//printf("vali is %d\n", vali);
				itot += vali;
			}
			int oneRD = abs(itot) % 10;
			//char itotStr[100]; printf("itot is %d\n", itot); sprintf(itotStr, "%d", itot);
			ans[k] = oneRD+48;
			//getchar();
		}
		ans[lenx] = '\0';
		if (z+1 == 100) {
			printf("after phase %d, ans is %s\n", z+1, ans); getchar();
			//printf("FIRST 8: [ ");
			dup2(fd, 1);
			printf("**ans: [ ");
			for (int m = 0; m < 8; m++) {
				printf("%c", ans[m]);
			}
			printf(" ]\n");
			exit(0);
		}
		strcpy(line1, ans);
	}
	
}
fclose(a);
}

void genbase(int k, vector <int>base) {
	if (k == 0) {
		newbase[k] = base;
	} else if (k != 0) {
		newbase[k].clear();
		for (int i = 0; i < (int)base.size(); i++) {
			for (int q = 0; q <= k; q++) {
				newbase[k].push_back(base[i]);
			}
		}
	}
	int z1 = newbase[k][0]; newbase[k].erase(newbase[k].begin()); newbase[k].push_back(z1);
	//printf("newbase[%d]: ", k);
	//for (int i = 0; i < (int)newbase[k].size(); i++) { printf("%d ", newbase[k][i]); } printf("\n"); getchar();

}
