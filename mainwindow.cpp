#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QTextCodec>
#include <QMatrix>
#include <QMessageBox>
#include <QWidget>
#include <QTabWidget>
#include <QDateTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置系统标题
    this->setWindowTitle(QStringLiteral("引导定位平台【成都迪迈沃克光电科技有限公司】"));

    //设定定位算法配置界面加载图片流设置
    ui->Projector->setButtons(ui->btn_ProjPlay, ui->btn_ProjFirst,ui->btn_ProjPrev, ui->btn_ProjNext, ui->btn_ProjFinal);
    ui->Projector->initProjector();
    connect(ui->Projector, &DM_Projector::triggerOnce, this, &MainWindow::loadImage_Projector);

    //初始化各个Label的位置
    ui->lab_calibrateImage->move(QPoint(0,0));
    ui->lab_calibrateImage->setScrollBar(ui->calibrateImageHBar,ui->calibrateImageVBar);
    ui->lab_algorithmnTemp->move(QPoint(0,0));
    ui->lab_algorithmImage->move(0,0);
    ui->lab_algorithmImage->setScrollBar(ui->algorithmImageHBar,ui->algorithmImageVBar);
    ui->lab_cameraVideo->move(0,0);
    ui->lab_cameraVideo->setScrollBar(ui->cameraVideoHBar,ui->cameraVideoVBar);

    //系统相关参数初始化：
    this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
    this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
    this->currentToolList = "";
    this->calibrateFlag = false;//未标定
    this->templateMassCenterFlag = true;//默认模板的抓取点为质心
    this->systemFunc = SystemFunction_Calibrate;//默认系统启动标定模式
    ui->SWidget_image->setCurrentWidget(ui->page_calibrateImage);//显示标定
    ui->TWidget_toolList->setCurrentItem(ui->TWidget_toolList->topLevelItem(1));//默认选中标定界面
    //系统启动工具栏不能调用，必须新建工程或者加载工程
    ui->TWidget_toolList->topLevelItem(0)->setFlags(Qt::NoItemFlags);
    ui->TWidget_toolList->topLevelItem(1)->setFlags(Qt::NoItemFlags);
    ui->TWidget_toolList->topLevelItem(2)->setFlags(Qt::NoItemFlags);
    ui->TWidget_toolList->topLevelItem(3)->setFlags(Qt::NoItemFlags);
    //系统初始化时，确认、执行、撤销三个按钮显示
    ui->btn_toolConfirm->setVisible(false);
    ui->btn_AlgorithmExcute->setVisible(false);
    ui->btn_AlgorithmRevocation->setVisible(false);

    //系统表格相关初始化
    this->initCalibrateCoordinateTable();
    this->initPreprocessAlgorithmTable();
    this->initAlgorithmCoordinateTable();
    this->initSystemCalibrateTable();

    //显示界面初始化
    //ui->calibratePlatePara->setCurrentWidget(ui->chessBoardPage);
    ui->lab_algorithmnTemp->setCenterCrossFlag(false);

    //ui->mainTab->setCurrentWidget(ui->tab_calibrate);
    //建立信号槽之间的关系
    connect(ui->lab_algorithmImage, &DM_Label::sendElement,this,&MainWindow::receiveLocationLabelElement);
    connect(ui->lab_calibrateImage, &DM_Label::sendElement,this,&MainWindow::receiveCalibrateElement);
    connect(ui->lab_cameraVideo,&DM_Label::sendPixelInformation,[=](QString pixelInformation){
        ui->cameraVideoInfo->setText(pixelInformation);
    });
    connect(ui->lab_calibrateImage,&DM_Label::sendPixelInformation,[=](QString pixelInformation){
        ui->calibrateImageInfo->setText(pixelInformation);
    });
    connect(ui->lab_algorithmImage,&DM_Label::sendPixelInformation,[=](QString pixelInformation){
        ui->algorithmImageInfo->setText(pixelInformation);
    });

    //设置系统参数
    this->projectDefaultFile = "../projectDefaultFile.dp";//先暂定保存到本地目录
    this->projectPath="./pro";//文件保存路径

    //通讯参数设置
    this->initCommunicationParameters();//初始化显示界面，后面根据实际便捷性在做调整，修成加载上次的配置文件
    //相机测试
    //this->initBaslerCameraParameters();//初始化相机连接

    //状态栏
    this->proStatus[0] = QStringLiteral("工程名：");//①工程名
    this->proStatus[1] = QStringLiteral("  ");//②工程名
    this->proStatus[2] = QStringLiteral("，标定状态：");//③，标定状态：
    this->proStatus[3] = QStringLiteral("未标定");//④，标定状态：
    ui->statusBar->showMessage(this->proStatus[0]+
            this->proStatus[1]+
            this->proStatus[2]+
            this->proStatus[3]);
}

MainWindow::~MainWindow()
{
    delete ui;
    while (!this->imgProcess.empty())
    {
        delete this->imgProcess.back();
        this->imgProcess.pop_back();
    }
    while(!this->imgCalibrate.empty())
    {
        delete this->imgCalibrate.back();
        this->imgCalibrate.pop_back();
    }
}

void MainWindow::initCalibrateCoordinateTable()
{
    ui->table_calibrateCoordinate->horizontalHeader()->setVisible(true); //隐藏行表头【表头不好合并】
    ui->table_calibrateCoordinate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_calibrateCoordinate->horizontalHeader()->setStyleSheet("QHeaderView::section{background: rgb(255, 255, 255);}");
    ui->table_calibrateCoordinate->horizontalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表头不可编辑
//    ui->table_calibrateCoordinate->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_calibrateCoordinate->setStyleSheet("background-color:rgb(200, 200, 200)");//设置背景色
    ui->table_calibrateCoordinate-> setAlternatingRowColors(true);//设置行颜色交叉显示

   //初始化表格
    for(int i = 0 ; i < ui->table_calibrateCoordinate->rowCount(); i++)
    {
        for(int j = 0; j < ui->table_calibrateCoordinate->columnCount(); j++)
        {
            ui->table_calibrateCoordinate->setItem(i, j, new QTableWidgetItem(""));
            ui->table_calibrateCoordinate->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_calibrateCoordinate->item(i, j)->setFlags(Qt::NoItemFlags);//第一列不允许修改
        }
        ui->table_calibrateCoordinate->setRowHeight(i,25);
    }
//    ui->table_calibrateCoordinate->setColumnCount(4);//设置表格列数
//    ui->table_calibrateCoordinate->setRowCount(11);//设置表格行
//    ui->table_calibrateCoordinate->setSpan(0,0,1,2);//合并第一行的0,1两列
//    ui->table_calibrateCoordinate->setSpan(0,2,1,2);//合并第一行的2,3两列
}

void MainWindow::initPreprocessAlgorithmTable()
{
    ui->table_preprocessAlgorithm->horizontalHeader()->setVisible(true); //隐藏行表头【表头不好合并】
    ui->table_preprocessAlgorithm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_preprocessAlgorithm->horizontalHeader()->setStyleSheet("QHeaderView::section{background: rgb(255,255,255);}");
    ui->table_preprocessAlgorithm->horizontalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表头不可编辑
//    ui->table_preprocessAlgorithm->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_preprocessAlgorithm->setStyleSheet("background-color:rgb(200,200,200)");//设置背景色
    ui->table_preprocessAlgorithm-> setAlternatingRowColors(true);//设置行颜色交叉显示

   //初始化表格
    for(int i = 0 ; i < ui->table_preprocessAlgorithm->rowCount(); i++)
    {
        for(int j = 0; j < ui->table_preprocessAlgorithm->columnCount(); j++)
        {
            ui->table_preprocessAlgorithm->setItem(i, j, new QTableWidgetItem(""));
            ui->table_preprocessAlgorithm->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_preprocessAlgorithm->item(i, j)->setFlags(Qt::NoItemFlags);
        }
        ui->table_preprocessAlgorithm->setRowHeight(i,25);
    }
}

void MainWindow::initSystemCalibrateTable()
{
    ui->table_systemCalibrate->horizontalHeader()->setVisible(true); //隐藏行表头【表头不好合并】
    ui->table_systemCalibrate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_systemCalibrate->horizontalHeader()->setStyleSheet("QHeaderView::section{background: rgb(255,255,255);}");
    ui->table_systemCalibrate->horizontalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表头不可编辑
//    ui->table_systemCalibrate->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_systemCalibrate->setStyleSheet("background-color:rgb(200,200,200)");//设置背景色
    ui->table_systemCalibrate->setAlternatingRowColors(true);//设置行颜色交叉显示
    ui->table_systemCalibrate->verticalHeader()->setDefaultSectionSize(200);//

   //初始化表格
    for(int i = 0 ; i < ui->table_systemCalibrate->rowCount(); i++)
    {
        for(int j = 0; j < ui->table_systemCalibrate->columnCount(); j++)
        {
            ui->table_systemCalibrate->setItem(i, j, new QTableWidgetItem(""));
            ui->table_systemCalibrate->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_systemCalibrate->item(i, j)->setFlags(Qt::NoItemFlags);
        }
        ui->table_systemCalibrate->setRowHeight(i,25);
    }
}

void MainWindow::initAlgorithmCoordinateTable()
{
    ui->table_algorithmCoordinate->horizontalHeader()->setVisible(true); //隐藏行表头【表头不好合并】
    ui->table_algorithmCoordinate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_algorithmCoordinate->horizontalHeader()->setStyleSheet("QHeaderView::section{background: rgb(255,255,255);}");
    ui->table_algorithmCoordinate->horizontalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表头不可编辑
//    ui->table_algorithmCoordinate->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应表头
    ui->table_algorithmCoordinate->setStyleSheet("background-color:rgb(200,200,200)");//设置背景色
    ui->table_algorithmCoordinate->setAlternatingRowColors(true);//设置行颜色交叉显示

   //初始化表格
    for(int i = 0 ; i < ui->table_algorithmCoordinate->rowCount(); i++)
    {
        for(int j = 0; j < ui->table_algorithmCoordinate->columnCount(); j++)
        {
            ui->table_algorithmCoordinate->setItem(i, j, new QTableWidgetItem(""));
            ui->table_algorithmCoordinate->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_algorithmCoordinate->item(i, j)->setFlags(Qt::NoItemFlags);
        }
        ui->table_algorithmCoordinate->setRowHeight(i,25);
    }
}

//执行图像处理算法
void MainWindow::excuteImageProcess()
{
    if(!this->imgProcess.empty())
    {
        if (this->locationImg.empty())
        {
            this->message += QStringLiteral("#>>>无图像,请先加载\n");
        }
        else if (!this->locationImg.empty())
        {
            this->locationImg_original.copyTo(this->locationImg);
            this->locationImg_original.copyTo(this->locationImg_show);

            for(int i = 0; i < this->imgProcess.size(); i++)
            {
                //如果当前算法为查找质心，那么上一次算法肯定为查找轮廓
                if (this->imgProcess.size()>1&&
                    this->imgProcess[i]->getImgProcessMethod() == DM_MOMENTS_Tag&&
                    this->imgProcess[i-1]->getImgProcessMethod() == DM_CONTOURS_Tag)
                {
                    std::vector<std::vector<cv::Point>> contours_ = (dynamic_cast<DM_FindContours*>(this->imgProcess[i - 1]))->contours;
                    (dynamic_cast<DM_Moment*>(this->imgProcess[i]))->setContours(contours_);
                }

                //如果当前算法为查找质心，那么上一次算法肯定为查找轮廓
                if (this->imgProcess.size()>1&&
                    this->imgProcess[i]->getImgProcessMethod() == DM_CONTOURSMATCH_Tag&&
                    this->imgProcess[i-1]->getImgProcessMethod() == DM_CONTOURS_Tag)
                {
                    std::vector<std::vector<cv::Point>> contours_ = (dynamic_cast<DM_FindContours*>(this->imgProcess[i - 1]))->contours;
                    (dynamic_cast<DM_ContoursMatch*>(this->imgProcess[i]))->setTrianContours(contours_);
                }
                //如果当前算法为坐标系统转换，则前一套算法必然已经计算除了关键点,目前关键支持质心
                if(this->imgProcess.size()> 1&&
                        this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                        this->imgProcess[i - 1]->getImgProcessMethod() == DM_MOMENTS_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_Moment*>(this->imgProcess[i - 1]))->getCenterOfMass();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }
                else if (this->imgProcess.size() > 1 &&
                    this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                    this->imgProcess[i - 1]->getImgProcessMethod() == DM_CONTOURS_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_FindContours*>(this->imgProcess[i - 1]))->getCenterOfMass();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }
                else if(this->imgProcess.size()> 1&&
                        this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                        this->imgProcess[i - 1]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_ChessBoardCalibration*>(this->imgProcess[i - 1]))->getFeaturetPoints();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }
                else if(this->imgProcess.size()> 1&&
                        this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                        this->imgProcess[i - 1]->getImgProcessMethod() == DM_HOUGHCIRCLE_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_HoughCircle*>(this->imgProcess[i - 1]))->getCircleCenters();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }
                else if (this->imgProcess.size() > 1 &&
                    this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                    this->imgProcess[i - 1]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_FindCircle*>(this->imgProcess[i - 1]))->getCircleCenters();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }
                else if (this->imgProcess.size() > 1 &&
                    this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                    this->imgProcess[i - 1]->getImgProcessMethod() == DM_MATCHTEMPLATE_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_MatchTemplate*>(this->imgProcess[i - 1]))->getGrabPoints();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }
                else if (this->imgProcess.size() > 1 &&
                    this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                    this->imgProcess[i - 1]->getImgProcessMethod() == DM_FEATUREMATCH_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_FeatureMatch_SIFT*>(this->imgProcess[i - 1]))->getGrabPoints();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }
                else if (this->imgProcess.size() > 1 &&
                    this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                    this->imgProcess[i - 1]->getImgProcessMethod() == DM_CONTOURSMATCH_Tag)
                {
                    std::vector<cv::Point2f> points = (dynamic_cast<DM_ContoursMatch*>(this->imgProcess[i - 1]))->getGrabPoints();
                    (dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[i]))->setOriginalPoints(points);
                }

                this->imgProcess[i]->process(this->locationImg);
                ui->lab_algorithmImage->setTexts(this->imgProcess[i]->getLabelText());
                this->message +=  QString::fromLocal8Bit(this->imgProcess[i]->getMessage().data());
                if(this->imgProcess[i]->getErrorID() == DM_error_no)
                {
                    this->locationImg = this->imgProcess[i]->getProcessedImage();
                    if(this->imgProcess[i]->getImgProcessMethod() != DM_COORDINATE_Tag)
                        this->locationImg_show = this->imgProcess[i]->getProcessedColorImage();
                }
                else//一步出错，后续就不进行了。
                {
                    break;
                }
            }
        }
    }
    else
    {
        ui->lab_algorithmImage->clearTexts();
        this->locationImg_original.copyTo(this->locationImg);
        this->locationImg_original.copyTo(this->locationImg_show);
    }
    this->updateAlgorithmCoordinateTable();
    this->updatePreprocessAlgorithmTable();
    this->sendPosByModbus(); //将转换结果传出

    ui->lab_algorithmImage->loadImage(this->locationImg_show);
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::addImgProcess(DM_ImageProcessBase *func)
{
    if(this->calibrateFlag)//index = 0:为标定
    {
        this->imgProcess.push_back(func);
        this->excuteImageProcess();
        if(this->imgProcess[this->imgProcess.size()-1]->getErrorID() != DM_error_no)//算法计算失败，执行算法不成功，撤销该操作
        {
            this->deleteImgProcess();
        }
    }
    else
    {
        this->message += QStringLiteral("#>>>请先标定\n");
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::deleteImgProcess(int index)
{
    if(this->imgProcess.size()>0)
    {
        if(index < this->imgProcess.size() && index >= 0)
        {
            std::vector<DM_ImageProcessBase*>::iterator iter = this->imgProcess.begin()+index;//释放该迭代器对应的那个指针指向的内存
            delete *iter;
            this->imgProcess.erase(this->imgProcess.begin()+index);
            this->updatePreprocessAlgorithmTable();
            this->message += QStringLiteral("#>>>删除指定算法成功\n");
        }
        else if (index = -1)
        {
            delete this->imgProcess.back();
            this->imgProcess.pop_back();
            this->updatePreprocessAlgorithmTable();
            this->message += QStringLiteral("#>>>撤销算法成功\n");
        }
        else
        {
            this->message += QStringLiteral("#>>>请输入正确的算法小标，才能进行删除\n");
        }
        this->excuteImageProcess();

    }
    else
    {
        this->message += QStringLiteral("#>>>算法为空\n");
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    //ui->statusBar_location->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
   // ui->statusBar_location->moveCursor(QTextCursor::End);
}
void MainWindow::clearImgProcess()
{
    while(!this->imgProcess.empty())
    {
        delete this->imgProcess.back();
        this->imgProcess.pop_back();
    }
    this->updatePreprocessAlgorithmTable();
    this->excuteImageProcess();
    this->message += QStringLiteral("#>>>清除算法成功\n");
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::updateCalibrateCoordinateTable()
{
	this->initCalibrateCoordinateTable();//先初始化，在更新表格
    if (this->calibrateFlag)
    {
        DM_HandEyeCalibration *func = dynamic_cast<DM_HandEyeCalibration*>(this->imgCalibrate[this->imgCalibrate.size()-1]);

        std::vector<cv::Point2f> cameraPoints = func->cameraPoints;//相机计算出来的9个点的坐标
        std::vector<cv::Point2f> robotPoints = func->robotPoints;//机器人的9点坐标
        int num = cameraPoints.size() <= robotPoints.size()? cameraPoints.size() : robotPoints.size();
        ui->table_calibrateCoordinate->setRowCount(num);
        for (int i = 0; i < num; i++)
        {
            QString cameraStr = QString::number(cameraPoints[i].x) + " , " + QString::number(cameraPoints[i].y);

            ui->table_calibrateCoordinate->setItem(i, 0, new QTableWidgetItem(cameraStr));
            ui->table_calibrateCoordinate->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
            ui->table_calibrateCoordinate->item(i, 0)->setFlags(Qt::NoItemFlags);

            QString robotStr = QString::number(robotPoints[i].x) + " , " + QString::number(robotPoints[i].y);
            ui->table_calibrateCoordinate->setItem(i, 1, new QTableWidgetItem(robotStr));
            ui->table_calibrateCoordinate->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
        }
    }
    else
    {

		std::vector<cv::Point2f> featurePoints;
		QString calibrateType = "";//标定类型选择
		QString calibrateStatus = "";//算法状态
		int algorithmNum = 0;
		for (int i = 0; i < this->imgCalibrate.size(); i++)
		{
			if (this->imgCalibrate[i]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)//方形棋盘格
			{
				featurePoints = dynamic_cast<DM_ChessBoardCalibration*>(this->imgCalibrate[0])->getFeaturetPoints();
			}
			else if (this->imgCalibrate[i]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)//圆形棋盘格
			{
				featurePoints = dynamic_cast<DM_FindCircle*>(this->imgCalibrate[0])->getCircleCenters();
			}
			else if (this->imgCalibrate[i]->getImgProcessMethod() == DM_FINDCIRCLE_HAND_Tag)//框选（圆）
			{
				featurePoints.push_back(dynamic_cast<DM_FindCircle_Hand*>(this->imgCalibrate[i])->getCircleCenter());
			}
		}
		//将特征点的结果显示到表格中
		for (int i = 0; i < ui->table_calibrateCoordinate->rowCount() && i < featurePoints.size(); i++)
		{
			QString str = QString::number(featurePoints[i].x) + " , " +
				QString::number(featurePoints[i].y);

			ui->table_calibrateCoordinate->setItem(i, 0, new QTableWidgetItem(str));
			ui->table_calibrateCoordinate->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
			ui->table_calibrateCoordinate->item(i, 0)->setFlags(Qt::NoItemFlags);

			if (ui->btn_modbusclose_R->isChecked())
			{
				ui->table_calibrateCoordinate->setItem(i, 1, new QTableWidgetItem(""));
				ui->table_calibrateCoordinate->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
			}
		}	
        
    }
}

void MainWindow::updatePreprocessAlgorithmTable()
{
    if(this->imgProcess.size() >= 1)
    {
        size_t count  = this->imgProcess.size();
        int tableRows = count > 1 ? count : 1;
        ui->table_preprocessAlgorithm->setRowCount(tableRows);
        for(int i = 0; i <  this->imgProcess.size(); i++)
        {
            if(this->imgProcess[i]->getImgProcessMethod() == DM_THRESHOLD_GENERAL_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("常规二值化")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_THRESHOLD_GENERAL_INV_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("常规_反向二值化")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_THRESHOLD_OTSU_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("OTSU二值化")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_THRESHOLD_ADAPTIVE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("自适应分块二值化")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MEANBLUR_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("均值滤波")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_GAUSSIANBLUR_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("高斯滤波")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MEDIANDMFILTER_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("中值滤波")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_BILATERALFILTER_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("双边滤波")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MORPHOLOGY_DILATE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像膨胀")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MORPHOLOGY_ERODE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像腐蚀")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MORPHOLOGY_OPEN_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像开操作")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MORPHOLOGY_CLOSE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像闭操作")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MORPHOLOGY_GRADIENT_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像形态学梯度")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MORPHOLOGY_TOPHAT_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像顶帽")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MORPHOLOGY_BLACKHAT_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像黑帽")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_CONTOURS_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("查找轮廓")));
            }
            else if(this->imgProcess[i]->getImgProcessMethod() == DM_MOMENTS_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像的矩_计算质心")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_COORDINATE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("相机坐标系->机器臂坐标系")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_HOUGHCIRCLE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("霍夫圆")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("通用圆")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("方形棋盘格特征点")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_MATCHTEMPLATE_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("模板匹配")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_FEATUREMATCH_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("特征点匹配")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_CONTOURSMATCH_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("轮廓匹配")));
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_IMGNOT_Tag)
            {
                ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(QStringLiteral("图像取反")));
            }

            ui->table_preprocessAlgorithm->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_preprocessAlgorithm->item(i, 0)->setFlags(Qt::NoItemFlags);
        }
        //初始化表格
        for (int i = this->imgProcess.size(); i < ui->table_preprocessAlgorithm->rowCount(); i++)
        {
            ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(" "));
            ui->table_preprocessAlgorithm->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
            ui->table_preprocessAlgorithm->item(i, 0)->setFlags(Qt::NoItemFlags);
        }
    }
    else
    {
        //初始化表格
         for(int i = 0 ; i < ui->table_preprocessAlgorithm->rowCount(); i++)
         {
             ui->table_preprocessAlgorithm->setItem(i, 0, new QTableWidgetItem(" "));
             ui->table_preprocessAlgorithm->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
             ui->table_preprocessAlgorithm->item(i, 0)->setFlags(Qt::NoItemFlags);
         }
    }
}

void MainWindow::deleteImgCalibrateAlgorithm(int index /*= -1*/)
{
	if (this->imgCalibrate.size() > 0)
	{
		if (index < this->imgCalibrate.size() && index >= 0)
		{
			std::vector<DM_ImageProcessBase*>::iterator iter = this->imgCalibrate.begin() + index;//释放该迭代器对应的那个指针指向的内存
			delete *iter;
			this->imgCalibrate.erase(this->imgCalibrate.begin() + index);
			
			
			this->message += QStringLiteral("#>>>删除指定算法成功\n");
		}
		else if (index = -1)
		{
			delete this->imgCalibrate.back();
			this->imgCalibrate.pop_back();
			
			this->message += QStringLiteral("#>>>撤销算法成功\n");
		}
		else
		{
			this->message += QStringLiteral("#>>>请输入正确的算法小标，才能进行删除\n");
		}
		this->updateCalibrateCoordinateTable();
		this->updateSystemCalibrateTable();
		this->updateLab_calibrateImage();

	}
	else
	{
		this->message += QStringLiteral("#>>>标定算法为空\n");
	}
	ui->systemStatusBar->setText(this->message);//显示运行状态
	ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::clearImgCalibrateAlgorithm()
{
	while (!this->imgCalibrate.empty())
	{
		delete this->imgCalibrate.back();
		this->imgCalibrate.pop_back();
	}
	this->initCalibrateCoordinateTable();//初始化标定值列表格式
	this->initAlgorithmCoordinateTable();//初始化定位列表格式

	this->message += QStringLiteral("#>>>清除算法成功\n");
	ui->systemStatusBar->setText(this->message);//显示运行状态
	ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::updateSystemCalibrateTable()
{
	this->initSystemCalibrateTable();//先初始化表格，在更新内容

	QString calibrateType = "";//标定类型选择
	QString calibrateStatus = "";//算法状态
	for (int i = 0; i < this->imgCalibrate.size() && i <  ui->table_systemCalibrate->rowCount(); i++)
	{
		if (this->imgCalibrate[i]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)//方形棋盘格
		{
			calibrateType = QStringLiteral("方形棋盘格_标定");
			calibrateStatus = QStringLiteral("计算成功");//算法状态
		}
		else if (this->imgCalibrate[i]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)//圆形棋盘格
		{
			calibrateType = QStringLiteral("圆形棋盘格_标定");
			calibrateStatus = QStringLiteral("计算成功");//算法状态
		}
		else if (this->imgCalibrate[i]->getImgProcessMethod() == DM_FINDCIRCLE_HAND_Tag)//框选（圆）
		{
			calibrateType = QStringLiteral("框选圆_标定");
			calibrateStatus = QStringLiteral("计算成功");//算法状态
		}
		else if (this->imgCalibrate[i]->getImgProcessMethod() == DM_COORDINATE_Tag)//标定坐标转化
		{
			calibrateType = QStringLiteral("坐标转换");
			calibrateStatus = QStringLiteral("转化完成");//算法状态
		}
		//更新标定状态表
		ui->table_systemCalibrate->setItem(i, 0, new QTableWidgetItem(calibrateType));
		ui->table_systemCalibrate->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
		ui->table_systemCalibrate->item(i, 0)->setFlags(Qt::NoItemFlags);

		ui->table_systemCalibrate->setItem(i, 1, new QTableWidgetItem(calibrateStatus));
		ui->table_systemCalibrate->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
		ui->table_systemCalibrate->item(i, 1)->setFlags(Qt::NoItemFlags);
	}
}

void MainWindow::updateLab_calibrateImage()
{
	ui->lab_calibrateImage->clearElements();
	ui->lab_calibrateImage->clearTexts();

	for (int i = 0; i < this->imgCalibrate.size() && i < ui->table_systemCalibrate->rowCount(); i++)
	{
		if (this->imgCalibrate[i]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)//方形棋盘格
		{
			std::vector<DM_LabelText> labelTexts = dynamic_cast<DM_ChessBoardCalibration*>(this->imgCalibrate[i])->getLabelText();
			std::vector<cv::Point2f> labelFeaturetPoints = dynamic_cast<DM_ChessBoardCalibration*>(this->imgCalibrate[i])->getFeaturetPoints();
			for (int i = 0; i < labelTexts.size() && i < labelFeaturetPoints.size(); i++)
			{
				DM_Point *labelFeaturetPoint_ = new DM_Point(labelFeaturetPoints[i]);
				ui->lab_calibrateImage->addElements(DM_LabelElement(labelFeaturetPoint_));
				delete labelFeaturetPoint_;

				ui->lab_calibrateImage->addTexts(labelTexts[i]);
			}
		}
		else if (this->imgCalibrate[i]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)//圆形棋盘格
		{
			std::vector<DM_LabelText> labelTexts = dynamic_cast<DM_FindCircle*>(this->imgCalibrate[i])->getLabelText();
			std::vector<DM_Circle> labelCircles = dynamic_cast<DM_FindCircle*>(this->imgCalibrate[i])->getCitcles();
			std::vector<cv::Point2f> labelCircleCenters = dynamic_cast<DM_FindCircle*>(this->imgCalibrate[i])->getCircleCenters();
			for (int i = 0;  i < labelTexts.size() && i < labelCircles.size() && i < labelCircleCenters.size(); i++)
			{
				DM_Circle *calibrateCircle_ = new DM_Circle(labelCircles[i]);
				ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateCircle_, false, QColor(0, 255, 0)));
				delete calibrateCircle_;

				DM_Point *calibrateCenterP_ = new DM_Point(labelCircleCenters[i]);
				ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateCenterP_));
				delete calibrateCenterP_;

				ui->lab_calibrateImage->addTexts(labelTexts[i]);
			}
		}
		else if (this->imgCalibrate[i]->getImgProcessMethod() == DM_FINDCIRCLE_HAND_Tag)//框选（圆）
		{
			//更新显示
			DM_Ring *calibrateROI_ = new DM_Ring(dynamic_cast<DM_FindCircle_Hand*>(this->imgCalibrate[i])->circleROI);
			ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateROI_, false, QColor(0, 255, 255)));
			delete calibrateROI_;

			DM_Circle *calibrateCircle_ = new DM_Circle(dynamic_cast<DM_FindCircle_Hand*>(this->imgCalibrate[i])->circle);
			ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateCircle_, false, QColor(0, 255, 0)));
			delete calibrateCircle_;

			DM_Point *calibrateCenterP_ = new DM_Point(dynamic_cast<DM_FindCircle_Hand*>(this->imgCalibrate[i])->circle.center);
			ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateCenterP_));
			delete calibrateCenterP_;

			DM_LabelText labelText_(QString::number(i+1),
				dynamic_cast<DM_FindCircle_Hand*>(this->imgCalibrate[i])->getCircle().center);//更新显示
			ui->lab_calibrateImage->addTexts(labelText_);
		}
	}
	ui->lab_calibrateImage->update();//更新显示
}

void MainWindow::updateAlgorithmCoordinateTable()
{
    if (this->imgProcess.size() >= 1 &&
        this->imgProcess[this->imgProcess.size() -1]->getImgProcessMethod() == DM_COORDINATE_Tag)
    {
        DM_CoordinateTransform *func = dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[this->imgProcess.size() - 1]);
        std::vector<cv::Point2f> originalPoints = func->getOriginalPoints();
        std::vector<cv::Point2f> objectPoints = func->getObjectPoints();

        //设置表格的行数
        int tableRows = originalPoints.size() > 9 ? originalPoints.size() : 9;
        ui->table_algorithmCoordinate->setRowCount(tableRows);
        int index = 0;
        for (; index < originalPoints.size()&& index < objectPoints.size(); index++)
        {
            QString originalStr = QString::number(originalPoints[index].x) + " , " +
                          QString::number(originalPoints[index].y);
            ui->table_algorithmCoordinate->setItem(index, 0, new QTableWidgetItem(originalStr));
            ui->table_algorithmCoordinate->item(index, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
            ui->table_algorithmCoordinate->item(index, 0)->setFlags(Qt::NoItemFlags);

            QString objectStr = QString::number(objectPoints[index].x) + " , " +
                                QString::number(objectPoints[index].y);
            ui->table_algorithmCoordinate->setItem(index, 1, new QTableWidgetItem(objectStr));
            ui->table_algorithmCoordinate->item(index, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
            ui->table_algorithmCoordinate->item(index, 1)->setFlags(Qt::NoItemFlags);

        }
        //为填充的行全部用"***"补全
        for (int i = index; i < ui->table_algorithmCoordinate->rowCount(); i++)
        {
            for (int j = 0; j < ui->table_algorithmCoordinate->columnCount(); j++)
            {
                ui->table_algorithmCoordinate->setItem(i, j, new QTableWidgetItem(""));
                ui->table_algorithmCoordinate->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
                ui->table_algorithmCoordinate->item(i, j)->setFlags(Qt::NoItemFlags);
            }
        }
    }
    else
    {
        //初始化表格
        for (int i = 0; i < ui->table_algorithmCoordinate->rowCount(); i++)
        {
            for (int j = 0; j < ui->table_algorithmCoordinate->columnCount(); j++)
            {
                ui->table_algorithmCoordinate->setItem(i, j, new QTableWidgetItem("***, ***"));
                ui->table_algorithmCoordinate->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
                ui->table_algorithmCoordinate->item(i, j)->setFlags(Qt::NoItemFlags);
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    ui->lab_calibrateImage->resize(ui->widget_calibrateLabel->size());
    ui->lab_algorithmnTemp->resize(ui->widget_algorithmnTemp->size());
    ui->lab_algorithmImage->resize(ui->widget_algorithmImage->size());
    //qDebug()<<"cameraImageWidget:" << ui->cameraImageWidget->size()<< "  lab_algorithmnImage:"<<ui->lab_algorithmnImage->size();
    ui->lab_cameraVideo->resize(ui->widget_cameraVideo->size());
    QMainWindow::paintEvent(ev);
}

//当算法列表改变时候，切换算法参数列表
void MainWindow::on_TWidget_toolList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    ui->lab_algorithmImage->setElementIndex(Default_DM);
//    ui->lab_algorithmImage->setElementType(true);
    ui->lab_calibrateImage->setElementIndex(Default_DM);
//    ui->lab_algorithmImage->setElementType(true);
    //切换图像显示界面和坐标列表
    this->currentToolList = current->text(0);//获取工具列表
    if(current->text(0) == QStringLiteral("相机"))
    {
        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
        ui->SWidget_image->setCurrentWidget(ui->page_cameraVideo);//显示相机界面
        //ui->SWidget_coordinate->setCurrentWidget(ui->page_calibrateCoordinate);//切换坐标列表
        this->systemFunc = SystemFunction_camera;//进入相机设置
    }
    else if(current->text(0) == QStringLiteral("标定")||
            current->text(0) == QStringLiteral("①标定板")||
            current->text(0) == QStringLiteral("方形棋盘格")||
            current->text(0) == QStringLiteral("圆形棋盘格")||
            current->text(0) == QStringLiteral("圆(框选)")||
            current->text(0) == QStringLiteral("②映射矩阵"))
    {
        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
        ui->SWidget_image->setCurrentWidget(ui->page_calibrateImage);//显示算法界面
        ui->SWidget_coordinate->setCurrentWidget(ui->page_calibrateCoordinate);//切换标定坐标列表
        ui->SWidget_table->setCurrentWidget(ui->page_calibrate);
        this->systemFunc = SystemFunction_Calibrate;//默认系统启动标定模式
    }
    else if(current->text(0) == QStringLiteral("通信"))
    {
        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
        this->systemFunc = SystemFunction_communication;//进入通讯设置
    }
    else
    {
        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
        ui->btn_AlgorithmRevocation->setVisible(true);//显示撤销功能
        ui->SWidget_image->setCurrentWidget(ui->page_algorithmImage);//显示算法界面
        ui->SWidget_coordinate->setCurrentWidget(ui->page_algorithmCoordinate);//切换坐标列表
        ui->SWidget_table->setCurrentWidget(ui->page_algorithm);
        this->systemFunc = SystemFunction_Algorithm;//进入通讯设置
    }

    //一旦点击工具列表都是将界面切换到参数说明界面
    ui->SWidget_information->setCurrentWidget(ui->page_paraInformation);
    //切换参数说明界面
    if(current->text(0) == QStringLiteral("相机"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->cameraInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
    }
    else if(current->text(0) == QStringLiteral("标定"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->calibrationInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
    }
    else if(current->text(0) == QStringLiteral("①标定板"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui-> calibrate_calibrationPlateInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
    }
    else if(current->text(0) == QStringLiteral("方形棋盘格"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->chessbordInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_FEATUREMATCH_Tag;
    }
    else if(current->text(0) == QStringLiteral("圆形棋盘格"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->calibrate_dotPlateInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_FINDCIRCLE_Tag;
    }
    else if(current->text(0) == QStringLiteral("圆(框选)"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->calibrate_findCirclehandInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_FINDCIRCLE_HAND_Tag;
    }
    else if(current->text(0) == QStringLiteral("②映射矩阵"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->calibrate_mappingMatrixInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_FINDCIRCLE_Tag;
    }

    //选择算法
    else if(current->text(0) == QStringLiteral("算法"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->algorithmInfo);
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
    }
     else if(current->text(0) == QStringLiteral("图像取反"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->imgNotInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_IMGNOT_Tag;
     }
     else if(current->text(0) == QStringLiteral("常规二值化"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->threasholdInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_GENERAL_Tag;
     }
     else if(current->text(0) == QStringLiteral("常规_反向二值化"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->threasholdInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_GENERAL_INV_Tag;
     }
     else if(current->text(0) == QStringLiteral("OTSU"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->threasholdInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_OTSU_Tag;
     }
     else if(current->text(0) == QStringLiteral("分块二值化"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->zoningThreasholdInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_ADAPTIVE_Tag;
     }
     else if(current->text(0) ==  QStringLiteral("均值滤波"))
     {
         ui->SWidget_paraInformation->setCurrentWidget(ui->blurInfo);
         this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
         this->imgAlgorithmType = DM_MEANBLUR_Tag;
         ui->blurKernelH->setEnabled(true);
         ui->blurKernelW->setEnabled(true);
         ui->blur_sigmaColor->setEnabled(false);
         ui->blur_sigmaSpace->setEnabled(false);
     }
     else if(current->text(0) ==  QStringLiteral("高斯滤波"))
     {
         ui->SWidget_paraInformation->setCurrentWidget(ui->blurInfo);
         this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
         this->imgAlgorithmType = DM_GAUSSIANBLUR_Tag;
         ui->blurKernelH->setEnabled(true);
         ui->blurKernelW->setEnabled(true);
         ui->blur_sigmaColor->setEnabled(false);
         ui->blur_sigmaSpace->setEnabled(false);
     }
     else if(current->text(0) ==  QStringLiteral("中值滤波"))
     {
         ui->SWidget_paraInformation->setCurrentWidget(ui->blurInfo);
         this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

         this->imgAlgorithmType = DM_MEDIANDMFILTER_Tag;
         ui->blurKernelH->setEnabled(true);
         ui->blurKernelW->setEnabled(true);
         ui->blur_sigmaColor->setEnabled(false);
         ui->blur_sigmaSpace->setEnabled(false);
     }
     else if(current->text(0) ==  QStringLiteral("双边滤波"))
     {
         ui->SWidget_paraInformation->setCurrentWidget(ui->blurInfo);
         this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

         this->imgAlgorithmType = DM_BILATERALFILTER_Tag;
         ui->blurKernelH->setEnabled(false);
         ui->blurKernelW->setEnabled(false);
         ui->blur_sigmaColor->setEnabled(true);
         ui->blur_sigmaSpace->setEnabled(true);
     }
     else if(current->text(0) == QStringLiteral("膨胀"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->morphologyInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MORPHOLOGY_DILATE_Tag;
     }
     else if(current->text(0) == QStringLiteral("腐蚀"))
     {
         ui->SWidget_paraInformation->setCurrentWidget(ui->morphologyInfo);
         this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

         this->imgAlgorithmType = DM_MORPHOLOGY_ERODE_Tag;
     }
     else if(current->text(0) == QStringLiteral("开"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->morphologyInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MORPHOLOGY_OPEN_Tag;
     }
     else if(current->text(0) == QStringLiteral("闭"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->morphologyInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MORPHOLOGY_CLOSE_Tag;
     }
     else if(current->text(0) == QStringLiteral("形态学梯度"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->morphologyInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MORPHOLOGY_GRADIENT_Tag;
     }
     else if(current->text(0) == QStringLiteral("顶帽"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->morphologyInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MORPHOLOGY_TOPHAT_Tag;
     }
     else if(current->text(0) == QStringLiteral("黑帽"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->morphologyInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MORPHOLOGY_BLACKHAT_Tag;
     }
    else if(current->text(0) == QStringLiteral("查找轮廓"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->contourInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_CONTOURS_Tag;
    }
    else if(current->text(0) == QStringLiteral("质心"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->momentInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MOMENTS_Tag;
    }
    else if(current->text(0) == QStringLiteral("查找霍夫圆")||
    current->text(0) == QStringLiteral("计算霍夫圆心"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->houghInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_HOUGHCIRCLE_Tag;
    }
    else if (current->text(0) == QStringLiteral("查找圆"))
     {
        ui->SWidget_paraInformation->setCurrentWidget(ui->findCircleInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_FINDCIRCLE_Tag;
     }
    else if(current->text(0) == QStringLiteral("方形棋盘格特征点"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->chessbordInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_CHESSBOARDCALIBRATION_Tag;
    }
    else if(current->text(0) == QStringLiteral("模板匹配"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->tempmatchInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_MATCHTEMPLATE_Tag;
        ui->similarityCoefficient->setEnabled(true);
    }
    else if(current->text(0) == QStringLiteral("轮廓匹配"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->tempmatchInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_CONTOURSMATCH_Tag;
        ui->similarityCoefficient->setEnabled(true);
    }
    else if(current->text(0) == QStringLiteral("特征点匹配"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->tempmatchInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_FEATUREMATCH_Tag;
        ui->similarityCoefficient->setEnabled(false);
    }
    else if(current->text(0) == QStringLiteral("相机坐标系->机器臂坐标系"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->defalutInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;

        this->imgAlgorithmType = DM_COORDINATE_Tag;
    }
    else if(current->text(0) == QStringLiteral("通信"))
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->modbusInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
    }
    else
    {
        ui->SWidget_paraInformation->setCurrentWidget(ui->defalutInfo);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
    }
}

//从文件夹中加载文件
void MainWindow::loadImage()
{

    if(ui->SWidget_image->currentWidget()->objectName() == ui->page_calibrateImage->objectName())
    {
        QString filesName = QFileDialog::getOpenFileName(this, QStringLiteral("加载图片"),QString(), QStringLiteral("图片类型(*PNG *jpg *BMP)"));
        if (filesName == "")
        {
            this->message = QStringLiteral("#>>>加载路径不正确\n");
        }
        else
        {
            cv::Mat img_= cv::imread(std::string(filesName.toLocal8Bit()),cv::IMREAD_GRAYSCALE);//加载图片
            if(img_.empty())
            {
                this->message = QStringLiteral("#>>>加载图片失败，请重新加载\n");;
            }
            else
            {
                this->message = QStringLiteral("#>>>标定图片加载成功\n");
                ui->lab_calibrateImage->loadImage(img_);
                ui->lab_calibrateImage->toFitScreen();
                img_.copyTo(this->calibrateImg);
                this->calibrateFlag = false;//重新加载图片，请重新标定
                this->initCalibrateCoordinateTable();
                this->initSystemCalibrateTable();//初始化标定列表
                ui->lab_calibrateImage->clearTexts();
				ui->lab_calibrateImage->clearElements();
				this->clearImgCalibrateAlgorithm();

                this->proStatus[3] = QStringLiteral("未标定");//②工程名
                ui->statusBar->showMessage(this->proStatus[0]+
                        this->proStatus[1]+
                        this->proStatus[2]+
                        this->proStatus[3]);
            }
        }
    }
    else if (ui->SWidget_image->currentWidget()->objectName() == ui->page_algorithmImage->objectName())
    {
        QString imgPath = QFileDialog::getExistingDirectory(this, "choose src Directory","/");
        qDebug()<<imgPath;
        ui->Projector->setFolderPath(QDir(imgPath));
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);

}

void MainWindow::loadImage_Projector(const QString &filePath)
{
    qDebug()<<"imgpath:"<<filePath;
    cv::Mat img_ = cv::imread(filePath.toStdString(),cv::IMREAD_GRAYSCALE);
    this->message = QStringLiteral("#>>>定位图片加载成功\n");
    img_.copyTo(this->locationImg_original);
    img_.copyTo(this->locationImg_show);
    img_.copyTo(this->locationImg);

    ui->lab_algorithmImage->loadImage(this->locationImg_show);
    ui->lab_algorithmImage->toFitScreen();
    this->excuteImageProcess();

    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::loadImage(cv::Mat img_)
{
    if (img_.empty())
    {
        this->message = QStringLiteral("#>>>加载图片为空\n");
    }
    else
    {
        if(ui->SWidget_image->currentWidget()->objectName() == ui->page_calibrateImage->objectName())
        {

            this->message = QStringLiteral("#>>>标定图片加载成功\n");
            ui->lab_calibrateImage->loadImage(img_);
            ui->lab_calibrateImage->toFitScreen();
            img_.copyTo(this->calibrateImg);
            this->calibrateFlag = false;//重新加载图片，请重新标定
            this->initCalibrateCoordinateTable();
            ui->lab_calibrateImage->clearTexts();
        }
        else if (ui->SWidget_image->currentWidget()->objectName() == ui->page_algorithmImage->objectName())
        {
            this->message = QStringLiteral("#>>>定位图片加载成功\n");
            img_.copyTo(this->locationImg_original);
            img_.copyTo(this->locationImg_show);
            img_.copyTo(this->locationImg);

            ui->lab_algorithmImage->loadImage(this->locationImg_show);
            ui->lab_algorithmImage->toFitScreen();
            this->excuteImageProcess();
        }
    }

    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::connectModbus()
{
    if(this->Rmodbus.isConnected())
    {
        this->Rmodbus.disconnectDevice();
    }
    if(this->Wmodbus.isConnected())
    {
        this->Wmodbus.disconnectDevice();
    }

    //初始化通讯界面相关参数
    QString moudbusIP = ui->modbusIP->text();
    int modbusTimeOut = ui->modbusTimeOut->value();
    int modbusRetries = ui->modbusRetries->value();

    int RmodbusPort = ui->modbusPort_R->value();
    int RmodbusServerID = ui->modbusSeverID_R->value();


    int WmodbusPort = ui->modbusPort_W->value();
    int WmodbusServerID = ui->modbusSeverID_W->value();


    this->Rmodbus.connectDevice(moudbusIP,
                          RmodbusPort,
                          RmodbusServerID,
                          modbusTimeOut,
                          modbusRetries);
    this->Wmodbus.connectDevice(moudbusIP,
                          WmodbusPort,
                          WmodbusServerID,
                          modbusTimeOut,
                          modbusRetries);
}

void MainWindow::sendPosByModbus()
{
    if (this->imgProcess.size() >= 1 &&
        this->imgProcess[this->imgProcess.size() -1]->getImgProcessMethod() == DM_COORDINATE_Tag)
    {

        DM_CoordinateTransform *func = dynamic_cast<DM_CoordinateTransform*>(this->imgProcess[this->imgProcess.size() - 1]);
        std::vector<cv::Point2f> objectPoints = func->getObjectPoints();

        this->WmodbusData[0] = this->WmodbusData[0] > 60000 ? 0:this->WmodbusData[0]++ ;

        this->WmodbusData[1] = objectPoints.size() > ui->modbusNumData_W->value() ?
                               ui->modbusNumData_W->value():objectPoints.size();
        int num = this->WmodbusData[1]*2 + 2;
        for(int i = 2, j = 0; i < num; i = i+2)
        {
            this->WmodbusData[i] = objectPoints[j].x;
            this->WmodbusData[i+1] = objectPoints[j++].y;
        }
    }
}

void MainWindow::newProject()
{
    bool isOK = DM_Dialog::getOpenProjectName(this->projectName, this, QStringLiteral("新建工程"),
                this->projectPath,QDir::Dirs,DM_Dialog::DM_DialogType_New);
    if(isOK)//新建成功，重新配置所有的标定及相关算法
    {
        //================更新标定相关的所有文件================
        //删除当前所有算法
        while (!this->imgCalibrate.empty())
        {
            delete this->imgCalibrate.back();
            this->imgCalibrate.pop_back();
        }
        //更新label
        this->calibrateImg.copyTo(this->calibrateImg_show);
        ui->lab_calibrateImage->loadImage(this->calibrateImg_show);
        ui->lab_calibrateImage->toFitScreen();
		ui->lab_calibrateImage->clearTexts();

        this->calibrateFlag = false;
        this->initCalibrateCoordinateTable();
        this->initSystemCalibrateTable();
        //================更新定位算法相关的所有文件================
        while (!this->imgProcess.empty())
        {
            delete this->imgProcess.back();
            this->imgProcess.pop_back();
        }
        //更新label
        this->locationImg_original.copyTo(this->locationImg_show);
        this->locationImg_original.copyTo(this->locationImg);
        ui->lab_algorithmImage->loadImage(this->locationImg_show);
		ui->lab_algorithmImage->clearTexts();
        ui->lab_algorithmImage->toFitScreen();
        this->initAlgorithmCoordinateTable();
        this->initPreprocessAlgorithmTable();
        //this->excuteImageProcess();

//        this->setWindowTitle(this->projectPath); //更新窗口名称
        this->message = QStringLiteral("#>>>新建工程完成！\n");

        //使能工具列表
        ui->TWidget_toolList->topLevelItem(0)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->TWidget_toolList->topLevelItem(1)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->TWidget_toolList->topLevelItem(2)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->TWidget_toolList->topLevelItem(3)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->btn_toolConfirm->setVisible(true);//启动确认按钮

        this->proStatus[1] = this->projectName;//②工程名
        ui->statusBar->showMessage(this->proStatus[0]+
                this->proStatus[1]+
                this->proStatus[2]+
                this->proStatus[3]);
    }
    else
    {
        this->message += QStringLiteral("#>>>新建工程失败！\n");
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

//================================================
//@brief:
//@author:Hxl
//@parameter:
//@time:2021-02-11
//================================================
void MainWindow::saveProject()
{
    if (this->projectName != "")
    {
        this->saveAlgorithms(this->imgCalibrate, this->projectPath+"/"+this->projectName+"/Calibrate.gp");//保存标定文件
        this->saveAlgorithms(this->imgProcess, this->projectPath+"/"+this->projectName+"/Algorithm.gp");//保存算法文件
        this->saveCommunicationParameters( this->projectPath+"/"+this->projectName+"/Communication.gp");//保存通讯参数
        this->saveCameraParameters(this->projectPath+"/"+this->projectName+"/Camera.gp");//保存相机参数

		
        this->message += QStringLiteral("#>>>工程保存成功！\n");
    }
    else//请新建工程
    {
        //========================保存标定文件=====================================
        int  res = QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("请先新建工程或者加载工程"),
                             QStringLiteral("新建工程"),QStringLiteral("退出"));
        if(res == 0)//新建工程
        {
            this->newProject();
        }
    }

    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}
//void MainWindow::saveAsProject()
//{
//    if (ui->SWidget_image->currentWidget()->objectName() == ui->page_calibrateImage->objectName())
//    {
//        this->projectCalibratePath = QFileDialog::getSaveFileName(this, QStringLiteral("新建标定文件"), QString(), QStringLiteral("文件类型(*.cp)"));
//        this->saveAlgorithms(this->imgCalibrate, this->projectCalibratePath);
//    }
//    else if (ui->SWidget_image->currentWidget()->objectName() == ui->page_algorithmImage->objectName())
//    {
//        this->projectAlgorithmPath = QFileDialog::getSaveFileName(this, QStringLiteral("新建定位文件"), QString(), QStringLiteral("文件类型(*.mp)"));
//        this->saveAlgorithms(this->imgProcess, this->projectAlgorithmPath);
//    }
//    else if (ui->SWidget_image->currentWidget()->objectName() == ui->page_cameraVideo->objectName())
//    {
//         this->projectParameterPath = QFileDialog::getSaveFileName(this, QStringLiteral("新建设置文件"), QString(), QStringLiteral("文件类型(*.sp)"));
//         this->saveCommunicationParameters(this->projectParameterPath);
//        //更新标题
//       this->setWindowTitle(this->projectParameterPath);
//    }
//    ui->systemStatusBar->setText(this->message);//显示运行状态
//    ui->systemStatusBar->moveCursor(QTextCursor::End);
//}



void MainWindow::loadProject()
{
//    QString name;
    bool isOK = DM_Dialog::getOpenProjectName(this->projectName, this, QStringLiteral("加载工程"),
               this->projectPath,QDir::Dirs,DM_Dialog::DM_DialogType_Load);
    if(isOK)
    {
        this->loadCalibrateParameters(this->projectPath+"/"+this->projectName+"/Calibrate.gp");//加载标定文件
        this->loadLocationAlgorithms(this->projectPath+"/"+this->projectName+"/Algorithm.gp");//加载算法文件
        this->loadCommunicationParameters(this->projectPath+"/"+this->projectName+"/Communication.gp");//加载通讯文件
        this->loadCameraParameters(this->projectPath+"/"+this->projectName+"/Camera.gp");//加载相机文件

        //使能工具列表
        ui->TWidget_toolList->topLevelItem(0)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->TWidget_toolList->topLevelItem(1)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->TWidget_toolList->topLevelItem(2)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->TWidget_toolList->topLevelItem(3)->setFlags(Qt::ItemIsSelectable|
                                                        Qt::ItemIsDragEnabled|
                                                        Qt::ItemIsDropEnabled|
                                                        Qt::ItemIsUserCheckable|
                                                        Qt::ItemIsEnabled);
        ui->btn_toolConfirm->setVisible(true);//启动确认按钮

        this->proStatus[1] = this->projectName;//②工程名
        if(this->calibrateFlag)
        {
            this->proStatus[3] = QStringLiteral("已标定");//②工程名
        }
		else
		{
			this->proStatus[3] = QStringLiteral("未标定");//②工程名
		}
        ui->statusBar->showMessage(this->proStatus[0]+
                this->proStatus[1]+
                this->proStatus[2]+
                this->proStatus[3]);
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::saveAlgorithms(std::vector<DM_ImageProcessBase *> imgAlgorithm, QString algorithmPath_)
{
	QSettings pro(algorithmPath_, QSettings::IniFormat);
	pro.clear();
	pro.sync();
	pro.setIniCodec(QTextCodec::codecForName("UTF-8"));//设定编码为UTF-8，否则无法显示中文
	
	//写入项目基本信息
	pro.beginGroup("CreationInformation");
	pro.setValue("CreationTime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
	pro.endGroup();
	//保存算法
	pro.beginGroup("AlgorithmInformation");
	pro.setValue("AlgorithmNum", imgAlgorithm.size());//保存算法的总数
	for (int i = 0 ; i < imgAlgorithm.size(); i++)
	{
	    QString Prefix = QString::number(i) + "/";
	    pro.setValue(Prefix + "ImgProcess_Tag", imgAlgorithm[i]->getImgProcessMethod());
	    switch (imgAlgorithm[i]->getImgProcessMethod())
	    {
	        case DM_HANDEYECALIBRATION_Tag://手眼标定（采用其他标定板计算标定图片的特征点）
	        {
                    DM_HandEyeCalibration *func = dynamic_cast<DM_HandEyeCalibration*>(imgAlgorithm[i]);
                    pro.beginWriteArray(Prefix + "cameraPoints");//新建节名，将原始数据存入其中
                    for (int i = 0; i < func->cameraPoints.size(); i++)
                    {
                        pro.setArrayIndex(i);//设定数组的下标
                        pro.setValue("data", QPointF(func->cameraPoints[i].x, func->cameraPoints[i].y));
                    }
                    pro.endArray();

                    pro.beginWriteArray(Prefix + "robotPoints");//新建节名，将机械臂数据存入其中
                    for (int i = 0; i < func->robotPoints.size(); i++)
                    {
                        pro.setArrayIndex(i);//设定数组的下标
                        pro.setValue("data", QPointF(func->robotPoints[i].x, func->robotPoints[i].y));
                    }
                    pro.endArray();

                    cv::Mat transformM = func->getTransformMatrix();
                    pro.beginWriteArray(Prefix + "transformMatrix");//新建节名，将旋转矩阵存入
                    for (int i = 0; i < transformM.rows; i++)
                    {
                        for (int j = 0; j < transformM.cols; j++)
                        {
                            pro.setArrayIndex(i*transformM.cols +j);//设定数组的下标
                            pro.setValue("data", transformM.at<double>(i, j));
                        }
                    }
                    pro.endArray();
					//存放标定图片
					
					if (!this->calibrateImg.empty())
					{
						pro.setValue(Prefix + "calibrateImg", this->projectPath + "/" + this->projectName + "/Calibrate.bmp");//阈值(常规二值化算法使用)
						cv::imwrite(this->projectPath.toStdString() + "/" + this->projectName.toStdString() + "/Calibrate.bmp", this->calibrateImg);
					}
                    break;
                }
	        //二值化
	        case DM_THRESHOLD_GENERAL_Tag:
	        case DM_THRESHOLD_GENERAL_INV_Tag:
	        case DM_THRESHOLD_OTSU_Tag:
	        case DM_THRESHOLD_ADAPTIVE_Tag:
	        {
                    DM_Threshold *func = dynamic_cast<DM_Threshold*>(imgAlgorithm[i]);
                    pro.setValue(Prefix + "thresh", func->thresh);//阈值(常规二值化算法使用)
                    pro.setValue(Prefix + "maxValue", func->maxValue);//使用 CV_THRESH_BINARY 和 CV_THRESH_BINARY_INV 的最大值。
                    pro.setValue(Prefix + "blockSize", func->blockSize);//块大小(即：将图像分成多少块)
                    pro.setValue(Prefix + "C", func->C);//自适应二值化时的偏移系数
                    break;
                }
	        case DM_CONTOURS_Tag://轮廓
	        {
                    DM_FindContours *func = dynamic_cast<DM_FindContours*>(imgAlgorithm[i]);
                    pro.setValue(Prefix + "minAreaThreshold", func->minAreaThreshold);//设定轮廓的最小面积阈值
                    pro.setValue(Prefix + "maxAreaThreshold", func->maxAreaThreshold);//设定轮廓的最大面积阈值（通过函数找出的面积必须介于minArea和maxArea之间）
                    pro.setValue(Prefix + "mode", func->mode);//轮廓查找模式
                    pro.setValue(Prefix + "method", func->method);//轮廓查找模式
                    break;
                }
	        case  DM_MOMENTS_Tag:
	        {
	            ;
	            break;
	        }
	        case DM_COORDINATE_Tag://坐标转化
	        {
	            DM_CoordinateTransform *func = dynamic_cast<DM_CoordinateTransform*>(imgAlgorithm[i]);
	            cv::Mat transformM = func->getTransformMatrix();
	            pro.beginWriteArray(Prefix + "transformMatrix");//新建节名写入数组
	            if (!transformM.empty())
	            {
	                for (int i = 0; i < transformM.rows; i++)
	                {
	                    for (int j = 0; j < transformM.cols; j++)
	                    {
	                        pro.setArrayIndex(i*transformM.cols + j);//设定数组的下标
	                        pro.setValue("data", transformM.at<double>(i, j));
	                    }
	                }
	            }
	            pro.endArray();
				//存放用于设计定位的算法的原始图片和图像模板
				//保存图片
				if (!this->locationImg_original.empty())
				{
					pro.setValue(Prefix + "locationImg", this->projectPath + "/" + this->projectName + "/Algorithm.bmp");//阈值(常规二值化算法使用)
					cv::imwrite(this->projectPath.toStdString() + "/" + this->projectName.toStdString() + "/Algorithm.bmp", this->locationImg_original);
				}
				for (int i = 0; i < this->tempImg.size(); i++)
				{
					if (!this->tempImg[i].empty())
					{
						pro.setValue(Prefix + "tempImg", this->projectPath + "/" + this->projectName + "/tempImg_" + 
							QString::fromStdString(std::to_string(i)) + ".bmp");//阈值(常规二值化算法使用)
						cv::imwrite(this->projectPath.toStdString() + "/" + this->projectName.toStdString() + "/tempImg_" + 
							std::to_string(i) + ".bmp", this->tempImg[i]);
					}
				}
	            break;
	        }
	        case DM_CHESSBOARDCALIBRATION_Tag:
	        {
	            DM_ChessBoardCalibration *func = dynamic_cast<DM_ChessBoardCalibration*>(imgAlgorithm[i]);
	            std::vector<cv::Point2f> featurePoints = func->getFeaturetPoints();
	            pro.beginWriteArray(Prefix + "featurePoints");//新建节名，将原始数据存入其中
	            for (int i = 0; i < featurePoints.size(); i++)
	            {
	                pro.setArrayIndex(i);//设定数组的下标
	                pro.setValue("data", QPointF(featurePoints[i].x, featurePoints[i].y));
	            }
	            pro.endArray();
	
	            cv::Size chessBoardSize = func->getChessBoardSize();
	            pro.setValue(Prefix + "chessBoardSize", QSize(chessBoardSize.width, chessBoardSize.height));
	
	            break;
	        }
	        case DM_HOUGHCIRCLE_Tag:
	        {
	            DM_HoughCircle *func = dynamic_cast<DM_HoughCircle*>(imgAlgorithm[i]);
	            pro.setValue(Prefix + "method", func->method);
	            pro.setValue(Prefix + "dp", func->dp);
	            pro.setValue(Prefix + "minDist", func->minDist);
	            pro.setValue(Prefix + "cannyThreshold", func->cannyThreshold);
	            pro.setValue(Prefix + "countThreshold", func->countThreshold);
	            pro.setValue(Prefix + "minRadius", func->minRadius);
	            pro.setValue(Prefix + "maxRadius", func->maxRadius);
	
	            std::vector<cv::Vec3f> circles = func->getCitcles();//检测出来的圆①和②个元素构成圆的圆心，③为圆的半径
	            pro.beginWriteArray(Prefix + "circles");//新建节名，将原始数据存入其中
	            for (int i = 0; i < circles.size(); i++)
	            {
	                pro.setArrayIndex(i);//设定数组的下标
	                pro.setValue("center", QPointF(circles[i][0], circles[i][1]));
	                pro.setValue("radius", circles[i][2]);
	            }
	            pro.endArray();
	
	            break;
	        }
	        case DM_FINDCIRCLE_Tag:
	        {
	            DM_FindCircle *func = dynamic_cast<DM_FindCircle*>(imgAlgorithm[i]);
	            pro.setValue(Prefix + "binaryzationThreshold", func->binaryzationThreshold);
	            pro.setValue(Prefix + "countThreshold", func->countThreshold);
	            pro.setValue(Prefix + "percent", func->percent);
	            pro.setValue(Prefix + "deviation", func->deviation);
	            pro.setValue(Prefix + "minRadius", func->minRadius);
	            pro.setValue(Prefix + "maxRadius", func->maxRadius);
	            pro.setValue(Prefix + "maxRadius", func->maxRadius);
	
	            std::vector<DM_Circle> circles = func->getCitcles();//检测出来的圆①和②个元素构成圆的圆心，③为圆的半径
	            pro.beginWriteArray(Prefix + "circles");//新建节名，将原始数据存入其中
	            for (int i = 0; i < circles.size(); i++)
	            {
	                pro.setArrayIndex(i);//设定数组的下标
	                pro.setValue("center", QPointF(circles[i].center.x, circles[i].center.y));
	                pro.setValue("radius", circles[i].radius);
	            }
	            pro.endArray();
	            break;
	        }
	        case DM_MATCHTEMPLATE_Tag:
	        {
	            DM_MatchTemplate *func = dynamic_cast<DM_MatchTemplate *>(imgAlgorithm[i]);
	            pro.setValue(Prefix + "tempGrabPoint", QPointF(func->tempGrabPoint.x, func->tempGrabPoint.y));
	            pro.setValue(Prefix + "similarity", func->similarity);
	            pro.setValue(Prefix + "templateSize", QSize(func->templateImg.cols, func->templateImg.rows));
	
	            pro.beginWriteArray(Prefix + "template");//新建节名，将原始数据存入其中
	            for (int i = 0; i < func->templateImg.rows; i++)
	            {
	                for (int j = 0; j < func->templateImg.cols; j++)
	                {
	                    pro.setArrayIndex(i*func->templateImg.cols + j);//设定数组的下标
	                    pro.setValue("data", func->templateImg.at<uchar>(i, j));
	                }
	            }
	            pro.endArray();

				for (int i = 0; i < this->tempImg.size(); i++)
				{
					if (!this->tempImg[i].empty())
					{
						pro.setValue(Prefix + "tempImg", this->projectPath + "/" + this->projectName + "/tempImg_" +
							QString::fromStdString(std::to_string(i)) + ".bmp");//阈值(常规二值化算法使用)
						cv::imwrite(this->projectPath.toStdString() + "/" + this->projectName.toStdString() + "/tempImg_" +
							std::to_string(i) + ".bmp", this->tempImg[i]);
					}
				}
	            break;
	        }
	        case DM_FEATUREMATCH_Tag:
	        {
	            DM_FeatureMatch_SIFT *func = dynamic_cast<DM_FeatureMatch_SIFT *>(imgAlgorithm[i]);
	            pro.setValue(Prefix + "tempGrabPoint", QPointF(func->tempGrabPoint.x, func->tempGrabPoint.y));
	            pro.setValue(Prefix + "imgScale", func->imgScale);
	            pro.setValue(Prefix + "templateSize", QSize(func->templateImg.cols, func->templateImg.rows));
	            pro.beginWriteArray(Prefix + "template");//新建节名，将原始数据存入其中
	            for (int i = 0; i < func->templateImg.rows; i++)
	            {
	                for (int j = 0; j < func->templateImg.cols; j++)
	                {
	                    pro.setArrayIndex(i*func->templateImg.cols + j);//设定数组的下标
	                    pro.setValue("data", func->templateImg.at<uchar>(i, j));
	                }
	            }
	            pro.endArray();

				for (int i = 0; i < this->tempImg.size(); i++)
				{
					if (!this->tempImg[i].empty())
					{
						pro.setValue(Prefix + "tempImg", this->projectPath + "/" + this->projectName + "/tempImg_" +
							QString::fromStdString(std::to_string(i)) + ".bmp");//阈值(常规二值化算法使用)
						cv::imwrite(this->projectPath.toStdString() + "/" + this->projectName.toStdString() + "/tempImg_" +
							std::to_string(i) + ".bmp", this->tempImg[i]);
					}
				}
	            break;
	        }
	        case DM_CONTOURSMATCH_Tag:
	        {
	            DM_ContoursMatch *func = dynamic_cast<DM_ContoursMatch *>(imgAlgorithm[i]);
	            pro.setValue(Prefix + "similarity", func->similarity);
	
	            //保存模板抓取点
	            pro.beginWriteArray(Prefix + "tempGrabPoint");//新建节名，将原始数据存入其中
	            for (int i = 0; i < func->tempGrabPoint.size(); i++)
	            {
	                pro.setArrayIndex(i);//设定数组的下标
	                pro.setValue("data", QPointF(func->tempGrabPoint[i].x, func->tempGrabPoint[i].y));
	            }
	            pro.endArray();
	
	            //保存模板
	            pro.beginWriteArray(Prefix + "template");//新建节名，将原始数据存入其中
	            for (int k = 0; k < func->templateImg.size(); k++)
	            {
	                pro.setArrayIndex(k);//设定数组的下标
	                pro.setValue("templateSize", QSize(func->templateImg[k].cols, func->templateImg[k].rows));
	                for (int i = 0; i < func->templateImg[k].rows; i++)
	                {
	                    for (int j = 0; j < func->templateImg[k].cols; j++)
	                    {
	                        pro.setValue(QString::number(i*func->templateImg[k].cols + j) + "/data", func->templateImg[k].at<uchar>(i, j));
	                    }
	                }
	            }
	            pro.endArray();
				for (int i = 0; i < this->tempImg.size(); i++)
				{
					if (!this->tempImg[i].empty())
					{
						pro.setValue(Prefix + "tempImg", this->projectPath + "/" + this->projectName + "/tempImg_" +
							QString::fromStdString(std::to_string(i)) + ".bmp");//阈值(常规二值化算法使用)
						cv::imwrite(this->projectPath.toStdString() + "/" + this->projectName.toStdString() + "/tempImg_" +
							std::to_string(i) + ".bmp", this->tempImg[i]);
					}
				}
	
	            //保存模板轮廓
	            std::vector<std::vector<cv::Point>> templateContours = func->getTemplateContours();
	            pro.beginWriteArray(Prefix + "templateContours");//新建节名，将原始数据存入其中
	            for (int i = 0; i < templateContours.size(); i++)
	            {
	                pro.setArrayIndex(i);//设定数组的下标
	                for (int j = 0; j < templateContours[i].size(); j++)
	                {
	                    pro.setValue(QString::number(j) +"/data", QPoint(templateContours[i][j].x, templateContours[i][j].y));
	                }
	                pro.setValue( "size", templateContours[i].size());
	            }
	            pro.endArray();
				
	            break;
	        }
	        case DM_IMGNOT_Tag:
	        {
	            break;
	        }
	        //滤波
	        case DM_MEANBLUR_Tag :
	        case DM_GAUSSIANBLUR_Tag :
	        case DM_MEDIANDMFILTER_Tag :
	        case DM_BILATERALFILTER_Tag :
	        {
	            DM_Blur *func = dynamic_cast<DM_Blur*>(imgAlgorithm[i]);
	            pro.setValue(Prefix + "sigmaColor", func->sigmaColor);//色彩空间滤波器
	            pro.setValue(Prefix + "sigmaSpace", func->sigmaSpace);//坐标空间标准差
	            cv::Size kenelSize = func->kenelSize;
	            pro.setValue(Prefix + "kenelSize", QSize(kenelSize.width, kenelSize.height));
	            break;
	        }
	        //滤波
	        case DM_MORPHOLOGY_DILATE_Tag://图像膨胀
	        case DM_MORPHOLOGY_ERODE_Tag://图像腐蚀
	        case DM_MORPHOLOGY_OPEN_Tag://图像开操作
	        case DM_MORPHOLOGY_CLOSE_Tag ://图像闭操作
	        case DM_MORPHOLOGY_GRADIENT_Tag://图像形态学梯度
	        case DM_MORPHOLOGY_TOPHAT_Tag://图像顶帽
	        case DM_MORPHOLOGY_BLACKHAT_Tag://图像黑帽
	        {
	            DM_Morphology *func = dynamic_cast<DM_Morphology*>(imgAlgorithm[i]);
	            cv::Size kenelSize = func->kenelSize;
	            pro.setValue(Prefix + "kenelSize", QSize(kenelSize.width, kenelSize.height));
	            break;
	        }
	        default:
	        break;
	    }
	}
	pro.endGroup();
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::loadCommunicationParameters(QString filePath_)
{
    QFileInfo communicationFile(filePath_);//项目文件路径
    if (!communicationFile.exists())
    {
        this->message += QStringLiteral("#>>>通信文件加载失败\n");
    }
    else
    {
        this->scaneTimer.stop();//先停止中断

        QSettings pro(filePath_, QSettings::IniFormat);
        pro.beginGroup("ParameterInformation");
        //========================modbus===================
        ui->modbusPort_R->setValue(pro.value("RmodbusPort").toInt());//读_modbus端口号
        ui->modbusSeverID_R->setValue(pro.value("RmodbusServerID").toInt());//读_moudbus serverID
        ui->modbusStartRegister_R->setValue(pro.value("RmodbusServerID").toInt()); //读_moudbus 读寄存器的起始地址
        ui->modbusNumData_R->setValue(pro.value("RmodbusRegisterAmount").toInt());//读_moudbus 读寄存器读取的数据个数
        //关闭读_modbus与标定界面的数据传输，数据全部手动输入(默认都是通过通信输入
        ui->btn_modbusclose_R->setChecked(pro.value("RmodbusClose").toBool());

        ui->modbusPort_W->setValue(pro.value("WmodbusPort").toInt());//写_modbus端口号
        ui->modbusSeverID_W->setValue(pro.value("WmodbusServerID").toInt());//写_moudbus serverID
        ui->modbusStartRegister_W->setValue(pro.value("WmodbusStartRegister").toInt());//写_moudbus 读寄存器的起始地址
        //写_moudbus 商品的最大数量[寄存器的个数:  2 + WmodbusProductQuantity * 2]
        ui->modbusNumData_W->setValue(pro.value("WmodbusProductQuantity").toInt());

        ui->modbusDataType->setCurrentText(pro.value("modbusDataType").toString());//modbus数据解析格式
        ui->modbusScanTime->setValue(pro.value("modbusScanTime").toInt());//moubus扫描时间
        ui->modbusTimeOut->setValue(pro.value("modbusTimeOut").toInt());//如果连接断开，重新连接的间隔时间（ms）
        ui->modbusRetries->setValue(pro.value("modbusRetries").toInt());//重连次数
        ui->modbusIP->setText(pro.value("moudbusIP").toString());//modbus_IP

        pro.endGroup();
        
        //重新连接modbus
        this->connectModbus();
        //更新WmodbusData 数据长度
        this->WmodbusData.resize(ui->modbusNumData_W->value()*2+2,0);
        this->WmodbusData[0] = 0;//第0次处理
        this->WmodbusData[1] = 0;//抓取0个工件
        
        this->scaneTimer.start(ui->modbusScanTime->value());//ms//重启中断
        this->message += QStringLiteral("#>>>通讯配置文件加载成功！\n");
    }


}

void MainWindow::connectBaslerCameraParameters()
{
    //    QString saveImgFromeCameraPath;//保存相机的路径
//        double cameraFrameRateAbs = 3.0;//设置帧率
//        int cameraExposureTime = 20000;//相机曝光时间
    //    bool saveImageFlag = false;//默认不保存
//        this->baslerCamera.initCamera();
//        this->baslerCamera.setTriggerType(DM_BaslerCamera::DM_CameraControlEnum::DM_Camera_Software);
//        this->baslerCamera.setAcquisitionFrameRateAbs(cameraFrameRateAbs);
//        this->baslerCamera.setExposureTime(cameraExposureTime);

//        ui->cameraExposureSlider->setValue(this->baslerCamera.getExposureTime());//设置曝光时间初始值
//        ui->cameraFrameRate->setValue(this->baslerCamera.getAcquisitionFrameRateAbs());

//        DM_BaslerCamera::DM_CameraControlEnum cameraTriggerType = this->baslerCamera.getTriggerType();
//        if( cameraTriggerType == DM_BaslerCamera::DM_CameraControlEnum::DM_Camera_Line1)
//        {
//            ui->camareTriggerType->setCurrentText(QStringLiteral("外部触发"));
//        }
//        else if(cameraTriggerType == DM_BaslerCamera::DM_CameraControlEnum::DM_Camera_Software)
//        {
//            ui->camareTriggerType->setCurrentText(QStringLiteral("软件触发"));
//        }
//        else
//        {
//            ui->camareTriggerType->setCurrentText(QStringLiteral("连续采集"));
//        }
//        //采集图像
//        connect(this->baslerCamera.cameraHandler, &DM_ImageEventHandler::currentImage,this,&MainWindow::getImageFromeCamera);

    this->baslerCamera.initCamera();//初始化baslerCamera
    if(ui->camareTriggerType->currentData() == QStringLiteral("外部触发"))
    {
        this->baslerCamera.setTriggerType(DM_BaslerCamera::DM_Camera_Line1);
    }
    else if(ui->camareTriggerType->currentData() == QStringLiteral("软件触发"))
    {
        this->baslerCamera.setTriggerType(DM_BaslerCamera::DM_Camera_Software);
    }
    else if(ui->camareTriggerType->currentData() == QStringLiteral("连续采集"))
    {
        this->baslerCamera.setTriggerType(DM_BaslerCamera::DM_Camera_ContinuousAcquisition);
    }
    this->baslerCamera.setAcquisitionFrameRateAbs(ui->cameraFrameRate->value());//重置相机相机采集帧率
    this->baslerCamera.setExposureTime(ui->cameraExposureSlider->value());//重置相机曝光时间
    //采集图像
    connect(this->baslerCamera.cameraHandler, &DM_ImageEventHandler::currentImage,this,&MainWindow::getImageFromeCamera);
}

void MainWindow::connectHIKCameraParameters()
{
    if(ui->camareTriggerType->currentText() == QStringLiteral("外部触发"))
    {
        this->HIKCamera.initCamera(DM_HIKCamera::DM_Camera_Line1);
    }
    else if(ui->camareTriggerType->currentText() == QStringLiteral("软件触发"))
    {
        this->HIKCamera.initCamera(DM_HIKCamera::DM_Camera_Software);
    }
    else if(ui->camareTriggerType->currentText() == QStringLiteral("连续采集"))
    {
        this->HIKCamera.initCamera(DM_HIKCamera::DM_Camera_ContinuousAcquisition);
    }
    this->HIKCamera.setAcquisitionFrameRateAbs(ui->cameraFrameRate->value());//重置相机相机采集帧率
    this->HIKCamera.setExposureTime(ui->cameraExposureSlider->value());//重置相机曝光时间
    //采集图像
    connect(&(this->HIKCamera), &DM_HIKCamera::currentImage,this,&MainWindow::getImageFromeCamera);
}

void MainWindow::connectCameraParameters()
{
    if(ui->comB_cameraBrand->currentText() == "HIK")
    {
        this->connectHIKCameraParameters();
    }
    else if(ui->comB_cameraBrand->currentText() == "Basler")
    {
        this->connectBaslerCameraParameters();
    }
}

void MainWindow::saveCameraParameters(QString filePath_)
{
    if (filePath_ == "")
    {
        this->message += QStringLiteral("#>>>保存相机配置文件的路径不正确，请重新输入\n");
    }
    else
    {
        QSettings pro(filePath_, QSettings::IniFormat);
        pro.clear();
        pro.sync();
        pro.setIniCodec(QTextCodec::codecForName("UTF-8"));//设定编码为UTF-8，否则无法显示中文

        //写入项目基本信息
        pro.beginGroup("CreationInformation");
        pro.setValue("CreationTime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
        pro.endGroup();
        //保存算法
        pro.beginGroup("CameraParameterInformation");
         //========================相机===================
         pro.setValue("saveImgFromeCameraPath", ui->saveCameraImagePathlineEdit->text());//保存相机的路径
         pro.setValue("cameraFrameRateAbs",  ui->cameraFrameRate->value());//相机采集帧率
         pro.setValue("cameraExposureTime", ui->cameraExposureSlider->value());//相机曝光时间
         pro.setValue("cameraTriggerType", ui->camareTriggerType->currentText());//相机触发类型
         pro.setValue("saveImageFlag", ui->btn_autosaveImage->isChecked());//保存图片标志
         pro.setValue("saveCameraBrand", ui->comB_cameraBrand->currentText());//保存相机品牌
         pro.endGroup();
    }
}

void MainWindow::loadCameraParameters(QString filePath_)
{  
    QFileInfo fi(filePath_);//项目文件路径
    if (!fi.exists())
    {
        this->message += QStringLiteral("#>>>缺少相机文件，请重新加载\n");
    }
    else
    {
        QSettings pro(filePath_, QSettings::IniFormat);
        pro.beginGroup("CameraParameterInformation");

        ui->saveCameraImagePathlineEdit->setText(pro.value("saveImgFromeCameraPath").toString());//保存相机的路径
        ui->cameraFrameRate->setValue(pro.value("cameraFrameRateAbs").toDouble());//相机采集帧率
        ui->cameraExposureSlider->setValue(pro.value("cameraExposureTime").toInt());//相机曝光时间
        ui->camareTriggerType->setCurrentText(pro.value("cameraTriggerType").toString());//相机触发类型
        ui->btn_autosaveImage->setChecked(pro.value("saveImageFlag").toBool());//保存图片没有
        ui->comB_cameraBrand->setCurrentText(pro.value("saveCameraBrand").toString());//保存相机品牌);
        this->connectCameraParameters();
        pro.endGroup();
        this->message += QStringLiteral("#>>>相机配置文件加载成功！\n");
    }
}

void MainWindow::saveDefaultFiles()
{
    QSettings pro(this->projectDefaultFile, QSettings::IniFormat);
    pro.clear();
    pro.sync();
    pro.setIniCodec(QTextCodec::codecForName("UTF-8"));//设定编码为UTF-8，否则无法显示中文

    //写入项目基本信息
    pro.beginGroup("CreationInformation");
    pro.setValue("CreationTime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
    pro.endGroup();
    //保存算法
    pro.beginGroup("FilesInformation");
    pro.setValue("projectPath", this->projectPath); //工程算法路径
    pro.setValue("projectName", this->projectName); //工程算法路径
    pro.endGroup();
}

void MainWindow::loadDefaultFiles()
{
    ;
}

void MainWindow::saveCommunicationParameters(QString filePath_)
{
    if (filePath_ == "")
    {
        this->message += QStringLiteral("#>>>工程保存路径不正确，请重新输入\n");
    }
    else
    {
        QSettings pro(filePath_, QSettings::IniFormat);
        pro.clear();
        pro.sync();
        pro.setIniCodec(QTextCodec::codecForName("UTF-8"));//设定编码为UTF-8，否则无法显示中文

        //写入项目基本信息
        pro.beginGroup("CreationInformation");
        pro.setValue("CreationTime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
        pro.endGroup();
        //保存算法
        pro.beginGroup("ParameterInformation");

        //========================modbus===================
         pro.setValue("RmodbusPort", ui->modbusPort_R->value());                     //读_modbus端口号
         pro.setValue("RmodbusServerID", ui->modbusSeverID_R->value());             //读_moudbus serverID
         pro.setValue("RmodbusStartRegister", ui->modbusStartRegister_R->value());   //读_moudbus 读寄存器的起始地址
         pro.setValue("RmodbusRegisterAmount", ui->modbusNumData_R->value()); //读_moudbus 读寄存器读取的数据个数
         pro.setValue("RmodbusClose", ui->btn_modbusclose_R->isChecked());//关闭读_modbus与标定界面的数据传输，数据全部手动输入(默认都是通过通信输入)

         pro.setValue("WmodbusPort", ui->modbusPort_W->value());                    //写_modbus端口号
         pro.setValue("WmodbusServerID", ui->modbusSeverID_W->value());            //写_moudbus serverID
         pro.setValue("WmodbusStartRegister", ui->modbusStartRegister_W->value());  //写_moudbus 读寄存器的起始地址
         pro.setValue("WmodbusProductQuantity", ui->modbusNumData_W->value()); //关闭读_modbus与标定界面的数据传输，数据全部手动输入(默认都是通过通信输入)
         pro.setValue("modbusScanTime", ui->modbusScanTime->value());//moubus扫描时间
         pro.setValue("modbusDataType", ui->modbusDataType->currentText());//modbus数据解析格式
         pro.setValue("modbusTimeOut", ui->modbusTimeOut->value());//如果连接断开，重新连接的间隔时间（ms）
         pro.setValue("modbusRetries", ui->modbusRetries->value());//重连次数
         pro.setValue("moudbusIP", ui->modbusIP->text());//modbus_IP


         pro.endGroup();
    }

}

std::vector<DM_ImageProcessBase *>  MainWindow::loadAlgorithms(QString algorithmPath_)
{
    std::vector<DM_ImageProcessBase *> imgAlgorithm;
    QFileInfo fi(algorithmPath_);//项目文件路径
    if (!fi.exists())
    {
        this->message += QStringLiteral("#>>>加载工程文件的路径不正确，请重新加载\n");
    }
    else
    {
//        this->setWindowTitle(algorithmPath_);
        QSettings pro(algorithmPath_, QSettings::IniFormat);
        pro.beginGroup("AlgorithmInformation");
        size_t AlgorithmNum = pro.value("AlgorithmNum").toULongLong();
        if (AlgorithmNum > 1)
        {
            //this->clearImgProcess();
            for (int i = 0; i < AlgorithmNum; i++)
            {
                QString Prefix = QString::number(i) + "/";
                int  ProcessType = pro.value(Prefix + "ImgProcess_Tag").toInt();
                switch (ProcessType)
                {
                case DM_HANDEYECALIBRATION_Tag://手眼标定（采用其他标定板计算标定图片的特征点）
                {

                    pro.beginReadArray(Prefix + "cameraPoints");//新建节名，将相机的坐标读出来
                    int cameraPointsNum = pro.value("size").toInt();
                    std::vector<cv::Point2f> cameraPoints;
                    for (int i = 0; i < cameraPointsNum; i++)
                    {
                        pro.setArrayIndex(i);//设定数组的下标
                        QPointF p = pro.value("data").toPointF();
                        cameraPoints.push_back(cv::Point2f(p.x(), p.y()));
                    }
                    pro.endArray();

                    pro.beginReadArray(Prefix + "robotPoints");//新建节名，将机械臂数据存入其中
                    int robotPointsNum = pro.value("size").toInt();
                    std::vector<cv::Point2f> robotPoints;
                    for (int i = 0; i < robotPointsNum; i++)
                    {
                        pro.setArrayIndex(i);//设定数组的下标
                        QPointF p = pro.value("data").toPointF();
                        robotPoints.push_back(cv::Point2f(p.x(), p.y()));

                    }
                    pro.endArray();
                    DM_HandEyeCalibration *func = new DM_HandEyeCalibration(cameraPoints,robotPoints);

                    pro.beginReadArray(Prefix + "transformMatrix");//新建节名，将机械臂数据存入其中
                    int transformMatrixNum = pro.value("size").toInt();
                    if (transformMatrixNum >= 9)
                    {
                        cv::Mat transformMatrix = cv::Mat::zeros(cv::Size(3, 3), CV_64FC1);
                        for (int i = 0; i < 3; i++)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                pro.setArrayIndex(i * 3 + j);//设定数组的下标
                                transformMatrix.at<double>(i, j) = pro.value("data").toDouble();
                            }
                            this->transformMatrix = transformMatrix;
                            func->transformMatrix = transformMatrix;
                        }
                    }
                    pro.endArray();
                    imgAlgorithm.push_back(func);
					//加载图片
					QString imgPath = pro.value(Prefix + "calibrateImg").toString();
					this->calibrateImg = cv::imread(imgPath.toStdString(),IMREAD_GRAYSCALE);
                    break;
                }
                //二值化
                case DM_THRESHOLD_GENERAL_Tag:
                case DM_THRESHOLD_GENERAL_INV_Tag:
                case DM_THRESHOLD_OTSU_Tag:
                case DM_THRESHOLD_ADAPTIVE_Tag:
                {
                    DM_Threshold *fun = new DM_Threshold(DM_ImgProcess_Tag(ProcessType),
                                                         pro.value(Prefix + "thresh").toDouble(),
                                                         pro.value(Prefix + "maxValue").toDouble(),
                                                         pro.value(Prefix + "blockSize").toInt(),
                                                         pro.value(Prefix + "C").toDouble());//二值化
                    imgAlgorithm.push_back(fun);
                    break;
                }
                case DM_CONTOURS_Tag://轮廓
                {
                    DM_FindContours *fun = new DM_FindContours(pro.value(Prefix + "minAreaThreshold").toDouble(),
                                                               pro.value(Prefix + "maxAreaThreshold").toDouble(),
                                                               pro.value(Prefix + "mode").toInt(),
                                                               pro.value(Prefix + "method").toInt());
                    imgAlgorithm.push_back(fun);
                    break;
                }
                case  DM_MOMENTS_Tag:
                {
                    DM_Moment *fun = new DM_Moment();
                    imgAlgorithm.push_back(fun);
                    break;
                }
                case DM_COORDINATE_Tag://坐标转化
                {
                    DM_CoordinateTransform *func = new DM_CoordinateTransform();

                    pro.beginReadArray(Prefix + "transformMatrix");//新建节名，将机械臂数据存入其中
                    int transformMatrixNum = pro.value("size").toInt();
                    if (transformMatrixNum >= 9)
                    {
                        cv::Mat transformMatrix = cv::Mat::zeros(cv::Size(3, 3), CV_64FC1);
                        for (int i = 0; i < 3; i++)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                pro.setArrayIndex(i * 3 + j);//设定数组的下标
                                transformMatrix.at<double>(i, j) = pro.value("data").toDouble();
                            }
                        }
                        func->setTransformMatrix(transformMatrix);
                    }
                    pro.endArray();
                    imgAlgorithm.push_back(func);
                    break;
                }
                case DM_CHESSBOARDCALIBRATION_Tag:
                {
                    std::vector<cv::Point2f> featurePoints;
                    pro.beginReadArray(Prefix + "featurePoints");//新建节名，将相机的坐标读出来
                    int featurePointsNum = pro.value("size").toInt();
                    for (int i = 0; i < featurePointsNum; i++)
                    {
                        pro.setArrayIndex(i);//设定数组的下标
                        QPointF p = pro.value("data").toPointF();
                        featurePoints.push_back(cv::Point2f(p.x(), p.y()));

                    }
                    pro.endArray();

                    QSize chessBoardSize = pro.value(Prefix + "chessBoardSize").toSize();
                    DM_ChessBoardCalibration *fun =  new  DM_ChessBoardCalibration(cv::Size(chessBoardSize.width(), chessBoardSize.height()));
                    imgAlgorithm.push_back(fun);
                    break;
                }
                case DM_HOUGHCIRCLE_Tag:
                {
                        DM_HoughCircle *func = new DM_HoughCircle(pro.value(Prefix + "minDist").toDouble(),
                                                                 pro.value(Prefix + "cannyThreshold").toDouble(),
                                                                 pro.value(Prefix + "countThreshold").toDouble(),
                                                                 pro.value(Prefix + "minRadius").toInt(),
                                                                 pro.value(Prefix + "maxRadius").toInt());//二值化
                        func->dp = pro.value(Prefix + "dp").toDouble();
                        func->method = pro.value(Prefix + "method").toInt();

                        std::vector<cv::Vec3f> circles;
                        pro.beginReadArray(Prefix + "circles");//新建节名，将相机的坐标读出来
                        int circlesNum = pro.value("size").toInt();
                        for (int i = 0; i < circlesNum; i++)
                        {
                            pro.setArrayIndex(i);//设定数组的下标
                            QPointF center = pro.value("center").toPointF();
                            float radius =  pro.value("radius").toFloat();
                            circles.push_back(cv::Vec3f(center.x(),center.y(),radius));

                        }
                        pro.endArray();
                        func->circles = circles;
                        imgAlgorithm.push_back(func);
                        break;
                }
                case DM_FINDCIRCLE_Tag:
                {
                    DM_FindCircle *func = new DM_FindCircle(pro.value(Prefix + "binaryzationThreshold").toInt(),
                        pro.value(Prefix + "countThreshold").toInt(),
                        pro.value(Prefix + "minRadius").toInt(),
                        pro.value(Prefix + "maxRadius").toInt(),
                        pro.value(Prefix + "percent").toInt(),
                        pro.value(Prefix + "deviation").toInt());

                        std::vector<DM_Circle> circles ;
                        pro.beginReadArray(Prefix + "circles");//新建节名，将相机的坐标读出来
                        int circlesNum = pro.value("size").toInt();
                        for (int i = 0; i < circlesNum; i++)
                        {
                            pro.setArrayIndex(i);//设定数组的下标
                            QPointF center = pro.value("center").toPointF();
                            float radius = pro.value("radius").toFloat();
                            circles.push_back(DM_Circle(DM_Point(center.x(), center.y()), radius));
                        }
                        pro.endArray();
                        func->circles = circles;
                        imgAlgorithm.push_back(func);
                        break;
                }
                case DM_MATCHTEMPLATE_Tag:
                {
                    QPointF tempGrabPoint_ = pro.value(Prefix + "tempGrabPoint" ).toPointF();
                    double similarity = pro.value(Prefix + "similarity").toDouble();
                    DM_MatchTemplate *func = new  DM_MatchTemplate(cv::Mat(),similarity,cv::Point2f(tempGrabPoint_.x(), tempGrabPoint_.y()));

                    QSize templateSize_ = pro.value(Prefix + "templateSize").toSize();

                    pro.beginReadArray(Prefix + "template");//新建节名，将机械臂数据存入其中
                    int templatNum = pro.value("size").toInt();
                    cv::Mat template_ = cv::Mat::zeros(cv::Size(templateSize_.width(), templateSize_.height()), CV_8UC1);
                    for (int i = 0; i < template_.rows; i++)
                    {
                        for (int j = 0; j < template_.cols; j++)
                        {
                            pro.setArrayIndex(i * template_.cols + j);//设定数组的下标
                            template_.at<uchar>(i, j) = pro.value("data").toUInt();
                        }
                    }
                    func->setTemplate(template_);
                    pro.endArray();

                    imgAlgorithm.push_back(func);
                    break;
                }
                case DM_FEATUREMATCH_Tag:
                {
                    QPointF tempGrabPoint_ = pro.value(Prefix + "tempGrabPoint").toPointF();
                    double imgScale = pro.value(Prefix + "imgScale").toDouble();
                    DM_FeatureMatch_SIFT *func = new  DM_FeatureMatch_SIFT(cv::Mat(), imgScale, cv::Point2f(tempGrabPoint_.x(), tempGrabPoint_.y()));

                    QSize templateSize_ = pro.value(Prefix + "templateSize").toSize();
                    /*int templatNum = pro.value(Prefix + "template" + "/size").toInt();*/
                    pro.beginWriteArray(Prefix + "template");//新建节名，将机械臂数据存入其中
                    cv::Mat template_ = cv::Mat::zeros(cv::Size(templateSize_.width(), templateSize_.height()), CV_8UC1);
                    for (int i = 0; i < template_.rows; i++)
                    {
                        for (int j = 0; j < template_.cols; j++)
                        {
                            pro.setArrayIndex(i * template_.cols + j);//设定数组的下标
                            template_.at<uchar>(i, j) = pro.value("data").toUInt();
                        }
                    }
                    pro.endArray();
                    func->setTemplate(template_);

                    imgAlgorithm.push_back(func);
                    break;
                }
                case DM_CONTOURSMATCH_Tag:
                {

                    double similarity = pro.value(Prefix + "similarity").toDouble();
                    DM_ContoursMatch *func = new  DM_ContoursMatch(std::vector<std::vector<cv::Point>>(), similarity);

                    //读取抓取点
                    pro.beginReadArray(Prefix + "tempGrabPoint");//新建节名，将原始数据存入其中
                    int grabPtsSize = pro.value("size").toUInt();
                    std::vector<cv::Point2f> grabPts;
                    for (int i = 0; i < grabPtsSize; i++)
                    {
                        pro.setArrayIndex(i);//设定数组的下标
                        QPointF tempGrabPoint_ = pro.value("data").toPointF();
                        grabPts.push_back(cv::Point2f(tempGrabPoint_.x(), tempGrabPoint_.y()));
                    }
                    pro.endArray();
                    func->setTemplateGrabPoint(grabPts);

                    //读取模板
                    pro.beginReadArray(Prefix + "template");//新建节名，将原始数据存入其中
                    int templateNum = pro.value("size").toUInt();
                    std::vector<cv::Mat> temPlateImgs;
                    for (int k = 0; k < templateNum; k++)
                    {
                        pro.setArrayIndex(k);//设定数组的下标
                        QSize imgSize = pro.value("templateSize").toSize();
                        cv::Mat img = cv::Mat::zeros(cv::Size(imgSize.width(), imgSize.height()), CV_8UC1);
                        for (int i = 0; i < img.rows; i++)
                        {
                            for (int j = 0; j < img.cols; j++)
                            {
                                img.at<uchar>(i, j) = pro.value(QString::number(i * img.cols + j) + "/data").toUInt();
                            }
                        }
                        temPlateImgs.push_back(img);
                    }
                    pro.endArray();
                    func->setTemplate(temPlateImgs);

                    //加载模板轮廓
                    std::vector<std::vector<cv::Point>> templateContours;
                    pro.beginReadArray(Prefix + "templateContours");//新建节名，将原始数据存入其中
                    int templateContoursSize = pro.value("size").toUInt();
                    for (int i = 0; i < templateContoursSize; i++)
                    {
                        pro.setArrayIndex(i);//设定数组的下标
                        int contoursNum = pro.value("size").toUInt();
                        std::vector<cv::Point> contourPoints;
                        for (int j = 0; j < contoursNum; j++)
                        {
                            QPoint p = pro.value( QString::number(j) + "/data").toPoint();
                            contourPoints.push_back(cv::Point(p.x(),p.y()));
                        }
                        templateContours.push_back(contourPoints);
                    }
                    pro.endArray();
                    func->setTemplateContours(templateContours);
                    imgAlgorithm.push_back(func);
                    break;
                }
                case DM_IMGNOT_Tag:
                {
                    DM_ImgNot *func = new  DM_ImgNot();
                    imgAlgorithm.push_back(func);
                }
                break;
                //滤波
                case DM_MEANBLUR_Tag :
                case DM_GAUSSIANBLUR_Tag :
                case DM_MEDIANDMFILTER_Tag :
                case DM_BILATERALFILTER_Tag :
                {
                    QSize kenelSize = pro.value(Prefix + "kenelSize").toSize();
                    DM_Blur *fun =  new  DM_Blur(DM_ImgProcess_Tag(ProcessType),
                                                 cv::Size(kenelSize.width(), kenelSize.height()),
                                                 pro.value("sigmaColor").toDouble(),
                                                 pro.value("sigmaSpace").toDouble());
                    imgAlgorithm.push_back(fun);
                    break;
                }
                //滤波
                case DM_MORPHOLOGY_DILATE_Tag://图像膨胀
                case DM_MORPHOLOGY_ERODE_Tag://图像腐蚀
                case DM_MORPHOLOGY_OPEN_Tag://图像开操作
                case DM_MORPHOLOGY_CLOSE_Tag ://图像闭操作
                case DM_MORPHOLOGY_GRADIENT_Tag://图像形态学梯度
                case DM_MORPHOLOGY_TOPHAT_Tag://图像顶帽
                case DM_MORPHOLOGY_BLACKHAT_Tag://图像黑帽
                {
                    QSize kenelSize = pro.value(Prefix + "kenelSize").toSize();
                    DM_Morphology *fun =  new  DM_Morphology(DM_ImgProcess_Tag(ProcessType),
                                                 cv::Size(kenelSize.width(), kenelSize.height()));
                    imgAlgorithm.push_back(fun);
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
            pro.endGroup();
//            this->message += QStringLiteral("#>>>工程文件加载成功！\n");
        }
//        else
//        {
//            this->message += QStringLiteral("#>>>工程文件为空，请重新加载！\n");
//        }

    }
    return imgAlgorithm;
}

void MainWindow::loadCalibrateParameters(QString filePath_)
{
    this->initSystemCalibrateTable();//初始化标定算法的执行过程的表格
    this->initCalibrateCoordinateTable();//初始化标定坐标
    QFileInfo calibrateFile(filePath_);//项目文件路径
    if(!calibrateFile.exists())
    {
        this->message += QStringLiteral("#>>>标定文件加载失败\n");
		this->calibrateFlag = false;
    }
    else
    {
        while (!this->imgCalibrate.empty())
        {
            delete this->imgCalibrate.back();
            this->imgCalibrate.pop_back();
        }
        this->imgCalibrate = this->loadAlgorithms(filePath_);

        //判定否完成标定
        if (this->imgCalibrate.size() > 0 &&
                this->imgCalibrate[this->imgCalibrate.size()-1]->getImgProcessMethod() == DM_HANDEYECALIBRATION_Tag &&
                !(dynamic_cast<DM_HandEyeCalibration*>(this->imgCalibrate[this->imgCalibrate.size() - 1]))->transformMatrix.empty())
        {
            this->calibrateFlag = true;
            this->transformMatrix = dynamic_cast<DM_HandEyeCalibration*>(this->imgCalibrate[this->imgCalibrate.size() - 1])->transformMatrix;
            cv::Mat tempImg = cv::Mat::zeros(1, 1, CV_8UC1);//新建一个空白图像，加载文件的时候用
            ui->lab_calibrateImage->loadImage(tempImg);
            ui->lab_calibrateImage->clearTexts();
            this->excuteImageProcess();

            //更新标定状态表
            ui->table_systemCalibrate->setItem(0, 0, new QTableWidgetItem(QStringLiteral("坐标标定")));
            ui->table_systemCalibrate->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_systemCalibrate->item(0,0)->setFlags(Qt::NoItemFlags);

            ui->table_systemCalibrate->setItem(0,1, new QTableWidgetItem(QStringLiteral("标定完成")));
            ui->table_systemCalibrate->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_systemCalibrate->item(0,1)->setFlags(Qt::NoItemFlags);

            this->message += QStringLiteral("#>>>标定文件加载成功【已标定】！\n");
        }
        else
        {
            this->calibrateFlag = false;
            this->message += QStringLiteral("#>>>标定文件加载成功【未标定】！\n");
        }
        this->updateCalibrateCoordinateTable();
        this->updateSystemCalibrateTable();

    }
}

void MainWindow::loadLocationAlgorithms(QString filePath_)
{
    QFileInfo algorithmFile(filePath_);//算法文件
    if (!algorithmFile.exists())
    {
        this->message += QStringLiteral("#>>>定位算法文件加载失败\n");
    }
    else
    {
        while (!this->imgProcess.empty())
        {
            delete this->imgProcess.back();
            this->imgProcess.pop_back();
        }
        this->imgProcess = this->loadAlgorithms(filePath_);
        this->tempImg.clear();
        this->tempImg_RGB.clear();
        this->tempContours.clear();
        for (int i = 0; i < this->imgProcess.size(); i++)
        {
            if (this->imgProcess[i]->getImgProcessMethod() == DM_MATCHTEMPLATE_Tag)
            {
                cv::Mat img = dynamic_cast<DM_MatchTemplate*>(this->imgProcess[i])->getTemplate();
                cv::Point2f grabP = dynamic_cast<DM_MatchTemplate*>(this->imgProcess[i])->getTempGrabPoint();
                cv::Mat imgRGB;
                cv::cvtColor(img, imgRGB, cv::COLOR_GRAY2BGR);
                cv::circle(imgRGB, grabP, 5, cv::Scalar(0, 0, 255), -1, CV_AA);
                this->tempImg.push_back(img);
                this->tempImg_RGB.push_back(imgRGB);
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_FEATUREMATCH_Tag)
            {
                cv::Mat img = dynamic_cast<DM_FeatureMatch_SIFT*>(this->imgProcess[i])->getTemplate();
                cv::Point2f grabP = dynamic_cast<DM_FeatureMatch_SIFT*>(this->imgProcess[i])->getTempGrabPoint();
                cv::Mat imgRGB;
                cv::cvtColor(img, imgRGB, cv::COLOR_GRAY2BGR);
                cv::circle(imgRGB, grabP, 5, cv::Scalar(0, 0, 255), -1, CV_AA);
                this->tempImg.push_back(img);
                this->tempImg_RGB.push_back(imgRGB);
            }
            else if (this->imgProcess[i]->getImgProcessMethod() == DM_CONTOURSMATCH_Tag)
            {
                std::vector<cv::Mat> imgs = dynamic_cast<DM_ContoursMatch*>(this->imgProcess[i])->getTemplates();
                std::vector<cv::Point2f> grabP = dynamic_cast<DM_ContoursMatch*>(this->imgProcess[i])->getTempGrabPoints();
                std::vector<std::vector<cv::Point>> contours = dynamic_cast<DM_ContoursMatch*>(this->imgProcess[i])->getTemplateContours();

                for (int i = 0;  i < imgs.size(); i++)
                {
                    cv::Mat imgRGB;
                    cv::cvtColor(imgs[i], imgRGB, cv::COLOR_GRAY2BGR);
                    cv::circle(imgRGB, grabP[i], 5, cv::Scalar(0, 0, 255), -1, CV_AA);
                    cv::drawContours(imgRGB, contours,i, cv::Scalar(0, 255, 0), 2, 8);
                    this->tempImg.push_back(imgs[i]);
                    this->tempImg_RGB.push_back(imgRGB);
                    this->tempContours.push_back(contours[i]);
                }
            }
        }
        if (!this->tempImg_RGB.empty())
        {
            ui->lab_algorithmnTemp->loadImage(this->tempImg_RGB[this->tempImg_RGB.size()-1]);
            ui->lab_algorithmnTemp->toFitScreen();
        }
        this->updatePreprocessAlgorithmTable();
        this->excuteImageProcess();
        this->message += QStringLiteral("#>>>定位算法文件加载成功！\n");
    }
}

void MainWindow::initCommunicationParameters()
{
   int RmodbusPort = 502;//读_modbus端口号
   int RmodbusServerID = 1;//读_moudbus serverID
   int RmodbusStartRegister = 0;//读_moudbus 读寄存器的起始地址
   //int RmodbusRegisterAmount = 18;//读_moudbus 读寄存器读取的数据个数

   int WmodbusPort = 503;//读_modbus端口号
   int WmodbusServerID = 1;//读_moudbus serverID
   int WmodbusStartRegister = 0;//读_moudbus 读寄存器的起始地址
   int WmodbusProductQuantity = 20;//读_moudbus 读寄存器读取的数据个数
    //初始化数据传输
    this->WmodbusData.resize(WmodbusProductQuantity*2+2,0);
    this->WmodbusData[0] = 0;//第0次处理
    this->WmodbusData[1] = 0;//抓取0个工件

    int modbusScanTime  = 100;//moubus扫描时间(100ms)
    int modbusTimeOut = 3000;//如果连接断开，重新连接的间隔时间（ms）
    int modbusRetries = 5;//重连次数
    QVariant moudbusIP = "127.0.0.0";//modbus_IP
    QString modbusDataType = "ABCD";//modbus数据解析格式

    //初始化通讯界面相关参数
    ui->modbusIP->setText(moudbusIP.toString());
    ui->modbusDataType->setCurrentText(modbusDataType);
    ui->modbusScanTime->setValue(modbusScanTime);
    ui->modbusTimeOut->setValue(modbusTimeOut);
    ui->modbusRetries->setValue(modbusRetries);

    ui->modbusPort_R->setValue(RmodbusPort);
    ui->modbusSeverID_R->setValue(RmodbusServerID);
    ui->modbusStartRegister_R->setValue(RmodbusStartRegister);
    //ui->modbusNumData_R->setValue(this->RmodbusRegisterAmount);

    ui->modbusPort_W->setValue(WmodbusPort);
    ui->modbusSeverID_W->setValue(WmodbusServerID);
    ui->modbusStartRegister_W->setValue(WmodbusStartRegister);
    ui->modbusNumData_W->setValue(WmodbusProductQuantity);

    connect(&scaneTimer, &QTimer::timeout, this,&MainWindow::moudbusReadAndWrite);
    connect(&this->Rmodbus,&DM_Modbus::deviceMessage,[=](const QString& msg)
   {qDebug()<< msg;});
    scaneTimer.start(modbusScanTime);//ms
}

//计算特征点
void MainWindow::calibrateFindFeature()
{
    if(this->calibrateImg.empty())
    {
        this->message += QStringLiteral("#>>>请重新加载标定图片,图片为空\n");
    }
    else
    {
        QString calibrateStatus = "";//标定算法运行的状态
        QString calibrateType = "";//标定类型选择
        //直接通过判定标定图片是不RGB图像，间接判定是否完特征点的查找，在该系统中一旦完成特征点的查找，标定图像肯定为彩色图像
        if(this->calibrateImg.channels() == 1 && !this->calibrateFlag)
        {
            //设定标定板类型
            DM_ImageProcessBase *func = nullptr;
            std::vector<cv::Point2f> featurePoints;
            int res = DM_error_deafult;
            if (this->currentToolList== QStringLiteral("圆形棋盘格"))
            {
                func = new DM_FindCircle(ui->dotPlate_binaryThreshold->value(),
                    ui->dotPlate_countThreshold->value(),
                    ui->dotPlate_minRadius->value(),
                    ui->dotPlate_maxRadius->value(),
                    ui->dotPlate_percent->value(),
                    ui->dotPlate_deviation->value());

                cv::Mat binaryImg;
                if (ui->dotPlate_binaryThreshold->value() <= 0)//如果阈值为0则采用自适应二值化
                {
                    cv::threshold(this->calibrateImg, binaryImg, 100, 255, CV_THRESH_OTSU);//确保黑中找白
                }
                else
                {
                    cv::threshold(this->calibrateImg, binaryImg, ui->dotPlate_binaryThreshold->value(), 255, CV_THRESH_BINARY);
                }
                //查找连通域
                cv::Mat binaryLabels;
                int n_comps = cv::connectedComponents(binaryImg, binaryLabels, 8, CV_16U);
                if (n_comps < 1)
                {
                    n_comps = 1;
                }
                std::vector<std::vector<cv::Point>>labelsPts(n_comps);
                long maxNum = binaryImg.rows * binaryImg.cols / 2;
                bool stopFlag = false;
                for (int x = 0; x < binaryImg.rows && !stopFlag; x++)
                {
                    for (int y = 0; y < binaryImg.cols; y++)
                    {
                        int pixel = binaryLabels.at<__int16>(x, y);//注意labels是CV_16U类型
                        //img_color.at<Vec3b>(x, y)[0] = (pixel * 10 * 10 * 10) % 255;
                        //img_color.at<Vec3b>(x, y)[1] = (pixel * 10 * 10) % 255;
                        //img_color.at<Vec3b>(x, y)[2] = (pixel * 10) % 255;
                        labelsPts[pixel].push_back(cv::Point(y, x));
                        if (labelsPts[pixel].size() > maxNum)
                        {
                            stopFlag = true;
                            break;
                        }
                    }
                }
                maxNum = labelsPts[0].size();
                int maxNumIndex = 0;
                for (int i = 0; i < labelsPts.size(); i++)
                {
                    if (labelsPts[i].size() > maxNum)
                    {
                        maxNum = labelsPts[i].size();
                        maxNumIndex = i;
                    }
                }
                int pixel = binaryImg.at<uchar>(labelsPts[maxNumIndex][0].y, labelsPts[maxNumIndex][0].x);
                if (pixel <= 125)
                {
                    res = func->process(this->calibrateImg);
                }
                else
                {
                    res = func->process(~this->calibrateImg);
                }
                featurePoints = (dynamic_cast<DM_FindCircle*>(func))->getCircleCenters();

                calibrateType = QStringLiteral("圆形棋盘格_标定");
            }
            else
            {
                func = new DM_ChessBoardCalibration(cv::Size(ui->chessBoardCols->value(),ui->chessBoardRows->value()));
                res = func->process(this->calibrateImg);
                featurePoints = dynamic_cast<DM_ChessBoardCalibration*>(func)->getFeaturetPoints();

                //更新显示
                calibrateType = QStringLiteral("方形棋盘格_标定");
            }
            //将标定放到imgProcess的第一个元素
            if(res == DM_error_no )
            {
                if(featurePoints.size() >= 9)
                {
                    if(this->imgCalibrate.empty())
                    {
                        this->imgCalibrate.push_back(func);
                    }
                    else//在图像算法进行过程中也有可能重新标定，故不增加元素，只更新
                    {
                        delete this->imgCalibrate[0];
                        this->imgCalibrate.erase(this->imgCalibrate.begin());
                        this->imgCalibrate.insert(this->imgCalibrate.begin(),func);
                    }
                    //更新状态显示
                   calibrateStatus = QStringLiteral("计算完成");
                }
                else
                { //更新状态显示
                    this->message +=  QStringLiteral("@>>>特征点不足9个，无法完成标定，请重新设置参数或者加载图片!\n");

                    calibrateStatus = QStringLiteral("特征点不足9个，无法完成标定");
                }

                //更新显示
                this->calibrateImg_show = func->getProcessedColorImage();
                ui->lab_calibrateImage->setTexts(func->getLabelText());
                ui->lab_calibrateImage->loadImage(this->calibrateImg_show);

                //将特征点的结果显示到表格中
                 for(int i = 0 ; i < ui->table_calibrateCoordinate->rowCount() && i < featurePoints.size() ; i++)
                 {
                     QString str = QString::number(featurePoints[i].x) + " , " +
                                   QString::number(featurePoints[i].y);

                     ui->table_calibrateCoordinate->setItem(i, 0, new QTableWidgetItem(str));
                     ui->table_calibrateCoordinate->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
                     ui->table_calibrateCoordinate->item(i,0)->setFlags(Qt::NoItemFlags);

                     if(ui->btn_modbusclose_R->isChecked())
                     {
                         ui->table_calibrateCoordinate->setItem(i, 1, new QTableWidgetItem("-1 , -1"));
                         ui->table_calibrateCoordinate->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
                     }
                 }
            }
            else
            {
                ui->lab_calibrateImage->clearTexts();
                ui->lab_calibrateImage->loadImage(this->calibrateImg);
                calibrateStatus = QStringLiteral("计算失败，请选择合适的参数或者算法");
            }
            this->message +=  QString::fromLocal8Bit(func->getMessage().data());

            //更新标定状态表
            ui->table_systemCalibrate->setItem(0, 0, new QTableWidgetItem(calibrateType));
            ui->table_systemCalibrate->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_systemCalibrate->item(0,0)->setFlags(Qt::NoItemFlags);

            ui->table_systemCalibrate->setItem(0,1, new QTableWidgetItem(calibrateStatus));
            ui->table_systemCalibrate->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_systemCalibrate->item(0,1)->setFlags(Qt::NoItemFlags);
        }
        else
        {
            ui->lab_calibrateImage->loadImage(this->calibrateImg);
            this->message += QStringLiteral("#>>>已经完成特征点的查找，无需重新查找。如果想执行该算法，请重新加载标定图片!\n");
        }
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void  MainWindow::calibrateFindFeature_chessboard()
{
	if (this->calibrateImg.empty())
	{
		this->message += QStringLiteral("#>>>请重新加载标定图片,图片为空\n");
	}
	else
	{
		QString calibrateStatus = "";//标定算法运行的状态
		QString calibrateType = "";//标定类型选择
		//直接通过判定标定图片是不RGB图像，间接判定是否完特征点的查找，在该系统中一旦完成特征点的查找，标定图像肯定为彩色图像
		if (this->calibrateImg.channels() == 1 && !this->calibrateFlag)
		{
			//设定标定板类型
			DM_ImageProcessBase *func = nullptr;
			std::vector<cv::Point2f> featurePoints;
			int res = DM_error_deafult;
			if(this->currentToolList == QStringLiteral("方形棋盘格"))
			{
				func = new DM_ChessBoardCalibration(cv::Size(ui->chessBoardCols->value(), ui->chessBoardRows->value()));
				res = func->process(this->calibrateImg);
				featurePoints = dynamic_cast<DM_ChessBoardCalibration*>(func)->getFeaturetPoints();

				//更新显示
				calibrateType = QStringLiteral("方形棋盘格_标定");
			}
			//将标定放到imgProcess的第一个元素
			if (res == DM_error_no)
			{
				if (featurePoints.size() >= 9)
				{
					if (this->imgCalibrate.empty())
					{
						this->imgCalibrate.push_back(func);
					}
					else//在图像算法进行过程中也有可能重新标定，故不增加元素，只更新
					{
						delete this->imgCalibrate[0];
						this->imgCalibrate.erase(this->imgCalibrate.begin());
						this->imgCalibrate.insert(this->imgCalibrate.begin(), func);
					}
					//更新状态显示
					calibrateStatus = QStringLiteral("计算完成");
				}
				else
				{ //更新状态显示
					this->message += QStringLiteral("@>>>特征点不足9个，无法完成标定，请重新设置参数或者加载图片!\n");

					calibrateStatus = QStringLiteral("特征点不足9个，无法完成标定");
				}

				//更新显示
				//this->calibrateImg_show = func->getProcessedColorImage();
				//ui->lab_calibrateImage->setTexts(func->getLabelText());
				//ui->lab_calibrateImage->loadImage(this->calibrateImg_show);

				////将特征点的结果显示到表格中
				//for (int i = 0; i < ui->table_calibrateCoordinate->rowCount() && i < featurePoints.size(); i++)
				//{
				//	QString str = QString::number(featurePoints[i].x) + " , " +
				//		QString::number(featurePoints[i].y);

				//	ui->table_calibrateCoordinate->setItem(i, 0, new QTableWidgetItem(str));
				//	ui->table_calibrateCoordinate->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
				//	ui->table_calibrateCoordinate->item(i, 0)->setFlags(Qt::NoItemFlags);

				//	if (ui->btn_modbusclose_R->isChecked())
				//	{
				//		ui->table_calibrateCoordinate->setItem(i, 1, new QTableWidgetItem("-1 , -1"));
				//		ui->table_calibrateCoordinate->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
				//	}
				//}
				
			}
			else
			{
				//ui->lab_calibrateImage->clearTexts();
				//ui->lab_calibrateImage->loadImage(this->calibrateImg);
				calibrateStatus = QStringLiteral("计算失败，请选择合适的参数或者算法");
			}
			this->message += QString::fromLocal8Bit(func->getMessage().data());

			////更新标定状态表
			//ui->table_systemCalibrate->setItem(0, 0, new QTableWidgetItem(calibrateType));
			//ui->table_systemCalibrate->item(0, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
			//ui->table_systemCalibrate->item(0, 0)->setFlags(Qt::NoItemFlags);

			//ui->table_systemCalibrate->setItem(0, 1, new QTableWidgetItem(calibrateStatus));
			//ui->table_systemCalibrate->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
			//ui->table_systemCalibrate->item(0, 1)->setFlags(Qt::NoItemFlags);
			this->updateCalibrateCoordinateTable();//更新坐标列表
			this->updateSystemCalibrateTable();//更新算法列表
			this->updateLab_calibrateImage();//更新图像显示
		}
		else
		{
			ui->lab_calibrateImage->loadImage(this->calibrateImg);
			this->message += QStringLiteral("#>>>已经完成特征点的查找，无需重新查找。如果想执行该算法，请重新加载标定图片!\n");
		}
	}
	ui->systemStatusBar->setText(this->message);//显示运行状态
	ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::calibrateFindFeature_circle()
{
	if (this->calibrateImg.empty())
	{
		this->message += QStringLiteral("#>>>请重新加载标定图片,图片为空\n");
	}
	else
	{
		QString calibrateStatus = "";//标定算法运行的状态
		QString calibrateType = "";//标定类型选择
		//直接通过判定标定图片是不RGB图像，间接判定是否完特征点的查找，在该系统中一旦完成特征点的查找，标定图像肯定为彩色图像
		if (this->calibrateImg.channels() == 1 && !this->calibrateFlag)
		{
			//设定标定板类型
			DM_ImageProcessBase *func = nullptr;
			std::vector<cv::Point2f> featurePoints;
			int res = DM_error_deafult;
			if (this->currentToolList == QStringLiteral("圆形棋盘格"))
			{
				func = new DM_FindCircle(ui->dotPlate_binaryThreshold->value(),
					ui->dotPlate_countThreshold->value(),
					ui->dotPlate_minRadius->value(),
					ui->dotPlate_maxRadius->value(),
					ui->dotPlate_percent->value(),
					ui->dotPlate_deviation->value());

				cv::Mat binaryImg;
				if (ui->dotPlate_binaryThreshold->value() <= 0)//如果阈值为0则采用自适应二值化
				{
					cv::threshold(this->calibrateImg, binaryImg, 100, 255, CV_THRESH_OTSU);//确保黑中找白
				}
				else
				{
					cv::threshold(this->calibrateImg, binaryImg, ui->dotPlate_binaryThreshold->value(), 255, CV_THRESH_BINARY);
				}
				//查找连通域
				cv::Mat binaryLabels;
				int n_comps = cv::connectedComponents(binaryImg, binaryLabels, 8, CV_16U);
				if (n_comps < 1)
				{
					n_comps = 1;
				}
				std::vector<std::vector<cv::Point>>labelsPts(n_comps);
				long maxNum = binaryImg.rows * binaryImg.cols / 2;
				bool stopFlag = false;
				for (int x = 0; x < binaryImg.rows && !stopFlag; x++)
				{
					for (int y = 0; y < binaryImg.cols; y++)
					{
						int pixel = binaryLabels.at<__int16>(x, y);//注意labels是CV_16U类型
						//img_color.at<Vec3b>(x, y)[0] = (pixel * 10 * 10 * 10) % 255;
						//img_color.at<Vec3b>(x, y)[1] = (pixel * 10 * 10) % 255;
						//img_color.at<Vec3b>(x, y)[2] = (pixel * 10) % 255;
						labelsPts[pixel].push_back(cv::Point(y, x));
						if (labelsPts[pixel].size() > maxNum)
						{
							stopFlag = true;
							break;
						}
					}
				}
				maxNum = labelsPts[0].size();
				int maxNumIndex = 0;
				for (int i = 0; i < labelsPts.size(); i++)
				{
					if (labelsPts[i].size() > maxNum)
					{
						maxNum = labelsPts[i].size();
						maxNumIndex = i;
					}
				}
				int pixel = binaryImg.at<uchar>(labelsPts[maxNumIndex][0].y, labelsPts[maxNumIndex][0].x);
				if (pixel <= 125)
				{
					res = func->process(this->calibrateImg);
				}
				else
				{
					res = func->process(~this->calibrateImg);
				}
				featurePoints = (dynamic_cast<DM_FindCircle*>(func))->getCircleCenters();

				calibrateType = QStringLiteral("圆形棋盘格_标定");
			}
			//将标定放到imgProcess的第一个元素
			if (res == DM_error_no)
			{
				if (featurePoints.size() >= 9)
				{
					if (this->imgCalibrate.empty())
					{
						this->imgCalibrate.push_back(func);
					}
					else//在图像算法进行过程中也有可能重新标定，故不增加元素，只更新
					{
						delete this->imgCalibrate[0];
						this->imgCalibrate.erase(this->imgCalibrate.begin());
						this->imgCalibrate.insert(this->imgCalibrate.begin(), func);
					}
					//更新状态显示
					calibrateStatus = QStringLiteral("计算完成");
				}
				else
				{ //更新状态显示
					this->message += QStringLiteral("@>>>特征点不足9个，无法完成标定，请重新设置参数或者加载图片!\n");

					calibrateStatus = QStringLiteral("特征点不足9个，无法完成标定");
				}

				////更新显示
				//this->calibrateImg_show = func->getProcessedColorImage();
				//ui->lab_calibrateImage->setTexts(func->getLabelText());
				//ui->lab_calibrateImage->loadImage(this->calibrateImg_show);

				////将特征点的结果显示到表格中
				//for (int i = 0; i < ui->table_calibrateCoordinate->rowCount() && i < featurePoints.size(); i++)
				//{
				//	QString str = QString::number(featurePoints[i].x) + " , " +
				//		QString::number(featurePoints[i].y);

				//	ui->table_calibrateCoordinate->setItem(i, 0, new QTableWidgetItem(str));
				//	ui->table_calibrateCoordinate->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
				//	ui->table_calibrateCoordinate->item(i, 0)->setFlags(Qt::NoItemFlags);

				//	if (ui->btn_modbusclose_R->isChecked())
				//	{
				//		ui->table_calibrateCoordinate->setItem(i, 1, new QTableWidgetItem("-1 , -1"));
				//		ui->table_calibrateCoordinate->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
				//	}
				//}
			}
			else
			{
				//ui->lab_calibrateImage->clearTexts();
				//ui->lab_calibrateImage->loadImage(this->calibrateImg);
				calibrateStatus = QStringLiteral("计算失败，请选择合适的参数或者算法");
			}
			this->message += QString::fromLocal8Bit(func->getMessage().data());

			//更新标定状态表
			//ui->table_systemCalibrate->setItem(0, 0, new QTableWidgetItem(calibrateType));
			//ui->table_systemCalibrate->item(0, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
			//ui->table_systemCalibrate->item(0, 0)->setFlags(Qt::NoItemFlags);

			//ui->table_systemCalibrate->setItem(0, 1, new QTableWidgetItem(calibrateStatus));
			//ui->table_systemCalibrate->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
			//ui->table_systemCalibrate->item(0, 1)->setFlags(Qt::NoItemFlags);

			this->updateCalibrateCoordinateTable();//更新坐标列表
			this->updateSystemCalibrateTable();//更新算法列表
			this->updateLab_calibrateImage();//更新图像显示
		}
		else
		{
			ui->lab_calibrateImage->loadImage(this->calibrateImg);
			this->message += QStringLiteral("#>>>已经完成特征点的查找，无需重新查找。如果想执行该算法，请重新加载标定图片!\n");
		}
	}
	ui->systemStatusBar->setText(this->message);//显示运行状态
	ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::calibrateFindFeatrue_circle_hand()
{
	if (this->calibrateImg.empty())
	{
		this->message += QStringLiteral("#>>>请重新加载标定图片,图片为空\n");
	}
	else
	{
		QString calibrateStatus = "";//标定算法运行的状态
		QString calibrateType = "";//标定类型选择
		//直接通过判定标定图片是不RGB图像，间接判定是否完特征点的查找，在该系统中一旦完成特征点的查找，标定图像肯定为彩色图像
		if (this->calibrateImg.channels() == 1 && !this->calibrateFlag)
		{
			//设定标定板类型
			DM_ImageProcessBase *func = nullptr;
			std::vector<cv::Point2f> featurePoints;

			int res = DM_error_deafult;
			if (this->currentToolList == QStringLiteral("圆(框选)"))
			{
				if (this->calibrateROI != DM_Ring())//已经赋初值
				{
					func = new DM_FindCircle_Hand(this->calibrateROI);
					res = func->process(this->calibrateImg);
				}
				this->calibrateROI = DM_Ring();
				calibrateType = QStringLiteral("圆(框选)");
			}
			//将标定放到imgProcess的第一个元素
			if (res == DM_error_no)
			{
				if (this->imgCalibrate.size() >= 9)
				{
					this->message += QStringLiteral("@>>>已经有9个特征点，请不要重复框选!\n");
				}
				else
				{ //更新状态显示
					this->imgCalibrate.push_back(func);
					this->message += QStringLiteral("@>>>第") +
						QString::number(this->imgCalibrate.size()) +
						QStringLiteral("个特征点计算完成\n");
					calibrateStatus = QStringLiteral("计算完成");

					//更新显示
					DM_Ring *calibrateROI_ = new DM_Ring(dynamic_cast<DM_FindCircle_Hand*>(func)->circleROI);
					ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateROI_, false, QColor(0, 255, 255)));
					delete calibrateROI_;

					DM_Circle *calibrateCircle_ = new DM_Circle(dynamic_cast<DM_FindCircle_Hand*>(func)->circle);
					ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateCircle_, false, QColor(0, 255, 0)));
					delete calibrateCircle_;

					DM_Point *calibrateCenterP_ = new DM_Point(dynamic_cast<DM_FindCircle_Hand*>(func)->circle.center);
					ui->lab_calibrateImage->addElements(DM_LabelElement(calibrateCenterP_));
					delete calibrateCenterP_;

					DM_LabelText labelText_(QString::number(this->imgCalibrate.size()),
						dynamic_cast<DM_FindCircle_Hand*>(func)->getCircle().center);//更新显示
					ui->lab_calibrateImage->addTexts(labelText_);
					ui->lab_calibrateImage->loadImage(this->calibrateImg);
					//将特征点的结果显示到表格中
					for (int i = 0; i < ui->table_calibrateCoordinate->rowCount() && i < this->imgCalibrate.size(); i++)
					{
						if (this->imgCalibrate[i]->getImgProcessMethod() == DM_FINDCIRCLE_HAND_Tag)
						{
							DM_Point p_ = dynamic_cast<DM_FindCircle_Hand*>(this->imgCalibrate[i])->circle.center;
							QString str = QString::number(p_.x) + " , " +
								QString::number(p_.y);

							ui->table_calibrateCoordinate->setItem(i, 0, new QTableWidgetItem(str));
							ui->table_calibrateCoordinate->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
							ui->table_calibrateCoordinate->item(i, 0)->setFlags(Qt::NoItemFlags);

							//更新标定状态表
							ui->table_systemCalibrate->setItem(i, 0, new QTableWidgetItem(calibrateType));
							ui->table_systemCalibrate->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
							ui->table_systemCalibrate->item(i, 0)->setFlags(Qt::NoItemFlags);

							ui->table_systemCalibrate->setItem(i, 1, new QTableWidgetItem(calibrateStatus));
							ui->table_systemCalibrate->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
							ui->table_systemCalibrate->item(i, 1)->setFlags(Qt::NoItemFlags);

							if (ui->btn_modbusclose_R->isChecked())
							{
								ui->table_calibrateCoordinate->setItem(i, 1, new QTableWidgetItem(""));
								ui->table_calibrateCoordinate->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置内容居中
							}
						}
					}
				}
			}
			else
			{
				calibrateStatus = QStringLiteral("计算失败，重新框选\n");
			}
			if (func != nullptr)
			{
				this->message += QString::fromLocal8Bit(func->getMessage().data());
			}
			
		}
		else
		{
			ui->lab_calibrateImage->loadImage(this->calibrateImg);
			this->message += QStringLiteral("#>>>已经完成特征点的查找，无需重新查找。如果想执行该算法，请重新加载标定图片!\n");
		}
	}
	ui->systemStatusBar->setText(this->message);//显示运行状态
	ui->systemStatusBar->moveCursor(QTextCursor::End);
}

void MainWindow::calibrateConfirm()
{
    //要进行标定必须先计算特征点，否则计算失
    if((this->imgCalibrate.size()>0 && 
		(this->imgCalibrate[0]->getImgProcessMethod() == DM_FINDCIRCLE_Tag ||
		this->imgCalibrate[0]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag))||
		(this->imgCalibrate.size() > 6 &&
		 this->imgCalibrate[0]->getImgProcessMethod() == DM_FINDCIRCLE_HAND_Tag))
    {
        if(!this->calibrateFlag)
        {
            std::vector<cv::Point2f> camreaFeatrues;
            if(this->imgCalibrate[0]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)
            {
                camreaFeatrues = dynamic_cast<DM_FindCircle*>(this->imgCalibrate[0])->getCircleCenters();
            }
			else if (this->imgCalibrate[0]->getImgProcessMethod() == DM_FINDCIRCLE_HAND_Tag)
			{
				for (int i = 0; i < this->imgCalibrate.size(); i++)
				{
					camreaFeatrues.push_back(dynamic_cast<DM_FindCircle_Hand*>(this->imgCalibrate[i])->getCircle().center.toPoint2f());
				}
			}
			else if (this->imgCalibrate[0]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)
			{
				camreaFeatrues = dynamic_cast<DM_ChessBoardCalibration*>(this->imgCalibrate[0])->getFeaturetPoints();
			}
			else
			{
				this->message += QStringLiteral("#>>>请完整填写与标定板上特征点的坐标相对应的坐标!\n");
			}
            std::vector<cv::Point2f> robotFeatrues;
            //获得表格中对应的机器人的坐标的值
            for(int i = 0 ; i < ui->table_calibrateCoordinate->rowCount() && i < camreaFeatrues.size() ; i++)
            {
                QTableWidgetItem *item = ui->table_calibrateCoordinate->item(i,1);
                QStringList strlist=item->text().split(",");
                if(strlist.size() >= 2)
                {
                    float x = QString(strlist.at(0)).toFloat();
                    float y = QString(strlist.at(1)).toFloat();
                    if(abs(x+1)< 1.0e-6 && abs(y+1)< 1.0e-6)
                    {
                        this->message += QStringLiteral("#>>>请完整填写与标定板上特征点的坐标相对应的坐标!\n");
                        break;
                    }
                    else
                    {
                        robotFeatrues.push_back(cv::Point2f(x,y));
                    }
                }
                else
                {
                    this->message += QStringLiteral("#>>>请【参照标准格式:(x,y)】填写与标定板上特征点的坐标相对应的坐标!\n");
                    break;
                }
            }
            if(robotFeatrues.size() <= camreaFeatrues.size())
            {
                DM_ImageProcessBase *func = new DM_HandEyeCalibration(camreaFeatrues,robotFeatrues);
                func->process();
                if(func->getErrorID() == DM_error_no)
                {
                    this->imgCalibrate.push_back(func);
                    this->calibrateFlag = true;//重新加载图片，请重新标定
                    this->transformMatrix = dynamic_cast<DM_HandEyeCalibration*>(func)->getTransformMatrix();

                    //========================保存标定文件=====================================
                    QMessageBox::StandardButton result = QMessageBox::information(NULL, QStringLiteral("提示"),
                                 QStringLiteral("是否保存标定数据?"), QMessageBox::Yes | QMessageBox::No);
                    if(result == QMessageBox::Yes)
                    {
                        //this->saveAsProject();
                        this->saveAlgorithms(this->imgCalibrate, this->projectPath+"/"+this->projectName+"/Calibrate.gp");//保存标定文件
                        this->proStatus[3] = QStringLiteral("已标定");//②工程名
                    }
                    else
                    {
                        this->proStatus[3] = QStringLiteral("未标定");//②工程名
                    }
                    ui->statusBar->showMessage(this->proStatus[0]+
                            this->proStatus[1]+
                            this->proStatus[2]+
                            this->proStatus[3]);
                }
                this->message +=  QString::fromLocal8Bit(func->getMessage().data());

                //更新标定状态表
                ui->table_systemCalibrate->setItem(1, 0, new QTableWidgetItem(QStringLiteral("坐标标定")));
                ui->table_systemCalibrate->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
                ui->table_systemCalibrate->item(1,0)->setFlags(Qt::NoItemFlags);

                ui->table_systemCalibrate->setItem(1,1, new QTableWidgetItem(QStringLiteral("标定完成")));
                ui->table_systemCalibrate->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
                ui->table_systemCalibrate->item(1,1)->setFlags(Qt::NoItemFlags);
            }
            else
            {
                //更新标定状态表
                ui->table_systemCalibrate->setItem(1, 0, new QTableWidgetItem(QStringLiteral("坐标标定")));
                ui->table_systemCalibrate->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
                ui->table_systemCalibrate->item(1,0)->setFlags(Qt::NoItemFlags);

                ui->table_systemCalibrate->setItem(1,1, new QTableWidgetItem(QStringLiteral("标定失败")));
                ui->table_systemCalibrate->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
                ui->table_systemCalibrate->item(1,1)->setFlags(Qt::NoItemFlags);
            }
        }
        else
        {
            this->message += QStringLiteral("#>>>该系统已经完成标定，请勿重复标定!\n");
        }
    }
    else
    {
        this->message += QStringLiteral("#>>>请先计算特征点，才能进入标定流程!\n");
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}
//执行算法
/*void MainWindow::on_btn_executeAlgorithm_clicked()
{
    //必须先标定成功了才能进行相应的算法操作，否则所有的算法不能执行
    if (this->calibrateFlag)
    {
        switch (this->imgAlgorithmType)
        {
            //二值化
            case DM_THRESHOLD_GENERAL_Tag:
            case DM_THRESHOLD_GENERAL_INV_Tag:
            case DM_THRESHOLD_OTSU_Tag:
            case DM_THRESHOLD_ADAPTIVE_Tag:
            {
                double thresh = ui->threashold_Box->value();
                int blockSize = ui->blockSize_Box->value();//这个必须为奇数

                int w = this->locationImg_original.rows > this->locationImg_original.cols ?
                        this->locationImg_original.cols : this->locationImg_original.rows;

                blockSize = blockSize < 3 ? 3: blockSize;
                blockSize = blockSize > w ? w: blockSize;
                blockSize = (blockSize % 2 == 0)? (blockSize-1):blockSize;//block必须为奇数
                DM_ImageProcessBase *func = new DM_Threshold(this->imgAlgorithmType, thresh, 255, blockSize);
                this->addImgProcess(func);
                break;
            }
            case DM_MEANBLUR_Tag :
            case DM_GAUSSIANBLUR_Tag :
            case DM_MEDIANDMFILTER_Tag :
            case DM_BILATERALFILTER_Tag :
            {
                cv::Size  kernelSize= cv::Size(ui->blurKernelW->value(),ui->blurKernelH->value());//这个必须为奇数
                DM_ImageProcessBase *func = new DM_Blur(this->imgAlgorithmType,kernelSize,
                                                        ui->blur_sigmaColor->value(),
                                                        ui->blur_sigmaSpace->value());
                this->addImgProcess(func);
                break;
            }
            case DM_MORPHOLOGY_DILATE_Tag :
            case DM_MORPHOLOGY_ERODE_Tag :
            case DM_MORPHOLOGY_OPEN_Tag :
            case DM_MORPHOLOGY_CLOSE_Tag :
            case DM_MORPHOLOGY_GRADIENT_Tag:
            case DM_MORPHOLOGY_TOPHAT_Tag :
            case DM_MORPHOLOGY_BLACKHAT_Tag:

            {
                cv::Size  kernelSize= cv::Size(ui->morphologyKernelW->value(),ui->morphologyKernelH->value());//这个必须为奇数
                DM_ImageProcessBase *func = new DM_Morphology(this->imgAlgorithmType,kernelSize);
                this->addImgProcess(func);
                break;
            }
            case DM_CONTOURS_Tag://轮廓
            {
                double maxArea = ui->maxArea_Box->value();
                double minArea = ui->minArea_Box->value();
                DM_ImageProcessBase *func = new DM_FindContours(minArea, maxArea);
                this->addImgProcess(func);
                break;
            }
            case  DM_MOMENTS_Tag://图像的矩
            {
                if ( this->imgProcess.size() > 1 &&
                     this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CONTOURS_Tag)
                {
                    DM_FindContours *func = dynamic_cast<DM_FindContours*>(this->imgProcess[this->imgProcess.size() - 1]);
                    std::vector<std::vector<cv::Point> > contours_ = func->contours;
                    DM_Moment *func_moment = new DM_Moment(contours_);
                    this->addImgProcess(func_moment);
                }
                else
                {
                    this->message += QStringLiteral("#>>>请先查找轮廓,才能进行“图像矩”相关算法\n");
                }
                break;
            }
            case DM_COORDINATE_Tag://坐标转化
            {
                if (this->imgProcess.size() >= 1 &&
                    this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_MOMENTS_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else if (this->imgProcess.size() >= 1 &&
                    this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CONTOURS_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else if (this->imgProcess.size() >= 1 &&
                         this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else if (this->imgProcess.size() >= 1 &&
                         this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_HOUGHCIRCLE_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else if (this->imgProcess.size() >= 1 &&
                    this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else if (this->imgProcess.size() >= 1 &&
                    this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_MATCHTEMPLATE_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else if (this->imgProcess.size() >= 1 &&
                    this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_FEATUREMATCH_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else if (this->imgProcess.size() >= 1 &&
                         this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CONTOURSMATCH_Tag)
                {
                    DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                    this->addImgProcess(func_coord);
                }
                else
                {
                    this->message += QStringLiteral("#>>>请先计算特征点的坐标(例如：调用“图像的矩-质心”算法)!\n");
                }

                //========================保存算法文件=====================================

                if(this->imgProcess[this->imgProcess.size()-1]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                   this->imgProcess[this->imgProcess.size()-1]->getErrorID() == DM_error_no)
                {
                    QMessageBox::StandardButton result = QMessageBox::information(NULL, QStringLiteral("提示"),
                                 QStringLiteral("是否保存算法?"), QMessageBox::Yes | QMessageBox::No);
                    if(result == QMessageBox::Yes)
                    {
                        this->saveAsProject();
                    }
                }
                break;
            }
            case DM_CHESSBOARDCALIBRATION_Tag://棋盘格查找
            {
                DM_ChessBoardCalibration *func = new DM_ChessBoardCalibration(cv::Size(ui->chessBoardCols->value(),ui->chessBoardRows->value()));
                this->addImgProcess(func);
                break;
            }
            case DM_HOUGHCIRCLE_Tag://霍夫圆
            {
                DM_HoughCircle *func = new DM_HoughCircle(ui->hough_minDist->value(),
                                                          ui->hough_cannyThreshold->value(),
                                                          ui->hough_countThreshold->value(),
                                                          ui->hough_minRadius->value(),
                                                          ui->hough_maxRadius->value());
                this->addImgProcess(func);
                break;
            }
            case DM_FINDCIRCLE_Tag:
            {
                DM_FindCircle *func = new DM_FindCircle(ui->findCircle_binaryThreshold->value(),
                                                        ui->findCircle_countThreshold->value(),
                                                        ui->findCircle_minRadius->value(),
                                                        ui->findCircle_maxRadius->value(),
                                                        ui->findCircle_percent->value(),
                                                        ui->findCircle_deviation->value());
                this->addImgProcess(func);
                break;
            }
            case DM_MATCHTEMPLATE_Tag://图像匹配
            {
                if(this->tempImg.empty())
                {
                    this->message += QStringLiteral("#>>>模板为空，请先框选模板!\n");
                }
                else
                {
                    DM_MatchTemplate *func = new DM_MatchTemplate(this->tempImg[this->tempImg.size()-1],
                        ui->similarityCoefficient->value(),
                        this->tempDrapPoints[this->tempDrapPoints.size()-1]);
                    this->addImgProcess(func);
                }
                break;
            }
            case  DM_FEATUREMATCH_Tag://特征点匹配
            {
                if (this->tempImg.empty())
                {
                    this->message += QStringLiteral("#>>>模板为空，请先框选模板!\n");
                }
                else
                {
                    DM_FeatureMatch_SIFT *func = new DM_FeatureMatch_SIFT(this->tempImg[this->tempImg.size() - 1],1.0,
                        this->tempDrapPoints[this->tempDrapPoints.size() - 1]);
                    this->addImgProcess(func);
                }
                break;
            }
            case  DM_CONTOURSMATCH_Tag://轮廓匹配
            {
                if (this->tempContours.empty())
                {
                    this->message += QStringLiteral("#>>>模板为空，请先框选模板!\n");
                }
                else
                {
                    DM_ContoursMatch *func = new DM_ContoursMatch(this->tempContours, ui->similarityCoefficient->value());
                    func->setTemplate(this->tempImg);
                    func->setTemplateGrabPoint(this->tempDrapPoints);
                    this->addImgProcess(func);
                }
                break;
            }
            case  DM_IMGNOT_Tag://轮廓匹配
            {

                DM_ImgNot *func = new DM_ImgNot();
                this->addImgProcess(func);
                break;
            }
            default:
            {
                this->message += QStringLiteral("#>>>请选择恰当的算法!\n");
                break;
            }
        }
    }
    else
    {
        this->message += QStringLiteral("#>>>请标定，才能执行后续算法\n");
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}
*/
void MainWindow::on_btn_addTemp_clicked()//添加模板
{
    cv::Mat img,img_RGB;
    this->locationImg(this->tempRect).copyTo(img);
    if (!img.empty())
    {
        if (img.channels() == 1)
        {
            cv::cvtColor(img, img_RGB, cv::COLOR_GRAY2BGR);

        }
        else
        {
            img.copyTo(img_RGB);
            cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        }
        cv::Point2f p(-1,-1);
        if (this->templateMassCenterFlag == false)//中心定位
        {
            p = cv::Point2f(img.cols / 2.0, img.rows / 2.0);
            cv::circle(img_RGB, p, 5, cv::Scalar(0, 0, 255), -1, CV_AA);
        }
        else//质心定位
        {
            cv::Mat binaryImg;
            cv::threshold(img, binaryImg, 100, 255, CV_THRESH_OTSU);
            int mode_ = cv::RETR_EXTERNAL;
            int method_ = cv::CHAIN_APPROX_NONE;
            std::vector<std::vector<cv::Point>> contours;//返回找到的轮廓
            std::vector<cv::Vec4i> hierarchy; //轮廓索引编号
            findContours(binaryImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
            double maxContourAreas = 0;//返回找到的轮廓对应的面积
            int maxContourAreasID = -1;
            for (int i = 0; i < contours.size();i++)
            {
                double s = cv::contourArea(contours[i]);
                if (s >= maxContourAreas)
                {
                    maxContourAreas = s;
                    maxContourAreasID = i;
                }
            }
            if (maxContourAreasID == -1)
            {
                this->message += QStringLiteral("#>>>查找模板轮廓失败，建议采用中心定位\n");
            }
            else
            {
                cv::Moments mu;//计算的矩
                mu = cv::moments(contours[maxContourAreasID], false);
                //计算轮廓的质心
                p = cv::Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
                this->message += QStringLiteral("#>>>查找计算质心成功\n");

                cv::drawContours(img_RGB, contours, maxContourAreasID, cv::Scalar(0, 255, 0), 2, 8);//则在待测试图像上画出此轮廓
                cv::circle(img_RGB, p, 2, cv::Scalar(0, 0, 255), -1, CV_AA);
                if (this->tempContours.empty())
                {
                    this->tempContours.push_back(contours[maxContourAreasID]);
                }
                else
                {
                    this->tempContours[0] = contours[maxContourAreasID];
                }
            }

        }

        //暂时考虑一个模板
        if(this->tempDrapPoints.empty())
        {
            this->tempDrapPoints.push_back(p);
            this->tempImg.push_back(img);
            this->tempImg_RGB.push_back(img_RGB);
        }
        else
        {
            this->tempDrapPoints[0] = p;
            img.copyTo(this->tempImg[0]);
            img_RGB.copyTo(this->tempImg_RGB[0]);
        }
        cv::imwrite("template.bmp", img);
        ui->lab_algorithmnTemp->loadImage(img_RGB);
        ui->lab_algorithmnTemp->toFitScreen();
        ui->lab_algorithmImage->setShowDrawElementFlag(false);
    }
    else
    {
        this->message += QStringLiteral("#>>>原始图片为空，请先加载图片！\n");
    }
    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}
void MainWindow::receiveLocationLabelElement(DM_Element *elem)
{
    if (elem != nullptr &&
        elem->type == Rect_ELMT)
    {
        DM_Rect *rect_ = dynamic_cast<DM_Rect *>(elem);
        this->tempRect = cv::Rect(rect_->leftTop.toPoint(), rect_->rightBottom.toPoint());
    }

}

void MainWindow::receiveCalibrateElement(DM_Element *elem)
{
    if (elem != nullptr &&
        elem->type == Ring_ELMT&&
		!this->calibrateImg.empty())
    {
        DM_Ring *ring_ = dynamic_cast<DM_Ring *>(elem);
        this->calibrateROI = DM_Ring(ring_->center, ring_->innerRadius,ring_->outerRadius,ring_->direction);
        //还需要将拟合的圆画出来
        DM_Circle circle_;
        circle_.generate(this->calibrateImg,*ring_);//获取拟合的圆
        //qDebug()<<"ring："<<calibrateROI.center.x<<","<< calibrateROI.center.y<< " INR:"<< calibrateROI.innerRadius<<"  outR:"<< calibrateROI.outerRadius;
       
		//临时显示当前框选的结果
		if(circle_.isValid())//拟合成功
        {
            //qDebug()<<"circle："<< circle_.center.toPoint().x<<","<< circle_.center.toPoint().y<< " R:"<< circle_.radius;
          /*  if (this->calibrateImg_show.empty())*/
			{
				if (this->calibrateImg.channels() == 1)
				{
					cv::cvtColor(this->calibrateImg, this->calibrateImg_show, COLOR_GRAY2BGR);
				}
				else
				{
					this->calibrateImg.copyTo(this->calibrateImg_show);
				}
			}
			cv::circle(this->calibrateImg_show, circle_.center.toPoint(), circle_.radius, cv::Scalar(0, 255, 0), 2);
            cv::circle(this->calibrateImg_show, circle_.center.toPoint(), 1, cv::Scalar(0, 0, 255), -1);
            ui->lab_calibrateImage->loadImage(this->calibrateImg_show);
        }

    }
}

void MainWindow::getImageFromeCamera()
{
	if (ui->comB_cameraBrand->currentText() == "HIK")
	{
		if (g_HIKCameraImage.empty()) return;//如果图像为空这不进行后面的操作
		if (ui->SWidget_image->currentWidget()->objectName() == ui->page_cameraVideo->objectName())
		{
			ui->lab_cameraVideo->loadImage(g_HIKCameraImage);//显示在label
		}
		else
		{
			this->loadImage(g_HIKCameraImage);
		}
		if (ui->btn_autosaveImage->isChecked())//手动点击了采集图片按钮，保存图像
		{
			QDate D1 = QDate::currentDate();
			QTime T1 = QTime::currentTime();
			std::string data = std::to_string(D1.year()) +
				std::to_string(D1.month()) +
				std::to_string(D1.day());
			std::string time = std::to_string(T1.hour()) +
				std::to_string(T1.minute()) +
				std::to_string(T1.second()) +
				std::to_string(T1.msec());
			std::string imgName;
			if (ui->saveCameraImagePathlineEdit->text() == "")
			{
				imgName = data + time + ".bmp";
			}
			else
			{
				imgName = ui->saveCameraImagePathlineEdit->text().toStdString() + "/" + data + time + ".bmp";
			}
			cv::imwrite(imgName, g_HIKCameraImage);
		}
	}
	else if (ui->comB_cameraBrand->currentText() == "Basler")
	{
		if(g_baslerCameraImage.empty()) return;//如果图像为空这不进行后面的操作
		if(ui->SWidget_image->currentWidget()->objectName() == ui->page_cameraVideo->objectName())
		{
		    ui->lab_cameraVideo->loadImage(g_baslerCameraImage);//显示在label
		}
		else
		{
		    this->loadImage(g_baslerCameraImage);
		}
		if(ui->btn_autosaveImage->isChecked())//手动点击了采集图片按钮，保存图像
		{
		    QDate D1 = QDate::currentDate();
		    QTime T1 =QTime::currentTime();
		    std::string data = std::to_string(D1.year()) +
		                       std::to_string(D1.month())+
		                       std::to_string(D1.day());
		    std::string time = std::to_string(T1.hour())+
		                       std::to_string(T1.minute())+
		                       std::to_string(T1.second())+
		                       std::to_string(T1.msec());
		    std::string imgName;
		    if(ui->saveCameraImagePathlineEdit->text() == "")
		    {
		        imgName = data + time +"1.bmp";
		    }
		    else
		    {
		        imgName = ui->saveCameraImagePathlineEdit->text().toStdString() + "/" + data + time +"1.bmp";
		    }
		    cv::imwrite(imgName,g_baslerCameraImage);
		}
	}
    
}
void MainWindow::on_cameraExposureSlider_valueChanged(int value)
{
	if (ui->comB_cameraBrand->currentText() == "HIK")
	{
		this->HIKCamera.setExposureTime(value);
	}
	else if (ui->comB_cameraBrand->currentText() == "Basler")
	{
		this->baslerCamera.setExposureTime(value);
	}
}

void MainWindow::on_cameraFrameRate_valueChanged(double arg1)
{
	if (ui->comB_cameraBrand->currentText() == "HIK")
	{
		this->HIKCamera.setAcquisitionFrameRateAbs(arg1);
	}
	else if (ui->comB_cameraBrand->currentText() == "Basler")
	{
		this->baslerCamera.setAcquisitionFrameRateAbs(arg1);
	}
}

void MainWindow::on_camareTriggerType_activated(const QString &arg1)
{
	if (ui->comB_cameraBrand->currentText() == "HIK")
	{
		if (arg1 == QStringLiteral("连续采集"))
		{
			this->HIKCamera.setTriggerSource(DM_HIKCamera::DM_Camera_ContinuousAcquisition);
		}
		else if (arg1 == QStringLiteral("软件触发"))
		{
			this->HIKCamera.setTriggerSource(DM_HIKCamera::DM_Camera_Software);
		}
		else if (arg1 == QStringLiteral("外部触发"))
		{
			this->HIKCamera.setTriggerSource(DM_HIKCamera::DM_Camera_Line1);
		}
	}
	else if (ui->comB_cameraBrand->currentText() == "Basler")
	{
		if(arg1 == QStringLiteral("连续采集"))
		{
		    this->baslerCamera.setTriggerType(DM_BaslerCamera::DM_Camera_ContinuousAcquisition);
		}
		else if(arg1 == QStringLiteral("软件触发"))
		{
		    this->baslerCamera.setTriggerType(DM_BaslerCamera::DM_Camera_Software);
		}
		else if(arg1 == QStringLiteral("外部触发"))
		{
		    this->baslerCamera.setTriggerType(DM_BaslerCamera::DM_Camera_Line1);
		}
	}
}

void MainWindow::cameraImage_cameraStart()
{

    if(ui->comB_cameraBrand->currentText() == "HIK")
    {
        this->HIKCamera.startAcquire();
    }
    else if(ui->comB_cameraBrand->currentText() == "Basler")
    {
        this->baslerCamera.startAcquire();
    }
    ui->action_takePicture->setEnabled(true);//使能采图按钮
}

void MainWindow::cameraImage_cameraStop()
{

    if(ui->comB_cameraBrand->currentText() == "HIK")
    {
        this->HIKCamera.stopAcquire();
    }
    else if(ui->comB_cameraBrand->currentText() == "Basler")
    {
          this->baslerCamera.stopAcquire();
    }
    ui->action_takePicture->setEnabled(false);//屏蔽采图按钮
}

void MainWindow::cameraImage_zoomIn()
{
    if(ui->SWidget_image->currentWidget()->objectName() == ui->page_calibrateImage->objectName())
    {
        ui->lab_calibrateImage->zoomInImage();
    }
    else if(ui->SWidget_image->currentWidget()->objectName() == ui->page_algorithmImage->objectName())
    {
        ui->lab_algorithmImage->zoomInImage();
    }
    else if(ui->SWidget_image->currentWidget()->objectName() == ui->page_cameraVideo->objectName())
    {
        ui->lab_cameraVideo->zoomInImage();
    }
}

void MainWindow::cameraImage_zoomOut()
{
    if(ui->SWidget_image->currentWidget()->objectName() == ui->page_calibrateImage->objectName())
    {
        ui->lab_calibrateImage->zoomOutImage();
    }
    else if(ui->SWidget_image->currentWidget()->objectName() == ui->page_algorithmImage->objectName())
    {
        ui->lab_algorithmImage->zoomOutImage();
    }
    else if(ui->SWidget_image->currentWidget()->objectName() == ui->page_cameraVideo->objectName())
    {
        ui->lab_cameraVideo->zoomOutImage();
    }
}

void MainWindow::cameraImage_fitScreen()
{
    if(ui->SWidget_image->currentWidget()->objectName() == ui->page_calibrateImage->objectName())
    {
        ui->lab_calibrateImage->toFitScreen();
    }
    else if(ui->SWidget_image->currentWidget()->objectName() == ui->page_algorithmImage->objectName())
    {
        ui->lab_algorithmImage->toFitScreen();
    }
    else if(ui->SWidget_image->currentWidget()->objectName() == ui->page_cameraVideo->objectName())
    {
        ui->lab_cameraVideo->toFitScreen();
    }
}

void MainWindow::cameraImage_takePicture()
{
    if(ui->comB_cameraBrand->currentText() == "HIK")
    {
        this->HIKCamera.grabImageBySotfware();
    }
    else if(ui->comB_cameraBrand->currentText() == "Basler")
    {
        this->baslerCamera.grabImageBySotfware();
    }

}

void MainWindow::moudbusReadAndWrite()
{
    //============更新链接状态===============
    if(this->Rmodbus.isConnected())
    {
        ui->modbusStatus_R->setText(QStringLiteral("已连接"));
        ui->modbusStatus_R->setStyleSheet("background-color: rgb(0, 255, 0)");
    }
    else
    {
        ui->modbusStatus_R->setText(QStringLiteral("未连接"));
        ui->modbusStatus_R->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if(this->Wmodbus.isConnected())
    {
        ui->modbusStatus_W->setText(QStringLiteral("已连接"));
        ui->modbusStatus_W->setStyleSheet("background-color: rgb(0, 255, 0)");
    }
    else
    {
        ui->modbusStatus_W->setText(QStringLiteral("未连接"));
        ui->modbusStatus_W->setStyleSheet("background-color: rgb(255, 0, 0)");
    }

    //读/写取数据

    //完成标定之后就不读取相应的寄存器
    if(this->Rmodbus.isConnected())
    {
        this->Rmodbus.readFloat32(ui->modbusStartRegister_R->value(),ui->modbusNumData_R->value(),this->RmodbusData,ui->modbusDataType->currentText());
    }
    if(this->Wmodbus.isConnected())
    {
        this->Wmodbus.writeFloat32(ui->modbusStartRegister_W->value(),this->WmodbusData,ui->modbusDataType->currentText());
    }
    //更新标定列表的参数
    if(!this->calibrateFlag &&
       !ui->btn_modbusclose_R->isChecked() &&
       this->RmodbusData.size() >= 18)//没有完成标定，启用通讯
    {
        for(int i = 0, j = 0; i < this->RmodbusData.size(); i = i+2 )
        {
            QString originalStr = QString::number(this->RmodbusData[i]) + " , " +
                          QString::number(this->RmodbusData[i+1]);
            ui->table_calibrateCoordinate->setItem(j, 1, new QTableWidgetItem(originalStr));
            ui->table_calibrateCoordinate->item(j,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置内容居中
            ui->table_calibrateCoordinate->item(j++, 1)->setFlags(Qt::NoItemFlags);

        }
    }
}

void MainWindow::on_btn_modbusConnect_clicked()
{
    this->connectModbus();
    //更新WmodbusData 数据长度
    this->WmodbusData.resize(ui->modbusNumData_W->value()*2+2,0);
    this->WmodbusData[0] = 0;//第0次处理
    this->WmodbusData[1] = 0;//抓取0个工件

}

void MainWindow::on_btn_modbusTest_clicked()
{
    if(this->RmodbusData.size()>2)
    {
        ui->modbusReadData0->setValue(this->RmodbusData[0]);
        ui->modbusReadData1->setValue(this->RmodbusData[1]);
    }

    //写入数据
    //this->WmodbusData.clear();
    this->WmodbusData[0] = ui->modbusWriteData0->value();
    this->WmodbusData[1] = ui->modbusWriteData1->value();
}

void MainWindow::on_btn_modbusclose_R_clicked(bool checked)
{

    if(checked)
    {
        //初始化表格
         for(int i = 0 ; i < ui->table_calibrateCoordinate->rowCount(); i++)
         {
             ui->table_calibrateCoordinate->item(i, 1)->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable);//第一列不允许修改
         }
    }
    else
    {
        //初始化表格
         for(int i = 0 ; i < ui->table_calibrateCoordinate->rowCount(); i++)
         {
             ui->table_calibrateCoordinate->item(i, 1)->setFlags(Qt::NoItemFlags);//第一列不允许修改
         }
    }
}


void MainWindow::on_btn_toolConfirm_clicked()
{
    ui->lab_algorithmImage->setElementIndex(Default_DM);
//    ui->lab_algorithmImage->setElementType(true);
    ui->lab_calibrateImage->setElementIndex(Default_DM);
//    ui->lab_algorithmImage->setElementType(true);

    //切换参数说明界面
    if(this->currentToolList == QStringLiteral("相机"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_cameraSetting);
        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能


        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
    }
    else if(this->currentToolList == QStringLiteral("通信"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_modbusSetting);
        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
    }
//    else if(this->currentToolList == QStringLiteral("标定")||
//            this->currentToolList == QStringLiteral("①标定板"))
//    {
//        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
//        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
//        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
//        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
//    }
    else if(this->currentToolList == QStringLiteral("方形棋盘格"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->chessbordPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_FEATUREMATCH_Tag;
        //this->calibrateFindFeature();
    }
    else if(this->currentToolList == QStringLiteral("圆形棋盘格"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->calibrate_dotPlatePara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_FINDCIRCLE_Tag;
        //this->calibrateFindFeature();
    }
    else if(this->currentToolList == QStringLiteral("圆(框选)"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->defalutPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动执行功能
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        ui->lab_calibrateImage->setElementIndex(Ring_ELMT);//绘制圆
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_FINDCIRCLE_HAND_Tag;
    }
    else if(this->currentToolList == QStringLiteral("②映射矩阵"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->defalutPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//隐藏撤销功能
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        //this->calibrateConfirm();
    }
    //选择算法
    else if(this->currentToolList == QStringLiteral("图像取反"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->defalutPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_IMGNOT_Tag;
    }
    else if(this->currentToolList == QStringLiteral("常规二值化"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->threasholdPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_GENERAL_Tag;
    }
    else if(this->currentToolList == QStringLiteral("常规_反向二值化"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->threasholdPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_GENERAL_INV_Tag;
    }
    else if(this->currentToolList == QStringLiteral("OTSU"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->threasholdPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_OTSU_Tag;
    }
    else if(this->currentToolList == QStringLiteral("分块二值化"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->zoningThreasholdPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_THRESHOLD_ADAPTIVE_Tag;
    }
    else if(this->currentToolList ==  QStringLiteral("均值滤波"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->blurPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MEANBLUR_Tag;
        ui->blurKernelH->setEnabled(true);
        ui->blurKernelW->setEnabled(true);
        ui->blur_sigmaColor->setEnabled(false);
        ui->blur_sigmaSpace->setEnabled(false);
    }
    else if(this->currentToolList ==  QStringLiteral("高斯滤波"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->blurPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_GAUSSIANBLUR_Tag;
        ui->blurKernelH->setEnabled(true);
        ui->blurKernelW->setEnabled(true);
        ui->blur_sigmaColor->setEnabled(false);
        ui->blur_sigmaSpace->setEnabled(false);
    }
    else if(this->currentToolList ==  QStringLiteral("中值滤波"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->blurPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MEDIANDMFILTER_Tag;
        ui->blurKernelH->setEnabled(true);
        ui->blurKernelW->setEnabled(true);
        ui->blur_sigmaColor->setEnabled(false);
        ui->blur_sigmaSpace->setEnabled(false);
    }
    else if(this->currentToolList ==  QStringLiteral("双边滤波"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->blurPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_BILATERALFILTER_Tag;
        ui->blurKernelH->setEnabled(false);
        ui->blurKernelW->setEnabled(false);
        ui->blur_sigmaColor->setEnabled(true);
        ui->blur_sigmaSpace->setEnabled(true);
    }
    else if(this->currentToolList == QStringLiteral("膨胀"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->morphologyPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MORPHOLOGY_DILATE_Tag;
    }
    else if(this->currentToolList == QStringLiteral("腐蚀"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->morphologyPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MORPHOLOGY_ERODE_Tag;
    }
    else if(this->currentToolList == QStringLiteral("开"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->morphologyPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MORPHOLOGY_OPEN_Tag;
    }
    else if(this->currentToolList == QStringLiteral("闭"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->morphologyPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MORPHOLOGY_CLOSE_Tag;
    }
    else if(this->currentToolList == QStringLiteral("形态学梯度"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->morphologyPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MORPHOLOGY_GRADIENT_Tag;
    }
    else if(this->currentToolList == QStringLiteral("顶帽"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->morphologyPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MORPHOLOGY_TOPHAT_Tag;
    }
    else if(this->currentToolList == QStringLiteral("黑帽"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->morphologyPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MORPHOLOGY_BLACKHAT_Tag;
    }
    else if(this->currentToolList == QStringLiteral("查找轮廓"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->contourPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_CONTOURS_Tag;
    }
    else if(this->currentToolList == QStringLiteral("质心"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->defalutPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MOMENTS_Tag;
    }
    else if(this->currentToolList == QStringLiteral("查找霍夫圆"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->houghPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_HOUGHCIRCLE_Tag;
    }
    else if (this->currentToolList == QStringLiteral("查找圆"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->findCirclePara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_FINDCIRCLE_Tag;
    }
    else if(this->currentToolList == QStringLiteral("方形棋盘格特征点"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->chessbordPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_CHESSBOARDCALIBRATION_Tag;
    }
    else if(this->currentToolList == QStringLiteral("模板匹配"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->tempmatchPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        ui->lab_algorithmImage->setElementIndex(Rect_ELMT);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_MATCHTEMPLATE_Tag;
        ui->similarityCoefficient->setEnabled(true);
    }
    else if(this->currentToolList == QStringLiteral("轮廓匹配"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->tempmatchPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        ui->lab_algorithmImage->setElementIndex(Rect_ELMT);
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_CONTOURSMATCH_Tag;
        ui->similarityCoefficient->setEnabled(true);
    }
    else if(this->currentToolList == QStringLiteral("特征点匹配"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->tempmatchPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_FEATUREMATCH_Tag;
        ui->similarityCoefficient->setEnabled(false);
    }
    else if(this->currentToolList == QStringLiteral("相机坐标系->机器臂坐标系"))
    {
        ui->SWidget_information->setCurrentWidget(ui->page_paraSetting);//将界面切换到参数说明界面
        ui->SWidget_paraSetting->setCurrentWidget(ui->defalutPara);
        ui->btn_AlgorithmExcute->setVisible(true);//启动算法执行
        ui->btn_AlgorithmRevocation->setVisible(true);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_COORDINATE_Tag;
    }
    else
    {
        //ui->SWidget_paraSetting->setCurrentWidget(ui->defalutPara);
        ui->btn_AlgorithmExcute->setVisible(false);//隐藏执行功能
        ui->btn_AlgorithmRevocation->setVisible(false);//启动撤销功能
        this->imgCalibrateType = DM_IMGPROCESS_DEFAULT_Tag;
        this->imgAlgorithmType = DM_IMGPROCESS_DEFAULT_Tag;
    }
}

void MainWindow::on_btn_AlgorithmRevocation_clicked()//撤销撤销算法
{
	if (this->systemFunc == SystemFunction_Calibrate)//实际上只有手动框选标准圆的ROI才能会有撤销这一功能
	{
		this->calibrateFlag = false;//一旦点击撤销按钮，系统标定状态就变成为标定
		this->proStatus[3] = QStringLiteral("未标定");//②工程名
		ui->statusBar->showMessage(this->proStatus[0] +
								   this->proStatus[1] +
								   this->proStatus[2] +
								   this->proStatus[3]);
		this->deleteImgCalibrateAlgorithm();
	}
	else if (this->systemFunc == SystemFunction_Algorithm)
	{
		this->deleteImgProcess();
	}
    
}

void MainWindow::on_btn_AlgorithmExcute_clicked()
{
    if(this->currentToolList == QStringLiteral("方形棋盘格"))
    {
		this->calibrateFindFeature_chessboard();
    }
	else if (this->currentToolList == QStringLiteral("圆形棋盘格"))
	{
		this->calibrateFindFeature_circle();
	}
	else if (this->currentToolList == QStringLiteral("圆(框选)"))
	{
		this->calibrateFindFeatrue_circle_hand();
	}
    else if(this->currentToolList == QStringLiteral("②映射矩阵"))
    {
        this->calibrateConfirm();
    }
    //必须先标定成功了才能进行相应的算法操作，否则所有的算法不能执行
    else
    {
        if (this->calibrateFlag)
        {
            switch (this->imgAlgorithmType)
            {
                //二值化
                case DM_THRESHOLD_GENERAL_Tag:
                case DM_THRESHOLD_GENERAL_INV_Tag:
                case DM_THRESHOLD_OTSU_Tag:
                case DM_THRESHOLD_ADAPTIVE_Tag:
                {
                    double thresh = ui->threashold_Box->value();
                    int blockSize = ui->blockSize_Box->value();//这个必须为奇数

                    int w = this->locationImg_original.rows > this->locationImg_original.cols ?
                            this->locationImg_original.cols : this->locationImg_original.rows;

                    blockSize = blockSize < 3 ? 3: blockSize;
                    blockSize = blockSize > w ? w: blockSize;
                    blockSize = (blockSize % 2 == 0)? (blockSize-1):blockSize;//block必须为奇数
                    DM_ImageProcessBase *func = new DM_Threshold(this->imgAlgorithmType, thresh, 255, blockSize);
                    this->addImgProcess(func);
                    break;
                }
                case DM_MEANBLUR_Tag :
                case DM_GAUSSIANBLUR_Tag :
                case DM_MEDIANDMFILTER_Tag :
                case DM_BILATERALFILTER_Tag :
                {
                    cv::Size  kernelSize= cv::Size(ui->blurKernelW->value(),ui->blurKernelH->value());//这个必须为奇数
                    DM_ImageProcessBase *func = new DM_Blur(this->imgAlgorithmType,kernelSize,
                                                            ui->blur_sigmaColor->value(),
                                                            ui->blur_sigmaSpace->value());
                    this->addImgProcess(func);
                    break;
                }
                case DM_MORPHOLOGY_DILATE_Tag :
                case DM_MORPHOLOGY_ERODE_Tag :
                case DM_MORPHOLOGY_OPEN_Tag :
                case DM_MORPHOLOGY_CLOSE_Tag :
                case DM_MORPHOLOGY_GRADIENT_Tag:
                case DM_MORPHOLOGY_TOPHAT_Tag :
                case DM_MORPHOLOGY_BLACKHAT_Tag:
                {
                    cv::Size  kernelSize= cv::Size(ui->morphologyKernelW->value(),ui->morphologyKernelH->value());//这个必须为奇数
                    DM_ImageProcessBase *func = new DM_Morphology(this->imgAlgorithmType,kernelSize);
                    this->addImgProcess(func);
                    break;
                }
                case DM_CONTOURS_Tag://轮廓
                {
                    double maxArea = ui->maxArea_Box->value();
                    double minArea = ui->minArea_Box->value();
                    DM_ImageProcessBase *func = new DM_FindContours(minArea, maxArea);
                    this->addImgProcess(func);
                    break;
                }
                case  DM_MOMENTS_Tag://图像的矩
                {
                    if ( this->imgProcess.size() > 1 &&
                         this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CONTOURS_Tag)
                    {
                        DM_FindContours *func = dynamic_cast<DM_FindContours*>(this->imgProcess[this->imgProcess.size() - 1]);
                        std::vector<std::vector<cv::Point> > contours_ = func->contours;
                        DM_Moment *func_moment = new DM_Moment(contours_);
                        this->addImgProcess(func_moment);
                    }
                    else
                    {
                        this->message += QStringLiteral("#>>>请先查找轮廓,才能进行“图像矩”相关算法\n");
                    }
                    break;
                }
                case DM_COORDINATE_Tag://坐标转化
                {
                    if (this->imgProcess.size() >= 1 &&
                        this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_MOMENTS_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else if (this->imgProcess.size() >= 1 &&
                        this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CONTOURS_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else if (this->imgProcess.size() >= 1 &&
                             this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CHESSBOARDCALIBRATION_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else if (this->imgProcess.size() >= 1 &&
                             this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_HOUGHCIRCLE_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else if (this->imgProcess.size() >= 1 &&
                        this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_FINDCIRCLE_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else if (this->imgProcess.size() >= 1 &&
                        this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_MATCHTEMPLATE_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else if (this->imgProcess.size() >= 1 &&
                        this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_FEATUREMATCH_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else if (this->imgProcess.size() >= 1 &&
                             this->imgProcess[this->imgProcess.size() - 1]->getImgProcessMethod() == DM_CONTOURSMATCH_Tag)
                    {
                        DM_CoordinateTransform *func_coord = new DM_CoordinateTransform(this->transformMatrix);
                        this->addImgProcess(func_coord);
                    }
                    else
                    {
                        this->message += QStringLiteral("#>>>请先计算特征点的坐标(例如：调用“图像的矩-质心”算法)!\n");
                    }

                    //========================保存算法文件=====================================

                    if(this->imgProcess[this->imgProcess.size()-1]->getImgProcessMethod() == DM_COORDINATE_Tag &&
                       this->imgProcess[this->imgProcess.size()-1]->getErrorID() == DM_error_no)
                    {
                        QMessageBox::StandardButton result = QMessageBox::information(NULL, QStringLiteral("提示"),
                                     QStringLiteral("是否保存算法?"), QMessageBox::Yes | QMessageBox::No);
                        if(result == QMessageBox::Yes)
                        {
                            //this->saveAsProject();
                            this->saveAlgorithms(this->imgProcess, this->projectPath+"/"+this->projectName+"/Algorithm.gp");//保存算法文件
                        }
                    }
                    break;
                }
                case DM_CHESSBOARDCALIBRATION_Tag://棋盘格查找
                {
                    DM_ChessBoardCalibration *func = new DM_ChessBoardCalibration(cv::Size(ui->chessBoardCols->value(),ui->chessBoardRows->value()));
                    this->addImgProcess(func);
                    break;
                }
                case DM_HOUGHCIRCLE_Tag://霍夫圆
                {
                    DM_HoughCircle *func = new DM_HoughCircle(ui->hough_minDist->value(),
                                                              ui->hough_cannyThreshold->value(),
                                                              ui->hough_countThreshold->value(),
                                                              ui->hough_minRadius->value(),
                                                              ui->hough_maxRadius->value());
                    this->addImgProcess(func);
                    break;
                }
                case DM_FINDCIRCLE_Tag:
                {
                    DM_FindCircle *func = new DM_FindCircle(ui->findCircle_binaryThreshold->value(),
                                                            ui->findCircle_countThreshold->value(),
                                                            ui->findCircle_minRadius->value(),
                                                            ui->findCircle_maxRadius->value(),
                                                            ui->findCircle_percent->value(),
                                                            ui->findCircle_deviation->value());
                    this->addImgProcess(func);
                    break;
                }
                case DM_MATCHTEMPLATE_Tag://图像匹配
                {
                    if(this->tempImg.empty())
                    {
                        this->message += QStringLiteral("#>>>模板为空，请先框选模板!\n");
                    }
                    else
                    {
                        DM_MatchTemplate *func = new DM_MatchTemplate(this->tempImg[this->tempImg.size()-1],
                            ui->similarityCoefficient->value(),
                            this->tempDrapPoints[this->tempDrapPoints.size()-1]);
                        this->addImgProcess(func);
                    }
                    break;
                }
                case  DM_FEATUREMATCH_Tag://特征点匹配
                {
                    if (this->tempImg.empty())
                    {
                        this->message += QStringLiteral("#>>>模板为空，请先框选模板!\n");
                    }
                    else
                    {
                        DM_FeatureMatch_SIFT *func = new DM_FeatureMatch_SIFT(this->tempImg[this->tempImg.size() - 1],1.0,
                            this->tempDrapPoints[this->tempDrapPoints.size() - 1]);
                        this->addImgProcess(func);
                    }
                    break;
                }
                case  DM_CONTOURSMATCH_Tag://轮廓匹配
                {
                    if (this->tempContours.empty())
                    {
                        this->message += QStringLiteral("#>>>模板为空，请先框选模板!\n");
                    }
                    else
                    {
                        DM_ContoursMatch *func = new DM_ContoursMatch(this->tempContours, ui->similarityCoefficient->value());
                        func->setTemplate(this->tempImg);
                        func->setTemplateGrabPoint(this->tempDrapPoints);
                        this->addImgProcess(func);
                    }
                    break;
                }
                case  DM_IMGNOT_Tag://轮廓匹配
                {

                    DM_ImgNot *func = new DM_ImgNot();
                    this->addImgProcess(func);
                    break;
                }
                default:
                {
                    this->message += QStringLiteral("#>>>请选择恰当的算法!\n");
                    break;
                }
            }
        }
        else
        {
            this->message += QStringLiteral("#>>>请标定，才能执行后续算法\n");
        }
    }

    ui->systemStatusBar->setText(this->message);//显示运行状态
    ui->systemStatusBar->moveCursor(QTextCursor::End);
}


void MainWindow::on_btn_saveCameraImagePath_clicked()
{
    QString path = QFileDialog::getExistingDirectory(
                this, "choose src Directory",
                 "/");
    ui->saveCameraImagePathlineEdit->setText(path);
}

void MainWindow::on_btn_connectCamera_clicked()
{
    this->connectCameraParameters();
}
