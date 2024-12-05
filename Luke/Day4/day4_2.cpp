#include "../helper.h"
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#define PI 3.14159
struct Point {int x, y;};
int main() {
    std::ifstream file("puzzle_input.txt");

    std::string line;
    std::vector<std::vector<char>> graph;
    // setup graph
    while(std::getline(file, line)) {
        graph.push_back(std::vector<char>());
        for(auto c : line) graph.back().push_back(c);
    }

    int sum = 0;
    // Centers are offset one-in
    for(int y = 1; y < graph.size() - 1; y++) {
        print_vector(graph[y]); printf("\n");
        for(int x = 1; x < graph.size() - 1; x++) {
            if (graph[y][x] == 'A') {
                auto dag1 = (graph[y-1][x-1] == 'S' && graph[y+1][x+1] == 'M') || (graph[y-1][x-1] == 'M' && graph[y+1][x+1] == 'S');
                auto dag2 = (graph[y+1][x-1] == 'S' && graph[y-1][x+1] == 'M') || (graph[y+1][x-1] == 'M' && graph[y-1][x+1] == 'S');
                sum += dag1 && dag2;
            }
        }
    }

    printf("Number of X-MAS: %d\n", sum);
    return 0;
}
