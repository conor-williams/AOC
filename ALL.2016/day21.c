#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <deque>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int lenx, leny;
#define DAY "2016 day21 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 100
#define getchar()

vector <char> V;
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
	char LINE[20];
	if (strcmp (argv[1], "ex1.txt") == 0) {
		strcpy(LINE, "abcde");
	} else {
		strcpy(LINE, "abcdefgh");
	}
	for (int i = 0; i < (int)strlen(LINE); i++) {
		V.push_back(LINE[i]);
	}
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
	
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	int ret;
	int num1, num2; char let1, let2;
	ret = sscanf(line1, "swap position %d with position %d", &num1, &num2);
	if (ret == 2) {
		char tmp1 = V[num2];
		V[num2] = V[num1];
		V[num1] = tmp1;
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
		continue;
	}
	ret = sscanf(line1, "swap letter %c with letter %c", &let1, &let2);
	if (ret == 2) {
		int pos1, pos2;
		int pos = 0;
		for (auto it = V.begin(); it != V.end(); it++) {
			if (*it == let1) {pos1 = pos;} 
			if (*it == let2) {pos2 = pos;}
			pos++;
		}
		char tmp1 = V[pos2];
		V[pos2] = V[pos1];
		V[pos1] = tmp1;
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
		continue;
	}
	ret = sscanf(line1, "reverse positions %d through %d", &num1, &num2);
	if (ret == 2) {
		if (num1 > num2) {
			int tmp = num1;
			num1 = num2;
			num2 = tmp;
		}
		reverse(V.begin()+num1, V.begin()+num2+1);
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
		continue;

	}
	ret = sscanf(line1, "rotate right %d", &num1);
	if (ret == 1) {
		rotate(V.begin(), V.begin()+V.size()-num1, V.end());
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
		continue;
	}
	ret = sscanf(line1, "rotate left %d", &num1);
	if (ret == 1) {
		rotate(V.begin(), V.begin()+num1, V.end());
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
		continue;
	}
	ret = sscanf(line1, "move position %d to position %d", &num1, &num2);
	if (ret == 2) {
		int n1 = V[num1];
		V.erase(V.begin()+num1);
		if (num1 > num2) {
			V.insert(V.begin()+num2, n1);
		} else if (num1 < num2) {
			V.insert(V.begin()+num2, n1);
		} else {
			printf("ERROR"); exit(0);
		}
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
		continue;
	}
		
	ret = sscanf(line1, "rotate based on position of letter %c", &let1);
	if (ret == 1) {
		int pos1;
		int len = 1;
		for (auto it = V.begin(); it != V.end(); it++) {
			if (*it == let1) {pos1 = len;} 
			len++;
		}
	printf("pos1 is %d\n", pos1);
		if (pos1-1 >= 4) {
			int times = pos1+1;
			times = times % V.size();
			rotate(V.begin(), V.begin()+V.size()-(times), V.end());
		} else {
			rotate(V.begin(), V.begin()+V.size()-pos1, V.end());
		}
		
			
for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); getchar();
		continue;
	}
	printf("ERROR %s\n", line1); exit(0);
	leny++;
}
fclose(a);
	for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n");
	printf("***tot %ld END\n", tot); fflush(stdout);
} 
