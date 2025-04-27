#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
// needs cygwin package: words
int lenx, leny;
#define DAY "		2016 day4 part2\n"
#undef _DEBUG_
long tot;
FILE *b;

int isitaword(char *incoming);

int isitaword(char *incoming) {
	char line1[200];
	fseek(b, 0, SEEK_SET);
	while (1) {
        	fgets(line1, 199, b);
	        if (feof(b)) break;
		line1[strlen(line1) -1]='\0';
		if (strcmp(incoming, line1) == 0) {
			return 1;
		}
	}
	return 0;
}
	
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        //b = fopen("/usr/share/dict/words", "r"); 
	//if (b == NULL) {printf("ERROR: /usr/share/dist/words not here - install cygwin package: words\n"); exit(0);}
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[220];
	unsigned int tot =0;
while(1) 
{

        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	//printf("LINE: %s\n", line1);
#ifdef _DEBUG_
#endif
        
//-------------------------
	char lets[200]; char checksum[6]; char sectorID[20]; int pos = 0;
	char FP[200]; int posFP = 0;
	sscanf(line1, "%[^\[]\[%[^]]", lets, checksum);

	//printf("lets, checksum [%s],[%s]\n", lets, checksum);
	
	for (int i = 0; i < (int)strlen(lets); i++) {
		if (islower((int)lets[i])) {
			FP[posFP] = lets[i];
			posFP++;
		} else if (lets[i] == '-') {
			FP[posFP] = ' ';
			posFP++;
		} else {
			sectorID[pos] = lets[i];	
			pos++;
		}
	}
	FP[posFP] = '\0';
	//printf("FP [%s]", FP);
	char new123S[200];
	sectorID[pos] = '\0'; int sectorIDI = atoi(sectorID); //printf("  ID: %d ", sectorIDI);
	int cot = 0;
	for (int i = 0; i < 26; i++) {
		//printf("here1\n"); fflush(stdout);
	//int i = sectorIDI % 26;
		
		for (int j = 0; j < posFP; j++) {
			if (FP[j] != ' ' && FP[j] != '\0') {
				char new123 = ((FP[j] + i -97) % 26) + 97;
				new123S[j] = new123;
				//printf("%c", new123);
			} else if (FP[j] == ' ') {
				new123S[j] = ' ';
				//printf("%c", (char)' ');
			} else {
				new123S[j] = FP[j];
			}
				
		}
		new123S[posFP] = '\0';
		char safnew123S[200];
		strcpy(safnew123S, new123S);
		char *word1 = strtok(new123S, " ");
		char *word2 = strtok(NULL, " ");
		char *word3 = strtok(NULL, " ");
		//if (sectorIDI ==324 && ((word1 != NULL && isitaword((char *)word1)) || (word2 != NULL && isitaword((char*) word2)) || (word3 != NULL && isitaword((char *)word3)))) 
		if ((word1 != NULL && strncasecmp(word1, "north", 5)==0) || (word2 != NULL && strncasecmp(word2, "north", 5)==0) || (word3 != NULL && strncasecmp(word3, "north", 5) == 0))  {
			fflush(stdout); dup2(fd, 1);
			printf("**ans: %d\n", sectorIDI);
			exit(0);
			//printf("[%s] \n", safnew123S);
			cot = 1;
		} else {
			if (i == 25 && cot == 0) {
				//printf("NO WORDS\n");
			}
		}
	}

	leny++;
} 
	printf("am here...\n");
	

	fflush(stdout); dup2(fd, 1);
	printf("****tot [%d]\n", tot);
    fclose(a);
}
