#include "filter.h"

class transform 
{
public:
	void canny(double threshod1,double threshod2, int size=3);  //size为sobel孔径大小


	Mat* sobel(bool type=1);
	explicit transform(Mat* &main_mat_r);
	~transform();
	int width, height;
	Mat *main_mat;
private:
	pair<kernel*, kernel*> get_sobel(int size);//获取sobel算子
};