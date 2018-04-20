#include "filter.h"

class transform 
{
public:
	enum OP_TYPE{SCHARR_OP=1,PREWITT_OP=2}; //另外两个算子 scharr  prewitt

	void canny(double threshod1,double threshod2, int size=3);  //size为sobel孔径大小
	//自定义规格算子 sobel生成还没写 ！
	Mat* sobel(int dx, int dy, int size, bool type = 1);
	Mat* laplacian(int ksize, double scale);
	
	//模板算子（无算子规格参数）
	Mat* sobel(bool type=1);
	Mat* laplacian();
	Mat* treshold(int tresh);   //阈值操作 全局阈值 自定义的待实现

	Mat* scharr();
	Mat* prewitt();

	Mat* op(pair<kernel*,kernel*>kernel_,bool type);  //算子运算



	Mat* hough_transform(double theta_length_ ,double r_length_,int tresh , bool is_binary_mat);             //霍夫变换 此行为需要先二值化  默认为已经二值化



	explicit transform(Mat* &main_mat_r);
	~transform();
	int width, height;
	Mat *main_mat;
private:

	pair<kernel*, kernel*> get_sobel(int size);//获取sobel算子 默认的sobel算子
	kernel* get_laplacian(int mask_type=1);//获取拉普拉算子,默认掩模为1类型的算子

	pair<kernel*, kernel*> get_sobel(int dx, int dy, int size);//自定义的soble内核 dx dy分别表示x y上的差分接数
	kernel* get_laplacian(int ksize,double scale);//ksize 用于计算二阶导滤波器孔径尺寸，scale表示可选比例因子 



	//另外两个算子

	pair<kernel*, kernel*>get_op(OP_TYPE type);   //获取算子

	//pair<kernel*, kernel*> get_scharr();
	//pair<kernel*, kernel*> get_prewitt();
};


