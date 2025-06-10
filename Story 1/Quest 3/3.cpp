#include <iostream>
#include <vector>
#include <numeric> // For std::gcd in C++17, though we'll implement our own extended version
#include <fstream>

// 1. Extended Euclidean Algorithm
// Finds g = gcd(a, b), and coefficients x, y such that ax + by = g
long long gcdExtended(long long a, long long b, long long &x, long long &y) {
    // Base Case
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    long long x1, y1; // To store results of recursive call
    long long g = gcdExtended(b % a, a, x1, y1);

    // Update x and y using results of recursive call
    x = y1 - (b / a) * x1;
    y = x1;

    return g;
}

// 2. Modular Inverse
// Finds modular inverse of 'a' under modulo 'm'
// Returns x such that (a * x) % m = 1
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = gcdExtended(a, m, x, y);

    // If gcd is not 1, inverse doesn't exist
    if (g != 1) {
        // This problem's moduli are prime, so inverse will always exist.
        // But for a general CRT implementation, this check is important.
        return -1; // Or throw an exception
    }

    // Ensure x is positive
    return (x % m + m) % m;
}

long long solveCRT(const std::vector<std::pair<long long, long long>>& congruences) {
    long long result = 0;
    long long product = 1; 

    for (const auto& cong : congruences) product *= cong.second;

    for (const auto& cong : congruences) {
        long long a_i = cong.first;  
        long long m_i = cong.second; 

        long long P_i = product / m_i;

        long long inverse_P_i = modInverse(P_i, m_i);

        long long term = (a_i * P_i) % product;
        term = (term * inverse_P_i) % product;
        
        result = (result + term) % product;
    }

    return (result % product + product) % product;
}

int main() {

    std::vector<std::pair<long long, long long>> snail_congruences;

    std::string line; std::ifstream in("3.txt");
    
    const char* format = "x=%lld y=%lld";

    while (std::getline(in, line)) {
        long long x, y;
        if (std::sscanf(line.c_str(), format, &x, &y) == 2) {
            long long disc_id = x + y - 1; 
            snail_congruences.emplace_back(y - 1, disc_id);
        }
    }

    std::cout << solveCRT(snail_congruences);

    return 0;
}