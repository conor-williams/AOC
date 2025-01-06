#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

#include <unistd.h>

#define getchar()
#define getchar()
using namespace std;
FILE *a;
#define LINE 1000
const char alfa[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int getalfa(char alf);
int isalfa(char alf);
int getPlaceHolder(char alf);
int placeHolder[65];
int placeHolderPos = 0;
string lines[100];
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day18.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	char line1[LINE];
	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		lines[leny] = line1;
		leny++;
	}
	fclose(a);

	string line2 = lines[0];	
if (argc != 3) {
	for (int g=1; g < leny; g++) {
		line2 = "[" + line2 + "," + lines[g] + "]";
		cout << "working on " << line2 << endl; getchar();

		int num1, num2;
explode:
		int count = 0;
		for (int i = 0; i < (int)line2.length(); i++) {
			if (line2[i] == '[') {
				count++;
			} else if (line2[i] == ']') {
				count--;
			}
			if (count >= 5 && line2[i] == '[' &&  isalfa(line2[i+1]) && line2[i+2]== ',' && isalfa(line2[i+3]) ) {
				//explode...
				printf("line2 pos i is %d\n", i);
				int lpos = i;
				assert(line2[i] == '[');
				assert(isalfa(line2[i+1]));
				num1 = getalfa(line2[i+1]);
				assert(line2[i+2] == ',');
				assert(isalfa(line2[i+3]));
				num2 = getalfa(line2[i+3]);
				assert(line2[i+4] == ']');
				int rpos = i+5;

				string subl;
				{
					string left = line2;
					subl = left.substr(0, lpos);
					reverse(subl.begin(), subl.end());
					for (int k = 0; k < (int)subl.length(); k++) {
						if (isalfa(subl[k])) {
							int sum1 = num1 + getalfa(subl[k]);
							assert(sum1 < 62);
							if (sum1 < 10) {
								subl[k] = sum1+48;
							} else {
								assert(sum1 < 62);
								subl[k] = alfa[sum1];
								//subl.replace(k, 1, alfa[sum1]);
							}
							break;
						}
					}
					reverse(subl.begin(), subl.end());
					cout << subl << endl;
				}
				string subr;
				{
					string right = line2;
					subr = right.substr(rpos, (int)line2.length()-1);
					for (int k = 0; k < (int)subr.length(); k++) {
						if (isalfa(subr[k])) {
							int sum1 = num2 + getalfa(subr[k]);
							assert(sum1 < 62);
							if (sum1 < 10) {
								subr[k] = sum1+48;
							} else {
								assert(sum1 < 62);
								//string tmp5 = to_string(sum1);
								subr[k] = alfa[sum1];
								//subr.replace(k, 1, alfa[sum1]);
							}
							break;
						}
					}
					cout << subr << endl;
				}
				string tmp1 = subl + "0" + subr;
				cout << "tmp1: " << tmp1 << endl;
				line2 = tmp1; i = -1; count = 0; continue;
			} else {
				continue;
			}
		}

		for (int k = 0; k < (int)line2.length(); k++) {
			if (isalfa(line2[k])) {
				int sum1 = getalfa(line2[k]);
				assert(sum1 < 62);
				if (sum1 >= 10) {
					int pos = sum1/2;
					char split1 = alfa[pos];
					char split2 = alfa[sum1 - pos];
					// [split1,split2]
					string tmp4;
					tmp4.push_back('[');
					tmp4.push_back(split1);
					tmp4.push_back(',');
					tmp4.push_back(split2);
					tmp4.push_back(']');
					assert(tmp4.length() == 5);
					line2.replace(k, 1, tmp4);
					goto explode;
				}
			}
		}
					
		cout << "Interim g:" << g << "-- line2: " << line2 << endl; getchar();
	}
    }
	for (int i = 0; i < (int)line2.length(); i++) {
		if (isdigit(line2[i])) {
			placeHolder[placeHolderPos] = line2[i]-48;
			line2[i] = alfa[placeHolderPos];
			placeHolderPos++;
			if (placeHolderPos > 62) { perror("TOOMANY"); exit(0);}
		}
	}

	cout << "line2: " << line2 << endl;
	for (int i = 0; i < placeHolderPos; i++) {
		printf("%d\n", placeHolder[i]);
	}
	printf("---\n");
again:
	for (int i = 0; i < (int)line2.length(); i++) {
		if (line2[i] == '[' &&  isalfa(line2[i+1]) && line2[i+2]== ',' && isalfa(line2[i+3]) ) {
			int sum1 = 3*getPlaceHolder(line2[i+1]) + 2*(getPlaceHolder(line2[i+3])); 
			cout << "sum1: " << sum1 << endl;
			placeHolder[getalfa(line2[i+1])] = sum1;
			string tmp4;
			tmp4.push_back(line2[i+1]);
			line2.replace(i, 5, tmp4);
			goto again;
			
		}
	}
	printf("===========\n");
	cout << "line2: " << line2 << endl;
	for (int i = 0; i < placeHolderPos; i++) {
		printf("%d\n", placeHolder[i]);
	}
	printf("-------\n");
	for (int i = 0; i < (int)line2.length(); i++) {
		printf("i:%d %c\n", i, line2[i]);
		if (isalfa(line2[i])) {
			printf("line2[i]: %c isalfa: %d\n", line2[i], isalfa(line2[i]));
			cout << "**ans: " << getPlaceHolder(line2[i]) << endl;

			fflush(stdout); dup2(fd, 1);
			printf("**ans: %d\n", getPlaceHolder(line2[i]));
			exit(0);
		}
	}

}
int getPlaceHolder(char alf) {
	int pos = getalfa(alf);
	return placeHolder[pos];
}
int isalfa(char alf) {
	for (int i = 0; i < 62; i++) {
		if (alf == alfa[i]) {
			return 1;
		}
	}
	return 0;
}
	
int getalfa(char alf) {
	int found = 0;
	for (int i = 0; i < 62; i++) {
		if (alf == alfa[i]) {
			found = 1;
			return i;
		}
	}
	if (found == 0) {printf("%c", alf); perror("ERR"); exit(0);}
	return 0;
}
