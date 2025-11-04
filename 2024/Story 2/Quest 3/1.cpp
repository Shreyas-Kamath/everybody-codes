#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

struct Die {
    std::vector<int> faces;
    long long pulse, seed;
    size_t index{};

    Die() = default;
    Die(std::vector<int>& f, long long p, long long s, long long i): faces(std::move(f)), pulse(p), seed(s), index(i) {};
};

int main() {
    std::ifstream in("1.txt"); std::string line;

    std::unordered_map<int, Die> dice; // id - pulse

    while (std::getline(in, line)) {
        int id = line.front() - '0';

        auto start = line.find('[');
        auto end = line.find(']');

        auto str = line.substr(start + 1, end - start - 1);

        std::vector<int> faces;

        std::istringstream iss(str); std::string num;

        while (std::getline(iss, num, ',')) faces.emplace_back(std::stoi(num));

        auto pos = line.find_last_of('=');

        long long seed = std::stoll(line.substr(pos + 1));

        dice[id] = {faces, seed, seed, 0};
    }

    long long total{}, roll{1};
    
    for (roll; total < 10000; ++roll) {
        for (auto& [id, d] : dice) {
            long long spin = roll * d.pulse;
            d.index = (d.index + spin) % d.faces.size();
            long long value = d.faces[d.index];
            total += value;

            d.pulse = (d.pulse + spin) % d.seed;
            d.pulse += 1 + roll + d.seed;
        }
    }
    printf("%d", roll - 1);
}