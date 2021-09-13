#include "DM_Label.h"
#include <QToolTip>

DM_Label::DM_Label(QWidget *parent):QLabel(parent)
{
    this->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    this->dragFlag = false;
    this->HScrollBar = nullptr;
    this->VScrollBar = nullptr;
    setHScrollBarValueFlag = false;//label重构事件更新Rect，从而需要重新设置水平卷轴值得标志
    setVScrollBarValueFlag = false;//label重构事件更新Rect，从而需要重新设置水平卷轴值得标志

    this->showCenterCrossFlag = true;//默认显示中心十字
    this->zoomValue = 1;   //当前缩放值
    this->maxZoomTimes = 200;//最大缩放次数（默认100次）
    this->maxZoomInTimes = 20.0; //最大放大倍数 （默认10倍）
    this->minZoomOutTimes = 0.1;//最小缩小倍数 （默认0.01）
    this->zoomBase = (this->maxZoomInTimes - this->minZoomOutTimes)/this->maxZoomTimes;  //缩放基数scaleBase = （maxZoomInTimes - minZoomOutTimes）/ maxScaleTim
    this->src = QImage();
    double w,h;
    if(this->src.width() < this->width())
    {
        w = this->src.width();
    }
    else
    {
        w = this->width();
    }
    if(this->src.height() < this->height())
    {
        h = this->src.height();
    }
    else
    {
        h = this->height();
    }
    this->rect = QRectF(QPointF(0,0),QSizeF(w,h));
    this->rectMove = this->rect;
    this->setScaledContents(false);//自动适应图片大小
    this->setMouseTracking(true);
    //==========================绘图=================================
    this->elementIndex = Default_DM;//默认不绘制任何图像
    this->drawFlag = false;
    this->drawRotatedRectStep = 0;
    this->drawRingStep = 0;//绘制圆环
    this->drawSectorStep = 0;//绘制圆弧
    this->showDrawElementFlag = true;//绘制最最近临时绘制的元素
    this->vectorElementFlag = true;//绘制矢量元素标志
    this->showPixelMessageflag = false;
    //==========================设置Label中各个板块的颜色=================================
    this->color_ROI = QColor(0, 255, 255);  //鼠标绘图的颜色和元素的ROI的颜色
    this->color_over = QColor(255, 0, 0);//区域越界
    this->penWidth = 3;
}

DM_Label::~DM_Label()
{
    ;
}
//加载图片
/*
void DM_Label::loadImage(const QImage &src_)
{
    if(src_.isNull())
    {
        return;
    }
    this->src = src_.copy();
    this->QImageToMat(src_).copyTo(this->srcMat);

    qDebug()<<"src_depth = "<< this->src.depth()<< "  src_fromat "<< this->src.format();
    double x,y,w,h;
    w = this->width()/this->zoomValue;
    h = this->height()/this->zoomValue;
    //如果rect没有初始化
    if(this->rect.width() <= 0 || this->rect.height() <= 0)
    {
        x = 0;
        y = 0;

        if(this->src.width() <= w)
        {
            w = this->src.width();
        }
        if(this->src.height() <= h)
        {
            h = this->src.height();
        }
    }
    else
    {
        if(this->src.width() <= this->rect.width())
        {
            w = this->src.width();
            x = 0;
        }
        else
        {
            if(this->src.width() >= this->rect.width()+this->rect.x())
            {
                x = this->rect.x();
            }
            else
            {
                x = this->src.width() - this->rect.width();
            }

        }

        if(this->src.height() <= this->rect.height())
        {
            h = this->src.height();
            y = 0;
        }
        else
        {
            if(this->src.height() >= this->rect.height() + this->rect.y())
            {
                y = this->rect.y();
            }
            else
            {
                y = this->src.height() - this->rect.height();
            }
        }
    }

    this->rect = QRectF(QPointF(x,y),QSizeF(w,h));//获得取图区域；
    this->labelWidth = w * this->zoomValue;
    this->labelHeight = h * this->zoomValue;
    this->showImage();//显示图片
}
*/
void DM_Label::loadImage(const cv::Mat &src_)
{
    bool upRectFlag = false;//更新区域的标志，如果图片大小变化，则从新更新区域，否则区域不变
    if(src_.empty())
    {
        return;
    }
    if(this->srcMat.cols != src_.cols ||
       this->srcMat.rows != src_.rows ||
       this->srcMat.empty())
    {
        upRectFlag = true;
    }
//	if(src_.channels()  == 1)
//	{
        src_.copyTo(this->srcMat);
//	}
//	else
//	{
//        cvtColor(src_,this->srcMat,COLOR_BGR2GRAY);
//	}
	this->drawElememt = DM_LabelElement();//重新加载图片不在显示临时绘制的元素
    this->src = this->matToQImage(src_).copy();

    if(upRectFlag)
    {
        //更新最小放大倍数
        double sW = double(this->width())/this->src.width();
        double sH = double(this->height())/this->src.height();
        if(sW >= 1 && sH >= 1)
        {
            this->minZoomOutTimes =1.0;
        }
        else if(sW <= sH && sW > 0)
        {
            this->minZoomOutTimes = sW;
        }
        else if(sW >= sH && sH > 0)
        {
            this->minZoomOutTimes = sH;
        }
        if(this->zoomValue < this->minZoomOutTimes)
        {
           this->zoomValue =  this->minZoomOutTimes;
        }

        double w,h;
        w = this->width()/this->zoomValue;
        h = this->height()/this->zoomValue;
        if(w >= this->src.width())
        {
            w = this->src.width();
        }
        if(h >= this->src.height())
        {
            h = this->src.height();
        }
        this->rect = QRectF(QPointF(0,0),QSizeF(w,h));//获得取图区域；
        this->labelWidth = w * this->zoomValue;
        this->labelHeight = h * this->zoomValue;
    }

    this->showImage();//显示图片
}

void DM_Label::showImage()
{
    QImage rectImage;//在rect中取出来的原图
    QImage labelImage;//将rectImage显示在label上的图片（按照最近插值）
    if(!this->src.isNull()&&
       this->src.width() >= this->rect.x() + this->rect.width() &&
       this->src.height()>= this->rect.y() + this->rect.height())
    {
        rectImage = this->src.copy(this->rect.toRect());
        labelImage = QImage(this->labelWidth,this->labelHeight,this->src.format());
        this->scale_NEAREST(&rectImage, &labelImage);
        this->setPixmap(QPixmap::fromImage(labelImage));
    }
}

void DM_Label::scale_NEAREST(QImage *src_, QImage *dst_)
{
    int srcWidth =src_->width() ;//变换前图片宽度
    int srcHeight = src_->height();//变换前图片高度
    int dstWidth = dst_->width();//变换后图片宽度
    int dstHeight = dst_->height();//变换后图片高度

    if(dstWidth<=0 || dstHeight <= 0 ||src_->isNull())
    {
        return;
    }
    qreal uW = (qreal)srcWidth / dstWidth;//宽度缩放比例
    qreal uH = (qreal)srcHeight / dstHeight;//高度缩放比例

    int x =0;//存储横坐标
    int y =0;//存储纵坐标
    for (int i = 0; i < dstHeight; i++)//遍历每一行
    {
        y = qRound(i*uH);   //对应处理前图片的行数
        if (y >= srcHeight)
        {
            y = srcHeight-1;
        }
        const uchar *pSrc = (uchar *)src_->constScanLine(y);//读取当前行的像素点
        uchar *pDst = (uchar *)dst_->scanLine(i);//读取处理后图片的行像素点
        for (int j = 0; j < dstWidth; j++) //对当前行循环每一个像素点
        {
            x = qRound(j*uW);//对应处理前图片的列数
            if(x >= srcWidth)
            {
                x = srcWidth -1;
            }
            int depth = src_->depth()/8;
            memcpy(pDst+j*depth, pSrc+x * depth, depth);
        }
    }
    //    for(int x = 0; x < dstWidth; x++)
    //    {
    //       for(int y = 0; y < dstHeight; y++)
    //       {
    //            int yy = qRound((double)y*uH);
    //            if (yy >= srcHeight)
    //            {
    //                yy = srcHeight-1;
    //            }
    //            int xx = qRound((double)x*uW);
    //            if(xx >= srcWidth)
    //            {
    //                xx = srcWidth -1;
    //            }
    //            dst_->setPixelColor(x,y,src_->pixelColor(xx,yy));
    //       }
    //    }
}

QImage DM_Label::matToQImage(const cv::Mat &inMat)
{
    switch (inMat.type() )
    {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image( inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_ARGB32 );
            return image;
        }
            // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image( inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_RGB888 );
            return image.rgbSwapped();
        }

            // 8-bit, 1 channel
        case CV_8UC1:
        {
            QImage image( inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_Grayscale8);
            return image;
        }

        default:
            qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

cv::Mat DM_Label::QImageToMat(const QImage &image)
{
    switch(image.format())
    {
        //8-bit, 4 channel
        case QImage::Format_RGB32:
        {
            cv::Mat mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), size_t(image.bytesPerLine()));
            return mat;
        }
            //8-bit, 3 channel
        case QImage::Format_RGB888:
        {
            QImage swapped = image.rgbSwapped();
            cv::Mat mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), size_t(swapped.bytesPerLine()));
            return mat;
        }
            //8-bit, 1 channel
        case QImage::Format_Indexed8:
        {
            cv::Mat mat(image.height(), image.width(), CV_8UC1, const_cast<uchar*>(image.bits()), size_t(image.bytesPerLine()));
            return mat;
        }
        default:
        break;
    }
    return cv::Mat();
}

bool DM_Label::transformLabeToImg_Point(const QPointF &P1, DM_Point &P2)
{
    if(this->labelHeight > 0 && this->labelWidth> 0 )
    {
        double scaleX = this->rect.toRect().width()/this->labelWidth;//计算横向比例尺
        double scaleY = this->rect.toRect().height()/this->labelHeight;//计算纵向比例尺
        P2.x = P1.x() * scaleX + this->rect.toRect().x();
        P2.y = P1.y() * scaleY + this->rect.toRect().y();
        return true;
    }
    else
    {
        P2 = DM_Point();
        return false;
    }
}

bool DM_Label::transformLabeToImg_Line(const QLineF &line1, DM_Line &line2)
{
    DM_Point p1,p2;
    if(this->transformLabeToImg_Point(line1.p1(),p1)&&
       this->transformLabeToImg_Point(line1.p2(),p2))
    {
        line2 = DM_Line(p1,p2);
        return true;
    }
    else
    {
        line2 = DM_Line();
        return false;
    }

}

bool DM_Label::transformLabeToImg_L(const double &L1, double &L2)
{
    if(this->labelHeight > 0 && this->labelWidth> 0 )
    {
        double scaleL = this->rect.toRect().width()/this->labelWidth;//计算横向比例尺
        L2 = L1*scaleL;
        return true;
    }
    else
    {
        L2 = 0;
        return false;
    }
}

bool DM_Label::transformImgTolabel_Point(const DM_Point &P1, QPointF &P2)
{
    if(this->rect.width() > 0 && this->rect.height() > 0)
    {
        //转化坐标系统
        double scaleX = double(this->labelWidth) / rect.toRect().width();//计算横向比例尺
        double scaleY =  double(this->labelHeight) / rect.toRect().height();//计算纵向比例尺
        P2 = QPointF((P1.x-this->rect.toRect().x())*scaleX,(P1.y-this->rect.toRect().y())*scaleY);
        return true;
    }
    else
    {
        P2 = QPointF();
        return false;
    }
}

bool DM_Label::transformImgTolabel_Line(const DM_Line &line1, QLineF &line2)
{
    QPointF p1,p2;
    if(this->transformImgTolabel_Point(line1.P1,p1)&&
       this->transformImgTolabel_Point(line1.P2,p2))
    {
        line2 = QLineF(p1,p2);
        return true;
    }
    else
    {
        line2 = QLineF();
        return false;
    }

}

bool DM_Label::transformImgTolabel_L(const double &L1, double &L2)
{
    if(this->rect.width() > 0 && this->rect.height() > 0)
    {
        //转化坐标系统
        double scaleL = double(this->labelWidth) / rect.toRect().width();//计算比例尺
        L2 = L1*scaleL;
        return true;
    }
    else
    {
        L2 = 0;
        return false;
    }
}

bool DM_Label::isInLabel(const std::vector<DM_Point> pts)
{
    for(int i = 0; i < pts.size(); i++)
    {
        if(!this->isInLabel(pts[i]))
        {
            return false;
        }
    }
    return true;
}

bool DM_Label::isInLabel(const std::vector<QPointF> pts)
{
    for(int i = 0; i < pts.size(); i++)
    {
        if(!this->isInLabel(pts[i]))
        {
            return false;
        }
    }
    return true;
}

bool DM_Label::isInLabel(const QLineF line_)
{
    if (this->isInLabel(line_.p1()) || this->isInLabel(line_.p2()))
    {
        return true;
    }
    else
    {
        if (line_.x1() <= 0 && line_.x2() >= 0)
        {
            return true;
        }
        else if (line_.x2() <= 0 && line_.x1() >= 0)
        {
            return true;
        }
        else if (line_.y1() <= 0 && line_.y2() >= 0)
        {
            return true;
        }
        else if (line_.y2() <= 0 && line_.y1() >= 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
}
bool DM_Label::isInLabel(const DM_Line line_)
{


    if (this->isInLabel(line_.P1) || this->isInLabel(line_.P2))
    {
        return true;
    }
    else
    {
        if (line_.P1.x <= this->rect.x() && line_.P2.x >= this->rect.x())
        {
            return true;
        }
        else if (line_.P2.x <= this->rect.x() && line_.P1.x >= this->rect.x())
        {
            return true;
        }
        else if (line_.P1.y <= this->rect.y() && line_.P2.y >= this->rect.y())
        {
            return true;
        }
        else if (line_.P2.y <= this->rect.y() && line_.P1.y >= this->rect.y())
        {
            return true;
        }
        else
        {
            return false;
        }

    }
}

bool DM_Label::isInLabel(const QRectF rect_)
{
    if(this->isInLabel(rect_.topLeft())||
       this->isInLabel(rect_.bottomLeft())||
       this->isInLabel(rect_.topRight())||
       this->isInLabel(rect_.bottomLeft()))
    {
        return true;
    }
    else
    {
        if (rect_.left() <= 0 && rect_.right() >= 0)
        {
            return true;
        }
        else if (rect_.top() <= 0 && rect_.bottom() >= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}
bool DM_Label::isInLabel(const DM_Rect rect_)
{
    std::vector<DM_Point> vertices = rect_.getVertices();
    bool inRectFlag = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (this->isInLabel(vertices[i]))
        {
            inRectFlag = true;
            break;
        }
    }
    if (!inRectFlag)
    {
        if (rect_.leftTop.x <= this->rect.x() && rect_.rightBottom.x >= this->rect.x())
        {
            inRectFlag = true;
        }
        else if (rect_.leftTop.y <= this->rect.y() && rect_.rightBottom.y >= this->rect.y())
        {
            inRectFlag = true;
        }
    }
    if (!inRectFlag)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool DM_Label::isInLabel(const DM_Circle circle_)
{
    DM_Rect rect  = circle_.getBoundingRect();
    return this->isInLabel(rect);
}

bool DM_Label::isInLabel(const DM_Arc arc_)
{
    DM_Rect rect  = arc_.getBoundingRect();
    return this->isInLabel(rect);
}

bool DM_Label::isInLabel(const DM_Sector sector_)
{
    const  DM_Rect rect  = sector_.getBoundingRect();
    return this->isInLabel(rect);
}


//绘制label的中心十字架
void DM_Label::centerCross_paintEvent()
{
    if(this->showCenterCrossFlag)
    {
        int centerX = (this->width()-1)>>1;
        int centerY = (this->height()-1)>>1;
        QPainter painter(this);
        painter.setPen(QPen(QColor(255,0,0),1));
        this->drawPoint_Label(painter,QPointF(centerX,centerY),CrossPoint_PT,50);
    }
}

void DM_Label::DM_LabelElement_paintEvent(DM_LabelElement elem)
{
    if (elem.element != nullptr)
    {
        switch (elem.element->type)
        {
            case Point_ELMT://点
            {
                DM_Point *temp =  dynamic_cast<DM_Point*>(elem.element);
                this->drawPoint_IMG(*temp, elem.color, elem.penWidth, elem.penType);
            }
            break;
            case Line_ELMT://直线
            {
                DM_Line *temp =  dynamic_cast<DM_Line*>(elem.element);
                if (elem.vectorFlag)
                {
                    this->drawDirectedLine_IMG(*temp, elem.color, elem.penWidth, elem.penType);
                }
                else
                {
                    this->drawLine_IMG(*temp, elem.color, elem.penWidth, elem.penType);
                }

            }
            break;
            case Circle_ELMT://圆
            {
                DM_Circle *temp =  dynamic_cast<DM_Circle*>(elem.element);
                this->drawCircle_IMG(*temp, elem.color, elem.penWidth, elem.penType);
            }
            break;
            case Ring_ELMT://圆环
            {
                DM_Ring *temp = dynamic_cast<DM_Ring*>(elem.element);
                if (elem.vectorFlag)
                {
                    this->drawRing_IMG(*temp, elem.color, elem.penWidth, elem.penType, temp->direction);
                }
                else
                {
                    this->drawRing_IMG(*temp, elem.color, elem.penWidth, elem.penType, 2);
                }

            }
            break;
            case Arc_ELMT://弧线
            {
                DM_Arc *temp =  dynamic_cast<DM_Arc*>(elem.element);
                this->drawArc_IMG(*temp, elem.color, elem.penWidth, elem.penType);
            }
            break;
            case RotatedRect_ELMT ://斜矩形
            {
                DM_RotatedRect *temp =  dynamic_cast<DM_RotatedRect*>(elem.element);
                if (elem.vectorFlag)
                {
                    this->drawDirectedRotatedRect_IMG(*temp, elem.color, elem.penWidth, elem.penType);
                }
                else
                {
                    this->drawRotatedRect_IMG(*temp, elem.color, elem.penWidth, elem.penType);
                }

            }
            break;
            case Rect_ELMT://矩形
            {
                DM_Rect *temp =  dynamic_cast<DM_Rect*>(elem.element);
                this->drawRect_IMG(*temp, elem.color, elem.penWidth, elem.penType);
            }
            break;
            case Pie_ELMT://扇形
            {
                DM_Pie *temp =  dynamic_cast<DM_Pie*>(elem.element);
                drawPie_IMG(*temp, elem.color, elem.penWidth, elem.penType);
            }
            break;
            case Sector_ELMT://扇环
            {
                DM_Sector *temp = dynamic_cast<DM_Sector*>(elem.element);
                if (elem.vectorFlag)
                {
                    drawSector_IMG(*temp, elem.color, elem.penWidth, elem.penType, temp->direction);
                }
                else
                {
                    drawSector_IMG(*temp, elem.color, elem.penWidth, elem.penType, 2);
                }
            }
            break;
            default:;
        }
    }

}

void DM_Label::lineElement_MousePress(QMouseEvent *ev)
{
    DM_Point P1;
    if (this->transformLabeToImg_Point(ev->pos(), P1) &&
        this->isInLabel(P1) &&
        this->isInLabel(ev->pos()))
    {
        this->drawFlag = true;
    }
    else
    {
        this->drawFlag = false;
    }
}

void DM_Label::lineElement_MouseRelease(QMouseEvent *ev)
{
    DM_Point P1, P2;
    if (this->transformLabeToImg_Point(this->startPos, P1) &&
        this->transformLabeToImg_Point(this->endPos, P2) &&
        this->isInLabel(P1) &&
        this->isInLabel(P2))//超过边界线
    {

        DM_Line *line_ = new DM_Line(P1, P2);
        this->drawElememt = DM_LabelElement(line_, this->vectorElementFlag, this->color_ROI, this->penWidth);
        delete line_;
        emit this->sendElement(this->drawElememt.element);
        this->update();

    }
    this->drawFlag = false;
}

void DM_Label::lineElement_MouseMove()
{
    DM_Point P1, P2;

    if (this->transformLabeToImg_Point(this->startPos, P1) &&
        this->transformLabeToImg_Point(this->endPos, P2) &&
        this->isInLabel(P1) &&
        this->isInLabel(P2))//超过边界线
    {
        if (this->isInLabel(this->startPos) &&
            this->isInLabel(this->endPos))//超过边界线
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedLine_IMG(DM_Line(P1, P2), this->color_ROI, this->penWidth);
            }
            else
            {
                this->drawLine_IMG(DM_Line(P1, P2), this->color_ROI, this->penWidth);
            }

        }
        else
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedLine_IMG(DM_Line(P1, P2), this->color_over, this->penWidth);
            }
            else
            {
                this->drawLine_IMG(DM_Line(P1, P2), this->color_over, this->penWidth);
            }
        }
    }
}

void DM_Label:: rectElement_MousePress(QMouseEvent* ev)
{
    DM_Point lefttop;
    transformLabeToImg_Point(this->startPos, lefttop);
    if(isInLabel(lefttop))
    {
        drawFlag = true;
    }
}

void DM_Label::rectElement_MouseRelease(QMouseEvent* ev)
{
    DM_Point lefttop;
    transformLabeToImg_Point(this->startPos, lefttop);
    DM_Point rightbom;
    transformLabeToImg_Point(this->endPos, rightbom);
    drawFlag = false;
    DM_Rect *rect_ = new DM_Rect(lefttop,rightbom);
    std::vector<DM_Point> vertices = rect_->getVertices();
    if(this->isInLabel(vertices))//超过边界线
    {
        this->drawElememt = DM_LabelElement(rect_, this->vectorElementFlag, this->color_ROI,this->penWidth);
        emit this->sendElement(this->drawElememt.element);
    }
    delete rect_;
    this->update();
}

void DM_Label::rectElement_MouseMove()
{
    DM_Point lefttop;
    transformLabeToImg_Point(this->startPos, lefttop);
    DM_Point rightbom;
    transformLabeToImg_Point(this->endPos, rightbom);
    drawFlag = true;

    DM_Rect rect_(lefttop,rightbom);
    std::vector<DM_Point> vertices = rect_.getVertices();
    if(!this->isInLabel(vertices))//超过边界线
    {
        this->drawRect_IMG(rect_, this->color_over,this->penWidth);
    }
    else
    {
        this->drawRect_IMG(rect_, this->color_ROI,this->penWidth);
    }

}

bool DM_Label::isInLabel(const QPointF  P1)
{
    if(P1.x() >= this->width()||
       P1.x() < 0||
       P1.y() >= this->height()||
       P1.y() < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool DM_Label::isInLabel(const DM_Point  P1)
{
    if (P1.x > this->rect.width() + this->rect.x() ||
        P1.x < this->rect.x() ||
        P1.y > this->rect.height() + this->rect.y() ||
        P1.y < this->rect.y())
    {
        return false;
    }
    else
    {
        return true;
    }
}


void DM_Label::rotatedRectElement_MousePress(QMouseEvent *ev)
{
    DM_Point P1;
    if(this->transformLabeToImg_Point(ev->pos(), P1))
    {
        if(this->drawRotatedRectStep == 0 || this->drawRotatedRectStep == 3)
        {
            this->rotatedRectPoints.clear();//清除缓存
            this->rotatedRectPoints.push_back(P1);
            this->drawFlag = true;
            this->drawRotatedRectStep =1;
        }
        else if(this->drawRotatedRectStep == 2)
        {
            this->drawRotatedRectStep = 3;
        }
        else
        {
            this->rotatedRectPoints.clear();
            this->drawFlag = false;
            this->drawRotatedRectStep = 0;
        }
    }
    else
    {
        this->rotatedRectPoints.clear();
        this->drawFlag = false;
        this->drawRotatedRectStep = 0;
    }
}

void DM_Label::rotatedRectElement_MouseRelease(QMouseEvent *ev)
{
    //如果超过量程，则重新规划
    if(this->endPos.x() >= this->width()||
       this->endPos.x() <= 0||
       this->endPos.y() >= this->height()||
       this->endPos.y() <= 0)
    {
        this->rotatedRectPoints.clear();
        this->drawFlag = false;
        this->drawRotatedRectStep = 0;
    }
    if(this->drawRotatedRectStep == 1)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1))
        {
            this->rotatedRectPoints.push_back(P1);
            this->drawFlag = true;
            this->drawRotatedRectStep = 2;
        }
        else
        {
            this->rotatedRectPoints.clear();
            this->drawFlag = false;
            this->drawRotatedRectStep = 0;
        }
    }
    else if(this->drawRotatedRectStep == 3)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1))
        {
            this->rotatedRectPoints.push_back(P1);
            this->drawFlag = false;
            DM_Line axisTemp(rotatedRectPoints[0],rotatedRectPoints[1]);
            DM_RotatedRect *rect_ = new DM_RotatedRect(axisTemp,P1);

            if(this->isInLabel(rect_->getVertices()))//超过边界线
            {
                this->drawElememt = DM_LabelElement(rect_, true, this->color_ROI, this->penWidth);
                emit this->sendElement(this->drawElememt.element);
            }
            delete rect_;
            this->update();
        }
        else
        {
            this->rotatedRectPoints.clear();
            this->drawFlag = false;
        }
        this->drawRotatedRectStep = 0;
    }
    else
    {
        this->rotatedRectPoints.clear();
        this->drawFlag = false;
        this->drawRotatedRectStep = 0;
    }
    this->update();
}

void DM_Label::rotatedRectElement_MouseMove()
{
    if(this->drawRotatedRectStep == 1 && rotatedRectPoints.size() >=1)
    {
        DM_Point  P2;
        this->transformLabeToImg_Point(this->endPos,P2);
        //如果区域超过显示红色
        if(!this->isInLabel(this->endPos))
        {
            this->drawLine_IMG(DM_Line( this->rotatedRectPoints[0],P2),this->color_over,this->penWidth);
        }
        else
        {
            this->drawLine_IMG(DM_Line( this->rotatedRectPoints[0],P2),this->color_ROI,this->penWidth);
        }
    }
    else  if(this->drawRotatedRectStep >= 2 && rotatedRectPoints.size() >=2)
    {
        DM_Line axis(rotatedRectPoints[0],rotatedRectPoints[1]);
        DM_Point P0;
        this->transformLabeToImg_Point(this->endPos,P0);
        DM_RotatedRect rectTemp(axis,P0);//定义协矩形

        std::vector<DM_Point> vertices = rectTemp.getVertices();
        if(!this->isInLabel(vertices))//超过边界线
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedRotatedRect_IMG(rectTemp,this->color_over,this->penWidth);
            }
            else
            {
                this->drawRotatedRect_IMG(rectTemp, this->color_over, this->penWidth);
            }
            this->drawLine_IMG(DM_Line(rotatedRectPoints[0],rotatedRectPoints[1]),this->color_over,this->penWidth);
        }
        else
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedRotatedRect_IMG(rectTemp, this->color_ROI, this->penWidth);
            }
            else
            {
                this->drawRotatedRect_IMG(rectTemp, this->color_ROI, this->penWidth);
            }
            this->drawLine_IMG(DM_Line(rotatedRectPoints[0],rotatedRectPoints[1]),this->color_ROI,this->penWidth);
        }
    }
}
void DM_Label::ringElement_MousePress(QMouseEvent *ev)
{
    if(this->drawRingStep == 0)
    {
        this->ringPoints.clear();
        this->drawFlag = true;
    }
    else if(this->drawRingStep == 2)
    {
        this->drawRingStep = 3;
    }
    else if(this->drawRingStep == 4)
    {
        this->drawRingStep = 5;
    }
}


void DM_Label::ringElement_MouseRelease(QMouseEvent *ev)
{
    if(this->drawRingStep < 2)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1))
        {
            this->ringPoints.push_back(P1);
            this->drawFlag = true;
            this->drawRingStep++;
        }
        else
        {
            this->ringPoints.clear();
            this->drawFlag = false;
            this->drawRingStep = 0;
        }
    }
    else if(this->drawRingStep == 3)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1) &&
           this->ringPoints.size() == 2)
        {
            this->ringPoints.push_back(P1);
            //判定最小外接矩形是否越界
            DM_Circle circleTemp(this->ringPoints[0],this->ringPoints[1],this->ringPoints[2]);
            std::vector<DM_Point> vertices = circleTemp.getBoundingRect().getVertices();
            if(this->isInLabel(vertices))
            {
                this->drawRingStep++;
                this->drawFlag = true;
            }
            else
            {
                this->ringPoints.clear();
                this->drawFlag = false;
                this->drawRingStep = 0;
            }
        }
        else
        {
            this->ringPoints.clear();
            this->drawFlag = false;
            this->drawRingStep = 0;
        }
    }
    else if(this->drawRingStep == 5)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1)&&
           this->ringPoints.size() == 3)
        {
            this->ringPoints.push_back(P1);
            //判定最小外接矩形是否越界
            DM_Circle circleTemp(this->ringPoints[0],this->ringPoints[1],this->ringPoints[2]);
            double R1 = circleTemp.center.dis_P2P(P1);
            double innerR, outerR;
            int director = 1;//判定搜索方向
            if(R1 >= circleTemp.radius )
            {
                outerR = R1;
                innerR = circleTemp.radius - (outerR-circleTemp.radius);
                director = 0;
            }
            else
            {
                innerR = R1;
                outerR = circleTemp.radius+ (circleTemp.radius - innerR);
                director = 1;
            }
            innerR = innerR < 2? 2:innerR;
            innerR = innerR > circleTemp.radius? circleTemp.radius:innerR;
            outerR = outerR < circleTemp.radius? circleTemp.radius:outerR;
            if (innerR+5<outerR)
            {
                DM_Ring *ringTemp = new DM_Ring(circleTemp.center, innerR, outerR);
                ringTemp->setDirection(director);
                std::vector<DM_Point> vertices = ringTemp->getBoundingRect().getVertices();
                if(this->isInLabel(vertices))
                {
                    this->drawElememt = DM_LabelElement(ringTemp, this->vectorElementFlag, this->color_ROI, this->penWidth);
                    emit this->sendElement(this->drawElememt.element);
                }
                delete ringTemp;

            }

            this->ringPoints.clear();
            this->drawFlag = false;
            this->drawRingStep = 0;
        }
        else
        {
            this->ringPoints.clear();
            this->drawFlag = false;
            this->drawRingStep = 0;
        }
    }
    else
    {
        this->ringPoints.clear();
        this->drawFlag = false;
        this->drawRingStep = 0;
    }
    this->update();
}

void DM_Label::ringElement_MouseMove()
{
    if( this->drawRingStep == 1 && this->ringPoints.size() ==1)
    {
        this->drawPoint_IMG( this->ringPoints[0],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
    }
    else if( this->drawRingStep == 2 && this->ringPoints.size() >=2)
    {
        this->drawPoint_IMG( this->ringPoints[0],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
        this->drawPoint_IMG( this->ringPoints[1],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
    }
    else if( this->drawRingStep == 3 )
    {
        DM_Point  P1;
        this->transformLabeToImg_Point(this->endPos,P1);

        //判定最小外接矩形是否越界
        DM_Circle circleTemp(this->ringPoints[0],this->ringPoints[1],P1);
        std::vector<DM_Point> vertices = circleTemp.getBoundingRect().getVertices();
        if(!this->isInLabel(vertices))
        {
            this->drawCircle_IMG(circleTemp,this->color_over,this->penWidth);
            this->drawPoint_IMG(this->ringPoints[0], this->color_over, this->penWidth, SkewCrossPoint_PT);
            this->drawPoint_IMG(this->ringPoints[1], this->color_over, this->penWidth, SkewCrossPoint_PT);
            this->drawPoint_IMG(P1, this->color_over, this->penWidth, SkewCrossPoint_PT);
        }
        else
        {
            this->drawCircle_IMG(circleTemp,this->color_ROI,this->penWidth);
            this->drawPoint_IMG(this->ringPoints[0], this->color_ROI, this->penWidth, SkewCrossPoint_PT);
            this->drawPoint_IMG(this->ringPoints[1], this->color_ROI, this->penWidth, SkewCrossPoint_PT);
            this->drawPoint_IMG(P1, this->color_ROI, this->penWidth, SkewCrossPoint_PT);
        }
    }
    else if (this->drawRingStep == 4 && this->ringPoints.size() >= 3)
    {
        this->drawPoint_IMG(this->ringPoints[0], this->color_ROI, this->penWidth, SkewCrossPoint_PT);
        this->drawPoint_IMG(this->ringPoints[1], this->color_ROI, this->penWidth, SkewCrossPoint_PT);
        this->drawPoint_IMG(this->ringPoints[2], this->color_ROI, this->penWidth, SkewCrossPoint_PT);
    }
    else if( this->drawRingStep == 5 && this->ringPoints.size() >=3)
    {
        DM_Circle circleTemp(this->ringPoints[0],this->ringPoints[1],this->ringPoints[2]);
        DM_Point  P1;
        this->transformLabeToImg_Point(this->endPos,P1);

        double R1 = circleTemp.center.dis_P2P(P1);
        double innerR, outerR;
        bool in2Out = 1;//判定搜索方向
        if(R1 >= circleTemp.radius )
        {
            outerR = R1;
            innerR = circleTemp.radius - (outerR-circleTemp.radius);
            in2Out = true;//判定搜索方向：从内到外
        }
        else
        {
            innerR = R1;
            outerR = circleTemp.radius+ (circleTemp.radius - innerR);
            in2Out = false;//判定搜索方向：从外到内
        }
        innerR = innerR < 2? 2:innerR;
        innerR = innerR > circleTemp.radius? circleTemp.radius:innerR;
        outerR = outerR < circleTemp.radius? circleTemp.radius:outerR;
        DM_Ring  ringTemp = DM_Ring(circleTemp.center,innerR,outerR);
        //绘制圆环
        std::vector<DM_Point> vertices = ringTemp.getBoundingRect().getVertices();

        if(!this->isInLabel(vertices))
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedRing_IMG(ringTemp,this->color_over,this->penWidth,SolidLine_PT,in2Out);
            }
            else
            {
                this->drawRing_IMG(ringTemp, this->color_over, this->penWidth, SolidLine_PT);
            }

            this->drawCircle_IMG(circleTemp,this->color_over,this->penWidth);
        }
        else
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedRing_IMG(ringTemp, this->color_ROI, this->penWidth, SolidLine_PT, in2Out);
            }
            else
            {
                this->drawRing_IMG(ringTemp, this->color_ROI, this->penWidth, SolidLine_PT);
            }
            this->drawCircle_IMG(circleTemp,this->color_ROI,this->penWidth);
        }
    }
}

void DM_Label::sectorElement_MousePress(QMouseEvent* ev)
{
    if (this->drawSectorStep == 0)
    {
        this->sectorPoints.clear();
        this->drawFlag = true;
    }
    else if (this->drawSectorStep == 2)
    {
        this->drawSectorStep = 3;
    }
    else if (this->drawSectorStep == 4)
    {
        this->drawSectorStep = 5;
    }
}

void DM_Label::sectorElement_MouseRelease(QMouseEvent *ev)
{
    if(this->drawSectorStep< 2)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1))
        {
            this->sectorPoints.push_back(P1);
            this->drawFlag = true;
            this->drawSectorStep++;
        }
        else
        {
            this->sectorPoints.clear();
            this->drawFlag = false;
            this->drawSectorStep= 0;
        }
    }
    else if(this->drawSectorStep== 3)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1) &&
           this->sectorPoints.size() == 2)
        {
            this->sectorPoints.push_back(P1);
            //判定最小外接矩形是否越界
            DM_Circle circleTemp(this->sectorPoints[0],this->sectorPoints[1],this->sectorPoints[2]);
            std::vector<DM_Point> vertices = circleTemp.getBoundingRect().getVertices();
            if(this->isInLabel(vertices))
            {
                this->drawSectorStep++;
                this->drawFlag = true;
            }
            else
            {
                this->sectorPoints.clear();
                this->drawFlag = false;
                this->drawSectorStep= 0;
            }
        }
        else
        {
            this->sectorPoints.clear();
            this->drawFlag = false;
            this->drawSectorStep= 0;
        }
    }
    else if(this->drawSectorStep== 5)
    {
        DM_Point P1;
        if(this->transformLabeToImg_Point(ev->pos(),P1)&&
           this->sectorPoints.size() == 3)
        {
            this->sectorPoints.push_back(P1);
            //判定最小外接矩形是否越界
            DM_Arc arcTemp(this->sectorPoints[0],this->sectorPoints[2],this->sectorPoints[1]);
            double R1 = arcTemp.center.dis_P2P(P1);
            double innerR, outerR;
            int director = 1;//判定搜索方向
            if(R1 >= arcTemp.radius )
            {
                outerR = R1;
                innerR = arcTemp.radius - (outerR-arcTemp.radius);
                director = 0;
            }
            else
            {
                innerR = R1;
                outerR = arcTemp.radius+ (arcTemp.radius - innerR);
                director = 1;
            }
            innerR = innerR < 2? 2:innerR;
            innerR = innerR > arcTemp.radius? arcTemp.radius:innerR;
            outerR = outerR < arcTemp.radius? arcTemp.radius:outerR;
            if (innerR+5<outerR)
            {

                DM_Sector *sectorTemp = new DM_Sector(arcTemp.center, innerR, outerR,arcTemp.startAngle,arcTemp.endAngle);
                sectorTemp->setDirection(director);

                std::vector<DM_Point> vertices = sectorTemp->getBoundingRect().getVertices();
                if (this->isInLabel(vertices))
                {
                    this->drawElememt = DM_LabelElement(sectorTemp, this->vectorElementFlag, this->color_ROI,this->penWidth);
                    emit this->sendElement(this->drawElememt.element);
                }
                delete sectorTemp;
            }

            this->sectorPoints.clear();
            this->drawFlag = false;
            this->drawSectorStep= 0;
        }
        else
        {
            this->sectorPoints.clear();
            this->drawFlag = false;
            this->drawSectorStep= 0;
        }
    }
    else
    {
        this->sectorPoints.clear();
        this->drawFlag = false;
        this->drawSectorStep= 0;
    }
    this->update();
}

void DM_Label::sectorElement_MouseMove()
{
    if( this->drawSectorStep== 1 && this->sectorPoints.size() ==1)
    {
        this->drawPoint_IMG( this->sectorPoints[0],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
    }
    else if( this->drawSectorStep== 2 && this->sectorPoints.size() ==2)
    {
        this->drawPoint_IMG( this->sectorPoints[0],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
        this->drawPoint_IMG( this->sectorPoints[1],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
    }
    else if( this->drawSectorStep== 3 )
    {
        DM_Point  P1;
        this->transformLabeToImg_Point(this->endPos,P1);

        //判定最小外接矩形是否越界
        DM_Arc arcTemp(this->sectorPoints[0],P1,this->sectorPoints[1]);
        std::vector<DM_Point> vertices = arcTemp.getBoundingRect().getVertices();
        if(!this->isInLabel(vertices))
        {
            this->drawArc_IMG(arcTemp,this->color_over,this->penWidth);
            this->drawPoint_IMG( this->sectorPoints[0],this->color_over,this->penWidth,SkewCrossPoint_PT);
            this->drawPoint_IMG( this->sectorPoints[1],this->color_over,this->penWidth,SkewCrossPoint_PT);
            this->drawPoint_IMG( P1,this->color_over,this->penWidth,SkewCrossPoint_PT);
        }
        else
        {
            this->drawArc_IMG(arcTemp,this->color_ROI,this->penWidth);
            this->drawPoint_IMG( this->sectorPoints[0],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
            this->drawPoint_IMG( this->sectorPoints[1],this->color_ROI,this->penWidth,SkewCrossPoint_PT);
            this->drawPoint_IMG( P1,this->color_ROI,this->penWidth,SkewCrossPoint_PT);
        }

    }
    else if( this->drawSectorStep== 5 && this->sectorPoints.size() >=3)
    {
        DM_Arc arcTemp(this->sectorPoints[0],this->sectorPoints[2],this->sectorPoints[1]);
        DM_Point  P1;
        this->transformLabeToImg_Point(this->endPos,P1);

        double R1 = arcTemp.center.dis_P2P(P1);
        double innerR, outerR;
        bool in2Out = 1;//判定搜索方向
        if(R1 >= arcTemp.radius )
        {
            outerR = R1;
            innerR = arcTemp.radius - (outerR-arcTemp.radius);
            in2Out = true;//判定搜索方向：从内到外
        }
        else
        {
            innerR = R1;
            outerR = arcTemp.radius+ (arcTemp.radius - innerR);
            in2Out = false;//判定搜索方向：从外到内
        }
        innerR = innerR < 2? 2:innerR;
        innerR = innerR > arcTemp.radius? arcTemp.radius:innerR;
        outerR = outerR < arcTemp.radius? arcTemp.radius:outerR;
        DM_Sector  sectorTemp = DM_Sector(arcTemp.center,innerR,outerR,arcTemp.startAngle,arcTemp.endAngle);
        //判定最小外接矩形是否越界
        std::vector<DM_Point> vertices = sectorTemp.getBoundingRect().getVertices();
        if (!this->isInLabel(vertices))
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedSector_IMG(sectorTemp,this->color_over,this->penWidth,SolidLine_PT,in2Out);
            }
            else
            {
                this->drawSector_IMG(sectorTemp, this->color_over, this->penWidth, SolidLine_PT);
            }

            this->drawArc_IMG(arcTemp,this->color_over,this->penWidth);
        }
        else
        {
            if (this->vectorElementFlag)
            {
                this->drawDirectedSector_IMG(sectorTemp, this->color_ROI, this->penWidth, SolidLine_PT, in2Out);
            }
            else
            {
                this->drawSector_IMG(sectorTemp, this->color_ROI, this->penWidth, SolidLine_PT);
            }
            this->drawArc_IMG(arcTemp,this->color_ROI,this->penWidth);
        }
    }
}

void DM_Label::clearDrawStatus()
{
    this->drawFlag = false;

    this->drawSectorStep = 0;
    this->sectorPoints.clear();

    this->drawRingStep = 0;
    this->ringPoints.clear();

    this->drawRotatedRectStep = 0;
    this->rotatedRectPoints.clear();
}

void DM_Label::setElementType(bool flag)
{
    this->vectorElementFlag = flag;
}

//=====================================================================================================
//函数名称：在label坐标系统中绘制点（点包括三类：普通点（默认），十字交叉点,斜交叉点）
//参数说明：
//       @painter:绘图设备
//       @point:需要绘制的点
//       @pointType:绘制点的类型（点包括三类：普通点（默认），十字交叉点,斜交叉点）
//       @D:交叉线的长度，该参数只有选择CrossPoint_PT与SkewCrossPoint_PT类型的点才有效，其他类型无效
//返回值:
//特殊说明：
//=====================================================================================================
void DM_Label::drawPoint_Label(QPainter &painter, const QPointF &point,Tag_DM pointType,double D)
{
    if(this->isInLabel(point))
    {
        if(pointType == SkewCrossPoint_PT)//绘制斜交叉点
        {
            painter.drawLine(QPointF(point.x()-D,point.y()-D), QPointF(point.x()+D,point.y()+D));//绘制直线
            painter.drawLine(QPointF(point.x()+D,point.y()-D), QPointF(point.x()-D,point.y()+D));//绘制直线
        }
        else if (pointType == CrossPoint_PT)//绘制十字交叉点
        {
            painter.drawLine(QPointF(point.x()-D,point.y()), QPointF(point.x()+D,point.y()));//绘制直线
            painter.drawLine(QPointF(point.x(),point.y()-D), QPointF(point.x(),point.y()+D));//绘制直线
        }
        else//绘制普通的点
        {
            painter.drawPoint(point);
        }
    }

}

//=====================================================================================================
//函数名称：在label坐标系统中绘制点集（点包括三类：普通点（默认），十字交叉点,斜交叉点）
//参数说明：
//       @painter:绘图设备
//       @points:需要绘制的点集
//       @pointType:绘制点的类型（点包括三类：普通点（默认），十字交叉点,斜交叉点）
//       @D:交叉线的长度，该参数只有选择CrossPoint_PT与SkewCrossPoint_PT类型的点才有效，其他类型无效
//返回值:
//特殊说明：
//=====================================================================================================
void DM_Label::drawPoints_Label(QPainter &painter, std::vector<QPointF> &points,Tag_DM pointType,double D)
{
    for(size_t i= 0; i < points.size(); i++)
    {
        this->drawPoint_Label(painter,points[i],pointType,D);
    }
    //painter.drawPoints(&points[0],points.size());
}

//=====================================================================================================
//函数名称：在label坐标系统中绘制线段
//参数说明：
//       @painter:绘图设备
//       @line:需要绘制的线段
//返回值:
//特殊说明：
//=====================================================================================================
void DM_Label::drawLine_Label(QPainter &painter, const QLineF &line)
{
    if(this->isInLabel(line))
    {
        painter.drawLine(line);//绘制直线
    }
}
//=====================================================================================================
//函数名称：在label坐标系统中绘制矢量线段（带箭头的线段）
//参数说明：
//       @painter:绘图设备
//       @line:需要绘制的线段
//       @D:绘制箭头长度
//返回值:
//特殊说明：
//=====================================================================================================
void DM_Label::drawDirectedLine_label(QPainter &painter, const QLineF &line, double D)
{
    if(this->isInLabel(line))
    {

        DM_Arrow arrow(DM_Point(line.x1(),line.y1()),DM_Point(line.x2(),line.y2()),D);
        std::vector<DM_Point> arrowVertices = arrow.getVertices();
        if (arrowVertices.size() == 4)
        {
            painter.drawLine(line);//绘制直线

            painter.save();//保存painter的初始状态
            QColor brushColor = painter.pen().color();
            QBrush brush(brushColor); //设置画刷的颜色（填充色）
            painter.setBrush(brush); //添加画刷
            QPointF points[3] = {QPointF(arrowVertices[1].x,arrowVertices[1].y),
                                 QPointF(arrowVertices[2].x,arrowVertices[2].y),
                                 QPointF(arrowVertices[3].x,arrowVertices[3].y)};
            painter.drawPolygon(points,3,Qt::WindingFill);
            painter.restore();//还原painter的初始状态
        }


    }
}
void DM_Label::drawRect_Label(QPainter &painter, const QRectF &rect)
{
    if(this->isInLabel(rect))
    {
        painter.drawRect(rect);//绘制矩形
    }
}
//=====================================================================================================
//函数名称：在label坐标系统中绘制斜矩形
//参数说明：
//       @painter:绘图设备
//       @points:需要绘制的斜矩形的四个端点
//返回值:
//特殊说明：如果需要绘制方向，传入的代表斜矩形的四个点，顺序必须由DM_Element中DM_RotatedRect类，端点函数getVertices自动生成，
//         否则画的箭头从rect[3]->rect[2],箭头在rect[2]上，可能不是您想要的。
//=====================================================================================================
void DM_Label::drawRotatedRect_Label(QPainter &painter, const std::vector<QPointF> &points)
{
    if(points.size() == 4)
    {
        this->drawLine_Label(painter,QLineF(points[0],points[1]));
        this->drawLine_Label(painter,QLineF(points[1],points[2]));
        this->drawLine_Label(painter,QLineF(points[2],points[3]));
        this->drawLine_Label(painter,QLineF(points[3],points[0]));

    }
}
//=====================================================================================================
//函数名称：在label坐标系统中绘制矢量斜矩形（带箭头方向的斜矩形）
//参数说明：
//       @painter:绘图设备
//       @points:需要绘制的斜矩形的四个端点
//       @D:箭头长度
//返回值:
//特殊说明：如果需要绘制方向，传入的代表斜矩形的四个点，顺序必须由DM_Element中DM_RotatedRect类，端点函数getVertices自动生成，
//         否则画的箭头从rect[3]->rect[2],箭头在rect[2]上，可能不是您想要的。
//=====================================================================================================
void DM_Label::drawDirectedRotatedRect_Label(QPainter &painter, const std::vector<QPointF> &points, double D)
{
    if(points.size() == 4)
    {

        this->drawLine_Label(painter,QLineF(points[0],points[1]));
        this->drawLine_Label(painter,QLineF(points[1],points[2]));
        this->drawLine_Label(painter,QLineF(points[3],points[0]));
        this->drawDirectedLine_label(painter,QLineF(points[3],points[2]),D);
    }
}

void DM_Label::drawCircle_Label(QPainter &painter, const QPointF &center, const double &r)
{
    this->drawEllipse_Label(painter,center,r,r);
}

void DM_Label::drawEllipse_Label(QPainter &painter, const QPointF &center, const double &Rx, const double &Ry)
{
    QRectF boundingRect(QPoint(center.x()-Rx,center.y()-Ry),QSizeF(2*Rx,2*Ry));
    if(isInLabel(boundingRect))
    {
        painter.drawEllipse(center,Rx,Ry);//绘制椭圆
    }
}

void DM_Label::drawEllipse_Label(QPainter &painter, const QRectF &rect)
{
    if(isInLabel(rect))
    {
        painter.drawEllipse(rect);//绘制椭圆
    }
}

void DM_Label::drawRing_Label(QPainter &painter, const QPointF &center, const double &innerR, const double &outerR)
{
    this->drawCircle_Label(painter,center,innerR);
    this->drawCircle_Label(painter,center,outerR);
}

void DM_Label::drawDirectedRing_Label(QPainter &painter, const QPointF &center, const double &innerR, const double &outerR, bool inToOut, double D)
{
    //绘制圆环
    this->drawRing_Label(painter,center,innerR,outerR);

    //绘制方向
    double innerRR,outerRR;
    if(innerR>=outerR)
    {
        innerRR = outerR;
        outerRR = innerR;
    }
    else
    {
        outerRR = outerR;
        innerRR = innerR;
    }
    QRectF outerRect(QPoint(center.x()-outerRR,center.y()-outerRR),QSizeF(2*outerRR,2*outerRR));
    QRectF innerRect(QPoint(center.x()-innerRR,center.y()-innerRR),QSizeF(2*innerRR,2*innerRR));

    double outerRect_midX = (outerRect.left()+outerRect.right())/2;
    double outerRect_midY = (outerRect.top()+outerRect.bottom())/2;

    double innerRect_midX = (innerRect.left()+innerRect.right())/2;
    double innerRect_midY = (innerRect.top() +innerRect.bottom())/2;
    //判定方向
    if(inToOut)
    {

        this->drawDirectedLine_label(painter,QLineF(QPointF(innerRect.left(),innerRect_midY),QPointF(outerRect.left(),outerRect_midY)),D);
        this->drawDirectedLine_label(painter,QLineF(QPointF(innerRect.right(),innerRect_midY),QPointF(outerRect.right(),outerRect_midY)),D);
        this->drawDirectedLine_label(painter,QLineF(QPointF(innerRect_midX,innerRect.top()),QPointF(outerRect_midX,outerRect.top())),D);
        this->drawDirectedLine_label(painter,QLineF(QPointF(innerRect_midX,innerRect.bottom()),QPointF(outerRect_midX,outerRect.bottom())),D);
    }
    else
    {
        this->drawDirectedLine_label(painter,QLineF(QPointF(outerRect.left(),outerRect_midY),QPointF(innerRect.left(),innerRect_midY)),D);
        this->drawDirectedLine_label(painter,QLineF(QPointF(outerRect.right(),outerRect_midY),QPointF(innerRect.right(),innerRect_midY)),D);
        this->drawDirectedLine_label(painter,QLineF(QPointF(outerRect_midX,outerRect.top()),QPointF(innerRect_midX,innerRect.top())),D);
        this->drawDirectedLine_label(painter,QLineF(QPointF(outerRect_midX,outerRect.bottom()),QPointF(innerRect_midX,innerRect.bottom())),D);
    }
}

void DM_Label::drawArc_Label(QPainter &painter, const QPointF &center, const double &Rx, const double &Ry, const double &startAngle, const double &endAngle)
{
    QRectF boundingRect(QPoint(center.x()-Rx,center.y()-Ry),QSizeF(2*Rx,2*Ry));
    if(isInLabel(boundingRect))
    {
        double startAngle_degree = -startAngle;

        //必须控制角度在0-360之间
        while(1)
        {
            if(startAngle_degree>=0)
            {
                if(startAngle_degree > DM_2PI)
                {
                    startAngle_degree = startAngle_degree - DM_2PI;
                }
                else
                {
                    break;
                }
            }
            else
            {
                startAngle_degree = startAngle_degree + DM_2PI;
            }
        }
        startAngle_degree = startAngle_degree *DM_180_PI*16;


        double endAngle_degree = -endAngle;
        while(1)
        {
            if(endAngle_degree>= 0)
            {
                if(endAngle_degree > DM_2PI)
                {
                    endAngle_degree = endAngle_degree - DM_2PI;
                }
                else
                {
                    break;
                }
            }
            else
            {
                endAngle_degree = endAngle_degree + DM_2PI;
            }
        }
        endAngle_degree = endAngle_degree *DM_180_PI*16;
        double spanAngle_degree  = 0;
        if(startAngle_degree <= endAngle_degree)
        {
            spanAngle_degree = endAngle_degree -5760 - startAngle_degree;
        }
        else
        {
            spanAngle_degree = endAngle_degree -  startAngle_degree;
        }

        painter.drawArc(boundingRect,startAngle_degree,spanAngle_degree);
    }
}

void DM_Label::drawArc_Label(QPainter &painter, const QRectF &rect, const double &startAngle, const double &endAngle)
{
    if(isInLabel(rect))
    {
        double startAngle_degree = -startAngle*DM_180_PI*16;
        double endAngle_degree = -endAngle*DM_180_PI*16;
        double spanAngle_degree = endAngle_degree - startAngle_degree;
        painter.drawArc(rect,startAngle_degree,spanAngle_degree);
    }
}

void DM_Label::drawPie_Label(QPainter &painter, const QPointF &center, const double &Rx, const double &Ry, const double &startAngle, const double &endAngle)
{
    QRectF boundingRect(QPoint(center.x()-Rx,center.y()-Ry),QSizeF(2*Rx,2*Ry));
    if(isInLabel(boundingRect))
    {
        double startAngle_degree = -startAngle;
        //必须控制角度在0-360之间
        while(1)
        {
            if(startAngle_degree>=0)
            {
                if(startAngle_degree > DM_2PI)
                {
                    startAngle_degree = startAngle_degree - DM_2PI;
                }
                else
                {
                    break;
                }
            }
            else
            {
                startAngle_degree = startAngle_degree + DM_2PI;
            }
        }
        startAngle_degree = startAngle_degree *DM_180_PI*16;


        double endAngle_degree = -endAngle;
        while(1)
        {
            if(endAngle_degree>= 0)
            {
                if(endAngle_degree > DM_2PI)
                {
                    endAngle_degree = endAngle_degree - DM_2PI;
                }
                else
                {
                    break;
                }
            }
            else
            {
                endAngle_degree = endAngle_degree + DM_2PI;
            }
        }
        endAngle_degree = endAngle_degree *DM_180_PI*16;
        double spanAngle_degree  = 0;
        if(startAngle_degree <= endAngle_degree)
        {
            spanAngle_degree = endAngle_degree -5760 - startAngle_degree;
        }
        else
        {
            spanAngle_degree = endAngle_degree -  startAngle_degree;
        }
        painter.drawPie(boundingRect,startAngle_degree,spanAngle_degree);
    }
}

void DM_Label::drawPie_Label(QPainter &painter, const QRectF &rect, const double &startAngle, const double &endAngle)
{
    if(isInLabel(rect))
    {
        double startAngle_degree = -startAngle*DM_180_PI*16;
        double endAngle_degree = -endAngle*DM_180_PI*16;
        double spanAngle_degree = endAngle_degree - startAngle_degree;
        painter.drawPie(rect,startAngle_degree,spanAngle_degree);
    }
}

void DM_Label::drawSector_Label(QPainter &painter, const QPointF &center, const double &innerR, const double &outerR, const double &startAngle, const double &endAngle)
{
    this->drawArc_Label(painter,center,innerR,innerR,startAngle,endAngle);
    this->drawArc_Label(painter,center,outerR,outerR,startAngle,endAngle);

    double innerRR,outerRR;
    if(innerR>=outerR)
    {
        innerRR = outerR;
        outerRR = innerR;
    }
    else
    {
        outerRR = outerR;
        innerRR = innerR;
    }
    QPointF outerStartPt = QPointF(center.x() + outerRR * cos(startAngle), center.y() + outerRR * sin(startAngle));
    QPointF outerEndPt = QPointF(center.x() + outerRR * cos(endAngle),center.y() + outerRR * sin(endAngle));
    QPointF innerStartPt = QPointF(center.x() + innerRR * cos(startAngle),center.y() + innerRR * sin(startAngle));
    QPointF innerEndPt = QPointF(center.x() + innerRR * cos(endAngle),center.y() + innerRR * sin(endAngle));

    this->drawLine_Label(painter,QLineF(outerStartPt,innerStartPt));
    this->drawLine_Label(painter,QLineF(outerEndPt,innerEndPt));
}

void DM_Label::drawDirectedSector_Label(QPainter &painter, const QPointF &center, const double &innerR, const double &outerR,
                                        const double &startAngle, const double &endAngle, bool inToOut, double D)
{
    this->drawArc_Label(painter,center,innerR,innerR,startAngle,endAngle);
    this->drawArc_Label(painter,center,outerR,outerR,startAngle,endAngle);
    double innerRR,outerRR;

    if(innerR>=outerR)
    {
        innerRR = outerR;
        outerRR = innerR;
    }
    else
    {
        outerRR = outerR;
        innerRR = innerR;
    }
    QPointF outerStartPt = QPointF(center.x() + outerRR * cos(startAngle), center.y() + outerRR * sin(startAngle));
    QPointF outerEndPt = QPointF(center.x() + outerRR * cos(endAngle),center.y() + outerRR * sin(endAngle));
    QPointF innerStartPt = QPointF(center.x() + innerRR * cos(startAngle),center.y() + innerRR * sin(startAngle));
    QPointF innerEndPt = QPointF(center.x() + innerRR * cos(endAngle),center.y() + innerRR * sin(endAngle));
    if(inToOut)
    {
        this->drawDirectedLine_label(painter,QLineF(innerStartPt,outerStartPt),D);
        this->drawDirectedLine_label(painter,QLineF(innerEndPt,outerEndPt),D);
    }
    else
    {
        this->drawDirectedLine_label(painter,QLineF(outerStartPt,innerStartPt),D);
        this->drawDirectedLine_label(painter,QLineF(outerEndPt,innerEndPt),D);
    }
}

void DM_Label::drawPoint_IMG(const DM_Point &point, const QColor color, double thickness, Tag_DM piontType, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿

    QPointF  pointTemp;
    this->transformImgTolabel_Point(point,pointTemp);
    this->drawPoint_Label(painter,pointTemp,piontType,D);
}

void DM_Label::drawPoints_IMG(const std::vector<cv::Point> &points, const QColor color, double thickness, Tag_DM pointType, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿

    QPointF  pointTemp;
    for(int i = 0; i < points.size(); i++)
    {
        this->transformImgTolabel_Point(points[i],pointTemp);
        this->drawPoint_Label(painter,pointTemp,pointType,D);
    }

}

void DM_Label::drawLine_IMG(const DM_Line &line, const QColor color, double thickness, Tag_DM lineType)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    QLineF outLine;
    this->transformImgTolabel_Line(line,outLine);
    this->drawLine_Label(painter,outLine);
}

void DM_Label::drawDirectedLine_IMG(const DM_Line &line, const QColor color, double thickness, Tag_DM lineType, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    QLineF outLine;
    this->transformImgTolabel_Line(line,outLine);
    this->drawDirectedLine_label(painter,outLine,D);
}

void DM_Label::drawRotatedRect_IMG(const DM_RotatedRect &rect, const QColor color, double thickness, Tag_DM lineType)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿



    std::vector<DM_Point> vertices = rect.getVertices();
    //将图像坐标系转化成label坐标系
    std::vector<QPointF>  vertices_label(4);
    this->transformImgTolabel_Point(vertices[0],vertices_label[0]);
    this->transformImgTolabel_Point(vertices[1],vertices_label[1]);
    this->transformImgTolabel_Point(vertices[2],vertices_label[2]);
    this->transformImgTolabel_Point(vertices[3],vertices_label[3]);

    this->drawRotatedRect_Label(painter,vertices_label);
}

void DM_Label::drawDirectedRotatedRect_IMG(const DM_RotatedRect &rect, const QColor color, double thickness, Tag_DM lineType, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿



    std::vector<DM_Point> vertices = rect.getVertices();
    //将图像坐标系转化成label坐标系
    std::vector<QPointF>  vertices_label(4);
    this->transformImgTolabel_Point(vertices[0],vertices_label[0]);
    this->transformImgTolabel_Point(vertices[1],vertices_label[1]);
    this->transformImgTolabel_Point(vertices[2],vertices_label[2]);
    this->transformImgTolabel_Point(vertices[3],vertices_label[3]);

    this->drawDirectedRotatedRect_Label(painter,vertices_label,D);
}

void DM_Label::drawRect_IMG(const DM_Rect& rect, const QColor color, double thickness, Tag_DM lineType)
{
    if(!rect.isValid()) return;
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿

    QPointF leftTopP,rightBottomP;
    this->transformImgTolabel_Point(rect.leftTop,leftTopP);
    this->transformImgTolabel_Point(rect.rightBottom,rightBottomP);
    this->drawRect_Label(painter,QRectF(leftTopP,rightBottomP));
}

void DM_Label::drawCircle_IMG(const DM_Circle &circle, const QColor color, double thickness, Tag_DM lineType)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    DM_Rect boundingRect= circle.getBoundingRect();
    QPointF leftTopP,rightBottomP;
    this->transformImgTolabel_Point(boundingRect.leftTop,leftTopP);
    this->transformImgTolabel_Point(boundingRect.rightBottom,rightBottomP);
    this->drawEllipse_Label(painter,QRectF(leftTopP,rightBottomP));
}

void DM_Label::drawEllipse_IMG(const DM_Ellipse &ellipse, const QColor color, double thickness, Tag_DM lineType)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    QPointF centerP;
    this->transformImgTolabel_Point(ellipse.center,centerP);
    painter.translate(centerP);//设置坐标系的中心
    painter.rotate(ellipse.angle*DM_180_PI);//设置旋转角度（以顺时针方向为正）

    double a,b;
    this->transformImgTolabel_L(ellipse.a,a);//Y 轴方向的轴
    this->transformImgTolabel_L(ellipse.b,b);//X 轴方向的轴

    this->drawEllipse_Label(painter,QPoint(0,0),b,a);
}

void DM_Label::drawRing_IMG(const DM_Ring &ring, const QColor color, double thickness, Tag_DM lineType, int direction, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿
    QPointF center;
    double outerR,innerR;
    this->transformImgTolabel_Point(ring.center,center);
    this->transformImgTolabel_L(ring.outerRadius,outerR);
    this->transformImgTolabel_L(ring.innerRadius,innerR);
    if (direction ==  0)
    {
        this->drawDirectedRing_Label(painter, center, innerR, outerR, true, D);
    }
    else if (direction == 1)
    {
        this->drawDirectedRing_Label(painter, center, innerR, outerR, false, D);
    }
    else
    {
        this->drawRing_Label(painter,center,innerR,outerR);
    }
}

void DM_Label::drawDirectedRing_IMG(const DM_Ring &ring, const QColor color, double thickness, Tag_DM lineType,bool inToOut, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿

    QPointF center;
    double outerR,innerR;
    this->transformImgTolabel_Point(ring.center,center);
    this->transformImgTolabel_L(ring.outerRadius,outerR);
    this->transformImgTolabel_L(ring.innerRadius,innerR);
    this->drawDirectedRing_Label(painter,center,innerR,outerR,inToOut,D);
}

void DM_Label::drawArc_IMG(const DM_Arc &arc, const QColor color, double thickness, Tag_DM lineType)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    QPointF center;
    double R;
    this->transformImgTolabel_Point(arc.center,center);
    this->transformImgTolabel_L(arc.radius,R);
    this->drawArc_Label(painter,center,R,R,arc.startAngle,arc.endAngle);
}

void DM_Label::drawPie_IMG(const DM_Pie &pie, const QColor color, double thickness, Tag_DM lineType)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    QPointF center;
    double R;
    this->transformImgTolabel_Point(pie.center,center);
    this->transformImgTolabel_L(pie.R,R);
    this->drawPie_Label(painter,center,R,R,pie.startAngle,pie.endAngle);
}

void DM_Label::drawSector_IMG(const DM_Sector &sector, const QColor color, double thickness, Tag_DM lineType, int direction, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    QPointF center;
    double outerR,innerR;
    this->transformImgTolabel_Point(sector.center,center);
    this->transformImgTolabel_L(sector.outerRadius,outerR);
    this->transformImgTolabel_L(sector.innerRadius,innerR);
    if (direction ==  0)
    {
        this->drawDirectedSector_Label(painter, center, innerR, outerR, sector.startAngle, sector.endAngle, true, D);
    }
    else if (direction == 1)
    {
        this->drawDirectedSector_Label(painter, center, innerR, outerR, sector.startAngle, sector.endAngle, false, D);
    }
    else
    {
        this->drawSector_Label(painter,center,innerR,outerR,sector.startAngle,sector.endAngle);
    }

}

void DM_Label::drawDirectedSector_IMG(const DM_Sector &sector, const QColor color, double thickness, Tag_DM lineType, bool inToOut, double D)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color), thickness);//绘制元素主体
    //设置线型
    if(lineType == DashLine_PT)//虚线------
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(lineType == DotLine_PT)//点线* * * *
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(lineType == DashDotLine_PT)//点画线*-*-*-
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(lineType == DashDotDotLine_PT)//点画线**-**-**-
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else//直线—————
    {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿


    QPointF center;
    double outerR,innerR;
    this->transformImgTolabel_Point(sector.center,center);
    this->transformImgTolabel_L(sector.outerRadius,outerR);
    this->transformImgTolabel_L(sector.innerRadius,innerR);
    this->drawDirectedSector_Label(painter,center,innerR,outerR,sector.startAngle,sector.endAngle,inToOut,D);
}

void DM_Label::drawText_IMG(const QString &str, const DM_Point &P, const QColor color, int wordSize, double angle)
{
    QPainter painter(this);//绘制元素主体
    QPen pen(QBrush(color),1);//绘制元素主体
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);//消锯齿
    QFont font(QStringLiteral("微软雅黑"), wordSize);
    painter.setFont(font);

    QPointF center;
    this->transformImgTolabel_Point(P,center);
    painter.translate(center);//设置坐标系的中心
    painter.rotate(angle*DM_180_PI);//设置旋转角度（以顺时针方向为正）

    // painter.drawText(QPointF(0,0),QString::fromLocal8Bit(str.c_str()));//当传入的数据是string时；
    painter.drawText(QPointF(0,0),str);
}



//缩放图片
void DM_Label::zoomImage(double zoomValue_)
{
    if(this->src.isNull())
    {
        return;
    }
    if(zoomValue_ < this->minZoomOutTimes)
    {
        if(this->zoomValue <= this->minZoomOutTimes)
        {
            return;
        }
        else
        {
            this->zoomValue = this->minZoomOutTimes;
        }
    }
    else if(zoomValue_ > this->maxZoomInTimes)
    {
        if(this->zoomValue >= this->maxZoomInTimes)
        {
            return;
        }
        else
        {
            this->zoomValue = this->maxZoomInTimes;
        }
    }
    else
    {
        this->zoomValue = zoomValue_;
    }
    QPointF center = this->rect.center();

    double x,y,w,h;
    w  = this->width()/this->zoomValue;
    if(w >= this->src.width())
    {
        x = 0;
        w = this->src.width();
    }
    else
    {
        if(w*0.5 <= center.x()+1 && this->src.width() > center.x()+w*0.5 )
        {
            x = center.x() - w*0.5;
        }
        else if(this->src.width() <= center.x()+w*0.5 )
        {
            x = this->src.width() - w;
        }
        else
        {
            x = 0;
        }
    }
    h = this->height()/this->zoomValue;
    if(h >= this->src.height())
    {
        y = 0;
        h = this->src.height();
    }
    else
    {
        if(h*0.5 <= center.y()+1 && this->src.height() > center.y()+h*0.5 )
        {
            y = center.y() - h*0.5;
        }
        else if(this->src.height() <= center.y()+h*0.5 )
        {
            y = this->src.height() - h;
        }
        else
        {
            y = 0;
        }
    }
    this->rect = QRectF(QPointF(x,y),QSizeF(w,h));
    this->labelWidth = w * this->zoomValue;
    this->labelHeight = h * this->zoomValue;

//	qDebug()<<QStringLiteral("放大倍数：")<<this->zoomValue
//		   <<  " labelWidth =  "<< this->labelWidth
//			<<  " labelHeight = "<<this->labelHeight
//			 <<  " cneter = " << center
//			  <<  " LabelRECT = " << this->x() << " , "<< this->y() << "," << this->width() << " * "<< this->height()
//			   <<  " IMGrect = " << this->rect;



    this->showImage();
    emit changeImageRectSignal(this->rect);//当重新取图之后发送取图区域
}
//移动图片(绝对位置)【将rect的topLeft移动到P(dx,dy)】
void DM_Label::moveImageAbs(double dx, double dy)
{
    if(this->src.isNull())
    {
        return;
    }
    double moveX = 0;
    double moveY = 0;
    //得到缩放中心
    if(dx >= 0)
    {
        moveX = dx/this->zoomValue;
    }
    else
    {
        moveX = this->rect.x();
    }
    if(dy >= 0)
    {
        moveY = dy/this->zoomValue;
    }
    else
    {
        moveY = this->rect.y();
    }

    //调整rect的中心区域
    if(this->rect.width() > 0 && this->rect.height() > 0)
    {
        QPointF topLetf = QPointF(moveX,moveY);
        //topLetf = QPointF(topLetf.x() + moveX, topLetf.y() + moveY);//将中心移动一下

        double x,y,w,h;
        w  = this->width()/this->zoomValue;
        if(w >= this->src.width())
        {
            x = 0;
            w = this->src.width();
        }
        else
        {
            if(topLetf.x() < 0)
            {
                x = 0;
            }
            else if(topLetf.x() >= 0 && topLetf.x() + w <= this->src.width())
            {
                x = topLetf.x();
            }
            else
            {
                x = this->src.width() - w;
            }
        }
        h = this->height()/this->zoomValue;
        if(h >= this->src.height())
        {
            y = 0;
            h = this->src.height();
        }
        else
        {
            if(topLetf.y() < 0)
            {
                y = 0;
            }
            else if(topLetf.y() >= 0 && topLetf.y() + h <= this->src.height())
            {
                y = topLetf.y();
            }
            else
            {
                y = this->src.height() - h;
            }
        }
        this->rect = QRectF(QPointF(x,y),QSizeF(w,h));
    }

    this->showImage();
}
//设置最大放大倍数
void DM_Label::setMaxZoomInTimes(const int maxZoomInTimes)
{
    if(maxZoomInTimes > 0 && maxZoomInTimes >= this->minZoomOutTimes)
    {
        this->maxZoomInTimes = maxZoomInTimes;
    }
}

//设置最小缩小倍数
void DM_Label::setMinZoomOutTimes(const int minZoomOutTimes)
{
    if(minZoomOutTimes > 0 && minZoomOutTimes <= this->maxZoomInTimes)
    {
        this->minZoomOutTimes = minZoomOutTimes;
    }
}

//设置从最小缩小倍数到最大放大倍数的缩放次数
void DM_Label::setMaxZoomTimes(const int maxZoomTimes)
{
    if(maxZoomTimes > 1)
    {
        this->maxZoomTimes = maxZoomTimes;
    }
}
//放大图片
void DM_Label::zoomInImage()
{
    this->zoomImage(this->zoomValue+this->zoomBase);
}
//缩小图片
void DM_Label::zoomOutImage()
{
    this->zoomImage(this->zoomValue-this->zoomBase);
}
//将图片调整至适屏状态，将当前压缩比例调整至最小；
void DM_Label::toFitScreen()
{
    if(this->src.width() > 0 &&
       this->src.height() > 0 &&
       this->zoomBase > 0)
    {
        this->rect = QRectF( QPointF(0,0),QSizeF(this->src.width(),this->src.height()));

        double zoomValueTempW = double(this->width())/this->src.width();
        double zoomValueTempH = double(this->height())/this->src.height();
        double zoomValueTemp = zoomValueTempH > zoomValueTempW ? zoomValueTempW : zoomValueTempH;
        int k = (zoomValueTemp - this->minZoomOutTimes)/this->zoomBase;
        if(k < 0)
        {
            k = 0;
        }
        else if (k > this->maxZoomTimes)
        {
            k = this->maxZoomTimes;
        }
        this->zoomValue = this->zoomBase*k + this->minZoomOutTimes;
        this->labelWidth = this->src.width() * this->zoomValue;
        this->labelHeight = this->src.height() * this->zoomValue;
        this->showImage();
        emit changeImageRectSignal(this->rect);
    }

}

void DM_Label::setCenterCrossFlag(bool flag /*= true*/)
{
    this->showCenterCrossFlag = flag;
    this->update();
}

void DM_Label::changeCenterCrossFlag()
{
    if (this->showCenterCrossFlag)
    {
        this->showCenterCrossFlag = false;
    }
    else
    {
        this->showCenterCrossFlag = true;
    }
    this->update();
}

void DM_Label::setScrollBar(QScrollBar *HScrollBar_, QScrollBar *VScrollBar_)
{
    //如果进入该函数，此两个指针不为空，说明没有进行初始化；
    if (this->HScrollBar == nullptr &&
        this->VScrollBar == nullptr)
    {
        this->HScrollBar = HScrollBar_;
        this->VScrollBar = VScrollBar_;

        //设置竖直卷轴
        this->VScrollBar->setMaximum(100);
        this->VScrollBar->setMinimum(0);
        //设置水平卷轴
        this->HScrollBar->setMaximum(100);
        this->HScrollBar->setMinimum(0);

        //信号与槽函数
        connect(this->HScrollBar,SIGNAL(valueChanged(int)),this,SLOT(HScrollBar_ValueChange(int)));
        connect(this->VScrollBar,SIGNAL(valueChanged(int)),this,SLOT(VScrollBar_ValueChange(int)));
        connect(this,SIGNAL(changeImageRectSignal(QRectF)),this,SLOT(scrollBar_setValue()));
    }
}

void DM_Label::setPixelMessageflag(bool flag /*= true*/)
{
    this->showPixelMessageflag = flag;
}

void DM_Label::revocationElements()
{
    if (!this->elements.empty())
    {
        this->elements.pop_back();
    }
}

void DM_Label::clearElements()
{
    this->elements.clear();
}

bool DM_Label::deleteElements(size_t index)
{
    if(index >= this->elements.size())
    {
        return false;
    }
    if(index < this->elements.size() && index >= 0)
    {
        this->elements.erase(this->elements.begin()+index);//删除该元素
        return true;
    }
    else
    {
        return false;
    }
}

void DM_Label::addElements(DM_LabelElement element_)
{
    this->elements.push_back(element_);
}

void DM_Label::setElements(const std::vector<DM_LabelElement> &element_)
{
    this->elements.clear();
    for(int i = 0; i < element_.size(); i++)
    {
        this->elements.push_back(element_[i]);
    }
}


void DM_Label::revocationTexts()
{
    this->texts.pop_back();
}

void DM_Label::clearTexts()
{
    this->texts.clear();
}

bool DM_Label::deleteTexts(size_t index)
{
    if (index >= this->texts.size())
    {
        return false;
    }
    if (index < this->texts.size() && index >= 0)
    {
        this->texts.erase(this->texts.begin() + index);//删除该元素
        return true;
    }
    else
    {
        return false;
    }
}

void DM_Label::addTexts(DM_LabelText text_)
{
    this->texts.push_back(text_);
}

void DM_Label::setTexts(const std::vector<DM_LabelText> &text_)
{
    this->texts.clear();
    for (int i = 0; i < text_.size(); i++)
    {
        this->texts.push_back(text_[i]);
    }
}

void DM_Label::setShowDrawElementFlag(bool flag /*= true*/)
{
    this->showDrawElementFlag = flag;
}
void DM_Label::setElementIndex(Tag_DM index)
{
    this->elementIndex = index;
    this->drawFlag = false;

    this->drawRingStep = 0;
    this->ringPoints.clear();

    this->drawSectorStep = 0;
    this->sectorPoints.clear();

    this->drawRotatedRectStep = 0;
    this->rotatedRectPoints.clear();
}


//鼠标按下
void DM_Label::mousePressEvent(QMouseEvent *ev)
{
    this->setCursor(Qt::ArrowCursor);
    this->startPos = ev->pos();

    //右键清空显示
    if (ev->button() == Qt::RightButton)
    {
        //将绘图信号复位
        this->clearDrawStatus();
        this->clearElements();
        return;
    }

    //按下ctrl + 鼠标左键：实现图片拖动功能
    if (ev->button() == Qt::LeftButton &&
        QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        this->rectMove = this->rect;
        this->dragFlag = true;
        //将绘图信号复位
        this->clearDrawStatus();
    }
    //判定是否启动绘图功能
    if(this->elementIndex != Default_DM&&
       ev->button() == Qt::LeftButton &&
       QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
        this->dragFlag = false;//将拖动信号复位
        this->showDrawElementFlag = true;
        this->drawElememt = DM_LabelElement();
        switch(this->elementIndex)
        {
            case Line_ELMT:
            {
                this->lineElement_MousePress(ev);
                break;
            }
            case RotatedRect_ELMT://绘制斜矩形
            {
                this->rotatedRectElement_MousePress(ev);
                break;
            }
            case Ring_ELMT://绘制圆环
            {
                this->ringElement_MousePress(ev);
                break;
            }
            case Sector_ELMT://绘制扇环
            {
                this->sectorElement_MousePress(ev);
                break;
            }

            case Rect_ELMT:
            {
                this->rectElement_MousePress(ev);
                break;
            }
            default:
            {
                this->drawFlag = false;
                break;
            }
        }

    }
}
//鼠标释放
void DM_Label::mouseReleaseEvent(QMouseEvent *ev)
{
    this->setCursor(Qt::ArrowCursor);
    this->dragFlag = false;//将拖拽标志复位
    //右键清空显示
    if (ev->button() == Qt::RightButton)
    {
        return;
    }
    //处理绘图信号_将绘图元素储存起来
    if(this->width() > 0 &&
       this->height() > 0 &&
       !this->src.isNull()&&
       !this->dragFlag&&
       this->drawFlag&&
       this->elementIndex != Default_DM    )
    {
        //绘制直线
        this->endPos = ev->pos();
        switch(this->elementIndex)
        {
            case Line_ELMT://绘制直线
            {
                this->lineElement_MouseRelease(ev);
                break;
            }
            case RotatedRect_ELMT://绘制斜矩形
            {
                this->rotatedRectElement_MouseRelease(ev);
                break;
            }
            case Ring_ELMT://绘制圆环
            {
                this->ringElement_MouseRelease(ev);
                break;
            }
            case Sector_ELMT://绘制扇环
            {
                this->sectorElement_MouseRelease(ev);
                break;
            }
            case Rect_ELMT://绘制矩形
            {
                this->rectElement_MouseRelease(ev);
                break;
            }
            default:
            break;
        }

    }
    else
    {
        this->drawFlag = false;
    }
}

//鼠标移动事件
void DM_Label::mouseMoveEvent(QMouseEvent *ev)
{
    //显示图片的位置和灰度值
    if (!this->src.isNull())
    {
        DM_Point pos_;
        this->transformLabeToImg_Point(ev->pos(), pos_);
        if (this->isInLabel(pos_))
        {
            QString text_Pixel = QString("Pos:(%1,%2)").arg(QString::number(int(pos_.x)), QString::number(int(pos_.y)));
            QColor rgb_ = this->src.pixelColor(QPoint(pos_.x, pos_.y));
            QString text_color = QString("RGB:(%1,%2,%3)").arg(QString::number(rgb_.red()), QString::number(rgb_.green()), QString::number(rgb_.blue()));
            emit sendPixelInformation(text_Pixel+"  "+ text_color);
            if(this->showPixelMessageflag)
            {
                QToolTip::showText(QCursor::pos(), text_Pixel+'\n'+ text_color+'\n');
            }
        }
    }
    //更改鼠标图案
    if (this->dragFlag)
    {
        this->setCursor(Qt::OpenHandCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }

    if(this->src.isNull())
    {
        return;
    }
    if(this->drawFlag)//启动绘画功能
    {
        this->endPos = ev->pos();
        update();
    }
    if (this->dragFlag)//画布移动
    {
        QPointF point = ev->pos() - this->startPos;
        double moveX = point.x() / this->zoomValue;
        double moveY = point.y() / this->zoomValue;
        //调整rect的中心区域
        if(this->rectMove.width() > 0 && this->rectMove.height() > 0&&(moveX != 0 || moveY != 0))
        {
            QPointF topLetf = this->rectMove.topLeft();
            topLetf = QPointF(topLetf.x() - moveX, topLetf.y() - moveY);//将中心移动一下

            double x,y,w,h;
            w  = this->width()/this->zoomValue;
            if(w >= this->src.width())
            {
                x = 0;
                w = this->src.width();
            }
            else
            {
                if(topLetf.x() < 0)
                {
                    x = 0;
                }
                else if(topLetf.x() >= 0 && topLetf.x() + w <= this->src.width())
                {
                    x = topLetf.x();
                }
                else
                {
                    x = this->src.width() - w;
                }
            }
            h = this->height()/this->zoomValue;
            if(h >= this->src.height())
            {
                y = 0;
                h = this->src.height();
            }
            else
            {
                if(topLetf.y() < 0)
                {
                    y = 0;
                }
                else if(topLetf.y() >= 0 && topLetf.y() + h <= this->src.height())
                {
                    y = topLetf.y();
                }
                else
                {
                    y = this->src.height() - h;
                }
            }
            this->rect = QRectF(QPointF(x,y),QSizeF(w,h));
        }
        this->showImage();
        emit changeImageRectSignal(this->rect);//当重新取图之后发送取图区域
    }
}
//重构滚轮事件
void DM_Label::wheelEvent(QWheelEvent *ev)
{
    this->setCursor(Qt::ArrowCursor);
    if(this->src.isNull())
    {
        return;
    }
    //得到缩放比例
    double zoomValueTemp = this->zoomValue;
    if (ev->delta() > 0)  //delta（）为正，滚轮向上滚
    {
        zoomValueTemp = zoomValueTemp + this->zoomBase;
    }
    else
    {
        zoomValueTemp = zoomValueTemp - this->zoomBase;
    }
    double zoomValueLast = this->zoomValue;//暂存上次的比例尺
    if (zoomValueTemp >= this->maxZoomInTimes)
    {
        if(this->zoomValue >= this->maxZoomInTimes)
        {
            return;
        }
        else
        {
            this->zoomValue = this->maxZoomInTimes;
        }
    }
    else if (zoomValueTemp <= this->minZoomOutTimes)
    {
        if(this->zoomValue <= this->minZoomOutTimes)
        {
            return;
        }
        else
        {
            this->zoomValue = this->minZoomOutTimes;
        }
    }
    else
    {
        this->zoomValue = zoomValueTemp;
    }
    //得到缩放中心
    double moveX = ev->pos().x()/zoomValueLast - ev->pos().x()/this->zoomValue;
    double moveY = ev->pos().y()/zoomValueLast - ev->pos().y()/this->zoomValue;
    //调整rect的中心区域
    if(this->rect.width() > 0 && this->rect.height() > 0)
    {
        QPointF topLetf = this->rect.topLeft();
        topLetf = QPointF(topLetf.x() + moveX, topLetf.y() + moveY);//将中心移动一下

        double x,y,w,h;
        w  = this->width()/this->zoomValue;
        if(w >= this->src.width())
        {
            x = 0;
            w = this->src.width();
        }
        else
        {
            if(topLetf.x() < 0)
            {
                x = 0;
            }
            else if(topLetf.x() >= 0 && topLetf.x() + w <= this->src.width())
            {
                x = topLetf.x();
            }
            else
            {
                x = this->src.width() - w;
            }
        }
        h = this->height()/this->zoomValue;
        if(h >= this->src.height())
        {
            y = 0;
            h = this->src.height();
        }
        else
        {
            if(topLetf.y() < 0)
            {
                y = 0;
            }
            else if(topLetf.y() >= 0 && topLetf.y() + h <= this->src.height())
            {
                y = topLetf.y();
            }
            else
            {
                y = this->src.height() - h;
            }
        }
        this->rect = QRectF(QPointF(x,y),QSizeF(w,h));
    }
    this->labelWidth = this->rect.width() * this->zoomValue;
    this->labelHeight = this->rect.height() * this->zoomValue;
    this->showImage();
    emit changeImageRectSignal(this->rect);//当重新取图之后发送取图区域
}

//重构绘图事件
void DM_Label::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);//必须有，才能让自己设置的背景图片显示出来
    if(this->rect.width() > 0 && this->rect.height() > 0)
    {
        //绘制实时图像（即：鼠标移动绘制的图像）
        if(this->drawFlag)
        {
            switch(this->elementIndex)
            {

                case Line_ELMT://绘制直线
                {
                    this->lineElement_MouseMove();
                    break;
                }
                case RotatedRect_ELMT://绘制斜矩形
                {
                    this->rotatedRectElement_MouseMove();
                    break;
                }

                case Ring_ELMT://绘制圆环
                {
                    this->ringElement_MouseMove();
                    break;
                }

                case Sector_ELMT://绘制扇环
                {
                    this->sectorElement_MouseMove();
                    break;
                }
                case Rect_ELMT://绘制矩形
                {
                    this->rectElement_MouseMove();
                    break;
                }
                default:;
            }
        }
        //显示绘制的最后一个元素
        if(this->showDrawElementFlag)
        {
           DM_LabelElement_paintEvent(this->drawElememt);
        }
        //绘制elements
        for(int i = 0; i < this->elements.size(); i++)
        {
            DM_LabelElement_paintEvent(this->elements[i]);
        }

        //显示文字
        for (int i= 0; i < this->texts.size(); i++)
        {
            this->drawText_IMG(this->texts[i].text, this->texts[i].pos, this->texts[i].color, this->texts[i].wordSize, this->texts[i].angle);
        }
    }
    //在label中心显示十字
    this->centerCross_paintEvent();
}

//重构窗口缩放事件
void DM_Label::resizeEvent(QResizeEvent *ev)
{
    QLabel::resizeEvent(ev);
    if(this->src.isNull())
    {
        return;
    }
    //更新最小放大倍数
    double sW = double(this->width())/this->src.width();
    double sH = double(this->height())/this->src.height();
    if(sW >= 1 && sH >= 1)
    {
        this->minZoomOutTimes =1.0;
    }
    else if(sW <= sH && sW > 0)
    {
        this->minZoomOutTimes = sW;
    }
    else if(sW >= sH && sH > 0)
    {
        this->minZoomOutTimes = sH;
    }
    if(this->zoomValue < this->minZoomOutTimes)
    {
       this->zoomValue =  this->minZoomOutTimes;
    }

    //调整rect的中心区域
    if(this->rect.width() > 0 && this->rect.height() > 0)
    {
        QPointF topLetf = this->rect.topLeft();

        double x,y,w,h;
        w  = this->width()/this->zoomValue;
        if(w >= this->src.width())
        {
            x = 0;
            w = this->src.width();
        }
        else
        {
            if(topLetf.x() + w <= this->src.width())
            {
                x = topLetf.x();
            }
            else
            {
                x = this->src.width() - w;
            }
        }
        h = this->height()/this->zoomValue;
        if(h >= this->src.height())
        {
            y = 0;
            h = this->src.height();
        }
        else
        {
            if(topLetf.y() >= 0 && topLetf.y() + h <= this->src.height())
            {
                y = topLetf.y();
            }
            else
            {
                y = this->src.height() - h;
            }
        }
        this->rect = QRectF(QPointF(x,y),QSizeF(w,h));
    }
    this->labelWidth = this->rect.width() * this->zoomValue;
    this->labelHeight = this->rect.height() * this->zoomValue;
    this->showImage();
    emit changeImageRectSignal(this->rect);//当重新取图之后发送取图区域
}

void DM_Label::HScrollBar_ValueChange(int value)
{
    if(!this->setHScrollBarValueFlag)
    {
        this->moveImageAbs(value*this->zoomValue,-1);
    }
    else
    {
        this->setHScrollBarValueFlag = false;
    }
}

void DM_Label::VScrollBar_ValueChange(int value)
{
    if(!this->setVScrollBarValueFlag)
    {
        this->moveImageAbs(-1,value*this->zoomValue);
    }
    else
    {
        this->setVScrollBarValueFlag = false;
    }
}
void DM_Label::scrollBar_setValue()
{
    double w = this->src.width()-this->rect.width();
    double h = this->src.height()-this->rect.height();
    double x = this->rect.x();//获取在原图中的取图起点
    double y = this->rect.y();//获取在原图中的取图起点

    this->HScrollBar->setMaximum(w);
    this->VScrollBar->setMaximum(h);
    this->HScrollBar->setValue(x);
    this->VScrollBar->setValue(y);
    this->setHScrollBarValueFlag = true;
    this->setVScrollBarValueFlag = true;
}

DM_LabelElement::DM_LabelElement(DM_Element *element_, bool vectorFlag_, QColor color_, double width_,Tag_DM penType_)
{
    if(element_ != nullptr&&
       element_->isValid())
    {
        switch(element_->type)
        {
            case Point_ELMT://点
            {
                DM_Point *temp =  dynamic_cast<DM_Point*>(element_);
                this->element = new DM_Point(temp->x,temp->y);
                break;
            }
            case Line_ELMT://直线
            {
                DM_Line *temp =  dynamic_cast<DM_Line*>(element_);
                this->element = new DM_Line(temp->P1,temp->P2);
                break;
            }
            case Circle_ELMT://圆
            {
                DM_Circle *temp =  dynamic_cast<DM_Circle*>(element_);
                this->element = new DM_Circle(temp->center,temp->radius);
                break;
            }
            case Ring_ELMT://圆环
            {
                DM_Ring *temp =  dynamic_cast<DM_Ring*>(element_);
                this->element = new DM_Ring(temp->center,temp->innerRadius,temp->outerRadius);
                break;
            }
            case Arc_ELMT://弧线
            {
                DM_Arc *temp =  dynamic_cast<DM_Arc*>(element_);
                this->element = new DM_Arc(temp->startPoint,temp->midPoint,temp->endPoint);
                break;
            }
            case RotatedRect_ELMT ://斜矩形
            {
                DM_RotatedRect *temp =  dynamic_cast<DM_RotatedRect*>(element_);
                this->element = new DM_RotatedRect(temp->center,temp->size,temp->angle);
                break;
            }
            case Rect_ELMT://矩形
            {
                DM_Rect *temp =  dynamic_cast<DM_Rect*>(element_);
                this->element = new DM_Rect(temp->leftTop,temp->rightBottom);
                break;
            }
            case Pie_ELMT://扇形
            {
                DM_Pie *temp =  dynamic_cast<DM_Pie*>(element_);
                this->element = new DM_Pie(temp->center,temp->R,temp->startAngle,temp->endAngle);
                break;
            }
            case Sector_ELMT://扇环
            {
                DM_Sector *temp = dynamic_cast<DM_Sector*>(element_);
                this->element = new DM_Sector(temp->center, temp->innerRadius,temp->outerRadius, temp->startAngle, temp->endAngle);
                break;
            }
            default:
            {
                this->element = nullptr;
            }
        }
    }
    else
    {
        this->element = nullptr;
    }
    this->color = color_;
    this->penWidth = width_;
    this->penType = penType_;
    this->vectorFlag = vectorFlag_;
}

DM_LabelElement::DM_LabelElement(const DM_LabelElement &obj)
{
    if (obj.element != nullptr)
    {
        switch(obj.element->type)
        {
        case Point_ELMT://点
        {
            DM_Point *temp = dynamic_cast<DM_Point*>(obj.element);
            this->element = new DM_Point(temp->x, temp->y);
            break;
        }
        case Line_ELMT://直线
        {
            DM_Line *temp = dynamic_cast<DM_Line*>(obj.element);
            this->element = new DM_Line(temp->P1, temp->P2);
            break;
        }
        case Circle_ELMT://圆
        {
            DM_Circle *temp = dynamic_cast<DM_Circle*>(obj.element);
            this->element = new DM_Circle(temp->center, temp->radius);
            break;
        }
        case Ring_ELMT://圆
        {
            DM_Ring *temp = dynamic_cast<DM_Ring*>(obj.element);
            this->element = new DM_Ring(temp->center, temp->innerRadius, temp->outerRadius);
            break;
        }
        case Arc_ELMT://弧线
        {
            DM_Arc *temp = dynamic_cast<DM_Arc*>(obj.element);
            this->element = new DM_Arc(temp->startPoint, temp->midPoint, temp->endPoint);
            break;
        }
        case RotatedRect_ELMT://斜矩形
        {
            DM_RotatedRect *temp = dynamic_cast<DM_RotatedRect*>(obj.element);
            this->element = new DM_RotatedRect(temp->center, temp->size, temp->angle);
            break;
        }
        case Rect_ELMT://矩形
        {
            DM_Rect *temp = dynamic_cast<DM_Rect*>(obj.element);
            this->element = new DM_Rect(temp->leftTop, temp->rightBottom);
            break;
        }
        case Pie_ELMT://扇形
        {
            DM_Pie *temp = dynamic_cast<DM_Pie*>(obj.element);
            this->element = new DM_Pie(temp->center, temp->R, temp->startAngle, temp->endAngle);
            break;
        }
        case Sector_ELMT://扇环
        {
            DM_Sector *temp = dynamic_cast<DM_Sector*>(obj.element);
            this->element = new DM_Sector(temp->center, temp->innerRadius, temp->outerRadius, temp->startAngle, temp->endAngle);
            break;
        }
        default:
        {
            this->element = nullptr;
        }
        }
    }
    else
    {
        this->element = nullptr;
    }

    this->color = obj.color;
    this->penWidth = obj.penWidth;
    this->penType = obj.penType;
    this->vectorFlag = obj.vectorFlag;
}

DM_LabelElement DM_LabelElement::operator=(const DM_LabelElement &obj)
{
    if(this->element != nullptr)
    {
        delete this->element;
        this->element = nullptr;

    }
    if (obj.element != nullptr)
    {
        switch(obj.element->type)
        {
            case Point_ELMT://点
            {
                DM_Point *temp = dynamic_cast<DM_Point*>(obj.element);
                this->element = new DM_Point(temp->x, temp->y);
                break;
            }
            case Line_ELMT://直线
            {
                DM_Line *temp = dynamic_cast<DM_Line*>(obj.element);
                this->element = new DM_Line(temp->P1, temp->P2);
                break;
            }
            case Circle_ELMT://圆
            {
                DM_Circle *temp = dynamic_cast<DM_Circle*>(obj.element);
                this->element = new DM_Circle(temp->center, temp->radius);
                break;
            }
            case Ring_ELMT://圆
            {
                DM_Ring *temp = dynamic_cast<DM_Ring*>(obj.element);
                this->element = new DM_Ring(temp->center, temp->innerRadius, temp->outerRadius);
                break;
            }
            case Arc_ELMT://弧线
            {
                DM_Arc *temp = dynamic_cast<DM_Arc*>(obj.element);
                this->element = new DM_Arc(temp->startPoint, temp->midPoint, temp->endPoint);
                break;
            }
            case RotatedRect_ELMT://斜矩形
            {
                DM_RotatedRect *temp = dynamic_cast<DM_RotatedRect*>(obj.element);
                this->element = new DM_RotatedRect(temp->center, temp->size, temp->angle);
                break;
            }
            case Rect_ELMT://矩形
            {
                DM_Rect *temp = dynamic_cast<DM_Rect*>(obj.element);
                this->element = new DM_Rect(temp->leftTop, temp->rightBottom);
                break;
            }
            case Pie_ELMT://扇形
            {
                DM_Pie *temp = dynamic_cast<DM_Pie*>(obj.element);
                this->element = new DM_Pie(temp->center, temp->R, temp->startAngle, temp->endAngle);
                break;
            }
            case Sector_ELMT://扇环
            {
                DM_Sector *temp = dynamic_cast<DM_Sector*>(obj.element);
                this->element = new DM_Sector(temp->center, temp->innerRadius, temp->outerRadius, temp->startAngle, temp->endAngle);
                break;
            }
            default:
            {
                this->element = nullptr;
            }
        }
    }
    else
    {
        this->element = nullptr;
    }

    this->color = obj.color;
    this->penWidth = obj.penWidth;
    this->penType = obj.penType;
    this->vectorFlag = obj.vectorFlag;
    return *this;
}

DM_LabelElement::~DM_LabelElement()
{
    if(this->element != nullptr)
    {
        delete this->element;
        this->element = nullptr;
    }
}

DM_LabelText::DM_LabelText(QString text_, DM_Point pos_, QColor color_ /*= QColor(255, 0, 0)*/,
                           double wordSize_ /*= 15*/, double angle_ /*= 0*/)
{
    this->text = text_;//文字
    this->color = color_;//绘制元素
    this->wordSize = wordSize_;//线条宽度
    this->pos = pos_;//文字位置
    this->angle = angle_;//文字角度
}

DM_LabelText::DM_LabelText(const DM_LabelText &obj)
{
    this->text = obj.text;//文字
    this->color = obj.color;//绘制元素
    this->wordSize = obj.wordSize;//线条宽度
    this->pos =obj.pos;//文字位置
    this->angle = obj.angle;//文字角度
}

DM_LabelText DM_LabelText::operator=(const DM_LabelText &obj)
{
    this->text = obj.text;//文字
    this->color = obj.color;//绘制元素
    this->wordSize = obj.wordSize;//线条宽度
    this->pos = obj.pos;//文字位置
    this->angle = obj.angle;//文字角度

    return *this;
}
