//2D傅里叶变换算法

#include<iostream>
#include <cmath>
#include <vector>
using namespace std;
template <typename T>
struct complex
{
	explicit complex() { real = 0; img = 0; }
	explicit complex(T r,T i) { real = r; img = i; }
	T real;   //实部
	T img;    //虚部
};

const double PI = 3.141592653589793238462;
template <typename T>
void  dft_2D(const vector<std::vector<T>>&input_matrix, vector<std::vector<complex<T>>>&output_matrix); //傅里叶变换

//template <typename T>
//void idft_2D(T **inpurarray, T ***outputarray, int size);//傅里叶逆变换

template <typename T>
void  init_matrix(T inputarray[][2], int height, int width, vector<std::vector<T>>&vec)
{
	for (int i = 0; i < height; i++)
	{
		vector<T> temp;
		for (int j = 0; j < width; j++)
		{
			temp.push_back(inputarray[i][j]);
		}
		vec.push_back(temp);
	}
}
template <typename T>
void show_matrix(const vector<std::vector<T>>&vec)
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
	dft_2D(inputarr, outputarr);

	cin.get();
	return 0;
}

template <typename T>
void dft_2D(const vector<std::vector<T>>&input_matrix, vector<std::vector<complex<T>>>&output_matrix)
{
	int height = input_matrix.size();
	int width = input_matrix.front().size();
	//int width = 2;   //..test;
	//init output_matrix
	vector<std::vector<complex<T>>> temp_matrix;
	for (int i = 0; i < height; i++)
	{
		vector<complex<T>> temp;
		for (int j = 0; j < width; j++)
		{
			complex<T> temp_complex;				//2通道 默认构造0
			temp.push_back(temp_complex);
		}
		output_matrix.push_back(temp);
		temp_matrix.push_back(temp);
	}




	const int M = height;
	const int N = width;

	for(int i=0;i<M;i++)
		for (int j = 0; j < N; j++)
		{

			double  t = 2.0*PI*(double)(j) / (double)(N);
			for (int o = 0; o < N;o++){
				T m_var = t*(double)(j);
				temp_matrix[i][j].real += input_matrix[i][j] * cos(m_var);
				temp_matrix[i][j].img -= input_matrix[i][j] * sin(m_var);
			}
		}

	for(int i=0;i<M;i++)
		for (int j = 0; j < N; j++)
		{

		}
	return;
}
//template <typename T>
//void idft(T **inputarray, T ***outputarray, int size)
//{
//	return;
//}

