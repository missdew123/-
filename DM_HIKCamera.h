#ifndef DM_HIKCAMERA_H
#define DM_HIKCAMERA_H
#include <QObject>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "MvCamera.h"

extern cv::Mat g_HIKCameraImage;
void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);//回调函数

class DM_HIKCamera : public QObject
{
    Q_OBJECT
public:
    explicit DM_HIKCamera(QObject *parent = Q_NULLPTR);
    ~DM_HIKCamera();

    enum DM_Camera_ControlEnum
    {
        DM_Camera_Error = -1,//相机传参错误或者获取参数失败
        DM_Camera_Default = 0,//相机默认参数
        DM_Camera_Line1, //设置相机的外触发
        DM_Camera_Software, //设置相机的软触发
        DM_Camera_ContinuousAcquisition, //设置相机的连续触发模式

        DM_Camera_ExposureTimeAbs, //设置相机的曝光时间
        DM_Camera_GainRaw, //设置相机的增益
        DM_Camera_AcquisitionFrameRateAbs, //设置相机的频率

        DM_Camera_Width, //图片的宽度
        DM_Camera_Height, //图片的高度
        DM_Camera_BinningHorizontal,//设置binning
        DM_Camera_BinningVertical,//设置binning

    };
    void initCamera(DM_Camera_ControlEnum triggerSource_ = DM_Camera_ContinuousAcquisition);//初始化相机，并启动相机
    void setExposureTime(double time); // 设置曝光时间
    double getExposureTime(); // 获取曝光时间
    int getExposureTimeMin(); // 最小曝光时间
    int getExposureTimeMax(); // 最大曝光时间

    void setTriggerSource(DM_Camera_ControlEnum type_);//设置出发模式
    DM_Camera_ControlEnum getTriggerSource();//获取出发模式

    void setAcquisitionFrameRateAbs(double rateABS = 1);//设置采集
    double getAcquisitionFrameRateAbs();//获取采集帧率

    void grabImageBySotfware();//通过软件触发采集图像
    bool stopAcquire(); // 结束采集
    bool startAcquire(); //开始采集

    MV_CC_DEVICE_INFO_LIST searchDevices();//查找驱动,返回IP
    MV_CC_DEVICE_INFO_LIST getDevices(){return this->devList;}//获取驱动
    std::string getDeviceIP();//获取驱动的IP

    bool connectDevice(MV_CC_DEVICE_INFO* pstDeviceInfo);//连接驱动
    void disConnectDevice();//断开连接驱动
    bool isOpen(){return this->isOpenDevice;}

    void setImageWidth(int width_);
    int getImageWidth();
    void setImageHeight(int height_);
    int getImageHeight();
    void setBinningVertical(int binningV_);
    void SetBinningHorizontal(int binningH_);
std::string message;//输出运行信息
private:
    double GetCameraParameter(DM_Camera_ControlEnum index); // 获取各种参数
    void SetCameraParameter(DM_Camera_ControlEnum index, double tmpValue = 0.0); // 设置各种参数
signals:
    void currentImage();
private:

    CMvCamera *camera;
    int maxExpourseTime;//最大曝光时间
    int minExpourseTime;//最小曝光时间
    DM_Camera_ControlEnum triggerSource;// 触发方式：软件触发，外部触发，连续采集

    MV_CC_DEVICE_INFO_LIST  devList;//驱动列表
//    MV_FRAME_OUT            pFrame;
    bool                    isOpenDevice;   // ch:是否打开设备
    bool                    isStartGrabbing;// ch:是否开始抓图

};

#endif // DM_HIKCAMERA_H
