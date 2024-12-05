

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
            printf("Rule 1: %s comes before %s\n", key.c_str(), val.c_str());
            rules[key] = val;
        } else {// Pages
            std::stringstream pageStream(line);
            std::unordered_set<std::string> seenBefore;
            std::string entry;
            bool validEntry = true;
            while (std::getline(pageStream, entry, ',')) {
                auto seen = seenBefore.find(entry);

            }
            numValid += validEntry;
        }
    }
}
