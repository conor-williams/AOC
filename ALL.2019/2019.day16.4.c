#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <vector>

using namespace std;

#define getchar()
long long lenx, leny;
#define DAY "2019 day16 part1\n"
#undef _DEBUG_
#define SIZE 1000
//int base[] = {0,1,0,-1};
vector <int> base = {0,1,0,-1};
int phases = 4;
//vector <int>newbase;
int len = 0;
void genbase(int k, vector <int>base);

vector <int>newbase;
vector <int>test1;

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
while(1) {
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = (int)strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif

	char line2[10010 * lenx];
	strcpy(line2, "");
	for (int i = 0; i < 10000; i++) {
		strcat(line2, line1);
	}

	char ans[lenx*10012];
	strcpy(ans, "");
	
	lenx = (int)strlen(line2);
	//printf("before genbase\n"); //for (int i = 0; i < lenx; i++) { genbase(i, base); }

	printf("lenx is %lld\n", lenx);
		
	for (int z = 0; z < 100; z++) {
		for (int k = 0; k < lenx ; k++) {
			long long itot = 0;
			genbase(k, base);
			int siz = (int)newbase.size();
			//printf("siz is %d\n", siz);
			for (int i = 0; i < lenx; i++) {
				long long q1 = line2[i] -48;
				long long q2 = newbase[i % siz];
				long long vali = (q1 * q2);
				itot += vali;
			}
			int oneRD = abs(itot) % 10;
			ans[k] = oneRD+48;
			if (k % 10000 == 0) {printf("k is %d\n", k);}
		}
		ans[lenx] = '\0';
		if (z+1 == 100 || z+1 == 1 || z+2 == 1) {
			char ans2[10];
			printf("FIRST 7: [ ");
			for (int m = 0; m < 7; m++) {
				printf("%c", ans[m]);
				ans2[m] = ans[m];
			}
			ans2[7] = '\0';
			char *pEnd;
			long long ans2ll = strtoll(ans2, &pEnd, 10);
			printf(" ]\n");

			printf("ANS: [ ");
			for (long long j = ans2ll; j < ans2ll+8; j++) {
				printf("%c", ans2[j]);
			}
			printf(" ]\n");
			
		}
		strcpy(line2, ans);
	}
	
}
fclose(a);
}

void genbase(int k, vector <int>base) {
	if (k == 0) {
		newbase = base;
	} else if (k != 0) {
		newbase.clear();
		for (int i = 0; i < (int)base.size(); i++) {
			for (int q = 0; q <= k; q++) {
				newbase.push_back(base[i]);
			}
		}
	}
	int z1 = newbase[0]; newbase.erase(newbase.begin()); newbase.push_back(z1);

}
