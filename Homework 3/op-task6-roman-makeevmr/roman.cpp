#include <iostream>

char *roman_number_creator(int arabic_number, char *roman_number) {
    char units[] = "IIIIIIIVVVIVIIVIIIIX";
    char tens[] = "XXXXXXXLLLXLXXLXXXXC";
    char hundreds[] = "CCCCCCCDDDCDCCDCCCCM";
    char thousands[] = "MMMMMM";
    char *roman_numbers[] = {thousands, hundreds, tens, units};
    int symbol_mapping[] = {0, 1, 3, 6, 8, 9, 11, 14, 18, 20};
    int arabic_digits[4] = {};
    int index = 3;
    while (arabic_number > 0) {
        arabic_digits[index] = arabic_number % 10;
        arabic_number /= 10;
        --index;
    }
    int roman_number_index = 0;
    for (int i = 0; i < 4; ++i) {
        if (arabic_digits[i] > 0) {
            for (int j = symbol_mapping[arabic_digits[i] - 1]; j < symbol_mapping[arabic_digits[i]]; ++j) {
                roman_number[roman_number_index] = roman_numbers[i][j];
                ++roman_number_index;
            }
        }
    }
    roman_number[roman_number_index] = '\0';
    return roman_number;
}

int main() {
    int arabic_number;
    char roman_number[16];
    std::cin >> arabic_number;
    roman_number_creator(arabic_number, roman_number);
    int roman_number_index = 0;
    while (roman_number[roman_number_index] != '\0') {
        std::cout << roman_number[roman_number_index];
        ++roman_number_index;
    }
    return 0;
}