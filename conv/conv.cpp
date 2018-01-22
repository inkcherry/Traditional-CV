#include <iostream>
void show_mat(double **,int w,int h);
void convolution(double** main_mat, double** kenel_mat, double** res_mat, int w_main_mat, int h_main_mat, int w_kenel_mat, int h_kenel_mat);  //f(x) h(x) g(x) ;

int main()
{
    double t_kernel_mat[9]={-1,-2,-1,0,0,0,1,2,1};
    double t_main_mat[9]={1,2,3,4,5,6,7,8,9};
	double **main_mat = new double *[3];
	/*
	{1£¬2£¬3
	4£¬5£¬6
	7£¬8£¬9}
	*/
	double **kenel_mat = new double *[3];
	/*
	{1£¬2
	3£¬4}
	*/
	double **res_mat = new double *[5];

	for (int i = 0; i <5; i++)
		res_mat[i] = new double[5];




	for (int i = 0; i < 3; i++)
	{
		main_mat[i] = new double[3];
		for (int j = 0; j < 3; ++j)
		{
			main_mat[i][j] = t_main_mat[i * 3 + j];
		}
	}


	for (int i = 0; i < 3; i++)
	{
		kenel_mat[i] = new double[3];
		for (int j = 0; j < 3; j++)
		{
			kenel_mat[i][j] = t_kernel_mat[i * 3 + j ];
		}
	}

	convolution(main_mat, kenel_mat, res_mat, 3, 3, 3, 3);
	show_mat(main_mat,3,3);
	show_mat(kenel_mat,3,3);
	show_mat(res_mat, 4, 4);
	std::cin.get();

	return 0;
}

//卷积 g=f*h
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
void show_mat(double **mat, int w, int h)   //其中会产生两个边缘
{
	for (int i = 1; i < h; i++)  //不显示边缘
	{
		for (int j = 1; j < w; j++)
		{
			std::cout << mat[i][j] << " ";
		}
        std::cout<<"\n";
	}
}

