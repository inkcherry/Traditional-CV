#pragma once
#include "image.h"
#include "dft.h"
#include "D3DGraphics.h"
#include <cstring>
#include <string>
#include <iostream>
#include <functional>
typedef std::pair<int, int> img_config;  //规定图像的长宽信息  
class Mat   //需要先灰度化
{
public:
	
	explicit Mat(img_config &image, D3DCOLOR *surface);  //转换成矩阵
	void show_main_mat();
	~Mat();
	f_2A_matrix<double> dft();//change  
	D3DCOLOR *get_fourier_surface();   //获取傅里叶图谱 
private:
	void _conver_to_mat(D3DCOLOR *surface);
	int width;
	int height;
	unsigned char **main_mat;//主矩阵

};

