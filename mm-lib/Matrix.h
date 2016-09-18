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
	double det();
	bool isSquare();
	double gauss();
	//Elementary transformations
	void rowsSwap(int a, int b);
	double* rowMultConstant(int a, double c);
	double* rowAddition(int a, int withB);
	double* rowAddition(int a, double* row);
	friend bool operator==(const Matrix &a, const Matrix &b);
	friend bool operator!=(const Matrix &a, const Matrix &b);
	double operator() (int row, int col	) const;
	Matrix Matrix::operator*(Matrix &b);
	void print();
};

