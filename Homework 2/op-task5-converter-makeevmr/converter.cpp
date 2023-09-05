#include <iostream>

void new_radix_symbols(long long int N, const short int radix, short int &index, int *digit_array) {
    while (N >= radix) {
        ++index;
        digit_array[index] = (int)(N % radix);
        N /= radix;
    }
    ++index;
    digit_array[index] = (int)N;
}

int main() {
    long long int N;
    short int radix;
    short int index = -1;
    int digit_array[31];
    std::cin >> N >> radix;
    new_radix_symbols(N, radix, index, digit_array);
    while (index >= 0) {
        switch(digit_array[index]) {
            case 10:
                std::cout << 'A';
                break;
            case 11:
                std::cout << 'B';
                break;
            case 12:
                std::cout << 'C';
                break;
            case 13:
                std::cout << 'D';
                break;
            case 14:
                std::cout << 'E';
                break;
            case 15:
                std::cout << 'F';
                break;
            default:
                std::cout << digit_array[index];
        }
        --index;
    }
    return 0;
}