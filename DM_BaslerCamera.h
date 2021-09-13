#ifndef DM_BASLERCAMERA_H
#define DM_BASLERCAMERA_H

#include <QObject>
#include <pylon/PylonIncludes.h>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <opencv2/opencv.hpp>

#include "DM_errorID.h"


//using namespace std;
using namespace Pylon;
using namespace GenApi;

extern cv::Mat g_baslerCameraImage;

//相机句柄类
class DM_ImageEventHandler: public QObject,public CImageEventHandler
{
    Q_OBJECT
public:
    explicit DM_ImageEventHandler(QObject *parent = Q_NULLPTR):QObject(parent){;}
signals:
//    void currentImage(QImage &img);
    void currentImage();
public:
    virtual void OnImageGrabbed( CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult);
};


class DM_BaslerCamera : public QObject
{
    Q_OBJECT
public:
    explicit DM_BaslerCamera(QObject *parent = Q_NULLPTR);
    ~DM_BaslerCamera();

    enum DM_CameraControlEnum
    {
        DM_Camera_Line1, //设置相机的外触发
        DM_Camera_Software, //设置相机的软触发
        DM_Camera_ContinuousAcquisition, //设置相机的连续触发模式

        DM_Camera_ExposureTimeAbs, //设置相机的曝光时间
        DM_Camera_GainRaw, //设置相机的增益
        DM_Camera_AcquisitionFrameRateAbs, //设置相机的频率
        DM_Camera_Width, //图片的宽度
        DM_Camera_Height, //图片的高度
    };
    void initCamera();//初始化相机，并启动相机
    void setExposureTime(double time); // 设置曝光时间
    int getExposureTime(); // 获取曝光时间
    int getExposureTimeMin(); // 最小曝光时间
    int getExposureTimeMax(); // 最大曝光时间

    void setTriggerType(DM_CameraControlEnum type_);//设置出发模式
    DM_CameraControlEnum getTriggerType();//获取出发模式

    void setAcquisitionFrameRateAbs(double rateABS = 1);//设置采集
    double getAcquisitionFrameRateAbs();//获取采集帧率

    void grabImageBySotfware();//通过软件触发采集图像
    bool stopAcquire(); // 结束采集
    bool startAcquire(); //开始采集

    bool isOpen(){return this->camera.IsOpen();}
private:
    void reConnectCamera();//连接相机，连接第一个相机//暂时不完善，慎用
//    bool getTriggerMode();//获取触发模式【一般不用】
//    void setTriggerMode(bool mode_);//设置触发模式【一般不用】
    void releaseCameraResource();//释放相机资源

    double GetCameraParameter(DM_CameraControlEnum index); // 获取各种参数
    void SetCameraParameter(DM_CameraControlEnum index, double tmpValue = 0.0); // 设置各种参数
private:

    CInstantCamera camera;
    int maxExpourseTime;//最大曝光时间
    int minExpourseTime;//最小曝光时间
    DM_CameraControlEnum triggerType;// 触发方式：软件触发，外部触发，连续采集

    std::string message;//输出运行信息
    DM_ErrorID_Tag errorID;
 public:
    DM_ImageEventHandler *cameraHandler;//定义抓图句柄

};

#endif // DM_BaslerCamera_H
