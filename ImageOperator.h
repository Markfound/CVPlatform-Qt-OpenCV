#ifndef ImageOperator_h
#define ImageOperator_h

#include "ProHeader.h"

void Laplacian_s(const Mat &SrcImg, Mat &DstImg, const int KernelSize);
void Canny_s(const Mat &SrcImg, Mat &DstImg, const int apertureSize, const double threshold1, const double threshold2);
void Sobel_s(const Mat &SrcImg, Mat &DstImg, const int KernelSize, const double scale, const int BorderMode); //scale:缩放因子=1不缩放
void Scharr_s(const Mat &SrcImg, Mat &DstImg, const double scale, const int BorderMode);
void prewitt_s(const Mat &SrcImg, Mat &DstImg);
void robot_s(const Mat &SrcImg, Mat &DstImg);
#endif
