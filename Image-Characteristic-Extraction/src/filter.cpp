#include "filter.h"
filter::filter(Mat*  &main_mat_r):main_mat(main_mat_r),
width(main_mat_r->get_img_config().first),
height(main_mat_r->get_img_config().second),
kernel_mat(nullptr)//默认
{
}


filter::~filter()
{
	delete kernel_mat;
	
}

double** filter::convolution()  //mat卷积操作   main_mat与kernel_mat进行卷积操作
{

	//卷积 g=f*h  返回一个新的矩阵
	int res_height = height + kernel_mat->main_config.second ;
	int res_width = width + kernel_mat->main_config.first ;

	double **res_mat=new double *[res_height];  //结果矩阵 形势与原矩阵相同
	for (int i = 0; i <=res_height; i++)
		res_mat[i] = new double[res_width];
		


	int h_main_mat = height;
	int w_main_mat = width;
	int h_kernel_mat = kernel_mat->main_config.first;
	int w_kernel_mat = kernel_mat->main_config.second;
	//Mat *res_Mmat = new Mat(width, height);
	
		double temp;

		for (int i = 0; i < h_main_mat + h_kernel_mat - 1; i++)
		{
			for (int j = 0; j < w_main_mat + w_kernel_mat - 1; j++)
			{
				temp = 0;
				for (int m = 0; m < h_main_mat; m++)
				{
					for (int n = 0; n < w_main_mat; n++)
					{
						if ((i - m) >= 0 && (i - m) < h_kernel_mat && (j - n) >= 0 && (j - n) < w_kernel_mat)
						{
							temp += (*main_mat)[m][n] *(*kernel_mat)[i - m][j - n];

						}
					}
				}
				res_mat[i][j] = temp;

			}
		}
		return res_mat;
		//
}
void filter::boxblur(const int & kernel_width, const int & kernel_height)
{
	
	kernel_factory pro(main_mat,kernel_width, kernel_height, kernel_factory::box);
}
//吸取dft写的很不友好的经验，全用double好了。

kernel_factory::kernel_factory(Mat* &main_mat_r, const int &k_width,const int &k_height,kerneltype  type)
{
	switch (type)
	{
	case box:
		init_box_kernel(main_mat_r,k_width,k_height);
		break;
	case blur:
		init_blur_kernel(main_mat_r, k_width, k_height);
		break;
	case gaussianblur:
		init_gaussianblur_kernel(main_mat_r, k_width, k_height);
		break;
	default:
		break;
	}
}

void kernel_factory::init_box_kernel(Mat* &main_mat_r, const int &k_width,const int &k_height)
{
	double **kernel_mat=new double*[k_height];
	for (int i = 0; i < k_height; i++)
	{	
		kernel_mat[i] = new double[k_width];
		for (int j = 0; j < k_width; j++)
		{
			kernel_mat[i][j] = 1;
		}
	}
	factory_kernel = new kernel(kernel_mat, const_cast<int &>(k_width), const_cast<int &>( k_height));
}

void kernel_factory::init_gaussianblur_kernel(Mat* & main_mat_r, const int &k_width, const int &k_height)
{
}

void kernel_factory::init_blur_kernel(Mat* & main_mat_r, const int &k_width, const int &k_height)
{
}
