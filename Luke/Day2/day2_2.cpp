#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../helper.h"

void getInputMetaData() {

    std::ifstream file("puzzle_input.txt");
    std::string record;
    int records{0}, maxLevels{0}, minLevels{500};
    while (std::getline(file, record)) {
        std::istringstream iss(record);
        std::string level;
        records++;

        int curLevelCount = 0;
        while (iss >> level) {
            curLevelCount ++;
        }
        if(curLevelCount == 0) continue;
        maxLevels = std::max(maxLevels, curLevelCount);
        minLevels = std::min(minLevels, curLevelCount);
    }
}


std::pair<bool, int> evaluateRecord(std::vector<int>& levels, int ignoreIndex = -1) {

    // Lambda for checking safety given two adjacent levels and the expected direction (increasing vs decreasing)
    auto safetyCheck = [](int previousLevel, int currentLevel, bool direction){
        int delta = currentLevel - previousLevel;
        bool newDirection = previousLevel > currentLevel;
        bool deltaSafety = std::abs(delta) >= 1 && std::abs(delta) <= 3;
        bool directionSafety = direction == newDirection;
        return deltaSafety && directionSafety;
    };
    
    // Compute first two records to get 
    int firstLevel, secondLevel;
    int startingIndex = 2;
    if(ignoreIndex != -1 && ignoreIndex < 2) {
        if (ignoreIndex == 0) {
            firstLevel = levels[1];
            secondLevel = levels[2];
        } else {
            firstLevel = levels[0];
            secondLevel = levels[2];
        }
        startingIndex = 3;
    } else {
        firstLevel = levels[0]; 
        secondLevel = levels[1]; 
    }

    bool recordDirection = firstLevel > secondLevel;
    bool recordSafety = safetyCheck(firstLevel, secondLevel, recordDirection);
    int previousLevel = secondLevel;

    if(recordSafety == false) {
        return {false, 1};
    }
    for (int i = startingIndex; i < levels.size(); i++) {
        if(ignoreIndex == i) continue;
        int currentLevel = levels[i];
        bool safetyResponse = safetyCheck(previousLevel, currentLevel, recordDirection);
        if(safetyResponse == false) {
            return {false, i};
        }
        recordSafety &= safetyResponse;
        previousLevel = currentLevel;
    }
    return {true, -1};
}

int main() {
    // getInputMetaData(); We may assume the puzzle input will have at least 5 levels per record, and at max 8. This will help to hardcode first two level check.

    // Assume opened :D
    std::ifstream file("puzzle_input.txt");

    std::string record;
    int safeReports = 0;

    while (std::getline(file, record)) {
        std::istringstream iss(record);
        std::string level;

        std::vector<int> levels;
        while (iss >> level) {
            levels.push_back(std::stoi(level));
        }

        auto [recordSafety, recordBadIndex] = evaluateRecord(levels);
        if(recordSafety == false) {
            auto [recordSafety1, recordBadIndex1] = evaluateRecord(levels, recordBadIndex);
            auto [recordSafety2, recordBadIndex2] = evaluateRecord(levels, recordBadIndex - 1);
            auto [recordSafety3, recordBadIndex3] = evaluateRecord(levels, recordBadIndex + 1);

            safeReports += (recordSafety1 || recordSafety2 || recordSafety3);
        } else {
            safeReports += recordSafety;
        }
    }

    printf("Safe records found: %d\n", safeReports);
    return 0;

}
