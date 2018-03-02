#include "morph.h"

morph::morph(Mat *& main_mat_r) :main_mat(main_mat_r),
width(main_mat_r->get_img_config().first),
height(main_mat_r->get_img_config().second),
kernel_mat(nullptr)//默认
{
	double **default_kernel = new double *[3];    //默认矩形核
	for(int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
		{
			default_kernel[i][j] = 1;
		}
	kernel_mat = new kernel(default_kernel,3,3);
}

Mat * morph::morph_operate(bool is_erode)  //
{
	double ** res_mat;
	//默认核是平坦的 
	if (kernel_mat->main_config.first != kernel_mat->main_config.second) //方形检测
		exit(-1);
	
	if (kernel_mat->main_config.first % 2 != 1)
		exit(-1);
	
	const int size = kernel_mat->main_config.first;
	const int edge = size / 2;   //floor

	const int bottom = height - size - 1;
	const int right = width - size - 1;

	if (!is_erode)
	{ 
		for (int i = edge; i < height-edge; i++)  //中心处理
		{
			double t_max = 0;
			for (int j = edge; j < width-edge; j++)
			{
				int l = i - 1, r = i + 1, int t = j - 1, b = j + 1;
				for(int k=t;k<b;k++)  
					for (int s = l; s < r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
			}
		}

		for (int i = 0; i < edge; i++)  //边缘处理(上)
		{
			for (int j = 0; j < width; j++);
		}
		
		for (int i = height - edge; i < height-1; i++)//边缘处理(下)
		{
			for (int j = 0; j < width; j++);
		}

		for (int i = 0; i < height; i++)      //(左)
		{
			for (int j = 0; j < edge; j++);
		}

		for (int i = 0; i < height; i++)  //(右)
		{
			for (int j = width - edge; j < width; j++);
		}

	}

	else
	{

	}

	return nullptr;
}

