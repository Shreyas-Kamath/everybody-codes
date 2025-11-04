#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <utility>

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const noexcept {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
}

struct Cell {
    int x{}, y{}, dist{};
};

int main() {
    std::ifstream in("3.txt");
    std::string line;
    std::vector<std::string> grid;
    std::unordered_set<std::pair<int, int>> palm_trees;

    int x{};
    while (std::getline(in, line)) {
        for (int y = 0; y < line.size(); ++y) {
            if (line[y] == 'P') {
                palm_trees.emplace(x, y);
            }
        }
        grid.push_back(std::move(line));
        ++x;
    }

    const int rows = grid.size();
    const int cols = grid[0].size();

    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };

    std::unordered_map<std::pair<int, int>, int> well_time;

    for (const auto& [sx, sy] : palm_trees) {
        std::queue<Cell> q;
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        q.emplace(sx, sy, 0);

        visited[sx][sy] = true;

        while (!q.empty()) {
            auto [x, y, d] = q.front(); q.pop();

            if (grid[x][y] == '.') {
                well_time[{x, y}] += d;
            }

            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 0 || ny < 0 || nx >= rows || ny >= cols) continue;
                if (visited[nx][ny]) continue;
                char cell = grid[nx][ny];
                if (cell == '#') continue;

                visited[nx][ny] = true;
                q.emplace(nx, ny, d + 1);
            }
        }
    }

    int min_total_time = std::numeric_limits<int>::max();

    for (const auto& [coord, total] : well_time) {
        min_total_time = std::min(min_total_time, total);
    }

    printf("%d\n", min_total_time);
    return 0;
}
