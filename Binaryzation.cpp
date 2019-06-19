#include"Binaryzation.h"

void Threshold_s(const Mat& SrcImg,Mat& DstImg,const int Min,const int Max,const int mode)
{
    if(SrcImg.channels()==3||SrcImg.channels()==4)
    {
        Mat SrcImgGray;
        cvtColor(SrcImg,SrcImgGray,COLOR_RGB2GRAY);
        threshold(SrcImgGray,DstImg,Min,Max,mode);
    }
    else
        threshold(SrcImg,DstImg,Min,Max,mode);
}
