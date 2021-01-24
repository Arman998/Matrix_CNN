#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>

class Matrix
{
    public:
        Matrix(int row, int col): m_rowSize(row), m_colSize(col) {
            srand(time(nullptr));
            m_mat2D.resize(m_rowSize);
            int size = m_mat2D.size();
            for (int i = 0; i < size; i++)
            {
                m_mat2D[i].resize(m_colSize);
                for (int j = 0; j < m_colSize; ++j) {
                    m_mat2D[i][j] = (rand() % 10);
                }
            }
            std::cout << "Created Matrix object" << std::endl;
        }
        // operator *(Matrix &);
        // Matrix& dotProduct();
        void print();

    private:
        std::vector<std::vector<int>> m_mat2D;
        int m_rowSize;
        int m_colSize;
};
/*
class Matrix3D
{
    public:
        Matrix3D();
        operator * (Matrix3D &);
    private:
        std::vector<Matrix> mat3D;
        unsigned int depth;
}
*/
