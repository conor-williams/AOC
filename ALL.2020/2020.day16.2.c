#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

using namespace std;
int lenx = 0;
int leny = 0;
int LINE = 1000;
struct what_s {
	char field[50];
	int frm1;
	int to1;
	int frm2;
	int to2;
};
struct what_s what[100];
int whatPos = 0;
int lists[400][200];
int mine[200];

int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r");
	printf("		2020 Day16 Part2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	int fields = 1;
	int yourticket = 0;
	int nearbyticket = 0;
	int listPos = 0;
	char yours[100];
	int ticket = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		//line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);


		if (fields == 1 && line1[0] == '\n') {
			fields = 0;
			yourticket = 1;
			continue;
		}
		if (fields == 1) {
			char field[100];
			char frm1[20], to1[20], frm2[20], to2[20];
			printf("line1:[[[%s]]]\n", line1);
			sscanf(line1, "%[^:]: %[^-]-%[^ ] or %[^-]-%[^\n]\n", field, frm1, to1, frm2, to2);
			printf("%s\n", field);
			printf("%s\n", frm1);
			printf("%s\n", to1);
			printf("%s\n", frm2);
			printf("%s\n", to2); //getchar();
			strcpy(what[whatPos].field, field);
			what[whatPos].frm1 = atoi(frm1);
			what[whatPos].to1 = atoi(to1);
			what[whatPos].frm2 = atoi(frm2);
			what[whatPos].to2 = atoi(to2);
			printf("%s:::: %d -> %d  %d -> %d\n", what[whatPos-1].field, what[whatPos-1].frm1, what[whatPos-1].to1, what[whatPos-1].frm2, what[whatPos-1].to2);
			whatPos++;
			continue;
		}
		if (yourticket == 1) {
			if (line1[0] == 'y' && line1[1] == 'o') {
				continue;
			} else {
				strcpy(yours, line1);
				listPos = 0;
				char *list1 = strtok(line1, ",\n");
				do {
					mine[listPos] = atoi(list1);
					lists[ticket][listPos++] = atoi(list1);
					//printf("list1 is %s\n", list1);
				} while ((list1 = strtok(NULL, ",\n")) != NULL);
				assert(listPos == whatPos);
				ticket++;
				yourticket = 0;
				nearbyticket = 1;
				continue;
			}
		}
		if (nearbyticket == 1 && line1[0] == '\n') {
			continue;
		} else if (nearbyticket == 1) {
			if (line1[0] == 'n' && line1[1] == 'e') {
				continue;
			} else {
				listPos = 0;
				char *list1 = strtok(line1, ",\n");
				do {
					lists[ticket][listPos++] = atoi(list1);
					//printf("list1 is %s\n", list1);
				} while ((list1 = strtok(NULL, ",\n")) != NULL);
				assert(listPos == whatPos);
				ticket++;
				continue;
			}
		}

		leny++;
	}

	printf("ticket is %d\n", ticket);
	int notsum = 0;
	int ti = ticket;
	vector <int> bad_tickets;
	for (int i = 0; i < ticket; i++) {//nearbytickets
		for (int j = 0; j < listPos; j++) {//within each ticket
			int found = 0;
			for (int k = 0; k < whatPos; k++) {//class row etc...
				if ((lists[i][j] >= what[k].frm1 && lists[i][j] <= what[k].to1) ||
						(lists[i][j] >= what[k].frm2 && lists[i][j] <= what[k].to2)) {
					found = 1;
					break;
				}
			}
			if (found == 0) {
				printf("not a match %d\n", lists[i][j]);
				notsum+=lists[i][j];
				lists[i][0] = -1;
				bad_tickets.push_back(i);
				printf("bad ticket... %d\n", i);// getchar();
			} else {
				//printf("good ticket %d\n", i); getchar();
			}
		}
	}
	printf("notsum is %d\n", notsum);
	printf("ticket is %d\n", ticket);


	vector <int> vec[500][25];
	for (int i = 0; i < ticket; i++) {//nearbytickets
		if (find(bad_tickets.begin(), bad_tickets.end(), i) != bad_tickets.end()) {continue;}
		for (int j = 0; j < listPos; j++) {//within each ticket
			if (lists[i][0] == -1) {continue;}
			for (int k = 0; k < whatPos; k++) {//class row etc...
				if ((lists[i][j] >= what[k].frm1 && lists[i][j] <= what[k].to1) ||
						(lists[i][j] >= what[k].frm2 && lists[i][j] <= what[k].to2)) {
					vec[i][j].push_back(k);
					//printf("i:%d j:%d pushing back %d\n", i, j, k);// getchar();
				}
			}
		}
	}


	
	for (int ii = 0; ii < ticket; ii++) {
		if (find(bad_tickets.begin(), bad_tickets.end(), ii) != bad_tickets.end()) {continue;}
		for (int kk = 1; kk < ticket; kk++) {
			if (find(bad_tickets.begin(), bad_tickets.end(), kk) != bad_tickets.end()) {continue;}
			for (int jj = 0; jj < listPos; jj++) {
				vector <int> v1 = vec[ii][jj];
				vector <int> v2 = vec[kk][jj];
				vector <int> v3;
				//printf("v1.size() is %d\n", (int)v1.size());
				sort(v1.begin(), v1.end());
				//printf("v2.size() is %d\n", (int)v2.size());// getchar();
				sort(v2.begin(), v2.end());
				set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
				vec[kk][jj] = v3;
			}
		}
	}
	for (int jj = 0; jj < listPos; jj++) {
		printf("jj: ");
		for (auto iii: vec[ti-1][jj]) {
			//printf(" %d (%s)", iii, what[iii].field);
			printf(" %d ", iii);//, what[iii].field);
		}
		printf("\n");
		
	}

	vector <int> done;
	int answer[30];

again:
	for (int jj = 0; jj < listPos; jj++) {
		//if (find(done.begin(), done.end(), jj) != done.end()) {continue;}
		if ((int)vec[ti-1][jj].size() == 1) {
			int removeInt = vec[ti-1][jj][0];
			done.push_back(removeInt);
			answer[jj] = removeInt;
			printf("removingInt %d\n", removeInt);// getchar();
			for (int kk = 0; kk < listPos; kk++) {
				for (int zzz = 0; zzz < (int)vec[ti-1][kk].size(); zzz++) {
					if (vec[ti-1][kk][zzz] == removeInt) {
						printf("removing pos zzz: %d\n", removeInt); //getchar();
						vec[ti-1][kk].erase(vec[ti-1][kk].begin()+zzz);
						break;
					}
				}
			}
		}
	}
	for (int jj = 0; jj < listPos; jj++) {
		if (vec[ti-1][jj].size() != 0) {goto again;}
	}


	for (int jj = 0; jj < listPos; jj++) {
		printf("jj: ");
		for (auto iii: vec[ti-1][jj]) {
			//printf(" %d (%s)", iii, what[iii].field);
			printf(" %d ", iii);//, what[iii].field);
		}
		printf("\n");
	}
	for (int ii = 0; ii < listPos; ii++) {
		printf("answer %d: %d -- %s\n", ii, answer[ii], what[answer[ii]].field);
	}
	long long ans1 = 1;
	for (int ii = 0; ii < listPos; ii++) {
		if (what[answer[ii]].field[0] == 'd' && what[answer[ii]].field[1] == 'e' &&
			what[answer[ii]].field[2] == 'p') {
				ans1 *= (mine[ii]);
		}
	}
	fflush(stdout); dup2(fd,1);
	printf("**ans: %lld\n", ans1);

}


