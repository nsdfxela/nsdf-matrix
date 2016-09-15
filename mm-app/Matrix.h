#include <vector>
class Matrix
{
	double **mat;
public:
	int rows;
	int columns;
	Matrix();
	Matrix(std::vector<double> &data, int rows, int cols);
	~Matrix();
	Matrix operator+(Matrix &b);
	Matrix Matrix::operator*(Matrix &b);
	double** Matrix::getMat();
	void print();
};

