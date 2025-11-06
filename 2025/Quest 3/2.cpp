#include <unordered_set>
#include <fstream>
#include <string>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    std::unordered_set<int> nums; std::string line;

    std::ifstream in("2.txt");

    std::getline(in, line);

    for (const auto n: line | views::split(',')) 
        nums.emplace(std::stoi(std::string(n.begin(), n.end())));
    
    std::vector<int> vec(nums.begin(), nums.end());

    ranges::nth_element(vec.begin(), vec.begin() + 19, vec.end());

    std::cout << ranges::fold_left(vec | views::take(20), 0, std::plus<int>{});
}