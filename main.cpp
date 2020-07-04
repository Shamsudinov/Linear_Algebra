#include <matrix.h>
using namespace std;

int main(){

    int x;


    Matrix first(5,5);
    fillMatrixByRandom(first);
    printMatrix(first);

    Matrix m_copy = first;
    printMatrix(m_copy);



}

