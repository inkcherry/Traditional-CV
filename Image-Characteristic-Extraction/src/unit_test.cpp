#include "unit_test.h"
#include "Mat.h"
#include "filter.h"
#include "morph.h"
#include  "transform.h"

using namespace std;
	double** test::get_mat() {
		double arr[9] = {
			1,2,3,
			4,10,6,
			7,8,9
		};
		double ** mat=new double*[3];

		for (int i = 0; i < 3; i++)
		{
			mat[i] = new double[3];
			for (int j = 0; j < 3; j++)
			{
				mat[i][j] = arr[i * 3 + j];
			}
		}
		return mat;
}

	double** test::get_mat2() {
		double arr[12] = { 
			1.0,2.0,3.0,
			4.5,4.5,4.5,
			5.0,6.0,7.0,
			8.0,9.0 ,8.0
		};
		double ** mat = new double*[4];

		for (int i = 0; i < 4; i++)
		{
			mat[i] = new double[3];
			for (int j = 0; j < 3; j++)
			{
				mat[i][j] = arr[i * 3 + j];
			}
		}
		return mat;
	}


	void test::show_mat(double **mat_, const int &width, const int &height) {
		string show_mat = "";
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				show_mat += std::to_string(mat_[i][j]) + " ";
			}
			show_mat += "\n";

		}
		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)show_mat.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
	}

	void test::show_d3dmat(unsigned long * d3dmat, const int & width, const int & height)
	{
		string show_mat = "";
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				show_mat += std::to_string(d3dmat[i*height+width]) + " ";
			}
		show_mat += "\n";
		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)show_mat.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
	}

	void unit::test_init_kernel() {
		double** test_mat = test::get_mat();
		//test::show_mat(test_mat, 3, 3);
		Mat *t_mat = new Mat(test_mat, 3, 3);
		filter t_fil(t_mat);


		t_fil.GaussianBlur(3, 1);

		kernel *ke = t_fil.get_kernel();
		test::show_mat(ke->kernel_mat, ke->main_config.first, ke->main_config.second);
		/*	t_fil.blur(3, 3);
			ke = t_fil.get_kernel();
			test::show_mat(ke->kernel_mat, ke->main_config.first, ke->main_config.second);*/
	}


	void unit::test_medianblur() {
		double** test_mat = test::get_mat();
		//test::show_mat(test_mat, 3, 3);
		Mat *t_mat = new Mat(test_mat, 3, 3);
		filter t_fil(t_mat);


		Mat *res_mat = t_fil.medianblur();

		res_mat->show_main_mat();
		//kernel *ke = t_fil.get_kernel();

	}


	void unit::test_bliateralblur() {
		double **mat = test::get_mat2();
		test::show_mat(mat, 3, 4);
		Mat *inital_mat = new Mat(mat, 3, 4);
		
		filter t_fi(inital_mat);
		Mat *res_mat = t_fi.bliateralblur(30, 10, 10);
		res_mat->show_main_mat();

	}

	void unit::test_morph()
	{
		/*	Mat *mat = new Mat(test::get_mat(),3,3);
			morph mor_unit(mat);
			Mat *after_morphop_mat = mor_unit.dilate(3,3);
			after_morphop_mat->show_main_mat();*/


		Mat *mat2 = new Mat(test::get_mat2(), 3, 4);
		morph mor_unit2(mat2);
		//Mat *after_morphop_mat2 = mor_unit2.dilate(3, 3);
		Mat *after_morphop_mat2 = mor_unit2.erode(3, 3);
		after_morphop_mat2->show_main_mat();

	}

	void unit::test_morph2()
	{
		Mat *mat2 = new Mat(test::get_mat2(), 3, 4);
		morph mor_unit2(mat2);
		//Mat *after_morphop_mat2 = mor_unit2.dilate(3, 3);
		Mat *after_morphop_mat2 = mor_unit2.open_op(3);
		after_morphop_mat2->show_main_mat();
	}

	void unit::test_morph3()
	{
		Mat *mat2 = new Mat(test::get_mat2(), 3, 4);
		morph mor_unit2(mat2);
		//Mat *after_morphop_mat2 = mor_unit2.dilate(3, 3);
		Mat *after_morphop_mat2 = mor_unit2.top_hat(3);
		Mat *after_morphop_mat3 = mor_unit2.black_hat(3);
		Mat *after_morphop_mat4 = mor_unit2.morph_grad(3);

	/*	after_morphop_mat2->show_main_mat();
		after_morphop_mat3->show_main_mat();*/
		after_morphop_mat4->show_main_mat();
	}

	image** unit::test_transform(Mat* &insert_mat)
	{

		typedef shared_ptr<D3DCOLOR>  sh_D3D;
		sh_D3D* sh_res_mat = new sh_D3D[2];  //由于布局不够合理，智能指针和普通指针有些混用，此处暂时需使用智能指针的指针类型，防止自动析构，以便于调试
		//insert_mat->show_main_mat();
		

		transform *ts = new transform(insert_mat);

		Mat* res_mat[2];
		
		image** res_img = new image*[2];



		
		res_mat[0] = ts->sobel();
		res_mat[1] = ts->laplacian();





		//res_mat[0]->show_main_mat();

	   sh_res_mat[0]=res_mat[0]->conver_to_d3dmat();
	   sh_res_mat[1] = res_mat[1]->conver_to_d3dmat();

	   res_img[0] = new image(*gobal_d3d, sh_res_mat[0].get(), insert_mat->get_img_config());
	   res_img[1] = new image(*gobal_d3d, sh_res_mat[1].get(), insert_mat->get_img_config());

	   //调试内容
	   //int a = (int)res_img[0];
	   //int b = (int)res_img[1];

	   //res_img[0]->show_digital_mat();
	   //res_img[0]->show_digital_mat();

	   //调试内容
	  /* Mat test123(res_img[0]->get_img_config(), res_img[0]->get_inital_surface());
	   test123.show_main_mat();*/

	   return  res_img;
}



	double ** unit::test_conv() {
		double **mat = test::get_mat();
		Mat  *analog_matrix = new Mat(mat, 3, 3);
		filter t_fi(analog_matrix);
		t_fi.boxblur(3, 3);//大小为3，3的核 方框滤波
		//t_fi.GaussianBlur(3, 3);
		double **after_conv_mat = t_fi.convolution();
		test::show_mat(after_conv_mat, 3, 3);
		return after_conv_mat;
	}
	image ** unit::test_treshold(Mat *& insert_mat)
	{
		typedef shared_ptr<D3DCOLOR>  sh_D3D;
		sh_D3D* sh_res_mat = new sh_D3D[2];  //由于布局不够合理，智能指针和普通指针有些混用，此处暂时需使用智能指针的指针类型，防止自动析构，以便于调试
											 //insert_mat->show_main_mat();


		transform *ts = new transform(insert_mat);

		Mat* res_mat[2];
		Mat* after_treshold_mat[2];  //阈值化处理之后的矩阵
		image** res_img = new image*[2];


		res_mat[0] = ts->sobel();
		res_mat[1] = ts->laplacian();
		transform a_t_r_m_1 =  transform(res_mat[0]);			
		transform a_t_r_m_2 = transform(res_mat[1]);


		after_treshold_mat[0] = a_t_r_m_1.treshold(100);  //阈值处理
		after_treshold_mat[1] = a_t_r_m_2.treshold(100);

		sh_res_mat[0] = after_treshold_mat[0]->conver_to_d3dmat();
		sh_res_mat[1] = after_treshold_mat[1]->conver_to_d3dmat();

		res_img[0] = new image(*gobal_d3d, sh_res_mat[0].get(), insert_mat->get_img_config());
		res_img[1] = new image(*gobal_d3d, sh_res_mat[1].get(), insert_mat->get_img_config());


		return res_img;
		return nullptr;
	}

	void unit::test_sobel()
	{
		double **mat = test::get_mat();
		Mat  *test_mat = new Mat(mat, 3, 3);
		transform *test_sobel = new transform(test_mat);
		test_sobel->sobel(1);  

	}

	void unit::test_laplace()
	{
		double **mat = test::get_mat();
		Mat  *test_mat = new Mat(mat, 3, 3);
		transform *test_laplace = new transform(test_mat);
		test_laplace->laplacian();


	}

	image* unit::test_hough(Mat* &insert_mat)
	{

		typedef shared_ptr<D3DCOLOR>  sh_D3D;
		sh_D3D *sh_res_mat = new sh_D3D ;
		transform  trans(insert_mat);
		Mat *after_hough_mat = trans.hough_transform(4,5, 1);
		

		after_hough_mat->show_main_mat();

		image* res_img =nullptr;





		*sh_res_mat = after_hough_mat->conver_to_d3dmat();
		res_img = new image(*gobal_d3d, (*sh_res_mat).get(), insert_mat->get_img_config());

		
		return res_img;
	



	}




