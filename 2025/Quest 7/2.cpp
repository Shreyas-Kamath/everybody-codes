#include <ranges>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

bool check(const std::string& name, const std::unordered_map<char, std::string>& rules) {

    for (const auto& window: name | std::views::slide(2)) {
        char key = window.at(0);
        char value = window.at(1);

        if (!rules.contains(key)) return false;
        if (!rules.at(key).contains(value)) return false;
    }

    return true;
}

int main() {
    std::ifstream in("names.txt"); std::string n;
    in >> n;

    std::vector<std::string> names = n | std::views::split(',') | std::ranges::to<std::vector<std::string>>();

    std::unordered_map<char, std::string> rules;

    std::ifstream in2("2.txt");

    while (std::getline(in2, n))
    {
        char key = n.front();
        auto substr = n.substr(n.find('>') + 2);

        rules[key] = substr | std::views::split(',') | std::views::join | std::ranges::to<std::string>();
    }
    
    int sum{};

    for (const auto& [index, name]: std::views::enumerate(names)) {
        if (check(name, rules)) sum += index + 1;
    }

    std::cout << sum;
}