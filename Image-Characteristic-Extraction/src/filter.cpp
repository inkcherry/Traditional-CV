#include "filter.h"

filter::filter(Mat & main_mat_r):main_mat(&main_mat_r),
	width(main_mat_r.get_img_config().first),
	height(main_mat_r.get_img_config().second)
{
}

void filter::convolution()
{
}


//吸取dft写的很不友好的经验，全用double好了。
