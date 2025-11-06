#include <unordered_set>
#include <fstream>
#include <string>
#include <ranges>
#include <algorithm>
#include <iostream>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    std::unordered_set<int> nums; std::string line;

    std::ifstream in("1.txt");

    std::getline(in, line);

    for (const auto n: line | views::split(',')) 
        nums.emplace(std::stoi(std::string(n.begin(), n.end())));
    
    std::cout << ranges::fold_left(nums, 0, std::plus<int>{});
}