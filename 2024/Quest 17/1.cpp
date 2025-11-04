#include <fstream>
#include <vector>
#include <string>
#include <queue>

namespace std
{
    template<>
    struct hash<std::pair<int, int>> {
        size_t operator ()(const std::pair<int, int>& p) const noexcept {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second << 1));
        }
    };
} 

int manhattan(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    return abs(lhs.first - rhs.first) + abs(lhs.second - rhs.second);
}

struct Comp {
    bool operator() (const auto& lhs, const auto& rhs) {
        return rhs.first < lhs.first;
    }
};

int main() {
    std::string line; std::ifstream in("1.txt"); 
    std::vector<std::string> grid; grid.reserve(20); int row{};

    std::vector<std::pair<int, int>> stars; stars.reserve(20);

    while (std::getline(in, line))
    {
        for (int col{}; col < line.length(); ++col) {
            if (line[col] == '*') stars.emplace_back(row, col);
        }
        ++row;
    }   

    std::vector<bool> visited(stars.size(), false);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Comp> pq;

    for (int i{1}; i < stars.size(); ++i) {
        pq.emplace(manhattan(stars.front(), stars[i]), i);
    }

    int total_cost{}, visited_count{1};
    visited[0] = true;

    while (visited_count < stars.size())
    {
        auto [cost, index] = pq.top(); pq.pop();

        if (visited[index]) continue;

        visited[index] = true;
        total_cost += cost;
        ++visited_count;

        for (int i{}; i < stars.size(); ++i) {
            if (!visited[i]) pq.emplace(manhattan(stars[i], stars[index]), i);
        }
    }
    
    printf("%d", total_cost + visited_count);
}