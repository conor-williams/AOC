#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define getchar()
char ar[1000][50];
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day3\n"); fflush(stdout);
        char line1[1000];

int leny = 0;
while (1) {
        fgets(line1, 50, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
	strcpy(ar[leny], line1);
	leny++;
}
fclose(a);

char numOXposes[strlen(ar[0])];
for (int x = 0; x < strlen(ar[0]); x++) {
	int count0 = 0;
	int count1 = 0;
	int oneof = -1;
	for (int y = 0; y < leny; y++)
	{
		int cont = 0;
		for (int x1 = 0; x1 < x; x1++) {
			if (ar[y][x1] == numOXposes[x1]) {
				cont++;	
			}
		}
		//printf("%s cont %d x is: %d\n", ar[y], cont, x);
		if (x == 0 || cont == x) {
			if (ar[y][x] == '0') {count0++;} else {count1++;}
			//if (x == 4) {printf("4: %s\n", ar[y]); getchar();}
			oneof = y;
		} else {
			continue;
		}
	}
	if (count0+count1 == 1) {
		strcpy(numOXposes, ar[oneof]); break;
	}
	       if (count0 > count1) {
			numOXposes[x] = '0';
			//OX numbers are all with a zero
	} else if (count0 < count1) {
			numOXposes[x] = '1';
	} else if (count0 == count1) {
			numOXposes[x] = '1';
		//printf("error..."); exit(0);
	}
}
printf("numOXposes is %s\n", numOXposes);
getchar(); getchar(); printf("here1"); getchar();
char numCO2poses[strlen(ar[0])];
for (int x = 0; x < strlen(ar[0]); x++) {
	int count0 = 0;
	int count1 = 0;
	int oneof = -1;
	for (int y = 0; y < leny; y++)
	{
		int cont = 0;
		for (int x1 = 0; x1 < x; x1++) {
			if (ar[y][x1] == numCO2poses[x1]) {
				cont++;	
			}
		}
		//printf("%s cont %d x is: %d\n", ar[y], cont, x);
		if (x == 0 || cont == x) {
			if (ar[y][x] == '0') {count0++;} else {count1++;}
			oneof = y;
			//if (x == 4) {printf("4: %s\n", ar[y]); getchar();}
		} else {
			continue;
		}
	}
	if (count0+count1 == 1) {
		strcpy(numCO2poses, ar[oneof]); break;
	}
	
	       if (count0 > count1) {
			numCO2poses[x] = '1';
			//OX numbers are all with a zero
	} else if (count0 < count1) {
			numCO2poses[x] = '0';
	} else if (count0 == count1) {
			numCO2poses[x] = '0';
		//printf("error..."); exit(0);
	} 
}
printf("numCO2poses is %s\n", numCO2poses);


unsigned int num1 = 0, num2 = 0;
for (int x = 0; x < strlen(ar[0]); x++) {
        if (numCO2poses[x] == '1') {
                num1 = num1 | (1 << (strlen(ar[0]) - 1 - x));
        }
        if (numOXposes[x] == '1') {
                num2 = num2 | (1 << (strlen(ar[0]) - 1 - x));
        }
}
printf("***num1 %u num2 %u\n", num1, num2);
printf("***num1 * num2: %u\n", num1*num2);

}
