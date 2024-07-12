#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <cmath>
#include <time.h>
#include <assert.h>

#include <vector>

using namespace std;

#define getchar()
int lenx, leny;
#define DAY "2019 day16 part2\n"
#undef _DEBUG_
#define SIZE 1000
vector <int> base = {0,1,0,-1};
int phases = 4;
int len = 0;
void genbase(int k, vector <int>base, int maxsize);

vector <int>newbase;

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	time_t t = time(NULL); struct tm *tm = localtime(&t); printf("%s", asctime(tm));

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

	char line2[line1len];
	for (int i = 0; i < 10000; i++) {strcat(line2, line1);}

	lenx = (int)strlen(line2);
	char ans3[lenx];
	char ans2[10];
	printf("\nFIRST 7:(z:%d) [ ", z); fflush(stdout);
	int r = 0;
	for (int m = 0; m < 7; m++) {
		printf("%c", line1[m]);
		ans2[r++] = line1[m];
	}
	ans2[7] = '\0';
	printf(" ]\n");

	char *pEnd;
	//long long ans2ll = strtoll(ans2, &pEnd, 10);
	int ans2I;
	sprintf(ans2I, "%s", ans2);
	for (int z = 0; z < 100; z++) {
		time_t t = time(NULL); struct tm *tm = localtime(&t); printf("z:%d [%s] %s\n", z, argv[1], asctime(tm));
		for (int k = 0; k < lenx ; k++) {
			int firstzero = 1;
			long long itot = 0;
			genbase(k, base, ans2I+8);
			int siz = (int)newbase.size();
			int end = line1len*siz > lenx ? lenx: line1len*siz;

			for (int i = ans2I; i < ans2I+8; i++) {
				int nb = newbase[i % siz];
				switch (nb) {
					case 0:
						/*
						if (k > 100) {
							i+=k;
							if (firstzero == 1) { i--; firstzero = 2; }
							assert(newbase[i % siz] == 0);
							if (i+1 < end) {
								assert(newbase[(i+1) % siz] != 0);
							}
						}
						*/
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
			if (times == 0) {times = 1;}
			{
				itot = itot * times;
				for (int i = times * (line1len*siz); i < lenx; i++) {
					//itot += (line2[i]-48) * newbase[i %siz];
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
			}
				
			int oneRD = abs(itot) % 10;
			ans3[k] = oneRD+48;
			if ((k % 10000) == 0) {printf("z:%d,k:%d [%s]\n", z, k, argv[1]);fflush(stdout);}
		}
		ans3[lenx] = '\0';
		if (z+1 == 100 || z+1 == 1 || z+1 == 2 || (z+1 % 10) == 0) {
			char ans2[10];
			printf("\nFIRST 7:(z:%d) [ ", z); fflush(stdout);
			int r = 0;
			for (int m = 0; m < 7; m++) {
				printf("%c", line1[m]);
				ans2[r++] = line1[m];
			}
			ans2[7] = '\0';
			printf(" ]\n");

			char *pEnd;
			long long ans2ll = strtoll(ans2, &pEnd, 10);
			if (ans2ll < line1len-8) {
				
				printf("ANS: [ ");
				for (int j = ans2ll; j < ans2ll+8; j++) {
					printf("z:[%d][%s]:%c", z, argv[1], ans3[j]);
				}
				printf(" ]\n");
			}
			
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
