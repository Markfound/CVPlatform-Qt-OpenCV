#include <iostream>
#include "processmodule.h"
#include"MainHeader.h"
#include<QFile>
#include<QDir>
#include<QFileDialog>

void processmodule::addCVActions(CVAction act)
{
    Order.push_back(act);
}

bool processmodule::swapCVActions(unsigned int index1, unsigned int index2)
{
    //Result.clear();
    if (Order.size()<index1 || Order.size()<index2)
    {
        return false;
    }
    else
    {
        CVAction t = Order[index1];
        Order[index1] = Order[index2];
        Order[index2] = t;
        //Result应重新执行，如果第一个是采集图像则不能调换              //待补充
        Mat m = Result[index1];
        Result[index1] = Result[index2];
        Result[index2] = m;
    }
    return true;
}

bool processmodule::deleteCVAction(int natrual_id)
{
    Order.erase(Order.begin()+natrual_id);
    Result.erase(Result.begin()+natrual_id);
    processCVActions(natrual_id,Order.size()-1);   //Markfound
    return true;
}

void processmodule::clearCVActions()
{
    Order.clear();
    Result.clear();
}
extern const int aNumberofChildren[5] = {0,2,5,10,19};
void processmodule::creat_cpp()  //5 3 6 8 3 2
{
    QString openpath=":/resources/Code.txt";
    QFile file1(openpath);
    file1.open(QFile::ReadOnly | QIODevice::Text);
    QTextStream in(&file1);
    QString savepath = QFileDialog::getSaveFileName(nullptr,tr("保存流程"),
                                                QDir::currentPath(),
                                                tr("*.cpp"));
    QFile file2(savepath);
    file2.open(QFile::WriteOnly | QIODevice::Text);
    QTextStream textStream(&file2);
    QString line = in.readAll();
    QStringList list=line.split("》");
    bool vis[100];
    memset(vis,0,sizeof vis);
    vector<int>op;
    vector<int>function;
    op.clear();
    function.clear();
    for(int i=0;i<Order.size();i++)
    {
        int index;
        if(Order[i].type_id<=4)
        {
            index=Order[i].type_id+Order[i].mode;
        }
        else if(Order[i].type_id<=10)
        {
            index=Order[i].type_id+4+Order[i].mode;
        }
        else if(Order[i].type_id==11)
        {
            index=Order[i].type_id+Order[i].mode+4+2;
        }
        else if(Order[i].type_id==12)
        {
            index=Order[i].type_id+Order[i].mode+4+2+5;
        }
        else if(Order[i].type_id<=14)
        {
            index=Order[i].type_id+4+2+5+7+Order[i].mode;
        }
        else if(Order[i].type_id<=17)
        {
            index=Order[i].type_id+4+2+5+7+2+Order[i].mode;
        }
        else
        {
            index=Order[i].type_id+4+2+5+7+2+1+Order[i].mode;
        }
        if(!vis[index])
        {
            vis[index]=1;

            function.push_back(index);
        }
        op.push_back(index);
    }
    textStream<<list[0]<<endl<<list[1]<<endl;
    for(int i=0;i<function.size();i++)
    {

        textStream<<list[function[i]+2]<<endl;
    }
    textStream<<list[list.size()-1]<<endl;
    openpath=":/resources/Code2.txt";
    QFile file3(openpath);
    file3.open(QFile::ReadOnly | QIODevice::Text);
    QTextStream in2(&file3);
    line=in2.readAll();
    QStringList list2=line.split(',');
    int cnt=1;
    for(int i=0;i<op.size();i++)
    {
        if(op[i]==0)
        {
            textStream<<"    "<<list2[op[i]]<<'(';
            textStream<<"DstImg,"<<'"'<<Order[i].arg[0]<<'"'<<");"<<endl;
            textStream<<"    Result.push_back(DstImg);"<<endl<<"    imshow("<<'"'<<cnt++<<'"'<<",DstImg);"<<endl;
        }
        else if(op[i]==1)
        {
            textStream<<"    "<<list2[op[i]]<<'(';
            textStream<<"Result["<<Order[i].arg[0].toInt()<<"],"<<'"'<<Order[i].arg[1]<<'"'<<");"<<endl;
        }
        else if(op[i]==12)
        {
            textStream<<"    pts.clear();"<<endl;
            for(int j=0;j<Order[i].p.size();j++)
            {
                textStream<<"    pts.push_back(Point("<<Order[i].p[j].x<<","<<Order[i].p[j].y<<"));"<<endl;
            }
            textStream<<"    "<<list2[op[i]]<<'(';
            textStream<<"Result["<<Order[i].arg[0].toInt()<<"],DstImg,pts);"<<endl;
        }
        else
        {
            //12
//            for(int j=0;j<Order[i].p.size();j++)
//            {
//                pts.push_back(Order[i].p[j]);
//            }
            textStream<<"    "<<list2[op[i]]<<'(';
            textStream<<"Result["<<Order[i].arg[0].toInt()<<"],DstImg";

            for(int j=1;j<Order[i].arg.size();j++)
            {
//                if(j==1&&Order[i].type_id==5&&(Order[i].mode==0||Order[i].mode==1||Order[i].mode==2||Order[i].mode==3||Order[i].mode==5))
//                    textStream<<",Result["<<Order[i].arg[j].toDouble()<<"]";
//                else
                textStream<<","<<Order[i].arg[j].toDouble();
            }
            textStream<<");"<<endl;
            textStream<<"    Result.push_back(DstImg);"<<endl<<"    imshow("<<'"'<<cnt++<<'"'<<",DstImg);"<<endl;
        }
    }
    textStream<<"    waitKey(0);"<<endl<<"    return 0;"<<endl<<"}";
    file1.close();
    file2.close();
    file3.close();
}

void processmodule::processCVActions(int st,int ed)
{
    isStop = false;
    for (unsigned int i = st; i <= ed;i++)
    {
        Mat result;
        switch (Order[i].type_id) {
        case 0:
        {
            string path_str = Order[i].arg[0].toLocal8Bit().constData();
            result = imread(path_str);
            break;
        }
        case 1:
        {
            string path_str = Order[i].arg[1].toLocal8Bit().constData();
            int which = Order[i].arg[0].toInt();
            imwrite(path_str,Result[which]);
            result = Result[which];
            break;
        }
        case 2:
        {
            PerspectiveTrans(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble(),Order[i].arg[3].toDouble(),Order[i].arg[4].toDouble(),Order[i].arg[5].toDouble(),Order[i].arg[6].toDouble(),Order[i].arg[7].toDouble(),Order[i].arg[8].toDouble(),Order[i].arg[9].toDouble(),Order[i].arg[10].toDouble(),Order[i].arg[11].toDouble(),Order[i].arg[12].toDouble(),Order[i].arg[13].toDouble(),Order[i].arg[14].toDouble(),Order[i].arg[15].toDouble(),Order[i].arg[16].toDouble());
            //Threshold_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toInt(),Order[i].arg[3].toInt());
            break;
        }
        case 3:
        {
            AffineTrans(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble(),Order[i].arg[3].toDouble(),Order[i].arg[4].toDouble(),Order[i].arg[5].toDouble(),Order[i].arg[6].toDouble(),Order[i].arg[7].toDouble(),Order[i].arg[8].toDouble(),Order[i].arg[9].toDouble(),Order[i].arg[10].toDouble(),Order[i].arg[11].toDouble(),Order[i].arg[12].toDouble());
            //Findcontours_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toInt()+1);
            break;
        }
        case 4:
        {
            //cvtColor(Result[Order[i].arg[0].toInt()],result,COLOR_RGB2GRAY);
            switch (Order[i].mode) {
            case 0:
            {
                resize_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble());
                break;
            }
            case 1:
            {
                getRotationMatrix2D_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble());
                break;
            }
            case 2:
            {
                mirror_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
                break;
            }
            case 3:
            {
                trainslation(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble());
                break;
            }
            default:
            {
                shear_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble());
                break;
            }
            }
            break;
        }
        case 5:
        {
            Rect_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble(),Order[i].arg[3].toDouble(),Order[i].arg[4].toDouble());
            break;
        }
        case 6:
        {
            RotatedRect_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble(),Order[i].arg[3].toDouble(),Order[i].arg[4].toDouble(),Order[i].arg[5].toDouble());
            break;
        }
        case 7:
        {
            circle_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble(),Order[i].arg[3].toDouble());
            break;
        }
        case 8:
        {
            vector<Point> pts;
            for(int j=0;j<Order[i].p.size();j++)
            {
                pts.push_back(Order[i].p[j]);
            }
            drawContours_s(Result[Order[i].arg[0].toInt()],result,pts);

            break;
        }
        case 9:
        {
            ellipse_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toDouble(),Order[i].arg[3].toDouble(),Order[i].arg[4].toDouble(),Order[i].arg[5].toDouble());
            break;
        }
        case 10:
        {
            if(Order[i].mode==0)
            {
                blur_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
            }
            else if(Order[i].mode==1)
            {
                MedianFiltering(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
            }
            else
            {
                GaussianFiltering(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
            }
//            switch (Order[i].arg[0].toInt())
//            {
//                case 0:
//                {
//                    equalizeHist_s(Result[Order[i].arg[1].toInt()],result);
//                    break;
//                }
//                case 1:
//                {
//                    Log(Result[Order[i].arg[1].toInt()],result,Order[i].arg[2].toDouble());
//                    break;
//                }
//                default:
//                {
//                    Gamma(Result[Order[i].arg[1].toInt()],result,Order[i].arg[2].toDouble());
//                    break;
//                }
//            }
            break;
        }
        case 11:
        {
            if(Order[i].mode==0)
            {
                Laplacian_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
            }
            else if(Order[i].mode==1)
            {
                Canny_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toDouble(),Order[i].arg[3].toDouble());
            }
            else if(Order[i].mode==2)
            {
                Sobel_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toDouble(),Order[i].arg[3].toInt());
            }
            else if(Order[i].mode==3)
            {
                Scharr_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble(),Order[i].arg[2].toInt());
            }
            else if(Order[i].mode==4)
            {
                prewitt_s(Result[Order[i].arg[0].toInt()],result);
            }
            else
            {
                robot_s(Result[Order[i].arg[0].toInt()],result);
            }
            //Dis_Trans(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
            break;
        }
        case 12:
        {
            if(Order[i].mode==0)
                equalizeHist_s(Result[Order[i].arg[0].toInt()],result);
            else if(Order[i].mode==1)
                Log(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble());
            else if(Order[i].mode==2)
                Gamma(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toDouble());
            else if(Order[i].mode==3)
                equalizeHist_stretching(Result[Order[i].arg[0].toInt()],result);
            else if(Order[i].mode==4)
                lut(Result[Order[i].arg[0].toInt()],result);
            else if(Order[i].mode==5)
                ImageReverse(Result[Order[i].arg[0].toInt()],result);
            else if(Order[i].mode==6)
                cvtColor_s(Result[Order[i].arg[0].toInt()],result);
            else
                applyColorMap_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
            break;
        }
        case 13:
        {
            unevenLightCompensate(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt());
            break;
        }
        case 14:
        {
            if(Order[i].mode==0)
            {
                Corrosion(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toInt(),Order[i].arg[3].toInt());
            }
            else if(Order[i].mode==1)
            {
                Expanding(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toInt(),Order[i].arg[3].toInt());
            }
            else
            {
                morphologyEx_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toInt(),Order[i].arg[3].toInt());
            }
            break;
        }
        case 15:
        {
            Threshold_s(Result[Order[i].arg[0].toInt()],result,Order[i].arg[1].toInt(),Order[i].arg[2].toInt(),Order[i].arg[3].toInt());
            break;
        }
        case 16:
        {
            dft_s(Result[Order[i].arg[0].toInt()],result);
            break;
        }
        case 17:
        {
            if(Order[i].mode)
            {
                verticalProjectionMat(Result[Order[i].arg[0].toInt()],result);
            }
            else
            {
                horizontalProjectionMat(Result[Order[i].arg[0].toInt()],result);
            }
            break;
        }
        case 18:
        {
            calcHist_s(Result[Order[i].arg[0].toInt()],result);
            break;
        }
        case 19:
        {
            HitOrMiss(Result[Order[i].arg[0].toInt()],result);
            break;
        }
        case 20:
        {
            thinImage(Result[Order[i].arg[0].toInt()],result);
            break;
        }
        default:

            break;
        }

        /*if (isStop)
        {
            emit BreakProcessing();
            break;
        }*/

        if ((unsigned int)Result.size()<=i)
            Result.push_back(result);
        else
            Result[i] = result;

    }
    emit FinishProcessing();
}

Mat processmodule::getResult(int natural_id)
{
    return Result[natural_id];
}

