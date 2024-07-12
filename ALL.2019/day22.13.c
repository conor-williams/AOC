#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <inttypes.h>
#include<bits/stdc++.h>

#include <bigintclass.h>
#include <bigint_function_definitions.h>

using ll=long long int;
using namespace std;

int lenx, leny;
#define DAY "2019 day22 part2\n"
#undef _DEBUG_
#define getchar()
#define LINE 200
bigint ENDL("119315717514047");
//#define ENDL (bigint)10007
//bigint _big__big_pow2(bigint x, bigint y, bigint z);

struct inst_s {
	int type; //1 = deal // 2 = cut //3 = incdeal
	int val;
};
int instTOT;
struct inst_s inst[100];

void runFOR2();
bigint inv(bigint va);
bigint offset("0");
bigint increment("1");

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
	bigint E2 = (bigint)ENDL-(bigint)2;
	bigint I1 = (bigint)1-increment;
	offset *= big_pow(I1,  E2) % (bigint)ENDL;  
	bigint second = 101741582076661;
	increment = big_pow(increment, second) % (bigint)ENDL;
        cout << "offset: " << offset << endl;;
	cout << "increment here is " << increment << endl;
       
	//offset = bigint("9154372642351086312809932254992713119267173353156446105615019182820382134356462930461220784270155999170896135475940207950810416752775720572575989941759795455046599650023839598425626661890904410084372091846841253142015667486504551414085355300171785955635652016714380463457031996543862638122972721477653145580927457490087019444973879345173604613549836383397751385784600151044056443657018606378415702682228417945261899551786034361342324300299465303769084248739702844376873078906883773638187204951142585639390025985662824358393797563792116032455221547447453058879034794735679820251797884147231528759922006");
        //increment = bigint("23886232355104");
	printf("here here here\n");
	bigint inc2020 = increment * bigint("2020");
	bigint oneMinus = bigint("1") - increment;
	bigint tenE = bigint("100") * ENDL;
	bigint ans2 =  (((inc2020 + (oneMinus *offset)) % ENDL) + tenE) % ENDL;
//	bigint ans2 =  (((((bigint) (((bigint)2020 * increment) + ((bigint)1-increment) *offset))) % ENDL) + (bigint)10*ENDL) %ENDL;

	assert(ans2 < ENDL);
	printf("\n\nCONOR: ans2->  ");
	cout << ans2 << endl;
/*
	runFOR2();
	offset *= _big__big_pow2(1-increment,  ENDL-2, ENDL);  
	increment = (bigint)_big__big_pow2(increment, 101741582076661, ENDL);
	bigint ans2 =  ((((bigint) ((2020 * increment) + ((1-increment) *offset) )) % ENDL) + 2*ENDL) %ENDL;

	assert(ans2 < ENDL);
	printf("\n\nCONOR: ans2->  ");
	cout << ans2 << endl;
*/

}

/*
bigint _big__big_pow2(bigint x, bigint y, bigint z)
{
 
    bigint res = 1;
    bigint x1 = x;

    if (x1 > 0) {
	    x1 = x1 % z;
    } else if (x1 < 0) {
	    x1 = ((x1 % z) + 5000*z) %z;
    }
 
    if (x1 == (bigint)0) return (bigint)0;
 
    while (y > (bigint)0) 
    { 
        if (y & (bigint)1) 
            res = (res*x1) % z; 
 
        //y = y>>1; 
	y = y/2;
        x1 = (x1*x1) % z; 
    } 
	assert (res < z);
    return res; 
 
}
*/
/*
bigint inv(bigint x) {
    bigint res = 1;     // Initialize result 
 
    bigint x1 = (bigint)x;
    bigint y = ENDL -2;
    bigint p = ENDL;
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
*/

void runFOR2() {
	for (int i = 0; i < instTOT; i++) {
		switch(inst[i].type) {
			case 1: { //into // reverse
				offset -= increment; increment *= (bigint)-1;	
			
				cout << offset << endl;
				cout << increment << endl;

				break;
				}
			case 2:
				{ //cut 
				offset += increment * (bigint)inst[i].val;
				cout << offset << endl;
				break;
				}
			case 3:
				{ //with increment
				printf("increment -- val is %d\n", inst[i].val);
				bigint in = (bigint)inst[i].val;
				bigint E = (bigint)ENDL-(bigint)2;
				cout << "calling big_pow" << endl;
				bigint tm = big_pow(in, E) %(bigint)ENDL;  
				cout << "after big_pow" << endl;
				increment *= tm;
				cout << increment << endl;
				break;
				}

		}

	}
}
/*
int main(){
    bigint a,b,n,ans,M=1000000007;
    cin>>a>>b>>n;
    ans=_big__big_pow(a,b,n);
    cout<<ans<<endl;
}
*/
