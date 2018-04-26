#include "transform.h"

void transform::canny(double threshod1, double threshod2, int size )
{
}

Mat * transform::op(pair<kernel*, kernel*>kernel_,bool type)
{
	filter *temp_filter = new filter(main_mat);

	Mat *res_mat = new Mat(width, height);

	Mat *gx_res = temp_filter->custom_kernel_op(kernel_.first);  //gx
	Mat *gy_res = temp_filter->custom_kernel_op(kernel_.second);



	//gx_res->show_main_mat();
	//gy_res->show_main_mat();

	//res_mat->show_main_mat();

	if (type = true)   //使用欧式距离内个公式
	{
		for (int i = 0; i < width; i++)
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

	//res_mat->show_main_mat();


	delete kernel_.first;
	delete kernel_.second;
	delete temp_filter;
	return res_mat;
	return nullptr;

	return nullptr;
}

Mat * transform::hough_transform(double theta_length_, double rho, int line_tresh, int tresh_, bool is_binary_mat_)
{
	//确定累加数组大小
	const int theta_length = 180;
	const int r_length = sqrt(2.0)*(height>width?height:width);      //极坐标的角和半径共线统计数组

	const bool is_binary_mat = is_binary_mat_;


	const int tresh = tresh_;
	const double transform_radian = PI / 180;



	Mat *res_mat =new Mat(width,height);

	int center_x = width / 2;
	int center_y = height / 2;




	unsigned int **count_arr = new unsigned int *[theta_length];  //初始化统计数组[theta_length][r_length]
	for (int i = 0; i < theta_length; i++)
	{
		count_arr[i] = new unsigned int[r_length];

		for (int j = 0; j < r_length; j++)
			count_arr[i][j] = 0;
	}



	if (!is_binary_mat)//需要先进行二值处理
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if ((*main_mat)[i][j] > tresh)
					(*res_mat)[i][j] = 255;
				else
				{
					(*res_mat)[i][j] = 0;
				}
			}
	}

	else
	{
		for(int i=0;i<height;i++)
			for (int j = 0; j < width; j++)
			{
				(*res_mat)[i][j] = (*main_mat)[i][j];
			}


	};

	for (int theta = 0; theta < theta_length; theta++)
	{
		double temp_radian = theta*transform_radian;
		double cos_var = cos(temp_radian);
		double sin_var = sin(temp_radian);

		for (int i = 0; i < height; i++)  //对应图像y
			for (int j = 0; j < width; j++)//对应图像x
			{
				if ((*res_mat)[i][j] == 255)//有值
				{
					double temp_r = cos_var*j + sin_var*i;
					int int_r = round(temp_r);
					count_arr[theta][int_r]++;
				}
				/*  double temp_r = (i*sin_var + j*cos_var);
				  if (temp_r < r_length&temp_r>0)
					  count_arr[theta_length][r_length];*/
			}
	}

	vector<pair<pair<int, int>, pair<int, int>>> lines;

	for (int i = 0; i < theta_length; i++)
	{
		for (int j = 0; j < r_length; j++)
		{
			if (count_arr[i][j] > line_tresh)
			{
				int ma_value = count_arr[i][j];

				for (int theta_off = rho*-1; theta_off <= rho; theta_off++)
					for (int r_off = rho*-1; r_off <= rho; r_off++)
					{
						if ((theta_off + i > 0 && theta_off + i < theta_length) && ((r_off + j > 0) && (r_off + j < r_length)))  //边界检测
						{
							if (count_arr[theta_off + i][r_off + j] > ma_value)
							{
								ma_value = count_arr[theta_off + i][r_off + j];
									r_off = rho + 1;  //跳出2级循环
									theta_off = rho + 1;
							}
						}
					}
				if(ma_value>count_arr[i][j])
					continue;

				//i  theta   |  j  r
				int x0, x1, y0, y1;
				x0 = x1 = y0 = y1 = 0;
				int temp_radian = i*transform_radian;
				
				if (i > 45 && i < 135) //用竖线|标志
				{
					
					x0 = 0;
					y0 = (double)(j - r_length / 2) - ((x0 - width / 2)*cos(temp_radian)) / sin(temp_radian) + (height / 2);
				    x1 = width - 0;
					y1 = (double)(j - r_length / 2) - ((x0 - width / 2)*cos(temp_radian)) / sin(temp_radian) + (height / 2);
				}
				else                 //用横线标识
				{
					y0 = 0;
				    x0 = (double)(j - r_length / 2) - ((y0 - height / 2)*sin(temp_radian)) / cos(temp_radian) + (width / 2);
					y1 = height - 0;
					x1 = (double(j - r_length / 2)) - ((y1 - height / 2)*sin(temp_radian)) / cos(temp_radian) + (width / 2);
				}

				lines.push_back(make_pair(make_pair(x0, y0), make_pair(x1, y1)));

			  }
		  }

	  }


    for(auto line:lines)
	{
		(*res_mat)[line.first.first][line.first.second] = 155;
		(*res_mat)[line.second.first][line.second.first] = 155;
	}
	return res_mat;
	return nullptr;
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
	kernel *laplacian_kernel = get_laplacian(mask_type);
	filter *temp_filter = new filter(main_mat);
	Mat *sharpen_mat = new Mat(width, height);
	sharpen_mat = temp_filter->custom_kernel_op(laplacian_kernel);
	//res_mat->show_main_mat();

	Mat *res_mat = new Mat(width, height);
	double c = scale; //原图像与锐化后res=inital+ c(△2f(x,y)) 
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			(*res_mat)[i][j] = c * (*sharpen_mat)[i][j] + (*main_mat)[i][j];
		}
	delete sharpen_mat;
	delete temp_filter;
	//res_mat->show_main_mat();
	return res_mat;
	return nullptr;
}

Mat* transform:: sobel(bool type )   //1为complex 
{
	pair<kernel*, kernel*> sobel_kernel =get_sobel(3);
	filter *temp_filter =new filter(main_mat);

	Mat *res_mat = new Mat(width,height);


	//this->main_mat->show_main_mat();

	Mat *gx_res = temp_filter->custom_kernel_op(sobel_kernel.first);  //gx
	Mat *gy_res = temp_filter->custom_kernel_op(sobel_kernel.second);


	//gx_res->show_main_mat();
	//gy_res->show_main_mat();

	//res_mat->show_main_mat();

	if (type = true)   //使用欧式距离内个公式
	{
		for(int i=0;i<height;i++)
			for (int j = 0; j < width; j++)
			{
				double cur_gx = (*gx_res)[i][j];
				double cur_gy = (*gy_res)[i][j];
				(*res_mat)[i][j] = sqrt(cur_gx*cur_gx + cur_gy*cur_gy);
			}
	}

	if (type = false)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				double cur_gx = (*gx_res)[i][j];
				double cur_gy = (*gy_res)[i][j];
				(*res_mat)[i][j] = abs(cur_gx) + abs(cur_gy);
			}
	}

	//res_mat->show_main_mat();


	delete sobel_kernel.first;
	delete sobel_kernel.second;
	delete temp_filter;

	//res_mat->show_main_mat();
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
	//res_mat->show_main_mat();
	return res_mat;
	return nullptr;
}
Mat * transform::treshold(int tresh)  //自定义阈值二值化
{
	Mat *res_mat = new Mat(width, height);
	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			if ((*main_mat)[i][j] > tresh)
				(*res_mat)[i][j] = 255;
			else 
			{
				(*res_mat)[i][j] = 0;
			}
		}

	return res_mat;

	return nullptr;
}



Mat * transform::scharr()
{
	return op(get_op(SCHARR_OP),false);
	return nullptr;
}
Mat * transform::prewitt()
{
	return op(get_op(PREWITT_OP), false);
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
	//gxy_kernel->show_kernel();
	return gxy_kernel;
	return nullptr;
}

pair<kernel*, kernel*> transform::get_op(OP_TYPE type)
{
	//不予实现prewitt算子生成过程 
	double (*res_gx_)[3];
	double (*res_gy_)[3];



	//PREWITT_OP

	//		   1
	//1 0 -1  *1
	//         1
	double PREWITT_gx_[3][3] = { { 1,0,-1 },{ 1,0,-1 },{ 1,0,-1 } };
	//         1
	//1 1 1   *0
	//         -1

	double PREWITT_gy_[3][3] = { { 1,1,1 },{ 0,0,0 },{ -1,-1,-1 } };





	//SCHARR_OP
	//          1
	//3 10 1  * 0
	//          1

	double SCHARR_gx_[3][3] = { { 3,10,3 },{ 0,0,0 },{ -3,-10,-3 } };


	//		   1
	//1 0 -1 * 1
	//         1
	double SCHARR_gy_[3][3] = { { 1,0,-1 },{ 1,0,-1 },{ 1,0,-1 } };


	switch (type)
	{
	case PREWITT_OP:  //prewitt算子

		res_gx_ = PREWITT_gx_;
		res_gy_ = PREWITT_gy_;
		break;
	case SCHARR_OP://sscharr算子

		res_gx_ = SCHARR_gx_;
		res_gy_ = SCHARR_gy_;
		break;
	}


	double **res_gx = new double *[3];
	double **res_gy = new double *[3];
	for (int i = 0; i < 3; i++)
	{
		res_gx[i] = new double[3];
		res_gy[i] = new double[3];
		for (int j = 0; j < 3; j++)
		{

			res_gx[i][j] = res_gx_[i][j];
			res_gy[i][j] = res_gy_[i][j];
		}
	}
	kernel *gx_kernel = new kernel(res_gx,3,3);
	kernel *gy_kernel = new kernel(res_gy, 3, 3);
	return make_pair(gx_kernel,gy_kernel);
}
