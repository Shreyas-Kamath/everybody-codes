#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <iostream>

long long sim(const auto& map, int days, const std::string& parent) {
    std::unordered_map<std::string, long long> counts;
    ++counts[parent];

    for (int i{}; i < days; ++i) {
        std::unordered_map<std::string, long long> new_counts;
        
        for (const auto& [termite, freq]: counts) {
            for (const auto& child: map.at(termite)) new_counts[child] += freq;
        }
        counts = std::move(new_counts);
    }

    long long sum{};

    for (const auto& [_, freq]: counts) sum += freq;

    return sum;
}

int main() {
    std::string line; std::ifstream in("3.txt"); std::string child;

    auto start = std::chrono::high_resolution_clock::now();

    std::unordered_map<std::string, std::vector<std::string>> termite_map;
    std::unordered_map<std::string, long long> termite_counts;

    while (std::getline(in, line))
    {

        std::string parent = line.substr(0, 3);

        std::istringstream iss(line.substr(4));

        std::vector<std::string> children;

        while (std::getline(iss, child, ',')) children.push_back(child);

        termite_map[parent] = std::move(children);
    }
    
    const int days{ 20 }; long long max{ LLONG_MIN }, min{ LLONG_MAX };

    for (const auto& [parent, _]: termite_map) {
        const auto population = sim(termite_map, days, parent);

        max = std::max(max, population);
        min = std::min(min, population);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printf("%lld", max - min);
}