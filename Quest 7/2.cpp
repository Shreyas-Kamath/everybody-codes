#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <ranges>
#include <sstream>
#include <algorithm>

int main() {
    std::string line; std::ifstream in("2.txt");

    std::unordered_map<std::string, int> map;

    while (std::getline(in, line)) {
        auto pos = line.find(':');
        auto first = line.substr(0, pos);

        int start{10};
        int sum{};

        std::istringstream after(line.substr(pos + 1));

        std::string token;

        std::vector<std::string> actions;
        while (std::getline(after, token, ',')) {
            actions.push_back(token);
        }

        for (int i = 0; i < 10; ++i) {
            const std::string& action = actions[i % actions.size()];
            if (action == "+") ++start;
            else if (action == "-") start = std::max(0, start - 1);
            sum += start;
        }

        map[first] = sum;
    }

    std::vector<std::pair<std::string, int>> vec(map.begin(), map.end());

    std::ranges::sort(vec, [](const auto& lhs, const auto& rhs) {
        return lhs.second > rhs.second;
    });

    auto ans = vec
    | std::views::transform([](const auto& pair) { return pair.first; })
    | std::views::join
    | std::ranges::to<std::string>();

    std::cout << ans;
}
