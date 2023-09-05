#include <iostream>

long long int binary_block_search(long long int N) {
    long long int min_blocks = 1; // block will be called n floors, each of which has n rooms
    long long int max_blocks = 1817;
    while (min_blocks < max_blocks) {
        long long int middle_block = (max_blocks + min_blocks) / 2;
        if (middle_block * (middle_block + 1) * (2 * middle_block + 1) == 6 * N) {
            return middle_block;
        } else if (middle_block * (middle_block + 1) * (2 * middle_block + 1) < 6 * N) {
            min_blocks = middle_block + 1;
        } else {
            max_blocks = middle_block;
        }
    }
    return min_blocks;
}


int main() {
    long long int N;
    std::cin >> N;
    long long int blocks_behind_N = binary_block_search(N) - 1;
    N -= (blocks_behind_N * (blocks_behind_N + 1) * (2 * blocks_behind_N + 1)) / 6; // remaining rooms
    long long int floors_behind_in_block = (N - 1) / (blocks_behind_N + 1);
    N -= floors_behind_in_block * (blocks_behind_N + 1);
    long long int floor_number = (1 + blocks_behind_N) * blocks_behind_N / 2 + floors_behind_in_block + 1;
    std::cout << floor_number << ' ' << N;
    return 0;
}
