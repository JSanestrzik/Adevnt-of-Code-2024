#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <numeric>

template <typename Func>
void read_input_from_file(std::ifstream &f_stream, Func func) {
    std::string line;

    while (std::getline(f_stream, line)) {
        func(line);
    }
}

long calculate_program_mul_sum(std::vector<std::string> &lines) {
    const std::regex exp(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    long mul_sum = 0;
    bool enable_multiplication = true;

    for(auto const &line : lines) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), exp);
        auto end = std::sregex_iterator();

        mul_sum += std::transform_reduce(begin, end, 0L, std::plus<>(), [&](const std::smatch &match) {
            if (match.str(0) == "don't()") {
                enable_multiplication = false;
            } else if (match.str(0) == "do()") {
                enable_multiplication = true;
            } else if (enable_multiplication && match[1].matched && match[2].matched) {
                return std::stol(match.str(1)) * std::stol(match.str(2));
            }
            return 0L;
        });
    }
    return mul_sum;
}

int main() {
    std::cout << "Advent of code 2024 Day 3" << std::endl;

    std::ifstream input("../../resources/input_day3_1.txt");

    std::vector<std::string> program;
    read_input_from_file(input, [&](std::string line) {
        program.emplace_back(line);
    });

    long mul_sum = calculate_program_mul_sum(program);
    std::cout << "Program mul sum: " << mul_sum << std::endl;

    input.close();
    return 0;
}
