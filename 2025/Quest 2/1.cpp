#include <cstdio>

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

int main() {
    Complex result = {0, 0};

    for (int i{}; i < 3; ++i) {
        result = result * result;
        result = result / Complex(10, 10);
        result = result + Complex(150, 56);
    }

    printf("[%lld,%lld]", result.real, result.img);
}