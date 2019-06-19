#include "q2.h"
#include"mainwindow.h"
#include<QGridLayout>
#include<QLayout>
#include<QMessageBox>
#include<QString>

extern processmodule CoreModule;  //处理数据：CVAction

void Q2::Myshow(int i)
{
    if(!this->itemAt(i)->widget()->isVisible())
    {
        this->itemAt(i)->widget()->show();
    }
}
void Q2::Myhide(int i)
{
    if(this->itemAt(i)->widget()->isVisible())
    {
        this->itemAt(i)->widget()->hide();
    }
}

void Q2::Correction_slots(int)
{
    int id=this->Correction->currentIndex();
    switch (id)
    {
        case 0:
        {
            for(int i=4;i<=7;i++)
            {
                Myshow(i);
            }
            for(int i=8;i<=17;i++)
            {
                Myhide(i);
            }
            break;
        }
        case 1:
        {
            Myhide(4);Myhide(5);Myhide(6);Myhide(7);
            Myshow(8);Myshow(9);
            for(int i=10;i<=17;i++)
            {
                Myhide(i);
            }
            break;
        }
        case 2:
        {
            for(int i=4;i<=9;i++)
            {
                Myhide(i);
            }
            Myshow(10);Myshow(11);
            for(int i=12;i<=17;i++)
            {
                Myhide(i);
            }
            break;
        }
        case 3:
        {
            for(int i=4;i<=11;i++)
            {
                Myhide(i);
            }
            for(int i=12;i<=15;i++)
            {
                Myshow(i);
            }
            Myhide(16);Myhide(17);
            break;
        }
        default:
        {
            for(int i=4;i<=15;i++)
            {
                Myhide(i);
            }
            Myshow(16);
            Myshow(17);
            break;
        }
    }
}

void Q2::change(int)
{
    int id=this->type->currentIndex();
    if(id==4)
    {
        if(this->itemAt(8)->widget()->isVisible())
        {
            this->itemAt(8)->widget()->hide();
            this->itemAt(9)->widget()->hide();
        }
        if(this->itemAt(2)->widget()->isVisible())
        {
            this->itemAt(2)->widget()->hide();
            this->itemAt(3)->widget()->hide();
        }
    }
    else if(id==6)
    {
        if(this->itemAt(2)->widget()->isVisible())
        {
            this->itemAt(2)->widget()->hide();
            this->itemAt(3)->widget()->hide();
        }
        if(!this->itemAt(8)->widget()->isVisible())
        {

            this->itemAt(8)->widget()->show();
            this->itemAt(9)->widget()->show();
        }
    }
    else
    {
        if(this->itemAt(8)->widget()->isVisible())
        {
            this->itemAt(8)->widget()->hide();
            this->itemAt(9)->widget()->hide();
        }
        if(!this->itemAt(2)->widget()->isVisible())
        {
            this->itemAt(2)->widget()->show();
            this->itemAt(3)->widget()->show();
        }
    }
    return;
}



void Q2::Operator_Slots(int)
{
    int id=this->Operator->currentIndex();
    if(id==0)
    {
        Myhide(4);Myhide(5);Myhide(8);Myhide(9);
        Myhide(10);Myhide(11);Myhide(12);Myhide(13);
        Myshow(6);Myshow(7);Myshow(0);Myshow(1);Myshow(2);Myshow(3);
    }
    else if(id==1)
    {
        Myhide(4);Myhide(5);Myhide(8);Myhide(9);
        Myshow(0);Myshow(1);Myshow(3);Myshow(6);
        for(int j=10;j<14;j++)
            Myshow(j);
    }
    else if(id==2)
    {
        Myhide(10);Myhide(11);Myhide(12);Myhide(13);
        Myshow(4);Myshow(5);Myshow(8);Myshow(9);
        Myshow(6);Myshow(7);Myshow(0);Myshow(1);Myshow(2);Myshow(3);
    }
    else if(id==3)
    {
        Myhide(6);Myhide(7);Myshow(3);Myshow(5);Myshow(8);
        Myhide(10);Myhide(11);Myhide(12);Myhide(13);Myshow(9);
        Myshow(0);Myshow(1);Myshow(2);Myshow(4);
    }
    else
    {
        Myshow(0);Myshow(1);Myshow(2);Myshow(3);
        for(int i=5;i<=13;i++)
        {
            Myhide(i);
        }
    }
}
void Q2::Enhance_Slots(int)
{
    int id=this->Enhance->currentIndex();
    if(id<3)
    {
        for(int i=4;i<=5;i++)
            Myshow(i);
        Myhide(6);Myhide(7);
    }
    else if(id==7)
    {
        for(int i=4;i<=5;i++)
            Myhide(i);
        Myshow(6);Myshow(7);
    }
    else
    {
        for(int i=4;i<=7;i++)
        {
            Myhide(i);
        }
    }
}
void Q2::ShowImgSize(int)
{
    if(this->ShowSizeFlag)
    {
        Mat now=CoreModule.getResult(this->imglist->currentIndex());
        QMessageBox::warning(NULL,tr("图片大小提示"),QString::number(now.cols)+"*"+QString::number(now.rows),QMessageBox::Yes);
    }
}

extern CVAction action;
void Q2::addPoint()
{
    action.p.push_back(Point2f(this->pointx->text().toDouble(),this->pointy->text().toDouble()));
    QMessageBox::warning(NULL,tr("提示"),tr("添加成功"),QMessageBox::Yes);
}
void Q2::Morphology_Slots(int)
{
    int id=this->Morphology->currentIndex();
    if(id<=1)
    {
        for(int i=2;i<=9;i++)
            Myshow(i);
    }
    else
    {
        Myshow(2);Myshow(3);
        Myhide(4);Myhide(5);
        for(int i=6;i<=9;i++)
            Myshow(i);
    }
}

Q2::Q2()
{
    this->type=new QComboBox();
    this->Operator=new QComboBox();
    this->Correction=new QComboBox();
    this->Enhance=new QComboBox();
    this->imglist = new QComboBox();
    this->pointx =new QLineEdit();
    this->Morphology=new QComboBox();
    this->pointy=new QLineEdit();
    this->add=new QPushButton();
    this->ShowSizeFlag=false;
    connect(this->type,SIGNAL(activated(int)),this,SLOT(change(int)));
    connect(this->Operator,SIGNAL(activated(int)),this,SLOT(Operator_Slots(int)));
    connect(this->Correction,SIGNAL(activated(int)),this,SLOT(Correction_slots(int)));
    connect(this->imglist,SIGNAL(activated(int)),this,SLOT(ShowImgSize(int)));
    connect(this->add,SIGNAL(pressed()),this,SLOT(addPoint()));
    connect(this->Enhance,SIGNAL(activated(int)),this,SLOT(Enhance_Slots(int)));
    connect(this->Morphology,SIGNAL(activated(int)),this,SLOT(Morphology_Slots(int)));
}

