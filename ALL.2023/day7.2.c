#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct acard {
    char card[6];
    int bid ;
};

struct acard single[1000];
int possingle = 0;
struct acard onepair[1000];
int posonepair = 0;
struct acard twopair[1000];
int postwopair = 0;
struct acard threeofakind[1000];
int posthreeofakind = 0;
struct acard fullhouse[1000];
int posfullhouse = 0;
struct acard fourofakind[1000];
int posfourofakind = 0;
struct acard fiveofakind[1000];
int posfiveofakind = 0;
int posmap[7];
struct acard *cmap[7];
char whatsin[17];

void main(int argc, char **argv)
{
        printf("%d", argc);
        printf("%s", argv[1]);
        fflush(stdin); fflush(stdout);
	cmap[0] = single;
	cmap[1] = onepair;
	cmap[2] = twopair;
	cmap[3] = threeofakind;
	cmap[4] = fullhouse;
	cmap[5] = fourofakind;
	cmap[6] = fiveofakind;

        FILE * a = fopen(argv[1], "r"); printf("Day7.1\n"); fflush(stdin); fflush(stdout);

        char line1[1000];
        int done = 1;
        while (1) {
            int TYPE = 0; int POS = 0; done = 1;
            for (int i = 0; i<17; i++) {whatsin[i] = 0;}
            fgets(line1, 1000, a); if (feof(a)) {break;}
	    char cards[20] = ""; int bid = 0;
	    sscanf(line1, "%s %d", cards, &bid);
	    printf("GOT cards: %s bid: %d\n", cards, bid);
            for (int k = 0; k <= 4; k++) {
	      switch(cards[k]) {
		case 'a': whatsin[1]++;
			break;
		case 'b': whatsin[2]++;
			break;
		case 'c': whatsin[3]++;
			break;
		case 'd': whatsin[4]++;
			break;
		case 'e': whatsin[5]++;
			break;
		case 'f': whatsin[6]++;
			break;
		case 'g': whatsin[7]++;
			break;
		case 'h': whatsin[8]++;
			break;
		case 'i': whatsin[9]++;
			break;
		case 'j': whatsin[10]++;
			break;
		case 'l': whatsin[12]++;
			break;
		case 'm': whatsin[13]++;
			break;
		case 'n': whatsin[14]++;
			break;
              }
           }
/* k = J = WILD */
/* find out which group it is in */
/* take the k/11/Jack and hand it to the highest...*/


//day 7.2
int valhighest = 0;
int indexhigh = 0;
for (int m = 14; m >= 1; m--) {
    if (m != 1) {if (whatsin[m] > valhighest) {indexhigh = m;}}
} 
if (whatsin[1] > 0) {whatsin[indexhigh] += whatsin[1]; whatsin[1] =0;}
// end day 7.2



	   for (int j = 1; j<=14; j++) {
                int found1 = 0;
		if (whatsin[j] == 5) {
printf("GOT FIVE of a KIND\n"); fflush(stdout);
		   TYPE = 6; POS = posmap[TYPE]; posmap[TYPE]++;
		   break;
		} else if (whatsin[j] == 4) {
printf("got FOUR OF A KIND\n");
/*if (j != 12 && whatsin[12] = 1) {TYPE=6; POS=posmap[TYPE]; posmap[TYPE]++; break;}*/
		   TYPE = 5; POS = posmap[TYPE]; posmap[TYPE]++;

		   break;
		} else if (whatsin[j] == 3) {
/*if (j!=12 && whatsin[12] > 0)*/ 
	            for (int k = 1; k<=14; k++) {
			if (whatsin[k] == 2) {
printf("GOT FULL HOUSE\n"); fflush(stdout);
                            TYPE = 4; POS = posmap[TYPE]; posmap[TYPE]++; found1 = 1;
			    break;
			}
		    }
		    if (found1 == 0) {
printf("GOT THREE OF A KIND\n"); fflush(stdout);
                       TYPE = 3; POS = posmap[TYPE]; posmap[TYPE]++;
		       break;
		    }
                }
           }

if (TYPE == 0) {
	   int found2 = 0;
           for (int j = 1; j <=14; j++) {
		if (whatsin[j] == 2) {
	            for (int k = j+1; k<=14; k++) {
			if (whatsin[k] == 2) {
                            TYPE = 2; POS = posmap[TYPE]; posmap[TYPE]++; found2 = 1;
			    break;
			}
		    }
		    if (found2 == 0) {
                        TYPE = 1; POS = posmap[TYPE]; posmap[TYPE]++;
			found2 = 1;
			break;
		    }
		 }
           }
}

if (TYPE == 0) {TYPE = 0; POS = posmap[TYPE]; posmap[TYPE]++;} 
           /* copy over the bid (& unnecessary cards)*/
           strcpy(cmap[TYPE][POS].card, cards);
	   cmap[TYPE][POS].bid = bid;
      }

//DEBUG
      for (int i = 0; i <= 6; i++) {
          printf("POS[%d]: %d\n", i, posmap[i]);
      }

      fclose(a);
      int tot = 0;
      int totalpos= 0;
      int pos = 1;
      for (int k = 0; k <= 6; k++ ) {
          for (int i = 0; i < posmap[k]; i++) {
//DEBUG
		printf("card: %5s bid: %5d pos: %4d\n", cmap[k][i].card, cmap[k][i].bid, pos);
		tot += pos * cmap[k][i].bid; pos++;}
      }
      printf("****TOT:***** %d\n", tot);
	
}

