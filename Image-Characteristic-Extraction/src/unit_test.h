#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <Windows.h>
#include "Mat.h"
#include "image.h"
extern  D3DGraphics* gobal_d3d;
namespace test {
	double** get_mat();
	double ** get_mat2();
	void show_mat(double **mat_, const int &width, const int &height);
	void show_d3dmat(unsigned long *d3dmat,const int &width, const int &height) ;
}

namespace unit {
	void test_medianblur();
	void test_init_kernel();
	void test_bliateralblur();
	void test_morph();
	void test_morph2();   //open_op   close_op
	void test_morph3();   //high_hat  black_hat  grap
	image** test_transform(Mat* &intsert_mat);
	void test_sobel();
	void test_laplace();
	double** test_conv();
	Mat* test_affine(Mat* insert_mat);
	image* test_hough(Mat* &insert_mat);
	image **test_treshold(Mat* &insert_mat);
	
}