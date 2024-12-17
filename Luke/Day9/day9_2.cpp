#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <string>
int main() {
    std::ifstream file("puzzle_input.txt");

    std::vector<char> disk;
    std::string diskLine;
    std::map<int, int> freeSpaceBlocks;
    std::map<int, int> objectIdToSize;
    
    while(std::getline(file, diskLine)) {
        bool freeSpace = false;
        int blockId = 0; 
        int runningIndex = 0;
        for(auto c : diskLine) {
            int numOfObject = c - '0';
            printf("Work on %c: %d block id = %d\n", c, numOfObject, blockId); 

            if(freeSpace) {
                freeSpaceBlocks[runningIndex] = numOfObject;
            } else {
                objectIdToSize[blockId] = numOfObject;
            }
            runningIndex += numOfObject;
            if(!freeSpace) blockId++;
            freeSpace = !freeSpace;
        }
    }

    for(auto objectIt = objectIdToSize.rbegin(); objectIt != objectIdToSize.rend(); ++objectIt) {
        auto largestObjectIt = std::prev(objectIdToSize.end());
        auto objectIdSize = largestObjectIt->second;

        auto freeBlockIt = freeSpaceBlocks.begin();

        while(freeBlockIt != freeSpaceBlocks.end() && freeBlockIt->second < objectIdSize) {
            freeBlockIt++;
        }
        // Found condition to insert
        if(freeBlockIt != freeSpaceBlocks.end()) {
           auto freeBlockSize = freeBlockIt->second; 
        }
    }

    auto it1 = freeSpaceBlocks.begin();
    auto it2 = objectIdToSize.begin();

    unsigned long long checksum = 0; 
    for(auto& [index, objectId] : objectIdToSize) {
        checksum += (objectId * index);
    }

    printf("Checksum of file: %llu\n", checksum);
}
