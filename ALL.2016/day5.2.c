#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>
//compile with:  -lmbedcrypto
#define getchar()
//////////////////////
#include <stdio.h>
#include <string.h>
#include <mbedtls/md5.h>
int num = 0;
int posAlready[10] = {0};

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

    char out5[30];
    sprintf(out5, "%02x%02x%02x%02x%02x%2x%2x", output[0], output[1], output[2], output[3], output[4], output[5], output[6]);

    if (out5[0] == '0' && out5[1] == '0' && out5[2] == '0' && out5[3] == '0' && out5[4] == '0') {
	int o55 = out5[5] - 48;
    	//print_hash(output);
	//pass[num] = out5[5];
	//int found = 0;
	if (o55 <= 7 && posAlready[o55] == 0) {
	    ///printf("%c \n", out5[6]);
	    ///printf("GOT %d\n", o55);
	    pass[o55] = out5[6];
	    posAlready[o55] = 1;
	    num++;
        }
    }
}

//////////////////////
int main(int argc, char **argv)
{
	unsigned long i = 0; 
	char buf[100];
        num = 0;
	printf("SLOW ~30seconds\n");
	printf("2016 day5.2\n");
	fflush(stdout); int fd = dup(1); close(1);
	int count = 0;
	char *input = "ojvtpuvg";
//	char *input = "abc";
	while (1) {
		count++;

		snprintf(buf, 100, "%s%lu", input, i);
		//if (count % 1000000 == 0) {
		//	printf("Check string: %s\n", buf);
		//	printf("MD5 Hash: ");
		//}
		compute_md5(buf);
			
		if (num == 8) {break;}
		i++;
	}
	pass[8] = '\0';
	dup2(fd, 1);
	printf("***Password: %s\n", pass);
}
