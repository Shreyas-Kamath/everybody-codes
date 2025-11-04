#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <ranges>
#include <sstream>
#include <algorithm>

int main() {
    std::string line; std::ifstream in("1.txt");

    std::vector<std::pair<char, int>> vec;

    while (std::getline(in, line)) {
        auto pos = line.find(':');
        auto first = line.substr(0, pos);

        int start{10};
        int sum{};

        std::istringstream after(line.substr(pos + 1));

        std::string token;

        while (std::getline(after, token, ',')) {
            if (token == "+") ++start;
            else if (token == "-") --start;

            sum += start;
        }

        vec.emplace_back(line[0], sum);
    }

    std::ranges::sort(vec, std::greater{}, &std::pair<char, int>::second);
    std::string ans;

    for (const auto& [key, _]: vec) ans.push_back(key);
    std::cout << ans;
}
