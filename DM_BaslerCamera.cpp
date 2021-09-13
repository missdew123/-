#include "DM_BaslerCamera.h"
//#include <QDateTime>
#include <QDebug>
//#include <iostream>


cv::Mat g_baslerCameraImage;


void DM_ImageEventHandler::OnImageGrabbed(CInstantCamera &camera, const CGrabResultPtr &ptrGrabResult)
{
    if(ptrGrabResult->GrabSucceeded())//如果抓图成功
    {
//        QImage image = QImage((unsigned char*)ptrGrabResult->GetBuffer(),
//                       ptrGrabResult->GetWidth(),
//                       ptrGrabResult->GetHeight(),
//                       QImage::Format_Grayscale8);
//        emit currentImage(image);

//       g_baslerCameraImage = QImage((unsigned char*)ptrGrabResult->GetBuffer(),
//                               ptrGrabResult->GetWidth(),
//                               ptrGrabResult->GetHeight(),
//                               QImage::Format_Grayscale8);
       g_baslerCameraImage = cv::Mat( ptrGrabResult->GetHeight(),
                                      ptrGrabResult->GetWidth(),
                                      CV_8UC1,
                                     (unsigned char*)ptrGrabResult->GetBuffer());
       emit currentImage();
    }
}


DM_BaslerCamera::DM_BaslerCamera(QObject *parent) : QObject(parent)
{
    this->maxExpourseTime = 999999;//最大曝光时间
    this->minExpourseTime = 1;//最小宝曝光时间
    cameraHandler = new DM_ImageEventHandler;//新建回调函数类

    this->message =   "@>>> 相机连接状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
    this->errorID = DM_error_no;//没有报错

}

DM_BaslerCamera::~DM_BaslerCamera()
{
    if (camera.IsGrabbing())
    {
        camera.StopGrabbing();
    }
    if(camera.IsOpen())
    {
        camera.DetachDevice();
        camera.Close();
        camera.DeregisterImageEventHandler(cameraHandler);
    }
    else
    {
        delete this->cameraHandler;
    }
    PylonTerminate();
}

void DM_BaslerCamera::initCamera()
{
    try
    {
        PylonInitialize();//相机相关基类初始化
        //判定一下是否连接了相机
        CTlFactory& TLFactory = CTlFactory::GetInstance();
        ITransportLayer * pTl = TLFactory.CreateTl("BaslerGigE");
        DeviceInfoList_t devices;
        int num = pTl->EnumerateDevices(devices);

        if(num < 1)//没有连接相机，则不进行后面的操作
        {
            qDebug() << "Cannot find Any camera!";
        }
        else
        {
            camera.Attach(CTlFactory::GetInstance().CreateFirstDevice());//启动相机驱动
            camera.Open();
            if(camera.IsOpen())
            {
                camera.RegisterImageEventHandler(cameraHandler , RegistrationMode_Append, Cleanup_Delete); //注册回调函数
                camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
                this->SetCameraParameter(DM_Camera_ContinuousAcquisition);//获取触发模式//必须先打开相机才能设置抓取模式
            }
        }
    }
    catch (GenICam::GenericException &e)
    {
        qDebug() << "OpenCamera Error" << QString(e.GetDescription());
    }
}

void DM_BaslerCamera::reConnectCamera()
{
    try
    {
        this->releaseCameraResource();

        PylonInitialize();//相机相关基类初始化
        //判定一下是否连接了相机
        CTlFactory& TLFactory = CTlFactory::GetInstance();
        ITransportLayer * pTl = TLFactory.CreateTl("BaslerGigE");
        DeviceInfoList_t devices;
        int num = pTl->EnumerateDevices(devices);

        if(num < 1)//没有连接相机，则不进行后面的操作
        {
            qDebug() << "Cannot find Any camera!";
        }
        else
        {
            camera.Attach(CTlFactory::GetInstance().CreateFirstDevice());//启动相机驱动
            camera.Open();
            if(camera.IsOpen())
            {
                camera.RegisterImageEventHandler(cameraHandler , RegistrationMode_Append, Cleanup_Delete); //注册回调函数
                camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
                this->SetCameraParameter(DM_Camera_ContinuousAcquisition);//获取触发模式//必须先打开相机才能设置抓取模式
            }
        }
    }
    catch (GenICam::GenericException &e)
    {
        qDebug() << "OpenCamera Error" << QString(e.GetDescription());
    }
}

//bool DM_BaslerCamera::getTriggerMode()
//{
//    INodeMap &cameraNodeMap = camera.GetNodeMap();
//    CEnumerationPtr  ptrTriggerSel = cameraNodeMap.GetNode ("TriggerSelector");
//    ptrTriggerSel->FromString("FrameStart");
//    CEnumerationPtr  ptrTrigger  = cameraNodeMap.GetNode ("TriggerMode");
//    return ptrTrigger->GetIntValue() == 1;
//}

//void DM_BaslerCamera::setTriggerMode(bool mode_)
//{
//    INodeMap &cameraNodeMap = camera.GetNodeMap();
//    CEnumerationPtr  ptrTriggerSel = cameraNodeMap.GetNode ("TriggerSelector");
//    ptrTriggerSel->FromString("FrameStart");
//    CEnumerationPtr  ptrTrigger  = cameraNodeMap.GetNode ("TriggerMode");
//    ptrTrigger->SetIntValue(mode_?1:0);
//}
void DM_BaslerCamera::setExposureTime(double time)
{
    if (time > this->maxExpourseTime)
    {
        time = this->maxExpourseTime;
    }
    else if(time < this->minExpourseTime)
    {
        time = this->minExpourseTime;
    }
    this->SetCameraParameter(DM_Camera_ExposureTimeAbs, time);
}

int DM_BaslerCamera::getExposureTime()
{
    return QString::number(this->GetCameraParameter(DM_Camera_ExposureTimeAbs)).toInt();
}

int DM_BaslerCamera::getExposureTimeMin()
{
    return this->maxExpourseTime;
}

int DM_BaslerCamera::getExposureTimeMax()
{
    return this->maxExpourseTime;
}

void DM_BaslerCamera::setTriggerType(DM_BaslerCamera::DM_CameraControlEnum type_)
{
    if(type_ == DM_Camera_Software             ||
       type_ == DM_Camera_Line1                ||
       type_ == DM_Camera_ContinuousAcquisition )
    {
        this->SetCameraParameter(type_);
    }
}

void DM_BaslerCamera::grabImageBySotfware()
{
    if(this->triggerType == DM_Camera_Software &&
       this->camera.IsOpen() &&
       this->camera.IsGrabbing())
    {
        // Execute the software trigger. Wait up to 500 ms for the camera to be ready for trigger.
        if ( this->camera.WaitForFrameTriggerReady( 500, TimeoutHandling_ThrowException))
        {
            this->camera.ExecuteSoftwareTrigger();
        }
    }
}

void DM_BaslerCamera::releaseCameraResource()
{
    if (this->camera.IsGrabbing())
    {
        this->camera.StopGrabbing();
    }
    if(this->camera.IsOpen())
    {
        this->camera.DetachDevice();
        this->camera.Close();
    }
    PylonTerminate();
}


void DM_BaslerCamera::SetCameraParameter(DM_CameraControlEnum index, double tmpValue)
{
    if(!this->camera.IsOpen()) return;//如果相机没有打开，直接返回
    INodeMap &cameraNodeMap = camera.GetNodeMap();
    switch (index)
    {
        case DM_Camera_Software:
        {
            CEnumerationPtr  ptrTriggerSel = cameraNodeMap.GetNode ("TriggerSelector");
            ptrTriggerSel->FromString("FrameStart");
            CEnumerationPtr  ptrTrigger  = cameraNodeMap.GetNode ("TriggerMode");
            ptrTrigger->SetIntValue(1);
            CEnumerationPtr  ptrTriggerSource = cameraNodeMap.GetNode ("TriggerSource");
            ptrTriggerSource->FromString("Software");
            triggerType = DM_Camera_Software;
        }
        break;
        case DM_Camera_Line1:
        {
            CEnumerationPtr  ptrTriggerSel = cameraNodeMap.GetNode ("TriggerSelector");
            ptrTriggerSel->FromString("FrameStart");
            CEnumerationPtr  ptrTrigger  = cameraNodeMap.GetNode ("TriggerMode");
            ptrTrigger->SetIntValue(1);
            CEnumerationPtr  ptrTriggerSource = cameraNodeMap.GetNode ("TriggerSource");
            ptrTriggerSource->FromString("Line1");
            triggerType = DM_Camera_Line1;
        }
        break;

        case DM_Camera_ContinuousAcquisition:
        {
            CEnumerationPtr  ptrTriggerSel = cameraNodeMap.GetNode ("TriggerSelector");
            ptrTriggerSel->FromString("FrameStart");
            CEnumerationPtr  ptrTrigger  = cameraNodeMap.GetNode ("TriggerMode");
            ptrTrigger->SetIntValue(0);
            triggerType = DM_Camera_ContinuousAcquisition;
        }
        break;

        case DM_Camera_ExposureTimeAbs:
        {
            const CFloatPtr exposureTime = cameraNodeMap.GetNode("ExposureTimeAbs");
            exposureTime->SetValue(tmpValue);
        }
        break;
        case DM_Camera_GainRaw:
        {
            const CIntegerPtr cameraGen = cameraNodeMap.GetNode("GainRaw");
            cameraGen->SetValue(tmpValue);
        }
        break;
        case DM_Camera_AcquisitionFrameRateAbs:
        {
            const CBooleanPtr frameRate = cameraNodeMap.GetNode("AcquisitionFrameRateEnable");
            frameRate->SetValue(TRUE);
            const CFloatPtr frameRateABS = cameraNodeMap.GetNode("AcquisitionFrameRateAbs");
            frameRateABS->SetValue(tmpValue);
        }
        break;
        case DM_Camera_Width:
        {
            const CIntegerPtr widthPic = cameraNodeMap.GetNode("Width");
            widthPic->SetValue(tmpValue);
        }
        break;
        case DM_Camera_Height:
        {
            const CIntegerPtr heightPic = cameraNodeMap.GetNode("Height");
            heightPic->SetValue(tmpValue);
        }
        break;
    default:
        break;
    }
}

double DM_BaslerCamera::GetCameraParameter(DM_CameraControlEnum index)
{
    if(!this->camera.IsOpen()) return -1;//如果相机没有打开，直接返回
    INodeMap &cameraNodeMap = camera.GetNodeMap();
    switch (index)
    {
        case DM_Camera_ExposureTimeAbs:
        {
            const CFloatPtr exposureTime = cameraNodeMap.GetNode("ExposureTimeAbs");
            return exposureTime->GetValue();
        }
        break;
        case DM_Camera_GainRaw:
        {
            const CIntegerPtr cameraGen = cameraNodeMap.GetNode("GainRaw");
            return cameraGen->GetValue();
        }
        break;
        case DM_Camera_AcquisitionFrameRateAbs:
        {
            const CBooleanPtr frameRate = cameraNodeMap.GetNode("AcquisitionFrameRateEnable");
            frameRate->SetValue(TRUE);
            //const CFloatPtr frameRateABS = cameraNodeMap.GetNode("AcquisitionFrameRateAbs");
            const CFloatPtr frameRateABS = cameraNodeMap.GetNode("ResultingFrameRateAbs");
            return frameRateABS->GetValue();
        }
        break;
        case DM_Camera_Width:
        {
            const CIntegerPtr widthPic = cameraNodeMap.GetNode("Width");
            return widthPic->GetValue();
        }
        break;
        case DM_Camera_Height:
        {
            const CIntegerPtr heightPic = cameraNodeMap.GetNode("Height");
            return heightPic->GetValue();
        }
        break;
        default:
            return -1;
        break;
    }
}



bool DM_BaslerCamera::stopAcquire()
{
     if (this->camera.IsGrabbing())
     {
         this->camera.StopGrabbing();
         return true;
     }
     else
     {
         return false;
     }
}

bool DM_BaslerCamera::startAcquire()
{
    if(camera.IsOpen()&&
       !this->camera.IsGrabbing())
    {
        camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
        return true;
    }
    else
    {
        return false;
    }
}

DM_BaslerCamera::DM_CameraControlEnum DM_BaslerCamera::getTriggerType()
{
    return this->triggerType;
}

void DM_BaslerCamera::setAcquisitionFrameRateAbs(double rateABS)
{
    this->SetCameraParameter(DM_Camera_AcquisitionFrameRateAbs,rateABS);
}

double DM_BaslerCamera::getAcquisitionFrameRateAbs()
{
   return this->GetCameraParameter(DM_Camera_AcquisitionFrameRateAbs);
}




