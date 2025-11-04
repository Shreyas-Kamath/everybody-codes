#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <iostream>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    std::string line;

    std::ifstream in("3-names.txt");

    std::getline(in, line);
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

    auto vec = line
    | views::split(',')
    | ranges::to<std::vector<std::string>>();

    std::ifstream in2("3-dirs.txt"); std::getline(in2, line);

    int n = (int)vec.size();

    for (auto sp: line | views::split(',')) {
        char dir = sp[0];
        int dist = std::stoi(std::string(sp.begin() + 1, sp.end()));

        int target;

        if (dir == 'L') {
            target = (- dist) % n;
            if (target < 0) target += n;
        }
        else target = dist % n;
        
        std::swap(vec[target], vec[0]);
    }

    std::cout << vec.front();
}