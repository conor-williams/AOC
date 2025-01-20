#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>

using namespace std;

#include <unistd.h>

map <unsigned long long, unsigned long long> mp[10];
unsigned long long getLocation(unsigned long long in);
unsigned long long lookup(unsigned long long in, int mppos);

#define getchar()
int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
struct mymap {
	unsigned long long from;
	unsigned long long to;
	unsigned long long range;
};
struct mymap stos[400];
struct mymap stof[400];
struct mymap ftow[400];
struct mymap wtol[400];
struct mymap ltot[400];
struct mymap ttoh[400];
struct mymap htol[400];

struct mymap *pmap[7];
int pmapNum[10];
int main(int argc, char **argv)
{
	printf("SLOW ~15 mins\n");
	printf("%d", argc);
	printf("%s", argv[1]);
	fflush(stdin); fflush(stdout);
	pmap[0] = stos;
	pmap[1] = stof;
	pmap[2] = ftow;
	pmap[3] = wtol;
	pmap[4] = ltot;
	pmap[5] = ttoh;
	pmap[6] = htol;

	FILE * a = fopen(argv[1], "r");
	printf("2023 Day5.2\n");
	fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	int linenum = 0;

	int poswithin = 0;
	fgets(line1, 1000, a); //seeds
	char seeds123[1000];
	line1[(int)strlen(line1)-1] = '\0';
	strcpy(seeds123, line1);
	fgets(line1, 1000, a); //blank
	int mymappos = -1;
	//POPULATE... Great...
	memset(pmapNum, 0, sizeof(pmapNum));
	while (1) {
		fgets(line1, 1000, a);
		if (strlen(line1) == 1) {fgets(line1, 1000, a);}
		if (strstr(line1, "map")) {
			fgets(line1, 1000, a); mymappos++; poswithin=0;
		}
		printf("%s", line1);
		if (feof(a)) break;
		linenum++;
		pmap[mymappos][poswithin].to = 0;
		pmap[mymappos][poswithin].from = 0;
		pmap[mymappos][poswithin].range = 0;
		sscanf(line1, "%llu %llu %llu",
				&pmap[mymappos][poswithin].to,
				&pmap[mymappos][poswithin].from,
				&pmap[mymappos][poswithin].range);
		//printf("got: %llu %llu %llu\n", pmap[mymappos][poswithin].to, pmap[mymappos][poswithin].from, pmap[mymappos][poswithin].range);
		pmapNum[mymappos]++;
		poswithin++;
	}


	char * fir = strtok(seeds123, ":");
	fir = strtok(NULL, ":");
	char nuIn[1000];
	strcpy(nuIn, fir);
	char *ne = strtok(nuIn, " \0");
	int pos123 = 0;
	unsigned long long NUMinput[50];
	unsigned long long NUMrange[50];
	do {
		char *bla;
		if (pos123 % 2 == 0) {
			NUMinput[pos123/2] = strtoull(ne, &bla, 10);
		} else {
			NUMrange[pos123/2] = strtoull(ne, &bla, 10);
		}
		pos123++;
	} while ((ne = strtok(NULL, " \0")) != NULL);
	NUMinput[(pos123/2)] = 0;
	NUMrange[(pos123/2)] = 0;

	int m = 0;
	////////////

	unsigned long long NUMsmall = 99999999999999;
	unsigned long long NUM = 0;;
	for (m = 0; NUMinput[m] != 0; m++) {
		printf("m is %d\n", m);
		for (unsigned long long kkk = 0; kkk < NUMrange[m]; kkk++) {
			NUM = NUMinput[m]+kkk;
			unsigned long long retNUM1 = getLocation(NUM);
			if (retNUM1 < NUMsmall) {NUMsmall = retNUM1;}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", NUMsmall);
}
unsigned long long getLocation(unsigned long long in) {
	unsigned long long tmp1 = lookup(in, 0);
	unsigned long long tmp2 = lookup(tmp1, 1);
	unsigned long long tmp3 = lookup(tmp2, 2);
	unsigned long long tmp4 = lookup(tmp3, 3);
	unsigned long long tmp5 = lookup(tmp4, 4);
	unsigned long long tmp6 = lookup(tmp5, 5);
	unsigned long long tmp7 = lookup(tmp6, 6);
	return tmp7;
}
unsigned long long lookup(unsigned long long in, int mppos) {
	for (int i = 0; i < pmapNum[mppos]; i++) {
		if (in >= pmap[mppos][i].from  && in <= pmap[mppos][i].from+pmap[mppos][i].range) {
			return pmap[mppos][i].to + in - pmap[mppos][i].from;
		} else {
			continue;
		}
	}
	return in;
}
