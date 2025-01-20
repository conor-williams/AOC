#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
struct pass {
	char ecl[30];
	char pid[30];
	char eyr[30];
	char hcl[30];
	char byr[30];
	char iyr[30];
	char cid[30];
	char hgt[30];
};

#define _DEBUG_
#define getchar()
struct pass people[500];

int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2020 Day4 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	for (int i = 0; i < 500; i++) {
		people[i].ecl[0] = '\0';
		people[i].pid[0] = '\0';
		people[i].eyr[0] = '\0';
		people[i].hcl[0] = '\0';
		people[i].byr[0] = '\0';
		people[i].iyr[0] = '\0';
		people[i].cid[0] = '\0';
		people[i].hgt[0] = '\0';
	}

	int leny = 0;
	while (1) {
		fgets(line1, 500, a);
		if (feof(a)) break;
		//line1[(int)strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		char what[100];
		if (line1[0] != '\n') {
			int j = 0;
			for (int i = 0; i < (int)strlen(line1); i++) {
				if (line1[i] == ' ' || line1[i] == '\n') {
					what[j] = '\0';
					j = 0;
				} else {
					what[j] = line1[i];
					j++;
				}
				if (j==0) {/*printf("what is [%s]\n", what);*/}
				if (j==0) {
					char *firstpart = strtok(what, ":");
					char *secondpart = strtok(NULL, ":");

					if (strcmp(firstpart, "ecl") == 0) {
						strcpy(people[leny].ecl, secondpart);
					} else if (strcmp(firstpart, "pid") == 0) {
						strcpy(people[leny].pid, secondpart);
					} else if (strcmp(firstpart, "eyr") == 0) {
						strcpy(people[leny].eyr, secondpart);
					} else if (strcmp(firstpart, "hcl") == 0) {
						strcpy(people[leny].hcl, secondpart);
					} else if (strcmp(firstpart, "byr") == 0){
						strcpy(people[leny].byr, secondpart);
					} else if (strcmp(firstpart, "iyr") == 0) {
						strcpy(people[leny].iyr, secondpart);
					} else if (strcmp(firstpart, "cid") == 0) {
						strcpy(people[leny].cid, secondpart);
					} else if (strcmp(firstpart, "hgt") == 0) {
						strcpy(people[leny].hgt, secondpart);
					}
					//printf("**%s** **%s**\n", firstpart, secondpart);
				}
			}
		} else {
			leny++;
		}
	}
	if (line1[0] != '\0') {leny++;}
	fclose(a);
	int tot = 0;
	int iyr;
	int eyr;
	for (int i = 0; i < leny; i++) {
		if (	people[i].ecl[0] != '\0' &&
				people[i].byr[0] != '\0' &&
				people[i].iyr[0] != '\0' &&
				people[i].eyr[0] != '\0' &&
				people[i].hcl[0] != '\0' &&
				people[i].pid[0] != '\0' &&
				people[i].hgt[0] != '\0') {
			int impossible = 0;
			int byr = atoi(people[i].byr);
			if ((int)strlen(people[i].byr) == 4 && byr >= 1920 && byr <= 2002) {
#ifdef _DEBUG_
				printf("good byr %s\n",  people[i].byr); getchar();
#endif
			} else {
#ifdef _DEBUG_
				printf("bad byr %s\n",  people[i].byr);
#endif
				impossible = 1; goto end;
			}
			iyr = atoi(people[i].iyr);
			if ((int)strlen(people[i].iyr) == 4 && iyr >= 2010 && iyr <= 2020) {
#ifdef _DEBUG_
				printf("good iyr %s\n",  people[i].iyr); getchar();
#endif
			} else {
#ifdef _DEBUG_
				printf("bad iyr %s\n",  people[i].iyr);
#endif
				impossible = 1; goto end;
			}
			eyr = atoi(people[i].eyr);
			if ((int)strlen(people[i].eyr) == 4 && eyr >= 2020 && eyr <= 2030) { 
#ifdef _DEBUG_
				printf("good eyr %s\n",  people[i].eyr); getchar();
#endif
			} else {
#ifdef _DEBUG_
				printf("bad eyr %s\n",  people[i].eyr); 
#endif
				impossible = 1; goto end;
			}
			if ((people[i].hgt[(int)strlen(people[i].hgt) -2] == 'c' &&
						people[i].hgt[(int)strlen(people[i].hgt) -1] == 'm')  ||  
					(people[i].hgt[(int)strlen(people[i].hgt) -2] == 'i' && 
					 people[i].hgt[(int)strlen(people[i].hgt) -1] == 'n') ) {
				for (int q = 0; q < (int)strlen(people[i].hgt) - 2; q++) {
					if (isdigit((int)people[i].hgt[q])) {
#ifdef _DEBUG_
						printf("good hgt 1 %s\n",  people[i].hgt); getchar();
#endif
					} else {
#ifdef _DEBUG_
						printf("bad hgt 1 %s\n",  people[i].hgt);
#endif
						impossible = 1; goto end;
					}
				}
				char tmpS[100] = ""; 
				strncpy(tmpS, people[i].hgt, (int)(int)strlen(people[i].hgt) -2);
#ifdef _DEBUG_
				printf("HGT: BEFORE: %s AFTER: %s\n", people[i].hgt, tmpS); 
#endif
				int len  = atoi(tmpS);
				if (people[i].hgt[(int)strlen(people[i].hgt) -2]  == 'c') {
					if (len >= 150 && len <= 193) {
#ifdef _DEBUG_
						printf("good hgt 2 %s\n",  people[i].hgt); getchar();
#endif
					} else {
#ifdef _DEBUG_
						printf("bad hgt 2 %s\n",  people[i].hgt);
#endif
						impossible = 1; goto end;
					}
				} else {
					if (len >= 59 && len <= 76) {
#ifdef _DEBUG_
						printf("good hgt 3 %s\n",  people[i].hgt);  getchar();
#endif
					} else {
#ifdef _DEBUG_
						printf("bad hgt 3 %s\n",  people[i].hgt);
#endif
						impossible = 1; goto end;
					}
				}
			} else {
				impossible = 1; goto end;
			}
			if ((int)strlen(people[i].hcl) == 7 && people[i].hcl[0] == '#') {
#ifdef _DEBUG_
				printf("good hcl 1 %s\n",  people[i].hcl); getchar();
#endif
				for (int q = 1; q < (int)(int)strlen(people[i].hcl); q++) {
					if (isdigit((int)people[i].hcl[q]) || 
							people[i].hcl[q] == 'a' ||
							people[i].hcl[q] == 'b' ||
							people[i].hcl[q] == 'c' ||
							people[i].hcl[q] == 'd' ||
							people[i].hcl[q] == 'e' ||
							people[i].hcl[q] == 'f') {
#ifdef _DEBUG_
						printf("good hcl 1 %s\n",  people[i].hcl); getchar();
#endif

					} else {
#ifdef _DEBUG_
						printf("bad hcl 1 %s\n",  people[i].hcl);
#endif
						impossible = 1; goto end;
					}
				}
			} else {
#ifdef _DEBUG_
				printf("bad hcl 2 %s\n",  people[i].hcl);
#endif
				impossible = 1; goto end;
			}
			if ((int)strlen(people[i].ecl) == 3 &&
					(
					 strcmp(people[i].ecl, "amb") == 0 ||
					 strcmp(people[i].ecl, "blu") == 0 ||
					 strcmp(people[i].ecl, "brn") == 0 ||
					 strcmp(people[i].ecl, "gry") == 0 ||
					 strcmp(people[i].ecl, "grn") == 0 ||
					 strcmp(people[i].ecl, "hzl") == 0 ||
					 strcmp(people[i].ecl, "oth") == 0 )) {
#ifdef _DEBUG_
				printf("good ecl 2 %s\n",  people[i].ecl); getchar();
#endif
			} else {
#ifdef _DEBUG_
				printf("bad ecl 2 %s\n",  people[i].ecl);
#endif
				impossible = 1; goto end;
			}
			if ((int)strlen(people[i].pid) == 9 &&
					isdigit((int)people[i].pid[0]) &&
					isdigit((int)people[i].pid[1]) &&
					isdigit((int)people[i].pid[2]) &&
					isdigit((int)people[i].pid[3]) &&
					isdigit((int)people[i].pid[4]) &&
					isdigit((int)people[i].pid[5]) &&
					isdigit((int)people[i].pid[6]) &&
					isdigit((int)people[i].pid[7]) &&
					isdigit((int)people[i].pid[8])) {
#ifdef _DEBUG_
				printf("good pid 2 %s\n", people[i].pid); getchar();
#endif
			} else {
#ifdef _DEBUG_
				printf("bad pid 2 %s\n", people[i].pid);
#endif
				impossible = 1; goto end;
			}
end:
			if (impossible == 0) {
				//printf("valid %d\n", i);
				tot++;
			}
		}

	}
	printf("\n***tot:  %d of (%d)\n", tot, leny);

	fflush(stdout); dup2(fd, 1);
	printf("**ans:  %d\n", tot);
}
