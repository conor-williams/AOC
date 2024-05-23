#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

struct build {
        char from;
        int fi;
        int to[26];
        int topos;
};
struct build all[26];
struct build after[26];

void BubbleSort(int a[], int array_size);
void BubbleSort(int a[], int array_size)
{
        int i, j, temp;
        for (i = 0; i < (array_size - 1); ++i)
        {
                for (j = 0; j < array_size - 1 - i; ++j )
                {
                        if (a[j] > a[j+1])
                        {
                                temp = a[j+1];
                                a[j+1] = a[j];
                                a[j] = temp;
                        }
                }
        }
}
int endpoint[20];
int endpointPos = 0;

#define _DEBUG_

int main(int argc, char**argv) {
        int leny = 0;
////////////////////////////
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2018 Day6.1\n"); fflush(stdout);
        int SIZE = 1000; char line1[SIZE];

        for (int i = 0; i < 26; i++) {
                after[i].from = i+65;
                after[i].fi = i;
                after[i].topos = 0;
        }
        for (int i = 0; i < 26; i++) {
                all[i].from = i+65;
                all[i].fi = i;
                all[i].topos = 0;
        }

        while (1)
        {
                fgets(line1, SIZE, a);
                if (feof(a)) break;
                //printf("line1 %s\n", line1);
                line1[strlen(line1)-1] = '\0';
                char F, T;
                int ret = sscanf(line1, "Step %c must be finished before step %c can begin.", &F, &T);
                if (ret != 2) {printf("ERROR"); exit(0);}
                all[F-65].to[all[F-65].topos] = T-65; all[F-65].topos++;
                after[T-65].to[after[T-65].topos] = F-65; after[T-65].topos++;
                leny++;

        }
        for (int i = 0; i < 26; i++) {
                if (all[i].topos != 0) {
                        BubbleSort(all[i].to, all[i].topos);
                }
                if (after[i].topos != 0) {
                        BubbleSort(after[i].to, after[i].topos);
                }
        }
        printf("run after\n"); for (int i = 0; i < 26; i++) { if (all[i].topos != 0) { printf("%c:", (char)(i+65)); for (int h = 0; h < all[i].topos; h++) { printf(" %c ", (char)(all[i].to[h]+65)); } printf("\n"); } }
        printf("run before\n"); for (int i = 0; i < 26; i++) { if (after[i].topos != 0) { printf("%c:", (char)(i+65)); for (int h = 0; h < after[i].topos; h++) { printf(" %c", (char)(after[i].to[h]+65)); } printf("\n"); } }

////////////////////////////
	char ans[] = "GJFMDHNBCIVTUWEQYALSPXZOR";
	//char ans[] = "CABDFE";

int count = 0;
int start = -5; int end;
int tosort[10];
int notnorm = 0;
int Q5Count[10] = {0};
int Q5[6][100] = {0};
int Q5Pos[6] = {0};
int already[100] = {0};
int alreadyPos = 0;
//Q5[0][0] = 'G' - 65;
//Q5Pos[0]++;
//Q5[1][0] = 'J' - 65;
//Q5Pos[1]++;
int Qs[6] = {0};
	printf("start < (int)strlen(ans) %d\n", start < (int)strlen(ans));
int qnum = 0;
while (start < (int)strlen(ans)) {
	if (notnorm == 1) {
	} else {
		start = start + 1;
		end = 5 + start;
	}
	if (end > (int)strlen(ans)) {end = strlen(ans);}
	printf(" %d -> %d\n", start, end-1);
	notnorm = 0;
	for (int i = start; i <= start; i++) {
		int prevQnum = qnum;
		int qnum = i%5;
/*
		for (int s = 0; s < 5; s++) {
			tosort[s] = Q5Pos[s];
		}
		sort(tosort, tosort+5);
		for (int s = 0; s < 5; s++) {
			if (Q5Pos[s] == tosort[0]) {
				qnum = s; break;
			}
		}
*/
		printf("at Q5 %d (%c)\n", qnum, ans[i]);
		if (after[ans[i]-65].topos > 1) {
			if (after[ans[i].to[0] == ans[i-1]-65) {
			Q5[prevQnum][Q5Pos[qnum]] = ans[i] - 65; Q5Pos[qnum]++;
			Q5Count[qnum] += ans[i]-4;	
			
			int pos = 0;
			for (int q = 0; q < after[ans[i]-65].topos; q++) {
				for (int r = 0; r<5; r++) {
					for (int t = 0; t < Q5Pos[r]; t++) {
						if (Q5[r][t] == after[ans[i]-65].to[q]) {
							int found = 0;
							for (int u = 0; u < alreadyPos; u++) {
								if (already[u] == Q5[r][t]) {
									found = 1; break;
								}
							}
							if (found == 0) {
								Q5Count[r] += Q5[r][t]+61;
								Qs[pos%5] = r; pos++;
								already[alreadyPos] = Q5[r][t]; alreadyPos++;
							} else if (found == 1) {
								Qs[pos%5] = r; pos++;
							}
								
						}
					}
				}
			}
			if (pos > 4) {printf("pos: %d\n", pos); pos=4;getchar();}
			if (pos < 4) {
				Qs[pos] = qnum; pos++;
			}
			already[alreadyPos] = ans[i]-65; alreadyPos++;
//			pos = 5;
//			for (int s = 0; s < 5; s++) {
//				tosort[s] = Q5Count[s];
//			}
			for (int s = 0; s < pos; s++) {
				tosort[s] = Q5Count[Qs[s]];
			}
			sort(tosort, tosort+pos);
			printf("WITHIN: pos(%d) \n", pos);
			for (int s = 0; s < pos; s++) {
				printf(" %d ", tosort[s]);
			} printf(" pos: (%d)\n", pos);
			for (int s = 0; s < pos; s++) {
				Q5Count[Qs[s]] = tosort[pos-1];
			}
			printf("Q5Counts \n");
			for (int b = 0; b < 5; b++) {
				printf(" %d:%d ", b, Q5Count[b]);
			}
			printf("\n");
			start = i+1;
			end = i+1+5;
			notnorm = 1;
			break;
		} else {
			Q5[prevQnum][Q5Pos[prevQnum]] = ans[i] - 65; Q5Pos[prevQnum]++;
			//Q5Count[(i-start)] += ans[i]-4;	
		}
	}
	count++;
}

	printf("Q5(BEF)Count[0]: %d\n",  Q5Count[0]);
//	Q5Count[0] += 'G'-4;
	Q5Count[0] += 'K'-4;
	printf("***(AFTJGK) Q5Count[0]: %d\n",  Q5Count[0]);
	printf("Q5Count[1]: %d\n",  Q5Count[1]);
	printf("Q5Count[2]: %d\n",  Q5Count[2]);
	printf("Q5Count[3]: %d\n",  Q5Count[3]);
	printf("Q5Count[4]: %d\n",  Q5Count[4]);
		
	return 0;
}
