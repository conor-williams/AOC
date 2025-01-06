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

#include <unistd.h>

#define getchar()
//#include <bigintclass.h>
//#include <bigint_function_definitions.h>

using ll=long long int;
using namespace std;
//compile: copy in bigint .h headers : -I.
int lenx, leny;
#define DAY "2019 day22 part2\n"
#undef _DEBUG_
#define getchar()
#define LINE 200
bigint ENDL("119315717514047");
//#define ENDL (bigint)10007
//bigint _big__big_pow2(bigint x, bigint y, bigint z);
bigint pow2(bigint x, bigint y, bigint z);

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
int fd;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); 

	fflush(stdout); fd = dup(1); close(1);
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
        cout << "offset: " << offset << endl;;
	cout << "increment here is " << increment << endl;
        //offset = bigint("89235752904760004379846037592493491454385121337233606032704815167101610241615004446546907091698062319827771581379878359114633925742691892292102241472992663151404098907882215539987246504315255357235692085996310756280360589673947916592002408783975553776220318045734090413778860779428247481538761477917089022593658771319107809463938330775391797593982464511757903680990108650810921232359895372595491759547194324722856179029187007521976099234486647270909343565294658162955517404894596431896376671385732528735943813045835139183361267913952287808495518762330034660223118561992506724374222553834");
        //increment = bigint("-21236495217695033207700216434524059624986285451065696521300760552111527763477374111203946342120681969011621563331777635441713869112655834756227237883181989829393463112856060577613219221915547067868454991257138608713641242337409405262495032934780638907355646025189841301803296652795463234295512872552471952280783248299727476054083962921398966209918708042342998068697452647088317982093883257866164573626823487833773120368657432784569974124941083756974998110260871888923330440467893040683969945337591141180178071346830393766179295454431374828666744720476405529145179817280990819123200000");

	bigint I1 = (bigint)1-increment;
	bigint E2 = (bigint)ENDL-(bigint)2;
	offset *= pow2(I1,  E2, (bigint)ENDL);  
	//printf("offset now "); cout << offset; cout << endl;
	bigint second = 101741582076661;
	increment = pow2(increment, second, (bigint)ENDL);
       
	//offset = bigint("9154372642351086312809932254992713119267173353156446105615019182820382134356462930461220784270155999170896135475940207950810416752775720572575989941759795455046599650023839598425626661890904410084372091846841253142015667486504551414085355300171785955635652016714380463457031996543862638122972721477653145580927457490087019444973879345173604613549836383397751385784600151044056443657018606378415702682228417945261899551786034361342324300299465303769084248739702844376873078906883773638187204951142585639390025985662824358393797563792116032455221547447453058879034794735679820251797884147231528759922006");
        //increment = bigint("23886232355104");
	printf("here here here\n");
	bigint inc2020 = increment * bigint("2020");
	bigint oneMinus = bigint("1") - increment;
	bigint tenE = bigint("100") * ENDL;
	bigint ans2 =  (((inc2020 + (oneMinus *offset)) % ENDL) + tenE) % ENDL;
//	bigint ans2 =  (((((bigint) (((bigint)2020 * increment) + ((bigint)1-increment) *offset))) % ENDL) + (bigint)10*ENDL) %ENDL;

	assert(ans2 < ENDL);
	dup2(fd, 1);
	printf("\n\nans: ans2->  ");
	//cout << ans2 << endl;
	printf("%s\n", ans2.str.c_str());
	//exit(0);
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

bigint pow2(bigint x, bigint y, bigint z)
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
        //if (y & (bigint)1) 
	int yyyy1 = y.str.back() - 48;
	//y.str();
        if (yyyy1 & 1) 
            res = (res*x1) % z; 
 
        //y = y>>1; 
	y = y/2;
        x1 = (x1*x1) % z; 
    } 
	assert (res < z);
    return res; 
 
}
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
				bigint tm = pow2(in, E, (bigint)ENDL);  
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


/*
    bigint class.h

    bigint Library for C++

    MIT License

    Created by Roshan Gupta on 16-10-2020
    Copyright (c) 2020 Roshan Gupta

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/*
#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <limits>

class bigint {
    public: 
        std::string str; // only data memeber for strong Big Integer as String. [For signed int, str[0] = '-']
        

        // Function Definitions for Internal Uses

        static std::string trim(std::string);
        static std::string add(std::string, std::string);
        static std::string subtract(std::string, std::string);
        static std::string multiply(std::string, std::string);
        static std::string divide(std::string, std::string);

        static std::string mod(std::string, std::string);
        static std::string shortDivide(std::string, unsigned long long int);
        static std::string maximum(std::string, std::string);
        static bool is_maximum(std::string, std::string);
        static bool is_strictlyMaximum(std::string, std::string);
        static std::string minimum(std::string, std::string);
        static bool is_minimum(std::string, std::string);
        static bool is_strictlyMinimum(std::string, std::string);
        static bool is_bigint(std::string);

        // Public Property

        static std::string abs(std::string);
        static std::string pow(std::string, std::string);
        static std::string sqrt(std::string);
        static std::string log2(std::string);
        static std::string log10(std::string);
        static std::string logwithbase(std::string, std::string);
        static std::string antilog2(std::string);
        static std::string antilog10(std::string);
        static void swap(std::string&, std::string&);
        static std::string reverse(std::string);
        static std::string gcd(std::string, std::string);
        static std::string lcm(std::string, std::string);
        static std::string fact(std::string);
        static bool isPalindrome(std::string);
        static bool isPrime(std::string);        


    public: 
        // Constructors for big int.
        bigint() {
            str = '0';  //default value
        }
        bigint(std::string s) {
            if(!is_bigint(s))
                throw std::runtime_error("Invalid Big Integer has been fed.");   // if the input string is not valid number.
            str = s;
        }
        bigint(long long int n) {
            str = std::to_string(n);
        }
        bigint(int n) {
            str = std::to_string(n);
        }
        bigint(long int n) {
            str = std::to_string(n);
        }
        bigint(const bigint &n) {
            str = n.str;
        }

        // operator overloading for output stream {<<}
        friend std::ostream &operator << (std::ostream& stream, const bigint &n) {
            stream << n.str;
            return stream;
        }

        // operator overloading for input stream {>>}
        friend std::istream &operator >> (std::istream& stream, bigint &n) {
            stream >> n.str;
            return stream;
        }

        // Operator {+} Overloadings, for different kind of 
        //parameter for the programmer's convinience  

        bigint operator + (bigint const &n) {
            bigint ans;
            ans.str = add(str, n.str);
            return ans;
        }        
        friend bigint operator + (bigint const &n1, int n2) {
            bigint ans;
            ans.str = add(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator + (int n1, bigint const &n2) {
            bigint ans;
            ans.str = add(n2.str, std::to_string(n1));
            return ans;
        }
        friend bigint operator + (bigint const &n1, long int n2) {
            bigint ans;
            ans.str = add(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator + (long int n1, bigint const &n2) {
            bigint ans;
            ans.str = add(n2.str, std::to_string(n1));
            return ans;
        }
        friend bigint operator + (bigint const &n1, long long int n2) {
            bigint ans;
            ans.str = add(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator + (long long int n1, bigint const &n2) {
            bigint ans;
            ans.str = add(n2.str, std::to_string(n1));
            return ans;
        }

        // Extra shortcut feature

        bigint& operator += (bigint const n) {
            (*this).str = add((*this).str, n.str);
            return (*this);
        }
        
        

        // Operator {-} Overloadings, for different kind of 
        //parameter for the programmer's convinience  

        bigint operator - (bigint const &n) {
            bigint ans;
            ans.str = subtract(str, n.str);
            return ans;
        }

        friend bigint operator - (bigint const &n1, int n2) {
            bigint ans;
            ans.str = subtract(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator - (int n1, bigint const &n2) {
            bigint ans;
            ans.str = subtract(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator - (bigint const &n1, long int n2) {
            bigint ans;
            ans.str = subtract(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator - (long int n1, bigint const &n2) {
            bigint ans;
            ans.str = subtract(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator - (bigint const &n1, long long int n2) {
            bigint ans;
            ans.str = subtract(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator - (long long int n1, bigint const &n2) {
            bigint ans;
            ans.str = subtract(std::to_string(n1), n2.str);
            return ans;
        }

        // Extra shortcut feature

        bigint& operator -= (bigint const n) {
            (*this).str = subtract((*this).str, n.str);
            return (*this);
        }

        // Operator {*} Overloadings, for different kind of 
        //parameter for the programmer's convinience  

        bigint operator * (bigint const &n) {
            bigint ans;
            ans.str = multiply(str, n.str);
            return ans;
        }
        friend bigint operator * (bigint const &n1, int n2) {
            bigint ans;
            ans.str = multiply(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator * (int n1, bigint const &n2) {
            bigint ans;
            ans.str = multiply(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator * (bigint const &n1, long int n2) {
            bigint ans;
            ans.str = multiply(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator * (long int n1, bigint const &n2) {
            bigint ans;
            ans.str = multiply(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator * (bigint const &n1, long long int n2) {
            bigint ans;
            ans.str = multiply(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator * (long long int n1, bigint const &n2) {
            bigint ans;
            ans.str = multiply(std::to_string(n1), n2.str);
            return ans;
        }
        // Extra shortcut feature

        bigint& operator *= (bigint const n) {
            (*this).str = multiply((*this).str, n.str);
            return (*this);
        }

        // Operator {/} Overloadings, for different kind of 
        //parameter for the programmer's convinience  

        bigint operator / (bigint const &n) {
            bigint ans;
            ans.str = divide(str, n.str);
            return ans;
        }
        friend bigint operator / (bigint const &n1, int n2) {
            bigint ans;
            ans.str = divide(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator / (int n1, bigint const &n2) {
            bigint ans;
            ans.str = divide(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator / (bigint const &n1, long int n2) {
            bigint ans;
            ans.str = divide(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator / (long int n1, bigint const &n2) {
            bigint ans;
            ans.str = divide(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator / (bigint const &n1, long long int n2) {
            bigint ans;
            ans.str = divide(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator / (long long int n1, bigint const &n2) {
            bigint ans;
            ans.str = divide(std::to_string(n1), n2.str);
            return ans;
        }

        // Extra shortcut feature

        bigint& operator /= (bigint const n) {
            (*this).str = divide((*this).str, n.str);
            return (*this);
        }

        // Operator {%} Overloadings, for different kind of 
        //parameter for the programmer's convinience  

        bigint operator % (bigint const &n) {
            bigint ans;
            ans.str = mod(str, n.str);
            return ans;
        }
        friend bigint operator % (bigint const &n1, int n2) {
            bigint ans;
            ans.str = mod(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator % (int n1, bigint const &n2) {
            bigint ans;
            ans.str = mod(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator % (bigint const &n1, long int n2) {
            bigint ans;
            ans.str = mod(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator % (long int n1, bigint const &n2) {
            bigint ans;
            ans.str = mod(std::to_string(n1), n2.str);
            return ans;
        }
        friend bigint operator % (bigint const &n1, long long int n2) {
            bigint ans;
            ans.str = mod(n1.str, std::to_string(n2));
            return ans;
        }
        friend bigint operator % (long long int n1, bigint const &n2) {
            bigint ans;
            ans.str = mod(std::to_string(n1), n2.str);
            return ans;
        }
        
        // Extra shortcut feature
        
        bigint& operator %= (bigint const n) {
            (*this).str = mod((*this).str, n.str);
            return (*this);
        }

        //-------------------------------------------------
        //------------Increment and Decrement--------------
        //-------------------------------------------------

        // Operator {++} Overloadings
        //for the pre incremention  
        bigint& operator ++ () {
            (*this).str = add((*this).str, "1"); 
            return (*this);
        }
        // Operator {++} Overloadings for the post incremention  
        bigint operator ++ (int) {
            (*this).str = add((*this).str, "1"); 
            return (*this);
        }

        // Operator {--} Overloadings for the pre decremention  
        bigint& operator -- () {
            (*this).str = subtract((*this).str, "1");
            return (*this);
        }

        // Operator {--} Overloadings for the post incremention  
        bigint operator -- (int) {
            (*this).str = subtract((*this).str, "1"); 
            return (*this);
        }

        //-------------------------------------------------
        //------------Conditional Operators----------------
        //-------------------------------------------------

        // Operator {>} Overloadings, for different kind of parameter for the programmer's convinience  

        bool operator > (bigint const &n) {
            return is_strictlyMaximum(str, n.str);
        }
        friend bool operator > (bigint const &n1, int n2) {
            return is_strictlyMaximum(n1.str, std::to_string(n2));
        }
        friend bool operator > (int n1, bigint const &n2) {
            return is_strictlyMaximum(std::to_string(n1), n2.str);
        }
        friend bool operator > (bigint const &n1, long int n2) {
            return is_strictlyMaximum(n1.str, std::to_string(n2));
        }
        friend bool operator > (long int n1, bigint const &n2) {
            return is_strictlyMaximum(std::to_string(n1), n2.str);
        }
        friend bool operator > (bigint const &n1, long long int n2) {
            return is_strictlyMaximum(n1.str, std::to_string(n2));
        }
        friend bool operator > (long long int n1, bigint const &n2) {
            return is_strictlyMaximum(std::to_string(n1), n2.str);
        }

        // Operator {<} Overloadings, for different kind of parameter for the programmer's convinience  

        bool operator < (bigint const &n) {
            return is_strictlyMinimum(str, n.str);
        }
        friend bool operator < (bigint const &n1, int n2) {
            return is_strictlyMinimum(n1.str, std::to_string(n2));
        }
        friend bool operator < (int n1, bigint const &n2) {
            return is_strictlyMinimum(std::to_string(n1), n2.str);
        }
        friend bool operator < (bigint const &n1, long int n2) {
            return is_strictlyMinimum(n1.str, std::to_string(n2));
        }
        friend bool operator < (long int n1, bigint const &n2) {
            return is_strictlyMinimum(std::to_string(n1), n2.str);
        }
        friend bool operator < (bigint const &n1, long long int n2) {
            return is_strictlyMinimum(n1.str, std::to_string(n2));
        }
        friend bool operator < (long long int n1, bigint const &n2) {
            return is_strictlyMinimum(std::to_string(n1), n2.str);
        }

        // Operator {>=} Overloadings, for different kind of parameter for the programmer's convinience  

        bool operator >= (bigint const &n) {
            return is_maximum(str, n.str);
        }
        friend bool operator >= (bigint const &n1, int n2) {
            return is_maximum(n1.str, std::to_string(n2));
        }
        friend bool operator >= (int n1, bigint const &n2) {
            return is_maximum(std::to_string(n1), n2.str);
        }
        friend bool operator >= (bigint const &n1, long int n2) {
            return is_maximum(n1.str, std::to_string(n2));
        }
        friend bool operator >= (long int n1, bigint const &n2) {
            return is_maximum(std::to_string(n1), n2.str);
        }
        friend bool operator >= (bigint const &n1, long long int n2) {
            return is_maximum(n1.str, std::to_string(n2));
        }
        friend bool operator >= (long long int n1, bigint const &n2) {
            return is_maximum(std::to_string(n1), n2.str);
        }

        // Operator {<=} Overloadings, for different kind of parameter for the programmer's convinience  

        bool operator <= (bigint const &n) {
            return is_minimum(str, n.str);
        }
        friend bool operator <= (bigint const &n1, int n2) {
            return is_minimum(n1.str, std::to_string(n2));
        }
        friend bool operator <= (int n1, bigint const &n2) {
            return is_minimum(std::to_string(n1), n2.str);
        }
        friend bool operator <= (bigint const &n1, long int n2) {
            return is_minimum(n1.str, std::to_string(n2));
        }
        friend bool operator <= (long int n1, bigint const &n2) {
            return is_minimum(std::to_string(n1), n2.str);
        }
        friend bool operator <= (bigint const &n1, long long int n2) {
            return is_minimum(n1.str, std::to_string(n2));
        }
        friend bool operator <= (long long int n1, bigint const &n2) {
            return is_minimum(std::to_string(n1), n2.str);
        }


        // Operator {==} Overloadings, for different kind of parameter for the programmer's convinience  

        bool operator ==(bigint const &n) {
            return (*this).str == n.str;
        }
        friend bool operator == (bigint const &n1, int n2) {
            return n1.str == std::to_string(n2);
        }
        friend bool operator == (int n1, bigint const &n2) {
            return std::to_string(n1) == n2.str;
        }
        friend bool operator == (bigint const &n1, long int n2) {
            return n1.str == std::to_string(n2);
        }
        friend bool operator == (long int n1, bigint const &n2) {
            return std::to_string(n1) == n2.str;
        }
        friend bool operator == (bigint const &n1, long long int n2) {
            return n1.str == std::to_string(n2);
        }
        friend bool operator == (long long int n1, bigint const &n2) {
            return std::to_string(n1) == n2.str;
        }


        // Operator {!=} Overloadings, for different kind of parameter for the programmer's convinience  

        bool operator !=(bigint const &n) {
            return (*this).str != n.str;
        }
        friend bool operator != (bigint const &n1, int n2) {
            return n1.str != std::to_string(n2);
        }
        friend bool operator != (int n1, bigint const &n2) {
            return std::to_string(n1) != n2.str;
        }
        friend bool operator != (bigint const &n1, long int n2) {
            return n1.str != std::to_string(n2);
        }
        friend bool operator != (long int n1, bigint const &n2) {
            return std::to_string(n1) != n2.str;
        }
        friend bool operator != (bigint const &n1, long long int n2) {
            return n1.str != std::to_string(n2);
        }
        friend bool operator != (long long int n1, bigint const &n2) {
            return std::to_string(n1) != n2.str;
        }

        //-----------------------------------------------------------
        //--------Function Definitions for External Uses-------------
        //-----------------------------------------------------------

        
        static bigint _big_max(bigint &a, bigint &b) {     // returns the maximum value between two Big Integers.
            bigint ans;
            ans.str = maximum(a.str, b.str);
            return ans;
        }
        static bigint _big_min(bigint &a, bigint &b) {      // returns the minimum value between two Big Integers.
            bigint ans;
            ans.str = minimum(a.str, b.str);
            return ans;
        }        
        static bigint _big_abs(bigint &a) {                 // returns the absolute value of Big Integer.
            bigint ans;
            ans.str = abs(a.str);
            return ans;
        }
        static bigint _big_pow(bigint &a, bigint &b) {      // returns the power value between two Big Integers i.e., a^b, ^ -> power
            bigint ans;
            ans.str = pow(a.str, b.str);
            return ans;
        }
        static bigint _big_sqrt(bigint &a) {                // returns the square root value of Big Integer.
            bigint ans;
            ans.str = sqrt(a.str);
            return ans;
        }
        static bigint _big_log2(bigint &a) {                // returns the log of Big Integer to the base of 2.
            bigint ans;
            ans.str = log2(a.str);
            return ans;
        }
        static bigint _big_log10(bigint &a) {               // returns the log of Big Integer to the base of 10.
            bigint ans;
            ans.str = log10(a.str);
            return ans;
        }
        static bigint _big_logwithbase(bigint &a, bigint &b) {  // returns the log of Big Integer(a) to the base of (b).
            bigint ans;
            ans.str = logwithbase(a.str, b.str);
            return ans;
        }
        static bigint _big_antilog2(bigint &a) {        // returns the antilog of Big Integer to the base of 2.
            bigint ans;
            ans.str = antilog2(a.str);
            return ans;
        }
        static bigint _big_antilog10(bigint &a) {       // returns the antilog of Big Integer to the base of 10.
            bigint ans;
            ans.str = antilog10(a.str);
            return ans;
        }
        static void _big_swap(bigint &a, bigint &b) {     // swaps the two Big Integers.
            swap(a.str, b.str);
        }
        static bigint _big_reverse(bigint &a) {             //Reverses the Big Integer.
            bigint ans;
            ans.str = reverse(a.str);
            return ans;
        }
        static bigint _big_gcd(bigint &a, bigint &b) {         // returns the gcd of Big Integers a and b.
            bigint ans;
            ans.str = gcd(a.str, b.str);
            return ans;
        }
        static bigint _big_lcm(bigint &a, bigint &b) {          // returns the lcm of Big Integers a and b.
            bigint ans;
            ans.str = lcm(a.str, b.str);
            return ans;
        }
        static bigint _big_fact(bigint &a) {                    // returns the factorial of Big Integer.
            bigint ans;
            ans.str = fact(a.str);
            return ans;
        }
        static bool _big_isPalindrome(bigint &a) {              // Check if the Big Integer is Palindromic Integer.
            return isPalindrome(a.str);
        }
        static bool _big_isPrime(bigint &a) {                   // Check if the Big Integer is Prime Integer.
            return isPrime(a.str);
        }


        // to biginteger functions

        static bigint _to_bigint(std::string s) {
            bigint ans;
            ans.str = s;
            return ans;
        }
        static bigint _to_bigint(int n) {
            bigint ans;
            ans.str = std::to_string(n);
            return ans;
        }
        static bigint _to_bigint(long int n) {
            bigint ans;
            ans.str = std::to_string(n);
            return ans;
        }
        static bigint _to_bigint(long long int n) {
            bigint ans;
            ans.str = std::to_string(n);
            return ans;
        }
};
*/


/*
    bigint_function_definitions.h

    bigint Library for C++

    MIT License

    Created by Roshan Gupta on 16-10-2020
    Copyright (c) 2020 Roshan Gupta

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


/*

#pragma once

#include "bigintclass.h"

#define big_abs bigint::_big_abs
#define big_max bigint::_big_max
#define big_min bigint::_big_min
#define big_pow bigint::_big_pow
#define big_sqrt bigint::_big_sqrt
#define big_log2 bigint::_big_log2
#define big_log10 bigint::_big_log10
#define big_logwithbase bigint::_big_logwithbase
#define big_antilog2 bigint::_big_antilog2
#define big_antilog10 bigint::_big_antilog10
#define big_swap bigint::_big_swap
#define big_reverse bigint::_big_reverse
#define big_gcd bigint::_big_gcd
#define big_lcm bigint::_big_lcm
#define big_fact bigint::_big_fact
#define big_isPrime bigint::_big_isPrime
#define big_isPalindrome bigint::_big_isPalindrome
#define to_bigint bigint::_to_bigint


bool bigint::is_bigint(std::string s) {                              // Checks if the feeded integer is valid Number or not.
    if(s[0] == '-')
        s.erase(0, 1);
    for(unsigned long long int i = 0; i < s.length(); ++i) {
        if(!((int)s[i] > 47 && (int)s[i] < 58))
            return false;
    }
    return true;
}


//---------------------------------------------------------
//--------Internal Arithmetic functions Definitions--------
//---------------------------------------------------------

//
//        ______________________________________________________
//                        Addition Function
//        ______________________________________________________
//                      Algorithm Explanation
//
//        Simple traversal from right to left in the longest string and adding each character 
//        from each of both strings as integer and keeping track of carry and storing the result 
//        into new String(sum). If the numbers are negative in either of the Strings provided 
//        the respective Subtract function is called.
//
//        Algorithmic Time Complexity : O(max(n, m))
//        Algorithmic Space Complexity : O(max(n, m))
//        where n ans m are the lengths of respective strings(Integers) provided.
//

std::string bigint::add(std::string str1, std::string str2) {          // returns arithmetic addition of str1+str2
    int str1_len = str1.length();
    int str2_len = str2.length();
    std::string sum = "";

    if(str1_len == 0 && str2_len == 0) {
        sum = "0";
    } else if(str1[0] == '-' && str2[0] == '-') {
        if(str1_len == 1 && str2_len == 1) {
            sum = "0";
        } else {
            sum = "-" + add(str1.erase(0, 1), str2.erase(0, 1));
        }
    } else if(str1[0] == '-') {
        sum = subtract(str2, str1.erase(0, 1));
    } else if(str2[0] == '-') {
        sum = subtract(str1, str2.erase(0, 1));
    } else {
        int i, j, track_sum, carry = 0;
        for(i = str1_len-1, j = str2_len-1; i >= 0 && j >= 0; --i, --j) {
            track_sum =  ((int)str1[i])-48 + ((int)str2[j])-48 + carry;
            carry = track_sum/10;
            sum = std::to_string(track_sum%10) + sum;
        }
        if(i >= 0 && j < 0) {
            for(; i >= 0; --i) {
                track_sum = ((int)str1[i])-48 + carry;
                carry = track_sum/10;
                sum = std::to_string(track_sum%10) + sum;
            }
        } else if(j >= 0 && i < 0) {
            for(; j >= 0; --j) {
                track_sum = ((int)str2[j])-48 + carry;
                carry = track_sum/10;
                sum = std::to_string(track_sum%10) + sum;
            }
        }
        if(carry) {
            sum = std::to_string(carry) + sum;
        }
    }
    return trim(sum);
}

//
//        ______________________________________________________
//                      Subtraction Function
//        ______________________________________________________
//                      Algorithm Explanation
//
//        Simple traversal from right to left in the longest string and subtracting each character 
//        from second string from  first string integer and keeping track of carry and storing the result 
//        into new String(ans). If the both numbers are negative in the Strings provided the respective 
//        Addition function is called.
//        
//        Algorithmic Time Complexity : O(max(n, m))
//        Algorithmic Space Complexity : O(max(n, m))
//        where n ans m are the lengths of respective strings(Integers) provided.
//

std::string bigint::subtract(std::string str1, std::string str2) {                 // returns arithmetic subtraction of str1-str2
    int str1_len = str1.length();
    int str2_len = str2.length();
    std::string sum = "";
    if(str1 == str2) {
        return "0";
    } else if(str1[0] == '-' && str2[0] == '-') {
        if(str2_len == 1 && str1_len == 1) {
            sum = "0";
        } else {
            bigint t1(str1.erase(0, 1));
            bigint t2(str2.erase(0, 1));
            std::string temp = subtract(t2.str, t1.str);
            bigint mx = maximum(t2.str, t1.str);
            if(temp[0] != '-' && mx.str == t1.str)
                sum = "-" + temp;
            else
                sum = temp;
        }
    } else if(str1[0] == '-') {
        sum = "-" + add(str1.erase(0, 1), str2);
    } else if(str2[0] == '-') {
        sum = add(str1, str2.erase(0, 1));
    } else {
        //? Implement Subtract

        int i, j, track_sum, carry = 0;      
        if(str1_len < str2_len) {
            std::string tp = str1;
            str1 = str2;
            str2 = tp;
            sum = "-" + subtract(str1, str2);
            return trim(sum);
        } else if(str1_len == str2_len) {
            bigint a(str1);
            bigint b(str2);
            bigint mx = maximum(a.str, b.str);
            if(mx.str == str2) {
                std::string tp = str1;
                str1 = str2;
                str2 = tp;
                bigint t1(str1);
                bigint t2(str2);
                bigint temp = subtract(str1, str2);
                sum = "-" + subtract(str1, str2);
                return trim(sum);
            }
        }
        int val1, val2;
        for(i = str1_len-1, j = str2_len-1; i >= 0 || j >= 0; --i, --j) {
            if(i >= 0) {
                val1 = (int) str1[i] - 48;
            } else {
                val1 = 0;
            }
            if(j >= 0) {
                val2 = (int) str2[j] - 48;
            } else {
                val2 = 0;
            }
            track_sum = val1 - val2 - carry;
            if(track_sum < 0) {
                track_sum += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            sum = std::to_string(track_sum) + sum;
        }
    }
    return trim(sum);
}

//
//        ______________________________________________________
//                     Multiplication Function
//        ______________________________________________________
//                      Algorithm Explanation
//
//        Like naive way of Multiplication. Traversing from the left of first string and multiplying
//        each character as integer to every character of second String as integer and tracking the
//        value of carry and adding to the last of each iterations.
//        
//        Algorithmic Time Complexity : O(n*m)
//        Algorithmic Space Complexity : O(n + m)
//        where n ans m are the lengths of respective strings(Integers) provided.
//

std::string bigint::multiply(std::string str1, std::string str2) {             // return arithmetic multiplication of str1*str2
    bool toAddNeg = false;
    int str1_len = str1.length();
    int str2_len = str2.length();
    std::string ans = "";
    if(str1[0] == '-' && str2[0] == '-') {
        ans = multiply(str1.erase(0, 1), str2.erase(0, 1));
    } else if(str1[0] == '-') {
        toAddNeg = true;
        ans = multiply(str1.erase(0, 1), str2);
    } else if(str2[0] == '-') {
        toAddNeg = true;
        ans = multiply(str1, str2.erase(0, 1));
    } else {
            if (str1_len == 0 || str2_len == 0)
                return "0";
            std::vector<int> result(str1_len + str2_len, 0);
            int i_n1 = 0;
            int i_n2 = 0;
            for (int i=str1_len-1; i>=0; i--) {
                int carry = 0;
                int n1 = str1[i] - '0';
                i_n2 = 0;
                for (int j=str2_len-1; j>=0; j--) {
                    int n2 = str2[j] - '0';
                    int sum = n1*n2 + result[i_n1 + i_n2] + carry;
                    carry = sum/10;
                    result[i_n1 + i_n2] = sum % 10;
                    i_n2++;
                }
                if (carry > 0)
                    result[i_n1 + i_n2] += carry;
                i_n1++;
            }
            int i = result.size() - 1;
            while (i>=0 && result[i] == 0)
                i--;
            if (i == -1)
                return "0";                    
            while (i >= 0)
                ans += std::to_string(result[i--]);
    } 
    if(toAddNeg && ans[0]!='0') {
        ans = '-' + ans;
    }
    return ans;
}


//
//        ______________________________________________________
//                        Division Function
//        ______________________________________________________
//                      Algorithm Explanation
//
//        The divisor increases iteratively till it reaches the Dividend. For fast reaching, a 
//        pre-determined limit is calculated depending upon the length difference of divisor
//        and divident=d, and power of 10 is calculated for length of answer precision. Further simple
//        addition is done till it reaches dividend.
//
//        If the divisior can be strored in primitive type of Int. :
//        As the dividend and result can be very large we store them in string. We first take 
//        digits which are divisible by number. After this take each digit and store result in string.
//        
//        Algorithmic Time Complexity : O(log(val. of divisor))  , if divisor can be stored as primitive type
//        Algorithmic Time Complexity : O((10^(len. diff.)) log(val. of divisor))
//        Algorithmic Space Complexity : O(log(n-m))
//        where n ans m are the lengths of respective strings(Integers) provided.
//

std::string bigint::divide(std::string str1, std::string str2) {                   // return arithmetic division of str1/str2
        std::string ans = "";
    if(str2 == "0") {
        return "0";
    } else if(str1 == str2) {
        return "1";
    } else if(str1[0] == '-' && str2[0] == '-') {
        ans = divide(str1.erase(0, 1), str2.erase(0, 1));
    } else if(str1[0] == '-') {
        std::string temp = divide(str1.erase(0, 1), str2);
        if(temp == "0")
            ans = temp;
        else
            ans = '-' + temp;        
    } else if(str2[0] == '-') {
        std::string temp = divide(str1, str2.erase(0, 1));
        if(temp == "0")
            ans = temp;
        else
            ans = '-' + temp; 
    } else { 
        if(str2 == "1")
            return str1;
        if(is_strictlyMaximum(str2, str1)) {
            return "0";
        }
        if(str2.length() <= 19) {
            std::stringstream strstrm(str2);
            unsigned long long int int_str2 = 0;
            strstrm >> int_str2;
            ans = shortDivide(str1, int_str2);
        }
        else {
            std::string temp = str2;
            ans = "0";
            std::string count = "0";
            while(str1 == maximum(str1, str2)) {
                int lenDiff = str1.length() - str2.length();
                if(lenDiff > 0 && str1[0] > str2[0]) {
                    count = add(count, pow("10", std::to_string(lenDiff)));
                    str1 = subtract(str1, multiply(str2, pow("10", std::to_string(lenDiff))));
                } else if(lenDiff > 0) {
                    count = add(count, pow("10", std::to_string(lenDiff-1)));
                    str1 = subtract(str1, multiply(str2, pow("10", std::to_string(lenDiff-1))));
                } else {
                    count = add(count, "1");
                    str1 = subtract(str1, str2);
                }
            }
            ans = count;
        }
    }
    return ans;
}

std::string bigint::shortDivide(std::string s1, unsigned long long int divisor) {     // return arithmetic division of str1/str2
    std::string ans;
    int idx = 0;
    long long int temp = s1[idx] - '0';
    
    while (temp < divisor) {
        temp = temp*10 + (s1[++idx] - '0');
        if(idx >= s1.length())
            break;
    }
    while (s1.length() > idx) {
        ans += (temp / divisor) + '0';
        temp = (temp % divisor)*10 + s1[++idx] - '0';
    }

    if (ans.length() == 0)
        return "0";

    return ans;
}

std::string bigint::mod(std::string str1, std::string str2) {                  // return arithmetic modulos of str1%str2
    std::string ans = subtract(str1, multiply(divide(str1, str2), str2));
    return ans;
}


std::string bigint::maximum(std::string str1, std::string str2) {              // return maximum of both strings.
    std::string max = "";
    bool bothNeg = false;
    bool isMax1 = false;
    bool isMax2 = false;
    if(str1[0] == '-' && str2[0] == '-') {
        bothNeg = true;
        str1.erase(0, 1);
        str2.erase(0, 1);
    } else if(str1[0] == '-') {
        return trim(str2);
    } else if(str2[0] == '-') {
        return trim(str1);
    }
    int str1_len = str1.length(), str2_len = str2.length();
    if(str1_len == str2_len) {
        for(int i = 0; i < str1_len; ++i) {
            if(str1[i] != str2[i]) {
                if(str1[i] > str2[i]) {
                    isMax1 = true;
                } else {
                    isMax2 = true;
                }
                break;
            }
        }
        if(!(isMax2 ^ isMax1)) {
            isMax1 = true;
        }
    } else if(str1_len > str2_len) {
        isMax1 = true;
    } else {
        isMax2 = true;
    }
    if(bothNeg) {
        if(isMax1)
            return ("-" + trim(str2));
        else 
            return ("-" + trim(str1));
    } else {
        if(isMax1)
            return trim(str1);
        else 
            return trim(str2);
    }
}

std::string bigint::minimum(std::string str1, std::string str2) {              // return minimum of both strings.
    std::string ans = maximum(str1, str2);
    if(ans == str1)
        return str2;
    return str1;
}

bool bigint::is_maximum(std::string str1, std::string str2) {             //checks if str1 >= str2, numerically
    if(str1 == maximum(str1, str2))
        return true;
    return false;
}

bool bigint::is_minimum(std::string str1, std::string str2) {             //checks if str1 <= str2, numerically
    if(str2 == maximum(str1, str2))
        return true;
    return false;
}

bool bigint::is_strictlyMaximum(std::string str1, std::string str2) {    //checks if str1 > str2, numerically
    if(str1 == str2)
        return false;
    if(str1 == maximum(str1, str2))
        return true;
    return false;
}

bool bigint::is_strictlyMinimum(std::string str1, std::string str2) {    //checks if str1 < str2, numerically
    if(str1 == str2)
        return false;
    if(str2 == maximum(str1, str2))
        return true;
    return false;
}

std::string bigint::trim(std::string s) {                         // function to remove zeros
    if(s == "0")
        return s;
    if(s[0] == '-') {
        int i = 1;
        while(s[i] == '0') {
            s.erase(i, 1);
        }
        return s;
    } else if(s[0] == '0') {
        int i = 0;
        while(s[i] == '0') {
            s.erase(i, 1);
        }
        return s;
    }
    return s;
}


//____________________________________________________________________________________________



std::string bigint::abs(std::string s) {                          // returns absolute value of string
    if(s[0] == '-')
        s.erase(0, 1);
    return s;
}


//
//        ______________________________________________________
//                        Power Function
//        ______________________________________________________
//                      Algorithm Explanation
//
//        It multiplies str1, str2 times and updates the str1 value
//        
//        Algorithmic Time Complexity : O(m), except multiplication time complexity
//        Algorithmic Space Complexity : O(1)
//        where n ans m are the lengths of respective strings(Integers) provided.
//

std::string bigint::pow(std::string str1, std::string str2) {                  // returns str1^str2, ^ -> power, numerically
    if(str2 == "0") {
        return "1";
    } else if(str1 == "0") {
        if(str2[0] == '-')
            return std::to_string((long long int)std::pow(0, -5));
        return "0";
    } else if(str1[0] == '-' && str2[0] == '-') {
        if(str1 == "-1" && str2 == "-1") {
            return "-1";
        } else if(str1 == "-1") {
            if((((int)str2[str2.length()-1])-48) & 1) {                
                return "-1";
            } else {
                return "1";
            }
        } else {
            return "0";
        }
    } else if(str1[0] == '-') {
        if((((int)str2[str2.length()-1])-48) & 1)
            return '-' + pow(str1.erase(0, 1), str2);
        return pow(str1.erase(0, 1), str2);
    } else if(str2[0] == '-') {
        if(str1 == "1") {
            return str1;
        } else {
            return "0";
        }
    } else {
        std::string init_str1 = str1;
        while(str2 != "1") {
            str1 = multiply(str1, init_str1);
            str2 = subtract(str2, "1");
        }
        return str1;
    }
}

//
//        ______________________________________________________
//                        Sqrt Function
//        ______________________________________________________
//                      Algorithm Explanation
//
//        Since sqrt of a string(s) has length floor(s/2), if s's length is even and 
//        ceil(s/2) if s's length is odd.
//        So it performs binary Search in that answer's range.
//        
//        Algorithmic Time Complexity : O(log(val. of s)), except divide time complexity
//        Algorithmic Space Complexity : O(s/2);
//

std::string bigint::sqrt(std::string s) {                 // returns sqrt(s), numerically
    if(s[0] == '-')
        return s;
    if(s == "0")
        return "0";
    unsigned long long int s_len = s.length();
    std::string ans;
    std::string mid = "";
    std::string high, low, square;
    unsigned long long int ans_len = s_len >> 1;
    if(s_len & 1) {
        low = pow("10", std::to_string(ans_len));
        high = pow("10", std::to_string(ans_len+1));
    } else {
        low = pow("10", std::to_string(ans_len-1));
        high = pow("10", std::to_string(ans_len));
    }
    std::string prev;
    while(1) {
        mid = divide(add(high, low), "2");
        square = multiply(mid, mid);
        if(prev == mid || (maximum(add(square, mid), s) == add(square, mid) && maximum(square, s) == s ) || high == low) {
            break;
        }
        if(maximum(square, s) == s) {
           low = mid;
        } else if(maximum(square, s) == square) {
             high = mid;
        }
        prev = mid;
    }
    ans = mid;
    return ans;
}



std::string bigint::log2(std::string s) {                 // returns log(s) to base of 2
    if(s == "0") {
        // throw new exception(std::out_of_range("log(0) is undefined"));
        return std::to_string(std::log2(0));
    }
    if(s[0] == '-') {
        // throw new exception(std::out_of_range("log(negative) is not allowed"));
        return std::to_string(std::log2(-1));
    }
    std::string logVal = "-1";
    while(s != "0") {
        logVal = add(logVal, "1");
        s = divide(s, "2");
    }
    return logVal;
}

std::string bigint::log10(std::string s) {                // returns log(s) to base of 10
    if(s == "0") {
        // throw new exception(std::out_of_range("log(0) is undefined"));
        return std::to_string(std::log2(0));
    }
    if(s[0] == '-') {
        // throw new exception(std::out_of_range("log(negative) is not allowed"));
        return std::to_string(std::log2(-1));
    }
    return std::to_string(s.length() - 1);
}

std::string bigint::logwithbase(std::string val, std::string base) {
    return divide(log2(val), log2(base));
}

std::string bigint::antilog2(std::string s) {
    return pow("2", s);
}

std::string bigint::antilog10(std::string s) {
    return pow("10", s);
}

void bigint::swap(std::string& str1, std::string& str2) {
    std::string s;
    s = str1;
    str1 = str2;
    str2 = s;
}

std::string bigint::reverse(std::string s) {          // reverses the string number, example: "7875" => "5787"
    bool fl = false;
    if(s[0] == '-') {
        s.erase(0, 1);
        fl = true;
    }
    unsigned long long int beg = 0, end = s.length() - 1;
    char ch;
    while(beg < end) {
        ch = s[beg];
        s[beg] = s[end];
        s[end] = ch;
        beg++;
        end--;
    }
    if(fl)
        s = '-' + s;
    return s;
}

//
//        ______________________________________________________
//                        gcd Function
//        ______________________________________________________
//                      Algorithm Explanation
//
//        It performs euclid method for finding greates common divisor
//        
//        Algorithmic Time Complexity : O(log(val. of str2)), except mod time complexity
//        Algorithmic Space Complexity : O(log(str2)) in stack;
//

std::string bigint::gcd(std::string str1, std::string str2) {
    if(is_strictlyMaximum(str2, str1))
        swap(str1, str2);
    std::string temp = "";
    while(is_strictlyMaximum(str2, "0")) {
        temp = mod(str1, str2);
        str1 = str2;
        str2 = temp;
    }
    return str1;
}


std::string bigint::lcm(std::string str1, std::string str2) {      // return lcm of both str1 and str2
    return divide(multiply(str1, str2), gcd(str1, str2));
}

std::string bigint::fact(std::string s) {                     // returns the factorial of string s, numerically
    if(s[0] == '-') {
        throw std::runtime_error("Factorial of Negative Integer is not defined.");
    }
    if(s == "0")
        return "1";
    std::string ans = "1";
    while(s != "0") {
        ans = multiply(ans, s);
        s = subtract(s, "1");
    }
    return ans;
}

bool bigint::isPalindrome(std::string s) {                  // checks if the Integer as string, s is Palindrome no. or not
    if(s[0] == '-')
        s.erase(0, 1);
    unsigned long long int beg = 0, end = s.length() - 1;
    while(beg < end) {
        if(s[beg] != s[end])
            return false;
        beg++;
        end--;
    }
    return true;
}

bool bigint::isPrime(std::string s) {                // checks if the String as Number is prime or not
    if(maximum(s, "2") != s)
        return false;
    std::string sqrt = bigint::sqrt(s);
    std::string i = "";
    for(i = "2"; is_maximum(sqrt, i); i = add(i, "1")) {
        if(mod(s, i) == "0")
            return false;
    }
    return true;
}


*/
