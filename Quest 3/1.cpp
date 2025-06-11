#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string line; std::ifstream in("1.txt");

    std::vector<std::string> grid;

    while (std::getline(in, line)) grid.emplace_back(line);

    int count{};

    for (auto& row: grid) {
        for (auto& ch: row) {
            if (ch == '#') { ch = '1'; ++count; }
        }
    }

    char layer = '2';
    bool changed = true;

    std::array<std::pair<int, int>, 4> directions{{ {0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

    while (changed) {
        changed = false;

        for (int i{}; i < grid.size(); ++i) {
            for (int j{}; j < grid[0].size(); ++j) {
                if (grid[i][j] == layer - 1) {
                    bool can_raise = true;

                    for (const auto& [dx, dy]: directions) {
                        int ni = i + dx, nj = j + dy;

                        if (ni < 0 || ni >= grid.size() || nj < 0 || nj >= grid[0].size() || 
                            grid[ni][nj] == '.' || grid[ni][nj] < layer - 1) {
                            can_raise = false;
                            break;
                        }
                    }

                    if (can_raise) {
                        grid[i][j] = layer;
                        changed = true;
                        ++count;
                    }
                }
            }
        }
        ++layer;
    }
    std::cout << count;

}