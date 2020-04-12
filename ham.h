// Author: Tobias Winter, Propulse NTNU
// Last updated: 15/10/2019
// Purpouse: Custom library for mathematical operations and functions

#include <iostream>
#include <vector>
using namespace std;

struct Matrix {
	int size[2];
	
	//The vector obj stores the elements of the Matrix class
	// Should not be acsessed directly
	vector<vector<double>> vector_obj;

	// Initializes Matrix by vector arg on form
	// {{a11, a12, a13, ...}, {a21, a22, a23}, {a31, a32, a33, ...}, ...}
	Matrix(vector<vector<double>> vector_arg);

	// Initializes Matrix m x n mattrix filled with zeros
	Matrix(int m, int n);

	// Returns number of rows in matrix
	int rows();

	// Returns number of columns in matrix
	int cols();

	// Accesses i-th row of matrix, returns vector obj
	// Be aware of vectors behaving as Matrixes
	// {{1, 2, 3, 4}}[0] = {1, 2, 3, 4}, not 1 or {1}
	vector<double>& operator[](int i);

	// Transposes matrix
	Matrix T();

	// Fills diagnonal of n x n matrix with a vector of size n
	Matrix diag();
};

struct Quaternion {
	// The elements of the quaternion
	double a;
	double b;
	double c;
	double d;

	// Initializes quaternion with four elements
	Quaternion(double a_arg, double b_arg, double c_arg, double d_arg);
	
	// Initializes quaternion from vector (as matrix), and a scalar
	Quaternion(double a_arg, Matrix v);

	// Returns conjugate of quaternion
	Quaternion conjugate();

	// Returns norm of quaternion
	double norm();

	// Makes the elements of the quaternion accesible through indexing
	// q[0] = a, q[1] = b, ...
	double& operator[](int i);

	// Returns inverse of quaternion
	Quaternion inverse();
};

// Matrix multiplication
Matrix operator*(Matrix& A, Matrix& B);

// Scalar-matrix multiplication
Matrix operator*(const double& c, Matrix A);

// The hamilton product of two quaternions
Quaternion operator*(Quaternion q, Quaternion r);

// Multiplies a scalar with a quaternion
Quaternion operator*(double k, Quaternion q);

// Makes matrix printable
ostream& operator<<(ostream& os, Matrix A);

// Makes quaternion printable
ostream& operator<<(ostream& os, Quaternion q);

// Makes vector printable
ostream& operator<<(ostream& os, const vector<double>& vector);