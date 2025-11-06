#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
#include <iostream>

int main() {
    std::unordered_set<int> nums; std::string line;

    std::ifstream in("1.txt");

    std::getline(in, line);

    std::istringstream iss(line); std::string n;

    while (std::getline(iss, n, ',')) nums.emplace(std::stoi(n));
    
    std::cout << std::accumulate(nums.begin(), nums.end(), 0);
}