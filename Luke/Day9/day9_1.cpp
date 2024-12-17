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
    std::set<int> freeSpaceIndices;
    std::map<int, int> indexToObject;
    
    while(std::getline(file, diskLine)) {
        bool freeSpace = false;
        int blockId = 0; 
        for(auto c : diskLine) {
            int numOfObject = c - '0';

            for(int i = 0; i < numOfObject; i++) {
                if(freeSpace) {
                    disk.push_back('.');
                    freeSpaceIndices.insert(disk.size() - 1);
                } else {
                    disk.push_back('0'+blockId);
                    indexToObject[disk.size() - 1] = blockId;
                }
            }
            if(!freeSpace) blockId++;
            freeSpace = !freeSpace;
        }
    }

    for(auto firstFreeSpace = freeSpaceIndices.begin(); firstFreeSpace != freeSpaceIndices.end() && !indexToObject.empty();) {
        auto largestObjectIt = std::prev(indexToObject.end());

        auto indexOfFirstFreeSpace = *firstFreeSpace;
        auto indexOfLargestObjectId = largestObjectIt->first;
        auto objectId = largestObjectIt->second;
        if(indexOfLargestObjectId < indexOfFirstFreeSpace) break;

        freeSpaceIndices.insert(indexOfLargestObjectId);
        indexToObject[indexOfFirstFreeSpace] = objectId;
        
        indexToObject.erase(largestObjectIt);
        firstFreeSpace = freeSpaceIndices.erase(firstFreeSpace);
    }

    auto it1 = freeSpaceIndices.begin();
    auto it2 = indexToObject.begin();

    unsigned long long checksum = 0; 
    for(auto& [index, objectId] : indexToObject) {
        checksum += (objectId * index);
    }

    printf("Checksum of file: %llu\n", checksum);
}
