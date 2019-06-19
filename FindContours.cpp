#include "FindContours.h"

void Findcontours_s(const Mat &SrcImg, Mat &DstImg,const int RETR,const int CHAIN)
{
//    RNG rng(12345);
//    Mat SrcImgGray;
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    vector<vector<Point> > contourss;
//    //检测方式
//    //RETR_EXTERNAL:0:只检测最外围轮廓;RETR_LIST:1:检测所有的轮廓,轮廓之间独立;RETR_FLOODFILL:4:
//    //RETR_CCOMP:2:检测所有的轮廓，所有轮廓只建立两个等级关系;RETR_TREE:3:检测所有轮廓，所有轮廓建立一个等级树结构。
//    //链接方式
//    //CHAIN_APPROX_NONE:1: 保存物体边界上所有连续的轮廓点到contours向量内
//    //CHAIN_APPROX_SIMPLE:2: 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours向量内，拐点与拐点之间直线段上的信息点不予保留
//    //CHAIN_APPROX_TC89_L1:3:，CHAIN_APPROX_TC89_KCOS:4:使用teh-Chinl chain 近似算法
//    cvtColor(SrcImg, SrcImgGray, COLOR_BGR2GRAY);
//    findContours(SrcImgGray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
//    DstImg = Mat::zeros(SrcImgGray.size(), CV_8UC3);
//    for (int i = 0; i < contours.size(); i++)
//    {
//        //Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//        approxPolyDP(Mat(contours[i]), contourss[i], 3, true);
//    }
//    drawContours(DstImg,contourss, -1, Scalar(128,255,255),3, LINE_AA, hierarchy, std::abs(3) );
//    //DstImg=SrcImgGray.clone();
    Mat gray_src;
    if(SrcImg.channels()==3||SrcImg.channels()==4)
        cvtColor(SrcImg, gray_src, COLOR_BGR2GRAY);
    else
        gray_src=SrcImg.clone();
    Mat binary_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    threshold(gray_src, binary_output, 100, 255, THRESH_OTSU);
    findContours(binary_output, contours, hierachy, RETR, CHAIN, Point(-1, -1));

    vector<vector<Point>> contours_ploy(contours.size());
    vector<Rect> ploy_rects(contours.size());
    vector<Point2f> ccs(contours.size());
    vector<float> radius(contours.size());

    vector<RotatedRect> minRects(contours.size());
    vector<RotatedRect> myellipse(contours.size());

    for (size_t i = 0; i < contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), contours_ploy[i], 3, true);
        ploy_rects[i] = boundingRect(contours_ploy[i]);
        minEnclosingCircle(contours_ploy[i], ccs[i], radius[i]);
        if (contours_ploy[i].size() > 5)
        {
            myellipse[i] = fitEllipse(contours_ploy[i]);
            minRects[i] = minAreaRect(contours_ploy[i]);
        }
    }
    RNG rng(12345);
    // draw it
    DstImg = SrcImg.clone();
    Point2f pts[4];
    for (size_t t = 0; t < contours.size(); t++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        //rectangle(drawImg, ploy_rects[t], color, 2, 8);
        //circle(drawImg, ccs[t], radius[t], color, 2, 8);
        if (contours_ploy[t].size() > 5)
        {
            ellipse(DstImg, myellipse[t], color, 1, 8);
            minRects[t].points(pts);
            for (int r = 0; r < 4; r++)
            {
                line(DstImg, pts[r], pts[(r + 1) % 4], color, 1, 8);
            }
        }
    }

}
