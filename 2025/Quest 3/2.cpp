#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
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

    std::istringstream iss(line); std::string n;

    while (std::getline(iss, n, ',')) nums.emplace(std::stoi(n));
    
    std::vector<int> vec(nums.begin(), nums.end());

    ranges::nth_element(vec.begin(), vec.begin() + 19, vec.end());

    std::cout << ranges::fold_left(vec | views::take(20), 0, std::plus<int>{});
}