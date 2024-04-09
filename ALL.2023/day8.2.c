#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

int nums[1000][1000];
long tot = 0;
int TOTNUMSM1 = 20;
//int TOTNUMSM1 = 5;
int LEVEL;
int done;
int notallzeroes = 0;
char one[4];
string oneS[4];
char two[4];
char tre[4];
void subnums();
void transferandcalc();

struct lr {
   char left[4];
   char rite[4];
};
int main(int argc, char **argv)
{
        int r = 0;
        char starts[100][5];
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        map<string, struct lr> mp;
        FILE * a = fopen(argv[1], "r"); printf("Day8.2\n"); fflush(stdin); fflush(stdout);

        char line1[1000];
        char instructs[1000];
        fgets(instructs, 1000, a);
            fgets(line1, 1000, a);
//build maps
printf("Entering loop...\n");
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s", asctime(tm));
} 
        while (1) {
done = 0;
            fgets(line1, 1000, a); if (feof(a)) {break;}
	    one[0] = line1[0]; one[1] = line1[1]; one[2] = line1[2]; one[3] = '\0';
	    string oneS = one;
       if (line1[2] == 'A') {strcpy(starts[r], one); r++;}
	    two[0] = line1[7]; two[1] = line1[8]; two[2] = line1[9]; two[3] = '\0';
	    tre[0] = line1[12]; tre[1] = line1[13]; tre[2] = line1[14]; tre[3] = '\0';
            struct lr tmplr; strcpy(tmplr.left, two); strcpy(tmplr.rite, tre);
	    //mp.insert({one, tmplr}); 
	    mp[oneS] = tmplr;
          
      }

strcpy(starts[r], "QQQ");
int s = 0;
int i = 0;

long long tot = 0;
nextinstruction:
{
for (s = 0; s < r; s++) {

//cout << "strarting parse" << endl;

string inst = (string)starts[s];
//cout << "inst" << inst << endl;
//getchar();
restart:
//cout << "here restart" << endl;
      for (; i < 999;) {
	  //printf("next %c ", instructs[i]);
          if (instructs[i] == '\n') {/*cout << "GOTO...";*/ i = 0; goto restart;}
	  else {
tot++;
              if (instructs[i] == 'L') { inst = (string)mp.at(inst).left; }
	      else {inst = (string)mp.at(inst).rite;}
//              cout << "new inst: " << inst << endl; 
	      strcpy(starts[s], inst.c_str());
              //if (inst == "ZZZ") {printf("found ZZZ..."); break;} 
	  }
//getchar();
	  break;
      }
}
if (s == r) {s = 0; int allZ = 1;
      for (int t = 0; t < r; t++) { if (starts[t][2] != 'Z') { allZ = 0; }}
      if (allZ == 1) {cout << "YAY, all Z..." << endl;} else {if (tot %
 1000000000 == 0) {{ 
time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s", asctime(tm));} cout << "Total: " << tot << endl; /*cout << "SoFar: " << tot << " -- " << "nums: " <<r << " To: 13,700,000,000,000 " << endl;*/}; allZ = 1; i++; goto nextinstruction;}
}
}
      fclose(a);
      printf("****TOT:***** %ld\n", tot/r);

}
//	if (starts[s][2] != 'Z') {i++; goto nextinstruction;}
