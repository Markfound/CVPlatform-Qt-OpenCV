#ifndef ImageSmoothing_h
#define ImageSmoothing_h

#include "ProHeader.h"

void BoxFilter(const Mat &SrcImg, Mat &DstImg,const int kernel);
void MedianFiltering(const Mat &SrcImg, Mat &DstImg,const int kernel);
void GaussianFiltering(const Mat &SrcImg, Mat &DstImg,const int kernel);
void blur_s(const Mat &SrcImg,Mat &DstImg,const int kernel);
//void BilateralFiltering(Mat &SrcImg, Mat &DstImg);

#endif
