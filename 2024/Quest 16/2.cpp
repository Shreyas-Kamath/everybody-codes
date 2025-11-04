#include <sstream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ranges>

long long coins_per_pull(
    const std::vector<std::vector<std::string>>& wheels, const std::vector<int>& steps, long long pull) {

    std::unordered_map<char, int> freq;

    for (size_t i = 0; i < wheels.size(); ++i) {
        const auto& wheel = wheels[i];
        size_t idx = (pull * steps[i]) % wheel.size();
        const auto& sym = wheel[idx];

        freq[sym[0]]++;
        freq[sym[2]]++;
    }

    long long coins = 0;
    for (auto& [eyes, count] : freq) {
        if (count >= 3) {
            coins += (count - 2);
        }
    }
    return coins;
}


int main() {
    std::ifstream in("data.txt");

    std::string line;
    std::getline(in, line);
    std::stringstream ss(line);
    std::vector<int> steps;
    std::string token;
    while (std::getline(ss, token, ',')) {
        steps.push_back(stoi(token));
    }

    std::vector<std::vector<std::string>> wheels(steps.size());

    while (getline(in, line)) {
        size_t pos = 0;
        for (size_t w = 0; w < steps.size(); ++w) {
            if (pos + 3 <= line.size()) {
                std::string section = line.substr(pos, 3);
                if (section != "   ") {
                    wheels[w].push_back(section);
                }
            }
            pos += 4;
        }
    }

    constexpr long long pulls = 202420242024;

    int cycle_length = std::ranges::fold_left(wheels | std::views::transform([](const auto& vec) {
        return (long long)vec.size();
    }), 1LL, std::lcm<long long, long long>);

    long long cycles = pulls / cycle_length;

    long long total_coins = 0;

    for (long long p{}; p < cycle_length; ++p) {
        total_coins += coins_per_pull(wheels, steps, p);
    }
    
    long long remainder = pulls % cycle_length;

    // for each cycle, add the coins quotient times...
    total_coins *= cycles;

    // plus remainder times
    for (long long p{}; p < remainder; ++p) {
        total_coins += coins_per_pull(wheels, steps, p);
    }

    std::cout << total_coins;
}
