#include "ImageSmoothing.h"

void BoxFilter(const Mat &SrcImg, Mat &DstImg,const int kernel)
{
    boxFilter(SrcImg, DstImg, -1, Size(kernel, kernel));
}
void blur_s(const Mat &SrcImg,Mat &DstImg,const int kernel)
{
    blur(SrcImg,DstImg,Size(kernel,kernel));
}
void MedianFiltering(const Mat &SrcImg, Mat &DstImg,const int kernel)
{
    medianBlur(SrcImg, DstImg, kernel);
}
void GaussianFiltering(const Mat &SrcImg, Mat &DstImg,const int kernel)
{
    GaussianBlur(SrcImg, DstImg, Size(kernel, kernel), 0);
}


//void BilateralFiltering(const Mat &SrcImg, Mat &DstImg)
//{
//    bilateralFilter(SrcImg, DstImg, 9, 70, 70);
//}
