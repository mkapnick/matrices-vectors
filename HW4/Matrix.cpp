//
//  Matrix.cpp
//  HW3
//
//  Created by Michael Kapnick on 2/4/14.
//  Copyright (c) 2014 Michael Kapnick. All rights reserved.
//

#include <iostream>
#include "Matrix.h"


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
Matrix::Matrix(int rows, int columns)
{
    setSize(rows, columns);
    allocateMemory();
    setValues(0.0);
    
}

/**
 * A copy constructor.
 *
 * Note: A copy constructor is critical because without one we can't
 * pass a Matrix by value (which requires that it be possible to
 * make a copy).
 *
 * @param original  The Matrix to copy
 */
Matrix::Matrix(const Matrix& original)
{
    setSize(original.rows, original.columns);
    allocateMemory();
    setValues(original.values);
    
    
}

/**
 * Destructor
 */
Matrix::~Matrix()
{
    deallocateMemory();
}

/**
 * Allocates memory for a Matrix instance
 */

void Matrix::allocateMemory()
{
    this -> values = new double *[this->rows];
    
    for(int i =0; i < this->rows; i++)
    {
        this->values[i] = new double[this->columns];
    }
}

/**
 * Deallocates memory for a Matrix instance
 *
 */

void Matrix::deallocateMemory()
{
    for (int i =0; i < this->rows; i++)
    {
        delete [] this->values[i];
        this->values[i] = NULL;
    }
    delete [] this -> values;
    this -> values = NULL;
}

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
double det(const Matrix& a)
{
    
    double determinant = 0;
    double largerDeterminant = 0;
    
    if (a.rows == 2)
    {
        
        int ad;
        int bc;
        
        ad = a.get(0,0) * a.get(1,1);
        bc = a.get(0,1) * a.get(1,0);
        
        determinant = (ad - bc);
        return determinant;
    }
    else
    {
        for(int c =0; c < a.columns; c++)
        {
            largerDeterminant += cof(a, 1,c+1);
            //printf("largerDeterminant is: %f\n", largerDeterminant);
        }
    }
    
    return largerDeterminant;
}
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
double cof(const Matrix& a, int i, int j)
{
    double sign, determinant;
    
    determinant = minor(a, i, j);
    //printf ("\ndeterminant is: %f \n", determinant);
    
    sign = 1;
    
    if( (i + j) % 2 != 0)
        sign = -1;
    
    //printf("Returning %f\n", (a.values[i-1][j-1] * sign) * determinant);
    return determinant * (sign * a.values[i-1][j-1]);
}


/**
 * Calculate a particular minor for a square matrix (i.e., the
 * determinant of the matrix with row i and column j removed)
 *
 * @param a   The matrix (which must be square)
 * @param i   The index of the row to exclude
 * @param j   The index of the column to exclude
 * @return    The minor
 */
double minor(const Matrix& a, int i, int j)
{
    double determinant;
    
    Matrix subMatrix = submatrix(a,i,j);
    determinant = det(subMatrix);
    return determinant;
}

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
Matrix submatrix(const Matrix& a, int i, int j)
{
    Matrix subMatrix = Matrix(a.rows - 1, a.columns - 1);
    
    i-=1;
    j-=1;
    
    bool cancelRow      = false;
    bool cancelColumn   = false;
    
    for (int r =0; r < a.rows; r++)
    {
        if(r != i)
        {
            for(int c =0; c < a.columns; c++)
            {
                if(c != j)
                {
                    if(cancelColumn)
                    {
                        if(cancelRow)
                            subMatrix.values[r-1][c-1] = a.get(r,c);
                        else
                            subMatrix.values[r][c-1] = a.get(r,c);
                    }
                    else
                    {
                        if(cancelRow)
                            subMatrix.values[r-1][c] = a.get(r,c);
                        else
                        {
                            subMatrix.values[r][c] = a.get(r,c);
                        }
                    }
                }
                else
                {
                    cancelColumn = true;
                }
            }
            cancelColumn = false;
        }
        else
        {
            cancelRow = true;
        }
    }
    return subMatrix;
}





/**
 * Get a particular element of this Matrix.
 *
 * @param r   The row index
 * @param c   The column index
 * @throws    out_of_range if r or c are out of bounds
 * @return    The value of the element
 */
double Matrix::get(int r, int c) const
{
    if(r < this -> rows && c < this -> columns)
    {
        return this->values[r][c];
    }
    else
        throw out_of_range("Index out of range");
}

/**
 * Get the number of columns in this Matrix
 *
 * @return  The number of columns
 */
int Matrix::getColumns() const
{
    return this -> columns;
}

/**
 * Get the number of rows in this Matrix
 *
 * @return  The number of rows
 */
int Matrix::getRows() const
{
    return this -> rows;
}

/**
 * Gets the size of the matrix
 *
 * @return rows * columns
 */

int Matrix::getSize() const
{
    return this->rows * this -> columns;
}

/**
 * Create and return an identity matrix
 *
 * Note: This function must return by value because the result Matrix
 * is a local variable.
 *
 * @param  size   The number of rows == columns in the (square) matrix
 * @throws length_error If size parameter is less than or equal to 0
 * @return        An identity Matrix
 */
Matrix identity(int size)
{
    
    
    
    if(size > 0)
    {
        Matrix identity = Matrix(size, size);
        for(int r =0; r < size; r++)
        {
            for(int c =0; c < size; c++)
            {
                if(r==c)
                    identity.values[r][c] = 1;
                else
                    identity.values[r][c] = 0;
            }
        }
        return identity;
    }
    
    else
        throw length_error("Size must be >= 0");
    
}


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

Matrix multiply(const Vector& a, const Vector& b)
{
    Matrix matrix = Matrix(1,1);
    
    if(a.getSize() == b.getSize() && a.getOrientation() != b.getOrientation())
    {
        for (int i =0; i < a.getSize(); i++)
        {
            matrix.values[0][0] += a.get(i) * b.get(i);
        }
    }
    else
        throw length_error("Sizes of vector don't match up");
    
    return matrix;
    
}

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
double& Matrix::operator()(int r, int c)
{
    r-=1;
    c-=1;
    
    if(r < this->rows && c < this->columns)
    {
        double& ref = this->values[r][c];
        return ref;
    }
    else
        throw out_of_range("Out of range error");
}

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

Matrix& Matrix::operator=(std::initializer_list<double> values)
{
    const double *  start;
    int             size, rowCount, columnCount, rows, columns;
    
    start       = values.begin();
    size        = (int)values.size();
    rows        = this->getRows();
    columns     = this->getColumns();
    rowCount    = 0;
    columnCount = 0;
    
    for (int i =0; i < rows * columns; i ++)
    {
        if(columnCount == columns)
        {
            rowCount++;
            columnCount = 0;
        }
        this->values[rowCount][columnCount] = *start;
        start++;
        columnCount++;
    }
    
    return *this;
}

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

Matrix& Matrix::operator=(const Matrix& other)
{
    this->setSize(other.rows, other.columns);
    allocateMemory();
    this->setValues(other.values);
    
    return *this;
}

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
Matrix operator+(const Matrix& a, const Matrix& b)
{
    Matrix m = Matrix(a.getRows(), a.getColumns());
    
    if(a.rows == b.rows && a.columns == b.columns)
    {
        int rowIndex = 0;
        
        while (rowIndex < a.getRows())
        {
            for (int columnIndex =0; columnIndex < a.columns; columnIndex++)
            {
                m.values[rowIndex][columnIndex] = a.values[rowIndex][columnIndex] + b.values[rowIndex][columnIndex];
            }
            rowIndex++;
        }
    }
    else
        throw length_error("Rows and Columns not the same");
    
    return m;
}

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

Matrix operator-(const Matrix& a, const Matrix& b)
{
    Matrix m = Matrix(a.getRows(), a.getColumns());
    
    if(a.rows == b.rows && a.columns == b.columns)
    {
        int rowIndex = 0;
        
        while (rowIndex < a.getRows())
        {
            for (int columnIndex =0; columnIndex < a.columns; columnIndex++)
            {
                m.values[rowIndex][columnIndex] = a.values[rowIndex][columnIndex] - b.values[rowIndex][columnIndex];
            }
            rowIndex++;
        }
    }
    else
        throw length_error("Rows and columns not the same");
    
    return m;
}

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
Matrix operator*(const Matrix& a, const Matrix& b)
{
    Matrix m = Matrix(b.getRows(), a.getColumns());
    
    int aRow    = 0;
    int bRow    = 0;
    int mRow    = 0;
    int aColumn = 0;
    int mColumn = 0;
    
    int counter =0;
    
    if(b.getColumns() == a.getRows())
    {
        while (counter < b.getRows() * a.getColumns())
        {
            for(int bColumn = 0; bColumn < b.getColumns(); bColumn++)
            {
                m.values[mRow][mColumn] += b.values[bRow][bColumn] * a.values[aRow][aColumn];
                aRow++;
            }
            
            counter++;
            aRow = 0;
            
            if(mColumn == a.getColumns() - 1)
            {
                mRow++;
                bRow++;
                aColumn = 0;
                mColumn = 0;
            }
            else
            {
                mColumn++;
                aColumn++;
            }
        }
    }
    
    else
        throw length_error("Row and columns not the same");
    
    return m;
}

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
 * @throw     length_error if sizes are incompatible
 * @return    The resulting Vector
 */

Vector operator*(const Vector& v, const Matrix& m)
{
    
    int vectorColumnIndex   = 0;
    int counter             = 0;
    int value               = 0;
    
    Vector vector = Vector(m.getColumns());
    
    if(v.getSize() == m.getColumns())
    {
        while (counter < m.getRows() - 1)
        {
            for (int row = 0; row < m.getRows(); row++)
            {
                value += v.get(vectorColumnIndex) * m.values[row][counter];
                vectorColumnIndex++;
            }
            
            vectorColumnIndex = 0;
            vector.set(counter, value);
            value = 0;
            counter++;
        }
    }
    else
        throw length_error("Rows and Columns not same size");
    
    return vector;
}

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

Vector operator*(const Matrix& m, const Vector& v)
{
    return v * m;
}

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
Matrix operator*(double k, const Matrix& a)
{
    Matrix result = Matrix(a.rows, a.columns);
    
    for (int r =0; r < a.rows; r ++)
    {
        for(int c=0; c< a.columns; c++)
        {
            result.values[r][c] = a.values[r][c] * k;
        }
    }
    return result;
}


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
Matrix operator*(const Matrix& a, double k)
{
    return k * a;
}

/**
 * Compare two matrices to see if they have identical elements
 * (within a given TOLERANCE for each element)
 *
 * @param a   The first matrix
 * @param b   The second matrix
 * @throws    length_error if the shapes of a and b do not conform
 * @return    true or false
 */
bool operator==(const Matrix& a, const Matrix& b)
{
    bool equals = true;
    
    if(a.rows == b.rows && a.columns == b.columns)
    {
        for(int r =0; r < a.rows && equals; r++)
        {
            for(int c =0; c < a.columns && equals; c++)
            {
                if (a.values[r][c] != b.values[r][c])
                    equals = false;
            }
        }
    }
    else
        throw length_error("Length error");
    
    return equals;
}

/**
 * Compare two matrices to see if they have different elements
 * (beyond a given TOLERANCE)
 *
 * @param a   The first matrix
 * @param b   The second matrix
 * @throws    length_error if the shapes of a and b do not conform
 * @return    true or false
 */
bool operator!=(const Matrix& a, const Matrix& b)
{
    return !(a==b);
}

/**
 *
 *
 *
 */
void Matrix::set(int r, int c, int value)
{
    r-=1;
    c-=1;
    if (r < this->getRows() && c < this->getColumns())
    {
        this->values[r][c] = value;
    }
}


/**
 * Sets the size of a matrix
 *
 * @param rows the number of rows in the matrix
 * @param columns the number of columns in the matrix
 */
void Matrix::setSize(int rows, int columns)
{
    this->rows      = rows;
    this->columns   = columns;
}

/**
 * Set each element in values to be
 * value
 *
 * @param value Set each index in the matrix
 *        to this value
 *
 */
void Matrix::setValues(double value)
{
    for (int r =0; r < this->getRows(); r++)
    {
        for(int c =0; c< this->getColumns(); c++)
        {
            this->values[r][c] = value;
        }
    }
}

/**
 * Fills up the matrix to whatever array
 * values is pointing to.. If n values is
 * smaller than the nxn matrix, not sure what to
 * to do
 *
 * @param values The array of doubles to enter
 * in the matrix
 *
 */
void Matrix::setValues(const double* values)
{
    for (int r=0; r < this->getRows(); r++)
    {
        for(int c=0; c< this->getColumns(); c++)
        {
            this->values[r][c] = *values;
            values++;
        }
    }
}

/**
 * Sets the values of a matrix
 * to the values of another
 * matrix
 *
 * @param values The matrix of new values
 */
void Matrix::setValues(double** values)
{
    for(int r =0; r < this->getRows(); r++)
    {
        for(int c=0; c < this->getColumns(); c++)
        {
            this->values[r][c] = values[r][c];
        }
    }
}

/**
 * Create and return a transposed version of a given matrix.
 *
 * Note: This function must return by value because the result Matrix
 * is a local variable.
 *
 * @param a   The original Matrix
 * @return    The transpose of a
 */
Matrix trans(const Matrix& a)
{
    //switch rows and columns
    Matrix result = Matrix(a.columns, a.rows);
    
    for (int r =0; r < result.getRows(); r++)
    {
        for(int c =0; c < result.getColumns(); c++)
        {
            result.values[r][c] = a.values[c][r];
        }
    }
    
    return result;
}




