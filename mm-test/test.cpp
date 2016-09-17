#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "gtest/gtest.h"

//TEST(testMatrix, matrixTest1)
//{
//	char *filename;
//	int nrow1, ncol1, nrow2, ncol2;
//	filename = "D:\\Stdy\\mm\\mm-app\\mm-lib\\input.txt";
//	std::ifstream file;
//	std::string line;
//	file.open(filename);
//	std::getline(file, line);
//	sscanf_s(line.c_str(), "%d %d %d %d", &nrow1, &ncol1, &nrow2, &ncol2);
//	std::vector<double> buffer;
//
//	double d;
//	/*Reading matrix A*/
//	int counter = nrow1*ncol1;
//	while (counter-- && file >> d)
//	{
//		buffer.push_back(d);
//	}
//
//	Matrix A(buffer, nrow1, ncol1);
//	buffer.clear();
//	/*Reading matrix B*/
//	counter = nrow2*ncol2;
//	while (counter-- && file >> d)
//	{
//		buffer.push_back(d);
//	}
//	file.close();
//	Matrix B(buffer, nrow2, ncol2);
//
//	A.print();
//	std::cout << std::endl;
//	B.print();
//	std::cout << std::endl;
//	Matrix C = A + B;
//	C = A * B;
//	C.print();
//	ASSERT_EQ(1, 10) << "TEST-TEST";
//}

TEST(testMatrix, equalityTest1)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
								, 2.0, 3.0, 12.0
								, 10.0, 15.0, 89.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	
	static const double Bdata[] = { 1.0, 7.0, 9.0
								  , 2.0, 3.0, 12.0
								  , 10.0, 15.0, 89.0 };
	std::vector<double> Bvec(Bdata, Bdata + sizeof(Bdata) / sizeof(Bdata[0]));

	Matrix A(Avec, 3, 3);
	Matrix B(Bvec, 3, 3);
 
	ASSERT_EQ(A, B);
}

TEST(testMatrix, equalityTest2)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0
		, 10.0, 15.0, 89.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));

	static const double Bdata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0
		, 10.0, 51.0, 89.0 };
	std::vector<double> Bvec(Bdata, Bdata + sizeof(Bdata) / sizeof(Bdata[0]));

	Matrix A(Avec, 3, 3);
	Matrix B(Bvec, 3, 3);

	ASSERT_NE(A, B);
}

TEST(testMatrix, isSquare)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0
		, 10.0, 15.0, 89.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	Matrix A(Avec, 3, 3);
	ASSERT_TRUE(A.isSquare());
}

TEST(testMatrix, rowAddition)
{
	static const double Adata[] = { 10.0, 20.0, -10.0
								  , -5.0, 10.0, 10.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	Matrix A(Avec, 2, 3);
	double* res = A.rowAddition(0, 1);
	ASSERT_EQ(res[0], 5.0);
	ASSERT_EQ(res[1], 30.0);
	ASSERT_EQ(res[2], 0.0);
}

TEST(testMatrix, rowConstantMultiplication)
{
	static const double Adata[] = { 0.0, 20.0, -10.0
		, -5.0, 10.0, 10.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	Matrix A(Avec, 2, 3);
	double* res = A.rowMultConstant(0, 100.0);
	
	ASSERT_EQ(res[0], 0.0);
	ASSERT_EQ(res[1], 2000.0);
	ASSERT_EQ(res[2], -1000.0);
}

TEST(testMatrix, gauss1)
{
	static const double Adata[] = 
		 { 2.0, 1.0, -1.0,
		  -3.0, -1.0, 2.0,
		  -2.0,  1.0, 2.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	static const double Bdata[] = 
	    { 2.0, 1.0, -1.0
		, 0.0, 0.5,  0.5
		, 0.0, 0.0, -1.0 };
	std::vector<double> Bvec(Bdata, Bdata + sizeof(Adata) / sizeof(Bdata[0]));
	Matrix A(Avec, 3, 3);
	Matrix B(Bvec, 3, 3);

	A.gauss();
	ASSERT_EQ(A, B);
}

TEST(testMatrix, gauss2)
{
	static const double Adata[] =
	{ 2.0, 1.0, 1.0,
	  4.0, -6.0, 0.0,
	-2.0, 7.0, 2.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	static const double Bdata[] =
	{ 2.0, 1.0, 1.0
	, 0.0, -8.0, -2.0
	, 0.0, 0.0, 1.0 };
	std::vector<double> Bvec(Bdata, Bdata + sizeof(Adata) / sizeof(Bdata[0]));
	Matrix A(Avec, 3, 3);
	Matrix B(Bvec, 3, 3);

	A.gauss();
	ASSERT_EQ(A, B);
}


TEST(testMatrix, isNotSquare)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	Matrix A(Avec, 3, 2);
	ASSERT_FALSE(A.isSquare());
}

TEST(testMatrix, constructorTest)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0
		, 10.0, 51.0, 89.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	Matrix A(Avec, 3, 3);
	
	ASSERT_EQ(A(0, 0), 1.0);
	ASSERT_EQ(A(0, 1), 7.0);
	ASSERT_EQ(A(0, 2), 9.0);

	ASSERT_EQ(A(1, 0), 2.0);
	ASSERT_EQ(A(1, 1), 3.0);
	ASSERT_EQ(A(1, 2), 12.0);

	ASSERT_EQ(A(2, 0), 10.0);
	ASSERT_EQ(A(2, 1), 51.0);
	ASSERT_EQ(A(2, 2), 89.0);
}

TEST(testMatrix, swap)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0
		, 10.0, 51.0, 89.0 };	
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	
	static const double Bdata[] = { 1.0, 7.0, 9.0
		, 10.0, 51.0, 89.0 
		, 2.0, 3.0, 12.0 };
	std::vector<double> Bvec(Bdata, Bdata + sizeof(Bdata) / sizeof(Bdata[0]));

	Matrix A(Avec, 3, 3);
	Matrix B(Bvec, 3, 3);
	A.rowsSwap(1, 2);
	ASSERT_EQ(A, B);
}