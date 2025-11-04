#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <iostream>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    std::string line;

    std::ifstream in("1-names.txt");

    std::getline(in, line);

    auto vec = line
    | views::split(',')
    | ranges::to<std::vector<std::string>>();

    std::ifstream in2("1-dirs.txt"); std::getline(in2, line);

    int index{};

    for (auto sp: line | views::split(',')) {
        char dir = sp[0];
        int dist = std::stoi(std::string(sp.begin() + 1, sp.end()));

        int new_pos = dir == 'L' ? index - dist : index + dist;

        index = std::clamp(new_pos, 0, (int)vec.size() - 1);
    }

    std::cout << vec[index];
}