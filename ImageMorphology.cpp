#include "ImageMorphology.h"
#include<QDebug>
void Corrosion(Mat &SrcImg, Mat &DstImg, const int width, const int height, const int shape)
{
    Mat element = getStructuringElement(shape, Size(width, height));
    erode(SrcImg, DstImg, element);
}
void Expanding(Mat &SrcImg, Mat &DstImg,const int width, const int height, const int shape)
{
    Mat element = getStructuringElement(shape, Size(width, height));
    dilate(SrcImg, DstImg, element);
}
void Dis_Trans(Mat &SrcImg, Mat &DstImg, const int masksize)
{
    cvtColor(SrcImg, SrcImg, COLOR_BGR2GRAY);
    GaussianBlur(SrcImg, SrcImg, Size(masksize, masksize), 2);
    threshold(SrcImg, SrcImg, 0, 255, THRESH_BINARY | THRESH_OTSU);
    distanceTransform(SrcImg, SrcImg, DIST_L2, masksize);
    DstImg = Mat::zeros(SrcImg.size(), CV_8UC1);
    float maxValue = 0;
    for (int i = 0; i < SrcImg.rows; i++)
    {
        for (int j = 0; j < SrcImg.cols; j++)
        {
            DstImg.at<uchar>(i, j) = SrcImg.at<float>(i, j);
            if (SrcImg.at<float>(i, j) > maxValue)
            {
                maxValue = SrcImg.at<float>(i, j); //获取距离变换的极大值
            }
        }
    }
    normalize(DstImg, DstImg, 0, 255, NORM_MINMAX);
}
void morphologyEx_s(const Mat &SrcImg, Mat &DstImg, int Width,int Height,int flag)
{
    Mat SrcImgGray;
    if(SrcImg.channels()>=3)
        cvtColor(SrcImg, SrcImgGray, COLOR_RGB2GRAY);
    else
        SrcImgGray=SrcImg.clone();
    Mat element = getStructuringElement(MORPH_RECT, Size(Width, Height));
    if(flag==0)
        morphologyEx(SrcImgGray, DstImg, MORPH_OPEN, element);
    else if(flag==1)
        morphologyEx(SrcImgGray, DstImg, MORPH_CLOSE, element);
    else if(flag==2)
        morphologyEx(SrcImgGray, DstImg, MORPH_TOPHAT, element);
    else if(flag==3)
        morphologyEx(SrcImgGray, DstImg, MORPH_BLACKHAT, element);
    else
        morphologyEx(SrcImgGray, DstImg, MORPH_GRADIENT, element);
}

void horizontalProjectionMat(Mat srcImg,Mat &dstImg)//水平投影
{
    if (srcImg.channels() >= 2)
    {
        cvtColor(srcImg, srcImg, COLOR_RGB2GRAY);
    }
    Mat binImg;
    blur(srcImg, binImg, Size(3, 3));
    threshold(binImg, binImg, 0, 255, THRESH_OTSU);
    int perPixelValue = 0;//每个像素的值
    int width = srcImg.cols;
    int height = srcImg.rows;
    int* projectValArry = new int[height];//创建一个储存每行白色像素个数的数组
    memset(projectValArry, 0, height * 4);//初始化数组
    for (int col = 0; col < height; col++)//遍历每个像素点
    {
        for (int row = 0; row < width; row++)
        {
            perPixelValue = binImg.at<uchar>(col, row);
            if (perPixelValue == 0)//如果是白底黑字
            {
                projectValArry[col]++;
            }
        }
    }
    dstImg.create(height, width, CV_8UC1);//创建画布
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            perPixelValue = 255;
            dstImg.at<uchar>(i, j) = perPixelValue;//设置背景为白色
        }
    }
    for (int i = 0; i < height; i++)//水平直方图
    {
        for (int j = 0; j < projectValArry[i]; j++)
        {
            perPixelValue = 0;
            dstImg.at<uchar>(i, width - 1 - j) = perPixelValue;//设置直方图为黑色
        }
    }

}
void verticalProjectionMat(Mat srcImg,Mat &dstImg)//垂直投影
{
    if (srcImg.channels() >= 2)
    {
        cvtColor(srcImg, srcImg, COLOR_RGB2GRAY);
    }
    Mat binImg;
    blur(srcImg, binImg, Size(3, 3));
    threshold(binImg, binImg, 0, 255, THRESH_OTSU);
    int perPixelValue;//每个像素的值
    int width = srcImg.cols;
    int height = srcImg.rows;
    int* projectValArry = new int[width];//创建用于储存每列白色像素个数的数组
    memset(projectValArry, 0, width * 4);//初始化数组
    for (int col = 0; col < width; col++)
    {
        for (int row = 0; row < height; row++)
        {
            perPixelValue = binImg.at<uchar>(row, col);
            if (perPixelValue == 0)//如果是白底黑字
            {
                projectValArry[col]++;
            }
        }
    }
    dstImg.create(height, width, CV_8UC1);//垂直投影的画布
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            perPixelValue = 255;  //背景设置为白色
            dstImg.at<uchar>(i, j) = perPixelValue;
        }
    }
    for (int i = 0; i < width; i++)//垂直投影直方图
    {
        for (int j = 0; j < projectValArry[i]; j++)
        {
            perPixelValue = 0;  //直方图设置为黑色
            dstImg.at<uchar>(height - 1 - j, i) = perPixelValue;
        }
    }
}
void calcHist_s(const Mat &SrcImg,Mat &DstImg)
{
    // 分割成3个单通道图像 ( R, G 和 B )
    vector<Mat> rgb_planes;
    split(SrcImg, rgb_planes);

    // 设定bin数目
    int histSize = 255;

    // 设定取值范围 ( R,G,B) )
    float range[] = { 0, 255 };
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat r_hist, g_hist, b_hist;

    // 计算直方图:
    calcHist(&rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

    // 创建直方图画布
    int hist_w = 400; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    DstImg.create(hist_w, hist_h, CV_8UC3);

    // 将直方图归一化到范围 [ 0, histImage.rows ]
    normalize(r_hist, r_hist, 0, DstImg.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, DstImg.rows, NORM_MINMAX, -1, Mat());
    normalize(b_hist, b_hist, 0, DstImg.rows, NORM_MINMAX, -1, Mat());

    // 在直方图画布上画出直方图
    for (int i = 1; i < histSize; i++)
    {
        line(DstImg, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
            Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
            Scalar(0, 0, 255), 2, 8, 0);
        line(DstImg, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
            Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
            Scalar(0, 255, 0), 2, 8, 0);
        line(DstImg, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
            Scalar(255, 0, 0), 2, 8, 0);
    }
}
void HitOrMiss(const Mat &SrcImg, Mat &DstImg)
{
    //Mat input_image = imread("d://timg.jpg", 2);
    /*imshow("Hit or Miss原图", input_image);
    Mat kernel1 = (Mat_<int>(3, 3) <<
        0, 1, 0,
        1, -1, 1,
        0, 1, 0);
    Mat kernel2 = (Mat_<int>(3, 3) <<
        0, 1, 0,
        1, 0, 1,
        0, 1, 0);
    Mat kernel3 = (Mat_<int>(3, 3) <<
        0, 0, 0,
        0, 1, 0,
        0, 0, 0);
    Mat output_image, output_image1, output_image2, output_image3, output_image4;
    Mat element = getStructuringElement(0, Size(3, 3), Point(-1, -1));
    erode(input_image, output_image3, element);
    imshow("腐蚀图", output_image3);
    morphologyEx(input_image, output_image1, MORPH_HITMISS, kernel3);
    morphologyEx(input_image, output_image2, MORPH_HITMISS, kernel2);
    morphologyEx(input_image, output_image, MORPH_HITMISS, kernel1);
    imshow("Hit or Miss0", output_image1);
    imshow("Hit or Miss1", output_image2);
    imshow("Hit or Miss", output_image);
    cv::absdiff(output_image1, output_image2, output_image4);
    cv::imshow("Hit or Miss2", output_image4);*/
    Mat SrcGray;
    if (SrcImg.channels() >= 3)
        cvtColor(SrcImg, SrcGray, COLOR_RGB2GRAY);
    else
        SrcGray = SrcImg.clone();
    Mat kernel1 = (Mat_<int>(3, 3) <<
        0, 1, 0,
        1, -1, 1,
        0, 1, 0);
    morphologyEx(SrcGray, DstImg, MORPH_HITMISS, kernel1);
}
void thinImage(const Mat & srcImg,Mat &dstImg)
{
    Mat SrcGray;
    if(srcImg.channels()>=2)
        cvtColor(srcImg,SrcGray,COLOR_RGB2GRAY);
    else
        SrcGray=srcImg.clone();
    dstImg = SrcGray.clone();
    vector<Point> deleteList;
    int neighbourhood[9];
    int nl = srcImg.rows;
    int nc = srcImg.cols;
    bool inOddIterations = true;
    while (true) {
        for (int j = 1; j < (nl - 1); j++) {
            uchar* data_last = dstImg.ptr<uchar>(j - 1);
            uchar* data = dstImg.ptr<uchar>(j);
            uchar* data_next = dstImg.ptr<uchar>(j + 1);
            for (int i = 1; i < (nc - 1); i++) {
                if (data[i] == 255) {
                    int whitePointCount = 0;
                    neighbourhood[0] = 1;
                    if (data_last[i] == 255) neighbourhood[1] = 1;
                    else  neighbourhood[1] = 0;
                    if (data_last[i + 1] == 255) neighbourhood[2] = 1;
                    else  neighbourhood[2] = 0;
                    if (data[i + 1] == 255) neighbourhood[3] = 1;
                    else  neighbourhood[3] = 0;
                    if (data_next[i + 1] == 255) neighbourhood[4] = 1;
                    else  neighbourhood[4] = 0;
                    if (data_next[i] == 255) neighbourhood[5] = 1;
                    else  neighbourhood[5] = 0;
                    if (data_next[i - 1] == 255) neighbourhood[6] = 1;
                    else  neighbourhood[6] = 0;
                    if (data[i - 1] == 255) neighbourhood[7] = 1;
                    else  neighbourhood[7] = 0;
                    if (data_last[i - 1] == 255) neighbourhood[8] = 1;
                    else  neighbourhood[8] = 0;
                    for (int k = 1; k < 9; k++) {
                        whitePointCount += neighbourhood[k];
                    }
                    if ((whitePointCount >= 2) && (whitePointCount <= 6)) {
                        int ap = 0;
                        if ((neighbourhood[1] == 0) && (neighbourhood[2] == 1)) ap++;
                        if ((neighbourhood[2] == 0) && (neighbourhood[3] == 1)) ap++;
                        if ((neighbourhood[3] == 0) && (neighbourhood[4] == 1)) ap++;
                        if ((neighbourhood[4] == 0) && (neighbourhood[5] == 1)) ap++;
                        if ((neighbourhood[5] == 0) && (neighbourhood[6] == 1)) ap++;
                        if ((neighbourhood[6] == 0) && (neighbourhood[7] == 1)) ap++;
                        if ((neighbourhood[7] == 0) && (neighbourhood[8] == 1)) ap++;
                        if ((neighbourhood[8] == 0) && (neighbourhood[1] == 1)) ap++;
                        if (ap == 1) {
                            if (inOddIterations && (neighbourhood[3] * neighbourhood[5] * neighbourhood[7] == 0)
                                && (neighbourhood[1] * neighbourhood[3] * neighbourhood[5] == 0)) {
                                deleteList.push_back(Point(i, j));
                            }
                            else if (!inOddIterations && (neighbourhood[1] * neighbourhood[5] * neighbourhood[7] == 0)
                                && (neighbourhood[1] * neighbourhood[3] * neighbourhood[7] == 0)) {
                                deleteList.push_back(Point(i, j));
                            }
                        }
                    }
                }
            }
        }
        if (deleteList.size() == 0)
            break;
        for (size_t i = 0; i < deleteList.size(); i++) {
            Point tem;
            tem = deleteList[i];
            uchar* data = dstImg.ptr<uchar>(tem.y);
            data[tem.x] = 0;
        }
        deleteList.clear();

        inOddIterations = !inOddIterations;
    }
}
