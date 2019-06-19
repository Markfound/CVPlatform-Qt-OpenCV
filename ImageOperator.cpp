#include "ImageOperator.h"

void Laplacian_s(const Mat &SrcImg, Mat &DstImg, const int KernelSize)
{
    GaussianBlur(SrcImg, SrcImg, Size(KernelSize, KernelSize), 0, 0, BORDER_DEFAULT);
    Laplacian(SrcImg, DstImg, CV_64F, KernelSize);
    convertScaleAbs(DstImg, DstImg);
}

void Canny_s(const Mat &SrcImg, Mat &DstImg, const int apertureSize, const double threshold1, const double threshold2)
{
    blur(SrcImg, SrcImg, Size(apertureSize, apertureSize));
    Canny(SrcImg, DstImg, threshold1, threshold2, apertureSize);
}
void Sobel_s(const Mat &SrcImg, Mat &DstImg, const int KernelSize, const double scale, const int BorderMode) //scale:缩放因子=1不缩放
{
    Mat Src_x, Src_y;
    GaussianBlur(SrcImg, SrcImg, Size(KernelSize, KernelSize), 0, 0, BORDER_DEFAULT);
    Sobel(SrcImg, Src_x, CV_16S, 1, 0, KernelSize, scale, 1, BorderMode);
    convertScaleAbs(Src_x, Src_x);
    Sobel(SrcImg, Src_y, CV_16S, 0, 1, KernelSize, scale, 1, BorderMode);
    convertScaleAbs(Src_y, Src_y);
    addWeighted(Src_x, 0.5, Src_y, 0.5, 0, DstImg);
}

void Scharr_s(const Mat &SrcImg, Mat &DstImg, const double scale, const int BorderMode)
{
    Mat Src_x, Src_y;
    Scharr(SrcImg, Src_x, CV_16S, 0, 1, scale, BorderMode);
    convertScaleAbs(Src_x, Src_x);
    Scharr(SrcImg, Src_y, CV_16S, 1, 0, scale, BorderMode);
    convertScaleAbs(Src_y, Src_y);
    addWeighted(Src_x, 0.5, Src_y, 0.5, 0, DstImg);
}
void prewitt_s(const Mat &SrcImg, Mat &DstImg)
{
    Mat Kernelx, Kernely;
    Mat SrcGray;
    cvtColor(SrcImg, SrcGray, COLOR_RGB2GRAY);

    Kernelx = (Mat_<double>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
    Kernely = (Mat_<double>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    filter2D(SrcGray, grad_x, CV_16S, Kernelx, Point(-1, -1));
    filter2D(SrcGray, grad_y, CV_16S, Kernely, Point(-1, -1));
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, DstImg);
}
void robot_s(const Mat &SrcImg, Mat &DstImg)
{
    Mat Kernelx, Kernely;
    Mat SrcGray;
    cvtColor(SrcImg, SrcGray, COLOR_RGB2GRAY);

    Kernelx = (Mat_<double>(2, 2) << 1,0,0,-1);
    Kernely = (Mat_<double>(2, 2) << 0,1,-1,0);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    filter2D(SrcGray, grad_x, CV_16S, Kernelx, Point(-1, -1));
    filter2D(SrcGray, grad_y, CV_16S, Kernely, Point(-1, -1));
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, DstImg);
}
