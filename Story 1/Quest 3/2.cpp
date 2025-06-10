#include <vector>
#include <iostream>
#include <string>
#include <fstream>

std::pair<int, int> get_pos_after_days(int x, int y, long long num_days) { 
    int disc_id = x + y - 1; 
    int new_x = (x + num_days - 1) % disc_id + 1;
    int new_y = disc_id + 1 - new_x;
    return { new_x, new_y };
}

int main() {
    std::string line;
    std::ifstream in("2.txt");

    std::vector<std::pair<int, int>> initial_positions; 

    const char* format = "x=%d y=%d";

    while (std::getline(in, line)) {
        int x{}, y{};

        if (std::sscanf(line.c_str(), format, &x, &y) == 2) {
            initial_positions.emplace_back(x, y);
        }
    }

    long long day{};

    while (1) {
        std::vector<std::pair<int, int>> current_positions_on_this_day; 

        bool all_aligned = true;
        for (const auto& [old_x, old_y] : initial_positions) { 
            auto [new_x, new_y] = get_pos_after_days(old_x, old_y, day);

            if (new_y != 1) all_aligned = false;
        
            current_positions_on_this_day.emplace_back(new_x, new_y);
        }

        if (all_aligned) { std::cout << day; break; }
        ++day;
    }

    return 0;
}