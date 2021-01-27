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
        Matrix();
        Matrix(int row, int col);
        inline int getRowSize() const {
            return row_size;
        }

        inline int getColumnSize() const {
            return column_size;
        }

        ~Matrix(){}
        Matrix operator*(const Matrix&) const;
        Matrix& operator=(const Matrix&);
        int dotProduct(const Matrix&, const Matrix&);
        void print();
        int getBlockAt(Matrix& block, int row, int col , int size);
        Matrix doCNN(const Matrix& filter);

    public:
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
