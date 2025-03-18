#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <unistd.h>


#define DAY "2023 Day12 Part2"
using namespace std;

int main(int argc, char **argv) {
	long long ways = 0;
   	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdout);
	int fd = dup(1); close(1);

	char line1[1000];
	int counter = 0;
	while(1) {
		counter++;
		//printf("%d \n", counter);

		fgets(line1, 999, a);
		if (feof(a)) break;
		//printf("LINE: %s", line1); fflush(stdout);

		char numsS[1000]; char record1[1000];
		sscanf(line1, "%s %s\n", record1, numsS);
		//printf("hashcode: %s -- numsS: %s\n", record1, numsS);

		vector <long long> checksum;
		char *token = strtok(numsS, ",");
		do {
			checksum.push_back(atoi(token));
		} while ((token = strtok(NULL, ",")) != NULL);

		//for (auto ii: checksum) { printf("%lld \n", ii); } printf("\n");

		unordered_map<long long, long long> positions;
		positions[0] = 1;

		//printf("record1: %s\n", record1);
		//     record = '?'.join([record for i in range(5)])
		//     checksum *= 5

		char recordOrig[100];
		strcpy(recordOrig, record1);
		
		for (int ii=0; ii< 4;ii++) {
			//sprintf(record1, "%s,%s", record1, recordOrig);
			strcat(record1, ",");
			strcat(record1, recordOrig);
		}
		
		//printf("record1 now: %s\n", record1);
		string record = record1;

		//cout << record << endl;

		vector <long long> checksumOrig = checksum;
		for (int ii = 0; ii < 4; ii++) {
			for (auto bb: checksumOrig) {
				checksum.push_back(bb);
			}
		}
		//for (auto ii: checksum) { printf("%lld ", ii); } printf("\n");


		long long oneof = 0;
		for (long long i = 0; i < (long long)checksum.size(); ++i) {
			long long contiguous = checksum[i];
			unordered_map<long long int, long long int> new_positions;

			for (const auto& [k, v] : positions) {
				for (long long n = k; n <= (long long)record.size() - accumulate(checksum.begin() + i + 1, checksum.end(), 0) + ((long long)checksum.size() - i - 1); ++n) {
					if (n + contiguous - 1 < (long long)record.size() && record.substr(n, contiguous).find('.') == string::npos) {
						if ((i == ((long long)checksum.size() - 1) && record.substr(n + contiguous).find('#') == string::npos) ||
								(i < (long long)checksum.size() - 1 && n + contiguous < (long long)record.size() && record[n + contiguous] != '#')) {
							new_positions[n + contiguous + 1] += v;
						}
					}
					if (record[n] == '#') {
						break;
					}
				}
			}
			positions = new_positions;
		} //ta https://www.codeconvert.ai/python-to-c++-converter && tmo1
		oneof = std::accumulate(positions.begin(), positions.end(), (long long)0, [](long long sum, const std::pair<long long, long long>& p) { return (long long)(sum + p.second); });
		if (oneof < 0) {printf("%d ERR...\n", counter);}
		if (counter == 72) {printf("%lld\n", oneof);}
		if (counter == 73) {printf("%lld\n", oneof);}
		if (counter == 74) {printf("%lld\n", oneof);}
		if (counter == 75) {printf("%lld\n", oneof);}
		ways += oneof;
		//printf("%lld + \n", oneof);
		
	}
	//std::cout << ways << std::endl;
	fflush(stdout); dup2(fd, 1); 
	printf("**ans: %lld\n", ways);

	return 0;
}


