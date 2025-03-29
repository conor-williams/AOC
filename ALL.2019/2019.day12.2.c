#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <map>
#include <numeric> // for std::gcd (C++17)
#include <algorithm>

using namespace std;

//gboyegadada

// Equivalent to Python's: f=str("i1.txt").strip()
string f;

class Body {
	public:
		vector<int> pos;
		vector<int> vel;
		// Constructor equivalent to Python's __init__
		Body(const vector<int>& p, const vector<int>& v) : pos(p), vel(v) { }
		// Equivalent to Python's __str__
		string toString() const {
			// Format: pos=<x={0}, y={1}, z={2}>
			ostringstream spos;
			spos << "pos=<x=" << pos[0] << ", y=" << pos[1] << ", z=" << pos[2] << ">";
			// Format: vel=<x={0}, y={1}, z={2}>
			ostringstream svel;
			svel << "vel=<x=" << vel[0] << ", y=" << vel[1] << ", z=" << vel[2] << ">";
			// Combined string
			ostringstream result;
			result << spos.str() << ", " << svel.str();
			return result.str();
		}
};

// Overload operator<< for Body to support printing like Python's print(m)
ostream& operator<<(ostream& os, const Body& b) {
	os << b.toString();
	return os;
}

vector<Body> moons;

long long lcm(long long a, long long b) {
	// Equivalent to Python's lcm function: (a * b) // gcd(a, b)
	return (a * b) / std::gcd(a, b);
}

void step(vector<Body>& bodies) {
	// for m1, m2 in itertools.combinations(range(4), 2):
	for (int m1 = 0; m1 < 4; m1++) {
		for (int m2 = m1 + 1; m2 < 4; m2++) {
			// for i in range(3):
			for (int i = 0; i < 3; i++) {
				if (bodies[m1].pos[i] > bodies[m2].pos[i]) {
					bodies[m2].vel[i] += 1;
					bodies[m1].vel[i] -= 1;
				} else if (bodies[m1].pos[i] < bodies[m2].pos[i]) {
					bodies[m1].vel[i] += 1;
					bodies[m2].vel[i] -= 1;
				}
			}
		}
	}
	// for b in bodies:
	for (auto & b : bodies) {
		// for i in range(3): b.pos[i] += b.vel[i]
		for (int i = 0; i < 3; i++) {
			b.pos[i] += b.vel[i];
		}
	}
}

void one(vector<Body>& moons) {
	cout << "Solution 1:" << "\n------------------------------------\n" << endl;
	cout << "Input steps:" << endl;
	int steps;
	cin >> steps;

	cout << "\nAfter " << 0 << " steps:" << endl;
	for (auto & m : moons) {
		cout << m << endl;
	}

	for (int i = 0; i < steps; i++) {
		step(moons);

		if ((i + 1) % (steps / 10) == 0) {
			cout << "\nAfter " << (i + 1) << " steps:" << endl;
			for (auto & m : moons) {
				cout << m << endl;
			}
		}
	}

	cout << "\nEnergy after " << steps << " steps:" << "\n---------------------------\n" << endl;
	int total = 0;
	for (auto & m : moons) {
		int pot = 0, kin = 0;
		for (int x : m.pos) {
			pot += abs(x);
		}
		for (int x : m.vel) {
			kin += abs(x);
		}
		total += pot * kin;

		cout << "pot: " << pot << " ; kin: " << kin << " ; total: " << (pot * kin) << endl;
	}

	cout << "\n---------------------------\n" << "total: " << total << endl;
}

// Explanation by u/rabuf (https://www.reddit.com/user/rabuf/) 

long long two(vector<Body>& moons) {
	long long steps = 0;
	// period is a dictionary mapping axis index to steps count
	map<int, long long> period;
	// start = [[(m.pos[axis], m.vel[axis]) for m in moons] for axis in range(3)]
	vector< vector< pair<int, int> > > start(3);
	for (int axis = 0; axis < 3; axis++) {
		for (auto & m : moons) {
			start[axis].push_back({m.pos[axis], m.vel[axis]});
		}
	}
	while (period.size() < 3) {
		steps += 1;
		step(moons);

		for (int axis = 0; axis < 3; axis++) {
			// if axis not in period and start[axis] == [(m.pos[axis], m.vel[axis]) for m in moons]:
			if (period.find(axis) == period.end()) {
				vector< pair<int, int> > current;
				for (auto & m : moons) {
					current.push_back({m.pos[axis], m.vel[axis]});
				}
				if (current == start[axis]) {
					period[axis] = steps;
				}
			}
		}
	}

	// Compute the lcm of the period values
	long long ans = 1;
	for (auto & p : period) {
		ans = lcm(ans, p.second);
	}
	//cout << "ans: " << ans << endl;
	return ans;
}

int main(int argc, char **argv) {
	printf("2019 Day12 Part 2\n");
#ifdef _ACCOLADE_
	printf("codeconver.ai (no mods) + reddit @ dartcoder/algos(github) <-> python\n");
#endif
	f = argv[1];
	// Read the file f ("i1.txt")
	ifstream infile(f);
	if (!infile.is_open()) {
		cerr << "Error opening file: " << f << endl;
		return 1;
	}
	string line;
	// for l in open(f):
	while (getline(infile, line)) {
		// pos = [int(x[2:]) for x in l.strip('<>\n').split(', ')]
		// Remove '<', '>', and newlines from the line
		string cleaned;
		for (char c : line) {
			if (c != '<' && c != '>' && c != '\n')
				cleaned.push_back(c);
		}
		// Now cleaned string is like "x=-1, y=0, z=2" etc.
		vector<int> pos;
		vector<int> vel = {0, 0, 0};
		// Use stringstream to split by ", "
		stringstream ss(cleaned);
		string token;
		while(getline(ss, token, ',')) {
			// Remove any leading spaces
			if (!token.empty() && token[0] == ' ')
				token.erase(0, 1);
			// token is like "x=-1" so take substring starting from index 2
			int value = stoi(token.substr(2));
			pos.push_back(value);
		}
		moons.push_back(Body(pos, vel));
	}
	infile.close();

	// The original Python code calls two(moons)
	long long ans1 = two(moons);
	printf("**ans: %lld\n", ans1);

	return 0;
}

