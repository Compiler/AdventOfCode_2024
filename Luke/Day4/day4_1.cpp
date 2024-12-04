#include "../helper.h"
#include <vector>
#include <fstream>
#include <string>

typedef std::vector<std::vector<char>> Graph ;

struct Coord {int x, y;};

bool coordInBounds(const Coord& coord, Graph& graph) {
    return coord.x >= 0 && coord.y <= graph.size() && coord.y >= 0 && coord.x <= graph[coord.y].size();
}
// Return {} for no letter, otherwise return x,y coord
std::vector<Coord> letterIsAdjacent(Graph& graph, char letter, Coord from) {
    static std::vector<Coord> directions = {{1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, 0}, {-1, 1}, {0, 1}, {0, -1}};
    if(!coordInBounds(from, graph)) return {};

    std::vector<Coord> result = {};
    for(auto& vec : directions) {
        Coord newCoord = {from.x + vec.x, from.y + vec.y};
        if (coordInBounds(newCoord, graph)) {
            char letterAtCoord = graph[newCoord.y][newCoord.x];
            if (letterAtCoord == letter) {
                printf("Found letter in adjacency: %d, %d -> %c %c\n", newCoord.y, newCoord.x, letter, letterAtCoord);
                result.push_back(newCoord);
            }
        } 
    }



    return result;
}

// Global success count, can pass to recursiveSearch as reference if modularization needed.
int successSum = 0;
void recursiveSearch(Graph& graph, Coord from, std::vector<char> lettersToFind) {
    if(lettersToFind.empty()) {
        printf("Done.\n");
        successSum++;
        return;
    }
    if(!coordInBounds(from, graph)) return;

    printf("Checking for %c from %d, %d\n", lettersToFind.front(), from.x, from.y);

    auto adjacentSuccesses = letterIsAdjacent(graph, lettersToFind.front(), from);
    printf("Found %d instances!\n", adjacentSuccesses.size());
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
                recursiveSearch(graph, {y, x}, lettersToFind);
            }
        }

    }

    printf("Number of 'XMAS' in graph: %d\n", successSum);

}
