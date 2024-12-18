#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <list>

typedef long long ull;

// Fast count
ull countDigits(ull n) {
    if (n == 0) return 1; 
    return static_cast<ull>(std::log10(std::abs(n))) + 1;
}

void step(std::list<ull>& stones) {

    for (auto stoneIt = stones.begin(); stoneIt != stones.end(); ++stoneIt) {
        auto stone = *stoneIt;
        auto numDigits = countDigits(stone);
        if(stone == 0) {
            *stoneIt = 1;
        } else if (numDigits % 2 == 0) {
            ull divisor = std::pow(10, numDigits / 2); 
            ull firstDigits = stone / divisor;        
            ull lastDigits = stone % divisor;
            *stoneIt = firstDigits;
            stoneIt = std::prev(stones.insert(std::next(stoneIt), lastDigits));
            stoneIt++;
        } else {
            *stoneIt = stone * 2024;
        }
    }

}

int main() {
    
    std::ifstream file("puzzle_input.txt");
    std::string line;
    std::list<ull> stones;
    std::getline(file, line);
    std::istringstream stream(line);
    while(stream >> line) stones.push_back(std::stoi(line));

    for(ull i = 0; i < 75; i++){
        printf("Step %d\n", i+1);
        step(stones);
    }

    printf("Num stones: %lld\n", stones.size());

    return 0;
}
