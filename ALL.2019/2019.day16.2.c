#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <cmath>
#include <time.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
#include <vector>

using namespace std;

//#define getchar()
int lenx, leny;
#define DAY "		2019 day16 part2\n"
//#undef _DEBUG_
#define SIZE 653
//vector <int> base = {0,1,0,-1};
//int phases = 4;
//int len = 0;
//void genbase(int k, vector <int>base, int maxsize);

///vector <int>newbase;

int main(int argc, char **argv)
{
	//lenx = 0; //leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
	//time_t t = time(NULL); struct tm *tm = localtime(&t); printf("%s", asctime(tm));

        char line1[SIZE];
//while(1) {
	{
        fgets(line1, SIZE-1, a);
        if (feof(a)) {exit(0);}
	line1[strlen(line1) -1]='\0';
	int line1len /*lenx*/ = (int)strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif

	//int line1len = (int)strlen(line1);
	//printf("line1 is [%s]\n", line1); getchar();

/*
	char *line2 = (char *)malloc(line1len*20001);
	char *line4 = (char *)malloc(line1len*20001);
	line2[0] = '\0';
	
	strcpy(line4, line1);
	for (int i = 0; i < 15 ; i++) {strcat(line2, line4); strcpy(line4, line2);}
	free(line4);
*/

		
	lenx = 10000 * line1len;
	char ans2[8]; //int r = 0;
	for (int m = 0; m < 7; m++) {
		//printf("%c", line1[m]);
		ans2[m] = line1[m];
	}
	ans2[7] = '\0';

	int ans2I = atoi(ans2);

	//printf("ans2I is %d\n", ans2I); fflush(stdout); getchar();
	char line3[lenx-ans2I+10] = "";
	char ans3[lenx-ans2I+10];
	int first = 1;
	for (int z = 0; z < 100; z++) {
		long long itot = 0;
		int k;
		for (k = lenx-1; k >= ans2I; k--) {
			int i = k;
			//for (int i = k; i < k+1; i++) {
			{
				if (first == 1) {
					itot += line1[i%line1len]-48;
				} else {
					itot += line3[i-ans2I]-48;
				}
			}

			//int oneRD = abs(itot) % 10;
			int oneRD = itot % 10;
			ans3[k-ans2I] = oneRD+48;
		}
		first = 2;
		ans3[k-ans2I] = '\0';
		strcpy(line3, ans3);
	}
	//free(line2);
	
	fflush(stdout); dup2(fd, 1);
	printf("**ans: [ ");
	for (int j = 0; j < 8; j++) {
		printf("%c", ans3[j]);
	}
	printf(" ]\n");
	}
	
fclose(a);

}

/*
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
*/
