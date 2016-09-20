#include <vector>
class Matrix
{
	double **mat;
public:
	int rows;
	int columns;
	Matrix();
	Matrix(const double *data, int rows, int cols);
	Matrix(std::vector<double> &data, int rows, int cols);
	~Matrix();
	
	double det();
	bool isSquare();
	double gauss();
	Matrix inv();
	Matrix cbind(Matrix &b);
	static Matrix createIdentity(int rows);
	//Elementary transformations
	void rowsSwap(int a, int b);
	double* rowMultConstant(int a, double c);
	double* rowAddition(int a, int withB);
	double* rowAddition(int a, double* row);
	//Operators
	friend bool operator==(const Matrix &a, const Matrix &b);
	friend bool operator!=(const Matrix &a, const Matrix &b);
	Matrix operator+(Matrix &b);
	double operator() (int row, int col	) const;
	Matrix operator*(Matrix &b);
	
	void print();
};

