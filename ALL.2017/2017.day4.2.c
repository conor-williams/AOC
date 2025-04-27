#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <algorithm>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;

int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("		2017 Day4.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[3000];

int leny = 0;
int valid = 0;
while (1) 
{
        fgets(line1, 2999, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
#ifdef _DEBUG_
 	printf("line1 %s\n", line1);
#endif
	int wordPos = 0;
	char *words[100];
	words[0] = strtok(line1, " ");
	do {
		wordPos++;
	} while ((words[wordPos] = strtok(NULL, " ")) != NULL);


	int found = 0;
	for (int i = 0; i < wordPos-1; i++) {
		for (int j = i+1; j < wordPos; j++) {
			if (strcmp(words[i], words[j]) == 0) {
				found = 1; break;			
			}
		}
	}
	
	int sArrayOrig[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	if (found == 0) {
		for (int i = 0; i < wordPos-1; i++) {
		    for (int j = i+1; j < wordPos; j++) {
			if (strlen(words[i]) != strlen(words[j])) {continue;}
			int sArray[20];
			for (int k = 0; k < 19; k++) {
				sArray[k] = sArrayOrig[k];
			}
			char newWord[100]; char origWord[100];
			strcpy(origWord, words[j]);
			next_permutation(sArray, sArray + (int)strlen(origWord));
			do {
				int l;
				for (l = 0; l < (int)strlen(origWord); l++) {
					newWord[l] = origWord[sArray[l]];
				}
				newWord[l] = '\0';
#ifdef _DEBUG_
				printf("comp %s V %s\n", words[i], newWord); 
#endif
				if (strcmp(words[i], newWord) == 0) {
					found = 1; goto end;			
				}
			} while (next_permutation(sArray, sArray + (int)strlen(origWord)));
		    }
		}
	}
end:
	if (found == 1) {
		printf("not valid\n");
        } else {
		printf("is valid\n");
		valid++;
	}
		
	leny++;
}

	fflush(stdout); dup2(fd, 1);
	printf("***valid is [%d]\n", valid);
}

