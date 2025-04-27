#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
struct bag {
	char bagcolor[100];
	char contains[40][100];
	int num[40];
	int containspos;
};
FILE *a;
int checkBAG(char *bag);
int bagpos = 0;
struct bag bags[800] = {0};
int count = 0;
int already[1000];
int alreadyPos = 0;
#define getchar() 

int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2020 Day7 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
        char line2[1000];
	
//int leny = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int pos = 0;
	for (int i = 0; i < strlen(line1); i++) {
		if (line1[i] == 'b' && line1[i+1] == 'a' && line1[i+2] == 'g' && line1[i+3] == 's') {
			i+=3;
		} else if (line1[i] == 'c' && line1[i+1] == 'o' && line1[i+2] == 'n' && line1[i+3] == 't' &&  line1[i+4] == 'a' && line1[i+5] == 'i' && line1[i+6] == 'n') {
			i+=6;
		} else if (isdigit((int)line1[i]) && isdigit((int)line1[i+1]) && isdigit((int)line1[i+2])) {
			i+=2;
			line2[pos] = ':';
			line2[pos+1] = line1[i];
			line2[pos+2] = line1[i+1];
			line2[pos+3] = line1[i+2];
			line2[pos+4] = ':'; pos+=5;
		} else if (isdigit((int)line1[i]) && isdigit((int)line1[i+1])) {
			i+=1;
			line2[pos] = ':';
			line2[pos+1] = line1[i];
			line2[pos+2] = line1[i+1];
			line2[pos+3] = ':'; pos+=4;
		} else if (isdigit((int)line1[i])) {
			line2[pos] = ':';
			line2[pos+1] = line1[i];
			line2[pos+2] = ':'; pos+=3;
		} else if (line1[i] == 'b' && line1[i+1] == 'a' && line1[i+2] == 'g') {
			i+=2;
		} else if (line1[i] == ',') {
		} else if (line1[i] == '.') {
		} else if (line1[i] == 'n' && line1[i+1] == 'o' && line1[i+2] == ' ' && line1[i+3] == 'o' &&  line1[i+4] == 't' && line1[i+5] == 'h' && line1[i+6] == 'e' && line1[i+7] == 'r') {
			i+=7;
		} else if (line1[i] == ' ') {
		} else {
			line2[pos] = line1[i];
			pos++;
		}
	}
	line2[pos] = '\0';
	printf("%s\n", line2); fflush(stdout);  getchar();
	int found = 0;
	for (int i = 0; i < strlen(line2); i++) {
		if (line2[i] == ':') {
			found = 1; break;
		}
	}
	if (found == 1) {
		char *ret1 = strtok(line2, ":");
/*
		bags[bagpos].num[mypos] = atoi(ret1); 
		ret1 = strtok(line2, ":");
*/
		strcpy(bags[bagpos].bagcolor, ret1); 
		int mypos = 0;
		while ((ret1 = strtok(NULL, ":")) != NULL) {
			bags[bagpos].num[mypos] = atoi(ret1); 
			ret1 = strtok(NULL, ":");
			strcpy(bags[bagpos].contains[bags[bagpos].containspos], ret1);
			bags[bagpos].containspos++;
			mypos++;
		}
	} else {
		strcpy(bags[bagpos].bagcolor, line2); 
	}
		
	bagpos++;
}
fclose(a);

printf("bagpos is %d\n", bagpos); getchar();
	count = checkBAG("shinygold");
	count--;
	printf("__i________---------------\n");
	printf("***count %d\n", count);
	
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);
}
int ind = 0;
int checkBAG(char *bag) {
	ind++; int mypos = 0;
	for (int k = 0; k < bagpos; k++) {
		if (strcmp(bag, bags[k].bagcolor) == 0) {
			printf("found bag (%s)\n", bag);
			mypos = k; break;	
		}
	}

	int tmpcount = 1;
	printf("containspos: %d\n", bags[mypos].containspos);
	for (int j = 0; j < bags[mypos].containspos; j++) {
		for (int z = 0; z < ind; z++) { printf("	"); }
		printf("return of %d * %s\n", bags[mypos].num[j], bags[mypos].contains[j]);
		tmpcount += bags[mypos].num[j] * checkBAG(bags[mypos].contains[j]);
		//count += bags[mypos].num[j] * checkBAG(bags[mypos].contains[j]);

	}
	ind--;
	return tmpcount;
}
