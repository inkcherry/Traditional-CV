#include <cmath>
#include <iostream>


double** getgaussiankernel(const int& size, const double& sigma);
void show_mat(double** &mat, const int &height, const int &width);
int main()
{
    double **g_mat = getgaussiankernel(3, 1);
    show_mat(g_mat, 3, 3);
    return 0;
}
double** getgaussiankernel(const int& size, const double& sigma)
{
    const int center = size / 2;
    double sum = 0;
    double **gaussiankernel_mat = new double*[size];
    for (int i = 0; i < size; i++)
        gaussiankernel_mat[i] = new double[size];



    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gaussiankernel_mat[i][j] = exp(-((i - center)*(i - center) + (j - center)*(j - center)) / (2.0*sigma*sigma));
            sum += gaussiankernel_mat[i][j];
        }
    }


    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gaussiankernel_mat[i][j] = gaussiankernel_mat[i][j] / sum;
        }
    }
    return gaussiankernel_mat;
}


void show_mat(double** &mat, const int &height, const int &width)
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            std::cout << mat[i][j];
        std::cout << "\n";
    }

}
