#ifndef DM_IMAGEALGORITHM_H
#define DM_IMAGEALGORITHM_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include "DM_ImageFeature.h"
#include <cstring>
#include <iostream>
#include "DM_errorID.h"
#include "DM_ImageFeature.h"
#include  "DM_Element.h"
#include "DM_Label.h"

//using namespace cv;
//using namespace std;
using namespace cv::xfeatures2d;

//图像预处理算法的枚举变量
enum DM_ImgProcess_Tag
{
    DM_IMGPROCESS_DEFAULT_Tag = -1,//图像算法默认参数
    DM_HANDEYECALIBRATION_Tag = 1,//手眼标定（采用棋盘格标定板计算标定图片的特征点）

    DM_THRESHOLD_GENERAL_Tag = 20,//常规二值化
	DM_THRESHOLD_GENERAL_INV_Tag,//常规反向二值化
    DM_THRESHOLD_OTSU_Tag,//常规二值化
    DM_THRESHOLD_ADAPTIVE_Tag,//自适应局部二值化

    DM_CONTOURS_Tag = 40,//查找轮廓

    DM_MOMENTS_Tag = 60,//图像的矩

    DM_COORDINATE_Tag = 80,//坐标系统转换

    DM_HOUGHCIRCLE_Tag = 100,//霍夫圆

	DM_FINDCIRCLE_Tag = 110,//直接查找圆
    DM_FINDCIRCLE_HAND_Tag = 111,//框选拟合圆

    DM_CHESSBOARDCALIBRATION_Tag =120, //棋盘格标定

    DM_MATCHTEMPLATE_Tag =140, //模板匹配

    DM_FEATUREMATCH_Tag = 160,//特征点匹配

	DM_CONTOURSMATCH_Tag = 180, //轮廓匹配

    DM_IMGNOT_Tag = 200,//图像取反

    DM_MORPHOLOGY_DILATE_Tag = 220,//图像膨胀
    DM_MORPHOLOGY_ERODE_Tag = 240,//图像腐蚀
    DM_MORPHOLOGY_OPEN_Tag =260,//图像开操作
    DM_MORPHOLOGY_CLOSE_Tag = 280,//图像闭操作
    DM_MORPHOLOGY_GRADIENT_Tag =300,//图像形态学梯度
    DM_MORPHOLOGY_TOPHAT_Tag =320,//图像顶帽
    DM_MORPHOLOGY_BLACKHAT_Tag =340,//图像黑帽

    DM_MEANBLUR_Tag = 360,//均值滤波
    DM_GAUSSIANBLUR_Tag = 380,//高斯滤波
    DM_MEDIANDMFILTER_Tag = 400,//中值滤波
    DM_BILATERALFILTER_Tag = 420,//双边滤波
};

//图像算法基类
class DM_ImageProcessBase
{
public:
     DM_ImageProcessBase(DM_ImgProcess_Tag proMethod_, std::string str_, DM_ErrorID_Tag errorID_ = DM_error_deafult) :
                         processMethod(proMethod_), message(str_), errorID(errorID_){ ; }
    virtual  ~ DM_ImageProcessBase() { ; }
public:
    virtual int process(cv::Mat src_ = cv::Mat()) = 0;
    virtual cv::Mat getProcessedImage() = 0;//获取经过图像算法处理之后的图片
	virtual cv::Mat getProcessedColorImage() = 0;//获取经过图像算法处理之后的彩色图片
    virtual std::vector<DM_LabelText> getLabelText() = 0;//获取需要需要显示的文字信息

    DM_ImgProcess_Tag getImgProcessMethod() { return this->processMethod; }
    std::string getMessage(){return this->message;}
    DM_ErrorID_Tag getErrorID(){return this->errorID;}
protected:
    DM_ImgProcess_Tag processMethod;//调用预处理方案
    std::string message;//输出运行信息
    DM_ErrorID_Tag errorID;
};


class DM_HandEyeCalibration :public DM_ImageProcessBase
{

public:
    DM_HandEyeCalibration(std::vector<cv::Point2f> cameraPoints_ = std::vector<cv::Point2f>(), std::vector<cv::Point2f> robotPoints_ = std::vector<cv::Point2f>());
    DM_HandEyeCalibration(const DM_HandEyeCalibration &obj);
    DM_HandEyeCalibration operator=(const DM_HandEyeCalibration &obj);
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage(){return this->dst.clone();}
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }
    void setRobotPoints(std::vector<cv::Point2f> points_);//输入机器人的坐标参数
    void setCameraPoints(std::vector<cv::Point2f> points_);//输入相片上的特征点

    std::vector<cv::Point2f> getCameraPoints(){return  this->cameraPoints;}
    std::vector<cv::Point2f> getRobotPoints(){return  this->robotPoints;}
    cv::Mat getTransformMatrix() { return transformMatrix.clone(); }
private:
    int calTransformMatrxi();//获取旋转矩阵
public:
    cv::Mat dst;//该类是不需要图像的，有时为了整个工程的完整性，故和其他类一样增加了一个dst的变量，此处仅仅作为传递，无他用。
	cv::Mat dst_color;//在原图上绘制轮廓
    std::vector<cv::Point2f> cameraPoints;//相机计算出来的9个点的坐标
    std::vector<cv::Point2f> robotPoints;//机器人的9点坐标
    cv::Mat transformMatrix;//转换矩阵
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};



//_____________________________________________________________________________________________________________
//类名及作用：该类主要用于图像二值化
//特殊说明：该二值化类主要分成两类：局部二值化和全局二值化
//参数说明：
// 	@dst;//输出结果，单通道的图片
//######################################全局二值化参数######################################
//	@thresh;//阈值（如果使用OTSU和TRIANGLE方法计算，该阈值自动生成）
//	@maxValue;//使用 CV_THRESH_BINARY 和 CV_THRESH_BINARY_INV 的最大值。
//	@thresholdType;//二值化方法，参见ThreadType_Tag
//######################################局部二值化参数######################################
//	@maxValue;//使用 CV_THRESH_BINARY 和 CV_THRESH_BINARY_INV 的最大值。
//	@thresholdType;//二值化方法，参见ThreadType_Tag
//	@adaptiveMethod;//局部二值化_自适应方案，cv::ADAPTIVE_THRESH_MEAN_C（平均）和cv::ADAPTIVE_THRESH_GAUSSIAN_C（高斯）
//	@blockSize;//局部二值化_素邻域大小: 3, 5, 7, ... ，此处必须为奇数
//	@C;//局部二值化_偏移系数
//返回值：报错码；
//_____________________________________________________________________________________________________________
class DM_Threshold: public  DM_ImageProcessBase
{
public:
//	enum ThreadType_Tag//二值化的方法
//	{
//		//全局二值化(该全局方案和opencv的二值化全局方案的顺序，参数全部一致，方便后续处理，如果后续要增加新方案，不能修改，请在后面添加)
//		THRESH_BINARY_Tag = 0,//过门限的值为最大值，其他值为0
//		THRESH_BINARY_INV_Tag = 1,//过门限的值为0，其他值为最大值
//		THRESH_TRUNC_Tag = 2,//过门限的值为门限值，其他值不变
//		THRESH_TOZERO_Tag = 3,//过门限的值不变，其他设置为0
//		THRESH_TOZERO_INV_Tag = 4,//过门限的值为0，其他不变
//		THRESH_MASK_Tag = 7,//不支持
//		THRESH_OTSU_Tag = 8,//全局阈值使用大津法（基于内建方差，该方案src必须为单通道8bit图）【自动求取阈值】
//		THRESH_TRIANGLE_Tag = 16,//全局阈值使用三角形算法（基于直方图，该方案src必须为单通道8bit图）【自动求取阈值】
//		//局部二值化
//		ADAPTIVE_THRESH_BINARY_Tag = 20,//局部自适应二值化,同“THRESH_BINARY”功能相同
//		ADAPTIVE_THRESH_BINARY_INV_Tag = 21//局部自适应二值化,同“THRESH_BINARY_INV”功能相同
//	};
public:
    DM_Threshold(DM_ImgProcess_Tag proMethod_= DM_THRESHOLD_GENERAL_Tag,double thresh_ = 0,
                 double maxValue_ = 255, int blockSize_ = -1, double C_ = 0);//二值化
	DM_Threshold(const DM_Threshold &obj);
	DM_Threshold& operator=(const  DM_Threshold &obj);
    ~DM_Threshold(){;}
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage(){return dst.clone();}
	cv::Mat getProcessedColorImage() { return this->dst.clone(); }
    std::vector<DM_LabelText> getLabelText() { return std::vector<DM_LabelText>(); }
public:
    cv::Mat dst;//输出结果，单通道的图片
	double thresh;//阈值
	double maxValue;//使用 CV_THRESH_BINARY 和 CV_THRESH_BINARY_INV 的最大值。
	int blockSize;//局部二值化_素邻域大小: 3, 5, 7, ... ，此处必须为奇数
	double C;//局部二值化_偏移系数
};



//图像轮廓查找
class DM_FindContours: public  DM_ImageProcessBase
{
public:
    DM_FindContours(double minAreaThreshold_= -1, double maxAreaThreshold_= -1, int mode_ = cv::RETR_EXTERNAL,int method_ = cv::CHAIN_APPROX_NONE);
	DM_FindContours(const DM_FindContours &obj);
	DM_FindContours operator=(const DM_FindContours &obj);
    ~DM_FindContours(){;}
public:
    int process(cv::Mat src_ = cv::Mat());//该待处理的图像一般为二值化之后的图像
    cv::Mat getProcessedImage(){return dst.clone();}
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<cv::Point2f> getCenterOfMass() { return this->mc; }//反回轮廓的质心
    std::vector<DM_LabelText> getLabelText() { return this->outText; }
public:
    cv::Mat dst;//直接绘制轮廓
	cv::Mat dst_color;//在原图上绘制轮廓
    std::vector<std::vector<cv::Point>> contours;//返回找到的轮廓
    std::vector<double> contourAreas;//返回找到的轮廓对应的面积
    std::vector<cv::Vec4i> hierarchy; //轮廓索引编号
	double minArea;//轮廓的最小面积
	double maxArea;//轮廓的最大面积
public:
	double minAreaThreshold;//设定轮廓的最小面积阈值
	double maxAreaThreshold;//设定轮廓的最大面积阈值（通过函数找出的面积必须介于minArea和maxArea之间）

	//①RETR_EXTERNAL只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略
	//②RETR_LIST   检测所有的轮廓，包括内围、外围轮廓，但是检测到的轮廓不建立等级关系，彼此之间独立，没有等级关系
	//③RETR_CCOMP  检测所有的轮廓，但所有轮廓只建立两个等级关系，外围为顶层
	//④RETR_TREE， 检测所有轮廓，所有轮廓建立一个等级树结构。
	int mode;//轮廓查找模式
	//①CV_CHAIN_APPROX_NONE 保存物体边界上所有连续的轮廓点到contours向量内
	//②CV_CHAIN_APPROX_SIMPLE 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours向量内，拐点与拐点之间直线段上的信息点不予保留
	//③和④：CV_CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使用teh - Chinl chain 近似算法
	int method;	//轮廓定义方式
    std::vector<cv::Point2f> mc;//轮廓的质心
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};

//计算图像的矩，目前只添加了就算质心的代码，后续有需要再添加
class DM_Moment: public DM_ImageProcessBase
{
public:
    DM_Moment(std::vector<std::vector<cv::Point>> contours_ = std::vector<std::vector<cv::Point>>());
	DM_Moment(const DM_Moment &obj);
	DM_Moment operator=(const DM_Moment &obj);
	~DM_Moment() {;}
public:
    int process(cv::Mat src_ = cv::Mat());//
	cv::Mat getProcessedImage() { return dst.clone(); }
	cv::Mat getProcessedColorImage() { return dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }
    std::vector<cv::Point2f> getCenterOfMass() { return this->mc; }
    void setContours(std::vector<std::vector<cv::Point>> contoour_){this->contours = contoour_;}
public:
    cv::Mat dst;//该图像为彩色图像后续不能在处理了，这个是机器坐标的最后一步算法
	cv::Mat dst_color;
public:
    std::vector<std::vector<cv::Point> > contours;//传入的轮廓信息
    std::vector<cv::Moments> mu;//计算的矩
    std::vector<cv::Point2f> mc;//计算的质心
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};


//根据转化矩阵获取目标转化点
class DM_CoordinateTransform :public DM_ImageProcessBase
{
public:
    DM_CoordinateTransform(cv::Mat transformMatrix_ = cv::Mat(), std::vector<cv::Point2f> originalPoints_ = std::vector<cv::Point2f>());
	DM_CoordinateTransform(const DM_CoordinateTransform &obj);
	~DM_CoordinateTransform() { ; }
public:
	int process(cv::Mat src_ = cv::Mat());//算法
	cv::Mat getProcessedImage() { return this->dst;}
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }

    void setOriginalPoints(std::vector<cv::Point2f> points) {this->originalPoints = points;}
	void setTransformMatrix(cv::Mat transformMatrix_){ this->transformMatrix = transformMatrix_; }
    std::vector<cv::Point2f> getOriginalPoints() { return this->originalPoints; }//原始点
    std::vector<cv::Point2f> getObjectPoints() { return this->objectPoints; }//目标点
	cv::Mat getTransformMatrix() { return this->transformMatrix; }//转换矩阵
public:
	cv::Mat dst;//该类是不需要图像的，有时为了整个工程的完整性，故和其他类一样增加了一个dst的变量，此处仅仅作为传递，无他用。
	cv::Mat dst_color;//
private:
	cv::Mat transformMatrix;//转换矩阵
    std::vector<cv::Point2f> originalPoints;//原始点
    std::vector<cv::Point2f> objectPoints;//目标点
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};

//霍夫圆
class DM_HoughCircle :public DM_ImageProcessBase
{
public:
    DM_HoughCircle(double minDist_,double cannyThreshold_, double countThreshold_,int minRadius_ = 0,int maxRadius = 0);
    DM_HoughCircle(const DM_HoughCircle &obj);
    DM_HoughCircle operator= (const DM_HoughCircle &obj);

    ~DM_HoughCircle() { ; }
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage() { return this->dst.clone();}//获取霍夫圆
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }

    std::vector<cv::Vec3f> getCitcles(){return this->circles;}
    std::vector<cv::Point2f> getCircleCenters();

public:
    cv::Mat dst;//该图像为rgb图，即在原图中回事找出来的圆；
	cv::Mat dst_color;
public:
    int method;//检测方法,目前opencv支持HOUGH_GRADIENT
    double dp;//分辨率，dp = 1，累加器的分辨率和原图相同，dp=2，累加器的分辨率为原图的1/2;
    double minDist;//最小圆心距；
    double cannyThreshold;//canny算子的高阈值，canny算子的低阈值为高阈值的一半
    double countThreshold;//构成圆的像素点的阈值
    int minRadius;//待检测圆的最小半径；
    int maxRadius;//待检测圆的最大半径

    std::vector<cv::Vec3f> circles;//检测出来的圆①和②个元素构成圆的圆心，③为圆的半径
//    std::vector<cv::Point2f> centers;//减出来的圆的圆心
//    std::vector<float> radius;//圆的半径
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};

//棋盘格标定
class DM_ChessBoardCalibration :public DM_ImageProcessBase
{
public:
    DM_ChessBoardCalibration(cv::Size chessBoardSize_);
    DM_ChessBoardCalibration(const DM_ChessBoardCalibration &obj);
    DM_ChessBoardCalibration operator=(const DM_ChessBoardCalibration &obj);
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage(){return this->dst.clone();}
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }
    void setChessBordSize(cv::Size chessBoardSize_) { this->chessBoardSize = chessBoardSize_; }//设定棋盘格的规格


    cv::Size  getChessBoardSize() { return this->chessBoardSize; }//获取标定板的规格
    std::vector<cv::Point2f> getFeaturetPoints(){return  this->featurePoints;}

private:
    cv::Mat dst;
	cv::Mat dst_color;
    cv::Size chessBoardSize;//棋盘格的规格（默认棋盘格为4*4）
    std::vector<cv::Point2f> featurePoints;//相机计算出来的9个点的坐标
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};

//模板匹配
class DM_MatchTemplate:public DM_ImageProcessBase
{
public:
    DM_MatchTemplate(cv::Mat templateImg_ = cv::Mat(), double similarity_ = 0.01, cv::Point2f tempGrabP_ = cv::Point2f(-1.0,-1.0));
    DM_MatchTemplate(const DM_MatchTemplate &obj);
    DM_MatchTemplate operator=(const DM_MatchTemplate &obj);
    ~DM_MatchTemplate() {;}
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage(){return this->dst.clone();}
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }

    void setTemplate(cv::Mat img_){img_.copyTo(this->templateImg);}
    void setSimilarity(double similarity_){this->similarity = similarity_;}
    void setTemplateGrabPoint(cv::Point2f p) { this->tempGrabPoint = p; }

    std::vector<cv::Point2f> getGrabPoints() { return this->grabPoints; }
    cv::Point2f getTempGrabPoint() { return this->tempGrabPoint; }
	cv::Mat getTemplate() { return this->templateImg; }
public:
    cv::Mat templateImg;
    cv::Mat dst;
	cv::Mat dst_color;
    double similarity;//判定为模板的相似度阈值

    std::vector<cv::Point> tempPos;//模板的位置
    //std::vector<cv::Point2f> tempCenter;//模板中心的位置
    cv::Point2f tempGrabPoint;//模板的抓取点
    std::vector<cv::Point2f> grabPoints;//抓取点
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};


//特征点匹配
class DM_FeatureMatch_SIFT :public DM_ImageProcessBase
{
public:
    DM_FeatureMatch_SIFT(cv::Mat templateImg_ = cv::Mat(), double  imgScale_ = 1.0, cv::Point2f tempGrabP_ = cv::Point2f(-1.0, -1.0));
	DM_FeatureMatch_SIFT(const DM_FeatureMatch_SIFT &obj);
	DM_FeatureMatch_SIFT operator=(const DM_FeatureMatch_SIFT &obj);
	~DM_FeatureMatch_SIFT() { ; }
public:
	int process(cv::Mat src_ = cv::Mat());//算法
	cv::Mat getProcessedImage() { return this->dst.clone(); }
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }

	void setTemplate(cv::Mat img_) { img_.copyTo(this->templateImg); }
    void setTemplateGrabPoint(cv::Point2f p) { this->tempGrabPoint = p; }

    std::vector<cv::Point2f> getGrabPoints() { return this->grabPoints; }
    cv::Point2f getTempGrabPoint() { return this->tempGrabPoint; }
	cv::Mat getTemplate() { return this->templateImg; }
private:


public:
	cv::Mat templateImg;
	cv::Mat dst;
	cv::Mat dst_color;

    std::vector<std::vector<cv::Point2f>> tempVertices;//被识别图像上，模板的四个端点
    cv::Point2f tempGrabPoint;//模板的抓取点
    std::vector<cv::Point2f> grabPoints;//抓取点
	double imgScale;
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};


//轮廓匹配
class DM_ContoursMatch :public DM_ImageProcessBase
{
public:
    DM_ContoursMatch(std::vector<std::vector<cv::Point>> templateContours_ = std::vector<std::vector<cv::Point>>(), double similarity_ = 0.01);
	DM_ContoursMatch(const DM_ContoursMatch &obj);
	DM_ContoursMatch operator=(const DM_ContoursMatch &obj);
	~DM_ContoursMatch() { ; }
public:
	int process(cv::Mat src_ = cv::Mat());//算法
	cv::Mat getProcessedImage() { return dst.clone(); }
	cv::Mat getProcessedColorImage() { return dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }

    void setTemplateContours(std::vector<std::vector<cv::Point>> templateContours_) {this->templateContours = templateContours_;}
    void setTrianContours(std::vector<std::vector<cv::Point>> trianContours_) { this->trianContours = trianContours_; }
    void setTemplate(std::vector<cv::Mat> img_);//仅仅为了存储模板，便于后续查阅，实际计算不需要该参数
    void setTemplateGrabPoint(std::vector <cv::Point2f> pts) { this->tempGrabPoint = pts; }

    std::vector<cv::Point2f> getTempGrabPoints() { return this->tempGrabPoint; }
    std::vector<cv::Mat> getTemplates() { return this->templateImg; }
    std::vector<std::vector<cv::Point>> getTemplateContours() { return this->templateContours; }
    std::vector<std::vector<cv::Point>> getTrianContours() { return this->trianContours; }
    std::vector<cv::Point2f> getGrabPoints() { return this->grabPoints; }

public:
    std::vector<std::vector<cv::Point>> templateContours;//模板轮廓;
    std::vector<std::vector<cv::Point>> trianContours;//模板轮廓;
    double similarity;//模板相似度
    std::vector<cv::Mat> templateImg;//该参数对于计算没有实际的用途，只是为了后续工程方便查阅实际的模板
    std::vector <cv::Point2f> tempGrabPoint;//模板的抓取点[该参数对于计算没有实际的用途，只是为了后续工程方便查阅实际的模板]

	cv::Mat dst;
	cv::Mat dst_color;
    std::vector<cv::Point2f> grabPoints;//抓取点【该算法默认是抓取质心】
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};

//图像取反
class DM_ImgNot :public DM_ImageProcessBase
{
public:
    DM_ImgNot(): DM_ImageProcessBase(DM_IMGNOT_Tag, "", DM_error_deafult){;}
    DM_ImgNot(const DM_ImgNot &obj);
    DM_ImgNot operator=(const DM_ImgNot &obj);
    ~DM_ImgNot() { ; }
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage() { return dst.clone(); }
	cv::Mat getProcessedColorImage() { return dst.clone(); }
    std::vector<DM_LabelText> getLabelText() { return std::vector<DM_LabelText>(); }
public:
    cv::Mat dst;
};

//形态学操作
class DM_Morphology:public DM_ImageProcessBase
{
public:
    DM_Morphology(DM_ImgProcess_Tag method = DM_MORPHOLOGY_DILATE_Tag,cv::Size kenelSize_ = cv::Size(3,3));
    DM_Morphology(const DM_Morphology &obj);
    DM_Morphology operator=(const DM_Morphology &obj);
    ~DM_Morphology() { ; }
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage() { return dst.clone(); }
    cv::Mat getProcessedColorImage() { return dst.clone(); }
    std::vector<DM_LabelText> getLabelText() { return std::vector<DM_LabelText>(); }
public:
    cv::Mat dst;
    cv::Size kenelSize;//内核
};

//滤波操作[均值滤波/高斯滤波]
class DM_Blur:public DM_ImageProcessBase
{
public:
    DM_Blur(DM_ImgProcess_Tag method = DM_MEANBLUR_Tag,cv::Size kenelSize_ = cv::Size(3,3),
            double sigmaColor_ = 3, double sigmaSpace_ = 3);
    DM_Blur(const DM_Blur &obj);
    DM_Blur operator=(const DM_Blur &obj);
    ~DM_Blur() { ; }
public:
    int process(cv::Mat src_ = cv::Mat());//算法
    cv::Mat getProcessedImage() { return dst.clone(); }
    cv::Mat getProcessedColorImage() { return dst.clone(); }
    std::vector<DM_LabelText> getLabelText() { return std::vector<DM_LabelText>(); }

public:
    cv::Mat dst;
    cv::Size kenelSize;//内核

    double sigmaColor;//色彩空间滤波器，值越大，该像素领域内有越广的颜色会被混合到一起，产生较大的半相等区域
    double sigmaSpace;//坐标空间标准差，值越大，意味着越远的像素会相互影响，从而使更大的区域中足够相似的颜色获取相同的颜色；
};


//查找圆
//该算法的原理：1.将图像二值化，查找轮廓，2.将符合要求的轮廓直接进行圆拟合。
//该方法判定圆的弊端：查找圆的方法简单粗暴，可能很多不是圆的轮廓全部拟合成了圆
class DM_FindCircle :public DM_ImageProcessBase
{
public:
	DM_FindCircle(double binaryzationThreshold_, double countThreshold_, int minRadius_ = 0, 
				  int maxRadius_ = 0, double percent_ = 0, double deviation_ = 10);
	DM_FindCircle(const DM_FindCircle &obj);
	DM_FindCircle operator= (const DM_FindCircle &obj);

	~DM_FindCircle() { ; }
public:
	int process(cv::Mat src_ = cv::Mat());//算法
	cv::Mat getProcessedImage() { return this->dst.clone(); }//获取霍夫圆
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
    std::vector<DM_LabelText> getLabelText() { return this->outText; }
    std::vector<DM_Circle> getCitcles() { return this->circles; }
    std::vector<cv::Point2f> getCircleCenters();
private:
    void circlesEdgeScore(std::vector<std::vector<cv::Point>> contours_, std::vector<DM_Circle> &circles_, std::vector<double> &scoreList_);
    void circlesEdgeScore(std::vector<cv::Point> contours_, DM_Circle &circles_, double &scoreList_);
public:
	double binaryzationThreshold;//二值化阈值，默认为0，则采用OTSU自动查找
	double countThreshold;//构成圆的像素点的阈值，默认为0，则所有的轮廓的全部拟合圆
	double percent;//拟合度，找到的圆和拟合的轮廓边沿的重合的基本重合的点的百分比
	double deviation;//拟合的轮廓和边沿点的允许的偏差
	int minRadius;//待检测圆的最小半径；
	int maxRadius;//待检测圆的最大半径

    std::vector<DM_Circle> circles;//

	cv::Mat dst;//该图像为rgb图，即在原图中回事找出来的圆；
	cv::Mat dst_color;
    std::vector<DM_LabelText> outText;//输出需要显示的文字
};

//查找通过框选区域自动拟合圆
class DM_FindCircle_Hand :public DM_ImageProcessBase
{
public:
	DM_FindCircle_Hand(DM_Ring circlrROI_);
	DM_FindCircle_Hand& operator= (const DM_FindCircle_Hand &obj);

	~DM_FindCircle_Hand() { ; }
public:
	int process(cv::Mat src_ = cv::Mat());//算法
	cv::Mat getProcessedImage() { return this->dst.clone(); }//获取霍夫圆
	cv::Mat getProcessedColorImage() { return this->dst_color.clone(); }
	std::vector<DM_LabelText> getLabelText() {return outText; }
	DM_Circle getCircle() { return this->circle; }
	cv::Point2f getCircleCenter() { return this->circle.center.toPoint2f(); }
public:
	DM_Ring circleROI;//圆的有限ROI
	DM_Circle circle;

	cv::Mat dst;//该图像为rgb图，即在原图中回事找出来的圆；
	cv::Mat dst_color;
	std::vector<DM_LabelText> outText;//输出需要显示的文字
};



#endif // DM_IMAGEALGORITHM_H











