#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <json.h>

class Matrix
{
    public:
        Matrix();
        Matrix(int row, int col);

        ~Matrix() = default;

        inline int getRowSize() const {
            return row_size;
        }

        inline int getColumnSize() const {
            return column_size;
        }

        Matrix operator*(const Matrix&) const;
        Matrix& operator=(const Matrix&);

        Matrix doCNN(const Matrix& filter);
        int dotProduct(const Matrix&, const Matrix&);
        int getBlockAt(Matrix& block, int row, int col , int size);
        void print();

    public:
        std::vector<std::vector<int>> matrix2D;

    private:
        int row_size;
        int column_size;
};
