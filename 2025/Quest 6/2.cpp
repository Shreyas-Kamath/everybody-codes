#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream in("2.txt"); std::string input;
    in >> input;

    int a{}, b{}, c{}, A{}, B{}, C{};

    for (char ch: input) {
        switch (ch) {
            case 'a': a += A; break;
            case 'A': ++A; break;
            case 'b': b += B; break;
            case 'B': ++B; break;
            case 'c': c += C; break;
            case 'C': ++C; break;
        }
    }

    std::cout << a + b + c;
}   