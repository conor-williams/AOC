#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("2018 Day5.1\n"); fflush(stdout);

	int SIZE = 60000;
        char line1[SIZE];

int leny = 0;
int min = SIZE;
while (1) 
{
        fgets(line1, SIZE, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
 	line1[strlen(line1)-1] = '\0';
	leny++;
}
	char newString[SIZE];
	int newStringPos = 0;
{
	int char1 = 'a';
	int char2 = 'A';
	int tot = 0;
	char line1saf[SIZE];
	strcpy(line1saf, line1);
	while ((int) char1 <=(int)'z') {
		tot = 0;
		newStringPos = 0;
		strcpy(line1, line1saf);
		printf("here2"); fflush(stdout);
		//memset(newString, 0, sizeof(newString));
		printf("here3"); fflush(stdout);
		for (int k = 0; k < strlen(line1); k++) {
			if (line1[k] == char1 || line1[k] == char2) {
			} else {
				newString[newStringPos] = line1[k]; newStringPos++;
				tot++;
			}
		}
		printf("here4"); fflush(stdout);
		printf("%c%c: %d\n", char1, char2, tot);
		if (tot < min) {min = tot;}
		char1++;
		char2++;
		
		newString[newStringPos] = '\0';	
		printf("newString: %s\n", newString); 
		
		for (int i = 0; i < strlen(newString) -1; i++) {
			if (i < 0) {i = 0;}
			int g = 0;
			for (g = i; g >= 0; g--) {
				if (newString[g] != '0') {break;}
			}
			int f = 0;
			if (newString[g] == '0') {
				f = 0;
				for (f = g; f <strlen(newString) -1; f++) {
					if (newString[f] != '0') {break;}
				}

			} else {f = g;}
			int s;
			for (s = f+1; s < strlen(newString); s++) {
				if (newString[s] != '0') {break;}
			}

			if (islower((int)newString[f]) && isupper((int)newString[s])) {
				if (newString[f] == tolower(newString[s])) {
					//printf("here1... newString[f] %c V %c newString[s]", newString[f], newString[s]);
					newString[f] = '0'; newString[s] = '0';
					//printf("after1 [%s]\n", newString);
				}
			} else if (isupper((int)newString[f]) && islower((int)newString[s])) {
				if (newString[f] == toupper(newString[s])) {
					//printf("here2... newString[f] %c V %c newString[s]", newString[f], newString[s]);
					newString[f] = '0'; newString[s] = '0';
					//printf("after2 [%s]\n", newString);
				}
			}
		}
		int count = 0;
		for (int i = 0; i < strlen(newString); i++) {
			if (newString[i] != '0') {count++;}
		}
		if (count < min) {min = count;}
	//	printf("***polymer len [%d]\n", count);
	}
}
	printf("***polymer len MIN [%d]\n", min);
}
