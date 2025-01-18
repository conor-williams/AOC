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

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
char grid2[2][3] = {{' ', '^', 'A'}, {'<', 'v', '>'}};
char grid1[4][3] = {{'7', '8', '9'}, {'4','5','6'}, {'1', '2', '3'}, {' ', '0', 'A'}};
int lenx;
int leny;
int numbers[10];
char numbersS[10][10];
string robotARM(string, int oneortwo);
int startRowRobot1 = 0; int startColRobot1 = 2;
int startRowRobot2 = 0; int startColRobot2 = 2;
int startRow = 3; int startCol = 2;

int checkCol(int mvCol, int row, int col, int isrobot);
int checkRow(int mvRow, int srow, int scol, int isrobot);
void moveRow(int mvRow, string &);
void moveCol(int mvCol, string &);
string ans2;
string ans;
//vector <string> veStr;
deque <string> veStr;
//vector <string> veStrRobot1;
deque <string> veStrRobot1;
//vector <string> veStrRobot2;
deque <string> veStrRobot2;
int fd;
int main(int argc, char **argv)
{
	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 21 Part 1\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
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
		printf("%d\n", numbers[i]);
		printf("%s\n", numbersS[i]);
	}

	//1st robot
	//789
	//456
	//123
	// 0A
	//char start = 'A';
	long long conans = 0;
	for (int i = 0; i < leny; i++) {
		//startRow = 3; startCol = 2;
		if (startRow != 3 && startCol != 2) {printf("ERR\n"); exit(0);}
		ans = "";
		veStr.clear();
		veStrRobot1.clear();
		veStrRobot2.clear();
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
							cout << "here1: " << ans3 <<endl;	
						} while (next_permutation(ans3.begin(), ans3.end()));
						getchar();
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
						cout << "st2 vals: " << endl;
						for (auto st2: veStr) {
							cout << st2 << endl;
						}
						cout << "after st2 vals...\n";

						//ans += "A";

						startRow = row;
						startCol = col;
						assert(grid1[row][col] == wat);
						goto ne;
					}
				}
			}
ne:
			continue;
		}
		//startRowRobot = 0; startColRobot = 2;
		int minLength = 999999;
		int p1 = -1;
		for (auto st2: veStr) {
			p1++;
			cout << "sending in : " << st2 << " " << p1 <<  " of " << veStr.size() << endl;
			veStrRobot1.clear();
			robotARM(st2, 1);
			int p2 = -1;
			for (auto st3: veStrRobot1) {
				p2++;
				cout << "now looking at output of robot1 (" << p2 << ") " << st3 <<  " of " << veStrRobot1.size() << endl; 
				veStrRobot2.clear();
				robotARM(st3, 2);
				for (auto st4: veStrRobot2) {
					if ((int)st4.length() < minLength) {minLength = st4.length();}
				}
			}
/*
			cout << "veStrRobot2.size(): " << veStrRobot2.size() << endl;
			for (auto st4: veStrRobot2) {
				if ((int)st4.length() < minLength) {minLength = st4.length();}
			}
*/
		}
		conans += minLength * numbers[i];
		printf("%d * %d\n", minLength, numbers[i]); getchar();

		/*
		   string first = robotARM(ans, 1);
		   string second = robotARM(first,2);
		   cout << second << endl;
		   cout << second.length() << endl;
		   conans += second.length() * numbers[i];
		   printf("%d * %d\n", (int)second.length(), numbers[i]); getchar();
		 */

	}
	//fflush(stdout); dup2(fd, 1);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", conans);
}


string robotARM(string ans, int oneortwo) {
	cout << ans << endl;
	//string ans2;
	ans2 = "";
	int startRowRobot, startColRobot;
	if (oneortwo == 1) {
		startRowRobot = startRowRobot1;
		startColRobot = startColRobot1;
	} else if (oneortwo == 2) {
		startRowRobot = startRowRobot2;
		startColRobot = startColRobot2;
	}
	if (startRowRobot != 0) {printf("here1"); exit(0);}
	if (startColRobot != 2) {printf("here2"); exit(0);}
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
						cout << "here1: " << ans3 <<endl;	
					} while (next_permutation(ans3.begin(), ans3.end()));
					getchar();
					if (numPerms == 1) {
						//ans += ans3;
						if (oneortwo == 1) {
							if (veStrRobot1.size() == 0) {
								veTmp.push_back(ans3+"A");
							} else {
								for (auto st: veStrRobot1) {
									veTmp.push_back(st+ans3+"A");
								}
							}
						} else if (oneortwo == 2) {
							if (veStrRobot2.size() == 0) {
								veTmp.push_back(ans3+"A");
							} else {
								for (auto st: veStrRobot2) {
									veTmp.push_back(st+ans3+"A");
								}
							}
						}
					} else {
						if (oneortwo == 1) {
							if (veStrRobot1.size() == 0) {
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
								for (auto st: veStrRobot1) {
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
						} else if (oneortwo == 2) {
							if (veStrRobot2.size() == 0) {
								for (int ii = 0; ii < numPerms; ii++) {
									int col1 = startColRobot; int row1 = startRowRobot;
									for (auto c1: per[ii]) {
										switch(c1) {
											case '^':
												if (checkRow(-1, row1, col1, 1) == -1) {goto aft5;} else {row1--;}
												break;
											case '>':
												if (checkCol(+1, row1, col1, 1) == -1) {goto aft5;} else {col1++;}
												break;
											case 'v':
												if (checkRow(1, row1, col1, 1) == -1) {goto aft5;} else {row1++;}
												break;	
											case '<':
												if (checkCol(-1, row1, col1, 1) == -1) {goto aft5;} else {col1--;}
												break;
										}
									}	
									veTmp.push_back(per[ii]+"A");
aft5:
									continue;
								}
							} else {
								for (auto st: veStrRobot2) {
									int col1 = startColRobot; int row1 = startRowRobot;
									for (int ii = 0; ii < numPerms; ii++) {
										for (auto c1: per[ii]) {
											switch(c1) {
												case '^':
													if (checkRow(-1, row1, col1, 1) == -1) {goto aft6;} else {row1--;}
													break;
												case '>':
													if (checkCol(+1, row1, col1, 1) == -1) {goto aft6;} else {col1++;}
													break;
												case 'v':
													if (checkRow(1, row1, col1, 1) == -1) {goto aft6;} else {row1++;}
													break;	
												case '<':
													if (checkCol(-1, row1, col1, 1) == -1) {goto aft6;} else {col1--;}
													break;
											}
										}	
										veTmp.push_back(st+per[ii]+"A");
aft6:
										continue;
									}
								}
							}
						}
					}
					if (oneortwo == 1) {
						veStrRobot1 = veTmp;
					} else if (oneortwo == 2) {
						veStrRobot2 = veTmp;
					}


					//ans += "A";

					//ans2 += "A";
					startRowRobot = row;
					startColRobot = col;
					goto ne2;
				}
			}
		}
ne2:
		continue;

	}
	cout << ans2 << endl;
	if (oneortwo == 1) {
		startRowRobot1 = startRowRobot;
		startColRobot1 = startColRobot;
	} else if (oneortwo == 2) {
		startRowRobot2 = startRowRobot;
		startColRobot2 = startColRobot;
	}
	return "";
	//return ans2;

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
