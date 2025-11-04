#include <fstream>
#include <string>
#include <array>

int main() {
    std::string input; std::ifstream in("1.txt");
    std::getline(in, input);

    constexpr std::array<char, 3> chars{'R', 'G', 'B'};
    int score{};

    int i{};

    while (i < input.length()) {
        auto fluffbolt = chars[score % 3];
        score += 1;

        while (i < input.length() && input[i] == fluffbolt) ++i;
        if (i < input.length()) ++i;
    }

    printf("%d", score);
    return 0;
}