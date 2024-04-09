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
	fclose(a);
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
	int time = 0;
	struct worker {
		int jobid;
		int timeleft;
		int Nidle;
		int Q;
	};
	struct worker workers[10] = {0};
	//for (int i = 0; i < (int)strlen(ans); i++) 
	printf("GJFMDHNBCIVTUWEQYALSPXZORK\n");
	while (1) {

		if (time == 0) { //G J
			workers[0].jobid = 'G' -65;
			workers[0].timeleft = 'G' -65+61;
			workers[0].Q = 0;
			workers[0].Nidle = 1;
///////////////////////////////////////////
			workers[1].jobid = 'J' -65;
			workers[1].timeleft = 'J' -65+61;
			workers[1].Q = 1;
			workers[1].Nidle = 1;
			time++;
			continue;
		}


		for (int i = 0; i < 5; i++) {
			if (workers[i].timeleft != 0) {
				workers[i].timeleft--;
			}
			if (workers[i].timeleft == 0) {
				if (workers[i].Nidle == 1) {
					workers[i].Nidle = 0;
					QFROM[workers[i].jobid] = workers[i].Q;
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
				int found22 = 0;
				for (int s = 0; s < 5; s++) {
					if (workers[s].Nidle == 1 && workers[s].jobid == l) {
						found22 = 1; break;
					}
				}
				if (found22 == 1) {b=1; break;}
				for (int k = 0; k < after[l].topos; k++) {
					if (after[l].to[k] == z)  {
						found++; break;
					}
				}
			}

			if (after[l].topos != 0 && found == after[l].topos && b == 0) {
				printf("NEXT: %c time %d\n", l+65, time); //getchar();
				for (int i = 0; i < 5; i++) {
					if (workers[i].Nidle == 0) {
						workers[i].jobid = l;
						workers[i].timeleft = l +61;
						workers[i].Q = i;
						workers[i].Nidle = 1;
						printf("%c -> worker %d (%d)\n", l+65, i, time);
						break;
					}
				}
						
			}
		}
		int found55 = 0;
		for (int i = 0; i < 5; i++) {
			if (workers[i].Nidle == 1) {found55 = 1; break;}
		}
		if (found55 == 0) { break; }
		time++;
	}
	printf("***time %d\n", time);
}
