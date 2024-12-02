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

bool is_monotonic(std::vector<long> &vec) {
    bool asc = true, desc = true;

    for(int i = 1; i < vec.size(); ++i) {
        long res = vec[i] - vec[i-1];
        asc = asc && res > 0;
        desc = desc && res < 0;
    }

    return asc || desc;
}

bool is_valid_report(std::vector<long> &report) {
    bool is_mono = is_monotonic(report);
    if (!is_mono) {
        return false;
    }

    for (int i = 1; i < report.size(); ++i) {
        long diff = report[i] - report[i-1];
        long abs_diff = std::abs(diff);

        if (abs_diff < 1 || abs_diff > 3) {
            return false;
        }
    }

    return true;
}

long calculate_valid_reports(std::vector<std::vector<long>> &reports) {
    assert(reports.size() > 2);
    long count = 0;

    for (std::vector<long> report : reports) {
        if (is_valid_report(report)) {
            count++;
        } else {
            for (int i =0; i < reports.size(); i++) {
                std::vector<long> copy = report;
                copy.erase(copy.begin()+i);
                if (is_valid_report(copy)) {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}

int main() {
    std::cout << "Advent of code 2024" << std::endl;

    std::ifstream Input("../resources/input_day1_1.txt");
    
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

    std::ifstream Reposts("../resources/input_day2_1.txt");
    std::vector<std::vector<long>> reports;

    read_input_from_file(Reposts, [&](std::string line) {
        size_t pos = 0;
        const std::string delim(" ");
        std::vector<long> levels;
        while((pos = line.find(delim)) != std::string::npos) {
            levels.emplace_back(std::stol(line.substr(0, pos)));
            line.erase(line.begin(), line.begin() + pos + delim.size());
        }
        levels.emplace_back(std::stol(line));
        reports.emplace_back(levels);
    });
    
//    std::vector<std::vector<long>> reports{
//        std::vector<long>{7, 6, 4, 2, 1},
//        std::vector<long>{1, 2, 7, 8, 9},
//        std::vector<long>{9, 7, 6, 2, 1},
//        std::vector<long>{1, 3, 2, 4, 5},
//        std::vector<long>{8, 6, 4, 4, 1},
//        std::vector<long>{1, 3, 6, 7, 9},
//    };
    long valid_reports = calculate_valid_reports(reports);

    std::cout << "Found distance: " << distance << std::endl;
    std::cout << "Similarity score: " << score << std::endl;
    std::cout << "Valid report: " << valid_reports << std::endl;

    Input.close();
    return 0;
}
