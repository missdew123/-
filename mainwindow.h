#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <string>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QString>
#include <QLabel>
#include <QSettings>
#include <QMetaType>
#include <QTimer>
#include "DM_ImageAlgorithm.h"
#include "DM_Element.h"
#include "DM_Modbus.h"
#include "DM_BaslerCamera.h"
#include "DM_Dialog.h"
#include "DM_HIKCamera.h"
#include "DM_Slider.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    enum SystemFunctionType
    {
        SystemFunction_camera = 1,//系统当前处在相机设置功能
        SystemFunction_Calibrate,//系统当前处在标定功能
        SystemFunction_Algorithm,//系统当前处在算法配置功能
        SystemFunction_communication //系统当前处在通讯设置
    };
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    //void on_algorithmType_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void loadImage();//加载图片
    void loadImage_Projector(const QString& filePath);//通过胶片加载图片
    void newProject();//新建工程[将所有的算法全部初始化]
    void saveProject();//保存工程
//    void saveAsProject();//工程另存为
    void loadProject();//加载工程

    void saveAlgorithms(std::vector<DM_ImageProcessBase *> imgAlgorithm, QString algorithmPath_);//保存算法
    std::vector<DM_ImageProcessBase *> loadAlgorithms(QString algorithmPath_);//加载算法

    void loadCalibrateParameters(QString filePath_);//加载标定参数
    void loadLocationAlgorithms(QString filePath_);//加载定位算法

    void initCommunicationParameters();//初始化通讯参数
    void saveCommunicationParameters(QString filePath_);//保存通讯的设置参数
    void loadCommunicationParameters(QString filePath_);//加载通讯的设置参数

    void connectBaslerCameraParameters();//初始化basler相机相关参数【系统默认值】
    void connectHIKCameraParameters();//初始化HIK相机先关参数
    void connectCameraParameters();//初始化此昂及参数
    void saveCameraParameters(QString filePath_);//保存相机的设置参数
    void loadCameraParameters(QString filePath_);//加载相机的设置参数

    void saveDefaultFiles();//保存默认文件[系统参数设置文件、标定文件、算法文件]路径
    void loadDefaultFiles();//加载默认文件

    void calibrateFindFeature();//查找标定板的特征点
	void calibrateFindFeature_chessboard();//从棋盘格查找特征点
	void calibrateFindFeature_circle();//圆形棋盘格查找特征点
	void calibrateFindFeatrue_circle_hand();//手动框选圆环自动拟合查找特征点
    void calibrateConfirm();//标定
   

    // void on_calibratePlateType_currentIndexChanged(const QString &arg1);
    void on_btn_addTemp_clicked();//添加模板
    //void on_tempMassCenter_PB_clicked();//将模板的抓取中心设置成质心，否则抓取中心为模板的中心
    void receiveLocationLabelElement(DM_Element *elem);//模板区域；
    void receiveCalibrateElement(DM_Element *elem);//获取标定区域

    //获取相机传回的图片
    void getImageFromeCamera();
    void on_cameraExposureSlider_valueChanged(int value);
    void on_cameraFrameRate_valueChanged(double arg1);
    void on_camareTriggerType_activated(const QString &arg1);
    //void on_saveCameraImagePathPushButton_clicked();

    void cameraImage_cameraStart();//相机开始采集
    void cameraImage_cameraStop();//相机停止采集
    void cameraImage_zoomIn();//相机Label放大
    void cameraImage_zoomOut();//相机Label缩小
    void cameraImage_fitScreen();//相机Label适屏
    void cameraImage_takePicture();//相机采集图片

    void moudbusReadAndWrite();//启动定时器,进行读操作
    void on_btn_modbusConnect_clicked();
    void on_btn_modbusTest_clicked();
    void on_btn_modbusclose_R_clicked(bool checked);
    void on_TWidget_toolList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);//工具列表
    void on_btn_toolConfirm_clicked();//确认按钮
    void on_btn_AlgorithmExcute_clicked();//算法执行按钮
	// void on_btn_executeAlgorithm_clicked();//执行算法
	void on_btn_AlgorithmRevocation_clicked(); //撤销算法

    void on_btn_saveCameraImagePath_clicked();//选择相机采集图片的保存路径

    void on_btn_connectCamera_clicked();//连接相机

private:
    void loadImage(cv::Mat img_);//加载图片
    void connectModbus();//初始化moudbus
    void sendPosByModbus();//通过modbus把数据发出

    void initCalibrateCoordinateTable();//初始化标定值列表格式
    void initAlgorithmCoordinateTable();//初始化定位列表格式
    void initPreprocessAlgorithmTable();//初始化算法列表格式
    void initSystemCalibrateTable();//初始化标定算法的执行过程的表格

    void updateCalibrateCoordinateTable();//初始化标定值列表格式（只用于重新加载工程的时候用）
    void updateSystemCalibrateTable();     //更新标定算法的执行过程的表格
	void updateLab_calibrateImage();//更新标定界面的显示
    void updateAlgorithmCoordinateTable(); //更新定位列表
    void updatePreprocessAlgorithmTable(); //更新算法列表

	void deleteImgCalibrateAlgorithm(int index = -1);//撤销标定算法
	void clearImgCalibrateAlgorithm();//清除算法
    void excuteImageProcess();//执行图像处理算法
    //此处注意增加/删除/清空只是针对算法，不对标定项做处理，所以所有的操作对于imgProcess的index而言都是≥1的
    void addImgProcess(DM_ImageProcessBase* func);//增加算法
    void deleteImgProcess(int index = -1);//删除算法，如果index=-1，默认删除最后一项
    void clearImgProcess();//清除算法

protected:
    //重绘区域
    void paintEvent(QPaintEvent *ev);
private:
    Ui::MainWindow *ui;
    QString message;//整个工程运行过程中的输出状态
    std::vector<DM_ImageProcessBase*> imgProcess;//图像算法处理
    std::vector<DM_ImageProcessBase*>  imgCalibrate;//图像标定（①：计算特征点，②：图像标定计算旋转矩阵）
    cv::Mat calibrateImg;//标定图片
    cv::Mat calibrateImg_show;//标定图片

    cv::Mat locationImg;//定位图片【处理之后的图片】
    cv::Mat locationImg_show;//定位图片【显示在label上面的图片】
    cv::Mat locationImg_original;//原始图像【保存传入的原始图片】

    DM_ImgProcess_Tag imgAlgorithmType;//图像算法类别
    DM_ImgProcess_Tag imgCalibrateType;//图像标定类型
    QString currentToolList;//当前工具列表
    bool  calibrateFlag;//标定完成标志
    cv::Mat transformMatrix;//转换矩阵
    DM_Ring calibrateROI;//手动框选ROI区域

    std::vector<cv::Mat> tempImg;//模板
    std::vector<cv::Mat> tempImg_RGB;//模板
    std::vector<cv::Point2f> tempDrapPoints;//模板抓取点（分成质心和中心两种,默认为质心）
    std::vector<std::vector<cv::Point>> tempContours;//返回找到的轮廓
    cv::Rect tempRect;//模板的区域
    bool templateMassCenterFlag;//模板质心Flag

    QString projectPath;//工程路径
    QString projectName;//工程名
    QString projectDefaultFile;//工程默认文件，用于保存最近的各个模板的存放路径，保存在工程根目录下

    SystemFunctionType systemFunc;//系统处理状态（包括：相机设定/标定/定位算法设定/通讯设置）
    QString proStatus[4];//系统关键的几个状态包括：①工程名：②XXX  ③，标定状态： ④未标定

private://=====================moudbus===================
    DM_Modbus Rmodbus;//读_modbus
    DM_Modbus Wmodbus;//写_modbus
    QTimer scaneTimer;
    std::vector<float> RmodbusData;//用于读取moudbus的数据
    //数据编号[0,           1,              (2,3), (4,5)......]
    //数据个数[处理的图像次数,本次抓取的工件个数,Pos1,  POs2.......]
    std::vector<float> WmodbusData;//用于写入modbus的数据

private://============================相机=======================
    DM_BaslerCamera  baslerCamera;//basler相机
    DM_HIKCamera     HIKCamera;//海康相机
    std::string      cameraBrand;//相机品牌
};

#endif // MAINWINDOW_H
