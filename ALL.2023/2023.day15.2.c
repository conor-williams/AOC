#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct lens {
	char label[100];
	int focal;
	char command;
	int boxnumber;
};
int commandFound = 0;
long tot = 0;
int leny = 0;
int lenx = 0;
#define DAY "2023 Day15 Part2\n"
int hashval(char *token);
struct lens box[256][30000];
int boxes[256];
void printboxes();
#undef _DEBUG_

int main(int argc, char **argv)
{
	for (int q = 0; q < 256; q++) {boxes[q] = 0;}
	//char starts[100][5];
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);

	char line1[30000];
	while(1) {
		fgets(line1, 30000, a);
		if (feof(a)) break;
		leny++;
	}
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	//printf("lenx %d - leny %d\n", lenx, leny);
	fclose(a);


	long tot = 0;
	struct lens lens1;
	char *token = strtok(line1, ",\n");
	while (token != NULL) {
		//tot += hashval(token);
		for (int i = 0; i < (int)strlen(token); i++) {
			{
				if (token[i] == '-') {
					lens1.command = '-';
					token[i] = '\0';
					commandFound = 1;
				} else if (token[i] == '=') {
					lens1.command = '=';
					token[i] = '\0';
					commandFound = 1;
				}
				strcpy(lens1.label, token);
				if (commandFound && lens1.command == '=') {
					lens1.focal = token[i+1] -48;
					commandFound = 0;}
				else if (commandFound && lens1.command == '-') {
					lens1.focal = -1;
					commandFound = 0;
				}
			}
		}
		lens1.boxnumber = hashval(token);
		token = strtok(NULL, ",\n");		
#ifdef _DEBUG_
		printf("L:%s C:%c F:%d B:%d\n", 
				lens1.label, lens1.command, lens1.focal, lens1.boxnumber);
#endif
		if (lens1.command == '=') {
			//if not in box
			int pos = 0;
			int foundbox = 0;
			if (boxes[lens1.boxnumber] > 0) {
				for (int i = 0; i< boxes[lens1.boxnumber]; i++) {
					if (strcmp(box[lens1.boxnumber][i].label, lens1.label) == 0) {
						//boxes[lens1.boxnumber]
						foundbox = 1;
						pos = i;
					}
				}
			}
			if (foundbox == 0) {
				strcpy(box[lens1.boxnumber][boxes[lens1.boxnumber]].label,
						lens1.label); 
				box[lens1.boxnumber][boxes[lens1.boxnumber]].command = lens1.command;
				box[lens1.boxnumber][boxes[lens1.boxnumber]].focal = lens1.focal; 
				box[lens1.boxnumber][boxes[lens1.boxnumber]].boxnumber = lens1.boxnumber; 
				boxes[lens1.boxnumber]++;
			} else {
				box[lens1.boxnumber][pos].focal = lens1.focal; 

			}
		} else if (lens1.command == '-') {
			int pos; int foundbox = 0;
			if (boxes[lens1.boxnumber] > 0) {
				for (int i = 0; i< boxes[lens1.boxnumber]; i++) {
					if (strcmp(box[lens1.boxnumber][i].label, lens1.label) == 0) {
						//boxes[lens1.boxnumber]
						foundbox = 1;
						pos = i;
						break;
#ifdef _DEBUG_
						printf("FOUND removing [%s] pos:[%d]... getchar\n", box[lens1.boxnumber][i].label, pos); getchar();
#endif
					}
				}
			} 
			if (foundbox == 1) {
				for (int i = pos; i < boxes[lens1.boxnumber]; i++) {
#ifdef _DEBUG_
					printf("here...."); getchar();
#endif
					if (i+1 != boxes[lens1.boxnumber]) {			
						strcpy(box[lens1.boxnumber][i].label, box[lens1.boxnumber][i+1].label);
						box[lens1.boxnumber][i].command = box[lens1.boxnumber][i+1].command;
						box[lens1.boxnumber][i].focal = box[lens1.boxnumber][i+1].focal;
						box[lens1.boxnumber][i].boxnumber = box[lens1.boxnumber][i+1].boxnumber; 
					}
				}
				boxes[lens1.boxnumber]--;
			}
		}
#ifdef _DEBUG_
		printboxes();
#endif
#ifdef _DEBUG_
		getchar();
#endif
	}
	//sumit();

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < boxes[i]; j++) {
			tot += (i + 1) * (j+1) * box[i][j].focal;	
		}
	}

	//printf("******** tot %ld\n", tot);
	printf("**ans: %ld\n", tot);

}
void printboxes() {
	for (int i = 0; i< 256; i++) {
		if (boxes[i] != 0) {
			printf("BOX %d: ", i);
			for (int k = 0; k < boxes[i]; k++) {
				printf("[%s %d]\n", box[i][k].label, box[i][k].focal);
			}
			printf("\n");
		}
	}
}
int hashval(char *token){
	int ascV = 0;
	int ans = 0;
	for (int x = 0; x < (int)strlen(token); x++) {
		ascV = (int)token[x]; 
		ans = ((ans + ascV) * 17) % 256;
		if (x == (int)strlen(token) - 1) {
			//printf("%d\n", ans);
			return ans;
		}
	}
	return 0;
}
