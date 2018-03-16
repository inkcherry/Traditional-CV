#pragma once
#include "filter.h"

class morph     //考虑 把filter和morph写一个父类 
{
public:
	explicit morph(Mat* &main_mat_r);
	explicit morph(Mat* &main_mat_r, double **kernel);
	Mat *erode(const int& size, const double &element) { return morph_operate(true); }  //min
	Mat *dilate(const int & size, const double &element) {return morph_operate(false); } //max
	//核不应当作为成员 但是已经踩了坑 要微笑这继续踩下去


	//
	Mat *open_op(const int &size);   //腐蚀min+膨胀max 总体↓
	Mat *close_op(const int &szie);//膨胀+腐蚀 总体 ↑
	Mat *morph_grad(const int &size);   //梯度
	Mat *top_hat(const int &szie);//顶帽  原图像与开运算之差
	Mat *black_hat(const int &szie); //黑帽	原图像与闭运算之差

private:
	Mat *morph_operate(bool is_erode);
	kernel *kernel_mat;
	int width, height;
	Mat *main_mat;
};
