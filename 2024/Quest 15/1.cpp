#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <queue>

using Point = std::pair<int, int>;

struct State {
    int x{}, y{}, cost{};
};

struct PointHash {
    size_t operator()(const Point& s) const {
        return ((uint64_t)(s.first) << 32) | (uint64_t)(s.second);
    }
};

int main() {
    std::string line; std::ifstream in("1.txt");

    std::unordered_set<Point, PointHash> visited;
    std::queue<State> q;

    std::vector<std::string> grid;

    while (std::getline(in, line)) grid.emplace_back(std::move(line));

    State first = {0, 21, 0};
    q.push(first);
    visited.insert({first.x, first.y});

    const int DX[4] = {-1, 0, 1, 0};
    const int DY[4] = {0, 1, 0, -1};

    while (!q.empty())
    {
        auto [x, y, cost] = q.front(); q.pop();

        if (grid[x][y] == 'H') { printf("%d", cost * 2); return 0; }

        for (int d{}; d < 4; ++d) {
            int nx = x + DX[d];
            int ny = y + DY[d];

            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) continue;
            if (grid[nx][ny] == '#' || visited.contains({ nx, ny })) continue;

            q.emplace(nx, ny, cost + 1);
            visited.emplace(nx, ny);
        }
    }
}