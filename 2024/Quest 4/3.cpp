#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> nails; nails.reserve(500);

    std::string line; std::ifstream file("data3.txt");

    while (std::getline(file, line)) { nails.emplace_back(std::stoi(line)); }

    int mid = nails.size() / 2;
    std::nth_element(nails.begin(), nails.begin() + mid, nails.end());

    long long ans{}, median = nails[mid];

    for (const auto& nail: nails) ans += std::abs(nail - median);

    std::cout << ans;
}