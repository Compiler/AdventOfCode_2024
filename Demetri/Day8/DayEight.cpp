#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "../Point.h"

bool is_in_bounds(int W, int r, int c) {
    return !(r < 0 || r >= W || c < 0 || c >= W);
}

std::vector<std::vector<char>> read_in_map(const std::string& file_name) {
    std::vector<std::vector<char>> mapped;
    std::ifstream file(file_name);
    std::string curr_line;
    char token;
    while (std::getline(file, curr_line)) {
        std::vector<char> curr_row;
        std::istringstream iss(curr_line);
        while (iss >> token) {
            curr_row.push_back(token);
        }
        mapped.push_back(curr_row);
    }
    return mapped;
}

void print_map(std::vector<std::vector<char>>& mapped) {
    for (auto& row : mapped) {
        for (auto& chr : row) {
            std::cout << chr;
        }
        std::cout << std::endl;
    }
}

int part_one(const std::string& file_name) {
    std::vector<std::vector<char>> mapped = read_in_map(file_name);
    int W = mapped.size();
    char curr_char;
    std::unordered_map<char, std::vector<Point>> locations;
    std::unordered_set<Point, PointHash> antinode_locations(10, PointHash(W));

    // Get the locations where each char appears
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < W; j++) {
            curr_char = mapped[i][j];
            if (curr_char == '.') {
                continue;
            }
            locations[curr_char].push_back(Point(i, j));
        }
    }


    // Pairwise slope between points, try and place antinode on every line
    for (auto& [chr, chr_locs] : locations) {
        int n = chr_locs.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int left_x = chr_locs[i].x, left_y = chr_locs[i].y; // Location of point 1
                int right_x = chr_locs[j].x, right_y = chr_locs[j].y; // Location of point 2
                int delta_x = left_x - right_x, delta_y = left_y - right_y; // Difference between the two / slope

                if (is_in_bounds(W, left_x + delta_x, left_y + delta_y)) {
                    antinode_locations.insert(Point(left_x + delta_x, left_y + delta_y));
                }

                if (is_in_bounds(W, right_x - delta_x, right_y - delta_y)) {
                    antinode_locations.insert(Point(right_x - delta_x, right_y - delta_y));
                }
                
            }
        }
    }
    

    return antinode_locations.size();
}

int part_two(const std::string& file_name) {
    std::vector<std::vector<char>> mapped = read_in_map(file_name);
    int W = mapped.size();
    char curr_char;
    int total = 0;
    std::unordered_map<char, std::vector<Point>> locations;
    std::unordered_set<Point, PointHash> antinode_locations(10, PointHash(W));

    // Get the locations where each char appears
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < W; j++) {
            curr_char = mapped[i][j];
            if (curr_char == '.') {
                continue;
            }
            locations[curr_char].push_back(Point(i, j));
        }
    }

    for (auto& [chr, chr_locs] : locations) {
        int n = chr_locs.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int left_x = chr_locs[i].x, left_y = chr_locs[i].y; 
                int right_x = chr_locs[j].x, right_y = chr_locs[j].y; 
                int delta_x = left_x - right_x, delta_y = left_y - right_y; 

                while (is_in_bounds(W, left_x, left_y)) {
                    antinode_locations.insert(Point(left_x , left_y));
                    left_x += delta_x;
                    left_y += delta_y;
                }

                while (is_in_bounds(W, right_x , right_y)) {
                    antinode_locations.insert(Point(right_x, right_y));
                    right_x -= delta_x;
                    right_y -= delta_y;
                }
                
            }
        }
    }
    
    return antinode_locations.size() + total;
}

int main() {
    const std::string file_name = "day_eight_input.txt";
    std::cout << part_one(file_name) << std::endl;
    std::cout << part_two(file_name) << std::endl;
}