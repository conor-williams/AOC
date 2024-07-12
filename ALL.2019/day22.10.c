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

using namespace std;

typedef __int128 uint128_t;

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)

static int print_u128_u(uint128_t u128)
{
    int rc;
    if (u128 > UINT64_MAX)
    {
        uint128_t leading  = u128 / P10_UINT64;
        uint64_t  trailing = u128 % P10_UINT64;
        rc = print_u128_u(leading);
        rc += printf("%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }
    else
    {
        uint64_t u64 = u128;
        rc = printf("%" PRIu64, u64);
    }
    return rc;
}


int lenx, leny;
#define DAY "2019 day22 part2\n"
#undef _DEBUG_
#define LINE 200
#define ENDL (__int128)119315717514047
__int128 pow2(__int128 x, __int128 y, __int128 z);

struct inst_s {
	int type; //1 = deal // 2 = cut //3 = incdeal
	int val;
};
int instTOT;
struct inst_s inst[100];

void runFOR2();
__int128 inv(int va);
__int128 offset = 0;
__int128 increment = 1;

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

#ifndef _EX_ 

	runFOR2();
	printf("increment: "); print_u128_u(increment);
	offset *= inv(1-increment);  
	//printf("offset %lld increment %lld\n", offset, increment);
	print_u128_u(increment);
	increment = (__int128)pow2(increment, 101741582076661, ENDL);
	printf("increment is : ");
	print_u128_u(increment); printf("\n");
	__int128 ans2 =  ((__int128) ((2020 * increment) + ((1-increment) *offset) )) % ENDL;

	printf("\nhere1 ENDL:");
	print_u128_u(ENDL); printf("\n");
	

	ans2 = ans2 % ENDL;
	__int128 divit = ans2/ENDL;
	printf("divit ---> ");
	print_u128_u(divit); printf("\n");
	if (ans2 > ENDL) {
		printf("GREATER\n");
	} else {
		printf("LESS\n");
	}
	printf("\n\nCONOR: ans->");
	print_u128_u(ans2); printf("\n");

#endif 
}

__int128 pow2(__int128 x, __int128 y, __int128 z)
{
 
    __int128 res = 1;
    __int128 x1 = x;

    x1 = x1 % z;
       printf("x1: mod of z-- "); print_u128_u(x1); printf("\n");
  
    if (x1 == 0) return 0;
 
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x1) % z; 
 
        y = y>>1; 
        x1 = (x1*x1) % z; 
       printf("res: -- "); print_u128_u(res); printf("\n");
       printf("x1: -- "); print_u128_u(x1); printf("\n");
    } 
//   printf("res: -- "); print_u128_u(res); printf("\n");
//	__int128 t1 = res/z;
//	res -= t1*z;
	res = res%z;
    return res; 
 
}

__int128 inv(int x) {
    __int128 res = 1;     // Initialize result 
 
    __int128 x1 = (__int128)x;
    __int128 y = ENDL -2;
    __int128 p = ENDL;
    x1 = x1 % p; 
  
    if (x1 == 0) return 0;
 
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x1) % p; 
 
        y = y>>1;
        x1 = (x1*x1) % p; 
    } 
    res = res %p;
    return res; 
} 

void runFOR2() {
	for (int i = 0; i < instTOT; i++) {
		switch(inst[i].type) {
			case 1: {
				offset -= increment; increment *=-1;	
				printf("offset reverse in rev\n");
				break;
				}
			case 2:
				{
				offset += increment * inst[i].val;
				printf("offset in cut\n ");
				break;
				}
			case 3:
				{
				printf("about to call inv is reshuffle\n");
				printf("val is %d\n", inst[i].val);
				__int128 tm = inv(inst[i].val);
				increment *= tm;
				printf("got back.tm:: ");
				print_u128_u(tm); printf("\n");

				printf("increment is: ");
				print_u128_u(increment); printf("\n");
				break;
				}

		}

	}
}
