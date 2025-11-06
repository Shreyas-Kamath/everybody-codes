#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <ranges>
#include <algorithm>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    std::unordered_map<int, int> freq; std::string line;

    std::ifstream in("3.txt");

    std::getline(in, line);

    std::istringstream iss(line); std::string n;

    while (std::getline(iss, n, ',')) {
        int val = std::stoi(n);
        ++freq[val];
    }
    
    std::cout << ranges::max(freq | views::values);
}