#include <bits/stdc++.h>
// tribulu
using namespace std;
int sum[301][301];
int input = 3613;
signed main() {
	printf("		2018 Day11 part2\n");
	int bx, by, bs, best = INT_MIN;
	for(int y = 1; y <= 300; y++) {
		for(int x = 1; x <= 300; x++) {
			int id = x + 10;
			int p = id * y + input;
			p = (p * id) / 100 % 10 - 5;
			sum[y][x] = p + sum[y - 1][x] + sum[y][x - 1] - sum[y - 1][x - 1];
		}
	}
	for(int s = 1; s <= 300; s++) {
		for(int y = s; y <= 300; y++) {
			for(int x = s; x <= 300; x++) {
				int total = sum[y][x] - sum[y - s][x] - sum[y][x - s] + sum[y - s][x - s];
				if(total > best) {
					best = total, bx = x, by = y, bs = s;
				}
			}
		}
	}
	//cout << bx - bs + 1 << "," << by - bs + 1 << "," << bs << endl;
	printf("**ans: %d,%d,%d\n", bx-bs+1 , by-bs+1, bs);
	return 0;
}
