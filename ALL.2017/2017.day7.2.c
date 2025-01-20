#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tots[10][10];
int tots2[1000][10][1000];
int tots2Pos[1000] = {0};
unsigned long long tot = 0;
#define SIZE 200
char line1[SIZE];
struct rules_s {
	char from[10];
	int weight;
	char to[20][10];
	int toPos;
};
int maxPosPos = 0;
int minPosPos = 999999;
int maxInd2 = 0;
int ind2 = 0;
int ind3 = 0;
int ind = 0;
int ind4 = 0;
int weight2 = 0;
int weight2Tot = 0;
int weight3Tot = 0;
int weight4Tot = 0;
int foundInd3 = 0;
struct tree_s {
	int weight;
	char what[2000][20];
	int whatPos;
};
int weight4Tots[2111];
int weight4TotsPos = 0;
int weight3Tots[2111];
int weight3TotsPos = 0;
int weight2Tots[2111];
int weight2TotsPos = 0;
struct tree_s tree[2111];
//int treePos[2111] = {0};
void findEnd(char from[]);
void traverseToBottom4(char from[]);

#include <unistd.h>

#define getchar()
#define assert(asdf)
int maxInd = 0;
void traverseToBottom(char from[], int pospos);

int weight;
struct rules_s rules[2111];
void next(char from[]);
int leny = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day7.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			tots[i][j] = 0;
		}
	}
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);
	
	char *first = strtok(line1, " (");
	strcpy(rules[leny].from, first);
	first = strtok(NULL, ")");
	printf("first is %s\n", first);
	first[0] = ' ';
	rules[leny].weight = atoi(first);
	strtok(NULL, ">");
	while ((first = strtok(NULL, " ,\0")) != NULL) {
		strcpy(rules[leny].to[rules[leny].toPos++], first);
		printf("cp %s\n", rules[leny].to[rules[leny].toPos-1]);
	}
	leny++;
}
fclose(a);

	int pos = 0;
	int myInd[3000] = {0};

	for (int i = 0; i < leny; i++) {
		if (rules[i].toPos == 0) {
			ind3 = 0;
			findEnd(rules[i].from);
			myInd[pos] = foundInd3;
			if (pos < 7) {
				printf("pos is %d --myInd[pos] %d\n", pos, myInd[pos]);
			}
			if (myInd[pos] > maxInd2) {maxInd2 = myInd[pos];}
			pos++;
		}
	}

	int myindStart[3000] = {0};
	for (int i = 0; i < pos; i++) {
		myindStart[i] = maxInd2 - myInd[i];
		if (i < 7) {
			printf("i is %d - myIndStart[i] %d\n", i, myindStart[i]);
		}
		if (myindStart[i] != 0 && myindStart[i] != 1) {
			//printf("myindStart is %d\n", myindStart[i]);
		}
	}
	//getchar();
	weight = 0;
	int iPos = 0;
	for (int i = 0; i < leny; i++) {
		if (rules[i].toPos == 0) {
			if (iPos < 7) {
				printf("iPos is %d -  myindStart[iPos] %d\n", iPos, myindStart[iPos]);
			}
			ind = myindStart[iPos++];
			weight+=rules[i].weight;
			//printf("[%s]\n", rules[i].from);
			strcpy(tree[ind].what[tree[ind].whatPos++], rules[i].from);
			
			next(rules[i].from);
			weight = 0;
		}
	}

	printf("TRAVERSE: ----------VVV---------\n");
	//for (int i = maxInd -1; i >= 0; i--) {
	printf("tree[maxInd-1].what[0].from is %s\n", tree[maxInd-1].what[0]); getchar();
	int i = maxInd -2;
	int pospos = 0;
	for (int j = 0; j < tree[i].whatPos; j++) {
		printf("***%s\n", tree[i].what[j]); getchar();
		weight2 = 0;
		weight2Tot = 0;
		for (int z = 0; z < leny; z++) {
			if (strcmp(tree[i].what[j], rules[z].from) == 0) {
				weight2Tot = rules[z].weight;
				//printf("**RULE %s *%d\n", rules[z].from, weight2Tot); getchar();
				weight2 = rules[z].weight; /*weight2Tot = weight2;*/ break;
			}
		}
		maxPosPos = 0;
		minPosPos = 999999;
		tots[pospos][0] = weight2;
		traverseToBottom(tree[i].what[j], pospos++);
		printf("min and max weight %d %d\n", maxPosPos, minPosPos);
		weight2Tot = 0;
		printf("--------\n");
	}

	printf("TOTS:\n");
	for (int i = 3; i < 4; i++) {
		printf("i: %d\necho $((	", i);
		for (int j = 0; j < tots2Pos[i]; j++) {
			for (int k = 0; k < 7; k++) {
				for (int z = 0; z < k; z++) {printf("	");} printf("%d ", tots2[i][k][j]);
			}
		}
		printf("))\n");
	}
	getchar();
	ind4 = 0;
	traverseToBottom4("kzltfq");

	for (int i = 0; i < weight2TotsPos; i++) {
		printf("** %d\n", weight2Tots[i]);
	}

	printf("SEARCH:\n");
	for (int i = 0; i < tree[maxInd-2].whatPos; i++) {
		printf("****%s\n", tree[maxInd-2].what[i]);
	}


	printf("***tot is ^^ [%llu]\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("broken: not working: not working...\n");
	return 0;
}


void traverseToBottom(char from[], int pospos) {
ind2++;
	//int weight2TotBef = weight2Tot;
	for (int i = 0; i < leny; i++) {
		if (strcmp(rules[i].from, from) == 0) {
			for (int j = 0; j < rules[i].toPos; j++) {
				for (int z = 0; z < leny; z++) {
					if (strcmp(rules[i].to[j], rules[z].from) == 0) {
						if (ind2 >= 1) {weight3Tot += rules[z].weight;}
						if (ind2 >= 2) {weight4Tot += rules[z].weight;}
						weight2 = rules[z].weight; weight2Tot+= rules[z].weight; break;
					}
				}
				tots[pospos][ind2] += weight2;
				/*
				int cWeight2;
				if (j == 0 && rules[i].toPos > 1 && ind2 >= 2) {
					cWeight2 = weight2;	
				} else {
					if (weight2 != cWeight2 && ind2 >= 2) {
						//for (int z = 0; z<ind2;z++) {printf("	");} 
						printf("ERR weight2 should be %d for %s (ind: %d)\n", cWeight2, rules[i].to[j], ind2);
					}
				}
				//for (int z = 0; z<ind2;z++) {printf("	");} printf("(%d) %s\n", weight2, rules[i].to[j]);
				*/
				traverseToBottom(rules[i].to[j], pospos);
				
			}
			if (rules[i].toPos == 0) {
				//printf("rules[i].weight is %d\n", rules[i].weight);
				if (rules[i].weight > maxPosPos) {maxPosPos = rules[i].weight;}
				else if (rules[i].weight < minPosPos) {minPosPos = rules[i].weight;}
				tots[pospos][ind2] += rules[i].weight;
			}
				
		}
	}
	
	
	tots2[pospos][ind2][tots2Pos[pospos]++] = weight2Tot;
	if (ind2 == 1) {
		//printf("maxInd is %d\n", maxInd);
		printf("weight2Tot: %d for [%s]\n", weight2Tot, from); 
		weight2Tots[weight2TotsPos++]= weight2Tot;
		weight2Tot = 0; getchar();
	} else if (ind2 == 2) {
		printf("**INDEX 3 weight3Tot: %d for [%s]\n", weight3Tot, from);  getchar();
		weight3Tots[weight3TotsPos++]= weight3Tot;
		weight3Tot = 0;
		//printf("ind2 is 1\n"); getchar();
	} else if (ind2 == 3) {
		printf("**INDEX 4 weight3Tot: %d for [%s]\n", weight4Tot, from);  getchar();
		weight4Tots[weight4TotsPos++]= weight4Tot;
		weight4Tot = 0;
		//printf("ind2 is 1\n"); getchar();
	} else {
		//weight2Tot = weight2TotBef;
	}
ind2--;
}
void next(char from[]) {
	ind++;
	if (ind > maxInd) {maxInd = ind;}
	for (int i = 0; i < leny; i++) {
		for (int k = 0; k < rules[i].toPos; k++) {
			if (strcmp(rules[i].to[k], from) == 0) {
				//for (int j = 0; j< ind; j++) {printf("	");} printf("(%d) [%s]\n", weight, rules[i].from);
				weight += rules[i].weight;
				int found = 0;
				for (int q = 0; q < tree[ind].whatPos; q++) {
					if (strcmp(tree[ind].what[q], rules[i].from) == 0) {
						found = 1; break;
					}
				}	
				if (ind > maxInd2-2) {
					for (int j = 0; j< ind; j++) {printf("	");} printf("[%s]\n", rules[i].from);
				}
				if (found == 1) {
					//printf("NEVER\n"); getchar();
					//tree[ind].weight += rules[i].weight;
				} else if (found == 0) {
					strcpy(tree[ind].what[tree[ind].whatPos++], rules[i].from);
					tree[ind].weight += rules[i].weight;
				}
				next(rules[i].from);
				//getchar();
			}
		}
	}
	ind--;
}
void traverseToBottom4(char from[]) {
ind4++;
	int weight3 = 0;
	for (int i = 0; i < leny; i++) {
		if (strcmp(rules[i].from, from) == 0) {
			for (int j = 0; j < rules[i].toPos; j++) {
				for (int z = 0; z < leny; z++) {
					if (strcmp(rules[i].to[j], rules[z].from) == 0) {
						weight3 = rules[z].weight; break;
					}
				}

				int cWeight3;
				if (j == 0 && rules[i].toPos > 1) {
					cWeight3 = weight3;	
				} else {
					if (weight3 != cWeight3) {
						printf("ERR weight3 should be [%d] is [%d] for %s (ind4: %d)\n", cWeight3, weight3, rules[i].to[j], ind4);
					}
				}
				if (rules[i].toPos == 1) {
					printf("only 1: weight3 is %d\n", weight3);
				}
				traverseToBottom4(rules[i].to[j]);
				
			}
		}
	}
	
ind4--;

}
void findEnd(char from[]) {
	//printf("in findEnd from %s\n", from);
	ind3++;

	for (int i = 0; i < leny; i++) {
		for (int k = 0; k < rules[i].toPos; k++) {
			if (strcmp(rules[i].to[k], from) == 0) {
				if (strcmp(rules[i].from, "hmvwl") == 0 || strcmp(rules[i].from, "tknk") == 0) {
					foundInd3 = ind3;
				} else {
					findEnd(rules[i].from);
				}
			}
		}
	}
	ind3--;
}

