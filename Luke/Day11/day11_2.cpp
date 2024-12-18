#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <unordered_map>

typedef long long ull;

// Fast count
ull countDigits(ull n) {
    if (n == 0) return 1; 
    return static_cast<ull>(std::log10(std::abs(n))) + 1;
}

std::unordered_map<ull, ull> memo;
int numStones = 0;
int step(ull stone, int iterations) {
    if (iterations == 0) {
        return 1;
    }



    auto numDigits = countDigits(stone);
    if(stone == 0) {
        memo[stone] = 1;
        step(1, iterations - 1);
    } else if (numDigits % 2 == 0) {
        ull divisor = std::pow(10, numDigits / 2); 
        ull firstDigits = stone / divisor;        
        ull lastDigits = stone % divisor;
        auto res1 = step(firstDigits, iterations - 1);
        auto res2 = step(lastDigits, iterations - 1);
        memo[stone] = res1+res2;
        return res1 + res2;
    } 
    memo[stone] = 1;
    return step(stone * 2024, iterations - 1);
}

int main() {
    
    std::ifstream file("puzzle_input.txt");
    std::string line;
    std::vector<ull> stones;
    std::getline(file, line);
    std::istringstream stream(line);
    while(stream >> line) stones.push_back(std::stoi(line));

    for(auto stone : stones) {
        step(stones, 75);
    }

    printf("Num stones: %lld\n", stones.size());

    return 0;
}
