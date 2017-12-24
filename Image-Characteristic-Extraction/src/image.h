#pragma once
#include "D3DGraphics.h"
#include <iostream>
typedef std::pair<int, int> img_config;  //规定图像的长宽信息

class image
{
public:
	enum DirectionState
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	image(D3DGraphics &d3d_,D3DCOLOR *image_surface,const img_config &img_onfig) ;   
	~image();
	void show_initial_image();  //处理前的图像
	void show_final_image();	//处理后的图像
	
	//....
	//treat function

	//
	void Grayscale(int way);// 灰度化处理 way为方法
	void _draw_image(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf, DirectionState dec);
	unsigned char to_matrix_max(D3DCOLOR &color);           //将d3dcolor转换为u char
	unsigned char to_matrix_avg(D3DCOLOR &color);           

private:
	img_config main_config;
	D3DGraphics *main_d3d;
	D3DCOLOR *inital_image_surface;
	D3DCOLOR final_image_surface[30000];
};

