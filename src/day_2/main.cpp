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

    std::ifstream Reposts("../../resources/input_day2_1.txt");
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
    
    long valid_reports = calculate_valid_reports(reports);

    std::cout << "Valid report: " << valid_reports << std::endl;

    Input.close();
    return 0;
}
