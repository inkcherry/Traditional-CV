#include "filter.h"
#include <typeindex>
#include <typeinfo>
#include <map>
struct affine_mat //用于仿射变换的矩阵
{	
	double main_affine_mat[6] = { 0 };
	int width, height;
	affine_mat() {

	}

	Mat * operator *( Mat *&main_mat)const
	{
		
		int res_mat_height = height * 2;
		int res_mat_width = width * 2;
		Mat *test_res_mat = new Mat(res_mat_height,res_mat_width);   //测试矩阵
		
		for(int y=0;y<res_mat_height;y++)
			for (int x= 0; x < res_mat_width; x++)
			{

				int new_x = round((main_affine_mat[0] + main_affine_mat[1] + main_affine_mat[2])*(double)x);
				int new_y = round((main_affine_mat[3] + main_affine_mat[4] + main_affine_mat[5])*(double)y);
				
				(*test_res_mat)[new_x][new_y] = (*main_mat)[y][x];
			}
	}
	virtual ~affine_mat() {};   
};





struct rotate_affine_mat:public affine_mat
{
	rotate_affine_mat(double theta) {
		main_affine_mat[4]=main_affine_mat[0] = cos(theta);
		main_affine_mat[3] = sin(theta);
		main_affine_mat[1] = -1 * main_affine_mat[3]; //-sin(theata);
	}
	~rotate_affine_mat() {};
};


class transform 
{
public:
	enum OP_TYPE{SCHARR_OP=1,PREWITT_OP=2}; //另外两个算子 scharr  prewitt
	enum AFFINE_TYPE { ROTATE=1 };
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


	Mat* affine(AFFINE_TYPE type,int parax,int para2);   //仿射变换


	Mat* hough_transform(double rho,int r_tresh, bool is_binary_mat);             //霍夫变换 此行为需要先二值化  默认为已经二值化



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


