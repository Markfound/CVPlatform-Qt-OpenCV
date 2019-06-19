#include"roi.h"
void Rect_s(const Mat &SrcImg, Mat &DstImg, double x1, double y1, double x2, double y2)
{
    DstImg = SrcImg(Rect(Point2f(x1, y1), Point2f(x2, y2)));
}
void RotatedRect_s(const Mat &SrcImg, Mat &DstImg, double x, double y,double size_x,double size_y, double angle)
{
    RotatedRect rRect = RotatedRect(Point2f(x, y), Size(size_x, size_y), angle);
    Rect brect = rRect.boundingRect();
    Point2f vertices[4];
    rRect.points(vertices);
    /*rectangle(SrcImg, brect, Scalar(255, 0, 0), 2);
    for (int i = 0; i < 4; i++)
        line(SrcImg, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
    */
    Mat Tem;
    warpAffine(SrcImg, Tem, getRotationMatrix2D(Point2f(x,y), angle, 1.0), Size(SrcImg.cols, SrcImg.rows));
    DstImg = Tem(brect);
}
void circle_s(const Mat &SrcImg, Mat &DstImg, double x, double y, double r)
{
    Mat logo = SrcImg(Rect(Point2f(x-r, y-r), Point2f(x+r, y+r)));
    Mat mask = Mat::zeros(Size(2*r, 2*r), CV_8UC1);  //注意这一句，创建一个同logo一样大的纯黑的mask
    circle(mask, Point(mask.rows / 2, mask.cols / 2), r, Scalar(255), -1, 8);  //在mask中画一个向内填充的白色圆
    DstImg = Mat::zeros(SrcImg.size(), CV_8UC1);
    logo.copyTo(DstImg, mask);//将logo拷贝到imgROI上，掩码为不为0的部分起作用，为0的部分不起作用
}
void drawContours_s(const Mat &SrcImg, Mat &DstImg, vector<Point> pts)
{
    Mat roi = Mat::zeros(SrcImg.size(), CV_8U);
    vector<vector<Point>> contour;
    contour.push_back(pts);
    drawContours(roi, contour, 0, Scalar::all(255), -1);
    SrcImg.copyTo(DstImg, roi);
}
void ellipse_s(const Mat &SrcImg, Mat &DstImg, double x, double y, double size_x, double size_y,double angle)
{
    DstImg = Mat::zeros(SrcImg.size(), SrcImg.type());
    Mat mask = Mat::zeros(SrcImg.size(), CV_8U);
    ellipse(mask, Point2f(x,y), Size(size_x, size_y), angle, 0, 360, Scalar(255), -1);
    SrcImg.copyTo(DstImg, mask);
}
