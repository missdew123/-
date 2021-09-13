#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#include <cstring>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/core/types.hpp>

using namespace cv::xfeatures2d;
//using namespace cv;
//using namespace std;



//=======================================================================================================================================
//函数名称：基于SIFT的模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@roiVertices：模板图片的四个顶点对应在trainImg种位置，0-左上，1-右上，2-右下，3-左下点
//  @grabPoints:被检测图片的
//  @templateGrabP:模板的抓取位置
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@tempfeatures:模板特征点的个数，默认为0，全部查找
//	@trainfeatures：:检测图片特征点的个数，默认为0，全部查找
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配唯一的缺点是运算比较慢，但是是一个万能匹配算法，具备旋转不变性，尺度不变性，位移不变性等良好的特性
//  ②本算法考虑的图像的倾斜关系，所以输出来的4个顶点并不一定是矩形，可能是梯形，如果是二维平面变化，需要再用minAreaRect函数求解外接矩形
//=======================================================================================================================================
bool DM_matchTemplateFast_SIFT(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<std::vector<cv::Point2d>> &roiVertices, std::vector<cv::Point2d> &grabPoints,
                               cv::Point2d templateGrabP = cv::Point2d(-1,-1),double imgScale = 1.0,  int tempfeatures = 0, int trainfeatures = 0);

//=======================================================================================================================================
//函数名称：基于SURF的模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@roiVertices：模板图片的四个顶点对应在trainImg种位置，0-左上，1-右上，2-右下，3-左下点
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@tempHessianThreshold:模板特征点的Hessian阈值，值越大，特征点越小
//	@trainHessianThreshold:检测图片特征点的Hessian阈值，值越大，特征点越小
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配唯一的缺点是运算比较慢，但是是一个万能匹配算法，具备旋转不变性，尺度不变性，位移不变性等良好的特性
//  ②本算法考虑的图像的倾斜关系，所以输出来的4个顶点并不一定是矩形，可能是梯形，如果是二维平面变化，需要再用minAreaRect函数求解外接矩形
//=======================================================================================================================================
bool DM_matchTemplateFast_SURF(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<cv::Point2d> &roiVertices, double imgScale = 2.0,
	double tempHessianThreshold = 500, double trainHessianThreshold = 500);


//=======================================================================================================================================
//函数名称：基于opencv模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@pos: x,y分别表示匹配点的位置，z表示匹配点的得分系数
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@maskImg：匹配掩膜
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配算法只使用于工件有定位，图片只存在普通的平通状态，实用该算法。如果在该条件下，匹配算法的精度、效率均远高于特征点匹配，故
//=======================================================================================================================================

bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, cv::Point3d &pos, double imgScale = 2, cv::Mat maskImg = cv::Mat());

//=======================================================================================================================================
//函数名称：基于opencv模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@roiVertices：模板图片的四个顶点对应在trainImg种位置，0-左上，1-右上，2-右下，3-左下点
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@startAngle:模板特征点的个数（单位弧度），默认为0，不旋转
//	@endtAngle：:检测图片特征点的个数（单位弧度），默认为0，不旋转
//	@AnglePrecision：角度细分精度，默认0.0087弧度，转化成角度就是0.5°
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配算法如果用于有旋转的情况，计算料率非常低，不建议使用。如果模板和被测图像之间只有平移关系，用该算法会比用特征点匹配更加精准，效率更高。如果只有平移则
//    直接调用bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, cv::Point3d &pos, double imgScale = 2,cv::Mat maskImg = cv::Mat());
//=======================================================================================================================================

bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<cv::Point2d> &roiVertices,double imgScale = 2,
							  double startAngle = 0, double endtAngle = 0,double anglePrecision = 0.00877);
