#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <algorithm>
#include<bits/stdc++.h>

#define getchar()
using namespace std;
string doMul(string num1, string num2);

FILE *a;
long long tot = 0;
struct monkey {
	unsigned long long int mNum;
	deque <string> items;
	char op;
	long long int val;
	unsigned long long int divNum;
	unsigned long long int f;
	unsigned long long int t;
	unsigned long long int numItems;
	};
struct monkey monkeys[20];
unsigned long long int numMonkeys = 0;
string doSum(string a, string b);
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        a = fopen(argv[1], "r"); printf("2022 Day11 part1\n"); fflush(stdout);
        char line1[1000];

unsigned long long int leny = 0;
unsigned long long int lineNum = 0;
while (1) {
next:
        fgets(line1, 999, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	//line1[strlen(line1)-1] = '\0';	
	
	unsigned long long int mNum; char ops[20]; unsigned long long int divNum; unsigned long long int m1; unsigned long long int m2; char starts[50];

	if (line1[0] == '\n') {printf("lineNum@ %llu\n", lineNum); goto next;}

	if (lineNum == 0) {sscanf(line1, "Monkey %llu:", &mNum);
		numMonkeys++;
		monkeys[mNum].numItems = 0;
		monkeys[mNum].mNum = mNum;}
	else if (lineNum == 1) {sscanf(line1, "  Starting items: %[^\n]", starts);
		char *first = strtok(starts, ", ");
		do {
			string fir = first;
			monkeys[mNum].items.push_back(fir);
		} while ((first = strtok(NULL, ", ")) != NULL); }
	else if (lineNum == 2) {sscanf(line1, "  Operation: new = old %[^\n]", ops);
		monkeys[mNum].op = ops[0];
		char ops2[20];
		int i;
		for (i = 2; i < (int)strlen(ops); i++) {
			ops2[i-2] = ops[i];
			
		}
		ops2[i-2] = '\0';
		printf("ops2 is [%s]\n", ops2);
		if (strcmp(ops2, "old") == 0) {monkeys[mNum].val = -1;} else {monkeys[mNum].val = atoi(ops2);}}
	else if (lineNum == 3) {sscanf(line1, "  Test: divisible by %llu", &divNum);
		monkeys[mNum].divNum = divNum;}
	else if (lineNum == 4) {sscanf(line1, "    If true: throw to monkey %llu", &m1);
		monkeys[mNum].t = m1;}
	else if (lineNum == 5) {sscanf(line1, "    If false: throw to monkey %llu", &m2);
		monkeys[mNum].f = m2;}
	lineNum++;
	lineNum = lineNum % 6;

	
	if (lineNum == 0) {
		printf("--------------------------\n");
		printf("%llu: %llu %llu %llu\n", mNum, divNum, m1, m2);}
	if (lineNum == 0) {
		printf("items: ");
		for (auto iter = monkeys[mNum].items.begin(); iter != monkeys[mNum].items.end(); iter++) {
			printf("%s ", iter->c_str());
		}
		printf("\n");
		printf("op: %c\n", monkeys[mNum].op);
		printf("val: %lld\n", monkeys[mNum].val);
	}
/*
Monkey 0:
  Starting items: 79, 98
  Operation: new = old * 19
  Test: divisible by 23
    If true: throw to monkey 2
    If false: throw to monkey 3
*/


	leny++;
}
fclose(a);

printf("numMonkeys is %llu\n", numMonkeys); getchar();

	for (unsigned long long int t = 0; t < 10000; t++) {
		for (unsigned long long int m = 0; m < numMonkeys; m++) {
			unsigned long long int end = monkeys[m].items.size();
			for (unsigned long long int k = 0; k < end; k++) {
				monkeys[m].numItems++;
				string v  =  monkeys[m].items.front();	
				monkeys[m].items.pop_front();
				string v1;
				if (monkeys[m].val == -1) {v1 = v;} else {v1 = to_string(monkeys[m].val);}
				string ans;
				switch (monkeys[m].op) {
					case('+'): ans = doSum(v, v1);
						break;
					case('*'): ans = doMul(v, v1);
						break;
					default:
						printf("ERROR"); exit(0);
				}
				//printf("ans is %s\n", ans.c_str());
				//ans /= 3;
				int res = 0;

				//num contains the large number stored as a string
				for (int j = 0; j < (int)ans.length(); j++) {
					    res = (res*10 + (int)ans[j] - '0') % monkeys[m].divNum; 
    				}


				//unsigned long long int ans2 = ans % monkeys[m].divNum;						
	
				if (res == 0) {
					monkeys[monkeys[m].t].items.push_back(ans);
				} else {
					monkeys[monkeys[m].f].items.push_back(ans);
				}
			}
		}
		int t1 = t+1;
		if ( t1 == 1 || t1== 20 || t1== 999|| t1==1000 || t1 == 2000 || t1==3000 || t1==4000 || t1==5000 
			|| t1 == 6000|| t1==7000 || t1 == 8000 || t1== 9000 || t1==10000) {
			printf("t1 is %d\n", t1);
			unsigned long long int numItems[numMonkeys+1];
			for (unsigned long long int i = 0; i < numMonkeys; i++) {
				numItems[i] = monkeys[i].numItems;
			}
			for (unsigned long long int i = 0; i < numMonkeys; i++) {
				printf("%llu: %llu\n", i, numItems[i]);
			} getchar();
		}
	}
	unsigned long long int numItems[numMonkeys+1];
	for (unsigned long long int i = 0; i < numMonkeys; i++) {
		numItems[i] = monkeys[i].numItems;
	}
	sort(numItems, numItems+numMonkeys);
	printf("****mul %llu * %llu = %llu\n", numItems[numMonkeys-1], numItems[numMonkeys-2], numItems[numMonkeys-1]*
			numItems[numMonkeys-2]);
	for (unsigned long long int i = 0; i < numMonkeys; i++) {
		printf("%llu: %llu\n", i, numItems[i]);
	}
}

string doSum(string a, string b)
{
    if(a.size() < b.size())
        swap(a, b);

    int j = a.size()-1;
    for(int i=b.size()-1; i>=0; i--, j--)
        a[j]+=(b[i]-'0');

    for(int i=a.size()-1; i>0; i--)
    {
        if(a[i] > '9')
        {
            int d = a[i]-'0';
            a[i-1] = ((a[i-1]-'0') + d/10) + '0';
            a[i] = (d%10)+'0';
        }
    }
    if(a[0] > '9')
    {
        string k;
        k+=a[0];
        a[0] = ((a[0]-'0')%10)+'0';
        k[0] = ((k[0]-'0')/10)+'0';
        a = k+a;
    }
    return a;
}

string doMul(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";
 
    // will keep the result number in vector
    // in reverse order
    vector<int> result(len1 + len2, 0);
 
    // Below two indexes are used to find positions
    // in result. 
    int i_n1 = 0; 
    int i_n2 = 0; 
     
    // Go from right to left in num1
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
 
        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0; 
         
        // Go from right to left in num2             
        for (int j=len2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';
 
            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position. 
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
 
            // Carry for next iteration
            carry = sum/10;
 
            // Store result
            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        }
 
        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
 
        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
 
    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
 
    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
    return "0";
 
    // generate the result string
    string s = "";
     
    while (i >= 0)
        s += std::to_string(result[i--]);
 
    return s;
}
