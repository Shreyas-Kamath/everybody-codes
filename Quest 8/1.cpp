#include <iostream>

constexpr int solve(int blocks) {
    int height = 0;
    int width = 1;

    while (blocks >= width) {
        blocks -= width;
        ++height;
        width += 2;
    }
    return (width - blocks) * width;
}

int main() {
    constexpr int result = solve(4098733);
    std::cout << result;
}
