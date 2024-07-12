#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <cmath>

#include <vector>

using namespace std;

#define getchar()
int lenx, leny;
#define DAY "2019 day16 part1\n"
#undef _DEBUG_
#define SIZE 1000
//int base[] = {0,1,0,-1};
vector <int> base = {0,1,0,-1};
int phases = 4;
//vector <int>newbase;
int len = 0;
void genbase(int k, vector <int>base, int maxsize);

vector <int>newbase;

deque <char> line3;
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

	int line1len = (int)strlen(line1);
	//for (int i = 0; i < 10000; i++) { for (int j = 0; j < line1len; j++) { line3.push_back(line1[j]); } }
	char line2[line1len*10001];
	for (int i = 0; i < 10000; i++) {strcat(line2, line1);}

	printf("before genbase...\n"); fflush(stdout);
	//lenx = line3.size();
	lenx = (int)strlen(line2);
	//for (int i = 0; i < lenx; i++) { genbase(i, base, lenx); if (i % 1000 == 0) {printf("%d\n", i);} }
		
	printf("after genbase..lenx is %d.\n", lenx); fflush(stdout);
	//printf("line3 size is %d\n", (int)line3.size());
	//deque <char> ans;
	char ans3[lenx];
	
	//deque<char> line3Orig; line3Orig = line3;
	for (int z = 0; z < 100; z++) {
		//strcpy(ans3, line2);
		for (int k = 0; k < lenx ; k++) {
			int firstzero = 1;
			long long itot = 0;
			genbase(k, base, lenx);
			int siz = (int)newbase.size();
			//if (siz == 0) {printf("k: %d siz\n", k); exit(0);}
			//printf("line1len*siz is %d\n", line1len*siz);

			int end = line1len*siz > lenx? lenx: line1len*siz;

			for (int i = 0; i < end; i++) {
				int nb = newbase[i % siz];
				switch (nb) {
					case 0:
						if (k > 100) {
							i+=k;
							if (firstzero == 1) { i--; firstzero = 2; }
						}
						break;
					case 1:
						itot += line2[i]-48;
						break;
					case -1:
						itot -= line2[i]-48;
						break;
				}
			}

			long long times = 10000/siz;
			if (times != 0) {
				itot = itot * times;
				for (int i = times * (line1len*siz); i < lenx; i++) {
					itot += (line2[i]-48) * newbase[i %siz];
				}
			} else {
				for (int i = line1len*siz; i < lenx; i++) {
					itot += (line2[i]-48) * newbase[i %siz];
				}
			}
				
			int oneRD = abs(itot) % 10;
			ans3[k] = oneRD+48;
			if (k % 10000 == 0) {printf("k is %d\n", k);}
		}
		ans3[lenx] = '\0';
		if (z+1 == 100 || z+1 == 1 || z+1 == 2) {
			char ans2[10];
			printf("FIRST 7: [ "); fflush(stdout);
			int r = 0;
			for (int m = 0; m < 7; m++) {
				printf("%c", ans3[m]);
				ans2[r++] = ans3[m];
			}
			ans2[7] = '\0';
			char *pEnd;
			long long ans2ll = strtoll(ans2, &pEnd, 10);
			printf(" ]\n");

			printf("ANS: [ ");
			for (int j = ans2ll; j < ans2ll+8; j++) {
				printf("%c", ans3[j]);
			}
			printf(" ]\n");
			
		}
		strcpy(line2, ans3);
	}
	
}
fclose(a);
}

void genbase(int k, vector <int>base, int maxsize) {
	if (k == 0) {
		newbase = base;
	} else if (k != 0) {
		newbase.clear();
		for (int i = 0; i < (int)base.size(); i++) {
			for (int q = 0; q <= k; q++) {
				newbase.push_back(base[i]);
				if ((int)newbase.size() > maxsize+10) {break;}
			}
			
		}
	}
	int z1 = newbase[0]; newbase.erase(newbase.begin()); newbase.push_back(z1);
	while ((int)newbase.size() > maxsize) { newbase.pop_back(); }
}
