#include <iostream>
#include <fstream>

bool files_opened(std::ifstream &input_file, std::ofstream &output_file) {
    if (input_file && output_file) {
        return true;
    }
    throw "File opening error";
}

void dec_to_hex(unsigned int decimal_number, char *hex_line_number) {
    int str_index = 8;
    while (decimal_number > 0) {
        unsigned int remainder = decimal_number % 16;
        if (remainder <= 9) {
            hex_line_number[str_index] = static_cast<char>(remainder + '0');
        }
        else {
            hex_line_number[str_index] = static_cast<char>('A' + remainder - 10);
        }
        --str_index;
        decimal_number /= 16;
    }
}

int main(int argc, char *argv[]) {
    int buffer_index;
    int row_length;
    int row_number = -1;
    unsigned char buffer[16];
    char hex_line_number[] = "0000000000";
    const int symbols_in_row = 16;
    std::ifstream input_file(argv[1], std::ios::binary | std::ios::in);
    std::ofstream output_file(argv[2]);
    try {
        files_opened(input_file, output_file);
    }
    catch (const char *error) {
        std::cout << error << std::endl;
    }
    while (input_file.peek() != EOF) {
        ++row_number;
        dec_to_hex(row_number, hex_line_number);
        output_file << hex_line_number << ": ";
        row_length = 0;
        for (size_t i = 0; i < symbols_in_row; ++i) {
            if (input_file.peek() != EOF) {
                buffer[row_length] = static_cast<unsigned char>(input_file.get());
                ++row_length;
            }
            else {
                break;
            }
        }
        buffer_index = 0;
        while (buffer_index < row_length) {
            int new_symbol = static_cast<int>(buffer[buffer_index]);
            if (new_symbol < 16) {
                output_file << '0';
            }
            output_file << std::uppercase << std::hex << new_symbol;
            output_file << " ";
            if (buffer_index == 7) {
                output_file << "| ";
            }
            ++buffer_index;
        }
        if (input_file.peek() == EOF) {
            if ((buffer_index - 1) < 7) {
                for (int i = 0; i < 3 * (8 - buffer_index); ++i) {
                    output_file << ' ';
                }
                output_file << "| ";
                buffer_index = 8;
            }
            for (int i = 0; i < 3 * (symbols_in_row - buffer_index); ++i) {
                output_file << ' ';
            }
        }
        output_file << ' ';
        buffer_index = 0;
        while (buffer_index < row_length) {
            if (buffer[buffer_index] < ' ') {
                output_file << '.';
            }
            else {
                output_file << buffer[buffer_index];
            }
            ++buffer_index;
        }
        if (input_file.peek() != EOF) {
            output_file << '\n';
        }
    }
    input_file.close();
    output_file.close();
    return 0;
}