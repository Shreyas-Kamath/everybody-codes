#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main() {
    std::string line; 
    std::ifstream in("2.txt");

    std::array<int, 4> nums{0, 1, 3, 5};

    int ans{};

    while (std::getline(in, line)) {

        for (int i{}; i < line.length(); i += 2) {
            char first = line[i];
            char second = line[i + 1];

            if (first == 'x' && second == 'x') continue;
            if (first == 'x') {
                ans += nums[second - 'A'];
            } else if (second == 'x') {
                ans += nums[first - 'A'];
            } else {
                ans += nums[first - 'A'] + nums[second - 'A'] + 2;
            }
        }
    }

    std::cout << ans;
}