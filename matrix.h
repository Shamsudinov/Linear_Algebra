#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix{
    int32_t number_of_rows;
    int32_t number_of_columns;
    int32_t **array = nullptr;

    void allocateMemory();
    void freeMemory() const;

public:
    Matrix();
    Matrix(int32_t number_of_rows, int32_t columns);
    Matrix(const Matrix&matrix);
    ~Matrix();

    Matrix &operator=(const Matrix& matrix);
    bool operator==(const Matrix &matrix);

    void set(int32_t row_index, int32_t column_index, int32_t value);
    int32_t get(int32_t row_index, int32_t column_index) const;

    int32_t numberOfRows() const;
    int32_t numberOfColumns() const;
};

#endif // MATRIX_H

void fillMatrixByRandom(Matrix &matrix);
void printMatrix(Matrix &matrix);
