#include "filter.h"
#include "morph.h"
filter::filter(Mat*  &main_mat_r):main_mat(main_mat_r),
width(main_mat_r->get_img_config().first),
height(main_mat_r->get_img_config().second),
kernel_mat(nullptr)//默认
{
}


filter::~filter()
{
	   //emmm这个地方应该用智能指针的 不好整了 此处为坑
	/*	delete kernel_mat;*/
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

	double near_arr[9] = { 0 };
	double **res_mat = new double *[height];
	for (int i = 0; i < height; i++)
		res_mat[i] = new double[width];

	function<int(double arr[9],int low,int height)>get_find_index = 
		[&](double arr[9], int low, int high) {
		int temp = arr[low];
		int pt = arr[low]; //
		while (low != high)
		{
			while (low < high && arr[high] >= pt)
				high--;
			arr[low] = arr[high];

			while (low < high && arr[low] <= pt)
				low++;
			arr[high] = arr[low];
		}
		arr[low] = temp;
		return low;
	
	};





	function<int(double arr[9], int low, int height)> find_median =   //找第中间值 
		[&get_find_index,&find_median](double arr[9], int low, int high)->double
	{
      //考虑 1丢弃一侧数据的快排 ，2堆排，3建树  4维护单调数组
	
		int temp_index;
		temp_index = get_find_index(arr, low,high );
		if (temp_index == 4)
		{  
	
			return arr[temp_index];
		}
		else if (temp_index > 4)
		{
			return find_median(arr, low, temp_index - 1);
		}
		else 
		{
			return find_median(arr, temp_index + 1, high);
		}
		return 0.0;
	};
	
	
	
	
	
	
	//边缘地带
	const int bottom_index = height - 1;
	const int right_index = width - 1;
	for (int i = 0; i < width; i++)  //=  
	{
		res_mat[0][i] =(*main_mat)[0][i];
		res_mat[bottom_index][i] = (*main_mat)[bottom_index][i];
	}
	

	for (int j = 0; j < height; j++)// ||
	{
		res_mat[j][0] = (*main_mat)[j][0];
		res_mat[j][right_index] = (*main_mat)[j][right_index];
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
					near_arr[near_arr_index++] = (*main_mat)[k][l];
				}
			res_mat[i][j] = find_median(near_arr, 0, 8);

		}

	Mat *res_mat_ = new Mat(res_mat, width, height);



	/*res_mat_->show_main_mat();*/


	return res_mat_;
}

Mat * filter::bliateralblur(int r,int sigma_d,int sigma_r)   //滤波器边长   sigma参数 d ,r
{

	//暂时处理目标为通道为1（灰度图像）
	const  int channels = 1;
	Mat &inital_mat=*main_mat;  

	//初始化结果矩阵
	double **res_mat = new double *[height];
	for (int i = 0; i < height; i++)
		res_mat[i] = new double[width];




	int i, j, m, n, k;
	int nx = width, ny = height;
	int w_filter = 2 * r + 1; // 滤波器边长  

	double gaussian_d_coeff = -0.5 / (sigma_d * sigma_d);
	double gaussian_r_coeff = -0.5 / (sigma_r * sigma_r);

	double** d_metrix = new double*[w_filter];  // spatial weight  



	//如果考虑为Mat添加多通道  在此处处理
	for (int i = 0; i < w_filter; i++)
	{
		d_metrix[i] = new double[w_filter];
	}


	double r_metrix[256];  // similarity weight  

						   // copy the original image  
	//double* img_tmp = new double[channels * nx * ny];


	//for (i = 0; i < ny; i++)
	//	for (j = 0; j < nx; j++)
	//		for (k = 0; k < channels; k++)
	//		{
	//			img_tmp[i * channels * nx + channels * j + k] = initial_mat[i * channels * nx + channels* j + k];
	//		}

	// compute spatial weight  
	for (i = -r; i <= r; i++)
		for (j = -r; j <= r; j++)
		{
			int x = j + r;
			int y = i + r;

			d_metrix[y][x] = exp((i * i + j * j) * gaussian_d_coeff);
		}

	// compute similarity weight  
	for (i = 0; i < 256; i++)
	{
		r_metrix[i] = exp(i * i * gaussian_r_coeff);
	}

	// bilateral filter  
	for (i = 0; i < ny; i++)  //0 2 1 0
		for (j = 0; j < nx; j++)
		{
			for (k = 0; k < channels; k++)
			{
				double weight_sum, pixcel_sum;
				weight_sum = pixcel_sum = 0.0;

				for (m = -r; m <= r; m++)
					for (n = -r; n <= r; n++)
					{
						if (m*m + n*n > r*r) continue;

						int x_tmp = j + n;
						int y_tmp = i + m;

						x_tmp = x_tmp < 0 ? 0 : x_tmp;
						x_tmp = x_tmp > nx - 1 ? nx - 1 : x_tmp;   // 边界处理，replicate  
						y_tmp = y_tmp < 0 ? 0 : y_tmp;
						y_tmp = y_tmp > ny - 1 ? ny - 1 : y_tmp;

						int pixcel_dif = (int)abs(inital_mat[y_tmp][x_tmp] - inital_mat[i][j]);
						double weight_tmp = d_metrix[m + r][n + r] * r_metrix[pixcel_dif];  // 复合权重  

						double kk = inital_mat[y_tmp][x_tmp];
						double kkk = pixcel_sum;


						if (i == 0 && j == 2 && m == 1 && n == 0) 
						{
							int a = 3;
						}
						pixcel_sum +=inital_mat[y_tmp][x_tmp] * weight_tmp;
						

						weight_sum += weight_tmp;


						
					}

				pixcel_sum = pixcel_sum / weight_sum;
				res_mat[i][j] = pixcel_sum;
				////res_mat[i][j][c]   c表示未来粗处理多通道添加量 


			
			} // 一个通道  

		}


	//delete[] img_tmp;


	Mat *res_mat_ = new Mat(res_mat, width, height);
	return res_mat_;

	return nullptr;
}

Mat * filter::custom_kernel_op(kernel *& custom_kernel)
{
	
	kernel_mat = custom_kernel;
	Mat *res_mat_ = new Mat(convolution(),this->width, this->height);
	return res_mat_;
	return nullptr;
}

//吸取dft写的很不友好的经验，全用double。。。

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

