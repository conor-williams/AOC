#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
#define getchar()
#define LINE 200
char* lltoa(long long val, int base){

	static char buf[64] = {0};

	int i = 62;
	int sign = (val < 0);
	if(sign) val = -val;

	if(val == 0) {return "0";}

	for(; val && i ; --i, val /= base) {
		buf[i] = "0123456789abcdef"[val % base];
	}

	if(sign) {
		buf[i--] = '-';
	}
	return &buf[i+1];

}
int main(int argc, char **argv) {
	printf("2022 Day 25 Part 1\n"); fflush(stdout);
#ifdef _ACCOLADE_
	printf("thank you java (openjdk-23.0.2) + codeconvert.ai\n");
#endif
	int fd = dup(1); close(1);
	FILE *a;
	a = fopen(argv[1], "r");
	std::vector<std::string> blah;
	char line1[LINE];
	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		blah.push_back(line1);
		leny++;
	}
	fclose(a);

	long long totOfNums = 0;
	for (size_t i = 0; i < blah.size(); i++) {
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		long long thisNum = 0;
		for (int z = blah[i].length() - 1; z >= 0; z--) {
			long long po = static_cast<long long>(blah[i].length() - 1 - z);
			long long sz = static_cast<long long>(std::pow(5, po));
			long long num = 0;
			switch (blah[i][z]) {
				case '2':
					num = 2;
					break;
				case '1':
					num = 1;
					break;
				case '0':
					num = 0;
					break;
				case '-':
					num = -1;
					break;
				case '=':
					num = -2;
					break;
				default:
					break;
			}
			thisNum += sz * num;
		}
		std::cout << "+ " << thisNum << std::endl;
		totOfNums += thisNum;
	}
	printf("totOfNums is %lld\n", totOfNums);
	string b5 = lltoa(totOfNums, 5);
	printf("%s\n", b5.c_str());

	string newVal = b5;
	for (int kk = (int)b5.length()-1; kk >= 0; kk--) {
		if (b5[kk] == '5') {
			newVal[kk] = '0';
			b5[kk-1] = 48+b5[kk-1]-47;
		} else if (b5[kk] == '4') {
			newVal[kk] = '-';
			b5[kk-1] = 47+b5[kk-1]-46;
		} else if (b5[kk] == '3') {
			newVal[kk] = '=';
			b5[kk-1] = 46+b5[kk-1]-45;
		} else {
			newVal[kk] = b5[kk];
		}

	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %s\n", newVal.c_str());
}
