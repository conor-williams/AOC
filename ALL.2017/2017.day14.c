#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
unsigned long long tot = 0;
#define SIZE 20000
char line1[SIZE];
int theInts[100];
/*#define N 5*/
#define N 256
unsigned int int_to_bin(unsigned int k);
char * tobin(char xy);
char grid[130][130];
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day14.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
int leny = 0;
int pos = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1: %s\n", line1);
	int len = strlen(line1);
	line1[len] = '-';
	line1[len+1] = '\0';

	
	
	
	for (int i = 0; i < strlen(line1); i++) {
		if (line1[i] == ',') {
			theInts[i] = 44;
		} else {
			theInts[i] = line1[i];
		}
		pos++;
	}
	//theInts[(int)strlen(line1)] = '-';
	tot = 0;
	leny++;
}
	pos++;

	int posOrig = pos;
	for (int q = 0; q <= 127; q++) {
		if (q < 10) {
			theInts[(int)strlen(line1)] = q+48;
			pos = posOrig;
		} else if (q < 100) {
			theInts[(int)strlen(line1)] = (q / 10)+48;
			theInts[(int)strlen(line1)+1] = (q % 10)+48;
			pos = posOrig+1;
		} else {
			theInts[(int)strlen(line1)] = 1+48;
			theInts[(int)strlen(line1)+1] = ((q / 10)-10)+48;
			theInts[(int)strlen(line1)+2] = (q % 10)+48;
			pos = posOrig+2;
		}
		int plus[] = {17,31,73,47,23};
		int count = 0;
		for (int k = pos; k< pos+5; k++) {
			theInts[k] = plus[count];
			count++;
		}
		pos += count;

		//printf("LENGTHS: ");
		//for (int j = 0; j < pos; j++) {
		//		printf(" %d ", theInts[j]);
		///}
		//printf("\n");getchar();

		int initial[260];
		int initial2[10000];
		for (int k = 0; k < N; k++) {
			initial[k] = k;
		}

		int startpos; int skip = 0;
		startpos = 0; int len;
		for (int P = 0; P < 64; P++) {
			for (int z = 0; z < pos ; z++) {
				len = theInts[z];
				//printf("len is %d\n", len);
				memset(initial2, 0, N*(sizeof(int)));
				for (int k = 0; k < len; k++) {
					int p = (startpos+k)%N;
					initial2[p] = initial[p];
				}
				for (int k = 0 ; k < len; k++) {
					int p = (startpos+k)%N;
					int q = (startpos+((len-k-1)))%N;
					//printf("swap p V q (pos %d V pos %d\n", p, q);
					//printf("swap p V q (actual %d V actual %d\n", initial[p], initial2[q]);
					initial[p] = initial2[q];
				}
				startpos = (startpos+len+skip)%N;
				skip++;
				//printf("NUMS: ");
				//for (int j = 0; j < N; j++) {
				//	printf(" %d ", initial[j]);
				//}
				//printf("\n");
				//printf("new start %d\n", startpos);
				//printf("skip %d\n", skip);
			}
		}
		int ans[20] = {0};
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				ans[i] ^= initial[i*16+j];
			}
		}
		printf("ANS nearly");
		for (int i = 0; i < 16; i++) {
			printf(" %d: ", ans[i]);
			printf("%x ", ans[i]);
		}
		printf("\n");
		printf("ANS: ");
		for (int i = 0; i < 16; i++) {
			printf("%02x", ans[i]);
			
		}
		char cAns[40] = "";
		for (int i = 0; i < 16; i++) {
			sprintf(cAns, "%s%02x", cAns, ans[i]);
		}
		printf("\n[%s]\n", cAns);
		char bAns[130] = "";
		for (int i = 0; i < 32; i++) {
			sprintf(bAns, "%s%s", bAns, tobin(cAns[i]));
		}
		bAns[128] = '\0';
		printf("\n[%s]\n", bAns);
		//getchar();
		
		strcpy(grid[q], bAns);
	}
	int newCount = 0;
	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < 128; x++) {
			if (grid[y][x] == '1') {
				newCount++;
			}
		}
	}
	printf("\n**newCount: %d\n", newCount);
	printf("\nEND\n");
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", newCount);

}

char * tobin(char xy) {
	switch (xy) {
		case '0':
			return "0000";
			break;
		case '1':
			return "0001";
			break;
		case '2':
			return "0010";
			break;
		case '3':
			return "0011";
			break;
		case '4':
			return "0100";
			break;
		case '5':
			return "0101";
			break;
		case '6':
			return "0110";
			break;
		case '7':
			return "0111";
			break;
		case '8':
			return "1000";
			break;
		case '9':
			return "1001";
			break;
		case 'a':
			return "1010";
			break;
		case 'b':
			return "1011";
			break;
		case 'c':
			return "1100";
			break;
		case 'd':
			return "1101";
			break;
		case 'e':
			return "1110";
			break;
		case 'f':
			return "1111";
			break;
	}

}
unsigned int int_to_bin(unsigned int k) {
//    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_bin(k / 2)));
}

