#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <algorithm>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;


int lenx, leny;
#define DAY "		2015 day15 part2\n"
#define _DEBUG_

int tot = 0;
struct vals {
	int num;
	char what[30];
	int cap;
	int dur;
	int fla;
	int tex;
	int cal;
};
map <int, struct vals> mp;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[200];
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	char what[30]; int cap; int dur; int fla; int tex; int cal;
	sscanf(line1, "%s capacity %d, durability %d, flavor %d, texture %d, calories %d", 
		what, &cap, &dur, &fla, &tex, &cal);
	struct vals tmp;
	tmp.num = leny;
	strcpy(tmp.what, what);
	tmp.cap = cap;
	tmp.dur = dur;
	tmp.fla = fla;
	tmp.tex = tex;
	tmp.cal = cal;
	printf("%d\n", tmp.tex);
	mp.insert({leny, tmp});
	leny++;
	
}
fclose(a);
/*
Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3
*/
/*
	int tot = 0;
	unsigned long long max = 0;
	for (int a = 1; a < 100; a++) {
		int b = 100 -a;
		{

				int captot = mp[0].cap *a + mp[1].cap *b;
				int durtot = mp[0].dur *a + mp[1].dur *b;
				int flatot = mp[0].fla *a + mp[1].fla *b;
				int textot = mp[0].tex *a + mp[1].tex *b;
				int caltot = mp[0].cal *a + mp[1].cal *b;
				if (captot < 0) {captot = 0;}
				if (durtot < 0) {durtot = 0;}
				if (flatot < 0) {flatot = 0;}
				if (textot < 0) {textot = 0;}
				if (caltot < 0) {caltot = 0;}
				unsigned long long ans = captot * durtot * flatot * textot;
				if (caltot == 500) {printf("%d %d %d %d (%llu)\n", a, b, c, d, ans);}
				if (ans > max) {max = ans;}
					

		}
	}
*/
	unsigned long long max = 0;
	for (int a = 1; a < 98; a++) {
		for (int b = 1; b < 100 -a; b++) {
			for (int c = 1; c < 100 -b -a ; c++) {
				int d = 100 -a -b -c;

				int captot = mp[0].cap *a + mp[1].cap *b + mp[2].cap *c + mp[3].cap * d;
				int durtot = mp[0].dur *a + mp[1].dur *b + mp[2].dur *c + mp[3].dur * d;
				int flatot = mp[0].fla *a + mp[1].fla *b + mp[2].fla *c + mp[3].fla * d;
				int textot = mp[0].tex *a + mp[1].tex *b + mp[2].tex *c + mp[3].tex * d;
				int caltot = mp[0].cal *a + mp[1].cal *b + mp[2].cal *c + mp[3].cal * d;
				if (captot < 0) {captot = 0;}
				if (durtot < 0) {durtot = 0;}
				if (flatot < 0) {flatot = 0;}
				if (textot < 0) {textot = 0;}
				if (caltot < 0) {caltot = 0;}
				unsigned long long ans = captot * durtot * flatot * textot;
				if (caltot == 500) {printf("%d %d (%llu)\n", a, b, ans);}
				if (caltot == 500 && ans > max) {max = ans;}
					

			}
		}
	}

	printf("***max %llu\n", max); fflush(stdout);
	fflush(stdout); dup2(fd, 1);
	printf("***ans: %llu\n", max); fflush(stdout);
}
