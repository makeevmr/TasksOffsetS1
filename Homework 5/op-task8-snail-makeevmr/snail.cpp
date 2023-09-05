#include <iostream>

void snail_matrix_filler(int **matrix, int *space_array, int rows, int columns) {
    bool right = true;
    bool down = false;
    bool left = false;
    bool up = false;
    int columns_to_pass = columns;
    int rows_to_pass = rows;
    int steps = columns_to_pass;
    int current_step = 0;
    int current_row_index = 0;
    int current_column_index = -1;
    int current_number_length = 1;
    int current_max_number = 10;
    bool last_down_left_corner = false;
    bool last_up_right_corner = false;
    int last_max_number = current_max_number;
    int last_corner_number = 1;
    int last_column_index = current_column_index;
    int last_corner_length = 1;
    for (int j = 1; j <= rows * columns; ++j) {
        if (j == current_max_number) {
            current_max_number *= 10;
            ++current_number_length;
        }
        ++current_step;
        if (right) {
            current_column_index += 1;
        }
        if (down) {
            current_row_index += 1;
        }
        if (left) {
            current_column_index -= 1;
        }
        if (up) {
            current_row_index -= 1;
        }
        matrix[current_row_index][current_column_index] = j;
        if (current_step == steps) {
            if (right) {
                right = false;
                down = true;
                current_step = 0;
                --rows_to_pass;
                steps = rows_to_pass;
            } else if (down) {
                down = false;
                left = true;
                current_step = 0;
                --columns_to_pass;
                steps = columns_to_pass;
                space_array[current_column_index] = current_number_length;
                last_down_left_corner = true;
                last_up_right_corner = false;
                last_corner_number = j;
                last_max_number = current_max_number;
                last_column_index = current_column_index;
                last_corner_length = current_number_length;
            } else if (left) {
                left = false;
                up = true;
                current_step = 0;
                --rows_to_pass;
                steps = rows_to_pass;
            } else if (up) {
                up = false;
                right = true;
                current_step = 0;
                --columns_to_pass;
                steps = columns_to_pass;
                space_array[current_column_index] = current_number_length;
                last_down_left_corner = false;
                last_up_right_corner = true;
                last_corner_number = j;
                last_max_number = current_max_number;
                last_column_index = current_column_index;
                last_corner_length = current_number_length;
            }
        }
    }
    if (last_down_left_corner) {
        --last_column_index;
        while (space_array[last_column_index] == 0) {
            ++last_corner_number;
            if (last_corner_number < last_max_number) {
                space_array[last_column_index] = last_corner_length;
            } else {
                last_max_number *= 10;
                ++last_corner_length;
                space_array[last_column_index] = last_corner_length;
            }
            --last_column_index;
            if (last_column_index < 0) {
                break;
            }
        }
    } else if (last_up_right_corner) {
        ++last_column_index;
        while (space_array[last_column_index] == 0) {
            ++last_corner_number;
            if (last_corner_number < last_max_number) {
                space_array[last_column_index] = last_corner_length;
            } else {
                last_max_number *= 10;
                ++last_corner_length;
                space_array[last_column_index] = last_corner_length;
            }
            ++last_column_index;
            if (last_column_index >= columns) {
                break;
            }
        }
    }
}

int main() {
    int rows;
    int columns;
    int current_number_length;
    std::cin >> rows;
    std::cin >> columns;
    int **matrix = new int *[rows];
    int *space_array = new int[columns];
    for (size_t i = 0; i < columns; ++i) {
        space_array[i] = 0;
    }
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[columns];
    }
    snail_matrix_filler(matrix, space_array, rows, columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            current_number_length = 0;
            int number_copy = matrix[i][j];
            while (number_copy > 0) {
                ++current_number_length;
                number_copy /= 10;
            }
            for (int k = 0; k < space_array[j] - current_number_length; ++k) {
                std::cout << ' ';
            }
            std::cout << matrix[i][j];
            if (j < columns - 1) {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] space_array;
    return 0;
}