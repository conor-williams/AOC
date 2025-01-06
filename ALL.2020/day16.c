#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
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

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day16 Part1\n"); fflush(stdout);
	
	fflush(stdout); int fd = dup(1); close(1);
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
		printf("%s\n", to2); getchar();
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
	for (int i = 0; i < ticket; i++) {
		for (int j = 0; j < listPos; j++) {
			int found = 0;
			for (int k = 0; k < whatPos; k++) {
				if ((lists[i][j] >= what[k].frm1 && lists[i][j] <= what[k].to1) ||
					(lists[i][j] >= what[k].frm2 && lists[i][j] <= what[k].to2)) {
					found = 1;
					break;
				}
			}
			if (found == 0) {
				printf("not a match %d\n", lists[i][j]);
				notsum+=lists[i][j];
			}
		}
	}
	printf("notsum is %d\n", notsum);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", notsum);
}


