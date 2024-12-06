

#include "../helper.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
int main() {
    
    std::ifstream file("puzzle_input.txt");

    std::string line;
    bool inStart = true;
    std::unordered_map<std::string, std::string> rules;
    int numValid = 0;
    while(std::getline(file, line)) {
        inStart = inStart && line != "";
        
        if (inStart) {// Rules
            int pivot = line.find('|');
            std::string key = line.substr(0, pivot); 
            std::string val = line.substr(pivot + 1, line.size()); 
            printf("Rule %ld: %s comes before %s\n", rules.size() + 1, key.c_str(), val.c_str());
            rules[key] = val;
        } else {// Pages
            if(line.empty()) continue;
            printf("Page: '%s'\n", line.c_str());
            int numEntries = std::count(line.begin(), line.end(), ',') + 1;
            int middleIndex = numEntries / 2;
            int middleEntry = 0;
            std::stringstream pageStream(line);
            std::unordered_set<std::string> seenBefore;
            std::string entry;
            bool validEntry = true;
            int index = 0;
            // Place an entry. While doing so, if we have ever seen it's rule-> invalid page.
            while (std::getline(pageStream, entry, ',')) {
                if(index == middleIndex) middleEntry = std::stoi(entry);
                auto ruleIt = rules.find(entry);
                const auto ruleStr = ruleIt != rules.end() ? ruleIt->second : ""; 
                const bool ruleSeenBefore = ruleIt != rules.end() && seenBefore.find(ruleStr) != seenBefore.end();
                const auto seenEntryBefore = seenBefore.find(entry) != seenBefore.end();
                if(ruleSeenBefore) validEntry = false;
                seenBefore.insert(entry);
                index++;
            }
            printf("Middle: %d\n", middleEntry);
            numValid += validEntry * middleEntry;
        }
    }
    printf("Sum of valid middle entries: %d\n", numValid);
}
