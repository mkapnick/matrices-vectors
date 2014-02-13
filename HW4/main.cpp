//
//  main.cpp
//  HW3
//
//  Created by Michael Kapnick on 2/4/14.
//  Copyright (c) 2014 Michael Kapnick. All rights reserved.
//

#include <iostream>
#include "Matrix.h"


char    fName[80];
char    description[100];

/**
 * Print a Matrix
 *
 * @param m   The Matrix to print
 */
void print(const Matrix& m)
{
    printf("\n");
    printf(" -");
    for (int c=0; c<m.getColumns(); c++) printf("      ");
    printf(" - \n");
    for (int r=0; r<m.getRows(); r++)
    {
        printf("| ");
        for (int c=0; c<m.getColumns(); c++)
        {
            printf(" %5.2f", m.get(r,c));
        }
        printf("  |\n");
    }
    printf(" -");
    for (int c=0; c<m.getColumns(); c++) printf("      ");
    printf(" - \n");
    
}

/**
 * Print out a char array
 *
 * @param arr pointer to char
 */

void printChar(char * arr)
{
    while (*arr != '\0')
    {
        printf("%c",*arr);
        arr++;
    }
}

/**
 * A function that prints out information about the test and the test results
 *
 * @param fName             the method name being tested
 * @param description       the description of the method being tested
 * @param expectedOutput    the expected output from a given method
 * @param actualOutput      the output received after testing the method
 * @param testNumber        current test number for a given method
 */

void helper(char * fName, char * description, Matrix expectedOutput, Matrix actualOutput, int testNumber)
{
    printf("\n");
    printChar(fName);
    printf("\nTest %i\n", testNumber);
    printChar(description);
    
    printf("\n%s", "Expected output:\n");
    print(expectedOutput);
    //printf("%2s%6s%2s\n","| ", expectedOutput.c_str(), " |");
    
    printf("\n%s", "Actual output:\n");
    print(actualOutput);
}

/**
 * A function that prints out information about the test and the test results
 *
 * @param fName             the method name being tested
 * @param description       the description of the method being tested
 * @param expectedOutput    the expected output from a given method
 * @param actualOutput      the output received after testing the method
 * @param testNumber        current test number for a given method
 */

void helper(char * fName, char * description, double expectedOutput, double actualOutput, int testNumber)
{
    printf("\n");
    printChar(fName);
    printf("\nTest %i\n", testNumber);
    printChar(description);
    
    printf("\n%s", "Expected output:\n");
    printf("%2s%2f\n"," ", expectedOutput);
    
    printf("\n%s", "Actual output:\n");
    printf("%2s%2f\n"," ", actualOutput);
}

/**
 * A function that prints out information about the test and the test results
 *
 * @param fName             the method name being tested
 * @param description       the description of the method being tested
 * @param expectedOutput    the expected output from a given method
 * @param actualOutput      the output received after testing the method
 * @param testNumber        current test number for a given method
 */

void helper(char * fName, char * description, string expectedOutput, string actualOutput, int testNumber)
{
    printf("\n");
    printChar(fName);
    printf("\nTest %i\n", testNumber);
    printChar(description);
    
    printf("\n%s", "Expected output:\n");
    printf("\n%2s%6s%2s\n", " -", "      ", "- ");
    printf("%2s%6s%2s\n","| ", expectedOutput.c_str(), " |");
    printf("%2s%6s%2s\n", " -", "      ", "- ");
    
    printf("\n%s", "Actual output:\n");
    printf("\n%2s%6s%2s\n", " -", "      ", "- ");
    printf("%2s%6s%2s\n","| ", actualOutput.c_str(), " |");
    printf("%2s%6s%2s\n", " -", "      ", "- ");
    printf("\n-------------------------------------------------------\n");
}


/*
 * A function that can be used to print a Vector
 *
 * @param v          The Vector to print
 */
void print(const Vector& v)
{
    printf("\n");
    if (v.getOrientation() == Vector::COLUMN)
    {
        printf("%2s%6s%2s\n"," -","     ","- ");
        for (int i=0; i<v.getSize(); i++)
        {
            printf("%2s%6.2f%2s\n","| ", v.get(i), " |");
        }
        printf("%2s%6s%2s\n"," -","     ","- ");
        printf("\n");
    }
    else
    {
        printf("[");
        for (int i=0; i<v.getSize(); i++)
        {
            printf(" %6.2f ", v.get(i));
        }
        printf("]\n");
    }
}

Matrix testConstructor()
{
    strcpy(fName, "Matrix::Matrix(int rows, int columns)");
    strcpy(description,"A constructor that does not allow for initial values (i.e., that initializes all elements to 0.0).  The Matrix must be initialized with the assignment operator");
    
    Matrix matrix  = Matrix(2,2);
    matrix.set(1, 1, 50);
    matrix.set(1, 2, 0);
    matrix.set(2, 1, .98);
    matrix.set(2, 2, -.0101);
    
    Matrix matrix2 = Matrix(matrix);
    helper(fName, description, matrix, matrix2, 1);
    
    matrix = Matrix(3,3);
    matrix.set(1, 1, 1000);
    matrix.set(1, 2, 0);
    matrix.set(1, 3, -90);
    matrix.set(2, 1, -.11909);
    matrix.set(2, 2, .1111);
    matrix.set(2, 3, 1);
    matrix.set(3, 1, -6);
    matrix.set(3, 2, 2);
    matrix.set(3, 3, 4);
    
    matrix2 = Matrix(matrix);
    helper(fName, description, matrix, matrix2, 2);
    
    
    matrix = Matrix(4,4);
    matrix.set(1, 1, 1000);
    matrix.set(1, 2, 0);
    matrix.set(1, 3, -90);
    matrix.set(1, 4, -90);
    matrix.set(2, 1, -.11909);
    matrix.set(2, 2, .1111);
    matrix.set(2, 3, 1);
    matrix.set(2, 4, 0);
    matrix.set(3, 1, -6);
    matrix.set(3, 2, 2);
    matrix.set(3, 3, 4);
    matrix.set(3, 4, -6);
    matrix.set(4, 1, -6);
    matrix.set(4, 2, 2);
    matrix.set(4, 3, 4);
    matrix.set(4, 4, -6);
    
    matrix2 = Matrix(matrix);
    helper(fName, description, matrix, matrix2, 3);
    
    return matrix;
    
}

void testDeterminant()
{
    strcpy(fName, "double det(const Matrix& a)");
    strcpy(description,"Calculate the determinant of a square matrix");
    
    Matrix matrix= Matrix(3,3);
    matrix = Matrix(3,3);
    matrix.set(1, 1, 1000);
    matrix.set(1, 2, 10);
    matrix.set(1, 3, -90);
    matrix.set(2, 1, -1);
    matrix.set(2, 2, 90);
    matrix.set(2, 3, 1);
    matrix.set(3, 1, -7);
    matrix.set(3, 2, 2);
    matrix.set(3, 3, 4);
    
    //Matrix& ref = matrix;
    helper(fName, description, 301450, det(matrix), 1);
    
    Matrix matrix2= Matrix(2,2);
    matrix2.set(1, 1, 50);
    matrix2.set(1, 2, 0);
    matrix2.set(2, 1, -1);
    matrix2.set(2, 2, 100);
    
    helper(fName, description, 5000, det(matrix2), 2);
    
    Matrix matrix3 = Matrix(4,4);
    matrix3.set(1, 1, 1000);
    matrix3.set(1, 2, 0);
    matrix3.set(1, 3, -90);
    matrix3.set(1, 4, -90);
    matrix3.set(2, 1, -1);
    matrix3.set(2, 2, 0);
    matrix3.set(2, 3, 1);
    matrix3.set(2, 4, 0);
    matrix3.set(3, 1, -5);
    matrix3.set(3, 2, 2);
    matrix3.set(3, 3, 4);
    matrix3.set(3, 4, -1);
    matrix3.set(4, 1, -9);
    matrix3.set(4, 2, 2);
    matrix3.set(4, 3, 4);
    matrix3.set(4, 4, -10);
    
    helper(fName, description, 17100, det(matrix3), 3);
    
}

void testIdentityMatrix()
{
    strcpy(fName, "Matrix identity(int size)");
    strcpy(description,"Create and return an identity matrix");
    
    Matrix exp = Matrix(2,2);
    exp(1,1) = 1;
    exp(1,2) = 0;
    exp(2,1) = 0;
    exp(2,2) = 1;
    helper(fName, description, exp, identity(2), 1);
    
    try
    {
        print(identity(-1));
    }
    catch(length_error& le)
    {
        helper(fName, description, "Size must be >= 0", le.what(), 2);
    }
    
    try
    {
        print(identity(0));
    }
    catch(length_error& le)
    {
        helper(fName, description, "Size must be >= 0", le.what(), 3);
    }
}

void testMultiply()
{
    strcpy(fName, "Matrix multiply(const Vector& a, const Vector& b)");
    strcpy(description,"Multiply a column Vector and a row Vector");
    
    Vector a = Vector(3, 'R');
    Vector b = Vector(3, 'C');
    
    a.set(0, 1);
    a.set(1, 2);
    a.set(2, 3);
    
    b.set(0, 1);
    b.set(1, 2);
    b.set(2, 3);
    
    Matrix exp = Matrix(1,1);
    exp(1,1)   = 14;
    
    helper(fName, description, exp, multiply(a,b),1);
    
    Vector c = Vector(4, 'R');
    Vector d = Vector(4, 'C');
    
    c.set(0, -1);
    c.set(1, 20);
    c.set(2, 0);
    c.set(3, -22);
    
    d.set(0, 11);
    d.set(1, 20);
    d.set(2, 0);
    d.set(3, -1);
    
    Matrix exp2 = Matrix(1,1);
    exp2(1,1) = 411;
    
    helper(fName, description, exp2, multiply(c,d),2);
    
    try
    {
        Vector e = Vector(3, 'R');
        Vector f = Vector(2, 'C');
        
        e.set(0, 1);
        e.set(1, 2);
        e.set(2, 3);
        
        f.set(0, 1);
        f.set(1, 2);
        
    }
    catch(length_error& le)
    {
        helper(fName, description, "Sizes of vector don't match up", le.what(), 3);
    }
}

void testOperatorEqual()
{
    strcpy(fName, "Matrix& Matrix::operator=(const Matrix& other)");
    strcpy(description,"Assign another Matrix to this Matrix.");
    
    Matrix matrix = Matrix(2,2);
    matrix.set(1, 1, 50);
    matrix.set(1, 2, 2);
    matrix.set(2, 1, 4);
    matrix.set(2, 2, 1);
    
    Matrix t = matrix;
    helper(fName, description, matrix, t, 1);
    
    matrix.set(1, 1, -500);
    matrix.set(1, 2, -1);
    matrix.set(2, 1, 0);
    matrix.set(2, 2, 500);
    
    t = matrix;
    
    helper(fName, description, matrix, t, 2);
    
    Matrix m = t = matrix;
    
    helper(fName, description, matrix, m, 3);
    
    
    /*********** Initializer list **************/
    
    strcpy(fName, "Matrix& Matrix::operator=(std::initializer_list<double> values)");
    strcpy(description,"Assign an initializer_list to this Matrix.");
    
    Matrix matrix2 = Matrix(3,3);
    matrix2 = {1,2,3,4,5,6,7,8,9};
    
    Matrix exp = Matrix(3,3);
    exp(1,1) = 1;
    exp(1,2) = 2;
    exp(1,3) = 3;
    exp(2,1) = 4;
    exp(2,2) = 5;
    exp(2,3) = 6;
    exp(3,1) = 7;
    exp(3,2) = 8;
    exp(3,3) = 9;
    
    helper(fName, description, exp, matrix2, 1);
    
    Matrix matrix3 = Matrix(2,2);
    matrix3 = {-1,0,1,100};
    
    Matrix exp2 = Matrix(2,2);
    exp2(1,1) = -1;
    exp2(1,2) = 0;
    exp2(2,1) = 1;
    exp2(2,2) = 100;
    
    helper(fName, description, exp2, matrix3, 2);
    
    Matrix matrix4 = Matrix(2,1);
    Matrix matrix5 = matrix4 = {0,-1};
    Matrix exp3 = Matrix(2,1);
    exp3(1,1) = 0;
    exp3(2,1) = -1;
    
    helper(fName, description, exp3, matrix4, 3);
}

void testOperatorParens()
{
    strcpy(fName, "double& Matrix::operator()(int r, int c)");
    strcpy(description,"Access an element of this Matrix using the function-call operator.");
    
    Matrix matrix = Matrix(2,2);
    matrix.set(1, 1, 50);
    matrix.set(1, 2, 2);
    matrix.set(2, 1, 4);
    matrix.set(2, 2, 1);
    
    helper(fName, description, 2, matrix(1,2), 1);
    
    try
    {
        matrix(4,444);
    }
    catch(out_of_range& o)
    {
        helper(fName, description, "Out of range error", o.what(), 2);
    }
    
    matrix(1,2) = 100;
    helper(fName, description,100, matrix(1,2),3);
}

void testOperatorMultiply()
{
    strcpy(fName, "Matrix operator*(const Matrix& a, const Matrix& b)");
    strcpy(description,"Multiply two matrices");
    
    Matrix matrix = Matrix(2,2);
    matrix(1,1) = 10;
    matrix(1,2) = 2;
    matrix(2,1) = 4;
    matrix(2,2) = 1;
    
    Matrix matrix2 = Matrix(2,2);
    matrix2(1, 1) = 10;
    matrix2(1,2) = 2;
    matrix2(2, 1) = 4;
    matrix2(2, 2) = 1;
    
    Matrix exp = Matrix(2,2);
    exp(1,1) = 108;
    exp(1,2) = 22;
    exp(2,1) = 44;
    exp(2,2) = 9;
    
    helper(fName, description, exp, matrix*matrix2, 1);
    
    Matrix m3 = Matrix(1,1);
    m3(1,1) = 1;
    
    try
    {
        m3 * matrix2;
    }
    catch(length_error& le)
    {
        helper(fName, description, "Row and columns not the same", le.what(), 2);
    }
    
    Matrix m4 = Matrix(1,1);
    m4(1,1) = 192993;
    
    Matrix expected = Matrix(1,1);
    expected(1,1) = 192993;
    
    helper(fName, description, expected , m3 * m4, 3);
    
    
    //----------------------------------------------------
    
    strcpy(fName, "Multiply a row Vector and a Matrix");
    strcpy(description,"Vector operator*(const Vector& v, const Matrix& m)");
    
    Vector v    = Vector(1, 'R');
    Matrix mm   = Matrix(1,1);
    
    mm(1,1) = 1;

    v.set(0,1);

    
    Matrix expected2 = Matrix(1,1);
    
    expected2(1,1) = 14;

    
    helper(fName,description, expected2, v * mm, 1);
    
    try
    {
        Vector v2 = Vector(2, 'C');
        v2.set(0,-1);
        v2.set(1,0);
        
        //v2 * mm;
        
    }
    catch(length_error& le)
    {
        helper(fName, description, "Rows and Columns not same size", le.what(),2);
    }
    
    
    //----------------------------------------------------
    
    strcpy(fName, "Multiply a Matrix and a column Vector");
    strcpy(description,"Vector operator*(const Matrix& m, const Vector& v)");
    
    //helper(fName,description, expected2, mm* v, 1);
    
    
    //----------------------------------------------------
    
    strcpy(fName, "Multiply a scalar and a matrix");
    strcpy(description,"Matrix operator*(double k, const Matrix& a)");
    
    Matrix ex = Matrix(4,3);
    ex(1,1) = 10;
    ex(1,2) = 20;
    ex(1,3) = 30;
    ex(2,1) = 10;
    ex(2,2) = 10;
    ex(2,3) = 20;
    ex(3,1) = 10;
    ex(3,2) = 20;
    ex(3,3) = 20;
    ex(4,1) = 20;
    ex(4,2) = 10;
    ex(4,3) = 10;
    
    helper(fName, description, ex, 10 * mm, 1);
    
    ex(1,1) = -10;
    ex(1,2) = -20;
    ex(1,3) = -30;
    ex(2,1) = -10;
    ex(2,2) = -10;
    ex(2,3) = -20;
    ex(3,1) = -10;
    ex(3,2) = -20;
    ex(3,3) = -20;
    ex(4,1) = -20;
    ex(4,2) = -10;
    ex(4,3) = -10;
    
    helper(fName, description, ex, -10 * mm, 2);
    
    ex(1,1) = 0;
    ex(1,2) = 0;
    ex(1,3) = 0;
    ex(2,1) = 0;
    ex(2,2) = 0;
    ex(2,3) = 0;
    ex(3,1) = 0;
    ex(3,2) = 0;
    ex(3,3) = 0;
    ex(4,1) = 0;
    ex(4,2) = 0;
    ex(4,3) = 0;
    
    helper(fName, description, ex, 0 * mm, 3);
    
    
    //----------------------------------------------------
    
    strcpy(fName, "Multiply a matrix and a scalar");
    strcpy(description,"Multiply a matrix and a scalar");
    
    helper(fName, description, ex, mm * 0, 1);
    
}

void testOperatorMinus()
{
    strcpy(fName, "operator-(const Matrix& a, const Matrix& b)");
    strcpy(description,"Subtract the Matrix b from the Matrix a (component by component)");
    
    Matrix matrix = Matrix(2,2);
    matrix.set(1, 1, 10);
    matrix.set(1, 2, 2);
    matrix.set(2, 1, 4);
    matrix.set(2, 2, 1);
    
    Matrix matrix2 = Matrix(2,2);
    matrix2.set(1, 1, 10);
    matrix2.set(1, 2, 2);
    matrix2.set(2, 1, 4);
    matrix2.set(2, 2, 1);
    
    Matrix exp = Matrix(2,2);
    exp(1,1) = 0;
    exp(1,2) = 0;
    exp(2,1) = 0;
    exp(2,2) = 0;
    
    helper(fName, description, exp, matrix-matrix2, 1);
    
    try
    {
        Matrix m = Matrix(1,2);
        m(1,1) = 0;
        m(1,2) = 100;
        
        m - matrix2;
    }
    
    catch(length_error& le)
    {
        helper(fName, description, "Rows and columns not the same", le.what(),2);
    }
    
    Matrix t  = Matrix(1,2);
    t(1,1) = 0;
    t(1,2) = 100;
    
    Matrix l = Matrix(1,2);
    l(1,1) =-100;
    l(1,2) = -1;
    
    Matrix exp2 = Matrix(1,2);
    exp2(1,1) = -100;
    exp2(1,2) = -101;
    
    helper(fName, description, exp2, l-t,3);
}

void testOperatorPlus()
{
    strcpy(fName, "Matrix operator+(const Matrix& a, const Matrix& b)");
    strcpy(description,"Add the Matrix a and the Matrix b");
    
    Matrix matrix = Matrix(2,2);
    matrix.set(1, 1, 10);
    matrix.set(1, 2, 2);
    matrix.set(2, 1, 4);
    matrix.set(2, 2, 1);
    
    Matrix matrix2 = Matrix(2,2);
    matrix2.set(1, 1, 10);
    matrix2.set(1, 2, 2);
    matrix2.set(2, 1, 4);
    matrix2.set(2, 2, 1);
    
    Matrix exp = Matrix(2,2);
    exp(1,1) = 20;
    exp(1,2) = 4;
    exp(2,1) = 8;
    exp(2,2) = 2;
    
    helper(fName, description, exp, matrix+matrix2, 1);
    
    try
    {
        Matrix m = Matrix(1,2);
        m(1,1) = 0;
        m(1,2) = 100;
        
        m + matrix2;
    }
    
    catch(length_error& le)
    {
        helper(fName, description, "Rows and columns not the same", le.what(),2);
    }
    
    Matrix t  = Matrix(1,2);
    t(1,1) = 0;
    t(1,2) = 100;
    
    Matrix l = Matrix(1,2);
    l(1,1) =-100;
    l(1,2) = -1;
    
    Matrix exp2 = Matrix(1,2);
    exp2(1,1) = -100;
    exp2(1,2) = 99;
    
    helper(fName, description, exp2, l+t,3);
    
}

void testTranspose()
{
    strcpy(fName, "Matrix trans(const Matrix& a)");
    strcpy(description,"Create and return a transposed version of a given matrix.");
    
    Matrix matrix = Matrix(3,2);
    matrix.set(1,1,1);
    matrix.set(1,2,2);
    matrix.set(2,1,3);
    matrix.set(2,2,4);
    matrix.set(3,1,5);
    matrix.set(3,2,6);
    
    Matrix exp  = Matrix(2,3);
    exp(1,1) = 1;
    exp(1,2) = 3;
    exp(1,3) = 5;
    exp(2,1) = 2;
    exp(2,2) = 4;
    exp(2,3) = 6;
    
    helper(fName, description, exp, trans(matrix),1);
    
    Matrix m2 = Matrix(2,1);
    
    m2(1,1) = 0;
    m2(2,1) = -1;
    
    Matrix exp2 = Matrix(1,2);
    exp2(1,1) = 0;
    exp2(1,2) = -1;
    
    helper(fName, description, exp2, trans(m2),2);
    
    Matrix m3 = Matrix(1,1);
    
    m3(1,1) = -1;
    
    Matrix exp3 = Matrix(1,1);
    exp3(1,1) = -1;
    
    helper(fName, description, exp3, trans(m3),3);
    
    
}

int main(int argc, const char * argv[])
{
    testConstructor();
    testDeterminant();
    testIdentityMatrix();
    testMultiply();
    testOperatorEqual();
    testOperatorParens();
    testOperatorPlus();
    testOperatorMinus();
    testOperatorMultiply();
    testTranspose();
    
    
    return 0;
}



