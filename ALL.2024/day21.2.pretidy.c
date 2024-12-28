#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>

//huge nums in this (add -I. to compile)
#include <bigintclass.h>
#include <bigint_function_definitions.h>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
unsigned long long minLLL;
unsigned long long cur;
int maxLevelSoFar = 0;
void sigfunc(int a) { printf("current minLLL: [[ %llu ]] cur:%llu maxLevelSoFar: (%d)\n", minLLL, cur, maxLevelSoFar); }
char grid2[2][3] = {{' ', '^', 'A'}, {'<', 'v', '>'}};
char grid1[4][3] = {{'7', '8', '9'}, {'4','5','6'}, {'1', '2', '3'}, {' ', '0', 'A'}};
int lenx;
int leny;
int numbers[10];
char numbersS[10][10];
unsigned long long robotARM(string, int numRobot, int reset, char startChar);
int startRow = 3; int startCol = 2;
unsigned long long calcLen(struct content_s aa);

int checkCol(int mvCol, int row, int col, int isrobot);
int checkRow(int mvRow, int srow, int scol, int isrobot);
void moveRow(int mvRow, string &);
void moveCol(int mvCol, string &);
string ans2;
string ans;
//vector <string> veStr;
deque <string> veStr;
deque <string> veStrRobot[40];
struct content_s {
	char first;
	unsigned long long keys[6][6];
	char last;
};
int getIndex(char aa);
char getTheChar(int aa);

deque <struct content_s> veStrRobotNEW[40];
map <tuple<string, int, char>, tuple<unsigned long long, string, vector<string>>> mp;
map <tuple<string, int, char>, tuple<unsigned long long, string, vector<string>>> mpTRY;
map <tuple<string, int, char>, tuple<unsigned long long, string, vector<struct content_s>>> mpNEW;
map <tuple<string, int, char>, tuple<unsigned long long, string, vector<struct content_s>>> mpNEW2;
int fd;
int LEVEL = 2;
void getLevel1Maps();
unsigned long long getNextLevel(string st2, string from, int level, char bb2);
unsigned long long robotARMNEW(string ans, int robotNum, int reset, char prev);
unsigned long long getNextLevelNEW(string st2, string from, int level, char bb2);
void resetContent(struct content_s & cont);
unsigned long long robotARMNEW2(struct content_s ans, int robotNum, int reset, char prev);
unsigned long long getNextLevelNEW2(struct content_s abab, string fromst2, int level, char bb2);
unsigned long long getNextLevelNEW2Level3(struct content_s abab, string st2, int level, char bb2, struct content_s & retCont);

unsigned long long calcLen(struct content_s aa) {
	unsigned long long len = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			len += aa.keys[i][j];
		}
	}
	return len;
}

void getLevel1Maps() {
	string check = "^>v<A";

	string cOrig = check;
/*
	for (int kk = 0; kk < (int)check.length(); kk++) {
		check = cOrig;
		string st2 = check.substr(kk, 1);
		string check2 = cOrig;
		for (int bb = 0; bb < (int)check2.length(); bb++) {
			char bb2 = check2[bb];
			unsigned long long minLength = 999999999999999999;
			int p1 = -1;
			string minStr;	
			vector <string> poss;
			//int minL2 = 999999999999999999;
			{
				p1++;
				//cout << "***HERE1sending in : " << st2 << " starting: " << bb2  << endl;
				veStrRobot[1].clear();
				//veStrRobotNEW[1].clear();
				robotARM(st2, 1, 0, bb2);
				//robotARMNEW(st2, 1, 0, bb2);
				{
					unsigned long long min5 = 999999999999999999;
					unsigned long long min6 = 999999999999999999;
					unsigned long long min7 = 999999999999999999;
					for (auto st4: veStrRobot[1]) {
						if ((unsigned long long)st4.length() < minLength) {minStr = st4; minLength = st4.length();}
					}

					int numx = 0;
					for (auto st4: veStrRobot[1]) {
						if ((unsigned long long)st4.length() != minLength) {numx++; continue;}
						//printf("%d of %d\n", numx++, (int)veStrRobot[1].size());
						veStrRobot[2].clear();
						robotARM(st4, 2, 1, bb2);
						int num = 0;
						for (auto st5: veStrRobot[2]) {
							if ((unsigned long long)st5.length() < min5) {num++; min5 = st5.length();}
						}
						int num2 = 0;
						for (auto st5: veStrRobot[2]) {
							if ((unsigned long long)st5.length() != min5) {num2++; continue;}
							//printf("%d of num %d\n", num2++, (int)veStrRobot[2].size());
							veStrRobot[3].clear();
							robotARM(st5, 3, 1, bb2);
							for (auto st6: veStrRobot[3]) {
								if ((unsigned long long)st6.length() < min6) {min6 = st6.length();}
							}
						}
					}
					mpTRY[{st2, 2, bb2}] = make_tuple(min5, minStr, poss);
					mpTRY[{st2, 3, bb2}] = make_tuple(min6, minStr, poss);
					mpTRY[{st2, 4, bb2}] = make_tuple(min7, minStr, poss);
					for (auto st4: veStrRobot[1]) {
						//printf("possibles are st4: %s\n", st4.c_str());
						//printf("possibles len %d\n", (int)st4.length());
						if ((unsigned long long)st4.length() == minLength) {
							poss.push_back(st4); 
						}
						//if ((int)st4.length() < minLength) {minStr = st4; minLength = st4.length();}
					}
					mpTRY[{st2, 1, bb2}] = make_tuple(minLength, minStr, poss);
				}
			}
		}
	}
*/

	printf("starting the level 2s -- \n");
	cOrig = check;
	for (int kk = 0; kk < (int)check.length(); kk++) {
		check = cOrig;
		string st2 = check.substr(kk, 1);
		string check2 = cOrig;
		for (int bb = 0; bb < (int)check2.length(); bb++) {
			char bb2 = check2[bb];
			unsigned long long minLength = 999999999999999999;
			int p1 = -1;
			string minStr;	
			vector <string> poss;
			unsigned long long minL2 = 999999999999999999;
			{
				p1++;
				//cout << "***HERE1sending in : " << st2 << " starting: " << bb2  << endl;
				veStrRobot[1].clear();
				veStrRobotNEW[1].clear();
				//robotARM(st2, 1, 0, bb2);
				robotARMNEW(st2, 1, 0, bb2);
				{
					for (auto st4: veStrRobot[1]) {
						if ((unsigned long long)st4.length() < minLength) {minStr = st4; minLength = st4.length();}
					}
					for (auto st4: veStrRobot[1]) {
						//printf("possibles are st4: %s\n", st4.c_str());
						//printf("possibles len %d\n", (int)st4.length());
						if ((unsigned long long)st4.length() == minLength) {
							poss.push_back(st4); 
						}
						//if ((int)st4.length() < minLength) {minStr = st4; minLength = st4.length();}
					}
				}
				mp[{st2, 1, bb2}] = make_tuple(minLength, minStr, poss);
				///////////////////				
				minL2 = 999999999999999999;
				for (auto st4: veStrRobotNEW[1]) {
					unsigned long long len = calcLen(st4);
					if (len < minL2) {minL2 = len;}
				}
				vector <struct content_s> possNEW;
				for (auto st4: veStrRobotNEW[1]) {
					unsigned long long len = calcLen(st4);
					//printf("calcLen is %llu\n", len);
					if (len == minL2) {minStr = ""; possNEW.push_back(st4);}	
				}
				mpNEW[{st2, 1, bb2}] = make_tuple(minL2, minStr, possNEW);
				///////////////////
				//bigint minLN2 = ("99999999999999999999999");
				unsigned long long minLN2 = 9999999999999999;
				
				for (auto st4: veStrRobotNEW[1]) {
					unsigned long long len = calcLen(st4);
					if (len < minLN2) {minLN2 = len;}
				}
				vector <struct content_s> possNEW2;
				for (auto st4: veStrRobotNEW[1]) {
					unsigned long long len = calcLen(st4);
					//printf("--calcLen is %d\n", len);
					if (len == minLN2) {minStr = ""; possNEW2.push_back(st4);}	
				}
				printf("possNEW2 size is (%d)\n", (int)possNEW2.size());
				mpNEW2[{st2, 1, bb2}] = make_tuple(minLN2, "", possNEW2);
				//printf("here1...\n");
				//printf("minLength: %d of %s is (%s)\n", minLength, st2.c_str(), minStr.c_str());

			}
		}
		//cout << st2 << " getchar " << endl;
	}

	for (int ijk = 2; ijk <= 25; ijk++) 
	{
		for (int kk = 0; kk < (int)check.length(); kk++) {
			check = cOrig;
			string st2 = check.substr(kk, 1);
			string check2 = cOrig;
			for (int bb = 0; bb < (int)check2.length(); bb++) {
				char bb2 = check2[bb];
				//int p1 = -1;
				string minStr;	
				{
					auto pa1234 = mpNEW2[{st2, ijk-1, bb2}];
					vector <struct content_s> possNEW23 = get<2>(pa1234);
					vector <struct content_s> dummyNEW23;
					//bigint minLenNEW23("9999999999999999999999");
					unsigned long long minLenNEW23 = 9999999999999999;
					//bitint minLenNEW23 = 99999999999999999999999;
					struct content_s retCont;
					resetContent(retCont);

					for (auto st55: possNEW23) {
						unsigned long long retLenNEW23 = getNextLevelNEW2Level3(st55, st2, ijk, bb2, retCont);
						//printf("getNextLevelNEW2 returned %llu\n", retLenNEW23);
						if (retLenNEW23 < minLenNEW23) {minLenNEW23 = retLenNEW23;}
					}
					for (auto st55: possNEW23) {
						unsigned long long retLenNEW23 = getNextLevelNEW2(st55, st2, ijk, bb2);
						if (retLenNEW23 == minLenNEW23) {minLenNEW23 = retLenNEW23; dummyNEW23.push_back(st55);}
					}
					mpNEW2[{st2, ijk, bb2}] = make_tuple(minLenNEW23, minStr, dummyNEW23);
					//printf("setting minLenNEW2 to %llu\n", minLenNEW23);

				}
			}
			//cout << st2 << " getchar " << endl;
		}
	}
}
unsigned long long getNextLevelNEW2Level3(struct content_s abab, string st2, int level, char bb2, struct content_s & retCont) {
	//char bef = 'A';
	unsigned long long size = 0;

	///	for (int i = 0; i < (int)st2.length(); i++) {
	for (int ii = 0; ii < 5; ii++) {
		for (int jj = 0; jj < 5; jj++) {
			char firstC = getTheChar(ii);
			char secondC = getTheChar(jj);
			string abc;
			abc.push_back(firstC);
			abc.push_back(secondC);
			string abcd; abcd.push_back(secondC);
			auto pa = mpNEW2[{abcd, level-1, firstC}];
			size += abab.keys[ii][jj] * get<0>(pa);
			//printf("size is %llu\n", size);
			retCont.keys[ii][jj] = abab.keys[ii][jj] * get<0>(pa);
		}
	}
	//bef = st2[i];//not used	
	//	}
	return size;
}
unsigned long long getNextLevelNEW2(struct content_s abab, string st2, int level, char bb2) {
	//char bef = 'A';
	unsigned long long size = 0;

	///	for (int i = 0; i < (int)st2.length(); i++) {
	for (int ii = 0; ii < 5; ii++) {
		for (int jj = 0; jj < 5; jj++) {
			char firstC = getTheChar(ii);
			char secondC = getTheChar(jj);
			string abc;
			abc.push_back(firstC);
			abc.push_back(secondC);
			string abcd; abcd.push_back(secondC);
			auto pa = mpNEW2[{abcd, level-1, firstC}];
			size += abab.keys[ii][jj] * get<0>(pa);
		}
	}
	//bef = st2[i];//not used	
	//	}
	return size;
}
unsigned long long getNextLevelNEW(string st2, string from, int level, char bb2) {
	char bef = 'A';
	unsigned long long size = 0;
	string outstr = "";
	for (int i = 0;  i < (int)st2.length(); i++) {
		string aaa = ""; aaa.push_back(st2[i]);

		tuple pa = mpNEW[{aaa, level-1, bef}];
		size += get<0>(pa);
		if (size == 0) {printf("size zero\n"); getchar();}
		//assert(size != 0);
		outstr += get<1>(pa);
		bef = st2[i];
	}
	return size;
}
unsigned long long getNextLevel(string st2, string from, int level, char bb2) {
	char bef = 'A';
	unsigned long long size = 0;
	string outstr = "";
	for (int i = 0;  i < (int)st2.length(); i++) {
		string aaa = ""; aaa.push_back(st2[i]);

		tuple pa = mp[{aaa, level-1, bef}];
		size += get<0>(pa);
		if (size == 0) {printf("size zero\n"); getchar();}
		//assert(size != 0);
		outstr += get<1>(pa);
		bef = st2[i];
	}
	return size;
}

int main(int argc, char **argv)
{
	//fd = dup(1); close(1);

	if (argc == 3) {LEVEL = atoi(argv[2]);}
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 21 Part 2\n"); fflush(stdout);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		numbers[leny] = atoi(line1);
		strcpy(numbersS[leny], line1);

		leny++;
	}
	fclose(a);

	for (int i = 0; i < leny; i++) {
		//printf("%d\n", numbers[i]);
		//printf("%s\n", numbersS[i]);
	}
	getLevel1Maps();

	//getLevel2Maps();

	veStrRobot[1].clear();
	veStrRobot[2].clear();


	//1st robot
	//789
	//456
	//123
	//char start = 'A';
	//unsigned long long conans = 0;
	bigint conans(0);
	for (int i = 0; i < leny; i++) {
		printf("working on %s (%d)\n", numbersS[i], numbers[i]);
		//startRow = 3; startCol = 2;
		if (startRow != 3 && startCol != 2) {printf("ERR\n"); exit(0);}
		ans = "";
		veStr.clear();
		veStrRobot[1].clear();
		veStrRobot[2].clear();
		for (int jj = 0; jj < (int)strlen(numbersS[i]); jj++) {
			char wat = numbersS[i][jj];
			//find numbersS[i][jj]
			//findRow
			//findColumn

			for (int row = 0; row < 4; row++) {
				for (int col = 0; col < 3; col++) {
					if (grid1[row][col] == wat) {
						int mvRow = row - startRow;
						int mvCol = col - startCol;
						//printf("wat is %c found @ col,row %d,%d mov:%d,%d\n", wat, col, row, mvCol, mvRow);
						if (checkRow(mvRow, startRow, startCol, 0) == -1) {
							//printf("checkRow fail\n"); 
						}
						string ans3 = "";
						if (checkCol(mvCol, startRow, startCol, 0) == -1) {
							moveRow(mvRow, ans3);
							moveCol(mvCol, ans3);
						} else {
							moveCol(mvCol, ans3);
							moveRow(mvRow, ans3);
						}
						sort(ans3.begin(), ans3.end());
						int numPerms = 0;
						string per[10];
						deque<string>veTmp;
						do {
							per[numPerms] = ans3;
							numPerms++;
						} while (next_permutation(ans3.begin(), ans3.end()));
						if (numPerms == 1) {
							//ans += ans3;
							if (veStr.size() == 0) {
								veTmp.push_back(ans3+"A");
							} else {
								for (auto st: veStr) {
									veTmp.push_back(st+ans3+"A");
								} 
							}
						} else {
							if (veStr.size() == 0) {
								for (int ii = 0; ii < numPerms; ii++) {
									int row1 = startRow; int col1 = startCol;
									for (auto c1: per[ii]) {
										switch(c1) {
											case '^':
												if (checkRow(-1, row1, col1, 0) == -1) {goto aft;} else {row1--;}
												break;
											case '>':
												if (checkCol(+1, row1, col1, 0) == -1) {goto aft;} else {col1++;}
												break;
											case 'v':
												if (checkRow(1, row1, col1, 0) == -1) {goto aft;} else {row1++;}
												break;	
											case '<':
												if (checkCol(-1, row1, col1, 0) == -1) {goto aft;} else {col1--;}
												break;
										}
									}	
									veTmp.push_back(per[ii]+"A");
aft:
									continue;

								}
							} else {
								for (auto st: veStr) {
									for (int ii = 0; ii < numPerms; ii++) {
										int row1 = startRow; int col1 = startCol;
										for (auto c1: per[ii]) {
											switch(c1) {
												case '^':
													if (checkRow(-1, row1, col1, 0) == -1) {goto aft2;} else {row1--;}
													break;
												case '>':
													if (checkCol(+1, row1, col1, 0) == -1) {goto aft2;} else {col1++;}
													break;
												case 'v':
													if (checkRow(1, row1, col1, 0) == -1) {goto aft2;} else {row1++;}
													break;	
												case '<':
													if (checkCol(-1, row1, col1, 0) == -1) {goto aft2;} else {col1--;}
													break;
											}
										}	
										veTmp.push_back(st+per[ii]+"A");
aft2:
										continue;
									}
								}
							}
						}
						veStr = veTmp;
						//cout << "st2 vals: " << endl;
						//for (auto st2: veStr) { cout << st2 << endl; } cout << "after st2 vals...\n"; getchar();

						startRow = row;
						startCol = col;
						goto ne;
					}
				}
			}
ne:
			continue;
		}

		minLLL = 999999999999999999;
		int p1 = -1;
		string prop;
		string propst3;
		for (auto st1: veStr) {
			p1++;
			//cout << "HERE3sending in : " << st2 << " " << p1 <<  " of " << veStr.size() << endl; getchar();
			veStrRobot[1].clear();
			robotARM(st1, 1, 1, 'A');

			for (auto st2: veStrRobot[1]) {
				veStrRobot[2].clear();
				robotARM(st2, 2, 1, 'X');
				for (auto st3: veStrRobot[2]) {
					if (st3.length() < minLLL) {propst3 = st3; prop = st3; minLLL = (unsigned long long)st3.length();}
				}
			}
		}
		printf("minLLL is %llu\n", minLLL);

		/*
		///REMOVE HERE FOR NON RECURSE
		for (auto st2: veStrRobot[1]) {
		veStrRobot[2].clear();
		robotARM(st2, 2, 1, 'X');
		for (auto st3: veStrRobot[2]) {
		printf("Level3: %d\n", (int)veStrRobot[2].size());
		veStrRobot[3].clear();
		robotARM(st3, 3, 1, 'X');
		for (auto st4: veStrRobot[3]) {
		printf("Level4: %d\n", (int)veStrRobot[3].size());
		veStrRobot[4].clear();
		robotARM(st4, 4, 1, 'X');
		for (auto st5: veStrRobot[4]) {
		printf("Level5: %d\n", (int)veStrRobot[4].size());
		veStrRobot[5].clear();
		robotARM(st5, 5, 1, 'X');
		for (auto st6: veStrRobot[5]) {
		veStrRobot[6].clear();
		robotARM(st6, 6, 1, 'X');
		for (auto st7: veStrRobot[6]) {
		veStrRobot[7].clear();
		robotARM(st7, 7, 1, 'X');
		for (auto st8: veStrRobot[7]) {
		veStrRobot[8].clear();
		robotARM(st8, 8, 1, 'X');
		for (auto st9: veStrRobot[8]) {
		veStrRobot[9].clear();
		robotARM(st9, 9, 1, 'X');
		for (auto st10: veStrRobot[9]) {
		veStrRobot[10].clear();
		robotARM(st10, 10, 1, 'X');
		for (auto st11: veStrRobot[10]) {
		veStrRobot[11].clear();
		robotARM(st11, 11, 1, 'X');
		for (auto st12: veStrRobot[11]) {
		veStrRobot[12].clear();
		robotARM(st12, 12, 1, 'X');
		for (auto st13: veStrRobot[12]) {
		veStrRobot[13].clear();
		robotARM(st13, 13, 1, 'X');
		for (auto st14: veStrRobot[13]) {
		if (st14.length() < minLLL) {minLLL = st14.length();}
		}
		}
		}
		}
		}
		}
		}
		}
		}
		}
		}
		}
		}
		}
		 */


/*
		//if (st12.length() < minLength) {minLength = st12.length();}
		{
			unsigned long long minLengthTest = 999999999999999999; 
			string got1;
			for (auto st2: veStr) {
				//cout << "Trying: " << st2 << endl;
				int minSub = 0;
				char crPrev = 'A';
				for (auto cr: st2) {
					string ab;
					ab.push_back(cr);
					tuple <int, string, vector<string>> tu11 = mpTRY[{ab, 4, crPrev}];
					minSub += get <0>(tu11); 
					crPrev = cr;

				}
				//printf("XXXXminSub is %d\n", minSub);
				if (minSub < (int)minLengthTest) {minLengthTest = minSub; got1 = st2;}
			}
			printf("LEVEL 4.... %llu\n", minLengthTest);
		}
		{
			unsigned long long minLengthTest = 999999999999999999; 
			string got1;
			for (auto st2: veStr) {
				//cout << "Trying: " << st2 << endl;
				int minSub = 0;
				char crPrev = 'A';
				for (auto cr: st2) {
					string ab;
					ab.push_back(cr);
					tuple <int, string, vector<string>> tu11 = mpTRY[{ab, 3, crPrev}];
					minSub += get <0>(tu11); 
					crPrev = cr;

				}
				//printf("XXXXminSub is %d\n", minSub);
				if (minSub < (int)minLengthTest) {minLengthTest = minSub; got1 = st2;}
			}
			printf("LEVEL 3.... %llu\n", minLengthTest);
		}
		unsigned long long minLengthTest = 999999999999999999; 
		string got1;
		for (auto st2: veStr) {
			//cout << "Trying: " << st2 << endl;
			int minSub = 0;
			char crPrev = 'A';
			for (auto cr: st2) {
				string ab;
				ab.push_back(cr);
				tuple <int, string, vector<string>> tu11 = mp[{ab, 2, crPrev}];
				minSub += get <0>(tu11); 
				crPrev = cr;

			}
			//printf("XXXXminSub is %d\n", minSub);
			if (minSub < (int)minLengthTest) {minLengthTest = minSub; got1 = st2;}
		}
		unsigned long long minLength3 = 999999999999999999; 
		string got2;
		for (auto st2: veStr) {
			//cout << "Trying: " << st2 << endl;
			int minSub = 0;
			char crPrev = 'A';
			for (auto cr: st2) {
				string ab;
				ab.push_back(cr);
				tuple <int, string, vector<struct content_s>> tu11 = mpNEW[{ab, 2, crPrev}];
				minSub += get <0>(tu11); 
				crPrev = cr;

			}
			//printf("XXXXminSub is %d\n", minSub);
			if (minSub < (int)minLength3) {minLength3 = minSub; got2 = st2;}
		}

		unsigned long long minLength4 = 999999999999999999;
		for (auto st2: veStr) {
			//cout << "Trying: " << st2 << endl;
			int minSub = 0;
			char crPrev = 'A';
			for (auto cr: st2) {
				string ab;
				ab.push_back(cr);
				tuple <int, string, vector<struct content_s>> tu11 = mpNEW2[{ab, 2, crPrev}];
				minSub += get <0>(tu11); 
				crPrev = cr;
			}
			//printf("XXXXminSub is %d\n", minSub);
			if (minSub < (int)minLength4) {minLength4 = minSub;}
		}

		unsigned long long minLength5 = 999999999999999999;
		for (auto st2: veStr) {
			int minSub = 0;
			char crPrev = 'A';
			for (auto cr: st2) {
				string ab;
				ab.push_back(cr);
				tuple <int, string, vector<struct content_s>> tu11 = mpNEW2[{ab, 3, crPrev}];
				minSub += get <0>(tu11); 
				crPrev = cr;
			}
			//printf("XXXXminSub is %d\n", minSub);
			if (minSub < (int)minLength5) {minLength5 = minSub;}
		}
		{
			unsigned long long minLength6 = 999999999999999999;
			for (auto st2: veStr) {
				int minSub = 0;
				char crPrev = 'A';
				for (auto cr: st2) {
					string ab;
					ab.push_back(cr);
					tuple <int, string, vector<struct content_s>> tu11 = mpNEW2[{ab, 4, crPrev}];
					minSub += get <0>(tu11); 
					crPrev = cr;
				}
				//printf("XXXXminSub is %d\n", minSub);
				if (minSub < (int)minLength6) {minLength6 = minSub;}
			}
			printf("LEVEL 4 -- quick way:: %llu\n", minLength6);
		}
*/
		for (int i25 = 3; i25 <= 25; i25++) 
		{
			unsigned long long minLength252525 = 999999999999999999;
			for (auto st2: veStr) {
				unsigned long long minSub = 0;
				char crPrev = 'A';
				for (auto cr: st2) {
					string ab;
					ab.push_back(cr);
					//tuple <int, string, vector<struct content_s>> tu11 = mpNEW2[{ab, i25, crPrev}];
					auto  tu11 = mpNEW2[{ab, i25, crPrev}];
					minSub += get <0>(tu11); 
					crPrev = cr;
				}
				//printf("XXXXminSub is %d\n", minSub);
				if (minSub < minLength252525) {minLength252525 = minSub;}
			}
			printf("LEVEL %d -- quick way:: %llu\n", i25, minLength252525);
		}


		int lev25 = 25;
		//unsigned long long minLength25 = 999999999999999999;
		bigint minLength25 = bigint("999999999999999999999999");
		for (auto st2: veStr) {
			//unsigned long long minSub = 0;
			bigint minSub = bigint(0);
			char crPrev = 'A';
			for (auto cr: st2) {
				string ab;
				ab.push_back(cr);
				//tuple <int, string, vector<struct content_s>> tu11 = mpNEW2[{ab, lev25, crPrev}];
				auto tu11 = mpNEW2[{ab, lev25, crPrev}];
				
				minSub += bigint(to_string(get <0>(tu11))); 
				crPrev = cr;
			}
			//printf("XXXXminSub is %d\n", minSub);
			if (minSub < minLength25) {minLength25 = minSub;}
		}
		printf("LEVEL 25 min (using): "); cout <<  minLength25 << endl;

		//printf("test:(both:%s) %d V %llu:proper(%s)(%s)\n", got1.c_str(), minLengthTest, minLength, prop.c_str(), propst3.c_str());
		//printf("minLLL:%llu V %llu: minLengthTest VV minLength3:%llu VVVV minLength4:%llu level3:(%llu)\n", minLLL, minLengthTest, minLength3, minLength4, minLength5);
		//part1
		//conans += minLLL * numbers[i];
		///printf("%llu * %d\n", minLLL, numbers[i]); //getchar();
		//part2
		conans += minLength25 * (bigint)numbers[i];

}
//dup2(fd, 1);
//dup2(fd, 1);
printf("**ans: ");
//printf("**ans: %llu\n", conans);
cout << conans << endl;
}

unsigned long long robotARMNEW2(struct content_s ans, int robotNum, int reset, char prev) {
	/*
	   int startRowRobot, startColRobot;
	   if (reset == 1) {
	   startRowRobot = 0; startColRobot = 2;
	   } else {
	   for (int row = 0; row < 2; row++) {
	   for (int col = 0; col < 3; col++) {
	   if (grid2[row][col] == prev) {
	   startRowRobot = row;
	   startColRobot = col;
	   }
	   }
	   }
	   }

	 */
	int size = 0;
	for (int ii = 0; ii < 5; ii++) {
		for (int jj = 0; jj < 5; jj++) {
			string aaa = "";
			aaa.push_back(getTheChar(ii));
			aaa.push_back(getTheChar(jj));
			tuple pa = mpNEW[{aaa, 1, prev}];

			size += get<0>(pa);
			ans.keys[ii][jj] = ans.keys[ii][jj] * size;
			prev = 'A';
		}
	}
	return size;
}
unsigned long long robotARMNEW(string ans, int robotNum, int reset, char prev) {

	if (robotNum > maxLevelSoFar) {maxLevelSoFar = robotNum;}
	if (robotNum > 2) { if (cur++ % 1000 == 0) { printf("LEVEL: (%d) times:%llu\n", robotNum, cur);}}
	ans2 = "";
	int startRowRobot, startColRobot;
	if (reset == 1) {
		startRowRobot = 0; startColRobot = 2;
	} else {
		for (int row = 0; row < 2; row++) {
			for (int col = 0; col < 3; col++) {
				if (grid2[row][col] == prev) {
					startRowRobot = row;
					startColRobot = col;
				}
			}
		}
	}
	for (int ii = 0; ii < (int)ans.length(); ii++) {
		char wat = ans[ii];
		for (int row = 0; row < 2; row++) {
			for (int col = 0; col < 3; col++) {
				if (grid2[row][col] == wat) {
					int mvRow = row - startRowRobot;
					int mvCol = col - startColRobot;
					//printf("wat is %c found @ col,row %d,%d mov:%d,%d\n", wat, col, row, mvCol, mvRow);

					if (checkRow(mvRow, startRowRobot, startColRobot, 1) == -1) {
						//printf("checkRow fail (robot)\n");
					}
					string ans3 = "";
					if (checkCol(mvCol, startRowRobot, startColRobot, 1) == -1) {
						//printf("*****got minus 1 position ii:%d %c\n", ii, wat); getchar();
						if (checkRow(mvRow, startRowRobot, startColRobot, 1) == -1) {
							printf("oopsRobot - err\n"); exit(0);
						}
						moveRow(mvRow, ans3);
						moveCol(mvCol, ans3);
					} else {
						moveCol(mvCol, ans3);
						moveRow(mvRow, ans3);
					}

					sort(ans3.begin(), ans3.end());
					int numPerms = 0;
					string per[10];
					deque <string> veTmp;
					deque <struct content_s> veTmpNEW;
					struct content_s cont2;
					resetContent(cont2);
					string n1;
					do {
						per[numPerms] = ans3;
						numPerms++;
					} while (next_permutation(ans3.begin(), ans3.end()));
					if (numPerms == 1) {
						if (veStrRobot[robotNum].size() == 0) {
							veTmp.push_back(ans3+"A");
							prev = 'A';
						} else {
							for (auto st: veStrRobot[robotNum]) {
								veTmp.push_back(st+ans3+"A");
							}
							prev = 'A';
						}

						//prePend prev to ans3;
						//ans3 = prev+ans3;
						ans3 = prev+ans3+"A";
						if (veStrRobotNEW[robotNum].size() == 0) {
							//memset(cont2, 0, sizeof(cont2));
							resetContent(cont2);

							for (int kkk = 1; kkk < (int)ans3.length(); kkk++) {
								int firstI = getIndex(ans3[kkk-1]);
								int secondI = getIndex(ans3[kkk]);
								cont2.keys[firstI][secondI]++;
							}
							prev = 'A';
							veTmpNEW.push_back(cont2);
						} else {
							for (auto ct: veStrRobotNEW[robotNum]) {
								for (int kkk = 0; kkk < (int)ans3.length(); kkk++) {
									int firstI = getIndex(ans3[kkk-1]);
									int secondI = getIndex(ans3[kkk]);
									ct.keys[firstI][secondI]++;
								}
								prev = 'A';
								veTmpNEW.push_back(ct);
							}
						}
					} else {
						if (veStrRobot[robotNum].size() == 0) {
							for (int ii = 0; ii < numPerms; ii++) {
								int col1 = startColRobot; int row1 = startRowRobot;
								for (auto c1: per[ii]) {
									switch(c1) {
										case '^':
											if (checkRow(-1, row1, col1, 1) == -1) {goto aft3;} else {row1--;}
											break;
										case '>':
											if (checkCol(+1, row1, col1, 1) == -1) {goto aft3;} else {col1++;}
											break;
										case 'v':
											if (checkRow(1, row1, col1, 1) == -1) {goto aft3;} else {row1++;}
											break;	
										case '<':
											if (checkCol(-1, row1, col1, 1) == -1) {goto aft3;} else {col1--;}
											break;
									}
								}	
								veTmp.push_back(per[ii]+"A");
								prev = 'A';
aft3:
								continue;
							}
						} else {
							for (auto st: veStrRobot[robotNum]) {
								for (int ii = 0; ii < numPerms; ii++) {
									int col1 = startColRobot; int row1 = startRowRobot;
									for (auto c1: per[ii]) {
										switch(c1) {
											case '^':
												if (checkRow(-1, row1, col1, 1) == -1) {goto aft4;} else {row1--;}
												break;
											case '>':
												if (checkCol(+1, row1, col1, 1) == -1) {goto aft4;} else {col1++;}
												break;
											case 'v':
												if (checkRow(1, row1, col1, 1) == -1) {goto aft4;} else {row1++;}
												break;	
											case '<':
												if (checkCol(-1, row1, col1, 1) == -1) {goto aft4;} else {col1--;}
												break;
										}
									}	
									veTmp.push_back(st+per[ii]+"A");
									prev = 'A';
aft4:
									continue;
								}
							}
						}

						if (veStrRobotNEW[robotNum].size() == 0) {
							for (int ii = 0; ii < numPerms; ii++) {
								int col1 = startColRobot; int row1 = startRowRobot;
								for (auto c1: per[ii]) {
									switch(c1) {
										case '^':
											if (checkRow(-1, row1, col1, 1) == -1) {goto aft33;} else {row1--;}
											break;
										case '>':
											if (checkCol(+1, row1, col1, 1) == -1) {goto aft33;} else {col1++;}
											break;
										case 'v':
											if (checkRow(1, row1, col1, 1) == -1) {goto aft33;} else {row1++;}
											break;	
										case '<':
											if (checkCol(-1, row1, col1, 1) == -1) {goto aft33;} else {col1--;}
											break;
									}
								}	

								n1 = prev+per[ii]+"A";
								resetContent(cont2);
								for (int kkk = 1; kkk < (int)n1.length(); kkk++) {
									int firstI = getIndex(n1[kkk-1]);
									int secondI = getIndex(n1[kkk]);
									cont2.keys[firstI][secondI]++;
								}
								veTmpNEW.push_back(cont2);
								prev = 'A';
aft33:
								continue;
							}
						} else {
							for (auto ct: veStrRobotNEW[robotNum]) {
								for (int ii = 0; ii < numPerms; ii++) {
									int col1 = startColRobot; int row1 = startRowRobot;
									for (auto c1: per[ii]) {
										switch(c1) {
											case '^':
												if (checkRow(-1, row1, col1, 1) == -1) {goto aft44;} else {row1--;}
												break;
											case '>':
												if (checkCol(+1, row1, col1, 1) == -1) {goto aft44;} else {col1++;}
												break;
											case 'v':
												if (checkRow(1, row1, col1, 1) == -1) {goto aft44;} else {row1++;}
												break;	
											case '<':
												if (checkCol(-1, row1, col1, 1) == -1) {goto aft44;} else {col1--;}
												break;
										}
									}	

									n1 = prev+per[ii]+"A";
									for (int kkk = 1; kkk < (int)n1.length(); kkk++) {
										int firstI = getIndex(n1[kkk-1]);
										int secondI = getIndex(n1[kkk]);
										ct.keys[firstI][secondI]++;
									}
									veTmpNEW.push_back(ct);
									prev = 'A';
aft44:
									continue;
								}
							}
						}
					}
					veStrRobot[robotNum] = veTmp;
					veStrRobotNEW[robotNum] = veTmpNEW;

					startRowRobot = row;
					startColRobot = col;
					goto ne2;
				}
			}
		}
ne2:
		continue;

	}

	return 0;

}
void resetContent(struct content_s & cont) {
	for (int ii = 0; ii < 5; ii++) {
		for (int jj = 0; jj < 5; jj++) {
			cont.keys[ii][jj] = 0;
		}
	}
	cont.first = ' ';
	cont.last = ' ';
}
char getTheChar(int aa) {
	switch(aa) {
		case 0:
			return 'A';
		case 1:
			return '^';
		case 2:
			return '<';
		case 3:
			return 'v';
		case 4:
			return '>';
	}
	return -1;
}
int getIndex(char aa) {
	switch(aa) {
		case 'A':
			return 0;
		case '^':
			return 1;
		case '<':
			return 2;
		case 'v':
			return 3;
		case '>':
			return 4;
	}
	return -1;
}

unsigned long long robotARM(string ans, int robotNum, int reset, char prev) {

	if (robotNum > maxLevelSoFar) {maxLevelSoFar = robotNum;}
	if (robotNum > 2) { if (cur++ % 1000 == 0) { printf("LEVEL: (%d) times:%llu\n", robotNum, cur);}}
	ans2 = "";
	int startRowRobot, startColRobot;
	if (reset == 1) {
		startRowRobot = 0; startColRobot = 2;
	} else {
		for (int row = 0; row < 2; row++) {
			for (int col = 0; col < 3; col++) {
				if (grid2[row][col] == prev) {
					startRowRobot = row;
					startColRobot = col;
				}
			}
		}
	}
	for (int ii = 0; ii < (int)ans.length(); ii++) {
		char wat = ans[ii];
		for (int row = 0; row < 2; row++) {
			for (int col = 0; col < 3; col++) {
				if (grid2[row][col] == wat) {
					int mvRow = row - startRowRobot;
					int mvCol = col - startColRobot;
					//printf("wat is %c found @ col,row %d,%d mov:%d,%d\n", wat, col, row, mvCol, mvRow);

					if (checkRow(mvRow, startRowRobot, startColRobot, 1) == -1) {
						//printf("checkRow fail (robot)\n");
					}
					string ans3 = "";
					if (checkCol(mvCol, startRowRobot, startColRobot, 1) == -1) {
						//printf("*****got minus 1 position ii:%d %c\n", ii, wat); getchar();
						if (checkRow(mvRow, startRowRobot, startColRobot, 1) == -1) {
							printf("oopsRobot - err\n"); exit(0);
						}
						moveRow(mvRow, ans3);
						moveCol(mvCol, ans3);
					} else {
						moveCol(mvCol, ans3);
						moveRow(mvRow, ans3);
					}

					sort(ans3.begin(), ans3.end());
					int numPerms = 0;
					string per[10];
					deque <string> veTmp;
					do {
						per[numPerms] = ans3;
						numPerms++;
					} while (next_permutation(ans3.begin(), ans3.end()));
					if (numPerms == 1) {
						if (veStrRobot[robotNum].size() == 0) {
							veTmp.push_back(ans3+"A");
						} else {
							for (auto st: veStrRobot[robotNum]) {
								veTmp.push_back(st+ans3+"A");
							}
						}
					} else {
						if (veStrRobot[robotNum].size() == 0) {
							for (int ii = 0; ii < numPerms; ii++) {
								int col1 = startColRobot; int row1 = startRowRobot;
								for (auto c1: per[ii]) {
									switch(c1) {
										case '^':
											if (checkRow(-1, row1, col1, 1) == -1) {goto aft3;} else {row1--;}
											break;
										case '>':
											if (checkCol(+1, row1, col1, 1) == -1) {goto aft3;} else {col1++;}
											break;
										case 'v':
											if (checkRow(1, row1, col1, 1) == -1) {goto aft3;} else {row1++;}
											break;	
										case '<':
											if (checkCol(-1, row1, col1, 1) == -1) {goto aft3;} else {col1--;}
											break;
									}
								}	
								veTmp.push_back(per[ii]+"A");
aft3:
								continue;
							}
						} else {
							for (auto st: veStrRobot[robotNum]) {
								for (int ii = 0; ii < numPerms; ii++) {
									int col1 = startColRobot; int row1 = startRowRobot;
									for (auto c1: per[ii]) {
										switch(c1) {
											case '^':
												if (checkRow(-1, row1, col1, 1) == -1) {goto aft4;} else {row1--;}
												break;
											case '>':
												if (checkCol(+1, row1, col1, 1) == -1) {goto aft4;} else {col1++;}
												break;
											case 'v':
												if (checkRow(1, row1, col1, 1) == -1) {goto aft4;} else {row1++;}
												break;	
											case '<':
												if (checkCol(-1, row1, col1, 1) == -1) {goto aft4;} else {col1--;}
												break;
										}
									}	
									veTmp.push_back(st+per[ii]+"A");
aft4:
									continue;
								}
							}
						}
					}
					veStrRobot[robotNum] = veTmp;

					startRowRobot = row;
					startColRobot = col;
					goto ne2;
				}
			}
		}
ne2:
		continue;

	}

	/*
	   if (robotNum == 1) {
	   unsigned long long minLength = 999999999999999999;
	   for (auto st2: veStrRobot[robotNum]) {
	   veStrRobot[robotNum+1].clear();
	   robotARM(st2, robotNum+1, 1, 'A');
	   for (auto st4: veStrRobot[robotNum+1]) {
	   if ((unsigned long long)st4.length() < minLength) {minLength = st2.length();}
	   }
	   }		
	   printf("minLength is %llu\n", minLength);
	   return minLength;
	   } else {
	   return 0;
	   }
	 */
	/*
	   unsigned long long minLength = 999999999999999999;
	   for (auto st2: veStrRobot[robotNum]) {
	   if (robotNum < LEVEL) {
	//printf("here1...\n"); getchar();
	veStrRobot[robotNum+1].clear();
	///cout << "FROM ROBOT: " << robotNum <<  " -- TOROBOT " << robotNum+1 << " sending in : " << st2 << " " << p1 <<  " of " << deStrRobot[robotNum].size() << endl;
	robotARM(st2, robotNum+1, 1, 'A');
	} else if (robotNum == LEVEL) {
	//printf("got to LEVEL: %d\n", LEVEL);
	//for (auto st4: deStrRobot[robotNum]) {
	if ((unsigned long long)st2.length() < minLength) {minLength = st2.length();}
	//}
	}
	}
	if (robotNum == LEVEL) {
	veStrRobot[robotNum].clear();
	}
	 */

	return 0;

}

void moveRow(int mvRow, string &ans33) {
	if (mvRow > 0) {
		for (int kk = 0; kk < abs(mvRow); kk++) {
			ans33 += "v";
		}
	} else if (mvRow < 0) {
		for (int kk = 0; kk < abs(mvRow); kk++) {
			ans33 += "^";
		}
	}
}
void moveCol(int mvCol, string & ans34) {
	if (mvCol > 0) {
		for (int kk = 0; kk < abs(mvCol); kk++) {
			ans34 += ">";
		}
	} else if (mvCol < 0) {
		for (int kk = 0; kk < abs(mvCol); kk++) {
			ans34 += "<";
		}
	}
}

int checkRow(int mvRow, int srow, int scol, int isrobot) {
	if (mvRow > 0) {
		for (int kk = 0; kk < abs(mvRow); kk++) {
			if (isrobot == 1) {
				if (grid2[srow+(kk+1)][scol] == ' ') { return -1;}
			} else {
				if (grid1[srow+(kk+1)][scol] == ' ') { return -1;}
			}
		}
	} else if (mvRow < 0) {
		for (int kk = 0; kk < abs(mvRow); kk++) {
			if (isrobot == 1) {
				if (grid2[srow-(kk+1)][scol] == ' ') { return -1;}
			} else {
				if (grid1[srow-(kk+1)][scol] == ' ') { return -1;}
			}
		}
	}
	return 0;
}
int checkCol(int mvCol, int srow, int scol, int isrobot) {
	if (mvCol > 0) {
		for (int kk = 0; kk < abs(mvCol); kk++) {
			if (isrobot == 1) {
				if (grid2[srow][scol+(kk+1)] == ' ') { return -1;}
			} else {
				if (grid1[srow][scol+(kk+1)] == ' ') { return -1;}
			}
		}
	} else if (mvCol < 0) {
		for (int kk = 0; kk < abs(mvCol); kk++) {
			if (isrobot == 1) {
				if (grid2[srow][scol-(kk+1)] == ' ') { return -1;}
			} else {
				if (grid1[srow][scol-(kk+1)] == ' ') { return -1;}
			}
		}
	}
	return 0;
}
void getLevel2Maps();
void getLevel2Maps() {
	string check = "^>v<A";

	string cOrig = check;
	for (int kk = 0; kk < (int)check.length(); kk++) {
		check = cOrig;
		string st2 = check.substr(kk, 1);
		string check2 = cOrig;
		for (int bb = 0; bb < (int)check2.length(); bb++) {
			char bb2 = check2[bb];
			unsigned long long minLength = 999999999999999999;
			int p1 = -1;
			//for (auto st2: veStr)
			string minStr;	
			{
				p1++;
				cout << "sending in : " << st2 << " " << p1 <<  " of " << veStr.size() << endl;
				veStrRobot[1].clear();
				robotARM(st2, 1, 0, bb2);
				int p2 = -1;
				for (auto st3: veStrRobot[1]) {
					p2++;
					cout << "now looking at output of robot1 (" << p2 << ") " << st3 <<  " of " << veStrRobot[1].size() << " start:" << bb2 << endl; 
					veStrRobot[2].clear();
					robotARM(st3, 2, 1, 'X');
					for (auto st4: veStrRobot[2]) {
						if ((unsigned long long)st4.length() < minLength) {minStr = st4; minLength = st4.length();}
					}
				}
				//printf("minLength: %d of %s is (%s)\n", minLength, st2.c_str(), minStr.c_str());
				//mp[{st2, 1, bb2}] = make_tuple(minLength, minStr);
			}
		}

		cout << st2 << " getchar " << endl; getchar();
	}
	veStrRobot[1].clear();
	veStrRobot[2].clear();
}
