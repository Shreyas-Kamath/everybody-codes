#include <unordered_set>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <iostream>

using Point = std::pair<int, int>;

struct State {
    int x{}, y{}, level{}, cost{};
    bool operator==(const State& other) const {
        return x == other.x && y == other.y && level == other.level;
    }
};

struct StateHash {
    size_t operator()(const State& s) const {
        return ((uint64_t)(s.level) << 32) | ((uint64_t)(s.y) << 16) | (uint64_t)(s.x);
    }
};

struct Comp {
    bool operator()(const State& lhs, const State& rhs) {
        return lhs.cost > rhs.cost;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        return ((uint64_t)(p.first) << 32) | (uint64_t)(p.second);
    }
};

int main() {
    std::ifstream in("data.txt");
    std::vector<std::string> grid;
    std::string line;

    int start_x{}, start_y{}, end_x{}, end_y{};

    std::unordered_set<Point, PointHash> starting_points;

    int row = 0;
    while (std::getline(in, line)) {
        for (int col = 0; col < (int)line.size(); ++col) {
            if (line[col] == 'S') { 
                start_x = row; start_y = col;
                line[col] = '0';
                starting_points.emplace(start_x, start_y);
            }
            if (line[col] == 'E') { end_x = row; end_y = col; }
        }
        grid.push_back(line);
        ++row;
    }

    grid[end_x][end_y] = '0';

    const int DX[4] = {-1, 0, 1, 0};
    const int DY[4] = {0, 1, 0, -1};

    std::priority_queue<State, std::vector<State>, Comp> pq;
    std::unordered_set<State, StateHash> visited;

    pq.push({end_x, end_y, 0, 0});

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();

        if (visited.contains(cur)) continue;
        visited.insert(cur);

        if (starting_points.contains({ cur.x, cur.y }) && cur.level == 0) {
            std::cout << cur.cost;
            return 0;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = cur.x + DX[d];
            int ny = cur.y + DY[d];

            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) continue;
            if (grid[nx][ny] == '#') continue;

            int target_level = grid[nx][ny] - '0';

            int move_cost = std::min(std::abs(cur.level - target_level),
                                     10 - std::abs(cur.level - target_level));

            pq.push({nx, ny, target_level, cur.cost + move_cost + 1});
        }
    }
}
