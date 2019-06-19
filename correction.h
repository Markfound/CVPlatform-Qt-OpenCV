#ifndef CORRECTION_H
#define CORRECTION_H

#include"ProHeader.h"
void PerspectiveTrans(const Mat &SrcImg,Mat &DstImg,double p1x,double p1y,double p2x,double p2y,double p3x,double p3y,double p4x,double p4y,double p11x,double p11y,double p22x,double p22y,double p33x,double p33y,double p44x,double p44y);
void AffineTrans(const Mat &SrcImg,Mat &DstImg,double p1x,double p1y,double p2x,double p2y,double p3x,double p3y,double p11x,double p11y,double p22x,double p22y,double p33x,double p33y);
void AffineTrans(const Mat &SrcImg,Mat &DstImg);
void resize_s(const Mat &SrcImg, Mat &DstImg, double width,double hight);
void getRotationMatrix2D_s(const Mat &SrcImg, Mat &DstImg, double degree);
void mirror_s(const Mat &SrcImg, Mat &DstImg,bool flag);
void trainslation(const Mat &SrcImg, Mat &DstImg,double width,double hight);
void shear_s(const Mat &SrcImg, Mat &DstImg, double ratio);
#endif // CORRECTION_H
