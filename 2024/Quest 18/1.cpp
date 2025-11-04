#include <fstream>
#include <string>
#include <queue>
#include <unordered_set>
#include <vector>

struct State {
    int x{}, y{}, time{};
};

struct Hash {
    size_t operator()(const std::pair<int, int>& p) const noexcept {
        return (p.first << 28) | (p.second << 16);
    }
};

int main() {
    std::vector<std::string> grid;

    std::string line; std::ifstream in("1.txt"); int count{};

    while (std::getline(in, line)) {
        count += std::count(line.begin(), line.end(), 'P');

        grid.push_back(std::move(line));
    }

    std::unordered_set<std::pair<int, int>, Hash> visited;
    std::queue<State> q;

    visited.insert({ 1, 0 });
    q.emplace(1, 0, 0);

    int trees_seen{};

    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};

    while (!q.empty()) {
        auto [x, y, time] = q.front(); q.pop();

        if (trees_seen == count) { printf("%d", time); exit(0); }

        for (int d{}; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) continue;
            if (grid[nx][ny] == '#') continue;
            if (visited.contains({ nx, ny })) continue;
            
            if (grid[nx][ny] == 'P') ++trees_seen;

            q.emplace(nx, ny, time + 1);
            visited.emplace(nx, ny);
        }
    }

}