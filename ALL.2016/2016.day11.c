#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <ctime>
#include <map>
#include <numeric>
#include <tuple>

using namespace std;
//vector<vector<tuple<int, int>>> visited_states;
vector<vector<tuple<int, vector<int>>>> visited_states;

#define getchar()
bool checkGenChipPairs(const vector<int>& vio_list) {
	// gen-chip pair
	vector<pair<int, int>> pairs;
	for (size_t i = 1; i < vio_list.size(); i += 2) {
		if (i + 1 < vio_list.size()) {
			pairs.push_back(make_pair(vio_list[i], vio_list[i + 1]));
		}
	}

	// floors of generators
	vector<int> gens;
	for (size_t i = 1; i < vio_list.size(); i += 2) {
		gens.push_back(vio_list[i]);
	}

	// check if any gen-chip pair is not on same floor, if true check if any gen is on the same floor as chip
	for (const auto& pair : pairs) {
		if (pair.first != pair.second) {
			if (find(gens.begin(), gens.end(), pair.second) != gens.end()) {
				return true;
			}
		}
	}
	return false;
}
/*
   bool violate(const vector<int>& vio_list) {
   vector<int> pairs;
   for (size_t x = 0; x < vio_list.size() - 1; x += 2) {
   pairs.push_back(vio_list[x]);
   pairs.push_back(vio_list[x + 1]);
   }
   vector<int> gens;
   for (size_t i = 1; i < vio_list.size(); i += 2) {
   gens.push_back(vio_list[i]);
   }
   for (size_t i = 0; i < pairs.size(); i += 2) {
   if (pairs[i] != pairs[i + 1]) {
   if (find(gens.begin(), gens.end(), pairs[i + 1]) != gens.end()) {
   return true;
   }
   }
   }
   return false;
   }
   */

bool vis_state(const vector<int>& vis_l) {
	//cout << "vis_l: " << endl;
	/*
	   for (const auto& val : vis_l) {
	   cout << val << " ";
	   }
	   cout << endl;
	   */

	// gen-chip pair
	vector<vector<int>> pairs;
	for (size_t i = 1; i < vis_l.size(); i += 2) {
		if (i + 1 < vis_l.size()) {
			pairs.push_back({vis_l[i], vis_l[i + 1]});
		}
	}

	// add floor to every pair
	vector<tuple<int, vector<int>>> state;
	//	vector<vector<tuple<int, int>>> visited_states;
	for (const auto& pair : pairs) {
		state.emplace_back(vis_l[0], pair);
	}

	// create unique state by adding floor to every pair and then sort by pair
	sort(state.begin(), state.end(), [](const auto& tup1, const auto& tup2) {
			return tup1 < tup2;
			});

	// check if the unique state already been visited, if not store in global visited_states
	if (find(visited_states.begin(), visited_states.end(), state) != visited_states.end()) {
		return true;
	} else {
		visited_states.push_back(state);
		return false;
	}
}
/*
   bool vis_state(const vector<int>& vis_l) {
   vector<tuple<int, int>> pairs;
   for (size_t x = 1; x < vis_l.size(); x += 2) {
//pairs.emplace_back(vis_l[0], vis_l[x]);
pairs.emplace_back(vis_l[x], vis_l[x+1]);
}
sort(pairs.begin(), pairs.end(), [](const tuple<int, int>& a, const tuple<int, int>& b) {
return get<1>(a) < get<1>(b);
});
if (find(visited_states.begin(), visited_states.end(), pairs) != visited_states.end()) {
return true;
} else {
visited_states.push_back(pairs);
return false;
}
}
*/

int main(int argc, char **argv) {
	//printf("ta->> karlanka + products.codeporting.ai + codeconvert.ai -- (broke into snippets)\n");
	printf("		2016 day 11 Part 1\n");
	//printf("--	does not use an input file\n");
	//vector<pair<vector<int>, int>> visited = { {{0, 1, 0, 2, 0}, 0} };
	//#visited = [([0, 1, 0, 2, 0], 0)]  # test
	vector<pair<vector<int>, int>> visited = { {{0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 2}, 0} };
	//#visited = [([0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 2], 0)]  # 1
	//vector<pair<vector<int>, int>> visited = { {{0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 2, 0, 0, 0, 0}, 0} };
	//visited = [([0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 2, 0, 0, 0, 0], 0)]  # 2

	int loops = 0;
	//for (const auto &lk : visited) {
	int sz = (int)visited.size();
	int bbb = 23;
	//for (const auto& lk : visited) {

	for (int iii = 0; iii < sz; iii++) {
		//if (iii == 0) {visited_new = visited;}
		/*
		   printf("visited.size is %d\n", (int)visited.size()); getchar();
		   for (auto it2 = visited.begin(); it2 != visited.end(); it2++) {
		   pair pa1 = *it2;
		   auto vec1 = pa1.first;
		   auto int1 = pa1.second;
		   for (auto it3 = vec1.begin(); it3 != vec1.end(); it3++) {
		   printf(" %d ", *it3);
		   }
		   printf("int1: %d\n", int1);
		   }
		   */
		//if (bbb == 25) {exit(0);}
		bbb++;
		//printf("in lk...\n");
		auto lk = visited[iii];
		vector<int> l = lk.first;
		int curr_floor = l[0];
		int curr_try = lk.second;
		vector<int> at_e_level;
		for (size_t i = 0; i < l.size(); ++i) {
			if (l[i] == curr_floor) {
				at_e_level.push_back(i);
			}
		}
		//printf("at_elevel.size() %d\n", (int)at_e_level.size());
		at_e_level.erase(at_e_level.begin()); // Remove the first occurrence
						      //printf("at_elevel.size() %d\n", (int)at_e_level.size());
		vector<tuple<int, int>> possible_moves;

		for (size_t i = 0; i < at_e_level.size(); ++i) {
			for (size_t j = i + 1; j < at_e_level.size(); ++j) {
				possible_moves.emplace_back(at_e_level[i], at_e_level[j]);
			}
		}
		/////////////////////////////////////
		//vector<int> at_e_level; // Initialize this vector with appropriate values
		//vector<pair<int, int>> possible_moves;

		// Generate combinations of two elements from at_e_level
		//for (size_t i = 0; i < at_e_level.size(); ++i) {
		//   for (size_t j = i + 1; j < at_e_level.size(); ++j) {
		//      possible_moves.push_back(make_pair(at_e_level[i], at_e_level[j]));
		// }
		//}

		// Add individual elements from at_e_level to possible_moves

		for (size_t i = 0; i < at_e_level.size(); ++i) {
			possible_moves.emplace_back(at_e_level[i], -99);
		}

		/*
		   for (const int &element : at_e_level) {
		   possible_moves.push_back({element, element}); // Assuming we want to add pairs of the same element
		   }
		   */
		/////////////////////////////////////

		//possible_moves.insert(possible_moves.end(), at_e_level.begin(), at_e_level.end());
		vector<int> dirs;
		if (curr_floor == 0) {
			dirs.push_back(1);
		} else if (curr_floor == 3) {
			dirs.push_back(-1);
		} else {
			dirs.push_back(-1);
			dirs.push_back(1);
		}
		vector<int> old_l = l;
		if (curr_floor == 1 && count(l.begin(), l.end(), 0) == 0) {
			dirs.erase(dirs.begin());
		}
		if (curr_floor == 2 && count(l.begin(), l.end(), 0) == 0 && count(l.begin(), l.end(), 1) == 0) {
			dirs.erase(dirs.begin());
		}
		for (int d : dirs) {
			//printf("dir d:%d\n", d);
			for (tuple<int, int> each : possible_moves) {
				//printf("each: %d %d\n", get<0>(each), get<1>(each));
				loops++;
				vector<int> test_l = old_l;

				if (get<1>(each) != -99) {
					if (d == -1) {
						continue;
					}
					test_l[0] = curr_floor + d;
					test_l[get<0>(each)] = curr_floor + d;
					test_l[get<1>(each)] = curr_floor + d;
				} else {
					test_l[0] = curr_floor + d;
					//test_l[each.first] = curr_floor + d;
					test_l[get<0>(each)] = curr_floor + d;
				}
				if (!checkGenChipPairs(test_l)) {
					/*
					   printf("here1....\n");
					   printf("test_l: ");
					   for (auto qqq: test_l) {
					   printf("%d ", qqq);
					   }
					   printf("\n");
					   */
					if (vis_state(test_l)) {
						//printf("continue...\n");
						continue;
					} else {
						visited.emplace_back(test_l, curr_try + 1);
						//printf("emplace...\n");
					}
				}
				if ((int)accumulate(test_l.begin(), test_l.end(), 0) == (int)test_l.size() * 3) {
					//cout << "current state: ";
					/*
					   for (int state : test_l) {
					   cout << state << " ";
					   }
					   cout << endl;
					   */
					/*
					   cout << "elapsed time: " << (clock() - start_time) / (double)CLOCKS_PER_SEC << endl;
					   cout << "allowed states visited: " << visited.size() << endl;
					   cout << "total visits: " << loops << endl;
					cout << "moves: " << curr_try + 1 << endl;
					   */
					printf("**ans: %d\n", curr_try+1);
					exit(0);
				}
			}
		}
		//printf("visited.size is %d\n", (int)visited.size());
		sz = (int)visited.size();
		//iii = -1;

	}
}

