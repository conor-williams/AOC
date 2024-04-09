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
getchar();
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
getchar();
int qnum = 0;


	for (int i = 0; i < strlen(ans); i++) {
		int qnum;
                for (int s = 0; s < 5; s++) {
                        tosort[s] = Q5Pos[s];
                }
                sort(tosort, tosort+5);
                for (int s = 0; s < 5; s++) {
                        if (Q5Pos[s] == tosort[0]) {
                                qnum = s; break;
                        }
                }

		Q5[qnum][Q5Pos[qnum]] = ans[i]-65; Q5Pos[qnum]++;
		
		for (int k = 0; k < all[ans[i] - 65].topos; k++) {
                	for (int s = 0; s < 5; s++) {
                        	tosort[s] = Q5Pos[s];
                	}
                	sort(tosort, tosort+5);
                	for (int s = 0; s < 5; s++) {
                        	if (Q5Pos[s] == tosort[0]) {
					Q5[qnum][Q5Pos[qnum]] = all[ans[i]].to[k];	
				}
			}
		}

	}
	return 0;
}
