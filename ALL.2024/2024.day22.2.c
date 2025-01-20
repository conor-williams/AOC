#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <deque>
#include <map>
#include <set>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <time.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
int lenx;
int leny;
deque <unsigned long long> secrets;
int TIMES = 2000;
void printit(deque <unsigned long long> s1);
unsigned long long mix(unsigned long long secret, unsigned long long in);
unsigned long long prune(unsigned long long in);

struct hash_function
{
	size_t operator()(const tuple<int , int , int, int>&x) const
	{
		unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
	}
};

array <unordered_map <tuple<int, int, int, int>, int, hash_function>, 3000> sellerMonkey;
unordered_set <tuple<int, int, int, int>, hash_function> seqset;
deque <tuple<int, int, int, int>> deQ;
tuple<int, int, int, int> maxtu;

struct diff_s {
	int val;
	int dif;
};
unsigned long long maxSum = 0;
int curTot = 0;
int curInQ = 0;
void sigfunc(int a) { printf("[[ %d of %d ]]\n", curInQ, curTot); }
struct diff_s diffs[3000][2001];
int main(int argc, char **argv)
{
	printf("SLOW ~2minutes\n");
        clock_t start, end; double cpu_time_used;

	if (argc == 3) {TIMES = atoi(argv[2]);}

	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 22 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		char *bla;
		unsigned long long pu = strtoull(line1, &bla, 10);
		secrets.push_back(pu);
		leny++;
	}
	fclose(a);
	printf("Creating diffs\n");
        start = clock();
	for (int i = 0; i < TIMES; i++) {
		deque <unsigned long long> secretsTmp;
		int numpos = 0;
		for (auto snum: secrets) {
			unsigned long long snumBef = snum;
			unsigned long long mul1 = snum *64;
			snum = mix(snum, mul1);
			snum = prune(snum);
			unsigned long long div1 = snum / 32;
			snum = mix(snum, div1);
			snum = prune(snum);
			unsigned long long mul2 = snum * 2048;
			snum = mix(snum, mul2);
			snum = prune(snum);
			secretsTmp.push_back(snum);

			diffs[numpos][i].dif = (snum % 10 - snumBef % 10);
			diffs[numpos][i].val = (snum % 10);
			numpos++;
		}

		secrets = secretsTmp;
		secretsTmp.clear();		
	}
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("        time: %f seconds\n", cpu_time_used);

	printf("Creating Sequences\n");
#ifdef _DEBUG_
	int curCreate = 0;
#endif
	start = clock();
	for (int numpos = 0; numpos < leny; numpos++) {
#ifdef _DEBUG_
		if (curCreate % 300 == 0) {printf("	(%4d) of (%d)\n", curCreate, leny);}
		curCreate++;
#endif

		diff_s *diffsPtr = diffs[numpos];
		for (int i = 3; i < TIMES; i++) {
			int one = diffsPtr[i-3].dif;
			int two = diffsPtr[i-2].dif;
			int three = diffsPtr[i-1].dif;
			int four = diffsPtr[i].dif;
			tuple <int, int, int, int> tu1 = make_tuple(one, two, three, four);
			int v5 = diffsPtr[i].val;

			if (sellerMonkey[numpos].find(tu1) == sellerMonkey[numpos].end()) {
				sellerMonkey[numpos][tu1] = v5;
				if (seqset.find(tu1) == seqset.end()) {
					seqset.insert(tu1);
					deQ.push_back(tu1);
				}
			} else {
			}
		}
	}
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("        time: %f seconds\n", cpu_time_used);


#ifdef _DEBUG_
	curTot = 0; printf("deQ size is %d\n", curTot = (int)deQ.size());
	curInQ = 0;
#endif
	printf("Summing each (slow approx: 1min) in deQ (%d) of each Monkey (%d)\n", (int)deQ.size(), leny);
	unsigned long long tmpSum = 0;
	start = clock();
	for (auto tu: deQ) {
#ifdef _DEBUG_
		if (curInQ % 3000 == 0) {printf("	(%5d) of (%d)\n", curInQ, curTot);}
		curInQ++;
#endif
		tmpSum = 0;
		for (int numpos = 0; numpos < leny; numpos++) {
			//look ahead
			if ((((leny - numpos) * 9) + tmpSum) < maxSum) {goto next;}
			if ((sellerMonkey[numpos].find({tu})) != sellerMonkey[numpos].end()) {
				tmpSum += sellerMonkey[numpos][{tu}];
			}
		}
		if (tmpSum > maxSum) {maxtu = tu; maxSum = tmpSum;}
next:
		continue;
	}
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("        time: %f seconds\n", cpu_time_used);

	printf("maxtu %d,%d,%d,%d\n", get<0>(maxtu), get<1>(maxtu), get<2>(maxtu), get<3>(maxtu));
	printf("TIMES: %d\n", TIMES);

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", maxSum);

}
void printit(deque <unsigned long long> s1) {
	for (auto n1: s1) {
		printf("%llu " , n1);
	}
	printf("\n");
}
unsigned long long mix(unsigned long long secret, unsigned long long inin) {
	return inin ^ secret;

}
unsigned long long prune(unsigned long long inin) {
	return inin % 16777216;
}














/* -- 
   maxSum = 0; tuple <int, int, int, int> my_var = make_tuple(0, 0, -1, 1);

   int myvarSum = 0;
   for (int numpos = 0; numpos < leny; numpos++) {
   if (sellerMonkey[numpos].find({my_var}) != sellerMonkey[numpos].end()) {
   myvarSum += sellerMonkey[numpos][{my_var}];
   }
   }
   printf("myvarSum is %d\n", myvarSum);
 */
//int one = get<0>(tu.first);
//int two = get<1>(tu.first);
//int three = get<2>(tu.first);
//int four = get<3>(tu.first);
//printf("%d %d %d %d -> %d\n", one, two, three, four, tu.second);
/*
   printf("Creating seqset\n");
   int seqCreate = 0;
   for (int numpos = 0; numpos < leny; numpos++) {
   seqCreate++;
   if (seqCreate % 300 == 0) {printf("(%d) of (%d)\n", seqCreate, leny);}

   for (auto elem: sellerMonkey[numpos]) {
   if (seqset.find(elem.first) == seqset.end()) {
   seqset.insert(elem.first);
   }
   }
   }
   printf("Created seqset\n");
 */
/*
   if (v5 > sellerMonkey[numpos][{one, two, three, four}]) {
//only the first time -- not the largest
//sellerMonkey[numpos][{one, two, three, four}] = v5;
}
 */
/*
   int one = diffs[numpos][i-3].dif;
   int two = diffs[numpos][i-2].dif;
   int three = diffs[numpos][i-1].dif;
   int four = diffs[numpos][i].dif;
   tuple <int, int, int, int> tu1 = make_tuple(one, two, three, four);
   int v5 = diffs[numpos][i].val;
 */
/*
struct PearsonHashing2
{
    size_t operator()(const tuple<int, int, int, int>&x) const
    {
	unsigned int T[] = {};
        
        unsigned int hash = 0;

	unsigned int bytes[5];
	bytes[0] = get<0>(x);
	bytes[1] = get<1>(x);
	bytes[2] = get<2>(x);
	bytes[3] = get<3>(x);
	for (int i = 0; i < 4; i++)
        {
		unsigned int arSubscript = (unsigned int)hash ^ (unsigned int)bytes[i];
	        hash = T[arSubscript];
        }

        return hash;
    }
};
*/
/*
struct PearsonHashing1
{
    byte operator()(const tuple<int, int, int, int>&x) const
    {
	byte T[] = {};
        
        byte hash = (byte)0;

	byte bytes[5];
	bytes[0] = (byte)get<0>(x);
	bytes[1] = (byte)get<1>(x);
	bytes[2] = (byte)get<2>(x);
	bytes[3] = (byte)get<3>(x);
	for (auto b: bytes)
        {
            hash = T[hash ^ b];
        }

        return hash;
    }
};
*/
/*
struct hash_function
{
	size_t operator()(const tuple<int , int , int, int>&x) const
	{
		unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
		//unsigned int hash = ((get<0>(x) & 0x18) << 3) | ((get<1>(x) & 0x18) << 1) | ((get<2>(x) & 0x18) >> 1) | ((get<3>(x) & 0x18) >> 3);
		return hash;

		//unsigned int hash = get<0>(x); hash *= 13; hash += get<1>(x); hash *= 13; hash += get<2>(x); hash *= 13; hash += get<3>(x); return hash;
		//unsigned int hash = get<0>(x); hash *= 13; hash += get<1>(x); hash *= 13; hash += get<2>(x); hash *= 13; hash += get<3>(x); return hash;
	}
};
*/
/*
struct hash_function
{
	size_t operator()(const tuple<int , int , int, int>&x) const
	{
		//BADunsigned int hash = get<0>(x); hash |= get<1>(x) << 4; hash |= get<2>(x) << 8; hash |= get<3>(x) << 12; return hash;
		unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 37; hash += get<2>(x); hash *= 37; hash += get<3>(x); return hash;
		//SLOWunsigned int hash = get<0>(x); hash += get<1>(x) * 16; hash += get<2>(x); hash *= 32; hash += get<3>(x)*64; return hash;
		//              return get<0>(x) ^ get<1>(x) ^ get<2>(x) ^ get<3>(x);
	}
};
*/
//array <map <tuple<int, int, int, int>, int>, 3000> sellerMonkey;
/*
struct key {};
struct my_hash
{
	my_hash() {}
	//my_hash(int i = 42) {}  // <<-- uncomment for bug
	std::size_t operator()(const key &ep) const { return 0; }
};
*/
//unordered_set <tuple<int, int, int, int>, PearsonHashing> seqset;
