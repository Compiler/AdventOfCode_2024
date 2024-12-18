#include <climits>
#include <fstream>
#include <functional>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::vector<std::vector<int>> Graph;
struct Point{ 
    int x,y;

    bool operator==(const Point& other) const {
        return other.x == x && other.y == y;
    }

    Point operator+(const Point& other) {
        return {other.x + x, other.y + y};
    }

    std::size_t operator()() const {
        std::size_t h1 = std::hash<int>{}(x); 
        std::size_t h2 = std::hash<int>{}(y);  

        return h1 ^ (h2 << 1);
    }
    std::size_t operator()(const Point& p) const {
        std::size_t h1 = std::hash<int>{}(p.x); 
        std::size_t h2 = std::hash<int>{}(p.y);  

        return h1 ^ (h2 << 1);
    }

};

std::vector<Point> directions = {{1,0}, {-1,0}, {0, 1}, {0, -1}};

bool inBounds(const Graph& g, const Point& p) {
    return p.y >= 0 && p.y < g.size() && g[p.y].size() > p.x && p.x >= 0;
}

int getCell(const Graph& g, const Point& p) {
    if(!inBounds(g, p)) return INT_MIN;
    return g[p.y][p.x];
}

int run_trail(Graph& graph, Point position) {
    if(!inBounds(graph, position)) return 0;
    int currentHeight = getCell(graph, position);
    if(currentHeight == 9){
        return 1;
    }
    printf("(%d, %d) = %d\n", position.x, position.y, currentHeight);

    // Run in all directions, backtrack at top.
    int total = 0;
    for(auto& newDirection : directions) {
        auto nextPos = position + newDirection;
        auto nextCell = getCell(graph, nextPos);
        if(nextCell == currentHeight + 1) {
            total += run_trail(graph, nextPos);
        }
    }

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
