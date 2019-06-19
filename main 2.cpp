#include "MainHeader.h"

int main()
{
    Mat SrcImg = imread("/Users/markfound/Desktop/20160912223814977.jpg");
    Mat Res;
    Dis_Trans(SrcImg, Res);
    imshow("res", Res);
    waitKey(0);
    return 0;
}
