#include "ImageOperation.h"

void add(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2)
{
    Mat SrcImg1RGB[5],SrcImg2RGB[5],DstImgRGB[5];
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        SrcImg1RGB[i].create(SrcImg1.size(),SrcImg1.type());
        SrcImg2RGB[i].create(SrcImg2.size(),SrcImg2.type());
    }
    split(SrcImg1, SrcImg1RGB);
    split(SrcImg2, SrcImg2RGB);
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        addWeighted(SrcImg1RGB[i], 0.5, SrcImg2RGB[i], 0.5, 0, DstImgRGB[i]);
    }
    merge(DstImgRGB,max(SrcImg1.channels(),SrcImg2.channels()),DstImg);
}
void sub(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2)
{
    Mat SrcImg1RGB[5],SrcImg2RGB[5],DstImgRGB[5];
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        SrcImg1RGB[i].create(SrcImg1.size(),SrcImg1.type());
        SrcImg2RGB[i].create(SrcImg2.size(),SrcImg2.type());
    }
    split(SrcImg1, SrcImg1RGB);
    split(SrcImg2, SrcImg2RGB);
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        absdiff(SrcImg1RGB[i], SrcImg2RGB[i], DstImgRGB[i]);
    }
    merge(DstImgRGB,max(SrcImg1.channels(),SrcImg2.channels()),DstImg);
}
void Intersection(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2)
{
    Mat SrcImg1RGB[5],SrcImg2RGB[5],DstImgRGB[5];
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        SrcImg1RGB[i].create(SrcImg1.size(),SrcImg1.type());
        SrcImg2RGB[i].create(SrcImg2.size(),SrcImg2.type());
    }
    split(SrcImg1, SrcImg1RGB);
    split(SrcImg2, SrcImg2RGB);
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        bitwise_and(SrcImg1RGB[i], SrcImg2RGB[i], DstImgRGB[i]); //逻辑与，求交集
    }
    merge(DstImgRGB,max(SrcImg1.channels(),SrcImg2.channels()),DstImg);
}
void Union(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2)
{
    Mat SrcImg1RGB[5],SrcImg2RGB[5],DstImgRGB[5];
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        SrcImg1RGB[i].create(SrcImg1.size(),SrcImg1.type());
        SrcImg2RGB[i].create(SrcImg2.size(),SrcImg2.type());
    }
    split(SrcImg1, SrcImg1RGB);
    split(SrcImg2, SrcImg2RGB);
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        bitwise_or(SrcImg1RGB[i], SrcImg2RGB[i], DstImgRGB[i]); //逻辑或，求交集
    }
    merge(DstImgRGB,max(SrcImg1.channels(),SrcImg2.channels()),DstImg);
}
void Complement(const Mat &SrcImg, Mat &DstImg)
{
    bitwise_not(SrcImg, DstImg); //逻辑非，求补集
}
void Distinction(const Mat &SrcImg1,Mat &DstImg, const Mat &SrcImg2)
{
    Mat SrcImg1RGB[5],SrcImg2RGB[5],DstImgRGB[5];
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        SrcImg1RGB[i].create(SrcImg1.size(),SrcImg1.type());
        SrcImg2RGB[i].create(SrcImg2.size(),SrcImg2.type());
    }
    split(SrcImg1, SrcImg1RGB);
    split(SrcImg2, SrcImg2RGB);
    for(int i=0;i<max(SrcImg1.channels(),SrcImg2.channels());i++)
    {
        bitwise_xor(SrcImg1RGB[i], SrcImg2RGB[i], DstImgRGB[i]); //异或，相同为0，相异为1
    }
    merge(DstImgRGB,max(SrcImg1.channels(),SrcImg2.channels()),DstImg);
}
void ExposureAdjustment(const Mat &SrcImg, Mat &DstImg, const int n) //n:曝光度
{
    DstImg = n * SrcImg;
}
void dft_s(const Mat &SrcImg, Mat &DstImg)
{
    Mat SrcGray;
    if (SrcImg.channels() >= 2)
        cvtColor(SrcImg, SrcGray, COLOR_RGB2GRAY);
    else
        SrcGray = SrcImg.clone();
    int M = getOptimalDFTSize(SrcGray.rows);
    int N = getOptimalDFTSize(SrcGray.cols);
    Mat padded;
    copyMakeBorder(SrcGray, padded, 0, M - SrcGray.rows, 0, N - SrcGray.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[2] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat ImgDFT;
    merge(planes, 2, ImgDFT);

    dft(ImgDFT, ImgDFT);
    //正变换过后，先对频谱图进行中心平移
    ImgDFT = ImgDFT(Rect(0, 0, ImgDFT.cols & -2, ImgDFT.rows & -2));

    int cx = ImgDFT.cols / 2;
    int cy = ImgDFT.rows / 2;
    // rearrange the quadrants of Fourier image
    // so that the origin is at the image center
    Mat tmp;
    Mat q0(ImgDFT, Rect(0, 0, cx, cy));
    Mat q1(ImgDFT, Rect(cx, 0, cx, cy));
    Mat q2(ImgDFT, Rect(0, cy, cx, cy));
    Mat q3(ImgDFT, Rect(cx, cy, cx, cy));
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    //将得到的频谱图分解成虚部和实部两部分
    split(ImgDFT, planes);
    Mat Proc_RE = planes[0];
    Mat Proc_IM = planes[1];

    /*******************************************************/
    //此处定义处理频谱的方法，实部和虚部要分开分别进行处理
    double ESP = 0.000001;
    for (int i = 0; i < Proc_RE.rows; ++i)
        for (int j = 0; j < Proc_RE.cols; ++j)
        {
            double dx = i - Proc_RE.rows / 2;
            double dy = j - Proc_RE.cols / 2;
            Proc_RE.at<float>(i, j) = (1 - exp(-100 / (pow(dx, 2) + pow(dy, 2) + ESP)))* Proc_RE.at<float>(i, j);
            Proc_IM.at<float>(i, j) = (1 - exp(-100 / (pow(dx, 2) + pow(dy, 2) + ESP)))* Proc_IM.at<float>(i, j);
        }
    /*******************************************************/
    //此处用于显示处理后的频谱图像（频谱为傅立叶变换的幅值，magnitude（）函数可以直接求得），
    magnitude(planes[0], planes[1], DstImg);
    DstImg += Scalar::all(1);
    log(DstImg, DstImg);
    normalize(DstImg, DstImg, 0, 1, NORM_MINMAX);
}
