#include <cmath>
#include <iostream>
const int channels = 1; //先试通道为1
double *initial_mat=nullptr;  //
void Bilateral_Filter(int width,int height,double *initial_mat,int r, double sigma_d, double sigma_r)
{
	int i, j, m, n, k;
	int nx = width, ny =height;
	int w_filter = 2 * r + 1; // 滤波器边长

	double gaussian_d_coeff = -0.5 / (sigma_d * sigma_d);
	double gaussian_r_coeff = -0.5 / (sigma_r * sigma_r);

	double** d_metrix = new double*[w_filter];  // spatial weight

	for (int i = 0; i < w_filter; i++)
	{
		d_metrix[i] = new double [w_filter];
	}

	double r_metrix[256];  // similarity weight

						   // copy the original image
	double* img_tmp = new double[channels * nx * ny];


	for (i = 0; i < ny; i++)
		for (j = 0; j < nx; j++)
			for (k = 0; k <channels; k++)
			{
				img_tmp[i * channels * nx + channels * j + k] = initial_mat[i * channels * nx + channels* j + k];
			}

	// compute spatial weight
	for (i = -r; i <= r; i++)
		for (j = -r; j <= r; j++)
		{
			int x = j + r;
			int y = i + r;

			d_metrix[y][x] = exp((i * i + j * j) * gaussian_d_coeff);
		}

	// compute similarity weight
	for (i = 0; i < 256; i++)
	{
		r_metrix[i] = exp(i * i * gaussian_r_coeff);
	}

	// bilateral filter
	for (i = 0; i < ny; i++)
		for (j = 0; j < nx; j++)
		{
			for (k = 0; k < channels; k++)
			{
				double weight_sum, pixcel_sum;
				weight_sum = pixcel_sum = 0.0;

				for (m = -r; m <= r; m++)
					for (n = -r; n <= r; n++)
					{
						if (m*m + n*n > r*r) continue;

						int x_tmp = j + n;
						int y_tmp = i + m;

						x_tmp = x_tmp < 0 ? 0 : x_tmp;
						x_tmp = x_tmp > nx - 1 ? nx - 1 : x_tmp;   // 边界处理，replicate
						y_tmp = y_tmp < 0 ? 0 : y_tmp;
						y_tmp = y_tmp > ny - 1 ? ny - 1 : y_tmp;

						int pixcel_dif = (int)abs(img_tmp[y_tmp * channels * nx +channels * x_tmp + k] - img_tmp[i * channels * nx + channels * j + k]);
						double weight_tmp = d_metrix[m + r][n + r] * r_metrix[pixcel_dif];  // 复合权重

						pixcel_sum += img_tmp[y_tmp *channels * nx + channels * x_tmp + k] * weight_tmp;
						weight_sum += weight_tmp;
					}

				pixcel_sum = pixcel_sum / weight_sum;
				initial_mat[i * channels * nx + channels * j + k] = pixcel_sum;

			} // 一个通道

		}


	delete[] img_tmp;
}
int main()
{
	double arr[12] = {
		1.0,2.0,3.0,
		4.5,4.5,4.5,
		5.0,6.0,7.0,
		8.0,9.0 ,8.0
	};
	initial_mat = new double[11];
	for (int i = 0; i < 12; i++)
	{
		initial_mat[i] = arr[i];
	}
	Bilateral_Filter(3, 4, initial_mat, 1, 1, 1);

	for (int i = 0; i < 12; i++)
	{
		std::cout << initial_mat[i]<<" ";
	}
	std::cout<<"\n";
	for (int i = 0; i < 12; i++)
	{
		std::cout << (int)((unsigned char)initial_mat[i]) << " ";
	}
	std::cin.get();
	return 0;
}
