#ifndef PROCESSMODULE_H
#define PROCESSMODULE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <QDebug>
#include <QObject>
#include<QPushButton>
#include<QLineEdit>
//#pragma execution_character_set("utf-8")

using namespace std;
using namespace cv;

struct CVAction   //Markfound
{
    int type_id;
    unsigned int mode;
    QString name;
    bool isProcessed = false;
    vector<QString>arg;
    vector<Point>p;
    CVAction()
    {
        type_id=-1;
        name="";
        mode=0;
        p.clear();
        arg.clear();
    }
    CVAction(unsigned int i, QString n) : type_id(i), name(n)
    {
        mode=0;
        p.clear();
        arg.clear();
    }
};

class processmodule : public QObject        //与主程序通讯
{
    Q_OBJECT

public:
    processmodule() {}
    Mat getResult(int natural_id);  //获取Result（答案）数组里面的图片
    void addCVActions(CVAction act);  //添加CVAction进Order里面
    bool deleteCVAction(int natrual_id);  //删除对应的CVAction
    bool swapCVActions(unsigned int index1, unsigned int index2);
    void clearCVActions();
    void processCVActions(int begin_natural_id,int end_natrual_id);
    unsigned long getNumberOfCVActions() {return Order.size();}
    unsigned long getNumberOfResults() {return Result.size();}
    void creat_cpp();
    CVAction& getCVAction(int natrual_id) {return Order[natrual_id];}

signals:
    void FinishProcessing();
    void BreakProcessing();

private:
    //想修改一下数据结构，使用数组+指针方式储存执行流程以及执行结果。可通过实验检测。
    vector<CVAction> Order;
    vector<Mat> Result;
    Mat LoadImage(QString path);
    Mat SaveImage(QString path);
    bool isStop = false;


};

#endif // PROCESSMODULE_H
