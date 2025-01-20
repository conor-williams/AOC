#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <inttypes.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std;

int lenx, leny;
#define DAY "2019 day22 part2\n"
#undef _DEBUG_
#define LINE 200
#define ENDL (int1024_t)119315717514047
//#define ENDL (int1024_t)10007
int1024_t pow2(int1024_t x, int1024_t y, int1024_t z);

struct inst_s {
	int type; //1 = deal // 2 = cut //3 = incdeal
	int val;
};
int instTOT;
struct inst_s inst[100];

void runFOR2();
int1024_t inv(int1024_t va);
int1024_t offset = 0;
int1024_t increment = 1;

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); 
        char line1[LINE];

	printf("filled the deck...\n"); fflush(stdout);
	
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

	runFOR2();
	offset *= pow2(1-increment,  ENDL-2, ENDL);  
	increment = (int1024_t)pow2(increment, 101741582076661 , ENDL);
        cout << "offset: " << offset << endl;;
	cout << "increment here is " << increment << endl;
       
	offset = 9154372642351086312809932254992713119267173353156446105615019182820382134356462930461220784270155999170896135475940207950810416752775720572575989941759795455046599650023839598425626661890904410084372091846841253142015667486504551414085355300171785955635652016714380463457031996543862638122972721477653145580927457490087019444973879345173604613549836383397751385784600151044056443657018606378415702682228417945261899551786034361342324300299465303769084248739702844376873078906883773638187204951142585639390025985662824358393797563792116032455221547447453058879034794735679820251797884147231528759922006;
        increment = 23886232355104;
	int1024_t ans2 =  ((((int1024_t) ((2020 * increment) + ((1-increment) *offset))) % ENDL) + ENDL) %ENDL;

	assert(ans2 < ENDL);
	printf("\n\nCONOR: ans2->  ");
	cout << ans2 << endl;
/*
	runFOR2();
	offset *= pow2(1-increment,  ENDL-2, ENDL);  
	increment = (int1024_t)pow2(increment, 101741582076661, ENDL);
	int1024_t ans2 =  ((((int1024_t) ((2020 * increment) + ((1-increment) *offset) )) % ENDL) + 2*ENDL) %ENDL;

	assert(ans2 < ENDL);
	printf("\n\nCONOR: ans2->  ");
	cout << ans2 << endl;
*/

}

int1024_t pow2(int1024_t x, int1024_t y, int1024_t z)
{
 
    int1024_t res = 1;
    int1024_t x1 = x;

    if (x1 > 0) {
	    x1 = x1 % z;
    } else if (x1 < 0) {
	    x1 = ((x1 % z) + 5000*z) %z;
    }
 
    if (x1 == 0) return 0;
 
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x1) % z; 
 
        y = y>>1; 
        x1 = (x1*x1) % z; 
    } 
	assert (res < z);
    return res; 
 
}

int1024_t inv(int1024_t x) {
    int1024_t res = 1;     // Initialize result 
 
    int1024_t x1 = (int1024_t)x;
    int1024_t y = ENDL -2;
    int1024_t p = ENDL;
	assert(x > 0);

    if (x1 > 0) {
	    x1 = x1 % p;
    } else if (x1 < 0) {
	    x1 = ((x1 % p) + 5*p) %p;
    }
    //x1 = x1 % p; 
  
    if (x1 == 0) return 0;
 
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x1) % p; 
 
        y = y>>1;
        x1 = (x1*x1) % p; 
    } 
    //res = res %p;
	assert (res < p);
    return res; 
} 

void runFOR2() {
	for (int i = 0; i < instTOT; i++) {
		switch(inst[i].type) {
			case 1: { //into // reverse
				offset -= increment; increment *=-1;	
			
				cout << offset << endl;
				cout << increment << endl;

				break;
				}
			case 2:
				{ //cut 
				offset += increment * inst[i].val;
				cout << offset << endl;
				break;
				}
			case 3:
				{ //with increment
				printf("val is %d\n", inst[i].val);
				int1024_t tm = pow2(inst[i].val,  ENDL-2, ENDL);  
				//int1024_t tm = inv(inst[i].val);
				increment *= tm;
				cout << increment << endl;
				break;
				}

		}

	}
}
