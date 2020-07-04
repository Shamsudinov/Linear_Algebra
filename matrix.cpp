#include "matrix.h"

void Matrix::allocateMemory(){

    array = new int32_t*[number_of_rows];
    for(int32_t row_index = 0; row_index < number_of_rows; row_index++)
        array[row_index] = new int32_t[number_of_columns];
}

void Matrix::freeMemory() const{

    for(int32_t row_index = 0; row_index < number_of_rows; row_index++)
        delete [] array[row_index];

    delete [] array;
}

Matrix::Matrix() :
    number_of_rows(3),
    number_of_columns(3){

    std::cout<<"Matrix()"<<std::endl;
    allocateMemory();
}

Matrix::Matrix(int32_t rows, int32_t columns) :
    number_of_rows(rows),
    number_of_columns(columns){

    std::cout<<"Matrix(args)"<<std::endl;
    allocateMemory();
}

Matrix::Matrix(const Matrix& matrix){

    std::cout<<"Copy Matrix()"<<std::endl;
    this->number_of_rows = matrix.numberOfRows();
    this->number_of_columns = matrix.numberOfColumns();
    //    std::cout<<"number_of_rows="<<number_of_rows<<std::endl;
    //    std::cout<<"number_of_columns="<<number_of_columns<<std::endl;
    this->allocateMemory();

    for(int32_t index_of_row = 0; index_of_row < this->number_of_rows; index_of_row++){
        for(int32_t index_of_column = 0; index_of_column < this->number_of_columns; index_of_column++){
            int32_t temp = matrix.get(index_of_row,index_of_column);
            array[index_of_row][index_of_column] = temp;
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
    }
    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            this->array[row_index][column_index] = matrix.get(row_index,column_index);
        }
    }

    return *this;

}

bool Matrix::operator==(const Matrix &matrix){
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

void Matrix::set(int32_t row_index, int32_t column_index, int32_t value){

    array[row_index][column_index] = value;
}

int32_t Matrix::get(int32_t row_index, int32_t column_index) const
{
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

void printMatrix(Matrix &matrix){

    for(int32_t row_index = 0; row_index < matrix.numberOfRows(); row_index++){
        for(int32_t column_index = 0; column_index < matrix.numberOfColumns(); column_index++){
            std::cout<<matrix.get(row_index,column_index)<<" ";
        }
        std::cout<<std::endl;
    }
}
