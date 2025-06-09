#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {

    std::vector<std::string> words;
    std::string line; std::ifstream in("words.txt");

    std::getline(in, line); in.close();
    std::string sen; std::stringstream ss(line);

    while (std::getline(ss, sen, ',')) words.push_back(sen);

    std::ifstream in2("sentence.txt");
    std::getline(in2, line); in2.close();

    std::stringstream ss2(line);
    int count{};
    while (ss2 >> sen) {
        for (const auto& word: words) {
            if (sen.contains(word)) ++count;
        }
    }
    std::cout << count;
}