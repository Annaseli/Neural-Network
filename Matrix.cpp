//
// Created by anna_seli on 13/06/2021.
//
#include "Matrix.h"

#define ALLOC_FAILURE "can't allocate matrix"
#define INVALID_ROW_OR_COLS "invalid number of rows and cols"
#define INVALID_FILE "can't read entire file"
#define INVALID_DIM_1 "matrix dimensions less then 1"
#define INVALID_DIM_2 "matrix dimensions doesn't match"
#define INVALID_DIM_3 "matrix dimensions aren't the same"
#define INVALID_INDEX_1 "indices not in range"
#define INVALID_INDEX_2 "index not in range"
#define EXIT_FAILURE 1

/*
  * matrix constructor
  * @param rows number of rows in new matrix
  * @param cols number of cls in new matrix
  */
Matrix::Matrix(int rows, int cols)
    : num_of_rows(rows), num_of_cols(cols)
{
    if ((rows < 1) || (cols < 1))
    {
        std::cerr << INVALID_ROW_OR_COLS << std::endl;
        exit(EXIT_FAILURE);
    }
    int size = rows * cols;
    matrix_data = new float[size];
    if (!matrix_data)
    {
        std::cerr << ALLOC_FAILURE << std::endl;
        exit(EXIT_FAILURE);
    }
    // initializing all elements to 0.
    for (int i = 0; i < size; i++)
    {
        matrix_data[i] = 0.0;
    }
}

/*
* default matrix constructor
*/
Matrix::Matrix()
    : Matrix(1, 1){}

/*
* copy constructor
*/
Matrix::Matrix(const Matrix &source_matrix)
    : num_of_rows(source_matrix.num_of_rows),
    num_of_cols(source_matrix.num_of_cols)
{
    // allocate new matrix
    matrix_data = new float[num_of_rows * num_of_cols];
    if (!matrix_data)
    {
        std::cerr << ALLOC_FAILURE << std::endl;
        exit(EXIT_FAILURE);
    }
    // copy elements from source matrix
    for (auto i = 0; i < num_of_rows * num_of_cols; i++)
    {
        matrix_data[i] = source_matrix.matrix_data[i];
    }
}

/*
 * destructor
 */
Matrix::~Matrix()
{
    delete [] matrix_data;
    matrix_data = nullptr;
}

/*
 * getter function for rows
 */
int Matrix::get_rows() const
{
    return num_of_rows;
}

/*
  * getter function for columns
  */
int Matrix::get_cols() const
{
    return num_of_cols;
}

/*
  * transpose matrix function
  * @return reference to this matrix to transpose
  */
Matrix& Matrix::transpose()
{
    // copy old matrix
    Matrix copy_matrix = Matrix(*this);
    // change rows and cols of current matrix
    int temp_rows = num_of_rows;
    num_of_rows = num_of_cols;
    num_of_cols = temp_rows;
    for (auto i = 0; i < num_of_rows; i++)
    {
        for (auto j = 0; j < num_of_cols; j++)
        {
            matrix_data[i * num_of_cols + j] = copy_matrix.matrix_data
                    [j * num_of_rows + i];
        }
    }
    return *this;
}

/*
  * transform matrix to a vector
  * @return vectorized this matrix
  */
Matrix &Matrix::vectorize()
{
    num_of_rows = num_of_rows * num_of_cols;
    num_of_cols = 1;
    return *this;
}

/*
  * function that prints all elements in matrix
  */
void Matrix::plain_print() const
{
    for (auto i = 0; i < num_of_rows; i++)
    {
        for (auto j = 0; j < num_of_cols; j++)
        {
            std::cout << matrix_data[i * num_of_cols + j] << " " << std::endl;
        }
    }
}

/*
  * function that multiplies elements in 2 matrices element-wise
  * @param another_matrix the second matrix to dot with the this matrix
  */
Matrix Matrix::dot(const Matrix &another_matrix) const
{
    Matrix new_matrix (num_of_rows, num_of_cols);
    for (auto i = 0; i < num_of_rows * num_of_cols; i++)
    {
        new_matrix.matrix_data[i] = matrix_data[i] *
                another_matrix.matrix_data[i];
    }
    return new_matrix;
}

/*
 * function that calculates the euclidean norm of the matrix
 */
float Matrix::norm() const
{
    float sum = 0;
    for (auto i = 0; i < num_of_rows; i++)
    {
        for (auto j = 0; j < num_of_cols; j++)
        {
            sum += std::pow(matrix_data[i * num_of_cols + j], 2);
        }
    }
    return std::sqrt(sum);
}

/*
  * rea from file operation for getting image of matrix
  * @param is the input stream
  * @param matrix the matrix to get image to
  * @return reference to the stream
  */
std::istream &read_binary_file(std::istream &is, const Matrix &matrix)
{
    if (!is)
    {
        std::cerr << INVALID_FILE << std::endl;
        exit(EXIT_FAILURE);
    }
    unsigned long length = matrix.num_of_rows * matrix.num_of_cols *
            sizeof(float);
    is.read((char *) (matrix.matrix_data), length);
    return is;
}

/*
 * plus operator that adds elements in 2 matrices element-wise
 * @param another_matrix the second matrix to plus to the this matrix
 */
Matrix Matrix::operator+(const Matrix &another_matrix) const
{
    if ((num_of_rows != another_matrix.num_of_rows) || (num_of_cols != another_matrix.num_of_cols))
    {
        std::cerr << INVALID_DIM_3 << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix new_matrix (num_of_rows, num_of_cols);
    for (auto i = 0; i < num_of_rows * num_of_cols; i++)
    {
        new_matrix.matrix_data[i] = matrix_data[i] +
                another_matrix.matrix_data[i];
    }
    return new_matrix;
}

/*
  * assignment operator that assigns matrix to the this matrix
  * @param another_matrix the matrix to assign
  * @return a reference to he this matrix that was assigned
  */
Matrix& Matrix::operator=(const Matrix &another_matrix)
{
    if (this == &another_matrix)
    {
        return *this;
    }
    num_of_rows = another_matrix.num_of_rows;
    num_of_cols = another_matrix.num_of_cols;
    delete [] matrix_data;
    int size = num_of_rows * num_of_cols;
    matrix_data = new float[size];
    for (auto i = 0; i < size; i++)
    {
        matrix_data[i] = another_matrix.matrix_data[i];
    }
    return *this;
}

/*
  * matrix multiplication as in linear algebra
  * @param another_matrix a matrix to be multiplied to the right with the
  * this matrix
  * @return product matrix
  */
Matrix Matrix::operator*(const Matrix &another_matrix) const
{

    if (num_of_cols != another_matrix.num_of_rows)
    {
        std::cerr << INVALID_DIM_2 << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix new_matrix (num_of_rows, another_matrix.num_of_cols);
    for (auto i = 0; i < num_of_rows; i++)
    {
        for (auto j = 0; j < another_matrix.num_of_cols; j++)
        {
            float sum = 0;
            for (auto k = 0; k < num_of_cols; k++)
            {
                float a = matrix_data[i * num_of_cols + k];
                float b = another_matrix.matrix_data
                        [k * another_matrix.num_of_cols + j];
                sum += (a * b);
            }
            new_matrix.matrix_data[i * another_matrix.num_of_cols + j] = sum;
        }
    }
    return new_matrix;
}

/*
  * right multiplication of scalar by matrix
  * @param c scalar
  * @return product matrix
  */
Matrix Matrix::operator*(float c) const
{
    Matrix new_matrix (num_of_rows, num_of_cols);
    int size = num_of_rows * num_of_cols;
    for (auto i = 0; i < size; i++)
    {
        new_matrix.matrix_data[i] = matrix_data[i] * c;
    }
    return new_matrix;
}

/*
  * left multiplication of scalar by matrix
  * @param c scalar
  * @param another_matrix matrix o be calculated
  * @return product matrix
  */
Matrix operator*(float c, const Matrix &another_matrix)
{
    //return this->operator*(another_matrix, c);
    Matrix new_matrix (another_matrix.num_of_rows, another_matrix.num_of_cols);
    int size = another_matrix.num_of_rows * another_matrix.num_of_cols;
    for (auto i = 0; i < size; i++)
    {
        new_matrix.matrix_data[i] = c * another_matrix.matrix_data[i];
    }
    return new_matrix;
}

/*
 * plus assign operator that adds elements in 2 matrices element-wise
 * and assigns the this matrix to the added matrix - self with a new one
 * @param another_matrix the second matrix to plus to the this matrix
 * @return a reference to the this transformed matrix
 */
Matrix &Matrix::operator+=(const Matrix &another_matrix)
{
    *this = *this + another_matrix;
    return *this;
}

/*
  * parenthesis function that gets the (i,j) value of the matrix
  * @param i number of row
  * @param j number of col
  * @return the float value in the matrix
  */
float &Matrix::operator()(int i, int j) const
{
    if ((i < 0) || (j < 0) || (i >= num_of_rows) || (j >= num_of_cols))
    {
        std::cerr << INVALID_INDEX_1 << std::endl;
        exit(EXIT_FAILURE);
    }
    return matrix_data[i * num_of_cols + j];
}

/*
  * square parenthesis function that gets the i value of the matrix
  * @param i index number
  * @return the float value in the matrix
  */
float &Matrix::operator[](int i) const
{
    if ((i < 0) || (i >= num_of_rows * num_of_cols))
    {
        std::cerr << INVALID_INDEX_2 << std::endl;
        exit(EXIT_FAILURE);
    }
    return matrix_data[i];
}

/*
  * insert operation for printing image of matrix
  * @param os the output stream
  * @param matrix the matrix to print
  * @return reference to the stream
  */
std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    for (auto i = 0; i < matrix.num_of_rows; i++)
    {
        for (auto j = 0; j < matrix.num_of_cols; j++)
        {
            if (matrix.matrix_data[i * matrix.num_of_cols + j] >= 0.1)
            {
                os << "  " << std::endl;
            }
            else
            {
                os << "**" << std::endl;
            }
        }
        os << std::endl;
    }
    return os;
}