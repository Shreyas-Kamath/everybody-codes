#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <ranges>
#include <iostream>
#include <algorithm>

struct Node {
    int mid{};
    std::optional<int> less = std::nullopt, more = std::nullopt;

    Node(int num): mid(num) {};
};

struct NodeInfo {
    long long quality;
    std::vector<long long> level_numbers;
    int id{};
};

long long extract_number(const Node& node) {
    std::string num;

    if (node.less.has_value()) num.append(std::to_string(node.less.value()));
    num.append(std::to_string(node.mid));
    if (node.more.has_value()) num.append(std::to_string(node.more.value()));

    return std::stoll(num);
}

int main() {
    std::string line; std::ifstream in("3.txt");

    std::vector<NodeInfo> info; int i{1};

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
        
        NodeInfo ni;

        ni.id = i++;

        ni.quality = std::stoll(nodes
        | std::views::transform([](const Node& node) { return std::to_string(node.mid); })
        | std::views::join
        | std::ranges::to<std::string>());

        std::vector<long long> numbers;

        for (const Node& node: nodes) numbers.push_back(extract_number(node));

        ni.level_numbers = std::move(numbers);

        info.push_back(ni);
    }

    auto cmp = [](const NodeInfo& lhs, const NodeInfo& rhs) -> bool {
        if (lhs.quality != rhs.quality) return lhs.quality > rhs.quality;

        auto zip_view = std::views::zip(lhs.level_numbers, rhs.level_numbers);

        auto find_first_mismatch = std::ranges::find_if(zip_view, [](const auto& pair) {
            return std::get<0>(pair) != std::get<1>(pair);
        });

        if (find_first_mismatch != zip_view.end()) {
            auto [a, b] = *find_first_mismatch;
            return a > b;
        }

        return lhs.id > rhs.id;
    };

    std::ranges::sort(info, cmp);

    int sum{};

    for (const auto& [nodeinfo, pos]: std::views::zip(info, std::views::iota(1))) {
        sum += pos * nodeinfo.id;
    }

    std::cout << sum;
}