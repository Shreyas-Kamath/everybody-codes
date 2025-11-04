#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main() {
    std::string line; 
    std::ifstream in("3.txt");

    std::array<int, 4> nums{0, 1, 3, 5};

    int ans{};

    while (std::getline(in, line)) {

        for (int i{}; i < line.length(); i += 3) {
            char first = line[i];
            char second = line[i + 1];
            char third = line[i + 2];

            if (first == 'x' && second == 'x' && third == 'x') continue;
            if (first == 'x' && second == 'x') {
                ans += nums[third - 'A'];
                continue;
            }
            if (first == 'x' && third == 'x') {
                ans += nums[second - 'A'];
                continue;
            }
            if (second == 'x' && third == 'x') {
                ans += nums[first - 'A'];
                continue;
            }
            if (first == 'x') {
                ans += nums[second - 'A'] + nums[third - 'A'] + 2;
            } else if (second == 'x') {
                ans += nums[first - 'A'] + nums[third - 'A'] + 2;
            } else if (third == 'x') {
                ans += nums[first - 'A'] + nums[second - 'A'] + 2;
            } else {
                ans += nums[first - 'A'] + nums[second - 'A'] + nums[third - 'A'] + 6;
            }
        }
    }

    std::cout << ans;
}