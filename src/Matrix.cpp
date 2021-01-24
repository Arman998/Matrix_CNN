#include <Matrix.h>

void Matrix::print()
{
    std::cout << "Called print finction" << std::endl;
    for (int i = 0; i < m_rowSize; ++i) {
        for (int j = 0; j < m_colSize; ++j) {
            std::cout << std::setw(3) << m_mat2D[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


