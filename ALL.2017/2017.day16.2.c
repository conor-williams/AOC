#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include <unistd.h>

//60 cycle pos 40
using namespace std;

vector <char> V;
int tot = 0;
#define SIZE 50000
char line1[SIZE];
char line1Orig[SIZE];
#ifdef EX1
	char start[] = "abcde";
#else
	char start[] = "abcdefghijklmnop";
#endif
int main(int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day16.2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	//printf("%s\n", start);
	V.clear();
	for (int i = 0; i < (int)strlen(start); i++) {
		V.push_back(start[i]);	
	}

int leny = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
// 	printf("line1 %s\n", line1);


//s1,x3/4,pe/b
	strcpy(line1Orig, line1);
	char strings[200][30];
	for (int i = 0; i < 100; i++) {
		//if ((i % 100000) == 0) {printf("%d\n", i);}
		char *first = strtok(line1, ",\0");
		char num1S[10]; int num1, num2;
		char let1, let2;
		char tmp1; char tmp2;
		do {
			switch (first[0]) {
				case 's':
					first[0] = ' ';
					rotate(V.begin(), V.begin()+V.size()-atoi(first), V.end());
					break;
				case 'x':
					sscanf(first, "x%[^/]/%d", num1S, &num2);
					num1 = atoi(num1S);
					//printf("num1 is %d]\n", num1);
					//printf("num2 is %d]\n", num2);
					tmp1 = V[num1];
					V[num1] = V[num2];
					V[num2] = tmp1;
					break;
				case 'p':
					sscanf(first, "p%c/%c", &let1, &let2);
					int pos1, pos2;
					int pos = 0;
					for (auto it = V.begin(); it != V.end(); it++) {
					       if (*it == let1) {pos1 = pos;}
					       if (*it == let2) {pos2 = pos;}
						pos++;
					}
					tmp2 = V[pos2];
					V[pos2] = V[pos1];
					V[pos1] = tmp2;
					break;	
			}
		} while ( (first = strtok(NULL, ",\0")) != NULL);
		///for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); 
		char newStr[100] = "";
		char newStr2[98] = "";
		for (auto it = V.begin(); it != V.end(); it++) { strcpy(newStr2, newStr); sprintf(newStr, "%s%c", newStr2, *it); }
		strcpy(strings[i], newStr);
		//printf("newStr is %s\n", newStr);
		if (strcmp(newStr, start) == 0) {printf("cycle detected @ %d\n", i+1);
			int pos = -1;
			printf("pos i want is %d \n", pos = ((unsigned long long)1000000000 % 60));
			fflush(stdout); dup2(fd, 1);
			printf("**ans: %s\n", strings[pos-1]);
			exit(0);
			//printf("strings[pos] is %s\n", strings[pos]);
			//printf("strings[pos] is %s\n", strings[pos+1]);
		}
		strcpy(line1, line1Orig);
	}
	leny++;
}
	fclose(a);
	for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); 
	return 0;
}
