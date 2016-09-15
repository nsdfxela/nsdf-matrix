#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Matrix::Matrix()
{
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
				c.getMat()[i][j] += this->getMat()[i][j];
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
					result[i][j] += this->getMat()[i][k] * b.getMat()[k][j];
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

double** Matrix::getMat(){
	return this->mat;
}

Matrix::~Matrix()
{
}
