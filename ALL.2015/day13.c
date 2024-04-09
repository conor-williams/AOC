#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <algorithm>
#include <string>

using namespace std;
int arr[10][10];
map <string, int> mp;
int lenx, leny;
#define DAY "2015 day13 part1\n"
#define _DEBUG_

int tot = 0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
       
        char line1[200];
	char prevMname[20];
	int peopleCounter = 0;
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	line1[strlen(line1) -1] = '\0'; //the dot
	char mName[20] = ""; char gainlose[20]; int points; char sName[20];
	strcpy(prevMname, mName);	
	sscanf(line1, "%s would %s %d happiness units by sitting next to %s",
		mName, gainlose, &points, sName);
	string mN = mName;
	map <string, int>::iterator it1;
	int mVal;
	if ((it1 = mp.find(mN)) == mp.end()) {
		mp.insert({mN, peopleCounter});
		mVal = peopleCounter;
		peopleCounter++;
	} else {
		mVal = it1->second;
	}

	string sN = sName;
	map <string, int>:: iterator it2;
	int sVal;
	if ((it2 = mp.find(sN)) == mp.end()) {
		mp.insert({sN, peopleCounter});
		sVal = peopleCounter;
		peopleCounter++;
	} else {
		sVal = it2->second;
	}
	if (strcmp(gainlose, "lose") == 0) {
		points -= 2*points;
	}
	arr[mVal][sVal] = points;
	leny++;
}
fclose(a);
	//mp.insert({"Con", peopleConter});	
	int con = peopleCounter;
	peopleCounter++;
	for (int i = 0; i < peopleCounter-1; i++) {
		arr[con][i] = 0;
		arr[i][con] = 0;
	}

	int sA[100];

	for (int i = 0; i < peopleCounter; i++) {
		sA[i] = i;
	}

	sort(sA, sA+peopleCounter);

	int maxSum = 0;
	do {
		int mySum = 0;	
		for (int i = 0; i < peopleCounter-1; i++) {
			mySum += arr[sA[i]][sA[i+1]];
			mySum += arr[sA[i+1]][sA[i]];
			
		}
		mySum += arr[sA[0]][sA[peopleCounter-1]];
		mySum += arr[sA[peopleCounter-1]][sA[0]];

		if (mySum > maxSum) {maxSum = mySum;}
		
	} while (next_permutation(sA, sA+peopleCounter));
	printf("***maxSum %d\n", maxSum); fflush(stdout);
}
