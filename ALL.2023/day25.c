#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h> 
#include <time.h>

using namespace std; 
time_t from;

struct comp {
	string name;
	int numlinks = 0;
	string links[9];
};
void *pfunc(void *vargp); 
void process123(struct comp i20, map <string, struct comp> *mpX, map <string, char> *orderL, map <string, char> *alreadyMap, int *, int**);
//map <string, char> alreadyMap;
map <string, struct comp> mp;
int leny;
int tot = 0;
map <string, char> order;
map <string, char> origorder;
int depth = 0;
void printit();
struct mypair {
	string one;
	string two;
	int kpos = 0;
	int qpos = 0;
};
int flatpos = 0;
struct mypair flatten[3500]; 
/*
int myfrom[] = {0,  26,  101, 401,  2001};
int myto[]   = {25, 100, 400, 2000, 3420};
*/
int myfrom[] = {1,  11, 26, 56,  101, 201, 401,  801, 1601, 2001};
int myto[]   = {10, 25, 55, 100, 200, 400, 800, 1600, 2000, 3420};
map <string, struct comp>mpG[10];
int main (int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

    	pthread_t tid0; pthread_t tid1; pthread_t tid2; pthread_t tid3; pthread_t tid4; 
	pthread_t tid5; pthread_t tid6; pthread_t tid7; pthread_t tid8; pthread_t tid9; 

        FILE * a = fopen(argv[1], "r"); printf("Day9.1\n"); fflush(stdin); fflush(stdout);
        char line1[1000];
	leny = 0;
        while (1) {
	
		fgets(line1, 1000, a); if (feof(a)) {break;}
//		printf("line1 %s", line1); 
		char from[100];
		char rest[300];
		sscanf(line1, "%[^:]: %[^\n]", from, rest); 
		string fromS = from;
		struct comp tmpcomp; tmpcomp.name = from;

		auto i2 = mp.find(fromS);
		if (i2 == mp.end()) {mp.insert({fromS, tmpcomp});}
		order.insert({fromS, 'A'});
		i2 = mp.find(fromS);
		char *ret;
		ret = strtok(rest, " \n\0");
		while (ret != NULL) {
			string tmpret = ret;
			{ /*main*/
				(*i2).second.links[(*i2).second.numlinks] = tmpret;
				//printf("numlink is %d\n", (*i2).second.numlinks);
				(*i2).second.numlinks++;
			}
			{
                                auto i1 = mp.find(tmpret);
                                if (i1 == mp.end()) {
                                        struct comp tmpcomp; tmpcomp.name = tmpret;
                                        tmpcomp.links[tmpcomp.numlinks] = fromS;
                                        tmpcomp.numlinks++;
                                        mp.insert({tmpret, tmpcomp});
                                } else {
                                        (*i1).second.links[(*i1).second.numlinks] = fromS;
                                        (*i1).second.numlinks++;
                                }
                        }

			ret = strtok(NULL, " \n\0");
		}
	} //while
	fclose(a);
	printf("map mp size %ld\n", mp.size()); 

	flatpos = 0;
	printf("before flatten...\n"); fflush(stdout); 
	auto it10 = mp.begin();
	while (it10 != mp.end()) {
		for (int k = 0; k < (*it10).second.numlinks; k++) {
			int found = 0;
			for (int l = 0; l < flatpos; l++) {
				if ((*it10).second.name == flatten[l].one && (*it10).second.links[k] == flatten[l].two) { found = 1; break;}
				if ((*it10).second.name == flatten[l].two && (*it10).second.links[k] == flatten[l].one) { found = 1; break;}
			}
			if (found == 0) {
				flatten[flatpos].one = (*it10).second.name; 
				flatten[flatpos].kpos = k;
					
				flatten[flatpos].two = (*it10).second.links[k]; 
				auto it12 = mp.find(flatten[flatpos].two);
				//if (it12 == mp.end()) {printf("did not find..."); fflush(stdout);} else {printf("found\n");}
				for (int i = 0; i < (*it12).second.numlinks; i++) {
					if ((*it12).second.links[i] == (*it10).second.name) {
						//printf("setting qpos\n"); fflush(stdout); 
						flatten[flatpos].qpos = i; break;
					}
				}
				flatpos++;
			}
		}
		it10++;
	}
	printf("after flatten... flatpos %d\n", flatpos); fflush(stdout); 

	origorder = order;
	printf("order(Pos) is %ld\n", order.size()); fflush(stdout);

	//myret[0] = 0; myret[1] = 0; myret[2] = 0;
	time(&from);
	for (int o = 0; o < flatpos -2; o++) {
		time_t rawtimeo; time(&rawtimeo);
		printf("Time since start o [%f]s for +1 (%d)\n", difftime(rawtimeo, from), o);
		string befo1 = mp[flatten[o].one].links[flatten[o].kpos];
		string befo2 = mp[flatten[o].two].links[flatten[o].qpos];
		mp[flatten[o].one].links[flatten[o].kpos] = "ZZZ";
		mp[flatten[o].two].links[flatten[o].qpos] = "ZZZ";
		mpG[0] = mp; mpG[1] = mp; mpG[2] = mp; mpG[3] = mp; mpG[4] = mp;
		mpG[5] = mp; mpG[6] = mp; mpG[7] = mp; mpG[8] = mp; mpG[9] = mp;
		myfrom[0] = o+1;
		int id0 = 0; pthread_create(&tid0, NULL, pfunc, &id0); 
		int id1 = 1; pthread_create(&tid1, NULL, pfunc, &id1);
		int id2 = 2; pthread_create(&tid2, NULL, pfunc, &id2); 
		int id3 = 3; pthread_create(&tid3, NULL, pfunc, &id3); 
		int id4 = 4; pthread_create(&tid4, NULL, pfunc, &id4);
		int id5 = 5; pthread_create(&tid5, NULL, pfunc, &id5);
		int id6 = 6; pthread_create(&tid6, NULL, pfunc, &id6);
		int id7 = 7; pthread_create(&tid7, NULL, pfunc, &id7);
		int id8 = 8; pthread_create(&tid8, NULL, pfunc, &id8);
		int id9 = 9; pthread_create(&tid9, NULL, pfunc, &id9);
		pthread_join(tid0, NULL);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);
		pthread_join(tid5, NULL);
		pthread_join(tid6, NULL);
		pthread_join(tid7, NULL);
		pthread_join(tid8, NULL);
		pthread_join(tid9, NULL);

		printf("finished all threads... re-looping"); fflush(stdout);
		mp[flatten[o].one].links[flatten[o].kpos] = befo1;
		mp[flatten[o].two].links[flatten[o].qpos] = befo2;
	}
	return 0;
}

void *pfunc(void *vargp) {
	printf("in pfunc..."); fflush(stdout);
	int *myid = (int *)vargp;
	map <string, struct comp> mp1 = mpG[*myid];
	map <string, char> alreadyMap;
	int *myret = (int *)malloc(4*sizeof(int));
	myret[0] = 0; myret[1] = 0; myret[2] = 0;
	printf("in pfunc %d %d->%d\n", *myid, myfrom[*myid], myto[*myid]); fflush(stdout);
		for (int p = myfrom[*myid]; p < myto[*myid]; p++) {
			if (p % 10 == 0) {
				time_t rawtimep; time(&rawtimep);
				printf("(%d) Time since start %d [%f]s for +10\n", *myid, p, difftime(rawtimep, from));
			}
			string befp1 = mp1[flatten[p].one].links[flatten[p].kpos];
			string befp2 = mp1[flatten[p].two].links[flatten[p].qpos];
			mp1[flatten[p].one].links[flatten[p].kpos] = "ZZZ";
			mp1[flatten[p].two].links[flatten[p].qpos] = "ZZZ";
			for (int q = p+1; q < flatpos; q++) {
				if (q % 300 == 0) 
				{
					time_t rawtimeq; time(&rawtimeq);
					printf("(%d) Time since start %d %d [%f]s for +300\n", *myid, p, q, difftime(rawtimeq, from));
				}
				string befq1 = mp1[flatten[q].one].links[flatten[q].kpos];
				string befq2 = mp1[flatten[q].two].links[flatten[q].qpos];
				mp1[flatten[q].one].links[flatten[q].kpos] = "ZZZ";
				mp1[flatten[q].two].links[flatten[q].qpos] = "ZZZ";
				map <string, char> orderL = origorder;
				int myretpos = 0;
				int b = 0;
				for (auto& [key, value]: orderL) {
					if (value != 'Q') {
						myret[myretpos] = 1;
						alreadyMap.clear();
						process123(mp1[key], &mp1, &orderL, &alreadyMap, &myretpos, &myret); 
						myretpos++;
						if (myretpos > 2) {b = 1; break;}
					}
				}
				if (myretpos == 2 && b==0) {
					printf("*(%d)***MULTIPLY == %d by %d == %d\n", *myid,
						myret[0], myret[1], myret[0]*myret[1]); 
					fflush(stdout);
				} else if (myretpos == 2 && b==1) {
					printf("*(%d)***BROKE MULTIPLY == %d by %d == %d\n", *myid,
						myret[0], myret[1], myret[0]*myret[1]); 
				}
				mp1[flatten[q].one].links[flatten[q].kpos] = befq1;
				mp1[flatten[q].two].links[flatten[q].qpos] = befq2;
			}
			mp1[flatten[p].one].links[flatten[p].kpos] = befp1; 
			mp1[flatten[p].two].links[flatten[p].qpos] = befp2;
		}
	free(myret);
	return NULL;
}

void process123(struct comp i20, map <string, struct comp> *mpX, map <string, char> *orderL, map <string, char> *alreadyMap, int *myretpos, int**myret)
{
	fflush(stdout);
	(*alreadyMap).insert({i20.name, 'A'});

	for (int i = 0; i < i20.numlinks; i++) {
	    	if (i20.links[i] != "ZZZ") {
			struct comp tmplink = (*mpX)[i20.links[i]];
			(*orderL)[tmplink.name] = 'Q';

			if ((*alreadyMap).find(tmplink.name) == (*alreadyMap).end()) {
				process123(tmplink, mpX, orderL, alreadyMap, myretpos, myret);
				(*myret)[*myretpos]++;
			}
	    	}
	}
	return;
}

void printit() {
	auto iter = mp.begin();
	for (; iter != mp.end(); iter++) {
		printf("%s:", (*iter).first.c_str());
		for (int i = 0; i < (*iter).second.numlinks; i++) {
			printf("%s ", (*iter).second.links[i].c_str());
		}
		printf("\n");
	}
	printf("-----------------------------------\n");	
}
