#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2015 day9 part1\n"
#define _DEBUG_

int tot = 0;
map <pair<string, string>, int> both;
map <string, int> just;

char cities[100][50];
vector <int> citiesI;
int numCities = 0;

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[200];
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	char from[50]; char to[50]; int dist;
	sscanf(line1, "%s to %s = %d", from, to, &dist);
	string fromS = from;
	string toS = to;

	printf("dist %d\n", dist);
	both.insert({{fromS, toS}, dist});	
	both.insert({{toS, fromS}, dist});	
	if (just.find(fromS) == just.end()) {
		just.insert({fromS, dist});
	}
	if (just.find(toS) == just.end()) {
		just.insert({toS, dist});
	}
	
	int found1 = 0;
	for (int j = 0; j < numCities; j++) {
		if (strcmp(cities[j], from) == 0) {
			found1 = 1; break;
		}
	}
	if (found1 == 0) {
		strcpy(cities[numCities], from); numCities++;
	}

	int found = 0;
	for (int j = 0; j < numCities; j++) {
		if (strcmp(cities[j], to) == 0) {
			found = 1; break;
		}
	}
	if (found == 0) {
		strcpy(cities[numCities], to); numCities++;
	}
	leny++;
}
fclose(a);

	for (int k = 0; k < numCities; k++) {
		citiesI.push_back(k);
	}

	sort(citiesI.begin(), citiesI.end());
	int min = 999999;
	do {
		for (int i = 0; i < numCities; i++) {
			printf("%s ", cities[citiesI[i]]);
		}
		int itot = 0;
		for (int i = 0; i < numCities-1; i++) {
			string city1 = cities[citiesI[i]];
			string city2 = cities[citiesI[i+1]];
			int citydist = 0;
			printf("%d ", citydist = both[{city1, city2}] );
			itot += citydist;
			
		}
		printf("tot: %d \n", itot);
		if (itot < min) {min = itot;}
		
	} while (next_permutation(citiesI.begin(), citiesI.end()));

	fflush(stdout); dup2(fd, 1);
	printf("***citydistmin %d\n", min); fflush(stdout);
}
