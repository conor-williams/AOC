#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day4 part1 \n"
#undef _DEBUG_
long tot;
int compare_function(const void *a, const void *b);

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
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
	printf("LINE: %s\n", line1);
#ifdef _DEBUG_
#endif
        
//-------------------------
	char lets[200]; char checksum[6]; char sectorID[20]; int pos = 0;
	int a2z[26] = {0};
	sscanf(line1, "%[^\[]\[%[^]]", lets, checksum);
	printf("lets, checksum [%s],[%s]\n", lets, checksum);
	for (int i = 0; i < (int)strlen(lets); i++) {
		if (islower((int)lets[i])) {
			a2z[(int)lets[i]-97]++;
		} else if (lets[i] == '-') {
			//ignore	
		} else {
			sectorID[pos] = lets[i];	
			pos++;
		}
	}
	printf("a2z: ");
	for (int i = 0; i < 26; i++) {
		printf(" %d ", a2z[i]);
	}
	printf("\n");

	sectorID[pos] = '\0';
	int sectorIDI = atoi(sectorID);
	printf("sectorIDI: %d\n", sectorIDI);
	char calcCS[6];
	for (int i = 0; i < 5; i++) {
		int maxind = 0;
		for (int j=0; j< 26; j++) {
			if (a2z[j] > a2z[maxind]) {maxind = j;} 
		}
		printf("ass: %d ", a2z[maxind]);
		calcCS[i] = (char)(maxind+97); a2z[maxind] = 0;
		printf("calcs[i] is %c\n", calcCS[i]);
	}
	calcCS[5] = '\0';
	//qsort(calcCS, 5, 1, compare_function);
	if (strcmp(calcCS, checksum) == 0) {
		printf("MATCH: %s\n", calcCS);
		tot+= sectorIDI;
	} else {
		printf("NOTA: [%s] [%s]\n", calcCS, checksum);
	}
} 

	dup2(fd, 1);
	printf("****tot [%d]\n", tot);
    fclose(a);
}
int compare_function(const void *a, const void *b) {
	int *x = (int *)a; int *y = (int *)b;
	return *x - *y;
}
