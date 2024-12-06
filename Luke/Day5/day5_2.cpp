

#include "../helper.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
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
            std::unordered_map<std::string, int> seenBefore;
            std::string entry;
            bool validEntry = true;
            int index = 0;
            std::vector<std::string> page_order;
            // Place an entry. While doing so, if we have ever seen it's rule-> invalid page.
            while (std::getline(pageStream, entry, ',')) {
                if(index == middleIndex) middleEntry = std::stoi(entry);
                auto ruleIt = rules.find(entry);
                std::string ruleViolated = "";
                for(auto rule : ruleIt->second){
                    const auto ruleStr = rule; 
                    const bool ruleSeenBefore = ruleIt != rules.end() && seenBefore.find(ruleStr) != seenBefore.end();
                    const auto seenEntryBefore = seenBefore.find(entry) != seenBefore.end();
                    if(ruleSeenBefore) {
                        validEntry = false;
                        ruleViolated = ruleStr;
                    }
                }
                if(validEntry) page_order.push_back(entry);
                seenBefore.insert({entry, index});
                index++;
            }
            numValid += validEntry * middleEntry;
        }
    }
    printf("Sum of valid middle entries: %d\n", numValid);
}
