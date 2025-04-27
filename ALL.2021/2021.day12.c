#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

map <string, vector <string>> mp;
void traverse(string st, string en, string called, map<string, int> al);
map <string, int> al;
int count = 0;
int first = 1;
map <string, int> call;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2021 Day 12.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
// XW-ed
int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	char one[20], two[20];
	sscanf(line1, "%[^-]-%[^\0]", one, two);
	string oneS = one; string twoS = two;
	cout << oneS << " " << twoS << endl;
	mp[oneS].push_back(twoS);
	mp[twoS].push_back(oneS);
	
	leny++;

}
fclose(a);

	for (auto itm = mp.begin(); itm!=mp.end(); itm++) {
		cout << "mapFirst: " << itm->first << endl;
		for (auto itv = itm->second.begin(); itv != itm->second.end(); itv++) {
			cout << *itv << " " ;
		}
		cout << endl;
	}

	//al["start"] = 1; al["end"] = 1;
	traverse("start", "end", "start", al);
	cout << "call 1 size: " << call.size() << endl;
	for (auto it = call.begin(); it != call.end(); it++) {
		cout << it->first << endl;
	}
/*
	getchar();
	al.clear();
	printf("calling again...\n");
	first = 1;
	traverse("start", "end", "start");
	cout << "call 2 size: " << call.size() << endl;
	for (auto it = call.begin(); it != call.end(); it++) {
		cout << it->first << endl;
	}
	getchar();
	first = 1;
	al.clear();
	traverse("start", "end", "start");
	cout << "call 3 size: " << call.size() << endl;;
	for (auto it = call.begin(); it != call.end(); it++) {
		cout << it->first << endl;
	}
	getchar();
*/
/*
	for (auto itm = mp.begin(); itm!=mp.end(); itm++) {
		if (itm->first == "start") {
			for (auto itv = itm->second.begin(); itv != itm->second.end(); itv++) {
				cout << *itv << " " ;
			}
			cout << endl;
		}
	}
*/
	printf("FIN ** count %d\n", count);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);
}
int ind = 0;
void traverse(string st, string en, string called, map<string, int> al) {
	ind++;
	vector <string> ve = mp[st];
	if (st == "start" && first == 1) {
		//cout << "in trav " << st << " -> " << en << " (" << ve.size() << ") " << endl;
		first = 0;
	} else if (st == "start" && first == 0) {
		ind--;
		return;
	}

	cout << "in trav " << st << " -> " << en << " (" << ve.size() << ") " << endl;
	
	if (st == "end") {
		cout << "end: " << ind << " -- " << called << endl;
		if (call.find(called) == call.end()) {
			cout << "END: " << called << endl;
			call[called] = 1;
			count++;
		} else {
			//al.clear(); 
		}
		ind--;
		return;
	}
	if (al.find(st) != al.end()) {
		printf("already.%s..\n", st.c_str());
		ind--;
		return;
	} else {
		string tmpSt = st;
		for (int i = 0; i < (int)tmpSt.length(); i++) {
			tmpSt[i] = tolower(st[i]);
		}
		if (tmpSt == st) {
			al[st] = 1;
		}

	}
	for (auto itv = ve.begin(); itv != ve.end(); itv++) {
		//if (*itv == en) {cout << "foundEnd\n"; getchar(); continue;}
		traverse(*itv, en, called + " " + *itv, al);	
/*
		cout << "now trying " << *itv << endl;
		if (called + " " + *itv == "start A b") {
			printf("removing b\n"); getchar();
			al.erase("b");
		}
*/
/*
		string cal2 = called + " " + *itv;
		char cal[200];
		strcpy(cal, cal2.c_str());
		char *fir = strtok(cal, " \0");
		
		do {
			cout << " fir is " << fir << endl;
		 	al.erase(fir);
			getchar();
		} while ((fir = strtok(NULL, " \0")) != NULL);
*/

//		if (ind == 1) {
//			al.clear();
//		}
	}
	ind--;
}
