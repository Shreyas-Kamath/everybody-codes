#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>

struct Node {
    std::string val{};
    std::vector<Node*> children{};
};

void dfs(Node* root, std::string& path, int depth, std::unordered_map<int, std::vector<std::string>>& lengths) {
    path.push_back(root->val[0]);

    if (root->val == "@") {
        lengths[depth].emplace_back(path);
    } else {
        for (auto& child : root->children) dfs(child, path, depth + 1, lengths);
    }
    path.pop_back();
}


int main() {
    std::string line; std::ifstream in("3.txt");

    std::unordered_map<int, std::vector<std::string>> lengths;
    std::unordered_map<std::string, std::unique_ptr<Node>> nodes; nodes.reserve(4000);

    while (std::getline(in, line)) {
        auto pos = line.find(':');

        std::string parent = line.substr(0, pos);
        std::string childrenStr = line.substr(pos + 1);

        if (!nodes.contains(parent)) {
            nodes[parent] = std::make_unique<Node>();
            nodes[parent]->val = parent;
        }

        std::istringstream iss(childrenStr);
        std::string child;

        Node* parent_node = nodes[parent].get();

        while (std::getline(iss, child, ',')) {
            if (child == "BUG" || child == "ANT") continue;

            if (!nodes.contains(child)) {
                nodes[child] = std::make_unique<Node>();
                nodes[child]->val = child;
            }

            parent_node->children.emplace_back(nodes[child].get());
        }
    }

    std::string path{};
    dfs(nodes["RR"].get(), path, 0, lengths);

    for (const auto& [depth, paths]: lengths) {
        if (paths.size() == 1) { std::cout << paths[0]; break; }
    }

    return 0;
}