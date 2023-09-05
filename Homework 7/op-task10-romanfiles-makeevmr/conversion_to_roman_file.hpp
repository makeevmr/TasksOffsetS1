#ifndef OFFSET_TASKS_CONVERSION_TO_ROMAN_FILE_H
#define OFFSET_TASKS_CONVERSION_TO_ROMAN_FILE_H

#include <fstream>

void conversion_to_roman_number(const char *arabic_number, int &arabic_number_length, char *roman_number, int &roman_number_length) {
    const char *roman_characters[] = {"I", "IV", "V", "IX", "X",
                                      "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    for (int i = 1; i <= arabic_number_length; ++i) {
        int category = 4 * (arabic_number_length - i);
        if (arabic_number[i - 1] < '4') {
            for (int j = 0; j < arabic_number[i - 1] - '0'; ++j) {
                roman_number[roman_number_length] = roman_characters[category][0];
                ++roman_number_length;
            }
        }
        if (arabic_number[i - 1] == '4') {
            roman_number[roman_number_length] = roman_characters[category + 1][0];
            roman_number[roman_number_length + 1] = roman_characters[category + 1][1];
            roman_number_length += 2;
        }
        if ('5' <= arabic_number[i - 1] && arabic_number[i - 1] < '9') {
            roman_number[roman_number_length] = roman_characters[category + 2][0];
            ++roman_number_length;
            for (int j = 0; j < arabic_number[i - 1] - '5'; ++j) {
                roman_number[roman_number_length] = roman_characters[category][0];
                ++roman_number_length;
            }
        }
        if (arabic_number[i - 1] == '9') {
            roman_number[roman_number_length] = roman_characters[category + 3][0];
            roman_number[roman_number_length + 1] = roman_characters[category + 3][1];
            roman_number_length += 2;
        }
    }
}

void conversion_to_roman_file(const char *input_file_name, const char *output_file_name) {
    std::ifstream input_file(input_file_name);
    std::ofstream output_file(output_file_name);
    int roman_number_length = 0;
    char roman_number[16];
    int arabic_number_length = 0;
    char arabic_number[5];
    bool number_detection_allowed = true;
    bool start_digit_detected = false;
    bool big_number_detected = false;
    if (input_file && output_file) {
        while (input_file.peek() != EOF) {
            char new_symbol = static_cast<char>(input_file.get());
            if (!start_digit_detected) {
                if (new_symbol < '0' || new_symbol > '9') {
                    number_detection_allowed = new_symbol == '(' || new_symbol == ' ' || new_symbol == '\n';
                    output_file << new_symbol;
                } else {
                    if (number_detection_allowed) {
                        if (new_symbol == '0') {
                            output_file << new_symbol;
                            number_detection_allowed = false;
                        } else {
                            start_digit_detected = true;
                            arabic_number[arabic_number_length] = new_symbol;
                            ++arabic_number_length;
                        }
                    } else {
                        output_file << new_symbol;
                    }
                }
            } else {
                if (new_symbol >= '0' && new_symbol <= '9') {
                    if (arabic_number_length < 4) {
                        if (!big_number_detected) {
                            arabic_number[arabic_number_length] = new_symbol;
                            ++arabic_number_length;
                        } else {
                            output_file << new_symbol;
                        }
                    } else {
                        output_file << arabic_number;
                        output_file << new_symbol;
                        big_number_detected = true;
                        arabic_number_length = 0;
                    }
                } else {
                    if ((new_symbol == '\n' || new_symbol == ')' || new_symbol == ' ' || new_symbol == '-') &&
                        !big_number_detected) {
                        if (arabic_number_length != 4 || arabic_number[0] <= '3') {
                            conversion_to_roman_number(arabic_number, arabic_number_length, roman_number,
                                                       roman_number_length);
                            for (int i = 0; i < roman_number_length; ++i) {
                                output_file << roman_number[i];
                            }
                            roman_number_length = 0;
                        } else {
                            arabic_number[arabic_number_length] = '\0';
                            output_file << arabic_number;
                        }
                    } else if (arabic_number_length <= 4) {
                        for (int i = 0; i < arabic_number_length; ++i) {
                            output_file << arabic_number[i];
                        }
                    }
                    number_detection_allowed = new_symbol == '(' || new_symbol == ' ' || new_symbol == '\n';
                    big_number_detected = false;
                    start_digit_detected = false;
                    arabic_number_length = 0;
                    output_file << new_symbol;
                }
            }
        }
        if (arabic_number_length > 0) {
            if (number_detection_allowed &&
                (arabic_number_length < 4 || arabic_number_length == 4 && arabic_number[0] < '4')) {
                conversion_to_roman_number(arabic_number, arabic_number_length, roman_number, roman_number_length);
                for (int i = 0; i < roman_number_length; ++i) {
                    output_file << roman_number[i];
                }
            } else {
                for (int i = 0; i < arabic_number_length; ++i) {
                    output_file << arabic_number[i];
                }
            }
        }
    }
    input_file.close();
    output_file.close();
}


#endif //OFFSET_TASKS_CONVERSION_TO_ROMAN_FILE_H
