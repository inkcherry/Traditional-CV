#pragma once
#include "image.h"
#include "dfa.h"
#include "D3DGraphics.h"
class Mat   //需要先灰度化
{
public:
	Mat(img_config &image,D3DCOLOR *surface);  //转换成矩阵
private:
	void _conver_to_mat(D3DCOLOR *surface);
	int width;
	int height;
	unsigned char **main_mat;//主矩阵
	~Mat();
};

