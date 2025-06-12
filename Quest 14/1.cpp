#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

int main() {
    std::string line; std::ifstream in("1.txt");

    std::getline(in, line);

    static const std::regex re(R"(([A-Z])(\d+))");

    std::istringstream iss(line); std::string word;

    int height{}; int max_height{};

    while (std::getline(iss, word, ',')) {
        std::smatch match;
        if (std::regex_match(word, match, re)) {
            std::string dir = match[1].str();
            int num = std::stoi(match[2]);

            if (dir == "U") height += num;
            else if (dir == "D") height -= num;

            max_height = std::max(max_height, height);
        }
    }

    std::cout << max_height;
}