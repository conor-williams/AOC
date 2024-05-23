#include <stdio.h>
#include <stdlib.h>

unsigned long long z1 = 10551350;
int main(void) {
	unsigned long long tot = 0;
	for (int z = 1; z <= z1; z++) {
		if (z1 % z == 0) {
			tot = z + tot;
			printf("%llu * %llu\n", z, z1/z);
		}

	}
	printf("tot is %llu\n", tot);
}
