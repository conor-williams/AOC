#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int Q5Count[10];
void main() {
	char ans[] = "GJFMDHNBCIVTUWEQYALSPXZORK";
	//char ans[] = "CABDFE";

	Q5Count[0] = (int)ans[0]-4;
	printf("%d\n", Q5Count[0]); getchar();
	int Q1 = 0; int Q2 = 1;
	for (int i = 1; i < (int)strlen(ans)-1; i++) {
		int end = (int)strlen(ans)-4;
		int sum1, sum2;
		int didmod = 0;
		for (int z = end; z >= i; z--) {
			sum1 = 0; sum2 = 0;
			for (int k = end; k >= i; k--) {
				sum1 += (int)ans[k]-4;
			}
			sum2 += sum1 + (int)ans[end+1]-4;
			if (sum1 < (int)ans[end+2]-4 && sum2 > (int)ans[end+2]-4) {
				printf("here1..."); getchar();
				Q5Count[Q1] += sum2;
				Q5Count[Q2] += (int)ans[end+2]-4;
				didmod = 1;
				i = z;
			}
		}
		if (didmod == 0) {
			Q5Count[Q1] += ans[i];
			Q5Count[Q2] += ans[i+1];
			i++;
		}
		Q1+=2;
		Q2+=2;
			
	}	
	Q5Count[0] += (int)ans[strlen(ans)-1]-4;
	printf("Q5Count[0]: %d\n",  Q5Count[0]);
	printf("Q5Count[1]: %d\n",  Q5Count[1]);
	printf("Q5Count[2]: %d\n",  Q5Count[2]);
	printf("Q5Count[3]: %d\n",  Q5Count[3]);
	printf("Q5Count[4]: %d\n",  Q5Count[4]);
		
}
