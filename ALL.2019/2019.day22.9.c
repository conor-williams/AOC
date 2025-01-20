#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

#define getchar()

int lenx, leny;
#define DAY "2019 day22 part2\n"
#undef _DEBUG_
#define LINE 200
unsigned long long ENDLIST;
#ifdef _EX_
//#define ENDLIST 10

#define ENDL 10007
#else
#define ENDL (unsigned long long)119315717514047
//#define END 19993
#endif
int var_ints[] = { 10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 19993, -1};


vector <int> deck;
vector <int> deckOrig;
//vector <unsigned long long> deck;
//vector <unsigned long long> deckOrig;
struct inst_s {
	int type; //1 = deal // 2 = cut //3 = incdeal
	int val;
};
int instTOT;
struct inst_s inst[100];
void run(int);
void runFOR(int FRM);
unsigned long long runBACK(unsigned long long FRM);
unsigned long long CARD = 9;

int main(int argc, char **argv)
{
	char *tmp;
	ENDLIST = ENDL;
	if (argc == 3) {ENDLIST = strtoll(argv[2], &tmp, 10);}
	if (argc == 4) {CARD = strtoll(argv[3], &tmp, 10);}
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); 
       
        char line1[LINE];

	//for (unsigned long long i = 0; i < END; i++) 
	//for (int i = 0; i < END; i++) { deck.push_back(i); } deckOrig = deck;

	printf("filled the deck...\n"); fflush(stdout);
	
/*
	for (int i = 10008; i < 30000; i ++) {
		int count = 0;
		for (int k = 2; k < i/2+1; k++) {
			if (i % k == 0) {
				count++;
			}
			if (count > 1) {break;}
		}
		if (count == 0) {printf("prime %d\n", i); getchar();}
	}
*/
	
while(1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif
	if (strcmp(line1, "deal into new stack") == 0) {
		inst[leny].type = 1;
		leny++;
		continue;
	} 

	int cutNum;
	int ret1 = sscanf(line1, "cut %d", &cutNum);
	if (ret1 == 1) {
		inst[leny].type = 2;
		inst[leny].val = cutNum;
		leny++;
		continue;
		
	}
	
	int dealInc;
	int ret2 = sscanf(line1, "deal with increment %d", &dealInc);
	if (ret2 == 1) {
		inst[leny].type = 3;
		inst[leny].val = dealInc;
		leny++;
		continue;
	}
	leny++;
	//printf("lenx %d - leny %d\n", lenx, leny);
}
fclose(a);
	instTOT = leny;
	printf("Starting RUN\n");

#ifndef _EX_ 
	unsigned long long FRM2 = 2020;
	printf("ENDLIST is %llu FRM2 is %llu\n", ENDLIST, FRM2);
	for (int t = 0; t < 3; t++) {
		FRM2 = runBACK((unsigned long long)FRM2);
		printf("t:(%3d) ->  %16llu\n", t, FRM2);
	}
#else 
	deck.clear();
	for (int i = 0; i < ENDLIST; i++) {
		deck.push_back(i);
	}
	for (int t = 0; t < 3; t++) {
		run(ENDLIST);
		
		printf("[[t: %d]] -- ", t);
		for (auto it = deck.begin(); it != deck.end(); it++) {
			if (ENDLIST == 10) {
				printf(" %d ", *it);
			} else if (it - deck.begin() == CARD) {
				printf(" %d ", *it);
			}
		}
		printf("\n");
	}

	for (int i = 0; i < ENDLIST; i++) {
		int FRM2 = i;
		if (FRM2 != CARD) {continue;}
		for (int t = 0; t < 3; t++) {
			FRM2 = runBACK(FRM2);
			//if (t == 2) {
				//printf("%d ->  %d\n", i, FRM2);
				printf("AFTER GOING BACK %d --- %d ->  %d\n", t, i, FRM2);
			//}
		}
	}
#endif 
}

unsigned long long runBACK(unsigned long long FRM) {
	for (int i = instTOT-1; i >= 0; i--) {
/*
		printf("instNum is %d type %d ", i, inst[i].type);
		if (inst[i].type == 2 || inst[i].type == 1) {
			printf(" val %d\n", inst[i].val);
		} else {
			printf("\n");
		}
		printf("FRM is %llu\n", FRM);
*/
		switch(inst[i].type) {
			case 1: {
				//reverse(deck.begin(), deck.end());
				FRM = ENDLIST - FRM -1;
				break;
				}
			case 2:
				{
				int cutNum = inst[i].val;
				unsigned long long cut1;
				if (cutNum < 0) {
					//cut1 = ENDLIST+cutNum;
					cut1 = abs(cutNum);
				} else {
					//cut1 = (unsigned long long) cutNum;
					cut1 = ENDLIST-cutNum;
				}

				if (cut1 > FRM) {
					//FRM = (FRM -(ENDLIST-cut1) + (3*ENDLIST)) % ENDLIST;
					//FRM = (FRM -(ENDLIST-cut1)) % ENDLIST;
					FRM = FRM + cut1 % ENDLIST;
				} else if (cut1 <= FRM) {
					//FRM = (FRM +cut1 + (3*ENDLIST)) % ENDLIST;
					FRM = FRM - cut1;
				}
				while (FRM < 0) {
					FRM = (FRM + ENDLIST) % ENDLIST;
					printf("here never"); exit(0);
				}
				break;
				}
			case 3:
				{
				//printf("dealInc (%d): . FRM:(%llu)\n", inst[i].val, FRM); fflush(stdout);
				unsigned long long dealInc = inst[i].val;
				unsigned long long mo = FRM % dealInc;
				unsigned long long di = FRM / dealInc;

				int found = 0;
				if (FRM == 0) {
					printf("FRM zero\n");
					FRM = 0;
					break;
				} else if (mo == 0) {
					FRM = di;
					break;
				} else {
					unsigned long long FRMORIG = FRM;
					unsigned long long FRMANS;
					for (unsigned long long j = 0; j < dealInc; j++) {
						FRM = FRMORIG;	
						unsigned long long ans = FRM + (ENDLIST * j);
						if (ans % dealInc == 0) {
							//printf("ans is %llu -- FRM is %llu -- j is %llu dealInc %llu \n", ans, FRM, j, dealInc);
							FRMANS = ans/dealInc;
							found++;
						}
					}
					FRM = FRMANS;
				}
				assert(found == 1);
				if (found == 0) {perror("ZERO FOUND\n"); exit(0);}
				if (found != 1) {printf("found is %d\n", found);}
/*
				for (int unsigned long long j = 0; j < ENDLIST; j++) {
					unsigned long long ans = (j * dealInc ) % ENDLIST;
					if (ans == FRM) {
						FRM = j; break;		
					}
				}
*/
/*
				unsigned long long per1 = ENDLIST / dealInc;
				unsigned long long per2 = ENDLIST % dealInc;
				unsigned long long mo = FRM % dealInc;
				unsigned long long di = FRM / dealInc;
				
				if (FRM == 0) {
					FRM = 0;
				} else if (mo == 0) {
					FRM = di;
				} else {
					//di++;
					FRM = (di +  ((dealInc - mo+1) * per2) + (2*ENDLIST))% ENDLIST;
					//FRM = (di +  ((dealInc - mo) * dealInc) + (2*ENDLIST))% ENDLIST;
				}
				printf("after FRM is %llu\n", FRM);
*/
				break;
				}

		}

	}
	return FRM;
}

/*
void runFOR(int FRM) {
	for (int i = 0; i < instTOT; i++) {
		switch(inst[i].type) {
			case 1: {
				//reverse(deck.begin(), deck.end());
				FRM = ENDLIST - FRM;
				break;
				}
			case 2:
				{
				int cutNum = inst[i].val;
				unsigned long long cut1 = (unsigned long long)cutNum;
				if (cutNum < 0) {
					cut1 = END+cutNum;
				}

				if (cut1 > FRM) {
					FRM = (END-cut1)+FRM;
				} else if (cut1 <= FRM) {
					FRM = FRM - cut1;
				}
				break;
				}
			case 3:
				{
				int dealInc = inst[i].val;
				FRM =  (FRM * dealInc) % END;
				break;
				break;
				}

		}

	}
}
*/
void run(int END) {
	for (int i = 0; i < instTOT; i++) {
		switch(inst[i].type) {
			case 1: {
				reverse(deck.begin(), deck.end());
				break;
				}
			case 2:
				{
				int cutNum = inst[i].val;
				//vector <unsigned long long> tmpV(END);
				vector <int> tmpV(END);
				unsigned long long cut1 = (unsigned long long)cutNum;
				if (cutNum < 0) {
					cut1 = END+cutNum;
				}
				//vector<unsigned long long>::iterator itm;
				vector<int>::iterator itm;
				itm = deck.begin() + cut1;

				copy(itm, deck.end(), tmpV.begin());
				copy(deck.begin(), itm, tmpV.begin()+(END-cut1));
				deck = tmpV;
				break;
				}
			case 3:
				{
				int dealInc = inst[i].val;
				//vector<unsigned long long> tmpVe(END);
				vector<int> tmpVe(END);
				for (int i = 0; i < END; i++) {
					int pos = (i*dealInc)%END;
					tmpVe[pos] = deck[i];
				}
				deck = tmpVe;
				break;
				}

		}

	}
}
/*
				if (FRM % dealInc == 0) {
					FRM = FRM/dealInc;
				} else {
					if (ENDLIST - FRM > FRM) {
						printf("FOR\n");
						for (unsigned long long i = 0; i < ENDLIST; i++) {
							unsigned long long ans =  (i * dealInc) % ENDLIST;
							if (ans == FRM) {FRM = i; break;}
						}
					} else {

						printf("BAK\n");
						for (unsigned long long i = ENDLIST-1; i >= 0; i--) {
							unsigned long long ans =  (i * dealInc) % ENDLIST;
							if (ans == FRM) {FRM = i; break;}
						}

					}
				}
*/
/*
	for (int z = 0; var_ints[z]!= -1; z++) {
		deck.clear();
		for (int i = 0; i < var_ints[z]; i++) {
			deck.push_back(i);
		}
		printf("var_insts[z] is %d deck.size() is %d\n", var_ints[z], (int)deck.size());
		for (int j = 0; j < 3; j++) {
			run(var_ints[z]);
			printf("******** pos0 %d -- pos 2020:%d\n", deck[0], deck[2020]);
			
			//if (deck == deckOrig) { printf("repeat at j:%d\n", j); getchar(); }
		}
		printf("Result: "); fflush(stdout);
		printf("******** pos0 %d -- pos 2020:%d\n", deck[0], deck[2020]);
		printf("-------\n");
	}
*/
//	printf("******** pos 2019%llu\n", deck[2019]);
//	printf("******** pos 2021%llu\n", deck[2021]);
