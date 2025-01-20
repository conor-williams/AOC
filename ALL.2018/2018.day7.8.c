#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

using namespace std;

#define _DEBUG_
int backward(int one, int parent, int ignore);
int myget = 0;
int myget2 = 0;
struct build {
	char from;
	int fi;
	int to[26];
	int topos;
};
int takeoffW();
void putonW(int X);
void cleanoffW(int X);
int Q5[6][100] = {0};
int Q5Pos[6] = {0};
int Q5Count[6] = {0};
int NUMQ5 = 5;
int waiting[100] = {0};
int waitingPos = 0;

char password[100];
int passwordPos = 0;
struct build all[26];
struct build after[26];
//int recurseCon(int one);
int recurseCon2(int one, int dont);
char ans[3000];
int ansPos = 0;
void BubbleSort(int a[], int array_size);
struct q {
	int child;
	int parent;
};
struct q mainQ[200];
void BubbleSortBack(struct q a[], int array_size);
int mainQtot = {0};
char intransit[100];
int intransitPos = 0;
int qnum = 0;
int qnumFirst = 0;
void BubbleSortBack(struct q a[], int array_size)
{
	int i, j, temp, tempP;
	for (i = 0; i < (array_size - 1); ++i)
	{
		for (j = 0; j < array_size - 1 - i; ++j )
		{
			if (a[j].child < a[j+1].child)
			{
				temp = a[j+1].child;
				tempP = a[j+1].parent;
				a[j+1].child = a[j].child;
				a[j+1].parent = a[j].parent;
				a[j].child = temp;
				a[j].parent = tempP;
			}
		}
	}
}
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
int main(int argc, char **argv)
{
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

	//Step J must be finished before step H can begin.
	int leny = 0;
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

	int startpoint[20];
	int startpointPos = 0;
	for (int k = 0; k < 26; k++) {
		if (all[k].topos == 0) { continue; }
		int found = 0;
		for (int i = 0; i < 26; i++) {
			if (k == i) {continue;} if (all[i].topos == 0) {continue;}
			for (int h = 0; h < all[i].topos; h++) {
				if (k == all[i].to[h]) {found = 1;goto end;/*is in right too*/}
			}
		}
end:
		if (found == 0) {
			startpoint[startpointPos] = k; startpointPos++;
			printf("first is %c\n", (char)(k+65));
		}
	}


	for (int i = 0; i < 26; i++) {
		if (all[i].topos == 0) {continue;}
		for (int h = 0; h < all[i].topos; h++) {
			if (all[all[i].to[h]].topos == 0) {
				int found = 0;
				for (int z=0; z<endpointPos;z++) {
					if (endpoint[z] == all[i].to[h]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					endpoint[endpointPos] = all[i].to[h]; endpointPos++;
				}
			}
		}
	}
	printf("startpoints: "); for (int i = 0; i < startpointPos; i++) { printf(" %c ", (char)(startpoint[i]+65)); } printf("\n");
	printf("endpoints: "); for (int i = 0; i < endpointPos; i++) { printf(" %c ", (char)(endpoint[i]+65)); } printf("\n"); 

	passwordPos = 0;
	for (int i = 0; i < startpointPos; i++) { printf("[%c]", startpoint[i]+65); recurseCon2(startpoint[i], 0); }
	printf("%c ---\n", endpoint[0]+65);
	password[passwordPos] = endpoint[0]+65; passwordPos++;
	password[passwordPos] = '\0';

	char password2[100];
	strcpy(password2, "GJFMDHNBCIVTUWEQYALSPXZORK");
	passwordPos = 26;
	printf("ANS: %s\n", password2);
	if (strcmp(password2, password) == 0) {
		printf("***YAHAY....\n");
	}
}

int allin = 0;
int backward(int one, int parent, int ignore)
{
	printf("GOT in func:backward: %c parent: %c\n", (char)(one+65), (char)parent+65);
	//if (one+65 == 'T') {printf("GOT in func:backward: %c parent: %c\n", (char)(one+65), (char)parent+65); /*int in = getchar(); if (in == (int)'T') {allin = 1;} */}
	if (allin == 1) {getchar();}
	printf("PASSS:"); for (int c = 0; c < passwordPos; c++) { printf("%c", password[c]);} printf("\n");
	printf("MAINQ:"); for (int c = 0; c < mainQtot; c++) { printf("%c ", (char)mainQ[c].child+65); } printf("\n");

	{
		int found4 = 0; for (int r = 0; r < passwordPos; r++) { if (password[r] == (char)(one+65   )) { found4 = 1; break; } }
		int found3 = 0; for (int r = 0; r < passwordPos; r++) { if (password[r] == (char)(parent+65)) { found3 = 1; break; } }

		if ((found3 == 1 || after[one].topos == 0) && (ignore == 0)) {
			if (after[one].topos == 0 && found4 == 0) {
				recurseCon2(one, 0);
			} else {
				int found7 = 0;
				for (int z = 0; z<after[parent].topos; z++) {
					for (int t = 0; t < passwordPos; t++) {
						if (after[parent].to[z] == password[t]) {
							found7++;
						}
					}

				}
				if (found7 == after[parent].topos) {
					recurseCon2(parent, 0);
				}
			}
			return 0;
		}
	}

	{
		int found5 = 0;
		for (int i = 0; i < after[one].topos; i++) {
			for (int r = 0; r < passwordPos; r++) { if (password[r] == (char)(after[one].to[i]+65)) { found5++; break; } }
		}
		if (found5 == after[one].topos && after[one].topos > 1) {
			//printf("** trying to get T one is %c\n", one+65);// getchar();
			recurseCon2(one, 0);
			return 0;
		}
		int goneback = 0;
		for (int i = 0; i < after[one].topos; i++) {
			printf("backward:|%c| parent [%c] : Grandfather[%c]-> backward\n", (char)after[one].to[i]+65, (char)(one+65), (char)(parent+65)); 
			if (parent != after[one].to[i]) { printf("GOING BACK\n"); goneback =1; backward(after[one].to[i], one, 0); } 
		}
		if (goneback == 0) {
			recurseCon2(one, 0);
		}
	}

		
	return 0;
}

int recurseCon2(int one, int dont) {
	int found1 = 0;
	char P[100] = "GJFMDHNBCIVTUWEQYALSPXZORK";
	for (int k = 0; k < passwordPos; k++) {
		if (password[k] == (char)one+65) {found1 = 1; break;}
	}
	if (found1 == 0) {
		if (dont == 0) {
			password[passwordPos] = (char)(one+65); passwordPos++;
                        printf("LOOKING AT [%c]\n", password[passwordPos-1]);
                        int n;
                        printf("----");
                        for (n = 0; n < NUMQ5; n++) {
                                printf(" Q%d: ", n);
                                for (int z = 0; z < Q5Pos[n]; z++) {
                                        printf(" %c, ", Q5[n][z]+65);
                                }
                        }
                        //getchar();
			int found = 0;
                        for (n = 0; n < NUMQ5; n++) { //take off
                                if (Q5Pos[n] > 0) {
				    for (int z = 0; z < Q5Pos[n]; z++) {
                                        if (Q5[n][z] == one) {
				int count = 0;
				for (int z = 0; z < 5; z++) {
					if (Q5Pos[z] == 0) {
						count++;
					}
				}
				BubbleSort(waiting, waitingPos);
				if ((count > 1 && n == 0)) {
					printf("COUNT (HERE)> Q is %d\n", n); getchar();
						Q5Pos[n]--;
                                                Q5Count[n] += one+61;
                                                printf("**taking off %c on Q %d\n", one+65, n);
						cleanoffW(one);
							if (waitingPos > 0) {
								if (Q5[n][0] == ('R' - 65)) {
									printf("got %c\n", Q5[n][0]+65); getchar();
								}
								Q5[n][0] = takeoffW();
								cleanoffW(Q5[n][0]);
								Q5Pos[n]++;
							}
						found = 1;
						Q5Pos[n]--;
				} else {
						Q5Pos[n]--;
                                                Q5Count[n] += one+61;
                                                printf("**taking off %c on Q %d\n", one+65, n);
						cleanoffW(one);
							if (waitingPos > 0) {
								if (Q5[n][0] == ('R' - 65)) {
									printf("got %c\n", Q5[n][0]+65); getchar();
								}
								//Q5[n][0] = takeoffW();
								
								Q5[n][0] = P[passwordPos]-65;//takeoffW();
								cleanoffW(Q5[n][0]);
								Q5Pos[n]++;
							}
						found = 1;
                                                break;
				}
                                        }
				    }
                                }
                        }
			if (found == 0) {
				BubbleSort(waiting, waitingPos);
				printf("\n\nwas on no Q\n no Q no Q... (%c)\n\n", one+65);  getchar();
				Q5[0][0] = P[passwordPos]-65;//takeoffW();
				printf("\n\nputting on \n (%c) Q:%d\n\n", P[passwordPos], n);  getchar();
				cleanoffW(Q5[n][0]);
				Q5Pos[0] = 1;
				cleanoffW(one);
				int tosort[10];
				                for (int s = 0; s < 5; s++) {
				                        tosort[s] = Q5Pos[s];
                				}
				                sort(tosort, tosort+5);
				                for (int s = 0; s < 5; s++) {
			                       		 if (Q5Pos[s] == tosort[0]) {
                       						qnum = s; break;
                        				}
						}
				int count = 0;
				for (int z = 0; z < 5; z++) {
					if (Q5Pos[z] == 0) {
						count++;
					}
				}
				if ((count > 1 && n == 0)) {
					printf("COUNT > 1\n"); getchar();
				} else {
					if (Q5Pos[tosort[0]] == 0) {
						Q5Count[tosort[0]] += one+61;
						if (one == 'G' -65) {
							Q5Count[0] = one+61;
							Q5Count[1] = one+61;
							Q5Count[2] = one+61;
							Q5Count[3] = one+61;
							Q5Count[4] = one+61;
						}
							
					} else {
						Q5Count[0] += one+61;
					}
				}
			}
			
		}
	}

	int tosort[10];
	qnum = qnumFirst;
	if (found1 == 0) {
		for (int i = 0; i < all[one].topos; i++) {
			for (int k = 0; k < endpointPos; k++) {
				if (endpoint[k] != all[one].to[i]) {

					printf("LOOP add?(%d): parent: (%c) - >(%c):%d\n", i, one+65, all[one].to[i]+65, after[all[one].to[i]].topos);

					int found5 = 0;
					int r = 0;
					for (r = 0; r < mainQtot; r++) {
						if (mainQ[r].child == (char)(all[one].to[i])) {
							found5 = 1; break;
						}
					}

					if (found5 == 0) {
						printf("adding %c to the Q of %c\n", all[one].to[i]+65, one+65);
						mainQ[mainQtot].child = all[one].to[i];
						mainQ[mainQtot].parent = one; mainQtot++;
					} else {
						mainQ[r].parent = one; 
					}

					if (i == 0 && (Q5Pos[qnum] == 0)) {
						printf("here1..."); getchar();
						qnumFirst = qnum;
					} else {
				                for (int s = 0; s < 5; s++) {
				                        tosort[s] = Q5Pos[s];
                				}
				                sort(tosort, tosort+5);
				                for (int s = 0; s < 5; s++) {
			                       		 if (Q5Pos[s] == tosort[0]) {
                       						qnum = s; break;
                        				}
						}
                			}
					printf("CHECKING %d for %c\n", qnum, all[one].to[i]+65); 
					int found77 = 0;
					for (int o = 0; o < 5; o++) {
						for (int p = 0; p < Q5Pos[o]; p++) {
							if (Q5[o][p] == all[one].to[i]) {
								found77 = 1; break;
							}
						}
					}
				BubbleSort(waiting, waitingPos);
					if (found77 == 0) {
						if (Q5Pos[qnum] == 0) {
							if (waitingPos > 0) {
								int found88 = 0;
								for (int t = 0; t<waitingPos; t++) {
									if (waiting[t] == all[one].to[i]) {
										found88 = 1; break;
									}
								}
								if (found88 == 0 || found88 == 1) {
									Q5[qnum][Q5Pos[qnum]] = takeoffW(); Q5Pos[qnum]++;
									putonW(all[one].to[i]);
								}
							} else {
								Q5[qnum][Q5Pos[qnum]] = all[one].to[i]; Q5Pos[qnum]++;
							}
						} else {
							printf("Q %d FULL\n", qnum); 
								int found88 = 0;
								for (int t = 0; t<waitingPos; t++) {
									if (waiting[t] == all[one].to[i]) {
										found88 = 1; break;
									}
								}
								if (found88 == 0 || found88 == 1) {
									putonW(all[one].to[i]);
								}
						}
					}
						
                        for (int n = 0; n < NUMQ5; n++) { printf(" Q%d: ", n); for (int z = 0; z < Q5Pos[n]; z++) { printf(" %c, ", Q5[n][z]+65); } } printf("\n"); } }
			qnum = qnumFirst;
		}
	}
				BubbleSort(waiting, waitingPos);
	BubbleSortBack(mainQ, mainQtot);
	while (mainQtot != 0) { mainQtot--; backward(mainQ[mainQtot].child, mainQ[mainQtot].parent, 1); if (passwordPos == 25) {break;}}
	printf("PASSWORD: "); for (int k = 0; k < passwordPos; k++) { printf("%c", password[k]); } printf("\n");
	for (int r = 0; r < 5; r++)  {
		printf("count %d is %d\n", r, Q5Count[r]); getchar();
	}
	Q5Count[0] += 'K' -65+61;
	for (int r = 0; r < 5; r++)  {
		printf("count with K %d is %d\n", r, Q5Count[r]); getchar();
	}
	return 0;
}

void cleanoffW(int X) {
again:
	int found = 0;
	for (int i = 0; i < waitingPos; i++) {
		if (waiting[i] == X) {
			found = 1;
			for (int k = i; k < waitingPos; k++) {
				waiting[k] = waiting[k+1];
			}
			break;
		}
	}
	if (found == 1) {
		waitingPos--;
		goto again;
	}
}
	
int takeoffW() {
	printf("\nin takeoffW...\n"); getchar();
	if (waitingPos == 0) {printf("ERROR waiting"); exit(0);}
	int tmpW = waiting[waitingPos-1];
/*
	int tmpW = waiting[0];
	for (int i = 0; i < waitingPos-1; i++) {
		waiting[i] = waiting[i+1];
	}
*/
	waitingPos--;
	return tmpW;
}
	

void putonW(int X) {
	waiting[waitingPos] = X;
	waitingPos++;
/*
	int tmpW[101];
	for (int i = 0; i < waitingPos; i++) {
		tmpW[i+1] = waiting[i];
	}
	tmpW[0] = X;
	waitingPos++;
	for (int i = 0; i < waitingPos; i++) {
		waiting[i] = tmpW[i];
	}
*/
}
	




