#include "ham.h"
#include <cmath>

Matrix::Matrix(vector<vector<double>> vector_arg) {
	vector_obj = vector_arg;
	size[0] = vector_obj.size();
	size[1] = vector_obj[0].size();
	try {
		for (auto row : vector_obj) {
			if (row.size() != size[1]) {
				throw "Bad matrix encountered";
			}
		}
	} catch (const char* msg) {
		cerr << msg << endl;
		exit(1);
	}
}

Matrix::Matrix(int m, int n) {
	vector<double> row(n, 0);
	vector<vector<double>> v(m, row);
	vector_obj = v;
}

Matrix Matrix::T() {
	Matrix A = *this;
	int m = A.rows();
	int n = A.cols();
	Matrix B(n, m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			B[j][i] = A[i][j];
		}
	}
	return B;
}

Matrix Matrix::diag() {
	Matrix A = *this;
	int n = A.cols();
	Matrix B(n, n);
	for (int i = 0; i < n; i++) {
		B[i][i] = A[0][i];
	}
	return B;
}

Matrix operator*(Matrix& A, Matrix& B) {
	int n = A.rows();
	int m = A.cols();
	int p = B.cols();
	try {
		if (B.rows() != m) {
			throw "Incompatible matrices";
		}
	} catch (const char* msg) {
		cerr << msg << endl;
		exit(1);
	}
	Matrix C(n, p);
	double sum {0};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			sum = 0;
			for (int k = 0; k < m; k++) {
				sum = sum + A.vector_obj[i][k] * B.vector_obj[k][j];
			}
			C.vector_obj[i][j] = sum;
		}
	}
	return C;
}

Matrix operator*(const double& c, Matrix A) {
	int m = A.rows();
	int n = A.cols();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = c*A[i][j];
		}
	}
	return A;
}

int Matrix::rows() {
	return this->vector_obj.size();
}

int Matrix::cols() {
	return this->vector_obj[0].size();
}

vector<double>& Matrix::operator[](int i) {
	return this->vector_obj[0];
}

ostream& operator<<(ostream& os, Matrix A) {
	int m = A.rows();
	os << "[";
	for (int i = 0; i < m - 1; i++) {
		os << A[i] << "\n";
	}
	os << A[m - 1] << "]";
	return os;
}

Quaternion::Quaternion(double a_arg, double b_arg, double c_arg, double d_arg) {
	a = a_arg;
	b = b_arg;
	c = c_arg;
	d = d_arg;
}

Quaternion::Quaternion(double a_arg, Matrix vector) {
	try {
		if (vector.rows() == 3 and vector.cols() == 1) {
			a = a_arg;
			b =	vector.vector_obj[0][0];
			c = vector.vector_obj[1][0];
			d = vector.vector_obj[2][0];
		}
		else if (vector.rows() == 1 and vector.cols() == 3) {
			a = a_arg;
			b =	vector.vector_obj[0][0];
			c = vector.vector_obj[0][1];
			d = vector.vector_obj[0][2];
		}
		else {
			throw "Not a vector";
		}
	} catch (const char* msg) {
		cerr << msg << endl;
		exit(1);
	}
}

Quaternion Quaternion::conjugate() {
	Quaternion q_star(this->a, -this->b, -this->c, -this->d);
	return q_star;
}

double Quaternion::norm() {
	double q_norm = sqrt(pow(this->a, 2)
		+ pow(this->b, 2)
		+ pow(this->c, 2)
		+ pow(this->d, 2));
	return q_norm;
}

ostream& operator<<(ostream& os, const vector<double>& v) {
	int n = v.size();
	os << "[";
	for (int i = 0; i < n - 1; i++) {
		os << v[i] << " ";
	}
	os << v[n - 1] << "]";
	return os;
}

double& Quaternion::operator[](int i) {
	try {
		switch(i) {
			case 0:
				return a;
			case 1:
				return b;
			case 2:
				return c;
			case 3:
				return d;
			default:
				throw "Out of bounds";
		}
	} catch (const char* msg) {
		cerr << msg << endl;
		exit(1);
	}
}

ostream& operator<<(ostream& os, Quaternion q) {
	os << "(" << q.a << " " << q.b << " " << q.c << " " << q.d << ")";
	return os;
}

Quaternion operator*(Quaternion q, Quaternion r) {
	double a = q.a*r.a - q.b*r.b - q.b*r.b - q.b*r.b;
	double b = q.a*r.b + q.b*r.a + q.c*r.d - q.d*r.c;
	double c = q.a*r.c - q.b*r.d + q.c*r.a + q.d*r.b;
	double d = q.a*r.d + q.b*r.c - q.c*r.b + q.d*r.a;
	Quaternion s(a, b, c, d);
	return s;
}

Quaternion operator*(double k, Quaternion q) {
	Quaternion r(k*q.a, k*q.b, k*q.c, k*q.d);
	return r;
}

Quaternion Quaternion::inverse() {
	return (1/pow(this->norm(), 2))*this->conjugate();
}