#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string line;
    std::ifstream in("data2.txt");
    std::vector<int> nums;
    
    while (std::getline(in, line)) nums.emplace_back(stoi(line));

    std::sort(nums.begin(), nums.end());

    int median = ((nums[nums.size() / 2] + nums[nums.size() / 2 - 1]) / 2) + 1;

    int ans{};

    for (const auto& num: nums) ans += abs(num - median);
    std::cout << ans;
}