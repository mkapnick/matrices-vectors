/**
 * Vector
 *
 * Purpose: The Vector class provides
 *          the necessary operations and
 *          behaviors of vectors
 *
 * Author:  Michael Kapnick, James Madison University
 *
 * Version: 3 February 2014
 */

using namespace std;
#include "math.h"
#include "Vector.h"


/**
 * Construct a column vector of given size
 *
 * @param size The size of the Vector
 */

Vector::Vector(int size)
{
    setSize(size, COLUMN);
    allocateMemory();
    setValues(0.0);
}

/**
 * Construct a column or row vector of given size
 *
 * Example of use:
 *
 *   Vector y(3, Vector::ROW);
 *
 * @param size        The size of the Vector
 * @param orientation The orientation (either COLUMN or ROW)
 */

Vector::Vector(int size, char orientation)
{
    setSize(size, orientation);
    allocateMemory();
    setValues(0.0);
}


/**
 * A copy constructor
 *
 * Note: Without a copy constructor one can't pass a Vector by
 * value (since when one passes by value a copy is made)
 *
 * @param original  The Vector to copy
 */

Vector::Vector(const Vector& original)
{
    setSize(original.size, original.orientation);
    allocateMemory();
    
    for (int i =0; i < original.size; i++)
    {
        this->values[i] = original.values[i];
    }
}


/**
 * Destructor
 */
Vector::~Vector()
{
    deallocateMemory();
}

/**
 * Allocate memory for the values in this Vector
 */
void Vector:: allocateMemory()
{
    this->values = new double[this->size];
}

/**
 * Deallocate the memory used by the values in this Vector
 */
void Vector::deallocateMemory()
{
    delete[] this->values;
    this-> values = NULL;
}


/**
 * Get a particular element of this Vector
 *
 * @param i   The index of the element
 * @return    The value of the element at the given index
 */
double Vector::get(int i) const
{
    double result = -1;
    
    if (i >=0 && i < this->size)
    {
        result = this->values[i];
    }
    return result;
}

/**
 * Get the orientation of this Vector
 *
 * @return    The orientation (Vector::COLUMN or Vector::ROW)
 */
char Vector::getOrientation() const
{
    return this->orientation;
}

/**
 * Get the size of this Vector
 *
 * @return The number of elements in this Vector
 */
int Vector::getSize() const
{
    return this->size;
}

/**
 * Calculate the Euclidean norm of a Vector
 *
 * @param a   The Vector
 * @return    ||a||
 */
double norm(const Vector& a)
{
    double norm = 0;
    double squared = 0;
    
    for (int i =0; i < a.getSize(); i++)
    {
        squared = a.values[i] * a.values[i];
        norm += squared;
    }
    
    norm = sqrt(norm);
    return norm;
}

/**
 * Calculate the normalized version of a Vector
 *
 * @param a   The Vector
 * @return    a / ||a||
 */
Vector normalized(const Vector& a)
{
    double current  = 0;
    double n        = 0;
    
    Vector copy     = Vector(a);
    n               = norm(copy);
    
    for (int i =0; i < a.getSize(); i++)
    {
        current = copy.values[i];
        current /= n;
        copy.values[i] = current;
        
    }
    return copy;
}


/**
 * Set all the elements of this Vector to a given value
 *
 * @param value   The value
 */
void Vector::setValues(double value)
{
    int counter =0;
    
    while(counter < this->size)
    {
        this->values[counter] = value;
        counter++;
    }
}

/**
 * Set all the elements of this Vector to a given value
 *
 * @param values A pointer to an array of doubles
 */
void Vector::setValues(const double * values)
{
    for (int i =0; i < this->size; i++)
    {
        this-> values[i] = *values;
        values++;
    }
}

/**
 * Access an element of this Vector using the function-call operator.
 *
 * Note: This method returns by reference so that this operator
 * can be used on the left side of the assignment operator. Though this
 * can be dangerous in general (since the value being referred to
 * may not always exist), in this case it shouldn't cause any
 * problems.
 *
 * Examples of use:
 *
 *     d = y(1);
 *     y(2) = 5.0;
 *
 * @param i   The index of the element
 * @throws    out_of_range exception if i is out of range
 * @return    The value of the element at the given index
 */
double& Vector::operator()(int i)
{
    // As long as i is with in the appropriate index
    if(i >= 0 && i < this->size && this-> size >0)
    {
        double &r = this->values[i];
        return r;
    }
    else
    {
        throw out_of_range("Index out of range");
    }
}

/**
 * Assign an initializer_list to this Vector.
 *
 * Examples of use:
 *
 *   y = {1,
 *        2,
 *        3};
 *
 *   x = {4, 5, 6, 7, 8, 9};
 *
 * Note: This method is not void so that one can write x = y = {1,2}
 * (which first assigns {1,2} to y and then assigns the result of
 * that assignment to x).  It returns the result by reference because
 * there is no chance that this will not refer to something.
 *
 * @param v   The initializer_list containing the values
 */
Vector& Vector::operator=(std::initializer_list<double> values)
{
    
    const double*   start;
    int             size, count;
    
    start   = values.begin();
    size    = (int)values.size();
    count   = 0;
    
    this->setSize(size, this->orientation);
    this->setValues(0.0);
    
    printf("size is: %i", size);
    
    while (count < size)
    {
        this->values[count++] = *start;
        start++;
    }
    
    return *this;
}

/**
 * Assign another Vector to this Vector.
 *
 * The two Vectors must have the same size and orientation.
 *
 * Note: This method is not void so that one can write x = y = z
 * (which first assigns z to y and then assigns the result of that
 * assignment to x). It returns the result by reference because there
 * is no concern that this will not refer to something.
 *
 * @param other   The right-side Vector
 * @throws        length_error if the sizes or orientations don't match
 * @return        The Vector referred to by this
 */
Vector& Vector::operator=(const Vector& other)
{
    if (this->size == other.getSize() && this->orientation == other.getOrientation())
    {
        setValues(other.values);
    }
    
    else {
        throw length_error("Size and/or orientation is not the same");
    }
    
    return *this;
    
}

/**
 * Add the Vector a and the Vector b (component by component)
 *
 * Note: This method must return by value because the result Vector
 * is a local variable.
 *
 * @param a  One Vector
 * @param b  The other Vector
 * @throws   length_error exception if the sizes or orientations don't match
 * @return   The Vector a+b
 */

Vector operator+(const Vector& a, const Vector& b)
{
    Vector copy = Vector(a);
    
    if (a.getSize() == b.getSize() && a.getOrientation() == b.getOrientation())
    {
        for (int i = 0; i < copy.getSize(); i++)
        {
            copy.values[i] = a.values[i] + b.values[i];
        }
    }
    
    else
    {
        throw length_error("Size and/or orientation are not the same");
    }
    
    return copy;
}

/**
 * Subtract the Vector b from the Vector a (component by component)
 *
 * The two Vectors must have the same size and orientation.
 *
 * Note: This method must return by value because the result Vector
 * is a local variable.
 *
 * @param a  One Vector
 * @param b  The other Vector
 * @throws   length_error if the sizes or orientations don't match
 * @return   The Vector a-b
 */

Vector operator-(const Vector& a, const Vector& b)
{
    Vector copy = Vector(a);
    if(a.getSize() == b.getSize() && a.getOrientation() == b.getOrientation())
    {
        for (int i = 0; i < copy.getSize(); i++)
        {
            copy.values[i] = a.values[i] - b.values[i];
        }
    }
    else
    {
        throw length_error("Size or orientation are not the same");
    }
    
    return copy;
    
}

/**
 * Multiply two Vectors (i.e., find the dot/inner product)
 *
 * The two Vectors must have the same size and same orientation
 *
 * Note: This method must return by value because the result Vector
 * is a local variable.
 *
 * @param a   The first Vector (a row Vector)
 * @param b   The second Vector (a column Vector)
 * @throws    length_error if the sizes or orientations don't match
 * @return    The resulting scalar
 */

double operator*(const Vector& a, const Vector& b)
{
    //As long as Vectors match in orientation and size
    
    double dot = 0;
    
    if(a.getSize() == b.getSize() && a.getOrientation() == b.getOrientation())
    {
        for (int i = 0; i < a.getSize(); i++)
        {
            dot += a.values[i] * b.values[i];
        }
    }
    else
    {
        throw length_error("Size and/or orientation not the same");
    }
    return dot;
}

/**
 * Multiply a scalar and a Vector
 *
 * Note: This method must return by value because the result Vector
 * is a local variable.
 *
 * @param k   The scalar
 * @param a   The Vector
 * @return    The resulting Vector
 */
Vector operator*(double k, const Vector& a)
{
    //As long as Vectors match in orientation and size
    
    Vector copy = Vector(a);
    
    for(int i =0; i < copy.getSize(); i++)
    {
        copy.values[i] = copy.values[i] * k;
    }
    return copy;
}


/**
 * Multiply a Vector and a scalar
 *
 * Note: This method must return by value because the result Vector
 * is a local variable.
 *
 * @param a   The Vector
 * @param k   The scalar
 * @return    The resulting Vector
 */
Vector operator*(const Vector& a, double k)
{
    return k * a;
}

/**
 * Compare two Vectors to see if they have identical (within a
 * pre-defined TOLERANCE) elements
 *
 * The two Vectors must have the same size and same orientation
 *
 * @param a   The first Vector
 * @param b   The second Vector
 * @throws    length_error if the sizes or orientations don't match
 * @return    true or false
 */
bool operator==(const Vector& a, const Vector& b)
{
    bool equal = true;
    
    if (a.getSize() == b.getSize() && a.getOrientation() == b.getOrientation())
    {
        for (int i = 0; i < a.getSize(); i++)
        {
            if (a.values[i] != b.values[i])
            {
                equal = false;
                break;
            }
        }
    }
    else
        throw length_error("Size and/or orientation not the same");
    
    return equal;
}

/**
 * Compare two Vectors to see if they have different (beyond a given
 * TOLERANCE) elements
 *
 * The two Vectors must have the same size and same orientation
 *
 * @param a   The first Vector
 * @param b   The second Vector
 * @throws    length_error if the sizes or orientations don't match
 * @return    true or false
 */

bool operator!=(const Vector& a, const Vector& b)
{
    bool result = true;
    if (a.getSize() == b.getSize() && a.getOrientation() == b.getOrientation())
    {
        bool equal  = (a == b);
        
        if(equal)
            result = false;
    }
    
    else
        throw length_error("Size and/or orientation not the same");
    return result;
}


/**
 * Sets the index of this vector to a given values
 *
 * @param index the index of the values array
 * @param value the value to place at the index
 *
 */
void Vector::set(const int index, const double value)
{
    if (index >= 0 && index <= this->size)
    {
        this->values[index] = value;
    }
}

/**
 * Initialize the size and orientation of this Vector
 *
 * @param size          The size
 * @param orientation   The orientation
 */
void Vector::setSize(int size, char orientation)
{
    this -> size        = size;
    this -> orientation = orientation;
}

/**
 * Create and return a transposed version of a given Vector
 *
 * Note: This function must return by value because the result Vector
 * is a local variable.
 *
 * @param a   The original Vector
 * @return    The transposed Vector
 */
Vector trans(const Vector& a)
{
    Vector vector = Vector(a);
    
    if(a.orientation == 'C')
        vector.orientation = 'R';
    else
        vector.orientation = 'C';
    
    return vector;
}


