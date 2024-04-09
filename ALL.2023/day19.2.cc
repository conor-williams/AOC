#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

int lenx, leny;
int processInstruction(string Xt);
void BubbleSort(int a[], int array_size);

struct numbs {
	char var;
	int val;
};
struct asdf {
	int val;
	int dif;
	char eq;
};

struct instruction {
	char name[10];
	char var;
	char cmd;
	int numb;
	char yes[10];
	char no[10];	
};
map<string, struct instruction> mp;
map<string, struct numbs> NUMBS;
unsigned long long tot = 0;
unsigned long long tot2 = 0;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * aF = fopen(argv[1], "r"); printf("Day19part2\n"); fflush(stdin); fflush(stdout);

        char line1[1000];

printf("Entering loop...\n"); fflush(stdout);
	leny=0, lenx =0;
int ANON = 0;
while (1)
{
//	printf("her1"); fflush(stdout);
	fgets(line1, 500, aF);
	if (feof(aF)) {printf("got eof\n"); break;}
//	printf("got %s\n", line1); fflush(stdout);
	if (line1[0] == '\n') {
		printf("ready to move...\n");
		break;
	}
        line1[(int)strlen(line1) -1] = '\0';
	lenx = strlen(line1);
	for (int i = 0; i<lenx; i++) {
		if (line1[i] == '}') {line1[i] = '}';}
		else if (line1[i] == '{') {line1[i] = ' ';}}
	
        leny++;
	struct instruction t;
	char rest[30];
	sscanf(line1, "%s %c%c%d:%[^'}'] ",t.name, &t.var, &t.cmd, &t.numb, rest);

printf("%s\n", t.name);
printf("%c\n", t.var);
printf("%c\n", t.cmd);
printf("%d\n", t.numb);
char rest1[30];
char rest2[30];
sscanf(rest, "%[^','],%s",rest1, rest2);
printf("%s: %s + %s\n", rest, rest1, rest2);
//printf("getchar.."); getchar();

{
	int foundcomma = 0;
	for (int i = 0; i < (int)strlen(rest1); i++) 
	{
		if (rest1[i] == ',') {foundcomma = 1; break;}
	}
	if (foundcomma == 0) {strcpy(t.yes, rest1);} else {printf("ERROR1\n"); getchar();}
	/* does not seem to be a split here for rest1 so no else */

	int foundcomma2 = 0;
	for (int i = 0; i < (int)strlen(rest2); i++) 
	{
		if (rest2[i] == ',') {foundcomma2 = 1; break;}
	}

	printf("rest2: %s\n", rest2);
	if (foundcomma2 == 0) {strcpy(t.no, rest2);} else {
		struct instruction t2; char rest3[30]; 
		sscanf(rest2, "%c%c%d:%s", &t2.var, &t2.cmd, &t2.numb, rest3);
		printf("%s\n",rest3);

		char rest4[30];
		char rest5[30];
		sscanf(rest3, "%[^','],%s",rest4, rest5);
		printf("%s: %s + %s\n", rest3, rest4, rest5);
		{
			int foundcomma4 = 0;
			for (int i = 0; i < (int)strlen(rest4); i++) 
			{
				if (rest4[i] == ',') {foundcomma4 = 1; break;}
			}
			if (foundcomma4 == 0) {strcpy(t2.yes, rest4);} else {printf("ERROR2\n"); getchar();}

			printf("%s\n", t2.yes);

			int foundcomma5 = 0;
			for (int i = 0; i < (int)strlen(rest5); i++) 
			{
				if (rest5[i] == ',') {foundcomma5 = 1; break;}
			}
			printf("rest5: %s\n", rest5); 
			if (foundcomma5 == 0) {strcpy(t2.no, rest5);} else {
				struct instruction t3; 
				sscanf(rest5, "%c%c%d:%[^','],%s", &t3.var, &t3.cmd, &t3.numb, t3.yes, t3.no);
				//printf("REST5: %s: %c %c %d yes:%s no: %s\n", rest5, t3.var, t3.cmd, t3.numb, t3.yes, t3.no);
				{
					char tmpname3[5]; sprintf(tmpname3, "X%d", ANON); ANON++;
					printf("HERE HERE HERE all the 33333****%s\n", tmpname3);
					printf("WATCH HERE HERE all the jUST %s YES NO****%s - %s\n", rest5, t3.yes, t3.no); 
					strcpy(t3.name, tmpname3); string name3 = t3.name; strcpy(t2.no, tmpname3);
					mp[name3] = t3;	
				}
			}
		}

		char tmpname2[5]; sprintf(tmpname2, "Y%d", ANON); ANON++;
		strcpy(t2.name, tmpname2); string name2 = t2.name; strcpy(t.no, t2.name);
		printf("HERE HERE HERE all the 222222****%s\n", tmpname2);
		mp[name2] = t2; 
		
       	 }
}
string name1 = t.name; mp[name1] = t;
}
printf("finished populating mp\n"); 
fclose(aF);
{
	struct asdf myasdf[4][10000];
	char X[4]; X[0] = 'x'; X[1] = 'm'; X[2] = 'a'; X[3] = 's';
	int myArrPos[4] = {0};
	for (int z=0; z<4; z++) {
		myasdf[z][0].val = 1; 
		myasdf[z][0].eq = '>';
		myArrPos[z] = 1;
	}
//conor
{
        aF = fopen(argv[1], "r"); 
        char line1[1000];

	while (1)
	{
		fgets(line1, 999, aF);
		if (feof(aF)) {printf("got eof\n"); break;}
		if (line1[0] == '\n') {
			printf("ready to move...\n");
			break;
		}
		line1[(int)strlen(line1) -1] = '\0';
		lenx = strlen(line1);
		for (int i = 0; i<lenx; i++) {
			     if (line1[i] == '{') {line1[i] = ',';}
			else if (line1[i] == '}') {line1[i] = ':';}}

		char line1Orig[1000];
		strcpy(line1Orig, line1);
		for (int i = 0; i < 4; i++) {
			strcpy(line1, line1Orig);
			printf("line1 is %s\n", line1); 
			for (int j=0; j<(int)strlen(line1); j++) {
				int ch=0;
				if (line1[j] == ',') {ch=1; int k=0; for (;k < (int)strlen(line1)-j; k++) {line1[k] = line1[j+k];} j=0; line1[k] = '\0'; printf("line1: %s\n", line1); }
				if (ch==1) {
					char tmps1[1000];
					char ss1[1000] = ""; strcat(ss1, ","); ss1[1] =  X[i]; ss1[2] = '<'; ss1[3] = '\0'; strcat(ss1, "%[^:]:");
		                	int rv = sscanf(line1, ss1, tmps1);
					printf("rv is %d\n", rv);
					if (rv == 1) {
//myasdf[i][myArrPos[i]].val = atoi(tmps1)-1; myArrPos[i]++;
myasdf[i][myArrPos[i]].val = atoi(tmps1); myasdf[i][myArrPos[i]].eq = '<'; myArrPos[i]++;
//myasdf[i][myArrPos[i]].val = atoi(tmps1)+1; myArrPos[i]++;

}
					char ss2[1000] = ""; strcat(ss2, ","); ss2[1] =  X[i]; ss2[2] = '>'; ss2[3] = '\0'; strcat(ss2, "%[^:]:");
					char tmps2[1000];
		                	int rv2 = sscanf(line1, ss2, tmps2);
					printf("rv2 is %d\n", rv2);
					if (rv2 == 1) {
//myasdf[i][myArrPos[i]].val = atoi(tmps2)-1; myArrPos[i]++;
//myasdf[i][myArrPos[i]].val = atoi(tmps2); myasdf[i][myArrPos[i]].eq = '>'; myArrPos[i]++;
myasdf[i][myArrPos[i]].val = atoi(tmps2)+1; myasdf[i][myArrPos[i]].eq = '>'; myArrPos[i]++;
//myasdf[i][myArrPos[i]].val = atoi(tmps2)+1; myArrPos[i]++;

}
				}
			}
		}
	}
	fclose(aF);

	for (int l = 0; l < 4; l++) {
	    	int i, j, temp;
		char tempEq;
	    	for (i = 0; i < (myArrPos[l] - 1); ++i)
	    	{
			for (j = 0; j < myArrPos[l] - 1 - i; ++j )
			{
		    		if (myasdf[l][j].val > myasdf[l][j+1].val)
		    		{
					temp = myasdf[l][j+1].val;
					tempEq = myasdf[l][j+1].eq;
					myasdf[l][j+1].val = myasdf[l][j].val;
					myasdf[l][j+1].eq = myasdf[l][j].eq;
					myasdf[l][j].val = temp;
					myasdf[l][j].eq = tempEq;
		    		}
			}
	    	}
	}	
	for (int l = 0; l < 4; l++) {
		myasdf[l][myArrPos[l]].val = 4001;
		myasdf[l][myArrPos[l]].eq = '<';
		myArrPos[l]++;
	}
	for (int l = 0; l < 4; l++) {
		for (int m = 0; m < myArrPos[l]-1; m++) {
			if (myasdf[l][m].val == myasdf[l][m+1].val && myasdf[l][m].eq == myasdf[l][m+1].eq) {
				for (int z = m; z < myArrPos[l]-1; z++) {
					myasdf[l][z].val = myasdf[l][z+1].val;
					myasdf[l][z].eq = myasdf[l][z+1].eq;
				}
				myArrPos[l]--;
			}
		}
		printf("\n");
	}

	for (int l = 0; l < 4; l++) {
		for (int k = 0; k < myArrPos[l]-1; k++) {
			myasdf[l][k].dif = myasdf[l][k+1].val - myasdf[l][k].val;
		}
	}

	for (int l = 0; l < 4; l++) {
		printf("%c: ", X[l]);
		for (int m = 0; m < myArrPos[l]; m++) {
			printf("%d:%c:[%d] ", myasdf[l][m].val, myasdf[l][m].eq, myasdf[l][m].dif);
		}
		printf("\n");
	}


}
tot = 0;
tot2 = 0;
unsigned long long tot3 = (unsigned long long)4000*4000*4000*4000;
{
	// move to parse
	string tmpY1 = "x"; string tmpY2 = "m"; string tmpY3 = "a"; string tmpY4 = "s";
	struct numbs num1; num1.var = 'x'; struct numbs num2; num2.var = 'm'; struct numbs num3; num3.var = 'a'; struct numbs num4; num4.var = 's'; 
printf("%d %d %d %d\n", myArrPos[0], myArrPos[1], myArrPos[2], myArrPos[3]);
	string startIN = "in";
	for (int x = 0; x < myArrPos[0]-1; x++) {
		if (myasdf[0][x].dif == 0) {continue;}
		printf("[%dof%d] x.val is [%d]: [%d](dif)\n", x, myArrPos[0], myasdf[0][x].val, myasdf[0][x].dif); fflush(stdout);
  		for (int m = 0; m < myArrPos[1]-1; m++) {
			if (myasdf[1][m].dif == 0) {continue;}
			printf("[%dof%d] x.val:[%d] m.val is [%d]: [%d](dif)\n", m, myArrPos[1], myasdf[0][x].val, myasdf[0][m].val, myasdf[0][m].dif); fflush(stdout);
			for (int a = 0; a < myArrPos[2]-1; a++) {
				if (myasdf[2][a].dif == 0) {continue;}
				for (int s = 0; s < myArrPos[3]-1; s++) {
					if (myasdf[3][s].dif == 0) {continue;}
					num1.val = myasdf[0][x].val; num2.val = myasdf[1][m].val; num3.val = myasdf[2][a].val; num4.val = myasdf[3][s].val; 

					NUMBS[tmpY1] = num1; NUMBS[tmpY2] = num2; NUMBS[tmpY3] = num3; NUMBS[tmpY4] = num4;

					int retval = processInstruction(startIN);
					if (retval != 0) {
						tot += (unsigned long long) myasdf[0][x].dif * myasdf[1][m].dif * myasdf[2][a].dif * myasdf[3][s].dif;
					}
					tot2 += (unsigned long long) myasdf[0][x].dif * myasdf[1][m].dif * myasdf[2][a].dif * myasdf[3][s].dif;
					//printf("%d *%d *%d *%d * retval: %d\n", myasdf[0][x].dif , myasdf[1][m].dif , myasdf[2][a].dif , myasdf[3][s].dif,  retval);
				}
			}
		}
	}
					printf("tot3: %llu\n", tot3);
					printf("tot2: %llu\n", tot2);
	printf("************ tot: %llu\n", tot);
}
}
}

void BubbleSort(int a[], int array_size)
{
    int i, j, temp;
    for (i = 0; i < (array_size - 1); ++i)
    {
        for (j = 0; j < array_size - 1 - i; ++j )
        {
            if (a[j] > a[j+1])
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
}

int processInstruction(string myInstName)
{
	struct instruction Xt = mp.at(myInstName); 
	string numY; numY.push_back(Xt.var);
	char ans1[8];
	switch (Xt.cmd) {
		case '>':
			if (NUMBS.at(numY).val > Xt.numb) {strcpy(ans1, Xt.yes);}
			else {strcpy(ans1, Xt.no);}
			break;
		case '<':
			if (NUMBS.at(numY).val < Xt.numb) {strcpy(ans1, Xt.yes);}
			else {strcpy(ans1, Xt.no); }
			break;
	}

	if (ans1[0] == 'R' || ans1[0] == 'A') {
		if (ans1[0] == 'A') {
			//tot++;
			return 1;
		} 
	} else {
		string ansString = ans1; 
		int ret = processInstruction(ans1);
		return ret;

	}
	return 0;
}

