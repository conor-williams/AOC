#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <mbedtls/md5.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2016 day17 part1\n"
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
char ans[3000][500];
int ansPos = 0;

void print_hash(unsigned char hash[16]) {
        for (int i = 0; i < 16; i++) {
                printf("%02x", hash[i]);
        }
        printf("\n");
}
int compute_md5(const char *input) {
        unsigned char output[16]; // MD5 output is 16 bytes

        mbedtls_md5_context ctx;
        mbedtls_md5_init(&ctx);
        mbedtls_md5_starts_ret(&ctx);
        mbedtls_md5_update_ret(&ctx, (const unsigned char*) input, strlen(input));
        mbedtls_md5_finish_ret(&ctx, output);
        mbedtls_md5_free(&ctx);


        sprintf(out5, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", output[0], output[1], output[2], output[3], output[4], output[5], output[6], output[7], output[8], output[9], output[10], output[11], output[12], output[13], output[14], output[15]);

        //printf("out5 is %s\n", out5);
	return 0;
}


int main(int argc, char **argv)
{
        char line1[SIZE];
	tot = 0;lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
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
		int min = 99999; int minPos = 0;
		for (int i = 0; i < ansPos; i++) {
			if ((int)strlen(ans[i]) < min) {min = (int)strlen(ans[i]); minPos = i;}
		}
		
		printf("**min is %s\n", ans[minPos]);
		fflush(stdout); dup2(fd, 1);
		char ans2[100];
		strncpy(ans2, ans[minPos]+(int)strlen(buf), 100);
		printf("**ans: %s\n", ans2);
		exit(0);
	} else {
		printf("no ans...\n");
	}
	leny++;
}
fclose(a);
	tot = 0;

	//fflush(stdout); dup2(fd, 1);
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
			char buf[200];
			sprintf(buf, "%s%c", in, dir);
			if (strlen(buf) > 190) {return;}
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
