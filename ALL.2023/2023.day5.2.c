//vss2sn
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <array>

using namespace std;
struct Mapping {
	array<long long, 2> from;
	array<long long, 2> to;

	long long apply_map(const long long n) const {
		return to[0] + (n - from[0]);
	}
};

struct Map {
	string map_from;
	string map_to;
	vector<Mapping> mappings;
};

vector<long long> extract(const string& s) {
	vector<long long> numbers;
	size_t start = 0;
	size_t end = s.find(' ');
	while (end != string::npos) {
		numbers.push_back(stoll(s.substr(start, end - start)));
		start = end + 1;
		end = s.find(' ', start);
	}
	numbers.push_back(stoll(s.substr(start, s.size() - start)));
	return numbers;
}

vector<pair<long long, long long>> apply_filter(vector<pair<long long, long long>> relevant_ranges, const vector<Mapping>& mappings) {
	vector<pair<long long, long long>> new_relevant_values;
	for (const auto&  relevant_range : relevant_ranges) {
		vector<pair<long long, long long>> ranges_where_filter_applied;
		vector<pair<long long, long long>> values_when_filter_applied;
		for (const auto& mapping : mappings) {
			if (relevant_range.second < mapping.from[0] || relevant_range.first > mapping.from[1]) continue;
			if (relevant_range.first >= mapping.from[0] && relevant_range.second <= mapping.from[1]) {
				ranges_where_filter_applied.emplace_back(relevant_range.first, relevant_range.second);
			} else if (relevant_range.first >= mapping.from[0] && relevant_range.second >= mapping.from[1]) {
				ranges_where_filter_applied.emplace_back(relevant_range.first, mapping.from[1]);
			} else if (relevant_range.first <= mapping.from[0] && relevant_range.second <= mapping.from[1]) {
				ranges_where_filter_applied.emplace_back(mapping.from[0],relevant_range.second);
			} else if (relevant_range.first <= mapping.from[0] && relevant_range.second >= mapping.from[1]) {
				ranges_where_filter_applied.emplace_back(mapping.from[0], mapping.from[1]);
			} else {
				cout << "?!" << '\n';
				exit(0);
			}
			values_when_filter_applied.emplace_back(mapping.apply_map(ranges_where_filter_applied.back().first), mapping.apply_map(ranges_where_filter_applied.back().second));
		}
		auto current_start = relevant_range.first;
		for (int i = 0; i < (int)ranges_where_filter_applied.size() ; i++) {
			new_relevant_values.emplace_back(current_start, ranges_where_filter_applied[i].first - 1);
			new_relevant_values.emplace_back(values_when_filter_applied[i].first, values_when_filter_applied[i].second);
			current_start = ranges_where_filter_applied[i].second + 1;
		}
		if (current_start <= relevant_range.second) {
			new_relevant_values.emplace_back(current_start, relevant_range.second);
		}
	}
	vector<pair<long long, long long>> filtered_new_relevant_values;
	copy_if (begin(new_relevant_values), end(new_relevant_values), back_inserter(filtered_new_relevant_values), [](const auto& ele ){
			return ele.first <= ele.second; 
			} );
	//   cout << new_relevant_values.size() << ' ' << filtered_new_relevant_values.size() << '\n';
	sort(begin(filtered_new_relevant_values), end(filtered_new_relevant_values), [](const auto& v1, const auto& v2) {return v1.first < v2.first;});
	return filtered_new_relevant_values;
}

int main(int argc, char * argv[]) {
	printf("2023 Day 5 Part 2\n");
	string input = argv[1];
	if (argc > 1) {
		input = argv[1];
	}

	string line;
	fstream file(input);
	vector<Map> maps;
	getline(file, line);
	vector<long long> input_ranges = extract(line.substr(7, line.size() - 7));
	vector<pair<long long, long long>> seeds;
	for (int i = 0; i < (int)input_ranges.size(); i+=2) {
		seeds.emplace_back(input_ranges[i], input_ranges[i] + input_ranges[i+1] - 1);
	}
	while(getline(file, line)) {
		if (line.empty()) {
			getline(file, line);
			Map map;
			long long start = 0;
			long long end = line.find('-');
			map.map_from = line.substr(start, end - start);
			start = end + 4;
			end = line.find(' ', start);
			map.map_to = line.substr(start, end - start);
			maps.push_back(map);
			getline(file, line);
		}
		const auto numbers = extract(line);
		Mapping mapping;
		mapping.to = {{numbers[0], numbers[0] + numbers[2]-1}};
		mapping.from = {{numbers[1], numbers[1] + numbers[2]-1}};
		// cout << mapping.from[0] << ' ' << mapping.from[1] << '\n';
		// cout << mapping.to[0] << ' ' << mapping.to[1] << '\n';
		maps.back().mappings.push_back(mapping);
	}

	for (auto& map : maps) {
		sort(begin(map.mappings), end(map.mappings), [](const auto& m1, const auto& m2) {return m1.from[0] < m2.from[0];});
	}

	for (int i = 0; i < (int)maps.size()-1; i++) {
		assert(maps[i+1].map_from == maps[i].map_to);
	}

	vector<pair<long long, long long>> relevant_values = seeds;
	for (const auto& map : maps) {
		relevant_values = apply_filter(relevant_values, map.mappings);
	}

	//cout << min_element(begin(relevant_values), end(relevant_values))->first << '\n';
	printf("**ans: %lld\n", min_element(begin(relevant_values), end(relevant_values))->first);
	return 0;
}
