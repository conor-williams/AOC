#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

#include <unistd.h>

#define getchar()
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

int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("2023 Day20 Part 1\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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

	int LOOP1 = 1000;
	//now process broadcast
	{
		// move to parse
		for (int j = 0; j < LOOP1; j++) {
			char b[100] = "broadcaster";
			strcpy(Qmain[0], b);
			char nextInst[20];
			mpQ0 = mp; int Qnum = 1;
			char nextnext[200];
			processNEXT(0, b, &mp); 
			cout << " 0 " << Qmain[0] << endl;
			cout << " 1 " << Qmain[1] << endl;
			cout << " 2 " << Qmain[2] << endl; 
			Qnum = 0;

			//BACKWARD
			while (1) {
				printf("THE Q AT START IS: [[[[[%d]]]]] [%s]\n", 0, Qmain[0]); 
				printf("THE Q AT START IS: [[[[[%d]]]]] [%s]\n", 1, Qmain[1]); 
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
								cout << start << endl;
								for (k = start+1, l=0; k < (int)strlen(nextInst); l++,k++) {
									nextnext[l] = nextInst[k];
									cout << k << "," << l << endl;
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
				cout << "BEFORE: Q0" << Qmain[0] <<endl;
				cout << "BEFORE: Q0" << Qmain[1] <<endl;
				cout << "******nexInst BLANKP? is " << nextInst << endl; 

				if ((int)strlen(nextInst) == 0) { 
					if ((int)strlen(Qmain[0]) == 0) {
						cout << "QMAIN zero " << Qmain[0] << endl;
						if ((int)strlen(Qmain[1]) == 0)  {
							printf("****SWITCH SWITCH no more instructions on ANY Q \n"); 
							break;
						} else if ((int)strlen(Qmain[1]) > 0) {
							strcpy(Qmain[0], Qmain[1]); strcpy(Qmain[1],""); Qmain[1][0] = '\0';
							cout << "BEFORE: " << Qmain[0] <<endl;
							cout << "BEFORE: " << Qmain[1] <<endl;
							reverseit();
							cout << "AFTER: " << Qmain[0] <<endl; 
							cout << "AFTER: " << Qmain[1] <<endl; 
						}
					}
				} else { Qnum++; processNEXT(Qnum, nextInst, &mp); Qnum--;}
			}
		}
	}
	tot = LOW*HIGH;
	printf("*LOOP1:(%d)**low %d, high %d\n", LOOP1, LOW, HIGH); fflush(stdout);
	printf("*LOOP1:(%d)**low*high is  %ld\n", LOOP1, tot); fflush(stdout);

	fflush(stdout); dup2(fd, 1);
	printf("**ans:  %ld\n", tot); fflush(stdout);
}


void reverseit() {
	char nextInst[200]; char nextnext[200]; char ans[50][12];
	int numInst = 0; int last = 0;

	for (int z=0; z < (int)strlen(Qmain[0]); z++) {
		if (Qmain[0][z] == ',') {numInst++;}
	}
	cout << "------------" << numInst << "-----------" << endl;
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
						cout << start << endl;
						for (k = start+1, l=0; k < (int)strlen(nextInst); l++,k++) {
							nextnext[l] = nextInst[k];
							cout << k << "," << l << endl;
						} 
						nextnext[l] = '\0';
						break;
					}

				}
				for (int i = (int)strlen(Qmain[0]); i >=0; i--) { if (Qmain[0][i] == ',') { Qmain[0][i] = '\0'; break; } }
				for (int i = (int)strlen(Qmain[0]); i >=0; i--) { if (Qmain[0][i] == ',') { Qmain[0][i+1] = '\0'; break; } }
				cout << "------" << k << "----" << endl;
				cout << nextnext << endl;
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
	cout << "------last --- " << last << "-----" << endl;
	for (int m = 0; m <= last; m++) {
		strcat(Qmain[0], ans[m]);
		strcat(Qmain[0], ",");
	}
	cout << "_____________REVERSE REVERSE BEWARE_______is reverse working for Q0_____" << endl; 

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
	printf("after: QQQQQQQ afer remove [%s]\n",Qmain[Qnum]);

}

void addtoQ(int qnum, char *next) {
	strcat(Qmain[qnum], next);
	strcat(Qmain[qnum], ",");
}


void processNEXT(int qnum, char *nextCharStar, map<string, struct reg> *mpQX)
{

	cout << "_____________________________" << endl;
	string tmpS = nextCharStar;
	auto it = (*mpQX).find(tmpS);
	if (it == (*mpQX).end()) {/*add dummy */
		struct reg regtmp1; strcpy(regtmp1.name, nextCharStar);
		regtmp1.type = 4; regtmp1.state = 0; regtmp1.signalin = SIGNALIN;
		string nm = nextCharStar; (*mpQX)[nm] = regtmp1;
		it = (*mpQX).find(tmpS);
		printf("ERROR.%s.. was incoming (SIGNALIN: %d) a high or a low\n", nextCharStar, SIGNALIN); 
	}
	char CURINPUT[20];

	{ /*get the stete */
		if ((*it).second.invstatepos != 0) { 
			cout << "READDING the state " << endl; 
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
				printf(" %d <- %d\n", i, i+1); 
			}
			(*it).second.invstatepos--;
		} else {

			cout << "WARNING WARNING only broadcaster... NOT NOT NOT READDING the state for: " << nextCharStar << endl; 
		}

	}

	printf("state of [%s] is (*it).second.state:::: %d\n", (*it).second.name, (*it).second.state);
	printf("signalin of [%s] (*it).second.signalin:::: %d\n", (*it).second.name, (*it).second.signalin); 
	printf("signalin of [%s] (*it).second.state:::: %d\n", (*it).second.name, (*it).second.state); 
	if ((*it).second.signalin == 0) {LOW++;} else {HIGH++;}


	if ((*it).second.type == 0)  {
		//printf("Incoming FlipFlop --%s--\n", nextCharStar);
		if ((*it).second.state == 0) {/*off*/
			if ((*it).second.signalin == 1) {/*high*/
				printf("	off - signal in  high.ignoring..\n");
			} else if ((*it).second.signalin == 0) {/*low*/
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
					printf("  FF1 ((turn on FF [%s]) & send (high sig(next)): %d -> [%s]\n", 
							(*it).second.name, (*it2).second.signalin, (*it).second.outs[i]);
					SIGNALIN = (*it2).second.signalin;
					addtoQ(qnum, (*it).second.outs[i]);
				} 
			}
		} else if ((*it).second.state == 1) {/*on*/
			if ((*it).second.signalin == 1) {/*high*/
				printf(" 	on -	signal in  high ignoring\n");
			} else if ((*it).second.signalin == 0) {/*low*/
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
					printf("FF2 ((turn off [%s]) & send (low sig(next)): %d -> [%s]\n", 
							(*it).second.name, (*it2).second.signalin, (*it).second.outs[i]);
					addtoQ(qnum, (*it).second.outs[i]);
				} 

			}
		}

	} else if ((*it).second.type == 1) {/*inverter*/
		printf("-------------The Tricky Inverter --%s--\n", nextCharStar);
		//char CURINPUT[20];
		printf("CURRENT INPUT is [%s] for [%s]\n", (*it).second.currentinput, nextCharStar); 
		{ /* set the current input */
			for (int i = 0; i < (*it).second.numouts; i++) {
				auto it3 = (*mpQX).find((*it).second.outs[i]);
				if ((*it3).second.type == 1) {
					printf("YATZEE inv to inv (%s) -> (%s)\n", (*it).second.name, (*it).second.outs[i]);}
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
					cout << "****adding 2222 SHOULD GET HERE" << " INV2saved " << (*it).second.currentinput << " "<< mytmpSS << " to INV2saved" << endl; 
					regsavedPrev.signalin = 0;
					INV2saved[mytmpSS] = regsavedPrev;
					printf("ADDED [%s] not in IV2saved here\n", mytmpSS.c_str());
				}
			}
		}

		{ /*some dubug */
			printf("signal  in %d\n", (*it).second.signalin);
			printf("currentinput of (%s) is (%s) ABC\n", nextCharStar, (*it).second.currentinput);
			printf("numins in %d\n", (*it).second.numins);
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
			printf("SOMEWHERE AROUND HERE MAYBE allhigh is %d\n", counthigh);	
		}
		int myoutputsignal;
		{ /* if all high set to low otherwise set to high */
			myoutputsignal = 1;
			if (counthigh == (*it).second.numins) {
				printf("* %d (all remembered inputs high so send low)\n", myoutputsignal);
				myoutputsignal = 0;
			} 
		}
		{ /*send to all the outputs the "myoutputsignal" */
			for (int i = (*it).second.numouts -1 ;i>=0; i--) {
				auto it2 = (*mpQX).find((*it).second.outs[i]);
				(*it2).second.signalin = myoutputsignal;
				strcpy((*it2).second.currentinput, (*it).second.name);
				printf("INV SENDING [%d] TO [%s]\n", myoutputsignal, (*it).second.outs[i]);
				//if ((*it2).second.type == 1) 

				int ind = (*it2).second.invstatepos;
				strcpy((*it2).second.invstate[ind].currentinput, nextCharStar);
				(*it2).second.invstate[ind].signalin = myoutputsignal;
				(*it2).second.invstatepos++;
				//////	
				strcpy((*it2).second.currentinput, nextCharStar);
				SIGNALIN = (*it2).second.signalin;
				addtoQ(qnum, (*it).second.outs[i]);
			}
		}
	} else if ((*it).second.type == 2) {/*broadcast*/
		printf("BROADCAST BROADCAST-----------------------\n");

		printf("%s ---n((*it).second.next)=%s\n", nextCharStar, (*it).second.next);

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
			printf("broadcaster --- ADDING %s\n", (*it).second.outs[i]); 
			addtoQ(0, (*it).second.outs[i]);
		}
	} else if ((*it).second.type == 4) { /*dummy*/
		printf("DUMMY [%s] sig: [%d]\n", (*it).second.name, (*it).second.signalin);
	}
}

