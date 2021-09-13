#pragma once
#include <opencv2/opencv.hpp>
//using namespace cv;

namespace cv_DM
{
//==============================================================================================
//函数说明：直线拟合
//参数说明：
//  @points, // 二维点的数组 或者  vector  或者  Mat
//	@line, // 输出直线,Vec4f (2d)或Vec6f (3d)的vector （一个是方向向量，另一个是拟合直线上的点）
//	@distType, // 距离类型(共7种直线拟合的算法，CV_DIST_L2(最小二乘法)受噪声的影响很大,其他方法具有一定的抗干扰性。
//     1）CV_DIST_L1     =  1,    distance = |x1-x2| + |y1-y2|
//     2）CV_DIST_L2     =  2,    the simple euclidean distance
//     3）CV_DIST_L12    =  4,    L1-L2 metric: distance = 2(sqrt(1+x*x/2) - 1))
//     4）CV_DIST_FAIR   =  5,    distance = c^2(|x|/c-log(1+|x|/c)),    c = 1.3998
//	   5）CV_DIST_WELSCH =  6,    distance = c^2/2(1-exp(-(x/c)^2)),     c = 2.9846
//	   6）CV_DIST_HUBER  =  7     distance = |x|<c ? x^2/2 : c(|x|-c/2), c=1.345

//	@param, // 距离参数（c）,跟所选的距离类型有关，值可以设置为0，fitLine()函数本身会自动选择最优化的值
//	@reps, // 径向的精度参数  一般设置为 1e-2
//	@aeps // 角度精度参数,   一般设置为 1e-2
//==============================================================================================
    void fitLine(cv::InputArray _points, cv::OutputArray _line, int distType = CV_DIST_L2,double param = 0, double reps = 1e-2, double aeps = 1e-2);//拟合直
//==============================================================================================
//函数说明：椭圆拟合
//参数说明：
// @_points:点集
//==============================================================================================
    cv::RotatedRect  fitEllipse(cv::InputArray _points);//拟合椭圆
}




cv::Mat translateImage(cv::Mat &src, int xOffset, int yOffset, bool bScale = false);
