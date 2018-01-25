#include "unit_test.h"

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

