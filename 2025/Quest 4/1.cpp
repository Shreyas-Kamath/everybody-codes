#include <fstream>
#include <vector>
#include <iostream>

int main() {
    std::ifstream in("1.txt");
    std::vector<double> gears; double d;

    while (in >> d) gears.push_back(d);

    double ans{1};

    for (int i{}; i < gears.size() - 1; ++i) {
        ans *= gears[i] / gears[i + 1];
        
    }

    std::cout << ans * 2025;
}