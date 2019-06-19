#ifndef ROI_H
#define ROI_H

#include"ProHeader.h"

void Rect_s(const Mat &SrcImg, Mat &DstImg, double x1, double y1, double x2, double y2);
void RotatedRect_s(const Mat &SrcImg, Mat &DstImg, double x, double y,double size_x,double size_y, double angle);
void circle_s(const Mat &SrcImg, Mat &DstImg, double x, double y, double r);
void drawContours_s(const Mat &SrcImg, Mat &DstImg, vector<Point> pts);
void ellipse_s(const Mat &SrcImg, Mat &DstImg, double x, double y, double size_x, double size_y,double angle);

#endif // ROI_H
