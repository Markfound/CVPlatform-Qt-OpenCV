#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QAction>
#include <QToolBar>
#include <QTreeWidgetItem>
#include <QList>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QStatusBar>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDockWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMenu>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QPixmap>
#include <QFile>
#include "processmodule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool setUITips(QString &s);
public slots:
    void openProcess();
    void newProcess();
    void saveProcess();
    void closeProcess();
    void startProcess();
    void Generate_Code();
    void showContextMenu(const QPoint &point);
    void addProcess(const  QModelIndex &Index);
    void endProcess();
    void stopProcess();
    void gGetFilePath();
    void clickAction(const  QModelIndex &Index);
    void UpperCVAction();
    void DownerCVAction();
    void DeleteCVAction();
    void SetProCVAction();

private:
    Ui::MainWindow *ui;
    bool processWindow = false;
    bool isSave = false;
    QStatusBar *pSBar; //底部状态栏
    QDockWidget *pProcessDock;
    QStringList lProList; //列表
    QStringListModel *pSLModel;  //列表显示
    QListView *mActionsView;
    QTreeWidget *pTree;
    QString sLocalFileName = tr("未命名.cvp");
    QString GlobalPath;
    QLineEdit *GlobalEdit1 = new QLineEdit();
    int GlobalFlag = -1;
    int ActionView_id= -1;

    //central
    QWidget *pCentral;  //副窗口
    QGridLayout *pCETLayout = new QGridLayout();
    QLabel *Img_label = new QLabel();

    bool SetArgs();
    void ResetStatus();   //初始化
    void ShowImage(Mat Image);  //显示图片

    vector<unsigned int> CVActionCount;

};

#endif // MAINWINDOW_H
