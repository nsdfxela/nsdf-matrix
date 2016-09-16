#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "gtest/gtest.h"

TEST(testMatrix, matrixTest1)
{
	char *filename;
	int nrow1, ncol1, nrow2, ncol2;
	filename = "D:\\Stdy\\mm\\mm-app\\mm-app\\input.txt";
	std::ifstream file;
	std::string line;
	file.open(filename);
	std::getline(file, line);
	sscanf_s(line.c_str(), "%d %d %d %d", &nrow1, &ncol1, &nrow2, &ncol2);
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
	C = A * B;
	C.print();
	ASSERT_EQ(1, 10) << "TEST-TEST";
}