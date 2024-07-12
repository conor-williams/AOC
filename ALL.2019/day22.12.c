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
#include<bits/stdc++.h>

using ll=long long int;
using namespace std;

using namespace std;
struct BigInt {
    string a;
    int sign;

    BigInt(){}
    void operator = (string b) {
        a= (b[0]=='-' ? b.substr(1) : b);
        reverse(a.begin(), a.end());
        (*this).Remove0(b[0]=='-' ? -1 : 1);
    }
    BigInt(string x) {(*this)=x;}
    BigInt(ll x) {(*this)=to_string(x);}
    void operator = (ll x){*this=to_string(x);}

    char operator[](int i){return a[i];}
    int size() {return a.size();}
    BigInt inverseSign() {sign*=-1; return (*this);}

    BigInt Remove0(int newSign) {
        sign = newSign;
        for(int i=a.size()-1; i>0 && a[i]=='0'; i--) a.pop_back();
        if(a.size()==1 && a[0]=='0') sign=1;
        return (*this);
    }

    bool operator == (BigInt x) {return sign==x.sign && a==x.a;}
    bool operator == (string x) {return *this==BigInt(x);}
    bool operator == (ll x)     {return *this==BigInt(x);}
    bool operator != (BigInt x) {return !(*this==x);}
    bool operator != (string x) {return !(*this==x);}
    bool operator != (ll x)     {return !(*this==x);}

    bool operator < (BigInt b) {
        if (sign!=b.sign) return sign<b.sign;
        if(a.size()!=b.size()) return a.size()*sign<b.size()*sign;
        for(int i=a.size()-1; i>=0; i--)
            if(a[i] != b[i]) return a[i]<b[i];
        return false;
    }
    bool operator <  (string x) {return *this<BigInt(x);}
    bool operator <  (ll x)     {return *this<BigInt(x);}
    bool operator <= (BigInt b) {return *this==b || *this<b;}
    bool operator <= (string b) {return *this==b || *this<b;}
    bool operator <= (ll b)     {return *this==b || *this<b;}
    bool operator >  (BigInt b) {return !(*this==b || *this<b);}
    bool operator >  (string x) {return !(*this==x || *this<x);}
    bool operator >  (ll b)     {return !(*this==b || *this<b);}
    bool operator >= (BigInt b) {return *this==b || *this>b;}
    bool operator >= (string b) {return *this==b || *this>b;}
    bool operator >= (ll b)     {return *this==b || *this>b;}

    BigInt operator + (BigInt b) {
        if(sign != b.sign) return (*this)-b.inverseSign();
        BigInt sum;
        for(int i=0, carry=0; i<a.size() || i<b.size() || carry; i++){
            if (i<a.size()) carry+=a[i]-'0';
            if (i<b.size()) carry+=b[i]-'0';
            sum.a += (carry % 10 + 48);
            carry /= 10;
        }
        return sum.Remove0(sign);
    }
    BigInt operator +  (string x) {return *this+BigInt(x);}
    BigInt operator +  (ll x)     {return *this+BigInt(x);}
    BigInt operator ++ (int) {*this+=1; return *this-1;}
    BigInt operator ++ ()    {*this+=1; return *this;}
      void operator += (BigInt x) {*this = *this+x;}
      void operator += (string x) {*this = *this+x;}
      void operator += (ll x)     {*this = *this+x;}


    BigInt operator - ( BigInt b ) {
        if(sign != b.sign) return (*this)+b.inverseSign();
        if(*this < b) return (b - *this).inverseSign();
        BigInt sub;
        for(int i=0,borrow=0; i<a.size(); i++) {
            borrow = a[i]-borrow-(i<b.size() ? b.a[i] : '0');
            sub.a += borrow>=0 ? borrow+'0' : borrow + 58;
            borrow = borrow>=0 ? 0:1;
        }
        return sub.Remove0(sign);
    }
    BigInt operator - (string x) {return *this-BigInt(x);}
    BigInt operator - (ll x)     {return *this-BigInt(x);}
    BigInt operator -- (int) {*this-=1; return *this+1;}
    BigInt operator -- ()    {*this-=1; return *this;}
      void operator -= (BigInt x) {*this = *this-x;}
      void operator -= (string x) {*this = *this-x;}
      void operator -= (ll x)     {*this = *this-x;}

    BigInt operator * (BigInt b) {
        BigInt mult("0");
        for(int i=0, k=a[i]; i<a.size(); i++, k=a[i]) {
            while(k-- -'0') mult=mult+b;
            b.a.insert(b.a.begin(),'0');
        }
        return mult.Remove0(sign * b.sign);
    }
    BigInt operator * (string x) {return *this*BigInt(x);}
    BigInt operator * (ll x)     {return *this*BigInt(x);}
      void operator *= (BigInt x) {*this = *this*x;}
      void operator *= (string x) {*this = *this*x;}
      void operator *= (ll x)     {*this = *this*x;}

    BigInt operator / (BigInt b) {
        if(b.size()==1 && b[0]=='0') b.a[0]/=(b[0]-'0');
        BigInt c("0"), d;
        for(int j=0; j<a.size(); j++) d.a += "0";
        int dSign = sign*b.sign; b.sign=1;
        for(int i=a.size()-1; i>=0; i--) {
            c.a.insert(c.a.begin(),'0');
            c=c+a.substr(i,1);
            while(!(c<b)) c=c-b, d.a[i]++;
        }
        return d.Remove0(dSign);
    }
    BigInt operator / (string x) {return *this/BigInt(x);}
    BigInt operator / (ll x)     {return *this/BigInt(x);}
      void operator /= (BigInt x) {*this = *this/x;}
      void operator /= (string x) {*this = *this/x;}
      void operator /= (ll x)     {*this = *this/x;}

    BigInt operator % (BigInt b) {
        if( b.size()==1 && b[0]=='0') b.a[0]/=(b[0]-'0') ;
        BigInt c("0");
        int cSign = sign*b.sign; b.sign=1;
        for( int i=a.size()-1; i>=0; i-- ) {
            c.a.insert( c.a.begin(),'0');
            c = c+a.substr(i,1);
            while(!(c<b)) c=c-b;
        }
        return c.Remove0(cSign);
    }
    BigInt operator % (string x) {return *this%BigInt(x);}
    BigInt operator % (ll x)     {return *this%BigInt(x);}
      void operator %= (BigInt x) {*this = *this%x;}
      void operator %= (string x) {*this = *this%x;}
      void operator %= (ll x)     {*this = *this%x;}

    void print() {
        if(sign==-1) putchar('-');
        for(int i=a.size()-1; i>=0; i--) putchar(a[i]);
    }
    friend istream& operator >>(istream &in,BigInt &x){
        string s; in>>s; x=s; return in;
    }
    friend ostream& operator <<(ostream &out,BigInt &x){
        if(x.sign==-1) putchar('-');
        for(int i=x.size()-1; i>=0; i--)
            putchar(x[i]);
        return out;
    }

    friend BigInt pow(BigInt base, BigInt pw){
        BigInt ans=1;
        while(pw!=0){
            if(pw%2 !=0) ans*=base;
            base*=base, pw/=2;
        }
        return ans;
    }
    friend BigInt pow(BigInt a, BigInt b,BigInt mod) {
        if (b==0) return BigInt(1);
        BigInt tmp=pow(a,b/2,mod);
        if ((b%2)==0) return (tmp*tmp)%mod;
        else return (((tmp*tmp)%mod)*a)%mod;
    }
    friend BigInt sqrt(BigInt x) {
        BigInt ans=x,tmp=(x+1)/2;
        while (tmp<ans) ans=tmp, tmp=(tmp+x/tmp)/2;
        return ans;
    }
    friend BigInt gcd(BigInt a,BigInt b){
        return a%b==0 ? b : gcd(b, a%b);
    }
    friend BigInt lcm(BigInt a,BigInt b){
        return a/gcd(a,b);
    }
};

int lenx, leny;
#define DAY "2019 day22 part2\n"
#undef _DEBUG_
#define LINE 200
BigInt ENDL("119315717514047");
//#define ENDL (BigInt)10007
BigInt pow2(BigInt x, BigInt y, BigInt z);

struct inst_s {
	int type; //1 = deal // 2 = cut //3 = incdeal
	int val;
};
int instTOT;
struct inst_s inst[100];

void runFOR2();
BigInt inv(BigInt va);
BigInt offset("0");
BigInt increment("1");

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
	offset *= pow((BigInt)1-increment,  ENDL-2, ENDL);  
	increment = (BigInt)pow(increment, 101741582076661 , ENDL);
        cout << "offset: " << offset << endl;;
	cout << "increment here is " << increment << endl;
       
	offset = BigInt("9154372642351086312809932254992713119267173353156446105615019182820382134356462930461220784270155999170896135475940207950810416752775720572575989941759795455046599650023839598425626661890904410084372091846841253142015667486504551414085355300171785955635652016714380463457031996543862638122972721477653145580927457490087019444973879345173604613549836383397751385784600151044056443657018606378415702682228417945261899551786034361342324300299465303769084248739702844376873078906883773638187204951142585639390025985662824358393797563792116032455221547447453058879034794735679820251797884147231528759922006");
        increment = BigInt("23886232355104");
	printf("here here here\n");
	BigInt inc2020 = increment * BigInt("2020");
	BigInt oneMinus = BigInt("1") - increment;
	BigInt tenE = BigInt("100") * ENDL;
	BigInt ans2 =  (((inc2020 + (oneMinus *offset)) % ENDL) + tenE) % ENDL;
//	BigInt ans2 =  (((((BigInt) (((BigInt)2020 * increment) + ((BigInt)1-increment) *offset))) % ENDL) + (BigInt)10*ENDL) %ENDL;

	assert(ans2 < ENDL);
	printf("\n\nCONOR: ans2->  ");
	cout << ans2 << endl;
/*
	runFOR2();
	offset *= pow2(1-increment,  ENDL-2, ENDL);  
	increment = (BigInt)pow2(increment, 101741582076661, ENDL);
	BigInt ans2 =  ((((BigInt) ((2020 * increment) + ((1-increment) *offset) )) % ENDL) + 2*ENDL) %ENDL;

	assert(ans2 < ENDL);
	printf("\n\nCONOR: ans2->  ");
	cout << ans2 << endl;
*/

}
/*

BigInt pow2(BigInt x, BigInt y, BigInt z)
{
 
    BigInt res = 1;
    BigInt x1 = x;

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
*/
/*
BigInt inv(BigInt x) {
    BigInt res = 1;     // Initialize result 
 
    BigInt x1 = (BigInt)x;
    BigInt y = ENDL -2;
    BigInt p = ENDL;
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
				BigInt tm = pow(inst[i].val,  ENDL-2, ENDL);  
				//BigInt tm = inv(inst[i].val);
				increment *= tm;
				cout << increment << endl;
				break;
				}

		}

	}
}
/*
int main(){
    BigInt a,b,n,ans,M=1000000007;
    cin>>a>>b>>n;
    ans=pow(a,b,n);
    cout<<ans<<endl;
}
*/
