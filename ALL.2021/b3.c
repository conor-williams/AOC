#include<stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;

//#define getchar()
int al[100];
int alPos = 0;
struct pairs_s {
	int b1;
	int b2;
	int o1;
	int o2;
};
vector <pair<int, int>> ve[31][31];
vector <pair<int, int>> veOrig[31][31];


struct data123_s {
	int value1;
	int value2;
	int used;
}; 
struct data123_s data123[] = {
	{0,2},
	{0,3},
	{0,4},
	{0,18},
	{0,27},
	{1,2},
	{1,4},
	{2,9},
	{3,8},
	{4,6},
	{4,8},
	{4,19},
	{4,23},
	{5,15},
	{5,28},
	{6,12},
	{6,25},
	{7,10},
	{7,13},
	{7,16},
	{7,26},
	{8,12},
	{8,16},
	{9,18},
	{10,17},
	{10,22},
	{10,23},
	{11,12},
	{12,15},
	{12,28},
	{13,17},
	{14,28},
	{14,29},
	{15,16},
	{15,25},
	{16,20},
	{16,23},
	{17,27},
	{20,26},
	{21,26},
	{22,24},
	{23, 25},
	{23, 27}
};
/////////////////////////////////////////
struct pairs_s pairs[] =
{
	{0,2,0,16},
	{0,2,1,17},
	{0,2,2,18},
	{0,2,3,19},
	{0,2,4,20},
	{0,2,5,21},
	{0,2,6,22},
	{0,2,7,23},
	{0,2,8,4},
	{0,2,9,5},
	{0,2,10,4},
	{0,2,11,5},
	{0,2,12,0},
	{0,2,13,1},
	{0,2,14,0},
	{0,2,15,1},
	{0,2,16,12},
	{0,2,16,14},
	{0,2,17,13},
	{0,2,17,15},
	{0,2,20,8},
	{0,2,20,10},
	{0,2,21,9},
	{0,2,21,11},
	{0,3,0,1},
	{0,3,1,0},
	{0,3,2,3},
	{0,3,3,2},
	{0,3,4,5},
	{0,3,5,4},
	{0,3,6,7},
	{0,3,7,6},
	{0,3,16,18},
	{0,3,17,19},
	{0,3,18,16},
	{0,3,19,17},
	{0,3,20,23},
	{0,3,21,22},
	{0,3,22,21},
	{0,3,23,20},
	{0,4,2,13},
	{0,4,2,15},
	{0,4,3,12},
	{0,4,3,14},
	{0,4,6,8},
	{0,4,6,10},
	{0,4,7,9},
	{0,4,7,11},
	{0,4,8,23},
	{0,4,9,22},
	{0,4,10,23},
	{0,4,11,22},
	{0,4,12,18},
	{0,4,13,19},
	{0,4,14,18},
	{0,4,15,19},
	{0,4,16,1},
	{0,4,17,0},
	{0,4,18,3},
	{0,4,19,2},
	{0,4,20,5},
	{0,4,21,4},
	{0,4,22,7},
	{0,4,23,6},
	{0,18,0,22},
	{0,18,1,23},
	{0,18,2,20},
	{0,18,3,21},
	{0,18,4,18},
	{0,18,5,19},
	{0,18,6,16},
	{0,18,7,17},
	{0,18,8,13},
	{0,18,8,15},
	{0,18,9,12},
	{0,18,9,14},
	{0,18,10,13},
	{0,18,10,15},
	{0,18,11,12},
	{0,18,11,14},
	{0,18,12,8},
	{0,18,12,10},
	{0,18,13,9},
	{0,18,13,11},
	{0,18,14,8},
	{0,18,14,10},
	{0,18,15,9},
	{0,18,15,11},
	{0,18,16,5},
	{0,18,17,4},
	{0,18,18,7},
	{0,18,19,6},
	{0,18,20,0},
	{0,18,21,1},
	{0,18,22,2},
	{0,18,23,3},
	{0,27,0,21},
	{0,27,1,20},
	{0,27,2,23},
	{0,27,3,22},
	{0,27,4,16},
	{0,27,5,17},
	{0,27,6,18},
	{0,27,7,19},
	{0,27,16,4},
	{0,27,17,5},
	{0,27,18,6},
	{0,27,19,7},
	{0,27,20,1},
	{0,27,21,0},
	{0,27,22,3},
	{0,27,23,2},
	{1,2,0,19},
	{1,2,1,18},
	{1,2,2,17},
	{1,2,3,16},
	{1,2,4,22},
	{1,2,5,23},
	{1,2,6,20},
	{1,2,7,21},
	{1,2,8,7},
	{1,2,9,6},
	{1,2,10,7},
	{1,2,11,6},
	{1,2,12,2},
	{1,2,13,3},
	{1,2,14,2},
	{1,2,15,3},
	{1,2,16,13},
	{1,2,16,15},
	{1,2,17,12},
	{1,2,17,14},
	{1,2,20,9},
	{1,2,20,11},
	{1,2,21,8},
	{1,2,21,10},
	{1,4,0,12},
	{1,4,0,14},
	{1,4,1,13},
	{1,4,1,15},
	{1,4,4,8},
	{1,4,4,10},
	{1,4,5,9},
	{1,4,5,11},
	{1,4,8,20},
	{1,4,9,21},
	{1,4,10,20},
	{1,4,11,21},
	{1,4,12,16},
	{1,4,13,17},
	{1,4,14,16},
	{1,4,15,17},
	{1,4,16,0},
	{1,4,17,1},
	{1,4,18,2},
	{1,4,19,3},
	{1,4,20,4},
	{1,4,21,5},
	{1,4,22,6},
	{1,4,23,7},
	{2,9,0,17},
	{2,9,1,16},
	{2,9,2,19},
	{2,9,3,18},
	{2,9,4,21},
	{2,9,5,20},
	{2,9,6,23},
	{2,9,7,22},
	{2,9,8,6},
	{2,9,9,7},
	{2,9,10,6},
	{2,9,11,7},
	{2,9,12,3},
	{2,9,13,2},
	{2,9,14,3},
	{2,9,15,2},
	{2,9,18,12},
	{2,9,18,14},
	{2,9,19,13},
	{2,9,19,15},
	{2,9,22,9},
	{2,9,22,11},
	{2,9,23,8},
	{2,9,23,10},
	{3,8,0,4},
	{3,8,1,5},
	{3,8,2,6},
	{3,8,3,7},
	{3,8,4,1},
	{3,8,5,0},
	{3,8,6,3},
	{3,8,7,2},
	{3,8,8,16},
	{3,8,9,17},
	{3,8,10,16},
	{3,8,11,17},
	{3,8,12,21},
	{3,8,13,20},
	{3,8,14,21},
	{3,8,15,20},
	{3,8,18,8},
	{3,8,18,10},
	{3,8,19,9},
	{3,8,19,11},
	{3,8,22,12},
	{3,8,22,14},
	{3,8,23,13},
	{3,8,23,15},
	{4,6,0,18},
	{4,6,1,19},
	{4,6,2,16},
	{4,6,3,17},
	{4,6,4,23},
	{4,6,5,22},
	{4,6,6,21},
	{4,6,7,20},
	{4,6,8,5},
	{4,6,9,4},
	{4,6,10,5},
	{4,6,11,4},
	{4,6,12,1},
	{4,6,13,0},
	{4,6,14,1},
	{4,6,15,0},
	{4,6,18,13},
	{4,6,18,15},
	{4,6,19,12},
	{4,6,19,14},
	{4,6,22,8},
	{4,6,22,10},
	{4,6,23,9},
	{4,6,23,11},
	{4,8,0,9},
	{4,8,0,11},
	{4,8,1,8},
	{4,8,1,10},
	{4,8,4,12},
	{4,8,4,14},
	{4,8,5,13},
	{4,8,5,15},
	{4,8,8,2},
	{4,8,9,3},
	{4,8,10,2},
	{4,8,11,3},
	{4,8,12,6},
	{4,8,13,7},
	{4,8,14,6},
	{4,8,15,7},
	{4,8,16,20},
	{4,8,17,21},
	{4,8,18,22},
	{4,8,19,23},
	{4,8,20,17},
	{4,8,21,16},
	{4,8,22,19},
	{4,8,23,18},
	{4,19,0,3},
	{4,19,1,2},
	{4,19,2,1},
	{4,19,3,0},
	{4,19,4,6},
	{4,19,5,7},
	{4,19,6,4},
	{4,19,7,5},
	{4,19,16,17},
	{4,19,17,16},
	{4,19,18,19},
	{4,19,19,18},
	{4,19,20,21},
	{4,19,21,20},
	{4,19,22,23},
	{4,19,23,22},
	{4,23,2,8},
	{4,23,2,10},
	{4,23,3,9},
	{4,23,3,11},
	{4,23,6,12},
	{4,23,6,14},
	{4,23,7,13},
	{4,23,7,15},
	{4,23,8,1},
	{4,23,9,0},
	{4,23,10,1},
	{4,23,11,0},
	{4,23,12,4},
	{4,23,13,5},
	{4,23,14,4},
	{4,23,15,5},
	{4,23,16,21},
	{4,23,17,20},
	{4,23,18,23},
	{4,23,19,22},
	{4,23,20,16},
	{4,23,21,17},
	{4,23,22,18},
	{4,23,23,19},
	{5,15,0,12},
	{5,15,0,14},
	{5,15,1,13},
	{5,15,1,15},
	{5,15,4,8},
	{5,15,4,10},
	{5,15,5,9},
	{5,15,5,11},
	{5,15,8,20},
	{5,15,9,21},
	{5,15,10,20},
	{5,15,11,21},
	{5,15,12,16},
	{5,15,13,17},
	{5,15,14,16},
	{5,15,15,17},
	{5,15,16,0},
	{5,15,17,1},
	{5,15,18,2},
	{5,15,19,3},
	{5,15,20,4},
	{5,15,21,5},
	{5,15,22,6},
	{5,15,23,7},
	{5,28,0,0},
	{5,28,1,1},
	{5,28,2,2},
	{5,28,3,3},
	{5,28,4,4},
	{5,28,5,5},
	{5,28,6,6},
	{5,28,7,7},
	{5,28,8,8},
	{5,28,8,10},
	{5,28,9,9},
	{5,28,9,11},
	{5,28,10,8},
	{5,28,10,10},
	{5,28,11,9},
	{5,28,11,11},
	{5,28,12,12},
	{5,28,12,14},
	{5,28,13,13},
	{5,28,13,15},
	{5,28,14,12},
	{5,28,14,14},
	{5,28,15,13},
	{5,28,15,15},
	{5,28,16,16},
	{5,28,17,17},
	{5,28,18,18},
	{5,28,19,19},
	{5,28,20,20},
	{5,28,21,21},
	{5,28,22,22},
	{5,28,23,23},
	{6,12,2,12},
	{6,12,2,14},
	{6,12,3,13},
	{6,12,3,15},
	{6,12,6,9},
	{6,12,6,11},
	{6,12,7,8},
	{6,12,7,10},
	{6,12,8,21},
	{6,12,9,20},
	{6,12,10,21},
	{6,12,11,20},
	{6,12,12,17},
	{6,12,13,16},
	{6,12,14,17},
	{6,12,15,16},
	{6,12,16,3},
	{6,12,17,2},
	{6,12,18,1},
	{6,12,19,0},
	{6,12,20,6},
	{6,12,21,7},
	{6,12,22,4},
	{6,12,23,5},
	{6,25,0,13},
	{6,25,0,15},
	{6,25,1,12},
	{6,25,1,14},
	{6,25,4,9},
	{6,25,4,11},
	{6,25,5,8},
	{6,25,5,10},
	{6,25,8,22},
	{6,25,9,23},
	{6,25,10,22},
	{6,25,11,23},
	{6,25,12,19},
	{6,25,13,18},
	{6,25,14,19},
	{6,25,15,18},
	{6,25,16,2},
	{6,25,17,3},
	{6,25,18,0},
	{6,25,19,1},
	{6,25,20,7},
	{6,25,21,6},
	{6,25,22,5},
	{6,25,23,4},
	{7,10,0,17},
	{7,10,1,16},
	{7,10,2,19},
	{7,10,3,18},
	{7,10,4,21},
	{7,10,5,20},
	{7,10,6,23},
	{7,10,7,22},
	{7,10,8,6},
	{7,10,9,7},
	{7,10,10,6},
	{7,10,11,7},
	{7,10,12,3},
	{7,10,13,2},
	{7,10,14,3},
	{7,10,15,2},
	{7,10,18,12},
	{7,10,18,14},
	{7,10,19,13},
	{7,10,19,15},
	{7,10,22,9},
	{7,10,22,11},
	{7,10,23,8},
	{7,10,23,10},
	{7,13,0,3},
	{7,13,1,2},
	{7,13,2,1},
	{7,13,3,0},
	{7,13,4,6},
	{7,13,5,7},
	{7,13,6,4},
	{7,13,7,5},
	{7,13,16,17},
	{7,13,17,16},
	{7,13,18,19},
	{7,13,19,18},
	{7,13,20,21},
	{7,13,21,20},
	{7,13,22,23},
	{7,13,23,22},
	{7,16,2,12},
	{7,16,2,14},
	{7,16,3,13},
	{7,16,3,15},
	{7,16,6,9},
	{7,16,6,11},
	{7,16,7,8},
	{7,16,7,10},
	{7,16,8,21},
	{7,16,9,20},
	{7,16,10,21},
	{7,16,11,20},
	{7,16,12,17},
	{7,16,13,16},
	{7,16,14,17},
	{7,16,15,16},
	{7,16,16,3},
	{7,16,17,2},
	{7,16,18,1},
	{7,16,19,0},
	{7,16,20,6},
	{7,16,21,7},
	{7,16,22,4},
	{7,16,23,5},
	{7,26,2,12},
	{7,26,2,14},
	{7,26,3,13},
	{7,26,3,15},
	{7,26,6,9},
	{7,26,6,11},
	{7,26,7,8},
	{7,26,7,10},
	{7,26,8,21},
	{7,26,9,20},
	{7,26,10,21},
	{7,26,11,20},
	{7,26,12,17},
	{7,26,13,16},
	{7,26,14,17},
	{7,26,15,16},
	{7,26,16,3},
	{7,26,17,2},
	{7,26,18,1},
	{7,26,19,0},
	{7,26,20,6},
	{7,26,21,7},
	{7,26,22,4},
	{7,26,23,5},
	{8,12,0,8},
	{8,12,0,10},
	{8,12,1,9},
	{8,12,1,11},
	{8,12,4,13},
	{8,12,4,15},
	{8,12,5,12},
	{8,12,5,14},
	{8,12,8,0},
	{8,12,9,1},
	{8,12,10,0},
	{8,12,11,1},
	{8,12,12,5},
	{8,12,13,4},
	{8,12,14,5},
	{8,12,15,4},
	{8,12,16,22},
	{8,12,17,23},
	{8,12,18,20},
	{8,12,19,21},
	{8,12,20,18},
	{8,12,21,19},
	{8,12,22,16},
	{8,12,23,17},
	{8,16,0,19},
	{8,16,1,18},
	{8,16,2,17},
	{8,16,3,16},
	{8,16,4,22},
	{8,16,5,23},
	{8,16,6,20},
	{8,16,7,21},
	{8,16,8,7},
	{8,16,9,6},
	{8,16,10,7},
	{8,16,11,6},
	{8,16,12,2},
	{8,16,13,3},
	{8,16,14,2},
	{8,16,15,3},
	{8,16,16,13},
	{8,16,16,15},
	{8,16,17,12},
	{8,16,17,14},
	{8,16,20,9},
	{8,16,20,11},
	{8,16,21,8},
	{8,16,21,10},
	{9,18,0,6},
	{9,18,1,7},
	{9,18,2,4},
	{9,18,3,5},
	{9,18,4,2},
	{9,18,5,3},
	{9,18,6,0},
	{9,18,7,1},
	{9,18,8,17},
	{9,18,9,16},
	{9,18,10,17},
	{9,18,11,16},
	{9,18,12,20},
	{9,18,13,21},
	{9,18,14,20},
	{9,18,15,21},
	{9,18,16,9},
	{9,18,16,11},
	{9,18,17,8},
	{9,18,17,10},
	{9,18,20,12},
	{9,18,20,14},
	{9,18,21,13},
	{9,18,21,15},
	{10,17,2,12},
	{10,17,2,14},
	{10,17,3,13},
	{10,17,3,15},
	{10,17,6,9},
	{10,17,6,11},
	{10,17,7,8},
	{10,17,7,10},
	{10,17,8,21},
	{10,17,9,20},
	{10,17,10,21},
	{10,17,11,20},
	{10,17,12,17},
	{10,17,13,16},
	{10,17,14,17},
	{10,17,15,16},
	{10,17,16,3},
	{10,17,17,2},
	{10,17,18,1},
	{10,17,19,0},
	{10,17,20,6},
	{10,17,21,7},
	{10,17,22,4},
	{10,17,23,5},
	{10,22,0,17},
	{10,22,1,16},
	{10,22,2,19},
	{10,22,3,18},
	{10,22,4,21},
	{10,22,5,20},
	{10,22,6,23},
	{10,22,7,22},
	{10,22,8,6},
	{10,22,9,7},
	{10,22,10,6},
	{10,22,11,7},
	{10,22,12,3},
	{10,22,13,2},
	{10,22,14,3},
	{10,22,15,2},
	{10,22,18,12},
	{10,22,18,14},
	{10,22,19,13},
	{10,22,19,15},
	{10,22,22,9},
	{10,22,22,11},
	{10,22,23,8},
	{10,22,23,10},
	{10,23,0,2},
	{10,23,1,3},
	{10,23,2,0},
	{10,23,3,1},
	{10,23,4,7},
	{10,23,5,6},
	{10,23,6,5},
	{10,23,7,4},
	{10,23,8,9},
	{10,23,8,11},
	{10,23,9,8},
	{10,23,9,10},
	{10,23,10,9},
	{10,23,10,11},
	{10,23,11,8},
	{10,23,11,10},
	{10,23,12,13},
	{10,23,12,15},
	{10,23,13,12},
	{10,23,13,14},
	{10,23,14,13},
	{10,23,14,15},
	{10,23,15,12},
	{10,23,15,14},
	{10,23,16,19},
	{10,23,17,18},
	{10,23,18,17},
	{10,23,19,16},
	{10,23,20,22},
	{10,23,21,23},
	{10,23,22,20},
	{10,23,23,21},
	{11,12,0,18},
	{11,12,1,19},
	{11,12,2,16},
	{11,12,3,17},
	{11,12,4,23},
	{11,12,5,22},
	{11,12,6,21},
	{11,12,7,20},
	{11,12,8,5},
	{11,12,9,4},
	{11,12,10,5},
	{11,12,11,4},
	{11,12,12,1},
	{11,12,13,0},
	{11,12,14,1},
	{11,12,15,0},
	{11,12,18,13},
	{11,12,18,15},
	{11,12,19,12},
	{11,12,19,14},
	{11,12,22,8},
	{11,12,22,10},
	{11,12,23,9},
	{11,12,23,11},
	{12,15,0,6},
	{12,15,1,7},
	{12,15,2,4},
	{12,15,3,5},
	{12,15,4,2},
	{12,15,5,3},
	{12,15,6,0},
	{12,15,7,1},
	{12,15,8,17},
	{12,15,9,16},
	{12,15,10,17},
	{12,15,11,16},
	{12,15,12,20},
	{12,15,13,21},
	{12,15,14,20},
	{12,15,15,21},
	{12,15,16,9},
	{12,15,16,11},
	{12,15,17,8},
	{12,15,17,10},
	{12,15,20,12},
	{12,15,20,14},
	{12,15,21,13},
	{12,15,21,15},
	{12,28,0,22},
	{12,28,1,23},
	{12,28,2,20},
	{12,28,3,21},
	{12,28,4,18},
	{12,28,5,19},
	{12,28,6,16},
	{12,28,7,17},
	{12,28,8,13},
	{12,28,8,15},
	{12,28,9,12},
	{12,28,9,14},
	{12,28,10,13},
	{12,28,10,15},
	{12,28,11,12},
	{12,28,11,14},
	{12,28,12,8},
	{12,28,12,10},
	{12,28,13,9},
	{12,28,13,11},
	{12,28,14,8},
	{12,28,14,10},
	{12,28,15,9},
	{12,28,15,11},
	{12,28,16,5},
	{12,28,17,4},
	{12,28,18,7},
	{12,28,19,6},
	{12,28,20,0},
	{12,28,21,1},
	{12,28,22,2},
	{12,28,23,3},
	{13,17,0,1},
	{13,17,1,0},
	{13,17,2,3},
	{13,17,3,2},
	{13,17,4,5},
	{13,17,5,4},
	{13,17,6,7},
	{13,17,7,6},
	{13,17,16,18},
	{13,17,17,19},
	{13,17,18,16},
	{13,17,19,17},
	{13,17,20,23},
	{13,17,21,22},
	{13,17,22,21},
	{13,17,23,20},
	{14,28,0,4},
	{14,28,1,5},
	{14,28,2,6},
	{14,28,3,7},
	{14,28,4,1},
	{14,28,5,0},
	{14,28,6,3},
	{14,28,7,2},
	{14,28,8,16},
	{14,28,9,17},
	{14,28,10,16},
	{14,28,11,17},
	{14,28,12,21},
	{14,28,13,20},
	{14,28,14,21},
	{14,28,15,20},
	{14,28,18,8},
	{14,28,18,10},
	{14,28,19,9},
	{14,28,19,11},
	{14,28,22,12},
	{14,28,22,14},
	{14,28,23,13},
	{14,28,23,15},
	{14,29,0,18},
	{14,29,1,19},
	{14,29,2,16},
	{14,29,3,17},
	{14,29,4,23},
	{14,29,5,22},
	{14,29,6,21},
	{14,29,7,20},
	{14,29,8,5},
	{14,29,9,4},
	{14,29,10,5},
	{14,29,11,4},
	{14,29,12,1},
	{14,29,13,0},
	{14,29,14,1},
	{14,29,15,0},
	{14,29,18,13},
	{14,29,18,15},
	{14,29,19,12},
	{14,29,19,14},
	{14,29,22,8},
	{14,29,22,10},
	{14,29,23,9},
	{14,29,23,11},
	{15,16,0,1},
	{15,16,1,0},
	{15,16,2,3},
	{15,16,3,2},
	{15,16,4,5},
	{15,16,5,4},
	{15,16,6,7},
	{15,16,7,6},
	{15,16,16,18},
	{15,16,17,19},
	{15,16,18,16},
	{15,16,19,17},
	{15,16,20,23},
	{15,16,21,22},
	{15,16,22,21},
	{15,16,23,20},
	{15,25,0,7},
	{15,25,1,6},
	{15,25,2,5},
	{15,25,3,4},
	{15,25,4,3},
	{15,25,5,2},
	{15,25,6,1},
	{15,25,7,0},
	{15,25,8,19},
	{15,25,9,18},
	{15,25,10,19},
	{15,25,11,18},
	{15,25,12,23},
	{15,25,13,22},
	{15,25,14,23},
	{15,25,15,22},
	{15,25,18,9},
	{15,25,18,11},
	{15,25,19,8},
	{15,25,19,10},
	{15,25,22,13},
	{15,25,22,15},
	{15,25,23,12},
	{15,25,23,14},
	{16,20,0,8},
	{16,20,0,10},
	{16,20,1,9},
	{16,20,1,11},
	{16,20,4,13},
	{16,20,4,15},
	{16,20,5,12},
	{16,20,5,14},
	{16,20,8,0},
	{16,20,9,1},
	{16,20,10,0},
	{16,20,11,1},
	{16,20,12,5},
	{16,20,13,4},
	{16,20,14,5},
	{16,20,15,4},
	{16,20,16,22},
	{16,20,17,23},
	{16,20,18,20},
	{16,20,19,21},
	{16,20,20,18},
	{16,20,21,19},
	{16,20,22,16},
	{16,20,23,17},
	{16,23,0,12},
	{16,23,0,14},
	{16,23,1,13},
	{16,23,1,15},
	{16,23,4,8},
	{16,23,4,10},
	{16,23,5,9},
	{16,23,5,11},
	{16,23,8,20},
	{16,23,9,21},
	{16,23,10,20},
	{16,23,11,21},
	{16,23,12,16},
	{16,23,13,17},
	{16,23,14,16},
	{16,23,15,17},
	{16,23,16,0},
	{16,23,17,1},
	{16,23,18,2},
	{16,23,19,3},
	{16,23,20,4},
	{16,23,21,5},
	{16,23,22,6},
	{16,23,23,7},
	{17,27,0,13},
	{17,27,0,15},
	{17,27,1,12},
	{17,27,1,14},
	{17,27,4,9},
	{17,27,4,11},
	{17,27,5,8},
	{17,27,5,10},
	{17,27,8,22},
	{17,27,9,23},
	{17,27,10,22},
	{17,27,11,23},
	{17,27,12,19},
	{17,27,13,18},
	{17,27,14,19},
	{17,27,15,18},
	{17,27,16,2},
	{17,27,17,3},
	{17,27,18,0},
	{17,27,19,1},
	{17,27,20,7},
	{17,27,21,6},
	{17,27,22,5},
	{17,27,23,4},
	{20,26,0,8},
	{20,26,0,10},
	{20,26,1,9},
	{20,26,1,11},
	{20,26,4,13},
	{20,26,4,15},
	{20,26,5,12},
	{20,26,5,14},
	{20,26,8,0},
	{20,26,9,1},
	{20,26,10,0},
	{20,26,11,1},
	{20,26,12,5},
	{20,26,13,4},
	{20,26,14,5},
	{20,26,15,4},
	{20,26,16,22},
	{20,26,17,23},
	{20,26,18,20},
	{20,26,19,21},
	{20,26,20,18},
	{20,26,21,19},
	{20,26,22,16},
	{20,26,23,17},
	{21,26,0,17},
	{21,26,1,16},
	{21,26,2,19},
	{21,26,3,18},
	{21,26,4,21},
	{21,26,5,20},
	{21,26,6,23},
	{21,26,7,22},
	{21,26,8,6},
	{21,26,9,7},
	{21,26,10,6},
	{21,26,11,7},
	{21,26,12,3},
	{21,26,13,2},
	{21,26,14,3},
	{21,26,15,2},
	{21,26,18,12},
	{21,26,18,14},
	{21,26,19,13},
	{21,26,19,15},
	{21,26,22,9},
	{21,26,22,11},
	{21,26,23,8},
	{21,26,23,10},
	{22,24,0,1},
	{22,24,1,0},
	{22,24,2,3},
	{22,24,3,2},
	{22,24,4,5},
	{22,24,5,4},
	{22,24,6,7},
	{22,24,7,6},
	{22,24,16,18},
	{22,24,17,19},
	{22,24,18,16},
	{22,24,19,17},
	{22,24,20,23},
	{22,24,21,22},
	{22,24,22,21},
	{22,24,23,20},
	{23,25,0,9},
	{23,25,0,11},
	{23,25,1,8},
	{23,25,1,10},
	{23,25,4,12},
	{23,25,4,14},
	{23,25,5,13},
	{23,25,5,15},
	{23,25,8,2},
	{23,25,9,3},
	{23,25,10,2},
	{23,25,11,3},
	{23,25,12,6},
	{23,25,13,7},
	{23,25,14,6},
	{23,25,15,7},
	{23,25,16,20},
	{23,25,17,21},
	{23,25,18,22},
	{23,25,19,23},
	{23,25,20,17},
	{23,25,21,16},
	{23,25,22,19},
	{23,25,23,18},
	{23,27,0,19},
	{23,27,1,18},
	{23,27,2,17},
	{23,27,3,16},
	{23,27,4,22},
	{23,27,5,23},
	{23,27,6,20},
	{23,27,7,21},
	{23,27,8,7},
	{23,27,9,6},
	{23,27,10,7},
	{23,27,11,6},
	{23,27,12,2},
	{23,27,13,3},
	{23,27,14,2},
	{23,27,15,3},
	{23,27,16,13},
	{23,27,16,15},
	{23,27,17,12},
	{23,27,17,14},
	{23,27,20,9},
	{23,27,20,11},
	{23,27,21,8},
	{23,27,21,10}
};
int pairsPos = 1008;

enum { DATA_SIZE = sizeof (data123) / sizeof (struct data123_s) };

static int output[DATA_SIZE];
int max123 = 0;
char ans[60000][90];
int ansPos = 0;
int traverse(int from, int to, int depth) {
	//if (depth == 0) {printf("%d -> %d\n", from, to);}
	output[depth++] = from;
	int i;
	if (from == to) {
		for (i = 0; i < depth; i++) {
			if (i == 0) {strcpy(ans[ansPos], "");}
			if (i) {
				//printf("-");
				sprintf(ans[ansPos], "%s%c", ans[ansPos], '-');
			}
			//printf("%d", output[i]);
			sprintf(ans[ansPos], "%s%d", ans[ansPos], output[i]);
		}
		//printf("\n");
		sprintf(ans[ansPos], "%s\n", ans[ansPos]);
		//printf("%s", ans);
		//if ((int)strlen(ans) > max123) {max123 = (int)strlen(ans);}
		ansPos++;
		
		//getchar();
	} else {
		for (i = 0; i < DATA_SIZE; i++) {
			if (!data123[i].used) {
				data123[i].used = 1;

				if (from == data123[i].value1) {
					if ((data123[i].value2 == 0 || to == 0) && depth != 0) {
					} else {
						traverse(data123[i].value2, to, depth);
					}
				} else if (from == data123[i].value2) {
					if ((data123[i].value1 == 0 || to == 0) && depth != 0) {
					} else {
						traverse(data123[i].value1, to, depth);
					}

				}

				data123[i].used = 0;
			}
		}
	}
	return -1;
}

int main() {
	for (int i = 0; i < DATA_SIZE; i++) {
		for (int j = 0; j < pairsPos; j++) {
			if (data123[i].value1 == pairs[j].b1 && data123[i].value2 == pairs[j].b2) {
				ve[data123[i].value1][data123[i].value2].push_back(pair(pairs[j].o1, pairs[j].o2)); 
				ve[data123[i].value2][data123[i].value1].push_back(pair(pairs[j].o2, pairs[j].o1)); 
			}
		}
	}
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (i == j) {continue;}
			if (i == 0) {
				vector <pair <int, int>> vpr = ve[i][j];
				for (auto it = vpr.begin(); it != vpr.end(); it++) {
					//printf("i,j(b1,b2): %d,%d == ve[i][j]: %d %d\n", i, j, (*it).first, (*it).second);
				}
			}

			veOrig[i][j] = ve[i][j];
		}
	}
	//getchar();

	for  (int k = 1; k < 30; k++) {
		//strcpy(ans[ansPos], "");
		traverse(0, k, 0);
/*
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				ve[i][j] = veOrig[i][j];
			}
		}
*/
	}

	int ignoreCount = 0;
	printf("ansPos is %d\n", ansPos); getchar();
	for (int i = 0; i < ansPos; i++) {
		printf("%s\n", ans[i]);
		char *fr = strtok(ans[i], "-\n");
		int pos = 0;
		int prevII, prevI, I = 0;
		vector <pair<int, int>> var_inter;
		do {
			prevII = prevI;
			prevI = I;
			printf("%d -- ", I = atoi(fr));	

			if (pos >1) {
				//ve[prevII][prevI] intersect ve[prevI][I];
				vector <pair <int, int>> le = ve[prevII][prevI];
				//printf("size le before %ld\n", le.size());
				ve[prevII][prevI].clear();
				vector <pair <int, int>> ri = ve[prevI][I];
				//printf("size ri before %ld\n", le.size());
				ve[prevI][I].clear();
				alPos = 0;
				for (int zb = 0; zb < 24; zb++) {
				for (unsigned long z = 0; z < le.size(); z++) {
					pair <int, int> pairL;
					pairL.first = le[z].first;
					pairL.second = le[z].second;
					for (unsigned long q = 0; q < ri.size(); q++) {
						pair <int, int> pairR;
						pairR.first = ri[q].first;
						int found = 0;
						for (int zi = 0; zi < alPos; zi++) {
							if (al[zi] == pairR.first) {
								found = 1; break;
							}
						}
						printf("b1:%d b2:%d -o1,o2 [%d,%d] V b1:%d b2:%d b2:o1,o2 [%d,%d]\n", prevII, prevI, le[z].first, le[z].second, prevI, I, ri[q].first, ri[q].second);
						getchar();
						if (found == 0) {al[alPos++] = pairR.first;} else { continue;}
								
						pairR.second = ri[q].second;
						
						if (le[z].second == ri[q].first) {
							printf("got one...\n");
							ve[prevII][prevI].push_back(pairL);
							ve[prevI][I].push_back(pairR);
						}
					}
				}
				long szle = ve[prevII][prevI].size();
				long szri = ve[prevI][I].size();
				//printf("size le after %ld\n", ve[prevII][prevI].size());
				//printf("size ri after %ld\n", ve[prevI][I].size());
				if (szle == 0 || szri == 0) {
					//printf("can ignore ans:[%d]\n", i);
					ignoreCount++;
					goto con;
				}
				
				
				//set_intersection(le.begin(), le.end(), ri.begin(), ri.end(), inserter(var_inter, var_inter.begin()));
				//cout << "Intersection of two sets: "; 
  				//for (auto i : var_inter) { cout << i.first << " " << i.second <<  " "; }
				//cout << endl;
			}
			pos++;
		} while ((fr = strtok(NULL, "-\n")) != NULL);
		printf("\n");
		//getchar();

con:
	continue;
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				ve[i][j] = veOrig[i][j];
			}
		}

	}
	printf("ansPos - ignoreCount is %d\n", ansPos - ignoreCount);
};