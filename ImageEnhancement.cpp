#include "ImageEnhancement.h"

void equalizeHist_s(const Mat &SrcImg, Mat &DstImg)
{
    Mat SrcImgRGB[5];
    DstImg.create(SrcImg.size(), SrcImg.type());
    split(SrcImg, SrcImgRGB);
    for (int i = 0; i < SrcImg.channels(); i++)
    {
        equalizeHist(SrcImgRGB[i], SrcImgRGB[i]);
    }
    merge(SrcImgRGB, SrcImg.channels(), DstImg);
}

void Log(const Mat &SrcImg, Mat &DstImg, const double NumOfLog)
{
    DstImg.create(SrcImg.size(), CV_32FC3);
    for (int i = 0; i < SrcImg.rows; i++)
    {
        for (int j = 0; j < SrcImg.cols; j++)
        {
            DstImg.at<Vec3f>(i, j)[0] = log(NumOfLog + SrcImg.at<Vec3b>(i, j)[0]);
            DstImg.at<Vec3f>(i, j)[1] = log(NumOfLog + SrcImg.at<Vec3b>(i, j)[1]);
            DstImg.at<Vec3f>(i, j)[2] = log(NumOfLog + SrcImg.at<Vec3b>(i, j)[2]);
        }
    }
    //归一化到0~255
    normalize(DstImg, DstImg, 0, 255, NORM_MINMAX);
    //转换成8bit图像显示
    convertScaleAbs(DstImg, DstImg);
}

void Gamma(const Mat &SrcImg, Mat &DstImg, const double gamma)
{
    DstImg.create(SrcImg.size(), CV_32FC3);
    for (int i = 0; i < SrcImg.rows; i++)
    {
        for (int j = 0; j < SrcImg.cols; j++)
        {
            DstImg.at<Vec3f>(i, j)[0] = pow(SrcImg.at<Vec3b>(i, j)[0], gamma);
            DstImg.at<Vec3f>(i, j)[1] = pow(SrcImg.at<Vec3b>(i, j)[1], gamma);
            DstImg.at<Vec3f>(i, j)[2] = pow(SrcImg.at<Vec3b>(i, j)[2], gamma);
        }
    }
    //归一化到0~255
    normalize(DstImg, DstImg, 0, 255, NORM_MINMAX);
    //转换成8bit图像显示
    convertScaleAbs(DstImg, DstImg);
}
void equalizeHist_stretching(Mat SrcImg, Mat &DstImg)
{
    double pR = 0.0;//斜率
    double pG = 0.0;//斜率
    double pB = 0.0;//斜率
    int minGrayDegree = 255;
    int maxGrayDegree = 0;
    int minGrayDegreeR = 255;
    int maxGrayDegreeR = 0;
    int minGrayDegreeG = 255;
    int maxGrayDegreeG = 0;
    int minGrayDegreeB = 255;
    int maxGrayDegreeB = 0;
    //Rectangle rt = new Rectangle(0, 0, dstBmp.Width, dstBmp.Height);
    //BitmapData bmpData = dstBmp.LockBits(rt, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
    //unsafe{
    for (int i = 0; i < SrcImg.rows; i++) {
        uchar* ptr = SrcImg.ptr<uchar>(i);
        for (int j = 0; j < SrcImg.cols; j++) {
            if ((minGrayDegreeR > *(ptr + j * 3 + 2)) && SrcImg.channels()>=3)
                minGrayDegreeR = *(ptr + j * 3 + 2);
            if ((maxGrayDegreeR < *(ptr + j * 3 + 2)) && SrcImg.channels() >= 3)
                maxGrayDegreeR = *(ptr + j * 3 + 2);
            if ((minGrayDegreeG > *(ptr + j * 3 + 1)) && SrcImg.channels() >= 2)
                minGrayDegreeG = *(ptr + j * 3 + 1);
            if ((maxGrayDegreeG < *(ptr + j * 3 + 1)) && SrcImg.channels() >= 2)
                maxGrayDegreeG = *(ptr + j * 3 + 1);
            if (minGrayDegreeB > *(ptr + j * 3))
                minGrayDegreeB = *(ptr + j * 3);
            if (maxGrayDegreeB < *(ptr + j * 3))
                maxGrayDegreeB = *(ptr + j * 3);
        }
    }
    pR = 255.0 / (maxGrayDegreeR - minGrayDegreeR);
    pG = 255.0 / (maxGrayDegreeG - minGrayDegreeG);
    pB = 255.0 / (maxGrayDegreeB - minGrayDegreeB);
    for (int i = 0; i < SrcImg.rows; i++) {
        uchar* ptr1 = SrcImg.ptr<uchar>(i);
        for (int j = 0; j < SrcImg.cols; j++) {
            *(ptr1 + j * 3) = (int)((*(ptr1 + j * 3) - minGrayDegreeB) * pB + 0.5);
            if(SrcImg.channels() >= 2)
                *(ptr1 + j * 3 + 1) = (int)((*(ptr1 + j * 3 + 1) - minGrayDegreeG) * pG + 0.5);
            if(SrcImg.channels() >= 3)
                *(ptr1 + j * 3 + 2) = (int)((*(ptr1 + j * 3 + 2) - minGrayDegreeR) * pR + 0.5);
        }
    }
    DstImg = SrcImg.clone();
}
void lut(const Mat &SrcImg,Mat &DstImg)
{
    int n=SrcImg.channels();
    uchar lutData[256 * 5];
    int j = 0;
    for (int i = 0; i<256; i++)
    {
        if (i <= 100)
        {
            for (int j = 0; j < n; j++)
            {
                lutData[i*n+j] = 100;
            }
        }
        else if (i > 100 && i <= 200)
        {
            for (int j = 0; j < n; j++)
            {
                lutData[i*n + j] = 200;
            }
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                lutData[i*n + j] = 256;
            }
        }

    }
    Mat lut(1, 256, SrcImg.type(), lutData);
    LUT(SrcImg, lut, DstImg);
}
void ImageReverse(Mat &SrcImg, Mat &DstImg)
{
    // cvtColor(SrcImg, SrcImg, COLOR_BGR2GRAY);
    DstImg = 255 - SrcImg;
}
void cvtColor_s(const Mat &SrcImg, Mat &DstImg)
{
    if(SrcImg.channels()==3||SrcImg.channels()==4)
        cvtColor(SrcImg, DstImg, COLOR_BGR2GRAY);
    else
        DstImg=SrcImg.clone();
}
void applyColorMap_s(const Mat &SrcImg,Mat &DstImg,const int mode)
{
    Mat SrcGray;
    cvtColor(SrcImg, SrcGray, COLOR_RGB2GRAY);
    applyColorMap(SrcGray, DstImg ,mode);
}
void unevenLightCompensate(Mat &image, Mat &DstImg,int blockSize)
{
    DstImg = image.clone();
    if (DstImg.channels() == 3) cvtColor(DstImg, DstImg, 7);
    double average = mean(DstImg)[0];
    int rows_new = ceil(double(DstImg.rows) / double(blockSize));
    int cols_new = ceil(double(DstImg.cols) / double(blockSize));
    Mat blockImage;
    blockImage = Mat::zeros(rows_new, cols_new, CV_32FC1);
    for (int i = 0; i < rows_new; i++)
    {
        for (int j = 0; j < cols_new; j++)
        {
            int rowmin = i*blockSize;
            int rowmax = (i + 1)*blockSize;
            if (rowmax > DstImg.rows) rowmax = DstImg.rows;
            int colmin = j*blockSize;
            int colmax = (j + 1)*blockSize;
            if (colmax > DstImg.cols) colmax = DstImg.cols;
            Mat imageROI = DstImg(Range(rowmin, rowmax), Range(colmin, colmax));
            double temaver = mean(imageROI)[0];
            blockImage.at<float>(i, j) = temaver;
        }
    }
    blockImage = blockImage - average;
    Mat blockImage2;
    resize(blockImage, blockImage2, DstImg.size(), (0, 0), (0, 0), INTER_CUBIC);
    Mat image2;
    DstImg.convertTo(image2, CV_32FC1);
    Mat dst = image2 - blockImage2;
    dst.convertTo(DstImg, CV_8UC1);
}
