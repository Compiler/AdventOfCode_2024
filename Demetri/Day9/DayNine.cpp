#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


struct MemoryBlock {
    bool is_free;
    int id_;
    int block_size;
    MemoryBlock *prev;
    MemoryBlock *next;

    std::string to_string() {
        std::ostringstream oss;
        for (int i = 0; i < block_size; i++) {
            if (is_free) {
                oss << ".";
            }
            else {
                oss << id_;
            }
        }
        return oss.str();
    }
};

typedef unsigned long long ull;

void print_memory(MemoryBlock *ptr, bool backwards) {
    while (ptr != nullptr) {
        std::cout << ptr->to_string();
        ptr = !backwards ? ptr->next : ptr->prev; 
    }
    std::cout << std::endl;
}

ull part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string puzzle_input;

    // Only 1 line for this puzzle
    std::getline(file, puzzle_input);
    std::vector<int> memory_line;
    int id_ = 0;
    for (int i = 0; i < puzzle_input.size(); i++) {
        int num_char = puzzle_input[i] - '0';
        bool is_free = i % 2 != 0;
        for (int j = 0; j < num_char; j++) {
            memory_line.push_back(is_free ? -1 : id_);
        }
        if (is_free) id_++;
    }

    int n = memory_line.size();
    int l = 0, r = n - 1;
    while (l < memory_line.size()) {

        // Move left to the next free, right to the next taken
        // Break out of loop if left exceeds right
        while (l < n && memory_line[l] != -1) {l++;}
        while (r >= 0  && memory_line[r] == -1) {r--;}
        if (l > r) {break;}

        // Free the val on the right, replace the val on the left;
        memory_line[l] = memory_line[r];
        memory_line[r] = -1;
    }   

    // Calculate checksum
    ull checksum = 0;
    for (int i = 0; i < memory_line.size(); i++) {
        if (memory_line[i] == -1) {
            continue;
        }
        checksum += memory_line[i] * i;
    }
    return checksum;

}

ull part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string puzzle_input;
    std::getline(file, puzzle_input);
    MemoryBlock dummy{false, -1, -1, nullptr, nullptr};
    MemoryBlock *right = &dummy, *left;

    int id_ = 0;
    for (int i = 0; i < puzzle_input.size(); i++) {
        int num_char = puzzle_input[i] - '0';
        bool is_free = i % 2 != 0;
        int block_id = is_free ? -1 : id_++;
        MemoryBlock *next_block = new MemoryBlock{is_free, block_id, num_char, right, nullptr};
        right->next = next_block;
        right = right->next;
    }

    while (right != nullptr && right->prev != nullptr) {
        left = dummy.next; // Start at head every time
        while (right != nullptr && right->is_free) {right = right->prev;} // Find next to-be moved block of memory
        // Move left until sufficient free space is found
        while (left != nullptr && left != right) {
            // If a free block is found, populate it, create a new block of the difference
            if (left->is_free && left->block_size >= right->block_size) {
                int left_size = left->block_size;

                // Populate left
                left->is_free = false;
                left->block_size = right->block_size;
                left->id_ = right->id_;

                // Make right free
                right->is_free = true;
                right->id_ = -1;

                // Insert new free memory of difference
                if (left_size - right->block_size != 0) {
                    MemoryBlock *new_free_space = new MemoryBlock{true, -1, left_size - right->block_size, left, left->next};
                    left->next->prev = new_free_space;
                    left->next = new_free_space;
                }
                break;
            }
            left = left->next;
        }
        right = right->prev;
    }

    ull checksum = 0;
    left = dummy.next;
    int pos = 0;
    while (left != nullptr) {
        if (!left->is_free) {
            for (int i = 0; i < left->block_size; i++) {
                std::cout << pos << "*" << left->id_ << std::endl;
                checksum += (pos++ * left->id_);
            }
        }
        else {
            pos += left->block_size;
        }
        left = left->next;
    }

    return checksum;
}

int main() {
    const std::string file_name = "day_nine_input.txt";
    std::cout << part_one(file_name) << std::endl;
    std::cout << part_two(file_name) << std::endl;

}