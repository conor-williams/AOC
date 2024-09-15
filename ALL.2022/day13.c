#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <iterator>
#include <regex>
#include <iostream>
#include <string>
#include <deque>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

int compareSQ(char fir[], char sec[], int index);
string doit (int found4, string s1, string s4repl);
string ridOfEmpties(string s1);
string ridOfEmpties2(string s1);

deque <string> Q1, Q2;
int countOrder = 0;
string sA1[1000];
string sA2[1000];

std::string replaceAll(std::string str, const std::string& from, const std::string& to);
std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 13 - 1\n"); fflush(stdout);
	char line1[LINE];

	int leny = 0;
	int first = 1;
	char fir[LINE];
	char sec[LINE];
	int index = 1;
	int tot = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			first = 1;
			continue;
		} else if (first == 1) {
			first = 0;
			strcpy(fir, line1);
			continue;
		} else if (first == 0) {
			first = 1;
			strcpy(sec, line1);
			int ret1 = compareSQ(fir, sec, index);
			if (index == 46 || index == 48 || index == 82) {getchar();}
			if (ret1 == 1) {
				printf("%d\n", index);
				tot+= index;
			} else if (ret1 == 2) {
				//tot+= index;
			}
			
			index++;
		}
		leny++;
		//printf("index [%d] tot [%d]\n", index-1, tot);
	}
	fclose(a);

	printf("**ans %d\n", tot);
}

int compareSQ(char fir[], char sec[], int index) {
	//cout << "Compare:: " << fir << " " << sec << endl;

	string s0str = "],0"; string s0repl= "],[0";
	string s1str = "],1"; string s1repl= "],[1";
	string s2str = "],2"; string s2repl= "],[2";
	string s3str = "],3"; string s3repl= "],[3";
	string s4str = "],4"; string s4repl= "],[4";
	string s5str = "],5"; string s5repl= "],[5";
	string s6str = "],6"; string s6repl= "],[6";
	string s7str = "],7"; string s7repl= "],[7";
	string s8str = "],8"; string s8repl= "],[8";
	string s9str = "],9"; string s9repl= "],[9";
	string sastr = "],a"; string sarepl= "],[a";
	string s1 = fir;

/*
	s1 = replaceAll(s1, "0", "[0]");
	s1 = replaceAll(s1, "1", "[1]");
	s1 = replaceAll(s1, "2", "[2]");
	s1 = replaceAll(s1, "3", "[3]");
	s1 = replaceAll(s1, "4", "[4]");
	s1 = replaceAll(s1, "5", "[5]");
	s1 = replaceAll(s1, "6", "[6]");
	s1 = replaceAll(s1, "7", "[7]");
	s1 = replaceAll(s1, "8", "[8]");
	s1 = replaceAll(s1, "9", "[9]");
	s1 = replaceAll(s1, "a", "[a]");
*/
/*
	int pos1 = 0;
	while (pos1 != (int)string::npos) {
		if ((pos1 = s1.find("10")) != (int)string::npos) {
			s1 = s1.replace(pos1, 2, "a");
		}
		pos1 = s1.find("10");
	}
*/
		
ag1:
	//printf("herex1\n");
	{
		size_t found0 = s1.find(s0str);
		size_t found1 = s1.find(s1str);
		size_t found2 = s1.find(s2str);
		size_t found3 = s1.find(s3str);
		size_t found4 = s1.find(s4str);
		size_t found5 = s1.find(s5str);
		size_t found6 = s1.find(s6str);
		size_t found7 = s1.find(s7str);
		size_t found8 = s1.find(s8str);
		size_t found9 = s1.find(s9str);
		size_t founda = s1.find(sastr);

		int foufou1 = 0;
		if (found0 != string::npos) {
			//printf("0");
			foufou1 = 1;
			s1 = doit(found0, s1, s0repl);
		} else if (found1 != string::npos) {
			//printf("1");
			foufou1 = 1;
			s1 = doit(found1, s1, s1repl);
		} else if (found2 != string::npos) {
			//printf("2");
			foufou1 = 1;
			s1 = doit(found2, s1, s2repl);
		} else if (found3 != string::npos) {
			//printf("3");
			foufou1 = 1;
			s1 = doit(found3, s1, s3repl);
		} else if (found4 != string::npos) {
			//printf("4");
			foufou1 = 1;
			s1 = doit(found4, s1, s4repl);
		} else if (found5 != string::npos) {
			//printf("5");
			foufou1 = 1;
			s1 = doit(found5, s1, s5repl);
		} else if (found6 != string::npos) {
			//printf("6");
			foufou1 = 1;
			s1 = doit(found6, s1, s6repl);
		} else if (found7 != string::npos) {
			//printf("7");
			foufou1 = 1;
			s1 = doit(found7, s1, s7repl);
		} else if (found8 != string::npos) {
			//printf("8");
			foufou1 = 1;
			s1 = doit(found8, s1, s8repl);
		} else if (found9 != string::npos) {
			//printf("9");
			foufou1 = 1;
			s1 = doit(found9, s1, s9repl);
		} else if (founda != string::npos) {
			//printf("9");
			foufou1 = 1;
			s1 = doit(founda, s1, sarepl);
		}
		if (foufou1 == 1) {
			//cout << s1 << endl; getchar();
			goto ag1;
		}
	}
	string s2 = sec;
/*
	int pos2 = 0;
	while (pos2 != (int)string::npos) {
		if ((pos2 = s2.find("10")) != (int)string::npos) {
			s2 = s2.replace(pos1, 2, "a");
		}
		pos2 = s2.find("10");
	}
*/
ag2:
	//printf("herex2");
	{
		size_t found0 = s2.find(s0str);
		size_t found1 = s2.find(s1str);
		size_t found2 = s2.find(s2str);
		size_t found3 = s2.find(s3str);
		size_t found4 = s2.find(s4str);
		size_t found5 = s2.find(s5str);
		size_t found6 = s2.find(s6str);
		size_t found7 = s2.find(s7str);
		size_t found8 = s2.find(s8str);
		size_t found9 = s2.find(s9str);
		size_t founda = s2.find(sastr);

		int foufou2 = 0;
		if (found0 != string::npos) {
			//cout << " 0 ";
			s2 = doit(found0, s2, s0repl);
			foufou2 = 1;
		} else if (found1 != string::npos) {
			//cout << " 1 ";
			s2 = doit(found1, s2, s1repl);
			foufou2 = 1;
		} else if (found2 != string::npos) {
			//cout << " 2 ";
			s2 = doit(found2, s2, s2repl);
			foufou2 = 1;
		} else if (found3 != string::npos) {
			//cout << " 3 ";
			s2 = doit(found3, s2, s3repl);
			foufou2 = 1;
		} else if (found4 != string::npos) {
			//cout << " 4444 ";
			s2 = doit(found4, s2, s4repl);
			foufou2 = 1;
		} else if (found5 != string::npos) {
			//cout << " 5 ";
			s2 = doit(found5, s2, s5repl);
			foufou2 = 1;
		} else if (found6 != string::npos) {
			//cout << " 6 ";
			s2 = doit(found6, s2, s6repl);
			foufou2 = 1;
		} else if (found7 != string::npos) {
			//cout << " 7 ";
			s2 = doit(found7, s2, s7repl);
			foufou2 = 1;
		} else if (found8 != string::npos) {
			//cout << " 8 ";
			foufou2 = 1;
			s2 = doit(found8, s2, s8repl);
		} else if (found9 != string::npos) {
			//cout << " 9 ";
			foufou2 = 1;
			s2 = doit(found9, s2, s9repl);
		} else if (founda != string::npos) {
			//cout << " 9 ";
			foufou2 = 1;
			s2 = doit(founda, s2, sarepl);
		}
		if (foufou2 == 1) {
			//cout << s2 << endl;
			//getchar();
			goto ag2;
		}
			
	}
	s1 = replaceAll(s1, "10", "a");
	s2 = replaceAll(s2, "10", "a");

	s1 = ridOfEmpties2(s1);
	s2 = ridOfEmpties2(s2);
/*
	string s1Orig = s1;
	string s2Orig = s2;
	s1 = ridOfEmpties(s1);
	s2 = ridOfEmpties(s2);
	if (s1 != s1Orig) {printf("EMPTY\n"); return 0;}
	if (s2 != s2Orig) {printf("EMPTY\n"); return 0;}
*/
	//cout << "Rid1: " << s1 << endl;
	//cout << "Rid2: " << s2 << endl;
	
	if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {
		cout << "Compare " << s1 << " V " << s2 << endl;
	}
	if (index == 46 || index == 48 || index == 82) {
		if (s1[0] == '[' && s1[1] == '[' && s1[2] == '[' && s2[0] == '[' && s2[1] == '[' && s2[1] != '[') {
			///???	
		} 
		if (index == 46) {
			s2 = replaceAll(s2, "0", "[[0]]");
			s2 = replaceAll(s2, "1", "[[1]]");
			s2 = replaceAll(s2, "2", "[[2]]");
			s2 = replaceAll(s2, "3", "[[3]]");
			s2 = replaceAll(s2, "4", "[[4]]");
			s2 = replaceAll(s2, "5", "[[5]]");
			s2 = replaceAll(s2, "6", "[[6]]");
			s2 = replaceAll(s2, "7", "[[7]]");
			s2 = replaceAll(s2, "8", "[[8]]");
			s2 = replaceAll(s2, "9", "[[9]]");
			s2 = replaceAll(s2, "a", "[[a]]");
		} else
		
		if (index == 48) {
			s1 = replaceAll(s1, "0", "[0]");
			s1 = replaceAll(s1, "1", "[1]");
			s1 = replaceAll(s1, "2", "[2]");
			s1 = replaceAll(s1, "3", "[3]");
			s1 = replaceAll(s1, "4", "[4]");
			s1 = replaceAll(s1, "5", "[5]");
			s1 = replaceAll(s1, "6", "[6]");
			s1 = replaceAll(s1, "7", "[7]");
			s1 = replaceAll(s1, "8", "[8]");
			s1 = replaceAll(s1, "9", "[9]");
			s1 = replaceAll(s1, "a", "[a]");
		} else
		if (index == 82) {printf("here1***\n\n\n\n****"); getchar(); s2 = replaceAll(s2, "%", "#");

			cout << "s2 now: " << s2 << endl;}
			
	}
   	//regex commaDigit("([[,0-9]+\]|5[[0-9+],\[)");
   	//regex commaDigit("([[,0-9]+]|[[0-9[^\\\[]]+,\\\[)");
   	//regex commaDigit("(\\\[[0-9,]+)");
   	regex commaDigit("(\\\[[0-9a,%#]+)");
   	//regex commaDigit("[[0-9]+,\\\[");
   	//regex commaDigit("(1|2)");
   	auto c1_beg = sregex_iterator(s1.begin(), s1.end(), commaDigit);
	auto c1_end = sregex_iterator();
	int poss1 = 0;
   	for (sregex_iterator i = c1_beg; i != c1_end; ++i) {
		smatch match = *i;	
		string match_str = match.str();
		if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) { cout << "Match s1 was " << match_str << endl;}
		if (match_str[0] == '[' && match_str.length() != 1) {
			match_str.replace(0, 1, "");
/*
		} else if (match_str[0] == '[' && match_str.length() == 1) {
			//]
			match_str.replace(0, 1, "N");
*/
		} else if (match_str[(int)match_str.length()-1] == ',') {
			match_str.replace((int)match_str.length()-1, 1, "");
		}
		if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {
			cout << "Match s1: " << match_str << endl;
		}
		sA1[poss1++] = match_str;
		//Q1.push_back(match_str);
	}

   	auto c2_beg = sregex_iterator(s2.begin(), s2.end(), commaDigit);
	auto c2_end = sregex_iterator();
	int poss2 = 0;
   	for (sregex_iterator i = c2_beg; i != c2_end; ++i) {
		smatch match = *i;	
		string match_str = match.str();
		if (match_str[0] == '[') {
			match_str.replace(0, 1, "");
		}
		if (match_str[(int)match_str.length()-1] == ',') {
			match_str.replace((int)match_str.length()-1, 1, "");
		}
		if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "Match s2: " << match_str << endl;}
		sA2[poss2++] = match_str;
		//Q2.push_back(match_str);
	}
	
	
	
	int shorter = poss1 <= poss2 ? poss1 : poss2;
	for (int zzq = 0; zzq < shorter; zzq++) {
		if ((int)sA1[zzq].length() == (int)sA2[zzq].length()) { //1. lists of same length and 2) both single digits
			if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "same lengths Comparing: " << sA1[zzq] << " V " << sA2[zzq] << endl;}
			if (sA1[zzq] == sA2[zzq]) {
				if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "Equal" << endl;}
				continue;
			} else if (sA1[zzq] < sA2[zzq]) {
				if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "LESS left" << endl;}
				return 1;
			} else { //right side greater
				if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "LESS right" << endl;}
				return 2;
			}
		} else if ((int)sA1[zzq].length() != (int)sA2[zzq].length()) {
			int shorter2 = sA1[zzq].length() < sA2[zzq].length() ? sA1[zzq].length() : sA2[zzq].length();
			if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "different lengths Comparing: " << sA1[zzq] << " V " << sA2[zzq] << endl;}
			if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {printf("lents: %d V %d -> %d\n", (int)sA1[zzq].length(), (int)sA2[zzq].length(), shorter2);}
			for (int qq3 = 0; qq3 < (int)shorter2; qq3++) {
				if (sA1[zzq][qq3] == sA2[zzq][qq3]) {
					if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "Equal " << sA2[zzq][qq3] << endl;}
					continue;
				} else if (sA1[zzq][qq3] < sA2[zzq][qq3]) {
					if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "less left\n";}
					return 1;
				} else if (sA1[zzq][qq3] > sA2[zzq][qq3]) {
					if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "less right\n";}
					return 2;
				} 
			}
			if (shorter2 == (int)sA1[zzq].length()) {
				//left side ran out...
				if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "left side ran out" << endl;}
				return 1;
			} else if (shorter2 == (int)sA2[zzq].length()) {
				//right side ran out...
				if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {cout << "right side ran out" << endl;}
				return 2;
			}
		} else {
			continue;
		}
	}
	if (poss1 == poss2) {
		if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {printf("lens the same -- returning 0\n");}
		return 0;
	} else if (shorter == poss1) {
		if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {printf("L E F T ran out\n");}
		return 1;
	} else if (shorter == poss2) {
		if (index == 6 || index == 7 || index == 46 || index == 48 || index == 82) {printf("R I G H T ran out\n");}
		return 2;
	}
	return 0;
/*
	countOrder = 0;
	if (Q1.size() < Q2.size()) {
		printf("left out right order\n");
		countOrder++;
	} else if (Q1.size() > Q2.size()) {
		printf("right out wrong order\n");
	}
	assert(Q1.size() == Q2.size());
*/
	
	cout << "Leving compare..." << endl;
}
string ridOfEmpties2(string s1) {
ag:
	for (int i = 0; i < (int)s1.length(); i++) {
		if (s1[i] == '[' && s1[i+1] == ']') {
			s1.replace(i, 2, "[%]");
			goto ag;
		}
	}
	return s1;
}


string ridOfEmpties(string s1) {
ag3:
	int depth = 0;
	int first2 = 0; int findDepth = 0; int findPos = 0;
	for (int i = 0; i < (int)s1.length(); i++) {
		//looking for [[ then corresponding ]]
		//printf("depth now %d\n", depth);
		if (s1[i] == '[' && s1[i+1] == '[' && first2 == 0) { //]]
			//printf("here1\n");
			first2 = 1; findDepth = depth; findPos = i;
			//printf("found two open\n");
			//[
		} else if (s1[i] == '[') { 
			//printf("here2\n");
			depth++; 
			//[[
		} else if (s1[i] == ']' && s1[i+1] == ']' && findDepth == depth-1 && first2 == 1) {
			//printf("found two two two two closed\n");
			s1.replace(findPos, 2, "["); //][
			s1.replace(i-1, 2, "]"); 
			goto ag3;
			//[
		} else if (s1[i] == ']') {
			//printf("here4\n");
			depth--;
		}
	}
	return s1;
}

string doit (int found4, string s1, string s4repl) {
	s1.replace(found4, 3, s4repl);
	int foundx = 0; int i;
	for (i = found4 + 3; i < (int)s1.length();i++) {
		if (s1[i] == ']') {
			s1.replace(i, 1, "]]");
			foundx = 1;
			break;
		}
	}
	if (foundx == 0) {
		s1.replace(i, 1, "]");
	}
	return s1;
}
/*
   string s1 = fir;
   regex commaDigit("],[0-9]");
   auto commaDigit_begin = sregex_iterator(s1.begin(), s1.end(), commaDigit);
   auto commaDigit_end = sregex_iterator();

   for (sregex_iterator i = commaDigit_begin; i != commaDigit_end; ++i) {
   smatch match = *i;	
   string match_str = match.str();
//fir.replace
cout << "Match: " << match_str << endl;

}
 */
