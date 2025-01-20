#include <stdio.h>
#include <stdlib.h>
void main() {
	int regb[10] = {0};
	//#ip 1
	//addi 1 16 1
one:
	printf("here at 1...\n"); getchar();

	regb[1] = regb[1] + 16; getchar();
	//printf("%s\n", *array[1]);
	//goto *array[1];
	{
		{
two:
static void *array[] = {&&one, &&two};
			printf("here at 2...\n"); getchar();
			goto *array[0];
			//seti 1 8 2
			regb[2] = 1;
			//seti 1 5 4
			regb[4] = 1;
			{
				//mulr 2 4 3
				regb[3] = regb[2] * regb[4];
				//eqrr 3 5 3
				if (regb[3] == regb[5]) {regb[3] = 1;} else {regb[3] = 0;}
				//addr 3 1 1
				regb[1] = regb[3] + regb[1];
				//addi 1 1 1
				regb[1] = regb[1] + 1;
				{
					//addr 2 0 0
					regb[0] = regb[2] + regb[0];
				}
				//addi 4 1 4
				regb[4] = regb[4] + 1;
				//gtrr 4 5 3
				if (regb[4] > regb[5]) {regb[3] = 1;} else {regb[3] = 0;}
				//addr 1 3 1
				regb[1] = regb[1] + regb[3];

				//seti 2 8 1
				regb[1] = 2;
			}
			//addi 2 1 2
			regb[2] = regb[2] + 1;
			//gtrr 2 5 3
			if (regb[2] > regb[5]) {regb[3] = 1;} else {regb[3] = 0;}
			//addr 3 1 1
			regb[1] = regb[3] + regb[1];
			//seti 1 8 1
			regb[1] = 1;
			//mulr 1 1 1
			regb[1] = regb[1] * regb[1];
		}
		//addi 5 2 5
		regb[5] = regb[5] + 2;
		//mulr 5 5 5
		regb[5] = regb[5] * regb[5];
		//mulr 1 5 5
		regb[5] = regb[1] * regb[5];
		//muli 5 11 5
		regb[5] = regb[5] * 11;
		//addi 3 5 3
		regb[3] = regb[3] + 5;
		//mulr 3 1 3
		regb[3] = regb[3] * regb[1];
		//addi 3 4 3
		regb[3] = regb[3] + 4;
		//addr 5 3 5
		regb[5] = regb[5] + regb[3];
		//addr 1 0 1
		regb[1] = regb[1] + regb[0];
		//seti 0 7 1
		regb[1] = 0;
	}
	//setr 1 1 3
	regb[3] = regb[1];
	//mulr 3 1 3
	regb[3] = regb[3] * regb[1];
	//addr 1 3 3
	regb[3] = regb[1] + regb[3];
	//mulr 1 3 3
	regb[3] = regb[1] * regb[3];
	//muli 3 14 3
	regb[3] = regb[3] * 14;
	//mulr 3 1 3
	regb[3] = regb[3] * regb[1];
	//addr 5 3 5
	regb[5] = regb[5] + regb[3];
	//seti 0 9 0
	regb[0] = 0;
	//seti 0 0 1
	regb[1] = 0;
}
