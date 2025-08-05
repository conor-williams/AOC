#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <string>

using namespace std;

#define getchar()
int lenx, leny;
#define DAY "		2015 day11 part2\n"

int tot = 0;
#define SIZE 200
int secondOne = 0;
void incrementString(std::string &str);
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); //close(1);


	char line1[SIZE];
	char in[20]; // = "hepxcrrq";
		     //	char in[] = "hepxxyzz";
		     //int inI[] = {(int)'h', (int) 'e', (int) 'p', (int) 'x', (int) 'c', (int) 'r', (int) 'r', (int) 'q'};
	while(1) {
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		strcpy(in, line1);
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
	}
	//fclose(a);


	string s(in);

	string ans = "";
	int go = 0;
	while (true) {
		incrementString(s);
		int found = 0;
		for (int ii = 0; ii < s.length()-2; ii++) {
			char ch = s[ii];
			if (s[ii+1] == ch+1 && s[ii+2] == ch+2) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			///notgood
			continue;
		}
		found = 0;
		for (int ii = 0; ii < s.length(); ii++) {
			if (s[ii] == 'i' || s[ii] == 'o' || s[ii] == 'l') {
				found = 1;
				break;
			}
		}
		if (found == 1) {
			//notgood
			continue;
		}
		found = 0;
		for (char ch = 'a'; ch <= 'z'; ch++) {
			for (int ii = 0; ii < s.length()-1; ii++) {
				if (s[ii] == ch && s[ii+1] == ch) {
					found++;
					break;
				}
			}
		}
		if (found >= 2) {
			if (go == 1) {
				ans = s;
				break;
			} else {
				go = 1;
			}
			//good
		} else {
			continue;
		}
	}

	//              System.setOut(originalOut);
	printf("**ans: ");
	printf("%s", ans.c_str());
	printf("\n");

}
void incrementString(std::string &str) {
	for (int i = str.size() - 1; i >= 0; --i) {
		if (str[i] == 'z') {
			str[i] = 'a';  // Wrap around for lowercase letters
		} else if (std::isalpha(str[i])) {
			str[i]++;  // Increment the character
			return;    // Stop once increment is done
		} else {
			// Handle non-alphabetic characters if needed
			str[i]++;
			return;
		}
	}
}

