#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;

map <string, int> mp;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day8.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[3000];

int leny = 0;
int max = 0;
while (1) 
{
        fgets(line1, 3000, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
 	line1[strlen(line1)-1] = '\0';
	char reg1[10]; int by=0; int ret; char reg2[10]; char op[10]; int X;
	string r1, r2;
        ret = sscanf(line1, "%s inc %d if %s %s %d", reg1, &by, reg2, op, &X);
	if (ret == 5) {
		r1 = reg1; r2 = reg2;
		if (mp.find(r1) == mp.end()) {mp.insert({r1, 0});} 
		if (mp.find(r2) == mp.end()) {mp.insert({r2, 0});} 

		if (op[0] == '>' && op[1] == '=') {
			if (mp[r2] >= X) {mp[r1] += by;}
		} else if (op[0] == '<' && op[1] == '=') {
			if (mp[r2] <= X) {mp[r1] += by;}
		} else if (op[0] == '=' && op[1] == '=') {
			if (mp[r2] == X) {mp[r1] += by;}
		} else if (op[0] == '!' && op[1] == '=') {
			if (mp[r2] != X) {mp[r1] += by;}
		} else if (op[0] == '<') {
			if (mp[r2] < X) {mp[r1] += by;}
		} else if (op[0] == '>') {
			if (mp[r2] > X) {mp[r1] += by;}
		} else {
			printf("ERROR2\n"); exit(0);
		}

		printf("inc+ %d [%s]\n", by, reg2);
	} else {
	        ret = sscanf(line1, "%s dec %d if %s %s %d", reg1, &by, reg2, op, &X);
		if (ret == 5) {
			r1 = reg1; r2 = reg2;
			if (mp.find(r1) == mp.end()) {mp.insert({r1, 0});} 
			if (mp.find(r2) == mp.end()) {mp.insert({r2, 0});} 

			if (op[0] == '>' && op[1] == '=') {
				if (mp[r2] >= X) {mp[r1] -= by;}
			} else if (op[0] == '<' && op[1] == '=') {
				if (mp[r2] <= X) {mp[r1] -= by;}
			} else if (op[0] == '=' && op[1] == '=') {
				if (mp[r2] == X) {mp[r1] -= by;}
			} else if (op[0] == '!' && op[1] == '=') {
				if (mp[r2] != X) {mp[r1] -= by;}
			} else if (op[0] == '<') {
				if (mp[r2] < X) {mp[r1] -= by;}
			} else if (op[0] == '>') {
				if (mp[r2] > X) {mp[r1] -= by;}
			} else {
				printf("ERROR3\n"); exit(0);
			}

			printf("%s dec %d iiifff [%s] %s %d\n", reg1, by, reg2, op, X);
		} else {
			printf("ERROR"); exit(0);
		}
	}
	leny++;
}
	for (auto iter = mp.begin(); iter !=  mp.end(); iter++) {
		if (iter->second> max) {max = iter->second;}
	}

	dup2(fd, 1);
	printf("***max %d\n", max);
}

