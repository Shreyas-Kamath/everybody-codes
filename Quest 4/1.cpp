#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string line;
    std::ifstream in("data.txt");
    std::vector<int> nums;
    
    while (std::getline(in, line)) nums.emplace_back(stoi(line));

    int min_elem = *std::min_element(nums.begin(), nums.end());

    int ans{};

    for (const auto& num: nums) ans += num - min_elem;

    std::cout << ans;
}