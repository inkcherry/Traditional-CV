#include "Mat.h"
#include "dfa.h"

Mat::Mat( img_config &image,  D3DCOLOR *surface): width(image.first), height(image.second)
{
	_conver_to_mat(surface);
}


void Mat:: _conver_to_mat(D3DCOLOR *surface)
{
	int n_piexls = width*height;   //定义全部像素
	
	main_mat= new unsigned char*[height];  // 定义一个 用于处理的矩阵
	for (int i = 0; i < height; i++)   //将D3D换成mat矩阵 
	{
		main_mat[i] = new unsigned char[width];
		for (int j = 0; j < width; j++)
		{
			//zhelijiang d3dcolor fanyichengzhongwen
			main_mat[i][j] = (unsigned char)(surface[i*width + j] << 24);
			//main_mat[i][j] = 0;   //test
		}
	}

}
void Mat::show_main_mat()
{
	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			std::cout << main_mat[i][j] << std::endl;
		}
}
Mat::~Mat()
{
	delete main_mat;
}
void Mat::dft()
{
	f_1A_matrix<unsigned char> inputarray;
	f_2A_matrix<unsigned char> outputarray;
	init_matrix(main_mat, 5, 3, inputarray);  //初始化矩阵
	dft_2d(inputarray, outputarray);         //转换后ouypuy矩阵为 要处理的矩阵
}