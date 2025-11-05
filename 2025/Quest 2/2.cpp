#include <cstdio>
#include <iostream>
#include <chrono>

struct Complex {
    long long real{}, img{};

    constexpr Complex operator+(const Complex& other) const {
        return {this->real + other.real, this->img + other.img};
    }

    constexpr Complex operator*(const Complex& other) const {
        return {this->real * other.real - this->img * other.img, this->real * other.img + this->img * other.real};
    }

    constexpr Complex operator/(const Complex& other) const {
        return {this->real / other.real, this->img / other.img};
    }
};

constexpr bool check(const Complex point) {
    Complex result = {0, 0};

    for (int i{}; i < 100; ++i) {
        result = result * result;
        result = result / Complex(100000, 100000);
        result = result + point;

        if (result.real > 1000000 || result.img > 1000000 || result.real < -1000000 || result.img < -1000000) return false;
    }

    return true;
}

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    constexpr Complex start = {-4511, -68892};
    constexpr Complex end = start + Complex(1000, 1000);

    int count{};

    for (long long i{start.real}; i <= end.real; i += 10) {
        for (long long j{start.img}; j <= end.img; j += 10) {
            Complex c = {i, j};
            if (check(c)) ++count;
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1) << '\n';

    printf("%d", count);
}