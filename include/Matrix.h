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
        Matrix(){}
        Matrix(int row, int col): row_size(row), column_size(col) {

            matrix2D.resize(row_size);
            int size = matrix2D.size();

            for (int i = 0; i < size; i++)
            {
                matrix2D[i].resize(column_size);
                for (int j = 0; j < column_size; ++j) {
                    matrix2D[i][j] = (rand() % 10);
                }
            }
            std::cout << "Created Matrix object" << std::endl;
        }

        inline int getRowSize() const {
            return row_size;
        }

        inline int getColumnSize() const {
            return column_size;
        }

        ~Matrix(){}
        Matrix operator*(const Matrix&);
        Matrix& operator=(const Matrix&);
        void print();
        std::vector<std::vector<int>> matrix2D;

    private:
        int row_size;
        int column_size;
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
