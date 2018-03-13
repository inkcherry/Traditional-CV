#include "unit_test.h"
#include "Mat.h"
#include "filter.h"
#include "morph.h"

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
		after_morphop_mat2->show_main_mat();
		after_morphop_mat3->show_main_mat();
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




