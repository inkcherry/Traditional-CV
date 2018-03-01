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

double ** morph::convolution()//因为膨胀腐蚀  核一般需要 平坦  因此这个地方需要重写
{
	
}
