#include "DM_HIKCamera.h"
#include <iostream>

cv::Mat g_HIKCameraImage;

void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
    if (pFrameInfo)
    {
        DM_HIKCamera *cameraHandler = (DM_HIKCamera *)pUser;//定义抓图句柄
        switch(pFrameInfo->enPixelType)
        {
            case PixelType_Gvsp_Mono8://黑白图像
            {
                cv::Mat(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1, pData).copyTo(g_HIKCameraImage);
                emit cameraHandler->currentImage();
            }
            break;
            case PixelType_Gvsp_RGB8_Packed://彩色图像
            {
                cv::Mat(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3, pData).copyTo(g_HIKCameraImage);
                cv::cvtColor(g_HIKCameraImage,g_HIKCameraImage,COLOR_RGB2BGR);
                 emit cameraHandler->currentImage();
            }
            break;
            default:
            break;
        }
    }

}

DM_HIKCamera::DM_HIKCamera(QObject *parent) : QObject(parent)
{
    this->maxExpourseTime = 999999;//最大曝光时间
    this->minExpourseTime = 1;//最小宝曝光时间

    this->message =   "@>>> 相机连接状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
    this->triggerSource = DM_Camera_Default;//设置触发源
    this->isOpenDevice = false;   // ch:是否打开设备
    this->isStartGrabbing = false;// ch:是否开始抓图
    this->camera = NULL;

}

DM_HIKCamera::~DM_HIKCamera()
{
    this->camera->StopGrabbing();//停止取流
    this->camera->RegisterImageCallBack(NULL,NULL);//注销回调函数
    this->camera->Close();//关闭设备
    if (NULL != this->camera )//释放内存
    {
       delete this->camera;
       this->camera = NULL;
    }
    this->message += "释放相机资源!\n";
}

void DM_HIKCamera::initCamera(DM_HIKCamera::DM_Camera_ControlEnum triggerSource_)
{
    this->searchDevices();
    if(this->devList.nDeviceNum<1)
    {
        this->message += "查找驱动失败\n";
    }
    else
    {
        this->connectDevice(this->devList.pDeviceInfo[0]);//连接第一台相机
        this->setTriggerSource(triggerSource_);//设置触发源
        int nRet = this->camera->RegisterImageCallBack(ImageCallBackEx,this);//注册回调函数
        if(nRet != MV_OK)
        {
            this->message += "注册回调函数失败!\n";
        }
        else//开始抓取
        {
            this->message += "注册回调函数成功!\n";
            this->startAcquire();
        }
    }

}

void DM_HIKCamera::setExposureTime(double time)
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

double DM_HIKCamera::getExposureTime()
{
    return this->GetCameraParameter(DM_Camera_ExposureTimeAbs);
}



int DM_HIKCamera::getExposureTimeMin()
{
    return this->maxExpourseTime;
}

int DM_HIKCamera::getExposureTimeMax()
{
    return this->maxExpourseTime;
}

DM_HIKCamera::DM_Camera_ControlEnum DM_HIKCamera::getTriggerSource()
{
    return this->triggerSource;
}

void DM_HIKCamera::setTriggerSource(DM_HIKCamera::DM_Camera_ControlEnum type_)
{
    if(type_ == DM_Camera_Software             ||
       type_ == DM_Camera_Line1                ||
       type_ == DM_Camera_ContinuousAcquisition )
    {
        this->SetCameraParameter(type_);
    }
}

void DM_HIKCamera::setAcquisitionFrameRateAbs(double rateABS)
{
    this->SetCameraParameter(DM_Camera_AcquisitionFrameRateAbs,rateABS);
}

double DM_HIKCamera::getAcquisitionFrameRateAbs()
{
   return this->GetCameraParameter(DM_Camera_AcquisitionFrameRateAbs);
}


void DM_HIKCamera::grabImageBySotfware()
{
    if (false == this->isStartGrabbing)
    {
        return;
    }
    else
    {
        this->camera->CommandExecute("TriggerSoftware");
    }
}


double DM_HIKCamera::GetCameraParameter(DM_HIKCamera::DM_Camera_ControlEnum index)
{
    if(!this->camera->IsDeviceConnected()) return -1;//如果相机没有打开，直接返回
    switch (index)
    {
        case DM_Camera_ExposureTimeAbs:
        {
            MVCC_FLOATVALUE stFloatValue = {0};
            int nRet = this->camera->GetFloatValue("ExposureTime", &stFloatValue);
            if (MV_OK != nRet)
            {
                return -1;
            }
            else
            {
                return stFloatValue.fCurValue;
            }

        }
        break;
        case DM_Camera_GainRaw:
        {

            MVCC_FLOATVALUE stFloatValue = {0};

            int nRet = this->camera->GetFloatValue("Gain", &stFloatValue);
            if (MV_OK != nRet)
            {
                return -1;
            }
            else
            {
                return stFloatValue.fCurValue;
            }
        }
        break;
        case DM_Camera_AcquisitionFrameRateAbs:
        {
            MVCC_FLOATVALUE stFloatValue = {0};

            int nRet = this->camera->GetFloatValue("ResultingFrameRate", &stFloatValue);
            if (MV_OK != nRet)
            {
                return -1;
            }
            else
            {
                return stFloatValue.fCurValue;
            }
        }
        break;
        case DM_Camera_Width:
        {
            MVCC_INTVALUE_EX enumValue = {0};
            int nRet = this->camera->GetIntValue("Width", &enumValue);
            if (MV_OK != nRet)
            {
                return -1;
            }
            else
            {
                return enumValue.nCurValue;
            }

        }
        break;
        case DM_Camera_Height:
        {
            MVCC_INTVALUE_EX enumValue = {0};
            int nRet = this->camera->GetIntValue("Height", &enumValue);
            if (MV_OK != nRet)
            {
                return -1;
            }
            else
            {
                return enumValue.nCurValue;
            }
        }
        break;
        default:
            return -1;
        break;
    }
}

void DM_HIKCamera::SetCameraParameter(DM_HIKCamera::DM_Camera_ControlEnum index, double tmpValue)
{
    if(!this->isOpenDevice ||
       !this->camera->IsDeviceConnected())return;//如果相机没有打开，直接返回

    switch (index)
    {
        case DM_Camera_Software:
        {
            this->camera->SetEnumValue("TriggerMode",MV_TRIGGER_MODE_ON);//开启触发模式
            int nRet = MV_OK;
            nRet = this->camera->SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
            if (MV_OK != nRet)
            {
                this->message += "相机软件触发设置失败!\n";
                this->triggerSource = DM_Camera_Default;
            }
            else
            {
                this->message +="相机软件触发设置成功!\n";
                this->triggerSource = index;
            }

        }
        break;
        case DM_Camera_Line1:
        {
            this->camera->SetEnumValue("TriggerMode",MV_TRIGGER_MODE_ON);//开启触发模式
            int nRet = MV_OK;
            nRet = this->camera->SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_LINE0);
            if (MV_OK != nRet)
            {
                this->message += "相机外触发设置失败!\n";
                this->triggerSource = DM_Camera_Default;
            }
            else
            {
                this->message += "相机外触发设置成功!\n";
                this->triggerSource = index;
            }
        }
        break;

        case DM_Camera_ContinuousAcquisition:
        {
            this->camera->SetEnumValue("TriggerMode",MV_TRIGGER_MODE_OFF);//开启触发模式
            int nRet = MV_OK;
            nRet = this->camera->SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_COUNTER0);
            if (MV_OK != nRet)
            {
                this->message += "相机连续触发设置失败!\n";
                this->triggerSource = DM_Camera_Default;
            }
            else
            {
                this->message += "相机连续触发设置成功!\n";
                this->triggerSource = index;
            }
        }
        break;

        case DM_Camera_ExposureTimeAbs:
        {
            // ch:调节这两个曝光模式，才能让曝光时间生效
            this->camera->SetEnumValue("ExposureMode", MV_EXPOSURE_MODE_TIMED);
            this->camera->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
            this->camera->SetFloatValue("ExposureTime", tmpValue);
        }
        break;
        case DM_Camera_GainRaw:
        {
            // ch:设置增益前先把自动增益关闭，失败无需返回
            this->camera->SetEnumValue("GainAuto", 0);
            this->camera->SetFloatValue("Gain", tmpValue);
        }
        break;
        case DM_Camera_AcquisitionFrameRateAbs:
        {
            this->camera->SetBoolValue("AcquisitionFrameRateEnable", true);
            this->camera->SetFloatValue("AcquisitionFrameRate", tmpValue);
        }
        break;
        case DM_Camera_Width:
        {
            this->stopAcquire();
            this->camera->SetIntValue("Width", tmpValue);
            this->startAcquire();
        }
        break;
        case DM_Camera_Height:
        {
            this->stopAcquire();
            this->camera->SetIntValue("Height", tmpValue);
            this->startAcquire();
        }
        break;
        case DM_Camera_BinningHorizontal:
        {
            this->stopAcquire();
            this->camera->SetEnumValue("BinningHorizontal", tmpValue);
            this->startAcquire();
        }
        break;
        case DM_Camera_BinningVertical:
        {
            this->stopAcquire();
            this->camera->SetEnumValue("BinningVertical", tmpValue);
            this->startAcquire();
        }
        break;
    default:
        break;
    }
}

bool DM_HIKCamera::stopAcquire()
{
    if (true == this->isOpenDevice &&
            true == this->isStartGrabbing &&
            NULL != this->camera)
    {
        this->camera->StopGrabbing();
        this->isStartGrabbing = false;
        return true;
    }
    else
    {
        return false;
    }
    this->message += "相机停止采集!\n";
}

bool DM_HIKCamera::startAcquire()
{
    if (false == this->isOpenDevice || true == this->isStartGrabbing || NULL == this->camera)
    {
        return false;
    }
    else
    {
        int nRet = this->camera->StartGrabbing();
        if (MV_OK != nRet)
        {

            this->message += "相机开始采集设置失败！\n";
            return false;
        }
        else
        {
            this->message += "相机开始采集\n";
            this->isStartGrabbing  = true;
            return true;
        }

    }
}
//查找相机，返回IP
MV_CC_DEVICE_INFO_LIST DM_HIKCamera::searchDevices()
{

    // ch:枚举子网内所有设备 | en:Enumerate all devices within subnet
    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &this->devList);
    if (MV_OK != nRet)
    {
        this->devList.nDeviceNum = 0;
    }
    // ch:将值加入到信息列表框中并显示出来 | en:Add value to the information list box and display
    //    std::vector<QString> ip;
    //    for (unsigned int i = 0; i < this->devList.nDeviceNum; i++)
    //    {
    //        MV_CC_DEVICE_INFO* pDeviceInfo = this->devList.pDeviceInfo[i];
    //        if (NULL == pDeviceInfo)
    //        {
    //            continue;
    //        }
    //        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
    //        {
    //            int nIp1 = ((this->devList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
    //            int nIp2 = ((this->devList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
    //            int nIp3 = ((this->devList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
    //            int nIp4 = (this->devList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

    //            ip.push_back( QString("%1.%2.%3.%4").arg(nIp1).arg(nIp2).arg(nIp3).arg(nIp4));
    //        }
    //    }
    return this->devList;
}

std::string DM_HIKCamera::getDeviceIP()
{
     MV_CC_DEVICE_INFO *pDeviceInfo = new MV_CC_DEVICE_INFO;
    int nRet =  this->camera->GetDeviceInfo(pDeviceInfo);
    if (nRet == MV_OK)
    {
        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            int nIp1 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            int nIp2 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            int nIp3 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            int nIp4 = (pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);
            return std::to_string(nIp1)+"."+std::to_string(nIp2)+"."+std::to_string(nIp3)+"."+std::to_string(nIp4);
        }
    }
}

bool DM_HIKCamera::connectDevice(MV_CC_DEVICE_INFO* pstDeviceInfo)
{
    if (NULL != this->camera || true == this->isOpenDevice)
    {
       return false;
    }

    this->camera = new CMvCamera;
    if (NULL == this->camera)
    {
        return false;
    }

    int nRet = this->camera->Open(pstDeviceInfo);
    if (MV_OK != nRet)
    {
        this->message += "相机连接失败!\n";
        delete this->camera;
        this->camera = NULL;
        this->isOpenDevice = false;

        return false;
    }
    else
    {
        this->message += "相机连接成功!\n";
        this->isOpenDevice = true;
        return true;
    }
}

void DM_HIKCamera::disConnectDevice()
{
    if (this->camera)
    {
        this->camera->Close();
        delete this->camera;
        this->camera = NULL;
    }

    this->isStartGrabbing = false;
    this->isOpenDevice = false;
    this->message += "相机断开连接!\n";
}

void DM_HIKCamera::setImageWidth(int width_)
{
     this->SetCameraParameter(DM_Camera_Width, width_);
}

int DM_HIKCamera::getImageWidth()
{
    return this->GetCameraParameter(DM_Camera_Width);
}

void DM_HIKCamera::setImageHeight(int height_)
{
    this->SetCameraParameter(DM_Camera_Height, height_);
}

int DM_HIKCamera::getImageHeight()
{
    return this->GetCameraParameter(DM_Camera_Height);
}

void DM_HIKCamera::setBinningVertical(int binningV_)
{
    if(binningV_ == 1 ||
            binningV_ == 2||
            binningV_ == 4)
    {
        this->SetCameraParameter(DM_Camera_BinningVertical, binningV_);
    }
}

void DM_HIKCamera::SetBinningHorizontal(int binningH_)
{
    if(binningH_ == 1 ||
            binningH_ == 2||
            binningH_ == 4)
    {
        this->SetCameraParameter(DM_Camera_BinningHorizontal, binningH_);
    }

}





