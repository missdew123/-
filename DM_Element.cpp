#include "DM_Element.h"


using namespace cv;
using namespace std;
#define PC_Debug //启用调试模式

bool isNaN(double x) { return x != x; }
bool isInf(double x) { return !isNaN(x) &&  isNaN(x - x); }//是否为无穷大

QString DM_MeasureElement::getType()
{
	switch (this->type)
	{
		case Point_ELMT:
		return QStringLiteral("点");
		case Line_ELMT:
		return QStringLiteral("线");
		case Circle_ELMT:
		return QStringLiteral("圆");
		case Arc_ELMT:
		return QStringLiteral("圆弧");
		case Thread_ELMT:
		return QStringLiteral("螺纹");
		case RotatedRect_ELMT:
		return QStringLiteral("旋转矩形");
		default:
		return QStringLiteral("默认元素");
	}
}

//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点
//参数(点1，点2，出参-细分出来的点)
//返回值：大于0，反馈点的个数； 小于0，两点重合，细分失败
//_____________________________________________________________________________________________________________
int  DM_MeasureElement::subDivide(const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	out_pts.clear();
	do
	{
		out_pts.push_back(cv::Point(x0, y0));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}
int  DM_MeasureElement::subDivide(const DM_Point& p1, const DM_Point& p2, std::vector<cv::Point>& out_pts)
{
	return subDivide(p1.toPoint(), p2.toPoint(), out_pts);
}
//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点，并从img上采样
//参数(图像img，点1，点2，出参-细分出来的点)
//返回值：
//     a)、大于0，反馈点的个数；
//     b)、-1，两点重合，细分失败
//     c)、-2，图像为空 不可采样
//_____________________________________________________________________________________________________________
int DM_MeasureElement::subDivide(const cv::Mat& img, const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point3i>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	if (img.empty()) return -2;//图像为空 不可采样

	out_pts.clear();

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	do
	{
		out_pts.push_back(cv::Point3i(x0, y0, img.at<uchar>(y0, x0)));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}
int DM_MeasureElement::subDivide(const cv::Mat& img, const DM_Point& p1, const DM_Point& p2, std::vector<cv::Point3i>& out_pts)
{
	return subDivide(img, p1.toPoint(), p2.toPoint(), out_pts);
}

//****************************************************DM_Point类*************************************************//
bool DM_Point::isInMat(const Mat& mat) const
{
	if (mat.empty()) return false;
	else if (0.0 <= x && x<double(mat.cols) && 0.0 <= y && y<double(mat.rows)) return true;
	else return false;
}
bool DM_Point::isInRect(const Rect& rect) const
{
	Point P = toPoint();
	if (rect.x <= P.x && P.x < (rect.x + rect.width) && rect.y <= P.y && P.y < (rect.y + rect.height)) return true;
	else return false;
}
bool DM_Point:: operator == (const DM_Point &p)
{
	if (abs(this->x - p.x)<= DM_eps && abs(this->y - p.y)<= DM_eps)
	{
		return true;
	}
	else
	{
		return false;
	}
}
DM_Point& DM_Point::operator=(const DM_Point &p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}
bool DM_Point:: operator != (const DM_Point &p)
{
	return !(this->operator==(p));
}
double DM_Point::dis_P2P(DM_Point b)
{
	double L = sqrt((this->x - b.x)*(this->x - b.x) + (this->y - b.y)*(this->y - b.y));
	return L;
}
//返回值：返回旋转之后的点
DM_Point DM_Point::getRotatePoint(DM_Point centerP, double angle)
{
	DM_Point dstP;
	dstP.x = (this->x - centerP.x)*cos(angle) - (this->y - centerP.y)*sin(angle) + centerP.x;
	dstP.y = (this->y - centerP.y)*cos(angle) + (this->x - centerP.x)*sin(angle) + centerP.y;
	return dstP;
}
//计算从this向量到vecor向量的旋转角度（弧度）
double DM_Point::getRotateAngle(DM_Point vector)
{
	DM_Point vectorA = *this;
	DM_Point vectorB = vector;
	double  dot = vectorA.x * vectorB.x + vectorA.y * vectorB.y;//两向量的点乘
	double LA = vectorA.dis_P2P(DM_Point(0, 0));
	double LB = vectorB.dis_P2P(DM_Point(0, 0));
	dot = dot / (LA*LB);

	double angle = acos(dot);
	double cross = vectorA.x * vectorB.y - vectorB.x * vectorA.y;
	if (cross < 0)
	{
		angle = 2 * DM_PI - angle;
	}

	return angle;
}
//==========================================================================================================
//函数名称及作用：计算距离当前点指定向量方向vector、指定距离dis的点
//返回值：计算成功返回true 计算失败false
//==========================================================================================================
bool  DM_Point::getPointOfSpecifiedDis(const DM_Point &vector, DM_Point &pt, const double dis)const
{
	DM_Point pt1 = DM_Point(this->x+vector.x,this->y + vector.y);
	DM_Point pt2 = *this;

	if (pt1 == pt2)
	{
		return false;
	}
	if (pt1.x == pt2.x)//则该线段与X轴垂直
	{
		float k = (pt1.y - pt2.y) / abs(pt1.y - pt2.y);
		k = k * dis;
		pt.x = pt2.x;
		pt.y = pt2.y + k;
	}
	else if (pt1.y == pt2.y)//则该线段与Y轴垂直
	{
		float k = (pt1.x - pt2.x) / abs(pt1.x - pt2.x);
		k = k * dis;
		pt.x = pt2.x + k;
		pt.y = pt2.y;
	}
	else
	{
		double L = pt1.dis_P2P(pt2);
		double cx = pt1.x - pt2.x;
		double cy = pt1.y - pt2.y;
		double cx_k = (cx*dis) / L;
		double cy_k = (cy*dis) / L;

		pt.x = pt2.x + cx_k;
		pt.y = pt2.y + cy_k;
	}
	return true;
}
DM_Point DM_Point::getMidPoint(DM_Point P1)
{
	return DM_Point((this->x+P1.x)*0.5,(this->y+P1.y)*0.5);
}


//****************************************************DM_Point类*************************************************//
DM_Line::DM_Line()
{
	this->A = 0;
	this->B = 0;
	this->IsVertical = false;
	this->k = 0;
	this->m = 0;//y轴截距
	this->angle = 0;
	this->IsValid = false;
	this->type = Line_ELMT;
}
DM_Line::DM_Line(const double& a, const double& b, const double& c)
{
	this->A = a;
	this->B = b;
	if (0.0 == this->A && 0.0 == this->B)
	{
		this->IsValid = false;
		return;
	}

	this->C = c;
	if (0.0 == this->B)//没有斜率==斜率无穷大
	{
		this->IsVertical = true;
		this->m = -C / A;//x轴截距
		this->angle = DM_PI_2;
	}
	else
	{
		this->IsVertical = false;
		this->k = -A / B;
		this->m = -C / B;//y轴截距
		this->angle = atan(k);
	}
	this->IsValid = true;
	this->type = Line_ELMT;
}
DM_Line::DM_Line(const double& k, const double& m)
{
	if (!isInf(k))//k为无穷大
	{
		this->A = k;
		this->B = -1.0;
		this->C = m;
		this->k = k;
		this->m = m;//y轴截距
		this->angle = atan(k);
		this->IsValid = true;
		this->IsVertical = false;
		this->type = Line_ELMT;
	}
	else
	{
		this->IsValid = false;
		this->IsVertical = true;
	}
}
DM_Line::DM_Line(const DM_Point& p, const double& k)
{
	this->type = Line_ELMT;
	//	例如 y - y1 = k(x - x1)
	//	即kx - y + kx1 + y1 = 0
	if (isInf(k))//k为无穷大
	{
		this->P1 = DM_Point(p.x, 0.0);
		this->P2 = p;
		this->IsValid = getLineParam();//初始化
	}
	else
	{
		//DM_Line L(k, -1.0, p.y-k*p.x);
		DM_Line L(k, p.y - k * p.x);
		this->IsValid = L.isValid();
		this->IsVertical = L.isVertical();
		if (!this->IsValid) return;
		this->A = L.A;
		this->B = L.B;
		this->C = L.C;
		this->k = L.k;
		this->m = L.m;
		this->angle = L.angle;
		this->P1 = DM_Point(0.0, this->m);
		this->P2 = p;
	}
}
DM_Line::DM_Line(const DM_Point& p1, const DM_Point& p2)
{
	this->P1 = p1;
	this->P2 = p2;
	this->IsValid = getLineParam();//初始化
	this->type = Line_ELMT;
}
//该构造函数主要为了与opencv混合使用（该构造函数不能准确计算P1和P2端点）
DM_Line::DM_Line(cv::Vec4d line_para)
{
	if (line_para[0] == 0 && line_para[1] == 0)
	{
		*this = DM_Line();
	}
	else if (line_para[0] == 0)//斜率不存在的情况
	{
		this->A = -1;
		this->B = 0;
		this->C = line_para[2];
		this->setLine(this->A, this->B, this->C);
	}
	else
	{
		this->A = line_para[1] / line_para[0];
		this->B = -1.0;
		this->C = line_para[3] - this->A * line_para[2];
		this->setLine(this->A, this->B, this->C);
	}
	//端点P1与P2计算不准确
	P1 = DM_Point(line_para[2], line_para[3]);
	this->type = Line_ELMT;
}


DM_Line::DM_Line(const DM_Line &obj)
{
	this->A = obj.A;
	this->B = obj.B;
	this->C = obj.C;
	this->k = obj.k;
	this->m = obj.m;
	this->angle = obj.angle;
	this->P1 = obj.P1;
	this->P2 = obj.P2;
	this->IsVertical = obj.IsVertical;
	this->IsValid = obj.IsValid;
	this->type = Line_ELMT;
}
DM_Line& DM_Line::operator=(const DM_Line &obj)
{
	this->A = obj.A;
	this->B = obj.B;
	this->C = obj.C;
	this->k = obj.k;
	this->m = obj.m;
	this->angle = obj.angle;
	this->P1 = obj.P1;
	this->P2 = obj.P2;
	this->IsVertical = obj.IsVertical;
	this->IsValid = obj.IsValid;
	this->type = obj.type;
	return *this;
}
bool DM_Line::operator==(const DM_Line &obj)
{
	//如果直线的角度为90°则只需要比较m；
	if ( abs(this->m - obj.m)       < DM_eps &&
		 abs(this->angle - DM_PI_2) < DM_eps &&
		 (this->IsValid == true))
	{
		return true;
	}
	//如果直线的角度不为90°则只需要比较m；
	else if (abs(this->k - obj.k)       < DM_eps &&
			 abs(this->m - obj.m)       < DM_eps &&
			 abs(this->angle - DM_PI_2) > DM_eps &&
			 (this->IsValid == true))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool DM_Line::operator!=(const DM_Line &obj)
{
	return !(this->operator==(obj));
}
//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点
//参数(点1，点2，出参-细分出来的点)
//返回值：大于0，反馈点的个数； 小于0，两点重合，细分失败
//_____________________________________________________________________________________________________________
/*int DM_Line::subDivide(const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	out_pts.clear();
	do
	{
		out_pts.push_back(cv::Point(x0, y0));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}
//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点，并从img上采样
//参数(图像img，点1，点2，出参-细分出来的点)
//返回值：
//     a)、大于0，反馈点的个数；
//     b)、-1，两点重合，细分失败
//     c)、-2，图像为空 不可采样
//_____________________________________________________________________________________________________________
int DM_Line::subDivide(cv::Mat& img, const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point3i>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	if (img.empty()) return -2;//图像为空 不可采样

	out_pts.clear();

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	do
	{
		out_pts.push_back(cv::Point3i(x0, y0, img.at<uchar>(y0, x0)));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}*/
//_____________________________________________________________________________________________________________
//函数名称及作用：获取指定区域内，指定方向上的梯度点
//参数：
//     img：输入图像；
//     roi: 划定的区域；
//     edge_pts: 边界上的点；
//     int isH2L:边沿点的极性问题，0： 从低灰度值到高灰度值 1：从高灰度值到低灰度值 2：不分极性
//返回值：
//     a)、大于0，反馈点的个数；
//     b)、-1，图像为空
//     c)、-2，roi不在图像中
//     c)、-3，roi尺寸过小
//_____________________________________________________________________________________________________________
/*
int DM_Line::getRotatedRectEdgePoints(cv::Mat& img, DM_RotatedRect roi, std::vector<cv::Point>& edge_pts, int isH2L)//获取斜方程内梯度方向的点
{
	if (img.empty()) return -1;//图像为空

	if (roi.isInMat(img)) return -2;//区域不在图像中
	if (roi.size.width< 5.f || roi.size.height < 5.f) return -3;//roi尺寸过小

	edge_pts.clear();

	std::vector<DM_Point> Vf = roi.getVertices();
	cv::Point Vertices[] = { Vf[0].toPoint(), Vf[1].toPoint(), Vf[2].toPoint(), Vf[3].toPoint() };//四舍五入

	vector<cv::Point> OutPts1, OutPts2;
	subDivide(Vertices[1], Vertices[2], OutPts2);
	subDivide(Vertices[0], Vertices[3], OutPts1);


	size_t Num = min(OutPts1.size(), OutPts2.size());
	std::vector<std::vector<cv::Point3i>> RawData;
	for (size_t i = 0; i < Num; ++i)
	{
		std::vector<cv::Point3i> temp_raw_data;
		subDivide(img, OutPts1[i], OutPts2[i], temp_raw_data);
		RawData.push_back(temp_raw_data);
	}
	//处理每个rawdata，计算中心差分
	std::vector<std::vector<int>> CentralDiffs;//存储所有的中心差分
	for (size_t i = 0; i < RawData.size(); ++i)
	{
		std::vector<int> temp_central_diff;
		temp_central_diff.push_back(0);//填充第0个
		for (size_t j = 1; j < RawData[i].size() - 1; ++j)
		{
			temp_central_diff.push_back((RawData[i][j + 1].z - RawData[i][j - 1].z));//
		}
		CentralDiffs.push_back(temp_central_diff);

	}
	//找差分最大值处
	for (size_t i = 0; i < CentralDiffs.size(); ++i)
	{
		size_t index_maxval = 0;
		size_t index_minval = 0;
		for (size_t j = 1; j < CentralDiffs[i].size(); ++j)//由于是中心差分，不看第0个
		{
			if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
				index_maxval = j;
			if (CentralDiffs[i][index_minval] > CentralDiffs[i][j])
				index_minval = j;
		}

		if (isH2L == 1)//查找下降沿
		{
			if (CentralDiffs[i][index_minval] <  5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = RawData[i][index_minval];
				edge_pts.push_back(Point(p_temp.x, p_temp.y));
			}
		}
		else if (isH2L == 0)//查找上升沿
		{
			if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = RawData[i][index_maxval];
				edge_pts.push_back(Point(p_temp.x, p_temp.y));
			}
		}
		else//查找跳边沿
		{
			if (CentralDiffs[i][index_maxval] > abs(CentralDiffs[i][index_minval]))
			{
				if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = RawData[i][index_maxval];
					edge_pts.push_back(Point(p_temp.x, p_temp.y));
				}
			}
			else
			{
				if (abs(CentralDiffs[i][index_minval]) > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = RawData[i][index_minval];
					edge_pts.push_back(Point(p_temp.x, p_temp.y));
				}
			}

		}

	}

#ifdef PC_Debug
	Mat srcBGR(img.size(), CV_8UC3);
	if (img.channels() != 1)
	{
		img.copyTo(srcBGR);
	}
	else
	{
		cvtColor(img, srcBGR, COLOR_GRAY2BGR);
	}
	for (int i = 0; i < edge_pts.size(); i++)
	{
		circle(srcBGR, edge_pts[i], 1, Scalar(0, 0, 255), -1);
	}


#endif
	return edge_pts.size();
}
*/

DM_Line DM_Line::generate(cv::Mat& img, DM_RotatedRect roi, int distType, int max_iter, int isH2L)
{
	if (img.empty()) return  *this = DM_Line();//图像为空
	if (!roi.isInMat(img)) return *this = DM_Line();//区域不在图像中
	if (roi.size.width < 5.f || roi.size.height < 5.f) return *this = DM_Line();//roi尺寸过小

	std::vector<DM_Point> edge_pts;
	roi.getRotatedRectEdgePoints(img, edge_pts, isH2L);//获取斜方程内梯度方向的点
	vector<DM_Point> pts;
//	DM_Line LL;
//	LineRANSAC(edge_pts, pts, LL);//排除干扰点，并且可以拟合出一条直线
	pts = edge_pts;//有上面的滤波，注释此行
#ifdef PC_Debug
	Mat srcBGR(img.size(), CV_8UC3);
	if (img.channels() != 1)
	{
		img.copyTo(srcBGR);
	}
	else
	{
		cvtColor(img, srcBGR, COLOR_GRAY2BGR);
	}
	for (int i = 0; i < pts.size(); i++)
	{
		circle(srcBGR, pts[i].toPoint(), 1, Scalar(255, 0, 0), 1);
	}

	std::vector<DM_Point> roiPoints = roi.getVertices();
	cv::line(srcBGR, roiPoints[0].toPoint(), roiPoints[1].toPoint(), Scalar(255, 255, 0), 1, CV_AA);
	cv::line(srcBGR, roiPoints[1].toPoint(), roiPoints[2].toPoint(), Scalar(255, 255, 0), 1, CV_AA);
	cv::line(srcBGR, roiPoints[2].toPoint(), roiPoints[3].toPoint(), Scalar(255, 255, 0), 1, CV_AA);
	cv::line(srcBGR, roiPoints[3].toPoint(), roiPoints[0].toPoint(), Scalar(255, 255, 0), 1, CV_AA);
#endif

	this->fit_Smart(pts, distType, max_iter);//精细化直线拟合

#ifdef PC_Debug
	cv::line(srcBGR, this->P1.toPoint(), this->P2.toPoint(), Scalar(0, 255, 255), 1);
#endif

	return *this;
}
DM_Line DM_Line::getPerpendicular(const DM_Point& p) const
{
	if (IsValid)
	{
		if (IsVertical)//自身没斜率  垂线斜率为零
			return DM_Line(p, 0.0);
		else if (0.0 == k)//自身斜率为零   垂线斜率为无穷大
		{
			double Perpendicular_K = 1.0;
			Perpendicular_K /= k;
			return DM_Line(p, Perpendicular_K);
		}
		else
			return DM_Line(p, -1.0 / k);
	}
	else
	{
		return DM_Line();
	}
}
bool DM_Line::getPerpendicularPoint(const DM_Point &p, DM_Point &crossPoint)
{
	if (this->isValid())
	{
		DM_Line perpendicularLine = this->getPerpendicular(p);
		if (perpendicularLine.isValid())
		{
			return  this->getCrossPoint(perpendicularLine, crossPoint);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}
//=====================================================================
//函数功能：获取两条线的角平分线
//函数参数说明：
// @line1:输入的直线
// @isSamllAngle:需要求角平分线的类型，
//  =>true: 求两直线相交的角度较小的那个角( 0°- 90°)的角平分线
//  =>false:求两直线相交的角度较小的那个角(90°-180°)的角平分线
//返回值说明：返回角分线线
//特殊说明：
// 1）两条直线是同一条直线则，返回this；
// 2）两条直线平行，则返回两条平行线的中线
// 3）量条直线成90度，这时需要主要，有可能返回来的线不是你期望的那条，特点如下：
//    a)如果两条直线的交点到两条直线的端点相等，则返回返回的直线是交点和两条直线的
//      第一个端点P1构成角平分线
//    b)如果两条直线的交点到两条直线的端点不相等，则返回返回的直线是交点和两条直线
//      中与交点相交最远的那个点构成角平分线
//=====================================================================
DM_Line DM_Line::getBisector(DM_Line &line1,bool isSmallAngle)
{

	DM_Line outLine = DM_Line();
	if (!this->IsValid || !line1.IsValid)
	{
		return outLine;
	}
	//如果两条直线重合，则返回其中一条直线
	if (this->operator==(line1))
	{
		return *this;
	}
	else if (abs(this->angle - line1.angle) < DM_eps)//两条直线的旋转角度一样，则必然平行
	{
		if (this->B == 0)//该直线和Y轴平行
		{
			double x1  = -this->C / this->A;
			double x2 = -line1.C / line1.A;
			double x3 = (x2 + x1)*0.5;
			double cc = x3;
			double aa = -1;
			double bb = 0;
			outLine = DM_Line(aa, bb, cc);
		}
		else
		{
			double mm = (this->m + line1.m) * 0.5;
			outLine = DM_Line(this->k, mm);
		}
	}
	else
	{
		//角平分线的原理是根据几何关系求得。将两条直线当做菱形的两条边，菱形的中心和交点的连线就是角平分线
		DM_Point crossP1;
		this->getCrossPoint(line1, crossP1);
		double L1 = crossP1.dis_P2P(this->P1);
		double L2 = crossP1.dis_P2P(this->P2);
		DM_Point PA = L1 >= L2 ? this->P1 : this->P2;
		double LA = L1 >= L2 ? L1 : L2;
		if (LA == 0)
		{
			return DM_Line();
		}
		DM_Point unitVectorA((PA.x - crossP1.x), (PA.y - crossP1.y));//由交点crossP1与PA组成的向量
		unitVectorA = DM_Point(unitVectorA.x/LA, unitVectorA.y/LA);//单位向量

		L1 = crossP1.dis_P2P(line1.P1);
		L2 = crossP1.dis_P2P(line1.P2);
		DM_Point PB = L1 >= L2 ? line1.P1 : line1.P2;
		double LB = L1 >= L2 ? L1 : L2;
		DM_Point unitVectorB((PB.x - crossP1.x), (PB.y - crossP1.y));//由交点crossP1与PB组成的向量
		unitVectorB = DM_Point(unitVectorB.x / LB, unitVectorB.y / LB);//单位向量
		//为了获取两条直线相交的最小夹角，故求解一下向量的夹角
		double angleA2B = unitVectorA.getRotateAngle(unitVectorB);
		DM_Point unitVectorC;
		if (isSmallAngle)
		{
			if (angleA2B <= 90 || angleA2B >= 270)
			{
				unitVectorC = DM_Point((unitVectorA.x + unitVectorB.x) / 2.0, (unitVectorA.y + unitVectorB.y) / 2.0);//由交点crossP1与PB组成的向量
			}
			else
			{
				unitVectorC = DM_Point((unitVectorA.x - unitVectorB.x) / 2.0, (unitVectorA.y - unitVectorB.y) / 2.0);//由交点crossP1与PB组成的向量
			}
		}
		else
		{
			if (angleA2B <= 90 || angleA2B >= 270)
			{
				unitVectorC = DM_Point((unitVectorA.x - unitVectorB.x) / 2.0, (unitVectorA.y - unitVectorB.y) / 2.0);//由交点crossP1与PB组成的向量
			}
			else
			{
				unitVectorC = DM_Point((unitVectorA.x + unitVectorB.x) / 2.0, (unitVectorA.y + unitVectorB.y) / 2.0);//由交点crossP1与PB组成的向量
			}
		}

		if (unitVectorC.x == 0 && unitVectorC.y == 0)
		{
			return DM_Line();
		}
		else if (unitVectorC.x == 0)//斜率不存在的情况
		{
			double AA = -1;
			double BB = 0;
			double CC = crossP1.x;
			outLine = DM_Line(AA, BB, CC);

		}
		else
		{
			double AA = unitVectorC.y / unitVectorC.x;
			double BB = -1.0;
			double CC = crossP1.y - AA * crossP1.x;
			outLine = DM_Line(AA, BB, CC);
		}
	}

	//计算P1，P2；
	//如果outLine的斜率在-45°到45°之间则计算的坐标以X轴为准
	if (outLine.angle <= DM_PI_4 && outLine.angle >= -DM_PI_4)
	{
		double y1, y2;
		if (abs(this->P1.x - this->P2.x)< DM_eps)
		{
			y1 = outLine.getY(line1.P1.x);
			y2 = outLine.getY(line1.P2.x);
			if (y1 < 0 )
			{
				double x1 = (line1.P1.x + line1.P2.x) / 2.0;
				y1 = outLine.getY(x1);
				outLine.P1 = DM_Point(x1, y1);
				outLine.P2 = DM_Point(line1.P2.x, y2);
			}
			else if (y2 < 0)
			{
				double x2 = (line1.P1.x + line1.P2.x) / 2.0;
				y2 = outLine.getY(x2);
				outLine.P1 = DM_Point(line1.P1.x, y1);
				outLine.P2 = DM_Point(x2, y2);
			}
			else
			{
				outLine.P1 = DM_Point(line1.P1.x, y1);
				outLine.P2 = DM_Point(line1.P2.x, y2);
			}
		}
		else
		{
			y1 = outLine.getY(this->P1.x);
			y2 = outLine.getY(this->P2.x);
			if (y1 < 0)
			{
				double x1 = (this->P1.x + this->P2.x) / 2.0;
				y1 = outLine.getY(x1);
				outLine.P1 = DM_Point(x1, y1);
				outLine.P2 = DM_Point(this->P2.x, y2);
			}
			else if (y2 < 0)
			{
				double x2 = (this->P1.x + this->P2.x) / 2.0;
				y2 = outLine.getY(x2);
				outLine.P1 = DM_Point(this->P1.x, y1);
				outLine.P2 = DM_Point(x2, y2);
			}
			else
			{
				outLine.P1 = DM_Point(this->P1.x, y1);
				outLine.P2 = DM_Point(this->P2.x, y2);
			}
		}
	}
	else
	{
		double x1,x2;
		if (abs(this->P1.y - this->P2.y) < DM_eps)
		{
			x1 = outLine.getX(line1.P1.y);
			x2 = outLine.getX(line1.P2.y);
			if (x1 < 0)
			{
				double y1 = (line1.P1.y + line1.P2.y) / 2.0;
				x1 = outLine.getX(y1);
				outLine.P1 = DM_Point(x1, y1);
				outLine.P2 = DM_Point(x2, line1.P2.y);
			}
			else if (x2 < 0)
			{
				double y2 = (line1.P1.y + line1.P2.y) / 2.0;
				x2 = outLine.getX(y2);
				outLine.P1 = DM_Point(x1, line1.P1.y);
				outLine.P2 = DM_Point(x2, y2);
			}
			else
			{
				outLine.P1 = DM_Point(x1, line1.P1.y);
				outLine.P2 = DM_Point(x2, line1.P2.y);
			}
		}
		else
		{
			x1 = outLine.getX(this->P1.y);
			x2 = outLine.getX(this->P2.y);
			if (x1 < 0)
			{
				double y1 = (this->P1.y + this->P2.y) / 2.0;
				x1 = outLine.getX(y1);
				outLine.P1 = DM_Point(x1, y1);
				outLine.P2 = DM_Point(x2, this->P2.y);
			}
			else if (x2 < 0)
			{
				double y2 = (this->P1.y + this->P2.y) / 2.0;
				x2 = outLine.getX(y2);
				outLine.P1 = DM_Point(x1, this->P1.y);
				outLine.P2 = DM_Point(x2, y2);
			}
			else
			{
				outLine.P1 = DM_Point(x1, this->P1.y);
				outLine.P2 = DM_Point(x2, this->P2.y);
			}
		}
	}
	return outLine;
}
bool DM_Line::getCrossPoint(const DM_Line& line, DM_Point& cross) const
{
	double D = line.A*this->B - this->A*line.B;
	if (0.0 == D)
	{
		cross = DM_Point();
		return false;//平行
	}
	else
	{
		D = 1.0 / D;
		cross = DM_Point((line.B*this->C - this->B*line.C)*D, (line.C*this->A - this->C*line.A)*D);
		return true;
	}
}
//点到线的距离
double DM_Line::dis_P2Line(const  DM_Point & p)
{
	return abs(this->A * p.x + this->B * p.y + this->C) / sqrt(this->A * this->A + this->B * this->B);
}

double DM_Line::dis_P2Line(const DM_Point &p, DM_Line &line_out)
{
	line_out = DM_Line();
	if(!this->isValid())
	{
		return -1.0;//长度为-1 说明获取交点 失败，无法求取距离
	}
	line_out = this->getPerpendicular(p);//获得垂线

	DM_Point crossPoint;
	if(line_out.isValid() && this->getCrossPoint(line_out, crossPoint))
	{
		line_out = DM_Line(p, crossPoint);
		if(line_out.isValid())
		{
			return crossPoint.dis_P2P(p);
		}
		else
		{
			return -1.0;
		}
	}
	else
	{
		return -1.0;
	}
}
//线线距离
double DM_Line::dis_Line2Line(DM_Line line, DM_Line& line_out)
{
	line_out = DM_Line();
	if (!this->isValid() || !line.isValid()) return -1.0;//长度为-1 说明获取交点 失败，无法求取距离
    double L1 = this->P1.dis_P2P(this->P2);
    double L2 = line.P1.dis_P2P(line.P2);
    if(L1 > L2)
    {
        DM_Point Mid = line.getMidPoint();
        DM_Point Cross;
        if (this->getCrossPoint(this->getPerpendicular(Mid), Cross))
        {
            line_out = DM_Line(Mid, Cross);
            return Mid.dis_P2P(Cross);
        }
        else
        {
            return -1;
        }
    }
    else
    {
        DM_Point Mid = this->getMidPoint();
        DM_Point Cross;
        if (line.getCrossPoint(line.getPerpendicular(Mid), Cross))
        {
            line_out = DM_Line(Mid, Cross);
            return Mid.dis_P2P(Cross);
        }
        else
        {
            return -1;
        }

    }
}
//线线夹角
double DM_Line::angle_Line2Line(const DM_Line& line)
{
	if (!this->isValid() || !line.isValid()) return -1.0;
	double CosA = abs(this->A*line.A + this->B*line.B) / (sqrt(pow(this->A, 2) + pow(this->B, 2))*sqrt(pow(line.A, 2) + pow(line.B, 2)));
	double angle = acos(CosA);//角度
	return angle;
}

double DM_Line::angle_Line2Line(const DM_Line &line, DM_Arc &arc_out)
{
	if (!this->isValid() || !line.isValid()) return -1.0;
	double CosA = abs(this->A*line.A + this->B*line.B) / (sqrt(pow(this->A, 2) + pow(this->B, 2))*sqrt(pow(line.A, 2) + pow(line.B, 2)));
	double angle = acos(CosA);//角度

	//求解圆弧
	//1、计算两直线的交点croosP；
	//2、计算交点到各个端点的距离
	//3、确定距离交点最远的两个端点PA PB
	//4、计算向量croosP、PA与向量crossP、PB的旋转角度是不是与夹角相等，否则跟换。

	return angle;
}
bool DM_Line::getLineParam()//通过p1 p2来计算
{
	A = P1.y - P2.y;
	B = P2.x - P1.x;
	if (0.0 == A && 0.0 == B) return false;

	C = P1.x * P2.y - P1.y * P2.x;
	if (0.0 == B)//没有斜率==斜率无穷大
	{
		IsVertical = true;
		this->m = -C / A;//x轴截距
		this->angle = DM_PI_2;
	}
	else
	{
		IsVertical = false;
		this->k = -A / B;
		this->m = -C / B;//y轴截距
		this->angle = atan(k);
	}
	return true;
}

DM_Ring::DM_Ring() :innerRadius(0.0), outerRadius(0.0), IsValid(false)
{
    this->type = Ring_ELMT;
    this->direction = 2;//无方向
}

DM_Ring::DM_Ring(const DM_Point &center, const double &inradius, const double &outradius, const int &dir)
{
    if (0 >= inradius || inradius >= outradius)//内圆半径大于0且小于外圆半径才ok
    {
        IsValid = false;
        return;
    }
    IsValid = true;
    this->center = center;
    this->innerRadius = inradius;
    this->outerRadius = outradius;
    this->type = Ring_ELMT;
    this->direction = dir;//无方向
}

DM_Rect DM_Ring::getBoundingRect() const
{
	return DM_Rect(DM_Point(this->center.x - this->outerRadius, this->center.y - this->outerRadius),
                   DM_Point(this->center.x + this->outerRadius, this->center.y + this->outerRadius));
}

bool DM_Ring::operator==(const DM_Ring &obj)
{
	if (this->center == obj.center &&
		abs(this->innerRadius - obj.innerRadius) < DM_eps &&
		abs(this->outerRadius - obj.outerRadius) < DM_eps &&
		this->direction == obj.direction &&
		this->IsValid == obj.IsValid)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DM_Ring& DM_Ring::operator=(const DM_Ring &obj)
{
	this->center = obj.center;
	this->innerRadius = obj.innerRadius;
	this->outerRadius = obj.outerRadius;
	this->direction = obj.direction;//方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
	this->IsValid = obj.IsValid;
	//初始化父类相关参数
	this->type = obj.type;
	this->name = obj.name;
	return *this;
}

void DM_Ring::setDirection(int dir)
{
    if(dir < 0)
    {
        this->direction = 0;
    }
    else if(dir > 2)
    {
        this->direction = 2;
    }
    else
    {
        this->direction =dir;
    }
}
bool DM_Ring::isInMat(const cv::Mat& img)
{
	return DM_Point(this->center.x - this->outerRadius, this->center.y - this->outerRadius).isInMat(img) &&
			DM_Point(this->center.x + this->outerRadius, this->center.y + this->outerRadius).isInMat(img);
}
//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点
//参数(点1，点2，出参-细分出来的点)
//返回值：大于0，反馈点的个数； 小于0，两点重合，细分失败
//_____________________________________________________________________________________________________________
/*
int DM_Ring::subDivide(const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	out_pts.clear();
	do
	{
		out_pts.push_back(cv::Point(x0, y0));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}
*/
//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点，并从img上采样
//参数(图像img，点1，点2，出参-细分出来的点)
//返回值：
//     a)、大于0，反馈点的个数；
//     b)、-1，两点重合，细分失败
//     c)、-2，图像为空 不可采样
//_____________________________________________________________________________________________________________
/*
int DM_Ring::subDivide(const cv::Mat& img, const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point3i>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	if (img.empty()) return -2;//图像为空 不可采样

	out_pts.clear();

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	do
	{
		out_pts.push_back(cv::Point3i(x0, y0, img.at<uchar>(y0, x0)));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}
*/
//获取圆环内指定方向的边沿点
//dir:查找方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
//查找的基准都是上升沿
int DM_Ring::getRingEdgePoints(const Mat& img, vector<DM_Point>& edge_pts, int dir)
{
	DM_Ring roi = *this;
	if (img.empty()) return -1;//图像为空
	if (!roi.isValid()) return -2;//roi无效
	if (!roi.isInMat(img)) return -3;//roi不在图像中
	if (roi.outerRadius < 10.0) return -4;//roi尺寸过小

	const double a = roi.center.x;
	const double b = roi.center.y;
	const double inr = roi.innerRadius;
	const double outr = roi.outerRadius;
	DM_Point InPt, OutPt;
	vector<vector<Point3i>> SampleData;
	const double dt = 1.0 / inr;//把圆周角拆分成一个单位长度一个角。内外圆均可,可实验下 稳定性谁高，反正内圆肯定速度更快
	for (double t = 0.0; t < DM_2PI; t += dt)
	{//x=a+r·cosθ, y=b+r·sinθ,//圆的参数方程
		vector<Point3i> temp_data;
		subDivide(img, InPt(a + inr * cos(t), b + inr * sin(t)).toPoint(),
				  OutPt(a + outr * cos(t), b + outr * sin(t)).toPoint(), temp_data);
		SampleData.push_back(temp_data);
	}

	//处理每个SampleData，计算中心差分
	vector<vector<int>> CentralDiffs;//存储所有的中心差分
	for (size_t i = 0; i < SampleData.size(); ++i)
	{
		vector<int> temp_central_diff;
		temp_central_diff.push_back(0);//填充第0个
		for (size_t j = 1; j < SampleData[i].size() - 1; ++j)
		{
			temp_central_diff.push_back((SampleData[i][j + 1].z - SampleData[i][j - 1].z));//可以考虑/2一下
		}
		CentralDiffs.push_back(temp_central_diff);
	}

	//找差分最大值处
	edge_pts.clear();
	for (size_t i = 0; i < CentralDiffs.size(); ++i)
	{
		size_t index_maxval = 0;
		size_t index_minval = 0;
		for (size_t j = 1; j < CentralDiffs[i].size(); ++j)//由于是中心差分，不看第0个
		{
			if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
				index_maxval = j;
			if (CentralDiffs[i][index_minval] > CentralDiffs[i][j])
				index_minval = j;
		}
		if (dir == 1)//从外环找到内环
		{
			if (CentralDiffs[i][index_minval] < 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = SampleData[i][index_minval];
				edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
			}
		}
		else if (dir == 0) //从内环找到外环
		{
			if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = SampleData[i][index_maxval];
				edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
			}
		}
		else//不分方向查找，找到整条线段上跳变边最大的点
		{
			if (CentralDiffs[i][index_maxval] > abs(CentralDiffs[i][index_minval]))
			{
				if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = SampleData[i][index_maxval];
					edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
				}
			}
			else
			{
				if (abs(CentralDiffs[i][index_minval]) > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = SampleData[i][index_minval];
					edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
				}
			}

		}
	}

#ifdef PC_Debug
	Mat srcBGR(img.size(), CV_8UC3);
	if (img.channels() != 1)
	{
		img.copyTo(srcBGR);
	}
	else
	{
		cvtColor(img, srcBGR, COLOR_GRAY2BGR);
	}
	for (int i = 0; i < edge_pts.size(); i++)
	{
		circle(srcBGR, edge_pts[i].toPoint(), 1, Scalar(0, 0, 255), -1);
	}
#endif
	return int(edge_pts.size());
}

DM_Circle::DM_Circle()
{
	this->center = DM_Point();
	this->radius = 0.0;
	IsValid = false;
	this->type = Circle_ELMT;
}
DM_Circle::DM_Circle(const DM_Point& center, const double& radius)
{
	this->center = center;
	this->radius = radius;
	this->type = Circle_ELMT;
	if (abs(radius) >= 1.0e-6)
	{
		IsValid = true;
	}
	else
	{
		IsValid = false;
	}
	
}
DM_Circle::DM_Circle(const vector<Point>& pts)
{
	this->type = Circle_ELMT;
	IsValid = false;
	size_t counts = pts.size();
	if (counts < 3)
	{
		//		cout << "points num is less than 3" << endl;
		*this = DM_Circle();
		return;
	}

	unsigned long long  X1 = 0;
	unsigned long long  Y1 = 0;
	unsigned long long  X2 = 0;
	unsigned long long  Y2 = 0;
	unsigned long long  X3 = 0;
	unsigned long long  Y3 = 0;
	unsigned long long  X1Y1 = 0;
	unsigned long long  X1Y2 = 0;
	unsigned long long  X2Y1 = 0;

	unsigned long long  x = 0;
	unsigned long long  y = 0;
	for (size_t i = 0; i < counts; ++i)
	{
		x = pts[i].x;
		y = pts[i].y;
		X1 = X1 + x;
		Y1 = Y1 + y;
		X2 = X2 + x * x;
		Y2 = Y2 + y * y;
		X3 = X3 + x * x * x;
		Y3 = Y3 + y * y * y;
		X1Y1 = X1Y1 + x * y;
		X1Y2 = X1Y2 + x * y * y;
		X2Y1 = X2Y1 + x * x * y;
	}

	double C, D, E, G, H, N;
	double a, b, c;
	N = counts;
	C = N * X2 - X1 * X1;
	D = N * X1Y1 - X1 * Y1;
	E = N * X3 + N * X1Y2 - (X2 + Y2) * X1;
	G = N * Y2 - Y1 * Y1;
	H = N * X2Y1 + N * Y3 - (X2 + Y2) * Y1;
	if (0.0 == (C * G - D * D) || 0.0 == (D * D - G * C))
	{
		//		cout << "bad points" << endl;
		*this = DM_Circle();
	}
	a = (H*D - E * G) / (C*G - D * D);
	b = (H*C - E * D) / (D*D - G * C);
	c = -(a*X1 + b * Y1 + X2 + Y2) / N;


	double A, B, R;
	A = -0.5 * a;
	B = -0.5 * b;
	R = sqrt(a*a + b * b - 4 * c) *0.5;

	*this = DM_Circle(DM_Point(A, B), R);
}
DM_Circle::DM_Circle(const vector<DM_Point>& pts)
{
	IsValid = false;
	this->type = Circle_ELMT;
	size_t counts = pts.size();
	if (counts < 3)
	{//cout << "points num is less than 3" << endl;
		*this = DM_Circle();
		return;
	}

	double X1 = 0;
	double Y1 = 0;
	double X2 = 0;
	double Y2 = 0;
	double X3 = 0;
	double Y3 = 0;
	double X1Y1 = 0;
	double X1Y2 = 0;
	double X2Y1 = 0;

	for (size_t i = 0; i < counts; ++i)
	{
		X1 = X1 + pts[i].x;
		Y1 = Y1 + pts[i].y;
		X2 = X2 + pts[i].x * pts[i].x;
		Y2 = Y2 + pts[i].y * pts[i].y;
		X3 = X3 + pts[i].x * pts[i].x * pts[i].x;
		Y3 = Y3 + pts[i].y * pts[i].y * pts[i].y;
		X1Y1 = X1Y1 + pts[i].x * pts[i].y;
		X1Y2 = X1Y2 + pts[i].x * pts[i].y * pts[i].y;
		X2Y1 = X2Y1 + pts[i].x * pts[i].x * pts[i].y;
	}

	double C, D, E, G, H, N;
	double a, b, c;
	N = counts;
	C = N * X2 - X1 * X1;
	D = N * X1Y1 - X1 * Y1;
	E = N * X3 + N * X1Y2 - (X2 + Y2) * X1;
	G = N * Y2 - Y1 * Y1;
	H = N * X2Y1 + N * Y3 - (X2 + Y2) * Y1;
	if (0.0 == (C * G - D * D) || 0.0 == (D * D - G * C))
	{
		//		cout << "bad points" << endl;
		*this =  DM_Circle();
	}
	a = (H*D - E * G) / (C*G - D * D);
	b = (H*C - E * D) / (D*D - G * C);
	c = -(a*X1 + b * Y1 + X2 + Y2) / N;


	double A, B, R;
	A = -0.5 * a;
	B = -0.5 * b;
	R = sqrt(a*a + b * b - 4 * c) *0.5;

	*this = DM_Circle(DM_Point(A, B), R);
}
DM_Circle::DM_Circle(const DM_Point& p1, const DM_Point& p2, const DM_Point& p3)
{
	this->type = Circle_ELMT;
	DM_Line L1(p1, p2);
	if (!L1.isValid()||
		(L1.isValid() && L1.dis_P2Line(p3) < DM_eps))
	{
		this->center = DM_Point();
		this->radius = 0;
		this->IsValid = false;
	}
	else
	{
		double x1 = p1.x, x2 = p2.x, x3 = p3.x;
		double y1 = p1.y, y2 = p2.y, y3 = p3.y;
		double a = x1 - x2;
		double b = y1 - y2;
		double c = x1 - x3;
		double d = y1 - y3;
		double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) * 0.5;
		double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) * 0.5;
		double det = b * c - a * d;
		if (abs(det) < 1e-5)
		{
			IsValid = false;
			return;
		}
		IsValid = true;
		this->center.x = -(d * e - b * f) / det;
		this->center.y = -(a * f - c * e) / det;
		this->radius = hypot(x1 - this->center.x, y1 - this->center.y);
	}
}
DM_Circle::DM_Circle(const cv::Point& p1, const cv::Point& p2, const cv::Point& p3)
{
	this->type = Circle_ELMT;
	*this = DM_Circle(DM_Point(p1), DM_Point(p2), DM_Point(p3));
}
DM_Circle::DM_Circle(const DM_Circle &obj)
{
	this->type = Circle_ELMT;
	this->center = obj.center;
	this->radius = obj.radius;
	IsValid = true;
}

DM_Circle::DM_Circle(const vector<Point>& pts, double half_thick, int max_iter /*= 10*/)
{
	this->type = Circle_ELMT;
	vector<DM_Point> pts_;
	for (int i = 0; i < pts.size(); i++)
	{
		pts_.push_back(pts[i]);
	}
	DM_Circle(pts_, half_thick, max_iter);
}

DM_Circle& DM_Circle::operator=(const DM_Circle &obj)
{
	this->center = obj.center;
	this->radius = obj.radius;
	IsValid = obj.IsValid;
	return *this;
}
DM_Circle::DM_Circle(const vector<DM_Point>& pts, double half_thick, int max_iter)
{
	fit_Smart(pts, half_thick, max_iter);
}
int DM_Circle::fit_Smart(const vector<DM_Point>& pts, double half_thick, int max_iter)
{
	size_t PtsNum = pts.size();
	if (PtsNum < 3) return -1;//点数少于3
	double InR, OutR, Dis;
	vector<DM_Point> temp_pts;
	DM_Circle cir = DM_Circle(pts);
	if (!cir.isValid()) return -2;//拟合失败

	InR = cir.radius - half_thick * 8.0;
	OutR = cir.radius + half_thick * 8.0;
	temp_pts.clear();
	for (size_t i = 0; i < PtsNum; ++i)//排除干扰点
	{
		Dis = cir.center.dis_P2P(pts[i]);
		if (InR < Dis&&Dis < OutR) temp_pts.push_back(pts[i]);
	}
	cir = DM_Circle(temp_pts);//再拟合
	if (!cir.isValid()) return -2;//拟合失败

	InR = cir.radius - half_thick * 4.0;
	OutR = cir.radius + half_thick * 4.0;
	temp_pts.clear();
	for (size_t i = 0; i < PtsNum; ++i)//排除干扰点
	{
		Dis = cir.center.dis_P2P(pts[i]);
		if (InR < Dis&&Dis < OutR) temp_pts.push_back(pts[i]);
	}
	cir = DM_Circle(temp_pts);//再拟合
	if (!cir.isValid()) return -2;//拟合失败

	InR = cir.radius - half_thick * 2.0;
	OutR = cir.radius + half_thick * 2.0;
	temp_pts.clear();
	for (size_t i = 0; i < PtsNum; ++i)//排除干扰点
	{
		Dis = cir.center.dis_P2P(pts[i]);
		if (InR < Dis&&Dis < OutR) temp_pts.push_back(pts[i]);
	}
	cir = DM_Circle(temp_pts);//再拟合
	if (!cir.isValid()) return -2;//拟合失败


	InR = cir.radius - half_thick;
	OutR = cir.radius + half_thick;
	*this = cir;
	for (int i = 0; i < max_iter; ++i)//再拟合
	{
		temp_pts.clear();
		for (size_t i = 0; i < PtsNum; ++i)//排除干扰点
		{
			Dis = cir.center.dis_P2P(pts[i]);
			if (InR < Dis&&Dis < OutR) temp_pts.push_back(pts[i]);
		}
		cir = DM_Circle(temp_pts);//再拟合
		if (!cir.isValid()) return -2;//拟合失败

		if (this->center == cir.center && this->radius == cir.radius)
		{
			//cout<<"current iter times : "<<i<<endl;
			break;
		}
		*this = cir;
	}
	return 1;
}
bool DM_Circle::isInMat(const Mat& mat)
{
	DM_Point LeftTop(this->center.x - this->radius, this->center.y - this->radius);
	DM_Point RightBottom(this->center.x + this->radius, this->center.y + this->radius);
	return (LeftTop.isInMat(mat) && RightBottom.isInMat(mat));
}

DM_Rect DM_Circle::getBoundingRect() const
{
	return DM_Rect(DM_Point(this->center.x - this->radius,this->center.y-this->radius),
				   DM_Point(this->center.x + this->radius,this->center.y+this->radius));
}
void DM_Circle::generate(const cv::Mat& img, DM_Ring ring)
{
	vector<DM_Point> pts;
    int ret = ring.getRingEdgePoints(img, pts,ring.direction);


#ifdef PC_Debug
	Mat imgBGR;
	cvtColor(img, imgBGR, COLOR_GRAY2BGR);
	for (int i = 0; i < pts.size(); i++)
	{
		circle(imgBGR, pts[i].toPoint(), 1, Scalar(0, 0, 255), -1);
	}
#endif
	if (ret < 0)
	{
		*this = DM_Circle();
	}
	else
	{
		*this = DM_Circle(pts, 3);
	}
}

DM_Ellipse::DM_Ellipse(const DM_Point& center, const double& a, const double& b, const double& angle)
{
	this->center = center;
	if (a > b)
	{
		this->a = a;
		this->b = b;
	}
	else
	{
		this->a = b;
		this->b = a;
	}

	this->angle = angle;
	this->IsValid = true;
}
DM_Ellipse::DM_Ellipse(const cv::RotatedRect &rect)
{
	this->center = rect.center;
	this->angle = rect.angle*DM_PI_180;
	this->b = rect.size.width;
	this->a = rect.size.height;
}
DM_Ellipse::DM_Ellipse(const DM_Ellipse& obj)
{
	this->center = obj.center;
	this->a = obj.a;
	this->b = obj.b;
	this->angle = obj.angle;
	this->IsValid = obj.IsValid;
}
DM_Ellipse& DM_Ellipse::operator=(const DM_Ellipse& obj)
{
	this->center = obj.center;
	this->a = obj.a;
	this->b = obj.b;
	this->angle = obj.angle;
	this->IsValid = obj.IsValid;

	return *this;
}
bool DM_Ellipse::operator==(const DM_Ellipse& obj)
{
	if (this->center == obj.center &&
		this->a == obj.a &&
		this->b == obj.b &&
		this->angle == obj.angle &&
		this->IsValid == obj.IsValid)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool DM_Ellipse::operator!=(const DM_Ellipse& obj)
{
	return !(*this == obj);
}
DM_Ellipse DM_Ellipse::generate(cv::Mat& img, DM_Ring roi, double precision , int max_iter , int isH2L )
{
	//查找图像上方的圆环
	vector<DM_Point> edge_pts;//表示上面圆环的点集
	roi.getRingEdgePoints(img, edge_pts, isH2L);
	this->fitsmart(edge_pts, precision, max_iter);
	return *this;
}
//获取椭圆与过椭圆心的直线，在竖直方向的交点
bool DM_Ellipse::getVerticalCrossPoint(DM_Point& Pt1, DM_Point& Pt2)
{
	if (a == 0 || b == 0)
	{
		return false;
	}
	double cosa = cos(angle*DM_PI_180);
	double sina = sin(angle*DM_PI_180);
	double m = (a*a) / 4.0;
	double n = (b*b) / 4.0;
	double w = (m*n) / (m*sina*sina + n * cosa*cosa);
	double y = sqrt(w);
	Pt1.x = center.x;
	Pt1.y = center.y + y;
	Pt2.x = center.x;
	Pt2.y = center.y - y;


	return true;
}
//获取椭圆与过椭圆心的直线，在水平方向的交点
bool DM_Ellipse::getHorizontalCrossPoint(DM_Point& Pt1, DM_Point& Pt2)
{
	if (a == 0 || b == 0)
	{
		return false;
	}
	double cosa = cos(angle*DM_PI_180);
	double sina = sin(angle*DM_PI_180);
	double m = (a*a) / 4.0;
	double n = (b*b) / 4.0;
	double w = (m*n) / (n*sina*sina + m * cosa*cosa);
	double x = sqrt(w);
	Pt1.x = center.x + x;
	Pt1.y = center.y;
	Pt2.x = center.x - x;
	Pt2.y = center.y;
	return true;
}

DM_Arc::DM_Arc(const Point& start_pt, const Point& mid_pt, const Point& end_pt)
{
	this->type = Arc_ELMT;
	DM_Circle Cir(start_pt, mid_pt, end_pt);
	IsValid = Cir.isValid();
	if (!IsValid) return;//如果无效

	this->startPoint = DM_Point(start_pt);
	this->midPoint = DM_Point(mid_pt);
	this->endPoint = DM_Point(end_pt);
	this->center = Cir.center;
	this->radius = Cir.radius;
	this->startAngle = getStdAngle(atan2(start_pt.y - this->center.y, start_pt.x - this->center.x));
	this->endAngle = getStdAngle(atan2(end_pt.y - this->center.y, end_pt.x - this->center.x));
	double MidAngle = getStdAngle(atan2(mid_pt.y - this->center.y, mid_pt.x - this->center.x));
	if (getStdAngle(this->endAngle - this->startAngle) < getStdAngle(MidAngle - this->startAngle))
	{
		double temp = this->startAngle;
		this->startAngle = this->endAngle;
		this->endAngle = temp;
	}
}

DM_Arc::DM_Arc(const DM_Point& start_pt, const DM_Point& mid_pt, const DM_Point& end_pt)
{
	*this = DM_Arc(start_pt.toPoint(), mid_pt.toPoint(), end_pt.toPoint());
}

DM_Arc::DM_Arc(DM_Point center, double radius, double start_angle, double end_angle)
{
	this->type = Arc_ELMT;
	this->center = center;
	this->radius = radius;
	this->startAngle = start_angle;
	this->endAngle = end_angle;
	IsValid = true;
}

DM_Arc::DM_Arc(const vector<DM_Point>& pts)
{
	type = Arc_ELMT;
	size_t counts = pts.size();
	//	cout<<"arc fitting points count : "<<counts<<endl;

	if (counts < 3)
	{
		//cout << "points num is less than 3" << endl;
		*this = DM_Arc();
		return;
	}

	points = pts;

	//坐标数值优化，将所有点都沿向量(-xmin, -ymin)平移
	int xmin = 99999999, ymin = 99999999;
	for (size_t i = 0; i < counts; ++i)
	{
		if (pts[i].x < xmin) xmin = pts[i].x;
		if (pts[i].y < ymin) ymin = pts[i].y;
	}
	//平移

	for (size_t i = 0; i < counts; ++i)
	{
		points[i].x -= xmin;
		points[i].y -= ymin;
	}

	double X1   = 0.0;
	double Y1   = 0.0;
	double X2   = 0.0;
	double Y2   = 0.0;
	double X3   = 0.0;
	double Y3   = 0.0;
	double X1Y1 = 0.0;
	double X1Y2 = 0.0;
	double X2Y1 = 0.0;
	for (size_t i = 0; i < counts; ++i)
	{
		X1   = X1   + points[i].x;
		Y1   = Y1   + points[i].y;
		X2   = X2   + points[i].x * this->points[i].x;
		Y2   = Y2   + points[i].y * this->points[i].y;
		X3   = X3   + points[i].x * this->points[i].x * this->points[i].x;
		Y3   = Y3   + points[i].y * this->points[i].y * this->points[i].y;
		X1Y1 = X1Y1 + points[i].x * this->points[i].y;
		X1Y2 = X1Y2 + points[i].x * this->points[i].y * this->points[i].y;
		X2Y1 = X2Y1 + points[i].x * this->points[i].x * this->points[i].y;
	}

	//	cout<<"X3 : "<<X3<<", Y3 : "<<Y3<<endl;
	double C, D, E, G, H, N;
	double a, b, c;
	N = counts;
	C = N * X2 - X1 * X1;
	D = N * X1Y1 - X1 * Y1;
	E = N * X3 + N * X1Y2 - (X2 + Y2) * X1;
	G = N * Y2 - Y1 * Y1;
	H = N * X2Y1 + N * Y3 - (X2 + Y2) * Y1;
	if (0.0 == (C * G - D * D) || 0.0 == (D * D - G * C))
	{
		//		cout << "bad points" << endl;
		*this = DM_Arc();
		return;
	}
	a = (H*D - E * G) / (C*G - D * D);
	b = (H*C - E * D) / (D*D - G * C);
	c = -(a*X1 + b * Y1 + X2 + Y2) / N;

	double A, B, R;
	A = -0.5 * a;
	B = -0.5 * b;
	R = sqrt(a*a + b * b - 4.0 * c) *0.5;


	this->center = DM_Point(A + xmin, B + ymin);//加上平移后的偏移量
	this->radius = R;
	this->IsValid = true;
	this->startAngle = 0.0;
	this->endAngle = DM_2PI;

	//	double X1   = 0.0;
	//	double Y1   = 0.0;
	//	double X2   = 0.0;
	//	double Y2   = 0.0;
	//	double X3   = 0.0;
	//	double Y3   = 0.0;
	//	double X1Y1 = 0.0;
	//	double X1Y2 = 0.0;
	//	double X2Y1 = 0.0;
	//	for(size_t i = 0; i < counts; ++i)
	//	{
	//		X1 = X1 +     double(Points[i].x);
	//		Y1 = Y1 +     double(Points[i].y);
	//		X2 = X2 +     double(Points[i].x) * double(Points[i].x);
	//		Y2 = Y2 +     double(Points[i].y) * double(Points[i].y);
	//		X3 = X3 +     double(Points[i].x) * double(Points[i].x) * double(Points[i].x);
	//		Y3 = Y3 +     double(Points[i].y) * double(Points[i].y) * double(Points[i].y);
	//		X1Y1 = X1Y1 + double(Points[i].x) * double(Points[i].y);
	//		X1Y2 = X1Y2 + double(Points[i].x) * double(Points[i].y) * double(Points[i].y);
	//		X2Y1 = X2Y1 + double(Points[i].x) * double(Points[i].x) * double(Points[i].y);
	//	}

	//	cout<<"X3 : "<<X3<<", Y3 : "<<Y3<<endl;
	//	double C, D, E, G, H, N;
	//	double a, b, c;
	//	N = counts;
	//	C = N * X2 - X1 * X1;
	//	D = N * X1Y1 - X1 * Y1;
	//	E = N * X3 + N * X1Y2 - (X2 + Y2) * X1;
	//	G = N * Y2 - Y1 * Y1;
	//	H = N * X2Y1 + N * Y3 - (X2 + Y2) * Y1;
	//	if(0.0 == (C * G - D * D) || 0.0 == (D * D - G * C))
	//	{
	//		//		cout << "bad points" << endl;
	//		*this = DM_Arc();
	//		return;
	//	}
	//	a = (H*D - E*G) / (C*G - D*D);
	//	b = (H*C - E*D) / (D*D - G*C);
	//	c = -(a*X1 + b*Y1 + X2 + Y2) / N;

	//	double A, B, R;
	//	A = -0.5 * a;
	//	B = -0.5 * b;
	//	R = sqrt(a*a + b*b - 4.0 * c) *0.5;


	//	this->Center = DM_Point(A, B);
	//	this->Radius = R;
	//	this->IsValid = true;
	//	this->StartAngle = 0.0;
	//	this->EndAngle = DM_2PI;


	//计算两个最两端边缘点对应的角度
	//	DM_RotatedRect rrect(minAreaRect(pts));
	//	DM_Arc arc(rrect.Axis.P1, rrect.Center, rrect.Axis.P2);
	//	this->arc.StartAngle
}



DM_Rect DM_Arc::getBoundingRect() const
{
	vector<DM_Point> Pts;
	Pts.push_back(this->startPoint);
	Pts.push_back(this->midPoint);
	Pts.push_back(this->endPoint);

	if (this->startAngle <= this->endAngle)
	{
		if (this->startAngle <= DM_PI_2)
		{
			if (this->endAngle > DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->radius));//通过90度
			if (this->endAngle > DM_PI) Pts.push_back(DM_Point(this->center.x - this->radius, this->center.y));//通过180度
			if (this->endAngle > DM_3PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y - this->radius));//通过270度
		}

		if (DM_PI_2 < this->startAngle&&this->startAngle <= DM_PI)
		{
			if (this->endAngle > DM_PI) Pts.push_back(DM_Point(this->center.x - this->radius, this->center.y));//通过180度
			if (this->endAngle > DM_3PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y - this->radius));//通过270度
		}

		if (DM_PI < this->startAngle&&this->startAngle<=DM_3PI_2&&this->endAngle>=DM_3PI_2)
		{
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->radius));//通过270度
		}
	}
	else
	{
		Pts.push_back(DM_Point(this->center.x + this->radius, this->center.y));//0

		if (this->startAngle <= DM_PI_2)
		{
			Pts.push_back(DM_Point(this->center.x, this->center.y + this->radius));//90
			Pts.push_back(DM_Point(this->center.x - this->radius, this->center.y));//180
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->radius));//270
		}

		if (DM_PI_2 < this->startAngle&&this->startAngle <= DM_PI)
		{
			Pts.push_back(DM_Point(this->center.x - this->radius, this->center.y));//180
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->radius));//270
			if (this->endAngle > DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->radius));//90
		}

		if (DM_PI < this->startAngle&&this->startAngle <= DM_3PI_2)
		{
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->radius));//270
			if (this->endAngle >= DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->radius));//90
			if (this->endAngle > DM_PI) Pts.push_back(DM_Point(this->center.x - this->radius, this->center.y));//180
		}

		if (DM_3PI_2 < this->startAngle&&this->startAngle <= DM_2PI)
		{
			if (this->endAngle >= DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->radius));//90
			if (this->endAngle >= DM_PI) Pts.push_back(DM_Point(this->center.x - this->radius, this->center.y));//180
			if (this->endAngle > DM_3PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y - this->radius));//270
		}
	}
	double xmin = 99999999.0, xmax = 0.0, ymin = 99999999.0, ymax = 0.0;
	for (size_t i = 0; i < Pts.size(); ++i)
	{
		if (Pts[i].x < xmin) xmin = Pts[i].x;
		if (Pts[i].x > xmax) xmax = Pts[i].x;
		if (Pts[i].y < ymin) ymin = Pts[i].y;
		if (Pts[i].y > ymax) ymax = Pts[i].y;
	}
	return DM_Rect(DM_Point(xmin, ymin), DM_Size(xmax - xmin, ymax - ymin));
}


bool DM_Arc::isInMat(const Mat& mat)
{
	DM_Rect BRect = this->getBoundingRect();
	return (BRect.leftTop.isInMat(mat) && BRect.rightBottom.isInMat(mat));
}



cv::RotatedRect DM_Ellipse::toRotateRect() const
{
	RotatedRect obj;
	obj.center = this->center.toPoint2f();
	obj.angle = this->angle* DM_180_PI;
	obj.size = Size2f(this->b, this->a);
	return obj;
}

DM_RotatedRect DM_Ellipse::toDM_RotateRect() const
{
	DM_RotatedRect obj(this->center.toPoint2f(),Size2f(this->b, this->a),this->angle);
	return obj;
}


DM_Size::DM_Size(const  DM_Size& size)
{
	if (size.width <= 0.f || size.height <= 0.f)
	{
		this->width = 0.0;
		this->height = 0.0;
		IsValid = false;
	}
	else
	{
		this->width = double(size.width);
		this->height = double(size.height);
		IsValid = true;
	}
}
DM_Size& DM_Size::operator=(const  DM_Size& size)
{
	this->width = double(size.width);
	this->height = double(size.height);
	this->IsValid = size.IsValid;
	return *this;
}
bool DM_Size::operator==(const  DM_Size& size)
{
	if (abs(this->width - double(size.width)) <=  DM_eps &&
		abs(this->height - double(size.height)) <= DM_eps &&
		abs(this->IsValid - size.IsValid) <= DM_eps)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DM_Rect::DM_Rect(const cv::Rect& rect)
{
	this->leftTop(rect.x, rect.y);
	this->rightBottom(rect.x + rect.width, rect.y + rect.height);
	this->center((this->leftTop.x + this->rightBottom.x)*0.5, ( this->leftTop.y + this->rightBottom.y)*0.5);
	this->size(rect.width, rect.height);
	if(this->leftTop == this->rightBottom)
	{
		IsValid = false;
	}
	else
	{
		IsValid = true;
	}
	this->type = Rect_ELMT;
}

DM_Rect::DM_Rect(const DM_Point& left_top, const DM_Point& right_bottom)
{
	this->leftTop = left_top;
	this->rightBottom = right_bottom;
	this->center((this->leftTop.x + this->rightBottom.x)*0.5, (this->leftTop.y + this->rightBottom.y)*0.5);
	this->size(right_bottom.x - left_top.x, right_bottom.y - left_top.y);
	if(this->leftTop == this->rightBottom)
	{
		IsValid = false;
	}
	else
	{
		IsValid = true;
	}
	this->type = Rect_ELMT;
}

DM_Rect::DM_Rect(const DM_Point& left_top, const DM_Size& size)
{
	this->leftTop = left_top;
	this->rightBottom = DM_Point(left_top.x + size.width, left_top.y + size.height);
	this->center((this->leftTop.x + this->rightBottom.x)*0.5, (this->leftTop.y + this->rightBottom.y)*0.5);
	this->size = size;
	if(this->leftTop == this->rightBottom)
	{
		IsValid = false;
	}
	else
	{
		IsValid = true;
	}
	this->type = Rect_ELMT;
}

DM_Rect::DM_Rect(double center_x, double center_y, double width, double height)
{
	*this = DM_Rect(DM_Point(center_x - width * 0.5, center_y - height * 0.5), DM_Size(width, height));
}

DM_Rect::DM_Rect(const DM_Rect &obj)
{
	this->IsValid = obj.IsValid;
	this->size = obj.size;
	this->leftTop = obj.leftTop;
	this->rightBottom = obj.rightBottom;
	this->center = obj.center;
	this->type = obj.type;
}

DM_Rect DM_Rect::operator=(const DM_Rect &obj)
{
	this->IsValid = obj.IsValid;
	this->size = obj.size;
	this->leftTop = obj.leftTop;
	this->rightBottom = obj.rightBottom;
	this->center = obj.center;
	this->type = obj.type;

	return *this;
}

vector<DM_Point> DM_Rect::getVertices() const
{
	vector<DM_Point> pts;
	pts.push_back(this->leftTop);
	pts.push_back(DM_Point(this->leftTop.x,this->leftTop.y+this->size.height));
	pts.push_back(this->rightBottom);
	pts.push_back(DM_Point(this->rightBottom.x, this->rightBottom.y - this->size.height));
	return pts;
}
cv::Rect DM_Rect::toCvRect() const
{
	return cv::Rect(this->leftTop.x + 0.5, this->leftTop.y + 0.5,this->size.width + 0.5, this->size.height + 0.5);
}

bool DM_Rect::isInMat(const Mat& mat) const
{
	return (this->leftTop.isInMat(mat) && this->rightBottom.isInMat(mat));
}

bool DM_Rect::isInRect(const Rect& rect) const
{
	return (this->leftTop.isInRect(rect) && this->rightBottom.isInRect(rect));
}

bool DM_Rect::isValid() const { return IsValid; }
/*
 * 功能：根据roi，和查找方向find direction，在img中寻找roi中查找极值点
 *
 * 参数(原始数据图像，感兴趣区域，出参-极值点，查找方向1=)
 *
 * 返回值：
 * 大于零：极值点个数
 * -1：图像为空
 * -2：roi不在图像中
 * -3：roi尺寸过小
 * -4：方向错误，必须是1,2,3,4
 * -5：边缘点过少
*/
int DM_Rect::getExtremePoint(Mat& img, vector<Point>& extreme_pts, int find_direction)
{
	DM_Rect roi = *this;
	if (img.empty()) return -1;//图像为空
	if (!roi.isInMat(img)) return -2;//roi不在图像中
	if (roi.size.width < 5.0 || roi.size.height < 5.0) return -3;//roi尺寸过小
	if (find_direction < 1 || find_direction > 4) return -4;//方向错误

	Mat src = img(roi.toCvRect());
	extreme_pts.clear();

	switch (find_direction)
	{
		case 1://x_max
		{
			//计算中心差分
			vector<vector<int>> CentralDiffs;//存储所有的中心差分
			int width = src.cols - 1, height = src.rows;//y方向时，height要减1
			for (int y = 0; y < height; ++y)
			{
				vector<int> temp_central_diff;
				temp_central_diff.push_back(0);//填充第0个
				for (int x = 1; x < width; ++x)//找y方向的极值
					temp_central_diff.push_back(abs(src.at<uchar>(y, x - 1) - src.at<uchar>(y, x + 1)));
				CentralDiffs.push_back(temp_central_diff);
			}

			vector<Point> edge_pts;
			size_t count_i = CentralDiffs.size();
			for (size_t i = 0; i < count_i; ++i)//x标
			{
				size_t index_maxval = 0;
				size_t count_j = CentralDiffs[i].size();
				for (size_t j = 1; j < count_j; ++j)//由于是中心差分，不看第0个   //x标
				{
					if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
					{
						index_maxval = j;
						if (CentralDiffs[i][index_maxval] > 30)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
							edge_pts.push_back(Point(int(index_maxval), int(i)));
					}
				}
			}
			if (edge_pts.size() < 5) return -5;//边缘点过少

			size_t count_edge_pts = edge_pts.size();
			size_t index_extreme = 0;
			int x_extreme = edge_pts[0].x;
			for (size_t i = 1; i < count_edge_pts; i++)
			{
				if (x_extreme < edge_pts[i].x)
				{
					index_extreme = i;
					x_extreme = edge_pts[i].x;
				}
			}

			int offset_x = int(roi.leftTop.x + 0.5), offset_y = int(roi.leftTop.y + 0.5);//添加偏移量
			for (size_t i = 0; i < count_edge_pts; i++)
				if (x_extreme == edge_pts[i].x) extreme_pts.push_back(Point(edge_pts[i].x + offset_x, edge_pts[i].y + offset_y));
		}break;

		case 2://x_min
		{
			//计算中心差分
			vector<vector<int>> CentralDiffs;//存储所有的中心差分
			int width = src.cols - 1, height = src.rows;//y方向时，height要减1
			for (int y = 0; y < height; ++y)
			{
				vector<int> temp_central_diff;
				temp_central_diff.push_back(0);//填充第0个
				for (int x = 1; x < width; ++x)//找y方向的极值
					temp_central_diff.push_back(abs(src.at<uchar>(y, x - 1) - src.at<uchar>(y, x + 1)));
				CentralDiffs.push_back(temp_central_diff);
			}

			vector<Point> edge_pts;
			size_t count_i = CentralDiffs.size();
			for (size_t i = 0; i < count_i; ++i)//x标
			{
				size_t index_maxval = 0;
				size_t count_j = CentralDiffs[i].size();
				for (size_t j = 1; j < count_j; ++j)//由于是中心差分，不看第0个   //x标
				{
					if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
					{
						index_maxval = j;
						if (CentralDiffs[i][index_maxval] > 30)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
							edge_pts.push_back(Point(int(index_maxval), int(i)));
					}
				}
			}
			if (edge_pts.size() < 5) return -5;//边缘点过少

			size_t count_edge_pts = edge_pts.size();
			size_t index_extreme = 0;
			int x_extreme = edge_pts[0].x;
			for (size_t i = 1; i < count_edge_pts; i++)
			{
				if (x_extreme > edge_pts[i].x)
				{
					index_extreme = i;
					x_extreme = edge_pts[i].x;
				}
			}
			int offset_x = int(roi.leftTop.x + 0.5), offset_y = int(roi.leftTop.y + 0.5);//添加偏移量
			for (size_t i = 0; i < count_edge_pts; i++)
				if (x_extreme == edge_pts[i].x) extreme_pts.push_back(Point(edge_pts[i].x + offset_x, edge_pts[i].y + offset_y));
		}break;

		case 3://y_max
		{
			//计算中心差分
			vector<vector<int>> CentralDiffs;//存储所有的中心差分
			int width = src.cols, height = src.rows - 1;//y方向时，height要减1
			for (int x = 0; x < width; ++x)
			{
				vector<int> temp_central_diff;
				temp_central_diff.push_back(0);//填充第0个
				for (int y = 1; y < height; ++y)//找y方向的极值
					temp_central_diff.push_back(abs(src.at<uchar>(y - 1, x) - src.at<uchar>(y + 1, x)));
				CentralDiffs.push_back(temp_central_diff);
			}

			vector<Point> edge_pts;
			size_t count_i = CentralDiffs.size();
			for (size_t i = 0; i < count_i; ++i)//x标
			{
				size_t index_maxval = 0;
				size_t count_j = CentralDiffs[i].size();
				for (size_t j = 1; j < count_j; ++j)//由于是中心差分，不看第0个   //y标
				{
					if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
					{
						index_maxval = j;
						if (CentralDiffs[i][index_maxval] > 30)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
							edge_pts.push_back(Point(int(i), int(index_maxval)));
					}
				}
			}
			if (edge_pts.size() < 5) return -5;//边缘点过少

			size_t count_edge_pts = edge_pts.size();
			size_t index_extreme = 0;
			int y_extreme = edge_pts[0].y;
			for (size_t i = 1; i < count_edge_pts; i++)
			{
				if (y_extreme < edge_pts[i].y)
				{
					index_extreme = i;
					y_extreme = edge_pts[i].y;
				}
			}
			int offset_x = int(roi.leftTop.x + 0.5), offset_y = int(roi.leftTop.y + 0.5);//添加偏移量
			for (size_t i = 0; i < count_edge_pts; i++)
				if (y_extreme == edge_pts[i].y) extreme_pts.push_back(Point(edge_pts[i].x + offset_x, edge_pts[i].y + offset_y));
		}break;

		case 4://y_min
		{
			//计算中心差分
			vector<vector<int>> CentralDiffs;//存储所有的中心差分
			int width = src.cols, height = src.rows - 1;//y方向时，height要减1
			for (int x = 0; x < width; ++x)
			{
				vector<int> temp_central_diff;
				temp_central_diff.push_back(0);//填充第0个
				for (int y = 1; y < height; ++y)//找y方向的极值
					temp_central_diff.push_back(abs(src.at<uchar>(y - 1, x) - src.at<uchar>(y + 1, x)));
				CentralDiffs.push_back(temp_central_diff);
			}

			vector<Point> edge_pts;
			size_t count_i = CentralDiffs.size();
			for (size_t i = 0; i < count_i; ++i)//x标
			{
				size_t index_maxval = 0;
				size_t count_j = CentralDiffs[i].size();
				for (size_t j = 1; j < count_j; ++j)//由于是中心差分，不看第0个   //y标
				{
					if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
					{
						index_maxval = j;
						if (CentralDiffs[i][index_maxval] > 30)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
							edge_pts.push_back(Point(int(i), int(index_maxval)));
					}
				}
			}
			if (edge_pts.size() < 5) return -5;//边缘点过少

			size_t count_edge_pts = edge_pts.size();
			size_t index_extreme = 0;
			int y_extreme = edge_pts[0].y;
			for (size_t i = 1; i < count_edge_pts; i++)
			{
				if (y_extreme > edge_pts[i].y)
				{
					index_extreme = i;
					y_extreme = edge_pts[i].y;
				}
			}
			int offset_x = int(roi.leftTop.x + 0.5), offset_y = int(roi.leftTop.y + 0.5);//添加偏移量
			for (size_t i = 0; i < count_edge_pts; i++)
				if (y_extreme == edge_pts[i].y) extreme_pts.push_back(Point(edge_pts[i].x + offset_x, edge_pts[i].y + offset_y));
		}break;
	}
	return int(extreme_pts.size());
}

DM_RotatedRect::DM_RotatedRect(const cv::RotatedRect& rcet)
{//不计算Axis
	this->center = DM_Point(rcet.center);
	this->size = DM_Size(rcet.size);
	this->angle = double(rcet.angle);
	this->IsValid = true;
}
DM_RotatedRect::DM_RotatedRect(const DM_Point& center, const DM_Size& size, const double& angle)
{//不计算Axis
	this->center = center;
	this->size = size;
	this->angle = angle;
	this->IsValid = true;
}
DM_RotatedRect::DM_RotatedRect(const DM_Line& axis, const DM_Point& p)
{
	this->axis = axis;
	this->IsValid = this->axis.isValid();
	if (IsValid)
	{
		this->center = this->axis.getMidPoint();//轴中点为矩形中心
		this->size = DM_Size(this->axis.P1.dis_P2P(this->axis.P2), this->axis.dis_P2Line(p)*2.0);

		DM_Line perpendicularLine = this->axis.getPerpendicular(p);
		DM_Point crossPoint;
		this->axis.getCrossPoint(perpendicularLine, crossPoint);

		DM_Point vectorA(-this->axis.P2.x, 0.0);
		DM_Point vectorB((this->axis.P1.x - this->axis.P2.x), (this->axis.P1.y - this->axis.P2.y));//主轴方向
		DM_Point vectorC((p.x - crossPoint.x), (p.y - crossPoint.y));//第三个点与主轴的交点构成的向量
		//计算向量C到向量B的夹角
		double  dotCB = vectorC.x * vectorB.x + vectorC.y * vectorB.y;//两向量的点乘
		double LC = vectorC.dis_P2P(DM_Point(0, 0));
		double LB = vectorB.dis_P2P(DM_Point(0, 0));
		dotCB = dotCB / (LC*LB);

		double angleCB = acos(dotCB);
		double vectorDirCB = vectorC.x * vectorB.y - vectorB.x * vectorC.y;
		if (vectorDirCB < 0)
		{
			angleCB = DM_2PI - angleCB;
		}
		if (abs(angleCB - DM_PI_2) < 1)//方向不一致则换向
		{
			vectorB = DM_Point((this->axis.P2.x - this->axis.P1.x), (this->axis.P2.y - this->axis.P1.y));//主轴方向
			vectorA = DM_Point(-this->axis.P1.x, 0.0);
		}

		double  dotAB = vectorA.x * vectorB.x + vectorA.y * vectorB.y;//两向量的点乘
		double LA = vectorA.dis_P2P(DM_Point(0, 0));
		LB = vectorB.dis_P2P(DM_Point(0, 0));
		dotAB = dotAB / (LA*LB);
		this->angle = acos(dotAB);
		double vectorDirAB = vectorA.x * vectorB.y - vectorB.x * vectorA.y;
		if (vectorDirAB < 0)
		{
			this->angle = 2 * DM_PI - this->angle;
		}
	}
}
DM_RotatedRect::DM_RotatedRect(DM_Point pt1, DM_Point pt2, double width)
{
	if (pt1 == pt2 || width <= 0)
	{
		this->IsValid = false;
	}
	else
	{
		DM_Point vectorA(-pt2.x, 0.0);
		DM_Point vectorB((pt1.x - pt2.x), (pt1.y - pt2.y));

		double  dot = vectorA.x * vectorB.x + vectorA.y * vectorB.y;//两向量的点乘
		double LA = vectorA.dis_P2P(DM_Point(0, 0));
		double LB = vectorB.dis_P2P(DM_Point(0, 0));
		dot = dot / (LA*LB);

		this->angle = acos(dot);
		double crossDir = vectorA.x * vectorB.y - vectorB.x * vectorA.y;
		if (crossDir < 0)
		{
			this->angle = DM_2PI - this->angle;
		}
		this->center.x = (pt1.x + pt2.x) / 2.0;
		this->center.y = (pt1.y + pt2.y) / 2.0;
		this->size = DM_Size(pt1.dis_P2P(pt2), width);
		this->IsValid = true;
	}
}

DM_RotatedRect::DM_RotatedRect(DM_Line axis, double width)
{
	if(axis.isValid() &&
	   axis.P1.isValid()&&
	   axis.P2.isValid())
	{
		*this =  DM_RotatedRect(axis.P1,axis.P2,width);
	}
	else
	{
		*this = DM_RotatedRect();
	}
}


vector<DM_Point> DM_RotatedRect::getVertices() const
{
	vector<DM_Point> Vertices;
	double A = sin(this->angle)*0.5;
	double B = cos(this->angle)*0.5;
	Vertices.push_back(DM_Point(this->center.x - A * this->size.height - B * this->size.width, this->center.y + B * this->size.height - A * this->size.width));//p0
	Vertices.push_back(DM_Point(this->center.x + A * this->size.height - B * this->size.width, this->center.y - B * this->size.height - A * this->size.width));//p1
	Vertices.push_back(DM_Point(2.0*this->center.x - Vertices[0].x, 2.0*this->center.y - Vertices[0].y));//p2
	Vertices.push_back(DM_Point(2.0*this->center.x - Vertices[1].x, 2.0*this->center.y - Vertices[1].y));//p3
	return Vertices;
}
cv::Rect DM_RotatedRect::getBoundingRect() const
{
	vector<DM_Point> Pt = getVertices();//角点
	cv::Rect R(cvFloor(min(min(min(Pt[0].x, Pt[1].x), Pt[2].x), Pt[3].x)),
			cvFloor(min(min(min(Pt[0].y, Pt[1].y), Pt[2].y), Pt[3].y)),
			cvCeil(max(max(max(Pt[0].x, Pt[1].x), Pt[2].x), Pt[3].x)),
			cvCeil(max(max(max(Pt[0].y, Pt[1].y), Pt[2].y), Pt[3].y)));
	R.width -= R.x - 1;
	R.height -= R.y - 1;
	return R;
}
cv::RotatedRect DM_RotatedRect::toCvRotatedRect()
{
	if (this->angle > 0.0) return cv::RotatedRect(this->center.toPoint2f(), this->size.toSize2f(), (this->angle)*DM_180_PI);
	else return cv::RotatedRect(this->center.toPoint2f(), this->size.toSize2f(), (this->angle + DM_2PI)*DM_180_PI);
}
bool DM_RotatedRect::isInMat(const Mat& mat)
{
	vector<DM_Point> Pts = getVertices();//角点
	return (Pts[0].isInMat(mat) && Pts[1].isInMat(mat) && Pts[2].isInMat(mat) && Pts[3].isInMat(mat));
}
bool DM_RotatedRect::isInRect(const Rect& rect)
{
	vector<DM_Point> Pts = getVertices();//角点
	return (Pts[0].isInRect(rect) && Pts[1].isInRect(rect) && Pts[2].isInRect(rect) && Pts[3].isInRect(rect));
}
bool DM_RotatedRect::isValid() const { return IsValid; }
DM_Arrow DM_RotatedRect::getDirArrow(double l)const
{
	vector<DM_Point> pts = getVertices();
	return DM_Arrow(pts[3], pts[2], l);
}


//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点
//参数(点1，点2，出参-细分出来的点)
//返回值：大于0，反馈点的个数； 小于0，两点重合，细分失败
//_____________________________________________________________________________________________________________
/*
int  DM_RotatedRect::subDivide(const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	out_pts.clear();
	do
	{
		out_pts.push_back(cv::Point(x0, y0));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}
*/
//_____________________________________________________________________________________________________________
//函数名称及作用：细分p1 p2，得到两点之间的直线的所有像素化的点，并从img上采样
//参数(图像img，点1，点2，出参-细分出来的点)
//返回值：
//     a)、大于0，反馈点的个数；
//     b)、-1，两点重合，细分失败
//     c)、-2，图像为空 不可采样
//_____________________________________________________________________________________________________________
/*
int  DM_RotatedRect::subDivide(cv::Mat& img, const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point3i>& out_pts)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) return -1;//两点重合，细分失败

	if (img.empty()) return -2;//图像为空 不可采样

	out_pts.clear();

	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) >> 1;
	int e2;
	do
	{
		out_pts.push_back(cv::Point3i(x0, y0, img.at<uchar>(y0, x0)));
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	} while (x0 != x1 || y0 != y1);

	return int(out_pts.size());
}
*/
//取图
//取图结果说明：统一用输入的4个顶点的第2个作为原点，第1个点和第2个点构成Y轴，第3个点和第二个点构成X轴
int DM_RotatedRect::getRotationRectImage(const Mat &src, Mat &dst)
{
	vector<DM_Point> rectPoints = this->getVertices();
	//检查数据有效性
	if (src.empty())
	{
		return DM_error_para;
	}
	if (!this->isInMat(src))
	{
		return DM_error_para;
	}
	Rect boundingRectangle = this->getBoundingRect();
	Mat boundingImage = src(boundingRectangle);
	if (boundingImage.empty())
	{
		return DM_error_calculate;
	}
	//建立仿射关系
	Point2f scrTriangle[3];
	Point2f dstTriangle[3];

	scrTriangle[0].x = rectPoints[0].x - boundingRectangle.x;
	scrTriangle[0].y = rectPoints[0].y - boundingRectangle.y;

	scrTriangle[1].x = rectPoints[1].x - boundingRectangle.x;
	scrTriangle[1].y = rectPoints[1].y - boundingRectangle.y;

	scrTriangle[2].x = rectPoints[2].x - boundingRectangle.x;
	scrTriangle[2].y = rectPoints[2].y - boundingRectangle.y;

	double h = DM_Point(rectPoints[0]).dis_P2P(rectPoints[1]);
	double w = DM_Point(rectPoints[1]).dis_P2P(rectPoints[2]);

	int rows = int(h);
	int cols = int(w);
	//构建的图像长、宽都多5个点
	if (w > boundingImage.cols)
	{
		cols = int(w) + 5;
	}
	else
	{
		cols = boundingImage.cols + 5;
	}

	if (h > boundingImage.rows)
	{
		rows = int(h) + 5;
	}
	else
	{
		rows = boundingImage.rows + 5;
	}
	Mat image = Mat::zeros(rows, cols, src.type());
	boundingImage.copyTo(image(Rect(0, 0, boundingImage.cols, boundingImage.rows)));

	dstTriangle[0] = Point2f(0, float(h));
	dstTriangle[1] = Point2f(0, 0);
	dstTriangle[2] = Point2f(float(w), 0);
	Mat warpMatrix;
	warpMatrix = getAffineTransform(scrTriangle, dstTriangle);
	Mat warpBoundingImage = Mat::zeros(image.size(), image.type());
	warpAffine(image, warpBoundingImage, warpMatrix, warpBoundingImage.size());

	w = w + 0.5;
	h = h + 0.5;//四舍五入
	dst.create(static_cast<int>(w), static_cast<int>(h), warpBoundingImage.type());
	dst = Mat::zeros(dst.size(), warpBoundingImage.type()); //将目标图像初始化

	dst = warpBoundingImage(Rect(0, 0, static_cast<int>(w), static_cast<int>(h)));
	if (dst.empty())
	{
		return DM_error_calculate;
	}
	else
	{
		return DM_error_no;
	}
}

//_____________________________________________________________________________________________________________
//函数名称及作用：获取指定区域内，指定方向上的梯度点
//参数：
//     img：输入图像；
//     edge_pts: 边界上的点；
//     int isH2L:边沿点的极性问题，0： 从低灰度值到高灰度值 1：从高灰度值到低灰度值 2：不分极性
//返回值：
//     a)、大于0，反馈点的个数；
//     b)、-1，图像为空
//     c)、-2，roi不在图像中
//     d)、-3，roi尺寸过小
//     e)、-4, roi的区域的无效
//_____________________________________________________________________________________________________________

int DM_RotatedRect::getRotatedRectEdgePoints(cv::Mat& img, std::vector<DM_Point>& edge_pts, int isH2L)//获取斜方程内梯度方向的点
{
	DM_RotatedRect roi = *this;//有效区域

	if (img.empty()) return -1;//图像为空
	if (!roi.isInMat(img)) return -2;//区域不在图像中
	if (roi.size.width< 5.f || roi.size.height < 5.f) return -3;//roi尺寸过小
	if (!roi.isValid()) return -4;//roi的区域无效

	edge_pts.clear();

	std::vector<DM_Point> Vf = roi.getVertices();
	cv::Point Vertices[] = { Vf[0].toPoint(), Vf[1].toPoint(), Vf[2].toPoint(), Vf[3].toPoint() };//四舍五入

	vector<cv::Point> OutPts1, OutPts2;
	subDivide(Vertices[1], Vertices[2], OutPts2);
	subDivide(Vertices[0], Vertices[3], OutPts1);


	size_t Num = min(OutPts1.size(), OutPts2.size());
	std::vector<std::vector<cv::Point3i>> RawData;
	for (size_t i = 0; i < Num; ++i)
	{
		std::vector<cv::Point3i> temp_raw_data;
		subDivide(img, OutPts1[i], OutPts2[i], temp_raw_data);
		RawData.push_back(temp_raw_data);
	}
	//处理每个rawdata，计算中心差分
	std::vector<std::vector<int>> CentralDiffs;//存储所有的中心差分
	for (size_t i = 0; i < RawData.size(); ++i)
	{
		std::vector<int> temp_central_diff;
		temp_central_diff.push_back(0);//填充第0个
		for (size_t j = 1; j < RawData[i].size() - 1; ++j)
		{
			temp_central_diff.push_back((RawData[i][j + 1].z - RawData[i][j - 1].z));//
		}
		CentralDiffs.push_back(temp_central_diff);

	}
	//找差分最大值处
	for (size_t i = 0; i < CentralDiffs.size(); ++i)
	{
		size_t index_maxval = 0;
		size_t index_minval = 0;
		for (size_t j = 1; j < CentralDiffs[i].size(); ++j)//由于是中心差分，不看第0个
		{
			if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
				index_maxval = j;
			if (CentralDiffs[i][index_minval] > CentralDiffs[i][j])
				index_minval = j;
		}

		if (isH2L == 1)//查找下降沿
		{
			if (CentralDiffs[i][index_minval] <  -5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = RawData[i][index_minval];
				edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
			}
		}
		else if (isH2L == 0)//查找上升沿
		{
			if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = RawData[i][index_maxval];
				edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
			}
		}
		else//查找跳边沿
		{
			if (CentralDiffs[i][index_maxval] > abs(CentralDiffs[i][index_minval]))
			{
				if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = RawData[i][index_maxval];
					edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
				}
			}
			else
			{
				if (abs(CentralDiffs[i][index_minval]) > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = RawData[i][index_minval];
					edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
				}
			}

		}

	}

#ifdef PC_Debug
	Mat srcBGR(img.size(), CV_8UC3);
	if (img.channels() != 1)
	{
		img.copyTo(srcBGR);
	}
	else
	{
		cvtColor(img, srcBGR, COLOR_GRAY2BGR);
	}
	for (int i = 0; i < edge_pts.size(); i++)
	{
		circle(srcBGR, edge_pts[i].toPoint(), 1, Scalar(0, 0, 255), -1);
	}


#endif
	return edge_pts.size();
}

DM_Arrow::DM_Arrow(DM_Point P1, DM_Point P2, double L)
{
	if (P1 == P2 || abs(L - 0.0) < DM_eps)
	{
		this->IsValid = false;
	}
	else
	{
		this->P1 = P1;
		this->P2 = P2;
		this->L = L;
		this->IsValid = true;
	}


}
//返回四个端点【0 - P1，1 - P2, 2 - 箭头端点1，3 - 箭头的端点2】
vector<DM_Point> DM_Arrow::getVertices() const
{
	vector<DM_Point> vertices;
	if (this->IsValid == false)
	{
		return vertices;
	}
	else
	{

		DM_Point pt3;
		DM_Point P2P1Vector(this->P1.x - this->P2.x, this->P1.y - this->P2.y);//从P2到P1的方向向量
		this->P2.getPointOfSpecifiedDis(P2P1Vector, pt3, this->L);
		DM_RotatedRect rect(pt3, this->P2, 2*this->L);
		vector<DM_Point> rectPts = rect.getVertices();

		if (rectPts.size() == 4)
		{
			vertices.push_back(this->P1);
			vertices.push_back(this->P2);
			vertices.push_back(rectPts[0]);
			vertices.push_back(rectPts[1]);
		}
		return vertices;
	}
}
DM_Arrow::DM_Arrow(const DM_Arrow& obj)
{
	this->P1 = obj.P1;
	this->P2 = obj.P2;
	this->L = obj.L;
	this->IsValid = obj.IsValid;
}
DM_Arrow& DM_Arrow::operator=(const DM_Arrow& obj)
{
	this->P1 = obj.P1;
	this->P2 = obj.P2;
	this->L = obj.L;
	this->IsValid = obj.IsValid;
	return *this;
}


DM_Sector::DM_Sector():IsValid(false)
{
    this->direction = 2;
    this->type = Sector_ELMT;
}


DM_Sector::DM_Sector(DM_Point center, double inner_radius, double outer_radius,
					 double start_angle, double end_angle)
{
	this->center = center;
	this->innerRadius = inner_radius;
	this->outerRadius = outer_radius;
	this->startAngle = start_angle;
	this->endAngle = end_angle;
	this->outerStartPt = DM_Point(this->center.x + this->outerRadius * cos(this->startAngle),
								  this->center.y + this->outerRadius * sin(this->startAngle));
	this->outerEndPt = DM_Point(this->center.x + this->outerRadius * cos(this->endAngle),
								this->center.y + this->outerRadius * sin(this->endAngle));
	this->innerStartPt = DM_Point(this->center.x + this->innerRadius * cos(this->startAngle),
								  this->center.y + this->innerRadius * sin(this->startAngle));
	this->innerEndPt = DM_Point(this->center.x + this->innerRadius * cos(this->endAngle),
								this->center.y + this->innerRadius * sin(this->endAngle));
	this->IsValid = true;

    this->direction = 2;
    this->type = Sector_ELMT;
}

DM_Rect DM_Sector::getBoundingRect()const
{
	vector<DM_Point> Pts;
	Pts.push_back(this->outerStartPt);
	Pts.push_back(this->outerEndPt);
	Pts.push_back(this->innerStartPt);
	Pts.push_back(this->innerEndPt);

	if (this->startAngle <= this->endAngle)
	{
		if (this->startAngle <= DM_PI_2)
		{
			if (this->endAngle > DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->outerRadius));//通过90度
			if (this->endAngle > DM_PI) Pts.push_back(DM_Point(this->center.x - this->outerRadius, this->center.y));//通过180度
			if (this->endAngle > DM_3PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y - this->outerRadius));//通过270度
		}

		if (DM_PI_2 < this->startAngle&&this->startAngle <= DM_PI)
		{
			if (this->endAngle > DM_PI) Pts.push_back(DM_Point(this->center.x - this->outerRadius, this->center.y));//通过180度
			if (this->endAngle > DM_3PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y - this->outerRadius));//通过270度
		}

		if (DM_PI < this->startAngle&&this->startAngle<=DM_3PI_2&&this->endAngle>=DM_3PI_2)
		{
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->outerRadius));//通过270度
		}

	}
	else
	{
		Pts.push_back(DM_Point(this->center.x + this->outerRadius, this->center.y));//0

		if (this->startAngle <= DM_PI_2)
		{
			Pts.push_back(DM_Point(this->center.x, this->center.y + this->outerRadius));//90
			Pts.push_back(DM_Point(this->center.x - this->outerRadius, this->center.y));//180
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->outerRadius));//270
		}

		else if (DM_PI_2 < this->startAngle&&this->startAngle <= DM_PI)
		{
			Pts.push_back(DM_Point(this->center.x - this->outerRadius, this->center.y));//180
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->outerRadius));//270
			if (this->endAngle > DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->outerRadius));//90
		}

		else if (DM_PI < this->startAngle&&this->startAngle <= DM_3PI_2)
		{
			Pts.push_back(DM_Point(this->center.x, this->center.y - this->outerRadius));//270
			if (this->endAngle > DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->outerRadius));//90
			if (this->endAngle > DM_PI) Pts.push_back(DM_Point(this->center.x - this->outerRadius, this->center.y));//180
		}

		else if (DM_3PI_2 < this->startAngle&&this->startAngle <= DM_2PI)
		{
			if (this->endAngle > DM_PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y + this->outerRadius));//90
			if (this->endAngle > DM_PI) Pts.push_back(DM_Point(this->center.x - this->outerRadius, this->center.y));//180
			if (this->endAngle > DM_3PI_2) Pts.push_back(DM_Point(this->center.x, this->center.y - this->outerRadius));//270
		}
	}

	double xmin = 999999.0, xmax = 0.0, ymin = 999999.0, ymax = 0.0;
	for (size_t i = 0; i < Pts.size(); ++i)
	{
		if (Pts[i].x < xmin) xmin = Pts[i].x;
		if (Pts[i].x > xmax) xmax = Pts[i].x;
		if (Pts[i].y < ymin) ymin = Pts[i].y;
		if (Pts[i].y > ymax) ymax = Pts[i].y;
	}
    return DM_Rect(DM_Point(xmin,ymin), DM_Size(xmax - xmin,ymax - ymin));
}

void DM_Sector::setDirection(int dir)
{
    if(dir < 0)
    {
        this->direction = 0;
    }
    else if(dir > 2)
    {
        this->direction = 2;
    }
    else
    {
        this->direction =dir;
    }
}

bool DM_Sector::isInMat(const Mat& mat)
{
	DM_Rect BRect = this->getBoundingRect();
	return (BRect.leftTop.isInMat(mat) && BRect.rightBottom.isInMat(mat));
}
//dir:查找方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
//查找的基准都是上升沿
int DM_Sector::getSectorEdgePoints(Mat& img, vector<DM_Point>& edge_pts,int dir)
{
	DM_Sector roi = *this;
	if(img.empty()) return -1;//图像为空
	if(!roi.isValid()) return -2;//roi无效
	if(!roi.isInMat(img)) return -3;//roi不在图像中
	if(roi.outerRadius<10.0) return -4;//roi尺寸过小

	const double a = roi.center.x;
	const double b = roi.center.y;
	const double inr = roi.innerRadius;
	const double outr = roi.outerRadius;
	DM_Point InPt, OutPt;
	vector<vector<Point3i>> SampleData;
	const double dt = 1.0/inr;//把圆周角拆分成一个单位长度一个角。内外圆均可,可实验下 稳定性谁高，反正内圆肯定速度更快
	for(double t = roi.startAngle; t<roi.endAngle; t+=dt)
	{//x=a+r·cosθ, y=b+r·sinθ,//圆的参数方程
		vector<Point3i> temp_data;
		subDivide(img, InPt(a+inr*cos(t), b+inr*sin(t)), OutPt(a+outr*cos(t), b+outr*sin(t)), temp_data);
		SampleData.push_back(temp_data);
	}
	//处理每个SampleData，计算中心差分
	vector<vector<int>> CentralDiffs;//存储所有的中心差分
	size_t count_i = SampleData.size();
	for(size_t i = 0; i<count_i; ++i)
	{
		vector<int> temp_central_diff;
		temp_central_diff.push_back(0);//填充第0个
		size_t count_j = SampleData[i].size()-1;
		for(size_t j=1; j<count_j; ++j)
		{
			temp_central_diff.push_back((SampleData[i][j+1].z - SampleData[i][j-1].z));//可以考虑/2一下
		}
		CentralDiffs.push_back(temp_central_diff);
	}
	edge_pts.clear();
	for (size_t i = 0; i < CentralDiffs.size(); ++i)
	{
		size_t index_maxval = 0;
		size_t index_minval = 0;
		for (size_t j = 1; j < CentralDiffs[i].size(); ++j)//由于是中心差分，不看第0个
		{
			if (CentralDiffs[i][index_maxval] < CentralDiffs[i][j])
				index_maxval = j;
			if (CentralDiffs[i][index_minval] > CentralDiffs[i][j])
				index_minval = j;
		}
		if (dir == 1)//从外环找到内环
		{
			if (CentralDiffs[i][index_minval] < 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = SampleData[i][index_minval];
				edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
			}
		}
		else if (dir == 0) //从内环找到外环
		{
			if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
			{
				Point3i p_temp = SampleData[i][index_maxval];
				edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
			}
		}
		else//不分方向查找，找到整条线段上跳变边最大的点
		{
			if (CentralDiffs[i][index_maxval] > abs(CentralDiffs[i][index_minval]))
			{
				if (CentralDiffs[i][index_maxval] > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = SampleData[i][index_maxval];
					edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
				}
			}
			else
			{
				if (abs(CentralDiffs[i][index_minval]) > 5)//如果梯度小于某个值，也就是对比度不够，也不认为是边缘
				{
					Point3i p_temp = SampleData[i][index_minval];
					edge_pts.push_back(DM_Point(p_temp.x, p_temp.y));
				}
			}

		}
	}

#ifdef PC_Debug
	Mat srcBGR(img.size(), CV_8UC3);
	if (img.channels() != 1)
	{
		img.copyTo(srcBGR);
	}
	else
	{
		cvtColor(img, srcBGR, COLOR_GRAY2BGR);
	}
	for (int i = 0; i < edge_pts.size(); i++)
	{
		circle(srcBGR, edge_pts[i].toPoint(), 1, Scalar(0, 0, 255), -1);
	}
	//	DM_drawSector(srcBGR, *this);
#endif

	return int(edge_pts.size());
}

DM_Thread::DM_Thread(vector<DM_Line>& edge_pts, int polarity)
{
	this->type = Thread_ELMT;
}

DM_Thread::DM_Thread(Mat& img, DM_RotatedRect roi)
{
	this->type = Thread_ELMT;
	vector<DM_Line> lines;
	//必须为4的整数个，因为确定一个原始三角形需要4条边

	//获取A侧全部直线
	lines = this->TriangleLines(img, roi.toCvRotatedRect(), 10, 10, 10, 20);
	size_t IndexStartA;
	if (6 > lines.size())
	{
		cout << "lines count is less than 6" << endl;
		this->IsValid = false;
		return;
	}
	//	cout<<"lines count : "<<lines.size()<<endl;

	//先判断一下roi是在左还是右;
	if (roi.center.x < img.cols*0.5)//在左侧
	{
		if (0 < lines[0].k)//左侧，也就是右侧的第一条直线应该为斜率为负的
		{
			IndexStartA = 0;
		}
		else if (0 < lines[1].k)
		{
			IndexStartA = 1;
		}
		else
		{
			cout << "wrong A side thread img!" << endl;
			this->IsValid = false;
			return;
		}
	}
	else//在右侧
	{
		if (0 > lines[0].k)//左侧，也就是右侧的第一条直线应该为斜率为正的
		{
			IndexStartA = 0;
		}
		else if (0 > lines[1].k)
		{
			IndexStartA = 1;
		}
		else
		{
			cout << "wrong A side thread img!" << endl;
			this->IsValid = false;
			return;
		}
	}

	//相邻2条直线求交点，三个连续交点则为原始三角形的三点，分为两侧，分别计算，先计算A侧
	vector<DM_Point> CrossPointA;
	size_t count = lines.size() - 1;
	for (size_t i = IndexStartA; i < count; ++i)
	{
		DM_Point cross;
		lines[i].getCrossPoint(lines[i + 1], cross);
		CrossPointA.push_back(cross);
	}

	//找到顶点和底边点拟合线
	vector<DM_Point> TopCrossPointA;//初始三角的对应底边的顶点
	vector<DM_Point> BaseCrossPointA;//底边的点
	count = CrossPointA.size();
	for (size_t i = 0; i < count; ++i)
	{
		if (0 == i % 2)
		{
			BaseCrossPointA.push_back(CrossPointA[i]);
		}
		else
		{
			TopCrossPointA.push_back(CrossPointA[i]);
		}
	}

	vector<double> Pitches;
	count = TopCrossPointA.size() - 1;
	for (size_t i = 0; i < count; ++i)//所有的顶点螺距
	{
		Pitches.push_back(TopCrossPointA[i].dis_P2P(TopCrossPointA[i + 1]));
	}

	count = BaseCrossPointA.size() - 1;
	for (size_t i = 0; i < count; ++i)//所有的底点螺距
	{
		Pitches.push_back(BaseCrossPointA[i].dis_P2P(BaseCrossPointA[i + 1]));
	}

	//求平均螺距
	double sum = 0.0;
	count = Pitches.size();
	for (size_t i = 0; i < count; ++i)//所有的底点螺距
	{
		sum += Pitches[i];
	}

	this->threadPitch = sum / count;
	this->threadLines = lines;
	this->IsValid = true;
	//	cout<<"pitch : "<<ThreadPitch<<endl;
}

Rect DM_Thread::getBoundingRect() const
{
	return cv::Rect();
}








int DM_Thread::ListdetectSeed(Mat src, Point2i seed)
{
	int count = 0, count2 = 0;
	int i = seed.x;
	int j = seed.y;
	if (src.at<uchar>(j, i) == 0)
	{
		if (j + 1 < src.rows && i >= 0 && i < src.cols)     //下
		{
			count++;
			if (src.at<uchar>(j + 1, i) == 255)     //下
				count2++;
		}

		if (j - 1 >= 0 && i >= 0 && i < src.cols)     //上
		{
			count++;
			if (src.at<uchar>(j - 1, i) == 255)     //上
				count2++;
		}

		if (j >= 0 && j < src.rows && i + 1 < src.cols)//右
		{
			count++;
			if (src.at<uchar>(j, i + 1) == 255)     //右
				count2++;
		}


		if (j >= 0 && j < src.rows && i - 1 >= 0)     //左
		{
			count++;
			if (src.at<uchar>(j, i - 1) == 255)     //左
				count2++;
		}
	}
	if (src.at<uchar>(j, i) == 0 && count != count2)
		return 2;
	else
		return 0;
}

int DM_Thread::Listdetect(Mat src, Point2i seed)
{
	int count = 0, count1 = 0, count2 = 0;
	int i = seed.x;
	int j = seed.y;
	if (src.at<uchar>(j, i) == 0)
	{
		if (j + 1 < src.rows && i >= 0 && i < src.cols)     //下
		{
			count++;
			if (src.at<uchar>(j + 1, i) == 255)     //下
				count2++;
		}

		if (j - 1 >= 0 && i >= 0 && i < src.cols)     //上
		{
			count++;
			if (src.at<uchar>(j - 1, i) == 255)     //上
				count2++;
		}

		if (j >= 0 && j < src.rows && i + 1 < src.cols)//右
		{
			count++;
			if (src.at<uchar>(j, i + 1) == 255)     //右
				count2++;
		}


		if (j >= 0 && j < src.rows && i - 1 >= 0)     //左
		{
			count++;
			if (src.at<uchar>(j, i - 1) == 255)     //左
				count2++;
		}

		if (j - 1 >= 0 && j - 1 < src.rows && i - 1 >= 0)     //左上
		{
			count++;
			if (src.at<uchar>(j - 1, i - 1) == 255)     //左上
				count2++;
		}

		if (j - 1 >= 0 && j - 1 < src.rows && i + 1 < src.cols)//右上
		{
			count++;
			if (src.at<uchar>(j - 1, i + 1) == 255)     //右上
				count2++;
		}

		if (j + 1 >= 0 && j + 1 < src.rows && i + 1 < src.cols)//右下
		{
			count++;
			if (src.at<uchar>(j + 1, i + 1) == 255)     //右下
				count2++;
		}

		if (j + 1 >= 0 && j + 1 < src.rows && i - 1 >= 0)     //左下
		{
			count++;
			if (src.at<uchar>(j + 1, i - 1) == 255)     //左下
				count2++;
		}

		if (j - 1 >= 0 && i - 1 >= 0 && i + 1 < src.cols && j + 1 < src.rows)
		{
			if (src.at<uchar>(j + 1, i) > 3 && src.at<uchar>(j - 1, i) > 3)
				count1++;
			if (src.at<uchar>(j, i + 1) > 3 && src.at<uchar>(j, i - 1) > 3)
				count1++;
		}
	}
	if (src.at<uchar>(j, i) == 0 && count != count2 && count1 == 0 && count2 != 0)
		return 2;
	else
		return 0;
}

void DM_Thread::FindSeed(Mat one, vector<Point2i>& points)
{
	//寻找第一个种子点
	Point2i seed = Point2i(0, 0);
	int FlagSeed = 0;
	//第一列
	for (int j = 1; j < one.rows - 1; j++)
	{
		if (one.at<uchar>(j, 0) == 0 && (one.at<uchar>(j + 1, 0) == 255 || one.at<uchar>(j - 1, 0) == 255))
		{
			seed.x = 0;
			seed.y = j;
			points.push_back(seed);
			FlagSeed = 1;
			break;
		}
	}

	//第一行
	if (FlagSeed == 0)
	{
		for (int i = 1; i < one.cols - 1; i++)
		{
			if (one.at<uchar>(0, i) == 0 && (one.at<uchar>(0, i - 1) == 255 || one.at<uchar>(0, i + 1) == 255))
			{
				seed.x = i;
				seed.y = 0;
				points.push_back(seed);
				FlagSeed = 1;
				break;
			}
		}
	}
	//最后一列
	if (FlagSeed == 0)
	{
		for (int j = 1; j < one.rows - 1; j++)
		{
			if (one.at<uchar>(j, one.cols - 1) == 0 && (one.at<uchar>(j + 1, one.cols - 1) == 255 || one.at<uchar>(j - 1, one.cols - 1) == 255))
			{
				seed.x = one.cols - 1;
				seed.y = j;
				points.push_back(seed);
				FlagSeed = 1;
				break;
			}
		}
	}

	//最后一行
	if (FlagSeed == 0)
	{
		for (int i = 1; i < one.cols - 1; i++)
		{
			if (one.at<uchar>(one.rows - 1, i) == 0 && (one.at<uchar>(one.rows - 1, i - 1) == 255 || one.at<uchar>(one.rows - 1, i + 1) == 255))
			{
				seed.x = i;
				seed.y = one.rows - 1;
				points.push_back(seed);
				FlagSeed = 1;
				break;
			}
		}
	}
	if (points.size() == 0)
		return;


	//第二个种子
	vector<Point2i> TwoSeeds;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			Point2i TwoSeed;
			TwoSeed.x = seed.x + x;
			TwoSeed.y = seed.y + y;
			if ((x != 0 || y != 0) && TwoSeed.x >= 0 && TwoSeed.x < one.cols && TwoSeed.y >= 0 && TwoSeed.y < one.rows)
				TwoSeeds.push_back(TwoSeed);
		}
	}
	//进行种子点查找
	int Flag = 0;
	for (size_t i = 0; i < TwoSeeds.size(); i++)
	{
		int Flagseed = 0;
		Flagseed = ListdetectSeed(one, TwoSeeds[i]);
		if (Flagseed == 2)
			points.push_back(TwoSeeds[i]);
		if (points.size() == 2)
		{
			Flag = 1;
			return;
		}
	}

	if (Flag != 1)
	{
		points.clear();
		for (size_t i = 0; i < TwoSeeds.size(); i++)
		{
			int Flagseed = 0;
			Flagseed = Listdetect(one, TwoSeeds[i]);
			if (Flagseed == 2)
				points.push_back(TwoSeeds[i]);
			if (points.size() == 2)
				return;
		}
	}
}

vector<Point2i> DM_Thread::ListEdgePoints(Mat one, Point2i Left)
{
	vector<Point2i> points[30];
	vector<Point2i> Empty;
	//多边缘提取
	for (int C = 0;; C++)
	{
		Point2i seed;
		FindSeed(one, points[C]);
		if (points[C].size() < 2)
		{
			points[C].clear();
			goto stop;
			//return points[C];
		}
		for (size_t i = 0; i < points[C].size(); i++)
		{
			one.at<uchar>(points[C][i].y, points[C][i].x) = 1;
		}

		//开始循迹
		int Stop = 0;
		int Sum = 0;
		do {
			Sum++;
			Point3i DD;
			seed = points[C][points[C].size() - 1];
			//检测方向
			vector<Point3i> Dir;
			DD.x = seed.x;
			DD.y = seed.y - 1;
			DD.z = 0;
			Dir.push_back(DD);//上
			DD.x = seed.x + 1;
			DD.y = seed.y - 1;
			DD.z = 1;
			Dir.push_back(DD);//右上
			DD.x = seed.x + 1;
			DD.y = seed.y;
			DD.z = 2;
			Dir.push_back(DD);//右
			DD.x = seed.x + 1;
			DD.y = seed.y + 1;
			DD.z = 3;
			Dir.push_back(DD);//右下
			DD.x = seed.x;
			DD.y = seed.y + 1;
			DD.z = 4;
			Dir.push_back(DD);//下
			DD.x = seed.x - 1;
			DD.y = seed.y + 1;
			DD.z = 5;
			Dir.push_back(DD);//左下
			DD.x = seed.x - 1;
			DD.y = seed.y;
			DD.z = 6;
			Dir.push_back(DD);//左
			DD.x = seed.x - 1;
			DD.y = seed.y - 1;
			DD.z = 7;
			Dir.push_back(DD);//左上
			//检测停止
			int OFF = 0;
			for (size_t j = 0; j < Dir.size(); j++)
			{
				if (points[C].size() > 20 && (Dir[j].x > one.cols - 1 || Dir[j].y > one.rows - 1 || Dir[j].y < 0 || Dir[j].x < 0))
				{
					OFF = 1;
					goto off;
				}
				if (Sum > points[C].size())
				{
					OFF = 1;
					goto off;
				}
			}
			//开始八邻域搜索边界点
			int begin = 0;//轮询初始位置变量
			for (int i = 0; i < Dir.size(); i++)
			{
				if (Dir[i].x == points[C][points[C].size() - 2].x && Dir[i].y == points[C][points[C].size() - 2].y)
				{
					begin = Dir[i].z + 1;
					break;
				}
			}

			int end = 0;
			for (size_t i = begin; i <= 7; i++)
			{
				int flag = 0;
				Point2i B;
				if (Dir[i].x >= 0 && Dir[i].x < one.cols && Dir[i].y >= 0 && Dir[i].y < one.rows)
				{
					if (one.at<uchar>(Dir[i].y, Dir[i].x) == 0 && Dir[i].x >= 0 && Dir[i].x < one.cols && Dir[i].y >= 0 && Dir[i].y < one.rows)
					{
						B.y = Dir[i].y;
						B.x = Dir[i].x;
						flag = Listdetect(one, B);
					}
					if (flag == 2)
					{
						seed.x = Dir[i].x;
						seed.y = Dir[i].y;
						one.at<uchar>(Dir[i].y, Dir[i].x) = 1;
						points[C].push_back(seed);
						end = 1;
						break;
					}
				}

			}
			//end为上面是否有符合的点，有的话end=1。
			if (end != 1)
			{
				for (size_t i = 0; i < begin; i++)
				{
					int flag = 0;
					Point2i B;
					if (Dir[i].x >= 0 && Dir[i].x < one.cols && Dir[i].y >= 0 && Dir[i].y < one.rows)\
					{
						if (one.at<uchar>(Dir[i].y, Dir[i].x) == 0 && Dir[i].x >= 0 && Dir[i].x < one.cols && Dir[i].y >= 0 && Dir[i].y < one.rows)
						{
							B.y = Dir[i].y;
							B.x = Dir[i].x;
							flag = Listdetect(one, B);
						}
						if (flag == 2)
						{
							seed.x = Dir[i].x;
							seed.y = Dir[i].y;
							one.at<uchar>(Dir[i].y, Dir[i].x) = 1;
							points[C].push_back(seed);
							break;
						}
					}
				}
			}
off:
			if (OFF == 1)
				Stop = 1;
			////cout<<points[C].size ()<<endl;
			////cout<<"最后一个点："<<points[C][points[C].size ()-1]<<endl;
		} while (Stop == 0);
		for (size_t i = 0; i < points[C].size(); i++)
		{
			points[C][i].x = points[C][i].x + Left.x;
			points[C][i].y = points[C][i].y + Left.y;
		}
	}

stop:
	int F_T = 0;
	int Flag = 0;
	for (int i = 0; i < 20; i++)
	{
		if (points[i].size() > F_T)
		{
			F_T = points[i].size();
			Flag = i;
		}
	}
	return points[Flag];
}

void DM_Thread::MultiFindSeed(Mat one, vector<Point2i>& points)
{
	//寻找第一个种子点
	Point2i seed = Point2i(0, 0);
	int FlagSeed = 0;
	//第一列
	for (int j = 1; j < one.rows - 1; j++)
	{
		if (one.at<uchar>(j, 0) == 0 && (one.at<uchar>(j + 1, 0) + one.at<uchar>(j - 1, 0)) == 255)
		{
			seed.x = 0;
			seed.y = j;
			points.push_back(seed);
			FlagSeed = 1;
			break;
		}
	}


	if (points.size() == 0)
		return;

	//第二个种子
	vector<Point2i> TwoSeeds;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			Point2i TwoSeed;
			TwoSeed.x = seed.x + x;
			TwoSeed.y = seed.y + y;
			if ((x != 0 || y != 0) && TwoSeed.x >= 0 && TwoSeed.x < one.cols && TwoSeed.y >= 0 && TwoSeed.y < one.rows)
				TwoSeeds.push_back(TwoSeed);
		}
	}
	//进行种子点查找
	int Flag = 0;
	for (size_t i = 0; i < TwoSeeds.size(); i++)
	{
		int Flagseed = 0;
		Flagseed = ListdetectSeed(one, TwoSeeds[i]);
		if (Flagseed == 2)
			points.push_back(TwoSeeds[i]);
		if (points.size() == 2)
		{
			Flag = 1;
			return;
		}
	}

	if (Flag != 1)
	{
		points.clear();
		for (size_t i = 0; i < TwoSeeds.size(); i++)
		{
			int Flagseed = 0;
			Flagseed = Listdetect(one, TwoSeeds[i]);
			if (Flagseed == 2)
				points.push_back(TwoSeeds[i]);
			if (points.size() == 2)
				return;
		}
	}
}

void DM_Thread::MultiEdgePoints(Mat Src, Point2i Left, vector<vector<Point2i> >& Points, int Counts)
{
	Mat one = Src.clone();
	vector<Point2i> points;
	for (int S = 0;; S++)
	{
		Point2i seed;
		MultiFindSeed(one, points);
		if (points.size() < 2)
		{
			points.clear();
			return;
		}
		for (size_t i = 0; i < points.size(); i++)
		{
			one.at<uchar>(points[i].y, points[i].x) = 1;
		}
		//开始循迹
		int Stop = 0;
		int Sum = 0;
		do {
			Sum++;
			Point3i DD;
			seed = points[points.size() - 1];
			//检测方向
			vector<Point3i> Dir;
			DD.x = seed.x;
			DD.y = seed.y - 1;
			DD.z = 0;
			Dir.push_back(DD);//上
			DD.x = seed.x + 1;
			DD.y = seed.y - 1;
			DD.z = 1;
			Dir.push_back(DD);//右上
			DD.x = seed.x + 1;
			DD.y = seed.y;
			DD.z = 2;
			Dir.push_back(DD);//右
			DD.x = seed.x + 1;
			DD.y = seed.y + 1;
			DD.z = 3;
			Dir.push_back(DD);//右下
			DD.x = seed.x;
			DD.y = seed.y + 1;
			DD.z = 4;
			Dir.push_back(DD);//下
			DD.x = seed.x - 1;
			DD.y = seed.y + 1;
			DD.z = 5;
			Dir.push_back(DD);//左下
			DD.x = seed.x - 1;
			DD.y = seed.y;
			DD.z = 6;
			Dir.push_back(DD);//左
			DD.x = seed.x - 1;
			DD.y = seed.y - 1;
			DD.z = 7;
			Dir.push_back(DD);//左上
			//检测停止
			int OFF = 0;
			for (size_t j = 0; j < Dir.size(); j++)
			{
				if (points.size() > 20 && (Dir[j].x > one.cols - 1 || Dir[j].y > one.rows - 1 || Dir[j].y < 0 || Dir[j].x < 0))
				{
					OFF = 1;
					goto off;
				}
				if (Sum > points.size())
				{
					OFF = 1;
					goto off;
				}
			}
			//开始八邻域搜索边界点
			int begin = 0;//轮询初始位置变量
			for (size_t i = 0; i < Dir.size(); i++)
			{
				if (Dir[i].x == points[points.size() - 2].x && Dir[i].y == points[points.size() - 2].y)
				{
					begin = Dir[i].z + 1;
					break;
				}
			}

			int end = 0;
			for (size_t i = begin; i <= 7; i++)
			{
				int flag = 0;
				Point2i B;
				if (Dir[i].x >= 0 && Dir[i].x < one.cols&&Dir[i].y >= 0 && Dir[i].y < one.rows)
				{
					if (one.at<uchar>(Dir[i].y, Dir[i].x) == 0 && Dir[i].x >= 0 && Dir[i].x < one.cols && Dir[i].y >= 0 && Dir[i].y < one.rows)
					{
						B.y = Dir[i].y;
						B.x = Dir[i].x;
						flag = Listdetect(one, B);
					}
					if (flag == 2)
					{
						seed.x = Dir[i].x;
						seed.y = Dir[i].y;
						one.at<uchar>(Dir[i].y, Dir[i].x) = 1;
						points.push_back(seed);
						end = 1;
						break;
					}
				}
			}
			//end为上面是否有符合的点，有的话end=1。
			if (end != 1)
			{
				for (size_t i = 0; i < begin; i++)
				{
					int flag = 0;
					Point2i B;
					if (Dir[i].x >= 0 && Dir[i].x < one.cols&&Dir[i].y >= 0 && Dir[i].y < one.rows)
					{
						if (one.at<uchar>(Dir[i].y, Dir[i].x) == 0 && Dir[i].x >= 0 && Dir[i].x < one.cols && Dir[i].y >= 0 && Dir[i].y < one.rows)
						{
							B.y = Dir[i].y;
							B.x = Dir[i].x;
							flag = Listdetect(one, B);
						}
						if (flag == 2)
						{
							seed.x = Dir[i].x;
							seed.y = Dir[i].y;
							one.at<uchar>(Dir[i].y, Dir[i].x) = 1;
							points.push_back(seed);
							break;
						}
					}
				}
			}
off:
			if (OFF == 1)
				Stop = 1;
		} while (Stop == 0);
		//坐标转换
		for (size_t i = 0; i < points.size(); i++)
		{
			points[i].x = points[i].x + Left.x;
			points[i].y = points[i].y + Left.y;
		}

		if (points.size() > Counts)
		{
			Points.push_back(points);
		}


		points.clear();
	}
}




vector<DM_Line> DM_Thread::TriangleLines(Mat Src, RotatedRect Roi, int LX, int RX, int Counts, int ThreshVal)
{
	vector<DM_Line> Lines;
	if (LX < 0 || RX < 0)
		return Lines;

	cv::Rect rect = Roi.boundingRect();
	Point2i Left(rect.x, rect.y), Right(rect.x + rect.width, rect.y + rect.height);

	Mat Block_1;
	Block_1 = Src(Range(Left.y, Right.y), Range(Left.x, Right.x)).clone();

	if (ThreshVal == 0) threshold(Block_1, Block_1, ThreshVal, 255, THRESH_OTSU);
	else threshold(Block_1, Block_1, ThreshVal, 255, THRESH_BINARY);


	//裁剪图
	Mat Detect = Block_1.clone();
	vector<Point2i> detect = ListEdgePoints(Detect, Left);

	int MaxX = 0, MinX = 999999;
	if (detect.size() > 3)
	{
		for (size_t j = 0; j < detect.size(); j++)
		{
			if (detect[j].x > MaxX)
				MaxX = detect[j].x;
			if (detect[j].x < MinX)
				MinX = detect[j].x;
		}

		Left.x = MinX + LX;
		Right.x = MaxX - RX;
	}
	else
	{
		cout << "MinX:" << MinX << endl;
		cout << "MaxX:" << MaxX << endl;
		return Lines;
	}

	//	line(Src, Point(MinX, 0), Point(MinX, Src.rows), Scalar(127));
	//	line(Src, Point(MaxX, 0), Point(MaxX, Src.rows), Scalar(127));
	//	imwrite("ssss.bmp", Src);
	//	cout << "MinX:" << MinX << endl;
	//	cout << "MaxX:" << MaxX << endl;

	Mat Block;
	if (Right.x > Left.x)
	{
		if (Right.x < Src.cols && Left.x>0)
		{
			Block = Src(Range(Left.y, Right.y), Range(Left.x, Right.x)).clone();
			if (ThreshVal == 0) threshold(Block, Block, ThreshVal, 255, THRESH_OTSU);
			else threshold(Block, Block, ThreshVal, 255, THRESH_BINARY);
		}
		else
		{
			cout << "cut err 1" << endl;
			return Lines;
		}
	}
	else
	{
		cout << "cut err 2" << endl;
		return Lines;
	}


	//	imwrite("block.bmp", Block);
	//	imwrite("Block_1.bmp", Block_1);

	vector<vector<Point2i>> points;
	MultiEdgePoints(Block, Left, points, Counts);

	if (points.size() < 4)//小于四组都无法确定一个螺纹初始三角形
	{
		cout << "pts < 4" << endl;
		return Lines;
	}


	for (size_t j = 0; j < points.size(); j++)
	{
		vector<DM_Point> temp_pts;
		temp_pts.reserve(points[j].size());
		for(size_t k = 0;k<points[j].size(); ++k)
		{
			temp_pts.push_back(DM_Point(points[j][k]));
		}
		DM_Line Line(temp_pts);
		if (Line.isValid())
			Lines.push_back(Line);
	}

	return Lines;
}



QString DM_Tool::getType()
{
	switch (this->type)
	{
		case Point_Tool:
		return QStringLiteral("直线上的点");
		case ExtremePoint_Tool:
		return QStringLiteral("极值点");
		case Line_Tool:
		return QStringLiteral("直线");
		case PeakLine_Tool:
		return QStringLiteral("峰值线");
		case Circle_Tool:
		return QStringLiteral("圆");
		case Arc_Tool:
		return QStringLiteral("圆弧");
		case Thread_Tool:
		return QStringLiteral("螺纹");
		case Runout_Tool:
		return QStringLiteral("跳动");
		case LineLineCross_Tool:
		return QStringLiteral("两线交点");
		case PointPointLine_Tool:
		return QStringLiteral("两点连线");
		case LineLineBisector_Tool:
		return QStringLiteral("角平分线");
		case FitLine_Tool:
		return QStringLiteral("拟合线");
		case FitCircle_Tool:
		return QStringLiteral("拟合圆");
		default:
		return QStringLiteral("默认工具");
	}
}



bool DM_ExtremePointTool::generate(cv::Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Point();
	this->element->name = this->name;
	this->extremePoints.clear();
	int Ret = this->ROI.getExtremePoint(img, this->extremePoints, this->findDirection);
	if (0 == Ret)
	{
		IsOK = false;
		this->status = QStringLiteral("没有找到极值点");
		return IsOK;
	}
	switch (Ret)
	{
		case -1:
			IsOK = false;
			this->status = QStringLiteral("图像为空");
		return IsOK;
		case -2:
			IsOK = false;
			this->status = QStringLiteral("roi不在图像中");
		return IsOK;
		case -3:
			IsOK = false;
			this->status = QStringLiteral("roi尺寸过小");
		return IsOK;
		case -4:
			IsOK = false;
			this->status = QStringLiteral("方向错误");
		return IsOK;
		case -5:
			IsOK = false;
			this->status = QStringLiteral("边缘点过少");
		return IsOK;
		default://大于零：采样点个数
		{
			IsOK = true;
			this->status = QStringLiteral("成功");
			double x = 0.0, y = 0.0;
			for (size_t i = 0; i < size_t(Ret); ++i)
			{
				x += this->extremePoints[i].x; y += this->extremePoints[i].y;
			}
			x /= Ret; y /= Ret;//取均值
			dynamic_cast<DM_Point*>(this->element)->x = x;
			dynamic_cast<DM_Point*>(this->element)->y = y;
		}return IsOK;
	}
}

DM_LineTool::DM_LineTool(const DM_RotatedRect& roi, QString name, size_t ID) :
	ROI(roi)
{
	this->type = Line_Tool;
	this->status = QStringLiteral("未生成");
	this->name = name;
	this->toolID = ID;
}

bool DM_LineTool::generate(cv::Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Line();
	this->element->name = this->name;
	this->points.clear();
	int Ret = this->ROI.getRotatedRectEdgePoints(img, this->points);
	switch (Ret)
	{
		case -1:
			IsOK = false;
			this->status = QStringLiteral("图像为空");
		return IsOK;

		case -2:
			IsOK = false;
			this->status = QStringLiteral("roi无效");
		return IsOK;

		case -3:
			IsOK = false;
			this->status = QStringLiteral("roi不在图像中");
		return IsOK;

		case -4:
			IsOK = false;
			this->status = QStringLiteral("roi尺寸过小");
		return IsOK;

		default: {}break;//大于零：采样点个数
	}

	DM_Line outLine= dynamic_cast<DM_Line*>(this->element)->fit_Smart(this->points);//返回1时 能够确保line is valid 也就是拟合成功
	if(outLine.isValid())
	{
		this->IsOK = true;
		this->status = QStringLiteral("拟合成功");
		return this->IsOK;
	}
	else
	{
		this->IsOK = false;
		this->status = QStringLiteral("拟合失败");
		return this->IsOK;
	}
}



bool DM_PeakLineTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Line();
	this->element->name = this->name;

	this->extremePoints.clear();
	int Ret = this->ROI.getExtremePoint(img,this->extremePoints, this->findDirection);
	if (0 == Ret)
	{
		IsOK = false;
		this->status = QStringLiteral("没有找到极值点");
		return IsOK;
	}
	switch (Ret)
	{
		case -1:
			IsOK = false;
			this->status = QStringLiteral("图像为空");
		return IsOK;
		case -2:
			IsOK = false;
			this->status = QStringLiteral("roi不在图像中");
		return IsOK;
		case -3:
			IsOK = false;
			this->status = QStringLiteral("roi尺寸过小");
		return IsOK;
		case -4:
			IsOK = false;
			this->status = QStringLiteral("方向错误");
		return IsOK;
		case -5:
			IsOK = false;
			this->status = QStringLiteral("边缘点过少");
		return IsOK;
		default://大于零：采样点个数
		{
			IsOK = true;
			this->status = QStringLiteral("成功");
			double x = 0.0, y = 0.0;
			for (size_t i = 0; i < size_t(Ret); ++i)
			{
				x += this->extremePoints[i].x; y += this->extremePoints[i].y;
			}
			x /= Ret; y /= Ret;//取均值
			delete this->element;
			if (1 == this->findDirection || 2 == this->findDirection)//x方向上的极值，切线是y方向的
			{
				this->element = new DM_Line(DM_Point(x, ROI.leftTop.y), DM_Point(x, ROI.rightBottom.y));
			}
			else//y方向上的极值，切线是x方向的
			{
				this->element = new DM_Line(DM_Point(ROI.leftTop.x, y), DM_Point(ROI.rightBottom.x, y));
			}
			this->element->name = this->name;
		}return IsOK;
	}
}


bool DM_CircleTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Circle();
	this->element->name = this->name;
	this->points.clear();
	int Ret = this->ROI.getRingEdgePoints(img, this->points,this->findDirection);
	switch (Ret)
	{
		case -1:
			IsOK = false;
			this->status = QStringLiteral("图像为空");
		return IsOK;

		case -2:
			IsOK = false;
			this->status = QStringLiteral("roi无效");
		return IsOK;

		case -3:
			IsOK = false;
			this->status = QStringLiteral("roi不在图像中");
		return IsOK;

		case -4:
			IsOK = false;
			this->status = QStringLiteral("roi尺寸过小");
		return IsOK;

		default: {}break;//大于零：采样点个数
	}

	DM_Circle cir;
	Ret = cir.fit_Smart(this->points, 10.0, 10);//返回1时 能够确保circle is valid 也就是拟合成功
	cout << "cir fit : " << Ret << endl;
	switch (Ret)
	{
		case 1:
			IsOK = true;
			this->status = QStringLiteral("拟合成功");
			delete this->element;
			this->element = new DM_Circle(cir.center, cir.radius);
			this->element->name = this->name;
		return IsOK;
		case -1:
			IsOK = false;
			this->status = QStringLiteral("采样点数目小于3");
		return IsOK;
		case -2:
			IsOK = false;
			this->status = QStringLiteral("拟合失败");
		return IsOK;
		default:
			IsOK = false;
			this->status = QStringLiteral("拟合圆异常返回值");
		return IsOK;
	}
}




bool DM_ArcTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Arc();
	this->element->name = this->name;
	this->points.clear();
	int Ret = this->ROI.getSectorEdgePoints(img,this->points,this->findDirection);
	switch (Ret)
	{
		case -1:
			IsOK = false;
			this->status = QStringLiteral("图像为空");
		return IsOK;

		case -2:
			IsOK = false;
			this->status = QStringLiteral("roi无效");
		return IsOK;

		case -3:
			IsOK = false;
			this->status = QStringLiteral("roi不在图像中");
		return IsOK;

		case -4:
			IsOK = false;
			this->status = QStringLiteral("roi尺寸过小");
		return IsOK;

		default: {}break;//大于零：采样点个数
	}

	DM_Circle cir;
	Ret = cir.fit_Smart(points, 2.0, 10);//返回1时 能够确保circle is valid 也就是拟合成功
	cout << "cir fit : " << Ret << endl;

	Mat srcBGR(img.size(), CV_8UC3);
	switch (Ret)
	{
		case 1:
			IsOK = true;
			this->status = QStringLiteral("拟合成功");
			delete this->element;
			this->element = new DM_Arc(cir.center, cir.radius, this->ROI.startAngle, this->ROI.endAngle);
#ifdef PC_Debug

			if (img.channels() != 1)
			{
				img.copyTo(srcBGR);
			}
			else
			{
				cvtColor(img, srcBGR, COLOR_GRAY2BGR);
			}
			//		DM_drawArc(srcBGR, *(dynamic_cast<DM_Arc*>(this->element)));
			//		DM_drawSector(srcBGR, this->ROI);
#endif


			this->element->name = this->name;
		return IsOK;
		case -1:
			IsOK = false;
			this->status = QStringLiteral("采样点数目小于3");
		return IsOK;
		case -2:
			IsOK = false;
			this->status = QStringLiteral("拟合失败");
		return IsOK;
		default:
			IsOK = false;
			this->status = QStringLiteral("拟合圆弧异常返回值");
		return IsOK;
	}
}



bool DM_ThreadTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Thread();
	this->element->name = this->name;
	if (img.empty() || !ROI.isValid() || !ROI.isInMat(img))
	{
		return false;
	}

	delete this->element;
	this->element = new DM_Thread(img, ROI);
	this->element->name = this->name;
	IsOK = dynamic_cast<DM_Thread*>(this->element)->isValid();
	if (IsOK)
	{
		this->status = QStringLiteral("生成成功");
	}
	else
	{
		this->status = QStringLiteral("生成失败");
	}
	return IsOK;
}


bool DM_LineLineCrossTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Point();
	this->element->name = this->name;
	size_t count_sups = this->superiorsIDs.size();
	if (2 != count_sups)
	{
		this->status = QStringLiteral("选中元素数量不为2");
		IsOK = false;
		return IsOK;
	}
	DM_Tool* tool1 = nullptr;
	for(size_t i = 0; i < tools.size(); i++)
	{
		if(this->superiorsIDs[0] == tools[i]->getToolID())
		{
			tool1 = tools[i];
			break;
		}
	}

	if (!tool1->isOK())
	{
		IsOK = tool1->generate(img, tools);
		if (!IsOK)
		{
			this->status = QStringLiteral("选中元素1生成失败");
			return IsOK;
		}
	}
	if (Line_ELMT != tool1->element->type)
	{
		this->status = QStringLiteral("元素1不是直线");
		IsOK = false;
		return IsOK;
	}
	DM_Line* line1 = dynamic_cast<DM_Line*>(tool1->element);
	if (!line1->isValid())
	{
		this->status = QStringLiteral("直线1无效");
		IsOK = false;
		return IsOK;
	}

	//DM_Tool* tool2 = tools[this->superiorsIDs[1]];
	DM_Tool* tool2 = nullptr;
	for(size_t i = 0; i < tools.size(); i++)
	{
		if(this->superiorsIDs[1] == tools[i]->getToolID())
		{
			tool2 = tools[i];
			break;
		}
	}
	if (!tool2->isOK())
	{
		IsOK = tool2->generate(img, tools);
		if (!IsOK)
		{
			this->status = QStringLiteral("选中元素2生成失败");
			return IsOK;
		}
	}
	if (Line_ELMT != tool2->element->type)
	{
		this->status = QStringLiteral("元素2不是直线");
		IsOK = false;
		return IsOK;
	}
	DM_Line* line2 = dynamic_cast<DM_Line*>(tool2->element);
	if (!line2->isValid())
	{
		this->status = QStringLiteral("直线2无效");
		IsOK = false;
		return IsOK;
	}


	DM_Point point_tmp;//交点
	IsOK = line1->getCrossPoint((*line2), point_tmp);

	if (IsOK)
	{
		dynamic_cast<DM_Point*>(this->element)->x = point_tmp.x;
		dynamic_cast<DM_Point*>(this->element)->y = point_tmp.y;

		this->status = QStringLiteral("计算交点成功");
	}
	else
	{
		this->status = QStringLiteral("计算交点失败");
	}
	return IsOK;
}

bool DM_PointPointLineTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	delete this->element;
	this->element = new DM_Line();
	this->element->name = this->name;
	size_t count_sups = this->superiorsIDs.size();
	if (2 != count_sups)
	{
		this->status = QStringLiteral("选中元素数量不为2");
		IsOK = false;
		return IsOK;
	}

	DM_Tool* tool1 = nullptr;
	for(size_t i = 0; i < tools.size(); i++)
	{
		if(this->superiorsIDs[0] == tools[i]->getToolID())
		{
			tool1 = tools[i];
			break;
		}
	}
	if (!tool1->isOK())
	{
		IsOK = tool1->generate(img, tools);
		if (!IsOK)
		{
			this->status = QStringLiteral("选中元素1生成失败");
			return IsOK;
		}
	}
	if (Point_ELMT != tool1->element->type)
	{
		this->status = QStringLiteral("元素1不是点");
		IsOK = false;
		return IsOK;
	}
	DM_Point* point1 = dynamic_cast<DM_Point*>(tool1->element);
	if (!point1->isValid())
	{
		this->status = QStringLiteral("点1无效");
		IsOK = false;
		return IsOK;
	}

	//DM_Tool* tool2 = tools[this->superiorsIDs[1]];
	DM_Tool* tool2 = nullptr;
	for(size_t i = 0; i < tools.size(); i++)
	{
		if(this->superiorsIDs[1] == tools[i]->getToolID())
		{
			tool2 = tools[i];
			break;
		}
	}
	if (!tool2->isOK())
	{
		IsOK = tool2->generate(img, tools);
		if (!IsOK)
		{
			this->status = QStringLiteral("选中元素2生成失败");
			return IsOK;
		}
	}
	if (Point_ELMT != tool2->element->type)
	{
		this->status = QStringLiteral("元素2不是点");
		IsOK = false;
		return IsOK;
	}
	DM_Point* point2 = dynamic_cast<DM_Point*>(tool2->element);
	if (!point2->isValid())
	{
		status = QStringLiteral("点2无效");
		IsOK = false;
		return IsOK;
	}

	DM_Line line_tmp(*point1, *point2);
	IsOK = line_tmp.isValid();


	if (IsOK)
	{
		delete this->element;
		this->element = new DM_Line(line_tmp.P1, line_tmp.P2);
		this->element->name = this->name;
		this->status = QStringLiteral("计算连线成功");
	}
	else
	{
		this->status = QStringLiteral("计算连线失败");
	}

	return IsOK;
}





DM_Pie::DM_Pie()
{
	this->center = DM_Point();
	this->R = 0;
	this->endAngle = 0;
	this->startAngle = 0;
	this->startPt = DM_Point();
	this->endPt= DM_Point();
	this->IsValid = false;
	this->type = Pie_ELMT;
	this->name = QStringLiteral("扇形");
}

DM_Pie::DM_Pie(DM_Point center, double R, double start_angle, double end_angle)
{
	this->center = center;
	this->R = R;
	this->endAngle = start_angle;
	this->startAngle = end_angle;
	this->startPt = DM_Point(this->center.x + this->R * cos(this->startAngle),this->center.y + this->R * sin(this->startAngle));
	this->endPt = DM_Point(this->center.x + this->R * cos(this->endAngle),this->center.y + this->R * sin(this->endAngle));
	this->IsValid = true;
	this->type = Pie_ELMT;
	this->name = QStringLiteral("扇形");
}

DM_Pie::DM_Pie(DM_Circle circle, double start_angle, double end_angle)
{
	if(circle.isValid())
	{

		this->center = circle.center;
		this->R = circle.radius;
		this->endAngle = start_angle;
		this->startAngle = end_angle;
		this->startPt = DM_Point(this->center.x + this->R * cos(this->startAngle),this->center.y + this->R * sin(this->startAngle));
		this->endPt = DM_Point(this->center.x + this->R * cos(this->endAngle),this->center.y + this->R * sin(this->endAngle));
		this->IsValid = true;
		this->type = Pie_ELMT;
		this->name = QStringLiteral("扇形");
	}
	else
	{
		this->center = DM_Point();
		this->R = 0;
		this->endAngle = 0;
		this->startAngle = 0;
		this->startPt = DM_Point();
		this->endPt= DM_Point();
		this->IsValid = false;
		this->type = Pie_ELMT;
		this->name = QStringLiteral("扇形");
	}

}

bool DM_LineLineBisectorTool::generate(Mat &img, vector<DM_Tool *> &tools)
{
	delete this->element;
	this->element = new DM_Point();
	this->element->name = this->name;
	size_t count_sups = this->superiorsIDs.size();
	if (2 != count_sups)
	{
		this->status = QStringLiteral("选中元素数量不为2");
		IsOK = false;
		return IsOK;
	}
	DM_Tool* tool1 = nullptr;
	for(size_t i = 0; i < tools.size(); i++)
	{
		if(this->superiorsIDs[0] == tools[i]->getToolID())
		{
			tool1 = tools[i];
			break;
		}
	}

	if (!tool1->isOK())
	{
		IsOK = tool1->generate(img, tools);
		if (!IsOK)
		{
			this->status = QStringLiteral("选中元素1生成失败");
			return IsOK;
		}
	}
	if (Line_ELMT != tool1->element->type)
	{
		this->status = QStringLiteral("元素1不是直线");
		IsOK = false;
		return IsOK;
	}
	DM_Line* line1 = dynamic_cast<DM_Line*>(tool1->element);
	if (!line1->isValid())
	{
		this->status = QStringLiteral("直线1无效");
		IsOK = false;
		return IsOK;
	}

	//DM_Tool* tool2 = tools[this->superiorsIDs[1]];
	DM_Tool* tool2 = nullptr;
	for(size_t i = 0; i < tools.size(); i++)
	{
		if(this->superiorsIDs[1] == tools[i]->getToolID())
		{
			tool2 = tools[i];
			break;
		}
	}
	if (!tool2->isOK())
	{
		IsOK = tool2->generate(img, tools);
		if (!IsOK)
		{
			this->status = QStringLiteral("选中元素2生成失败");
			return IsOK;
		}
	}
	if (Line_ELMT != tool2->element->type)
	{
		this->status = QStringLiteral("元素2不是直线");
		IsOK = false;
		return IsOK;
	}
	DM_Line* line2 = dynamic_cast<DM_Line*>(tool2->element);
	if (!line2->isValid())
	{
		this->status = QStringLiteral("直线2无效");
		IsOK = false;
		return IsOK;
	}

	DM_Line bisector;
	bisector = line1->getBisector((*line2));

	if (bisector.isValid())
	{
		delete this->element;
		this->element = new DM_Line(bisector);
		this->element->name = this->name;
		this->status = QStringLiteral("计算角平分线成功");
		IsOK = true;
	}
	else
	{
		this->status = QStringLiteral("计算交点失败");
		IsOK = false;
	}
	return IsOK;
}

bool DM_FitLineTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	size_t count_sups = this->superiorsIDs.size();
	if (2 > count_sups)
	{
		this->status = QStringLiteral("选中元素数量小于2个");
		IsOK = false;
		return IsOK;
	}

	//检查选中元素 是否全部ok，是否全是点，顺便获取所有点
	vector<DM_Point> pts;
	pts.reserve(superiorsIDs.size());
	for(size_t i = 0; i<superiorsIDs.size(); ++i)
	{
		for(size_t j = 0; j<tools.size(); ++j)
		{
			if(this->superiorsIDs[i] == tools[j]->getToolID())
			{
				cout<<"sup elmt : "<<i<<endl;
				DM_Tool* temp_tool = tools[j];
				if(!temp_tool->isOK())
				{
					cout<<"sup elmt : "<<i<<" is ng"<<endl;
					IsOK = temp_tool->generate(img, tools);
					if (!IsOK)
					{
						this->status = (QStringLiteral("元素生成失败:")+temp_tool->name);
						return IsOK;
					}
				}
				if(Point_ELMT != temp_tool->element->type)
				{
					cout<<"sup elmt : "<<i<<" is "<<temp_tool->element->type<<endl;
					this->status = (QStringLiteral("元素不是点:")+temp_tool->name);
					IsOK = false;
					return IsOK;
				}
				pts.push_back(*dynamic_cast<DM_Point*>(temp_tool->element));
				break;
			}
		}
	}

	delete this->element;
	this->element = new DM_Line(pts);
	if (element->isValid())
	{
		this->element->name = this->name;
		this->status = QStringLiteral("拟合成功");
		IsOK = true;
	}
	else
	{
		cout<<"fit ng"<<endl;
		this->status = QStringLiteral("拟合失败");
		IsOK = false;
	}
	return IsOK;
}

bool DM_FitCircleTool::generate(Mat& img, vector<DM_Tool*>& tools)
{
	size_t count_sups = this->superiorsIDs.size();
	if (3 > count_sups)
	{
		this->status = QStringLiteral("选中元素数量小于3个");
		IsOK = false;
		return IsOK;
	}

	//检查选中元素 是否全部ok，是否全是点，顺便获取所有点
	vector<DM_Point> pts;
	pts.reserve(superiorsIDs.size());
	for(size_t i = 0; i<superiorsIDs.size(); ++i)
	{
		for(size_t j = 0; j<tools.size(); ++j)
		{
			if(this->superiorsIDs[i] == tools[j]->getToolID())
			{
				DM_Tool* temp_tool = tools[j];
				if(!temp_tool->isOK())
				{
					IsOK = temp_tool->generate(img, tools);
					if (!IsOK)
					{
						this->status = (QStringLiteral("元素生成失败:")+temp_tool->name);
						return IsOK;
					}
				}
				if(Point_ELMT != temp_tool->element->type)
				{
					this->status = (QStringLiteral("元素不是点:")+temp_tool->name);
					IsOK = false;
					return IsOK;
				}
				pts.push_back(*dynamic_cast<DM_Point*>(temp_tool->element));
				break;
			}
		}
	}

	delete this->element;
	this->element = new DM_Circle(pts);
	if (element->isValid())
	{
		this->element->name = this->name;
		this->status = QStringLiteral("拟合成功");
		IsOK = true;
	}
	else
	{
		this->status = QStringLiteral("拟合失败");
		IsOK = false;
	}
	return IsOK;
}



bool DM_matchTemplate(Mat src, Mat templateMat, DM_Point& offset)
{
	if(src.empty()||templateMat.empty()) return false;

	//步骤二：创建一个空画布用来绘制匹配结果
	cv::Mat dstImg;
	dstImg.create(src.dims,src.size,src.type());
	//	cv::imshow("createImg",dstImg);

	//步骤三：匹配，最后一个参数为匹配方式
	cv::matchTemplate(src, templateMat, dstImg, 0);
	//函数介绍
	//void cv::matchTemplate(
	//		cv::InputArray image, // 用于搜索的输入图像
	//		cv::InputArray templ, // 用于匹配的模板，和image类型相同
	//		cv::OutputArray result, // 匹配结果图像
	//		int method // 用于比较的方法
	//		)

	//步骤四：归一化图像矩阵，可省略
	cv::normalize(dstImg, dstImg, 0, 1, 32);

	//步骤五：获取最大或最小匹配系数
	//首先是从得到的 输出矩阵中得到 最大或最小值（平方差匹配方式是越小越好，所以在这种方式下，找到最小位置）
	//找矩阵的最小位置的函数是 minMaxLoc函数
	cv::Point minPoint;
	cv::Point maxPoint;
	double *minVal = 0;
	double *maxVal = 0;
	cv::minMaxLoc(dstImg, minVal, maxVal, &minPoint, &maxPoint);
	offset.x = minPoint.x;
	offset.y = minPoint.y;

	//步骤六：开始正式绘制
	//	cv::rectangle(src, minPoint, cv::Point(minPoint.x + templateMat.cols, minPoint.y + templateMat.rows),
	//				  cv::Scalar(0,255,0), 2, 8);
	//	circle(src, cv::Point(minPoint.x + 15, minPoint.y + 15), 1, Scalar(20, 20, 240), -1, CV_AA);

	//	cv::imwrite("dst.bmp", img1);
	//	cv::imshow("【匹配后的图像】", img1);
	//	cv::rectangle(dstImg, minPoint, cv::Point(minPoint.x + img2.cols, minPoint.y + img2.rows), cv::Scalar(0,0,0), 2, 8);
	//	cv::imshow("【匹配后的计算过程图像】", dstImg);
	//	cv::waitKey(0);

	return true;
}


Mat imgTranslate(Mat& matSrc, DM_Point offset, bool bScale)
{
	Point p = offset.toPoint();
	int xOffset = p.x;
	int yOffset = p.y;
	//判断是否改变图像大小,并设定被复制ROI
	int nRows = matSrc.rows;
	int nCols = matSrc.cols;
	int nRowsRet = 0;
	int nColsRet = 0;
	Rect rectSrc;
	Rect rectRet;
	if (bScale)
	{
		nRowsRet = nRows + abs(yOffset);
		nColsRet = nCols + abs(xOffset);
		rectSrc.x = 0;
		rectSrc.y = 0;
		rectSrc.width = nCols;
		rectSrc.height = nRows;
	}
	else
	{
		nRowsRet = matSrc.rows;
		nColsRet = matSrc.cols;
		if (xOffset >= 0)
		{
			rectSrc.x = 0;
		}
		else
		{
			rectSrc.x = abs(xOffset);
		}
		if (yOffset >= 0)
		{
			rectSrc.y = 0;
		}
		else
		{
			rectSrc.y = abs(yOffset);
		}
		rectSrc.width = nCols - abs(xOffset);
		rectSrc.height = nRows - abs(yOffset);
	}
	// 修正输出的ROI
	if (xOffset >= 0)
	{
		rectRet.x = xOffset;
	}
	else
	{
		rectRet.x = 0;
	}
	if (yOffset >= 0)
	{
		rectRet.y = yOffset;
	}
	else
	{
		rectRet.y = 0;
	}
	rectRet.width = rectSrc.width;
	rectRet.height = rectSrc.height;
	// 复制图像
	Mat matRet(nRowsRet, nColsRet, matSrc.type(), Scalar(255));
	cout<<"rect src : "<<rectSrc.x<<", "<<rectSrc.y<<", "<<rectSrc.width<<", "<<rectSrc.height<<endl;
	cout<<"rect ret : "<<rectRet.x<<", "<<rectRet.y<<", "<<rectRet.width<<", "<<rectRet.height<<endl;
	matSrc(rectSrc).copyTo(matRet(rectRet));
	return matRet;
}

DM_Line DM_Line::fit_Smart(const vector<DM_Point>& pts, int distType, int max_iter)
{
	//先拟合一次，然后计算到样本点相距直线最远距离
	//然后根据输入的直线半粗细 注意是半粗细，和最远距离，每次取中值，反复迭代。直至最远距离-半粗细<=1时，
	//下一步直接用半粗细过滤一次，然后拟合至完全收敛
	//拟合直线
	if (pts.size() < 2)//样本点数小于2，则无法拟合
	{
		this->IsValid = false;//bad
		return DM_Line();
	}
	//记录拟合的原始点
	this->points = pts;

	DM_Line L(pts, distType);//初次拟合
	if (!L.isValid())//拟合失败
	{
		return DM_Line();
	}
	DM_Line outline;
	DM_Line oldLine = L;
	outline = L;
	vector<double> dis;
	double  disGate;
	vector<DM_Point> temp_pts;
	//前面四次为基础拟合，分别剔除掉总点数的80% 70% 60% 50% 40%，最后精细化的拟合全部以40%的点作为参照点
	for (int i = 0; i < max_iter + 5; i++)
	{
		dis.clear();
		for (int j = 0; j < pts.size(); j++)
		{
			dis.push_back(L.dis_P2Line(pts[j]));
		}
		sort(dis.begin(), dis.end());

		int k = 4 > i ? (8 - i) : 4;
		disGate = dis[dis.size()*k / 10];

		temp_pts.clear();
		for (int i = 0; i < pts.size(); i++)//排除干扰点
		{
			if (L.dis_P2Line(pts[i]) < disGate)
			{
				temp_pts.push_back(pts[i]);
			}
		}

		L = DM_Line(temp_pts, distType);//精细拟合
		if (!L.isValid())//拟合失败
		{
			outline = oldLine;
			break;
		}
		if (oldLine.A == L.A && oldLine.B == L.B && oldLine.C == L.C)
		{
			outline = oldLine;
			break;
		}
		oldLine = L;
		outline = L;
	}

	//重新计算端点
	int MinX = pts[0].x, MaxX = pts[0].x, MinY = pts[0].y, MaxY = pts[0].y;
	for (int i = 0; i < pts.size(); ++i)
	{
		if (pts[i].x < MinX) MinX = pts[i].x;
		if (pts[i].x > MaxX) MaxX = pts[i].x;
		if (pts[i].y < MinY) MinY = pts[i].y;
		if (pts[i].y > MaxY) MaxY = pts[i].y;
	}
	//确定定义域，找出数据点的两个端点
	int X_Range = MaxX - MinX;
	int Y_Range = MaxY - MinY;
	if (X_Range > Y_Range)
	{
		outline.P1.x = MinX;
		outline.P1.y = outline.getY(outline.P1.x);
		outline.P2.x = MaxX;
		outline.P2.y = outline.getY(outline.P2.x);
	}
	else
	{
		outline.P1.y = MinY;
		outline.P1.x = outline.getX(outline.P1.y);
		outline.P2.y = MaxY;
		outline.P2.x = outline.getX(outline.P2.y);
	}
	*this = outline;
	return outline;
}

DM_Line::DM_Line(const vector<DM_Point>& pts, int distType, double param, double reps, double aeps)
{
	if (pts.size() < 2)//样本点数小于2，则无法拟合
	{
		this->IsValid = false;//bad
		return;
	}
	//记录拟合的原始点
	this->points = pts;

	vector<Point2i> temp_pts;
	temp_pts.reserve(pts.size());
	for(size_t i =0; i<pts.size(); ++i)
	{
		temp_pts.push_back(pts[i].toPoint());
	}

	cv::Vec4d line_para;
	cv_DM::fitLine(temp_pts, line_para, distType,param, reps, aeps);
	if (line_para[0] == 0 && line_para[1] == 0)
	{
		*this = DM_Line();
	}
	else if (line_para[0] == 0)//斜率不存在的情况
	{
		this->A = -1;
		this->B = 0;
		this->C = line_para[2];
		this->setLine(this->A, this->B, this->C);
	}
	else
	{
		this->A = line_para[1] / line_para[0];
		this->B = -1.0;
		this->C = line_para[3] - this->A * line_para[2];
		this->setLine(this->A, this->B, this->C);
	}
	int MinX = pts[0].x, MaxX = pts[0].x, MinY = pts[0].y, MaxY = pts[0].y;

	for (int i = 0; i < pts.size(); ++i)
	{
		if (pts[i].x < MinX) MinX = pts[i].x;
		if (pts[i].x > MaxX) MaxX = pts[i].x;
		if (pts[i].y < MinY) MinY = pts[i].y;
		if (pts[i].y > MaxY) MaxY = pts[i].y;
	}
	//确定定义域，找出数据点的两个端点
	int X_Range = MaxX - MinX;
	int Y_Range = MaxY - MinY;
	if (X_Range > Y_Range)
	{
		P1.x = MinX;
		P1.y = getY(P1.x);
		P2.x = MaxX;
		P2.y = getY(P2.x);
	}
	else
	{
		P1.y = MinY;
		P1.x = getX(P1.y);
		P2.y = MaxY;
		P2.x = getX(P2.y);
	}
}



DM_Ellipse DM_Ellipse::fitEllipse(const vector<DM_Point>& points)
{
	int i, n = points.size();
	if (n < 5)
		return DM_Ellipse();

	// New fitellipse algorithm, contributed by Dr. Daniel Weiss
	Point2d c(0, 0);
	double gfp[5] = { 0 }, rp[5] = { 0 }, t;
	const double min_eps = 1e-8;

	AutoBuffer<double> _Ad(n * 5), _bd(n);
	double *Ad = _Ad, *bd = _bd;

	// first fit for parameters A - E
	Mat A(n, 5, CV_64F, Ad);
	Mat b(n, 1, CV_64F, bd);
	Mat x(5, 1, CV_64F, gfp);

	for (i = 0; i < n; i++)
	{
		Point2d p = points[i].toPoint2d();
		c += p;
	}
	c.x /= n;
	c.y /= n;

	for (i = 0; i < n; i++)
	{
		Point2d p = points[i].toPoint2d();
		p -= c;

		bd[i] = 10000.0; // 1.0?
		Ad[i * 5] = -(double)p.x * p.x; // A - C signs inverted as proposed by APP
		Ad[i * 5 + 1] = -(double)p.y * p.y;
		Ad[i * 5 + 2] = -(double)p.x * p.y;
		Ad[i * 5 + 3] = p.x;
		Ad[i * 5 + 4] = p.y;
	}

	solve(A, b, x, DECOMP_SVD);

	// now use general-form parameters A - E to find the ellipse center:
	// differentiate general form wrt x/y to get two equations for cx and cy
	A = Mat(2, 2, CV_64F, Ad);
	b = Mat(2, 1, CV_64F, bd);
	x = Mat(2, 1, CV_64F, rp);
	Ad[0] = 2 * gfp[0];
	Ad[1] = Ad[2] = gfp[2];
	Ad[3] = 2 * gfp[1];
	bd[0] = gfp[3];
	bd[1] = gfp[4];
	solve(A, b, x, DECOMP_SVD);

	// re-fit for parameters A - C with those center coordinates
	A = Mat(n, 3, CV_64F, Ad);
	b = Mat(n, 1, CV_64F, bd);
	x = Mat(3, 1, CV_64F, gfp);
	for (i = 0; i < n; i++)
	{
		Point2d p = points[i].toPoint2d();
		p -= c;
		bd[i] = 1.0;
		Ad[i * 3] = (p.x - rp[0]) * (p.x - rp[0]);
		Ad[i * 3 + 1] = (p.y - rp[1]) * (p.y - rp[1]);
		Ad[i * 3 + 2] = (p.x - rp[0]) * (p.y - rp[1]);
	}
	solve(A, b, x, DECOMP_SVD);

	// store angle and radii
	rp[4] = -0.5 * atan2(gfp[2], gfp[1] - gfp[0]); // convert from APP angle usage
	if (abs(gfp[2]) > min_eps)
		t = gfp[2] / sin(-2.0 * rp[4]);
	else // ellipse is rotated by an integer multiple of pi/2
		t = gfp[1] - gfp[0];
	rp[2] = abs(gfp[0] + gfp[1] - t);
	if (rp[2] > min_eps)
		rp[2] = std::sqrt(2.0 / rp[2]);
	rp[3] = abs(gfp[0] + gfp[1] + t);
	if (rp[3] > min_eps)
		rp[3] = std::sqrt(2.0 / rp[3]);

	center.x = (double)rp[0] + c.x;
	center.y = (double)rp[1] + c.y;
	this->a = (double)(rp[2] * 2);
	this->b = (double)(rp[3] * 2);
	if (this->b > this->a)
	{
		double tmp;
		CV_SWAP(this->a, this->b, tmp);

	}
	this->angle = (double)(90 + rp[4] * 180 / CV_PI);
	if (this->angle < -180)
		this->angle += 360;
	if (this->angle > 360)
		this->angle -= 360;
	this->IsValid = true;
	return *this;
}
