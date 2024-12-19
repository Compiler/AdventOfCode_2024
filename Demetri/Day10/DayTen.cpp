#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include "../Point.h"

std::vector<std::vector<int>> directions = {
    {-1, 0}, // Up
    {1, 0}, // Down
    {0, -1}, // Left
    {0, 1} // Right
};

std::vector<std::vector<int>> read_in_map(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    char token;
    std::vector<std::vector<int>> map;

    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);
        std::vector<int> curr_row;
        while (iss >> token) {
            curr_row.push_back(token - '0');
        }
        map.push_back(curr_row);
    }
    return map;
}

bool is_in_bounds(int W, int r, int c) {
    return !(r < 0 || r >= W || c < 0 || c >= W);
}

int get_trailhead_score(std::vector<std::vector<int>>& map, 
                        std::unordered_set<Point, PointHash>& visited,
                        int r, int c, int num_check, bool part_two) {
    
    Point p(r, c);
    if (!is_in_bounds(map.size(), r, c) || map[r][c] != num_check || visited.find(p) != visited.end()) {
        return 0;
    }
    
    if (!part_two) {visited.insert(p);}
    if (num_check == 9) {
        return true;
    }

    int total = 0;
    for (auto& dir : directions) {
        int new_row = r + dir[0];
        int new_col = c + dir[1];
        total += get_trailhead_score(map, visited, new_row, new_col, num_check + 1, part_two);
    }

    return total;
}

int part_one(const std::string& file_name) {
    std::vector<std::vector<int>> map = read_in_map(file_name);
    int W = map.size();
    int total_score = 0;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < W; j++) {
            if (map[i][j] == 0) {
                std::unordered_set<Point, PointHash> visited(0, PointHash(W));
                int curr_score = get_trailhead_score(map, visited, i, j, 0, false);
                std::cout << Point(i, j).to_string() << " has score: " << curr_score << std::endl;
                total_score += curr_score;
            }
        }
    }
    return total_score;
}

int part_two(const std::string& file_name) {
    std::vector<std::vector<int>> map = read_in_map(file_name);
    int W = map.size();
    int total_score = 0;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < W; j++) {
            if (map[i][j] == 0) {
                std::unordered_set<Point, PointHash> visited(0, PointHash(W));
                int curr_score = get_trailhead_score(map, visited, i, j, 0, true);
                std::cout << Point(i, j).to_string() << " has score: " << curr_score << std::endl;
                total_score += curr_score;
            }
        }
    }
    return total_score;
}

int main() {
    const std::string file_name = "day_ten_input.txt";
    std::cout << part_one(file_name) << std::endl;
    std::cout << part_two(file_name) << std::endl;
}