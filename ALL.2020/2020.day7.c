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
	int containspos;
};
FILE *a;
int checkBAG(int mypos);
int bagpos = 0;
struct bag bags[800] = {0};
int count = 0;
int already[1000];
int alreadyPos = 0;

int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2020 Day7 Part 1\n"); fflush(stdout);

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
			line2[pos] = ':'; pos++;
		} else if (isdigit((int)line1[i]) && isdigit((int)line1[i+1])) {
			i+=1;
			line2[pos] = ':'; pos++;
		} else if (isdigit((int)line1[i])) {
			line2[pos]=':'; pos++;
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
	printf("%s\n", line2); fflush(stdout); 
	int found = 0;
	for (int i = 0; i < strlen(line2); i++) {
		if (line2[i] == ':') {
			found = 1; break;
		}
	}
	if (found == 1) {
		char *ret1 = strtok(line2, ":");
		strcpy(bags[bagpos].bagcolor, ret1); 
		while ((ret1 = strtok(NULL, ":")) != NULL) {
			strcpy(bags[bagpos].contains[bags[bagpos].containspos], ret1);
			bags[bagpos].containspos++;
		}
	} else {
		strcpy(bags[bagpos].bagcolor, line2); 
	}
		
	bagpos++;
}
fclose(a);

printf("bagpos is %d\n", bagpos); getchar();
for (int i = 0; i < bagpos; i++) {
	already[alreadyPos] = i;
	alreadyPos++;
	if (checkBAG(i)) {count++;}
	printf("___________%d---------------\n", i);
}

	printf("***count %d\n", count);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);
}
int checkBAG(int mypos) {
	printf("bagcolor: [%s]\n", bags[mypos].bagcolor);
	if (strcmp("shinygold", bags[mypos].bagcolor) == 0) {
		printf("found shiny gold count static\n");
		//count++;
	}
	for (int j = 0; j < bags[mypos].containspos; j++) {
		printf("	[%s]\n", bags[mypos].contains[j]);
		if (strcmp("shinygold", bags[mypos].contains[j]) == 0) {
			printf("found [here]shiny gold count^\n");
			return 1;
			break;
		}
		for (int k = 0; k < bagpos; k++) {
			if (strcmp(bags[mypos].contains[j], bags[k].bagcolor) == 0) {
				if (checkBAG(k)) {return 1;}
			}
		}
	}
	return 0;
}
