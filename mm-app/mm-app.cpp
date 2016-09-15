// mm-app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(int argc, char* argv[])
{
	char *filename;
	int nrow1, ncol1, nrow2, ncol2;
	filename = argv[1];
	std::ifstream file;
	std::string line;
	file.open(filename);
	std::getline(file, line);
	sscanf(line.c_str(), "%d %d %d %d", &nrow1, &ncol1, &nrow2, &ncol2);
	std::vector<double> buffer;

	double d;
	/*Reading matrix A*/
	int counter = nrow1*ncol1;
	while (counter-- && file >> d)
	{
		buffer.push_back(d);
	}
	
	Matrix A(buffer, nrow1, ncol1);
	buffer.clear();
	/*Reading matrix B*/
	counter = nrow2*ncol2;
	while (counter-- && file >> d)
	{
		buffer.push_back(d);
	}
	file.close();
	Matrix B(buffer, nrow2, ncol2);
	
	A.print();
	std::cout << std::endl;
	B.print();
	std::cout << std::endl;
	Matrix C = A + B;
	Matrix D = A * B;
	C.print();

	return 0;
}

