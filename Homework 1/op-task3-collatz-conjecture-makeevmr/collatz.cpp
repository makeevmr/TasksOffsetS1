#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int steps = 0;
    int max_number = 1;
    while(n != 1) {
        if (max_number < n) {
            max_number = n;
        }
        ++steps;
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n * 3 + 1;
        }
    }
    std::cout << steps << ' ' << max_number;
}
