#include"Correction.h"

void PerspectiveTrans(const Mat &SrcImg,Mat &DstImg,double p1x,double p1y,double p2x,double p2y,double p3x,double p3y,double p4x,double p4y,double p11x,double p11y,double p22x,double p22y,double p33x,double p33y,double p44x,double p44y)  //, Point2f *scrPoints, Point2f *dstPoints
{
    Point2f AffinePoints0[4] = {Point2f(p1x, p1y), Point2f(p2x, p2y), Point2f(p3x, p3y), Point2f(p4x, p4y)};
    Point2f AffinePoints1[4] = {Point2f(p11x, p11y), Point2f(p22x, p22y), Point2f(p33x, p33y), Point2f(p44x, p44y)};
    Mat Trans = getPerspectiveTransform(AffinePoints0, AffinePoints1);
    warpPerspective(SrcImg, DstImg, Trans, Size(SrcImg.cols, SrcImg.rows), INTER_CUBIC);
}
void AffineTrans(const Mat &SrcImg,Mat &DstImg,double p1x,double p1y,double p2x,double p2y,double p3x,double p3y,double p11x,double p11y,double p22x,double p22y,double p33x,double p33y)  //, Point2f *scrPoints, Point2f *dstPoints
{
    Point2f AffinePoints0[3] = {Point2f(p1x, p1y), Point2f(p2x, p2y), Point2f(p3x, p3y)};
    Point2f AffinePoints1[3] = {Point2f(p11x, p11y), Point2f(p22x, p22y), Point2f(p33x, p33y)};
    Mat Trans = getAffineTransform(AffinePoints0, AffinePoints1);
    warpAffine(SrcImg, DstImg, Trans, Size(SrcImg.cols, SrcImg.rows), INTER_CUBIC);
}
void resize_s(const Mat &SrcImg, Mat &DstImg, double width,double hight)
{
    resize(SrcImg, DstImg, Size(SrcImg.cols*width, SrcImg.rows*hight));
}
void getRotationMatrix2D_s(const Mat &SrcImg, Mat &DstImg, double degree)
{
    warpAffine(SrcImg, DstImg, getRotationMatrix2D(Point2f(SrcImg.cols / 2, SrcImg.rows / 2), degree, 0.5), Size(SrcImg.cols, SrcImg.rows));
}
void mirror_s(const Mat &SrcImg, Mat &DstImg,bool flag)
{
    Mat map_x;
    Mat map_y;
    map_x.create(SrcImg.size(), CV_32F);
    map_y.create(SrcImg.size(), CV_32F);
    for (int i = 0; i < SrcImg.rows; ++i)
    {
        for (int j = 0; j < SrcImg.cols; ++j)
        {
            if (!flag)
            {
                map_x.at<float>(i, j) = (float)(SrcImg.cols - j);
                map_y.at<float>(i, j) = (float)i;
            }
            else
            {
                map_x.at<float>(i, j) = (float)(SrcImg.cols - j);
                map_y.at<float>(i, j) = (float)(SrcImg.rows - i);
            }
        }
    }
    remap(SrcImg, DstImg, map_x, map_y, INTER_LINEAR);
}
void trainslation(const Mat &SrcImg, Mat &DstImg,double width,double hight)
{
    cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);

    t_mat.at<float>(0, 0) = 1;
    t_mat.at<float>(0, 2) = SrcImg.cols*width; //水平平移量
    t_mat.at<float>(1, 1) = 1;
    t_mat.at<float>(1, 2) = SrcImg.rows*hight; //竖直平移量

                                //根据平移矩阵进行仿射变换
    warpAffine(SrcImg, DstImg, t_mat, SrcImg.size());

}
void shear_s(const Mat &SrcImg, Mat &DstImg, double ratio)
{
    double a = tan(ratio*acos(-1.0) / 180.0);
    int W = SrcImg.cols;
    int H = SrcImg.rows + W*a;
    DstImg.create(Size(W, H), SrcImg.type());
    for(int i=0;i<SrcImg.rows;i++)
    {
        for (int j = 0; j < SrcImg.cols; j++)
        {
            int x = i + j*a;
            for(int k=0;k<SrcImg.channels();k++)
            {
                DstImg.at<Vec3b>(x, j)[k] = SrcImg.at<Vec3b>(i, j)[k];
            }
        }
    }
}
