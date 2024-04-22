#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//////////////////////
#include <stdio.h>
#include <string.h>
#include <mbedtls/md5.h>
char the;

void print_hash(unsigned char hash[16]) {
	for (int i = 0; i < 16; i++) {
		printf("%02x", hash[i]);
	}
	printf("\n");
}
int compute_md5(const char *input, int timerOn, int pr) {
	unsigned char output[16]; // MD5 output is 16 bytes

	mbedtls_md5_context ctx;
	mbedtls_md5_init(&ctx);
	mbedtls_md5_starts_ret(&ctx);
	mbedtls_md5_update_ret(&ctx, (const unsigned char*) input, strlen(input));
	mbedtls_md5_finish_ret(&ctx, output);
	mbedtls_md5_free(&ctx);

	unsigned char out5[50];
	//printf("ouput is %s\n", output);

	sprintf(out5, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\0", output[0], output[1], output[2], output[3], output[4], output[5], output[6], output[7], output[8], output[9], output[10], output[11], output[12], output[13], output[14], output[15]);

	if (pr == 1) { printf("out5 is %s strlen(out5) %d\n", out5, strlen(out5)); print_hash(output); if (timerOn == 1) {printf("the is %c\n", the);}}
	if (timerOn == 1) {
		for (int j = 0; j < 32-4; j++) {
			if (out5[j] == the && out5[j] == out5[j+1] && out5[j+1] == out5[j+2] && out5[j+2] == out5[j+3] && out5[j+3] == out5[j+4]) {
				return 5;
			}
		}
	} else if (timerOn == 0) {
		for (int k = 0; k < 32-2; k++) {
			if (out5[k] == out5[k+1] && out5[k+1] == out5[k+2]) {
				the = out5[k];
				if (pr == 1) { print_hash(output); printf("the is %c\n", the);}
				return 3;
			}
		}
	}
}

//////////////////////
int main(int argc, char **argv)
{
	unsigned long i = 0; 
	char buf[100];
	//char *input = "ihaygndm";
	char *input = "abc";
	int pos = 0;
	while (1) {
		if (i % 1000 == 0) {printf(" i is: %d\n", i);}
		snprintf(buf, 50, "%s%lu", input, i);
		if (compute_md5(buf, 0, 0) == 3) {
			for (int j = i+1; j < 1000+i+1; j++) {
				snprintf(buf, 50, "%s%lu", input, j);
				if (compute_md5(buf, 1, 0) == 5) {
					pos++;
					if (pos == 64) {
						printf("gotcha... @ j == %d **i is %d pos: %d\n", j, i, pos); getchar();
						printf("**** index i is %d\n", i); getchar();
					} else if (pos == 63) {
						printf("**** index i is %d\n", i); 
					} else if (pos == 65) {
						printf("**** index i is %d\n", i); getchar();
					}
				}
			}
		}
		i++;
	}
	//printf("***Password: %s\n", pass);
}
