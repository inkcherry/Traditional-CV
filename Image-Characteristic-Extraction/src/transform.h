#include "filter.h"

class transform 
{
public:
	void canny(double threshod1,double threshod2, int size=3);  //size为sobel孔径大小
	//自定义规格算子
	Mat* sobel(int dx, int dy, int size, bool type = 1);
	Mat* laplacian(int ksize, double scale);
	//模板算子（无算子规格参数）
	Mat* sobel(bool type=1);
	Mat* laplacian();


	explicit transform(Mat* &main_mat_r);
	~transform();
	int width, height;
	Mat *main_mat;
private:

	pair<kernel*, kernel*> get_sobel(int size);//获取sobel算子 默认的sobel算子
	kernel* get_laplacian(int mask_type=1);//获取拉普拉算子,默认掩模为1类型的算子

	pair<kernel*, kernel*> get_sobel(int dx, int dy, int size);//自定义的soble内核 dx dy分别表示x y上的差分接数
	kernel* get_laplacian(int ksize,double scale);//ksize 用于计算二阶导滤波器孔径尺寸，scale表示可选比例因子
};


