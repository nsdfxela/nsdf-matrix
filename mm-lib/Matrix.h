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
	friend bool operator==(const Matrix &a, const Matrix &b);
	friend bool operator!=(const Matrix &a, const Matrix &b);

	double operator() (int row, int col	) const;
	Matrix Matrix::operator*(Matrix &b);
	double** Matrix::getMat();
	void print();
};

