#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <deque>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <regex>
//#include <ctre.hpp>

using namespace std;
FILE *a;
#define LINE 3500
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
deque <string> from;
deque <string> to;
int loop(string sto1, int pos, int *countLocal);
set <char> se;
int main(int argc, char **argv)
{
	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 19 Part 1\n"); fflush(stdout);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);

		if (line1[0] == '\0') {printf("here2\n");goto next;}
		if (line1[0] == 'Q') {printf("here2\n");break;}
		if (leny == 0) {
			char *fir = strtok(line1, " ,\0");
			do {
				string f1 = fir;
				reverse(f1.begin(), f1.end());
				from.push_back(f1);
			} while ((fir = strtok(NULL, " ,\0")) != NULL);
		} else {
			string f2 = line1;
			reverse(f2.begin(), f2.end());
			to.push_back(f2);
			for (int i = 0; i < (int)strlen(line1); i++)  {
				se.insert(line1[i]);
			}
		}
next:
		leny++;
	}
	fclose(a);

	int count = 0;
	sort(from.begin(), from.end());
	//char re_var[12000] = "(";
	string re_var = "(";
	
	int first = 0;
	for (auto x: from) {
		if (first == 1) {
			//snprintf(re_var, 11000, "%s|(%s)*", re_var, x.c_str());
			re_var += "|(" + x + ")*";
		} else {
			first = 1;
			//snprintf(re_var, 11000, "%s(%s)*", re_var, x.c_str());
			re_var += "(" + x + ")*";
		}
			
	}

	re_var += ")+";
	
	//snprintf(re_var, 11000, "%s)+", re_var);
	printf("re_var is %s\n", re_var.c_str());
		
	printf("from.size() is %d\n", (int)from.size());
	//for (auto a: from) { cout << a << endl; } getchar();

	//basic_regex reCon (re_var);
	//char myregexex1[] = "((b)*|(br)*|(bwu)*|(g)*|(gb)*|(r)*|(rb)*|(wr)*)+";
	int zzz = 0;
	for (auto sto1: to) {
		cout << zzz << ": " << sto1 << endl;
		int countLocal = 0;
		loop(sto1, 0, &countLocal);
		if (countLocal != 0) {count++;}
		zzz++;
	}
	printf("**ans %d\n", count);
}


int level = 0;
int loop(string sto1, int pos, int *countLocal) {
	level++;
	if (pos >= (int)sto1.length()) {
		level--; 
		//for (int zz = 0; zz < level; zz++) {printf("	");} cout << "returning 22" << endl;
		 (*countLocal)++;return 22;
	}
	for (auto sfrm1: from) {
		//for (int zz = 0; zz < level; zz++) {printf("	");} cout << sfrm1 << endl;
		int len = sfrm1.length();
		int retVal = sto1.compare(pos, len, sfrm1);
		//string subto1 = sto1.substr(pos, len); int retVal = strcmp(subto1.c_str(), sfrm1.c_str());	
		if (retVal == 0) {
			//for (int zz = 0; zz < level; zz++) {printf("	");}
			//printf("equal %s V %s\n", subto1.c_str(), sfrm1.c_str());
			int loopRet = 0;
			loopRet = loop(sto1, pos+len, countLocal);
			if (loopRet == 22) {level--; return 22;}
		} else if (retVal < 0) {
			//for (int zz = 0; zz < level; zz++) {printf("	");}
			//printf("less %s V %s\n", subto1.c_str(), sfrm1.c_str());
			level--;
			return 99;
		} else { //greater
			//for (int zz = 0; zz < level; zz++) {printf("	");}
			//printf("greater %s V %s\n", subto1.c_str(), sfrm1.c_str());
			continue;
		}
	}
	level--;
	return 100;
}

/*
	int zzz = 0;
	for (auto sto1: toFiltered) {
		cout << zzz << ": " << sto1 << endl;
		int countLocal = 0;
		loop(sto1, 0, &countLocal);
		if (countLocal != 0) {count++;}
		zzz++;
	}
*/



























/*
	string a = "hello";
	string b = "hellp";
	string c = "hephellllpp";

	cout << a << " V " << b << endl;
	int rval = a.compare(0, 5, b);
	
	if (regex_match(a, regex("((he)*|(ll)*|(o)*)+")  )) {printf("got a match a\n");} else {printf("no match a\n");}
	if (regex_match(b, regex("((he)*|(ll)*|(o)*)+"))) {printf("got a match b \n");} else {printf("no match b\n");}
	if (regex_match(b, regex("((he)*|(ll)*|(p)*)+"))) {printf("got a match p\n");} else {printf("no match p\n");}
	if (regex_match(c, regex("((he)*|(ll)*|(p)*)+"))) {printf("got a match c\n");} else {printf("no match c\n");}

	printf("1rval is %d\n", rval); getchar();
	rval = b.compare(0, 5, a);
	printf("2rval is %d\n", rval); getchar();
*/
/*
	deque <string> toFiltered;
	for (auto sto1: to) {
		int notfound = 0;
		for (int kk = 0; kk < (int)sto1.length(); kk++) {
			if (se.find(sto1[kk]) == se.end()) {
				notfound = 1; break;	
			}
		}
		if (notfound == 0) {toFiltered.push_back(sto1);}
	}
	printf("tos: %d V %d\n", (int)to.size(), (int)toFiltered.size());
*/
//        string myregexit1 = "((b)*|(bb)*|(bbb)*|(bbbruuw)*|(bbbw)*|(bbg)*|(bbr)*|(bbrrru)*|(bbruu)*|(bbrwu)*|(bbu)*|(bburg)*|(bbw)*|(bbwg)*|(bg)*|(bgb)*|(bgbg)*|(bgbrggwu)*|(bgg)*|(bggbwwwg)*|(bgr)*|(bgrb)*|(bgrbg)*|(bgrggrg)*|(bgrw)*|(bgrwg)*|(bgu)*|(bguub)*|(bguwwbw)*|(bgw)*|(bgwrw)*|(br)*|(brb)*|(brg)*|(brggug)*|(brgub)*|(brgwgb)*|(brr)*|(brrb)*|(brrbbr)*|(brrw)*|(bru)*|(bruw)*|(brw)*|(brwb)*|(brwbb)*|(bu)*|(bub)*|(bubrb)*|(bug)*|(bugwu)*|(bur)*|(burbu)*|(burrrbwr)*|(buru)*|(burw)*|(buu)*|(buub)*|(buug)*|(buurw)*|(buuu)*|(buuubug)*|(buuwg)*|(buuwr)*|(buw)*|(buwggwg)*|(buwr)*|(bw)*|(bwb)*|(bwg)*|(bwgu)*|(bwgurww)*|(bwguu)*|(bwguubb)*|(bwgwguw)*|(bwr)*|(bwrbbur)*|(bwrr)*|(bwrrrgr)*|(bwrwwgg)*|(bwu)*|(bwub)*|(bwubg)*|(bwug)*|(bww)*|(bwwg)*|(bwwr)*|(bwwu)*|(gb)*|(gbb)*|(gbbb)*|(gbbr)*|(gbbwwg)*|(gbg)*|(gbgb)*|(gbggwru)*|(gbgwuub)*|(gbr)*|(gbru)*|(gbrurgg)*|(gbu)*|(gbub)*|(gbuu)*|(gbuuwwub)*|(gbw)*|(gbwruuw)*|(gbwuwbr)*|(gbwuwgg)*|(gbwwr)*|(gbwwu)*|(gg)*|(ggb)*|(ggbgru)*|(ggbuu)*|(ggbw)*|(ggg)*|(gggbgw)*|(gggrrb)*|(ggguwwb)*|(ggr)*|(ggrwr)*|(ggrwuu)*|(ggu)*|(ggur)*|(ggurwg)*|(ggw)*|(ggwb)*|(ggwr)*|(ggwu)*|(ggwugrbg)*|(ggwwg)*|(ggwww)*|(gr)*|(grb)*|(grbuw)*|(grg)*|(grgbbgg)*|(grgr)*|(grr)*|(grrbr)*|(grrgb)*|(grrru)*|(gru)*|(grubrr)*|(gruwb)*|(grw)*|(grwruug)*|(grww)*|(grwwg)*|(gu)*|(gub)*|(gubgbrww)*|(gubgr)*|(gubr)*|(gubw)*|(gug)*|(gugwgbr)*|(gugwrb)*|(gur)*|(gurb)*|(gurrb)*|(gurw)*|(guu)*|(guur)*|(guurgg)*|(guw)*|(guwbw)*|(guwgbwr)*|(guwgg)*|(guwrrbu)*|(guwu)*|(guwuuwur)*|(gw)*|(gwb)*|(gwbwg)*|(gwg)*|(gwgu)*|(gwr)*|(gwrgur)*|(gwrr)*|(gwu)*|(gwugr)*|(gww)*|(gwwburr)*|(gwwggr)*|(gwwguub)*|(r)*|(rb)*|(rbb)*|(rbbg)*|(rbbgb)*|(rbbuwu)*|(rbg)*|(rbggg)*|(rbgrg)*|(rbr)*|(rbrbuwb)*|(rbrgw)*|(rbrubbw)*|(rbrw)*|(rbrww)*|(rbu)*|(rbubuwrw)*|(rbug)*|(rbuur)*|(rbw)*|(rbwubb)*|(rbwwgrg)*|(rg)*|(rgbrg)*|(rgbugr)*|(rgbwww)*|(rgg)*|(rgggb)*|(rgr)*|(rgu)*|(rgw)*|(rgwbu)*|(rr)*|(rrb)*|(rrbgurr)*|(rrg)*|(rrgb)*|(rrgbrur)*|(rrgrbrgw)*|(rrr)*|(rrrb)*|(rrrgbg)*|(rrru)*|(rru)*|(rrubug)*|(rrugbr)*|(rrurgg)*|(rruuru)*|(rrw)*|(ru)*|(rub)*|(rubb)*|(rubbuwu)*|(rububwug)*|(rubwb)*|(rubwub)*|(rug)*|(rugbbbrb)*|(rugbww)*|(rugwg)*|(rurbb)*|(rurr)*|(ruruw)*|(ruu)*|(ruurug)*|(ruw)*|(ruwbr)*|(ruwwgww)*|(rw)*|(rwb)*|(rwbgrggb)*|(rwbuw)*|(rwg)*|(rwgruug)*|(rwr)*|(rwrrub)*|(rwrrwu)*|(rwru)*|(rwu)*|(rwugg)*|(rww)*|(rwwgwg)*|(rwwrb)*|(rwwrwuuw)*|(rwwrww)*|(u)*|(ub)*|(ubb)*|(ubbgg)*|(ubbrwugu)*|(ubg)*|(ubgu)*|(ubguwr)*|(ubgwwg)*|(ubr)*|(ubrb)*|(ubu)*|(ububbg)*|(ubug)*|(ubuub)*|(ubw)*|(ubwb)*|(ubwgwwr)*|(ug)*|(ugb)*|(ugg)*|(uggbr)*|(uggbug)*|(uggguw)*|(ugr)*|(ugrgwb)*|(ugrr)*|(ugrwbr)*|(ugu)*|(ugub)*|(uguwu)*|(ugw)*|(ugwb)*|(ugwbr)*|(ugwurbrb)*|(ur)*|(urb)*|(urbrgr)*|(urg)*|(urgu)*|(urgubwr)*|(urr)*|(urrb)*|(urru)*|(uru)*|(uruubg)*|(uruw)*|(urw)*|(urwbwg)*|(urwg)*|(urwurb)*|(urwwu)*|(uu)*|(uub)*|(uubb)*|(uubbg)*|(uubr)*|(uug)*|(uugb)*|(uugbww)*|(uugr)*|(uur)*|(uurr)*|(uurrg)*|(uuu)*|(uuur)*|(uuurrg)*|(uuurw)*|(uuuu)*|(uuw)*|(uuwbwr)*|(uuwg)*|(uuwrbu)*|(uuww)*|(uw)*|(uwb)*|(uwbb)*|(uwbrw)*|(uwg)*|(uwgbgur)*|(uwr)*|(uwrr)*|(uwru)*|(uwrwu)*|(uwrwwg)*|(uwu)*|(uwur)*|(uwuugw)*|(uwuwu)*|(uww)*|(uwwb)*|(uwwgru)*|(uwwu)*|(uwwugw)*|(uwwuwwbr)*|(w)*|(wb)*|(wbb)*|(wbbuwr)*|(wbg)*|(wbgw)*|(wbr)*|(wbrb)*|(wbrg)*|(wbrw)*|(wbrwu)*|(wbu)*|(wbuuw)*|(wbw)*|(wbwwrub)*|(wgb)*|(wgbr)*|(wgbub)*|(wgbubb)*|(wgbwb)*|(wgg)*|(wggbbbg)*|(wggbrbru)*|(wgr)*|(wgrb)*|(wgu)*|(wguwbw)*|(wgw)*|(wgwgw)*|(wgwruu)*|(wgwu)*|(wgww)*|(wgwwguwb)*|(wr)*|(wrb)*|(wrbbw)*|(wrbgbgwg)*|(wrbrrw)*|(wrbuu)*|(wrg)*|(wrgb)*|(wrgrww)*|(wrgwrwrw)*|(wrrr)*|(wrrrg)*|(wrrwwg)*|(wru)*|(wrw)*|(wrwg)*|(wrwu)*|(wrww)*|(wu)*|(wub)*|(wubgbr)*|(wubwbgr)*|(wug)*|(wugb)*|(wur)*|(wurb)*|(wurgww)*|(wurr)*|(wurwu)*|(wuu)*|(wuug)*|(wuur)*|(wuurr)*|(wuw)*|(wuwb)*|(wwb)*|(wwbb)*|(wwbbr)*|(wwbu)*|(wwggg)*|(wwgwb)*|(wwr)*|(wwubu)*|(wwugu)*|(wwugwrr)*|(www)*|(wwwbw)*|(wwwwrb)*)+";
//static constexpr auto pattern = ctll::fixed_string{ "(b*|(br)*|(bwu)*|g*|(gb)*|r*|(rb)*|(wr)*)+" };
//static constexpr auto pattern = ctll::fixed_string{ "((b)*|(bb)*|(bbb)*|(bbbruuw)*|(bbbw)*|(bbg)*|(bbr)*|(bbrrru)*|(bbruu)*|(bbrwu)*|(bbu)*|(bburg)*|(bbw)*|(bbwg)*|(bg)*|(bgb)*|(bgbg)*|(bgbrggwu)*|(bgg)*|(bggbwwwg)*|(bgr)*|(bgrb)*|(bgrbg)*|(bgrggrg)*|(bgrw)*|(bgrwg)*|(bgu)*|(bguub)*|(bguwwbw)*|(bgw)*|(bgwrw)*|(br)*|(brb)*|(brg)*|(brggug)*|(brgub)*|(brgwgb)*|(brr)*|(brrb)*|(brrbbr)*|(brrw)*|(bru)*|(bruw)*|(brw)*|(brwb)*|(brwbb)*|(bu)*|(bub)*|(bubrb)*|(bug)*|(bugwu)*|(bur)*|(burbu)*|(burrrbwr)*|(buru)*|(burw)*|(buu)*|(buub)*|(buug)*|(buurw)*|(buuu)*|(buuubug)*|(buuwg)*|(buuwr)*|(buw)*|(buwggwg)*|(buwr)*|(bw)*|(bwb)*|(bwg)*|(bwgu)*|(bwgurww)*|(bwguu)*|(bwguubb)*|(bwgwguw)*|(bwr)*|(bwrbbur)*|(bwrr)*|(bwrrrgr)*|(bwrwwgg)*|(bwu)*|(bwub)*|(bwubg)*|(bwug)*|(bww)*|(bwwg)*|(bwwr)*|(bwwu)*|(gb)*|(gbb)*|(gbbb)*|(gbbr)*|(gbbwwg)*|(gbg)*|(gbgb)*|(gbggwru)*|(gbgwuub)*|(gbr)*|(gbru)*|(gbrurgg)*|(gbu)*|(gbub)*|(gbuu)*|(gbuuwwub)*|(gbw)*|(gbwruuw)*|(gbwuwbr)*|(gbwuwgg)*|(gbwwr)*|(gbwwu)*|(gg)*|(ggb)*|(ggbgru)*|(ggbuu)*|(ggbw)*|(ggg)*|(gggbgw)*|(gggrrb)*|(ggguwwb)*|(ggr)*|(ggrwr)*|(ggrwuu)*|(ggu)*|(ggur)*|(ggurwg)*|(ggw)*|(ggwb)*|(ggwr)*|(ggwu)*|(ggwugrbg)*|(ggwwg)*|(ggwww)*|(gr)*|(grb)*|(grbuw)*|(grg)*|(grgbbgg)*|(grgr)*|(grr)*|(grrbr)*|(grrgb)*|(grrru)*|(gru)*|(grubrr)*|(gruwb)*|(grw)*|(grwruug)*|(grww)*|(grwwg)*|(gu)*|(gub)*|(gubgbrww)*|(gubgr)*|(gubr)*|(gubw)*|(gug)*|(gugwgbr)*|(gugwrb)*|(gur)*|(gurb)*|(gurrb)*|(gurw)*|(guu)*|(guur)*|(guurgg)*|(guw)*|(guwbw)*|(guwgbwr)*|(guwgg)*|(guwrrbu)*|(guwu)*|(guwuuwur)*|(gw)*|(gwb)*|(gwbwg)*|(gwg)*|(gwgu)*|(gwr)*|(gwrgur)*|(gwrr)*|(gwu)*|(gwugr)*|(gww)*|(gwwburr)*|(gwwggr)*|(gwwguub)*|(r)*|(rb)*|(rbb)*|(rbbg)*|(rbbgb)*|(rbbuwu)*|(rbg)*|(rbggg)*|(rbgrg)*|(rbr)*|(rbrbuwb)*|(rbrgw)*|(rbrubbw)*|(rbrw)*|(rbrww)*|(rbu)*|(rbubuwrw)*|(rbug)*|(rbuur)*|(rbw)*|(rbwubb)*|(rbwwgrg)*|(rg)*|(rgbrg)*|(rgbugr)*|(rgbwww)*|(rgg)*|(rgggb)*|(rgr)*|(rgu)*|(rgw)*|(rgwbu)*|(rr)*|(rrb)*|(rrbgurr)*|(rrg)*|(rrgb)*|(rrgbrur)*|(rrgrbrgw)*|(rrr)*|(rrrb)*|(rrrgbg)*|(rrru)*|(rru)*|(rrubug)*|(rrugbr)*|(rrurgg)*|(rruuru)*|(rrw)*|(ru)*|(rub)*|(rubb)*|(rubbuwu)*|(rububwug)*|(rubwb)*|(rubwub)*|(rug)*|(rugbbbrb)*|(rugbww)*|(rugwg)*|(rurbb)*|(rurr)*|(ruruw)*|(ruu)*|(ruurug)*|(ruw)*|(ruwbr)*|(ruwwgww)*|(rw)*|(rwb)*|(rwbgrggb)*|(rwbuw)*|(rwg)*|(rwgruug)*|(rwr)*|(rwrrub)*|(rwrrwu)*|(rwru)*|(rwu)*|(rwugg)*|(rww)*|(rwwgwg)*|(rwwrb)*|(rwwrwuuw)*|(rwwrww)*|(u)*|(ub)*|(ubb)*|(ubbgg)*|(ubbrwugu)*|(ubg)*|(ubgu)*|(ubguwr)*|(ubgwwg)*|(ubr)*|(ubrb)*|(ubu)*|(ububbg)*|(ubug)*|(ubuub)*|(ubw)*|(ubwb)*|(ubwgwwr)*|(ug)*|(ugb)*|(ugg)*|(uggbr)*|(uggbug)*|(uggguw)*|(ugr)*|(ugrgwb)*|(ugrr)*|(ugrwbr)*|(ugu)*|(ugub)*|(uguwu)*|(ugw)*|(ugwb)*|(ugwbr)*|(ugwurbrb)*|(ur)*|(urb)*|(urbrgr)*|(urg)*|(urgu)*|(urgubwr)*|(urr)*|(urrb)*|(urru)*|(uru)*|(uruubg)*|(uruw)*|(urw)*|(urwbwg)*|(urwg)*|(urwurb)*|(urwwu)*|(uu)*|(uub)*|(uubb)*|(uubbg)*|(uubr)*|(uug)*|(uugb)*|(uugbww)*|(uugr)*|(uur)*|(uurr)*|(uurrg)*|(uuu)*|(uuur)*|(uuurrg)*|(uuurw)*|(uuuu)*|(uuw)*|(uuwbwr)*|(uuwg)*|(uuwrbu)*|(uuww)*|(uw)*|(uwb)*|(uwbb)*|(uwbrw)*|(uwg)*|(uwgbgur)*|(uwr)*|(uwrr)*|(uwru)*|(uwrwu)*|(uwrwwg)*|(uwu)*|(uwur)*|(uwuugw)*|(uwuwu)*|(uww)*|(uwwb)*|(uwwgru)*|(uwwu)*|(uwwugw)*|(uwwuwwbr)*|(w)*|(wb)*|(wbb)*|(wbbuwr)*|(wbg)*|(wbgw)*|(wbr)*|(wbrb)*|(wbrg)*|(wbrw)*|(wbrwu)*|(wbu)*|(wbuuw)*|(wbw)*|(wbwwrub)*|(wgb)*|(wgbr)*|(wgbub)*|(wgbubb)*|(wgbwb)*|(wgg)*|(wggbbbg)*|(wggbrbru)*|(wgr)*|(wgrb)*|(wgu)*|(wguwbw)*|(wgw)*|(wgwgw)*|(wgwruu)*|(wgwu)*|(wgww)*|(wgwwguwb)*|(wr)*|(wrb)*|(wrbbw)*|(wrbgbgwg)*|(wrbrrw)*|(wrbuu)*|(wrg)*|(wrgb)*|(wrgrww)*|(wrgwrwrw)*|(wrrr)*|(wrrrg)*|(wrrwwg)*|(wru)*|(wrw)*|(wrwg)*|(wrwu)*|(wrww)*|(wu)*|(wub)*|(wubgbr)*|(wubwbgr)*|(wug)*|(wugb)*|(wur)*|(wurb)*|(wurgww)*|(wurr)*|(wurwu)*|(wuu)*|(wuug)*|(wuur)*|(wuurr)*|(wuw)*|(wuwb)*|(wwb)*|(wwbb)*|(wwbbr)*|(wwbu)*|(wwggg)*|(wwgwb)*|(wwr)*|(wwubu)*|(wwugu)*|(wwugwrr)*|(www)*|(wwwbw)*|(wwwwrb)*)+" };
//string pattern = ctll::fixed_string{ "((b)*|(br)*|(bwu)*|(g)*|(gb)*|(r)*|(rb)*|(wr)*)+" };
//int match123(std::string_view sv) noexcept;
//int match123(std::string_view sv);
/*
int match123(std::string_view sv) {
//int match123(std::string_view sv) noexcept {
//constexpr auto match123(std::string_view sv) noexcept 
    return (int)ctre::match<pattern>(sv);
}
*/
//		if (match123(sto1)) {printf("match\n"); count++;}  else {printf("not a match\n");}
