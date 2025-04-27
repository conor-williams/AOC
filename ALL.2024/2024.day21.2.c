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

#include <unistd.h>

#define getchar()
#define assert(asdf)
unsigned long long MINS = (unsigned long long)-1;

using namespace std;

FILE *a;

#define LINE 1000
#define getchar()
unsigned long long minLLL;
unsigned long long cur;
int maxLevelSoFar = 0;
void sigfunc(int a) { printf("current minLLL: [[ %llu ]] cur:%llu maxLevelSoFar: (%d)\n", minLLL, cur, maxLevelSoFar); }

int lenx;
int leny;
int numbers[10];
char numbersS[10][10];

char grid2[2][3] = {{' ', '^', 'A'}, {'<', 'v', '>'}};
char grid1[4][3] = {{'7', '8', '9'}, {'4','5','6'}, {'1', '2', '3'}, {' ', '0', 'A'}};

int startRow = 3; int startCol = 2;
int checkCol(int mvCol, int row, int col, int isrobot);
int checkRow(int mvRow, int srow, int scol, int isrobot);
void moveRow(int mvRow, string &);
void moveCol(int mvCol, string &);

deque <string> veStr;
struct content_s {
	char first;
	unsigned long long keys[6][6];
	char last;
};
void resetContent(struct content_s & cont);
int getIndex(char aa);
char getTheChar(int aa);

deque <struct content_s> veStrRobot[28];
unsigned long long calcLen(struct content_s aa);

map <tuple<string, int, char>, tuple<unsigned long long, string, vector<struct content_s>>> mp;
void getLevelMaps();
unsigned long long robotARM(string ans, int robotNum, int reset, char prev);
unsigned long long getNextLevel(struct content_s abab, string st2, int level, char bb2);

unsigned long long calcLen(struct content_s aa) {
	unsigned long long len = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			len += aa.keys[i][j];
		}
	}
	return len;
}

void getLevelMaps() {
	string check = "^>v<A";

	string cOrig = check;

	printf("starting to get levels...\n");
	cOrig = check;

	for (int kk = 0; kk < (int)check.length(); kk++) {
		check = cOrig;
		string st2 = check.substr(kk, 1);
		string check2 = cOrig;
		for (int bb = 0; bb < (int)check2.length(); bb++) {
			char bb2 = check2[bb];
			string minStr;	
			vector <string> poss;
			{
				///////////////////
				veStrRobot[1].clear();
				robotARM(st2, 1, 0, bb2);
				unsigned long long minLN2 = MINS;

				for (auto st4: veStrRobot[1]) {
					unsigned long long len = calcLen(st4);
					if (len < minLN2) {minLN2 = len;}
				}
				vector <struct content_s> poss;
				for (auto st4: veStrRobot[1]) {
					unsigned long long len = calcLen(st4);
					if (len == minLN2) {minStr = ""; poss.push_back(st4);}	
				}
				mp[{st2, 1, bb2}] = make_tuple(minLN2, "", poss);

			}
		}
	}

	for (int ijk = 2; ijk <= 25; ijk++) 
	{
		for (int kk = 0; kk < (int)check.length(); kk++) {
			check = cOrig;
			string st2 = check.substr(kk, 1);
			string check2 = cOrig;
			for (int bb = 0; bb < (int)check2.length(); bb++) {
				char bb2 = check2[bb];
				string minStr;	
				{
					auto pa1234 = mp[{st2, ijk-1, bb2}];
					vector <struct content_s> poss3 = get<2>(pa1234);
					vector <struct content_s> dummy3;
					unsigned long long minLen3 = MINS;
					struct content_s retCont;
					resetContent(retCont);

					for (auto st55: poss3) {
						unsigned long long retLen3 = getNextLevel(st55, st2, ijk, bb2);
						if (retLen3 < minLen3) {minLen3 = retLen3;}
					}
					for (auto st55: poss3) {
						unsigned long long retLen3 = getNextLevel(st55, st2, ijk, bb2);
						if (retLen3 == minLen3) {minLen3 = retLen3; dummy3.push_back(st55);}
					}
					mp[{st2, ijk, bb2}] = make_tuple(minLen3, minStr, dummy3);

				}
			}
		}
	}
}
unsigned long long getNextLevel(struct content_s abab, string st2, int level, char bb2) {
	unsigned long long size = 0;

	for (int ii = 0; ii < 5; ii++) {
		for (int jj = 0; jj < 5; jj++) {
			char firstC = getTheChar(ii);
			char secondC = getTheChar(jj);
			string abc;
			abc.push_back(firstC);
			abc.push_back(secondC);
			string abcd; abcd.push_back(secondC);
			auto pa = mp[{abcd, level-1, firstC}];
			size += abab.keys[ii][jj] * get<0>(pa);
			//retCont
		}
	}
	return size;
}

int main(int argc, char **argv)
{
	signal(SIGQUIT, &sigfunc);
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2024 Day 21 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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
		printf("%s: ((%d))\n", numbersS[i], numbers[i]);
	}
	getLevelMaps();

	//1st robot -- the humble beginnings
	//789
	//456
	//123
	//char start = 'A';
	//unsigned long long conans = 0;

	unsigned long long conans = 0;
	for (int i = 0; i < leny; i++) {
		printf("working on %s (%d)\n", numbersS[i], numbers[i]);
		startRow = 3; startCol = 2;
		//if (startRow != 3 && startCol != 2) {printf("ERR\n"); exit(0);}
		veStr.clear();
		for (int jj = 0; jj < (int)strlen(numbersS[i]); jj++) {
			char wat = numbersS[i][jj];

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
						startRow = row;
						startCol = col;
						goto ne;
					}
				}
			}
ne:
			continue;
		}

		for (int i25 = 3; i25 <= 25; i25++) 
		{
			unsigned long long minLength252525 = MINS;
			for (auto st2: veStr) {
				unsigned long long minSub = 0;
				char crPrev = 'A';
				for (auto cr: st2) {
					string ab;
					ab.push_back(cr);
					auto  tu11 = mp[{ab, i25, crPrev}];
					minSub += get <0>(tu11); 
					crPrev = cr;
				}
				if (minSub < minLength252525) {minLength252525 = minSub;}
			}
			printf("LEVEL %d -- quick way:: %llu\n", i25, minLength252525);
		}


		int lev25 = 25;
		unsigned long long minLength25 = MINS;
		for (auto st2: veStr) {
			unsigned long long minSub = 0;
			
			char crPrev = 'A';
			for (auto cr: st2) {
				string ab;
				ab.push_back(cr);
				auto tu11 = mp[{ab, lev25, crPrev}];

				//minSub += bigint(to_string(get <0>(tu11))); 
				minSub += get<0>(tu11);
				crPrev = cr;
			}
			if (minSub < minLength25) {minLength25 = minSub;}
		}
		printf("LEVEL 25 min (using): "); cout <<  minLength25 << endl;

		conans += minLength25 * numbers[i];

	}

	//printf("**ans: ");
	//cout << conans << endl;
	
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", conans);
	//cout << conans << endl;
}
unsigned long long robotARM(string ans, int robotNum, int reset, char prev) {

	if (robotNum > maxLevelSoFar) {maxLevelSoFar = robotNum;}
	if (robotNum > 2) { if (cur++ % 1000 == 0) { printf("LEVEL: (%d) times:%llu\n", robotNum, cur);}}
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
					deque <struct content_s> veTmp;
					struct content_s cont2;
					resetContent(cont2);
					string n1;
					do {
						per[numPerms] = ans3;
						numPerms++;
					} while (next_permutation(ans3.begin(), ans3.end()));

					if (numPerms == 1) {
						prev = 'A';

						//prePend prev to ans3;
						ans3 = prev+ans3+"A";
						if (veStrRobot[robotNum].size() == 0) {
							//memset(cont2, 0, sizeof(cont2));
							resetContent(cont2);

							for (int kkk = 1; kkk < (int)ans3.length(); kkk++) {
								int firstI = getIndex(ans3[kkk-1]);
								int secondI = getIndex(ans3[kkk]);
								cont2.keys[firstI][secondI]++;
							}
							prev = 'A';
							veTmp.push_back(cont2);
						} else {
							for (auto ct: veStrRobot[robotNum]) {
								for (int kkk = 0; kkk < (int)ans3.length(); kkk++) {
									int firstI = getIndex(ans3[kkk-1]);
									int secondI = getIndex(ans3[kkk]);
									ct.keys[firstI][secondI]++;
								}
								prev = 'A';
								veTmp.push_back(ct);
							}
						}
					} else {
						prev = 'A';
						if (veStrRobot[robotNum].size() == 0) {
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
								veTmp.push_back(cont2);
								prev = 'A';
aft33:
								continue;
							}
						} else {
							for (auto ct: veStrRobot[robotNum]) {
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
									veTmp.push_back(ct);
									prev = 'A';
aft44:
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
