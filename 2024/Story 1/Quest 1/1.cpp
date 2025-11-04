#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>

std::string eni(int N, int EXP, int MOD) {
    std::deque<int> remainders;

    long long init_score = 1;

    for (int i{}; i < EXP; ++i) {

        init_score *= N;
        int remainder = init_score % MOD;
        remainders.push_front(remainder);
    }

    return remainders
        | std::views::transform([](int x) { return std::to_string(x); })
        | std::views::join
        | std::ranges::to<std::string>();
}

int main() {
    const std::regex pattern(R"(A=(\d+) B=(\d+) C=(\d+) X=(\d+) Y=(\d+) Z=(\d+) M=(\d+))");
    std::ifstream file("data.txt"); std::string line;

    long long max{LLONG_MIN};

    while (std::getline(file, line)) {
        std::smatch match;

        std::regex_match(line, match, pattern);
        
        auto first = eni(stoi(match[1]), stoi(match[4]), stoi(match[7]));
        auto second = eni(stoi(match[2]), stoi(match[5]), stoi(match[7]));
        auto third = eni(stoi(match[3]), stoi(match[6]), stoi(match[7]));

        
        long long val = stoll(first) + stoll(second) + stoll(third);

        max = std::max(max, val);
    }   

    std::cout << max;
}
