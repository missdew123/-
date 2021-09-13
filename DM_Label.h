#ifndef DM_LABEL_H
#define DM_LABEL_H

#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QDebug>
#include <QPixmap>
#include <QRect>
#include <QPoint>
#include <QWheelEvent>
#include <QPainter>
#include <QRectF>
#include <QString>
#include <QApplication>
#include <QFileDialog>
#include <iostream>
#include "DM_Element.h"

//using namespace cv;

class DM_LabelElement
{
public:
    DM_LabelElement(DM_Element *element_ = nullptr, bool vectorFlag_ = false, QColor color_ = QColor(255,0,0),
                    double width_ = 2,Tag_DM penType_ = SolidLine_PT);
    DM_LabelElement(const DM_LabelElement &obj);
    DM_LabelElement operator=(const DM_LabelElement &obj);
    ~DM_LabelElement();
public:
    DM_Element *element;//绘制元素
    QColor color;//绘制元素
    double penWidth;//线条宽度
    Tag_DM penType;//绘制线条类型/绘制点类型
    bool vectorFlag;//是否是矢量元素（带方向）
};
//绘制文字
class DM_LabelText
{
public:
    DM_LabelText(QString text_ = "",DM_Point pos_ = DM_Point(), QColor color_ = QColor(255, 0, 255),
                 double wordSize_ = 15, double angle_ = 0);
    DM_LabelText(const DM_LabelText &obj);
    DM_LabelText operator=(const DM_LabelText &obj);
    ~DM_LabelText() { ; }
public:
    QString text;//文字
    QColor color;//绘制元素
    double wordSize;//线条宽度
    DM_Point pos;//文字位置
    double angle;//文字角度
};

class DM_Label : public QLabel
{
        Q_OBJECT
    public:
        DM_Label(QWidget *parent = Q_NULLPTR);
        ~DM_Label();
    public:
        //void loadImage(const QImage &src_);//加载图片【该功能暂时屏蔽，所有图片加载只有一个mat通道】
        void loadImage(const cv::Mat &src_);//加载图片

        void moveImageAbs(double dx = -1, double dy = -1);//移动图片(绝对位置)【将rect的topLeft移动到P(dx,dy)】
        inline QRectF getRect()const{return this->rect;}//反馈此时的取图区域

        inline double getZoomValue()const{return this->zoomValue;}//得到当前缩放倍数
        inline double getZoomBase()const{return this->zoomBase;}//得到缩放比例基数

        //以下三个参数一起决定了zoomBase缩放基数，并且决定了缩放梯度的陡峭问题，将缩放次数ZoomTimes调整得越大，缩放梯度越平缓。缩放时，看起来图像越连贯
        void setMaxZoomInTimes(const int  maxZoomInTimes = 10.0); //设置最大放大倍数
        void setMinZoomOutTimes(const int  minZoomOutTimes = 0.1);//设置最小缩小倍数
        void setMaxZoomTimes(const int maxZoomTimes = 40);//设置从最小缩小倍数到最大放大倍数的缩放次数

        void zoomImage(double  zoomValue_ = -1);//缩放图像(X,Y方向都用同一缩放因子)
        void zoomInImage();//放大图像，调用一次放大原图的scaleBase倍；
        void zoomOutImage();//缩小图像，调用一次缩小原图的scaleBase
        void toFitScreen();//将图片调整到适屏
        void setScrollBar(QScrollBar *HScrollBar_,QScrollBar *VScrollBar_);//传入滑动条

        //常用标志的状态设置
        void setCenterCrossFlag(bool flag  = true);//设置是否显示十字中心(true:显示/false:隐藏)
        void changeCenterCrossFlag();//切换是否显示中心十字架
        void setPixelMessageflag(bool flag = true);//设置显示像素信息标志
    public://绘图
       void setShowDrawElementFlag(bool flag = true);//设置显示临时绘制元素的标志
       void setElementIndex(Tag_DM index);//设置绘制元素编号
       void clearDrawStatus();//清除绘图状态,处理偶尔一个元件没有绘制完成，下次绘制的时候不能绘制的问题；
       void setElementType(bool flag = true);//设置绘制元素的类型，true为矢量元素，false为普通元素

       void revocationElements();//撤销上次绘制的内容
       void clearElements();//清除所有的Tool
       bool deleteElements(size_t index);//删除指定位置的Element
       void addElements(DM_LabelElement element_);//添加元素
       void setElements(const std::vector<DM_LabelElement> &element_);//重置element_

       void revocationTexts();//撤销上次添加的文字
       void clearTexts();//清除所有的文字
       bool deleteTexts(size_t index);//删除指定位置的文字
       void addTexts(DM_LabelText text_);//添加文字
       void setTexts(const std::vector<DM_LabelText> &text_);//重置文字
    private:
        void centerCross_paintEvent();//绘制label的中心十字架

        void DM_LabelElement_paintEvent(DM_LabelElement elem);//绘制DM_labelElement
        //绘制直线
        void lineElement_MousePress(QMouseEvent *ev);
        void lineElement_MouseRelease(QMouseEvent *ev);
        void lineElement_MouseMove();

        //绘制矩形
        void rectElement_MousePress(QMouseEvent *ev);
        void rectElement_MouseRelease(QMouseEvent *ev);
        void rectElement_MouseMove();

        //绘制斜矩形
        int drawRotatedRectStep;//绘制旋转矩形的步骤,1画轴，2画矩形
        std::vector<DM_Point> rotatedRectPoints;//绘图过程中构成旋转矩形的三个点（0-1：构成中轴线，2：到中轴线的距离的两倍为矩形宽度）
        void rotatedRectElement_MousePress(QMouseEvent *ev );
        void rotatedRectElement_MouseRelease(QMouseEvent *ev );
        void rotatedRectElement_MouseMove();

        //绘制圆环
        int drawRingStep;//第1-3个点确定中心圆环，第4个点确定大小半径
        std::vector<DM_Point> ringPoints;//绘制过程中产生的点
        void ringElement_MousePress(QMouseEvent *ev);
        void ringElement_MouseRelease(QMouseEvent *ev );
        void ringElement_MouseMove();

        //绘制扇环
        int drawSectorStep;//第1-3个点确定圆，第4个点确定大小半径
        std::vector<DM_Point> sectorPoints;//绘制过程中产生的点
        void sectorElement_MousePress(QMouseEvent *ev);
        void sectorElement_MouseRelease(QMouseEvent *ev);
        void sectorElement_MouseMove();
    private:
        void showImage();//将图片显示到Label上面
        void scale_NEAREST(QImage *src_, QImage *dst_);//临近插值法
        QImage matToQImage(const cv::Mat &inMat);//将mat类型的数据转换成QImage;
        cv::Mat QImageToMat(const QImage &image);//将QImage转化成Mat;
        bool transformLabeToImg_Point(const QPointF &P1, DM_Point &P2);//从 label（显示窗口）坐标系转变到Img(原图坐标系中)；
        bool transformLabeToImg_Line(const QLineF &line1, DM_Line &line2);//从 label（显示窗口）坐标系转变到Img(原图坐标系中)；
        bool transformLabeToImg_L(const double &L1, double &L2);//从 label（显示窗口）坐标系转变到Img(原图坐标系中)_线段长度；

        bool transformImgTolabel_Point(const DM_Point &P1, QPointF &P2);//从 Img(原图)坐标系转变到label(显示窗口)；
        bool transformImgTolabel_Line(const DM_Line &line1, QLineF &line2);//从 Img(原图)坐标系转变到label(显示窗口)；
        bool transformImgTolabel_L(const double &L1, double &L2);//从 Img(原图)坐标系转变到label(显示窗口)_线段长度；

        //以下判定是否在label的元素标准，只有相关元素有一部分在label内就返回true，否者false；
        bool isInLabel(const QPointF P1);//判定该点(以label为坐标系)在不在label内
        bool isInLabel(const DM_Point P1);//判定该点(以图片为坐标系)在不在label内
        bool isInLabel(const std::vector<DM_Point> pts);//判定点集(以图片为坐标系)在不在label内【有一个点在外面就返回flase】
        bool isInLabel(const std::vector<QPointF> pts); //判定点集(以label为坐标系)在不在label内【有一个点在外面就返回flase】
        bool isInLabel(const QLineF line_);//判定线段(以label为坐标系)是不是在显示区域内
        bool isInLabel(const DM_Line line_);//判定线段(以图片为坐标系)是否在显示区域内点；

        bool isInLabel(const QRectF rect_);//判定该矩形(以label为坐标系)是否在label内
        bool isInLabel(const DM_Rect rect_);//判定该矩形(以图片为坐标系)是否在显示区域内点；
        bool isInLabel(const DM_Circle circle_);//判定圆(以图片为坐标系)是否在显示区域内点；
        bool isInLabel(const DM_Arc  arc_);//判定圆弧(以图片为坐标系)是否在显示区域内点；
        bool isInLabel(const DM_Sector  sector_);//判定扇环(以图片为坐标系)是否在显示区域内点；
    private:
        //绘图
        //=============================================以Lablel为坐标系统=================================================================
        //绘制点——部分参数说明：①piontType-绘制点的类型（普通点（默认），十字交叉点,斜交叉点）
        //                   ②D-交叉线的长度，该参数只有选择CrossPoint_PT与SkewCrossPoint_PT类型的点才有效，其他点类型无效
        void drawPoint_Label(QPainter &painter, const QPointF& point,Tag_DM pointType = NormalPoint_PT,double D  = 3);//绘制点集 绘制点
        void drawPoints_Label(QPainter &painter, std::vector<QPointF>& points,Tag_DM pointType = NormalPoint_PT,double D  = 3);//绘制点集

        void drawLine_Label(QPainter &painter, const QLineF& line);//绘制直线
        //绘制矢量线段——部分参数说明：①D-箭头长度，
        void drawDirectedLine_label(QPainter &painter, const QLineF& line,double D  = 8);//绘制矢量直线(带箭头)
        void drawRect_Label(QPainter &painter,const QRectF &rect);//绘制矩形

        //绘制斜矩形
        //特殊说明：如果需要绘制方向，传入的代表斜矩形的四个点，顺序必须由DM_Element中DM_RotatedRect类，端点函数getVertices自动生成，否则画的箭头可能不是想要的方式
        void drawRotatedRect_Label(QPainter &painter,const std::vector<QPointF> &points);//传入四个顶点分别为协矩形的四个端点

        //绘制斜矩形——部分参数说明：①D-箭头长度
        //特殊说明：如果需要绘制方向，传入的代表斜矩形的四个点，顺序必须由DM_Element中DM_RotatedRect类，端点函数getVertices自动生成，否则画的箭头可能不是想要的方式
        void drawDirectedRotatedRect_Label(QPainter &painter,const std::vector<QPointF> &points,double D  = 8);//传入四个顶点分别为协矩形的四个端点

        // //绘制椭圆——部分参数说明：①Rx-X轴方向的半轴，Ry-y轴方向的短半轴）
        void drawEllipse_Label(QPainter &painter,const QPointF &center, const double &Rx, const double &Ry);//绘制椭圆
        void drawEllipse_Label(QPainter &painter,const QRectF &rect);//绘制椭圆
        void drawCircle_Label(QPainter &painter,const QPointF &center, const double &r);//绘制圆
        void drawRing_Label(QPainter &painter,const QPointF &center, const double &innerR, const double &outerR);//绘制圆环
        //绘制带方向的圆环——部分参数说明：①inToOut：绘制的方向，true—从内环到外环，false-从外环到内环    ②D-箭头长度
        void drawDirectedRing_Label(QPainter &painter,const QPointF &center, const double &innerR,
                                    const double &outerR,bool inToOut = true,double D  = 8);//绘制矢量圆环

        //center、Rx、Ry:分别为椭圆的中心，X轴方向的半轴，Y轴方向的半轴，由这三个参数可以构成椭圆（如果是圆，这Rx=Ry=r）
        //startAngle、endAngle:弧的起止角度（特殊说明：①角度为弧度 ②角的正值表示顺时针方向，负值表示逆时针方向，③0度是3点钟的位置）
        void drawArc_Label(QPainter &painter,const QPointF &center, const double &Rx, const double &Ry,
                           const double &startAngle,const double &endAngle);//绘制弧
        //rect:椭圆或者圆的最小外接矩形
        //startAngle、endAngle:弧的起止角度（特殊说明：①角度为弧度 ②角的正值表示逆时针方向，负值表示顺时针方向，③0度是3点钟的位置）
        void drawArc_Label(QPainter &painter,const QRectF &rect,const double &startAngle,const double &endAngle);//绘制弧

        //center、Rx、Ry:分别为椭圆的中心，X轴方向的半轴，Y轴方向的半轴，由这三个参数可以构成椭圆（如果是圆，这Rx=Ry=r）
        //startAngle、endAngle:弧的起止角度（特殊说明：①角度为弧度 ②角的正值表示顺时针方向，负值表示逆时针方向，③0度是3点钟的位置）
        void drawPie_Label(QPainter &painter,const QPointF &center, const double &Rx, const double &Ry,
                           const double &startAngle,const double &endAngle);//绘制扇形
        //rect:椭圆或者圆的最小外接矩形
        //startAngle、endAngle:弧的起止角度（特殊说明：①角度为弧度 ②角的正值表示顺时针方向，负值表示逆时针方向，③0度是3点钟的位置）
        void drawPie_Label(QPainter &painter,const QRectF &rect,const double &startAngle,const double &endAngle);//绘制扇形

        //绘制扇环(这个默认为圆环)
        //center、innerR、outerR:分别为椭圆的中心，内半径，外半径，由这三个参数可以构成圆环
        //startAngle、endAngle:弧的起止角度（特殊说明：①角度为弧度 ②角的正值表示顺时针方向，负值表示逆时针方向，③0度是3点钟的位置）
        void drawSector_Label(QPainter &painter,const QPointF &center, const double &innerR, const double &outerR,
                              const double &startAngle,const double &endAngle);
        void drawDirectedSector_Label(QPainter &painter,const QPointF &center, const double &innerR, const double &outerR,
                                      const double &startAngle,const double &endAngle,bool inToOut = true,double D  = 8);
        //=============================================以IMG为坐标系统=================================================================
    public:
        //参数说明：①point-需要绘制的点；②color-颜色；③thickness-绘图直径；④piontType-绘制点的类型（普通点，十字交叉点,斜交叉点）
        //⑤D-交叉线的长度，该参数只有选择CrossPoint_PT与SkewCrossPoint_PT类型的点才有效，其他点类型无效
        void drawPoint_IMG(const DM_Point& point, const QColor color= QColor(255, 0, 0),double thickness = 1,
                           Tag_DM pointType = NormalPoint_PT,double D  = 3);//绘制点
        void drawPoints_IMG(const std::vector<cv::Point>& points, const QColor color= QColor(255, 0, 0),double thickness = 1,
                            Tag_DM pointType = NormalPoint_PT,double D  = 3);//绘制点集

        //参数说明：①line-需要绘制的线；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        //⑤D-箭头的长度
        void drawLine_IMG(const DM_Line& line, const QColor color= QColor(255, 0, 0),double thickness = 1,
                          Tag_DM lineType = SolidLine_PT);//绘制直线
        void drawDirectedLine_IMG(const DM_Line& line, const QColor color= QColor(255, 0, 0),double thickness = 1,
                                  Tag_DM lineType = SolidLine_PT,double D  = 8);//绘制直线

        //参数说明：①rect-需要绘制的斜矩形；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        //⑤D-箭头的长度
        void drawRotatedRect_IMG(const DM_RotatedRect &rect, const QColor color= QColor(255, 0, 0),double thickness = 1,
                                 Tag_DM lineType = SolidLine_PT);//绘制协矩形
        void drawDirectedRotatedRect_IMG(const DM_RotatedRect &rect, const QColor color= QColor(255, 0, 0),double thickness = 1,
                                         Tag_DM lineType = SolidLine_PT,double D  = 8);//绘制带方向的协矩形

        //参数说明：①rect-需要绘制的矩形；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        void drawRect_IMG(const DM_Rect &rect, const QColor color= QColor(255, 0, 0),double thickness = 1,
                          Tag_DM lineType = SolidLine_PT);//绘制带矩形

        //参数说明：①circle-需要绘制的圆；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        void drawCircle_IMG(const DM_Circle &circle, const QColor color= QColor(255, 0, 0),double thickness = 1,
                            Tag_DM lineType = SolidLine_PT);//绘制圆

        //参数说明：①circle-需要绘制的椭圆；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        void drawEllipse_IMG(const DM_Ellipse &ellipse, const QColor color= QColor(255, 0, 0),double thickness = 1,
                             Tag_DM lineType = SolidLine_PT);//绘制椭圆

        //参数说明：①ring-需要绘制的圆环；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        //⑤inToOut:圆环的查找方向是否是从内向外找，direction:方向，0-从内环找到外环，1-从外环找到内环，2-不分方向⑥D-箭头的长度
        void drawRing_IMG(const DM_Ring &ring, const QColor color= QColor(255, 0, 0),double thickness = 1,
                                  Tag_DM lineType = SolidLine_PT, int direction = 2, double D = 8);//绘制圆环
        void drawDirectedRing_IMG(const DM_Ring &ring, const QColor color= QColor(255, 0, 0),double thickness = 1,
                                  Tag_DM lineType = SolidLine_PT,bool inToOut = true,double D  = 8);//绘制圆环

        //绘制弧长
        //参数说明：①arc-需要绘制的弧长；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        void drawArc_IMG(const DM_Arc &arc, const QColor color= QColor(255, 0, 0),double thickness = 1,
                         Tag_DM lineType = SolidLine_PT);//绘制弧
        //绘制扇形
        //参数说明：①pie-需要绘制的扇形；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        void drawPie_IMG(const DM_Pie &pie, const QColor color= QColor(255, 0, 0),double thickness = 1,
                         Tag_DM lineType = SolidLine_PT);//绘制扇形

        //绘制扇环
        //参数说明：①pie-需要绘制的扇形；②color-颜色；③thickness-绘图直径；④lineType-绘制点的类型（实线（默认），虚线，点画线等，详情查看枚举）
        //⑤inToOut:圆环的查找方向是否是从内向外找，direction:方向，0-从内环找到外环，1-从外环找到内环，2-不分方向 ⑥D-箭头的长度
        void drawSector_IMG(const DM_Sector &sector, const QColor color= QColor(255, 0, 0),double thickness = 1,
                            Tag_DM lineType = SolidLine_PT, int direction = 2, double D = 8);//绘制扇环
        void drawDirectedSector_IMG(const DM_Sector &sector, const QColor color= QColor(255, 0, 0),double thickness = 1,
                                    Tag_DM lineType = SolidLine_PT,bool inToOut = true,double D  = 8);//绘制扇环
        //写文字
        //参数说明：①str: 书写的内容；②color-颜色；③wordSize：字号；④angle-字体旋转角度（特殊说明：①角度为弧度 ②角的正值表示顺时针方向，负值表示逆时针方向，③0度是3点钟的位置）
        void drawText_IMG(const QString &str,const DM_Point &P, const QColor color= QColor(255, 0, 0),int wordSize = 15,double angle = 0);
    protected:
        //捕获事件
        //鼠标按下
        void mousePressEvent(QMouseEvent *ev);
        //鼠标释放
        void mouseReleaseEvent(QMouseEvent *ev);
        //鼠标移动
        void mouseMoveEvent(QMouseEvent *ev);
        //滚轮事件
        void wheelEvent(QWheelEvent *ev);
        //重绘区域
        void paintEvent(QPaintEvent *ev);
        //重载缩放事件
        void resizeEvent(QResizeEvent *ev);
    signals:
        //【特别说明】如果直接通过moveImageAbs直接移动rect是不发送此信号的，特指通过重构事件改变取图区域
        void changeImageRectSignal(QRectF rect);//当重新更新取图区域之后，发送新的绘图区域,该函数主要用于增加了进度条之后才有用
        void sendElement(DM_Element *elem);//发送新绘制的区域
        void sendPixelInformation(QString str);
    private slots:
        void HScrollBar_ValueChange(int value);//设置水平卷轴的值
        void VScrollBar_ValueChange(int value);//设置竖直卷轴的值
        void scrollBar_setValue();//根据Label重构事件更新Rect区域之后，设置卷轴的位置和最大值
    private:
        QWidget *pixelMessage;

        QImage src;//传入的原图
        cv::Mat srcMat;//传入的图片（mat类型）//肯定是灰度图像
        QRectF rect;//取图区域(在原图中，而非缩放后的图片的取图区域)
        QRectF rectMove;//取图区域（在拖动的图片的时候，使用该参数记录开始移动时的初始位置）
        double labelWidth;//按照输入图像的比例计算的label的宽度
        double labelHeight;//按照输入图像的比例计算的label的高度
        QScrollBar *HScrollBar, *VScrollBar;//此处只管使用，不管该指针的新建和销毁
        bool setHScrollBarValueFlag;//label重构事件更新Rect，从而需要重新设置水平卷轴值得标志
        bool setVScrollBarValueFlag;//label重构事件更新Rect，从而需要重新设置水平卷轴值得标志

        //==============src 缩放功能=================================
        double  zoomValue;   //当前缩放值
        double zoomBase;  //缩放基数 zoomBase = （maxZoomInTimes - minZoomOutTimes）/ maxZoomTimes
        double maxZoomTimes;//最大缩放次数（默认100次）
        double maxZoomInTimes; //最大放大倍数 （默认10倍）
        double minZoomOutTimes;//最小缩小倍数 （默认0.1）【该值随着窗口的变化而变化，初始值为0.1】
        //===========================================================
        QPointF  startPos; //开始按下鼠标时的初始坐标
        QPointF  endPos; //释放鼠标时的坐标
        bool dragFlag;     //正在移动标致（用于拖动使用）
        bool showCenterCrossFlag;  //显示中心十字交叉,默认显示正中心参考。
        bool showPixelMessageflag; //显示像素信息（位置和灰度值）
        bool drawFlag;//开始绘图标致
        //====================绘图颜色调整=======================================
        QColor color_ROI; //鼠标拖动绘图的颜色(天蓝   区域都是这个颜色)
        QColor color_over; //鼠标拖动区域超过label（即：图形越界）（越界红色）
        double penWidth;//笔画宽度；
        //====================绘图/显示内容=======================================
        bool vectorElementFlag;//绘制矢量元素标志
        Tag_DM elementIndex;//绘图编号
        std::vector<DM_LabelElement> elements;//绘制的元素
        bool showDrawElementFlag;//显示临时绘制元素的标志
        DM_LabelElement drawElememt;//临时绘制的元素
        std::vector<DM_LabelText> texts;//绘制的文字
};

#endif // DM_LABEL_H
