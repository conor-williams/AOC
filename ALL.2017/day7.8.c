#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

unsigned long long tot = 0;
#define SIZE 200
char line1[SIZE];
struct rules_s {
	char from[10];
	int weight;
	char to[20][10];
	int toPos;
	int totWeight;
};
int weight2 = 0;
int weight2Tot = 0;
struct tree_s {
	int weight;
	char what[1000][20];
	int whatPos;
};
int weight2Tots[1111];
int weight2TotsPos = 0;
struct tree_s tree[1111];
//int treePos[1111] = {0};

int maxInd = 0;
void traverseToBottom(char from[]);
void traverseToBottom3(char from[]);

int weight;
struct rules_s rules[1111];
void next(char from[]);
int leny = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.1\n"); fflush(stdout);


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
	rules[leny].totWeight = atoi(first);
	strtok(NULL, ">");
	while ((first = strtok(NULL, " ,\0")) != NULL) {
		strcpy(rules[leny].to[rules[leny].toPos++], first);
		printf("cp %s\n", rules[leny].to[rules[leny].toPos-1]);
	}
	leny++;
}
fclose(a);
	for (int i = 0; i < leny; i++) {
		printf("[%s]\n", rules[i].from);
		printf("[%d]\n", rules[i].weight);
		for (int k = 0; k < rules[i].toPos; k++) {
			printf("	[%s]\n", rules[i].to[k]);
			for (int z = 0; z < leny; z++) {
				if (strcmp(rules[i].to[k], rules[z].from) == 0) { 
					rules[i].totWeight += rules[z].totWeight; break;
				}
			}
		}
	}
	printf("----------Tot Weights: --------------\n");
	for (int i = 0; i < leny; i++) {
		if (rules[i].toPos > 0) {
			printf("[%d]\n", rules[i].totWeight);
		}
	}
	printf("---------------------- --------------\n");

	weight = 0;
	for (int i = 0; i < leny; i++) {
		if (rules[i].toPos == 0) {
			weight+=rules[i].weight;
			printf("[%s]\n", rules[i].from);
			strcpy(tree[0].what[tree[0].whatPos++], rules[i].from);
			next(rules[i].from);
			weight = 0;
		}
	}

	
	for (int i = 0; i < maxInd; i++) {
		for (int j = 0; j < tree[i].whatPos; j++) {
			printf("%s\n", tree[i].what[j]);
		}
		printf("--------\n");
	}


	printf("TRAVERSE: ----------VVV---------\n");
	//for (int i = maxInd-2; i >= 0; i--) {
	int i = maxInd -1;
	for (int j = 0; j < tree[i].whatPos; j++) {
		printf("***%s\n", tree[i].what[j]); getchar();
		weight2 = 0;
		weight2Tot = 0;
		for (int z = 0; z < leny; z++) {
			if (strcmp(tree[i].what[j], rules[z].from) == 0) {
				
				weight2 = rules[z].weight; /*weight2Tot = weight2;*/ break;
				
			}
		}
		traverseToBottom(tree[i].what[j]);
		printf("got weight %d\n", weight2Tot);
		weight2Tot = 0;
		printf("--------\n");
	}

	printf("SHOULD3 HAVE NO ERRS ^^\n");
	getchar();
	printf("SHOULD HAVE NO ERRS ^^\n");
	i = maxInd -1;
	int MINUS = 80000;
	printf("SEARCH:\n");
	for (int i = 0; i < tree[maxInd-2].whatPos; i++) {
		printf("****%s\n", tree[maxInd-2].what[i]);
	}
	getchar();
	exit(0);
	for (int t = 0; t < leny; t++) {
		for (int b = 0; b < tree[maxInd-2].whatPos; b++) {
			if (strcmp(rules[t].from, tree[maxInd-2].what[b]) == 0) {
				break;
			} else {
				goto nextt;
			}
		}
		
		printf("trying rule %d of (%d)\n", t, leny);
		int origW = rules[t].weight; 
		rules[t].weight -= MINUS;
		for (int inc = 0; inc < MINUS*2; inc++) {
			rules[t].weight++;	
			for (int j = 0; j < tree[i].whatPos; j++) {
				weight2 = 0;
				weight2Tot = 0;
				weight2TotsPos = 0;
				for (int z = 0; z < leny; z++) {
					if (strcmp(tree[i].what[j], rules[z].from) == 0) {
						weight2 = rules[z].weight; /*weight2Tot = weight2;*/ break;
					}
				}
			
				traverseToBottom(tree[i].what[j]);
				weight2Tot = 0;
				//printf("--------\n");

				int found = 0;
				for (int r = 0; r < weight2TotsPos; r++) {
					//printf("%d\n", weight2Tots[r]);
				}
				for (int r = 0; r < weight2TotsPos-1; r++) {
					if (weight2Tots[r] == weight2Tots[r+1]) {
						found++;
					}
				} 
				if (found == weight2TotsPos-1) {
					printf("[%s] curr: (%d)\n", rules[t].from, rules[t].weight);
					printf("all the same\n");
				}
			}
		}
		rules[t].weight = origW;
nextt:
		continue;
	}



	printf("***tot is ^^ [%llu]\n", tot);
	return 0;
}
int ind3 = 0;
void traverseToBottom3(char from[]) {
ind3++;
	int weight2TotBef = weight2Tot;
	for (int i = 0; i < leny; i++) {
		if (strcmp(rules[i].from, from) == 0) {
			for (int j = 0; j < rules[i].toPos; j++) {
				for (int z = 0; z < leny; z++) {
					if (strcmp(rules[i].to[j], rules[z].from) == 0) {
						weight2 = rules[z].weight; weight2Tot+= rules[z].weight; break;
					}
				}
				int cWeight2;
				if (j == 0 && rules[i].toPos > 1 && ind3 >2) {
					cWeight2 = weight2;	
				} else {
					if (weight2 != cWeight2 && ind3 >2) {
						for (int z = 0; z<ind3;z++) {printf("	");} 
						printf("ERR weight2 should be %d for %s (ind3: %d)\n", cWeight2, rules[i].to[j], ind3);
					}
				}
				//for (int z = 0; z<ind2;z++) {printf("	");} printf("(%d) %s\n", weight2, rules[i].to[j]);
				traverseToBottom(rules[i].to[j]);
				
			}
		}
	}
	//weight2Tot = weight2TotBef;
	if (ind3 == 2) {
		printf("weight2Tot: %d for [%s]\n", weight2Tot, from);
		weight2Tots[weight2TotsPos++]= weight2Tot;
		weight2Tot = 0;
	} else {
		weight2Tot = weight2TotBef;
	}
ind3--;
}
int ind2 = 0;
void traverseToBottom(char from[]) {
ind2++;
	int weight2TotBef = weight2Tot;
	for (int i = 0; i < leny; i++) {
		if (strcmp(rules[i].from, from) == 0) {
			for (int j = 0; j < rules[i].toPos; j++) {
				for (int z = 0; z < leny; z++) {
					if (strcmp(rules[i].to[j], rules[z].from) == 0) {
						weight2 = rules[z].weight; weight2Tot+= rules[z].weight; break;
					}
				}
				int cWeight2;
				if (j == 0 && rules[i].toPos > 1 && ind2 >= 2) {
					cWeight2 = weight2;	
				} else {
					if (weight2 != cWeight2 && ind2 >= 2) {
						//for (int z = 0; z<ind2;z++) {printf("	");} 
						//printf("ERR weight2 should be %d for %s (ind: %d)\n", cWeight2, rules[i].to[j], ind2);
					}
				}
				//for (int z = 0; z<ind2;z++) {printf("	");} printf("(%d) %s\n", weight2, rules[i].to[j]);
				traverseToBottom(rules[i].to[j]);
				
			}
		}
	}
	//weight2Tot = weight2TotBef;
	if (ind2 == 2) {
		printf("weight2Tot: %d for [%s]\n", weight2Tot, from);
		weight2Tots[weight2TotsPos++]= weight2Tot;
		weight2Tot = 0;
	} else {
		weight2Tot = weight2TotBef;
	}
ind2--;
}
int ind = 0;
void next(char from[]) {
	ind++;
	if (ind > maxInd) {maxInd = ind;}
	for (int i = 0; i < leny; i++) {
		for (int k = 0; k < rules[i].toPos; k++) {
			if (strcmp(rules[i].to[k], from) == 0) {
				for (int j = 0; j< ind; j++) {printf("	");} printf("(%d) [%s]\n", weight, rules[i].from);
				weight += rules[i].weight;
				int found = 0;
				for (int q = 0; q < tree[ind].whatPos; q++) {
					if (strcmp(tree[ind].what[q], rules[i].from) == 0) {
						found = 1; break;
					}
				}	
				if (found == 1) {
					printf("NEVER\n"); getchar();
					//tree[ind].weight += rules[i].weight;
				} else if (found == 0) {
					strcpy(tree[ind].what[tree[ind].whatPos++], rules[i].from);
					tree[ind].weight += rules[i].weight;
				}
				next(rules[i].from);
				getchar();
			}
		}
	}
	ind--;
}
