#include "matrix.h"

void Matrix::allocateMemory(){

    array = new int32_t*[number_of_rows];
    for(int32_t row_index = 0; row_index < number_of_rows; row_index++)
        array[row_index] = new int32_t[number_of_columns];
}

void Matrix::freeMemory() const{

    if(array == nullptr)
        return;

    for(int32_t row_index = 0; row_index < number_of_rows; row_index++)
        delete [] array[row_index];

    delete [] array;
}

Matrix::Matrix() :
    number_of_rows(0),
    number_of_columns(0),
    array(nullptr){

    std::cout<<"Matrix()"<<std::endl;
}

Matrix::Matrix(int32_t rows, int32_t columns) :
    number_of_rows(rows),
    number_of_columns(columns),
    array(nullptr){

    std::cout<<"Matrix(args)"<<std::endl;
    allocateMemory();
}

Matrix::Matrix(const Matrix& matrix){

    std::cout<<"Copy Matrix()"<<std::endl;
    this->number_of_rows = matrix.numberOfRows();
    this->number_of_columns = matrix.numberOfColumns();

    this->allocateMemory();

    for(int32_t index_of_row = 0; index_of_row < this->number_of_rows; index_of_row++){
        for(int32_t index_of_column = 0; index_of_column < this->number_of_columns; index_of_column++){
            array[index_of_row][index_of_column] = matrix.get(index_of_row,index_of_column);
        }
    }
}

Matrix::~Matrix(){

    std::cout<<"~Matrix()"<<std::endl;
    freeMemory();
}


Matrix& Matrix::operator=(const Matrix& matrix){

    std::cout<<"Assignment operator"<<std::endl;

    if(this == &matrix)
        return *this;

    if(matrix.numberOfRows() != this->number_of_rows || matrix.numberOfColumns() != this->number_of_columns){
        // Here must be an exeption
        throw 1;
    }
    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            this->array[row_index][column_index] = matrix.get(row_index,column_index);
        }
    }

    return *this;

}

Matrix Matrix::operator+(const Matrix &matrix){

    if(matrix.numberOfRows() != this->number_of_rows || matrix.numberOfColumns() != this->number_of_columns){
        throw 1;
    }

    Matrix temp_matrix(number_of_rows,number_of_columns);
    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){

            int32_t temp_value = this->array[row_index][column_index] +  matrix.get(row_index,column_index);
            temp_matrix.set(row_index,column_index,temp_value);
        }
    }

    return temp_matrix;
}

Matrix &Matrix::operator+=(const Matrix &matrix){

    *this = *this+matrix;
    return *this;
}

Matrix Matrix::operator-(const Matrix &matrix){

    if(matrix.numberOfRows() != this->number_of_rows || matrix.numberOfColumns() != this->number_of_columns){
        throw 1;
    }

    Matrix temp_matrix(number_of_rows,number_of_columns);
    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            int32_t temp_value = this->array[row_index][column_index] -  matrix.get(row_index,column_index);
            temp_matrix.set(row_index,column_index,temp_value);
        }
    }

    return temp_matrix;
}

Matrix &Matrix::operator-=(const Matrix &matrix){

    *this =  *this - matrix;
    return *this;
}

Matrix Matrix::operator*(const Matrix &matrix){

    if(this->number_of_columns != matrix.numberOfRows() ){
        throw 2;
    }

    Matrix temp_matrix(this->number_of_rows,matrix.numberOfColumns());

    for(int32_t row_index = 0; row_index < this->number_of_rows; row_index++){
        for(int32_t col_index = 0; col_index < matrix.numberOfColumns(); col_index++){
            int32_t temp_value = 0;
            for(int32_t index = 0; index < matrix.numberOfColumns(); index++){
                temp_value += this->array[row_index][index] * matrix.get(index,col_index);
            }
            temp_matrix.set(row_index,col_index,temp_value);
        }
    }
    return temp_matrix;
}

void Matrix::operator*=(const Matrix &matrix){

    *this = ( (*this) * matrix);
}

Matrix Matrix::operator*(const int32_t scalar){

    Matrix temp_matrix(this->number_of_rows,this->number_of_columns);

    for(int32_t row_index = 0; row_index < this->number_of_rows; row_index++){
        for(int32_t col_index = 0; col_index < this->number_of_columns; col_index++){
            int32_t temp_value = this->array[row_index][col_index] * scalar;
            temp_matrix.set(row_index,col_index,temp_value);
        }
    }

    return temp_matrix;
}

bool Matrix::operator==(const Matrix &matrix) const{

    if(matrix.numberOfRows() != this->number_of_rows || matrix.numberOfColumns() != this->number_of_columns)
        return false;

    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            if(this->array[row_index][column_index] != matrix.get(row_index,column_index))
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &matrix) const{

    if(*this == matrix)
        return false;
    return true;
}

std::ostream& operator<<(std::ostream &out, const Matrix &matrix){

    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            out<<matrix.get(row_index,column_index)<<" ";
        }
        out<<std::endl;
    }
    out<<std::endl;

    return out;
}

void Matrix::set(int32_t row_index, int32_t column_index, int32_t value){

    array[row_index][column_index] = value;
}

int32_t Matrix::get(int32_t row_index, int32_t column_index) const{

    return array[row_index][column_index];
}

int32_t Matrix::numberOfRows() const{

    return number_of_rows;
}

int32_t Matrix::numberOfColumns() const{

    return number_of_columns;
}


void fillMatrixByRandom(Matrix &matrix){

    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            matrix.set(row_index,column_index,std::rand()%10);
        }
    }
}

void printMatrix(const Matrix &matrix){

    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            std::cout<<matrix.get(row_index,column_index)<<" ";
        }
        std::cout<<std::endl;
    }
}
