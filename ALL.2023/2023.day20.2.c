#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
#include <numeric> 
#include <unistd.h>

using namespace std;
int CURPOS;
int lenx, leny;
struct invstateStr {
	char currentinput[100];
	int signalin = 0;
	int state = 0;
};


int QnumMAX;
struct reg {
	char name[50];
	int type;
	int state = 0;
	int signalin = 0;
	char next[50];
	char currentinput[100];
	int numouts = 0;
	char outs[100][30];
	int numins = 0;
	char input[100][30];
	int firsttime = 1;
	struct invstateStr invstate[750];
	int invstatepos = 0;
};
map<string, struct reg> mp;
map<string, struct reg> mpQ0;
map<string, struct reg> mpQ1;
map<string, struct reg> mpQ2;
map<string, struct reg> INV2saved;

int HIGH = 0; int LOW = 0;	
int SIGNALIN = 0;
long tot = 0;
void reverseit();
void processNEXT(int qnum, char *nextInst, map<string, struct reg> *mpQX);
char Qmain[3][1000];
void addtoQ(int qnum, char *next);
void removeoffQ(int qnum);

vector <unsigned long long> nums;
unsigned long long gcd(unsigned long long a, unsigned long long b);
unsigned long long lcm(std::vector<unsigned long long> numbers);

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

unsigned long long lcm(vector<unsigned long long> numbers)
{
	return accumulate(numbers.begin(), numbers.end(), (unsigned long long)1,
			[](unsigned long long x, unsigned long long y) { return (unsigned long long)(x * y) / gcd(x, y); });
}
int fd;
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("		2023 Day20 part2\n"); 
	printf("	SLOW ~13seconds\n"); fflush(stdout);
	fd = dup(1); close(1);
	char line1[1000];

	printf("Entering loop...\n"); fflush(stdout);
	leny=0, lenx =0;
	while (1)
	{
		printf("-------vvv-------------\n");
		//	printf("her1"); fflush(stdout);
		fgets(line1, 500, a);
		if (feof(a)) {printf("got eof\n"); break;}
		printf("got %s\n", line1); fflush(stdout);
		if (line1[0] == '\n') {
			printf("ready to move...\n");
			break;
		}
		//        line1[(int)strlen(line1) -1] = '\0';

		char line2[100]; int len1 = strlen(line1); int ind2 = 0;
		for (int i = 0; i < len1; i++) {
			if (line1[i] == ' ') {
			} else if (i == 0 && line1[0] == '&') {
				line2[0] = 'I';
				ind2++;
			} else if (i == 0 && line1[0] == '%') {
				line2[0] = 'R';
				ind2++;
			} else {
				line2[ind2] = line1[i];
				ind2++;
			}
		}
		line2[ind2] = '\0'; 
		//printf("LINE2: %s\n", line2);
		strcpy(line1, line2);
		line1[strlen(line1)-1] = '\0';
		lenx = strlen(line1); leny++;


		if (line1[0] == 'R' ) {
			char allTOregs[900]; char regFROMname[50];
			sscanf(line1, "R%[^-]->%s", regFROMname, allTOregs);
			printf("FROM REG: %s (toregs: %s)\n", regFROMname, allTOregs);
			{
				struct reg regtmp; strcpy(regtmp.name, regFROMname); regtmp.type = 0; regtmp.state = 0; strcpy(regtmp.next, allTOregs);
				strcat(regtmp.next, ",");

				char *ret = strtok(allTOregs, "\n,");
				while (ret != NULL) {
					printf(" REG REG TO: %s\n", ret);
					strcpy(regtmp.outs[regtmp.numouts], ret);
					regtmp.numouts++;
					ret = strtok(NULL, "\n,");	
				}
				string nm = regFROMname; mp[nm] = regtmp;
			}
		} else if (line1[0] == 'I') { /*inverters start with ampersand */
			char allTOinvs[900]; char invFROMname[50];
			sscanf(line1, "I%[^-]->%s", invFROMname, allTOinvs);
			printf("FROM INV: %s (toinvs: %s)\n", invFROMname, allTOinvs);
			{
				struct reg invtmp; strcpy(invtmp.name, invFROMname); invtmp.type = 1; invtmp.state = 0; strcpy(invtmp.next, allTOinvs);
				strcat(invtmp.next, ",");
				char *ret = strtok(allTOinvs, "\n,");
				while (ret != NULL) {
					printf(" INV	REG TO: %s\n", ret);
					strcpy(invtmp.outs[invtmp.numouts], ret);
					invtmp.numouts++;
					ret = strtok(NULL, "\n,");	
				}
				string nm = invFROMname; mp[nm] = invtmp;
			}

		} else { /*broadcaster*/
			char allTObros[900]; 
			sscanf(line1, "broadcaster->%s", allTObros);
			printf("broadcaster .. toBregs: %s\n", allTObros);
			{
				struct reg brotmp; strcpy(brotmp.name, "broadcaster"); brotmp.type = 2; brotmp.state = 0; strcpy(brotmp.next, allTObros);
				strcat(allTObros, ",");

				char *ret = strtok(allTObros, "\n,");
				while (ret != NULL) {
					printf(" B	REG TO: %s\n", ret);
					strcpy(brotmp.outs[brotmp.numouts], ret);
					brotmp.numouts++;
					ret = strtok(NULL, "\n,");	
				}
				string nm = "broadcaster"; mp[nm] = brotmp;
			}

		}
		printf("-------^^^-------------\n");
	}
	fclose(a);

	{/*populate inputs...*/
		a = fopen(argv[1], "r"); printf("Day19part1\n"); fflush(stdin); fflush(stdout);

		printf("Entering loop to get inputs...\n"); fflush(stdout);
		leny=0, lenx =0;

		while (1)
		{
			printf("-------vvv-------------\n");
			//	printf("her1"); fflush(stdout);
			fgets(line1, 500, a);
			if (feof(a)) {printf("got eof\n"); break;}
			printf("got %s\n", line1); fflush(stdout);
			if (line1[0] == '\n') {
				printf("ready to move...\n");
				break;
			}
			//        line1[(int)strlen(line1) -1] = '\0';

			char line2[100]; int len1 = strlen(line1); int ind2 = 0;
			for (int i = 0; i < len1; i++) {
				if (line1[i] == ' ') {
				} else if (i == 0 && line1[0] == '&') {
					line2[0] = 'I';
					ind2++;
				} else if (i == 0 && line1[0] == '%') {
					line2[0] = 'R';
					ind2++;
				} else {
					line2[ind2] = line1[i];
					ind2++;
				}
			}
			line2[ind2] = '\0'; 
			//printf("LINE2: %s\n", line2);
			strcpy(line1, line2);
			line1[strlen(line1)-1] = '\0';
			lenx = strlen(line1); leny++;

			if (line1[0] == 'R' ) {
				char allTOregs[900]; char regFROMname[50];
				sscanf(line1, "R%[^-]->%s", regFROMname, allTOregs);
				{
					char *ret = strtok(allTOregs, "\n,");
					while (ret != NULL) {
						printf(" REG REG FROM: %s TO: %s\n", regFROMname,ret);

						string nm = ret;
						strcpy(mp[nm].input[mp[nm].numins], regFROMname);
						mp[nm].numins++;

						ret = strtok(NULL, "\n,");	
					}
				}
			} else if (line1[0] == 'I') { /*inverters start with ampersand */
				char allTOinvs[900]; char invFROMname[50];
				sscanf(line1, "I%[^-]->%s", invFROMname, allTOinvs);
				{
					char *ret = strtok(allTOinvs, "\n,");
					while (ret != NULL) {
						printf(" INV	REG FROM %s TO: %s\n", invFROMname, ret);

						string nm = ret;
						strcpy(mp[nm].input[mp[nm].numins], invFROMname);
						mp[nm].numins++;

						ret = strtok(NULL, "\n,");	
					}
				}

			} else { /*broadcaster*/
				char allTObros[900]; 
				sscanf(line1, "broadcaster->%s", allTObros);
				{
					char *ret = strtok(allTObros, "\n,");
					while (ret != NULL) {
						printf(" B	REG FROM %s TO: %s\n", "broadcaster",ret);

						string nm = ret;
						strcpy(mp[nm].input[mp[nm].numins], "broadcaster");
						mp[nm].numins++;

						ret = strtok(NULL, "\n,");	
					}
				}

			}

		}

	}
	fclose(a);

	int LOOP1 = 100000;
	//now process broadcast
	{
		// move to parse
		//   for (int j = 0; j < LOOP1; j++) 
		int j = 1;
		while (1) {
			if (j % 1000 == 0) {printf("loop now at: [%d]\n", j);}

			CURPOS = j;
			char b[100] = "broadcaster";
			strcpy(Qmain[0], b);
			char nextInst[20];
			mpQ0 = mp; int Qnum = 1;
			char nextnext[200];
			processNEXT(0, b, &mp); 
#ifdef _DEBUG_
			cout << " 0 " << Qmain[0] << endl;
			cout << " 1 " << Qmain[1] << endl;
			cout << " 2 " << Qmain[2] << endl; 
#endif
			Qnum = 0;

			//BACKWARD
			while (1) {
#ifdef _DEBUG_
				printf("THE Q AT START IS: [[[[[%d]]]]] [%s]\n", 0, Qmain[0]); 
				printf("THE Q AT START IS: [[[[[%d]]]]] [%s]\n", 1, Qmain[1]); 
#endif
				strcpy(nextnext, "");
				strcpy(nextInst, Qmain[0]);

				if (strlen(nextInst) != 0) {
					for (int i = (int)strlen(nextInst); i >=0; i--) { if (nextInst[i] == ',') { nextInst[i] = '\0'; break; } }
					for (int i = (int)strlen(Qmain[0]); i >=0; i--) { if (Qmain[0][i] == ',') { Qmain[0][i] = '\0'; break; } }
				}
				if (strlen(nextInst) != 0) {
					int found = 0;
					for (int i = (int)strlen(nextInst); i >=0; i--) {if (nextInst[i] == ',') {found = 1; break;} }
					if (found == 1) {
						for (int i = (int)strlen(Qmain[0]); i >=0; i--) {if (Qmain[0][i] == ',') {Qmain[0][i+1] = '\0'; break;} }

						for (int i = (int)strlen(nextInst); i >=0; i--) { 
							if (nextInst[i] == ',') { 
								int start = i; int k,l; 
#ifdef _DEBUG_
								cout << start << endl;
#endif
								for (k = start+1, l=0; k < (int)strlen(nextInst); l++,k++) {
									nextnext[l] = nextInst[k];
#ifdef _DEBUG_
									cout << k << "," << l << endl;
#endif
								} 
								nextnext[l] = '\0';
								break;
							}

						}
						strcpy(nextInst,nextnext);
					} else {
						strcpy(nextInst, Qmain[0]);
						strcpy(Qmain[0], "");
					}
				}
#ifdef _DEBUG_
				cout << "BEFORE: Q0" << Qmain[0] <<endl;
				cout << "BEFORE: Q0" << Qmain[1] <<endl;
				cout << "******nexInst BLANKP? is " << nextInst << endl; 
#endif

				if ((int)strlen(nextInst) == 0) { 
					if ((int)strlen(Qmain[0]) == 0) {
#ifdef _DEBUG_
						cout << "QMAIN zero " << Qmain[0] << endl;
#endif
						if ((int)strlen(Qmain[1]) == 0)  {
#ifdef _DEBUG_
							printf("****SWITCH SWITCH no more instructions on ANY Q \n"); 
#endif
							break;
						} else if ((int)strlen(Qmain[1]) > 0) {
							strcpy(Qmain[0], Qmain[1]); strcpy(Qmain[1],""); Qmain[1][0] = '\0';
#ifdef _DEBUG_
							cout << "BEFORE: " << Qmain[0] <<endl;
							cout << "BEFORE: " << Qmain[1] <<endl;
#endif
							reverseit();
#ifdef _DEBUG_
							cout << "AFTER: " << Qmain[0] <<endl; 
							cout << "AFTER: " << Qmain[1] <<endl; 
#endif
						}
					}
				} else { Qnum++; processNEXT(Qnum, nextInst, &mp); Qnum--;}
			}
			j++;
		}
	}
	tot = LOW*HIGH;
	printf("*LOOP1:(%d)**low %d, high %d\n", LOOP1, LOW, HIGH); fflush(stdout);
	printf("*LOOP1:(%d)**low*high is  %ld\n", LOOP1, tot); fflush(stdout);
}


void reverseit() {
	char nextInst[200]; char nextnext[200]; char ans[50][12];
	int numInst = 0; int last = 0;

	for (int z=0; z < (int)strlen(Qmain[0]); z++) {
		if (Qmain[0][z] == ',') {numInst++;}
	}
#ifdef _DEBUG_
	cout << "------------" << numInst << "-----------" << endl;
#endif
	for (int k = 0; k < numInst; k++) {
		strcpy(nextInst, Qmain[0]);
		if (strlen(nextInst) != 0) {
			for (int i = (int)strlen(nextInst); i >=0; i--) { if (nextInst[i] == ',') { nextInst[i] = '\0'; break; } }
		}
		if (strlen(nextInst) != 0) {
			int found = 0;
			for (int i = (int)strlen(nextInst); i >=0; i--) {if (nextInst[i] == ',') {found = 1; break;} }
			if (found == 1) {
				for (int i = (int)strlen(nextInst); i >=0; i--) { 
					if (nextInst[i] == ',') { 
						int start = i; int k,l; 
#ifdef _DEBUG_
						cout << start << endl;
#endif
						for (k = start+1, l=0; k < (int)strlen(nextInst); l++,k++) {
							nextnext[l] = nextInst[k];
#ifdef _DEBUG_
							cout << k << "," << l << endl;
#endif
						} 
						nextnext[l] = '\0';
						break;
					}

				}
				for (int i = (int)strlen(Qmain[0]); i >=0; i--) { if (Qmain[0][i] == ',') { Qmain[0][i] = '\0'; break; } }
				for (int i = (int)strlen(Qmain[0]); i >=0; i--) { if (Qmain[0][i] == ',') { Qmain[0][i+1] = '\0'; break; } }
#ifdef _DEBUG_
				cout << "------" << k << "----" << endl;
				cout << nextnext << endl;
#endif
				last = k;
				strcpy(ans[k],nextnext);
				strcpy(nextnext, "");
			} else {
				last = k;
				for (int i = (int)strlen(Qmain[0]); i >=0; i--) { if (Qmain[0][i] == ',') { Qmain[0][i] = '\0'; break; } }
				strcpy(nextnext, Qmain[0]);
				strcpy(ans[k],nextnext);
				strcpy(nextnext, "");
			}
		}
	}
	strcpy(Qmain[0], "");
#ifdef _DEBUG_
	cout << "------last --- " << last << "-----" << endl;
#endif
	for (int m = 0; m <= last; m++) {
		strcat(Qmain[0], ans[m]);
		strcat(Qmain[0], ",");
	}
#ifdef _DEBUG_
	cout << "_____________REVERSE REVERSE BEWARE_______is reverse working for Q0_____" << endl; 
#endif

}
void removeoffQ(int Qnum) {

	int foundComma = 0;
	for (int i = 0; i< (int) strlen(Qmain[Qnum]); i++) {
		if (Qmain[Qnum][i] == ',') {
			foundComma = i;	
			break;
		}
	}
	foundComma++;

	int ind;
	for (ind = 0; ind < (int)strlen(Qmain[Qnum]) - foundComma; ind++) {
		Qmain[Qnum][ind] = Qmain[Qnum][ind+foundComma];
	}
	Qmain[Qnum][ind] = '\0';
	//printf("after: [%c]\n",Qmain[Qnum][0]);
	//printf("after: QQQQQQQ afer remove [%s]\n",Qmain[Qnum]);

}

void addtoQ(int qnum, char *next) {
	strcat(Qmain[qnum], next);
	strcat(Qmain[qnum], ",");
}


void processNEXT(int qnum, char *nextCharStar, map<string, struct reg> *mpQX)
{

#ifdef _DEBUG_
	cout << "_____________________________" << endl;
#endif
	string tmpS = nextCharStar;
	auto it = (*mpQX).find(tmpS);
	if (it == (*mpQX).end()) {/*add dummy */
		printf("adding nextCharStar, %s\n", nextCharStar); getchar();
		struct reg regtmp1; strcpy(regtmp1.name, nextCharStar);
		regtmp1.type = 4; regtmp1.state = 0; regtmp1.signalin = SIGNALIN;
		string nm = nextCharStar; (*mpQX)[nm] = regtmp1;
		it = (*mpQX).find(tmpS);
		printf("ERROR.%s.. was incoming (SIGNALIN: %d) a high or a low\n", nextCharStar, SIGNALIN); 
	}
	char CURINPUT[20];
	if (strcmp((*it).second.name, "") == 0) {strcpy((*it).second.name, nextCharStar); (*it).second.type = 4; printf("found blank [%s]\n", nextCharStar); printf("%d\n", (*it).second.signalin);}

	/*
	   if (strcmp((*it).second.name, "ls") == 0) {
	   if ((*it).second.signalin == 0) {
	   printf("%s - %d - %d", (*it).second.name, (*it).second.signalin, CURPOS);
	   }
	   } else if (strcmp((*it).second.name, "vc") == 0) {if ((*it).second.signalin == 0) {printf("%s - %d - %d", (*it).second.name, (*it).second.signalin, CURPOS);}
	   } else if (strcmp((*it).second.name, "nb") == 0) {if ((*it).second.signalin == 0) {printf("%s - %d - %d", (*it).second.name, (*it).second.signalin, CURPOS);}
	   } else if (strcmp((*it).second.name, "vg") == 0) {if ((*it).second.signalin == 0) {printf("%s - %d - %d", (*it).second.name, (*it).second.signalin, CURPOS);}
	   }
	   */
	{ /*get the stete */
		if ((*it).second.invstatepos != 0) { 
#ifdef _DEBUG_
			cout << "READDING the state " << endl; 
#endif
			if ((*it).second.invstatepos == 300) {
				cout << "WARNING WARNING 300..." << (*it).second.invstatepos << endl; getchar();
			}
			///					int ind = (*it).second.invstatepos;
			int ind = 0;
			strcpy(CURINPUT, (*it).second.invstate[ind].currentinput);
			strcpy((*it).second.currentinput, (*it).second.invstate[ind].currentinput);
			(*it).second.signalin =  (*it).second.invstate[ind].signalin;
			for (int i = 0; i< (*it).second.invstatepos; i++) {
				(*it).second.invstate[i] = (*it).second.invstate[i+1];
#ifdef _DEBUG_
				printf(" %d <- %d\n", i, i+1); 
#endif
			}
			(*it).second.invstatepos--;
		} else {

#ifdef _DEBUG_
			cout << "WARNING WARNING only broadcaster... NOT NOT NOT READDING the state for: " << nextCharStar << endl; 
#endif
		}

	}

#ifdef _DEBUG_
	printf("state of [%s] is (*it).second.state:::: %d\n", (*it).second.name, (*it).second.state);
	printf("signalin of [%s] (*it).second.signalin:::: %d\n", (*it).second.name, (*it).second.signalin); 
	printf("signalin of [%s] (*it).second.state:::: %d\n", (*it).second.name, (*it).second.state); 
#endif
	if (strcmp(nextCharStar, "rx") == 0 ) {
		if ((*it).second.signalin == 0) {
			printf("found getchar rx signal low %d", CURPOS);
			fflush(stdout); getchar();
		} 
	} 
	if ((*it).second.signalin == 0) {LOW++;} else {HIGH++;}


	if ((*it).second.type == 0)  {
		//printf("Incoming FlipFlop --%s--\n", nextCharStar);
		if ((*it).second.state == 0) {/*off*/
			if ((*it).second.signalin == 1) {/*high*/
#ifdef _DEBUG_
				printf("	off - signal in  high.ignoring..\n");
#endif
			} else if ((*it).second.signalin == 0) {/*low*/
				//printf("%d\n", (*it).second.numouts); //getc(stdin);
				(*it).second.state = 1;  /*turn on */

				for (int i = (*it).second.numouts -1 ;i>=0; i--) {
					auto it2 = (*mpQX).find((*it).second.outs[i]);
					if (it2 == (*mpQX).end()) {printf("ERROR\n"); getchar();}
					strcpy((*it2).second.currentinput, nextCharStar);
					SIGNALIN = (*it2).second.signalin;
					(*it2).second.signalin = 1; 
					//////
					int ind3 = (*it2).second.invstatepos;
					strcpy((*it2).second.invstate[ind3].currentinput, nextCharStar);
					(*it2).second.invstate[ind3].signalin = (*it2).second.signalin;
					(*it2).second.invstatepos++;
					//////
#ifdef _DEBUG_
					printf("  FF1 ((turn on FF [%s]) & send (high sig(next)): %d -> [%s]\n", 
							(*it).second.name, (*it2).second.signalin, (*it).second.outs[i]);
#endif
					if (strcmp((*it).second.outs[i], "lg") == 0) {
						//fflush(stdout); dup2(fd, 1);
						printf("YYY\n"); printf("%d %s -> %s high\n", CURPOS, (*it).second.name, (*it).second.outs[i]);}
					//nums.push_back(CURPOS);
					//close(1);
					/*
					   if (nums.size() == 4) {
					   fflush(stdout); dup2(fd, 1); 
					   for (auto ii: nums) {
					   printf("%d \n", ii);
					   }
					   printf("**ans: %llu\n", lcm(nums));
					//exit(0);
					*/


					SIGNALIN = (*it2).second.signalin;
					addtoQ(qnum, (*it).second.outs[i]);
				} 
				}
			} else if ((*it).second.state == 1) {/*on*/
				if ((*it).second.signalin == 1) {/*high*/
#ifdef _DEBUG_
					printf(" 	on -	signal in  high ignoring\n");
#endif
				} else if ((*it).second.signalin == 0) {/*low*/
					//printf("low %d\n", (*it).second.numouts); getc(stdin);
					(*it).second.state = 0; /*turn off*/ 

					for (int i = (*it).second.numouts -1 ;i>=0; i--) {
						auto it2 = (*mpQX).find((*it).second.outs[i]);
						if (it2 == (*mpQX).end()) {printf("ERROR2\n"); getchar();}

						strcpy((*it2).second.currentinput, nextCharStar);
						(*it2).second.signalin = 0; 
						SIGNALIN = (*it2).second.signalin;
						////
						int ind4 = (*it2).second.invstatepos;
						strcpy((*it2).second.invstate[ind4].currentinput, nextCharStar);
						(*it2).second.invstate[ind4].signalin = (*it2).second.signalin;
						(*it2).second.invstatepos++;
						////
						/*
						   if (strcmp((*it).second.outs[i], "vg") == 0 || 
						   strcmp((*it).second.outs[i], "nb") == 0 || 
						   strcmp((*it).second.outs[i], "vc") == 0 || 
						   strcmp((*it).second.outs[i], "ls") == 0) {

						   printf("FF2 ((turn off [%s]) & send (low sig(next)): %d -> [%s]\n", 
						   (*it).second.name, (*it2).second.signalin, (*it).second.outs[i]);
						   }
						   */

#ifdef _DEBUG_
#endif
						addtoQ(qnum, (*it).second.outs[i]);
					} 

				}
			}

		} else if ((*it).second.type == 1) {/*inverter*/
#ifdef _DEBUG_
			printf("-------------The Tricky Inverter --%s--\n", nextCharStar);
#endif
			///char CURINPUT[20];
#ifdef _DEBUG_
			printf("CURRENT INPUT is [%s] for [%s]\n", (*it).second.currentinput, nextCharStar); 
#endif
			{ /* set the current input */
				for (int i = 0; i < (*it).second.numouts; i++) {
					auto it3 = (*mpQX).find((*it).second.outs[i]);
					if ((*it3).second.type == 1) {
#ifdef _DEBUG_
						printf("YATZEE inv to inv (%s) -> (%s)\n", (*it).second.name, (*it).second.outs[i]);
#endif
					}
					strcpy((*it3).second.currentinput, nextCharStar);
					SIGNALIN = (*it3).second.signalin;
				} 
			}
			{ /* create entries in INV2saved */
				for (int i = 0; i < (*it).second.numins; i++) {
					string tmpSS = (*it).second.input[i];
					string mytmpSS = nextCharStar; mytmpSS += (*it).second.input[i];
					auto ittmp = INV2saved.find(mytmpSS);
					if (ittmp == INV2saved.end()) {         
						struct reg regsavedPrev;
						strcpy(regsavedPrev.name, (*it).second.currentinput);
#ifdef _DEBUG_
						cout << "****adding 2222 SHOULD GET HERE" << " INV2saved " << (*it).second.currentinput << " "<< mytmpSS << " to INV2saved" << endl; 
#endif
						regsavedPrev.signalin = 0;
						INV2saved[mytmpSS] = regsavedPrev;
#ifdef _DEBUG_
						printf("ADDED [%s] not in IV2saved here\n", mytmpSS.c_str());
#endif
					}
				}
			}

			{ /*some dubug */
#ifdef _DEBUG_
				printf("signal  in %d\n", (*it).second.signalin);
				printf("currentinput of (%s) is (%s) ABC\n", nextCharStar, (*it).second.currentinput);
				printf("numins in %d\n", (*it).second.numins);
#endif
			}

			{/* update the saved signal for this one */
				string mytmpSp = nextCharStar; mytmpSp += (*it).second.currentinput; 

				auto itPrev = INV2saved.find(mytmpSp);

				int found = 0;
				for (int i = 0; i < (*it).second.numins; i++) {

					if (strcmp((*it).second.currentinput, (*it).second.input[i]) == 0) {
						(*itPrev).second.signalin = (*it).second.signalin;
						found++;
					}
				}
				if (found != 1) {printf("WARNING");fflush(stdout); exit(0);}
			}

			int counthigh;
			{ /* count the high signals in store */
				counthigh = 0;
				for (int i = 0; i < (*it).second.numins; i++) {
					string tmpSS = (*it).second.input[i];
					string mytmpSS = nextCharStar; mytmpSS += (*it).second.input[i];
					auto ittmp = INV2saved.find(mytmpSS);
					if ((*ittmp).second.signalin == 1) {
						counthigh++;
					}
				}
#ifdef _DEBUG_
				printf("SOMEWHERE AROUND HERE MAYBE allhigh is %d\n", counthigh);	
#endif
			}
			int myoutputsignal;
			{ /* if all high set to low otherwise set to high */
				myoutputsignal = 1;
				if (counthigh == (*it).second.numins) {
#ifdef _DEBUG_
					printf("* %d (all remembered inputs high so send low)\n", myoutputsignal);
#endif
					myoutputsignal = 0;
				} 
			}
			{ /*send to all the outputs the "myoutputsignal" */
				for (int i = (*it).second.numouts -1 ;i>=0; i--) {
					auto it2 = (*mpQX).find((*it).second.outs[i]);
					(*it2).second.signalin = myoutputsignal;
					strcpy((*it2).second.currentinput, (*it).second.name);
#ifdef _DEBUG_
					printf("INV SENDING [%d] TO [%s]\n", myoutputsignal, (*it).second.outs[i]);
#endif
					//if ((*it2).second.type == 1) 

					int ind = (*it2).second.invstatepos;
					strcpy((*it2).second.invstate[ind].currentinput, nextCharStar);
					(*it2).second.invstate[ind].signalin = myoutputsignal;
					(*it2).second.invstatepos++;
					//////	
					strcpy((*it2).second.currentinput, nextCharStar);
					SIGNALIN = (*it2).second.signalin;
					addtoQ(qnum, (*it).second.outs[i]);
					if (myoutputsignal == 1) {
						if (strcmp((*it).second.outs[i], "lg") == 0) {
							printf("here1...");
							printf("%d %s -> %s high\n", CURPOS, (*it).second.name, (*it).second.outs[i]);
							printf("\nconor\npushing %d\n", CURPOS);
							nums.push_back(CURPOS);
							printf("%lld\n", nums.back());
							if (nums.size() == 4) {
								for (auto ii: nums) {
									printf("%lld \n", ii);
								}
								fflush(stdout); dup2(fd, 1); 
								printf("**ans: %llu\n", lcm(nums));
								exit(0);
							}
						}

					}
				}
			}
		} else if ((*it).second.type == 2) {/*broadcast*/
#ifdef _DEBUG_
			printf("BROADCAST BROADCAST-----------------------\n");
			printf("%s ---n((*it).second.next)=%s\n", nextCharStar, (*it).second.next);
#endif

			strcpy(Qmain[0], "");
			for (int i = (*it).second.numouts -1 ;i>=0; i--) {
				string regNAME = (*it).second.outs[i];
				auto it2 = mp.find(regNAME); 
				(*it2).second.signalin = 0;  
				///
				int ind = (*it2).second.invstatepos;
				strcpy((*it2).second.invstate[ind].currentinput, nextCharStar);
				(*it2).second.invstate[ind].signalin = (*it).second.signalin;
				(*it2).second.invstatepos++;
				///
#ifdef _DEBUG_
				printf("broadcaster --- ADDING %s\n", (*it).second.outs[i]); 
#endif
				addtoQ(0, (*it).second.outs[i]);
			}
		} else if ((*it).second.type == 4) { /*dummy*/
#ifdef _DEBUG_
			printf("DUMMY [%s] sig: [%d]\n", (*it).second.name, (*it).second.signalin);
#endif
		}
	}

