#ifndef ImageMorphology_h
#define ImageMorphology_h

#include "ProHeader.h"

void Corrosion(Mat &SrcImg, Mat &DstImg, const int width, const int height, const int shape);
void Dis_Trans(Mat &SrcImg, Mat &DstImg, const int masksize);
void Expanding(Mat &SrcImg, Mat &DstImg, const int width, const int height, const int shape);
void morphologyEx_s(const Mat &SrcImg, Mat &DstImg, int Width,int Height,int flag);
void horizontalProjectionMat(Mat srcImg,Mat &dstImg);
void verticalProjectionMat(Mat srcImg,Mat &dstImg);
void calcHist_s(const Mat &SrcImg,Mat &DstImg);
void HitOrMiss(const Mat &SrcImg, Mat &DstImg);
void thinImage(const Mat & srcImg,Mat &dstImg);
#endif
