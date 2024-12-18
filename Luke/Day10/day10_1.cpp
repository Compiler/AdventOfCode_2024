#include <climits>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> Graph;
struct Point{ 
    int x,y;

    bool operator==(const Point& other) {
        return other.x == x && other.y == y;
    }

    Point operator+(const Point& other) {
        return {other.x + x, other.y + y};
    }
};

std::vector<Point> directions = {{1,0}, {-1,0}, {0, 1}, {0, -1}};

bool inBounds(const Graph& g, const Point& p) {
    return p.y >= 0 && p.y < g.size() && g[p.y].size() > p.x && p.x >= 0;
}

int run_trail(Graph& graph, Point position, Point lastPosition = {-INT_MAX, -INT_MAX}, Point direction = {0, 0}, int lastHeight = -1, bool root = true) {
    Point newPosition = position + direction;
    if(!inBounds(graph, position) || !inBounds(graph, newPosition) ) return 0;
    int currentHeight = graph[position.y][position.x];
    if(currentHeight == 9) {
        printf("Success!\n");
        return 1;
    }
    int newHeight = graph[newPosition.y][newPosition.x];
    if(newPosition == lastPosition) return 0;
    printf("Entered: (%d, %d) from (%d, %d), new height %d, old one is %d\n", newPosition.x, newPosition.y, position.x, position.y, newHeight, currentHeight);
    if(!root && currentHeight + 1 != newHeight) return 0;

    printf("Ran to %d at (%d, %d)\n", currentHeight, newPosition.x, newPosition.y);
    // Run in all directions, backtrack at top.
    int total = 0;
    for(auto& newDirection : directions) total += run_trail(graph, newPosition, position, newDirection, currentHeight, false);
    return total;
}

int main() {
    
    std::ifstream file("puzzle_input.txt");
    std::string line;
     
    std::vector<Point> trailHeads;
    // Build graph
    Graph graph;
    while (std::getline(file, line)) {
        graph.push_back({});
        for(auto c : line) {
            if(c == '0') trailHeads.push_back({(int)graph.back().size(), (int)graph.size() - 1});
            graph.back().push_back(c - '0');
        }
    }

    int trailScore = 0;
    for(auto& trailHead : trailHeads) {
        printf("Running trail (%d, %d)\n", trailHead.x, trailHead.y);
        trailScore += run_trail(graph, trailHead);
    }
    printf("Trail scores sum: %d\n", trailScore);


}
