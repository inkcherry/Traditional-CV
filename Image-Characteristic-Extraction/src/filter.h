#pragma once
#include "Mat.h"
typedef std::pair<int, int> img_config;  //规定图像的长宽信息  

struct kernel //内核函数不提供计算功能  内核函数
{	
	img_config main_config;
	//测试
	kernel() :kernel_mat(new double *[3]),main_config(make_pair(3, 3))   //默认矩阵3*3 1，2，1     0 0 0  -1 -2 -3
	{
		int default_arr[9] = { 1,2,1,0,0,0,-1,-2,-1 };
		for (int i = 0; i < 3; i++)
		{
			kernel_mat[i] = new double[3];
			for (int j = 0; j < 3;j++)
			{
				kernel_mat[i][j] = default_arr[i * 3 + j];
			}
		}
	}


	explicit kernel(int &width, int &height) :kernel_mat(new double *[height]), main_config ( make_pair(width, height))
	{
		for (int i = 0; i < width; i++)
		{
			kernel_mat[i] = new double[width];
		}
	}
	//数组初始化
	explicit kernel( double** &kernel_mat_, int &width, int &height) :kernel_mat(kernel_mat_), main_config(make_pair(width, height)) {};
	explicit kernel(double** &kernel_mat_, int &&width, int &&height) :kernel_mat(kernel_mat_), main_config(make_pair(move(width), move(height))) {};
	void show_kernel() {
		if (kernel_mat == nullptr)
		{
			int msgboxID = MessageBox(
				NULL,

				(LPCSTR)L"NULLPTR(mat)",
				(LPCSTR)L"Account Details",
				MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
			);
			return;
		}

		string show_mat = "";
		for (int i = 0; i < main_config.second; i++)
		{
			for (int j = 0; j < main_config.first; j++)
			{


				show_mat += std::to_string(kernel_mat[i][j]) + " ";
			}
			show_mat += "\n";

		}
		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)show_mat.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
	}
public:
	double **kernel_mat;
	double * operator[](int &index) { return kernel_mat[index]; }
	double * operator[](int &&index) { return kernel_mat[move(index)]; }

};


//class filter;
class kernel_factory  //工厂类 。。   有些核是特殊定义的  这个暂时未实现
{
public:
	enum kerneltype {box,blur,gaussianblur};
	kernel_factory(Mat* & main_mat_r,const int &k_width,const int &k_height, kerneltype  typ, const double &gaussian_sigma=0);
	kernel* get_factory_kernel() { return factory_kernel; }
private:
	kernel *factory_kernel;
	void init_box_kernel(Mat* &main_mat_r, const int &k_width,const  int &k_height);
	void init_gaussianblur_kernel(Mat* &main_mat_r,const int &k_size, const double &sigama);
	void init_blur_kernel(Mat* &main_mat_r,const int &k_width,const int &k_height);
};






class filter   //滤波类 提供一般的滤波接口   会通过滤波修改Mat的值
{
public:
	explicit filter(Mat* &main_mat_r) ;
	~filter();
	double**  convolution();  //卷积  设为友元是为了让为形态学操作提供接口;

	/*线性滤波函数 */  //参数为核函数大小
	void boxblur(const int &kernel_width,const int &kernel_height);//方框滤波
	void blur(const int &kernel_width, const int &kernel_height);   //均值滤波
	void GaussianBlur(const int &kernel_size, const double &sigma);//高斯滤波
	
	/*End*/





	/*非线性滤波函数*/
	/*非线性滤波无需卷积操作.滤波函数及返回结果矩阵*/
	Mat*  medianblur();       //中值滤波（尖锐斑点 椒盐噪音去除）
	Mat*  bliateralblur(int r, int sigma_d, int sigma_r);   //双边滤波
	/*End*/


	Mat *custom_kernel_op(kernel *&custom_kernel);   //对外提供一个接受自定义核的函数，以支持像sobel这样的操作
	kernel*  get_kernel(){ return kernel_mat; }
private:
	kernel *kernel_mat ;
	int width, height;
	Mat *main_mat;
};


