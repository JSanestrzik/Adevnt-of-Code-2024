#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <fstream>
#include <string>
#include <iterator>

template <typename Func>
void read_input_from_file(std::ifstream &f_stream, Func func) {
    std::string line;

    while (std::getline(f_stream, line)) {
        func(line);
    }
}

long find_total_distance(std::vector<long> lhs, std::vector<long> rhs) {
    assert(lhs.size() == rhs.size());

    std::vector<long> result(lhs.size());

    std::transform(
        lhs.begin(), 
        lhs.end(), 
        rhs.begin(),
        result.begin(), 
        [](long lv, long rv) { return std::abs(lv - rv); }
    );

    return std::accumulate(result.begin(), result.end(), 0);
}

long calculate_similarity_score(std::vector<long> &lhs, std::vector<long> &rhs) {
    long score = 0;
    
    for (long location_id : lhs) {
        score += location_id * std::count(rhs.begin(), rhs.end(), location_id);
    }

    return score;
}

int main() {
    std::cout << "Advent of code 2024" << std::endl;

    std::ifstream Input("../../resources/input_day1_1.txt");
    
    std::vector<long> left_list;
    std::vector<long> right_list;

    read_input_from_file(Input, [&](std::string line) {
        size_t pos = 0;
        const std::string delim("   ");
        while((pos = line.find(delim)) != std::string::npos) {
            left_list.emplace_back(std::stol(line.substr(0, pos)));
            line.erase(line.begin(), line.begin() + pos + delim.size());
            right_list.emplace_back(std::stol(line));
        }
    });

    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    long distance = find_total_distance(left_list, right_list);
    long score = calculate_similarity_score(left_list, right_list);

    std::cout << "Found distance: " << distance << std::endl;
    std::cout << "Similarity score: " << score << std::endl;

    Input.close();
    return 0;
}
