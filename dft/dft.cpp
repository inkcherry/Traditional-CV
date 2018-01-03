//2d傅里叶变换算法

#include<iostream>
#include <cmath>
#include <vector>
const double PI = 3.141592653589793238462;
using namespace std;
template <typename T>
struct complex
{
	explicit complex() { real = 0; img = 0; }
	explicit complex(T r, T i) { real = r; img = i; }
	T real;   //实部
	T img;    //虚部
};


template<typename T>
using f_2A_matrix = vector<std::vector<complex<T>>>; //包含虚数部分双通道矩阵

template<typename T>
using f_1A_matrix = vector<std::vector<T>>;    //单通道2d矩阵


template <typename T>
void  dft_2d(const f_1A_matrix<T>&input_matrix, f_2A_matrix<T>&output_matrix); //傅里叶变换

template<typename T>
void idft_2d(const  f_2A_matrix<T>& input_matrix, f_1A_matrix<T>&outpu_matritx); //傅里叶逆变换


template <typename T>
void show_matrix(const f_2A_matrix<T>&outpu_matrix);

template <typename T>
void show_matrix(const f_1A_matrix<T>&vec);

template <typename T>
void  init_matrix(T inputarray[][3], int height, int width, f_1A_matrix<T>&vec);  //暂定


template <typename T>
void rotate_matrix(f_1A_matrix<T>&input_matrix);               //一个错位调整

// main
int main()
{
	double inarr[5][3] = { {2,2,2}, {3,3,3 },{ 2,2,2 },{ 4,4,4 }, {7,7,6} };
	double outarr[5][3][2] = { 0 };
	std::vector<std::vector<double> > inputarr;
	vector<vector<complex<double>>> outputarr;
	init_matrix(inarr, 5, 3, inputarr);
	show_matrix(inputarr);
	dft_2d(inputarr, outputarr);
	show_matrix(outputarr);

    //逆运算
	std::vector<std::vector<double> > inverse_inputarr;
	idft_2d(outputarr, inverse_inputarr);

	std::cout << "逆变换后还原的矩阵"<<std::endl;
	show_matrix(inverse_inputarr);
	cin.get();
	return 0;
}




//函数定义
template <typename T>
void dft_2d(const f_1A_matrix<T>&input_matrix, f_2A_matrix<T>&output_matrix)
{

	//运算以double形式运算，展示数据以原数据类型展示
	int height = input_matrix.size();
	int width = input_matrix.front().size();



	f_2A_matrix<T> temp_matrix;
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

	//show_matrix(output_matrix);
	//show_matrix(temp_matrix);
	//std::cout << "___________________________" << std::endl;


	const int m = height;
	const int n = width;
	const double temp_sqrt = 1.0 / sqrt(m * n);  //乘积1
	for (int u = 0; u < m; u++) {
		for (int y = 0; y < n; y++)
		{

			double  t = 2.0*PI*(double)(y) / (double)(n);
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
			double t = 2.0*PI*(double)(x) / (double)(m);
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


template <typename T>
void show_matrix(const f_2A_matrix<T>&output_matrix)
{
	std::cout << "real part" << std::endl; //实
	for (auto i : output_matrix)
	{
		for (auto j : i)
			std::cout << j.real << ",";
		cout << "\n";
	}
	std::cout << "\nimg part" << std::endl;
	for (auto i : output_matrix)
	{
		for (auto j : i)
			std::cout << j.img << ",";
		cout << "\n";
	}
	return;
}

template<typename T>
void idft_2d(const f_2A_matrix<T>& input_matrix,f_1A_matrix<T>&output_matrix)
{

	int height = input_matrix.size();
	int width = input_matrix.front().size();


	const int M = height;
	const int N = width;
	const double temp_sqrt = 1.0 / sqrt(M * N);  //乘积1
	f_2A_matrix<T> temp_matrix;                   // 辅助运算的2A矩阵

	for (int i = 0; i < height; i++)
	{
		vector<complex<T>> temp_2A_node;
		vector<T> temp_1A_node;
		for (int j = 0; j < width; j++)
		{
			complex<T> temp_complex;				//2通道 默认构造0
			temp_2A_node.push_back(temp_complex);
			temp_1A_node.push_back(0);
		}
		output_matrix.push_back(temp_1A_node);
		temp_matrix.push_back(temp_2A_node);
	}



	for (int x = 0; x < M; x++)
	{
		for (int v = 0; v < N; v++)
		{
			double t = 2.0*PI*(double)(v) / (double)(N);
			for (int y = 0; y < N; y++) {
				double temp_var = t*(double)(y);
				double temp_sin = sin(temp_var);
				double temp_cos = cos(temp_var);

				temp_matrix[x][v].real += input_matrix[x][y].real * temp_cos - input_matrix[x][y].img * temp_sin;
				temp_matrix[x][v].img  += input_matrix[x][y].img  *temp_cos + input_matrix[x][y].real * temp_sin;

			}
		}
	}
	//cout << "_________mid__________";
	//show_matrix(temp_matrix)
	for (int u = 0; u < M; u++)
	{
		for (int v = 0; v < N; v++)
		{
			double t=2.0*PI*(double)(u) / (double)(M);
			for (int x = 0; x < M; x++)
			{
				double temp_var = t*(double)(x);
				output_matrix[u][v] += temp_matrix[x][v].real * cos(temp_var) - temp_matrix[x][v].img * sin(temp_var);
				/*std::cout << "..." << output_matrix[u][v] << endl;*/
			}
			output_matrix[u][v] *= temp_sqrt;
		}
	}
	rotate_matrix(output_matrix);   //关于一个错位的修复
	show_matrix(output_matrix);
}


template <typename T>
void  init_matrix(T inputarray[][3], int height, int width, f_1A_matrix<T>&vec)
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
void show_matrix(const f_1A_matrix<T>&vec)
{
	for (auto i : vec)
	{
		for (auto j : i)
			cout << j << " ";
		cout << "\n";
	}
}


template <typename T>
void rotate_matrix(f_1A_matrix<T>&input_matrix)
{
	const int M = input_matrix.size();
	const int N = input_matrix.front().size();
	vector<T> temp;

	for (int i = 1; i < ceil(M/2.0); i++)   //不太清楚第一行为什么不错位
	{
			temp = input_matrix[i];
			input_matrix[i] = input_matrix[M-i];
			input_matrix[M - i] = temp;
	}
}
