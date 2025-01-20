#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

int lenx, leny;
void processInstruction(string Xt);

struct numbs {
	char var;
	int val;
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
long tot = 0;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day19part1\n"); fflush(stdin); fflush(stdout);

        char line1[1000];

printf("Entering loop...\n"); fflush(stdout);
	leny=0, lenx =0;
int ANON = 0;
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

{
{
	// move to parse
	while (1)
	{
		printf("her31"); fflush(stdout);
		fgets(line1, 500, a);
		if (feof(a)) {printf("got eof\n"); break;}
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
		printf("%c %d %c %d %c %d %c %d\n",  var1, val1, var2, val2,  var3, val3, var4, val4); 
		struct numbs num1; num1.var = var1; num1.val = val1; 
		struct numbs num2; num2.var = var2; num2.val = val2; 
		struct numbs num3; num3.var = var3; num3.val = val3; 
		struct numbs num4; num4.var = var4; num4.val = val4; 

		string tmpY1; tmpY1.push_back(var1);
		string tmpY2; tmpY2.push_back(var2);
		string tmpY3; tmpY3.push_back(var3);
		string tmpY4; tmpY4.push_back(var4);
		NUMBS[tmpY1] = num1; NUMBS[tmpY2] = num2; NUMBS[tmpY3] = num3; NUMBS[tmpY4] = num4;

		string startIN = "in";
						//		struct instruction Xt = mp.at("in"); //////////////////		printf("CCCCCCC START CCCCCC %c\n", Xt.var);
printf("_____________START       VVVVVV---------------\n");
		processInstruction(startIN);
printf("_____________END       ^^^^^^^---------------\n");
			
		//getchar();
	}
	printf("************ tot: %ld\n", tot);
}
}
fclose(a);
}

	void processInstruction(string myInstName)
	{
		struct instruction Xt = mp.at(myInstName); string numY; numY.push_back(Xt.var);
		printf("BBBB Xt.numb CCCCCC %d %c %d\n", NUMBS.at(numY).val, Xt.cmd, Xt.numb); fflush(stdout);
		char ans1[8];
		switch (Xt.cmd) {
			case '>':
				if (NUMBS.at(numY).val > Xt.numb) {printf("GREATER yes dir\n"); printf("YES: %s\n", Xt.yes ); strcpy(ans1, Xt.yes);}
				else {printf("NO: next: [%s]\n", Xt.no); strcpy(ans1, Xt.no);}
				break;
			case '<':
				if (NUMBS.at(numY).val < Xt.numb) {printf("LESS yes dir\n");  	printf("YES:  %s\n", Xt.yes ); strcpy(ans1, Xt.yes);}
				else {printf("NO..: next: [%s]\n", Xt.no); strcpy(ans1, Xt.no); }
				break;
			default:
				printf("ERR");
				break;
		}

		if (ans1[0] == 'R' || ans1[0] == 'A') {
			if (ans1[0] == 'A') {
				printf("ANSWER AAAAAAAAAAAAAAA\n");
				string xxx = "x";
				string mmm = "m";
				string aaa = "a";
				string sss = "s";
				tot += NUMBS[xxx].val + NUMBS[mmm].val + NUMBS[aaa].val + NUMBS[sss].val;
			} else if (ans1[0] == 'R') {
				printf("ANSWER RRRRRRRRRRRRRr\n");
			}
			printf("END GAME STUFF %c", ans1[0]);
		} else {
			string ansString = ans1; printf("NEXT INSTRUCTION: %s\n", ans1);
			processInstruction(ans1);

/*
 struct instruction Xt2 = mp.at(ansString);
			printf("RUNNING var is %s %c\n", Xt2.name, Xt2.var);

			{
				string nextIN = ans1;
				processInstruction(nextIN);
			}
*/
		}
		
	}

