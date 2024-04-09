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
	char ans[] = "JFMDHNBCIVTUWEQYALSPXZOR";
	//char ans[] = "CABDFE";

int tosort[10];
//int notnorm = 0;
int Q5Count[10] = {0};
//int Q5[6][100] = {0};
//int Q5Pos[6] = {0};
int already[100] = {0};
int alreadyPos = 0;
//Q5[0][0] = 'G' - 65;
//Q5Pos[0]++;
//Q5[1][0] = 'J' - 65;
//Q5Pos[1]++;
//int Qs[6] = {0};

	int qnum = 0;
	for (int i = 0; i < (int)strlen(ans); i++) {
		int prevQnum = qnum;

		for (int s = 0; s < 5; s++) {
			tosort[s] = Q5Count[s];
		}
		sort(tosort, tosort+5);
		for (int s = 0; s < 5; s++) {
			if (Q5Count[s] == tosort[0]) {
				qnum = s; break;
			}
		}
		printf("at Q5 %d (%c) prevQnum:(%d)\n", qnum, ans[i], prevQnum);
		
		if (after[ans[i]-65].to[0] == ans[i-1]-65) {
			printf(" %c V %c Q:(%d) \n", ans[i], ans[i-1], prevQnum);
			Q5Count[prevQnum] += ans[i]-4;	
			qnum = prevQnum;
			already[alreadyPos] = ans[i]-65; alreadyPos++;
		} else {
			int found = 0;
			for (int y = 0; y < after[ans[i]-65].topos; y++) {
				for (int z = 0; z < alreadyPos; z++) {
					if (already[z] == after[ans[i]-65].to[y]) {
						found++; break;
					}
				}
			}
			if (found == after[ans[i]-65].topos) {
				for (int s = 0; s < 5; s++) {
					tosort[s] = Q5Count[s];
				}
				sort(tosort, tosort+5);
				for (int x = 0; x < 5; x++) {
					Q5Count[x] = tosort[4];
				}
			}
			//printf(" %c Q:(%d)\n", ans[i], qnum);
			Q5Count[qnum] += ans[i]-4;	
			already[alreadyPos] = ans[i]-65; alreadyPos++;
		}
		Q5[preQnum] = ans[i] - 65; Q5Pos[prevQnum]++;
			
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
