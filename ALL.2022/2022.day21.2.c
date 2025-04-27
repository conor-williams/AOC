#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <map>
#include <iostream>

using namespace std;
map <string, pair <string, int>> mp;
map <string, pair <string, int>> mpOrig;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

struct inst_s {
	char s1[20];
	char s2[10000];
	char s3[10000];
	char op;
	long long num1;
};
struct inst_s inst[2000];

string doCalc(string ch);
long long hasOp(string ch);
long long alldigitsAndOp(string ch); 
long long alldigits(string ch); 

char restRootOrig1[20];
char restRootOrig2[20];
int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day 21 part2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	long long leny = 0;
	//long long instr = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		//char s1[20], s2[20], s3[20];
		char rest[100];
		//char rest2[120];
		//long long ret;//, num1;
			      //ret = sscanf(line1, "%s: %s %c %s", inst[leny].s1, inst[leny].s2, inst[leny].op, inst[leny].s3);
		/*ret = */sscanf(line1, "%[^:]:%[^\0]", inst[leny].s1, rest);
		//printf("ret is %lld\n", ret);
		//sprintf(rest2, "( %s)", rest); //string re = rest2; //if (strcmp(inst[leny].s1, "root") == 0) {first = leny;}

		mp[inst[leny].s1] = make_pair(rest, 0);
		if (strcmp(inst[leny].s1, "root") == 0) {
			sscanf(rest, "%s + %s", restRootOrig1, restRootOrig2);
		}
		//assert(ret == 2);
		leny++;
	}
	fclose(a);

	mpOrig = mp;
	string newString;
	printf("%s === %s\n", restRootOrig1, restRootOrig2);
	//for (int iii = 0; iii < 400; iii++) 
	//unsigned long long upper = 400; pow(2, 14);
	unsigned long long upper = /*400; */pow(10, 13);
	unsigned long long lower = 0; //pow(10, 6);
	int five = 0;
	while (1) {
		printf("in while at start...\n");
		unsigned long long iii;
		if (upper-lower <= 5) {
			iii = lower+five;
			five++;
		} else {
			iii = lower+((upper - lower) /2);
		}
		mp = mpOrig;
		char tmpS[30];
		sprintf(tmpS, "%llu", iii);
		mp["humn"].first = tmpS;
		//mp["humn"] = "3296135418821";
		//mp["humn"] = "5"; //iii;
		printf("iii: %llu\n", iii); fflush(stdout);
again:
		for (auto it = mp.begin(); it != mp.end(); it++) {
			//cout << "checking: " << it->second << endl;
			//printf("%lld %lld %lld\n", alldigitsAndOp(it->second), hasOp(it->second), alldigits(it->second));

			if (it->second.second == 0 && alldigitsAndOp(it->second.first) == 1 && hasOp(it->second.first)) {
				//printf("calling doCalc\n");
				if ((it->second.first = doCalc(it->second.first)) == "-99") {printf("bad %llu %llu\n", lower, upper); lower+=100; goto nextiii;}
			} else if (it->second.second == 0 && alldigits(it->second.first)) {
				//printf("alldigits...\n");
				for (auto it2 = mp.begin(); it2 != mp.end(); it2++) {
					long long ind = 0;
					if ((ind = it2->second.first.find(it->first)) != -1 ) {
						it2->second.first.replace(ind, 4, it->second.first);
						it->second.second = 1;
						break;
						//printf("doing a replace...\n");
					}
				}
			}
		}
		if (alldigits(mp["root"].first)) { 
			//	cout << "not going again" << endl;
			unsigned long long one = strtoull(mp[restRootOrig1].first.c_str(), 0, 10);
			unsigned long long two = strtoull(mp[restRootOrig2].first.c_str(), 0, 10);
			printf("here1... one V two %llu V %llu\n", one, two);
		
			if (mp[restRootOrig1] == mp[restRootOrig2]) {
				fflush(stdout); dup2(fd, 1);
				cout << "**ans: " << iii << endl;
				exit(0);
			} else if (one < two) {
				printf("one LT %llu V %llu\n", one, two);
				//printf("humn shouting %d not a match... mp[root]: %s\n", iii, mp["root"].c_str());
				printf("upper lower %llu V %llu\n", upper, lower);
				if (five == 0) {
					upper = iii;
				}
			} else if (one > two) {
				printf("two LT %llu V %llu\n", one, two);
				if (five == 0) {
					lower = iii;
				}
				printf("upper lower %llu V %llu\n", upper, lower);
			}
			printf("after %llu V %llu\n", one, two);
			printf("aft %llu V %llu\n", upper, lower);

			getchar();
			printf("goto...\n");
			
			goto nextiii;
			///cout << "**ans: " << mp["root"] << endl; ///getchar();
		} else {
			//cout << "interim ans: " << mp["root"] << endl;
			//printf("again...\n");
			goto again;
		}
nextiii:
		continue;
	}

}
string doCalc(string ch) {
	char blah[100];
	strcpy(blah, ch.c_str());
	long long num1, num2; char op;

	long long ret = sscanf(blah, "%lld %c %lld", &num1, &op, &num2);
	if (ret != 3) {
		return "-99";
		//printf("err:%s\n", blah); exit(0);
	}
	long long ans = 0;
	switch (op) {
		case '+':
			ans = num1 + num2;
			break;
		case '-':
			ans = num1 - num2;
			break;
		case '*':
			ans = num1 * num2;
			break;
		case '/':
			ans = num1 / num2;
			break;
	}
	//printf("tmp)ans is %lld\n", ans);
	char anS[100];
	sprintf(anS, "%lld", ans);
	string an = anS;
	return an;
}

long long hasOp(string ch) 
{
	long long found = 0;
	for (long long i = 0; i < (long long)ch.length(); i++) {
		if (ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/') {
			found = 1;
			break;
		}
	}
	return found;
}



long long alldigitsAndOp(string ch) 
{
	long long found = 1;
	for (long long i = 0; i < (long long)ch.length(); i++) {

		if (ch[i] == ' ' || (ch[i]>='0' && ch[i] <= '9') || ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/') {
			//ok
		} else {
			found = 0;
			break;
		}
	}
	return found;
}

long long alldigits(string ch) 
{
	long long found = 1;
	for (long long i = 0; i < (long long)ch.length(); i++) {
		if (ch[i] == ' ' || ch[i] == '-' || (ch[i] >= '0' && ch[i] <= '9')) {
			//ok
		} else {
			found = 0;
			break;
		}
	}
	return found;
}
