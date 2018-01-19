#include <iostream>
void show_mat(double **,int w,int h);
void convolution(double** main_mat, double** kenel_mat, double** res_mat, int w_main_mat, int h_main_mat, int w_kenel_mat, int h_kenel_mat);  //f(x) h(x) g(x) ;

int main()
{
	double **main_mat = new double *[3];
	/*
	{1£¬2£¬3
	4£¬5£¬6
	7£¬8£¬9}
	*/
	double **kenel_mat = new double *[2];
	/*
	{1£¬2
	3£¬4}
	*/
	double **res_mat = new double *[4];

	for (int i = 0; i <4; i++)
		res_mat[i] = new double[4];




	for (int i = 0; i < 3; i++)
	{
		main_mat[i] = new double[3];
		for (int j = 0; j < 3; ++j)
		{
			main_mat[i][j] = i * 3 + j + 1;
		}
	}


	for (int i = 0; i < 2; i++)
	{
		kenel_mat[i] = new double[2];
		for (int j = 0; j < 2; j++)
		{
			kenel_mat[i][j] = i * 2 + j + 1;
		}
	}

	convolution(main_mat, kenel_mat, res_mat, 3, 3, 2, 2);
	show_mat(res_mat, 4, 4);
	std::cin.get();

	return 0;
}

void convolution(double** main_mat, double** kenel_mat, double** res_mat, int w_main_mat, int h_main_mat, int w_kenel_mat, int h_kenel_mat)  //f(x) h(x) g(x)
{
	double temp;

	for (int i = 0; i < h_main_mat + h_kenel_mat - 1; i++)
	{
		for (int j = 0; j < w_main_mat + w_kenel_mat - 1; j++)
		{
			temp = 0;
			for (int m = 0; m < h_main_mat; m++)
			{
				for (int n = 0; n < w_main_mat; n++)
				{
					if ((i - m) >= 0 && (i - m) < h_kenel_mat && (j - n) >= 0 && (j - n) < w_kenel_mat)
					{
						temp += main_mat[m][n] * kenel_mat[i - m][j - n];
					}
				}
			}
			res_mat[i][j] = temp;

		}
	}
}
void show_mat(double **mat, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			std::cout << mat[i][j] << " ";
		}

	}
}

