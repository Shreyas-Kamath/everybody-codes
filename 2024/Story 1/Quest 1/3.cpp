#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <numeric>

long long eni(long long N, long long EXP, long long MOD) {

    std::vector<long long> remainders;
    std::unordered_map<long long, int> seen;

    long long init{1};

    for (int i{}; i < EXP; ++i) {

        init = (init * N) % MOD;
        if (seen.contains(init)) {
            int cycle_start = seen[init];
            int cycle_length = remainders.size() - cycle_start;

            long long cycle_sum{};

            for (int j{cycle_start}; j < remainders.size(); ++j) cycle_sum += remainders[j];

            long long pre_cycle_sum{};

            for (int j{}; j < cycle_start; ++j) pre_cycle_sum += remainders[j];

            long long remaining = EXP - cycle_start;

            long long total = pre_cycle_sum;

            total += (remaining / cycle_length) * cycle_sum;

            for (int _{}; _ < remaining % cycle_length; ++_) total += remainders[cycle_start + _];
        
            return total;
        }

        seen[init] = remainders.size();
        remainders.push_back(init);
    }

    return std::accumulate(remainders.begin(), remainders.end(), 0LL);
}

int main() {
    const std::regex pattern(R"(A=(\d+) B=(\d+) C=(\d+) X=(\d+) Y=(\d+) Z=(\d+) M=(\d+))");
    std::ifstream file("3.txt"); std::string line;

    long long max{LLONG_MIN};

    while (std::getline(file, line)) {
        std::smatch match;

        std::regex_match(line, match, pattern);
        
        auto first = eni(stoll(match[1]), stoll(match[4]), stoll(match[7]));
        auto second = eni(stoll(match[2]), stoll(match[5]), stoll(match[7]));
        auto third = eni(stoll(match[3]), stoll(match[6]), stoll(match[7]));
        
        long long val = first + second + third;

        max = std::max(max, val);
    }   

    std::cout << max;
}
