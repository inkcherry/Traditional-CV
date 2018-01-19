#pragma once
#include "Mat.h"
class filter   //滤波类 提供一般的滤波接口   会通过滤波修改Mat的值
{

public:
	filter(Mat &main_mat_r);
	~filter();
	void  convolution();  //卷积

	/*线性滤波函数 */
	void boxblur();//方框滤波
	void blur();   //均值滤波
	void GaussianBlur();//高斯滤波
	
private:
	int width, height;
	Mat *main_mat;
};

