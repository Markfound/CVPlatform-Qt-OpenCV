#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MainHeader.h"
#include "q2.h"

//#pragma execution_character_set("utf-8")

//计算方法：当前的前一组的项目数
const int aNumberofChildren[5] = {0,2,5,10,19};
CVAction action;

processmodule CoreModule;  //处理数据：CVAction

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1024,768);
    setWindowTitle(tr("Computer Vision Platform"));

    //Menu
    QMenuBar* mBar = menuBar();   //顶部状态栏
    mBar->setContextMenuPolicy(Qt::PreventContextMenu);
    QMenu *pFile = mBar->addMenu(tr("文件"));
    QAction *pNew = new QAction(tr("新建"),pFile);
    QAction *pOpen = new QAction(tr("打开"),pFile);
    QAction *pSave = new QAction(tr("保存"),pFile);
    QAction *pClose = new QAction(tr("关闭"),pFile);
    pFile->addAction(pNew);
    pFile->addAction(pOpen);
    pFile->addAction(pSave);
    pFile->addAction(pClose);
    connect(pOpen,&QAction::triggered,this,&MainWindow::openProcess);
    connect(pNew,&QAction::triggered,this,&MainWindow::newProcess);
    connect(pSave,&QAction::triggered,this,&MainWindow::saveProcess);
    connect(pClose,&QAction::triggered,this,&MainWindow::closeProcess);

    QMenu *pProcess = mBar->addMenu(tr("流程"));
    QAction *pGenerate = new QAction(tr("生成Cpp代码"),pProcess);
    pProcess->addAction(pGenerate);
    connect(pGenerate,&QAction::triggered,this,&MainWindow::Generate_Code);
    //Tool
    pTree = new QTreeWidget();  //菜单栏
    pTree->setHeaderLabel(tr("工具箱"));
    pTree->expandsOnDoubleClick();  //双击展开

    QTreeWidgetItem *pBasicOperation = new QTreeWidgetItem(pTree,QStringList(QString(tr("输入输出"))));
    QTreeWidgetItem *pGetImage = new QTreeWidgetItem(pBasicOperation,QStringList(QString(tr("采集图像"))));
    QTreeWidgetItem *pSaveImage = new QTreeWidgetItem(pBasicOperation,QStringList(QString(tr("储存图像"))));
    pBasicOperation->addChild(pGetImage);
    pBasicOperation->addChild(pSaveImage);

    QTreeWidgetItem *pCorrection = new QTreeWidgetItem(pTree,QStringList(QString(tr("畸变矫正"))));
    QTreeWidgetItem *pPerspective = new QTreeWidgetItem(pCorrection,QStringList(QString(tr("透视变换"))));
    QTreeWidgetItem *pAffine = new QTreeWidgetItem(pCorrection,QStringList(QString(tr("仿射变换"))));
    QTreeWidgetItem *pGeometric = new QTreeWidgetItem(pCorrection,QStringList(QString(tr("几何变换"))));
    pCorrection->addChild(pPerspective);
    pCorrection->addChild(pAffine);
    pCorrection->addChild(pGeometric);

    QTreeWidgetItem *pROI = new QTreeWidgetItem(pTree,QStringList(QString(tr("ROI"))));
    QTreeWidgetItem *pRectangle = new QTreeWidgetItem(pROI,QStringList(QString(tr("正矩形"))));
    QTreeWidgetItem *pRotating_rectangle = new QTreeWidgetItem(pROI,QStringList(QString(tr("旋转矩形"))));
    QTreeWidgetItem *pRing = new QTreeWidgetItem(pROI,QStringList(QString(tr("圆形"))));
    QTreeWidgetItem *pRound = new QTreeWidgetItem(pROI,QStringList(QString(tr("多边形"))));
    QTreeWidgetItem *pPolygon = new QTreeWidgetItem(pROI,QStringList(QString(tr("椭圆形"))));
    pROI->addChild(pRectangle);
    pROI->addChild(pRotating_rectangle);
    pROI->addChild(pRing);
    pROI->addChild(pRound);
    pROI->addChild(pPolygon);

    QTreeWidgetItem *pPretreatment = new QTreeWidgetItem(pTree,QStringList(QString(tr("预处理"))));
    QTreeWidgetItem *pDenoising = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("去噪"))));
    QTreeWidgetItem *pEdge_detection = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("边缘检测"))));
    QTreeWidgetItem *pBrightness_enhancement = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("亮度增强"))));
    QTreeWidgetItem *pMake_up = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("补偿"))));
    QTreeWidgetItem *pMorphology = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("形态学 （灰度）"))));
    QTreeWidgetItem *pBinarization = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("二值化 "))));
    QTreeWidgetItem *pFrequency = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("频域处理（FFT）"))));
    QTreeWidgetItem *pProjection = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("投影"))));
    QTreeWidgetItem *pHist = new QTreeWidgetItem(pPretreatment,QStringList(QString(tr("直方图"))));
    pPretreatment->addChild(pDenoising);
    pPretreatment->addChild(pEdge_detection);
    pPretreatment->addChild(pBrightness_enhancement);
    pPretreatment->addChild(pMake_up);
    pPretreatment->addChild(pMorphology);
    pPretreatment->addChild(pBinarization);
    pPretreatment->addChild(pFrequency);
    pPretreatment->addChild(pProjection);
    pPretreatment->addChild(pHist);

    QTreeWidgetItem *pSplit = new QTreeWidgetItem(pTree,QStringList(QString(tr("分割"))));
    QTreeWidgetItem *pMorphology_B = new QTreeWidgetItem(pSplit,QStringList(QString(tr("击中击不中"))));
    QTreeWidgetItem *pMorphology_C = new QTreeWidgetItem(pSplit,QStringList(QString(tr("骨骼细化"))));
    pSplit->addChild(pMorphology_B);
    pSplit->addChild(pMorphology_C);

//Markfound
    QToolBar *pBar = new QToolBar(tr("工具箱"));
    pBar->setContextMenuPolicy(Qt::PreventContextMenu);
    addToolBar(Qt::LeftToolBarArea,pBar);
    pBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    pBar->setFixedWidth(160);
    pBar->addWidget(pTree);

    connect(pTree,&QTreeWidget::doubleClicked,this,&MainWindow::addProcess);

    //StatusBar
    pSBar = ui->statusBar;
    pSBar->showMessage(tr("请先新建流程"));

    //DockWidget
    pProcessDock = new QDockWidget(QString(tr("流程 - ")) + sLocalFileName + QString("*"));
    pProcessDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    pProcessDock->setMinimumWidth(250);
    mActionsView = new QListView();

    pSLModel = new QStringListModel();
    pSLModel->setStringList(lProList);

    mActionsView->setModel(pSLModel);
    mActionsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mActionsView->setContextMenuPolicy(Qt::CustomContextMenu);
    mActionsView->setUpdatesEnabled(true);

    connect(mActionsView, &QListView::customContextMenuRequested,this,&MainWindow::showContextMenu);
    connect(mActionsView,&QListView::clicked,this,&MainWindow::clickAction);

    pProcessDock->setWidget(mActionsView);
    pProcessDock->setVisible(false);

    addDockWidget(Qt::LeftDockWidgetArea,pProcessDock);

    //Central Widget
    pCentral = ui->centralWidget;
    pCETLayout->addWidget(Img_label);
    pCentral->setLayout(pCETLayout);

    //信号与槽
    connect(&CoreModule,&processmodule::FinishProcessing,this,&MainWindow::endProcess);
    connect(&CoreModule,&processmodule::BreakProcessing,this,&MainWindow::stopProcess);

    showMaximized();
}
bool MainWindow::SetArgs()
{
    QDialog *setting_dialog = new QDialog();
    setting_dialog->setWindowTitle(tr("CVPlatform - ") + action.name);
    setting_dialog->setFixedHeight(250);
    setting_dialog->setFixedWidth(500);
    setting_dialog->setWindowFlags(Qt::WindowMaximizeButtonHint);
    Q2 layout;

    QLabel *proimglabel = new QLabel(tr("处理图像："));


    QPushButton *savebutton = new QPushButton(tr("确定"));
    QPushButton *cancelbutton = new QPushButton(tr("取消"));
    connect(savebutton,&QPushButton::clicked,setting_dialog,&QDialog::accept);
    connect(cancelbutton,&QPushButton::clicked,setting_dialog,&QDialog::reject);
    for (auto i = lProList.begin(); i != lProList.end() && *i != action.name; i++)
    {
        layout.imglist->addItem(*i);
    }
    layout.addWidget(proimglabel,0,0,1,1);
    layout.addWidget(layout.imglist,0,1,1,2);
    switch (action.type_id) {
    case 0:
    case 1:
    {
        QLabel *tip0 = new QLabel();
        QPushButton *button0 = new QPushButton(tr("..."));
        connect(button0,&QPushButton::clicked,this,&MainWindow::gGetFilePath);
        GlobalFlag = action.type_id;
        if (action.type_id)
        {
            GlobalEdit1->setText("");
        }
        else
        {
            proimglabel->setVisible(false);
            layout.imglist->setVisible(false);
            GlobalEdit1->setText("");
        }

        tip0->setText(tr("文件路径："));
        layout.addWidget(tip0,1,0,1,1);
        layout.addWidget(GlobalEdit1,1,1,1,1);
        layout.addWidget(button0,1,2,1,1);
        layout.addWidget(savebutton,2,1,1,1);
        layout.addWidget(cancelbutton,2,2,1,1);

        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        action.mode=0;
        if (action.type_id)
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(GlobalEdit1->text());
        }
        else
        {
            action.arg.push_back(GlobalEdit1->text());
        }
        break;
    }
    case 2:
    {
        layout.ShowSizeFlag=true;
        QLabel *tip1=new QLabel("指定变换前后四个点的坐标:");
        QLabel *tip11=new QLabel("a(x,y):");QLabel *tip12=new QLabel("a'(x,y):");
        QLabel *tip21=new QLabel("b(x,y):");QLabel *tip22=new QLabel("b'(x,y):");
        QLabel *tip31=new QLabel("c(x,y):");QLabel *tip32=new QLabel("c'(x,y):");
        QLabel *tip41=new QLabel("d(x,y):");QLabel *tip42=new QLabel("d'(x,y):");
        QLineEdit *edit11=new QLineEdit();QLineEdit *edit12=new QLineEdit();
        QLineEdit *edit21=new QLineEdit();QLineEdit *edit22=new QLineEdit();
        QLineEdit *edit31=new QLineEdit();QLineEdit *edit32=new QLineEdit();
        QLineEdit *edit41=new QLineEdit();QLineEdit *edit42=new QLineEdit();

        QLineEdit *edit13=new QLineEdit();QLineEdit *edit14=new QLineEdit();
        QLineEdit *edit23=new QLineEdit();QLineEdit *edit24=new QLineEdit();
        QLineEdit *edit33=new QLineEdit();QLineEdit *edit34=new QLineEdit();
        QLineEdit *edit43=new QLineEdit();QLineEdit *edit44=new QLineEdit();
        layout.addWidget(tip1,1,0,1,4);
        layout.addWidget(tip11,2,0,1,0,0);
        layout.addWidget(edit11,2,1,1,1);layout.addWidget(edit12,2,2,1,1);
        layout.addWidget(tip21,3,0,1,1);
        layout.addWidget(edit21,3,1,1,1);layout.addWidget(edit22,3,2,1,1);
        layout.addWidget(tip31,4,0,1,1);
        layout.addWidget(edit31,4,1,1,1);layout.addWidget(edit32,4,2,1,1);
        layout.addWidget(tip41,5,0,1,1);
        layout.addWidget(edit41,5,1,1,1);layout.addWidget(edit42,5,2,1,1);

        layout.addWidget(tip12,2,3,1,1);
        layout.addWidget(edit13,2,4,1,1);layout.addWidget(edit14,2,5,1,1);
        layout.addWidget(tip22,3,3,1,1);
        layout.addWidget(edit23,3,4,1,1);layout.addWidget(edit24,3,5,1,1);
        layout.addWidget(tip32,4,3,1,1);
        layout.addWidget(edit33,4,4,1,1);layout.addWidget(edit34,4,5,1,1);
        layout.addWidget(tip42,5,3,1,1);
        layout.addWidget(edit43,5,4,1,1);layout.addWidget(edit44,5,5,1,1);

        layout.addWidget(savebutton,6,1,1,1);
        layout.addWidget(cancelbutton,6,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        action.mode=0;
        layout.ShowSizeFlag=false;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit11->text());action.arg.push_back(edit12->text());
            action.arg.push_back(edit21->text());action.arg.push_back(edit22->text());
            action.arg.push_back(edit31->text());action.arg.push_back(edit32->text());
            action.arg.push_back(edit41->text());action.arg.push_back(edit42->text());
            action.arg.push_back(edit13->text());action.arg.push_back(edit14->text());
            action.arg.push_back(edit23->text());action.arg.push_back(edit24->text());
            action.arg.push_back(edit33->text());action.arg.push_back(edit34->text());
            action.arg.push_back(edit43->text());action.arg.push_back(edit44->text());
        }
        break;
    }
    case 3:
    {
        layout.ShowSizeFlag=true;
        QLabel *tip1=new QLabel("指定变换前后三个点的坐标:");
        QLabel *tip11=new QLabel("a(x,y):");QLabel *tip12=new QLabel("a'(x,y):");
        QLabel *tip21=new QLabel("b(x,y):");QLabel *tip22=new QLabel("b'(x,y):");
        QLabel *tip31=new QLabel("c(x,y):");QLabel *tip32=new QLabel("c'(x,y):");
        QLineEdit *edit11=new QLineEdit();QLineEdit *edit12=new QLineEdit();
        QLineEdit *edit21=new QLineEdit();QLineEdit *edit22=new QLineEdit();
        QLineEdit *edit31=new QLineEdit();QLineEdit *edit32=new QLineEdit();

        QLineEdit *edit13=new QLineEdit();QLineEdit *edit14=new QLineEdit();
        QLineEdit *edit23=new QLineEdit();QLineEdit *edit24=new QLineEdit();
        QLineEdit *edit33=new QLineEdit();QLineEdit *edit34=new QLineEdit();
        layout.addWidget(tip1,1,0,1,4);
        layout.addWidget(tip11,2,0,1,0,0);
        layout.addWidget(edit11,2,1,1,1);layout.addWidget(edit12,2,2,1,1);
        layout.addWidget(tip21,3,0,1,1);
        layout.addWidget(edit21,3,1,1,1);layout.addWidget(edit22,3,2,1,1);
        layout.addWidget(tip31,4,0,1,1);
        layout.addWidget(edit31,4,1,1,1);layout.addWidget(edit32,4,2,1,1);

        layout.addWidget(tip12,2,3,1,1);
        layout.addWidget(edit13,2,4,1,1);layout.addWidget(edit14,2,5,1,1);
        layout.addWidget(tip22,3,3,1,1);
        layout.addWidget(edit23,3,4,1,1);layout.addWidget(edit24,3,5,1,1);
        layout.addWidget(tip32,4,3,1,1);
        layout.addWidget(edit33,4,4,1,1);layout.addWidget(edit34,4,5,1,1);

        layout.addWidget(savebutton,6,1,1,1);
        layout.addWidget(cancelbutton,6,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        action.mode=0;
        layout.ShowSizeFlag=false;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit11->text());action.arg.push_back(edit12->text());
            action.arg.push_back(edit21->text());action.arg.push_back(edit22->text());
            action.arg.push_back(edit31->text());action.arg.push_back(edit32->text());
            action.arg.push_back(edit13->text());action.arg.push_back(edit14->text());
            action.arg.push_back(edit23->text());action.arg.push_back(edit24->text());
            action.arg.push_back(edit33->text());action.arg.push_back(edit34->text());
        }
        break;
    }
    case 4:
    {
        layout.Correction->addItem("放大缩小");
        layout.Correction->addItem("旋转");
        layout.Correction->addItem("镜像");
        layout.Correction->addItem("平移");
        layout.Correction->addItem("错切");
        QLabel *tip1=new QLabel(tr("操作模式："));
        QLabel *tip21=new QLabel(tr("水平放大系数："));
        QLabel *tip22=new QLabel(tr("垂直放大系数："));
        QLineEdit *edit21=new QLineEdit(tr("1.0"));
        QLineEdit *edit22=new QLineEdit(tr("1.0"));
        QLabel *tip3=new QLabel(tr("旋转角度(0~360)："));
        QLineEdit *edit3=new QLineEdit(tr("90"));
        QComboBox *combox4=new QComboBox();
        combox4->addItem("水平镜像");
        combox4->addItem("垂直镜像");
        QLabel *tip4=new QLabel(tr("镜像模式："));
        QLabel *tip51=new QLabel(tr("垂直平移系数(0.0~1.0)："));
        QLabel *tip52=new QLabel(tr("水平平移系数(0.0~1.0)："));
        QLineEdit *edit51=new QLineEdit(tr("0.0"));
        QLineEdit *edit52=new QLineEdit(tr("0.0"));
        QLabel *tip6=new QLabel(tr("错切比率(0~50)："));
        QLineEdit *edit6=new QLineEdit(tr("0"));

        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(layout.Correction,1,1,1,2);

        layout.addWidget(tip21,2,0,1,1);
        layout.addWidget(edit21,2,1,1,2);
        layout.addWidget(tip22,3,0,1,1);
        layout.addWidget(edit22,3,1,1,2);

        layout.addWidget(tip3,2,0,1,1);
        layout.addWidget(edit3,2,1,1,2);

        layout.addWidget(tip4,2,0,1,1);
        layout.addWidget(combox4,2,1,1,2);

        layout.addWidget(tip51,2,0,1,1);
        layout.addWidget(edit51,2,1,1,2);
        layout.addWidget(tip52,3,0,1,1);
        layout.addWidget(edit52,3,1,1,2);

        layout.addWidget(tip6,2,0,1,1);
        layout.addWidget(edit6,2,1,1,2);

        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);
        setting_dialog->setLayout(&layout);
        for(int i=8;i<=17;i++)
            layout.itemAt(i)->widget()->hide();
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        if(action.arg.empty())
        {
            action.mode=layout.Correction->currentIndex();
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            switch (action.mode) {
            case 0:
            {
                action.arg.push_back(edit21->text());
                action.arg.push_back(edit22->text());
                break;
            }
            case 1:
            {
                action.arg.push_back(edit3->text());
                break;
            }
            case 2:
            {
                action.arg.push_back(QString::number(combox4->currentIndex()));
                break;
            }
            case 3:
            {
                action.arg.push_back(edit51->text());
                action.arg.push_back(edit52->text());
                break;
            }
            default:
            {
                action.arg.push_back(edit6->text());
                break;
            }
            }
        }
        break;
    }
    case 5:
    {
        layout.ShowSizeFlag=true;
        QLabel *tip1=new QLabel("点1坐标：");
        QLabel *tip2=new QLabel("点2坐标：");
        QLineEdit *edit11=new QLineEdit();
        QLineEdit *edit12=new QLineEdit();
        QLineEdit *edit21=new QLineEdit();
        QLineEdit *edit22=new QLineEdit();
        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(edit11,1,1,1,1);
        layout.addWidget(edit12,1,2,1,1);
        layout.addWidget(tip2,2,0,1,1);
        layout.addWidget(edit21,2,1,1,1);
        layout.addWidget(edit22,2,2,1,1);
        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        layout.ShowSizeFlag=false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit11->text());
            action.arg.push_back(edit12->text());
            action.arg.push_back(edit21->text());
            action.arg.push_back(edit22->text());
        }
//        QComboBox *imglist2 = new QComboBox();

//        for (auto i = lProList.begin(); i != lProList.end() && *i != action.name; i++)
//        {
//            imglist2->addItem(*i);
//        }

//        QLabel *tip0 = new QLabel(tr("处理图像2："));
//        QLabel *tip1 = new QLabel(tr("运算类型："));
//        QLabel *tip2 = new QLabel(tr("曝光度"));
//        QLineEdit *edit0=new QLineEdit();
//        edit0->setText("1");
//        //QComboBox *type = new QComboBox();
//        layout.type->addItem("Add(加)");
//        layout.type->addItem("Sub(减)");
//        layout.type->addItem("And(与)");
//        layout.type->addItem("Or(或)");
//        layout.type->addItem("Complement(非)");
//        layout.type->addItem("Exclusive or(异或)");
//        layout.type->addItem("Exposure(曝光)");
//        layout.addWidget(tip0,1,0);
//        layout.addWidget(imglist2,1,1);
//        layout.addWidget(tip1,2,0);
//        layout.addWidget(layout.type,2,1);
//        layout.addWidget(savebutton,3,1,1,1);
//        layout.addWidget(cancelbutton,3,2,1,1);
//        layout.addWidget(tip2,1,0);
//        layout.addWidget(edit0,1,1);
//        setting_dialog->setLayout(&layout);
//        layout.itemAt(8)->widget()->hide();
//        layout.itemAt(9)->widget()->hide();
//        if (setting_dialog->exec() == QDialog::Rejected)
//            return false;
//        if(action.arg.empty())
//        {
//            action.mode=layout.type->currentIndex();
//            action.arg.push_back(QString::number(imglist->currentIndex()));
//            if(layout.type->currentIndex()==4)
//            {

//            }
//            else if(layout.type->currentIndex()==6)
//            {
//                action.arg.push_back(edit0->text());
//            }
//            else
//            {
//                action.arg.push_back(QString::number(imglist2->currentIndex()));
//            }
//        }
        break;
    }
    case 6:
    {
        layout.ShowSizeFlag=true;
        QLabel *tip1=new QLabel("中心点坐标：");
        QLabel *tip2=new QLabel("矩阵大小：");
        QLabel *tip3=new QLabel("旋转角度：");
        QLineEdit *edit11=new QLineEdit();
        QLineEdit *edit12=new QLineEdit();
        QLineEdit *edit21=new QLineEdit();
        QLineEdit *edit22=new QLineEdit();
        QLineEdit *edit3=new QLineEdit();
        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(edit11,1,1,1,1);
        layout.addWidget(edit12,1,2,1,1);
        layout.addWidget(tip2,2,0,1,1);
        layout.addWidget(edit21,2,1,1,1);
        layout.addWidget(edit22,2,2,1,1);
        layout.addWidget(tip3,3,0,1,1);
        layout.addWidget(edit3,3,1,1,2);
        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        layout.ShowSizeFlag=false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit11->text());
            action.arg.push_back(edit12->text());
            action.arg.push_back(edit21->text());
            action.arg.push_back(edit22->text());
            action.arg.push_back(edit3->text());
        }
//        layout.addWidget(savebutton,1,1,1,1);
//        layout.addWidget(cancelbutton,1,2,1,1);
//        setting_dialog->setLayout(&layout);
//        if (setting_dialog->exec() == QDialog::Rejected)
//            return false;
//        action.mode=0;
//        action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        break;
    }
    case 7:
    {
        layout.ShowSizeFlag=true;
        QLabel *tip1=new QLabel("圆心坐标：");
        QLabel *tip2=new QLabel("半径：");
        QLineEdit *edit11=new QLineEdit();
        QLineEdit *edit12=new QLineEdit();
        QLineEdit *edit21=new QLineEdit();
        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(edit11,1,1,1,1);
        layout.addWidget(edit12,1,2,1,1);
        layout.addWidget(tip2,2,0,1,1);
        layout.addWidget(edit21,2,1,1,1);
        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        layout.ShowSizeFlag=false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit11->text());
            action.arg.push_back(edit12->text());
            action.arg.push_back(edit21->text());
        }

        break;
    }
    case 8:
    {
        layout.ShowSizeFlag=true;
        layout.add->setText("添加点");
        QLabel *tip1 =new QLabel("边界点坐标：");
        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(layout.pointx,1,1,1,1);
        layout.addWidget(layout.pointy,1,2,1,1);
        layout.addWidget(layout.add,1,3,1,1);
        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        if(action.p.size()<3)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        layout.ShowSizeFlag=false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        }

        break;
    }
    case 9:
    {
        layout.ShowSizeFlag=true;
        QLabel *tip1=new QLabel("椭圆中心坐标：");
        QLabel *tip2=new QLabel("椭圆长短轴：");
        QLabel *tip3=new QLabel("中心角度(0~360)：");
        QLineEdit *edit11=new QLineEdit();
        QLineEdit *edit12=new QLineEdit();
        QLineEdit *edit21=new QLineEdit();
        QLineEdit *edit22=new QLineEdit();
        QLineEdit *edit3=new QLineEdit();
        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(edit11,1,1,1,1);
        layout.addWidget(edit12,1,2,1,1);
        layout.addWidget(tip2,2,0,1,1);
        layout.addWidget(edit21,2,1,1,1);
        layout.addWidget(edit22,2,2,1,1);
        layout.addWidget(tip3,3,0,1,1);
        layout.addWidget(edit3,3,1,1,1);
        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
        {
            layout.ShowSizeFlag=false;
            return false;
        }
        layout.ShowSizeFlag=false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit11->text());
            action.arg.push_back(edit12->text());
            action.arg.push_back(edit21->text());
            action.arg.push_back(edit22->text());
            action.arg.push_back(edit3->text());
        }



        break;
    }
    case 10:
    {
                QComboBox *combox1=new QComboBox();
                combox1->addItem("均值滤波");
                combox1->addItem("中值滤波");
                combox1->addItem("高斯滤波");
                QLabel *tip1=new QLabel();
                QLabel *tip2=new QLabel();
                tip1->setText(tr("Filtering Method:"));
                tip2->setText(tr("Kernel Size:"));
                QLineEdit *edit1=new QLineEdit();
                edit1->setText("3");
                layout.addWidget(tip1,1,0,1,1);
                layout.addWidget(combox1,1,1,1,2);
                layout.addWidget(tip2,2,0,1,1);
                layout.addWidget(edit1,2,1,1,2);
                layout.addWidget(savebutton,3,1,1,1);
                layout.addWidget(cancelbutton,3,2,1,1);
                setting_dialog->setLayout(&layout);
                if (setting_dialog->exec() == QDialog::Rejected)
                    return false;
                if(action.arg.empty())
                {
                    action.mode=combox1->currentIndex();
                    action.arg.push_back(QString::number(layout.imglist->currentIndex()));
                    action.arg.push_back(edit1->text());
                }

        break;
    }
    case 11:
    {
        QLabel *tip0=new QLabel();
        layout.Operator->addItem("Laplacian");
        layout.Operator->addItem("Canny");
        layout.Operator->addItem("Sobel");
        layout.Operator->addItem("Scharr");
        layout.Operator->addItem("Prewitt");
        layout.Operator->addItem("Robot");
        QComboBox *combox1=new QComboBox();
        combox1->addItem("BORDER_CONSTANT");
        combox1->addItem("BORDER_REFLECT");
        combox1->addItem("BORDER_REFLECT101");
        combox1->addItem("BORDER_WRAP");
        combox1->addItem("BORDER_DEFAULT");
        combox1->addItem("BORDER_TRANSPARENT");
        QLabel *tip1=new QLabel();
        QLabel *tip2=new QLabel();
        QLabel *tip3=new QLabel();
        QLabel *tip4=new QLabel();
        QLabel *tip5=new QLabel();
        QLineEdit *edit1=new QLineEdit(tr("3"));
        QLineEdit *edit2=new QLineEdit(tr("1"));
        QLineEdit *edit3=new QLineEdit(tr("50"));
        QLineEdit *edit4=new QLineEdit(tr("120"));
        tip0->setText(tr("Operator:"));
        tip1->setText(tr("Kernel Size："));
        tip2->setText(tr("Scale："));
        tip3->setText(tr("threshold1："));
        tip4->setText(tr("threshold2："));
        tip5->setText(tr("BorderMode："));
        layout.addWidget(tip0,1,0,1,1);
        layout.addWidget(layout.Operator,1,1,1,2);
        layout.addWidget(tip5,2,0,1,1);
        layout.addWidget(combox1,2,1,1,2);
        layout.addWidget(tip1,3,0,1,1);
        layout.addWidget(edit1,3,1,1,2);
        layout.addWidget(tip2,4,0,1,1);
        layout.addWidget(edit2,4,1,1,2);
        layout.addWidget(tip3,5,0,1,1);
        layout.addWidget(edit3,5,1,1,2);
        layout.addWidget(tip4,6,0,1,1);
        layout.addWidget(edit4,6,1,1,2);
        layout.addWidget(savebutton,7,1,1,1);
        layout.addWidget(cancelbutton,7,2,1,1);
        setting_dialog->setLayout(&layout);
        layout.itemAt(4)->widget()->hide();
        layout.itemAt(5)->widget()->hide();
        layout.itemAt(8)->widget()->hide();
        layout.itemAt(9)->widget()->hide();
        layout.itemAt(10)->widget()->hide();
        layout.itemAt(11)->widget()->hide();
        layout.itemAt(12)->widget()->hide();
        layout.itemAt(13)->widget()->hide();

        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        action.mode=layout.Operator->currentIndex();
        if(layout.Operator->currentIndex()==0)
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit1->text());
        }
        else if(layout.Operator->currentIndex()==1)
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit1->text());
            action.arg.push_back(edit3->text());
            action.arg.push_back(edit4->text());
        }
        else if(layout.Operator->currentIndex()==2)
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit1->text());
            action.arg.push_back(edit2->text());
            action.arg.push_back(QString::number(combox1->currentIndex()));
        }
        else if(layout.Operator->currentIndex()==3)
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit2->text());
            action.arg.push_back(QString::number(combox1->currentIndex()));
        }
        else
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        }
//        QLabel *tip1=new QLabel(tr("MaskSize:"));
//        QLineEdit *edit1=new QLineEdit(tr("3"));
//        layout.addWidget(tip1,1,0,1,1);
//        layout.addWidget(edit1,1,1,1,2);
//        layout.addWidget(savebutton,2,1,1,1);
//        layout.addWidget(cancelbutton,2,2,1,1);
//        setting_dialog->setLayout(&layout);
//        if (setting_dialog->exec() == QDialog::Rejected)
//            return false;
//        if(action.arg.empty())
//        {
//            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
//            action.arg.push_back(edit1->text());
//        }
        break;
    }
    case 12:
    {
        QLabel *tip1=new QLabel(tr("Processing Mode:"));
        QLabel *tip2=new QLabel(tr("Coefficient:"));
        QLineEdit *edit1=new QLineEdit(tr("1"));
        QLabel *tip3=new QLabel("彩色模式：");
        QComboBox *combox3=new QComboBox();
        combox3->addItem("COLORMAP_AUTUMN");
        combox3->addItem("COLORMAP_BONE");
        combox3->addItem("COLORMAP_JET");
        combox3->addItem("COLORMAP_WINTER");
        combox3->addItem("COLORMAP_RAINBOW");
        combox3->addItem("COLORMAP_OCEAN");
        combox3->addItem("COLORMAP_SUMMER");
        combox3->addItem("COLORMAP_SPRING");
        combox3->addItem("COLORMAP_COOL");
        combox3->addItem("COLORMAP_HSV");
        combox3->addItem("COLORMAP_PINK");
        combox3->addItem("COLORMAP_HOT");
        layout.Enhance->addItem("直方图均衡化");
        layout.Enhance->addItem("Log");
        layout.Enhance->addItem("Gamma");
        layout.Enhance->addItem("直方图拉伸");
        layout.Enhance->addItem("LUT");
        layout.Enhance->addItem("取反");
        layout.Enhance->addItem("彩色转灰度");
        layout.Enhance->addItem("伪彩色");
        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(layout.Enhance,1,1,1,2);
        layout.addWidget(tip2,2,0,1,1);
        layout.addWidget(edit1,2,1,1,2);

        layout.addWidget(tip3,3,0,1,1);
        layout.addWidget(combox3,3,1,1,2);
        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);
        setting_dialog->setLayout(&layout);
        layout.itemAt(6)->widget()->hide();
        layout.itemAt(7)->widget()->hide();

        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        if(action.arg.empty())
        {
            action.mode=layout.Enhance->currentIndex();
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            if(action.mode<=2&&action.mode!=0)
            {
                action.arg.push_back(edit1->text());
            }
            else if(action.mode==7)
            {
                action.arg.push_back(QString::number(layout.Enhance->currentIndex()));
            }
        }
//        QLabel *tip0=new QLabel();
//        QComboBox *combox1=new QComboBox();
//        combox1->addItem("BORDER_CONSTANT");
//        combox1->addItem("BORDER_REFLECT");
//        combox1->addItem("BORDER_REFLECT101");
//        combox1->addItem("BORDER_WRAP");
//        combox1->addItem("BORDER_DEFAULT");
//        combox1->addItem("BORDER_TRANSPARENT");
//        QLabel *tip1=new QLabel();
//        QLabel *tip2=new QLabel();
//        QLabel *tip3=new QLabel();
//        QLabel *tip4=new QLabel();
//        QLabel *tip5=new QLabel();
//        QLineEdit *edit1=new QLineEdit(tr("3"));
//        QLineEdit *edit2=new QLineEdit(tr("1"));
//        QLineEdit *edit3=new QLineEdit(tr("50"));
//        QLineEdit *edit4=new QLineEdit(tr("120"));
//        tip0->setText(tr("Operator:"));
//        tip1->setText(tr("Kernel Size："));
//        tip2->setText(tr("Scale："));
//        tip3->setText(tr("threshold1："));
//        tip4->setText(tr("threshold2："));
//        tip5->setText(tr("BorderMode："));
//        layout.addWidget(tip0,1,0,1,1);
//        layout.addWidget(layout.Operator,1,1,1,2);
//        layout.addWidget(tip5,2,0,1,1);
//        layout.addWidget(combox1,2,1,1,2);
//        layout.addWidget(tip1,3,0,1,1);
//        layout.addWidget(edit1,3,1,1,2);
//        layout.addWidget(tip2,4,0,1,1);
//        layout.addWidget(edit2,4,1,1,2);
//        layout.addWidget(tip3,5,0,1,1);
//        layout.addWidget(edit3,5,1,1,2);
//        layout.addWidget(tip4,6,0,1,1);
//        layout.addWidget(edit4,6,1,1,2);
//        layout.addWidget(savebutton,7,1,1,1);
//        layout.addWidget(cancelbutton,7,2,1,1);
//        setting_dialog->setLayout(&layout);
//        layout.itemAt(4)->widget()->hide();
//        layout.itemAt(5)->widget()->hide();
//        layout.itemAt(8)->widget()->hide();
//        layout.itemAt(9)->widget()->hide();
//        layout.itemAt(10)->widget()->hide();
//        layout.itemAt(11)->widget()->hide();
//        layout.itemAt(12)->widget()->hide();
//        layout.itemAt(13)->widget()->hide();

//        if (setting_dialog->exec() == QDialog::Rejected)
//            return false;
//        action.mode=layout.Operator->currentIndex();
        break;
    }
    case 13:
    {
        QLabel *tip=new QLabel("内核大小");
        QLineEdit *edit=new QLineEdit("32");
        layout.addWidget(tip,1,0,1,1);
        layout.addWidget(edit,1,1,1,1);
        layout.addWidget(savebutton,2,1,1,1);
        layout.addWidget(cancelbutton,2,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        if(action.arg.empty())
        {
            action.mode=0;
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit->text());
        }
        break;
    }
    case 14:
    {
        QLabel *tip1=new QLabel(tr("Processing Mode:"));
        QLabel *tip2=new QLabel(tr("Kernel Width:"));
        QLabel *tip3=new QLabel(tr("Kernel Height:"));
        QLabel *tip4=new QLabel(tr("MORPH Shape:"));
        QComboBox *combo2=new QComboBox();
        layout.Morphology->addItem("腐蚀");
        layout.Morphology->addItem("膨胀");
        layout.Morphology->addItem("开运算");
        layout.Morphology->addItem("闭运算");
        layout.Morphology->addItem("顶帽");
        layout.Morphology->addItem("底帽");
        layout.Morphology->addItem("梯度");
        combo2->addItem("MORPH_RECT");
        combo2->addItem("MORPH_CROSS");
        combo2->addItem("MORPH_ELLIPSE");
        QLineEdit *edit1=new QLineEdit(tr("3"));
        QLineEdit *edit2=new QLineEdit(tr("3"));

        layout.addWidget(tip1,1,0,1,1);
        layout.addWidget(layout.Morphology,1,1,1,2);
        layout.addWidget(tip4,2,0,1,1);
        layout.addWidget(combo2,2,1,1,2);
        layout.addWidget(tip2,3,0,1,1);
        layout.addWidget(edit1,3,1,1,2);
        layout.addWidget(tip3,4,0,1,1);
        layout.addWidget(edit2,4,1,1,2);


        layout.addWidget(savebutton,5,1,1,1);
        layout.addWidget(cancelbutton,5,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        if(action.arg.empty())
        {
            action.mode=layout.Morphology->currentIndex();
            if(action.mode>2)
                action.mode=2;
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            if(action.mode<=1)
            {
                action.arg.push_back(edit1->text());
                action.arg.push_back(edit2->text());
                action.arg.push_back(QString::number(combo2->currentIndex()));
            }
            else
            {
                action.arg.push_back(edit1->text());
                action.arg.push_back(edit2->text());
                action.arg.push_back(QString::number(layout.Morphology->currentIndex()-2));
            }
        }
        break;
    }
    case 15:
    {
        QLabel *tip0 = new QLabel();
        QLabel *tip1 = new QLabel();
        QLabel *tip2 = new QLabel();
        QLineEdit *edit0 = new QLineEdit();
        QLineEdit *edit1 = new QLineEdit();
        QComboBox *combox0 = new QComboBox();

        if(action.arg.empty())
        {
            edit0->setText("0");
            edit1->setText(tr("255"));
        }
        else
        {
            edit0->setText(action.arg[1]);
            edit1->setText(action.arg[2]);
            combox0->setCurrentText(action.name);
        }
        tip0->setText(tr("门限值(0~255)："));
        tip1->setText(tr("最大值(0~255)："));
        tip2->setText(tr("二值化方法："));
        combox0->addItem("THRESH_BINARY");
        combox0->addItem("THRESH_BINARY_INV");
        combox0->addItem("THRESH_TRUNC");
        combox0->addItem("THRESH_TOZERO");
        combox0->addItem("THRESH_TOZERO_INV");
        combox0->addItem("THRESH_MASK");   //7
        combox0->addItem("THRESH_OTSU");   //8
        combox0->addItem("THRESH_TRIANGLE"); //16
        layout.addWidget(tip0,1,0,1,1);
        layout.addWidget(edit0,1,1,1,2);
        layout.addWidget(tip1,2,0,1,1);
        layout.addWidget(edit1,2,1,1,2);
        layout.addWidget(tip2,3,0,1,1);
        layout.addWidget(combox0,3,1,1,2);
        layout.addWidget(savebutton,4,1,1,1);
        layout.addWidget(cancelbutton,4,2,1,1);

        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
            action.arg.push_back(edit0->text());
            action.arg.push_back(edit1->text());
            if(combox0->currentIndex()<=4)
                action.arg.push_back(QString::number(combox0->currentIndex()));
            else if(combox0->currentIndex()<=6)
                action.arg.push_back(QString::number(combox0->currentIndex()+2));
            else
                action.arg.push_back(QString::number(16));
        }
//        QComboBox *combox0 = new QComboBox();
//        QComboBox *combox1 = new QComboBox();
//        QLabel *tip0 = new QLabel();
//        QLabel *tip1 = new QLabel();
//        combox0->addItem("RETR_EXTERNAL");
//        combox0->addItem("RETR_LIST");
//        combox0->addItem("RETR_CCOMP");
//        combox0->addItem("RETR_TREE");
//        combox0->addItem("RETR_FLOODFILL");
//        combox1->addItem("CHAIN_APPROX_NONE");
//        combox1->addItem("CHAIN_APPROX_SIMPLE");
//        combox1->addItem("CHAIN_APPROX_TC89_L1");
//        combox1->addItem("CHAIN_APPROX_TC89_KCOS");
//        tip0->setText(tr("检测方式:"));
//        tip1->setText(tr("链接方式:"));
//        layout.addWidget(tip0,1,0,1,1);
//        layout.addWidget(combox0,1,1,1,2);
//        layout.addWidget(tip1,2,0,1,1);
//        layout.addWidget(combox1,2,1,1,2);
//        layout.addWidget(savebutton,3,1,1,1);
//        layout.addWidget(cancelbutton,3,2,1,1);
//        setting_dialog->setLayout(&layout);
//        if (setting_dialog->exec() == QDialog::Rejected)
//            return false;
//        action.mode=0;
//        if(action.arg.empty())
//        {
//            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
//            action.arg.push_back(QString::number(combox0->currentIndex()));
//            action.arg.push_back(QString::number(combox1->currentIndex()));
//        }
        break;
    }
    case 16:
    {
        layout.addWidget(savebutton,1,1,1,1);
        layout.addWidget(cancelbutton,1,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        }
        break;
    }
    case 17:
    {
        QComboBox *combox=new QComboBox();
        combox->addItem("水平投影");
        combox->addItem("垂直投影");
        QLabel *tip=new QLabel("投影模式：");
        layout.addWidget(tip,1,0,1,1);
        layout.addWidget(combox,1,1,1,1);
        layout.addWidget(savebutton,2,1,1,1);
        layout.addWidget(cancelbutton,2,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        action.mode=combox->currentIndex();
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        }
        break;
    }
    case 18:
    {
        layout.addWidget(savebutton,1,1,1,1);
        layout.addWidget(cancelbutton,1,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        action.mode=0;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        }
        break;
    }
    case 19:
    {
        layout.addWidget(savebutton,1,1,1,1);
        layout.addWidget(cancelbutton,1,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        }
        break;
    }
    case 20:
    {
        layout.addWidget(savebutton,1,1,1,1);
        layout.addWidget(cancelbutton,1,2,1,1);
        setting_dialog->setLayout(&layout);
        if (setting_dialog->exec() == QDialog::Rejected)
            return false;
        if(action.arg.empty())
        {
            action.arg.push_back(QString::number(layout.imglist->currentIndex()));
        }
        break;
    }
    default:
        break;
    }

    return true;
}

//开始执行流程
void MainWindow::startProcess()
{
    if (processWindow)
    {
        CoreModule.processCVActions(0,CoreModule.getNumberOfCVActions()-1);
        pSBar->showMessage(tr("执行中..."));
        //待执行流程的信号与槽建立后再启用
        //pProcessDock->setEnabled(false);
    }
    else
    {
        QMessageBox::warning(this,tr("当前没有流程"),tr("请先新建一个流程"),QMessageBox::Yes);
    }
}

void MainWindow::endProcess()
{
    qDebug()<<"Enter EndProcess";
    ShowImage(CoreModule.getResult(CoreModule.getNumberOfResults()-1));
    //Mat tmp = Mat(CoreModule.getResult(CoreModule.getNumberOfResults()-1));
    //imshow("test",tmp);
    //waitKey(0);
    //pSBar->showMessage(tr("执行完成"));
    //pProcessDock->setEnabled(true);
}

void MainWindow::stopProcess()
{
    QMessageBox::warning(this,tr("出错了"),tr("执行流程的过程中出错了，请检查你的流程设置。"),QMessageBox::Yes);
}

void MainWindow::ShowImage(Mat Image)
{
    QImage imgshow;
    //有bug：颜色通道转换有问题   //已修复by：Markfound
    switch ( Image.type() )
        {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
        imgshow = QImage (Image.data,
                          Image.cols, Image.rows,
                          static_cast<int>(Image.step),
                          QImage::Format_ARGB32 );
        break;
        }

        // 8-bit, 3 channel
        case CV_8UC3:
        {
        imgshow = QImage (Image.data,
                          Image.cols, Image.rows,
                          static_cast<int>(Image.step),
                          QImage::Format_RGB888 );

        imgshow = imgshow.rgbSwapped();
        break;
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
        imgshow =  QImage (Image.data,
                           Image.cols, Image.rows,
                           static_cast<int>(Image.step),
                           QImage::Format_Grayscale8 );
        break;
          //Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5
        }
        default:
        {
            Image.convertTo(Image,CV_8U,255);
            switch ( Image.type() )
                {
                // 8-bit, 4 channel
                case CV_8UC4:
                {
                imgshow = QImage (Image.data,
                                  Image.cols, Image.rows,
                                  static_cast<int>(Image.step),
                                  QImage::Format_ARGB32 );
                break;
                }

                // 8-bit, 3 channel
                case CV_8UC3:
                {
                imgshow = QImage (Image.data,
                                  Image.cols, Image.rows,
                                  static_cast<int>(Image.step),
                                  QImage::Format_RGB888 );

                imgshow = imgshow.rgbSwapped();
                break;
                }

                // 8-bit, 1 channel
                case CV_8UC1:
                {
                imgshow =  QImage (Image.data,
                                   Image.cols, Image.rows,
                                   static_cast<int>(Image.step),
                                   QImage::Format_Grayscale8 );
                break;
                }
                break;
            }
            break;
        }
        break;
        }

    Img_label->setPixmap(QPixmap::fromImage(imgshow));
}
void MainWindow::Generate_Code()
{
    if(!processWindow)
    {
        QMessageBox::warning(this,tr("当前没有流程"),tr("没有找到可用流程"),QMessageBox::Yes);
        return;
    }
    else
    {
        CoreModule.creat_cpp();
        QMessageBox::warning(this,tr("保存"),tr("生成cpp成功"),QMessageBox::Yes);
    }
}

void MainWindow::openProcess()
{
    bool isContinue = true;
    if (processWindow && !isSave)
    {
         QMessageBox::StandardButton reply =
                 QMessageBox::question(this,tr("保存"),tr("是否保存当前流程数据"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
         if (reply == QMessageBox::Yes)
         {
             saveProcess();
         }
         if (reply == QMessageBox::Cancel)
         {
             isContinue = false;
         }
    }
    if (isContinue)
    {
        ResetStatus();
        QString openpath = QFileDialog::getOpenFileName(nullptr,
                                                        tr("打开流程"),
                                                        QDir::currentPath(),
                                                        tr("*.cvp"));
        if (openpath == "") return;
        QFile file(openpath);
        file.open(QFile::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list=line.split(',');
//            QString str0 = line.section(',',0,0);
//            QString str1 = line.section(',',1,1);
            unsigned int type_id = list[0].toUInt();
            CVAction ac(type_id,list[1]);
            if (CVActionCount.size()  <  type_id + 1)
                CVActionCount.resize(type_id + 1,0);
            CVActionCount[type_id]++;
            for (int i = 2; i < list.size() ; i++)   //Markfound
            {
                if (list[i] == "") break;
                ac.arg.push_back(list[i]);
            }
            CoreModule.addCVActions(ac);
            lProList.append(ac.name);
        }
        pSLModel->setStringList(lProList);
        pProcessDock->setVisible(true);
        processWindow = true;
        isSave = true;
        sLocalFileName = openpath;
        pProcessDock->setWindowTitle(QString(tr("流程 - ")) + sLocalFileName);
        startProcess();
    }
}

void MainWindow::newProcess()
{
    if (processWindow && !isSave)   //是否已经又一个流程在运行，并且该流程没有保存
    {
         QMessageBox::StandardButton reply =
                 QMessageBox::question(this,tr("保存"),tr("是否保存当前流程数据"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
         if (reply == QMessageBox::Yes)
         {
             saveProcess();
             processWindow = false;
             newProcess();
         }
         if (reply == QMessageBox::No)
         {
             processWindow = false;
             newProcess();
         }
    }
    else
    {
        //新建流程
        ResetStatus();
        processWindow = true;
        pProcessDock->setVisible(true);
        pSLModel->setStringList(lProList);
        pSBar->showMessage("执行完成");
    }
}

void MainWindow::saveProcess()
{
    QString savepath = QFileDialog::getSaveFileName(nullptr,tr("保存流程"),
                                                QDir::currentPath(),
                                                tr("*.cvp"));
    if (savepath == "") return;
    QFile file(savepath);

    file.open(QFile::WriteOnly | QIODevice::Truncate);
    QTextStream textStream(&file);
    unsigned long total = CoreModule.getNumberOfCVActions();
    for (unsigned long i = 0; i < total; i++)
    {
        CVAction tem = CoreModule.getCVAction(i);
        textStream<<tem.type_id<<','<<tem.name;
        for(unsigned int j=0;j<tem.arg.size();j++)
        {
            textStream<<','<<tem.arg[j];
        }
//        textStream << t.type_id <<","<<t.name<<","<<
//                      t.arg0<<","<<t.arg1<<","<<t.arg2<<","<<t.arg3<<","<<t.arg4<<","<<t.arg5<<","<<t.arg6<<","<<t.arg7<<","<<t.arg8<<","<<t.arg9;
//        if (i != total - 1) textStream<<"\n";
        textStream<<'\n';
     }
    file.close();
    isSave = true;
    sLocalFileName = savepath;
    pProcessDock->setWindowTitle(QString("流程 - ") + sLocalFileName);
}


void MainWindow::closeProcess()
{
    if (processWindow && !isSave)
    {
         QMessageBox::StandardButton reply =
                 QMessageBox::question(this,tr("保存"),tr("是否保存当前流程数据"),QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
         if (reply == QMessageBox::Yes)
         {
             saveProcess();
             processWindow = false;
             closeProcess();
         }
         else if (reply == QMessageBox::No)
         {
             processWindow = false;
             closeProcess();
         }
    }
    else
    {
        ResetStatus();
        pProcessDock->setVisible(false);
    }
}

void MainWindow::showContextMenu(const QPoint&)
{
    if (!mActionsView->selectionModel()->selection().empty())
    {
        ActionView_id = mActionsView->selectionModel()->currentIndex().row();
        QMenu *cMenu = new QMenu(mActionsView);
        QAction *pUpAction = cMenu->addAction(tr("上移"));
        QAction *pDownAction = cMenu->addAction(tr("下移"));
        QAction *pDeleteAction = cMenu->addAction(tr("删除"));
        QAction *pPropertyAction = cMenu->addAction(tr("属性"));

        connect(pUpAction,&QAction::triggered,this,&MainWindow::UpperCVAction);
        connect(pDownAction,&QAction::triggered,this,&MainWindow::DownerCVAction);
        connect(pDeleteAction,&QAction::triggered,this,&MainWindow::DeleteCVAction);
        connect(pPropertyAction,&QAction::triggered,this,&MainWindow::SetProCVAction);
        cMenu->exec(QCursor::pos());
        //有bug，显示不一定对应的选项
        if (CoreModule.getNumberOfResults()>ActionView_id)
            ShowImage(CoreModule.getResult(ActionView_id));
    }
}

void MainWindow::UpperCVAction()
{
    if (ActionView_id > 0 && CoreModule.getNumberOfCVActions() > ActionView_id)
    {
        CoreModule.swapCVActions(ActionView_id,ActionView_id-1);
        lProList.swap(ActionView_id,ActionView_id-1);
        pSLModel->setStringList(lProList);
        CoreModule.processCVActions(ActionView_id-1,ActionView_id);
    }
}

void MainWindow::DownerCVAction()
{
    if (ActionView_id < CoreModule.getNumberOfCVActions() -1)
    {
        CoreModule.swapCVActions(ActionView_id,ActionView_id+1);
        lProList.swap(ActionView_id,ActionView_id+1);
        pSLModel->setStringList(lProList);
        CoreModule.processCVActions(ActionView_id,ActionView_id+1);
    }
}

void MainWindow::DeleteCVAction()
{
    //有bug，并不能真正减减（彩色转灰）
    CoreModule.deleteCVAction(ActionView_id);
    --CVActionCount[ActionView_id];
    lProList.erase(lProList.begin()+ActionView_id);
    pSLModel->setStringList(lProList);
    CoreModule.processCVActions(ActionView_id,CoreModule.getNumberOfCVActions()-1);
}

void MainWindow::SetProCVAction()
{
    action=CoreModule.getCVAction(ActionView_id);
    if (SetArgs())
        CoreModule.processCVActions(ActionView_id,CoreModule.getNumberOfCVActions() - 1);
    //优化项：此处修改之后centralwidge应该显示当前项修改之后得结果而不应该显示最后的结果
}

void MainWindow::clickAction(const QModelIndex &Index)
{
    int nth = Index.row();
    if (CoreModule.getNumberOfResults()>nth)
        ShowImage(CoreModule.getResult(nth));
}

void MainWindow::ResetStatus()
{
    //标志位重置
    isSave = false;
    sLocalFileName = tr("未命名.cvp");
    pProcessDock->setWindowTitle(QString(tr("流程 - ")) + sLocalFileName + QString("*"));
    CoreModule.clearCVActions();
    processWindow = false;
    lProList.clear();
    CVActionCount.clear();

    GlobalFlag = -1;
    GlobalPath = "";
    GlobalEdit1->setEnabled(true);
    GlobalEdit1->setText("");
    Img_label->clear();
}

//把流程项添加进去
void MainWindow::addProcess(const QModelIndex &Index)
{
    if (processWindow && Index.parent().column() != -1 && Index.parent().row() != -1)
    {
        unsigned int type_id =aNumberofChildren[Index.parent().row()] + Index.row();
        if(CoreModule.getNumberOfResults()==0&&type_id!=0)
        {
            QMessageBox::warning(this,tr("当前没有图片"),tr("请先采集一个图片"),QMessageBox::Yes);
            return;
        }
        if ((unsigned int)CVActionCount.size() <  type_id + 1)
            CVActionCount.resize(type_id + 1,0);
        CVActionCount[type_id]++;
        QString action_name = Index.data().toString() + QString::number(CVActionCount[type_id]);
        action = CVAction(type_id,action_name);
        bool isSetArgSuccess = SetArgs();
        if (isSetArgSuccess == false)
            CVActionCount[type_id]--;
        if (isSetArgSuccess)
        {
            CoreModule.addCVActions(action);
            int id = CoreModule.getNumberOfCVActions()-1;
            CoreModule.processCVActions(id,id);
            lProList.append(action_name);
            pSLModel->setStringList(lProList);
            isSave = false;
            pProcessDock->setWindowTitle(QString(tr("流程 - ")) + sLocalFileName + QString("*"));
        }


    }
    else if (Index.parent().column() != -1 && Index.parent().row() != -1 )
    {
        QMessageBox::warning(this,tr("当前没有流程"),tr("请先新建一个流程"),QMessageBox::Yes);
    }

}

void MainWindow::gGetFilePath()
{
    switch (GlobalFlag) {
    case 0:
    {
        GlobalPath = QFileDialog::getOpenFileName(this,QDir::currentPath(),".", tr("Images (*.jpg *.jpeg *.tif *.bmp *.png)"));
        GlobalEdit1->setText(GlobalPath);
        break;
    }
    case 1:
    {
        GlobalPath = QFileDialog::getSaveFileName(this,QDir::currentPath(),".", tr("*.jpg;;*.png;;*.tif;;*.bmp"));
        GlobalEdit1->setText(GlobalPath);
        break;
    }
    default:
        break;
    }

}






MainWindow::~MainWindow()
{
    delete ui;
}
