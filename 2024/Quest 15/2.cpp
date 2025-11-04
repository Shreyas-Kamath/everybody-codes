#include <fstream>
#include <ranges>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using Pair = std::pair<int, int>;

struct PairHash {
    size_t operator()(const Pair& p) const {
        return ((uint64_t)(p.first) << 32) | (uint64_t)(p.second);
    }
};

int bfs(const Pair& start, const Pair& end, const std::vector<std::string>& grid) {
    static const int DX[4] = {-1, 0, 1, 0};
    static const int DY[4] = {0, 1, 0, -1};

    const auto& [start_x, start_y] = start;
    const auto& [end_x, end_y] = end;
    
    std::queue<std::tuple<int, int, int>> q;
    std::unordered_set<Pair, PairHash> visited;

    q.emplace(start_x, start_y, 0);
    visited.emplace(start_x, start_y);

    while (!q.empty()) {
        const auto [x, y, steps] = q.front(); q.pop();

        if (x == end_x && y == end_y) return steps;

        for (int d{}; d < 4; ++d) {
            int nx = x + DX[d];
            int ny = y + DY[d];
            
            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid.size()) continue;
            if (grid[nx][ny] == '#' || grid[nx][ny] == '~') continue;
            if (visited.contains({ nx, ny })) continue;

            q.emplace(nx, ny, steps + 1);
            visited.emplace(nx, ny);
        }
    }
    return 0;
}

int main() {
    std::string line; std::ifstream in("2.txt");
    int rows{};
   
    std::vector<std::string> grid;
    std::unordered_map<char, std::vector<Pair>> herb_locations;

    while (std::getline(in, line))
    {
        for (int cols{}; cols < line.length(); ++cols) {
            if (isalpha(line[cols])) herb_locations[line[cols]].emplace_back(rows, cols);
        }
        ++rows;
        grid.push_back(line);
    }
    herb_locations['S'].push_back({ 0, 42 });

    std::unordered_map<char, std::unordered_map<char, std::vector<int>>> precomputations;
    
    for (const auto& [start, start_vec]: herb_locations) {
        for (const auto& [end, end_vec]: herb_locations) {
            if (start == end || precomputations[start].contains(end) || precomputations[end].contains(start)) continue;

            for (const auto& start_coord: start_vec) {
                for (const auto& end_coord: end_vec) {
                    int length = bfs(start_coord, end_coord, grid);

                    precomputations[start][end].push_back(length);
                    precomputations[end][start].push_back(length);
                }
            }
        }
    }

}