#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

int lenx, leny;

struct numbs {
	char var;
	int val;
};
struct innerinnerinstruction {
	char var;
	char cmd;
	int numb;
	char yes[10];
	char no[10];	
};

struct innerinstruction {
	char var;
	char cmd;
	int numb;
	char yes[10];
	char no[10];	
	struct innerinnerinstruction innerinner;	
};

struct instruction {
	char name[10];
	char var;
	char cmd;
	int numb;
	char yes[10];
	char no[10];	
	struct innerinstruction inner;	
};

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        map<string, struct instruction> mp;
        map<string, struct numbs> NUMBS;
        FILE * a = fopen(argv[1], "r"); printf("Day19part1\n"); fflush(stdin); fflush(stdout);

        char line1[1000];
        char instructs[1000];
printf("Entering loop...\n"); fflush(stdout);
	leny=0, lenx =0;
while (1)
{
//	printf("her1"); fflush(stdout);
	fgets(line1, 500, a);
	if (feof(a)) {printf("got eof\n"); break;}
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
/* EXAMPLES */
/*
R,           a>1636:R,A
hrx,         a<1434:cj,s>2727:sp,szk
R,           s>3521:A,a>997:R,A
tb,R
R,A
*/


//printf("%s\n", t.name);
//printf("%c\n", t.var);
//printf("%c\n", t.cmd);
//printf("%d\n", t.numb);
char rest1[30];
char rest2[30];
sscanf(rest, "%[^','],%s",rest1, rest2);
printf("%s: %s + %s\n", rest, rest1, rest2);


{
	int foundcomma = 0;
	for (int i = 0; i < (int)strlen(rest1); i++) 
	{
		if (rest1[i] == ',') {foundcomma = 1; break;}
	}
	if (foundcomma == 0) {strcpy(t.yes, rest1);}
	/* does not seem to be a split here for rest1 so no else */

	int foundcomma2 = 0;
	for (int i = 0; i < (int)strlen(rest2); i++) 
	{
		if (rest2[i] == ',') {foundcomma2 = 1; break;}
	}
	if (foundcomma2 == 0) {strcpy(t.no, rest2);} else {
		struct innerinstruction t2; char rest3[30]; struct innerinnerinstruction t3; 
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
			if (foundcomma4 == 0) {strcpy(t2.yes, rest4);}

			printf("%s\n", t2.yes);

			int foundcomma5 = 0;
			for (int i = 0; i < (int)strlen(rest5); i++) 
			{
				if (rest5[i] == ',') {foundcomma5 = 1; break;}
			}
			if (foundcomma5 == 0) {strcpy(t2.no, rest5);} else {
				sscanf(rest5, "%c%c%d%[^',']%s", &t3.var, &t3.cmd, &t3.numb, t3.yes, t3.no);
				//printf("REST5: %s: %c %c %d yes:%s no: %s\n", rest5, t3.var, t3.cmd, t3.numb, t3.yes, t3.no);
			}
		}
		t2.innerinner = t3;
		t.inner = t2;

       	 }
}
string name1 = t.name;
mp[name1] = t;
}

{
	// move to parse
	while (1)
	{
		printf("her31"); fflush(stdout);
		fgets(line1, 500, a);
		if (feof(a)) {printf("got eof\n"); exit(0);}
		printf("got %s\n", line1); fflush(stdout);
		if (line1[0] == '\n') {
			continue;
		}
		line1[(int)strlen(line1) -1] = '\0';
		lenx = strlen(line1);
		char var1; char var2; char var3; char var4;
		int val1; int val2; int val3; int val4;
		sscanf(line1, "{%c=%d,%c=%d,%c=%d,%c=%d}",  &var1, &val1, &var2,&val2,  &var3, &val3, &var4, &val4);
			//{x=2127,m=1623,a=2188,s=1013}
		printf("%c %d %c %d %c %d %c %d\n",  var1, val1, var2, val2,  var3, val3, var4, val4); getchar();
		struct numbs num1; num1.var = var1; num1.val = val1; 
		struct numbs num2; num2.var = var2; num2.val = val2; 
		struct numbs num3; num3.var = var3; num3.val = val3; 
		struct numbs num4; num4.var = var4; num4.val = val4; 

		string tmpY1; tmpY1.push_back(var1);
		string tmpY2; tmpY2.push_back(var2);
		string tmpY3; tmpY3.push_back(var3);
		string tmpY4; tmpY4.push_back(var4);
		NUMBS[tmpY1] = num1; NUMBS[tmpY2] = num2; NUMBS[tmpY3] = num3; NUMBS[tmpY4] = num4;

			
	{
		string startIN = "in";
		struct instruction Xt = mp.at("in");
		printf("CCCCCCC START CCCCCC %c\n", Xt.var); string numY; numY.push_back(Xt.var);
		//printf("CCCCCCC Xt.numb CCCCCC %d cmd %c\n", Xt.numb, Xt.cmd); fflush(stdout);
		char ans1[20];
		switch (Xt.cmd) {
			case '>':
				if (NUMBS.at(numY).val > Xt.numb) {printf("GREATER yes dir\n"); printf("NO:  %s\n", Xt.no ); strcpy(ans1, Xt.no);}
				if (NUMBS.at(numY).val < Xt.numb) {printf("LESS yes dir\n");    printf("YES: %s\n", Xt.yes); strcpy(ans1, Xt.yes);}
				break;
			case '<':
				if (NUMBS.at(numY).val < Xt.numb) {printf("LESS no dir\n");  	printf("NO:  %s\n", Xt.no ); strcpy(ans1, Xt.no);}
				if (NUMBS.at(numY).val > Xt.numb) {printf("GREATER yes dir\n"); printf("YES: %s\n", Xt.yes); strcpy(ans1, Xt.yes); }
				break;
			default:
				printf("ERR");
				break;
		}
		if (ans1[0] == 'R' || ans1[0] == 'A') {
			printf("END GAME STUFF %c", ans1[0]);
		} else {
			string ansString = ans1; struct instruction Xt2 = mp.at(ansString);
			printf("RUNNING var is %s %c\n", Xt2.name, Xt2.var);

{
		string numZ; numZ.push_back(Xt2.var);
		char ans2[20];
		switch (Xt2.cmd) {
			case '>':
				if (NUMBS.at(numZ).val > Xt2.numb) {printf("GREATER yes dir\n"); printf("NO:  %s\n", Xt2.no ); strcpy(ans2, Xt2.no);}
				if (NUMBS.at(numZ).val < Xt2.numb) {printf("LESS yes dir\n");    printf("YES: %s\n", Xt2.yes); strcpy(ans2, Xt2.yes);}
				break;
			case '<':
				if (NUMBS.at(numZ).val < Xt2.numb) {printf("LESS no dir\n");  	printf("NO:  %s\n", Xt2.no ); strcpy(ans2, Xt2.no);}
				if (NUMBS.at(numZ).val > Xt2.numb) {printf("GREATER yes dir\n"); printf("YES: %s\n", Xt2.yes); strcpy(ans2, Xt2.yes); }
				break;
			default:
				printf("ERR");
				break;
		}
		if (ans1[0] == 'R' || ans1[0] == 'A') {
		}
}
		
	}
	getchar();
	}
}
}
fclose(a);
}
