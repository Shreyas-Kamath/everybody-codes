#include <unordered_map>
#include <fstream>
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

    for (const auto n: line | views::split(',')) {
        int val = std::stoi(std::string(n.begin(), n.end()));
        ++freq[val];
    }
    
    std::cout << ranges::max(freq | views::values);
}