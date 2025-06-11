#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line; std::ifstream in("3.txt");

    long long max{LLONG_MIN}; long long min{LLONG_MAX};

    std::unordered_map<std::string, long long> counts;
    std::unordered_map<std::string, std::vector<std::string>> children;
    std::vector<std::string> iters;

    while (std::getline(in, line)) {
        auto find = line.find(":");

        std::string parent = line.substr(0, find);
        iters.push_back(parent);

        std::string kids = line.substr(find + 1);

        std::istringstream iss(kids); std::string kid;

        while (std::getline(iss, kid, ',')) children[parent].push_back(kid);
    }

    for (const auto& iter: iters) {
        counts.clear();
        counts[iter] = 1;

        for (int i{}; i < 20; ++i) {
            std::unordered_map<std::string, long long> newCounts;
            for (const auto& [parent, count]: counts) {
                for (const auto& child: children[parent]) newCounts[child] += count;
            }
            counts = std::move(newCounts);
        }
        
        long long total{};
        for (const auto& [parent, count]: counts) total += count;

        max = std::max(max, total);
        min = std::min(min, total);
    }

    std::cout << max - min;
}