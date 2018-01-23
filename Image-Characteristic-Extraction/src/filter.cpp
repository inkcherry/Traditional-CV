#include "filter.h"
//filter::filter(Mat & main_mat_r):main_mat(&main_mat_r),
//width(main_mat_r.get_img_config().first),
//height(main_mat_r.get_img_config().second),
//kernel_mat(kernel())  //默认构造
//{
//}


filter::~filter()
{
	delete main_mat;
}

void filter::convolution()  //mat卷积操作
{

	////卷积 g=f*h  返回一个新的矩阵
	//double **res_mat=new double *[height];  //结果矩阵 形势与原矩阵相同
	//for (int i = 0; i < height; i++)
	//	res_mat[i] = new double[width];



	//int h_main_mat = height;
	//int w_main_mat = width;
	//int h_kernel_mat = kernel_mat.main_config.first;
	//int w_kernel_mat = kernel_mat.main_config.second;
	////Mat *res_Mmat = new Mat(width, height);
	//
	//	double temp;

	//	for (int i = 0; i < h_main_mat + h_kernel_mat - 1; i++)
	//	{
	//		for (int j = 0; j < w_main_mat + w_kernel_mat - 1; j++)
	//		{
	//			temp = 0;
	//			for (int m = 0; m < h_main_mat; m++)
	//			{
	//				for (int n = 0; n < w_main_mat; n++)
	//				{
	//					if ((i - m) >= 0 && (i - m) < h_kernel_mat && (j - n) >= 0 && (j - n) < w_kernel_mat)
	//					{
	//						temp += main_mat[m][n] * kernel_mat[i - m][j - n];
	//					}
	//				}
	//			}
	//			res_mat[i][j] = temp;

	//		}
	//	}
	//
}
//吸取dft写的很不友好的经验，全用double好了。
