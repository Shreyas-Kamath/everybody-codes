#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

int sim(const auto& map, auto& counts, int days) {

    for (int i{}; i < days; ++i) {
        std::unordered_map<char, long long> new_counts;
        
        for (const auto& [termite, freq]: counts) {
            for (const auto& child: map.at(termite)) new_counts[child] += freq;
        }
        counts = std::move(new_counts);
    }

    int sum{};
    for (const auto& [_, freq]: counts) sum += freq;

    return sum;
}

int main() {
    std::string line; std::ifstream in("2.txt"); std::string child;

    std::unordered_map<char, std::vector<char>> termite_map;
    std::unordered_map<char, long long> termite_counts;

    termite_counts['Z'] = 1;

    while (std::getline(in, line))
    {
        char parent = line.front();

        std::istringstream iss(line.substr(2));

        std::vector<char> children;

        while (std::getline(iss, child, ',')) children.push_back(child.front());

        termite_map[parent] = std::move(children);
    }
    
    const int days{ 10 };

    printf("%d", sim(termite_map, termite_counts, days));
}