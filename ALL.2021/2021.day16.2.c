#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <unistd.h>

using namespace std;

struct bins_s {
	int x;
	string bin;
};
map<string, int> mp2;
map<int, string> mp;
#define getchar()
#define assert(asdf)
//struct bins_s bins = {0, "000", 1, "001", 2, "010", 3, "011", 4, "100", 5, "101", 6, "110", 7, "111" };
/*
   '0' = "0000"
   '1' = "0001"
   '2' = "0010"
   '3' = "0011"
   '4' = "0100"
   '5' = "0101"
   '6' = "0110"
   '7' = "0111"
   '8' = "1000"
   '9' = "1001"
   'A' = "1010"
   'B' = "1011"
   'C' = "1100"
   'D' = "1101"
   'E' = "1110"
   'F' = "1111"
   */
FILE *a;
void getitit(string bitS, int &subCounter);
#define LINE 2000
char bitLine[LINE*4];

int vvtot = 0;
string bitLineOrig;
int bitLineOrigPos = 0;
vector <long long> vec[2000];
int main(int argc, char **argv)
{
	mp[0] = "000"; mp[1] = "001"; mp[2] = "010"; mp[3] = "011";
	mp[4] = "100"; mp[5] = "101"; mp[6] = "110"; mp[7] = "111";

	mp2["000"] = 0; mp2["001"] = 1; mp2["010"] = 2; mp2["011"] = 3;
	mp2["100"] = 4; mp2["101"] = 5; mp2["110"] = 6; mp2["111"] = 7;
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	//mp4[0] = "0000";

	//mp4_4["0000"] = 0;
	a = fopen(argv[1], "r"); printf("		2021 Day16.2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	strcpy(bitLine, "");
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		printf("LINE: %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		for (int i = 0; i < (int)strlen(line1); i++) {
			switch(line1[i]) {
				case ('0'): strcat(bitLine, "0000"); break;
				case ('1'): strcat(bitLine, "0001"); break;
				case ('2'): strcat(bitLine, "0010"); break;
				case ('3'): strcat(bitLine, "0011"); break;
				case ('4'): strcat(bitLine, "0100"); break;
				case ('5'): strcat(bitLine, "0101"); break;
				case ('6'): strcat(bitLine, "0110"); break;
				case ('7'): strcat(bitLine, "0111"); break;
				case ('8'): strcat(bitLine, "1000"); break;
				case ('9'): strcat(bitLine, "1001"); break;
				case ('A'): strcat(bitLine, "1010"); break;
				case ('B'): strcat(bitLine, "1011"); break;
				case ('C'): strcat(bitLine, "1100"); break;
				case ('D'): strcat(bitLine, "1101"); break;
				case ('E'): strcat(bitLine, "1110"); break;
				case ('F'): strcat(bitLine, "1111"); break;
				default: perror("ERR"); exit(0);
			}
		}
		printf("%s\n", bitLine);

		string bitLineS = bitLine;
		bitLineOrig = bitLineS;
		bitLineOrigPos = 0;
		int blah = 0;
		getitit(bitLineS, blah);
		printf("ans???\n");
		for (auto var_int: vec[1]) {
			printf("%lld \n", var_int);
		}
		printf("\n");
		leny++;
	}
	fclose(a);

	//cout << "**vvtot " << vvtot << endl;
	assert(vec[1].size() == 1);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", vec[1][0]);
}
int ind = 0;
void getitit(string bitLineS, int &subCounter) {
	ind++;
	cout << "in getitit: " << bitLineS << endl;

	int found = 0;
	for (int zz = 0; zz < (int)bitLineS.length(); zz++) {
		if (bitLineS[zz] == '1') {
			found = 1; break;
		}
	}
	if (found == 0) {ind--; return;}

	string version = bitLineS.substr(0, 3);
	cout << "Version: " << mp2[version] << endl;
	vvtot += mp2[version];
	string type = bitLineS.substr(3, 3);
	cout << "Type: " << mp2[type] << endl;

	if (mp2[type] == 4) { //literal packet
		printf("found literal packet type is four\n");
		string literal = bitLineS.substr(6, bitLineS.length()-1);
		cout << "literal: " << literal << endl;
		int start = 0;
		if (literal.length() > 0) {
			string lit;
			while (1) {
				string onebit = literal.substr(start, 1);
				string fourbit = literal.substr(start+1, 4);
				lit += fourbit;	
				cout << "fourbit: " << fourbit << endl;

				if (onebit == "0") {break;}
				start += 5;

			}
			cout << "lit: " << lit << endl;
			cout << "litDec: " << strtol(lit.c_str(), NULL, 2) << endl;
			vec[ind].push_back(strtoll(lit.c_str(), NULL, 2));
			cout << "vvtot now : " << vvtot << endl;

			bitLineOrigPos += start+5;
			subCounter += start+5+6;
		} else {
			cout << "should not be here " << endl; exit(0);
			bitLineOrigPos += start;
			subCounter += start+6;
		}


	} else { //operator packet
		printf("found operator packet\n");
		int I = atoi(bitLineS.substr(6, 1).c_str());
		if (I == 0) {
			cout << "I : " << I  << " (len in bit) " << endl;
			int L = strtol(bitLineS.substr(7, 15).c_str(), NULL, 2);
			cout << "L: " << L << endl;
			string valL = bitLineS.substr(7+15, L);
			cout << "calling getit " << valL << endl; getchar();
			int blah;
			int Lorig = L;
			do {
				blah = 0;
				getitit(valL, blah);
				cout << "blah back is " << blah << endl;
				if (blah == 0) {printf("blah should not be zero\n"); exit(0); blah = Lorig; break;}
				valL = valL.substr(blah, valL.length()-1);
				L -= blah;
				cout << ind << ": **ind " << "L is " << L << endl; getchar();
				cout << ind << ": **ind " << "blah is " << blah << endl; getchar();
				cout << "valL is [" << valL << "]"<< endl;
				cout << "valL.length is <" << valL.length() << ">"<< endl;
			} while (valL.length() > 0);
			bitLineOrigPos += 7+15+Lorig;
			subCounter += 7+15+Lorig;
			//int val = strtol(bitLineS.substr(7+15, L).c_str(), NULL, 2);
		} else if (I == 1) {
			cout << "**I : " << I  << " (num subs) " << endl;
			int N = strtol(bitLineS.substr(7, 11).c_str(), NULL, 2);
			cout << "N: " << N << endl;
			int st = 18; // 3 + 3 + 1 + 11
			bitLineOrigPos += 18;
			//subCounter += 18;
			int subC = 18;
			for (int qq = 0; qq < N; qq++) {
				printf("**qq is %d of N:%d start: %d\n", qq, N, st);fflush(stdout);
				getitit(bitLineS.substr(st, bitLineS.length()-1), subC);
				cout << subC << " subCounter back " << endl;
				st = subC;
			}
			subCounter += subC;
		} else {
			perror("UNK"); exit(0);
		}

		printf("vec to which we apply maths\n");
		for (auto var_int: vec[ind+1]) {
			printf("%lld ", var_int);
		}printf("\n");
		switch(mp2[type]) {
			case 0: {

					long long ans = 0;
					for (auto var_int: vec[ind+1]) {
						ans+=var_int;
					}
					vec[ind].push_back(ans);
					break;
				}
			case 1: {
					long long ans = 1;
					for (auto var_int: vec[ind+1]) {
						ans*=var_int;
					}
					vec[ind].push_back(ans);
					break;
				}
			case 2: {
					long long ans = numeric_limits<long long>::max();

					//long long ans = 999999999;
					for (auto var_int: vec[ind+1]) {
						if (var_int < ans) {ans = var_int;}
					}
					vec[ind].push_back(ans);
					break;
				}
			case 3: {
					long long ans = 0;
					for (auto var_int: vec[ind+1]) {
						if (var_int > ans) {ans = var_int;}
					}
					vec[ind].push_back(ans);
					break;
				}
			case 4: {
					printf("no case 4..\n"); exit(0); break;
				}
			case 5: {
					long long ans;	
					assert((int)vec[ind+1].size() == 2);
					ans = (vec[ind+1][0] > vec[ind+1][1] ? 1  : 0);
					vec[ind].push_back(ans);
					break;
				}
			case 6: {
					long long ans;	
					assert((int)vec[ind+1].size() == 2);
					ans = (vec[ind+1][0] < vec[ind+1][1] ? 1  : 0);
					vec[ind].push_back(ans);
					break;
				}
			case 7: {
					long long ans;
					assert((int)vec[ind+1].size() == 2);
					ans = (vec[ind+1][0] == vec[ind+1][1] ? 1 : 0);
					vec[ind].push_back(ans);
					break;
				}
		}
		vec[ind+1].clear();
	}
	ind--;
}
