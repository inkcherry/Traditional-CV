#pragma once
#include "image.h"
#include "dft.h"
#include "D3DGraphics.h"
#include <cstring>
#include <string>
#include <iostream>
#include <functional>
class Mat   //需要先灰度化
{
public:
	
	explicit Mat(img_config &image, D3DCOLOR *surface);  //转换成矩阵
	void show_main_mat();
	~Mat();
	void dft();//change
private:
	void _conver_to_mat(D3DCOLOR *surface);
	int width;
	int height;
	unsigned char **main_mat;//主矩阵

};

