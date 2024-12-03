#include <fstream>
#include <sstream>
#include <string>

int main() {

    // Assume opened :D
    std::ifstream file("puzzle_input.txt");

    // Lambda for checking safety given two adjacent levels and the expected direction (increasing vs decreasing)
    auto safetyCheck = [](int previousLevel, int currentLevel, bool direction){
        int delta = currentLevel - previousLevel;
        bool newDirection = previousLevel > currentLevel;
        bool deltaSafety = std::abs(delta) >= 1 && std::abs(delta) <= 3;
        bool directionSafety = direction == newDirection;
        return deltaSafety && directionSafety;
    };


    std::string record;
    int safeReports = 0;

    while (std::getline(file, record)) {
        std::istringstream iss(record);
        std::string level;

        // Compute first two records to get 
        iss >> level;
        int firstLevel = std::stoi(level); 
        iss >> level;
        int secondLevel = std::stoi(level); 

        bool recordDirection = firstLevel > secondLevel;
        bool recordSafety = safetyCheck(firstLevel, secondLevel, recordDirection);
        int previousLevel = secondLevel;
        // No clear-line short-circuit
        while (iss >> level) {
            int currentLevel = std::stoi(level);
            recordSafety &= safetyCheck(previousLevel, currentLevel, recordDirection);
            previousLevel = currentLevel;
        }
        safeReports += recordSafety;
    }

    printf("Safe records found: %d\n", safeReports);
    return 0;

}
