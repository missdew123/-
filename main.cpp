#include "mainwindow.h"
#include <QApplication>
//==================工程修改记录=================================

//**********************************************
//版本： v1.5
//时间：20210715
//修改内容：增加海康相机SDK
//**********************************************
int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::Mat>("cv::Mat");//注册自定义类型
    qRegisterMetaType<DM_Element>("DM_Element");//注册自定义类型

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
