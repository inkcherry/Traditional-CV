#include "transform.h"

void transform::canny(double threshod1, double threshod2, int size )
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

Mat * transform::laplacian(int mask_type, double scale)
{

	return nullptr;
}

Mat* transform:: sobel(bool type )   //1为complex 
{
	pair<kernel*, kernel*> sobel_kernel =get_sobel(3);
	filter *temp_filter =new filter(main_mat);

	Mat *res_mat = new Mat(width,height);

	Mat *gx_res = temp_filter->custom_kernel_op(sobel_kernel.first);  //gx
	Mat *gy_res = temp_filter->custom_kernel_op(sobel_kernel.second);



	//gx_res->show_main_mat();
	//gy_res->show_main_mat();

	res_mat->show_main_mat();

	if (type = true)   //使用欧式距离内个公式
	{
		for(int i=0;i<width;i++)
			for (int j = 0; j < height; j++)
			{
				double cur_gx = (*gx_res)[i][j];
				double cur_gy = (*gy_res)[i][j];
				(*res_mat)[i][j] = sqrt(cur_gx*cur_gx + cur_gy*cur_gy);
			}
	}

	if (type = false)
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				double cur_gx = (*gx_res)[i][j];
				double cur_gy = (*gy_res)[i][j];
				(*res_mat)[i][j] = abs(cur_gx) + abs(cur_gy);
			}
	}

	res_mat->show_main_mat();


	delete sobel_kernel.first;
	delete sobel_kernel.second;
	delete temp_filter;
	return res_mat;
	return nullptr;
}
Mat * transform::laplacian()
{
	kernel *laplacian_kernel = get_laplacian();
	filter *temp_filter = new filter(main_mat);
	Mat *sharpen_mat = new Mat(width, height);
	sharpen_mat = temp_filter->custom_kernel_op(laplacian_kernel);
	//res_mat->show_main_mat();

	Mat *res_mat = new Mat(width, height);
	double c = 0.5; //原图像与锐化后res=inital+ c(△2f(x,y)) 
	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			(*res_mat)[i][j] = c * (*sharpen_mat)[i][j] + (*main_mat)[i][j];
		}
	delete sharpen_mat;
	delete temp_filter;
	res_mat->show_main_mat();
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
	//gx_kernel->show_kernel();
	//gy_kernel->show_kernel();

	return make_pair(gx_kernel, gy_kernel);
	return make_pair(nullptr,nullptr);
}

kernel * transform::get_laplacian(int mask_type)
{   //dst   对图像求x二阶偏导+y二阶偏导
	// ksize=1 约等于原图像于对如下核卷积
	//0   1    0
	//1  -4   1
	//0   1   0
	double (*gxy_)[3] ;
	double gxy_1[3][3] = { { -0,1,+0 },{ 1,-4,1 },{ 0,1,0 } };
	double gxy_2[3][3] = { { 1,1,1 },{ 1,-8,1 },{ 1,1,1 } };
	double gxy_3[3][3] = { { 0,-1,0 },{ -1,4,-1 },{ 0,-1,0 } };
	double gxy_4[3][3] = { { -1,-1,-1 },{ -1,8,-1 },{ -1,-1,-1 } };
	switch (mask_type)
	{
	case 1:
		gxy_ = gxy_1;
		break;
	case 2:
		gxy_ = gxy_2;
		break;
	case 3:
		gxy_ = gxy_3;
		break;
	case 4:
		gxy_ = gxy_4;
		break;
	default:
		break;
	}



	double **gxy = new double*[3];

	for (int i = 0; i < 3; i++)
	{
		gxy[i] = new double[3];
		for (int j = 0; j < 3; j++)
		{
			gxy[i][j] = gxy_[i][j];
			gxy[i][j] = gxy_[i][j];
		}
	}
	kernel *gxy_kernel = new kernel(gxy, 3, 3);
	gxy_kernel->show_kernel();
	return gxy_kernel;
	return nullptr;
}
