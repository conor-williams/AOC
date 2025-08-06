#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define getchar()
int main(int argc, char **argv) {
	printf("		2017 day23 Part 2\n");
	fflush(stdout); int fd = dup(1); close(1);


        FILE * a = fopen(argv[1], "r");
        char line1[1000];
	int B = 0;
while(1)
{
        fgets(line1, 999, a);
        if (feof(a)) break;
        line1[strlen(line1) -1]='\0';

	sscanf(line1, "set b %d\n", &B);
	break;
}



	long long h = 0;
	long long b = ((B*100)+100000);
	//long long c = (b+1000);
	
	long long f = 0;
	long long d = 0;
	long long e = 0;
	long long g = 0;

	int z = -1;
	do {
		z++;

		f = 1;
		d = 2;
		int times2 = 0;
		do {
			times2++;
			e = 2;
		
			int times = 0;
			//int timesF = 0;
			//e -= 1*105698;
			//times = 105698;
			do {
				times++;
				g = d; // 2
				g *= e; // 2
				g -= b; // sub b
				if (g == 0) {
					f = 0;
					//printf("f is %lld\n", f);
					goto fset;
				} else if (g>0) {
					goto after;
				}
				e -= -1; //add one to e
				g = e;
				g -= b; //sub b

				//printf("g is %lld\n", g);
			} while (g != 0);
	//105698 
after:
			d -= -1; // add one to d
			g = d;
			g -= b; //sub b
		} while  (g!= 0);
		///printf("times2 is %d\n", times2);//one less
		
fset:
		if (f == 0) {
			//printf("h minus\n");
			h -= -1;
		}
		//g = b;
		//printf("b is %lld\n", b);
		//g -= c;
		//printf("c is %lld\n", b);
		//printf("g is %lld\n", g);
		//if (g == 0) {break;}
	
		b -= -17;
		
	} while (z < 1000);
		
	
	printf("h is %lld\n", h);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", h);


}
///if (times == 105698) {if (f != 0) {printf("fnot\n");} else { printf("times is %lld\n", times); }}
