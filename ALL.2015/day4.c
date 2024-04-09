#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//////////////////////
#include <stdio.h>
#include <string.h>
#include <mbedtls/md5.h>
int num = 0;

void print_hash(unsigned char hash[16]) {
    for (int i = 0; i < 16; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}
unsigned char pass[10];

void compute_md5(const char *input) {
    unsigned char output[16]; // MD5 output is 16 bytes
    mbedtls_md5_context ctx;

    mbedtls_md5_init(&ctx);
    mbedtls_md5_starts_ret(&ctx);
    mbedtls_md5_update_ret(&ctx, (const unsigned char*) input, strlen(input));
    mbedtls_md5_finish_ret(&ctx, output);
    mbedtls_md5_free(&ctx);

    unsigned char out5[7];
    sprintf(out5, "%02x%02x%02x%02x%02x\0", output[0], output[1], output[2], output[3], output[4], output[5]);

    if (out5[0] == '0' && out5[1] == '0' && out5[2] == '0' && out5[3] == '0' && out5[4] == '0') {
    	print_hash(output);
	printf("%s\n", input);
	printf("that was password^^^^^\n");
	getchar();
	pass[num] = out5[5];
	printf("%c \n", out5[5]);
	num++;
    }
}

//////////////////////
int main(int argc, char **argv)
{
	unsigned long i = 1; 
	char buf[100];
        num = 0;
	int count = 0;
	char *input = "bgvyzdsv";
//	char *input = "abcdef";
//	char *input = "pqrstuv";
	while (1) {
		count++;

		snprintf(buf, 100, "%s%lu", input, i);
		//if (count % 1000000 == 0) {
		//	printf("Check string: %s\n", buf);
		//	printf("MD5 Hash: ");
		//}
		compute_md5(buf);
			
		if (num == 1) {break;}
		i++;
	}
	pass[8] = '\0';
	printf("***Password: %s\n", pass);
}
