#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>

#define getchar()
//codeconvert.ai
int main() {
	printf("2022 Day 25 Part 1\n");
    std::vector<std::string> blah = {
        "1",
        "2",
        "1=",
        "1-",
        "10",
        "11",
        "12",
        "2=",
        "2-",
        "20",
        "1=0",
        "1-0",
        "1=11-2",
        "1-0---0",
        "1121-1110-1=0"
    };
    
    long long totOfNums = 0;
    for (size_t i = 0; i < blah.size(); i++) {
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        long long thisNum = 0;
        for (int z = blah[i].length() - 1; z >= 0; z--) {
            long long po = static_cast<long long>(blah[i].length() - 1 - z);
            long long sz = static_cast<long long>(std::pow(5, po));
            long long num = 0;
            switch (blah[i][z]) {
                case '2':
                    num = 2;
                    break;
                case '1':
                    num = 1;
                    break;
                case '0':
                    num = 0;
                    break;
                case '-':
                    num = -1;
                    break;
                case '=':
                    num = -2;
                    break;
                default:
                    break;
            }
            thisNum += sz * num;
        }
        std::cout << "+ " << thisNum << std::endl;
        totOfNums += thisNum;
    }
}
