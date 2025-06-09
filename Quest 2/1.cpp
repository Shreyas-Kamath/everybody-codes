#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {

    std::unordered_set<std::string> words;
    std::string line; std::ifstream in("words.txt");

    std::getline(in, line); in.close();
    std::string word; std::stringstream ss(line);

    while (std::getline(ss, word, ',')) words.insert(word);

    std::ifstream in2("sentence.txt");
    std::getline(in2, line);

    std::stringstream ss2(line);
    int count{};
    while (ss2 >> word) {
        for (auto it = words.begin(); it != words.end(); ++it) {
            if (word.contains(*it)) ++count;
        }
    }
    std::cout << count;
}