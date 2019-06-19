#ifndef Q2_H
#define Q2_H

#include"processmodule.h"
#include <QWidget>
#include<QComboBox>
#include<QGridLayout>
#include<QPushButton>
class Q2 : public QGridLayout
{
    Q_OBJECT
public:
    explicit Q2();
    QComboBox *type;
    QComboBox *Operator;
    QComboBox *Correction;
    QComboBox *Enhance;
    QComboBox *imglist;
    QComboBox *Morphology;
    QLineEdit *pointx;
    QLineEdit *pointy;
    QPushButton *add;
    bool ShowSizeFlag;
    void Myshow(int);
    void Myhide(int);
public slots:
    void Morphology_Slots(int);
    void Correction_slots(int);
    void ShowImgSize(int);
    void Enhance_Slots(int);
    void change(int);
    void Operator_Slots(int);
    void addPoint();
};

#endif // Q2_H
