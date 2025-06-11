#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line; std::ifstream in("1.txt");

    std::unordered_map<std::string, int> counts;
    std::unordered_map<std::string, std::vector<std::string>> children;

    counts["A"] = 1;

    while (std::getline(in, line)) {
        auto find = line.find(":");

        std::string parent = line.substr(0, find);

        std::string kids = line.substr(find + 1);

        std::istringstream iss(kids); std::string kid;

        while (std::getline(iss, kid, ',')) children[parent].push_back(kid);
    }

    for (int i{}; i < 4; ++i) {
        std::unordered_map<std::string, int> newCounts;
        for (const auto& [parent, count]: counts) {
            for (const auto& child: children[parent]) newCounts[child] += count;
        }
        counts = std::move(newCounts);
    }

    int total{};

    for (const auto& [parent, count]: counts) total += count;
    std::cout << total;
}