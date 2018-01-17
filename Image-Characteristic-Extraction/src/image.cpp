#include "image.h"




image::image(D3DGraphics &d3d_, D3DCOLOR *image_surface_, const img_config &img_config_) :
	main_d3d(&d3d_),
	inital_image_surface(image_surface_),
	main_config(img_config_),
	fourier_surface(nullptr)
{
	//final_image_surface = new D3DCOLOR(img_config_.first*img_config_.second + 1);
}

image::~image()
{
}

void  image::show_initial_image()const
{
	_draw_image(100, 100, main_config.first, main_config.second, inital_image_surface, UP);
}

void image::Grayscale(int way)
{
	
	switch (way)
	{
	case 1:
		{int npiexls = (main_config.second)*(main_config.second);
			for (int i = 0; i < npiexls; i++)  //灰度处理  最大值法
			{
				unsigned char max_ = to_matrix_max(inital_image_surface[i]);
				final_image_surface[i] = D3DCOLOR_ARGB(max_, max_, max_, max_);
			}
		break;
		}
	case 2:
		{int npiexls = (main_config.second)*(main_config.second);
			for (int i = 0; i < npiexls; i++)  //灰度处理  最大值法
			{
				unsigned char max_ = to_matrix_avg(inital_image_surface[i]);
				final_image_surface[i] = D3DCOLOR_ARGB(max_, max_, max_, max_);
			}
		break;
		}
	default:
		break;
	}
	return; 
	
}
void image::ConverTo_Fourier_atlas(Mat &mat)
{
	fourier_surface = mat.get_fourier_surface();
}
unsigned char image::to_matrix_max(D3DCOLOR &color)          //将d3dcolor转换为u char
{
	unsigned char max_ = 0;
	for (int i = 0; i < 3; i++)
	{  
		unsigned char cur = ((color >> 16 - i * 8)&ANDD);
		max_=max_ >  cur? max_ : cur;   //第一位A不读取
	}
	return max_;
}
unsigned char image::to_matrix_avg(D3DCOLOR &color)
{
	int sum = 0;
	for (int i = 0; i < 3; i++)
	{
		sum =sum+ ((color >> 24 - i * 8)&ANDD);
	
	}
	return sum/3;
}
void image::show_final_image()const
{
	_draw_image(100, 100, main_config.first, main_config.second, final_image_surface, UP);
}
void image::show_fourier_image() const
{
	_draw_image(300, 300, main_config.first, main_config.second,fourier_surface, UP);
}
void  image::_draw_image(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf, DirectionState dec)const
{
	int AllPixel = (width)*(height);
	if (dec == UP)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				main_d3d->PutPixel(x + xoff, yoff + y, xsurf[x + y*width]);
			}
		}
	}
	if (dec == DOWN)
	{
		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = width - 1; x >= 0; x--)
			{
				main_d3d->PutPixel(x + xoff, yoff + y, xsurf[AllPixel - y*width - x]);
			}
		}
	}
	if (dec == LEFT)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				main_d3d->PutPixel(y + xoff, yoff + x, xsurf[x + y*width]);
			}
		}
	}
	if (dec == RIGHT)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				main_d3d->PutPixel(y + xoff, yoff + x, xsurf[AllPixel - y*width - x]);
			}
		}

	}
}
