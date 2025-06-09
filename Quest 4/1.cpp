#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {

    std::vector<int> nails;
    int min{INT_MAX};

    std::string line; std::ifstream file("data.txt");

    while (std::getline(file, line)) {
        int nail = std::stoi(line);
        nails.push_back(nail);

        min = std::min(min, nail);
    }

    int ans{};

    for (const auto& nail: nails) {
        ans += nail - min;
    }
    std::cout << ans;
}