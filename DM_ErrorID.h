#pragma once

//反馈报错代码
enum DM_ErrorID_Tag
{
    DM_error_deafult = -1,//错误代码的默认初始值
    DM_error_no = 0,//没有错误
	DM_error_fileLoadFail,//文件加载失败
	DM_error_ImageLoadFail,//图片加载失败
	DM_error_para,//传参错误
	DM_error_calculate,//没有计算出预期结果或者计算中途发生意外终止
    DM_error_Init,//系统没有进行初始化或者说初始化错误
    DM_error_CameraConnection,//相机连接失败

};
