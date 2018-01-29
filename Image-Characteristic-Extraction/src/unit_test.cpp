#include "unit_test.h"
#include "Mat.h"
#include "filter.h"

using namespace std;
	double** test::get_mat() {
		int arr[9] = { 1,2,3,4,5,6,7,8,9 };
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

	void unit::test_init_kernel() {
		double** test_mat = test::get_mat();
		//test::show_mat(test_mat, 3, 3);
		Mat *t_mat = new Mat(test_mat, 3, 3);
		filter t_fil(t_mat);
		t_fil.boxblur(3, 3);

		kernel *ke = t_fil.get_kernel();
		test::show_mat(ke->kernel_mat, ke->main_config.first, ke->main_config.second);
		t_fil.blur(3, 3);
		ke = t_fil.get_kernel();
		test::show_mat(ke->kernel_mat, ke->main_config.first, ke->main_config.second);
	}