#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <cstring>

bool is_right_triangle_matrix(double **input_matrix, int dimension, double precision) {
    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            if (std::abs(input_matrix[i][j]) > precision) {
                return false;
            }
        }
    }
    return true;
}

bool is_left_triangle_matrix(double **input_matrix, int dimension, double precision) {
    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = i; j < dimension; ++j) {
            if (std::abs(input_matrix[i][j]) > precision) {
                return false;
            }
        }
    }
    return true;
}

void swap_rows(double **input_matrix, int dimension, size_t first_row, size_t second_row) {
    for (size_t i = 0; i < dimension; ++i) {
        std::swap(input_matrix[first_row][i], input_matrix[second_row][i]);
    }
}

void get_dimension(std::ifstream &input_file, int &rows, int &columns) {
    char character;
    char str_number[10];
    int str_number_index = 0;
    do {
        character = static_cast<char>(input_file.get());
        if ('0' <= character && character <= '9') {
            str_number[str_number_index] = character;
            ++str_number_index;
        } else {
            str_number[str_number_index] = '\0';
            if (character == ' ') {
                rows = std::atoi(str_number);
            } else {
                columns = std::atoi(str_number);
            }
            str_number_index = 0;
        }
    } while (character != '\n');
}

void fill_in_matrix(std::ifstream &input_file, double **input_matrix, int columns) {
    char character;
    char str_number[10];
    int str_number_index = 0;
    int current_element = 0;
    while (input_file) {
        character = static_cast<char>(input_file.get());
        if ('0' <= character && character <= '9' || character == '-' || character == '.') {
            str_number[str_number_index] = character;
            ++str_number_index;
        } else {
            if (str_number_index > 0) {
                str_number[str_number_index] = '\0';
                input_matrix[current_element / columns][current_element % columns] = std::atof(str_number);
                str_number_index = 0;
                ++current_element;
            }
        }
    }

}

long double get_matrix_determinant(double **input_matrix, int dimension, double precision) {
    double divider;
    long double determinant = 1;
    if (is_left_triangle_matrix(input_matrix, dimension, precision) ||
        is_right_triangle_matrix(input_matrix, dimension, precision)) {
        for (size_t i = 0; i < dimension; ++i) {
            determinant *= input_matrix[i][i];
        }
        return determinant;
    }
    for (size_t i = 0; i < dimension; ++i) {
        if (std::abs(input_matrix[i][i]) > precision) {
            if (std::abs(input_matrix[i][i] - 1) > precision) {
                divider = input_matrix[i][i];
                determinant *= divider;
                for (size_t j = i; j < dimension; ++j) {
                    if (std::abs(input_matrix[i][j]) > precision) {
                        input_matrix[i][j] /= divider;
                    }
                }
            }
        } else {
            bool found_not_zero_element = false;
            size_t row_to_swap;
            for (size_t j = i + 1; j < dimension; ++j) {
                if (std::abs(input_matrix[j][i]) > precision) {
                    found_not_zero_element = true;
                    row_to_swap = j;
                    break;
                }
            }
            if (!found_not_zero_element) {
                return 0;
            }
            swap_rows(input_matrix, dimension, i, row_to_swap);
            determinant = -determinant;
            divider = input_matrix[i][i];
            determinant *= divider;
            for (size_t j = i; j < dimension; ++j) {
                if (std::abs(input_matrix[i][j]) > precision) {
                    input_matrix[i][j] /= divider;
                }
            }
        }
        double multiplier;
        for (size_t j = i + 1; j < dimension; ++j) {
            if (std::abs(input_matrix[j][i]) > precision) {
                multiplier = input_matrix[j][i];
                for (size_t k = i; k < dimension; ++k) {
                    input_matrix[j][k] -= multiplier * input_matrix[i][k];
                }
            }
        }
    }
    return determinant;
}

void get_inverse_matrix(double **input_matrix, double **inverse_matrix, int dimension, double precision) {
    double divider;
    double multiplier;
    for (size_t i = 0; i < dimension; ++i) {
        if (std::abs(input_matrix[i][i]) > precision) {
            if (std::abs(input_matrix[i][i] - 1) > precision) {
                divider = input_matrix[i][i];
                for (size_t j = i; j < dimension; ++j) {
                    if (std::abs(input_matrix[i][j]) > precision) {
                        input_matrix[i][j] /= divider;
                    }
                }
                for (size_t j = 0; j < dimension; ++j) {
                    inverse_matrix[i][j] /= divider;
                }
            }
        } else {
            size_t row_to_swap = 1;
            for (size_t j = i + 1; j < dimension; ++j) {
                if (std::abs(input_matrix[j][i]) > precision) {
                    row_to_swap = j;
                    break;
                }
            }
            swap_rows(input_matrix, dimension, i, row_to_swap);
            swap_rows(inverse_matrix, dimension, i, row_to_swap);
            divider = input_matrix[i][i];
            for (size_t j = i; j < dimension; ++j) {
                if (std::abs(input_matrix[i][j]) > precision) {
                    input_matrix[i][j] /= divider;
                }
            }
            for (size_t j = 0; j < dimension; ++j) {
                inverse_matrix[i][j] /= divider;
            }
        }
        for (size_t j = i + 1; j < dimension; ++j) {
            if (std::abs(input_matrix[j][i]) > precision) {
                multiplier = input_matrix[j][i];
                for (size_t k = i; k < dimension; ++k) {
                    input_matrix[j][k] -= multiplier * input_matrix[i][k];
                }
                for (size_t k = 0; k < dimension; ++k) {
                    inverse_matrix[j][k] -= multiplier * inverse_matrix[i][k];
                }
            }
        }
    }
    for (int i = dimension - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            multiplier = input_matrix[j][i];
            input_matrix[j][i] -= multiplier;
            for (int k = dimension - 1; k >= 0; --k) {
                inverse_matrix[j][k] -= multiplier * inverse_matrix[i][k];
            }
        }
    }
}


int main(int argc, char *argv[]) {
    int rows = 1;
    int columns = 1;
    const double PRECISION = 0.00001;
    long double determinant;
    double **inverse_matrix;
    double **input_matrix_copy;
    bool inv_matrix_initialized = false;
    bool input_matrix_copy_initialized = false;
    std::ifstream input_file(argv[2]);
    std::ofstream output_file(argv[3]);
    if (input_file.is_open() && output_file.is_open()) {
        get_dimension(input_file, rows, columns);
        double **input_matrix = new double *[rows];
        for (size_t i = 0; i < rows; ++i) {
            input_matrix[i] = new double[columns];
        }
        fill_in_matrix(input_file, input_matrix, columns);
        if (rows != columns) {
            output_file << "error";
        } else {
            if (strcmp(argv[1], "-det") == 0) {
                determinant = get_matrix_determinant(input_matrix, rows, PRECISION);
                output_file << determinant;
            } else {
                input_matrix_copy_initialized = true;
                input_matrix_copy = new double *[rows];
                for (size_t i = 0; i < rows; ++i) {
                    input_matrix_copy[i] = new double[columns];
                }
                for (size_t i = 0; i < rows; ++i) {
                    for (size_t j = 0; j < columns; ++j) {
                        input_matrix_copy[i][j] = input_matrix[i][j];
                    }
                }
                determinant = get_matrix_determinant(input_matrix, rows, PRECISION);
                if (std::abs(determinant) < PRECISION) {
                    output_file << "singular";
                } else {
                    inv_matrix_initialized = true;
                    inverse_matrix = new double *[rows];
                    for (size_t i = 0; i < rows; ++i) {
                        inverse_matrix[i] = new double[columns];
                    }
                    for (size_t i = 0; i < rows; ++i) {
                        for (size_t j = 0; j < columns; ++j) {
                            if (i == j) {
                                inverse_matrix[i][j] = 1;
                            } else {
                                inverse_matrix[i][j] = 0;
                            }
                        }
                    }
                    get_inverse_matrix(input_matrix_copy, inverse_matrix, rows, PRECISION);
                    output_file << rows << ' ' << columns << std::endl;
                    for (size_t i = 0; i < rows; ++i) {
                        for (size_t j = 0; j < columns; ++j) {
                            output_file << inverse_matrix[i][j] << ' ';
                        }
                        output_file << std::endl;
                    }
                }
            }
        }
        if (input_matrix_copy_initialized) {
            for (size_t i = 0; i < rows; ++i) {
                delete[] input_matrix_copy[i];
            }
            delete[] input_matrix_copy;
        }
        if (inv_matrix_initialized) {
            for (size_t i = 0; i < rows; ++i) {
                delete[] inverse_matrix[i];
            }
            delete[] inverse_matrix;
        }
        for (size_t i = 0; i < rows; ++i) {
            delete[] input_matrix[i];
        }
        delete[] input_matrix;
    }
    input_file.close();
    output_file.close();
    return 0;
}