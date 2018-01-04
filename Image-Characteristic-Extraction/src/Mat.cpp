#include "Mat.h"


Mat::Mat(img_config &image, D3DCOLOR *surface): width(image.first), height(image.second)
{
	_conver_to_mat(surface);
}


void Mat:: _conver_to_mat(D3DCOLOR *surface)
{
	main_mat= new unsigned char*[height];
	for (int i = 0; i < height; i++)   //½«D3D»»³Émat¾ØÕó 
	{
		main_mat[i] = new unsigned char[width];
		for (int j = 0; j < width; j++)
		{
			main_mat[i][j] = 0;   //test
		}
	}
}
Mat::~Mat()
{

}
