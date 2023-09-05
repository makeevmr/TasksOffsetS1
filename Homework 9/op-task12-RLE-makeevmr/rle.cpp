#include <iostream>
#include <fstream>
#include <cstring>

bool files_opened(std::ifstream &input_file, std::ofstream &output_file) {
    if (input_file && output_file) {
        return true;
    }
    throw "File opening error";
}

void fill_non_repeating_characters(std::ofstream &output_file, signed char *non_repeating_characters,
                                   int &current_array_size,
                                   signed char &current_char_length) {
    output_file << current_char_length;
    for (size_t i = 0; i < current_array_size; ++i) {
        output_file << non_repeating_characters[i];
    }
    current_array_size = 0;
}

void coded_file(std::ifstream &input_file, std::ofstream &output_file) {
    bool first_character_defined = false;
    bool last_output_block = false;
    signed char current_symbol = 'a';
    signed char previous_symbol = 'a';
    signed char current_char_length = 0;
    signed char last_output_block_symbol;
    const int array_size = 128;
    int current_array_size = 0;
    signed char non_repeating_characters[array_size];
    while (input_file.peek() != EOF) {
        current_symbol = static_cast<signed char>(input_file.get());
        if (first_character_defined) {
            if (current_char_length >= 0 && current_symbol == previous_symbol) {
                if (current_char_length < 127) {
                    ++current_char_length;
                } else {
                    output_file << current_char_length << previous_symbol;
                    current_char_length = 0;
                    last_output_block = true;
                    last_output_block_symbol = previous_symbol;
                }
            }
            if (current_char_length <= 0 && current_symbol != previous_symbol) {
                if (current_array_size < array_size) {
                    non_repeating_characters[current_array_size] = previous_symbol;
                    ++current_array_size;
                    --current_char_length;
                } else {
                    fill_non_repeating_characters(output_file, non_repeating_characters, current_array_size,
                                                  current_char_length);
                    non_repeating_characters[0] = previous_symbol;
                    current_array_size = 1;
                    current_char_length = -1;
                    last_output_block = false;
                }
            }
            if (current_char_length < 0 && current_symbol == previous_symbol) {
                if (current_char_length == -1 && last_output_block && last_output_block_symbol == non_repeating_characters[0]) {
                    current_char_length = 0;
                    output_file << current_char_length << non_repeating_characters[0];
                } else {
                    fill_non_repeating_characters(output_file, non_repeating_characters, current_array_size,
                                                  current_char_length);
                }
                current_array_size = 0;
                current_char_length = 1;
                last_output_block = false;
            }
            if (current_char_length > 0 && current_symbol != previous_symbol) {
                output_file << current_char_length << previous_symbol;
                current_char_length = 0;
                last_output_block = true;
                last_output_block_symbol = previous_symbol;
            }
        } else {
            first_character_defined = true;
            current_char_length = 0;
        }
        if (input_file.peek() != EOF) {
            previous_symbol = current_symbol;
        }
    }
    if (current_char_length > 0) {
        output_file << current_char_length << current_symbol;
    } else {
        if (current_char_length == -1 && last_output_block && last_output_block_symbol == non_repeating_characters[0]) {
            current_char_length = 0;
            output_file << current_char_length << non_repeating_characters[0];
        } else if (current_array_size < array_size) {
            non_repeating_characters[current_array_size] = current_symbol;
            ++current_array_size;
            --current_char_length;
            fill_non_repeating_characters(output_file, non_repeating_characters, current_array_size,
                                          current_char_length);
        } else {
            fill_non_repeating_characters(output_file, non_repeating_characters, current_array_size,
                                          current_char_length);
            current_char_length = -1;
            output_file << current_char_length << current_symbol;
        }
    }
}

void decoded_file(std::ifstream &input_file, std::ofstream &output_file) {
    bool positive_length;
    signed char current_symbol;
    int block_length;
    while (input_file.peek() != EOF) {
        current_symbol = static_cast<signed char>(input_file.get());
        block_length = static_cast<unsigned char>(current_symbol);
        if (block_length > 127) {
            block_length -= 256;
        }
        if (block_length >= 0) {
            ++block_length;
            positive_length = true;
        } else {
            positive_length = false;
        }
        block_length = std::abs(block_length);
        if (positive_length) {
            current_symbol = static_cast<signed char>(input_file.get());
            for (int i = 0; i < block_length; ++i) {
                output_file << current_symbol;
            }
        } else {
            for (int i = 0; i < block_length; ++i) {
                current_symbol = static_cast<signed char>(input_file.get());
                output_file << current_symbol;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    std::ifstream input_file(argv[2], std::ios::binary | std::ios::in);
    std::ofstream output_file(argv[3], std::ios::binary);
    try {
        files_opened(input_file, output_file);
    } catch (const char *error) {
        std::cout << error << std::endl;
    }
    if (strcmp(argv[1], "-e") == 0) {
        coded_file(input_file, output_file);
    }
    if (strcmp(argv[1], "-d") == 0) {
        decoded_file(input_file, output_file);
    }
    input_file.close();
    output_file.close();
    return 0;
}