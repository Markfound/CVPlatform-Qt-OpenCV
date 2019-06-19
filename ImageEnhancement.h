#ifndef ImageEnhancement_h
#define ImageEnhancement_h

#include "ProHeader.h"
void equalizeHist_s(const Mat &SrcImg, Mat &DstImg);
void Log(const Mat &SrcImg, Mat &DstImg,const double NumOfLog);
void Gamma(const Mat &SrcImg, Mat &DstImg, const double gamma);
void equalizeHist_stretching(Mat SrcImg, Mat &DstImg);
void lut(const Mat &SrcImg,Mat &DstImg);
void ImageReverse(Mat &SrcImg, Mat &DstImg);
void cvtColor_s(const Mat &SrcImg, Mat &DstImg);
void applyColorMap_s(const Mat &SrcImg,Mat &DstImg,const int mode);
void unevenLightCompensate(Mat &image, Mat &DstImg,int blockSize);
#endif

