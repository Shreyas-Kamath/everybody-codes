#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <memory>
#include <unordered_map>

struct Node {
    int id{};
    int rank;
    char letter;

    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
};

void insert(std::unique_ptr<Node>& root, std::unique_ptr<Node> new_node) {
    if (root == nullptr) {
        root = std::move(new_node);
        return;
    }

    if (new_node->rank < root->rank) insert(root->left, std::move(new_node));
    else insert(root->right, std::move(new_node));
}

const auto get_message(Node* root) {
    std::queue<Node*> queue;

    std::string message{};
    std::string current_level{};

    int max_nodes{};

    if (root) queue.push(root);

    while (!queue.empty()) {

        int size = queue.size();
        current_level.clear();

        for (int i{}; i < size; ++i) {
            
            auto current = queue.front(); queue.pop();
            current_level += current->letter;

            if (current->left) queue.push(current->left.get());
            if (current->right) queue.push(current->right.get());
        }

        if (size > max_nodes) { max_nodes = size; message = current_level; }
    }

    return message;
}

void swap_nodes(auto& node_map, int id) {
    if (!node_map.contains(id)) return;

    auto& [left_node, right_node] = node_map[id];
    std::swap(left_node->letter, right_node->letter);
    std::swap(left_node->rank, right_node->rank);

}

int main() {
    static const std::regex pattern(R"(ADD id=(\d+) left=\[(\d+),(.{1})\] right=\[(\d+),(.{1})\])");

    std::string line; std::ifstream file("2.txt");

    std::unordered_map<int, std::pair<Node*, Node*>> node_map;

    std::unique_ptr<Node> root_left = nullptr;
    std::unique_ptr<Node> root_right = nullptr;

    while (std::getline(file, line)) {
        std::smatch match;

        if (std::regex_match(line, match, pattern)) {

            int id = std::stoi(match[1]);
            int left_rank = std::stoi(match[2]);
            char left_letter = match[3].str()[0];

            int right_rank = std::stoi(match[4]);
            char right_letter = match[5].str()[0];

            // left tree first
            auto new_left = std::make_unique<Node>();
            new_left->id = id;
            new_left->rank = left_rank;
            new_left->letter = left_letter;

            // now right tree
            auto new_right = std::make_unique<Node>();
            new_right->id = id;
            new_right->rank = right_rank;
            new_right->letter = right_letter;

            node_map[id] = { new_left.get(), new_right.get() };

            insert(root_left, std::move(new_left));
            insert(root_right, std::move(new_right));
        }

        else {
            std::istringstream iss(line); std::string command;
            iss >> command >> command;

            swap_nodes(node_map, std::stoi(command));
        }

    }

    std::cout << get_message(root_left.get()) + get_message(root_right.get());
}
