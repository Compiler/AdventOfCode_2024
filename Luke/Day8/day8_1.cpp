#include <cctype>
#include <fstream>
#include <functional>
#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
struct Point {
    int x, y;
    std::size_t operator()(const Point& p) const {
        std::size_t h1 = std::hash<int>{}(p.x); 
        std::size_t h2 = std::hash<int>{}(p.y);  

        return h1 ^ (h2 << 1);
    }

    std::size_t operator()() const {
        std::size_t h1 = std::hash<int>{}(x); 
        std::size_t h2 = std::hash<int>{}(y);  

        return h1 ^ (h2 << 1);
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Line {
    int rise;
    int run;
};

typedef std::vector<std::vector<char>> Graph;

std::unordered_set<Point, Point> antinodes;

bool pointIsAntenna(Graph& graph, const Point& point) {
    const char cell = graph[point.y][point.x];
    return std::isalpha(cell) || std::isdigit(cell);
}

bool inBounds(const Graph& graph, const Point& point) {
    return point.y < graph.size() && point.y >= 0 && graph[point.y].size() > point.x && point.x >= 0;
}

void generate_anti_nodes(Graph& graph, Point currentPoint, Point coincidentPoint, Line& line) {
    if(!pointIsAntenna(graph, currentPoint)) return; 

    char key = graph[currentPoint.y][currentPoint.x];
    //while(inBounds(graph, currentPoint)) {
        currentPoint.y += line.rise;
        currentPoint.x += line.run;
        if(currentPoint == coincidentPoint) return;
        if(inBounds(graph, currentPoint)) {
            const bool isAntenna = pointIsAntenna(graph, currentPoint);
            char& point = graph[currentPoint.y][currentPoint.x]; 
            if(point != '#') {
                if(!isAntenna) point = '#';
                antinodes.insert(currentPoint);
            }
        }
    //}
}

int main() {
    std::ifstream input("puzzle_input.txt");
    std::unordered_multimap<char, Point> freqList;
    Graph graph;

    std::string row;
    while(std::getline(input, row)) {
        graph.push_back({});
        for(auto col : row) {
            graph.back().push_back(col); 
            Point p = {(int)graph.back().size() - 1, (int)graph.size() - 1};
            if(pointIsAntenna(graph, p)) {
                freqList.insert({col, p});
            }
        }
    }

    for (auto it = freqList.begin(); it != freqList.end(); ) {
        auto key = it->first;
        auto range = freqList.equal_range(key);

        for (auto pointIt = range.first; pointIt != range.second; ++pointIt) {
            const Point& point1 = pointIt->second;
            for(auto point2It = std::next(pointIt); point2It != range.second; ++point2It) {
                const Point& point2 = point2It->second;
                Line connectionLine = {(point2.y - point1.y), point2.x - point1.x};
                // run twice to start from each point so I don't have to do case checking.
                generate_anti_nodes(graph, point1, point2, connectionLine);
                generate_anti_nodes(graph, point2, point1, connectionLine);
                connectionLine.rise = -connectionLine.rise;
                connectionLine.run = -connectionLine.run;
                generate_anti_nodes(graph, point1, point2, connectionLine);
                generate_anti_nodes(graph, point2, point1, connectionLine);
            }
        }

        it = range.second; 
    }

    printf("Total unique anti-nodes: %d\n", antinodes.size());
}
