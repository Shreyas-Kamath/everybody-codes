#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main() {
    std::string line; 
    std::ifstream in("data.txt");

    std::array<int, 3> nums{0, 1, 3};

    int ans{};

    while (std::getline(in, line)) {

        for (const auto& ch: line) {
            ans += nums[ch - 'A'];
        }
    }

    std::cout << ans;
}