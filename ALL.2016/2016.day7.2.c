#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <string>
#include <vector>
#include <unistd.h>

using namespace std;
#define getchar()
int lenx, leny;
#define DAY "		2016 day7 part2\n"
#undef _DEBUG_
long tot;

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
	int tot = 0;
while(1) 
{
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';

	
			int evenodd = 0;
			vector <string>  partsGood;
			vector <string> partsBad;
			char *in = strtok(line1, "\\[\\]");
			while (in != NULL) {
				if (evenodd % 2 == 0) { 
					partsGood.push_back(in);
				} else {
					partsBad.push_back(in);
				}
				evenodd++;
				in = strtok(NULL, "\\[\\]");
			}
			vector <string> abbaGood;
			vector <string> abbaFlip;
			for (int ii = 0; ii < partsGood.size(); ii++) {
				string pbG = partsGood[ii];
				for (int kk = 0; kk < pbG.length()-2; kk++) {
					if (pbG[kk] == pbG[kk+2] && pbG[kk] != pbG[kk+1]) {
						abbaGood.push_back(pbG.substr(kk, 3));
						char abG[4];
						abG[0] = pbG[kk+1];
						abG[2] = pbG[kk+1];
						abG[1] = pbG[kk];

						string abGS = string(abG, 0, 3);
						abbaFlip.push_back(abGS);
					}
				}
			}


			vector <string> abbaBad;
			for (int ii = 0; ii < partsBad.size(); ii++) {
				string pbB = partsBad[ii];
				for (int kk = 0; kk < abbaFlip.size(); kk++) {
					if (pbB.find(abbaFlip[kk]) != string::npos) {
						tot++;
						goto after;
					}
				}
			}
after:
	continue;
}
fclose(a);

	fflush(stdout); dup2(fd, 1);
	printf("**count [%d]\n", tot);
	printf("\n");
    	return 0;
} 
