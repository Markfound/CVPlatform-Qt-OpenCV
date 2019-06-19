#ifndef ImageOperation_h
#define ImageOperation_h

#include "ProHeader.h"

void add(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2);
void sub(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2);
void Intersection(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2);
void Union(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2);
void Complement(const Mat &SrcImg, Mat &DstImg);
void Distinction(const Mat &SrcImg1, Mat &DstImg,const Mat &SrcImg2);
void ExposureAdjustment(const Mat &SrcImg, Mat &DstImg, const int n); //n:曝光系数
void dft_s(const Mat &SrcImg, Mat &DstImg);
#endif
