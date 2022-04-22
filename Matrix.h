// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <fstream>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/*
 * Matrix class
 */
class Matrix
{
    /*
     * left multiplication of scalar by matrix
     * @param c scalar
     * @param another_matrix matrix o be calculated
     * @return product matrix
     */
    friend Matrix operator*(float c, const Matrix &another_matrix);
    /*
     * insert operation for printing image of matrix
     * @param os the output stream
     * @param matrix the matrix to print
     * @return reference to the stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    /*
     * rea from file operation for getting image of matrix
     * @param is the input stream
     * @param matrix the matrix to get image to
     * @return reference to the stream
     */
    friend std::istream &read_binary_file(std::istream &is,
                                          const Matrix &matrix);

private:
    int num_of_rows;
    int num_of_cols;

public:
    float *matrix_data;
    /*
     * matrix constructor
     * @param rows number of rows in new matrix
     * @param cols number of cls in new matrix
     */
    Matrix(int rows, int cols);
    /*
     * default matrix constructor
     */
    Matrix();
    /*
     * copy constructor
     */
    Matrix(const Matrix &source_matrix);
    /*
     * destructor
     */
    ~Matrix();
    /*
     * getter function for rows
     */
    int get_rows() const;
    /*
     * getter function for columns
     */
    int get_cols() const;
    /*
     * transpose matrix function
     * @return reference to this matrix to transpose
     */
    Matrix &transpose();
    /*
     * transform matrix to a vector
     * @return vectorized this matrix
     */
    Matrix &vectorize();
    /*
     * function that prints all elements in matrix
     */
    void plain_print() const;
    /*
     * function that multiplies elements in 2 matrices element-wise
     * @param another_matrix the second matrix to dot with the this matrix
     */
    Matrix dot(const Matrix &another_matrix) const;
    /*
     * function that calculates the euclidean norm of the matrix
     */
    float norm() const;
    /*
     * plus operator that adds elements in 2 matrices element-wise
     * @param another_matrix the second matrix to plus to the this matrix
     */
    Matrix operator+(const Matrix &another_matrix) const;
    /*
     * assignment operator that assigns matrix to the this matrix
     * @param another_matrix the matrix to assign
     * @return a reference to he this matrix that was assigned
     */
    Matrix &operator=(const Matrix &another_matrix);
    /*
     * matrix multiplication as in linear algebra
     * @param another_matrix a matrix to be multiplied to the right with the
     * this matrix
     * @return product matrix
     */
    Matrix operator*(const Matrix &another_matrix) const;
    /*
     * right multiplication of scalar by matrix
     * @param c scalar
     * @return product matrix
     */
    Matrix operator*(float c) const;
    /*
     * plus assign operator that adds elements in 2 matrices element-wise
     * and assigns the this matrix to the added matrix - self with a new one
     * @param another_matrix the second matrix to plus to the this matrix
     * @return a reference to the this transformed matrix
     */
    Matrix &operator+=(const Matrix &another_matrix);
    /*
     * parenthesis function that gets the (i,j) value of the matrix
     * @param i number of row
     * @param j number of col
     * @return the float value in the matrix
     */
    float &operator()(int i, int j) const;
    /*
     * square parenthesis function that gets the i value of the matrix
     * @param i index number
     * @return the float value in the matrix
     */
    float &operator[](int i) const;
};

#endif //MATRIX_H
