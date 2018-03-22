#include "transform.h"

void transform::canny(double threshod1, double threshod2, int size = 3)
{
}

transform::transform(Mat* &main_mat_r):main_mat(main_mat_r),
width(main_mat_r->get_img_config().first),
height(main_mat_r->get_img_config().second)
{

}

transform::~transform()
{
}

Mat* transform:: sobel(bool type = 1)   //1为complex
{
	pair<kernel*, kernel*> sobel_kernel =get_sobel(3);
	filter *temp_filter =new filter(main_mat);
	Mat *gx_res = temp_filter->custom_kernel_op(sobel_kernel.first);  //gx
	Mat *gx_res = temp_filter->custom_kernel_op(sobel_kernel.second);

	Mat *res_mat;





	delete sobel_kernel.first;
	delete sobel_kernel.second;
	delete temp_filter;
	return res_mat;
	return nullptr;
}
pair<kernel*,kernel*> transform::get_sobel(int size)
{
	//使用经典的sobel核
	//gx			   gy
	// 1  0 1			-1 -2 -1
	//-2 0 2			0   0  0
	//-1 0 1			1   2  1
	double gx_[3][3] = { {-1,0,+1},{-2,0,+2},{-1,0,+1} };
	double gy_[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };


	double **gx = new double*[3];
	double **gy = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		gx[i] = new double[3];
		gy[i] = new double[3];
		for (int j = 0; j < 3; j++)
		{
			gx[i][j] = gx_[i][j];
			gy[i][j] = gy_[i][j];
		}
	}
	kernel *gx_kernel = new kernel(gx, 3, 3);
	kernel *gy_kernel = new kernel(gy, 3, 3);
	return make_pair(gx_kernel, gy_kernel);
	return make_pair(nullptr,nullptr);
}
