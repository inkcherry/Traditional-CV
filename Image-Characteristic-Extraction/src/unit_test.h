#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <Windows.h>
namespace test {
	double** get_mat();
	void show_mat(double **mat_, const int &width, const int &height);
}