#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include<QSplashScreen>
#include<QElapsedTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/resources/Screen.jpg");  //创建一个QPixmap对象,设置启动图片
    QSplashScreen splash(pixmap);  //利用QPixmap对象创建一个QSplashScreen对象
    splash.show();  //显示此启动图片
    a.processEvents();  //使程序在显示启动画面的同时仍能响应鼠标其他事件
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<2500)
        QCoreApplication::processEvents();
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
