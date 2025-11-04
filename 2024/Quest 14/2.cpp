#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_set>

int main() {
    std::string line; std::ifstream in("2.txt");

    std::unordered_set<std::string> visited;

    static const std::regex re(R"(([A-Z])(\d+))");

    while (std::getline(in, line)) {
        std::istringstream iss(line); std::string word;
        int x{}, y{}, z{};

        while (std::getline(iss, word, ',')) {
            std::smatch match;
            if (std::regex_match(word, match, re)) {
                std::string dir = match[1].str();
                int num = std::stoi(match[2]);

                if (dir == "U") y += num;
                else if (dir == "D") y -= num;
                else if (dir == "L") x -= num;
                else if (dir == "R") x += num;
                else if (dir == "F") z += num;
                else if (dir == "B") z -= num;

                visited.emplace(std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z));
            }
        }
    }


    std::cout << visited.size();
}