#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define CONSTRUCT(list, r, c) \
	this->rows = r; \
	this->columns = c; \
	mat = new double*[rows]; \
for (int i = 0; i < rows; i++) \
{ \
	mat[i] = new double[cols]; \
for (int j = 0; j < cols; j++) \
	{ \
	mat[i][j] = data[i*cols + j]; \
	} \
} \

Matrix::Matrix()
{
}
double Matrix::operator() (int row, int col) const
{
	return mat[row][col];
}

bool operator==(const Matrix &a, const Matrix &b)
{
	if (a.rows == b.rows
		&& (a.columns == b.columns))

	{
		for (int i = 0; i < a.rows; i++)
		{
			for (int j = 0; j < a.columns; j++)
			{
				if (a(i, j) != b(i, j))
					return false;
			}
		}
		return true;
	}
	else return false;
}

bool operator!=(const Matrix &a, const Matrix &b)
{
	return !operator==(a, b);
}

void Matrix::print()
{
	char print_buffer[50];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{

			sprintf(print_buffer, "%f ", mat[i][j]);
			std::cout << print_buffer;
		}
		std::cout << std::endl;
	}
}

Matrix Matrix::operator+(Matrix &b)
{
	if (b.rows != this->rows || b.columns != this->columns)
	{
		throw;
	}
	else
	{
		Matrix c(b);
		for (int i = 0; i < b.rows; i++)
		{
			for (int j = 0; j < b.columns; j++)
			{
				c.mat[i][j] += this->mat[i][j];
			}
		}
		return c;
	}
}

Matrix Matrix::operator*(Matrix &b)
{
	if (columns != b.rows)
	{
		throw;
	}
	else
	{
		double **result;
		result = new double*[this->rows];
		for (int i = 0; i < this->rows; i++)
		{
			result[i] = new double[b.columns];
			for (int j = 0; j < b.columns; j++)
			{
				result[i][j] = 0;
				for (int k = 0; k < this->columns; k++)
				{
					result[i][j] += this->operator()(i, k) * b(k, j);
				}
			}
		}
		Matrix m;
		m.mat = result;
		m.rows = this->rows;
		m.columns = b.columns;
		return m;
	}

}

double Matrix::det()
{
	Matrix copy(*this);
	double d = copy.gauss();
	double result = 1.0;
	for (int i = 0; i < rows; i++)
		result *= copy(i, i);
	return result / d;
}

bool Matrix::isSquare()
{
	return (rows == columns);
}

void Matrix::rowsSwap(int a, int b)
{
	if (a == b)
		return;

	double* buf = mat[a];
	mat[a] = mat[b];
	mat[b] = buf;
}

double* Matrix::rowAddition(int a, int withB)
{
	return rowAddition(a, mat[withB]);
}

double* Matrix::rowAddition(int a, double* row)
{
	double* result = new double[columns];
	std::copy(mat[a], mat[a] + columns, result);
	for (int i = 0; i < columns; i++)
	{
		result[i] += row[i];
	}
	return result;
}

double* Matrix::rowMultConstant(int a, double c)
{
	double* result = new double[columns];
	std::copy(mat[a], mat[a] + columns, result);
	for (int i = 0; i < columns; i++)
	{
		result[i] *= c;
	}
	return result;
}

Matrix Matrix::cbind(Matrix &b)
{
	
	double **data;
	data = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		data[i] = new double[columns + b.columns];
		std::copy(this->mat[i], (this->mat[i] + columns ), data[i]);
		std::copy(b.mat[i], (b.mat[i] + b.columns ), (data[i] + columns));
	}
	Matrix res;
	res.mat = data;
	res.rows = rows;
	res.columns = columns + b.columns;
	return res;
}

Matrix Matrix::createIdentity(int rows)
{
	Matrix res;
	res.rows = rows;
	res.columns = rows;
	res.mat = new double*[rows];
	for (int i = 0; i < rows; i++){
		res.mat[i] = new double[rows];
		for (int j = 0; j < rows; j++)
		{
			i == j ? res.mat[i][j] = 1.0 : res.mat[i][j] = 0;
		}
	}
	return res;
}

double Matrix::gauss()
{
	/*if (!isSquare()){
		throw;
	}*/

	double detMultiplier = 1.0;
	double coeff = 0.0;
	for (int k = 0; k < columns - 1; k++)
	{
		for (int j = k; j < rows; j++)
		{
			if (mat[j][k] != 0)
			{
				rowsSwap(j, k);
				detMultiplier *= -1;
				break;
			}
		}

		for (int j = k + 1; j < rows; j++)
		{
			coeff = mat[j][k] / mat[k][k];
			double* newRow = rowMultConstant(k, -coeff);
			mat[j] = rowAddition(j, newRow);
		}
	}
	return detMultiplier;
}

double Matrix::gaussJordan()
{
	double detMultiplier = gauss();
	double coeff = 0.0;
	int col = 0;
	for (int i = rows-1; i >= 0; i--)
	{ 
		for (int j = i-1; j >= 0; j--)
		{
			coeff = mat[j][i] / mat[i][i];
			double* newRow = rowMultConstant(i, -coeff);
			mat[j] = rowAddition(j, newRow);
			detMultiplier *= (coeff);
		}
		mat[i] = rowMultConstant(i, 1 / mat[i][i]);
		detMultiplier *= (mat[i][i]);
	}
	return detMultiplier;
}

Matrix Matrix::inv()
{
	Matrix mtrx(*this);
	Matrix I = createIdentity(mtrx.rows);
	Matrix AI = mtrx.cbind(I);
	AI.gaussJordan();
	Matrix A(new double[mtrx.rows*mtrx.columns], mtrx.rows, mtrx.columns);
	
	for (int i = 0; i < A.rows; i++){
		std::copy(AI.mat[i] + mtrx.columns, AI.mat[i] + AI.columns, A.mat[i]);
	}
	return A;
}

void Matrix::luDecomposition(Matrix &l, Matrix &u)
{

}

Matrix::Matrix(const double *data, int rows, int cols)
{
	CONSTRUCT(data, rows, cols)
}

Matrix::Matrix(std::vector<double> &data, int rows, int cols)
{
	CONSTRUCT(data, rows, cols)
}

Matrix::~Matrix()
{
}
