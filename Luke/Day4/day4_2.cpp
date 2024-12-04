#include "../helper.h"
#include <vector>
#include <fstream>
#include <string>

struct Coord {int x, y;};

// 2 pt is a coordinate and a vector
typedef Coord Vec;
typedef std::vector<std::vector<char>> Graph ;

bool coordInBounds(const Coord& coord, const Graph& graph) {
    return coord.x >= 0 && coord.y < graph.size() && coord.y >= 0 && coord.x < graph[coord.y].size();
}
// Return {} for no letter, otherwise return x,y coord
std::vector<Coord> letterIsAdjacent(const Graph& graph, char letter, Coord from) {
    const std::vector<Vec> directions = {
        {1, 0},  {-1, 0}, {0, 1},  {0, -1}, // Horizontal and vertical
        {1, 1},  {1, -1}, {-1, 1}, {-1, -1} // Diagonals
    };

    if(!coordInBounds(from, graph)) return {};
    printf("Checking for %c @ (%d, %d)\n", letter, from.x, from.y);

    std::vector<Coord> result = {};
    for(auto& vec : directions) {
        Coord newCoord = {from.x + vec.x, from.y + vec.y};
        if (coordInBounds(newCoord, graph)) {
            char letterAtCoord = graph[newCoord.y][newCoord.x];
            if (letterAtCoord == letter) {
                printf("Found: [%d, %d] => (%d, %d) = %c\n", vec.x, vec.y, newCoord.x, newCoord.y, letterAtCoord);
                result.push_back(newCoord);
            }
        } 
    }



    return result;
}

// Global success count, can pass to recursiveSearch as reference if modularization needed.
int successSum = 0;
std::vector<std::vector<bool>> visited;
void recursiveSearch(Graph& graph, Coord from, std::vector<char> lettersToFind) {
    if(lettersToFind.empty()) {
        successSum++;
        printf("Done @ (%d, %d)\n", from.x, from.y);
        return;
    }
    if(!coordInBounds(from, graph) ) return;
    auto adjacentSuccesses = letterIsAdjacent(graph, lettersToFind.front(), from);
    if(adjacentSuccesses.empty()) return;
    lettersToFind.erase(lettersToFind.begin()); 
    int curSum = successSum;
    for(auto successCoord : adjacentSuccesses) {
        recursiveSearch(graph, successCoord, lettersToFind);
    }
}

int main() {
    std::ifstream file("puzzle_input.txt");


    // Create 2d vector of values
    Graph graph;
    std::string line;
    while(std::getline(file, line)) {
       graph.push_back(std::vector<char>(line.size(), '.')); 
       visited.push_back(std::vector<bool>(line.size(), false));
       for(int i = 0; i < line.size(); i++) {
           graph.back()[i] = line[i];
       }
    }


    // Full graph completed
    // lettersToFind as state machine / queue of current search
    std::vector<char> lettersToFind = {'M', 'A', 'S'}; // Only search if we have an 'X'

    for(int y = 0; y < graph.size(); y++) {
       print_vector(graph[y]);
       printf("\n");
    }
    for(int y = 0; y < graph.size(); y++) {
        for(int x = 0; x < graph[y].size(); x++) {
            if(graph[y][x] == 'X') {
                recursiveSearch(graph, {x, y}, lettersToFind);
            }
        }

    }

    printf("Number of 'XMAS' in graph: %d\n", successSum);

}
