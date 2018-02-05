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
	/*初始化结果矩阵和辅助矩阵*/
	int res_height = height + kernel_mat->main_config.second ;
	int res_width = width + kernel_mat->main_config.first ;

	int h_main_mat = height;
	int w_main_mat = width;

	int h_kernel_mat = kernel_mat->main_config.first;
	int w_kernel_mat = kernel_mat->main_config.second;

	double **res_mat=new double *[res_height];  //结果矩阵 形势与原矩阵相同
	double **r_res_mat = new double *[h_main_mat];


	for (int i = 0; i <= res_height; i++)
	{
		res_mat[i] = new double[res_width];
		for (int j = 0; j < res_width; j++)
			res_mat[i][j] = 0;
		//memset(res_mat[i], 0, sizeof(res_mat[i]));
	}

	for (int i = 0; i < h_main_mat; i++)
		r_res_mat[i] = new double[w_main_mat];

	std::function<void()> delete_res_mat = [&]() {
		for (int i = 0; i < res_height; i++)
		{
			delete[]res_mat[i];
			//res_mat[i] = nullptr;
		}
		//delete[] res_mat;    //??????????

	};

	/**/
	

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
		//return res_mat;//emmm这个运算矩阵 需要将他转换为真正矩阵  。。。。
		//通过copy实现
		for (int i = 1; i < h_main_mat + 1; i++)
		{
			for (int j = 1; j < w_main_mat + 1; j++)
				r_res_mat[i - 1][j - 1] = res_mat[i][j];
			
		}


		delete_res_mat(); //删除辅助运算的矩阵



		return r_res_mat;
}
void filter::boxblur(const int & kernel_width, const int & kernel_height)
{
	
	kernel_factory pro(main_mat,kernel_width, kernel_height, kernel_factory::box);
	kernel_mat = pro.get_factory_kernel();
}
void filter::blur(const int & kernel_width, const int & kernel_height)
{
	kernel_factory pro(main_mat, kernel_width, kernel_height, kernel_factory::blur);
	kernel_mat = pro.get_factory_kernel();
}
void filter::GaussianBlur(const int & kernel_size, const double & sigma)
{
	kernel_factory pro(main_mat, kernel_size, kernel_size, kernel_factory::gaussianblur, sigma);
	kernel_mat = pro.get_factory_kernel();
}


Mat* filter::medianblur()
{
	double **res_mat = new double *[height];
	for (int i = 0; i < height; i++)
		res_mat[i] = new double[width];


	function<double(double arr[9])>find_median =   //找第中间值 
		[](double arr[9])
	{

		return arr[1];
	};
	
	
	
	
	double near_arr[9] = {0};
	
	//边缘地带
	const int bottom_index = height - 1;
	const int right_index = width - 1;
	for (int i = 0; i < width; i++)  //=  
	{
		res_mat[0][i] = *main_mat[0][i];
		res_mat[bottom_index][i] = *main_mat[bottom_index][i];
	}
	

	for (int j = width - 1; j < height; j++)// ||
	{
		res_mat[j][0] = *main_mat[j][0];
		res_mat[j][right_index] = *main_mat[j][0];
	}



	//中心地带
	for(int i=1;i<height-1;i++)
		for (int j = 1; j < width-1; j++)
		{
			int top = i - 1, bottom = i + 1;
			int left = j - 1, right = j + 1;
			int near_arr_index = 0;
			for(int k=top;k<=bottom;k++)
				for (int l = left; l <= right; l++)
				{
					near_arr[near_arr_index++] = *main_mat[i][j];
					res_mat[i][j] = find_median(near_arr);
				}
		}

	Mat *res_mat_ = new Mat(res_mat, width, height);
	return res_mat_;
}

//吸取dft写的很不友好的经验，全用double好了。

kernel_factory::kernel_factory(Mat* &main_mat_r, const int &k_width,const int &k_height,kerneltype  type,const double& gaussian_sigma)
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
		init_gaussianblur_kernel(main_mat_r, k_width, gaussian_sigma);  //這裏有點不一樣
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

void kernel_factory::init_gaussianblur_kernel(Mat* &main_mat_r, const int &k_size, const double &sigma)
{
	const int center = k_size / 2;
	double sum = 0;
	double **gaussiankernel_mat = new double*[k_size];
	for (int i = 0; i < k_size; i++)
		gaussiankernel_mat[i] = new double[k_size];



	for (int i = 0; i < k_size; i++)
	{
		for (int j = 0; j < k_size; j++)
		{
			gaussiankernel_mat[i][j] = exp(-((i - center)*(i - center) + (j - center)*(j - center)) / (2.0*sigma*sigma));
			sum += gaussiankernel_mat[i][j];
		}
	}


	for (int i = 0; i < k_size; i++)
	{
		for (int j = 0; j < k_size; j++)
		{
			gaussiankernel_mat[i][j] = gaussiankernel_mat[i][j] / sum;
		}
	}
	factory_kernel = new kernel(gaussiankernel_mat, const_cast<int &>(k_size), const_cast<int &>(k_size));
}

void kernel_factory::init_blur_kernel(Mat* & main_mat_r, const int &k_width, const int &k_height)//中值滤波
{
	double **kernel_mat = new double*[k_height];
	for (int i = 0; i < k_height; i++)
	{
		kernel_mat[i] = new double[k_width];
		for (int j = 0; j < k_width; j++)
		{
			kernel_mat[i][j] = 1.0/((k_width)+(k_height));
		}
	}
	factory_kernel = new kernel(kernel_mat, const_cast<int &>(k_width), const_cast<int &>(k_height));
}
