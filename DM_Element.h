#pragma once

#include <QString>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>
#include "DM_Fit.h"
#include "DM_errorID.h"

//using namespace std;
//using namespace cv;
#define DM_PI                 3.1415926535897932384626433832795  // PI
#define DM_PI_4 	          0.78539816339744828                // PI/4     0.25PI     45°
#define DM_PI_2 	          1.5707963267948966                 // PI/2     0.5PI      90°
#define DM_3PI_4              2.3561944901923448                 // 3PI/4    0.75PI     135°
#define DM_3PI_2              4.7123889803846897                 // 3PI/2    1.5PI      270°
#define DM_2PI                6.283185307179586476925286766559   // 2PI                 360°
#define DM_180_PI             57.295779513082323                 // 180/PI   弧度转角度  直接乘上去就行
#define DM_PI_180             0.017453292519943295               // PI/180   角度转弧度  直接乘上去就行
#define DM_1_2PI              0.15915494309189535                // 1/2PI
#define DM_1_PI 	          0.31830988618379069                // 1/PI
#define DM_2_PI 	          0.63661977236758138                // 2/PI

#define DM_eps                1.0e-6                             // 设置绝对误差阈值，当两个数绝对误差很小很小的时候，就认为两者相等；

#define DM_INF                1.0/0.0
#define DM_ISVERTICAL         1.0/0.0                            // 无斜率

typedef signed char           int8;
typedef unsigned char         uint8;
typedef signed int            int32;
typedef unsigned int          uint32;
typedef signed long long      int64;
typedef unsigned long long    uint64;
typedef float                 flt;
typedef double                dbl;
typedef float                 flt32;
typedef double                flt64;

bool isNaN(double x);
bool isInf(double x);//依据: Inf – Inf得到的为NaN

//类的向前声明
class DM_Point;//向量和点都用这个类
class DM_Line;//线
class DM_Ring;//环
class DM_Circle;//圆
class DM_Ellipse;//椭圆
class DM_Arrow;//箭头
class DM_Size;//尺寸
class DM_RotatedRect;//斜矩形
class DM_Arc;//弧线
class DM_Rect;//矩形
class DM_Sector;//扇形
class DM_Thread;//螺纹
class DM_Color;//颜色
class DM_Pie;//扇形

enum Tag_DM
{
	Default_DM = -1,
	Unknown_DM = 0,
	Base_DM = 1,

	Element_DM = 1000,//元素类型
	Point_ELMT = 1100,
	Line_ELMT = 1200,
	Circle_ELMT = 1300,
	Arc_ELMT = 1400,//弧线
	Thread_ELMT = 1500,
	RotatedRect_ELMT = 1600,//斜矩形
	Rect_ELMT = 1700,//矩形
	Pie_ELMT = 1800,//扇形
    Ring_ELMT = 1900,//圆环
    Sector_ELMT = 1910,//扇环

	Tool_DM = 2000,//ROI类型 对应 工具的类型
	Point_Tool = 2100,//直线上的点
	ExtremePoint_Tool,//极值点
	ArcRingExtremePoint_Tool,//弧环极值点
	Line_Tool = 2200,//直线
	PeakLine_Tool,//峰值线
	CenterLine_Tool,//中心线
	Circle_Tool = 2300,//圆
	PeakCircle_Tool,//峰值圆
	Arc_Tool = 2400,//圆弧
	PeakArc_Tool,//峰值圆弧
	Thread_Tool = 2500,//螺纹
	Runout_Tool = 2600,//跳动

	LineLineCross_Tool = 3000,//线线交点    //生成结果是点
	PointPointLine_Tool,//两点连线          //生成结果是线
	LineLineBisector_Tool,//两线角平分线     //生成结果是线
	FitLine_Tool,//拟合线
	FitCircle_Tool,//拟合圆

	Instruction_DM = 5000,//测量指令类型
	PointPointDistance_INS,//点点距离
	PointLineDistance_INS,//点线距离
	PointCircleDistance_INS,//点圆距离
	LineLineDistance_INS,//线线距离
	LineCircleDistance_INS,//线圆距离
	CircleDiameter_INS,//圆径(大直径 小直径 可选)
	ArcRadius_INS,//弧半径
	LineLineAngle_INS,//线线角度

	ThreadPitch_INS = 5100,//螺距
	RunoutValue_INS = 5200,//跳动
	//待续

	//绘图元素的形态
	PaintType = 6000,
	NormalPoint_PT,//普通
	CrossPoint_PT,//正十字交叉点
	SkewCrossPoint_PT,//斜十字交叉点

	SolidLine_PT = 6100,//直线—————
	DashLine_PT,//虚线------
	DotLine_PT,//点线* * * *
	DashDotLine_PT,//点画线*-*-*-
	DashDotDotLine_PT,//点画线**-**-**-

	Location_DM = 7000,//定位工具
	TemplateMatch_LOC,//模板匹配
};
typedef class DM_MeasureElement
{
	public:
		DM_MeasureElement() :type(Element_DM) {}
		virtual ~DM_MeasureElement() {}
		QString getType();
		virtual bool isValid() const {return false;}
	protected:
		//获取指定方向的梯度点
		int subDivide(const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point>& out_pts);//细分
		int subDivide(const DM_Point& p1, const DM_Point& p2, std::vector<cv::Point>& out_pts);//细分
		int subDivide(const cv::Mat& img, const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point3i>& out_pts);//细分并采样
		int subDivide(const cv::Mat& img, const DM_Point& p1, const DM_Point& p2, std::vector<cv::Point3i>& out_pts);//细分并采样
	public:
		Tag_DM type;
		QString name;

}DM_Element;
//点和二维向量均使用这个类
class DM_Point : virtual public DM_MeasureElement
{
	public:
		DM_Point() :x(0.0), y(0.0) {this->type = Point_ELMT;}
		template<typename T> DM_Point(const T &_x, const T &_y) : x(_x), y(_y) {this->type = Point_ELMT;}//int float double
        template<typename T> DM_Point(const cv::Point_<T> &p) : x(p.x), y(p.y) {this->type = Point_ELMT;}
		DM_Point(const DM_Point &obj) :x(obj.x), y(obj.y) {this->type = Point_ELMT;}

		template<typename T> DM_Point& operator ()(const T& _x, const T& _y) { x = _x; y = _y; return *this; }
		bool operator == (const DM_Point &p);
		bool operator != (const DM_Point &p);
		DM_Point& operator=(const DM_Point &p);
        friend std::ostream& operator <<(std::ostream& out, const DM_Point& pt) { out << "(" << pt.x << ", " << pt.y << ")"; return out; }
        friend std::istream& operator >>(std::istream& in, DM_Point& pt) { in >> pt.x >> pt.y; if (!in) { pt(-1.0, -1.0); } return in; }

        cv::Point toPoint() const { return cv::Point(int(x + 0.5), int(y + 0.5)); }//四舍五入
        cv::Point2f toPoint2f() const { return cv::Point2f(float(x), float(y)); }
        cv::Point2d toPoint2d() const { return cv::Point2d(x, y); }

        bool isInMat(const cv::Mat& mat) const;//是否在图像中
		bool isInRect(const cv::Rect& rect)const;//是否在图像中
		bool isValid() const { return !(isNaN(x) || isNaN(y)); }//x, y任意一个为NaN都是无效点
	public:
        double dis_P2P(DM_Point b);//点到点的距离
		DM_Point getRotatePoint(DM_Point centerP, double angle);//计算当前点，围绕centerP旋转angle角度（弧度）之后的坐标
		double getRotateAngle(DM_Point vector);//计算从this向量到vecor向量的旋转角度（弧度）
		bool getPointOfSpecifiedDis(const DM_Point &vector, DM_Point &pt, const double dis)const;//计算距离当前点dis，在指定方向向量vector上的点
		DM_Point getMidPoint(DM_Point P1);//得到两个点的中点；
	public:
		double x, y;
};
class DM_Line: virtual public DM_MeasureElement
{
	public:
		DM_Line();
		DM_Line(const double& a, const double& b, const double& c);//一般式 int float double
		DM_Line(const double& k, const double& m);//斜截式 int float double
		DM_Line(const DM_Point& p, const double& k);//点斜式
		DM_Line(const DM_Point& p1, const DM_Point& p2);//两点式
		DM_Line(cv::Vec4d line_para);//opencv直线表达方法，前两个参数组成方向向量，后两个参数组成直线上面的点
        DM_Line(const std::vector<DM_Point>& pts, int distType = CV_DIST_L2, double param = 0, double reps = 1e-2, double aeps = 1e-2);//最小二乘法拟合
		DM_Line(const DM_Line &obj);
		DM_Line& operator=(const DM_Line &obj);
		bool operator==(const DM_Line &obj);
		bool operator!=(const DM_Line &obj);

		template<typename T>
		void setLine(const T& a, const T& b, const T& c) { *this = DM_Line(a, b, c); }//int float double
		bool isVertical() { return IsVertical; }
        bool isInMat(const cv::Mat& mat) { return (P1.isInMat(mat) && P2.isInMat(mat)); }
		bool isInRect(const cv::Rect& rect) { return (P1.isInRect(rect) && P2.isInRect(rect)); }//是否在矩形中
		bool isValid() const { return IsValid; }
	private:
		bool getLineParam();//获得直线参数
		//获取指定方向的梯度点
		//int subDivide(const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point>& out_pts);
		//int subDivide(cv::Mat& img, const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point3i>& out_pts);
		//判定样本最前面的两个点的距离是不是很近(服务于RANSAC滤波)
        template<typename T>bool DM_verifyComposition(const std::vector<cv::Point_<T>> pts, double disGate = 5.0);
	public:
		//RANSAC滤波
		template<typename T>
        int  LineRANSAC(const std::vector<T> &ptSet, std::vector<T> &pts, DM_Line &L, const double disGate = 2.0, const int percent = 55);//排除干扰点算法
        DM_Line fit_Smart(const std::vector<DM_Point>& pts, int distType = CV_DIST_HUBER, int max_iter = 5);
		//int getRotatedRectEdgePoints(cv::Mat& img, DM_RotatedRect roi, std::vector<cv::Point>& edge_pts, int isH2L = 0);//获取斜方程内梯度方向的点

		//特殊说明：以斜矩形roi的端点的Points[4]中的points[3]->points[2]做为该矩形查找直线的默认方向；
		DM_Line generate(cv::Mat& img, DM_RotatedRect roi, int distType = CV_DIST_HUBER, int max_iter = 5, int isH2L = 0);

		DM_Line getPerpendicular(const DM_Point& p = DM_Point(0.0, 0.0)) const;//垂线
		bool getPerpendicularPoint(const DM_Point &p, DM_Point &crossPoint);//垂点
		DM_Point getMidPoint() const { return DM_Point((P1.x + P2.x)*0.5, (P1.y + P2.y)*0.5); }//中点
		DM_Line getPerpendicularBisector() const { return getPerpendicular(getMidPoint()); }//中垂线
		DM_Line getBisector(DM_Line &line1, bool isSmallAngle = true);//得到两条线的角平分线或者说两条平行线的中线
		bool getCrossPoint(const DM_Line& line, DM_Point& cross) const;//获得线线交点

		double dis_P2Line(const  DM_Point & p);//点到线的距离
		double dis_P2Line(const  DM_Point & p,DM_Line& line_out);//点到线的距离
        double dis_Line2Line(DM_Line line, DM_Line& line_out);//线线距离
		double angle_Line2Line(const DM_Line& line);//线线夹角（弧度）
		double angle_Line2Line(const DM_Line& line,DM_Arc& arc_out);//线线夹角（弧度,输出圆弧）

		double getX(const double& y) const { if (!IsValid) return 0.0; if (IsVertical) return m; else return (y - m) / k; }
		double getY(const double& x) const { if (!IsValid) return 0.0; else return k * x + m; }
		int getX(const int& y) const { return int(getX(double(y)) + 0.5); }
		int getY(const int& x) const { return int(getY(double(x)) + 0.5); }

	public:
		double A, B, C;
		double k, m;//斜率截距，如果无斜率，isVertical为true，则b为x轴截距
		double angle;//倾斜角单位弧度（取值范围-DM_PI/2 - DM_PI/2） 与x轴平行的方向为角度为0，逆时针旋转角度为负，顺时针旋转角度为正
		DM_Point P1, P2;//定义域的范围
		std::vector<DM_Point> points;//拟合直线的原始点
	private:
		bool IsVertical;//是否有斜率
		bool IsValid;//是否有效，有可能 A B同时为零，初始化两点重合的情况。
};
//annular ring 圆环
class DM_Ring: virtual public DM_MeasureElement
{
	public:
        DM_Ring();
        DM_Ring(const DM_Point& center, const double& inradius, const double& outradius,const int& dir = 2);

		DM_Rect getBoundingRect() const;//获取圆环的外接矩形
		bool operator== (const DM_Ring &obj);
		bool operator!= (const DM_Ring &obj) { return !this->operator==(obj); }
		DM_Ring& operator= (const DM_Ring &obj);
        void setDirection(int dir = 2);
		bool isInMat(const cv::Mat& img);
		bool isValid() const { return IsValid; }
	public:
		//dir:查找方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
		//查找的基准都是上升沿
        int getRingEdgePoints(const cv::Mat& img, std::vector<DM_Point>& edge_pts, int dir = 0);
	public:
		DM_Point center;
		double innerRadius, outerRadius;
        int direction;//方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
	private:
		bool IsValid;
};
//圆
class DM_Circle: virtual public DM_MeasureElement
{
	public:
		DM_Circle();
		DM_Circle(const DM_Point& center, const double& radius);
        DM_Circle(const std::vector<cv::Point>& pts);//最小二乘法拟合圆
        DM_Circle(const std::vector<DM_Point>& pts, double half_thick, int max_iter = 10);//最小二乘法拟合圆
        DM_Circle(const std::vector<cv::Point>& pts, double half_thick, int max_iter = 10);//最小二乘法拟合圆
        DM_Circle(const std::vector<DM_Point>& pts);//拟合
		DM_Circle(const DM_Point& p1, const DM_Point& p2, const DM_Point& p3);//计算
		DM_Circle(const cv::Point& p1, const cv::Point& p2, const cv::Point& p3);//计算
		DM_Circle(const DM_Circle &obj);
		DM_Circle& operator=(const DM_Circle &obj);

        bool isInMat(const cv::Mat& mat);
		bool isValid() const { return IsValid; }
	public:
		DM_Rect getBoundingRect() const;
        int fit_Smart(const std::vector<DM_Point>& pts, double half_thick, int max_iter = 10);
        void generate(const cv::Mat& img, DM_Ring ring);
	public:
		DM_Point center;
		double radius;
	private:
		bool IsValid;//是否有效
};
//椭圆默认公式：(X*X)/(b*b) + (Y*Y)/(a*a) = 1
//椭圆旋转平移公式：[(X-X0)*COSα + (Y-Y0)*SINα]^2/b^2 +[(Y-Y0)*COSα - (X-X0)*SINα]^2/a^2 = 1;
//其中α：椭圆旋转角度，（X0，Y0）椭圆心坐标
class DM_Ellipse: virtual public DM_MeasureElement
{
	public:
		DM_Ellipse() :center(0,0), a(0), b(0),angle(0){ IsValid = false; }
		DM_Ellipse(const DM_Point& center, const double& a, const double& b, const double& angle);
		DM_Ellipse(const cv::RotatedRect &rect);//为了配合opencv椭圆的表达方式
        template<typename T> DM_Ellipse(const std::vector<T> &points);//最小二乘法拟合圆

		DM_Ellipse(const DM_Ellipse& obj);
		DM_Ellipse& operator=(const DM_Ellipse& obj);
		bool operator==(const DM_Ellipse& obj);
		bool operator!=(const DM_Ellipse& obj);

		cv::RotatedRect toRotateRect()const;//为了配合opencv的表达方式
		DM_RotatedRect toDM_RotateRect()const;
		bool isValid() const { return IsValid; }
	public:
        DM_Ellipse fitEllipse(const std::vector<DM_Point> & points);//最小二乘法拟合圆
		//智能拟合对分散的干扰点的排除能力很弱，在进行拟合时，尽量先排除分散比较广的点；
		//参数说明：pts：输入的点；
		//        precision: 拟合的精度
		//        max_iter： 拟合次数
		//反馈参数： 0，拟合失败，1拟合成功
        template<typename T> bool fitsmart(const std::vector<T> & pts, double precision = 1.0, int max_iter = 5);
		DM_Ellipse generate(cv::Mat& img, DM_Ring roi, double precision = 1.0, int max_iter = 5, int isH2L = 0);

		bool getVerticalCrossPoint(DM_Point& Pt1, DM_Point& Pt2);//获取椭圆与过椭圆心的直线，在竖直方向的交点
		bool getHorizontalCrossPoint(DM_Point& Pt1, DM_Point& Pt2);//获取椭圆与过椭圆心的直线，在水平方向的交点
		double s() { return (DM_PI_4 * a*b); }//椭圆的面积
	public:
		DM_Point center;//椭圆中心
		double a;//椭圆长轴(Y轴方向的轴)
		double b;//椭圆短轴(X轴方向的轴)
		double angle;//椭圆角度弧度
	private:
		bool IsValid;//是否有效
};
//弧线
class DM_Arc : virtual public DM_MeasureElement
{
	public:
		DM_Arc() :IsValid(false) { this->type = Arc_ELMT; }
		DM_Arc(const DM_Point& start_pt, const DM_Point& mid_pt, const DM_Point& end_pt);//三点计算法
        DM_Arc(const cv::Point& start_pt, const cv::Point& mid_pt, const cv::Point& end_pt);//三点计算法
		DM_Arc(DM_Point center, double radius, double start_angle, double end_angle);
        DM_Arc(const std::vector<DM_Point>& pts);//最小二乘法拟合圆

		DM_Rect getBoundingRect() const;

        bool isInMat(const cv::Mat& mat);
		bool isValid() const { return IsValid; }
	private:
		inline double getStdAngle(const double& angle) { return angle < 0.0 ? angle + DM_2PI : angle; }
	public:
		DM_Point center;
		double radius;
		DM_Point startPoint, endPoint, midPoint;//都是图像上的点 所以是整数坐标
		double startAngle, endAngle;//弧度
        std::vector<DM_Point> points;
	private:
		bool IsValid;
};
//特殊说明：
//构建箭头角度：与主轴线（P1与P2构成的直线）45°
//箭头的大小:在主轴线上找到距离P2为L的点P3，然后以P3和P2为中轴线构建斜矩形宽度为L，取斜矩形的两个端点（靠P1侧的点）和P2构成箭头
class DM_Arrow: virtual public DM_MeasureElement
{
	public:
		DM_Arrow() { IsValid = false; }
		DM_Arrow(DM_Point P1, DM_Point P2, double L);
        std::vector<DM_Point> getVertices()const;//返回四个端点【0-P1，1-P2, 2-箭头端点1，3-箭头的端点2】
		bool isValid() const { return IsValid; }
		DM_Arrow(const DM_Arrow& obj);
		DM_Arrow& operator=(const DM_Arrow& obj);
	public:
		DM_Point P1;//箭头主轴的第1个端点
		DM_Point P2;//箭头主轴的第2个端点
		double L;//箭头长度（以P2为基准）
	private:
		bool IsValid;
};
class DM_Size
{
	public:
		DM_Size():width(0.0), height(0.0), IsValid(false) {}
		template<typename T> DM_Size(const T width, const T height);
		template<typename T> DM_Size(const cv::Size_<T> size);


		template<typename T>
		DM_Size& operator ()(const cv::Size_<T>& size) { this->width = double(size.width); this->height = double(size.height); return *this; }
		template<typename T>
		DM_Size& operator ()(T width, T height) { this->width = width; this->height = height; return *this; }

		DM_Size(const  DM_Size& size);
		DM_Size& operator=(const  DM_Size& size);
		bool operator==(const  DM_Size& size);
		bool operator!=(const  DM_Size& size) { return !this->operator==(size); }

		cv::Size toSize() const { return cv::Size(int(this->width + 0.5), int(this->height + 0.5)); }
		cv::Size2f toSize2f() const { return cv::Size2f(float(this->width), float(this->height)); }
		cv::Size2d toSize2d() const { return cv::Size2d(this->width, this->height); }
		bool isValid() const { return IsValid; }
	public:
		double width, height;
	private:
		bool IsValid;
};
class DM_Rect : virtual public DM_MeasureElement
{
	public:
		DM_Rect() :IsValid(false) {this->type = Rect_ELMT;}
		DM_Rect(const cv::Rect& rcet);
		DM_Rect(const DM_Point& left_top, const DM_Point& right_bottom);
		DM_Rect(const DM_Point& left_top, const DM_Size& size);
		DM_Rect(double center_x, double center_y, double width, double height);

		DM_Rect(const DM_Rect &obj);
		DM_Rect operator=(const DM_Rect &obj);

        std::vector<DM_Point> getVertices() const;//返回四个端点
		cv::Rect toCvRect() const;

        bool isInMat(const cv::Mat& mat) const;
		bool isInRect(const cv::Rect& rect)const;//是否在图像中
		bool isValid() const;
	public:
		//x± y±四个方向的极值点
        int getExtremePoint(cv::Mat& img, std::vector<cv::Point>& extreme_pts, int find_direction);
	public:
		DM_Point leftTop, rightBottom, center;
		DM_Size size;
	private:
		bool IsValid;
};
//该类的特殊说明：以斜矩形的端点的Points[4]中的points[3]->points[2]做为该矩形查找直线的默认方向；
class DM_RotatedRect: virtual public DM_MeasureElement
{
	public:
		DM_RotatedRect():angle(0.0), IsValid(false){}
		DM_RotatedRect(const cv::RotatedRect& rrcet);
		DM_RotatedRect(const DM_Point& center, const DM_Size& size, const double& angle);
		//以axis长度为width，axis的中点为Center，点p距离中轴的距离的二倍为高，
		DM_RotatedRect(const DM_Line& axis, const DM_Point& p);

		DM_RotatedRect(DM_Point pt1, DM_Point pt2, double width);//输入构成中轴线的端点和宽度，该斜矩形以中轴线的长度为高
		DM_RotatedRect(DM_Line axis, double width);//输入构成中轴线和宽度，该斜矩形以中轴线的长度为高

        std::vector<DM_Point> getVertices() const;//返回四个端点
		cv::Rect getBoundingRect() const;
		cv::RotatedRect toCvRotatedRect();
		DM_Arrow getDirArrow(double l = 5.0)const;//获得斜矩形的方向箭头
        bool isInMat(const cv::Mat& mat);
		bool isInRect(const cv::Rect& rect);//是否在图像中
		bool isValid() const;
		//private:
		//获取指定方向的梯度点
		// int subDivide(const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point>& out_pts);
		// int subDivide(cv::Mat& img, const cv::Point& p1, const cv::Point& p2, std::vector<cv::Point3i>& out_pts);

	public:
        int getRotationRectImage(const cv::Mat &src, cv::Mat &dst);//取图
		int getRotatedRectEdgePoints(cv::Mat& img, std::vector<DM_Point>& edge_pts, int isH2L = 0);//获取斜方程内梯度方向的点(默认查找方向：上升沿)
	public:
		DM_Point center;
		DM_Size size;
		double angle;//弧度
		DM_Line axis;
	private:
		bool IsValid;//是否有效，有可能 A B同时为零，初始化两点重合的情况。
};
//annular sector 扇环
class DM_Sector : virtual public DM_MeasureElement
{
	public:
        DM_Sector();
		DM_Sector(DM_Point center, double inner_radius, double outer_radius,
				  double start_angle, double end_angle);

		DM_Rect getBoundingRect()const;
        void setDirection(int dir);
        bool isInMat(const cv::Mat& mat);
		bool isValid() const { return IsValid; }
	public:
		//dir:查找方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
		//查找的基准都是上升沿
        int getSectorEdgePoints(cv::Mat& img,  std::vector<DM_Point>& edge_pts, int dir = 0);
	public:
		DM_Point center;
		double innerRadius, outerRadius;
		double startAngle, endAngle;//起始 结束角   单位弧度
		DM_Point outerStartPt, outerEndPt, innerStartPt, innerEndPt;
        int direction;//方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
	private:
		bool IsValid;
};
//扇形
class DM_Pie: virtual public DM_MeasureElement
{
	public:
		DM_Pie();
		DM_Pie(DM_Point center, double R,double start_angle, double end_angle);
		DM_Pie(DM_Circle circle,double start_angle, double end_angle);

		bool isValid() const { return IsValid; }

	public:
		DM_Point center;
		double R;
		double startAngle, endAngle;//起始 结束角   单位弧度
		DM_Point startPt, endPt;//弧度
	private:
		bool IsValid;
};
//螺纹
class DM_Thread : virtual public DM_MeasureElement
{
	public:
		DM_Thread():IsValid(false){}
        DM_Thread(std::vector<DM_Line>& edge_pts, int polarity);//构成螺纹的直线，极性说明是朝那边的螺纹
        DM_Thread(cv::Mat& img, DM_RotatedRect roi);//构成螺纹的直线，极性说明是朝那边的螺纹

		cv::Rect getBoundingRect() const;

		// bool isInMat(const Mat& mat);
		bool isValid() const { return IsValid; }
	private:
		//四邻域梯度累计判断法
        int ListdetectSeed(cv::Mat src, cv::Point2i seed);
		//梯度累计判断法
        int Listdetect(cv::Mat src, cv::Point2i seed);
		//寻找种子点
        void FindSeed(cv::Mat one, std::vector<cv::Point2i> &points);
		//提取序列边缘点
        std::vector<cv::Point2i> ListEdgePoints(cv::Mat one, cv::Point2i Left);
		//多边缘图寻找种子点
        void MultiFindSeed(cv::Mat one, std::vector<cv::Point2i> &points);
		//多边缘提取
        void MultiEdgePoints(cv::Mat Src, cv::Point2i Left, std::vector<std::vector<cv::Point2i>> &Points, int Counts);
		//螺纹三角直线提取
        std::vector<DM_Line> TriangleLines(cv::Mat Src, cv::RotatedRect Roi, int LX, int RX, int Counts, int ThreshVal);
	public:
		double threadAngle;//螺纹角
		double threadPitch;//螺距
		DM_Line smallDiameterLine, largeDiameterLine;//外螺纹小径和大径的线，小径指接近下方为黑的，大径指上方是白色的
        std::vector<DM_Line> threadLines;//构成螺纹的所有边缘点
	private:
		bool IsValid;
};



class DM_Tool
{
	public:
		DM_Tool() :type(Tool_DM), element(nullptr), IsOK(false),
			name(QStringLiteral("默认工具")), status(QStringLiteral("默认状态")),toolID(0)
		{
			this->element = new DM_MeasureElement();//避免空指针
		}
		virtual ~DM_Tool() { delete this->element; }
        virtual bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools) = 0;//从img上根据ROI，生成对应的Element  点、线、圆、圆弧  return是否成功
		QString getType();//输出工具类型对应的汉字
		QString getStatus() { return this->status; }//根据generate的运行状态输出对应的汉字，可以当成调试信息 包含roi越界 算法条件不满足 生成成功 等等
		bool isOK() { return IsOK; }
		void setToolID(size_t ID = 0){this->toolID = ID;}
		size_t getToolID() {return this->toolID;}

	public:
		DM_Element* element;
		Tag_DM type;//这两个要写入文件中
		QString name;//这两个要写入文件中
		//上下级工具，也就是 依赖关系， 该工具依赖上级工具，被下级工具依赖，所以在删除工具时一定要关联删除
		//上级工具数目为零说明 不依赖其他工具，只需图像和自身参数即可生成元素
        std::vector<size_t> superiorsIDs, inferiorIndexes;//关联工具存储的对象就是toolID
	protected:
		size_t toolID;//每一个工具有一个唯一的编号，主要用于关联tool的调用，使用工具类的同时，按照实际需求分配
		bool IsOK;//generate生成是否成功
		QString status;
};
class DM_ExtremePointTool : virtual public DM_Tool
{
	public:
		DM_ExtremePointTool(const DM_Rect& roi, int find_direction, QString name = QStringLiteral("默认极值点"),size_t ID = 0) :
			ROI(roi),
			findDirection(find_direction)
		{
			this->type = ExtremePoint_Tool;
			this->status = QStringLiteral("未生成");
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Point getElement() const { return *dynamic_cast<DM_Point*>(this->element); }
	public:
		DM_Rect ROI;
		int findDirection;
        std::vector<cv::Point> extremePoints;
};
class DM_LineTool : virtual public DM_Tool
{
	public:
		DM_LineTool(const DM_RotatedRect &roi, QString name = QStringLiteral("默认直线"), size_t ID = 0);
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Line getElement() const { return *dynamic_cast<DM_Line*>(this->element); }
	public:
		DM_RotatedRect ROI;
        std::vector<DM_Point> points;
};
class DM_PeakLineTool : virtual public DM_Tool
{
	public:
		DM_PeakLineTool(const DM_Rect& roi, int find_direction, QString name = QStringLiteral("默认峰值线"),size_t ID = 0) :
			ROI(roi),
			findDirection(find_direction)
		{
			this->type = PeakLine_Tool;
			this->status = QStringLiteral("未生成");
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Line getElement() const { return *dynamic_cast<DM_Line*>(this->element); }
	public:
		DM_Rect ROI;
		int findDirection;
        std::vector<cv::Point> extremePoints;
};
class DM_CircleTool : virtual public DM_Tool
{
	public:
		DM_CircleTool(const DM_Ring& roi, QString name = QStringLiteral("默认圆"),size_t ID = 0,int direction = 0) :
			ROI(roi)
		{
			this->type = Circle_Tool;
			this->status = QStringLiteral("未生成");
			this->name = name;
			this->findDirection = direction;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Circle getElement() const { return *dynamic_cast<DM_Circle*>(this->element); }
	public:
		DM_Ring ROI;
        std::vector<DM_Point> points;
		int findDirection;//查找方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
};
class DM_ArcTool : virtual public DM_Tool
{
	public:
		DM_ArcTool(const DM_Sector& roi, QString name = QStringLiteral("默认圆弧"), size_t ID = 0) :
			ROI(roi)
		{
			this->type = Arc_Tool;
			this->status = QStringLiteral("未生成");
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Arc getElement() const { return *dynamic_cast<DM_Arc*>(this->element); }
	public:
		DM_Sector ROI;
        std::vector<DM_Point> points;
		int findDirection;//查找方向，0-从内环找到外环，1-从外环找到内环，2-不分方向
};
class DM_ThreadTool : virtual public DM_Tool//目前仅有计算螺距线的功能
{
	public:
		DM_ThreadTool(const DM_RotatedRect& roi, QString name = QStringLiteral("默认螺纹"), size_t ID = 0) :
			ROI(roi)
		{
			this->type = Thread_Tool;
			this->status = QStringLiteral("未生成");
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Thread getElement() const { return *dynamic_cast<DM_Thread*>(this->element); }
	public:
		DM_RotatedRect ROI;
		DM_Thread thread;
};
class DM_RunoutTool : virtual public DM_Tool//目前仅有计算螺距线的功能
{
	public:
		DM_RunoutTool(const DM_RotatedRect& roi, QString name = QStringLiteral("默认跳动"), size_t ID = 0) :
			ROI(roi)
		{
			this->type = Runout_Tool;
			this->status = QStringLiteral("未生成");
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools){return true;}//从img上根据ROI，生成对应的Element return是否成功
		DM_RotatedRect& getElement() const { return *dynamic_cast<DM_RotatedRect*>(this->element); }
	public:
		DM_RotatedRect ROI;
		//vector<Point> Points;
};
class DM_LineLineCrossTool : virtual public DM_Tool
{
	public:
		DM_LineLineCrossTool(size_t tool_index1, size_t tool_index2, QString name = QStringLiteral("默认两线交点"), size_t ID = 0)
		{
			this->type = LineLineCross_Tool;
			this->status = QStringLiteral("未生成");
			this->superiorsIDs.push_back(tool_index1);
			this->superiorsIDs.push_back(tool_index2);
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Point getElement() const { return *dynamic_cast<DM_Point*>(this->element); }
	public:
};
class DM_PointPointLineTool : virtual public DM_Tool
{
	public:
		DM_PointPointLineTool(size_t tool_index1, size_t tool_index2, QString name = QStringLiteral("默认两点连线"), size_t ID = 0)
		{
			this->type = PointPointLine_Tool;
			this->status = QStringLiteral("未生成");
			this->superiorsIDs.push_back(tool_index1);
			this->superiorsIDs.push_back(tool_index2);
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Line getElement() const { return *dynamic_cast<DM_Line*>(this->element); }
	public:
};

class DM_LineLineBisectorTool : virtual public DM_Tool
{
	public:
		DM_LineLineBisectorTool(size_t tool_id1, size_t tool_id2, QString name = QStringLiteral("默认角平分线"), size_t ID = 0)
		{
			this->type = LineLineBisector_Tool;
			this->status = QStringLiteral("未生成");
			this->superiorsIDs.push_back(tool_id1);
			this->superiorsIDs.push_back(tool_id2);
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Line getElement() const { return *dynamic_cast<DM_Line*>(this->element); }
	public:
};

class DM_FitLineTool : virtual public DM_Tool
{
	public:
        DM_FitLineTool(std::vector<size_t> ids, QString name = QStringLiteral("默认拟合线"), size_t ID = 0)
		{
			this->type = FitLine_Tool;
			this->status = QStringLiteral("未生成");
			this->superiorsIDs = ids;
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Line getElement() const { return *dynamic_cast<DM_Line*>(this->element); }
	public:
};

class DM_FitCircleTool : virtual public DM_Tool
{
	public:
        DM_FitCircleTool(std::vector<size_t> ids, QString name = QStringLiteral("默认拟合圆"), size_t ID = 0)
		{
			this->type = FitCircle_Tool;
			this->status = QStringLiteral("未生成");
			this->superiorsIDs = ids;
			this->name = name;
			this->toolID = ID;
		}
        bool generate(cv::Mat& img, std::vector<DM_Tool*>& tools);//从img上根据ROI，生成对应的Element return是否成功
		DM_Circle getElement() const { return *dynamic_cast<DM_Circle*>(this->element); }
	public:
};




//=====================================================函数实现=======================================================================


//==================================fitlineSmart参数说明========================================
//功能：智能拟合
//	pts：输入的待拟合的点的点集
//  half_thick：拟合精度
//  max_iter: 拟合次数
//  返回值：
//         1：拟合成功
//         0：拟合失败
//         -1：采样点数小于2，不能拟合
//==============================================================================================


//判定样本最前面的两个点的距离是不是很近
template<typename T>
bool DM_Line::DM_verifyComposition(const std::vector<cv::Point_<T>> pts, double disGate)
{
	if (pts.size() < 2)
	{
		return false;
	}
	if (abs(pts[0].x - pts[1].x) < disGate && abs(pts[0].y - pts[1].y) < disGate)
	{
		return false;
	}
	else
	{
		return true;
	}
}
template<typename T>
int  DM_Line::LineRANSAC(const std::vector<T> &ptSet, std::vector<T> &pts, DM_Line &outLine, const double disGate, const int percent)
{
	bool stopflag = false;
	pts.clear();
	if (ptSet.size() < 2)
	{
		outLine = DM_Line();
		return -1;
	}
	//粗略过滤一遍
	int gate = ptSet.size() * percent / 100;
	for (int i = 0; i + 1 < ptSet.size() && !stopflag; i++)
	{
		for (int j = ptSet.size() - 1; j > i && !stopflag; j--)  //每轮比较n-1-i次
		{
            std::vector<Point> pt_sam;
			pt_sam.clear();
			pt_sam.push_back(ptSet[i]);
			pt_sam.push_back(ptSet[j]);

			if (!DM_verifyComposition(pt_sam))//两直线中的两点不能相聚太近
			{
				continue;
			}
			outLine = DM_Line(pt_sam);
			if (!outLine.isValid())
			{
				continue;
			}
			for (int k = 0; k < ptSet.size(); k++)
			{
				if (outLine.dis_P2Line(ptSet[k]) < disGate)
				{
					pt_sam.push_back(ptSet[k]);
				}
			}
			//记录下此时的点数
			if (pt_sam.size() >= pts.size())
			{
				pts.clear();
				pts = pt_sam;

			}
			if (pts.size() > gate)
			{
				stopflag = true;
				break;
			}
		}
	}
	outLine = DM_Line(pts, CV_DIST_HUBER);
	//精细过滤一遍
	if (outLine.isValid())
	{
		pts.clear();
		for (int k = 0; k < ptSet.size(); k++)
		{
			if (outLine.dis_P2Line(ptSet[k]) < disGate)
			{
				pts.push_back(ptSet[k]);
			}
		}
		outLine = DM_Line(pts, CV_DIST_HUBER);
	}
	return 1;
}
//最小二乘法拟合圆
template<typename T>
DM_Ellipse::DM_Ellipse(const std::vector<T> &points)
{
	int i, n = points.size();
	if (n < 5)
		return;

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
		Point2d p = points[i];
		c += p;
	}
	c.x /= n;
	c.y /= n;

	for (i = 0; i < n; i++)
	{
		Point2d p = points[i];
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
		Point2d p = points[i];
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


	this->angle = (double)(DM_PI_2 + rp[4]);
	if (this->angle < -DM_PI)
		this->angle += DM_2PI;
	if (this->angle > DM_2PI)
		this->angle -= DM_2PI;
	//    this->angle = (double)(90 + rp[4] * 180 / CV_PI);
	//    if (this->angle < -180)
	//        this->angle += 360;
	//    if (this->angle > 360)
	//        this->angle -= 360;
	this->IsValid = true;
}
//反馈参数说明： -1：输入的点的个数太少，不发生拟合
template<typename T>
bool DM_Ellipse::fitsmart(const std::vector<T> & pts, double precision, int max_iter)//最小二乘法拟合圆
{
	if (pts.size() < 5)
	{
		*this = DM_Ellipse();
		return false;
	}
	//第1次拟合
	this->fitEllipse(pts);
	//*this = obj;

	Point2d f1, f2;//两焦点
	double AA, BB, CC;
	AA = a * 0.5;
	BB = b * 0.5;
	CC = sqrt(AA*AA - BB * BB);
	f1 = Point2d(center.x - CC * sin(angle*DM_PI_180), center.y + CC * cos(angle*DM_PI_180));
	f2 = Point2d(center.x + CC * sin(angle*DM_PI_180), center.y - CC * cos(angle*DM_PI_180));
    std::vector<T> temp_pts;
	temp_pts.clear();
	for (int i = 0; i < pts.size(); ++i)//过滤
	{
		DM_Point p(pts[i].x, pts[i].y);
		if (abs(p.dis_P2P( f1) + p.dis_P2P( f2) - 2.0*AA) < 4 * precision)
			temp_pts.push_back(pts[i]);
	}
	if (temp_pts.empty()) return true;

	//第2次拟合
	this->fitEllipse(temp_pts);
	AA = a * 0.5;
	BB = b * 0.5;
	CC = sqrt(AA*AA - BB * BB);
	f1 = Point2d(center.x - CC * sin(angle*DM_PI_180), center.y + CC * cos(angle*DM_PI_180));
	f2 = Point2d(center.x + CC * sin(angle*DM_PI_180), center.y - CC * cos(angle*DM_PI_180));

	temp_pts.clear();
	for (int i = 0; i < pts.size(); ++i)//过滤
	{
		DM_Point p(pts[i].x, pts[i].y);
		if (abs(p.dis_P2P(f1) + p.dis_P2P(f2) - 2.0*AA) < 3 * precision)
			temp_pts.push_back(pts[i]);
	}
	if (temp_pts.empty()) return true;

	//第3次拟合
	this->fitEllipse(temp_pts);
	AA = a * 0.5;
	BB = b * 0.5;
	CC = sqrt(AA*AA - BB * BB);
	f1 = Point2d(center.x - CC * sin(angle*DM_PI_180), center.y + CC * cos(angle*DM_PI_180));
	f2 = Point2d(center.x + CC * sin(angle*DM_PI_180), center.y - CC * cos(angle*DM_PI_180));

	temp_pts.clear();
	for (int i = 0; i < pts.size(); ++i)//过滤
	{
		DM_Point p(pts[i].x, pts[i].y);
		if (abs(p.dis_P2P(f1) + p.dis_P2P(f2) - 2.0*AA) < 2 * precision)
			temp_pts.push_back(pts[i]);
	}
	if (temp_pts.empty()) return true;

	this->fitEllipse(temp_pts);
	DM_Ellipse obj_old = *this;
	//精细化拟合
	for (int k = 0; k < max_iter; k++)
	{
		AA = a * 0.5;
		BB = b * 0.5;
		CC = sqrt(AA*AA - BB * BB);
		f1 = Point2d(center.x - CC * sin(angle*DM_PI_180), center.y + CC * cos(angle*DM_PI_180));
		f2 = Point2d(center.x + CC * sin(angle*DM_PI_180), center.y - CC * cos(angle*DM_PI_180));

		temp_pts.clear();
		for (int i = 0; i < pts.size(); ++i)//过滤
		{
			DM_Point p(pts[i].x, pts[i].y);
			if (abs(p.dis_P2P(f1) + p.dis_P2P(f2) - 2.0*AA) < precision)
				temp_pts.push_back(pts[i]);
		}
		if (temp_pts.empty()) return true;
		this->fitEllipse(temp_pts);
		if (*this == obj_old)
		{
			break;
		}
		obj_old = *this;
	}
	return true;
}


template<typename T> DM_Size::DM_Size(const T width, const T height)
{
	if (width <= 0.0 || height <= 0.0)
	{
		this->width = 0.0;
		this->height = 0.0;
		IsValid = false;
	}
	else
	{
		this->width = width;
		this->height = height;
		IsValid = true;
	}
}
template<typename T> DM_Size::DM_Size(const cv::Size_<T> size)
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



bool DM_matchTemplate(cv::Mat src, cv::Mat templateMat, DM_Point& offset);


cv::Mat imgTranslate(cv::Mat &matSrc, DM_Point offset, bool bScale = false);
