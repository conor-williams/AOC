#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;
FILE *a;
#define LINE 1000
const char alpha[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

string lines[100];
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day18\n"); fflush(stdout);
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
	for (int g=1; g < leny; g++) {
		line2 = "[" + line2 + "," + lines[g] + "]";
		cout << "working on " << line2 << endl; getchar();

		int count = 0;
		int num1, num2;
		for (int i = 0; i < (int)line2.length(); i++) {
			if (line2[i] == '[') {
				count++;
			} else if (line2[i] == ']') {
				count--;
			}
			if (count >= 5 && line2[i] == '[' &&  isalpha(line2[i+1]) && line2[i+2]== ',' && isalpha(line2[i+3]) ) {

				/*
				   ||
				( isdigit(line2[i+1]) && isdigit(line2[i+2) && line2[i+3]== ',' && isdigit(line2[i+4]))  ||
				( isdigit(line2[i+1]) && line2[i+2]== ',' && isdigit(line2[i+3])  ) ) 
				*/

				//explode...
				printf("line2 pos i is %d\n", i);
				int lpos = i;
				assert(line2[i] == '[');
				assert(isalpha(line2[i+1]));
				num1 = line2[i+1]-48;
				assert(line2[i+2] == ',');
				assert(isalpha(line2[i+3]));
				num2 = line2[i+3]-48;
				assert(line2[i+4] == ']');
				int rpos = i+5;

				string subl;
				{
					string left = line2;
					subl = left.substr(0, lpos);
					reverse(subl.begin(), subl.end());
					for (int k = 0; k < (int)subl.length(); k++) {
						if (isalpha(subl[k])) {
							int sum1 = num1 + subl[k]-48;
							if (sum1 < 10) {
								subl[k] = sum1+48;
							} else {
								string tmp5 = to_string(sum1);
								subl.replace(k, 1, tmp5);
								
/*
								///split...
								int split1 = sum1/2;
								int split2 = sum1 - split1;
								// [split1,split2]
								string tmp4;
								tmp4.push_back(']');
								tmp4.push_back(split2+48);
								tmp4.push_back(',');
								tmp4.push_back(split1+48);
								tmp4.push_back('[');
								assert(tmp4.length() == 5);
								subl.replace(k, 1, tmp4);
*/
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
						if (isalpha(subr[k])) {
							int sum1 = num2 + subr[k]-48;
							if (sum1 < 10) {
								subr[k] = sum1+48;
							} else {
								string tmp5 = to_string(sum1);
								subr.replace(k, 1, tmp5);
/*
								///split
								int split1 = sum1/2;
								int split2 = sum1 - split1;
								//rev of [split1,split2]
								string tmp4;
								tmp4.push_back('[');
								tmp4.push_back(split1+48);
								tmp4.push_back(',');
								tmp4.push_back(split2+48);
								tmp4.push_back(']');
								assert(tmp4.length() == 5);
								subr.replace(k, 1, tmp4);
*/
							}
							break;
						}
					}
					cout << subr << endl;
				}
				string tmp1 = subl + "0" + subr;
				cout << "tmp1: " << tmp1 << endl;
				//strcpy(line2, tmp1.c_str()); i = -1; count = 0; continue;
				line2 = tmp1; i = -1; count = 0; continue;
			} else {
				continue;
			}
		}
		for (int k = 0; k < (int)line2.length(); k++) {
			
		cout << "Interim g:" << g << "-- line2: " << line2 << endl; getchar();

	}
}
