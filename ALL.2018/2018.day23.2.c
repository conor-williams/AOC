#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <queue>

#define getchar()
#undef _DEBUG_
#define SIZE 100

using namespace std;
char line1[SIZE];
unsigned long tot = 0;
struct xyzr_s {
	long long x1;
	long long y1;
	long long z1;
	long long r1;
};
int maxBeacons = 0;

long long mx1;
long long my1;
long long mz1;
struct xyzr_s xyzr[1010];
int leny = 0;
int fd;
struct Compare {
	bool operator()(const pair<long, long>& a, const pair<long, long>& b) {
		return a.first > b.first;
	}
};
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day23.2\n"); fflush(stdout);
	fd = dup(1);// close(1);

	leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		sscanf(line1, "pos=<%lld,%lld,%lld>, r=%lld", &xyzr[leny].x1, &xyzr[leny].y1,
				&xyzr[leny].z1, &xyzr[leny].r1);
		leny++;
	}
	fclose(a);
	//printit();
	priority_queue<pair<long, long>, vector<pair<long, long>>, Compare> Q;
	for (int i = 0; i < leny; i++) {
		long d = abs(xyzr[i].x1) + abs(xyzr[i].y1) + abs(xyzr[i].z1);
		long max = 0L > d-xyzr[i].r1 ? 0L : d-xyzr[i].r1;
		Q.push(make_pair(max, 1L));
		Q.push(make_pair(d + xyzr[i].r1 + 1, -1L));
	}

	long count = 0;
	long maxCount = 0;
	long result = 0;
	while (!Q.empty()) {
		//pair<long, long> current = (pair<long, long>)Q.pop();
		auto current = Q.top();
		Q.pop();
		count += current.second;
		if (count > maxCount) {
			result = current.first;
			maxCount = count;
		}
	}
	printf("**ans: ");
	printf("%ld\n", result);
}


