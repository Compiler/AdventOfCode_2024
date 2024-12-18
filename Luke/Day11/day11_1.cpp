#include <string>
#include <sstream>
#include <vector>
#include <fstream>
int main() {
    
    std::ifstream file("puzzle_input.txt");
    std::string line;
    std::vector<int> stones;
    std::getline(file, line);
    std::istringstream stream(line);
    while(stream >> line) stones.push_back(std::stoi(line));

    for(auto stone : stones) printf("%d ", stone);

}
