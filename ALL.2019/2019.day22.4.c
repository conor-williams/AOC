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
long long ENDLIST;
#ifdef _EX_
//#define ENDLIST 10
//#define ENDL 29989
//#define ENDL 1002247
//#define ENDL 19993
#define ENDL 10007

//#define ENDL 10007
#else
#define ENDL (long long)119315717514047
//#define END 19993
#endif
int var_ints[] = { 10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 19993, -1};


vector <int> deck;
vector <int> deckOrig;
vector <int> decks;
///int decksPos = 0;

struct inst_s {
	int type; //1 = deal // 2 = cut //3 = incdeal
	int val;
};
int instTOT;
struct inst_s inst[100];
void run(int);
void runFOR(int FRM);
long long runBACK(long long FRM);
long long CARD = 9;

int main(int argc, char **argv)
{
	printf("CHECKING CYCLE\n");
	char *tmp;
	ENDLIST = ENDL;
	if (argc == 3) {ENDLIST = strtoll(argv[2], &tmp, 10);}
	if (argc == 4) {CARD = strtoll(argv[3], &tmp, 10);}
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); 
       
        char line1[LINE];


	for (int i = 0; i < ENDLIST; i++) { deck.push_back(i); } deckOrig = deck;
	printf("filled the deck.of %lld..\n", ENDLIST); fflush(stdout);
	
//29989	

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

	//for (int i = 0; i < ENDLIST; i++) { deck.push_back(i); }

	{decks = deck;}
	for (int t = 1; t < ENDLIST+10; t++) {
		run(ENDLIST);
		
		if (decks == deck) {
			printf("cycle to zero at %d == 0\n", t);
		}
		//if (found == 0) {decks[decksPos++] = deck;}
	}
	printf("FIN\n");

}

long long runBACK(long long FRM) {
	for (int i = instTOT-1; i >= 0; i--) {
/*
		printf("instNum is %d type %d ", i, inst[i].type);
		if (inst[i].type == 2 || inst[i].type == 1) {
			printf(" val %d\n", inst[i].val);
		} else {
			printf("\n");
		}
		printf("FRM is %lld\n", FRM);
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
				long long cut1 = (long long)cutNum;
				if (cutNum < 0) {
					cut1 = ENDLIST+cutNum;
				}

				if (cut1 > FRM) {
					FRM = (FRM -(ENDLIST-cut1) + (2*ENDLIST)) % ENDLIST;
					//FRM = (FRM -(ENDLIST-cut1)) % ENDLIST;
				} else if (cut1 <= FRM) {
					FRM = (FRM +cut1 + (2*ENDLIST)) % ENDLIST;
				}
				while (FRM < 0) {
					FRM = (FRM + ENDLIST) % ENDLIST;
				}
				break;
				}
			case 3:
				{
				//printf("dealInc (%d): . FRM:(%lld)\n", inst[i].val, FRM); fflush(stdout);
				long long dealInc = inst[i].val;
				long long mo = FRM % dealInc;
				long long di = FRM / dealInc;

				int found = 0;
				if (FRM == 0) {
					printf("FRM zero\n");
					FRM = 0;
					break;
				} else if (mo == 0) {
					FRM = di;
					break;
				} else {
					long long FRMORIG = FRM;
					long long FRMANS;
					for (long long j = 0; j < dealInc; j++) {
						FRM = FRMORIG;	
						long long ans = FRM + (ENDLIST * j);
						if (ans % dealInc == 0) {
							//printf("ans is %lld -- FRM is %lld -- j is %lld dealInc %lld \n", ans, FRM, j, dealInc);
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
				for (int long long j = 0; j < ENDLIST; j++) {
					long long ans = (j * dealInc ) % ENDLIST;
					if (ans == FRM) {
						FRM = j; break;		
					}
				}
*/
/*
				long long per1 = ENDLIST / dealInc;
				long long per2 = ENDLIST % dealInc;
				long long mo = FRM % dealInc;
				long long di = FRM / dealInc;
				
				if (FRM == 0) {
					FRM = 0;
				} else if (mo == 0) {
					FRM = di;
				} else {
					//di++;
					FRM = (di +  ((dealInc - mo+1) * per2) + (2*ENDLIST))% ENDLIST;
					//FRM = (di +  ((dealInc - mo) * dealInc) + (2*ENDLIST))% ENDLIST;
				}
				printf("after FRM is %lld\n", FRM);
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
				long long cut1 = (long long)cutNum;
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
				//vector <long long> tmpV(END);
				vector <int> tmpV(END);
				long long cut1 = (long long)cutNum;
				if (cutNum < 0) {
					cut1 = END+cutNum;
				}
				//vector<long long>::iterator itm;
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
				//vector<long long> tmpVe(END);
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
						for (long long i = 0; i < ENDLIST; i++) {
							long long ans =  (i * dealInc) % ENDLIST;
							if (ans == FRM) {FRM = i; break;}
						}
					} else {

						printf("BAK\n");
						for (long long i = ENDLIST-1; i >= 0; i--) {
							long long ans =  (i * dealInc) % ENDLIST;
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
//	printf("******** pos 2019%lld\n", deck[2019]);
//	printf("******** pos 2021%lld\n", deck[2021]);
