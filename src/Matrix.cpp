#include <Matrix.h>
#include <helper.h>
/*
   Constructor to create a matrix according
   to the provided dimensions and fill it
   with random numbers in the range
   between 0-10;
 */
Matrix::Matrix(int row, int col): row_size(row), column_size(col) {

	matrix2D.resize(row_size);
	int size = matrix2D.size();

	for (int i = 0; i < size; ++i) {
		matrix2D[i].resize(column_size);
		for (int j = 0; j < column_size; ++j) {
			matrix2D[i][j] = (rand() % 10);
		}
	}
}

/*
   default constructor to create a matrix wit
   32x32 dimensions filled with all zeros;
 */
Matrix::Matrix(): row_size(32), column_size(32) {

	matrix2D.resize(row_size);
	int size = matrix2D.size();
	for (int i = 0; i < size; ++i) {
		matrix2D[i].resize(column_size, 0);

	}
}

/*
   The function checks  the correspondence of the
   dimensions for provided matrix and initialize
   the internal member matrix2D of an object;
 */
void Matrix::setMatrix2D(const std::vector<std::vector<int>>& matrix)
{
	assert(this->row_size == matrix.size());
	assert(this->column_size == matrix[0].size());
	this->matrix2D = matrix;
}

const std::vector<std::vector<int>>& Matrix::getMatrix2D() const
{
	return matrix2D;
}

// The matrix multiplication operator is overloaded
Matrix Matrix::operator*(const Matrix& m) const
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

// Matrix attribution operator overloaded
Matrix& Matrix::operator=(const Matrix& m)
{

	if (&m == this) {
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

/*
   Perform covolution operation on the member
   matrix with the provided kernel matrix and
   retrun a result 2D matrix;
 */
Matrix Matrix::doCNN(const Matrix& filter)
{
	int filter_size = filter.getRowSize();
	int r_sz = getRowSize();
	int c_sz = getColumnSize();

	if (filter_size > r_sz || filter_size > c_sz) {

		help();
	}
	Matrix cnn_matrix((r_sz - filter_size + 1), (c_sz - filter_size + 1));
	Matrix block(filter_size, filter_size);

	for (int i = 0; i <= (r_sz - filter_size); ++i) {
		for (int j = 0; j <= (c_sz - filter_size); ++j) {
			if (getBlockAt(block, i, j, filter_size) != -1) {
				cnn_matrix.matrix2D[i][j] = dotProduct(filter, block);
			}
		}
	}
	return cnn_matrix;
}

/*
   gets the function as a parameter from two matrices,
   multiplies the matrices and calculates the sum of
   the multiplied elements;
 */
int Matrix::dotProduct(const Matrix& first_mat, const Matrix& second_mat)
{
	Matrix product = first_mat * second_mat;
	int dotProduct = 0;
	int r_sz = product.getRowSize();
	int c_sz = product.getColumnSize();
	for (int i = 0; i < r_sz; ++i) {
		for (int j = 0; j < c_sz; ++j) {
			dotProduct += product.matrix2D[i][j];
		}
	}
	return dotProduct;
}

/*
   The size of the matrix is checked in the function and,
   if the next step does not exceed the size of the matrix,
   it assigns the elements of the matrix starting from the
   mentioned point;
 */
int Matrix::getBlockAt(Matrix& block, int row, int col, int size)
{
	if ((row + size > getRowSize()) || (col + size > getColumnSize())) {
		return -1;
	}
	for (int i = row; i < row + size; ++i) {
		for (int j = col; j < col + size; ++j) {
			block.matrix2D[i - row][j - col] = matrix2D[i][j];
		}
	}

	return 0;
}

void Matrix::print()
{
	for (int i = 0; i < row_size; ++i) {
		for (int j = 0; j < column_size; ++j) {
			std::cout << std::setw(3) << matrix2D[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
