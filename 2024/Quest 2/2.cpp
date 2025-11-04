#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::ifstream in("words.txt");
    std::string line;
    std::vector<std::string> words;

    std::getline(in, line); in.close();
    std::istringstream iss(line);
    std::string word;
    while (std::getline(iss, word, ',')) words.push_back(word);

    std::ifstream data("data.txt");
    int total = 0;

    while (std::getline(data, line)) {
        std::string rev = line;
        std::reverse(rev.begin(), rev.end());

        for (const std::string& pattern : words) {
            size_t len = pattern.length();

            // Match in forward direction
            for (size_t i = 0; i + len <= line.length(); ++i) {
                if (line.substr(i, len) == pattern) {
                    total += len;
                }
            }

            // Match in reverse direction only if pattern != reverse(pattern)
            // (Prevents double-counting palindromes in symmetric spots)
            if (std::string(pattern.rbegin(), pattern.rend()) != pattern) {
                for (size_t i = 0; i + len <= rev.length(); ++i) {
                    if (rev.substr(i, len) == pattern) {
                        total += len;
                    }
                }
            }
        }
    }

    printf("%d\n", total);
}
