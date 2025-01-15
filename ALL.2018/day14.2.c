#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
//int END = 2028;	//plus ten
//int END = 59414;
int END = 330121;
int tot = 0;
#define SIZE 299
char line1[SIZE];
int leny = 0;
void printit(char ar1[], int len, int poses[], int posesPos);
int rshift(int x, int n);
char rshift2(int n);

char ar[40000000];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2018 Day14.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[(int)strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	strcpy(ar, line1);
	leny++;
}
fclose(a);
	int poses[20];
	int posesPos = (int)strlen(ar);
	for (int i = 0; i < posesPos; i++) {
		poses[i] = i;
	}

	//printit(ar, (int)strlen(ar), poses, posesPos); getchar();
	char end[10];
	sprintf(end, "%d", END);
	int endLen = (int)strlen(end);
	int ans = 0;
	unsigned long long count = 0;
	int len = (int)strlen(ar);
	do {
		count ++;
		if (count %5000 == 0) {printf("count %llu\n", count);}
		int sum = 0; 
		for (int j = 0; j < posesPos; j++) {
			sum += ar[poses[j]] - 48;
		}

		char dig1 = (sum % 10) +48;
		char dig2 = (sum / 10) +48;

		if (dig2 != '0') {
			ar[len] = dig2;
			ar[len+1] = dig1;
			ar[len+2] = '\0';
			len += 2;
		} else {
			ar[len] = dig1;
			ar[len+1] = '\0';
			len+=1;
		}
		for (int j = 0; j < posesPos; j++) {
			poses[j] = (poses[j] + (ar[poses[j]]-48+1)) % len;
		}

/////////////////////
		int found = 0;
		for (int i = endLen-1; i >= 0; i--) {
			if (rshift2(i) == ar[len -i-1]) {
				found++;
			}  else {
				break;
			}
		}
		if (found == endLen) {
			ans = 1;
			break;
		}
/////////////////////
		found = 0;
		for (int i = endLen-1; i >= 0; i--) {
			if (rshift2(i) == ar[len -i-1-1]) {
				found++;
			}  else {
				break;
			}
		}
		if (found == (int)strlen(end)) {
			ans = 2;
			break;
		}
			
	} while (1);


	fflush(stdout); dup2(fd, 1);
	if (ans == 1) {
		printf("ANS1: ");
		printf("%d\n", (int)strlen(ar)-(int)strlen(end));
		printf("\n");
	} else if (ans == 2) {
		printf("ANS2: ");
		printf("%d\n", (int)strlen(ar)-(int)strlen(end)-1);
		printf("\n");
	}
}
void printit(char ar1[], int len, int poses[], int posesPos) {
	printf("AR: ");
	for (int i = 0; i < len; i++) {
		printf("%c,", ar1[i]);
	}
	printf("\n");
	printf("Poses: ");
	for (int i = 0; i < posesPos; i++) {
		printf(" %d, ", poses[i]);
	} 
	printf("\n");
}
	
char rshift2(int n) {
	switch(n){
//2018
/*
		case 0: return('4');
		case 1: return('1');
		case 2: return('4');
		case 3: return('9');
		case 4: return('5');
*/
		case 0: return('1');
		case 1: return('2');
		case 2: return('1');
		case 3: return('0');
		case 4: return('3');
		case 5: return('3');
	}
	return '0';
}
int rshift(int x, int n) {
	switch(n){
		case 0: return(x);
		case 1: return(x/10);
		case 2: return(x/100);
		case 3: return(x/1000);
		case 4: return(x/10000);
		case 5: return(x/100000);
		case 6: return(x/1000000);
		case 19: return(x/10000000000000000000ULL);
		default: if (x<10000000000000000000ULL) return(0);
				 printf("Sorry, not yet implemented\n");
			 return(0);
	}
}
