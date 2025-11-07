#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    std::ifstream in("2.txt");
    std::vector<long double> gears; long double d;

    while (in >> d) gears.push_back(d);

    long double ans = 1;

    for (int i = gears.size() - 1; i > 0; --i) {
        ans *= gears[i] / gears[i - 1];
    }

    std::cout << (long long)std::ceil(ans * 10000000000000); 
}