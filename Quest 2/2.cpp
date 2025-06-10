#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {

    std::vector<std::string> words;
    std::string line; std::ifstream in("words2.txt");

    std::getline(in, line); in.close();
    std::string sen; std::stringstream ss(line);

    while (std::getline(ss, sen, ',')) words.push_back(sen);
    long long count{};

    std::ifstream in2("sentence2.txt");
    while (std::getline(in2, line)){
        
        std::stringstream ss2(line);
        while (ss2 >> sen) {
            std::string temp = sen;
            std::reverse(temp.begin(), temp.end());

            for (const auto& word: words) {
                if (sen.contains(word)) count += word.length();
                if (temp.contains(word)) count += word.length();
            }
        }
    }


    std::cout << count;
}