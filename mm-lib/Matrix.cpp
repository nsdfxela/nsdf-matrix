#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
				if (a(i,j) != b(i,j))
					return false;
			}
		}
		return true;
	}
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
					result[i][j] += this->operator()(i,k) * b(k,j);
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

Matrix::Matrix(std::vector<double> &data, int rows, int cols)
{
	this->rows = rows;
	this->columns = cols;

	mat = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new double[cols];
		for (int j = 0; j < cols; j++)
		{
			mat[i][j] = data[i*cols + j];
		}
	}
}

double Matrix::det()
{
	Matrix copy(*this);
	double d = copy.gauss();
	copy.print();
	double result = 1.0;
	for (int i = 0; i < rows; i++)
		result *= copy(i,i);
	return result/d;
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
	std::copy(mat[a], mat[a]+columns, result);
	for (int i = 0; i < columns; i++)
	{
		result[i] *= c;
	}
	return result;
}

double Matrix::gauss()
{
	if (!isSquare()){
		throw;
	}
	double detMultiplier = 1.0;
	double coeff = 0.0;
	for (int k = 0; k < columns-1; k++)
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
			
			for (int j = k+1; j < rows; j++)
			{
				coeff = mat[j][k] / mat[k][k];
				double* newRow = rowMultConstant(k, -coeff);
				mat[j] = rowAddition(j, newRow);
			}
	}
	return detMultiplier;
}

Matrix::~Matrix()
{
}
