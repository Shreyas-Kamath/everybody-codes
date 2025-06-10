#include <iostream>
#include <array>

inline constexpr std::pair<int, int> final_pos(int x, int y) {
    int cycle = x + y - 1;
    int new_x = (x + 99) % cycle + 1;
    int new_y = cycle + 1 - new_x;

    return { new_x, new_y };
}

int main() {

    constexpr std::array<std::pair<int, int>, 10> vals {{
        {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
        {6, 6}, {8, 1}, {4, 7}, {5, 4}, {3, 4}
    }};

    int sum{};

    for (const auto& pair: vals) {

        auto [new_x, new_y] = final_pos(pair.first, pair.second);

        sum += new_x + 100 * new_y;
    }

    std::cout << sum;
}