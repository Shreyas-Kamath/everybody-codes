#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

auto mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    long long cur = base % mod;

    while (exp > 0) {
        if (exp & 1) result = (result * cur) % mod;
        cur = (cur * cur) % mod;
        exp >>= 1;
    }
    return result;
}


auto eni(long long N, long long EXP, long long MOD) {
    std::vector<std::string> remainders;

    for (int i{}; i < 5; ++i) {

        long long val = mod_pow(N, EXP - i, MOD);
        remainders.push_back(std::to_string(val));
    }

    return remainders
    | std::views::join
    | std::ranges::to<std::string>();
}

int main() {
    const std::regex pattern(R"(A=(\d+) B=(\d+) C=(\d+) X=(\d+) Y=(\d+) Z=(\d+) M=(\d+))");
    std::ifstream file("2.txt"); std::string line;

    long long max{LLONG_MIN};

    while (std::getline(file, line)) {
        std::smatch match;

        std::regex_match(line, match, pattern);
        
        auto first = eni(stoll(match[1]), stoll(match[4]), stoll(match[7]));
        auto second = eni(stoll(match[2]), stoll(match[5]), stoll(match[7]));
        auto third = eni(stoll(match[3]), stoll(match[6]), stoll(match[7]));

        
        long long val = stoll(first) + stoll(second) + stoll(third);

        max = std::max(max, val);
    }   

    std::cout << max;
}
