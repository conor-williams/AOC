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
	char ans[] = "GJFMDHNBCIVTUWEQYALSPXZORK";
	//char ans[] = "CABDFE";
getchar();
int Q5Count[50] = {0};

int QFROM[29];
	for (int z = 0; z < 26; z++) {
		QFROM[z] = -1;
	}
	for (int z = 0; z < 30; z++) {
		Q5Count[z] = 0;
	}

int Qs[20] = {0};
int QsPos = 0;
int qnum = 0;
	for (int i = 0; i < (int)strlen(ans); i++) {
		printf("GJFMDHNBCIVTUWEQYALSPXZORK\n");
		//printf("LOOKING AT [%c] qnum : %d\n", ans[i], qnum);

		if (i == 0) {
			qnum = 0;
			//Q5Count[0] = ans[i]-4;
			for (int o = 0; o < 10; o++) {
				Q5Count[0] = ans[i]-4;
			}
		} else if (i==1){
			qnum = 1;
			Q5Count[1] += ans[i]-4; 
			for (int o = 0; o < 10; o++) {
				Q5Count[o] = ans[i]-4;
			}
		} else if (i==25){
			qnum = 0;
			Q5Count[0] += ans[i]-4; 
		} else {
			Q5Count[qnum] += ans[i]-4; 
		}
		
		//printf("adding %d\n", ans[i]-4);
		QFROM[ans[i] - 65] = qnum;	
		//printf("Q5Count %d %d\n", qnum, Q5Count[qnum]);
		if (i == 25) {break;}
		int found = 0;
		QsPos = 0;
		for (int z = 0; z < 26; z++) {
			if (QFROM[z] == -1) {
			} else {
				for (int k = 0; k < all[z].topos; k++) {
					//printf("FORWARD [%c]\n", ans[i+1]);
					if (k==0 && (all[z].to[k] == ans[i+1]-65))  {
						found++;
						if (found >= 1) {
							Qs[QsPos] = QFROM[z]; QsPos++;
							if (found == 1) {
								qnum = QFROM[z];	 
							} else {
								QFROM[z] = qnum;
							}
							printf("found %c @same as %c FOR Q %d\n", ans[i+1], z+65, qnum);
							
						} getchar();
						//goto past;
					}
				}
			}
		}
past:
		if (found > 1) {
/*
			int max = 0;
			for (int r = 0; r < QsPos; r++) {
				if (Q5Count[Qs[r]] > max) {max = Q5Count[Qs[r]];}
			}
			int first = Q5Count[qnum]; 
			int alladd = 0;
			for (int r = 0; r < QsPos; r++) {
				 alladd += Q5Count[Qs[r]];
			}
			Q5Count[qnum] = alladd; 
*/
		}
		if (found == 0) {
		              int tosort[10];
                              for (int s = 0; s < 5; s++) {
                                            tosort[s] = Q5Count[s];
                               }
                               sort(tosort, tosort+5);
				if (tosort[0] == tosort[1]) {
					printf("SAME...\n"); //getchar();
				}
                                for (int s = 0; s < 5; s++) {
                                     if (Q5Count[s] == tosort[0]) {
                                           qnum = s; break;
                                     }
                               }

			//qnum++;
		}

	}
	for (int r = 0; r< 10; r++) {
		printf("Q5Count %d: %d\n", r, Q5Count[r]);
	}


	//sort(Q5Count, Q5Count+7);
	//int tosort[10];
	//for (int z = 0; z < 7; z++) {
		//tosort[z] = z;
	//}
	
	int nums[] = {0,1,2,3,4,5,6,7};
	for (int i = 2; i < 7; i++) {
		sort(nums, nums+7);
		do {
			int sum = 0;
			for (int r = 0; r<i; r++) {
				sum+=Q5Count[nums[r]];
			}
			if (sum == 1050) {
				for (int s =0; s < i; s++) {
					printf(" %d+ ", Q5Count[nums[s]] );
				}
				printf(" SUM: %d\n", sum); getchar(); goto end;
			}
				
		} while (next_permutation(nums, nums+8));
	}
end:
	return 0;
}





/*
                		for (int s = 0; s < 5; s++) {
                        		tosort[s] = Q5Pos[s];
                		}
                		sort(tosort, tosort+5);
                		for (int s = 0; s < 5; s++) {
                        		if (Q5Pos[s] == tosort[0]) {
						Q5[qnum][Q5Pos[qnum]] = all[ans[i]].to[k];	
					}
				}
*/
