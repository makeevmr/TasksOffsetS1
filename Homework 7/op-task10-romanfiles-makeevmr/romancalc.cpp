#include <iostream>
#include <fstream>
#include "conversion_to_roman_file.hpp"

int map_roman_number(char roman_symbol) {
    if (roman_symbol == 'I') {
        return 1;
    }
    if (roman_symbol == 'V') {
        return 5;
    }
    if (roman_symbol == 'X') {
        return 10;
    }
    if (roman_symbol == 'L') {
        return 50;
    }
    if (roman_symbol == 'C') {
        return 100;
    }
    if (roman_symbol == 'D') {
        return 500;
    }
    if (roman_symbol == 'M') {
        return 1000;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    conversion_to_roman_file(argv[1], "interim.txt");
    std::ifstream input_file("interim.txt");
    std::ofstream output_file(argv[2]);
    int previous_number;
    int current_number;
    int roman_sum = 0;
    int result_number;
    int stack_number_length = 0;
    int stack[100];
    int stack_length = 0;
    char arabic_number[5];
    int arabic_number_length = 0;
    char roman_number[16];
    int roman_number_length = 0;
    bool pass_step = false;
    bool start_digit_detected = false;
    if (input_file && output_file) {
        while (input_file.peek() != EOF) {
            char new_symbol = static_cast<char>(input_file.get());
            if (new_symbol == 'I' || new_symbol == 'V' || new_symbol == 'X' || new_symbol == 'L' || new_symbol == 'C' ||
                new_symbol == 'D' || new_symbol == 'M') {
                if (!start_digit_detected) {
                    previous_number = map_roman_number(new_symbol);
                    start_digit_detected = true;
                } else {
                    current_number = map_roman_number(new_symbol);
                    if (!pass_step) {
                        if (previous_number >= current_number) {
                            roman_sum += previous_number;
                        } else {
                            pass_step = true;
                            roman_sum += current_number - previous_number;
                        }
                    } else {
                        pass_step = false;
                    }
                    previous_number = current_number;
                }
            } else {
                if (new_symbol == '+' || new_symbol == '-' || new_symbol == '*' || new_symbol == '/') {
                    if (stack_length - 2 >= 0) {
                        if (new_symbol == '+') {
                            result_number = stack[stack_length - 2] + stack[stack_length - 1];
                        }
                        if (new_symbol == '-') {
                            result_number = stack[stack_length - 2] - stack[stack_length - 1];
                        }
                        if (new_symbol == '*') {
                            result_number = stack[stack_length - 2] * stack[stack_length - 1];
                        }
                        if (new_symbol == '/') {
                            result_number = stack[stack_length - 2] / stack[stack_length - 1];
                        }
                        stack[stack_length - 2] = result_number;
                        --stack_length;
                    }
                }
                if (new_symbol == '\n' || (new_symbol == ' ' && start_digit_detected)) {
                    if (start_digit_detected) {
                        if (!pass_step) {
                            roman_sum += previous_number;
                        }
                        stack[stack_length] = roman_sum;
                        ++stack_length;
                        roman_sum = 0;
                        pass_step = false;
                        start_digit_detected = false;
                    }
                    if (new_symbol == '\n') {
                        output_file << " = ";
                        if (stack_length - 1 >= 0) {
                            if (1 > stack[stack_length - 1] || stack[stack_length - 1] > 3999) {
                                output_file << "ERR";
                            } else {
                                std::sprintf(arabic_number, "%d", stack[stack_length - 1]);
                                arabic_number_length = 0;
                                while (stack[stack_length - 1] != 0) {
                                    ++arabic_number_length;
                                    stack[stack_length - 1] /= 10;
                                }
                                conversion_to_roman_number(arabic_number, arabic_number_length, roman_number,
                                                           roman_number_length);
                                roman_number[roman_number_length] = '\0';
                                output_file << roman_number;
                                roman_number_length = 0;
                                stack_length = 0;
                            }
                        }
                    }
                }
            }
            output_file << new_symbol;
        }
        if (stack_length > 0) {
            output_file << " = ";
            if (1 > stack[stack_length - 1] || stack[stack_length - 1] > 3999) {
                output_file << "ERR";
            } else {
                std::sprintf(arabic_number, "%d", stack[stack_length - 1]);
                stack_number_length = 0;
                while (stack[stack_length - 1] != 0) {
                    ++stack_number_length;
                    stack[stack_length - 1] /= 10;
                }
                conversion_to_roman_number(arabic_number, stack_number_length, roman_number,
                                           roman_number_length);
                roman_number[roman_number_length] = '\0';
                output_file << roman_number;
            }
        }
    }
    input_file.close();
    output_file.close();
    return 0;
}