//vss2sn
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <array>

using namespace std;
struct Mapping {
	long long destination_start;
	long long source_start;;
	long long range;

	bool in_destination_range(const long long n) const {
		return n >= destination_start && n <= destination_start + range;
	}

	bool in_source_range(const long long n) const {
		return n >= source_start && n <= source_start + range;
	}

	long long get_mapping(const long long n) const {
		return destination_start + (n - source_start);
	}
};

struct Map {
	string map_from;
	string map_to;
	vector<Mapping> mappings;
};

vector<long long> extract(const string& s) {
	vector<long long> numbers;
	long long start = 0;
	long long end = s.find(' ');
	while (end != string::npos) {
		// cout << s.substr(start, end - start) << '|' << '\n';
		numbers.push_back(stoll(s.substr(start, end - start)));
		start = end + 1;
		end = s.find(' ', start);
	}
	// cout << s.substr(start, s.size() - start) << '|' << '\n';
	numbers.push_back(stoll(s.substr(start, s.size() - start)));
	return numbers;
}

vector<string> parameters {
	"soil", "fertilizer", "water", "light", "temperature", "humidity", "location"
};

long long get_location (long long value, const vector<Map>& maps, const string& map_from) {
	if (map_from == "location") {
		return value;
	}
	const auto map = *find_if(
			begin(maps), 
			end(maps), 
			[&map_from](const auto& map) {
			return map.map_from == map_from;
			}
			);
	for (const auto& mapping : map.mappings) {
		if (mapping.in_source_range(value)) {
			return get_location(mapping.get_mapping(value), maps, map.map_to);
		} 
	}
	return get_location(value, maps, map.map_to);
}

int main(int argc, char * argv[]) {
	printf("		2023 Day 5 Part 1\n");
	string input = argv[1];
	if (argc > 1) {
		input = argv[1];
	}

	string line;
	fstream file(input);
	vector<Map> maps;
	getline(file, line);
	// cout << line << '\n';
	vector<long long> seeds = extract(line.substr(7, line.size() - 7));

	while(getline(file, line)) {
		if (line.empty()) {
			getline(file, line);
			// cout << line << '\n';

			Map map;
			long long start = 0;
			long long end = line.find('-');
			map.map_from = line.substr(start, end - start);
			start = end + 4;
			end = line.find(' ', start);
			map.map_to = line.substr(start, end - start);
			//cout << map.map_from << " ---> " << map.map_to << '\n';
			maps.push_back(map);
			getline(file, line);
		}
		// cout << line << '\n';

		const auto numbers = extract(line);
		Mapping mapping;
		mapping.destination_start = numbers[0];
		mapping.source_start = numbers[1];
		mapping.range = numbers[2];
		// for (const auto number : numbers) {
		//   cout << number << ' ';
		// }
		// cout << '\n';
		maps.back().mappings.push_back(mapping);
	}

	vector<long long> locations;
	for (const auto& seed : seeds) {
		locations.push_back(get_location(seed, maps, "seed"));
		//cout << locations.back() << '\n';
	}
	//cout << *min_element(begin(locations), end(locations)) << '\n';
	//cout << *min_element(begin(locations), end(locations)) << '\n';

	printf("**ans: %lld\n", *min_element(begin(locations), end(locations))); 
	return 0;
}
