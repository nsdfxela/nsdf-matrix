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

TEST(testMatrix, det)
{
	static const double Adata[] =
	{ 2.0, 1.0, 1.0,
	4.0, -6.0, 0.0,
	-2.0, 7.0, 2.0 };
	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	
	Matrix A(Avec, 3, 3);
	double det = A.det();
	ASSERT_EQ(det, -16.0);
}

TEST(testMatrix, det2)
{
	static const double Adata[] =
	{ 0.440981766, 0.2256360, 0.65062182, 0.27429142, 0.6668476, 0.34110213, 0.6688382,
	0.053314246, 0.9509703, 0.08845699, 0.09599700, 0.2119761, 0.82880369, 0.8542271,
	0.005385053, 0.7820807, 0.27225012, 0.87603066, 0.9346250, 0.59914844, 0.4868032,
	0.902596908, 0.2991466, 0.84494488, 0.46673596, 0.3066095, 0.79195919, 0.3077258,
	0.874406090, 0.4678755, 0.07489958, 0.90506278, 0.3073542, 0.03876189, 0.7682957,
	0.614470835, 0.7843640, 0.50044150, 0.01084699, 0.0342375, 0.86218561, 0.6975900,
	0.836206900, 0.3609330, 0.55240323, 0.58422357, 0.1840902, 0.61532534, 0.9894036, };

	std::vector<double> Avec(Adata, Adata + sizeof(Adata) / sizeof(Adata[0]));
	Matrix A(Avec, 7, 7);
	double determinant = A.det();
	EXPECT_FLOAT_EQ(determinant, -0.02500575);

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

TEST(testMatrix, constructorTest2)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0
		, 10.0, 51.0, 89.0 };
	Matrix A(Adata, 3, 3);

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

TEST(testMatrix, cbind)
{
	static const double Adata[] = { 1.0, 7.0, 9.0
		, 2.0, 3.0, 12.0
		, 10.0, 51.0, 89.0 };

	static const double Bdata[] = 
	    { 1.0, 0.0, 0.0
		, 0.0, 1.0, 0.0
		, 0.0, 0.0, 1.0 };

	Matrix A(Adata, 3, 3);
	Matrix B(Bdata, 3, 3);
	Matrix C = A.cbind(B);
	
	ASSERT_EQ(C(0, 3), 1.0);
	ASSERT_EQ(C(1, 3), 0.0);
	ASSERT_EQ(C(2, 3), 0.0);
	ASSERT_EQ(C(0, 4), 0.0);
	ASSERT_EQ(C(1, 4), 1.0);
	ASSERT_EQ(C(2, 4), 0.0);
	ASSERT_EQ(C(0, 5), 0.0);
	ASSERT_EQ(C(1, 5), 0.0);
	ASSERT_EQ(C(2, 5), 1.0);
}

TEST(testMatrix, identity)
{
	Matrix A = Matrix::createIdentity(3);
	ASSERT_EQ((A)(0, 0), 1.0);
	ASSERT_EQ((A)(1, 0), 0.0);
	ASSERT_EQ((A)(2, 0), 0.0);
	ASSERT_EQ((A)(0, 1), 0.0);
	ASSERT_EQ((A)(1, 1), 1.0);
	ASSERT_EQ((A)(2, 1), 0.0);
	ASSERT_EQ((A)(0, 2), 0.0);
	ASSERT_EQ((A)(1, 2), 0.0);
	ASSERT_EQ((A)(2, 2), 1.0);
	
}

TEST(testMatrix, identity2)
{
	Matrix A = Matrix::createIdentity(100);
	ASSERT_EQ((A)(0, 0), 1.0);
	ASSERT_EQ((A)(1, 1), 1.0);
	ASSERT_EQ((A)(2, 2), 1.0);
	ASSERT_EQ((A)(88, 88), 1.0);

}

TEST(testMatrix, inversion)
{

	static const double Adata[] = { 0.83713082, 0.89945422, 0.2475557, 0.38640846, 0.3220384, 0.4908369, 0.35427415, 0.6820444,
		0.16408505, 0.08438874, 0.9473535, 0.85953968, 0.3720836, 0.2397122, 0.82839885, 0.7091935,
		0.81904553, 0.77424245, 0.7459364, 0.17823068, 0.6736013, 0.3828627, 0.47393671, 0.4698798,
		0.05122909, 0.52335285, 0.3185233, 0.49749688, 0.7614367, 0.2472524, 0.46638974, 0.2211583,
		0.66374367, 0.35342016, 0.8592638, 0.97158578, 0.4855654, 0.6428755, 0.44007243, 0.2276820,
		0.01161055, 0.04104302, 0.1324462, 0.05616432, 0.2599191, 0.5133695, 0.49840857, 0.3170504,
		0.27280851, 0.03873000, 0.2253261, 0.68495935, 0.5496109, 0.7314455, 0.44641709, 0.3555080,
		0.65881631, 0.67780922, 0.6746421, 0.80468019, 0.9952057, 0.2377356, 0.04817506, 0.5719705 };
	static const double AinvData[] = { -0.107231148, 0.4320926, 2.6643306, -0.6082967, -1.5656767, -4.424583, 3.7478205, -1.6150731,
		 0.990061160, -0.6215834, -1.5611165, 1.0562084, 1.3810477, 2.141498, -2.8870044, 0.5218031,
		-0.604652609, -0.1593624, -0.7922131, -0.6282436, 1.7392879, 3.093142, -3.0343408, 1.2914144,
		 0.487821573, 0.3332087, -0.7749594, 0.5248279, 0.2308728, -1.467355, 0.7099435, -0.2809382,
		-0.955480744, -0.1122161, 1.3069518, 0.3708846, -1.2559945, -1.241101, 1.8012877, 0.1297538,
		 0.157249494, -1.1427807, -1.7214876, -0.5543570, 1.9302480, 4.177751, -2.2939979, 1.1996925,
		-0.002459896, 0.9317469, 2.0442862, 1.0833719, -1.4506776, -3.453528, 2.7639341, -2.4767745,
		 0.574490158, 0.5498574, -0.9249098, -1.0544927, -0.7042295, 1.688502, -0.7289013, 1.3464922 };

	Matrix A(Adata, 10, 10);
	Matrix Ainv(AinvData, 10, 10);
	/*Matrix B = A.inv();
	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 10; j++)
	{
		EXPECT_DOUBLE_EQ(Ainv(i, j), B(i, j));
	}
	*/
}