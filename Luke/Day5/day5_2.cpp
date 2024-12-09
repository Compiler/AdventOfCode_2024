

#include "../helper.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

int finalSum = 0;

bool validatePage(std::vector<std::string>& pageEntries, std::unordered_map<std::string, std::vector<std::string>>& rules, bool root = true) {
    print_vector(pageEntries); printf("\n");
    std::unordered_map<std::string, int> seenBefore;
    std::string entry;
    bool validEntry = true;
    bool wasInvalid = false;
    std::vector<std::string> entries;
    int swapIndex = INT_MAX;

    for(int i = 0; i < entries.size(); i++) {
        auto& entry = entries[i];
        auto ruleIt = rules.find(entry);
        std::string ruleViolated = "";
        for(auto rule : ruleIt->second){
            const auto ruleStr = rule; 
            const bool ruleSeenBefore = ruleIt != rules.end() && seenBefore.find(ruleStr) != seenBefore.end();
            const auto seenEntryBefore = seenBefore.find(entry) != seenBefore.end();
            if(ruleSeenBefore) {
                wasInvalid = true;
                auto indexOfRule = seenBefore[entry];
                validEntry = false;
                ruleViolated = ruleStr;
                std::swap(entries[i], entries[indexOfRule]);
                break;
            }
        }
        if(!validEntry){
            wasInvalid = true;
            break;
        }
        seenBefore.insert({entry, i});
    }
    if(!validEntry) validEntry = validatePage(pageEntries, rules, 0);
    if(wasInvalid && root) finalSum += std::stoi(entries[entries.size() / 2]);
    if(root) printf("Correct: ");
    print_vector(pageEntries); printf("\n");

    return true;
}
int main() {
    
    std::ifstream file("puzzle_input.txt");

    std::string line;
    bool inStart = true;
    std::unordered_map<std::string, std::vector<std::string>> rules;
    int numValid = 0;
    while(std::getline(file, line)) {
        inStart = inStart && line != "";
        
        if (inStart) {// Rules
            int pivot = line.find('|');
            std::string key = line.substr(0, pivot); 
            std::string val = line.substr(pivot + 1, line.size()); 
            rules[key].push_back(val);
        } else {// Pages
            if(line.empty()) continue;
            int numEntries = std::count(line.begin(), line.end(), ',') + 1;
            int middleIndex = numEntries / 2;
            int middleEntry = 0;
            std::stringstream pageStream(line);
            std::string entry;
            std::vector<std::string> entries;
            while (std::getline(pageStream, entry, ',')) {
                entries.push_back(entry);
            }
            if(validatePage(entries, rules)) numValid += std::stoi(entries[middleIndex]);
        }
    }
    printf("Sum of valid middle entries: %d\n", finalSum);
}
