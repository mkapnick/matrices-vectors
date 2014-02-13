//
//  Matrix.h
//  HW3
//
//  Created by Michael Kapnick on 2/4/14.
//  Copyright (c) 2014 Michael Kapnick. All rights reserved.
//

#ifndef HW4_Matrix_h
#define HW4_Matrix_h


#define TOLERANCE   0.0001

#include <cmath>
#include <initializer_list>
#include <math.h>
#include <stdexcept>
#include "Vector.h"
using namespace std;

/**
 * An encapsulation of a Matrix
 */
class Matrix
{
protected:
    double**  values;
    int       columns, rows;
    
    void allocateMemory();
    void deallocateMemory();
    void setSize(int rows, int columns);
    void setValues(double value);
    void setValues(const double* values);
    void setValues(double** values);
    
public:
    
    /**
     * A constructor that does not allow for initial values (i.e., that
     * initializes all elements to 0.0).  The Matrix must be initialized
     * with the assignment operator.
     *
     * Example of use:
     *
     *   Matrix y(3,3);
     *
     * @param rows     The number of rows
     * @param columns  The number of columns
     */
    Matrix(int rows, int columns);
    
    /**
     * A copy constructor.
     *
     * Note: A copy constructor is critical because without one we can't
     * pass a Matrix by value (which requires that it be possible to
     * make a copy).
     *
     * @param original  The Matrix to copy
     */
    Matrix(const Matrix& original);
    
    /**
     * Construct a Matrix from a Vector
     *
     * The resulting Matrix will be eithe nx1 or 1xn depending
     * on the orientation of the Vector
     *
     * @param v  The Vector to "copy"
     */
    Matrix(const Vector& v);
    
    
    /**
     * Destructor
     */
    ~Matrix();
    
    /**
     * Calculate the cofactor of a square matrix
     * (i.e., the signed determinate of the matrix with row
     * i and column j removed)
     *
     * @param a   The matrix (which must be square)
     * @param i   The index of the row to exclude
     * @param j   The index of the column to exclude
     * @throws    length_error if the Matrix isn't square
     * @throws    out_of_range if i or j are out of bounds
     * @return    The cofactor
     */
    friend double cof(const Matrix& a, int i, int j);
    
    /**
     * Calculate the determinant of a square matrix
     *
     * Note: This implementation is not efficient since it
     * explicitly creates each of the minors. However, it is easy to understand.
     *
     * @param a   The matrix (which must be square)
     * @throws    length_error if the Matrix is smaller than 2x2
     * @throws    length_error if the Matrix isn't square
     * @return    The value of the determinant
     */
    friend double det(const Matrix& a);
    
    /**
     * Get a particular element of this Matrix.
     *
     * @param r   The row index
     * @param c   The column index
     * @throws    out_of_range if r or c are out of bounds
     * @return    The value of the element
     */
    double get(int r, int c) const;
    
    /**
     * Gets the size of the matrix
     *
     * @return rows * columns
     */
    
    int getSize() const;
    
    /**
     * Get the number of columns in this Matrix
     *
     * @return  The number of columns
     */
    int getColumns() const;
    
    /**
     * Get the number of rows in this Matrix
     *
     * @return  The number of rows
     */
    int getRows() const;
    
    
    /**
     * Multiply a row Vector and a Matrix
     *
     * Note: This method must return by value because the result Vector
     * is a local variable.
     *
     * It is worth noting that, if this method returned a Matrix rather
     * than a Vector, it could be implemented as return (Matrix(v) * m);
     *
     * @param v   The row Vector
     * @param m   The Matrix
     * @return    The resulting Vector
     */
    friend Vector operator*(const Vector& v, const Matrix& m);
    
    /**
     * Create and return an identity matrix
     *
     * Note: This function must return by value because the result Matrix
     * is a local variable.
     *
     * @param  size   The number of rows == columns in the (square) matrix
     * @return        An identity Matrix
     */
    friend Matrix identity(int size);
    
    /**
     * Calculate a particular minor for a square matrix (i.e., the
     * determinant of the matrix with row i and column j removed)
     *
     * @param a   The matrix (which must be square)
     * @param i   The index of the row to exclude
     * @param j   The index of the column to exclude
     * @return    The minor
     */
    friend double minor(const Matrix& a, int i, int j);
    
    /**
     * Multiply a column Vector and a row Vector
     *
     * Note: We can't overload the * operator for this purpose
     * because it is already overloaded in the Vector class for the
     * dot/inner product
     *
     * @param a   The column Vector
     * @param b   The row Vector
     * @throws    length_error if the shapes of a and b do not conform
     * @return    The Matrix resulting from multiplying a and b
     */
    friend Matrix multiply(const Vector& a, const Vector& b);
    
    /**
     * Access an element of this Matrix using the function-call operator.
     *
     * Note: This method returns by reference so that this operator
     * can be used on the left side of the assignment operator. Though this
     * can be dangerous in general (since the value being referred to
     * may not always exist), in this case it shouldn't cause any
     * problems.
     *
     * Examples of use:
     *
     *     d = y(1,1);
     *     y(2,3) = 5.0;
     *
     * @param r   The row index
     * @param c   The column index
     * @throws    out_of_range if r or c are out of bounds
     * @return    The value of the element
     */
    double& operator()(int r, int c);
    
    /**
     * Assign an initializer_list to this Matrix.
     *
     * Example of use:
     *
     *   y = {1, 2, 3,
     *        4, 5, 6,
     *        7, 8, 9};
     *
     * Note: This method is not void so that one can write x = y = {1, 2}
     * (which first assigns {1, 2} to y and then assigns the result of
     * that assignment to x).  It returns the result by reference because
     * there is no concern that this will not refer to something.
     *
     * @param m   The initializer_list containing the values
     * @return    The Matrix referred to by this
     */
    Matrix& operator=(std::initializer_list<double> values);
    
    /**
     * Assign another Matrix to this Matrix.
     *
     * Note: This method is not void so that one can write x = y = z
     * (which first assigns z to y and then assigns the result of that
     * assignment to x). It returns the result by reference because there
     * is no concern that this will not refer to something.
     *
     * @param other   The Matrix to copy
     * @return        The Matrix referred to by this
     */
    Matrix& operator=(const Matrix& other);
    
    /**
     * Add the Matrix a and the Matrix b
     *
     * Note: This method must return by value because the result Matrix
     * is a local variable.
     *
     * @param a   One Matrix
     * @param b   The other Matrix
     * @throws    length_error if the shapes of a and b do not conform
     * @return    a+b
     */
    friend Matrix operator+(const Matrix& a, const Matrix& b);
    
    /**
     * Subtract the Matrix b from the Matrix a (component by component)
     *
     * Note: This method must return by value because the result Matrix
     * is a local variable.
     *
     * @param a   One Matrix
     * @param b   The other Matrix
     * @throws    length_error if the shapes of a and b do not conform
     * @return    a-b
     */
    friend Matrix operator-(const Matrix& a, const Matrix& b);
    
    /**
     * Multiply two matrices
     *
     * Note: This method must return by value because the result Matrix
     * is a local variable.
     *
     * @param a   The first matrix (m x n)
     * @param b   The second matrix (n x s)
     * @throws    length_error if the shapes of a and b do not conform
     * @return    The resulting matrix (m x s)
     */
    friend Matrix operator*(const Matrix& a, const Matrix& b);
    
    
    /**
     * Multiply a Matrix and a column Vector
     *
     * Note: This method must return by value because the result Matrix
     * is a local variable.
     *
     * It is worth noting that, if this method returned a Matrix rather
     * than a Vector, it could be implemented as return return (m * Matrix(v));
     *
     * @param m   The Matrix
     * @param v   The column Vector
     * @return    The resulting Matrix
     */
    friend Vector operator*(const Matrix& m, const Vector& v);
    
    /**
     * Multiply a scalar and a matrix
     *
     * Note: This method must return by value because the result Matrix
     * is a local variable.
     *
     * @param k   The scalar
     * @param a   The matrix
     * @return    The resulting matrix
     */
    friend Matrix operator*(double k, const Matrix& a);
    
    /**
     * Multiply a matrix and a scalar
     *
     * Note: This method must return by value because the result Matrix
     * is a local variable.
     *
     * @param a   The matrix
     * @param k   The scalar
     * @return    The resulting matrix
     */
    friend Matrix operator*(const Matrix& a, double k);
    
    /**
     * Compare two matrices to see if they have identical elements
     * (within a given TOLERANCE for each element)
     *
     * @param a   The first matrix
     * @param b   The second matrix
     * @throws    length_error if the shapes of a and b do not conform
     * @return    true or false
     */
    friend bool operator==(const Matrix& a, const Matrix& b);
    
    /**
     * Compare two matrices to see if they have different elements
     * (beyond a given TOLERANCE)
     *
     * @param a   The first matrix
     * @param b   The second matrix
     * @throws    length_error if the shapes of a and b do not conform
     * @return    true or false
     */
    friend bool operator!=(const Matrix& a, const Matrix& b);
    
    /**
     * Set a value to a particular row/column
     * index in the matrix
     *
     * @param r     The row index
     * @param c     The column index
     * @param value Value to set at index r and c
     */
    void set(int r, int c, int value);
    /**
     * Remove a row and column from a matrix
     *
     * @param a   The matrix (which must be square)
     * @param i   The index of the row to exclude
     * @param j   The index of the col to exclude
     * @throws    length_error the Matrix is smaller than 2x2
     * @throws    length_error if the shapes of a and b do not conform
     * @throws    out_of_range if i or j are out of bounds
     * @return    The submatrix (i.e., a with row i and column j excluded)
     */
    friend Matrix submatrix(const Matrix& a, int i, int j);
    
    /**
     * Create and return a transposed version of a given matrix.
     *
     * Note: This function must return by value because the result Matrix
     * is a local variable.
     *
     * @param a   The original Matrix
     * @return    The transpose of a
     */
    friend Matrix trans(const Matrix& a);
    
};


double cof(const Matrix& a, int i, int j);
double det(const Matrix& a);
Matrix identity(int size);
double minor(const Matrix& a, int i, int j);
Matrix multiply(const Vector& a, const Vector& b);
Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, const Matrix& b);
Matrix operator*(double k, const Matrix& a);
Vector operator*(const Vector& v, const Matrix& m);
Vector operator*(const Matrix& m, const Vector& v);
bool   operator==(const Matrix& a, const Matrix& b);
bool   operator!=(const Matrix& a, const Matrix& b);
Matrix submatrix(const Matrix& a, int i, int j);
Matrix trans(const Matrix& a);


#endif

