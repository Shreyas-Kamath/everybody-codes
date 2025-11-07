#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <optional>

struct Gear {
    double first{};
    std::optional<double> second = std::nullopt;
};

int main() {
    std::ifstream in("3.txt");
    std::vector<Gear> gears; std::string line;

    while (std::getline(in, line)) {
        auto find = line.find('|');
        if (find == std::string::npos) gears.emplace_back(std::stod(line));
        else gears.emplace_back(std::stod(line.substr(0, find)), std::stod(line.substr(find + 1)));
    }

    long double ans{1};

    for (int i{}; i < gears.size() - 1; ++i) {
        const auto& prev = gears[i];
        const auto& next = gears[i + 1];

        ans *= prev.second.value_or(prev.first) / next.first;
    }

    std::cout << (long long)(ans * 100);

}