#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
struct mymap {
    long to;
    long from;
    long range;
};
struct mymap stos[400];
struct mymap stof[400];
struct mymap ftow[400];
struct mymap wtol[400];
struct mymap ltot[400];
struct mymap ttoh[400];
struct mymap htol[400];

struct mymap *pmap[7];
void main(int argc, char **argv)
{
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
        printf("Day5.1\n");
        fflush(stdin); fflush(stdout);
        char line1[1000];
        int linenum = 0;

int poswithin = 0;
        fgets(line1, 1000, a); //seeds
        fgets(line1, 1000, a); //blank
int mymappos = -1;
//POPULATE... Great...
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
	    sscanf(line1, "%d %d %d",
		&pmap[mymappos][poswithin].to,
		&pmap[mymappos][poswithin].from,
		&pmap[mymappos][poswithin].range);
	    printf("got: %ld %ld %ld\n", pmap[mymappos][poswithin].to, pmap[mymappos][poswithin].from, pmap[mymappos][poswithin].range);
	    poswithin++;
        }
printf("RAND: %ld\n", pmap[6][3].range);

long NUM;
long NUMinput[] = {2880930400, 17599561, 549922357, 200746426, 1378552684, 43534336, 155057073, 56546377, 824205101, 378503603, 1678376802, 130912435, 2685513694, 137778160, 2492361384, 188575752, 3139914842, 1092214826, 2989476473, 58874625, 0};
//long NUMinput[] = {79, 14, 55, 13, 0};
        //TRACE 2880930400
        //.from -> .to
        //.to becomes .from for next etc...
	//long NUM = 2880930400;
int m = 0;
long NUMsmallest = 0;
        
    for (m = 0; NUMinput[m] != 0; m++) {
        NUM = NUMinput[m];
if (m == 0) {NUMsmallest = NUM;}
	for (int k = 0; k < 7; k++) {
	    int l=0;
            while (1) {
		if (pmap[k][l].to == 0 && pmap[k][l].from == 0 &&
		    pmap[k][l].range == 0) { break;}
		if (pmap[k][l].from <= NUM) {
	printf("LESS\n");
		     if (pmap[k][l].from + pmap[k][l].range >= NUM) {
			NUM = NUM - pmap[k][l].from + pmap[k][l].to;
			break;
		     }
		} else {printf("greatet...");}
                l++;
	    }
	}
	printf("Location[%d]: %ld\n", m, NUM);
        
        if (NUMsmallest > NUM) {NUMsmallest = NUM;}
    }
//find smallest
	printf("Last Location: %ld\n", NUM);
	printf("Location Smallest: %ld\n", NUMsmallest);
        fflush(stdin); fflush(stdout);
        fclose(a);
//printf("*** Score:  %d ****\n", score);
printf("%d", linenum);
}

