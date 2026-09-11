#include <iostream>
#include <limits>

#include "lab01/matrix_ops.hpp"

int main() {
    int** matrix = nullptr;
    std::size_t rows = 0;
    std::size_t cols = 0;
    bool has_matrix = false;

    bool running = true;

    while (running) {
        std::cout
            << "\n1. Создать матрицу\n"
            << "2. Заполнить значением\n"
            << "3. Напечатать\n"
            << "4. Алгоритм варианта\n"
            << "0. Выход\n"
            << "Выберите пункт: ";

        int choice{};

        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                std::cout << "\nВвод завершен\n";
                break;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Ошибка: введите номер пункта меню\n";
            continue;
        }

        switch (choice) {
            case 1: {
                long long input_rows{};
                long long input_cols{};

                while (true) {
                    std::cout << "Введите кол-во строк и столбцов: ";

                    if (!(std::cin >> input_rows >> input_cols)) {
                        if (std::cin.eof()) {
                            running = false;
                            break;
                        }

                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::cout << "Неверный ввод\n";
                        continue;
                    }

                    if (input_rows < 0 || input_cols < 0) {
                        std::cout << "Размеры должны быть неотрицательными\n";
                        continue;
                    }

                    break;
                }

                if (!running) {
                    break;
                }

                const std::size_t new_rows{static_cast<std::size_t>(input_rows)};
                const std::size_t new_cols{static_cast<std::size_t>(input_cols)};

                int** new_matrix = lab01::matrix_create(new_rows, new_cols);

                lab01::matrix_delete(matrix, rows);
                matrix = nullptr;

                matrix = new_matrix;
                rows = new_rows;
                cols = new_cols;
                has_matrix = true;

                std::cout << "Создана матрица " << rows << " на " << cols << '\n';

                break;
            }

            case 2: {
                if (!has_matrix) {
                    std::cout << "Матрица еще не создана\n";
                    break;
                }

                int value{};
                while (true) {
                    std::cout << "Введите значение: ";

                    if (!(std::cin >> value)) {
                        if (std::cin.eof()) {
                            running = false;
                            break;
                        }

                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::cout << "Неверный ввод\n";
                        continue;
                    }

                    break;
                }

                if (!running) {
                    break;
                }

                lab01::matrix_fill(matrix, rows, cols, value);

                lab01::matrix_print(matrix, rows, cols);

                break;
            }

            case 3:
                if (!has_matrix) {
                    std::cout << "Матрица еще не создана\n";
                    break;
                }

                std::cout << "Матрица " << rows << " на " << cols << ":\n";
                lab01::matrix_print(matrix, rows, cols);

                break;

            case 4: {
                if (!has_matrix) {
                    std::cout << "Матрица еще не создана\n";
                    break;
                }

                int** transposed = lab01::matrix_transpose(matrix, rows, cols);

                std::cout << "Транспонированная матрица " << cols << " на " << rows << ":\n";
                lab01::matrix_print(transposed, cols, rows);

                lab01::matrix_delete(transposed, cols);
                transposed = nullptr;

                break;
            }

            case 0:
                running = false;
                break;

            default:
                std::cout << "Неизвестный пункт меню\n";
                break;
        }
    }

    lab01::matrix_delete(matrix, rows);
    matrix = nullptr;

    return 0;
}
