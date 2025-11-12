#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <ranges>
#include <iostream>

struct Node {
    int mid{};
    std::optional<int> less = std::nullopt, more = std::nullopt;

    Node(int num): mid(num) {};
};

int main() {
    std::string line; std::ifstream in("2.txt");
    
    long long max = LLONG_MIN, min = LLONG_MAX;

    while (std::getline(in, line)) {
        std::string nums = line.substr(line.find(':') + 1);

        std::istringstream iss(nums);

        std::vector<Node> nodes;

        std::string num;

        while (std::getline(iss, num, ',')) {
            int n = std::stoi(num);

            bool placed = false;

            for (auto& node: nodes) {
                if (n < node.mid && !node.less) {
                    node.less = n;
                    placed = true;
                    break;
                }
                if (n > node.mid && !node.more) {
                    node.more = n;
                    placed = true;
                    break;
                }
            }

            if (!placed) nodes.emplace_back(n);
        }   

        long long val = std::stoll(nodes 
        | std::views::transform([](const Node& node) { return std::to_string(node.mid); })
        | std::views::join
        | std::ranges::to<std::string>());

        max = std::max(max, val);
        min = std::min(min, val);
    }

    std::cout << max - min;
}