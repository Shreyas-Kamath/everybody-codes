#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("data.txt");

    // Read step sizes from first line
    string line;
    getline(in, line);
    stringstream ss(line);
    vector<int> steps;
    string token;
    while (getline(ss, token, ',')) {
        steps.push_back(stoi(token));
    }

    vector<vector<string>> wheels(steps.size());

    while (getline(in, line)) {
        size_t pos = 0;
        for (size_t w = 0; w < steps.size(); ++w) {
            if (pos + 3 <= line.size()) {
                string section = line.substr(pos, 3);
                if (section != "   ") {
                    wheels[w].push_back(section);
                }
            }
            pos += 4;
        }
    }

    constexpr int pulls = 100;

    for (size_t w = 0; w < wheels.size(); ++w) {
        size_t idx = (pulls * steps[w]) % wheels[w].size();
        cout << wheels[w][idx] << (w + 1 < wheels.size() ? " " : "\n");
    }
}
