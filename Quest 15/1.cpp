#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

int get_path(const std::vector<std::string>& grid, const std::pair<int, int>& curr_herb, const std::pair<int, int>& start) {
    const auto& [x, y] = curr_herb;
    const auto& [start_x, start_y] = start;

    static const int dx[4] = { -1, 1, 0, 0 };
    static const int dy[4] = { 0, 0, -1, 1 };

    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

    visited[x][y] = true;

    std::queue<std::tuple<int, int, int>> q;

    q.emplace(x, y, 0);

    while (!q.empty()) {

        auto [cx, cy, cost] = q.front(); q.pop();

        for (int d{}; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) continue;
            if (grid[nx][ny] == '#' || grid[nx][ny] == 'H' || visited[nx][ny]) continue;

            if (nx == start_x && ny == start_y) return cost + 1;

            q.emplace(nx, ny, cost + 1);
            visited[nx][ny] = true;
        }
    }

    return INT_MAX;
}

int main() {
    std::ifstream in("1.txt"); std::string line;

    std::vector<std::string> grid; grid.reserve(30);
    std::vector<std::pair<int, int>> herbs;

    int row{};

    while (std::getline(in, line))
    {
        for (int col{}; col < line.length(); ++col) {
            if (line[col] == 'H') herbs.emplace_back(row, col);
        }
        grid.push_back(line);
        ++row;
    }

    std::pair<int, int> start { 0, 21 };

    int min_path{ INT_MAX };

    for (const auto& herb: herbs) {
        min_path = std::min(min_path, get_path(grid, herb, start));
    }

    printf("%d", min_path * 2);
}