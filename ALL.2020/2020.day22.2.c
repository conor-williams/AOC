#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <deque>
#include <map>
#include <unordered_map>
#include <unistd.h>
#include <set>
#include <unordered_set>

using namespace std;

#define MAX_ROUNDS 600
struct hash_func
{
	size_t operator()(const pair<deque<int> , deque<int>>&x) const
	{
		unsigned int hash = 0;
		auto q1 = x.first;
		for (auto it = q1.begin(); it!= q1.end(); it++) {
			hash+=*it;
			hash*=37;
		}
		auto q2 = x.second;
		for (auto it = q2.begin(); it!= q2.end(); it++) {
			hash+=*it;
			hash*=37;
		}
		return hash;
		///unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 37; hash += get<2>(x); hash *= 37; hash += get<3>(x); return hash;
	}
};

int lenx = 0;
int leny = 0;
int lenz = 0;

int LINE = 1000;

#define MAXIND 500
deque <int> player1[MAXIND];
deque <int> player2[MAXIND];
int score(deque<int> pl);
pair <int, int> game();

//unordered_map <tuple<deque<int>, deque<int>>, int, hash_func> mp[MAXIND];
//unordered_set <pair <deque<int>, deque<int>>, hash_func> mp[MAXIND];
set <pair <deque<int>, deque<int>>> mp[MAXIND];
void clearmp(int ind123);
int save(int ind, deque <int> player1, deque <int> player2);

int fd;
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("		2020 Day22 Part2\n"); fflush(stdout);
	fd = dup(1); close(1);
	char line1[LINE];

	int p1 = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);

		if (strcmp(line1, "Player 1:") == 0) {
			p1 = 1;
			continue;
		} else if (strcmp(line1, "Player 2:") == 0) {
			p1 = 0;
			continue;
		} else if (line1[0] == '\0') {
			continue;
		}

		if (p1 == 1) {
			player1[0].push_back(atoi(line1));
		} else if (p1 == 0) {
			player2[0].push_back(atoi(line1));
		}

		leny++;
	}
	fclose(a);
	printf("size player1 == %d\n", (int)player1[0].size());
	printf("size player2 == %d\n", (int)player2[0].size());

	auto pa = game();
	printf("winner: player%d\n", pa.first);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", pa.second);
	fflush(stdout);
}

int ind = -1;
int save(deque <int> player1, deque <int> player2) {
	//printf("saving...\n");
	//if (mp[ind].find({player1, player2}) == mp[ind].end()) {
	auto tu = make_pair(player1, player2);
	if (mp[ind].count(tu) == 0) {
		mp[ind].insert(tu);
		return 0;
	} else {
		return 1;
	}
}
pair<int, int> game() {
	ind++;
	//if (ind+10 > MAXIND) {fflush(stdout); dup2(fd, 1); printf("err: ind %d\n", ind); fflush(stdout); exit(0);}
	//for (int i = 0; i < ind; i++) {printf("	");} printf("game() ind is %d\n", ind);
	//mp[ind].clear();
	//clearmp(ind);
	int round = 0;
	int x1, x2;
	pair <int, int> res;
	res.first = -1;
	while (1) {
		if (round > MAX_ROUNDS) {res.first = 22; goto getscore;}
		res.first = -1;
		//int already = save(player1[ind], player2[ind]);
		//for (int i = 0; i < ind; i++) {printf("	");} printf("round: %d -- already is %d\n", round+1, already);
		//if (already == 1) {res.first = 22; goto getscore;}
		if ((int)player1[ind].size() == 0 || (int)player2[ind].size() == 0) { break; }
		//for (int i = 0; i < ind; i++) {printf("	");}

		//for (int i = 0; i < ind; i++) {printf("	");} printf("p1: ");
		//for (auto it = player1[ind].begin(); it != player1[ind].end(); it++) { printf("%d ", *it); } printf("\n");
		//for (int i = 0; i < ind; i++) {printf("	");} printf("p2: ");
		//for (auto it = player2[ind].begin(); it != player2[ind].end(); it++) { printf("%d ", *it); } printf("\n");
		x1 = player1[ind].front(); x2 = player2[ind].front();
		player1[ind].pop_front();
		player2[ind].pop_front();
		if ((int)player1[ind].size() >= x1 && (int)player2[ind].size() >= x2) {
			//for (int i = 0; i < ind; i++) {printf("	");} printf("sizes good... going to play...\n");
			// using std::make_move_iterator;

			 // std::deque<int> d2(make_move_iterator(from), make_move_iterator(to));
//  std::fill(from,to,0);
			player1[ind+1].assign(player1[ind].begin(), player1[ind].begin()+x1);

		       //	= //player1[ind];
			//player1[ind+1].pop_front();

			/*
			for (int ii = 0; ii <  (int)player1[ind+1].size()-x1; ii++) {
				player1[ind+1].pop_back();
			}
			*/
			//player2[ind+1] = player2[ind];
			player2[ind+1].assign(player2[ind].begin(), player2[ind].begin()+x2);
			//player2[ind+1].pop_front();
			/*
			for (int ii = 0; ii <  (int)player2[ind+1].size()-x2; ii++) {
				player2[ind+1].pop_back();
			}
			*/
			res = game();
		}

		//if (res.first == 1) {printf("player 1 wins special\n");} 
		//else if (res.first == 2) {printf("player 2 wins special\n");}
		if (res.first == 1 || (x1 > x2 && res.first == -1)) {
			//player1[ind].pop_front();
			//player2[ind].pop_front();
			player1[ind].push_back(x1);
			player1[ind].push_back(x2);
			//for (int i = 0; i < ind; i++) {printf("	");} printf("p1: wins round:%d\n", round+1);
		} else if (res.first == 2 || (x1 < x2 && res.first == -1)) {
			//player1[ind].pop_front();
			//player2[ind].pop_front();
			player2[ind].push_back(x2);
			player2[ind].push_back(x1);
			//for (int i = 0; i < ind; i++) {printf("	");} printf("p2: wins round %d\n", round+1);
		} else {
			fflush(stdout); dup2(fd, 1); printf("ERR\n"); fflush(stdout); exit(0);
		}

		round++;
		//getchar();
	}

getscore:
	//for (int i = 0; i < ind; i++) {printf("	");} printf("round is %d\n", round);
	if (res.first == 22 || (int)player1[ind].size() != 0) {
		//printf("player1 wins (%d)\n", (int)player1[ind].size());
		//printf("**score %d\n", score(player1[ind]));
		//for (int i = 0; i < ind; i++) {printf("	");} printf("p1: wins game\n");
		pair <int, int> pa;
		pa.first = 1;
		if (ind == 0) {
			pa.second = score(player1[0]);
			//if (res.first == 22) {printf("Player1: res at 22 (%d)\n", pa.second); fflush(stdout);}
			//if (res.first == 22) {printf("Player1: pop res at 22 (%d)\n", pa.second); fflush(stdout);}
			return pa;
		} else {
			pa.second = 0;
			ind--;
			return pa;
		}
	} else {
		//printf("player2 wins (%d)\n", (int)player2[ind].size());
		//printf("**score %d\n", score(player2[ind]));
		//for (int i = 0; i < ind; i++) {printf("	");} printf("p2: wins game\n");
		pair <int, int> pa;
		pa.first = 2;
		if (ind == 0) {
			pa.second = score(player2[0]);
			//if (res.first == 22) {printf("Player2 pop: res at 22 (%d)\n", pa.second); fflush(stdout);}
			return pa;
		} else {
			pa.second = 0;
			ind--;
			return pa;
		}

	}
	fflush(stdout); dup2(fd, 1);
	printf("never here...\n");
	fflush(stdout);
	ind--;
}

int score(deque<int> pl) {
	int sc = 0;
	//printf("pl.size() is %d\n", (int)pl.size());
	int size = (int)pl.size();
	for (int i = 0; i < size; i++) {
		int val = pl.back();
		//printf("%d - %d\n", val, i+1);
		sc += (val * (i+1));
		pl.pop_back();
	}
	return sc;
}

/*
   void clearmp(int ind123) {
   auto it = mp.begin();
   while (it != mp.end()) {
   auto tu = it->first;
   int indGet = get<0>(tu);
   if (ind123 == indGet) {
   printf("del..\n");
   it = mp.erase(it);
   } else {
   it++;
   }
   }
   }

*/
/*
template <typename ForwardIt>
std::deque<int> extract(ForwardIt from, ForwardIt to)
{
  using std::make_move_iterator;

  std::deque<int> d2(make_move_iterator(from),
                     make_move_iterator(to));
  std::fill(from,to,0);

  return d2;
}
*/
