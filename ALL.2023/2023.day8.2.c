#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;

#include <unistd.h>

#define getchar()
int nums[1000][1000];
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
vector <string> vecStarts;
vector <string> vecEnds;
struct lr {
	char left[4];
	char rite[4];
};
int gcd(unsigned long long a, unsigned long long b);
unsigned long long findlcm(vector <unsigned long long>arr, int n);
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("Day8.2\n"); fflush(stdin); fflush(stdout);
	fflush(stdout); int fd = dup(1); close(1);
	map<string, struct lr> mp;

	char line1[1000];
	char instructs[1000];
	fgets(instructs, 1000, a);
	fgets(line1, 1000, a);
	//build maps
	while (1) {
		done = 0;
		fgets(line1, 1000, a); if (feof(a)) {break;}
		one[0] = line1[0]; one[1] = line1[1]; one[2] = line1[2]; one[3] = '\0';
		string oneS = one;
		two[0] = line1[7]; two[1] = line1[8]; two[2] = line1[9]; two[3] = '\0';
		tre[0] = line1[12]; tre[1] = line1[13]; tre[2] = line1[14]; tre[3] = '\0';
		struct lr tmplr; strcpy(tmplr.left, two); strcpy(tmplr.rite, tre);
		//mp.insert({one, tmplr}); 
		mp[oneS] = tmplr;

		//printf("0: %s\n", one); cout << "oneS: " << oneS << endl; printf("1: %s\n", two); printf("2: %s\n", tre);
		//printf("FOUND: %s left: %s right: %s\n", one, mp.at(oneS).left, mp.at(oneS).rite);

	}
	fclose(a);

	for (auto it = mp.begin(); it != mp.end(); it++) {
		printf("%s\n", (*it).first.c_str());
		if ((*it).first[2] == 'A') {
			vecStarts.push_back((*it).first);
			/*char end[5];
			  end[0] = (*it).first[0];
			  end[1] = (*it).first[0];
			  end[2] = 'Z';
			  end[3] = '\0';
			  */

			//if (mp.find(end) == mp.end()) {
			//	printf("ERROR... exit"); exit(0);
			//}
			//vecEnds.push_back(end);
		}
	}
	printf("vecStarts.size is %d\n", (int)vecStarts.size());
	//assert((int)vecStarts.size() == (int)vecEnds.size());
	getchar();
	cout << "strarting parse" << endl;

	vector <unsigned long long> totsV;
	unsigned long long path = 0;
	for (int ii = 0; ii < (int)vecStarts.size(); ii++) {
		path = 0;
		string inst = vecStarts[ii];
restart:
		for (int i = 0; i < 999; i++) {
			if (instructs[i] == '\n') {
				goto restart;
			} else {
				path++;
				if (instructs[i] == 'L') {
					inst = (string)mp.at(inst).left;
				} else {
					inst = (string)mp.at(inst).rite;
				}
				if (inst[2] == 'Z') {
					printf("END: (%s) -> (%s) %llu\n",
							vecStarts[ii].c_str(), inst.c_str(), path);
					totsV.push_back(path);
					break;
				} 
			}
		}
	}
	sort (totsV.begin(), totsV.end());
	auto it10 = unique(totsV.begin(), totsV.end());
	totsV.resize(distance(totsV.begin(), it10));
	unsigned long long totsMul = 1;
	/*
	   printf("totsV.size() %d\n", (int)totsV.size());
	   for (auto oneOf: totsV) {
	   totsMul *= oneOf;
	   }
	   for (auto oneOf: totsV) {
	   if (totsMul % oneOf == 0) {
	   totsMul /= oneOf;
	   }
	   }
	   */

	totsMul = 0;
	printf("%llu\n", totsMul = findlcm(totsV, (int)totsV.size()));
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", totsMul);

}
int gcd(unsigned long long a, unsigned long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

// Returns LCM of array elements
unsigned long long findlcm(vector <unsigned long long>arr, int n)
{
	// Initialize result
	unsigned long long ans = arr[0];

	// ans contains LCM of arr[0], ..arr[i]
	// after i'th iteration,
	for (int i = 1; i < n; i++)
		ans = (((arr[i] * ans)) /
				(gcd(arr[i], ans)));

	return ans;
}
/*
   for(mit = totsV.begin(); mit != totsV.end(); )
   {   if(condition)
   mit = myVec.erase(mit);
   else
   mit++;
   }
   */
