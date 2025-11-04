#include <fstream>
#include <vector>
#include <string>
#include <ranges>

int main() {
    std::string line; std::ifstream in("1.txt");
    std::vector<std::string> grid;

    while (std::getline(in, line)) grid.push_back(std::move(line));
    in.close();

    std::ifstream in2("1-directions.txt");
    std::vector<std::string> directions;

    while (std::getline(in2, line)) directions.push_back(std::move(line));

    for (const auto& direction: directions) {
        int start = 
    }
}