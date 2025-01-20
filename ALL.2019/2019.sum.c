#include <stdlib.h>
#include <stdio.h>

void main(void) {
	int ar[] = {5,4,3,2,1};


	int start = 0;

		for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
			start = start*2 + ar[j];
		}
	}
	printf("start is %lld\n", start);

////PH,*,SIG,2,+,27,26

///3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5

//long long ans = 166689759;
long long ans = 139629729;
	for (int j = 4; j >=0 ; j--) {
		for (int i = 4; i >= 0; i--) {
			ans = (ans - ar[j]) /2;
			int mod = ((ans - ar[j]))%2;
			if (mod != 0) {printf("Mod not zero...%d\n", mod);getchar();}
		}
		printf("%lld \n", ans);getchar();
	}
}
