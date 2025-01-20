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
struct build deps[26];

struct mymax {
	int max;
	int l1;
	int l2;
};
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
	for (int i = 0; i < 26; i++) {
		deps[i].from = i+65;
		deps[i].fi = i;
		deps[i].topos = 0;
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
	for (int l = 0; l < 26; l++) {
		for (int i = 0; i < 26; i++) {
			for (int k = 0; k < after[i].topos; k++) {
				if (after[i].to[k] == l) {
					deps[l].to[deps[l].topos] = i; deps[l].topos++; break;
				}
			}
		}
	}
	for (int l = 0; l < 26; l++) {
		BubbleSort(deps[l].to, deps[l].topos);
	}
	printf("DEPS\n");
	for (int l = 0; l < 26; l++) {
		printf("%c:", l+65);
		for (int k = 0; k < deps[l].topos; k++) {
			printf(" %c ", deps[l].to[k]+65);
		}
		printf("\n");
	} getchar();

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
	int time = -1;
	struct worker {
		int jobid;
		int timeleft;
		int Nidle;
		int Q;
	};
	struct worker workers[10] = {0};
	//for (int i = 0; i < (int)strlen(ans); i++) 
	while (1) {
		printf("GJFMDHNBCIVTUWEQYALSPXZORK\n");
		//printf("LOOKING AT [%c] qnum : %d\n", ans[i], qnum);

		time++;
		if (time == 0) { //G
			qnum = 0;
			worker[0].jobid = 'G' -65;
			worker[0].timeleft = 'G' -65+61;
			worker[0].Q = 0;
			worker[0].Nidle = 1;
///////////////////////////////////////////
			worker[1].jobid = 'J' -65;
			worker[1].timeleft = 'J' -65+61;
			worker[1].Q = 0;
			worker[1].Nidle = 1;
			continue;
		}

		for (int i = 0; i < 5; i++) {
			if (worker[i].timeleft != 0) {
				worker[i].timeleft--;
			} else {
				if (worker[i].idle == 1) {
					worker[i].idle = 0;
					QFROM[worker[i].jobid] = worker.Q;
				}
			}
		}
		if (time == 1200) {break;}

		QsPos = 0;

		for (int l = 0; l < 26; l++) { //letter
			int found = 0; int b = 0;
			for (int z = 0; z < 26; z++) { //done
				if (QFROM[z] == -1) {continue;}
				if (l == z) {b = 1; break;}
				for (int k = 0; k < after[l].topos; k++) {
					if (after[l].to[k] == z)  {
						found++; break;
					}
				}
			}

			if (found == after[l].topos && b == 0) {
				printf("NEXT: %c time %d\n", l+65, time); getchar();
				Qs[QsPos] = l; QsPos++;
			}
		}
		for (int r = 0; r < QsPos; r++) {
			QFROM[Qs[r]] = qnum;
		}
		if (QsPos == 1) {
			Q5Count[0] += Qs[0] + 61;
		} else if (QsPos <= 5) {
			int max = 0;
			for (int j = 0; j < QsPos; j++) {
				if (Qs[j] > max) {max = Qs[j];}
			}
			for (int o = 0; o < 5; o++) {
				Q5Count[o] += max+61;
			}
		} else if (QsPos > 5 && QsPos < 10) {
			int tosort[10];
			for (int q = 0; q < QsPos; q++) {
				tosort[q] = Qs[q];
			}
			sort(tosort, tosort+QsPos);
			struct mymax maxes[1000]; int maxesPos = 0;
			do {
				int len = QsPos/2;
				struct mymax sums[len+1];
				
				for (int r = 0; r < len; r++) {
					sums[r].max = tosort[2*r] + tosort[(2*r)+1];
					sums[r].l1 = tosort[2*r];
					sums[r].l2 = tosort[(2*r)+1];
				}
				struct mymax max; max.max = 9999;
				for (int s = 0; s < len; s++) {
					if (sums[s].max < max.max) {max.max = sums[s].max; max.l1 = sums[s].l1; max.l2 = sums[s].l2;}
				}
				int found00 = 0;
				for (int t = 0; t < maxesPos; t++) {
					if (max.max == maxes[t].max) {
						found00 = 1; break;
					}
				}
				if (found00 == 0) {
					maxes[maxesPos].max = max.max; 
					maxes[maxesPos].l1 = max.l1 ; 
					maxes[maxesPos].l2 = max.l2; 

maxesPos++;
				}
			} while (next_permutation(tosort, tosort+QsPos));
			struct mymax min; min.max = 9999;
			for (int u = 0; u < maxesPos; u++) {
				if (maxes[u].max < min.max) {min.max = maxes[u].max; min.l1 = maxes[u].l1; min.l2 = maxes[u].l2;}
			}
			printf("MIN is %d\n", min.max+61+61); 
			printf("LETTER SUM is %d\n", min.l1 + min.l2 + 122); getchar();
			printf("LETTERS are %c %c\n", min.l1+65, min.l2+65); getchar();
		//	for (int o = 0; o < 5; o++) {
		//		Q5Count[o] += min+61+61;
		//	}
		}
		getchar();

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
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4) + ('S'-4) + ('P' - 4) + ('X' - 4) + ('Z' - 4) + ('O' - 4) + ('R' -4) + ('K'-4));
	printf("%d\n", ('G'-4));
	printf("%d\n", ('G'-4) + ('M' - 4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4) + ('S'-4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4) + ('S'-4) + ('P' - 4) );
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4) + ('S'-4) + ('P' - 4) + ('X' - 4) );
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4) + ('S'-4) + ('P' - 4) + ('X' - 4) + ('Z' - 4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4) + ('S'-4) + ('P' - 4) + ('X' - 4) + ('Z' - 4) + ('O' - 4));
	printf("%d\n", ('G'-4) + ('M' - 4) + ('D' - 4) + ('I'-4) + ('Y'-4) + ('A' -4) + ('L'-4) + ('S'-4) + ('P' - 4) + ('X' - 4) + ('Z' - 4) + ('O' - 4) + ('R' -4));
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
