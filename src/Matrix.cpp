#include <Matrix.h>

void Matrix::print()
{
    std::cout << "Called print finction" << std::endl;
    for (int i = 0; i < row_size; ++i) {
        for (int j = 0; j < column_size; ++j) {
            std::cout << std::setw(3) << matrix2D[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::operator*(const Matrix& m)
{
    if (column_size == m.getRowSize()) {
        Matrix product(row_size, m.getColumnSize());
        for (int i = 0; i < row_size; ++i) {
            for (int j = 0; j < column_size; ++j) {
                int sum = 0;
                for (int c = 0; c < column_size; ++c) {
                    sum += matrix2D[i][c] * m.matrix2D[c][j];
                }
                product.matrix2D[i][j] = sum;
            }
        }
        return product;
    } else {
        std::cout << "incorrect matrices dimensions" << std::endl;
        exit (1);
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{

    if(&m == this) {
        return *this;
    }

    row_size = m.getRowSize();
    column_size = m.getColumnSize();
    matrix2D.resize(row_size);
    for (int i = 0; i < row_size; i++)
    {
        matrix2D[i].resize(column_size, 0);
    }
    matrix2D = m.matrix2D;

    return *this;
}

int Matrix::dotProduct()
{
    Matrix m, m1;

    Matrix result = m * m1;
    int dotProduct = 0;
    for (int i = 0; i < result.getRowSize(); ++i) {
        for (int j = 0; j < result.getColumnSize(); ++j) {
            dotProduct += result.matrix2D[i][j];
        }
    }
    return dotProduct;
}

Matrix doCNN(const Mtarix& filter)
{

}
