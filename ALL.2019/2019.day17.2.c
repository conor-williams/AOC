#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <deque>
#include <cassert>
#include <unistd.h>
#include <string>

using namespace std;
int theconstructedlinePos = 0;
//char theconstructedline[] = "A,B,A,C,B,B,A,B,A,CZL,10,R,8,R,8,R,12,L,8ZL,10,R,6Z2,R,6,L,10,R,12,L,8,L,10,R,12ZnZ";
//char theconstructedline[] = "A,B,CZ3ZL3ZR2ZyZ";
//char theconstructedline[] = "A,B,C,A,B,XXX,C,B,C,B,XXX,C,A,B,C,A,B,XXX,CZR,6,L,10,R,8,R,8ZR,12,L,8ZL,10Zn";
//char theconstructedline[] = "A,B,C,A,B,C,B,B,A,C,C,B,A,A,A,A,A,C,C,B,B,B,C,B,C,B,C,B,B,A,C,C,B,A,A,A,A,A,C,C,B,B,B,C,A,B,C,A,B,C,B,B,A,C,C,B,A,A,A,A,A,C,C,B,B,B,CZR,6,L,10,R,8,R,8ZR,12,L,8ZL,10ZnZ";
//-- R:6 L:10 R:8 R:8 -- R:12 L:8 -- L:10

long long ans = 0;
//char theconstructedline[] = "A,B,A,C,B,C,A,B,A,CZR,6,L,10,R,8,R,8ZR,12,L,8,L,10ZR,12,L,10,R,6,L,10ZnZ";
char theconstructedline[200];
int numNewline = 0;
int times2222;
int numDots = 0;
//int sx = 0; int sy = 0;
const int SZ = 120;
char grid[SZ][SZ];
int already[SZ][SZ];
int yy = 0;
int xx = 0;
int var_inPos = 0;
char var_in[200];
string gPath;
int numPos = 0;
int firstHash = -1;
int lenx, leny;
int turnon = 0;
#define DAY "		2019 day 17 part2\n"
//#define _DEBUG_
#undef DEBUG
#define getchar()
int numSteps = 0;
#define MAX 6000
int instTOT = 0;
long long inst[MAX];
long long instOrig[MAX];
char instruction    [MAX][40];
void replaceAll(std::string& str, const std::string& from, const std::string& to);
void next(int x, int y, int ex, int ey, int dir, char turn, string tu2);

long long output[6] = {0};
long long saveInst[6][MAX] = {0};
long long nextInst[6] = {0};
long long relativeBase[6] = {0};
int times[6] = {0};
int finished[6] = {0};
int inputCounters[6] = {0};
int phase[] = {1,1,1,1,1,-1};
int machine(int machineNumber, int one);
char myInput;
char reverseInput(char in);
int OXX = 0;
int OXY = 0;
int MINPATH;
//char tmpIn[] = {'3','3','3','1','2'};
long long  tmpIn[] = {1, 2, 2,  2, 2, 2, 2, 2, 2, 2, -1};
int tmpInPos = 0;
void printit();
void next(int x, int y, int path);
int mytimes = 1;
#define SX 120
#define SY 120
//char grid[SY+5][SX+5];
int yCur = 0;
int xCur = 0;
int MAXPATH = 0;

int pathPrev = 0;
struct pos_s {
	//char dir;
	int x;
	int y;
	deque <char> path;
};
deque <pos_s> myInputQ;
deque <char> myBack;
struct pos_s pos2;
int MOVE = 0;
deque <char> PATH;
int pathPOS = 0;
void ne(int x, int y, int endX, int endY, int px, int py, int dir, int turn, int path, char move);
int fd;
///#define getchar()
int main(int argc, char **argv)
{

	struct pos_s st = {xCur, yCur, PATH};

	//myInputQ.push_back(st);
	for (int y = 0; y < SY; y++) {
		for (int x = 0; x < SX; x++) {
			grid[y][x] = '.';
		}
		grid[y][SX] = ' ';
		grid[y][SX+1] = (y%10) + 48;
	}
	for (int x = 0; x < SX; x++) {
		grid[SY][x] = ' ';
		grid[SY+1][x] = (x%10)+48;
	}

	//grid[0][0] = 'X';
	lenx = 0; leny = 0;
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
	fd = dup(1); close(1);

	char line1[MAX];
	for (int i = 0 ; i < MAX; i++) {
		inst[i] = 0;
	}

	int newStart = 0;
	int pos = 0;
	while(1) {
		fgets(line1, MAX-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s getchar\n", line1); getchar();
#endif
		for (int i = 0; i < (int)strlen(line1); i++) {
			if (line1[i] == ',') {
				instruction[newStart][pos] = '\0';
#ifdef _DEBUG_
				printf("instruction[newStart]: %s (newStart:%d)\n", instruction[newStart], newStart); 
#endif
				newStart++;
				pos = 0;
#ifdef _DEBUG_
				printf("instruction[newStart]getc\n");
				printf("getc\n");
#endif
			} else {
				instruction[newStart][pos] = line1[i];
				/*
				if (i != 0) {
					instruction[newStart][pos] = line1[i];
				} else {
					instruction[newStart][pos] = '2';
				}
				*/
				pos++;
			}
		}
		leny++;
	}
	fclose(a);
	instruction[newStart][pos] = '\0';
	newStart++;
	char *stop;
	for (int i = 0; i < newStart; i++) {
		inst[i] = strtoul(instruction[i], &stop, 10);
#ifdef _DEBUG_
		if (inst[i] < 0) {
			printf("%lld\n", inst[i]); getchar();
		} else {
			printf("%lld\n", inst[i]);
		}
#endif
	}
	instTOT = newStart;
	printf("START-------------\n");

	for (int i = 0; i < instTOT; i++) {
		instOrig[i] = inst[i];
	}

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < instTOT; i++) {
			saveInst[j][i] = inst[i];
		}
	}

	sort(phase, phase+5);
	long long outputMAX = 0; int phaseMAX[5] = {0};
	do {	
re600:
		for (int i = 0; i < 5; i++) {
			output[i] = 0;
			nextInst[i] = 0;
			relativeBase[i] = 0;
			times[i] = 0;
			finished[i] = 0;
			inputCounters[i] = 0;
		}
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < instTOT; i++) {
				saveInst[j][i] = instOrig[i];
			}
		}
		int i = -1;	
restart:
		i++;
		i = i%5;
		i = 0; /////////////////////////////////	
		int one = 1;
		/*
		   int ret = machine(i, one);
		   if (ret == 34) {goto restart;} else if (ret == 33 && i == 4) {goto end;} else if (ret == 33 && one == 1) {goto end;}  else if (ret == 22) {goto restart;}
end:
printf("output CONOR %lld\n", output[0]);  getchar();
if (output[0] > outputMAX) {outputMAX = output[0]; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
		//printf("output: %lld\n", output[0]);
		//printf("outputMAX now: %lld\n", outputMAX);
		*/
		break;
	} while (next_permutation(phase, phase+5));

	printf("***OUTPUTMAX: %lld\n", outputMAX);
	printf("PHASEMAX:\n"); for (int i = 0; i < 5; i++) { printf("%d ", phaseMAX[i]); } printf("\n"); //getchar();

	times2222 = -1;
	while (ans == 0) {
		times2222++;

		for (int i = 0; i < 5; i++) {
			output[i] = 0;
			nextInst[i] = 0;
			relativeBase[i] = 0;
			times[i] = 0;
			finished[i] = 0;
			inputCounters[i] = 0;
		}
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < instTOT; i++) {
				saveInst[j][i] = instOrig[i];
			}
		}
		printf("running again: ");
		getchar();
		int ret = machine(0, 1);
		if (times2222 == 0) {
			for (int yy4 = 0; yy4 < 120; yy4++) {
				for (int xx4 = 0; xx4 < 120; xx4++) {
					printf("%c", grid[yy4][xx4]);
				}
				printf("\n");
			}
			getchar();
			int sx = 0; int sy = 0; int dir = 0; int ex = 0; int ey = 0;
			for (int yy3 = 1; yy3< 120-1; yy3++) {
				for (int xx3 = 1; xx3 < 120-1; xx3++) {
					if (grid[yy3][xx3] == '^') {
						dir = 0;
						sx = xx3; sy = yy3;
						goto after2;
					} else if (grid[yy3][xx3] == '>') {
						dir = 1;
						sx = xx3; sy = yy3;
						goto after2;
					} else if (grid[yy3][xx3] == 'v') {
						dir = 2;
						sx = xx3; sy = yy3;
						goto after2;
					} else if (grid[yy3][xx3] == '<') {
						dir = 3;
						sx = xx3; sy = yy3;
						goto after2;
					}

				}
			}
after2:
			for (int yy3 = 1; yy3< 120-1; yy3++) {
				for (int xx3 = 1; xx3 < 120-1; xx3++) {
					int count = 0;
					if (grid[yy3][xx3] != '#') {continue;}
					if (grid[yy3-1][xx3] == '.') {
						count++;
					} 
					if (grid[yy3][xx3+1] == '.') {
						count++;
					}
					if (grid[yy3+1][xx3] == '.') {
						count++;
					}
					if (grid[yy3][xx3-1] == '.') {
						count++;
					}
					if (count == 3) {
						ex = xx3; ey= yy3;
						goto after3;
					}
				}
			}

after3:
			grid[ey][ex] = '#';
			grid[sy][sx] = '#';
			printf("starts/ends: %d %d %d %d\n", sy, sx, ey, ex);
			getchar();
			string bla = "";
			for (int yy = 0; yy < 120; yy++) {
				for (int xx = 0; xx < 120; xx++) {
					already[yy][xx] = 0;
				}
			}
			next(sx, sy, ex, ey, dir, 'Q', bla);
			printf("gPath: %s\n", gPath.c_str());
			getchar();
			{
				int count = 0;
				int first = 0;
				string pa = "";
				for (char ch: gPath) {
					if (ch != 'S') {
						if (first != 0) {
							//pa += "22" /*+ to_string(count+1) */ + ",";
							pa = pa+ to_string(count+1) + ",";
						} else {
							first = 1;
						}
						pa = pa + ch + ",";
						count = 0;
					} else {
						count++;
					}
				}
				pa += to_string(count+1);
				pa += ",";
				printf("%s\n", pa.c_str());
				string paOrig = pa;
				printf("%s\n", paOrig.c_str());
				int ar[3];
				for (int end = 0; end < 3; end++) {
					for (int iii = 0; iii < end; iii++) {
						ar[iii] = 1;
					}
					for (int iii = end; iii < 3; iii++) {
						ar[iii] = 0;
					}
					int arOrig[3];// = Arrays.copyOf(ar, 3);
					sort(ar, ar+3);
					for (int qqqq =0; qqqq < 3; qqqq++) {
						arOrig[qqqq] = ar[qqqq];
					}

					do {
						pa = paOrig;
						int paPos = 0;
						string parts[3];
						parts[0] = "";
						parts[1] = "";
						parts[2] = "";
						int partsPos = 0;
						for (int jjj = 0; jjj < 3; jjj++) {
							if (ar[jjj] == 1) {
								paPos = 0;
								for (int kk = 0; kk < 8; kk++) {
									paPos = pa.find(",", paPos+1);
								}
								parts[partsPos] = pa.substr(0, paPos);

								replaceAll(pa, parts[partsPos]+",", "");
								partsPos++;
							} else {
								paPos = 0;
								for (int kk = 0; kk < 6; kk++) {
									paPos = pa.find(",", paPos+1);
								}
								parts[partsPos] = pa.substr(0, paPos);
								replaceAll(pa, parts[partsPos]+",", "");
								partsPos++;
							}
						}
						if (pa.find("R") == -1 && pa.find("L") == -1) {

							string pa2 = paOrig;
							for (int ii = 0; ii < 3; ii++) {
								char ch = (char)('A'+ii);
								string rep1;
								rep1.push_back(ch);
								replaceAll(pa2, parts[ii], rep1);
							}
							if (pa2.find("R") == -1 && pa2.find("L") == -1) {
								printf("yatzee...");
								pa2 = pa2.substr(0, pa2.length()-1);
								for (int ii = 0; ii < 3; ii++) {
									pa2+= "\n";
									pa2+=parts[ii];
								}
								pa2+="\nn\n";
								strcpy(theconstructedline, pa2.c_str());
								printf("var_in %s\n", var_in);
								getchar();
								goto after5;
							}


						}
					} while (next_permutation(ar, ar+3));
				}

			}

		}
after5:
		continue;
	}
after4:
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", ans);
	exit(0);
}
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

char reverseInput(char in) {
	switch (in) {
		case '1': return '2';
		case '2': return '1';
		case '3': return '4';
		case '4': return '3';
	}
	return 0;
}

void next(int x, int y, int ex, int ey, int dir, char turn, string tu2) {
	if (x == ex && y == ey) {printf("END\n"); getchar(); gPath = tu2; printf("end %s\n", tu2.c_str()); return;}
	if (grid[y][x] != '#') {return;}
	/*
		if (x == 26 && y== 28) {
			printf("here26...");
		}
		if (x == 27 && y== 28) {
			printf("here27...");
		}
		*/
	if (already[y][x] == 0) {
		int goStrait = 0;
		string tu = tu2;
		//printf("tu: %s\n", tu.c_str());
		int count = 0;
		if (y-1 >= 0 && grid[y-1][x] == '#') {
			count++;
		} 
		if (x+1 < 120 && grid[y][x+1] == '#') {
			count++;
		}
		if (y+1 < 120 && grid[y+1][x] == '#') {
			count++;
		}
		if (x-1 >= 0 && grid[y][x-1] == '#') {
			count++;
		}
		if (count == 4) {
			goStrait = 1;
		}

		if (dir == 0) {
			if (y-1 >= 0) {
				next(x, y-1, ex, ey, 0, 'S', tu+'S');
			}
			if (goStrait != 1) {
				if (x-1 >= 0) {
					next(x-1, y, ex, ey, 3, 'L', tu+'L');
				}
				if (x+1 < 120) {
					next(x+1, y, ex, ey, 1, 'R', tu+'R');
				}
			}
		} else if (dir == 1) {
			if (x == 27 && y== 28) {
				printf("here10...");
			}
			if (x+1 < 120) {
				next(x+1, y, ex, ey, 1, 'S', tu+'S');
			}
			if (goStrait != 1) {
				if (y-1 >= 0) {
					next(x, y-1, ex, ey, 0, 'L', tu+'L');
				}
				if (y+1 < 120) {
					next(x, y+1, ex, ey, 2, 'R', tu+'R');
				}
			}
		} else if (dir == 2) {
			if (y+1 < 120) {
				next(x, y+1, ex, ey, 2, 'S', tu+'S');
			}
			if (goStrait != 1) {
				if (x+1 < 120) {
					next(x+1, y, ex, ey, 1, 'L', tu+'L');
				}
				if (x-1 >= 0) {
					next(x-1, y, ex, ey, 3, 'R', tu+'R');
				}
			}
		} else if (dir == 3) {
			if (x-1 >= 0) {
				next(x-1, y, ex, ey, 3, 'S', tu+'S');
			}
			if (goStrait != 1) {
				if (y+1 < 120) {
					next(x, y+1, ex, ey, 2, 'L', tu+'L');
				}
				if (y-1 >= 0) {
					next(x, y-1, ex, ey, 0, 'R', tu+'R');
				}
			}
		}
	}


}

int machine(int machineNumber, int one) {
	if (finished[machineNumber] == 1) { return 22;}
	long long input[10];	

	for (int i = 0; i < instTOT; i++) {
		inst[i] = saveInst[machineNumber][i];
	}

	int inputCounter = inputCounters[machineNumber];

	if (machineNumber == 0 && times[machineNumber] == 0) {
		input[1] = 1; 
		input[0] = phase[machineNumber];
	} else {
		input[1] = output[machineNumber];
		input[0] = phase[machineNumber];
	}
	if (times2222 != 0) {
		printf("setting inst to 2..>");
		printf("inst[0] was %lld\n", inst[0]);
		inst[0] = (long long)2;
		printf("nextInst[0]: %d\n", nextInst[0]);
		getchar();
	}

	for (int i = nextInst[machineNumber]; i < instTOT; i++) {
#ifdef _DEBUG_
		printf("\nNEW NEW NEW:::"); fflush(stdout);
		printf("POS InstNUM: (%d) ", i); fflush(stdout);
		printf(" is [%lld] ", inst[i]); fflush(stdout); //getchar();
#endif

		int myINST = inst[i] % 100;
		if (myINST == 3) {
			{printf("got a 3 (using %lld) -> [pos:%lld]\n", input[inputCounter], inst[i+1]);}
#ifdef _DEBUG_
#endif
			printf("myInput is [%c]\n", myInput); printf("%d,%d \n", xCur, yCur);// getchar();
			if (inst[i] > 200) {
				printf("giveinput\n");
				///char in[100]; gets(in); fflush(stdin);
				//inst[relativeBase[machineNumber]+inst[i+1]] = input[inputCounter];
				///printf("in is %s\n", in); printf("int of in is %d\n", in[0]);
				//printf("giving %d\n", in[0]); getchar();
				inst[relativeBase[machineNumber]+inst[i+1]] = (int)theconstructedline[theconstructedlinePos++];
			} else {
				///input[inputCounter] = (long long)(myInput - 48);
				printf("giveinput\n");
				//char in[100]; gets(in); fflush(stdin);

				///printf("in is %s\n", in);
				//printf("giving %d\n", in[0]); getchar();
				//inst[inst[i+1]] = input[inputCounter];
				inst[inst[i+1]] = (int)theconstructedline[theconstructedlinePos++];
			}
			if (inputCounter != 1) {
				inputCounter++;
			}
			i++; printf("leaving 3 (input)...\n"); fflush(stdout);
			//printit(); getchar();
		} else if (myINST == 4) {
			printf("here5...\n"); fflush(stdout);
			{printf("got a 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);}
#ifdef _DEBUG_
#endif
			//OUT 0 == Wall 1 == OK 2==OX
			numSteps++;
			long long OUT;
			if (inst[i] > 200) {
				input[1] = inst[relativeBase[machineNumber]+inst[i+1]];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[relativeBase[machineNumber]+inst[i+1]]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[relativeBase[machineNumber]+inst[i+1]]; 
				}
				OUT =  inst[relativeBase[machineNumber]+inst[i+1]];

				printf("REL OUT: %lld (base: %lld+%lld)\n", inst[relativeBase[machineNumber]+inst[i+1]],
						relativeBase[machineNumber], inst[i+1]);
#ifdef _DEBUG_
#endif
			} else if (inst[i] > 100) {
				printf("or is it OUT: %lld\n", inst[i+1]);
#ifdef _DEBUG_
				printf("or is it OUTS: %s\n", instruction[i+1]);
#endif
				input[1] = inst[i+1];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[i+1]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[i+1]; 
				}
				OUT = inst[i+1];
			} else {
				printf("OUT: %lld\n", inst[inst[i+1]]); 
#ifdef _DEBUG_
				printf("OUTS: %s\n", instruction[inst[i+1]]);
#endif
				input[1] = inst[inst[i+1]];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[inst[i+1]]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[inst[i+1]]; 
				}
				OUT = inst[inst[i+1]];
			}
			struct pos_s pos1;

			if (times2222 == 1 && OUT > 50) {
				printf("OUT is %lld\n", OUT);
				getchar();
			}
			if (OUT > 255) {
				ans = OUT;
				printf("setting ans...");
				printf("OUT is %lld\n", OUT);
				getchar();
			} else if (yy < 120 && xx < 120) {

				if (OUT == 35) {grid[yy][xx] = '#'; xx++;}
				else if (OUT == 46) {grid[yy][xx] = '.'; xx++;}
				else if (OUT == 10) {yy++;xx=0;}
				else { grid[yy][xx] = (char)(OUT%256); xx++; }
			}

			i++;
		} else if (myINST == 99) {
			printf("GOT QUIT 99\n"); //in = 1; 
			return 9999;
			if (machineNumber == 4) {return 33;} else if (machineNumber == 0 && one == 1) {return 33;} else {return 22;}
		} else { 
			int err = 0;
			char tmpStr[20]; char tmp2[20]; sprintf(tmpStr, "%05llu", inst[i]);

			for (int k = 0; k < 4; k++) {
				tmp2[k] = tmpStr[strlen(tmpStr)-(3-k)-1];
			}
			long long mypos;
			if (inst[i] > 20000)  {
				mypos = relativeBase[machineNumber] + inst[i+3];
			} else {
				mypos = inst[i+3];
			}
			if (tmp2[2] != '0') {
				printf("tmp2... not zero... [[ %s ]]\n", tmp2);  exit(0);
			}
			tmp2[4] = '\0';
#ifdef _DEBUG_
			printf("NOW: %s\n", tmp2); 
#endif
			long long val1, val2, ans;

			if (tmp2[1] == '0') {

				val1 = inst[inst[i+1]]; 
#ifdef _DEBUG_
				printf("(pos0) val1 %lld\n", inst[inst[i+1]]);
#endif
			}
			else if (tmp2[1] == '1') {


				val1 = inst[i+1];
#ifdef _DEBUG_
				printf("(Npos1) val1 %lld\n", val1);
#endif
			} 
			else if (tmp2[1] == '2') {val1 = inst[relativeBase[machineNumber]+inst[i+1]];
				printf("(Rpos1) val1 %lld\n", val1);
#ifdef _DEBUG_
#endif
			} 
			else { printf("HERE"); /*getchar();*/ val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

			if (myINST != 9) {
				if (tmp2[0] == '0') {val2 = inst[inst[i+2]];
#ifdef _DEBUG_
					printf("(pos0) val2 %lld\n", val2);
#endif
				} else if (tmp2[0] == '1') {val2 = inst[i+2];
#ifdef _DEBUG_
					printf("(Npos1) val2 %lld\n", val2);
#endif
				} else if (tmp2[0] == '2') {val2 = inst[relativeBase[machineNumber]+inst[i+2]];
#ifdef _DEBUG_
					printf("(Rpos2) val2 %lld\n", val2);
#endif
				} else { printf("HERE2"); /*getchar(); */val2 = inst[i+2];}
			} else {
				printf("GOT A NINE\n"); //getchar();
			}

			if (myINST == 2) {
#ifdef _DEBUG_
				printf("%lld **** %lld\n", val1, val2);
#endif
				ans = val1 * val2;
			} else if (myINST == 1) {
#ifdef _DEBUG_
				printf("%lld ++++ %lld\n", val1, val2);
#endif
				ans = val1 + val2;
			} else if (myINST == 5) {
#ifdef _DEBUG_
				for (int i = 0; i < instTOT; i++) {
					printf("%lld,", inst[i]);
				} printf("\n");
				printf("val1 is %lld\n", val1); 
#endif
				if (val1 != 0) {
#ifdef _DEBUG_
					printf("NONZ: JUMP to (%lld)\n", val2);
#endif
					i = val2-1; err = 2;
				} else {
#ifdef _DEBUG_
					printf("ZNOJUMP (%lld)\n", val1);
#endif
					err = 1;} 
			} else if (myINST == 6) {
				if (val1 == 0) {
#ifdef _DEBUG_
					printf("ZERO: JUMP to (%lld)\n", val2);
#endif
					i = val2-1; err = 2;
				} else {
#ifdef _DEBUG_
					printf("NONZ NOJMP (%lld)\n", val1);
#endif
					err = 1;}
			} else if (myINST == 7) {
				if (val1 < val2) {ans = 1;} else {ans = 0;}
#ifdef _DEBUG_
				printf("%lld <<<<< %lld\n", val1, val2); 
#endif
			} else if (myINST == 8) {
				if (val1 == val2) {ans = 1;} else {ans = 0;}
#ifdef _DEBUG_
				printf("%lld ===== %lld\n", val1, val2); 
#endif
			} else if (myINST == 9) {
				relativeBase[machineNumber] += val1;
#ifdef _DEBUG_
				printf("relativeBase Change (+%lld) -> %lld\n", val1, relativeBase[machineNumber]); 
#endif
				err = 11;
			} else {
				printf("UNK: **ERROR: instruction[i][3] (%d) [%c%c]\n", i, instruction[i][2], instruction[i][3]); exit(0);
				err = 10;
				//getchar();
			}

			if (err == 0) {
#ifdef _DEBUG_
				printf("ANS (%lld) -> pos (i+3:%d) %lld (mypos %lld)\n", ans, i+3, inst[i+3], mypos); fflush(stdout);
#endif
				inst[mypos] = ans;
				char ansS[10]; sprintf(ansS, "%lld", ans); strcpy(instruction[mypos], ansS);
				i += 3;
			} else if (err == 1) {
				i += 2;
			} else if (err == 11) {
				i += 1;
			} else if (err != 2) {
				i += 3;
			} //err2 is JMP //err10 = UNK
		} 
	}
	//printf("output CONOR %lld COUNT %d\n", output, count); //getchar(); getchar();
	//if (output > outputMAX) {outputMAX = output; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
	//printf("output: %lld\n", output);
	return 10;
}
void printit() {
	for (int y = 0; y < SY+2; y++) { 
		for (int x = 0; x<SX+2; x++) {
			if (x == xCur && y == yCur) {
				printf("D");
			} else {
				printf("%c", grid[y][x]);
			}
		} 
		printf("\n");
	} printf("\n");
}

void ne(int x, int y, int endX, int endY, int px, int py, int dir, int turn, int path, char move) {
	//printf("in ne... x,y %d,%d\n", x, y);
	if (endX == x && endY == y) { printf("end reached"); return; }
	if (grid[y][x] == '.') {printf("DOT\n"); return;}
	if (x < 0 || x > SX || y < 0 || y > SY) {printf("OOR\n"); return;}
	if (turn == 'y') {printf(":%d %c", path - pathPrev, move); pathPrev = path;}
	if (already[y][x] == -1 || grid[y][x] == 'o') {
		already[y][x] = 1;
		if (dir == 'U' && (grid[y-1][x] == '#'  || grid[y-1][x] == 'o')&& (already[y-1][x] == -1 || grid[y-1][x] == 'o') && y-1 >= 0 ) {
			ne(x, y-1, endX, endY, x, y, 'U', 'n', path+1, 'S');
			return;
		} else if (dir == 'D' && (grid[y+1][x] == '#'  || grid[y+1][x] == 'o')&& (already[y+1][x] == -1 || grid[y+1][x] == 'o') && y+1 < SY) {
			ne(x, y+1, endX, endY, x, y, 'D', 'n', path+1, 'S');
			return;
		} else if (dir == 'R' && (grid[y][x+1] == '#'  || grid[y][x+1] == 'o')&& (already[y][x+1] == -1 || grid[y][x+1] == 'o') && x+1 < SX) {
			ne(x+1, y, endX, endY, x, y, 'R', 'n', path+1, 'S'); 
			return;
		} else if (dir == 'L' && (grid[y][x-1] == '#' || grid[y][x-1] == 'o') && (already[y][x-1] == -1 || grid[y][x-1] == 'o') && x-1 >= 0) {
			ne(x-1, y, endX, endY, x, y, 'L', 'n', path+1, 'S');
			return;
		} else if (dir == 'U' && (grid[y][x-1] == '#'  || grid[y][x-1] == 'o')&& (already[y][x-1] == -1|| grid[y][x-1] == 'o')  && x-1 >= 0) {
			ne(x-1, y, endX, endY, x, y, 'L', 'y', path+1, 'L');
			return;
		} else if (dir == 'U' && (grid[y][x+1] == '#'  || grid[y][x+1] == 'o')&& (already[y][x+1] == -1 || grid[y][x+1] == 'o') && x+1 < SX) {
			ne(x+1, y, endX, endY, x, y, 'R', 'y', path+1, 'R'); 
			return;
		} else if (dir == 'D' && (grid[y][x+1] == '#'  || grid[y][x+1] == 'o')&& (already[y][x+1] == -1 || grid[y][x+1] == 'o') && x+1 < SX) {
			ne(x+1, y, endX, endY, x, y, 'R', 'y', path+1, 'L');
			return;
		} else if (dir == 'D' && (grid[y][x-1] == '#'  || grid[y][x-1] == 'o')&& (already[y][x-1] == -1 || grid[y][x-1] == 'o') && x-1 >= 0) {
			ne(x-1, y, endX, endY, x, y, 'L', 'y', path+1, 'R'); 
			return;
		} else if (dir == 'L' && (grid[y+1][x] == '#'  || grid[y+1][x] == 'o')&& (already[y+1][x] == -1 || grid[y+1][x] == 'o') && y+1 < SY) {
			ne(x, y+1, endX, endY, x, y, 'D', 'y', path+1, 'L');
			return;
		} else if (dir == 'L' && (grid[y-1][x] == '#'  || grid[y-1][x] == 'o')&& (already[y-1][x] == -1 || grid[y-1][x] == 'o') && y-1 >= 0) {
			ne(x, y-1, endX, endY, x, y, 'U', 'y', path+1, 'R'); 
			return;
		} else if (dir == 'R' && (grid[y-1][x] == '#'  || grid[y-1][x] == 'o')&& (already[y-1][x] == -1 || grid[y-1][x] == 'o') && y-1 >= 0) {
			ne(x, y-1, endX, endY, x, y, 'U', 'y', path+1, 'L'); 
			return;
		} else if (dir == 'R' && (grid[y+1][x] == '#'  || grid[y+1][x] == 'o')&& (already[y+1][x] == -1 || grid[y+1][x] == 'o') && y+1 < SY) {
			ne(x, y+1, endX, endY, x, y, 'D', 'y', path+1, 'R'); 
			return;
		}
	}
}
