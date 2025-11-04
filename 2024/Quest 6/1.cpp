#include <fstream>
#include <unordered_map>
#include <string>
#include <ranges>
#include <vector>

void dfs(const std::unordered_map<std::string, std::vector<std::string>>& map, std::unordered_map<int, std::vector<std::string>>& depth_map, int depth, const std::string& root, std::string& path) {
    if (root == "@") {
        depth_map[depth].push_back(path);
        return;
    }

    if (auto it = map.find(root); it != map.end()) {
        for (const auto& child: it->second) {
            path.append(child);
            dfs(map, depth_map, depth + 1, child, path);
            path.resize(path.size() - child.size());
        }
    }
}

int main() {
    std::fstream in("1.txt"); std::string line;

    std::unordered_map<std::string, std::vector<std::string>> map;
    std::unordered_map<int, std::vector<std::string>> depth_map;

    std::string root = "RR";
    std::string path = root;

    while (std::getline(in, line))
    {
        auto sep = line.find(':');

        std::string parent = line.substr(0, sep);
        
        auto children = line.substr(sep + 1)
        | std::views::split(',')
        | std::ranges::to<std::vector<std::string>>();

        map[parent] = std::move(children);
    }
    
    dfs(map, depth_map, 0, root, path);

    for (const auto& vec: depth_map | std::views::values) {
        if (vec.size() == 1) {
            printf("%s", vec.front().c_str());
        }
    }
}