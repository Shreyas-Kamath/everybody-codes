#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream in("1.txt"); std::string input;
    in >> input;

    int count{}, knights{};

    for (char c: input) {
        if (c == 'A') ++knights;
        else if (c == 'a') count += knights;
    }

    std::cout << count;
}   