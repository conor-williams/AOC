#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <unistd.h>
///#define assert(asf)
//#define getchar()
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>


using namespace std;

int findCorrespondingEndCurl(string &ss1, int rPos);
int findCorrespondingEndSqr(string &ss1, int rPos);
int findCurlToTheLeft(string &ss1, int rPos);
int findSqrToTheLeft(string &ss1, int rPos);

struct hash_function
{
	size_t operator()(const tuple<int , int , int, int>&x) const
	{
		unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 37; hash += get<2>(x); hash *= 37; hash += get<3>(x); return hash;
	}
};


FILE *a;
#define LINE 28000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

int main(int argc, char **argv)
{
	clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); if (a == NULL) {printf("BAD file %s\n", argv[1]); exit(0);}
	printf("2015 Day 12 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		leny++;

		string ss = line1;
		//int len = ss.length();
		size_t pos;
		//if first open to the left is { then blank from there to next }
		//if the first open to the left is [ then just change red to QQQ
		while ((pos = ss.find("red")) != string::npos) {
			size_t redPos = pos;
			int curlPos = findCurlToTheLeft(ss, redPos);
			int sqrPos = findSqrToTheLeft(ss, redPos);
			//size_t curlPos = ss.rfind("{", redPos);
			//size_t sqrPos = ss.rfind("[", redPos);
			//printf("curlPos > sqrPos: %d\n", (int)curlPos > (int)sqrPos);
			//printf("curlPos %d V %d sqrPos\n", (int)curlPos, (int)sqrPos);
			//printf("sqrPos %d\n", sqrPos);
			if ((int)curlPos != -1) {
			       	if ((int)curlPos > sqrPos) {
					//printf("curlPos %d V %d sqrPos\n", (int)curlPos, (int)sqrPos);
					int curlEndPos = findCorrespondingEndCurl(ss, (int)redPos);
					//size_t curlEndPos = ss.find("}", redPos);
					//printf("XXX%s\n", ss.substr(curlPos, curlEndPos-curlPos+1).c_str());
					ss.replace(curlPos, curlEndPos-curlPos+1, curlEndPos-curlPos+1, 'b');
				} else {
					int sqrEndPos = findCorrespondingEndSqr(ss, (int)redPos);
					printf("SQR%s\n", ss.substr(sqrPos, sqrEndPos-sqrPos+1).c_str());
					ss.replace(redPos, 3, "QQQ");		
					
				}

			} else {
				//printf("here2...\n");
				int sqrEndPos = findCorrespondingEndSqr(ss, (int)redPos);
				printf("SQR%s\n", ss.substr(sqrPos, sqrEndPos-sqrPos+1).c_str());
				ss.replace(redPos, 3, "QQQ");		
			}
			//printf("curlPos %d V %d sqrPos\n", (int)curlPos, (int)sqrPos);
		}
		//getchar();
		printf("ss: %s\n", ss.c_str());

		int tot = 0;
		strcpy(line1, ss.c_str());
		char line2[LINE];
		
                for (int i = 0; i < (int)strlen(line1); i++) {
                        if (isdigit(line1[i]) || line1[i] == '-') {line2[i] = line1[i];}
                        else {line2[i] = ',';}
                }
                line2[(int)strlen(line1)] = '\0';
                char *fir = strtok(line2, ",");
		if (fir != NULL) {
			do {
       	                	if (fir[0] == '\0') {continue;} else {tot+=atoi(fir);}
			} while ((fir = strtok(NULL, ",")) != NULL);
		}
		//printf("l2: %s\n", line2);
		fflush(stdout); dup2(fd, 1);
		printf("**ans: %d\n", tot);
		close(1); 
		//printf("tot for this line %d\n", tot);

		//printf("ss: %s\n", ss.c_str());
		
	}
	fclose(a);

}
int findCurlToTheLeft(string &ss1, int rPos) {
	int countOfCurls = 0;
	for (int ii = rPos; ii >= 0; ii--) {
		if (ss1[ii] == '{') {
			countOfCurls++;
		} else if (ss1[ii] == '}') {
			countOfCurls--;
		}
		if (countOfCurls == 1 && ss1[ii] == '{') {
			return ii;
		}
		/*
		if (countOfCurly == 0 && ss1[ii] == '{') {
			return ii;
		} else if (ss1[ii] == '{') {
			countOfCurly++;
		} else if (ss1[ii] == '}') {
			countOfCurly--;
		}
		*/
	}
	//not found
	return -1;
}
int findSqrToTheLeft(string &ss1, int rPos) {
	int countOfSqr = 0;
	for (int ii = rPos; ii >= 0; ii--) {
		if (ss1[ii] == '[') {
			countOfSqr++;
		} else if (ss1[ii] == ']') {
			countOfSqr--;
		}
		if (countOfSqr == 1 && ss1[ii] == '[') {
			return ii;
		}
		/*
		if (countOfSqr == 0 && ss1[ii] == '[') {
			return ii;
		} else if (ss1[ii] == '[') {
			countOfSqr++;
		} else if (ss1[ii] == '}') {
			countOfSqr--;
		}
		*/
	}
	//not found
	return -1;
}

int findCorrespondingEndSqr(string &ss1, int rPos)
{
	int len1 = ss1.length();
	int countOfCurly = 0;
	for (int ii = rPos ; ii < len1; ii++) {
		if (ss1[ii] == ']' && countOfCurly == 0) {
			return ii;
		} else if (ss1[ii] == '[') {
			countOfCurly++;
		} else if (ss1[ii] == ']') {
			countOfCurly--;
		}
	}
	return len1-1;
}
int findCorrespondingEndCurl(string &ss1, int rPos)
{
	int len1 = ss1.length();
	int countOfCurly = 0;
	for (int ii = rPos ; ii < len1; ii++) {
		if (ss1[ii] == '}' && countOfCurly == 0) {
			return ii;
		} else if (ss1[ii] == '{') {
			countOfCurly++;
		} else if (ss1[ii] == '}') {
			countOfCurly--;
		}
	}
	return len1-1;
}
