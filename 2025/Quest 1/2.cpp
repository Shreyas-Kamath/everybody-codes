#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <iostream>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    std::string line;

    std::ifstream in("2-names.txt");

    std::getline(in, line);
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

    auto vec = line
    | views::split(',')
    | ranges::to<std::vector<std::string>>();

    std::ifstream in2("2-dirs.txt"); std::getline(in2, line);

    int index{};

    for (auto sp: line | views::split(',')) {
        char dir = sp[0];
        int dist = std::stoi(std::string(sp.begin() + 1, sp.end()));

        if (dir == 'L') {
            int new_pos = index - dist;
            new_pos %= (int)vec.size();
            if (new_pos < 0) new_pos += vec.size();
            index = new_pos;
        }
        else index = (index + dist) % vec.size();
    }

    std::cout << vec[index];
}