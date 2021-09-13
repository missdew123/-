#include "DM_ImageAlgorithm.h"


DM_HandEyeCalibration::DM_HandEyeCalibration(std::vector<cv::Point2f> cameraPoints_, std::vector<cv::Point2f> robotPoints_):
    DM_ImageProcessBase(DM_HANDEYECALIBRATION_Tag,"", DM_error_deafult)
{
    this->dst = cv::Mat();//输出结果图片
    this->transformMatrix = cv::Mat();//输出转化系数方程
	for (int i = 0; i < 9 && i < cameraPoints_.size();i++)
	{
		this->cameraPoints.push_back(cameraPoints_[i]);
	}
	for (int i = 0; i < 9 && i < robotPoints_.size() && i < this->cameraPoints.size(); i++)
	{
		this->robotPoints.push_back(robotPoints_[i]);
	}
	this->outText.clear();
}

DM_HandEyeCalibration::DM_HandEyeCalibration(const DM_HandEyeCalibration &obj) :DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
    this->cameraPoints = obj.cameraPoints;
    this->robotPoints = obj.robotPoints;
	this->outText = obj.outText;
    obj.dst.copyTo(this->dst);
    obj.transformMatrix.copyTo(this->transformMatrix);
	
}

DM_HandEyeCalibration DM_HandEyeCalibration::operator=(const DM_HandEyeCalibration &obj)
{
    this->message = obj.message;
    this->processMethod = obj.processMethod;
    this->errorID = obj.errorID;
    this->cameraPoints = obj.cameraPoints;
    this->robotPoints = obj.robotPoints;
	this->outText = obj.outText;

    obj.dst.copyTo(this->dst);
    obj.transformMatrix.copyTo(this->transformMatrix);
	
    return *this;
}
int DM_HandEyeCalibration::process(cv::Mat src_ /*= cv::Mat()*/)
{
    this->message =   "@>>> 手眼标定算法运行状态 : ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	if (src_.channels() > 1)
	{
		src_.copyTo(this->dst_color);
        cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);
	}
	else
	{
        cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
		src_.copyTo(this->dst);
	}
    return this->calTransformMatrxi();
}

void DM_HandEyeCalibration::setRobotPoints(std::vector<cv::Point2f> points_)
{
	for (int i = 0; i < 9 && i < points_.size(); i++)
	{
		this->robotPoints.push_back(points_[i]);
	}
}


void DM_HandEyeCalibration::setCameraPoints(std::vector<cv::Point2f> points_)
{
	for (int i = 0; i < 9 && i < points_.size();i++)
	{
		this->cameraPoints.push_back(points_[i]);
	}
}

int DM_HandEyeCalibration::calTransformMatrxi()
{
	this->outText.clear();
    if ( this->cameraPoints.size() >= 9 && this->robotPoints.size()>= 9)//找出的角点必须为9，否则认为计算失败
    {
		
		//将特征点绘出出来
		if (!this->dst_color.empty())
		{
			for (int i = 0; i < this->cameraPoints.size(); i++)
			{
                cv::circle(this->dst_color, this->cameraPoints[i], 1, cv::Scalar(0, 0, 255), -1, CV_AA);
                DM_LabelText str(QString::number(i + 1), cv::Point(this->cameraPoints[i].x + 5, this->cameraPoints[i].y));
				this->outText.push_back(str);
				/*putText(this->dst_color, to_string(i + 1), Point(this->cameraPoints[i].x + 5, this->cameraPoints[i].y),
                    FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/
			}
		}

        this->transformMatrix = findHomography( this->cameraPoints, this->robotPoints, CV_RANSAC);//获取单应性矩阵
        if (this->transformMatrix.empty())
        {
            this->message += "标定失败，请检查输入的坐标和计算的特征点的坐标是否一一对应!\n";
            this->errorID = DM_error_calculate;
        }
        else
        {
            this->message += "标定成功\n";
            this->errorID = DM_error_no;
        }
		
        return this->errorID;
    }
    else
    {
        this->message  += "找到的特征点小于9个或者输入的坐标不完整!\n ";
        this->errorID = DM_error_calculate;
        return DM_error_calculate;
    }
}

DM_Threshold::DM_Threshold(DM_ImgProcess_Tag proMethod_, double thresh_, double maxValue_, int blockSize_, double C_):
    DM_ImageProcessBase(proMethod_, "")
{
    this->dst = cv::Mat();
    this->thresh = thresh_;//阈值
    this->maxValue = maxValue_;//使用 CV_THRESH_BINARY 和 CV_THRESH_BINARY_INV 的最大值。

    this->blockSize = blockSize_;//用来计算阈值的象素邻域大小: 3, 5, 7, ... ，此处必须为奇数
    this->C = C_;//自适应二值化时的偏移系数
}

DM_Threshold::DM_Threshold(const DM_Threshold &obj) :DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
    obj.dst.copyTo(this->dst);

	this->thresh = obj.thresh;//阈值(常规二值化算法使用)
	this->maxValue = obj.maxValue;//使用 CV_THRESH_BINARY 和 CV_THRESH_BINARY_INV 的最大值。
	this->blockSize = obj.blockSize;//块大小(即：将图像分成多少块)
	this->C = obj.C;//自适应二值化时的偏移系数
}
DM_Threshold& DM_Threshold::operator=(const DM_Threshold &obj)
{

    obj.dst.copyTo(this->dst);
	this->thresh = obj.thresh;//阈值(常规二值化算法使用)
	this->maxValue = obj.maxValue;//使用 CV_THRESH_BINARY 和 CV_THRESH_BINARY_INV 的最大值。
	this->blockSize = obj.blockSize;//块大小(即：将图像分成多少块)
	this->C = obj.C;//自适应二值化时的偏移系数
    this->processMethod = obj.processMethod;//图像预处理方法，该类全部都是THRESHOLD_Tag
	return *this;
}


int DM_Threshold::process(cv::Mat src_)
{
    this->message = "@>>> 二值化运行状态： ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	if (src_.empty())
	{
        this->message = "待处理的图片为空，请重新加载！=> ";
		return DM_error_ImageLoadFail;//图片加载失败
	}
	else 
	{
		cv::Mat src;
		if (src_.channels() > 1)
		{
            cv::cvtColor(src_, src, cv::COLOR_BGR2GRAY);
		}
		else
		{
			src = src_;
		}

        if (this->processMethod == DM_THRESHOLD_ADAPTIVE_Tag)//局部二值化
		{
            cv::adaptiveThreshold(src,this->dst,this->maxValue,cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY,this->blockSize,this->C);
		}
        else if (this->processMethod == DM_THRESHOLD_OTSU_Tag)//局部二值化
		{
            cv::threshold(src,this->dst,this->thresh,this->maxValue,CV_THRESH_OTSU);
		}
		else if (this->processMethod == DM_THRESHOLD_GENERAL_INV_Tag)//局部二值化
		{
			cv::threshold(src, this->dst, this->thresh, this->maxValue, CV_THRESH_BINARY_INV);
		}
		else//全局二值化
		{
            cv::threshold(src,this->dst,this->thresh,this->maxValue, CV_THRESH_BINARY);
		}
        this->message += "二值化处理成功!\n";
		this->errorID = DM_error_no;
		return DM_error_no;
	}

}

DM_FindContours::DM_FindContours(double minAreaThreshold_ , double maxAreaThreshold_,int mode_, int method_) :
                                 DM_ImageProcessBase(DM_CONTOURS_Tag, "")
{
	this->dst = cv::Mat();
	this->dst_color = cv::Mat();
	
	this->contours.clear();
	this->contourAreas.clear();
	this->hierarchy.clear();

	this->minAreaThreshold = minAreaThreshold_;
	this->maxAreaThreshold = maxAreaThreshold_;
	this->maxArea = -1;
	this->minArea = -1;
	this->mode = mode_;
	this->method = method_;

	this->outText.clear();
}
DM_FindContours::DM_FindContours(const DM_FindContours &obj):DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{

    obj.dst.copyTo(this->dst);
    obj.dst_color.copyTo(this->dst_color);
	this->message = obj.message;
	this->contours = obj.contours;
	this->contourAreas = obj.contourAreas;
	this->hierarchy = obj.hierarchy;
	this->outText = obj.outText;

	this->minArea = obj.minArea;
	this->maxArea = obj.maxArea;
	this->minAreaThreshold = obj.minAreaThreshold;
	this->maxAreaThreshold = obj.maxAreaThreshold;

	this->mode = obj.mode;
	this->method = obj.method;
}
DM_FindContours DM_FindContours::operator=(const DM_FindContours &obj)
{
    obj.dst.copyTo(this->dst);
    obj.dst_color.copyTo(this->dst_color);
	this->message = obj.message;
	this->contours = obj.contours;
	this->contourAreas = obj.contourAreas;
	this->hierarchy = obj.hierarchy;
	this->outText = obj.outText;

	this->minArea = obj.minArea;
	this->maxArea = obj.maxArea;
	this->minAreaThreshold = obj.minAreaThreshold;
	this->maxAreaThreshold = obj.maxAreaThreshold;
	this->mode = obj.mode;
	this->method = obj.method;
	return *this;
}


int DM_FindContours::process(cv::Mat src_)
{
    this->message = "@>>>查找轮廓算法运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
	if (src_.empty())
	{
        this->message = " 待处理的图片为空，请重新加载！=> ";
		this->errorID = DM_error_ImageLoadFail;
		return DM_error_ImageLoadFail;
	}
	cv::Mat src;
	if (src_.channels() > 1)
	{

        cv::cvtColor(src_, src, cv::COLOR_BGR2GRAY);
		src_.copyTo(this->dst_color);
        cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);
	}
	else
	{
		src_.copyTo(src);
        cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
		src_.copyTo(this->dst);
	}

	threshold(src, src, 100, 255, CV_THRESH_OTSU);//确保黑中找白
	findContours(src, this->contours, this->hierarchy, this->mode, this->method);
	if (this->contours.empty())
	{
		;
	}
	//else if (this->maxAreaThreshold == -1 && this->minAreaThreshold == -1)
	//{
	//	//计算轮廓质心
	//	DM_Moment mu(this->contours);
	//	mu.process(src);
    //	std::vector<cv::Point2f> centerP = mu.getCenterOfMass();

	//	for (int i = 0; i < this->contours.size();i++)
	//	{
	//		double s = contourArea(this->contours[i]);
	//		this->contourAreas.push_back(s);

	//		//将轮廓绘出
	//		drawContours(this->dst_color, this->contours, i, Scalar(0, 0, 255), 3);
	//		cv::circle(this->dst_color, Point(centerP[i].x, centerP[i].y), 5, Scalar(255, 0, 0), -1, CV_AA);
	//		string str = to_string(i+1);
	//		putText(this->dst_color, str, Point(centerP[i].x + 5, centerP[i].y), FONT_HERSHEY_COMPLEX,
	//			1.0, Scalar(255, 0, 0), 2, CV_AA, false);
	//	}
	//}
	else
	{
		//计算轮廓质心
		DM_Moment mu(this->contours);
		mu.process(src);
		this->mc = mu.getCenterOfMass();
		
		int index = 1;
		for (int i = 0; i < this->contours.size();)
		{
			double s = contourArea(this->contours[i]);
			if ((s > this->maxAreaThreshold && this->maxAreaThreshold > 0) ||
				(s < this->minAreaThreshold && this->minAreaThreshold > 0))
			{
				//将轮廓绘出
			/*	drawContours(this->dst_color, this->contours, i, Scalar(0, 0, 255), 2);
				DM_LabelText str(QString::number(s), Point(this->mc[i].x + 5, this->mc[i].y));
				this->outText.push_back(str);*/
                /*putText(this->dst_color, to_string(int(s)), Point(this->mc[i].x + 5, this->mc[i].y), FONT_HERSHEY_COMPLEX,
                        1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/

				this->contours.erase((this->contours.begin() + i));
				this->hierarchy.erase(this->hierarchy.begin() + i);
				this->mc.erase(this->mc.begin() + i);
			}
			else
			{
				//将轮廓绘出
                cv::drawContours(this->dst_color, this->contours, i, cv::Scalar(0, 255, 0), 2);
                cv::circle(this->dst_color, cv::Point(this->mc[i].x, this->mc[i].y), 1, cv::Scalar(0, 0, 255), -1, CV_AA);
				DM_LabelText str("[" + QString::number(index++)+"]S:"+ QString::number(s),
                                 cv::Point(this->mc[i].x + 5, this->mc[i].y));
				this->outText.push_back(str);
				/*putText(this->dst_color, str, Point(this->mc[i].x + 5, this->mc[i].y), FONT_HERSHEY_COMPLEX,
					1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/

				this->contourAreas.push_back(s);
				i++;

				
			}
		}
	}
	//输出关键信息
	/*cvtColor(src, this->dst_color, COLOR_GRAY2BGR);
	cv::Mat(src.size(), CV_8UC1, Scalar(0)).copyTo(this->dst);*/
	if (this->contours.empty())
	{
        this->message += " 没有找到轮廓\n";
	}
	else
	{
		/*drawContours(this->dst_color, this->contours, -1, Scalar(0, 0, 255),3);*/
		/*drawContours(this->dst, this->contours, -1, Scalar(255),3);*/

		sort(this->contourAreas.begin(), this->contourAreas.end());//将面积排序
		this->maxArea = this->contourAreas[this->contourAreas.size() - 1];
		this->minArea = this->contourAreas[0];
        this->message += " 轮廓信息【 轮廓数量: " + std::to_string(this->contours.size())+
                         " 最大轮廓: " + std::to_string(this->maxArea) +
                         " 最小轮廓: " + std::to_string(this->minArea) + "】\n";
	}
	this->errorID = DM_error_no;
	return DM_error_no;
}


DM_Moment::DM_Moment(std::vector<std::vector<cv::Point> > contours_):DM_ImageProcessBase(DM_MOMENTS_Tag, "")
{
    this->dst = cv::Mat();
    this->mc.clear();
    this->mu.clear();
    this->contours = contours_;
	this->outText.clear();
}

DM_Moment::DM_Moment(const DM_Moment &obj):DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
    obj.dst.copyTo(this->dst);

    this->mc = obj.mc;
    this->mu = obj.mu;
    this->contours = obj.contours;
	this->outText = obj.outText;
}

DM_Moment DM_Moment::operator=(const DM_Moment &obj)
{

    obj.dst.copyTo(this->dst);

    this->mc = obj.mc;
    this->mu = obj.mu;
    this->contours = obj.contours;

    this->message = obj.message;
	this->outText = obj.outText;
    this->processMethod = obj.processMethod;
    return *this;
}

int DM_Moment::process(cv::Mat src_)
{
    this->message = "@>>>图像的矩运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
    if (this->contours.empty())
    {
        this->message += "  轮廓为空! => ";
		this->errorID = DM_error_para;
        return DM_error_para;
    }
    else if(src_.empty())
    {
        this->message += "  图像为空! => ";
        return DM_error_ImageLoadFail;
    }
    else
    {
		if (src_.channels() > 1)
		{
			src_.copyTo(this->dst_color);
            cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);
		}
		else
		{
            cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
			src_.copyTo(this->dst);
		}

		this->mu.clear();
		this->mc.clear();
        //计算矩
        for( int i = 0; i < this->contours.size(); i++ )
        {
            this->mu.push_back( moments(this->contours[i], false ));
        }
        //计算轮廓的质心
        for( int i = 0; i < contours.size(); i++ )
        {
            this->mc.push_back( cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ));
        }
        for (int i = 0; i < this->mc.size(); i++)
        {
            cv::circle(this->dst_color,this->mc[i], 1, cv::Scalar(0, 0, 255), -1, CV_AA);
            DM_LabelText str(QString::number(i + 1), cv::Point(this->mc[i].x + 5, this->mc[i].y));
			this->outText.push_back(str);
			/*putText(this->dst_color, to_string(i+1), Point(this->mc[i].x+5, this->mc[i].y), FONT_HERSHEY_COMPLEX,
                    1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/
        }
        this->message += " 计算完成!\n";
		this->errorID = DM_error_no;
        return DM_error_no;
    }

}

DM_CoordinateTransform::DM_CoordinateTransform(cv::Mat transformMatrix_, std::vector<cv::Point2f> originalPoints_) :
    DM_ImageProcessBase(DM_COORDINATE_Tag, "")
{
	this->transformMatrix = transformMatrix_;
	this->originalPoints = originalPoints_;
	this->objectPoints.clear();
	this->outText.clear();
	this->dst = cv::Mat();
}

DM_CoordinateTransform::DM_CoordinateTransform(const DM_CoordinateTransform &obj) :
	DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
	this->transformMatrix = obj.transformMatrix;
	this->originalPoints = obj.originalPoints;
	this->objectPoints = obj.objectPoints;
	this->dst = obj.dst;
	this->outText = obj.outText;
}

int DM_CoordinateTransform::process(cv::Mat src_ /*= cv::Mat()*/)
{
    this->message = "@>>>坐标转化运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
    this->dst = src_;//仅仅为了工程的完整性，该参数作为信号传递使用，
	if (src_.channels() > 1)
	{
		src_.copyTo(this->dst_color);
        cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);

	}
	else
	{
        cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
		src_.copyTo(this->dst);
	}

	if (this->transformMatrix.empty())
	{
        this->message += "转化矩阵为空，请先标定坐标转化矩阵! => ";
		this->errorID = DM_error_para;
	}
	else if (this->originalPoints.empty())
	{
        this->message += "没有需要转换坐标的点，请先计算关键点! => ";
		this->errorID = DM_error_para;
	}
	else
	{
		//绘图
		for (int i = 0; i < this->originalPoints.size(); i++)
		{
            cv::circle(this->dst_color, this->originalPoints[i], 1, cv::Scalar(0, 0, 255), -1, CV_AA);
            DM_LabelText str(QString::number(i + 1), cv::Point(this->originalPoints[i].x + 5, this->originalPoints[i].y));
			this->outText.push_back(str);
			/*putText(this->dst_color, to_string(i + 1), Point(this->originalPoints[i].x + 5, this->originalPoints[i].y), 
                    FONT_HERSHEY_COMPLEX,1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/
		}
        cv::perspectiveTransform(this->originalPoints, this->objectPoints, this->transformMatrix);  //映射矩阵
        this->message += "坐标转换完成！\n";
		this->errorID = DM_error_no;
	}
	return this->errorID;
}

DM_HoughCircle::DM_HoughCircle(double minDist_, double cannyThreshold_, double countThreshold_, int minRadius_,
                               int maxRadius_):DM_ImageProcessBase(DM_HOUGHCIRCLE_Tag, "")
{
    this->method = cv::HOUGH_GRADIENT;
    this->dp = 1.0;
    this->minDist = minDist_;
    this->cannyThreshold = cannyThreshold_;
    this->countThreshold = countThreshold_;
    this->minRadius = minRadius_;
    this->maxRadius = maxRadius_;
    this->circles.clear();
    this->dst = cv::Mat();
	this->outText.clear();
}

DM_HoughCircle::DM_HoughCircle(const DM_HoughCircle &obj):DM_ImageProcessBase(obj.processMethod,obj.message,obj.errorID)
{
    if (obj.dst.empty())
    {
        this->dst = cv::Mat();
    }
    else
    {
        obj.dst.copyTo(this->dst);
    }
    this->method = obj.method;
    this->dp = obj.dp;
    this->minDist = obj.minDist;
    this->cannyThreshold = obj.cannyThreshold;
    this->countThreshold = obj.countThreshold;
    this->minRadius = obj.minRadius;
    this->maxRadius = obj.maxRadius;
    this->circles = obj.circles;
	this->outText = obj.outText;
}

DM_HoughCircle DM_HoughCircle::operator=(const DM_HoughCircle &obj)
{
    if (obj.dst.empty())
    {
        this->dst = cv::Mat();
    }
    else
    {
        obj.dst.copyTo(this->dst);
    }
    this->method = obj.method;
    this->dp = obj.dp;
    this->minDist = obj.minDist;
    this->cannyThreshold = obj.cannyThreshold;
    this->countThreshold = obj.countThreshold;
    this->minRadius = obj.minRadius;
    this->maxRadius = obj.maxRadius;
    this->circles = obj.circles;
	this->outText = obj.outText;
    return *this;
}

int DM_HoughCircle::process(cv::Mat src_)
{
    this->message = "@>>>霍夫圆运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
    if(src_.empty())
    {
        this->message += "载入图像为空";
        this->errorID = DM_error_ImageLoadFail;
    }
    else
    {
		if (src_.channels() > 1)
		{
			src_.copyTo(this->dst_color);
            cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);
		}
		else
		{
            cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
			src_.copyTo(this->dst);
		}

        cv::Mat cannyImg;
        cv::Canny(src_, cannyImg, 50, 100);
        std::vector<std::vector<cv::Point>> contours;//返回找到的轮廓
        std::vector<cv::Vec4i> hierarchy; //轮廓索引编号
        cv::findContours(cannyImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        if(contours.empty())
        {
            this->message += " 没有找到边沿轮廓，请重新加载图片或者设置参数 ！\n";
            this->errorID = DM_error_calculate;
        }
        else
        {
            cv::Mat contoursIMg = cv::Mat(cannyImg.size(), CV_8UC1, cv::Scalar(0));
            cv::drawContours(contoursIMg, contours, -1, cv::Scalar(255), 1);
            cv::HoughCircles(contoursIMg, this->circles, cv::HOUGH_GRADIENT, 1.5, this->minDist,
						 this->cannyThreshold, this->countThreshold, this->minRadius, this->maxRadius);
            
            for (int i = 0; i < this->circles.size(); i++)
            {
                cv::Point center(this->circles[i][0], circles[i][1]);
                int radius = this->circles[i][2];
                cv::circle(this->dst_color, center, radius, cv::Scalar(255, 0, 0), 2);
                cv::circle(this->dst_color, center, 1, cv::Scalar(0, 255, 0), -1);
				DM_LabelText str(QString::number(i + 1), center);
				this->outText.push_back(str);
                /*putText(this->dst_color, to_string(i+1), center, FONT_HERSHEY_COMPLEX,
                        1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/
            }
            if(this->circles.empty())
            {
                this->message += " 没有找到圆，请重新加载图片或者设置参数！\n";
                this->errorID = DM_error_calculate;
            }
            else
            {
                this->message += " 霍夫圆查找完成！\n";
                this->errorID = DM_error_no;
            }
        }

    }
    return this->errorID;
}

std::vector<cv::Point2f> DM_HoughCircle::getCircleCenters()
{
    std::vector<cv::Point2f>centerPoints;
    for(int i = 0; i < this->circles.size(); i++)
    {
        centerPoints.push_back(cv::Point2f(this->circles[i][0],this->circles[i][1]));
    }
    return centerPoints;
}

DM_ChessBoardCalibration::DM_ChessBoardCalibration(cv::Size chessBoardSize_):DM_ImageProcessBase(DM_CHESSBOARDCALIBRATION_Tag, "")
{
    this->dst = cv::Mat();
    this->chessBoardSize = chessBoardSize_;
    this->featurePoints.clear();
	this->outText.clear();
}

DM_ChessBoardCalibration::DM_ChessBoardCalibration(const DM_ChessBoardCalibration &obj):DM_ImageProcessBase(obj.processMethod,obj.message,obj.errorID)
{
    if(obj.dst.empty())
    {
        this->dst = cv::Mat();
    }
    else
    {
        obj.dst.copyTo(this->dst);
    }
    this->chessBoardSize = obj.chessBoardSize;
    this->featurePoints = obj.featurePoints;
	this->outText = obj.outText;
}

DM_ChessBoardCalibration DM_ChessBoardCalibration::operator=(const DM_ChessBoardCalibration &obj)
{
    if(obj.dst.empty())
    {
        this->dst = cv::Mat();
    }
    else
    {
        obj.dst.copyTo(this->dst);
    }
    this->chessBoardSize = obj.chessBoardSize;
    this->featurePoints = obj.featurePoints;

    this->message = obj.message;
    this->processMethod  = obj.processMethod;
    this->errorID = obj.errorID;
	this->outText = obj.outText;
    return *this;
}

int DM_ChessBoardCalibration::process(cv::Mat src_)
{
    this->message = "@>>>棋盘格标定运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
    if (src_.empty())
    {
        this->message += "待处理的图片为空，请重新加载！ => ";
        this->errorID = DM_error_ImageLoadFail;
        return DM_error_ImageLoadFail;
    }
    //-------------------读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化----------------------
    if (src_.channels() > 1)
    {
		src_.copyTo(this->dst_color);
        cvtColor(src_, this->dst, CV_RGB2GRAY);
    }
    else
    {
        cvtColor(src_, this->dst_color, CV_GRAY2BGR);
        src_.copyTo(this->dst);
    }
    std::vector<cv::Point2f> imagePointsBuf;
    cv::Size cornerSize(this->chessBoardSize.width - 1, this->chessBoardSize.height - 1);
    if (cv::findChessboardCorners(this->dst, cornerSize, imagePointsBuf, CV_CALIB_CB_ADAPTIVE_THRESH |
                              CV_CALIB_CB_FILTER_QUADS))//如果内角点必须全部找完，否则排除这组数据，方便后续处理
    {
        cv::cornerSubPix(this->dst, imagePointsBuf, cv::Size(5, 5), cv::Size(-1, -1),
            cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        for (int i = 0; i < imagePointsBuf.size(); i++)
        {
            cv::circle(this->dst_color,imagePointsBuf[i], 1, cv::Scalar(0, 0, 255), 1, CV_AA);
            DM_LabelText str(QString::number(i + 1), cv::Point(imagePointsBuf[i].x + 5, imagePointsBuf[i].y));
			this->outText.push_back(str);
            /*putText(this->dst_color, to_string(i+1), Point(imagePointsBuf[i].x+5, imagePointsBuf[i].y), FONT_HERSHEY_COMPLEX,
                    1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/
        }
        if (imagePointsBuf.size() > 0)//
        {
            this->message += "特征点查找完成!\n";
            this->featurePoints = imagePointsBuf;
            this->errorID = DM_error_no;
            return DM_error_no;
        }
        else
        {
            this->message += "计算失败!\n";
            this->errorID = DM_error_calculate;
            return DM_error_calculate;
        }
    }
    else
    {
        this->message += "计算失败!\n";
        this->errorID = DM_error_calculate;
        return DM_error_calculate;
    }
    return this->errorID;
}


DM_MatchTemplate::DM_MatchTemplate(cv::Mat templateImg_, double similarity_, cv::Point2f tempGrabP_):
	              DM_ImageProcessBase(DM_MATCHTEMPLATE_Tag, "")
{
    templateImg_.copyTo(this->templateImg);
    this->similarity = similarity_;
	this->tempGrabPoint = tempGrabP_;
	this->outText.clear();
}

DM_MatchTemplate::DM_MatchTemplate(const DM_MatchTemplate &obj):DM_ImageProcessBase(obj.processMethod,obj.message,obj.errorID)
{
    obj.templateImg.copyTo(this->templateImg);
    this->similarity = obj.similarity;
    obj.dst.copyTo(this->dst);
    //this->tempCenter = obj.tempCenter;
    this->tempPos = obj.tempPos;
	this->tempGrabPoint = obj.tempGrabPoint;
	this->grabPoints = obj.grabPoints;
	this->outText = obj.outText;
}

DM_MatchTemplate DM_MatchTemplate::operator=(const DM_MatchTemplate &obj)
{
    this->processMethod = obj.processMethod;
    this->message = obj.message;
    this->errorID = obj.errorID;

    obj.templateImg.copyTo(this->templateImg);
    this->similarity = obj.similarity;
    obj.dst.copyTo(this->dst);

   /* this->tempCenter = obj.tempCenter;*/
    this->tempPos = obj.tempPos;
	this->tempGrabPoint = obj.tempGrabPoint;
	this->grabPoints = obj.grabPoints;
	this->outText = obj.outText;
    return *this;
}

int DM_MatchTemplate::process(cv::Mat src_)
{
    this->message = "@>>>模板匹配运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
    if (src_.empty())
    {
        this->message += "待处理的图片为空，请重新加载！\n";
        this->errorID = DM_error_ImageLoadFail;
        return this->errorID;
    }
    if(this->templateImg.empty())
    {
        this->message += "模板为空，请重新加载！\n";
        this->errorID = DM_error_ImageLoadFail;
        return this->errorID;
    }
	if (this->templateImg.cols > src_.cols || this->templateImg.rows > src_.rows)
	{
		this->message += "模板比测试图像大，请重新加载！\n";
		this->errorID = DM_error_para;
		return this->errorID;
	}
	if (src_.channels() > 1)
	{
		src_.copyTo(this->dst_color);
        cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);
		
	}
	else
	{
        cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
		src_.copyTo(this->dst);
	}

    cv::Mat resImg;
    cv::matchTemplate(src_, this->templateImg, resImg, cv::TM_SQDIFF);
    cv::normalize(resImg, resImg, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    /*this->tempCenter.clear();*/
	this->grabPoints.clear();
    this->tempPos.clear();
    this->message += "相似度{\n";
    

    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
	int index = 0;
    while(1)
    {
        cv::minMaxLoc(resImg, &minVal, &maxVal, &minLoc, &maxLoc);
        this->message += std::to_string(minVal);
        if(minVal < this->similarity)
        {
            this->message += ", ";
            this->tempPos.push_back(minLoc);
			if (this->tempGrabPoint.x >= 0 && 
				this->tempGrabPoint.y >= 0 &&
				this->tempGrabPoint.x <= this->templateImg.cols &&
				this->tempGrabPoint.y <= this->templateImg.rows)
			{
                this->grabPoints.push_back(cv::Point2f(float(minLoc.x) + this->tempGrabPoint.x,
					                               float(minLoc.y) + this->tempGrabPoint.y));
			}
			else
			{
                this->grabPoints.push_back(cv::Point2f(float(minLoc.x) + this->templateImg.cols / 2.0,
					                               float(minLoc.y) + this->templateImg.rows / 2.0));
			}
           

			int x,y,w, h;
			if (minLoc.x >= this->templateImg.cols/2)
			{
				x = minLoc.x - this->templateImg.cols / 2;
			}
			else
			{
				x = 0;
			}
			if (minLoc.y >=  this->templateImg.rows/2)
			{
				y = minLoc.y - this->templateImg.rows / 2;
			}
			else
			{
				y = 0;
			}
			if (x + this->templateImg.cols < resImg.cols)
			{
				w = this->templateImg.cols;
			}
			else
			{
				w = resImg.cols - x;
			}
			if (y + this->templateImg.rows < resImg.rows)
			{
				h = this->templateImg.rows;
			}
			else
			{
				h = resImg.rows - y;
			}
            cv::Rect rec(x,y,w,h);
            cv::Mat roiImg = cv::Mat::ones(h, w,CV_32FC1);
			roiImg.copyTo(resImg(rec));
			
            cv::circle(this->dst_color,this->grabPoints[index], 1, cv::Scalar(0,0,255), -1);
			DM_LabelText str(QString::number(index + 1), this->grabPoints[index]);
			this->outText.push_back(str);
			/*putText(this->dst_color, to_string(index + 1), this->grabPoints[index], FONT_HERSHEY_COMPLEX,
					1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/
            cv::rectangle(this->dst_color, cv::Rect(minLoc.x, minLoc.y, this->templateImg.cols, this->templateImg.rows), cv::Scalar(0, 255, 0), 2, 8, 0);
			index++;
        }
        else
        {
            break;
        }

    }
    this->message += "}";
    if(this->tempPos.empty())
    {
        this->message += "在当前阈值下没有找到对应的模板，请重新设定阈值\n";
        this->errorID = DM_error_para;
        return this->errorID;
    }
    else
    {
        this->message += "模板查找完成\n";
        this->errorID = DM_error_no;
        return this->errorID;
    }

}

DM_FeatureMatch_SIFT::DM_FeatureMatch_SIFT(cv::Mat templateImg_ /*= cv::Mat()*/, double  imgScale_, cv::Point2f tempGrabP_ /*= cv::Point2f(-1.0, -1.0)*/) :
	DM_ImageProcessBase(DM_FEATUREMATCH_Tag, "", DM_error_deafult)
{
	templateImg_.copyTo(this->templateImg);
	this->imgScale = imgScale_;
	this->tempGrabPoint = tempGrabP_;
	this->tempVertices.clear();
	this->grabPoints.clear();
	this->outText.clear();
}

DM_FeatureMatch_SIFT::DM_FeatureMatch_SIFT(const DM_FeatureMatch_SIFT &obj) :DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
	obj.templateImg.copyTo(this->templateImg);
	obj.dst.copyTo(this->dst);
	this->tempVertices = obj.tempVertices;
	this->tempGrabPoint = obj.tempGrabPoint;
	this->grabPoints = obj.grabPoints;
	this->imgScale = obj.imgScale;
	this->outText = obj.outText;
}

DM_FeatureMatch_SIFT DM_FeatureMatch_SIFT::operator=(const DM_FeatureMatch_SIFT &obj)
{
	obj.templateImg.copyTo(this->templateImg);
	obj.dst.copyTo(this->dst);
	this->tempVertices = obj.tempVertices;
	this->tempGrabPoint = obj.tempGrabPoint;
	this->grabPoints = obj.grabPoints;
	this->imgScale = obj.imgScale;
	this->outText = obj.outText;

	this->message = obj.message;
	this->processMethod = obj.processMethod;
	this->errorID = obj.errorID;

	return *this;
}


int DM_FeatureMatch_SIFT::process(cv::Mat src_ /*= cv::Mat()*/)
{
	this->message = "@>>> 特征点匹配运行状态： ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
	if (src_.empty())
	{
		this->message += "待处理的图片为空，请重新加载！\n";
		this->errorID = DM_error_ImageLoadFail;
		return this->errorID;//图片加载失败
	}
	else
	{
		if (src_.channels() > 1)
		{
			src_.copyTo(this->dst_color);
            cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);

		}
		else
		{
            cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
			src_.copyTo(this->dst);
		}

        std::vector<std::vector<cv::Point2d>> tempVertices_;//被识别图像上，模板的四个端点
        std::vector<cv::Point2d> grabPoints_;//抓取点
        if (DM_matchTemplateFast_SIFT(this->templateImg, src_,tempVertices_, grabPoints_,
			this->tempGrabPoint, this->imgScale))
		{
			this->tempVertices.clear();
			this->grabPoints.clear();
			for (int i = 0; i < tempVertices_.size(); i++)
			{
				

                cv::line(this->dst_color, cv::Point(tempVertices_[i][0].x, tempVertices_[i][0].y), cv::Point(tempVertices_[i][1].x, tempVertices_[i][1].y), cv::Scalar(0, 255, 0), 3);
                cv::line(this->dst_color, cv::Point(tempVertices_[i][1].x, tempVertices_[i][1].y), cv::Point(tempVertices_[i][2].x, tempVertices_[i][2].y), cv::Scalar(0, 255, 0), 3);
                cv::line(this->dst_color, cv::Point(tempVertices_[i][2].x, tempVertices_[i][2].y), cv::Point(tempVertices_[i][3].x, tempVertices_[i][3].y), cv::Scalar(0, 255, 0), 3);
                cv::line(this->dst_color, cv::Point(tempVertices_[i][3].x, tempVertices_[i][3].y), cv::Point(tempVertices_[i][0].x, tempVertices_[i][0].y), cv::Scalar(0, 255, 0), 3);

                cv::circle(this->dst_color, cv::Point(grabPoints_[i].x, grabPoints_[i].y), 1, cv::Scalar(0, 0, 255), -1);
                DM_LabelText str(QString::number(i + 1), cv::Point(grabPoints_[i].x+5, grabPoints_[i].y));
				this->outText.push_back(str);
                //putText(this->dst_color, to_string(i + 1), Point(grabPoints_[i].x, grabPoints_[i].y), FONT_HERSHEY_COMPLEX,1.0, Scalar(0, 255, 255), 2, CV_AA, false);
				//为了整个系统的精度同意，全部将输出点转化成float
				this->grabPoints.push_back(grabPoints_[i]);
				
                std::vector<cv::Point2f> tempVP;
                tempVP.push_back(cv::Point2f(tempVertices_[i][0].x, tempVertices_[i][0].y));
                tempVP.push_back(cv::Point2f(tempVertices_[i][1].x, tempVertices_[i][1].y));
                tempVP.push_back(cv::Point2f(tempVertices_[i][2].x, tempVertices_[i][2].y));
                tempVP.push_back(cv::Point2f(tempVertices_[i][3].x, tempVertices_[i][3].y));

				this->tempVertices.push_back(tempVP);
				
			}
			this->message += "特征点匹配完成！\n";
			this->errorID = DM_error_no;
			return this->errorID;//图片加载失败
		}
		else
		{
			this->message += "特征点查找失败，请检查图片或者重新框选特征点！\n";
			this->errorID = DM_error_calculate;
			return this->errorID;//图片加载失败
		}

	}
}

DM_ContoursMatch::DM_ContoursMatch(std::vector<std::vector<cv::Point> > templateContours_, double similarity_):
    DM_ImageProcessBase(DM_CONTOURSMATCH_Tag, "", DM_error_deafult)
{
    this->templateContours = templateContours_;
    this->trianContours.clear();
    this->grabPoints.clear();
    this->similarity = similarity_;
	this->outText.clear();
}

DM_ContoursMatch::DM_ContoursMatch(const DM_ContoursMatch &obj):DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
    obj.dst.copyTo(this->dst);
	obj.dst_color.copyTo(this->dst_color);
	this->templateImg.clear();
	for (int i = 0; i < obj.templateImg.size(); i++)
	{
		this->templateImg.push_back(obj.templateImg[i].clone());
	}

    this->templateContours = obj.templateContours;
    this->trianContours = obj.trianContours;
    this->grabPoints = obj.grabPoints;
    this->similarity = obj.similarity;
	this->tempGrabPoint = obj.tempGrabPoint;
	this->outText = obj.outText;
}

DM_ContoursMatch DM_ContoursMatch::operator=(const DM_ContoursMatch &obj)
{
    obj.dst.copyTo(this->dst);
	obj.dst_color.copyTo(this->dst_color);
	this->templateImg.clear();
	for (int i = 0; i < obj.templateImg.size(); i++)
	{
		this->templateImg.push_back(obj.templateImg[i].clone());
	}

    this->templateContours = obj.templateContours;
    this->trianContours = obj.trianContours;
    this->grabPoints = obj.grabPoints;
    this->similarity = obj.similarity;
	this->tempGrabPoint = obj.tempGrabPoint;

    this->message = obj.message;
    this->processMethod = obj.processMethod;
    this->errorID = obj.errorID;
	this->outText = obj.outText;
    return *this;

}

int DM_ContoursMatch::process(cv::Mat src_)
{

    this->message = "@>>> 轮廓匹配运行状态： ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
    if (this->trianContours.empty())
    {
        this->message = "请先计算轮廓，否则无法计算！\n";
        this->errorID = DM_error_para;
        return this->errorID;//
    }
    else if(this->templateContours.empty())
    {
        this->message = "请框选模板轮廓，否则无法计算！\n";
        this->errorID = DM_error_para;
        return this->errorID;//图片加载失败
    }
    else if(src_.empty())
    {
        this->message = "图片为空，请先加载图片！\n";
        this->errorID = DM_error_ImageLoadFail;
        return this->errorID;//图片加载失败
    }
    else
    {
		if (src_.channels() > 1)
		{
			src_.copyTo(this->dst_color);
            cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);

		}
		else
		{
            cv::cvtColor(src_, this->dst_color, cv::COLOR_GRAY2BGR);
			src_.copyTo(this->dst);
		}

		//计算轮廓质心
        DM_Moment mu(this->trianContours);
        mu.process(src_);
        std::vector<cv::Point2f> centerP = mu.getCenterOfMass();

        int index = 1;
		this->grabPoints.clear();
        for (int i = 0; i < this->templateContours.size();i++)//遍历待测试图像的轮廓
        {
            for(int j = 0; j < this->trianContours.size(); j++)
            {
                //返回此轮廓与模版轮廓之间的相似度
                double similarity_ = cv::matchShapes(this->templateContours[i], this->trianContours[j], CV_CONTOURS_MATCH_I1, 0);
                if (similarity_ < this->similarity)//如果此轮廓与模版轮廓的相似度小于0.1
                {
                    cv::drawContours(this->dst_color, this->trianContours, j, cv::Scalar(0, 255, 0), 3, 8);//则在待测试图像上画出此轮廓
                    cv::circle(this->dst_color,cv::Point(centerP[j].x,centerP[j].y), 3, cv::Scalar(0, 0, 255), -1, CV_AA);
					
					DM_LabelText str("[" + QString::number(index)+"]S:"+ QString::number(similarity_),
                                     cv::Point(centerP[j].x + 5, centerP[j].y));
					this->outText.push_back(str);
					/*string str = to_string(index);*/
					/*putText(this->dst_color, str, Point(centerP[j].x + 5, centerP[j].y), FONT_HERSHEY_COMPLEX,
						1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/

                    this->grabPoints.push_back(centerP[j]);
                    index++;

                }
				else
				{
                    cv::drawContours(this->dst_color, this->trianContours, j, cv::Scalar(0, 0, 255), 2, 8);//则在待测试图像上画出此轮廓
                    DM_LabelText str(QString::number(similarity_), cv::Point(centerP[j].x + 5, centerP[j].y));
					this->outText.push_back(str);
					/*putText(this->dst_color, to_string(similarity_), Point(centerP[j].x + 5, centerP[j].y), FONT_HERSHEY_COMPLEX,
                        1.0, Scalar(0, 255, 255), 2, CV_AA, false);*/
				}
            }
        }
        this->message += "轮廓匹配完成！\n";
        this->errorID = DM_error_no;
        return this->errorID;//图片加载失败
    }
}
void DM_ContoursMatch::setTemplate(std::vector<cv::Mat> img_)
{
	for (int i = 0;  i < img_.size(); i++)
	{
		this->templateImg.push_back(img_[i].clone());
	}
}
DM_ImgNot::DM_ImgNot(const DM_ImgNot &obj):
    DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
    obj.dst.copyTo(this->dst);
}

DM_ImgNot DM_ImgNot::operator=(const DM_ImgNot &obj)
{
    this->message = obj.message;
    this->processMethod = obj.processMethod;
    this->errorID = obj.errorID;
    obj.dst.copyTo(this->dst);
    return *this;
}

int DM_ImgNot::process(cv::Mat src_)
{
    this->message = "@>>> 图像取反运行状态： ";//重新加载表头，每次运行直接更新数据，不要重复加载。
    if(src_.empty())
    {
        this->message = "图片为空，请先加载图片！\n";
        this->errorID = DM_error_ImageLoadFail;
        return this->errorID;//图片加载失败
    }
    else
    {
        this->dst = ~src_;
        this->message += "图片取反完成！\n";
        this->errorID = DM_error_no;
        return this->errorID;//图片加载失败
    }
}

DM_Morphology::DM_Morphology(DM_ImgProcess_Tag method,cv::Size kenelSize_):
               DM_ImageProcessBase(method, "", DM_error_deafult)
{
    int w,h;
    if(kenelSize_.width % 2 == 0)
    {
        w = kenelSize_.width+1;
    }
    else
    {
        w = kenelSize_.width;
    }

    if(kenelSize_.height % 2 == 0)
    {
        h = kenelSize_.height+1;
    }
    else
    {
        h = kenelSize_.height;
    }
    this->kenelSize = cv::Size(w,h);
}

DM_Morphology::DM_Morphology(const DM_Morphology &obj):
               DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
    this->kenelSize = obj.kenelSize;
    obj.dst.copyTo(this->dst);
}

DM_Morphology DM_Morphology::operator=(const DM_Morphology &obj)
{
    this->message = obj.message;
    this->processMethod = obj.processMethod;
    this->errorID = obj.errorID;

    obj.dst.copyTo(this->dst);
    this->kenelSize = obj.kenelSize;

    return *this;
}

int DM_Morphology::process(cv::Mat src_)
{
    this->message = "@>>> 图像形态学运行状态： ";//重新加载表头，每次运行直接更新数据，不要重复加载。
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,this->kenelSize);
    if(src_.empty())
    {
        this->message = "图片为空，请先加载图片！\n";
        this->errorID = DM_error_ImageLoadFail;
        return this->errorID;//图片加载失败
    }
    //心态学操作
    if(this->processMethod == DM_MORPHOLOGY_DILATE_Tag)//图像膨胀
    {
        cv::morphologyEx(src_,this->dst,cv::MORPH_DILATE,element);
        this->message += "图像膨胀操作完成！\n";
    }
    else if(this->processMethod == DM_MORPHOLOGY_ERODE_Tag)//图像腐蚀
    {
        cv::morphologyEx(src_,this->dst,cv::MORPH_ERODE,element);
        this->message += "图像腐蚀操作完成！\n";
    }
    else if(this->processMethod == DM_MORPHOLOGY_OPEN_Tag)//图像开
    {
        cv::morphologyEx(src_,this->dst,cv::MORPH_OPEN,element);
        this->message += "图像开操作完成！\n";
    }
    else if(this->processMethod == DM_MORPHOLOGY_CLOSE_Tag)//图像闭
    {
        cv::morphologyEx(src_,this->dst,cv::MORPH_CLOSE,element);
        this->message += "图像闭操作完成！\n";
    }
    else if(this->processMethod == DM_MORPHOLOGY_GRADIENT_Tag)//图像形态学梯度
    {
        cv::morphologyEx(src_,this->dst,cv::MORPH_GRADIENT,element);
        this->message += "图像形态学操作完成！\n";
    }
    else if(this->processMethod == DM_MORPHOLOGY_TOPHAT_Tag)//图像顶帽
    {
        cv::morphologyEx(src_,this->dst,cv::MORPH_TOPHAT,element);
        this->message += "图像顶帽操作完成！\n";
    }
    else if(this->processMethod == DM_MORPHOLOGY_BLACKHAT_Tag)//图像黑帽
    {
        cv::morphologyEx(src_,this->dst,cv::MORPH_BLACKHAT,element);
        this->message += "图像黑帽操作完成！\n";
    }
    else
    {
        this->message += "算法选择错误，请重新选择！\n";
    }
    this->errorID = DM_error_no;
    return this->errorID;//图片加载失败
}

DM_Blur::DM_Blur(DM_ImgProcess_Tag method, cv::Size kenelSize_, double sigmaColor_, double sigmaSpace_):
                         DM_ImageProcessBase(method, "", DM_error_deafult)
{
    int w,h;
    if(kenelSize_.width % 2 == 0)
    {
        w = kenelSize_.width+1;
    }
    else
    {
        w = kenelSize_.width;
    }

    if(kenelSize_.height % 2 == 0)
    {
        h = kenelSize_.height+1;
    }
    else
    {
        h = kenelSize_.height;
    }
    this->kenelSize = cv::Size(w,h);
    this->sigmaColor = sigmaColor_;
    this->sigmaSpace = sigmaSpace_;
}

DM_Blur::DM_Blur(const DM_Blur &obj):
                 DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
    this->kenelSize = obj.kenelSize;
    obj.dst.copyTo(this->dst);

    this->sigmaColor = obj.sigmaColor;
    this->sigmaSpace = obj.sigmaSpace;
}

DM_Blur DM_Blur::operator=(const DM_Blur &obj)
{
    this->message = obj.message;
    this->processMethod = obj.processMethod;
    this->errorID = obj.errorID;

    obj.dst.copyTo(this->dst);
    this->kenelSize = obj.kenelSize;
    this->sigmaColor = obj.sigmaColor;
    this->sigmaSpace = obj.sigmaSpace;

    return *this;
}

int DM_Blur::process(cv::Mat src_)
{
    this->message = "@>>> 均值滤波运行状态： ";//重新加载表头，每次运行直接更新数据，不要重复加载。
    if(src_.empty())
    {
        this->message = "图片为空，请先加载图片！\n";
        this->errorID = DM_error_ImageLoadFail;
        return this->errorID;//图片加载失败
    }
    //滤波
    if(this->processMethod == DM_MEANBLUR_Tag)//均值滤波
    {
        blur(src_,this->dst,this->kenelSize);
        this->message += "均值滤波完成！\n";
    }
    //高斯滤波
    else if(this->processMethod == DM_GAUSSIANBLUR_Tag)
    {
        GaussianBlur(src_,this->dst,this->kenelSize,0);
        this->message += "高斯滤波完成！\n";
    }
    //中值滤波
    else if(this->processMethod == DM_MEDIANDMFILTER_Tag)
    {
        int kenelS = this->kenelSize.width > this->kenelSize.height?
                    this->kenelSize.width : this->kenelSize.height;
        medianBlur(src_,this->dst,kenelS);
        this->message += "中值滤波完成！\n";
    }
    //双边滤波
    else if(this->processMethod == DM_BILATERALFILTER_Tag)
    {
        bilateralFilter(src_,this->dst, -1, this->sigmaColor, this->sigmaSpace);
        this->message += "双边滤波完成！\n";
    }
    else
    {
        this->message += "算法选择错误，请重新选择！\n";
    }
    this->errorID = DM_error_no;
    return this->errorID;//图片加载失败
}

DM_FindCircle::DM_FindCircle(double binaryzationThreshold_, double countThreshold_, int minRadius_ /*= 0*/, 
							 int maxRadius_ /*= 0*/, double percent_ /*= 0*/, double deviation_ /*= 10*/):
							 DM_ImageProcessBase(DM_FINDCIRCLE_Tag, "", DM_error_deafult)
{
	this->binaryzationThreshold = binaryzationThreshold_;//二值化阈值，默认为0，则采用OTSU自动查找
	this->countThreshold = countThreshold_;//构成圆的像素点的阈值，默认为0，则所有的轮廓的全部拟合圆
	this->percent = percent_;//拟合度，找到的圆和拟合的轮廓边沿的重合的基本重合的点的百分比
	this->deviation = deviation_;//拟合的轮廓和边沿点的允许的偏差
	this-> minRadius = minRadius_;//待检测圆的最小半径；
	this-> maxRadius = maxRadius_;//待检测圆的最大半径

	this->circles.clear();//检测出来的圆①和②个元素构成圆的圆心，③为圆的半径
	this->outText.clear();
}
DM_FindCircle::DM_FindCircle(const DM_FindCircle &obj) :DM_ImageProcessBase(obj.processMethod, obj.message, obj.errorID)
{
	this->binaryzationThreshold = obj.binaryzationThreshold;//二值化阈值，默认为0，则采用OTSU自动查找
	this->countThreshold = obj.countThreshold;//构成圆的像素点的阈值，默认为0，则所有的轮廓的全部拟合圆
	this->percent = obj.percent;//拟合度，找到的圆和拟合的轮廓边沿的重合的基本重合的点的百分比
	this->deviation = obj.deviation;//拟合的轮廓和边沿点的允许的偏差
	this->minRadius = obj.minRadius;//待检测圆的最小半径；
	this->maxRadius = obj.maxRadius;//待检测圆的最大半径
	this->circles = obj.circles;//检测出来的圆①和②个元素构成圆的圆心，③为圆的半径

	this->dst = cv::Mat();
	this->dst_color = cv::Mat();
	this->outText = obj.outText;

}
DM_FindCircle DM_FindCircle::operator=(const DM_FindCircle &obj)
{
	this->binaryzationThreshold = obj.binaryzationThreshold;//二值化阈值，默认为0，则采用OTSU自动查找
	this->countThreshold = obj.countThreshold;//构成圆的像素点的阈值，默认为0，则所有的轮廓的全部拟合圆
	this->percent = obj.percent;//拟合度，找到的圆和拟合的轮廓边沿的重合的基本重合的点的百分比
	this->deviation = obj.deviation;//拟合的轮廓和边沿点的允许的偏差
	this->minRadius = obj.minRadius;//待检测圆的最小半径；
	this->maxRadius = obj.maxRadius;//待检测圆的最大半径
	this->circles = obj.circles;//检测出来的圆①和②个元素构成圆的圆心，③为圆的半径

	obj.dst.copyTo(this->dst);
	obj.dst_color.copyTo(this->dst_color);
	this->outText = obj.outText;
	return *this;
}
bool compara()
{
	return true;
}
int DM_FindCircle::process(cv::Mat src_ /*= cv::Mat()*/)
{
	this->message = "@>>>查找圆算法运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();
	this->circles.clear();

	if (src_.empty())
	{
		this->message += " 待处理的图片为空，请重新加载！\n";
		this->errorID = DM_error_ImageLoadFail;
		return DM_error_ImageLoadFail;
	}
	cv::Mat src;
	if (src_.channels() > 1)
	{

        cv::cvtColor(src_, src, cv::COLOR_BGR2GRAY);
        cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);
	}
	else
	{
		src_.copyTo(src);
		src_.copyTo(this->dst);
	}
	if (this->binaryzationThreshold <= 0)//如果阈值为0则采用自适应二值化
	{
		threshold(src, src, 100, 255, CV_THRESH_OTSU);//确保黑中找白
	}
	else
	{
		cv::threshold(src, src, this->binaryzationThreshold, 255, CV_THRESH_BINARY);
	}
	//初始化dstColor
    cv::cvtColor(src, this->dst_color, cv::COLOR_GRAY2BGR);
	//查找连通域
    cv::Mat labels;
    int n_comps = cv::connectedComponents(src, labels, 8, CV_16U);

	//draw
	int rows = src.rows;
	int cols = src.cols;
    cv::Mat src_color;// = Mat::zeros(imageShold.size(), CV_8UC3);
	src_color.create(rows, cols, CV_8UC3);
    src_color = cv::Scalar::all(0);

	if (n_comps <= 0)
	{
		this->message += "没有招到轮廓，请修正相关参数或者更换图片！\n";
		this->errorID = DM_error_calculate;
		return DM_error_ImageLoadFail;
	}
    std::vector<std::vector<cv::Point>>labelsPts(n_comps-1);
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			int label = labels.at<__int16>(x, y);//注意labels是CV_16U类型
			if (label == 0)
			{
				/*src_color.at<Vec3b>(x, y) = Vec3b(255, 255, 255);*/
				continue;
			}
			//src_color.at<Vec3b>(x, y)[0] = (label * 10 * 10 * 10) % 255;
			//src_color.at<Vec3b>(x, y)[1] = (label * 10 * 10) % 255;
			//src_color.at<Vec3b>(x, y)[2] = (label * 10) % 255;
            labelsPts[label-1].push_back(cv::Point(y, x));
		}
	}
    std::vector<std::vector<cv::Point>> contours;//返回找到的轮廓
	for (int i = 0; i < labelsPts.size(); i++)
	{ 
        cv::Rect labelsRect = cv::boundingRect(labelsPts[i]);
		//for (int k = 0; k < labelsPts[i].size(); k++)
		//{
		//	this->dst_color.at<Vec3b>(labelsPts[i][k].y, labelsPts[i][k].x)[0] = 0;
		//	this->dst_color.at<Vec3b>(labelsPts[i][k].y, labelsPts[i][k].x)[1] = 255;
		//	this->dst_color.at<Vec3b>(labelsPts[i][k].y, labelsPts[i][k].x)[2] = 255;
		//}
		//如果外接矩形和图片大小相等，认为是图像外框，不用检测轮廓
		if (labelsRect.width + 3  >= this->dst_color.cols ||
			labelsRect.height + 3 >= this->dst_color.rows )
		{
			continue;
		}
        std::vector<std::vector<cv::Point>> contours_;//返回找到的轮廓
        std::vector<double> contourAreas;//返回找到的轮廓对应的面积
        std::vector<cv::Vec4i> hierarchy; //轮廓索引编号
        int mode = cv::RETR_EXTERNAL;
        int method = cv::CHAIN_APPROX_NONE;
        cv::findContours(src(labelsRect), contours_, hierarchy, mode, method,cv::Point(labelsRect.x, labelsRect.y));
		
	/*	cv::rectangle(this->dst_color, labelsRect, cv::Scalar(0, 255, 0), 1);
		drawContours(this->dst_color, contours_, -1, Scalar(255, 0, 0), 1);*/
		for (int j = 0; j < contours_.size(); j++)
		{
			contours.push_back(contours_[j]);
		}
	}

	//查找轮廓
    std::vector<std::vector<cv::Point>> circleContours;//有效的圆轮廓
	if (contours.empty())
	{
		this->message += " 没有找到轮廓，请调整参数或者重新加载待测图片";
	}
	else
	{
		for (int i = 0; i < contours.size(); i++)
		{
			DM_Circle circleTemp(contours[i]);
			if (!circleTemp.isValid())
			{
				continue;
			}
			double percentTemp;
			this->circlesEdgeScore(contours[i], circleTemp, percentTemp);
			bool res1 = false, res2 = false, res3 = false;
			//判定半径
			if ((this->minRadius >= 0 &&
				this->maxRadius > 0 &&
				this->minRadius <= circleTemp.radius &&
				this->maxRadius >= circleTemp.radius)||
				(this->minRadius <= 0 &&
				this->maxRadius <= 0))
			{
					res1 = true;
			}
			//判定评分
			if (percentTemp >= this->percent)
			{
				res2 = true;
			}
			//判定边沿点
			if (this->countThreshold <= contours[i].size())
			{
				res3 = true;
			}

			if (res3 && res2 && res1)
			{
				this->circles.push_back(circleTemp);
				
                cv::drawContours(this->dst_color, contours, i, cv::Scalar(255, 0, 0), 1);
                cv::circle(this->dst_color, circleTemp.center.toPoint(), circleTemp.radius, cv::Scalar(0, 255, 0), 2);
                cv::circle(this->dst_color, circleTemp.center.toPoint(), 1, cv::Scalar(0, 0, 255), -1);
				DM_LabelText str("R:" +
								 QString::number(int(circleTemp.radius)) + "-P:" + 
								 QString::number(int(percentTemp)), 
                                cv::Point(circleTemp.center.x + 5, circleTemp.center.y));
				this->outText.push_back(str);
				/*string str = to_string(int(this->circles.size()))+"/R:" + to_string(int(circleTemp.radius)) + "/P:" + to_string(int(percentTemp));
				putText(this->dst_color, str, Point(circleTemp.center.x + 5, circleTemp.center.y), FONT_HERSHEY_COMPLEX,
					1.0, Scalar(0, 255, 255), 1, CV_AA, false);*/
			}
		}
	}
	//冒泡排序
	DM_Circle circlesTemp;//
	DM_LabelText outTextTemp;
	for (int i= 0; i < this->circles.size(); i++)
	{
		for (int j = 0; j <  this->circles.size()-i-1; j++)
		{
			if (this->circles[j].center.y  > this->circles[j+1].center.y + this->circles[j+1].radius)
			{
				circlesTemp = this->circles[j];
				this->circles[j] = this->circles[j + 1];
				this->circles[j + 1] = circlesTemp;

				outTextTemp = this->outText[j];
				this->outText[j] = this->outText[j+1];
				this->outText[j + 1] = outTextTemp;
			}
			else if (abs(this->circles[j].center.y - this->circles[j+1].center.y) < this->circles[j].radius &&
				     abs(this->circles[j+1].center.y - this->circles[j].center.y) < this->circles[j + 1].radius &&
				     this->circles[j].center.x > this->circles[j+1].center.x)
			{
				circlesTemp = this->circles[j];
				this->circles[j] = this->circles[j + 1];
				this->circles[j + 1] = circlesTemp;

				outTextTemp = this->outText[j];
				this->outText[j] = this->outText[j + 1];
				this->outText[j + 1] = outTextTemp;
			}
		}
	}
	for (int i = 0; i < this->outText.size(); i++)
	{
		this->outText[i].text = "[" + QString::number(i + 1) + "]" + this->outText[i].text;
	}

	//输出关键信息
	if (this->circles.empty())
	{
        this->message += " 没有找到圆!\n";
	}
	else
	{
        this->message += " 运算完成!\n";
	}
	this->errorID = DM_error_no;
	return DM_error_no;
}
void  DM_FindCircle::circlesEdgeScore(std::vector<std::vector<cv::Point>> contours_, std::vector<DM_Circle> &circles_, std::vector<double> &scoreList_)
{
	for (int i = 0; i < contours_.size(); i++)
	{
		int count = 0;
		for (int j = 0; j < contours_[i].size(); j++)
		{
			double dis = circles_[i].center.dis_P2P(DM_Point(contours_[i][j]));
			if (abs(dis - circles_[i].radius) < this->deviation)
			{
				count++;
			}
		}
		scoreList_.push_back(count / (2 *CV_PI * circles_[i].radius));
	}
}
void DM_FindCircle::circlesEdgeScore(std::vector<cv::Point> contours_, DM_Circle &circles_, double &scoreList_)
{
	if (contours_.empty() || !circles_.isValid())
	{
		scoreList_ = 0;
	}
	else
	{
		int count = 0;
		for (int j = 0; j < contours_.size(); j++)
		{
			double dis = circles_.center.dis_P2P(DM_Point(contours_[j]));
			if (abs(dis - circles_.radius) < this->deviation)
			{
				count++;
			}
		}
		double p = double(count) / (contours_.size());
		scoreList_ = p * 100;//百分比
	}
	
}
std::vector<cv::Point2f> DM_FindCircle::getCircleCenters()
{
    std::vector<cv::Point2f>centerPoints;
	for (int i = 0; i < this->circles.size(); i++)
	{
		centerPoints.push_back(this->circles[i].center.toPoint2f());
	}
	return centerPoints;
}
DM_FindCircle_Hand::DM_FindCircle_Hand(DM_Ring circlrROI_) :
	DM_ImageProcessBase(DM_FINDCIRCLE_HAND_Tag, "", DM_error_deafult)
{
	this->circleROI = circlrROI_;
}
DM_FindCircle_Hand& DM_FindCircle_Hand::operator=(const DM_FindCircle_Hand &obj)
{
	this->circle = obj.circle;
	this->circleROI = obj.circleROI;
	obj.dst.copyTo(this->dst);
	obj.dst_color.copyTo(this->dst_color);
	this->outText = obj.outText;

	//初始化父类的相关参数
	this->processMethod = obj.processMethod;//调用预处理方案
	this->message = obj.message;//输出运行信息
	this->errorID = obj.errorID;

	return *this;
}

int DM_FindCircle_Hand::process(cv::Mat src_ /*= cv::Mat()*/)
{
	this->message = "@>>>查找圆算法运行状态: ";//重新加载表头，每次运行直接更新数据，不要重复加载。
	this->outText.clear();

	if (src_.empty())
	{
		this->message += " 待处理的图片为空，请重新加载！\n";
		this->errorID = DM_error_ImageLoadFail;
		return DM_error_ImageLoadFail;
	}
	cv::Mat src;
	if (src_.channels() > 1)
	{

		cv::cvtColor(src_, src, cv::COLOR_BGR2GRAY);
		cv::cvtColor(src_, this->dst, cv::COLOR_BGR2GRAY);
	}
	else
	{
		src_.copyTo(src);
		src_.copyTo(this->dst);
	}
	//初始化dstColor
	cv::cvtColor(src, this->dst_color, cv::COLOR_GRAY2BGR);

	//还需要将拟合的圆画出来
	this->circle.generate(src, this->circleROI);//获取拟合的圆
	//临时显示当前框选的结果
	if (this->circle.isValid())//拟合成功
	{
		cv::circle(this->dst_color, this->circle.center.toPoint(), this->circle.radius, cv::Scalar(0, 255, 0), 2);
		cv::circle(this->dst_color, this->circle.center.toPoint(), 1, cv::Scalar(0, 0, 255), -1);
		this->message += " 运算完成!\n";
		this->errorID = DM_error_no;
	}
	else
	{
		this->message += " 没有找到圆!\n";
		this->errorID = DM_error_calculate;
	}
	return this->errorID;
}

