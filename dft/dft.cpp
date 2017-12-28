//2d傅里叶变换算法

#include<iostream>
#include <cmath>
#include <vector>
using namespace std;
template <typename t>
struct complex
{
	explicit complex() { real = 0; img = 0; }
	explicit complex(t r,t i) { real = r; img = i; }
	t real;   //实部
	t img;    //虚部
};

const double pi = 3.141592653589793238462;
template <typename t>
void  dft_2d(const vector<std::vector<t>>&input_matrix, vector<std::vector<complex<t>>>&output_matrix); //傅里叶变换

template <typename t>
void show_matrix(const vector<vector<complex<t>>>&outpu_matrix);   //展示傅里叶变换之后的矩阵

//template <typename t>
//void idft_2d(t **inpurarray, t ***outputarray, int size);//傅里叶逆变换

template <typename t>
void  init_matrix(t inputarray[][2], int height, int width, vector<std::vector<t>>&vec)
{
	for (int i = 0; i < height; i++)
	{
		vector<t> temp;
		for (int j = 0; j < width; j++)
		{
			temp.push_back(inputarray[i][j]);
		}
		vec.push_back(temp);
	}
}
template <typename t>
void show_matrix(const vector<std::vector<t>>&vec)
{
	for (auto i : vec)
	{
		for (auto j : i)
			cout << j<<" ";
		cout << "\n";
	}
}
void test(int **a) {}
int main()
{
	double inarr[3][2] = { { 1,2 },{ 2,4 },{ 3,5 } };
	double outarr[2][3][2] = { 0 };
	std::vector<std::vector<double> > inputarr;
	vector<vector<complex<double>>> outputarr;
	init_matrix(inarr, 3, 2, inputarr);
	show_matrix(inputarr);
	dft_2d(inputarr, outputarr);
	show_matrix(outputarr);
	cin.get();
	return 0;
}


template <typename t>
void dft_2d(const vector<std::vector<t>>&input_matrix, vector<std::vector<complex<t>>>&output_matrix)
{

	//运算以double形式运算，展示数据以原数据类型展示
	int height = input_matrix.size();
	int width = input_matrix.front().size();



	vector<std::vector<complex<t>>> temp_matrix;
	for (int i = 0; i < height; i++)
	{
		vector<complex<t>> temp;
		for (int j = 0; j < width; j++)
		{
			complex<t> temp_complex;				//2通道 默认构造0
			temp.push_back(temp_complex);
		}
		output_matrix.push_back(temp);
		temp_matrix.push_back(temp);
	}

	//show_matrix(output_matrix);
	//show_matrix(temp_matrix);
	//std::cout << "___________________________" << std::endl;


	const int m = height;
	const int n = width;
	const double temp_sqrt = 1.0 / sqrt(m * n);  //乘积1
	for (int u = 0; u < m; u++) {
		for (int y = 0; y < n; y++)
		{

			double  t = 2.0*pi*(double)(y) / (double)(n);
			for (int v = 0; v < n; v++) {
				double m_var = t*(double)(v);  //uy/n
				temp_matrix[u][y].real += input_matrix[u][v] * cos(m_var);
				temp_matrix[u][y].img -= input_matrix[u][v] * sin(m_var);

			}
		}
	}


	for (int x = 0; x < m; x++) {
		for (int y = 0; y < n; y++)
		{
			double t = 2.0*pi*(double)(x) / (double)(m);
			for (int u = 0; u < m; ++u)
			{
				double m_var = t*double(u);  //ux/m

				output_matrix[x][y].real += temp_matrix[u][y].real*cos(m_var) - temp_matrix[u][y].img*sin(m_var);
				output_matrix[x][y].img += temp_matrix[u][y].img*cos(m_var) + temp_matrix[u][y].real*sin(m_var);
			}
			output_matrix[x][y].real *= temp_sqrt;
			output_matrix[x][y].img *= temp_sqrt;
		}

	}

	return;
}


template <typename t>
void show_matrix(const vector<vector<complex<t>>>&output_matrix)
{
	std::cout << "real part" << std::endl; //实
	for (auto i : output_matrix)
	{
		for (auto j : i)
			std::cout << j.real<<",";
		cout << "\n";
	}
	std::cout << "\nimg part" << std::endl;
	for (auto i : output_matrix)
	{
		for (auto j : i)
			std::cout << j.img<<",";
		cout << "\n";
	}
	return;
}
//template <typename t>
//void idft(t **inputarray, t ***outputarray, int size)
//{
//	return;
//}

