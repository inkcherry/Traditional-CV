#pragma once
#include "Mat.h"
typedef std::pair<int, int> img_config;  //规定图像的长宽信息  

struct kernel //内核函数不提供计算功能  内核函数
{	
	img_config main_config;
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
	double **kernel_mat;
	double * operator[](int &index) { return kernel_mat[index]; }
	double * operator[](int &&index) { return kernel_mat[move(index)]; }

};


class filter;
class filterfactory   //工厂类 。。   有些核是特殊定义的  这个暂时未实现
{
public:
	enum kerneltype {aa,bb,cc,dd};
	filterfactory(Mat &main_mat_r, kerneltype &type) {}
	filter* filter_product;
private:
	filter* get_filter_product() { return filter_product; }
};



class filter   //滤波类 提供一般的滤波接口   会通过滤波修改Mat的值
{
public:
	explicit filter(Mat &main_mat_r) ;
	~filter();
	double**  convolution();  //卷积

	/*线性滤波函数 */
	void boxblur();//方框滤波
	void blur();   //均值滤波
	void GaussianBlur();//高斯滤波
private:
	kernel kernel_mat ;
	int width, height;
	Mat *main_mat;
};

