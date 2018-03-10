#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <Windows.h>
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
	double** test_conv();
	
}