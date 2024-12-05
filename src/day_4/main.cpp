#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>

template <typename Func>
void read_input_from_file(std::ifstream &f_stream, Func func) {
    std::string line;

    while (std::getline(f_stream, line)) {
        func(line);
    }
}

bool check_for_word(const std::vector<std::vector<char>> word_grid, 
        const std::string &word, 
        int x, 
        int y, 
        int dx, 
        int dy) {
    const int width = word_grid.size();
    const int height = word_grid[0].size();
    const int word_len = word.size();

    for (int i = 0; i < word_len; i++) {
        int x_pos = x + i * dx;
        int y_pos = y + i * dy;

        if(x_pos < 0 || x_pos >= width || y_pos < 0 || y_pos >= height || word_grid[x_pos][y_pos] != word[i]) {
            return false;
        }
    }

    return true;
}

long match_count(const std::vector<std::vector<char>> &word_grid, const std::string &word) {
    const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0},{1, 1}, {1, -1}};
    long match_count = 0;
    
    const int width = word_grid.size();
    const int height = word_grid[0].size();

    const std::string reverse_word(word.rbegin(), word.rend()); 
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            for(auto[dx, dy] : directions) { 
                if (check_for_word(word_grid, word, x, y, dx, dy) || check_for_word(word_grid, reverse_word, x, y, dx, dy)) {
                    match_count++;
                }
            }
        }
    }

    return match_count;
}

bool check_for_x_word(const std::vector<std::vector<char>> word_grid, 
        const std::string &word, 
        int x, 
        int y, 
        int dx, 
        int dy) {
    const long middle_index = std::floor(word.size()/2);

    if(word_grid[x][y] != word[middle_index]) {
        return false;
    }

    const int width = word_grid.size();
    const int height = word_grid[0].size();
    const int word_len = word.size();

    for (int i = 0; i < word_len; i++) {
        int x_pos = x - (middle_index * dx) + i * dx;
        int y_pos = y - (middle_index * dy) + i * dy;

        if(x_pos < 0 || x_pos >= width || y_pos < 0 || y_pos >= height || word_grid[x_pos][y_pos] != word[i]) {
            return false;
        }
    }

    return true;
}

long match_x_word_count(const std::vector<std::vector<char>> &word_grid, const std::string &word) {
    assert(word.size()%2 == 1);
    const std::vector<std::pair<int, int>> directions = {{1, 1}, {1, -1}};
    long match_count = 0;
    
    const int width = word_grid.size();
    const int height = word_grid[0].size();

    const std::string reverse_word(word.rbegin(), word.rend()); 
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            long x_match_count = 0;
            for(auto[dx, dy] : directions) { 
                if (check_for_x_word(word_grid, word, x, y, dx, dy) || check_for_x_word(word_grid, reverse_word, x, y, dx, dy)) {
                    x_match_count++;
                }
            }
            if (x_match_count == 2) {
                match_count++;
            }
        }
    }

    return match_count;
}

int main() {
    std::cout << "Advent of code 2024 Day 3" << std::endl;

    std::ifstream input("../../resources/input_day4_1.txt");

    std::vector<std::vector<char>> word_grid;
    read_input_from_file(input, [&](std::string line) {
        word_grid.emplace_back(std::vector(line.begin(), line.end()));
    });

    long word_count = 0;
    word_count = match_x_word_count(word_grid, "MAS");
    std::cout << "XMAS match count: " << word_count << std::endl;

    input.close();
    return 0;
}
