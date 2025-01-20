#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <mbedtls/md5.h>

#include <unistd.h>
// compile: -Wl,--stack,999777666
#define getchar()
int lenx, leny;
#define DAY "2016 day17 part2 \n"
#define _DEBUG_
long tot;
#define SIZE 50
#define SZ 20
char grid[SZ][SZ] = {
	{"######"},
	{"#    #"},
	{"#    #"},
	{"#    #"},
	{"#   V "},
	{"######"}
};
void next(int x, int y, int steps, char dir, char*in);
char out5[50];
//int already[SZ][SZ];
char ans[10000][4000];
int ansPos = 0;

void print_hash(unsigned char hash[16]) {
	for (int i = 0; i < 16; i++) {
		printf("%02x", hash[i]);
	}
	printf("\n");
}
int compute_md5(const char *input) {
	unsigned char output22[100]; // MD5 output is 16 bytes

	mbedtls_md5_context ctx;
	mbedtls_md5_init(&ctx);
	mbedtls_md5_starts_ret(&ctx);
	mbedtls_md5_update_ret(&ctx, (const unsigned char*) input, strlen(input));
	mbedtls_md5_finish_ret(&ctx, output22);
	mbedtls_md5_free(&ctx);


	sprintf(out5, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", output22[0], output22[1], output22[2], output22[3], output22[4], output22[5], output22[6], output22[7], output22[8], output22[9], output22[10], output22[11], output22[12], output22[13], output22[14], output22[15]);

	//printf("out5 is %s\n", out5);
	return 0;
}


int main(int argc, char **argv)
{
	char line1[SIZE];
	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	while(1) 
	{
		ansPos = 0;
		/*
		   for (int y = 0; y < SZ; y++) {
		   for (int x = 0; x < SZ; x++) {
		   already[y][x] = -1;
		   }
		   }
		 */
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
		char buf[200];
		sprintf(buf, "%s", line1);
		compute_md5(buf);
		char out7[200];
		strcpy(out7, out5);
		//printf("out7: %s\n", out7);
		int sx = 1; int sy = 1;
		//already[sy][sx] = 0;
		for (int i = 0; i < 4; i++) {
			if (out7[i] == 'b' || out7[i] == 'c' || out7[i] == 'd' || out7[i] == 'e' || out7[i] == 'f') {
				switch (i) {
					case 0: //UP
						//printf("FIRST UP [%s]\n", line1);
						next(sx, sy-1, 0, 'U', (char *)line1);
						break;
					case 1: //DOWN
						//printf("FIRST DOWN [%s]\n", line1);
						next(sx, sy+1, 0, 'D', (char *)line1);
						break;
					case 2: //LEFT
						//printf("FIRST LEFT [%s]\n", line1);
						next(sx-1, sy, 0, 'L', (char *)line1);
						break;
					case 3: //RIGHT
						//printf("FIRST RIGHT [%s]\n", line1);
						next(sx+1, sy, 0, 'R', (char *)line1);
						break;
				}
				//door open
			} else {
				//door locked
			}
		}
		if (ansPos > 0) {
			int max = 0; int maxPos = 0;
			for (int i = 0; i < ansPos; i++) {
				if ((int)strlen(ans[i]) > max) {max = (int)strlen(ans[i]); maxPos = i;}
			}

			//printf("**max is %s LEN: %d\n", ans[maxPos], (int)strlen(ans[maxPos]) - (int)strlen(line1));
			fflush(stdout); dup2(fd, 1);
			printf("**ans: %d\n", (int)strlen(ans[maxPos]) - (int)strlen(line1));
			exit(0);
		} else {
			printf("no ans...\n");
		}
		leny++;
	}
	fclose(a);
	tot = 0;

	printf("***tot %ld END\n", tot); fflush(stdout);
} 
void next(int x, int y, int steps, char dir, char *in) {


	if (grid[y][x] == '#') {
		//printf("wall\n");
		return;
	} else if (grid[y][x] == ' ') {
		//printf("SPACE\n");
		//printf("already[y][x] is %d\n", already[y][x]); getchar();
		//if (already[y][x] > steps+1 || already[y][x] == -1) {
		{

			//already[y][x] = steps+1;
			char buf[4000];
			sprintf(buf, "%s%c", in, dir);
			//if (strlen(buf) > 190) {return;}
			//printf("buf is %s in is %s\n", buf, in);
			compute_md5(buf);
			char out6[50];
			strcpy(out6, out5);
			//printf("out6 is %s\n", out6);
			for (int i = 0; i < 4; i++) {
				if (out6[i] == 'b' || out6[i] == 'c' || out6[i] == 'd' || out6[i] == 'e' || out6[i] == 'f') {
					//door open
					switch (i) {
						case 0: //UP
							//printf("UP ");
							next(x, y-1, steps+1, 'U', buf);
							break;
						case 1: //DOWN
							//printf("DOWN ");
							next(x, y+1, steps+1, 'D', buf);
							break;
						case 2: //LEFT
							//printf("LEFT ");
							next(x-1, y, steps+1, 'L', buf);
							break;
						case 3: //RIGHT
							//printf("RIGHT ");
							next(x+1, y, steps+1, 'R', buf);
							break;
					}
				} else {
					//door locked
				}
			}
		}
	} else if (grid[y][x] == 'V') {
		//printf("already @ V is %d\n", already[y][x]);
		sprintf(ans[ansPos], "%s%c", in, dir);
		//printf("ANS: %s%c\n", in, dir);
		ansPos++;
		//return;
	}
	}
