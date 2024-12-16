#include <vector>
#include <fstream>
#include <sstream>

typedef unsigned long long ull;

bool evaluate(std::vector<ull>& nums, ull target, ull total = 0, ull index = 0) {
    if(target == total)      return true;
    if(index >= nums.size()) return false;

    if(index == 0) {
        return evaluate(nums, target, nums[index], index+1);
    }else{
        auto addPath = evaluate(nums, target, total + nums[index], index+1);
        auto mulPath = evaluate(nums, target, total * nums[index], index+1);
        return addPath || mulPath;
    }
}

int main() {
    std::ifstream file("puzzle_input.txt");

    std::string line;

    ull sumTestValues = 0;

    while(std::getline(file, line)) {
        ull testValue = std::stoll(line.substr(0, line.find(':')));
        std::istringstream stream(line.substr(line.find(':') + 1));
        std::vector<ull> numbers;
        ull number;
        while(stream >> number) {
            numbers.push_back(number);
        }

        if (evaluate(numbers, testValue)) {
            sumTestValues += testValue;
        }
    }

    printf("Sums of testvalues: %llu\n", sumTestValues);
}
