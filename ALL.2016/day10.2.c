#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
int lenx, leny;
#define DAY "2016 day10 part1 \n"
#undef _DEBUG_
long tot;
vector <int> orderV;
struct bot {
	int botNum;
	//int Bchip[100];
	vector<int> Bchip;
	int BchipPos;
	int accessed;
};
int botNum = 0;
struct output {
	int Ochip[100];
	int OchipPos;
};
struct bot bots[500] = {0};
int botMax = 0;
struct output outputs[500] = {0};
int outputNum = 0;

struct instruction {
	int Bfrom;
	int type;
	int output1;
	int output2;
	int bot1;
	int bot2;
};
struct instruction inst[500] = {0};
int instPos = 0;
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
       
        char line1[1000];
while(1) 
{
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	int ret = 0; int chip; int botFrom, bot1 = 0, bot2 = 0; int output1 = 0; int output2 = 0;
	ret = sscanf(line1, "value %d goes to bot %d", &chip, &botFrom);
	if (ret == 2) {
		printf("here1 %s\n", line1);
		if (botFrom == 190) {
			printf("here10 %s\n", line1); getchar();
		}
		int curBot = botNum;
		int found22 = 0; int k;
		for (k = 0; k < botNum; k++) {
			if (bots[k].botNum ==  botFrom) {
				curBot = k;
				found22 = 1; break;
			}
		}
		if (found22 == 1) {
			//curBot = k;
			if (bots[k].botNum == 190) {
				printf("FOUND pos(%d) %d %s\n", curBot, bots[k].botNum, line1); getchar();
			}
		} else {
			//curBot = botNum; botNum++;
			botNum++;
			if (botFrom == 190) {
				printf("NOT FOUND using pos(%d) %d %s\n", curBot, bots[k].botNum, line1); getchar();
			}
		}
		bots[curBot].Bchip.push_back(chip);
		bots[curBot].BchipPos++;
		if (botFrom == 190) {
			printf("%d\n", bots[curBot].BchipPos); getchar();
		}
		bots[curBot].accessed++;
		bots[curBot].botNum = botFrom;
		if (botFrom > botMax) {botMax = botFrom;}
		if (bots[curBot].accessed == 1) {orderV.push_back(botNum);}
		goto end;
	}
	ret = sscanf(line1, "bot %d gives low to bot %d and high to bot %d", &botFrom, &bot1, &bot2);
	if (ret == 3) {
		printf("here2 %s\n", line1);
		inst[instPos].type = 1;	
		inst[instPos].Bfrom = botFrom;	
		inst[instPos].bot1 = bot1;	
		inst[instPos].bot2 = bot2;	
		inst[instPos].output1 = output1;	
		inst[instPos].output2 = output2;	
		instPos++;
		int found = 0; int k;
		for (k = 0; k < botNum; k++) {
			if (bots[k].botNum ==  bot1) {
				found = 1; break;
			}
		}
		if (found == 0) {
			bots[botNum].botNum = bot1; botNum++;
		}
		found = 0; 
		for (k = 0; k < botNum; k++) {
			if (bots[k].botNum ==  bot2) {
				found = 1; break;
			}
		}
		if (found == 0) {
			bots[botNum].botNum = bot2; botNum++;
		}
		goto end;
	}
	ret = sscanf(line1, "bot %d gives low to output %d and high to output %d", &botFrom, &output1, &output2);
	if (ret == 3) {
		printf("here3 %s\n", line1);
		inst[instPos].type = 2;	
		inst[instPos].Bfrom = botFrom;	
		inst[instPos].bot1 = bot1;	
		inst[instPos].bot2 = bot2;	
		inst[instPos].output1 = output1;	
		inst[instPos].output2 = output2;	
		instPos++;
		goto end;
	}
	ret = sscanf(line1, "bot %d gives low to bot %d and high to output %d", &botFrom, &bot1, &output1);
	if (ret == 3) {
		printf("here4 %s\n", line1);
		inst[instPos].type = 3;	
		inst[instPos].Bfrom = botFrom;	
		inst[instPos].bot1 = bot1;	
		inst[instPos].bot2 = bot2;	
		inst[instPos].output1 = output1;	
		inst[instPos].output2 = output2;	
		instPos++;
		int found = 0; int k;
		for (k = 0; k < botNum; k++) {
			if (bots[k].botNum ==  bot1) {
				found = 1; break;
			}
		}
		if (found == 0) {
			bots[botNum].botNum = bot1; botNum++;
		}
		found = 0; 
		goto end;
	}
	ret = sscanf(line1, "bot %d gives low to output %d and high to bot %d", &botFrom, &output1, &bot1);
	if (ret == 3) {
		printf("here5 %s\n", line1);
		inst[instPos].type = 4;	
		inst[instPos].Bfrom = botFrom;	
		inst[instPos].bot1 = bot1;	
		inst[instPos].bot2 = bot2;	
		inst[instPos].output1 = output1;	
		inst[instPos].output2 = output2;	
		instPos++;
		int found = 0; int k;
		for (k = 0; k < botNum; k++) {
			if (bots[k].botNum ==  bot1) {
				found = 1; break;
			}
		}
		if (found == 0) {
			bots[botNum].botNum = bot1; botNum++;
		}
		found = 0; 
		goto end;
	}
	printf("ERRROR no deal\n"); getchar();
end:
	leny++;
}
fclose(a);
	printf("INSTRUCTIONS (%d):\n", instPos);
	for (int i = 0; i < instPos; i++) {
		printf("i: %d type: %d\n", i, inst[i].type);
	}
	printf("\nBOTS\n");
	for (int i = 0; i < botNum; i++) {
		printf("bot: (%d) Numchips: %d Chips:\n", bots[i].botNum, bots[i].BchipPos);
		sort(bots[i].Bchip.begin(), bots[i].Bchip.end());
		for (int j = 0; j < bots[i].BchipPos; j++) {
			printf("	%d\n", bots[i].Bchip[j]);
		}
	}
	int Q[2000]; int QPos = 0;
	printf("ADD TO Q\n");
	for (int j = 0; j < botNum; j++) {
		if (bots[j].BchipPos > 1) {
			Q[QPos] = bots[j].botNum; QPos++;
			printf("ADDED %d\n", bots[j].botNum);
		}
	}

	// Traverse Q
	int outputMax = 0;
	printf("Traverse Q...\n");
	for (int j = 0; j < QPos; j++) {
		int mBot = 0;
		int warning = 0;
		for (int r = 0; r < botNum; r++) {
			if (bots[r].botNum == Q[j]) {
				if (bots[r].BchipPos < 2) {
					printf("WARNING botNum:%d less than 2 (%d) NEXTPOS_<\n", bots[r].botNum, bots[r].BchipPos); 
					warning = 1;
				}
				sort(bots[r].Bchip.begin(), bots[r].Bchip.end());
				mBot = r;
			}
		}
		if (warning == 0) {
			printf("Accessing mBot (%d) numChips(%d) \n", bots[mBot].botNum, bots[mBot].BchipPos);
			int found = 0;
			for (int j = 0; j < bots[mBot].BchipPos; j++) {
				printf("	%d\n", bots[mBot].Bchip[j]);
				if (bots[mBot].Bchip[j] == 61) {
					found++;
				} else if (bots[mBot].Bchip[j] == 17) {
					found++;
				}
				if (found == 2) {printf("FOUND IT BOT: (%d)\n", bots[mBot].botNum); getchar();}
			}
		} else {
			printf("NOT Accessing (%d)\n", bots[mBot].botNum);
			continue;
		}
			
		for (int i = 0; i < instPos; i++) {
			if (inst[i].Bfrom == bots[mBot].botNum) {
				int o1, o2;
				switch(inst[i].type) {
					case 1:
						printf("instruction 1 bot1 bot2\n");
						for (int k = 0; k < botNum; k++) {
							if (inst[i].bot1 == bots[k].botNum) {
								printf("low (%d)-> bots[k].botNum (%d)\n", bots[mBot].Bchip.at(0), bots[k].botNum);
								bots[k].Bchip.push_back(bots[mBot].Bchip.at(0));
								bots[k].BchipPos++;
								Q[QPos] = bots[k].botNum; QPos++;
								break;
							}
						}
						for (int k = 0; k < botNum; k++) {
							if (inst[i].bot2 == bots[k].botNum) {
								printf("high (%d) -> bots[k].botNum (%d)\n", bots[mBot].Bchip.at(bots[mBot].BchipPos-1), bots[k].botNum);
								bots[k].Bchip.push_back(bots[mBot].Bchip.at(bots[mBot].BchipPos-1));
								bots[k].BchipPos++;
								Q[QPos] = bots[k].botNum; QPos++;
								break;
							}
						}
						////
						for (int z = 1; z < bots[mBot].BchipPos-1; z++) {
							printf("here1..."); fflush(stdout);
							bots[mBot].Bchip.at(z-1) = bots[mBot].Bchip.at(z);
						}
						bots[mBot].BchipPos -= 2;
						break;
					case 2:
						printf("instruction 2 output1 (%d) output2 (%d)\n", inst[i].output1, inst[i].output2);
						//low
						o1 = inst[i].output1;
						outputs[o1].Ochip[outputs[o1].OchipPos] = bots[mBot].Bchip.at(0);
						outputs[o1].OchipPos++;
						if (o1 > outputMax) {outputMax = o1;}
						//high
						o2 = inst[i].output2;
						outputs[o2].Ochip[outputs[o2].OchipPos] = bots[mBot].Bchip.at(bots[mBot].BchipPos-1);
						outputs[o2].OchipPos++;
						if (o2 > outputMax) {outputMax = o2;}
						////
						for (int z = 1; z < bots[mBot].BchipPos-1; z++) {
							bots[mBot].Bchip.at(z-1) = bots[mBot].Bchip.at(z);
						}
						bots[mBot].BchipPos -= 2;
						break;
					case 3:
						printf("instruction 3 bot1 output1\n");
						//low
						for (int k = 0; k < botNum; k++) {
							if (inst[i].bot1 == bots[k].botNum) {
								printf("low (%d) -> bots[k].botNum (%d)\n", bots[mBot].Bchip.at(0), bots[k].botNum);
								bots[k].Bchip.push_back(bots[mBot].Bchip.at(0));
								bots[k].BchipPos++;
								Q[QPos] = bots[k].botNum; QPos++;
								break;
							}
						}
						//high
						o1 = inst[i].output1;
						outputs[o1].Ochip[outputs[o1].OchipPos] = bots[mBot].Bchip.at(bots[mBot].BchipPos-1);
						outputs[o1].OchipPos++;
						if (o1 > outputMax) {outputMax = o1;}
				
						////
						for (int z = 1; z < bots[mBot].BchipPos-1; z++) {
							bots[mBot].Bchip.at(z-1) = bots[mBot].Bchip.at(z);
						}
						bots[mBot].BchipPos-=2;
						break;
					case 4:
						printf("instruction 4 output1 bot1\n");
						//low
						o1 = inst[i].output1;
						printf("low (%d)-> outputs[o1] (%d)\n", bots[mBot].Bchip.at(0), o1);
						outputs[o1].Ochip[outputs[o1].OchipPos] = bots[mBot].Bchip.at(0);
						outputs[o1].OchipPos++;
						if (o1 > outputMax) {outputMax = o1;}
						//high
						for (int k = 0; k < botNum; k++) {
							if (inst[i].bot1 == bots[k].botNum) {
								printf("high (%d) -> bots[k].botNum (%d)\n",  bots[mBot].Bchip.at(bots[mBot].BchipPos-1),  bots[k].botNum);
								bots[k].Bchip.push_back(bots[mBot].Bchip.at(bots[mBot].BchipPos-1));
								bots[k].BchipPos++;
								Q[QPos] = bots[k].botNum; QPos++;
								break;
							}
						}
						////
						for (int z = 1; z < bots[mBot].BchipPos-1; z++) {
							bots[mBot].Bchip.at(z-1) = bots[mBot].Bchip.at(z);
						}
						bots[mBot].BchipPos -= 2;
						break;
				} 
			}
		}
	}
	for (int i = 0; i <= outputMax; i++) {
		if (outputs[i].OchipPos > 0) {
			printf("output %d : numChips (%d)\n", i, outputs[i].OchipPos);
			for (int k = 0; k < outputs[i].OchipPos; k++) {
				printf("	%d\n", outputs[i].Ochip[k]);
			}
		}
	}

	printf("BINS...\n");
	int mul = 1;
	for (int i = 0; i <= outputMax; i++) {
		if (i <= 2) {
			printf("output %d : numChips (%d)\n", i, outputs[i].OchipPos);
			for (int k = 0; k < outputs[i].OchipPos; k++) {
				mul*=outputs[i].Ochip[k];
				printf("	%d\n", outputs[i].Ochip[k]);
			}
		}
	}
	printf("***mul %d\n", mul);
	printf("mul END\n");
    	return 0;
} 
