

#include <fstream>
#include <regex>
#include <string>
typedef long long mint;
int main() {

    std::ifstream file("puzzle_input.txt");

    mint sum = 0;
    std::string fileLine;

    std::regex pattern(R"(do\(\).*?mul\([0-9]+,[0-9]+\))");
    std::regex numberPattern(R"([0-9]+)");
    while (std::getline(file, fileLine)) {
        auto matchesIt = std::sregex_iterator(fileLine.begin(), fileLine.end(), pattern);
        for (auto it = matchesIt; it != std::sregex_iterator(); ++it) {
            std::string match = it->str();
            printf("Match: %s\n", match.c_str());
            if(match.find("don't()") != std::string::npos) continue;
            auto numIt = std::sregex_iterator(match.begin(), match.end(), numberPattern);
            mint num1 = std::stoi(numIt++->str());
            mint num2 = std::stoi(numIt->str());
            sum += num1*num2;
        }
    }

    printf("Sum of muls: %lld\n", sum);
}
