#pragma once
#include "filter.h"

class morph     //考虑 把filter和morph写一个父类 
{
public:
	explicit morph(Mat* &main_mat_r);
	explicit morph(Mat* &main_mat_r, double **kernel);
	Mat *erode(const int& size, const double &element) { return morph_operate(true); };
	Mat *dilate(const int & size, const double &element) {return morph_operate(false); };
	//核不应当作为成员 但是已经踩了坑 要微笑这继续踩下去


private:
	Mat *morph_operate(bool is_erode);
	kernel *kernel_mat;
	int width, height;
	Mat *main_mat;
};
