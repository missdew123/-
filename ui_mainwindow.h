/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <dm_label.h>
#include <dm_projector.h>
#include "dm_slider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_LoadProject;
    QAction *action_NewProject;
    QAction *action_SaveProject;
    QAction *action_LoadImg;
    QAction *action_cameraStart;
    QAction *action_cameraStop;
    QAction *action_imageZoomIn;
    QAction *action_imageZoomOut;
    QAction *action_ImageFitScreen;
    QAction *action_takePicture;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_5;
    QSplitter *splitter_3;
    QStackedWidget *SWidget_image;
    QWidget *page_algorithmImage;
    QGridLayout *gridLayout_7;
    QSplitter *splitter_2;
    DM_Projector *Projector;
    QToolButton *btn_ProjFirst;
    QToolButton *btn_ProjNext;
    QToolButton *btn_ProjPrev;
    QToolButton *btn_ProjFinal;
    QToolButton *btn_ProjPlay;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_9;
    QWidget *widget_algorithmImage;
    DM_Label *lab_algorithmImage;
    QScrollBar *algorithmImageHBar;
    QLabel *algorithmImageInfo;
    QScrollBar *algorithmImageVBar;
    QWidget *page_calibrateImage;
    QGridLayout *gridLayout_14;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_calibrateLabel;
    DM_Label *lab_calibrateImage;
    QScrollBar *calibrateImageHBar;
    QLabel *calibrateImageInfo;
    QScrollBar *calibrateImageVBar;
    QWidget *page_cameraVideo;
    QGridLayout *gridLayout_22;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_19;
    QWidget *widget_cameraVideo;
    DM_Label *lab_cameraVideo;
    QScrollBar *cameraVideoHBar;
    QLabel *cameraVideoInfo;
    QScrollBar *cameraVideoVBar;
    QGroupBox *groupBox_16;
    QGridLayout *gridLayout_10;
    QStackedWidget *SWidget_coordinate;
    QWidget *page_algorithmCoordinate;
    QVBoxLayout *verticalLayout_6;
    QTableWidget *table_algorithmCoordinate;
    QWidget *page_calibrateCoordinate;
    QVBoxLayout *verticalLayout_11;
    QTableWidget *table_calibrateCoordinate;
    QGroupBox *groupBox_17;
    QGridLayout *gridLayout_11;
    QStackedWidget *SWidget_table;
    QWidget *page_calibrate;
    QVBoxLayout *verticalLayout_25;
    QTableWidget *table_systemCalibrate;
    QWidget *page_algorithm;
    QVBoxLayout *verticalLayout_30;
    QTableWidget *table_preprocessAlgorithm;
    QSplitter *splitter_4;
    QStackedWidget *SWidget_toolsDirectory;
    QWidget *page_toolList;
    QGridLayout *gridLayout_21;
    QGroupBox *groupBox_15;
    QVBoxLayout *verticalLayout;
    QTreeWidget *TWidget_toolList;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_toolConfirm;
    QPushButton *btn_AlgorithmExcute;
    QPushButton *btn_AlgorithmRevocation;
    QSplitter *splitter;
    QStackedWidget *SWidget_information;
    QWidget *page_paraInformation;
    QGridLayout *gridLayout_20;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_19;
    QStackedWidget *SWidget_paraInformation;
    QWidget *defalutInfo;
    QWidget *threasholdInfo;
    QGridLayout *gridLayout_31;
    QTextBrowser *textBrowser_20;
    QWidget *zoningThreasholdInfo;
    QGridLayout *gridLayout_30;
    QTextBrowser *textBrowser_21;
    QWidget *blurInfo;
    QVBoxLayout *verticalLayout_8;
    QTextBrowser *textBrowser_7;
    QWidget *morphologyInfo;
    QVBoxLayout *verticalLayout_7;
    QTextBrowser *textBrowser_9;
    QWidget *contourInfo;
    QVBoxLayout *verticalLayout_12;
    QTextBrowser *textBrowser_6;
    QWidget *houghInfo;
    QHBoxLayout *horizontalLayout_7;
    QTextBrowser *textBrowser_4;
    QWidget *findCircleInfo;
    QHBoxLayout *horizontalLayout_18;
    QTextBrowser *textBrowser_8;
    QWidget *tempmatchInfo;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *textBrowser_5;
    QWidget *chessbordInfo;
    QGridLayout *gridLayout_8;
    QTextBrowser *textBrowser_11;
    QWidget *imgNotInfo;
    QGridLayout *gridLayout_28;
    QTextBrowser *textBrowser_12;
    QWidget *momentInfo;
    QGridLayout *gridLayout_29;
    QTextBrowser *textBrowser_15;
    QWidget *modbusInfo;
    QGridLayout *gridLayout_12;
    QTextBrowser *textBrowser_13;
    QWidget *calibrate_dotPlateInfo;
    QGridLayout *gridLayout_13;
    QTextBrowser *textBrowser_3;
    QWidget *cameraInfo;
    QGridLayout *gridLayout_26;
    QTextBrowser *textBrowser_18;
    QWidget *calibrationInfo;
    QGridLayout *gridLayout_25;
    QTextBrowser *textBrowser_19;
    QWidget *calibrate_mappingMatrixInfo;
    QGridLayout *gridLayout_33;
    QTextBrowser *textBrowser_22;
    QWidget *calibrate_calibrationPlateInfo;
    QGridLayout *gridLayout_32;
    QTextBrowser *textBrowser_23;
    QWidget *algorithmInfo;
    QGridLayout *gridLayout_34;
    QTextBrowser *textBrowser_24;
    QWidget *calibrate_findCirclehandInfo;
    QGridLayout *gridLayout_3;
    QTextBrowser *textBrowser_25;
    QWidget *page_paraSetting;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *groupBox_18;
    QVBoxLayout *verticalLayout_22;
    QSplitter *splitter_6;
    QStackedWidget *SWidget_paraSetting;
    QWidget *defalutPara;
    QWidget *threasholdPara;
    QVBoxLayout *verticalLayout_32;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_81;
    QSpinBox *threashold_Box;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *verticalSpacer_20;
    QWidget *zoningThreasholdPara;
    QVBoxLayout *verticalLayout_33;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_82;
    QSpinBox *blockSize_Box;
    QSpacerItem *horizontalSpacer_24;
    QSpacerItem *verticalSpacer_21;
    QWidget *blurPara;
    QVBoxLayout *verticalLayout_34;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_83;
    QSpinBox *blurKernelW;
    QLabel *label_84;
    QSpinBox *blurKernelH;
    QSpacerItem *horizontalSpacer_26;
    QHBoxLayout *horizontalLayout_46;
    QLabel *label_85;
    QDoubleSpinBox *blur_sigmaColor;
    QLabel *label_86;
    QDoubleSpinBox *blur_sigmaSpace;
    QSpacerItem *horizontalSpacer_25;
    QSpacerItem *verticalSpacer_25;
    QWidget *morphologyPara;
    QVBoxLayout *verticalLayout_35;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_87;
    QSpinBox *morphologyKernelW;
    QLabel *label_88;
    QSpinBox *morphologyKernelH;
    QSpacerItem *horizontalSpacer_27;
    QSpacerItem *verticalSpacer_26;
    QWidget *contourPara;
    QVBoxLayout *verticalLayout_36;
    QHBoxLayout *horizontalLayout_49;
    QLabel *label_89;
    QSpinBox *maxArea_Box;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_52;
    QLabel *label_90;
    QSpinBox *minArea_Box;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_22;
    QWidget *houghPara;
    QHBoxLayout *horizontalLayout_55;
    QGridLayout *gridLayout_16;
    QLabel *label_91;
    QDoubleSpinBox *hough_minDist;
    QLabel *label_92;
    QLabel *label_93;
    QSpinBox *hough_minRadius;
    QLabel *label_94;
    QDoubleSpinBox *hough_cannyThreshold;
    QLabel *label_95;
    QDoubleSpinBox *hough_countThreshold;
    QSpinBox *hough_maxRadius;
    QSpacerItem *horizontalSpacer_6;
    QWidget *findCirclePara;
    QHBoxLayout *horizontalLayout_56;
    QGridLayout *gridLayout_17;
    QLabel *label_96;
    QDoubleSpinBox *findCircle_percent;
    QDoubleSpinBox *findCircle_binaryThreshold;
    QLabel *label_97;
    QDoubleSpinBox *findCircle_countThreshold;
    QSpinBox *findCircle_maxRadius;
    QSpinBox *findCircle_deviation;
    QLabel *label_98;
    QLabel *label_99;
    QLabel *label_100;
    QLabel *label_101;
    QSpinBox *findCircle_minRadius;
    QSpacerItem *horizontalSpacer_17;
    QWidget *chessbordPara;
    QGridLayout *gridLayout_18;
    QLabel *label_102;
    QSpinBox *chessBoardCols;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label_103;
    QSpinBox *chessBoardRows;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *verticalSpacer_23;
    QWidget *calibrate_dotPlatePara;
    QHBoxLayout *horizontalLayout_12;
    QGridLayout *gridLayout_5;
    QLabel *label_13;
    QLabel *label_11;
    QDoubleSpinBox *dotPlate_countThreshold;
    QDoubleSpinBox *dotPlate_percent;
    QDoubleSpinBox *dotPlate_binaryThreshold;
    QLabel *label_12;
    QLabel *label;
    QSpinBox *dotPlate_deviation;
    QSpinBox *dotPlate_maxRadius;
    QLabel *label_14;
    QLabel *label_15;
    QSpinBox *dotPlate_minRadius;
    QSpacerItem *horizontalSpacer_18;
    QWidget *tempmatchPara;
    QGridLayout *gridLayout_24;
    QGridLayout *gridLayout_23;
    QVBoxLayout *verticalLayout_28;
    QVBoxLayout *verticalLayout_27;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_104;
    QDoubleSpinBox *similarityCoefficient;
    QSpacerItem *horizontalSpacer_22;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *btn_addTemp;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *verticalSpacer_15;
    QVBoxLayout *verticalLayout_29;
    QWidget *widget_algorithmnTemp;
    DM_Label *lab_algorithmnTemp;
    QSpacerItem *verticalSpacer_16;
    QWidget *page_modbusSetting;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_20;
    QGridLayout *gridLayout_15;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_28;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_3;
    QLabel *label_40;
    QLabel *label_45;
    QLabel *label_36;
    QLabel *label_47;
    QVBoxLayout *verticalLayout_21;
    QLineEdit *modbusIP;
    QComboBox *modbusDataType;
    QHBoxLayout *horizontalLayout_19;
    QSpinBox *modbusScanTime;
    QLabel *label_44;
    QHBoxLayout *horizontalLayout_27;
    QSpinBox *modbusTimeOut;
    QLabel *label_46;
    QSpinBox *modbusRetries;
    QVBoxLayout *verticalLayout_65;
    QHBoxLayout *horizontalLayout_32;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *btn_modbusConnect;
    QHBoxLayout *horizontalLayout_37;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *btn_modbusTest;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *verticalSpacer_17;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_40;
    QHBoxLayout *horizontalLayout_25;
    QVBoxLayout *verticalLayout_41;
    QLabel *label_5;
    QLabel *label_55;
    QLabel *label_57;
    QLabel *label_58;
    QLabel *label_59;
    QLabel *label_139;
    QVBoxLayout *verticalLayout_66;
    QSpinBox *modbusPort_R;
    QSpinBox *modbusSeverID_R;
    QSpinBox *modbusStartRegister_R;
    QSpinBox *modbusNumData_R;
    QLabel *modbusStatus_R;
    QToolButton *btn_modbusclose_R;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout_42;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_24;
    QLineEdit *lineEdit_25;
    QVBoxLayout *verticalLayout_43;
    QLineEdit *lineEdit_12;
    QDoubleSpinBox *modbusReadData0;
    QDoubleSpinBox *modbusReadData1;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_31;
    QHBoxLayout *horizontalLayout_23;
    QVBoxLayout *verticalLayout_63;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *label_37;
    QLabel *label_38;
    QLabel *label_56;
    QVBoxLayout *verticalLayout_64;
    QSpinBox *modbusPort_W;
    QSpinBox *modbusSeverID_W;
    QSpinBox *modbusStartRegister_W;
    QSpinBox *modbusNumData_W;
    QLabel *modbusStatus_W;
    QHBoxLayout *horizontalLayout_22;
    QVBoxLayout *verticalLayout_14;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_20;
    QLineEdit *lineEdit_21;
    QVBoxLayout *verticalLayout_15;
    QLineEdit *lineEdit_7;
    QDoubleSpinBox *modbusWriteData0;
    QDoubleSpinBox *modbusWriteData1;
    QSpacerItem *verticalSpacer_14;
    QWidget *page_cameraSetting;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QComboBox *comB_cameraBrand;
    QPushButton *btn_connectCamera;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_48;
    DM_Slider *cameraExposureSlider;
    QHBoxLayout *horizontalLayout_48;
    QLabel *label_49;
    QDoubleSpinBox *cameraFrameRate;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_50;
    QLabel *label_50;
    QComboBox *camareTriggerType;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBox_14;
    QVBoxLayout *verticalLayout_18;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_54;
    QLabel *label_52;
    QLineEdit *saveCameraImagePathlineEdit;
    QToolButton *btn_saveCameraImagePath;
    QHBoxLayout *horizontalLayout_51;
    QLabel *label_51;
    QToolButton *btn_autosaveImage;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *verticalSpacer_6;
    QTextBrowser *systemStatusBar;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_help;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1235, 723);
        action_LoadProject = new QAction(MainWindow);
        action_LoadProject->setObjectName(QStringLiteral("action_LoadProject"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/img/icon/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_LoadProject->setIcon(icon);
        action_NewProject = new QAction(MainWindow);
        action_NewProject->setObjectName(QStringLiteral("action_NewProject"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/img/icon/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_NewProject->setIcon(icon1);
        action_SaveProject = new QAction(MainWindow);
        action_SaveProject->setObjectName(QStringLiteral("action_SaveProject"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/img/icon/svae.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_SaveProject->setIcon(icon2);
        action_LoadImg = new QAction(MainWindow);
        action_LoadImg->setObjectName(QStringLiteral("action_LoadImg"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/img/icon/LoadIMg.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_LoadImg->setIcon(icon3);
        action_cameraStart = new QAction(MainWindow);
        action_cameraStart->setObjectName(QStringLiteral("action_cameraStart"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/img/icon/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_cameraStart->setIcon(icon4);
        action_cameraStop = new QAction(MainWindow);
        action_cameraStop->setObjectName(QStringLiteral("action_cameraStop"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/img/icon/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_cameraStop->setIcon(icon5);
        action_imageZoomIn = new QAction(MainWindow);
        action_imageZoomIn->setObjectName(QStringLiteral("action_imageZoomIn"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/img/icon/zoomIn.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_imageZoomIn->setIcon(icon6);
        action_imageZoomOut = new QAction(MainWindow);
        action_imageZoomOut->setObjectName(QStringLiteral("action_imageZoomOut"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/img/icon/zoomOut.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_imageZoomOut->setIcon(icon7);
        action_ImageFitScreen = new QAction(MainWindow);
        action_ImageFitScreen->setObjectName(QStringLiteral("action_ImageFitScreen"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icon/img/icon/fit.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_ImageFitScreen->setIcon(icon8);
        action_takePicture = new QAction(MainWindow);
        action_takePicture->setObjectName(QStringLiteral("action_takePicture"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icon/img/icon/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_takePicture->setIcon(icon9);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_5 = new QSplitter(centralWidget);
        splitter_5->setObjectName(QStringLiteral("splitter_5"));
        splitter_5->setOrientation(Qt::Vertical);
        splitter_3 = new QSplitter(splitter_5);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter_3->setChildrenCollapsible(false);
        SWidget_image = new QStackedWidget(splitter_3);
        SWidget_image->setObjectName(QStringLiteral("SWidget_image"));
        SWidget_image->setMinimumSize(QSize(200, 200));
        SWidget_image->setFrameShape(QFrame::Box);
        page_algorithmImage = new QWidget();
        page_algorithmImage->setObjectName(QStringLiteral("page_algorithmImage"));
        gridLayout_7 = new QGridLayout(page_algorithmImage);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        splitter_2 = new QSplitter(page_algorithmImage);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setHandleWidth(0);
        splitter_2->setChildrenCollapsible(false);
        Projector = new DM_Projector(splitter_2);
        Projector->setObjectName(QStringLiteral("Projector"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Projector->sizePolicy().hasHeightForWidth());
        Projector->setSizePolicy(sizePolicy1);
        Projector->setMinimumSize(QSize(50, 0));
        Projector->setMaximumSize(QSize(200, 16777215));
        btn_ProjFirst = new QToolButton(Projector);
        btn_ProjFirst->setObjectName(QStringLiteral("btn_ProjFirst"));
        btn_ProjFirst->setGeometry(QRect(50, 130, 23, 22));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icon/img/icon/PlayFirst.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_ProjFirst->setIcon(icon10);
        btn_ProjNext = new QToolButton(Projector);
        btn_ProjNext->setObjectName(QStringLiteral("btn_ProjNext"));
        btn_ProjNext->setGeometry(QRect(50, 110, 23, 22));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icon/img/icon/PlayNext.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_ProjNext->setIcon(icon11);
        btn_ProjPrev = new QToolButton(Projector);
        btn_ProjPrev->setObjectName(QStringLiteral("btn_ProjPrev"));
        btn_ProjPrev->setGeometry(QRect(50, 50, 23, 22));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icon/img/icon/PlayPrevious.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_ProjPrev->setIcon(icon12);
        btn_ProjFinal = new QToolButton(Projector);
        btn_ProjFinal->setObjectName(QStringLiteral("btn_ProjFinal"));
        btn_ProjFinal->setGeometry(QRect(50, 70, 23, 22));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icon/img/icon/PlayFinal.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_ProjFinal->setIcon(icon13);
        btn_ProjPlay = new QToolButton(Projector);
        btn_ProjPlay->setObjectName(QStringLiteral("btn_ProjPlay"));
        btn_ProjPlay->setGeometry(QRect(50, 90, 23, 22));
        btn_ProjPlay->setAcceptDrops(false);
        btn_ProjPlay->setAutoFillBackground(false);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icon/img/icon/PlayFilm.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_ProjPlay->setIcon(icon14);
        btn_ProjPlay->setAutoRepeat(false);
        btn_ProjPlay->setAutoExclusive(false);
        splitter_2->addWidget(Projector);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        widget_algorithmImage = new QWidget(layoutWidget);
        widget_algorithmImage->setObjectName(QStringLiteral("widget_algorithmImage"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_algorithmImage->sizePolicy().hasHeightForWidth());
        widget_algorithmImage->setSizePolicy(sizePolicy2);
        widget_algorithmImage->setMinimumSize(QSize(200, 200));
        lab_algorithmImage = new DM_Label(widget_algorithmImage);
        lab_algorithmImage->setObjectName(QStringLiteral("lab_algorithmImage"));
        lab_algorithmImage->setGeometry(QRect(2, 2, 171, 131));
        lab_algorithmImage->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(80, 80, 80, 255));"));
        lab_algorithmImage->setFrameShape(QFrame::Box);
        lab_algorithmImage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_9->addWidget(widget_algorithmImage);

        algorithmImageHBar = new QScrollBar(layoutWidget);
        algorithmImageHBar->setObjectName(QStringLiteral("algorithmImageHBar"));
        algorithmImageHBar->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));"));
        algorithmImageHBar->setOrientation(Qt::Horizontal);

        verticalLayout_9->addWidget(algorithmImageHBar);

        algorithmImageInfo = new QLabel(layoutWidget);
        algorithmImageInfo->setObjectName(QStringLiteral("algorithmImageInfo"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(algorithmImageInfo->sizePolicy().hasHeightForWidth());
        algorithmImageInfo->setSizePolicy(sizePolicy3);
        algorithmImageInfo->setMinimumSize(QSize(0, 20));
        algorithmImageInfo->setMaximumSize(QSize(16777215, 20));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QLinearGradient gradient(0, 0, 0, 0.5);
        gradient.setSpread(QGradient::ReflectSpread);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setColorAt(0, QColor(40, 40, 40, 255));
        gradient.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush1(gradient);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QLinearGradient gradient1(0, 0, 0, 0.5);
        gradient1.setSpread(QGradient::ReflectSpread);
        gradient1.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient1.setColorAt(0, QColor(40, 40, 40, 255));
        gradient1.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush2(gradient1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        QLinearGradient gradient2(0, 0, 0, 0.5);
        gradient2.setSpread(QGradient::ReflectSpread);
        gradient2.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient2.setColorAt(0, QColor(40, 40, 40, 255));
        gradient2.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush3(gradient2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QLinearGradient gradient3(0, 0, 0, 0.5);
        gradient3.setSpread(QGradient::ReflectSpread);
        gradient3.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient3.setColorAt(0, QColor(40, 40, 40, 255));
        gradient3.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush4(gradient3);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QLinearGradient gradient4(0, 0, 0, 0.5);
        gradient4.setSpread(QGradient::ReflectSpread);
        gradient4.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient4.setColorAt(0, QColor(40, 40, 40, 255));
        gradient4.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush5(gradient4);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        QLinearGradient gradient5(0, 0, 0, 0.5);
        gradient5.setSpread(QGradient::ReflectSpread);
        gradient5.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient5.setColorAt(0, QColor(40, 40, 40, 255));
        gradient5.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush6(gradient5);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        QLinearGradient gradient6(0, 0, 0, 0.5);
        gradient6.setSpread(QGradient::ReflectSpread);
        gradient6.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient6.setColorAt(0, QColor(40, 40, 40, 255));
        gradient6.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush7(gradient6);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        QLinearGradient gradient7(0, 0, 0, 0.5);
        gradient7.setSpread(QGradient::ReflectSpread);
        gradient7.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient7.setColorAt(0, QColor(40, 40, 40, 255));
        gradient7.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush8(gradient7);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        QLinearGradient gradient8(0, 0, 0, 0.5);
        gradient8.setSpread(QGradient::ReflectSpread);
        gradient8.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient8.setColorAt(0, QColor(40, 40, 40, 255));
        gradient8.setColorAt(1, QColor(110, 110, 110, 255));
        QBrush brush9(gradient8);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        algorithmImageInfo->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font.setPointSize(12);
        algorithmImageInfo->setFont(font);
        algorithmImageInfo->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));\n"
"color: rgb(255, 255, 255);"));
        algorithmImageInfo->setFrameShape(QFrame::Box);

        verticalLayout_9->addWidget(algorithmImageInfo);


        horizontalLayout_3->addLayout(verticalLayout_9);

        algorithmImageVBar = new QScrollBar(layoutWidget);
        algorithmImageVBar->setObjectName(QStringLiteral("algorithmImageVBar"));
        algorithmImageVBar->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));"));
        algorithmImageVBar->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(algorithmImageVBar);

        splitter_2->addWidget(layoutWidget);

        gridLayout_7->addWidget(splitter_2, 0, 0, 1, 1);

        SWidget_image->addWidget(page_algorithmImage);
        page_calibrateImage = new QWidget();
        page_calibrateImage->setObjectName(QStringLiteral("page_calibrateImage"));
        gridLayout_14 = new QGridLayout(page_calibrateImage);
        gridLayout_14->setSpacing(0);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        gridLayout_14->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_calibrateLabel = new QWidget(page_calibrateImage);
        widget_calibrateLabel->setObjectName(QStringLiteral("widget_calibrateLabel"));
        widget_calibrateLabel->setAutoFillBackground(false);
        lab_calibrateImage = new DM_Label(widget_calibrateLabel);
        lab_calibrateImage->setObjectName(QStringLiteral("lab_calibrateImage"));
        lab_calibrateImage->setEnabled(true);
        lab_calibrateImage->setGeometry(QRect(10, 10, 261, 221));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lab_calibrateImage->sizePolicy().hasHeightForWidth());
        lab_calibrateImage->setSizePolicy(sizePolicy4);
        lab_calibrateImage->setMouseTracking(true);
        lab_calibrateImage->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(80, 80, 80, 255));"));
        lab_calibrateImage->setFrameShape(QFrame::Box);
        lab_calibrateImage->setScaledContents(false);
        lab_calibrateImage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(widget_calibrateLabel);

        calibrateImageHBar = new QScrollBar(page_calibrateImage);
        calibrateImageHBar->setObjectName(QStringLiteral("calibrateImageHBar"));
        calibrateImageHBar->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));"));
        calibrateImageHBar->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(calibrateImageHBar);

        calibrateImageInfo = new QLabel(page_calibrateImage);
        calibrateImageInfo->setObjectName(QStringLiteral("calibrateImageInfo"));
        sizePolicy3.setHeightForWidth(calibrateImageInfo->sizePolicy().hasHeightForWidth());
        calibrateImageInfo->setSizePolicy(sizePolicy3);
        calibrateImageInfo->setMinimumSize(QSize(0, 20));
        calibrateImageInfo->setMaximumSize(QSize(16777215, 20));
        calibrateImageInfo->setFont(font);
        calibrateImageInfo->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));\n"
"color: rgb(255, 255, 255);"));
        calibrateImageInfo->setFrameShape(QFrame::Box);

        verticalLayout_2->addWidget(calibrateImageInfo);


        horizontalLayout_2->addLayout(verticalLayout_2);

        calibrateImageVBar = new QScrollBar(page_calibrateImage);
        calibrateImageVBar->setObjectName(QStringLiteral("calibrateImageVBar"));
        calibrateImageVBar->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));"));
        calibrateImageVBar->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(calibrateImageVBar);


        gridLayout_14->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        SWidget_image->addWidget(page_calibrateImage);
        page_cameraVideo = new QWidget();
        page_cameraVideo->setObjectName(QStringLiteral("page_cameraVideo"));
        gridLayout_22 = new QGridLayout(page_cameraVideo);
        gridLayout_22->setSpacing(0);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QStringLiteral("gridLayout_22"));
        gridLayout_22->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(0);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        widget_cameraVideo = new QWidget(page_cameraVideo);
        widget_cameraVideo->setObjectName(QStringLiteral("widget_cameraVideo"));
        lab_cameraVideo = new DM_Label(widget_cameraVideo);
        lab_cameraVideo->setObjectName(QStringLiteral("lab_cameraVideo"));
        lab_cameraVideo->setGeometry(QRect(10, 30, 241, 191));
        lab_cameraVideo->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(80, 80, 80, 255));"));
        lab_cameraVideo->setFrameShape(QFrame::Box);
        lab_cameraVideo->setScaledContents(false);

        verticalLayout_19->addWidget(widget_cameraVideo);

        cameraVideoHBar = new QScrollBar(page_cameraVideo);
        cameraVideoHBar->setObjectName(QStringLiteral("cameraVideoHBar"));
        cameraVideoHBar->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));"));
        cameraVideoHBar->setOrientation(Qt::Horizontal);

        verticalLayout_19->addWidget(cameraVideoHBar);

        cameraVideoInfo = new QLabel(page_cameraVideo);
        cameraVideoInfo->setObjectName(QStringLiteral("cameraVideoInfo"));
        sizePolicy3.setHeightForWidth(cameraVideoInfo->sizePolicy().hasHeightForWidth());
        cameraVideoInfo->setSizePolicy(sizePolicy3);
        cameraVideoInfo->setMinimumSize(QSize(0, 20));
        cameraVideoInfo->setMaximumSize(QSize(16777215, 20));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        cameraVideoInfo->setFont(font1);
        cameraVideoInfo->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));\n"
"color: rgb(255, 255, 255);\n"
""));
        cameraVideoInfo->setFrameShape(QFrame::Box);

        verticalLayout_19->addWidget(cameraVideoInfo);


        horizontalLayout_5->addLayout(verticalLayout_19);

        cameraVideoVBar = new QScrollBar(page_cameraVideo);
        cameraVideoVBar->setObjectName(QStringLiteral("cameraVideoVBar"));
        cameraVideoVBar->setStyleSheet(QLatin1String("border:2px solid;\n"
"border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-bottom-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"border-right-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(32, 32, 32, 255), stop:0.75 rgba(160, 160, 160, 255));\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(40, 40, 40, 255), stop:1 rgba(110, 110, 110, 255));"));
        cameraVideoVBar->setOrientation(Qt::Vertical);

        horizontalLayout_5->addWidget(cameraVideoVBar);


        gridLayout_22->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        SWidget_image->addWidget(page_cameraVideo);
        splitter_3->addWidget(SWidget_image);
        groupBox_16 = new QGroupBox(splitter_3);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        sizePolicy2.setHeightForWidth(groupBox_16->sizePolicy().hasHeightForWidth());
        groupBox_16->setSizePolicy(sizePolicy2);
        groupBox_16->setMinimumSize(QSize(200, 200));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        groupBox_16->setFont(font2);
        groupBox_16->setAlignment(Qt::AlignCenter);
        gridLayout_10 = new QGridLayout(groupBox_16);
        gridLayout_10->setSpacing(0);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        SWidget_coordinate = new QStackedWidget(groupBox_16);
        SWidget_coordinate->setObjectName(QStringLiteral("SWidget_coordinate"));
        SWidget_coordinate->setFrameShape(QFrame::Box);
        page_algorithmCoordinate = new QWidget();
        page_algorithmCoordinate->setObjectName(QStringLiteral("page_algorithmCoordinate"));
        verticalLayout_6 = new QVBoxLayout(page_algorithmCoordinate);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetDefaultConstraint);
        table_algorithmCoordinate = new QTableWidget(page_algorithmCoordinate);
        if (table_algorithmCoordinate->columnCount() < 2)
            table_algorithmCoordinate->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font2);
        __qtablewidgetitem->setBackground(QColor(0, 170, 255, 0));
        table_algorithmCoordinate->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font2);
        table_algorithmCoordinate->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (table_algorithmCoordinate->rowCount() < 2)
            table_algorithmCoordinate->setRowCount(2);
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font3.setPointSize(14);
        font3.setBold(false);
        font3.setWeight(50);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font3);
        table_algorithmCoordinate->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_algorithmCoordinate->setVerticalHeaderItem(1, __qtablewidgetitem3);
        table_algorithmCoordinate->setObjectName(QStringLiteral("table_algorithmCoordinate"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(table_algorithmCoordinate->sizePolicy().hasHeightForWidth());
        table_algorithmCoordinate->setSizePolicy(sizePolicy5);
        table_algorithmCoordinate->setMinimumSize(QSize(200, 200));
        table_algorithmCoordinate->setFont(font3);
        table_algorithmCoordinate->setFrameShape(QFrame::Panel);
        table_algorithmCoordinate->setLineWidth(0);
        table_algorithmCoordinate->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        table_algorithmCoordinate->setAlternatingRowColors(true);
        table_algorithmCoordinate->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        table_algorithmCoordinate->setRowCount(2);
        table_algorithmCoordinate->setColumnCount(2);
        table_algorithmCoordinate->horizontalHeader()->setVisible(false);
        table_algorithmCoordinate->horizontalHeader()->setCascadingSectionResizes(false);
        table_algorithmCoordinate->horizontalHeader()->setDefaultSectionSize(100);
        table_algorithmCoordinate->horizontalHeader()->setHighlightSections(true);
        table_algorithmCoordinate->horizontalHeader()->setStretchLastSection(false);
        table_algorithmCoordinate->verticalHeader()->setVisible(false);
        table_algorithmCoordinate->verticalHeader()->setCascadingSectionResizes(false);
        table_algorithmCoordinate->verticalHeader()->setDefaultSectionSize(22);
        table_algorithmCoordinate->verticalHeader()->setMinimumSectionSize(20);
        table_algorithmCoordinate->verticalHeader()->setStretchLastSection(false);

        verticalLayout_6->addWidget(table_algorithmCoordinate);

        SWidget_coordinate->addWidget(page_algorithmCoordinate);
        page_calibrateCoordinate = new QWidget();
        page_calibrateCoordinate->setObjectName(QStringLiteral("page_calibrateCoordinate"));
        verticalLayout_11 = new QVBoxLayout(page_calibrateCoordinate);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        table_calibrateCoordinate = new QTableWidget(page_calibrateCoordinate);
        if (table_calibrateCoordinate->columnCount() < 2)
            table_calibrateCoordinate->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem4->setFont(font2);
        __qtablewidgetitem4->setBackground(QColor(0, 170, 255, 0));
        table_calibrateCoordinate->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem5->setFont(font2);
        __qtablewidgetitem5->setBackground(QColor(0, 170, 255));
        table_calibrateCoordinate->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        if (table_calibrateCoordinate->rowCount() < 9)
            table_calibrateCoordinate->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem7->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(6, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(7, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font3);
        table_calibrateCoordinate->setVerticalHeaderItem(8, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setTextAlignment(Qt::AlignCenter);
        table_calibrateCoordinate->setItem(1, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        table_calibrateCoordinate->setItem(1, 1, __qtablewidgetitem16);
        table_calibrateCoordinate->setObjectName(QStringLiteral("table_calibrateCoordinate"));
        sizePolicy2.setHeightForWidth(table_calibrateCoordinate->sizePolicy().hasHeightForWidth());
        table_calibrateCoordinate->setSizePolicy(sizePolicy2);
        table_calibrateCoordinate->setMinimumSize(QSize(200, 200));
        table_calibrateCoordinate->setFont(font3);
        table_calibrateCoordinate->setFrameShape(QFrame::Panel);
        table_calibrateCoordinate->setLineWidth(0);
        table_calibrateCoordinate->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        table_calibrateCoordinate->setAlternatingRowColors(true);
        table_calibrateCoordinate->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        table_calibrateCoordinate->horizontalHeader()->setVisible(false);
        table_calibrateCoordinate->horizontalHeader()->setCascadingSectionResizes(false);
        table_calibrateCoordinate->horizontalHeader()->setHighlightSections(true);
        table_calibrateCoordinate->horizontalHeader()->setStretchLastSection(false);
        table_calibrateCoordinate->verticalHeader()->setCascadingSectionResizes(false);
        table_calibrateCoordinate->verticalHeader()->setHighlightSections(true);
        table_calibrateCoordinate->verticalHeader()->setStretchLastSection(false);

        verticalLayout_11->addWidget(table_calibrateCoordinate);

        SWidget_coordinate->addWidget(page_calibrateCoordinate);

        gridLayout_10->addWidget(SWidget_coordinate, 0, 1, 1, 1);

        splitter_3->addWidget(groupBox_16);
        groupBox_17 = new QGroupBox(splitter_3);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        sizePolicy2.setHeightForWidth(groupBox_17->sizePolicy().hasHeightForWidth());
        groupBox_17->setSizePolicy(sizePolicy2);
        groupBox_17->setMinimumSize(QSize(200, 200));
        groupBox_17->setFont(font2);
        groupBox_17->setAlignment(Qt::AlignCenter);
        gridLayout_11 = new QGridLayout(groupBox_17);
        gridLayout_11->setSpacing(0);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        SWidget_table = new QStackedWidget(groupBox_17);
        SWidget_table->setObjectName(QStringLiteral("SWidget_table"));
        SWidget_table->setFrameShape(QFrame::Box);
        page_calibrate = new QWidget();
        page_calibrate->setObjectName(QStringLiteral("page_calibrate"));
        verticalLayout_25 = new QVBoxLayout(page_calibrate);
        verticalLayout_25->setSpacing(6);
        verticalLayout_25->setContentsMargins(11, 11, 11, 11);
        verticalLayout_25->setObjectName(QStringLiteral("verticalLayout_25"));
        table_systemCalibrate = new QTableWidget(page_calibrate);
        if (table_systemCalibrate->columnCount() < 2)
            table_systemCalibrate->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setFont(font2);
        __qtablewidgetitem17->setBackground(QColor(255, 255, 255));
        table_systemCalibrate->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setFont(font2);
        table_systemCalibrate->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        if (table_systemCalibrate->rowCount() < 10)
            table_systemCalibrate->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        table_systemCalibrate->setVerticalHeaderItem(0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        table_systemCalibrate->setVerticalHeaderItem(1, __qtablewidgetitem20);
        table_systemCalibrate->setObjectName(QStringLiteral("table_systemCalibrate"));
        sizePolicy2.setHeightForWidth(table_systemCalibrate->sizePolicy().hasHeightForWidth());
        table_systemCalibrate->setSizePolicy(sizePolicy2);
        table_systemCalibrate->setMinimumSize(QSize(200, 10));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font4.setPointSize(14);
        table_systemCalibrate->setFont(font4);
        table_systemCalibrate->setRowCount(10);
        table_systemCalibrate->setColumnCount(2);

        verticalLayout_25->addWidget(table_systemCalibrate);

        SWidget_table->addWidget(page_calibrate);
        page_algorithm = new QWidget();
        page_algorithm->setObjectName(QStringLiteral("page_algorithm"));
        verticalLayout_30 = new QVBoxLayout(page_algorithm);
        verticalLayout_30->setSpacing(6);
        verticalLayout_30->setContentsMargins(11, 11, 11, 11);
        verticalLayout_30->setObjectName(QStringLiteral("verticalLayout_30"));
        table_preprocessAlgorithm = new QTableWidget(page_algorithm);
        if (table_preprocessAlgorithm->columnCount() < 1)
            table_preprocessAlgorithm->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setFont(font2);
        table_preprocessAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem21);
        if (table_preprocessAlgorithm->rowCount() < 1)
            table_preprocessAlgorithm->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setFont(font3);
        table_preprocessAlgorithm->setVerticalHeaderItem(0, __qtablewidgetitem22);
        table_preprocessAlgorithm->setObjectName(QStringLiteral("table_preprocessAlgorithm"));
        table_preprocessAlgorithm->setRowCount(1);
        table_preprocessAlgorithm->setColumnCount(1);
        table_preprocessAlgorithm->horizontalHeader()->setMinimumSectionSize(30);
        table_preprocessAlgorithm->verticalHeader()->setDefaultSectionSize(25);

        verticalLayout_30->addWidget(table_preprocessAlgorithm);

        SWidget_table->addWidget(page_algorithm);

        gridLayout_11->addWidget(SWidget_table, 0, 0, 1, 1);

        splitter_3->addWidget(groupBox_17);
        splitter_5->addWidget(splitter_3);
        splitter_4 = new QSplitter(splitter_5);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        SWidget_toolsDirectory = new QStackedWidget(splitter_4);
        SWidget_toolsDirectory->setObjectName(QStringLiteral("SWidget_toolsDirectory"));
        sizePolicy1.setHeightForWidth(SWidget_toolsDirectory->sizePolicy().hasHeightForWidth());
        SWidget_toolsDirectory->setSizePolicy(sizePolicy1);
        SWidget_toolsDirectory->setMinimumSize(QSize(200, 100));
        SWidget_toolsDirectory->setFrameShape(QFrame::StyledPanel);
        page_toolList = new QWidget();
        page_toolList->setObjectName(QStringLiteral("page_toolList"));
        gridLayout_21 = new QGridLayout(page_toolList);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QStringLiteral("gridLayout_21"));
        groupBox_15 = new QGroupBox(page_toolList);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        groupBox_15->setFont(font2);
        groupBox_15->setStyleSheet(QLatin1String("border-right-color: rgb(85, 255, 255);\n"
"border-bottom-color: rgb(255, 0, 0);\n"
"border-left-color: rgb(255, 255, 127);\n"
"border-top-color: rgb(255, 85, 255);"));
        groupBox_15->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(groupBox_15);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        TWidget_toolList = new QTreeWidget(groupBox_15);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icon/img/icon/pro.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font5.setPointSize(14);
        font5.setBold(true);
        font5.setUnderline(false);
        font5.setWeight(75);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(0, font5);
        __qtreewidgetitem->setIcon(0, icon15);
        TWidget_toolList->setHeaderItem(__qtreewidgetitem);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icon/img/icon/camera1.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font6;
        font6.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font6.setPointSize(13);
        font6.setBold(true);
        font6.setWeight(75);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icon/img/icon/calibrate.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font7;
        font7.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font7.setPointSize(12);
        font7.setBold(true);
        font7.setWeight(75);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/icon/img/icon/algorithm.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icon/img/icon/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(TWidget_toolList);
        __qtreewidgetitem1->setFont(0, font6);
        __qtreewidgetitem1->setIcon(0, icon16);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(TWidget_toolList);
        __qtreewidgetitem2->setFont(0, font2);
        __qtreewidgetitem2->setIcon(0, icon17);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem3->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem4->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem5->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem6->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem7->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(TWidget_toolList);
        __qtreewidgetitem8->setFont(0, font2);
        __qtreewidgetitem8->setIcon(0, icon18);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem9->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem9);
        __qtreewidgetitem10->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem11->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(__qtreewidgetitem11);
        __qtreewidgetitem12->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem13->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem14 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem14->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem15 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem15->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem16 = new QTreeWidgetItem(__qtreewidgetitem11);
        __qtreewidgetitem16->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem17 = new QTreeWidgetItem(__qtreewidgetitem16);
        __qtreewidgetitem17->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem18 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem18->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem19 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem19->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem20 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem20->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem21 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem21->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem22 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem22->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem23 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem23->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem24 = new QTreeWidgetItem(__qtreewidgetitem23);
        __qtreewidgetitem24->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem25 = new QTreeWidgetItem(__qtreewidgetitem23);
        __qtreewidgetitem25->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem26 = new QTreeWidgetItem(__qtreewidgetitem23);
        __qtreewidgetitem26->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem27 = new QTreeWidgetItem(__qtreewidgetitem23);
        __qtreewidgetitem27->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem28 = new QTreeWidgetItem(__qtreewidgetitem23);
        __qtreewidgetitem28->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem29 = new QTreeWidgetItem(__qtreewidgetitem23);
        __qtreewidgetitem29->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem30 = new QTreeWidgetItem(__qtreewidgetitem23);
        __qtreewidgetitem30->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem31 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem31->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem32 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem32->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem33 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem33->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem34 = new QTreeWidgetItem(__qtreewidgetitem33);
        __qtreewidgetitem34->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem35 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem35->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem36 = new QTreeWidgetItem(__qtreewidgetitem35);
        __qtreewidgetitem36->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem37 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem37->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem38 = new QTreeWidgetItem(__qtreewidgetitem37);
        __qtreewidgetitem38->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem39 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem39->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem40 = new QTreeWidgetItem(__qtreewidgetitem39);
        __qtreewidgetitem40->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem41 = new QTreeWidgetItem(__qtreewidgetitem39);
        __qtreewidgetitem41->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem42 = new QTreeWidgetItem(__qtreewidgetitem39);
        __qtreewidgetitem42->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem43 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem43->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem44 = new QTreeWidgetItem(__qtreewidgetitem43);
        __qtreewidgetitem44->setFont(0, font7);
        QTreeWidgetItem *__qtreewidgetitem45 = new QTreeWidgetItem(TWidget_toolList);
        __qtreewidgetitem45->setFont(0, font7);
        __qtreewidgetitem45->setIcon(0, icon19);
        TWidget_toolList->setObjectName(QStringLiteral("TWidget_toolList"));
        TWidget_toolList->setFrameShape(QFrame::Box);
        TWidget_toolList->setEditTriggers(QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        TWidget_toolList->setIconSize(QSize(16, 16));

        verticalLayout->addWidget(TWidget_toolList);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btn_toolConfirm = new QPushButton(groupBox_15);
        btn_toolConfirm->setObjectName(QStringLiteral("btn_toolConfirm"));
        btn_toolConfirm->setMinimumSize(QSize(0, 25));
        btn_toolConfirm->setMaximumSize(QSize(100, 25));
        btn_toolConfirm->setBaseSize(QSize(75, 25));
        btn_toolConfirm->setFont(font7);

        horizontalLayout_4->addWidget(btn_toolConfirm);

        btn_AlgorithmExcute = new QPushButton(groupBox_15);
        btn_AlgorithmExcute->setObjectName(QStringLiteral("btn_AlgorithmExcute"));
        btn_AlgorithmExcute->setMinimumSize(QSize(0, 25));
        btn_AlgorithmExcute->setMaximumSize(QSize(100, 25));
        btn_AlgorithmExcute->setFont(font2);

        horizontalLayout_4->addWidget(btn_AlgorithmExcute);

        btn_AlgorithmRevocation = new QPushButton(groupBox_15);
        btn_AlgorithmRevocation->setObjectName(QStringLiteral("btn_AlgorithmRevocation"));
        btn_AlgorithmRevocation->setMinimumSize(QSize(0, 25));
        btn_AlgorithmRevocation->setMaximumSize(QSize(100, 25));
        btn_AlgorithmRevocation->setFont(font2);

        horizontalLayout_4->addWidget(btn_AlgorithmRevocation);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_21->addWidget(groupBox_15, 0, 0, 1, 1);

        SWidget_toolsDirectory->addWidget(page_toolList);
        splitter_4->addWidget(SWidget_toolsDirectory);
        splitter = new QSplitter(splitter_4);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setChildrenCollapsible(true);
        SWidget_information = new QStackedWidget(splitter);
        SWidget_information->setObjectName(QStringLiteral("SWidget_information"));
        SWidget_information->setEnabled(true);
        sizePolicy2.setHeightForWidth(SWidget_information->sizePolicy().hasHeightForWidth());
        SWidget_information->setSizePolicy(sizePolicy2);
        SWidget_information->setMinimumSize(QSize(100, 100));
        SWidget_information->setFrameShape(QFrame::StyledPanel);
        SWidget_information->setFrameShadow(QFrame::Sunken);
        page_paraInformation = new QWidget();
        page_paraInformation->setObjectName(QStringLiteral("page_paraInformation"));
        gridLayout_20 = new QGridLayout(page_paraInformation);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QStringLiteral("gridLayout_20"));
        groupBox_5 = new QGroupBox(page_paraInformation);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font8.setPointSize(14);
        font8.setBold(true);
        font8.setUnderline(false);
        font8.setWeight(75);
        groupBox_5->setFont(font8);
        groupBox_5->setAlignment(Qt::AlignCenter);
        gridLayout_19 = new QGridLayout(groupBox_5);
        gridLayout_19->setSpacing(0);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        gridLayout_19->setContentsMargins(0, 0, 0, 0);
        SWidget_paraInformation = new QStackedWidget(groupBox_5);
        SWidget_paraInformation->setObjectName(QStringLiteral("SWidget_paraInformation"));
        QFont font9;
        font9.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font9.setBold(false);
        font9.setWeight(50);
        SWidget_paraInformation->setFont(font9);
        defalutInfo = new QWidget();
        defalutInfo->setObjectName(QStringLiteral("defalutInfo"));
        SWidget_paraInformation->addWidget(defalutInfo);
        threasholdInfo = new QWidget();
        threasholdInfo->setObjectName(QStringLiteral("threasholdInfo"));
        gridLayout_31 = new QGridLayout(threasholdInfo);
        gridLayout_31->setSpacing(6);
        gridLayout_31->setContentsMargins(11, 11, 11, 11);
        gridLayout_31->setObjectName(QStringLiteral("gridLayout_31"));
        textBrowser_20 = new QTextBrowser(threasholdInfo);
        textBrowser_20->setObjectName(QStringLiteral("textBrowser_20"));
        QFont font10;
        font10.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font10.setPointSize(9);
        font10.setBold(false);
        font10.setItalic(false);
        font10.setWeight(50);
        textBrowser_20->setFont(font10);
        textBrowser_20->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_31->addWidget(textBrowser_20, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(threasholdInfo);
        zoningThreasholdInfo = new QWidget();
        zoningThreasholdInfo->setObjectName(QStringLiteral("zoningThreasholdInfo"));
        gridLayout_30 = new QGridLayout(zoningThreasholdInfo);
        gridLayout_30->setSpacing(6);
        gridLayout_30->setContentsMargins(11, 11, 11, 11);
        gridLayout_30->setObjectName(QStringLiteral("gridLayout_30"));
        textBrowser_21 = new QTextBrowser(zoningThreasholdInfo);
        textBrowser_21->setObjectName(QStringLiteral("textBrowser_21"));
        textBrowser_21->setFont(font10);
        textBrowser_21->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_30->addWidget(textBrowser_21, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(zoningThreasholdInfo);
        blurInfo = new QWidget();
        blurInfo->setObjectName(QStringLiteral("blurInfo"));
        verticalLayout_8 = new QVBoxLayout(blurInfo);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        textBrowser_7 = new QTextBrowser(blurInfo);
        textBrowser_7->setObjectName(QStringLiteral("textBrowser_7"));
        QFont font11;
        font11.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font11.setUnderline(false);
        textBrowser_7->setFont(font11);

        verticalLayout_8->addWidget(textBrowser_7);

        SWidget_paraInformation->addWidget(blurInfo);
        morphologyInfo = new QWidget();
        morphologyInfo->setObjectName(QStringLiteral("morphologyInfo"));
        verticalLayout_7 = new QVBoxLayout(morphologyInfo);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        textBrowser_9 = new QTextBrowser(morphologyInfo);
        textBrowser_9->setObjectName(QStringLiteral("textBrowser_9"));
        QFont font12;
        font12.setUnderline(false);
        textBrowser_9->setFont(font12);

        verticalLayout_7->addWidget(textBrowser_9);

        SWidget_paraInformation->addWidget(morphologyInfo);
        contourInfo = new QWidget();
        contourInfo->setObjectName(QStringLiteral("contourInfo"));
        verticalLayout_12 = new QVBoxLayout(contourInfo);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        textBrowser_6 = new QTextBrowser(contourInfo);
        textBrowser_6->setObjectName(QStringLiteral("textBrowser_6"));
        textBrowser_6->setFont(font12);

        verticalLayout_12->addWidget(textBrowser_6);

        verticalLayout_12->setStretch(0, 4);
        SWidget_paraInformation->addWidget(contourInfo);
        houghInfo = new QWidget();
        houghInfo->setObjectName(QStringLiteral("houghInfo"));
        horizontalLayout_7 = new QHBoxLayout(houghInfo);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        textBrowser_4 = new QTextBrowser(houghInfo);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setFont(font12);

        horizontalLayout_7->addWidget(textBrowser_4);

        SWidget_paraInformation->addWidget(houghInfo);
        findCircleInfo = new QWidget();
        findCircleInfo->setObjectName(QStringLiteral("findCircleInfo"));
        horizontalLayout_18 = new QHBoxLayout(findCircleInfo);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        textBrowser_8 = new QTextBrowser(findCircleInfo);
        textBrowser_8->setObjectName(QStringLiteral("textBrowser_8"));
        textBrowser_8->setFont(font12);

        horizontalLayout_18->addWidget(textBrowser_8);

        horizontalLayout_18->setStretch(0, 3);
        SWidget_paraInformation->addWidget(findCircleInfo);
        tempmatchInfo = new QWidget();
        tempmatchInfo->setObjectName(QStringLiteral("tempmatchInfo"));
        verticalLayout_4 = new QVBoxLayout(tempmatchInfo);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        textBrowser_5 = new QTextBrowser(tempmatchInfo);
        textBrowser_5->setObjectName(QStringLiteral("textBrowser_5"));
        textBrowser_5->setFont(font12);

        verticalLayout_4->addWidget(textBrowser_5);

        SWidget_paraInformation->addWidget(tempmatchInfo);
        chessbordInfo = new QWidget();
        chessbordInfo->setObjectName(QStringLiteral("chessbordInfo"));
        gridLayout_8 = new QGridLayout(chessbordInfo);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        textBrowser_11 = new QTextBrowser(chessbordInfo);
        textBrowser_11->setObjectName(QStringLiteral("textBrowser_11"));
        textBrowser_11->setFont(font12);

        gridLayout_8->addWidget(textBrowser_11, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(chessbordInfo);
        imgNotInfo = new QWidget();
        imgNotInfo->setObjectName(QStringLiteral("imgNotInfo"));
        gridLayout_28 = new QGridLayout(imgNotInfo);
        gridLayout_28->setSpacing(6);
        gridLayout_28->setContentsMargins(11, 11, 11, 11);
        gridLayout_28->setObjectName(QStringLiteral("gridLayout_28"));
        textBrowser_12 = new QTextBrowser(imgNotInfo);
        textBrowser_12->setObjectName(QStringLiteral("textBrowser_12"));
        textBrowser_12->setFont(font10);
        textBrowser_12->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_28->addWidget(textBrowser_12, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(imgNotInfo);
        momentInfo = new QWidget();
        momentInfo->setObjectName(QStringLiteral("momentInfo"));
        gridLayout_29 = new QGridLayout(momentInfo);
        gridLayout_29->setSpacing(6);
        gridLayout_29->setContentsMargins(11, 11, 11, 11);
        gridLayout_29->setObjectName(QStringLiteral("gridLayout_29"));
        textBrowser_15 = new QTextBrowser(momentInfo);
        textBrowser_15->setObjectName(QStringLiteral("textBrowser_15"));
        textBrowser_15->setFont(font10);
        textBrowser_15->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_29->addWidget(textBrowser_15, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(momentInfo);
        modbusInfo = new QWidget();
        modbusInfo->setObjectName(QStringLiteral("modbusInfo"));
        gridLayout_12 = new QGridLayout(modbusInfo);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        textBrowser_13 = new QTextBrowser(modbusInfo);
        textBrowser_13->setObjectName(QStringLiteral("textBrowser_13"));
        QFont font13;
        font13.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font13.setPointSize(14);
        font13.setBold(false);
        font13.setItalic(false);
        font13.setWeight(50);
        textBrowser_13->setFont(font13);

        gridLayout_12->addWidget(textBrowser_13, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(modbusInfo);
        calibrate_dotPlateInfo = new QWidget();
        calibrate_dotPlateInfo->setObjectName(QStringLiteral("calibrate_dotPlateInfo"));
        gridLayout_13 = new QGridLayout(calibrate_dotPlateInfo);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        textBrowser_3 = new QTextBrowser(calibrate_dotPlateInfo);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));

        gridLayout_13->addWidget(textBrowser_3, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(calibrate_dotPlateInfo);
        cameraInfo = new QWidget();
        cameraInfo->setObjectName(QStringLiteral("cameraInfo"));
        gridLayout_26 = new QGridLayout(cameraInfo);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QStringLiteral("gridLayout_26"));
        textBrowser_18 = new QTextBrowser(cameraInfo);
        textBrowser_18->setObjectName(QStringLiteral("textBrowser_18"));
        textBrowser_18->setFont(font13);
        textBrowser_18->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));

        gridLayout_26->addWidget(textBrowser_18, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(cameraInfo);
        calibrationInfo = new QWidget();
        calibrationInfo->setObjectName(QStringLiteral("calibrationInfo"));
        gridLayout_25 = new QGridLayout(calibrationInfo);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QStringLiteral("gridLayout_25"));
        textBrowser_19 = new QTextBrowser(calibrationInfo);
        textBrowser_19->setObjectName(QStringLiteral("textBrowser_19"));
        textBrowser_19->setFont(font10);
        textBrowser_19->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_25->addWidget(textBrowser_19, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(calibrationInfo);
        calibrate_mappingMatrixInfo = new QWidget();
        calibrate_mappingMatrixInfo->setObjectName(QStringLiteral("calibrate_mappingMatrixInfo"));
        gridLayout_33 = new QGridLayout(calibrate_mappingMatrixInfo);
        gridLayout_33->setSpacing(6);
        gridLayout_33->setContentsMargins(11, 11, 11, 11);
        gridLayout_33->setObjectName(QStringLiteral("gridLayout_33"));
        textBrowser_22 = new QTextBrowser(calibrate_mappingMatrixInfo);
        textBrowser_22->setObjectName(QStringLiteral("textBrowser_22"));
        textBrowser_22->setFont(font10);
        textBrowser_22->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_33->addWidget(textBrowser_22, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(calibrate_mappingMatrixInfo);
        calibrate_calibrationPlateInfo = new QWidget();
        calibrate_calibrationPlateInfo->setObjectName(QStringLiteral("calibrate_calibrationPlateInfo"));
        gridLayout_32 = new QGridLayout(calibrate_calibrationPlateInfo);
        gridLayout_32->setSpacing(6);
        gridLayout_32->setContentsMargins(11, 11, 11, 11);
        gridLayout_32->setObjectName(QStringLiteral("gridLayout_32"));
        textBrowser_23 = new QTextBrowser(calibrate_calibrationPlateInfo);
        textBrowser_23->setObjectName(QStringLiteral("textBrowser_23"));
        textBrowser_23->setFont(font10);
        textBrowser_23->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_32->addWidget(textBrowser_23, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(calibrate_calibrationPlateInfo);
        algorithmInfo = new QWidget();
        algorithmInfo->setObjectName(QStringLiteral("algorithmInfo"));
        gridLayout_34 = new QGridLayout(algorithmInfo);
        gridLayout_34->setSpacing(6);
        gridLayout_34->setContentsMargins(11, 11, 11, 11);
        gridLayout_34->setObjectName(QStringLiteral("gridLayout_34"));
        textBrowser_24 = new QTextBrowser(algorithmInfo);
        textBrowser_24->setObjectName(QStringLiteral("textBrowser_24"));
        textBrowser_24->setFont(font10);
        textBrowser_24->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_34->addWidget(textBrowser_24, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(algorithmInfo);
        calibrate_findCirclehandInfo = new QWidget();
        calibrate_findCirclehandInfo->setObjectName(QStringLiteral("calibrate_findCirclehandInfo"));
        gridLayout_3 = new QGridLayout(calibrate_findCirclehandInfo);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        textBrowser_25 = new QTextBrowser(calibrate_findCirclehandInfo);
        textBrowser_25->setObjectName(QStringLiteral("textBrowser_25"));
        QFont font14;
        font14.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font14.setPointSize(12);
        font14.setBold(false);
        font14.setItalic(false);
        font14.setWeight(50);
        textBrowser_25->setFont(font14);
        textBrowser_25->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));

        gridLayout_3->addWidget(textBrowser_25, 0, 0, 1, 1);

        SWidget_paraInformation->addWidget(calibrate_findCirclehandInfo);

        gridLayout_19->addWidget(SWidget_paraInformation, 0, 0, 1, 1);


        gridLayout_20->addWidget(groupBox_5, 0, 0, 1, 1);

        SWidget_information->addWidget(page_paraInformation);
        page_paraSetting = new QWidget();
        page_paraSetting->setObjectName(QStringLiteral("page_paraSetting"));
        horizontalLayout_10 = new QHBoxLayout(page_paraSetting);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        groupBox_18 = new QGroupBox(page_paraSetting);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        groupBox_18->setFont(font5);
        groupBox_18->setAlignment(Qt::AlignCenter);
        verticalLayout_22 = new QVBoxLayout(groupBox_18);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        splitter_6 = new QSplitter(groupBox_18);
        splitter_6->setObjectName(QStringLiteral("splitter_6"));
        splitter_6->setOrientation(Qt::Vertical);
        splitter_6->setChildrenCollapsible(false);
        SWidget_paraSetting = new QStackedWidget(splitter_6);
        SWidget_paraSetting->setObjectName(QStringLiteral("SWidget_paraSetting"));
        QFont font15;
        font15.setBold(false);
        font15.setWeight(50);
        SWidget_paraSetting->setFont(font15);
        SWidget_paraSetting->setFrameShape(QFrame::Box);
        defalutPara = new QWidget();
        defalutPara->setObjectName(QStringLiteral("defalutPara"));
        SWidget_paraSetting->addWidget(defalutPara);
        threasholdPara = new QWidget();
        threasholdPara->setObjectName(QStringLiteral("threasholdPara"));
        verticalLayout_32 = new QVBoxLayout(threasholdPara);
        verticalLayout_32->setSpacing(6);
        verticalLayout_32->setContentsMargins(11, 11, 11, 11);
        verticalLayout_32->setObjectName(QStringLiteral("verticalLayout_32"));
        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName(QStringLiteral("horizontalLayout_43"));
        label_81 = new QLabel(threasholdPara);
        label_81->setObjectName(QStringLiteral("label_81"));
        QFont font16;
        font16.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font16.setPointSize(12);
        font16.setUnderline(false);
        label_81->setFont(font16);
        label_81->setFrameShape(QFrame::Box);

        horizontalLayout_43->addWidget(label_81);

        threashold_Box = new QSpinBox(threasholdPara);
        threashold_Box->setObjectName(QStringLiteral("threashold_Box"));
        QFont font17;
        font17.setPointSize(15);
        font17.setUnderline(false);
        threashold_Box->setFont(font17);
        threashold_Box->setMinimum(1);
        threashold_Box->setMaximum(255);
        threashold_Box->setValue(100);

        horizontalLayout_43->addWidget(threashold_Box);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_19);

        horizontalLayout_43->setStretch(0, 1);
        horizontalLayout_43->setStretch(1, 3);
        horizontalLayout_43->setStretch(2, 9);

        verticalLayout_32->addLayout(horizontalLayout_43);

        verticalSpacer_20 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_32->addItem(verticalSpacer_20);

        SWidget_paraSetting->addWidget(threasholdPara);
        zoningThreasholdPara = new QWidget();
        zoningThreasholdPara->setObjectName(QStringLiteral("zoningThreasholdPara"));
        verticalLayout_33 = new QVBoxLayout(zoningThreasholdPara);
        verticalLayout_33->setSpacing(6);
        verticalLayout_33->setContentsMargins(11, 11, 11, 11);
        verticalLayout_33->setObjectName(QStringLiteral("verticalLayout_33"));
        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName(QStringLiteral("horizontalLayout_44"));
        label_82 = new QLabel(zoningThreasholdPara);
        label_82->setObjectName(QStringLiteral("label_82"));
        label_82->setFont(font16);
        label_82->setFrameShape(QFrame::Box);

        horizontalLayout_44->addWidget(label_82);

        blockSize_Box = new QSpinBox(zoningThreasholdPara);
        blockSize_Box->setObjectName(QStringLiteral("blockSize_Box"));
        blockSize_Box->setFont(font17);
        blockSize_Box->setMaximum(9999999);
        blockSize_Box->setSingleStep(3);

        horizontalLayout_44->addWidget(blockSize_Box);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_24);

        horizontalLayout_44->setStretch(0, 1);
        horizontalLayout_44->setStretch(1, 1);
        horizontalLayout_44->setStretch(2, 10);

        verticalLayout_33->addLayout(horizontalLayout_44);

        verticalSpacer_21 = new QSpacerItem(20, 173, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_33->addItem(verticalSpacer_21);

        SWidget_paraSetting->addWidget(zoningThreasholdPara);
        blurPara = new QWidget();
        blurPara->setObjectName(QStringLiteral("blurPara"));
        verticalLayout_34 = new QVBoxLayout(blurPara);
        verticalLayout_34->setSpacing(6);
        verticalLayout_34->setContentsMargins(11, 11, 11, 11);
        verticalLayout_34->setObjectName(QStringLiteral("verticalLayout_34"));
        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName(QStringLiteral("horizontalLayout_45"));
        label_83 = new QLabel(blurPara);
        label_83->setObjectName(QStringLiteral("label_83"));
        label_83->setFont(font16);
        label_83->setFrameShape(QFrame::Box);

        horizontalLayout_45->addWidget(label_83);

        blurKernelW = new QSpinBox(blurPara);
        blurKernelW->setObjectName(QStringLiteral("blurKernelW"));
        blurKernelW->setFont(font17);
        blurKernelW->setMinimum(3);
        blurKernelW->setMaximum(9999);
        blurKernelW->setSingleStep(1);
        blurKernelW->setValue(3);

        horizontalLayout_45->addWidget(blurKernelW);

        label_84 = new QLabel(blurPara);
        label_84->setObjectName(QStringLiteral("label_84"));
        label_84->setFont(font16);
        label_84->setFrameShape(QFrame::Box);

        horizontalLayout_45->addWidget(label_84);

        blurKernelH = new QSpinBox(blurPara);
        blurKernelH->setObjectName(QStringLiteral("blurKernelH"));
        blurKernelH->setFont(font17);
        blurKernelH->setMinimum(3);
        blurKernelH->setMaximum(9999);
        blurKernelH->setSingleStep(1);
        blurKernelH->setValue(3);

        horizontalLayout_45->addWidget(blurKernelH);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_26);

        horizontalLayout_45->setStretch(0, 1);
        horizontalLayout_45->setStretch(1, 1);
        horizontalLayout_45->setStretch(2, 1);
        horizontalLayout_45->setStretch(3, 1);
        horizontalLayout_45->setStretch(4, 3);

        verticalLayout_34->addLayout(horizontalLayout_45);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName(QStringLiteral("horizontalLayout_46"));
        horizontalLayout_46->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_85 = new QLabel(blurPara);
        label_85->setObjectName(QStringLiteral("label_85"));
        label_85->setFont(font16);
        label_85->setFrameShape(QFrame::Box);

        horizontalLayout_46->addWidget(label_85);

        blur_sigmaColor = new QDoubleSpinBox(blurPara);
        blur_sigmaColor->setObjectName(QStringLiteral("blur_sigmaColor"));
        blur_sigmaColor->setFont(font12);
        blur_sigmaColor->setMinimum(3);
        blur_sigmaColor->setMaximum(9999);

        horizontalLayout_46->addWidget(blur_sigmaColor);

        label_86 = new QLabel(blurPara);
        label_86->setObjectName(QStringLiteral("label_86"));
        label_86->setFont(font16);
        label_86->setFrameShape(QFrame::Box);

        horizontalLayout_46->addWidget(label_86);

        blur_sigmaSpace = new QDoubleSpinBox(blurPara);
        blur_sigmaSpace->setObjectName(QStringLiteral("blur_sigmaSpace"));
        QFont font18;
        font18.setBold(false);
        font18.setUnderline(false);
        font18.setWeight(50);
        blur_sigmaSpace->setFont(font18);
        blur_sigmaSpace->setMinimum(3);
        blur_sigmaSpace->setMaximum(9999);

        horizontalLayout_46->addWidget(blur_sigmaSpace);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_25);

        horizontalLayout_46->setStretch(0, 1);
        horizontalLayout_46->setStretch(1, 1);
        horizontalLayout_46->setStretch(2, 1);
        horizontalLayout_46->setStretch(3, 1);
        horizontalLayout_46->setStretch(4, 3);

        verticalLayout_34->addLayout(horizontalLayout_46);

        verticalSpacer_25 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_34->addItem(verticalSpacer_25);

        SWidget_paraSetting->addWidget(blurPara);
        morphologyPara = new QWidget();
        morphologyPara->setObjectName(QStringLiteral("morphologyPara"));
        verticalLayout_35 = new QVBoxLayout(morphologyPara);
        verticalLayout_35->setSpacing(6);
        verticalLayout_35->setContentsMargins(11, 11, 11, 11);
        verticalLayout_35->setObjectName(QStringLiteral("verticalLayout_35"));
        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QStringLiteral("horizontalLayout_47"));
        label_87 = new QLabel(morphologyPara);
        label_87->setObjectName(QStringLiteral("label_87"));
        label_87->setFont(font16);
        label_87->setFrameShape(QFrame::Box);

        horizontalLayout_47->addWidget(label_87);

        morphologyKernelW = new QSpinBox(morphologyPara);
        morphologyKernelW->setObjectName(QStringLiteral("morphologyKernelW"));
        morphologyKernelW->setFont(font17);
        morphologyKernelW->setMinimum(3);
        morphologyKernelW->setMaximum(9999);
        morphologyKernelW->setSingleStep(1);
        morphologyKernelW->setValue(3);

        horizontalLayout_47->addWidget(morphologyKernelW);

        label_88 = new QLabel(morphologyPara);
        label_88->setObjectName(QStringLiteral("label_88"));
        label_88->setFont(font16);
        label_88->setFrameShape(QFrame::Box);

        horizontalLayout_47->addWidget(label_88);

        morphologyKernelH = new QSpinBox(morphologyPara);
        morphologyKernelH->setObjectName(QStringLiteral("morphologyKernelH"));
        morphologyKernelH->setFont(font17);
        morphologyKernelH->setMinimum(3);
        morphologyKernelH->setMaximum(9999);
        morphologyKernelH->setSingleStep(1);
        morphologyKernelH->setValue(3);

        horizontalLayout_47->addWidget(morphologyKernelH);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_47->addItem(horizontalSpacer_27);

        horizontalLayout_47->setStretch(0, 1);
        horizontalLayout_47->setStretch(1, 1);
        horizontalLayout_47->setStretch(2, 1);
        horizontalLayout_47->setStretch(3, 1);
        horizontalLayout_47->setStretch(4, 3);

        verticalLayout_35->addLayout(horizontalLayout_47);

        verticalSpacer_26 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_35->addItem(verticalSpacer_26);

        SWidget_paraSetting->addWidget(morphologyPara);
        contourPara = new QWidget();
        contourPara->setObjectName(QStringLiteral("contourPara"));
        verticalLayout_36 = new QVBoxLayout(contourPara);
        verticalLayout_36->setSpacing(6);
        verticalLayout_36->setContentsMargins(11, 11, 11, 11);
        verticalLayout_36->setObjectName(QStringLiteral("verticalLayout_36"));
        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QStringLiteral("horizontalLayout_49"));
        label_89 = new QLabel(contourPara);
        label_89->setObjectName(QStringLiteral("label_89"));
        label_89->setFont(font16);
        label_89->setFrameShape(QFrame::Box);

        horizontalLayout_49->addWidget(label_89);

        maxArea_Box = new QSpinBox(contourPara);
        maxArea_Box->setObjectName(QStringLiteral("maxArea_Box"));
        maxArea_Box->setFont(font17);
        maxArea_Box->setMaximum(999999);

        horizontalLayout_49->addWidget(maxArea_Box);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_49->addItem(horizontalSpacer_13);

        horizontalLayout_49->setStretch(0, 1);
        horizontalLayout_49->setStretch(1, 1);
        horizontalLayout_49->setStretch(2, 9);

        verticalLayout_36->addLayout(horizontalLayout_49);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setSpacing(6);
        horizontalLayout_52->setObjectName(QStringLiteral("horizontalLayout_52"));
        label_90 = new QLabel(contourPara);
        label_90->setObjectName(QStringLiteral("label_90"));
        label_90->setFont(font16);
        label_90->setFrameShape(QFrame::Box);

        horizontalLayout_52->addWidget(label_90);

        minArea_Box = new QSpinBox(contourPara);
        minArea_Box->setObjectName(QStringLiteral("minArea_Box"));
        minArea_Box->setFont(font17);
        minArea_Box->setMaximum(999999);

        horizontalLayout_52->addWidget(minArea_Box);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_52->addItem(horizontalSpacer_12);

        horizontalLayout_52->setStretch(0, 1);
        horizontalLayout_52->setStretch(1, 1);
        horizontalLayout_52->setStretch(2, 9);

        verticalLayout_36->addLayout(horizontalLayout_52);

        verticalSpacer_22 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_36->addItem(verticalSpacer_22);

        verticalLayout_36->setStretch(0, 1);
        verticalLayout_36->setStretch(1, 1);
        verticalLayout_36->setStretch(2, 1);
        SWidget_paraSetting->addWidget(contourPara);
        houghPara = new QWidget();
        houghPara->setObjectName(QStringLiteral("houghPara"));
        horizontalLayout_55 = new QHBoxLayout(houghPara);
        horizontalLayout_55->setSpacing(6);
        horizontalLayout_55->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_55->setObjectName(QStringLiteral("horizontalLayout_55"));
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(6);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        label_91 = new QLabel(houghPara);
        label_91->setObjectName(QStringLiteral("label_91"));
        label_91->setFont(font16);
        label_91->setFrameShape(QFrame::Box);

        gridLayout_16->addWidget(label_91, 0, 0, 1, 2);

        hough_minDist = new QDoubleSpinBox(houghPara);
        hough_minDist->setObjectName(QStringLiteral("hough_minDist"));
        hough_minDist->setFont(font12);
        hough_minDist->setMaximum(100001);
        hough_minDist->setValue(100);

        gridLayout_16->addWidget(hough_minDist, 0, 2, 1, 2);

        label_92 = new QLabel(houghPara);
        label_92->setObjectName(QStringLiteral("label_92"));
        label_92->setFont(font16);
        label_92->setFrameShape(QFrame::Box);

        gridLayout_16->addWidget(label_92, 3, 0, 1, 2);

        label_93 = new QLabel(houghPara);
        label_93->setObjectName(QStringLiteral("label_93"));
        label_93->setFont(font16);
        label_93->setFrameShape(QFrame::Box);

        gridLayout_16->addWidget(label_93, 4, 0, 1, 2);

        hough_minRadius = new QSpinBox(houghPara);
        hough_minRadius->setObjectName(QStringLiteral("hough_minRadius"));
        hough_minRadius->setFont(font17);
        hough_minRadius->setMinimum(0);
        hough_minRadius->setMaximum(100000);
        hough_minRadius->setValue(0);

        gridLayout_16->addWidget(hough_minRadius, 4, 2, 1, 2);

        label_94 = new QLabel(houghPara);
        label_94->setObjectName(QStringLiteral("label_94"));
        label_94->setFont(font16);
        label_94->setFrameShape(QFrame::Box);

        gridLayout_16->addWidget(label_94, 2, 0, 1, 2);

        hough_cannyThreshold = new QDoubleSpinBox(houghPara);
        hough_cannyThreshold->setObjectName(QStringLiteral("hough_cannyThreshold"));
        hough_cannyThreshold->setFont(font12);
        hough_cannyThreshold->setMinimum(0);
        hough_cannyThreshold->setMaximum(255);
        hough_cannyThreshold->setValue(99.99);

        gridLayout_16->addWidget(hough_cannyThreshold, 1, 2, 1, 2);

        label_95 = new QLabel(houghPara);
        label_95->setObjectName(QStringLiteral("label_95"));
        label_95->setFont(font16);
        label_95->setFrameShape(QFrame::Box);

        gridLayout_16->addWidget(label_95, 1, 0, 1, 2);

        hough_countThreshold = new QDoubleSpinBox(houghPara);
        hough_countThreshold->setObjectName(QStringLiteral("hough_countThreshold"));
        hough_countThreshold->setFont(font12);
        hough_countThreshold->setMaximum(10000);
        hough_countThreshold->setValue(50);

        gridLayout_16->addWidget(hough_countThreshold, 2, 2, 1, 2);

        hough_maxRadius = new QSpinBox(houghPara);
        hough_maxRadius->setObjectName(QStringLiteral("hough_maxRadius"));
        hough_maxRadius->setFont(font17);
        hough_maxRadius->setMinimum(0);
        hough_maxRadius->setMaximum(100000);
        hough_maxRadius->setValue(0);

        gridLayout_16->addWidget(hough_maxRadius, 3, 2, 1, 2);

        gridLayout_16->setColumnStretch(0, 1);
        gridLayout_16->setColumnStretch(1, 1);
        gridLayout_16->setColumnStretch(2, 1);
        gridLayout_16->setColumnStretch(3, 1);
        gridLayout_16->setColumnMinimumWidth(0, 1);
        gridLayout_16->setColumnMinimumWidth(1, 1);
        gridLayout_16->setColumnMinimumWidth(2, 1);
        gridLayout_16->setColumnMinimumWidth(3, 1);

        horizontalLayout_55->addLayout(gridLayout_16);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_55->addItem(horizontalSpacer_6);

        horizontalLayout_55->setStretch(0, 1);
        horizontalLayout_55->setStretch(1, 3);
        SWidget_paraSetting->addWidget(houghPara);
        findCirclePara = new QWidget();
        findCirclePara->setObjectName(QStringLiteral("findCirclePara"));
        horizontalLayout_56 = new QHBoxLayout(findCirclePara);
        horizontalLayout_56->setSpacing(6);
        horizontalLayout_56->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_56->setObjectName(QStringLiteral("horizontalLayout_56"));
        gridLayout_17 = new QGridLayout();
        gridLayout_17->setSpacing(6);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        label_96 = new QLabel(findCirclePara);
        label_96->setObjectName(QStringLiteral("label_96"));
        label_96->setFont(font16);
        label_96->setFrameShape(QFrame::Box);

        gridLayout_17->addWidget(label_96, 5, 0, 1, 1);

        findCircle_percent = new QDoubleSpinBox(findCirclePara);
        findCircle_percent->setObjectName(QStringLiteral("findCircle_percent"));
        findCircle_percent->setFont(font12);
        findCircle_percent->setDecimals(0);
        findCircle_percent->setMaximum(100001);
        findCircle_percent->setValue(10);

        gridLayout_17->addWidget(findCircle_percent, 0, 1, 1, 1);

        findCircle_binaryThreshold = new QDoubleSpinBox(findCirclePara);
        findCircle_binaryThreshold->setObjectName(QStringLiteral("findCircle_binaryThreshold"));
        findCircle_binaryThreshold->setFont(font12);
        findCircle_binaryThreshold->setDecimals(0);
        findCircle_binaryThreshold->setMinimum(0);
        findCircle_binaryThreshold->setMaximum(255);
        findCircle_binaryThreshold->setValue(0);

        gridLayout_17->addWidget(findCircle_binaryThreshold, 4, 1, 1, 1);

        label_97 = new QLabel(findCirclePara);
        label_97->setObjectName(QStringLiteral("label_97"));
        label_97->setFont(font16);
        label_97->setFrameShape(QFrame::Box);

        gridLayout_17->addWidget(label_97, 0, 0, 1, 1);

        findCircle_countThreshold = new QDoubleSpinBox(findCirclePara);
        findCircle_countThreshold->setObjectName(QStringLiteral("findCircle_countThreshold"));
        findCircle_countThreshold->setFont(font12);
        findCircle_countThreshold->setDecimals(0);
        findCircle_countThreshold->setMaximum(100);
        findCircle_countThreshold->setValue(0);

        gridLayout_17->addWidget(findCircle_countThreshold, 5, 1, 1, 1);

        findCircle_maxRadius = new QSpinBox(findCirclePara);
        findCircle_maxRadius->setObjectName(QStringLiteral("findCircle_maxRadius"));
        findCircle_maxRadius->setFont(font17);
        findCircle_maxRadius->setMinimum(0);
        findCircle_maxRadius->setMaximum(100000);
        findCircle_maxRadius->setValue(0);

        gridLayout_17->addWidget(findCircle_maxRadius, 2, 1, 1, 1);

        findCircle_deviation = new QSpinBox(findCirclePara);
        findCircle_deviation->setObjectName(QStringLiteral("findCircle_deviation"));
        findCircle_deviation->setFont(font12);
        findCircle_deviation->setSingleStep(10);
        findCircle_deviation->setValue(10);

        gridLayout_17->addWidget(findCircle_deviation, 1, 1, 1, 1);

        label_98 = new QLabel(findCirclePara);
        label_98->setObjectName(QStringLiteral("label_98"));
        label_98->setFont(font16);
        label_98->setFrameShape(QFrame::Box);

        gridLayout_17->addWidget(label_98, 2, 0, 1, 1);

        label_99 = new QLabel(findCirclePara);
        label_99->setObjectName(QStringLiteral("label_99"));
        label_99->setFont(font16);
        label_99->setFrameShape(QFrame::Box);

        gridLayout_17->addWidget(label_99, 4, 0, 1, 1);

        label_100 = new QLabel(findCirclePara);
        label_100->setObjectName(QStringLiteral("label_100"));
        label_100->setFont(font16);
        label_100->setFrameShape(QFrame::Box);

        gridLayout_17->addWidget(label_100, 1, 0, 1, 1);

        label_101 = new QLabel(findCirclePara);
        label_101->setObjectName(QStringLiteral("label_101"));
        label_101->setFont(font16);
        label_101->setFrameShape(QFrame::Box);

        gridLayout_17->addWidget(label_101, 3, 0, 1, 1);

        findCircle_minRadius = new QSpinBox(findCirclePara);
        findCircle_minRadius->setObjectName(QStringLiteral("findCircle_minRadius"));
        findCircle_minRadius->setFont(font17);
        findCircle_minRadius->setMinimum(0);
        findCircle_minRadius->setMaximum(100000);
        findCircle_minRadius->setValue(0);

        gridLayout_17->addWidget(findCircle_minRadius, 3, 1, 1, 1);


        horizontalLayout_56->addLayout(gridLayout_17);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_56->addItem(horizontalSpacer_17);

        horizontalLayout_56->setStretch(0, 1);
        horizontalLayout_56->setStretch(1, 3);
        SWidget_paraSetting->addWidget(findCirclePara);
        chessbordPara = new QWidget();
        chessbordPara->setObjectName(QStringLiteral("chessbordPara"));
        gridLayout_18 = new QGridLayout(chessbordPara);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        label_102 = new QLabel(chessbordPara);
        label_102->setObjectName(QStringLiteral("label_102"));
        QFont font19;
        font19.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font19.setPointSize(12);
        font19.setBold(false);
        font19.setUnderline(false);
        font19.setWeight(50);
        label_102->setFont(font19);
        label_102->setFrameShape(QFrame::Box);

        gridLayout_18->addWidget(label_102, 0, 0, 1, 1);

        chessBoardCols = new QSpinBox(chessbordPara);
        chessBoardCols->setObjectName(QStringLiteral("chessBoardCols"));
        QFont font20;
        font20.setPointSize(15);
        font20.setBold(false);
        font20.setUnderline(false);
        font20.setWeight(50);
        chessBoardCols->setFont(font20);
        chessBoardCols->setMinimum(4);
        chessBoardCols->setMaximum(20);
        chessBoardCols->setSingleStep(3);
        chessBoardCols->setValue(4);

        gridLayout_18->addWidget(chessBoardCols, 0, 1, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(191, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_20, 0, 2, 1, 1);

        label_103 = new QLabel(chessbordPara);
        label_103->setObjectName(QStringLiteral("label_103"));
        QFont font21;
        font21.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font21.setPointSize(12);
        font21.setBold(false);
        font21.setUnderline(false);
        font21.setWeight(50);
        label_103->setFont(font21);
        label_103->setFrameShape(QFrame::Box);

        gridLayout_18->addWidget(label_103, 1, 0, 1, 1);

        chessBoardRows = new QSpinBox(chessbordPara);
        chessBoardRows->setObjectName(QStringLiteral("chessBoardRows"));
        chessBoardRows->setFont(font20);
        chessBoardRows->setMinimum(4);
        chessBoardRows->setMaximum(20);

        gridLayout_18->addWidget(chessBoardRows, 1, 1, 1, 1);

        horizontalSpacer_21 = new QSpacerItem(191, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_21, 1, 2, 1, 1);

        verticalSpacer_23 = new QSpacerItem(20, 161, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_18->addItem(verticalSpacer_23, 2, 0, 1, 1);

        SWidget_paraSetting->addWidget(chessbordPara);
        calibrate_dotPlatePara = new QWidget();
        calibrate_dotPlatePara->setObjectName(QStringLiteral("calibrate_dotPlatePara"));
        horizontalLayout_12 = new QHBoxLayout(calibrate_dotPlatePara);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_13 = new QLabel(calibrate_dotPlatePara);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font21);
        label_13->setFrameShape(QFrame::Box);

        gridLayout_5->addWidget(label_13, 5, 0, 1, 1);

        label_11 = new QLabel(calibrate_dotPlatePara);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font21);
        label_11->setFrameShape(QFrame::Box);

        gridLayout_5->addWidget(label_11, 0, 0, 1, 1);

        dotPlate_countThreshold = new QDoubleSpinBox(calibrate_dotPlatePara);
        dotPlate_countThreshold->setObjectName(QStringLiteral("dotPlate_countThreshold"));
        dotPlate_countThreshold->setFont(font15);
        dotPlate_countThreshold->setDecimals(0);
        dotPlate_countThreshold->setMaximum(100);
        dotPlate_countThreshold->setValue(0);

        gridLayout_5->addWidget(dotPlate_countThreshold, 5, 1, 1, 1);

        dotPlate_percent = new QDoubleSpinBox(calibrate_dotPlatePara);
        dotPlate_percent->setObjectName(QStringLiteral("dotPlate_percent"));
        dotPlate_percent->setFont(font15);
        dotPlate_percent->setDecimals(0);
        dotPlate_percent->setMaximum(100001);
        dotPlate_percent->setValue(10);

        gridLayout_5->addWidget(dotPlate_percent, 0, 1, 1, 1);

        dotPlate_binaryThreshold = new QDoubleSpinBox(calibrate_dotPlatePara);
        dotPlate_binaryThreshold->setObjectName(QStringLiteral("dotPlate_binaryThreshold"));
        dotPlate_binaryThreshold->setFont(font15);
        dotPlate_binaryThreshold->setDecimals(0);
        dotPlate_binaryThreshold->setMinimum(0);
        dotPlate_binaryThreshold->setMaximum(255);
        dotPlate_binaryThreshold->setValue(0);

        gridLayout_5->addWidget(dotPlate_binaryThreshold, 4, 1, 1, 1);

        label_12 = new QLabel(calibrate_dotPlatePara);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font21);
        label_12->setFrameShape(QFrame::Box);

        gridLayout_5->addWidget(label_12, 4, 0, 1, 1);

        label = new QLabel(calibrate_dotPlatePara);
        label->setObjectName(QStringLiteral("label"));
        QFont font22;
        font22.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font22.setPointSize(12);
        font22.setBold(false);
        font22.setWeight(50);
        label->setFont(font22);
        label->setFrameShape(QFrame::Box);

        gridLayout_5->addWidget(label, 1, 0, 1, 1);

        dotPlate_deviation = new QSpinBox(calibrate_dotPlatePara);
        dotPlate_deviation->setObjectName(QStringLiteral("dotPlate_deviation"));
        dotPlate_deviation->setFont(font15);
        dotPlate_deviation->setSingleStep(10);
        dotPlate_deviation->setValue(10);

        gridLayout_5->addWidget(dotPlate_deviation, 1, 1, 1, 1);

        dotPlate_maxRadius = new QSpinBox(calibrate_dotPlatePara);
        dotPlate_maxRadius->setObjectName(QStringLiteral("dotPlate_maxRadius"));
        dotPlate_maxRadius->setFont(font20);
        dotPlate_maxRadius->setMinimum(0);
        dotPlate_maxRadius->setMaximum(100000);
        dotPlate_maxRadius->setValue(0);

        gridLayout_5->addWidget(dotPlate_maxRadius, 2, 1, 1, 1);

        label_14 = new QLabel(calibrate_dotPlatePara);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font21);
        label_14->setFrameShape(QFrame::Box);

        gridLayout_5->addWidget(label_14, 2, 0, 1, 1);

        label_15 = new QLabel(calibrate_dotPlatePara);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font21);
        label_15->setFrameShape(QFrame::Box);

        gridLayout_5->addWidget(label_15, 3, 0, 1, 1);

        dotPlate_minRadius = new QSpinBox(calibrate_dotPlatePara);
        dotPlate_minRadius->setObjectName(QStringLiteral("dotPlate_minRadius"));
        dotPlate_minRadius->setFont(font20);
        dotPlate_minRadius->setMinimum(0);
        dotPlate_minRadius->setMaximum(100000);
        dotPlate_minRadius->setValue(0);

        gridLayout_5->addWidget(dotPlate_minRadius, 3, 1, 1, 1);


        horizontalLayout_12->addLayout(gridLayout_5);

        horizontalSpacer_18 = new QSpacerItem(719, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_18);

        SWidget_paraSetting->addWidget(calibrate_dotPlatePara);
        tempmatchPara = new QWidget();
        tempmatchPara->setObjectName(QStringLiteral("tempmatchPara"));
        gridLayout_24 = new QGridLayout(tempmatchPara);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QStringLiteral("gridLayout_24"));
        gridLayout_23 = new QGridLayout();
        gridLayout_23->setSpacing(6);
        gridLayout_23->setObjectName(QStringLiteral("gridLayout_23"));
        verticalLayout_28 = new QVBoxLayout();
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setObjectName(QStringLiteral("verticalLayout_28"));
        verticalLayout_27 = new QVBoxLayout();
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setObjectName(QStringLiteral("verticalLayout_27"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_104 = new QLabel(tempmatchPara);
        label_104->setObjectName(QStringLiteral("label_104"));
        label_104->setFont(font21);
        label_104->setFrameShape(QFrame::Box);

        horizontalLayout_9->addWidget(label_104);

        similarityCoefficient = new QDoubleSpinBox(tempmatchPara);
        similarityCoefficient->setObjectName(QStringLiteral("similarityCoefficient"));
        similarityCoefficient->setFont(font18);
        similarityCoefficient->setDecimals(4);
        similarityCoefficient->setMaximum(1);
        similarityCoefficient->setSingleStep(0.001);
        similarityCoefficient->setValue(0.1);

        horizontalLayout_9->addWidget(similarityCoefficient);

        horizontalSpacer_22 = new QSpacerItem(144, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_22);


        verticalLayout_27->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        btn_addTemp = new QPushButton(tempmatchPara);
        btn_addTemp->setObjectName(QStringLiteral("btn_addTemp"));
        QFont font23;
        font23.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font23.setPointSize(15);
        font23.setBold(false);
        font23.setUnderline(false);
        font23.setWeight(50);
        btn_addTemp->setFont(font23);

        horizontalLayout_11->addWidget(btn_addTemp);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_23);


        verticalLayout_27->addLayout(horizontalLayout_11);


        verticalLayout_28->addLayout(verticalLayout_27);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_28->addItem(verticalSpacer_15);


        gridLayout_23->addLayout(verticalLayout_28, 0, 0, 1, 1);

        verticalLayout_29 = new QVBoxLayout();
        verticalLayout_29->setSpacing(6);
        verticalLayout_29->setObjectName(QStringLiteral("verticalLayout_29"));
        widget_algorithmnTemp = new QWidget(tempmatchPara);
        widget_algorithmnTemp->setObjectName(QStringLiteral("widget_algorithmnTemp"));
        sizePolicy2.setHeightForWidth(widget_algorithmnTemp->sizePolicy().hasHeightForWidth());
        widget_algorithmnTemp->setSizePolicy(sizePolicy2);
        widget_algorithmnTemp->setMinimumSize(QSize(200, 200));
        lab_algorithmnTemp = new DM_Label(widget_algorithmnTemp);
        lab_algorithmnTemp->setObjectName(QStringLiteral("lab_algorithmnTemp"));
        lab_algorithmnTemp->setGeometry(QRect(40, 30, 121, 131));
        lab_algorithmnTemp->setFrameShape(QFrame::Box);
        lab_algorithmnTemp->setScaledContents(false);

        verticalLayout_29->addWidget(widget_algorithmnTemp);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_29->addItem(verticalSpacer_16);


        gridLayout_23->addLayout(verticalLayout_29, 0, 1, 1, 1);


        gridLayout_24->addLayout(gridLayout_23, 0, 0, 1, 1);

        SWidget_paraSetting->addWidget(tempmatchPara);
        splitter_6->addWidget(SWidget_paraSetting);

        verticalLayout_22->addWidget(splitter_6);


        horizontalLayout_10->addWidget(groupBox_18);

        SWidget_information->addWidget(page_paraSetting);
        page_modbusSetting = new QWidget();
        page_modbusSetting->setObjectName(QStringLiteral("page_modbusSetting"));
        horizontalLayout = new QHBoxLayout(page_modbusSetting);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_20 = new QGroupBox(page_modbusSetting);
        groupBox_20->setObjectName(QStringLiteral("groupBox_20"));
        groupBox_20->setFont(font2);
        groupBox_20->setAlignment(Qt::AlignCenter);
        gridLayout_15 = new QGridLayout(groupBox_20);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(0);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        label_3 = new QLabel(groupBox_20);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font4);
        label_3->setFrameShape(QFrame::NoFrame);

        verticalLayout_17->addWidget(label_3);

        label_40 = new QLabel(groupBox_20);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setFont(font4);

        verticalLayout_17->addWidget(label_40);

        label_45 = new QLabel(groupBox_20);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setFont(font4);

        verticalLayout_17->addWidget(label_45);

        label_36 = new QLabel(groupBox_20);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setFont(font4);

        verticalLayout_17->addWidget(label_36);

        label_47 = new QLabel(groupBox_20);
        label_47->setObjectName(QStringLiteral("label_47"));
        label_47->setFont(font4);

        verticalLayout_17->addWidget(label_47);

        verticalLayout_17->setStretch(0, 1);
        verticalLayout_17->setStretch(1, 1);
        verticalLayout_17->setStretch(2, 1);
        verticalLayout_17->setStretch(3, 1);
        verticalLayout_17->setStretch(4, 1);

        horizontalLayout_28->addLayout(verticalLayout_17);

        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        modbusIP = new QLineEdit(groupBox_20);
        modbusIP->setObjectName(QStringLiteral("modbusIP"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(modbusIP->sizePolicy().hasHeightForWidth());
        modbusIP->setSizePolicy(sizePolicy6);
        modbusIP->setMinimumSize(QSize(150, 0));
        modbusIP->setMaximumSize(QSize(200, 16777215));
        modbusIP->setFont(font4);

        verticalLayout_21->addWidget(modbusIP);

        modbusDataType = new QComboBox(groupBox_20);
        modbusDataType->addItem(QString());
        modbusDataType->addItem(QString());
        modbusDataType->addItem(QString());
        modbusDataType->addItem(QString());
        modbusDataType->setObjectName(QStringLiteral("modbusDataType"));
        sizePolicy6.setHeightForWidth(modbusDataType->sizePolicy().hasHeightForWidth());
        modbusDataType->setSizePolicy(sizePolicy6);
        modbusDataType->setMinimumSize(QSize(150, 0));
        modbusDataType->setMaximumSize(QSize(250, 16777215));
        modbusDataType->setFont(font4);

        verticalLayout_21->addWidget(modbusDataType);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        modbusScanTime = new QSpinBox(groupBox_20);
        modbusScanTime->setObjectName(QStringLiteral("modbusScanTime"));
        sizePolicy6.setHeightForWidth(modbusScanTime->sizePolicy().hasHeightForWidth());
        modbusScanTime->setSizePolicy(sizePolicy6);
        modbusScanTime->setMinimumSize(QSize(150, 0));
        modbusScanTime->setMaximumSize(QSize(200, 16777215));
        modbusScanTime->setFont(font4);
        modbusScanTime->setMinimum(20);
        modbusScanTime->setMaximum(9999);
        modbusScanTime->setValue(100);

        horizontalLayout_19->addWidget(modbusScanTime);

        label_44 = new QLabel(groupBox_20);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setFont(font4);

        horizontalLayout_19->addWidget(label_44);


        verticalLayout_21->addLayout(horizontalLayout_19);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(0);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        modbusTimeOut = new QSpinBox(groupBox_20);
        modbusTimeOut->setObjectName(QStringLiteral("modbusTimeOut"));
        sizePolicy6.setHeightForWidth(modbusTimeOut->sizePolicy().hasHeightForWidth());
        modbusTimeOut->setSizePolicy(sizePolicy6);
        modbusTimeOut->setMinimumSize(QSize(150, 0));
        modbusTimeOut->setMaximumSize(QSize(200, 16777215));
        modbusTimeOut->setFont(font4);
        modbusTimeOut->setMaximum(9999);
        modbusTimeOut->setValue(3000);

        horizontalLayout_27->addWidget(modbusTimeOut);

        label_46 = new QLabel(groupBox_20);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setFont(font4);

        horizontalLayout_27->addWidget(label_46);


        verticalLayout_21->addLayout(horizontalLayout_27);

        modbusRetries = new QSpinBox(groupBox_20);
        modbusRetries->setObjectName(QStringLiteral("modbusRetries"));
        sizePolicy6.setHeightForWidth(modbusRetries->sizePolicy().hasHeightForWidth());
        modbusRetries->setSizePolicy(sizePolicy6);
        modbusRetries->setMinimumSize(QSize(150, 0));
        modbusRetries->setMaximumSize(QSize(50, 16777215));
        modbusRetries->setFont(font4);
        modbusRetries->setMaximum(10);
        modbusRetries->setValue(5);

        verticalLayout_21->addWidget(modbusRetries);

        verticalLayout_21->setStretch(0, 1);
        verticalLayout_21->setStretch(1, 1);
        verticalLayout_21->setStretch(2, 1);
        verticalLayout_21->setStretch(3, 1);
        verticalLayout_21->setStretch(4, 1);

        horizontalLayout_28->addLayout(verticalLayout_21);


        verticalLayout_13->addLayout(horizontalLayout_28);

        verticalLayout_65 = new QVBoxLayout();
        verticalLayout_65->setSpacing(6);
        verticalLayout_65->setObjectName(QStringLiteral("verticalLayout_65"));
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_14);

        btn_modbusConnect = new QPushButton(groupBox_20);
        btn_modbusConnect->setObjectName(QStringLiteral("btn_modbusConnect"));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(btn_modbusConnect->sizePolicy().hasHeightForWidth());
        btn_modbusConnect->setSizePolicy(sizePolicy7);
        btn_modbusConnect->setMinimumSize(QSize(100, 0));
        btn_modbusConnect->setMaximumSize(QSize(200, 16777215));
        btn_modbusConnect->setFont(font4);

        horizontalLayout_32->addWidget(btn_modbusConnect);


        verticalLayout_65->addLayout(horizontalLayout_32);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QStringLiteral("horizontalLayout_37"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_15);

        btn_modbusTest = new QPushButton(groupBox_20);
        btn_modbusTest->setObjectName(QStringLiteral("btn_modbusTest"));
        sizePolicy7.setHeightForWidth(btn_modbusTest->sizePolicy().hasHeightForWidth());
        btn_modbusTest->setSizePolicy(sizePolicy7);
        btn_modbusTest->setMinimumSize(QSize(100, 0));
        btn_modbusTest->setMaximumSize(QSize(150, 16777215));
        btn_modbusTest->setFont(font4);

        horizontalLayout_37->addWidget(btn_modbusTest);


        verticalLayout_65->addLayout(horizontalLayout_37);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_65->addItem(verticalSpacer_11);

        verticalLayout_65->setStretch(0, 1);
        verticalLayout_65->setStretch(1, 1);

        verticalLayout_13->addLayout(verticalLayout_65);

        verticalSpacer_17 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_17);


        gridLayout_15->addLayout(verticalLayout_13, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_20);

        groupBox_8 = new QGroupBox(page_modbusSetting);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setFont(font2);
        groupBox_8->setAlignment(Qt::AlignCenter);
        verticalLayout_40 = new QVBoxLayout(groupBox_8);
        verticalLayout_40->setSpacing(6);
        verticalLayout_40->setContentsMargins(11, 11, 11, 11);
        verticalLayout_40->setObjectName(QStringLiteral("verticalLayout_40"));
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(0);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        verticalLayout_41 = new QVBoxLayout();
        verticalLayout_41->setSpacing(6);
        verticalLayout_41->setObjectName(QStringLiteral("verticalLayout_41"));
        label_5 = new QLabel(groupBox_8);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);
        label_5->setMinimumSize(QSize(0, 25));
        label_5->setFont(font4);

        verticalLayout_41->addWidget(label_5);

        label_55 = new QLabel(groupBox_8);
        label_55->setObjectName(QStringLiteral("label_55"));
        sizePolicy3.setHeightForWidth(label_55->sizePolicy().hasHeightForWidth());
        label_55->setSizePolicy(sizePolicy3);
        label_55->setMinimumSize(QSize(0, 25));
        label_55->setFont(font4);

        verticalLayout_41->addWidget(label_55);

        label_57 = new QLabel(groupBox_8);
        label_57->setObjectName(QStringLiteral("label_57"));
        sizePolicy3.setHeightForWidth(label_57->sizePolicy().hasHeightForWidth());
        label_57->setSizePolicy(sizePolicy3);
        label_57->setMinimumSize(QSize(0, 25));
        label_57->setFont(font4);

        verticalLayout_41->addWidget(label_57);

        label_58 = new QLabel(groupBox_8);
        label_58->setObjectName(QStringLiteral("label_58"));
        sizePolicy3.setHeightForWidth(label_58->sizePolicy().hasHeightForWidth());
        label_58->setSizePolicy(sizePolicy3);
        label_58->setMinimumSize(QSize(0, 25));
        label_58->setFont(font4);

        verticalLayout_41->addWidget(label_58);

        label_59 = new QLabel(groupBox_8);
        label_59->setObjectName(QStringLiteral("label_59"));
        sizePolicy3.setHeightForWidth(label_59->sizePolicy().hasHeightForWidth());
        label_59->setSizePolicy(sizePolicy3);
        label_59->setMinimumSize(QSize(0, 25));
        label_59->setFont(font4);

        verticalLayout_41->addWidget(label_59);

        label_139 = new QLabel(groupBox_8);
        label_139->setObjectName(QStringLiteral("label_139"));
        sizePolicy3.setHeightForWidth(label_139->sizePolicy().hasHeightForWidth());
        label_139->setSizePolicy(sizePolicy3);
        label_139->setMinimumSize(QSize(0, 25));
        label_139->setFont(font4);

        verticalLayout_41->addWidget(label_139);

        verticalLayout_41->setStretch(0, 1);
        verticalLayout_41->setStretch(1, 1);
        verticalLayout_41->setStretch(2, 1);
        verticalLayout_41->setStretch(3, 1);
        verticalLayout_41->setStretch(4, 1);
        verticalLayout_41->setStretch(5, 1);

        horizontalLayout_25->addLayout(verticalLayout_41);

        verticalLayout_66 = new QVBoxLayout();
        verticalLayout_66->setSpacing(6);
        verticalLayout_66->setObjectName(QStringLiteral("verticalLayout_66"));
        modbusPort_R = new QSpinBox(groupBox_8);
        modbusPort_R->setObjectName(QStringLiteral("modbusPort_R"));
        sizePolicy3.setHeightForWidth(modbusPort_R->sizePolicy().hasHeightForWidth());
        modbusPort_R->setSizePolicy(sizePolicy3);
        modbusPort_R->setMinimumSize(QSize(150, 25));
        modbusPort_R->setFont(font4);
        modbusPort_R->setMaximum(1000);
        modbusPort_R->setValue(502);

        verticalLayout_66->addWidget(modbusPort_R);

        modbusSeverID_R = new QSpinBox(groupBox_8);
        modbusSeverID_R->setObjectName(QStringLiteral("modbusSeverID_R"));
        sizePolicy3.setHeightForWidth(modbusSeverID_R->sizePolicy().hasHeightForWidth());
        modbusSeverID_R->setSizePolicy(sizePolicy3);
        modbusSeverID_R->setMinimumSize(QSize(150, 25));
        modbusSeverID_R->setFont(font4);
        modbusSeverID_R->setMaximum(10000);
        modbusSeverID_R->setValue(1);

        verticalLayout_66->addWidget(modbusSeverID_R);

        modbusStartRegister_R = new QSpinBox(groupBox_8);
        modbusStartRegister_R->setObjectName(QStringLiteral("modbusStartRegister_R"));
        sizePolicy3.setHeightForWidth(modbusStartRegister_R->sizePolicy().hasHeightForWidth());
        modbusStartRegister_R->setSizePolicy(sizePolicy3);
        modbusStartRegister_R->setMinimumSize(QSize(150, 25));
        modbusStartRegister_R->setFont(font4);

        verticalLayout_66->addWidget(modbusStartRegister_R);

        modbusNumData_R = new QSpinBox(groupBox_8);
        modbusNumData_R->setObjectName(QStringLiteral("modbusNumData_R"));
        sizePolicy3.setHeightForWidth(modbusNumData_R->sizePolicy().hasHeightForWidth());
        modbusNumData_R->setSizePolicy(sizePolicy3);
        modbusNumData_R->setMinimumSize(QSize(150, 0));
        QFont font24;
        font24.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font24.setPointSize(14);
        font24.setBold(true);
        font24.setItalic(false);
        font24.setWeight(75);
        modbusNumData_R->setFont(font24);
        modbusNumData_R->setStyleSheet(QStringLiteral("background-color: rgb(184, 184, 184);"));
        modbusNumData_R->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        modbusNumData_R->setReadOnly(true);
        modbusNumData_R->setButtonSymbols(QAbstractSpinBox::NoButtons);
        modbusNumData_R->setAccelerated(false);
        modbusNumData_R->setMinimum(0);
        modbusNumData_R->setMaximum(9);
        modbusNumData_R->setSingleStep(9);
        modbusNumData_R->setValue(9);

        verticalLayout_66->addWidget(modbusNumData_R);

        modbusStatus_R = new QLabel(groupBox_8);
        modbusStatus_R->setObjectName(QStringLiteral("modbusStatus_R"));
        sizePolicy3.setHeightForWidth(modbusStatus_R->sizePolicy().hasHeightForWidth());
        modbusStatus_R->setSizePolicy(sizePolicy3);
        modbusStatus_R->setMinimumSize(QSize(150, 25));
        modbusStatus_R->setFont(font2);
        modbusStatus_R->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        modbusStatus_R->setFrameShape(QFrame::Box);
        modbusStatus_R->setIndent(0);
        modbusStatus_R->setOpenExternalLinks(false);

        verticalLayout_66->addWidget(modbusStatus_R);

        btn_modbusclose_R = new QToolButton(groupBox_8);
        btn_modbusclose_R->setObjectName(QStringLiteral("btn_modbusclose_R"));
        btn_modbusclose_R->setEnabled(true);
        sizePolicy3.setHeightForWidth(btn_modbusclose_R->sizePolicy().hasHeightForWidth());
        btn_modbusclose_R->setSizePolicy(sizePolicy3);
        btn_modbusclose_R->setMinimumSize(QSize(150, 25));
        QFont font25;
        font25.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        btn_modbusclose_R->setFont(font25);
        btn_modbusclose_R->setTabletTracking(false);
        btn_modbusclose_R->setStyleSheet(QLatin1String("QToolButton{ \n"
"color:rgb(255, 255, 255); \n"
"border-style:solid; \n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241), \n"
"stop: 0.3 rgb(160,160,160), \n"
"stop: 1 rgb(140,140,140)); \n"
"border:1px; \n"
"background:transparent;\n"
"padding:1px 1px;\n"
"} "));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/icon/img/icon/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon20.addFile(QStringLiteral(":/icon/img/icon/open1.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_modbusclose_R->setIcon(icon20);
        btn_modbusclose_R->setIconSize(QSize(100, 25));
        btn_modbusclose_R->setCheckable(true);
        btn_modbusclose_R->setChecked(false);
        btn_modbusclose_R->setAutoRaise(false);

        verticalLayout_66->addWidget(btn_modbusclose_R);

        verticalLayout_66->setStretch(0, 1);
        verticalLayout_66->setStretch(1, 1);
        verticalLayout_66->setStretch(2, 1);
        verticalLayout_66->setStretch(3, 1);
        verticalLayout_66->setStretch(4, 1);
        verticalLayout_66->setStretch(5, 1);

        horizontalLayout_25->addLayout(verticalLayout_66);


        verticalLayout_40->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(0);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        verticalLayout_42 = new QVBoxLayout();
        verticalLayout_42->setSpacing(6);
        verticalLayout_42->setObjectName(QStringLiteral("verticalLayout_42"));
        lineEdit_9 = new QLineEdit(groupBox_8);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        QFont font26;
        font26.setPointSize(14);
        lineEdit_9->setFont(font26);
        lineEdit_9->setAlignment(Qt::AlignCenter);

        verticalLayout_42->addWidget(lineEdit_9);

        lineEdit_24 = new QLineEdit(groupBox_8);
        lineEdit_24->setObjectName(QStringLiteral("lineEdit_24"));
        lineEdit_24->setFont(font4);
        lineEdit_24->setAlignment(Qt::AlignCenter);

        verticalLayout_42->addWidget(lineEdit_24);

        lineEdit_25 = new QLineEdit(groupBox_8);
        lineEdit_25->setObjectName(QStringLiteral("lineEdit_25"));
        lineEdit_25->setFont(font4);
        lineEdit_25->setAlignment(Qt::AlignCenter);

        verticalLayout_42->addWidget(lineEdit_25);


        horizontalLayout_26->addLayout(verticalLayout_42);

        verticalLayout_43 = new QVBoxLayout();
        verticalLayout_43->setSpacing(6);
        verticalLayout_43->setObjectName(QStringLiteral("verticalLayout_43"));
        lineEdit_12 = new QLineEdit(groupBox_8);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        lineEdit_12->setFont(font26);
        lineEdit_12->setAlignment(Qt::AlignCenter);

        verticalLayout_43->addWidget(lineEdit_12);

        modbusReadData0 = new QDoubleSpinBox(groupBox_8);
        modbusReadData0->setObjectName(QStringLiteral("modbusReadData0"));
        modbusReadData0->setFont(font4);
        modbusReadData0->setAlignment(Qt::AlignCenter);
        modbusReadData0->setReadOnly(true);
        modbusReadData0->setButtonSymbols(QAbstractSpinBox::NoButtons);
        modbusReadData0->setMaximum(1e+9);

        verticalLayout_43->addWidget(modbusReadData0);

        modbusReadData1 = new QDoubleSpinBox(groupBox_8);
        modbusReadData1->setObjectName(QStringLiteral("modbusReadData1"));
        modbusReadData1->setFont(font4);
        modbusReadData1->setAlignment(Qt::AlignCenter);
        modbusReadData1->setReadOnly(false);
        modbusReadData1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        modbusReadData1->setMaximum(1e+8);

        verticalLayout_43->addWidget(modbusReadData1);


        horizontalLayout_26->addLayout(verticalLayout_43);


        verticalLayout_40->addLayout(horizontalLayout_26);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_40->addItem(verticalSpacer_8);

        verticalLayout_40->setStretch(0, 2);
        verticalLayout_40->setStretch(1, 1);

        horizontalLayout->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(page_modbusSetting);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setFont(font24);
        groupBox_9->setStyleSheet(QStringLiteral(""));
        groupBox_9->setAlignment(Qt::AlignCenter);
        verticalLayout_31 = new QVBoxLayout(groupBox_9);
        verticalLayout_31->setSpacing(6);
        verticalLayout_31->setContentsMargins(11, 11, 11, 11);
        verticalLayout_31->setObjectName(QStringLiteral("verticalLayout_31"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        verticalLayout_63 = new QVBoxLayout();
        verticalLayout_63->setSpacing(6);
        verticalLayout_63->setObjectName(QStringLiteral("verticalLayout_63"));
        label_41 = new QLabel(groupBox_9);
        label_41->setObjectName(QStringLiteral("label_41"));
        sizePolicy3.setHeightForWidth(label_41->sizePolicy().hasHeightForWidth());
        label_41->setSizePolicy(sizePolicy3);
        label_41->setMinimumSize(QSize(0, 25));
        label_41->setFont(font24);

        verticalLayout_63->addWidget(label_41);

        label_42 = new QLabel(groupBox_9);
        label_42->setObjectName(QStringLiteral("label_42"));
        sizePolicy3.setHeightForWidth(label_42->sizePolicy().hasHeightForWidth());
        label_42->setSizePolicy(sizePolicy3);
        label_42->setMinimumSize(QSize(0, 25));
        label_42->setFont(font24);

        verticalLayout_63->addWidget(label_42);

        label_37 = new QLabel(groupBox_9);
        label_37->setObjectName(QStringLiteral("label_37"));
        sizePolicy3.setHeightForWidth(label_37->sizePolicy().hasHeightForWidth());
        label_37->setSizePolicy(sizePolicy3);
        label_37->setMinimumSize(QSize(0, 25));
        label_37->setFont(font24);

        verticalLayout_63->addWidget(label_37);

        label_38 = new QLabel(groupBox_9);
        label_38->setObjectName(QStringLiteral("label_38"));
        sizePolicy3.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy3);
        label_38->setMinimumSize(QSize(0, 25));
        label_38->setFont(font24);

        verticalLayout_63->addWidget(label_38);

        label_56 = new QLabel(groupBox_9);
        label_56->setObjectName(QStringLiteral("label_56"));
        sizePolicy3.setHeightForWidth(label_56->sizePolicy().hasHeightForWidth());
        label_56->setSizePolicy(sizePolicy3);
        label_56->setMinimumSize(QSize(0, 25));

        verticalLayout_63->addWidget(label_56);

        verticalLayout_63->setStretch(0, 1);
        verticalLayout_63->setStretch(1, 1);
        verticalLayout_63->setStretch(2, 1);
        verticalLayout_63->setStretch(3, 1);
        verticalLayout_63->setStretch(4, 1);

        horizontalLayout_23->addLayout(verticalLayout_63);

        verticalLayout_64 = new QVBoxLayout();
        verticalLayout_64->setSpacing(6);
        verticalLayout_64->setObjectName(QStringLiteral("verticalLayout_64"));
        modbusPort_W = new QSpinBox(groupBox_9);
        modbusPort_W->setObjectName(QStringLiteral("modbusPort_W"));
        sizePolicy3.setHeightForWidth(modbusPort_W->sizePolicy().hasHeightForWidth());
        modbusPort_W->setSizePolicy(sizePolicy3);
        modbusPort_W->setMinimumSize(QSize(150, 25));
        modbusPort_W->setFont(font24);
        modbusPort_W->setMaximum(1000);
        modbusPort_W->setValue(503);

        verticalLayout_64->addWidget(modbusPort_W);

        modbusSeverID_W = new QSpinBox(groupBox_9);
        modbusSeverID_W->setObjectName(QStringLiteral("modbusSeverID_W"));
        sizePolicy3.setHeightForWidth(modbusSeverID_W->sizePolicy().hasHeightForWidth());
        modbusSeverID_W->setSizePolicy(sizePolicy3);
        modbusSeverID_W->setMinimumSize(QSize(150, 25));
        modbusSeverID_W->setFont(font24);
        modbusSeverID_W->setMaximum(10000);
        modbusSeverID_W->setValue(1);

        verticalLayout_64->addWidget(modbusSeverID_W);

        modbusStartRegister_W = new QSpinBox(groupBox_9);
        modbusStartRegister_W->setObjectName(QStringLiteral("modbusStartRegister_W"));
        sizePolicy3.setHeightForWidth(modbusStartRegister_W->sizePolicy().hasHeightForWidth());
        modbusStartRegister_W->setSizePolicy(sizePolicy3);
        modbusStartRegister_W->setMinimumSize(QSize(150, 25));
        modbusStartRegister_W->setFont(font24);
        modbusStartRegister_W->setMaximum(1000);
        modbusStartRegister_W->setValue(0);

        verticalLayout_64->addWidget(modbusStartRegister_W);

        modbusNumData_W = new QSpinBox(groupBox_9);
        modbusNumData_W->setObjectName(QStringLiteral("modbusNumData_W"));
        sizePolicy3.setHeightForWidth(modbusNumData_W->sizePolicy().hasHeightForWidth());
        modbusNumData_W->setSizePolicy(sizePolicy3);
        modbusNumData_W->setMinimumSize(QSize(150, 25));
        modbusNumData_W->setFont(font24);
        modbusNumData_W->setMinimum(1);
        modbusNumData_W->setMaximum(99999);
        modbusNumData_W->setValue(20);

        verticalLayout_64->addWidget(modbusNumData_W);

        modbusStatus_W = new QLabel(groupBox_9);
        modbusStatus_W->setObjectName(QStringLiteral("modbusStatus_W"));
        sizePolicy3.setHeightForWidth(modbusStatus_W->sizePolicy().hasHeightForWidth());
        modbusStatus_W->setSizePolicy(sizePolicy3);
        modbusStatus_W->setMinimumSize(QSize(150, 25));
        modbusStatus_W->setFont(font2);
        modbusStatus_W->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        modbusStatus_W->setFrameShape(QFrame::Box);

        verticalLayout_64->addWidget(modbusStatus_W);

        verticalLayout_64->setStretch(0, 1);
        verticalLayout_64->setStretch(1, 1);
        verticalLayout_64->setStretch(2, 1);
        verticalLayout_64->setStretch(3, 1);
        verticalLayout_64->setStretch(4, 1);

        horizontalLayout_23->addLayout(verticalLayout_64);


        verticalLayout_31->addLayout(horizontalLayout_23);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(0);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        lineEdit_6 = new QLineEdit(groupBox_9);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setFont(font26);
        lineEdit_6->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(lineEdit_6);

        lineEdit_20 = new QLineEdit(groupBox_9);
        lineEdit_20->setObjectName(QStringLiteral("lineEdit_20"));
        lineEdit_20->setFont(font26);
        lineEdit_20->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(lineEdit_20);

        lineEdit_21 = new QLineEdit(groupBox_9);
        lineEdit_21->setObjectName(QStringLiteral("lineEdit_21"));
        lineEdit_21->setFont(font26);
        lineEdit_21->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(lineEdit_21);


        horizontalLayout_22->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        lineEdit_7 = new QLineEdit(groupBox_9);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setFont(font26);
        lineEdit_7->setAlignment(Qt::AlignCenter);

        verticalLayout_15->addWidget(lineEdit_7);

        modbusWriteData0 = new QDoubleSpinBox(groupBox_9);
        modbusWriteData0->setObjectName(QStringLiteral("modbusWriteData0"));
        modbusWriteData0->setFont(font26);
        modbusWriteData0->setAlignment(Qt::AlignCenter);
        modbusWriteData0->setReadOnly(false);
        modbusWriteData0->setButtonSymbols(QAbstractSpinBox::NoButtons);
        modbusWriteData0->setMaximum(1e+9);

        verticalLayout_15->addWidget(modbusWriteData0);

        modbusWriteData1 = new QDoubleSpinBox(groupBox_9);
        modbusWriteData1->setObjectName(QStringLiteral("modbusWriteData1"));
        modbusWriteData1->setFont(font26);
        modbusWriteData1->setAlignment(Qt::AlignCenter);
        modbusWriteData1->setReadOnly(false);
        modbusWriteData1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        modbusWriteData1->setMaximum(1e+8);

        verticalLayout_15->addWidget(modbusWriteData1);


        horizontalLayout_22->addLayout(verticalLayout_15);


        verticalLayout_31->addLayout(horizontalLayout_22);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_31->addItem(verticalSpacer_14);

        verticalLayout_31->setStretch(0, 2);
        verticalLayout_31->setStretch(1, 1);

        horizontalLayout->addWidget(groupBox_9);

        SWidget_information->addWidget(page_modbusSetting);
        page_cameraSetting = new QWidget();
        page_cameraSetting->setObjectName(QStringLiteral("page_cameraSetting"));
        gridLayout_2 = new QGridLayout(page_cameraSetting);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_13 = new QGroupBox(page_cameraSetting);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(10);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(groupBox_13->sizePolicy().hasHeightForWidth());
        groupBox_13->setSizePolicy(sizePolicy8);
        groupBox_13->setFont(font2);
        groupBox_13->setAlignment(Qt::AlignCenter);
        verticalLayout_10 = new QVBoxLayout(groupBox_13);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_2 = new QLabel(groupBox_13);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_6->addWidget(label_2);

        comB_cameraBrand = new QComboBox(groupBox_13);
        comB_cameraBrand->addItem(QString());
        comB_cameraBrand->addItem(QString());
        comB_cameraBrand->setObjectName(QStringLiteral("comB_cameraBrand"));

        horizontalLayout_6->addWidget(comB_cameraBrand);

        btn_connectCamera = new QPushButton(groupBox_13);
        btn_connectCamera->setObjectName(QStringLiteral("btn_connectCamera"));

        horizontalLayout_6->addWidget(btn_connectCamera);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_10->addLayout(horizontalLayout_6);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(0);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_48 = new QLabel(groupBox_13);
        label_48->setObjectName(QStringLiteral("label_48"));

        horizontalLayout_20->addWidget(label_48);

        cameraExposureSlider = new DM_Slider(groupBox_13);
        cameraExposureSlider->setObjectName(QStringLiteral("cameraExposureSlider"));
        cameraExposureSlider->setMinimum(1);
        cameraExposureSlider->setMaximum(999999);
        cameraExposureSlider->setPageStep(100);
        cameraExposureSlider->setValue(20000);
        cameraExposureSlider->setSliderPosition(20000);
        cameraExposureSlider->setTracking(true);
        cameraExposureSlider->setOrientation(Qt::Horizontal);
        cameraExposureSlider->setInvertedAppearance(false);
        cameraExposureSlider->setInvertedControls(false);
        cameraExposureSlider->setTickPosition(QSlider::NoTicks);
        cameraExposureSlider->setTickInterval(100);

        horizontalLayout_20->addWidget(cameraExposureSlider);

        horizontalLayout_20->setStretch(0, 1);
        horizontalLayout_20->setStretch(1, 10);

        verticalLayout_10->addLayout(horizontalLayout_20);

        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(0);
        horizontalLayout_48->setObjectName(QStringLiteral("horizontalLayout_48"));
        label_49 = new QLabel(groupBox_13);
        label_49->setObjectName(QStringLiteral("label_49"));

        horizontalLayout_48->addWidget(label_49);

        cameraFrameRate = new QDoubleSpinBox(groupBox_13);
        cameraFrameRate->setObjectName(QStringLiteral("cameraFrameRate"));
        cameraFrameRate->setMinimum(0.5);
        cameraFrameRate->setMaximum(20);

        horizontalLayout_48->addWidget(cameraFrameRate);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_48->addItem(horizontalSpacer_10);

        horizontalLayout_48->setStretch(0, 1);
        horizontalLayout_48->setStretch(1, 2);
        horizontalLayout_48->setStretch(2, 10);

        verticalLayout_10->addLayout(horizontalLayout_48);

        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(0);
        horizontalLayout_50->setObjectName(QStringLiteral("horizontalLayout_50"));
        label_50 = new QLabel(groupBox_13);
        label_50->setObjectName(QStringLiteral("label_50"));

        horizontalLayout_50->addWidget(label_50);

        camareTriggerType = new QComboBox(groupBox_13);
        camareTriggerType->addItem(QString());
        camareTriggerType->addItem(QString());
        camareTriggerType->addItem(QString());
        camareTriggerType->setObjectName(QStringLiteral("camareTriggerType"));

        horizontalLayout_50->addWidget(camareTriggerType);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_50->addItem(horizontalSpacer_11);

        horizontalLayout_50->setStretch(0, 1);
        horizontalLayout_50->setStretch(1, 5);
        horizontalLayout_50->setStretch(2, 1);

        verticalLayout_10->addLayout(horizontalLayout_50);


        gridLayout_2->addWidget(groupBox_13, 0, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 1, 1, 1);

        groupBox_14 = new QGroupBox(page_cameraSetting);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setFont(font2);
        groupBox_14->setAlignment(Qt::AlignCenter);
        verticalLayout_18 = new QVBoxLayout(groupBox_14);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_18->addItem(horizontalSpacer_5);

        horizontalLayout_54 = new QHBoxLayout();
        horizontalLayout_54->setSpacing(0);
        horizontalLayout_54->setObjectName(QStringLiteral("horizontalLayout_54"));
        label_52 = new QLabel(groupBox_14);
        label_52->setObjectName(QStringLiteral("label_52"));

        horizontalLayout_54->addWidget(label_52);

        saveCameraImagePathlineEdit = new QLineEdit(groupBox_14);
        saveCameraImagePathlineEdit->setObjectName(QStringLiteral("saveCameraImagePathlineEdit"));
        saveCameraImagePathlineEdit->setReadOnly(true);

        horizontalLayout_54->addWidget(saveCameraImagePathlineEdit);

        btn_saveCameraImagePath = new QToolButton(groupBox_14);
        btn_saveCameraImagePath->setObjectName(QStringLiteral("btn_saveCameraImagePath"));
        btn_saveCameraImagePath->setStyleSheet(QLatin1String("QToolButton{ \n"
"color:rgb(255, 255, 255); \n"
"border-style:solid; \n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241), \n"
"stop: 0.3 rgb(160,160,160), \n"
"stop: 1 rgb(140,140,140)); \n"
"border:1px; \n"
"background:transparent;\n"
"padding:1px 1px;\n"
"} "));
        btn_saveCameraImagePath->setIcon(icon);
        btn_saveCameraImagePath->setIconSize(QSize(24, 24));

        horizontalLayout_54->addWidget(btn_saveCameraImagePath);

        horizontalLayout_54->setStretch(0, 2);
        horizontalLayout_54->setStretch(1, 10);
        horizontalLayout_54->setStretch(2, 1);

        verticalLayout_18->addLayout(horizontalLayout_54);

        horizontalLayout_51 = new QHBoxLayout();
        horizontalLayout_51->setSpacing(0);
        horizontalLayout_51->setObjectName(QStringLiteral("horizontalLayout_51"));
        label_51 = new QLabel(groupBox_14);
        label_51->setObjectName(QStringLiteral("label_51"));

        horizontalLayout_51->addWidget(label_51);

        btn_autosaveImage = new QToolButton(groupBox_14);
        btn_autosaveImage->setObjectName(QStringLiteral("btn_autosaveImage"));
        btn_autosaveImage->setEnabled(true);
        btn_autosaveImage->setTabletTracking(false);
        btn_autosaveImage->setStyleSheet(QLatin1String("QToolButton{ \n"
"color:rgb(255, 255, 255); \n"
"border-style:solid; \n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241), \n"
"stop: 0.3 rgb(160,160,160), \n"
"stop: 1 rgb(140,140,140)); \n"
"border:1px; \n"
"background:transparent;\n"
"padding:1px 1px;\n"
"} "));
        btn_autosaveImage->setIcon(icon20);
        btn_autosaveImage->setIconSize(QSize(100, 30));
        btn_autosaveImage->setCheckable(true);
        btn_autosaveImage->setChecked(false);
        btn_autosaveImage->setAutoRaise(false);

        horizontalLayout_51->addWidget(btn_autosaveImage);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_51->addItem(horizontalSpacer_9);

        horizontalLayout_51->setStretch(0, 1);
        horizontalLayout_51->setStretch(1, 1);
        horizontalLayout_51->setStretch(2, 20);

        verticalLayout_18->addLayout(horizontalLayout_51);


        gridLayout_2->addWidget(groupBox_14, 1, 0, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 1, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 2, 0, 1, 1);

        SWidget_information->addWidget(page_cameraSetting);
        splitter->addWidget(SWidget_information);
        systemStatusBar = new QTextBrowser(splitter);
        systemStatusBar->setObjectName(QStringLiteral("systemStatusBar"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(systemStatusBar->sizePolicy().hasHeightForWidth());
        systemStatusBar->setSizePolicy(sizePolicy9);
        systemStatusBar->setMinimumSize(QSize(0, 25));
        systemStatusBar->setMaximumSize(QSize(16777215, 16777214));
        systemStatusBar->setBaseSize(QSize(0, 50));
        systemStatusBar->setFont(font);
        splitter->addWidget(systemStatusBar);
        splitter_4->addWidget(splitter);
        splitter_5->addWidget(splitter_4);

        gridLayout->addWidget(splitter_5, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1235, 23));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_help = new QMenu(menuBar);
        menu_help->setObjectName(QStringLiteral("menu_help"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setFont(font2);
        statusBar->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        lab_calibrateImage->setBuddy(lab_calibrateImage);
#endif // QT_NO_SHORTCUT

        toolBar->addAction(action_LoadProject);
        toolBar->addAction(action_NewProject);
        toolBar->addAction(action_SaveProject);
        toolBar->addAction(action_LoadImg);
        toolBar->addSeparator();
        toolBar->addAction(action_imageZoomIn);
        toolBar->addAction(action_imageZoomOut);
        toolBar->addAction(action_ImageFitScreen);
        toolBar->addAction(action_cameraStop);
        toolBar->addAction(action_cameraStart);
        toolBar->addAction(action_takePicture);
        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_help->menuAction());
        menu_File->addAction(action_LoadProject);
        menu_File->addSeparator();
        menu_File->addAction(action_NewProject);
        menu_File->addSeparator();
        menu_File->addAction(action_SaveProject);
        menu_File->addSeparator();
        menu_File->addSeparator();
        menu_File->addAction(action_LoadImg);
        menu_File->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(action_LoadImg, SIGNAL(triggered()), MainWindow, SLOT(loadImage()));
        QObject::connect(action_SaveProject, SIGNAL(triggered()), MainWindow, SLOT(saveProject()));
        QObject::connect(action_NewProject, SIGNAL(triggered()), MainWindow, SLOT(newProject()));
        QObject::connect(action_LoadProject, SIGNAL(triggered()), MainWindow, SLOT(loadProject()));
        QObject::connect(action_imageZoomOut, SIGNAL(triggered()), MainWindow, SLOT(cameraImage_zoomOut()));
        QObject::connect(action_imageZoomIn, SIGNAL(triggered()), MainWindow, SLOT(cameraImage_zoomIn()));
        QObject::connect(action_ImageFitScreen, SIGNAL(triggered()), MainWindow, SLOT(cameraImage_fitScreen()));
        QObject::connect(action_cameraStop, SIGNAL(triggered()), MainWindow, SLOT(cameraImage_cameraStop()));
        QObject::connect(action_cameraStart, SIGNAL(triggered()), MainWindow, SLOT(cameraImage_cameraStart()));
        QObject::connect(action_takePicture, SIGNAL(triggered()), MainWindow, SLOT(cameraImage_takePicture()));

        SWidget_image->setCurrentIndex(1);
        SWidget_coordinate->setCurrentIndex(1);
        SWidget_table->setCurrentIndex(0);
        SWidget_toolsDirectory->setCurrentIndex(0);
        SWidget_information->setCurrentIndex(2);
        SWidget_paraInformation->setCurrentIndex(19);
        SWidget_paraSetting->setCurrentIndex(10);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_LoadProject->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\351\241\271\347\233\256", nullptr));
        action_NewProject->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        action_SaveProject->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\351\241\271\347\233\256", nullptr));
        action_LoadImg->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\345\233\276\347\211\207", nullptr));
        action_cameraStart->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        action_cameraStop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        action_imageZoomIn->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\346\224\276\345\244\247", nullptr));
        action_imageZoomOut->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\347\274\251\345\260\217", nullptr));
        action_ImageFitScreen->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\351\200\202\345\261\217", nullptr));
        action_takePicture->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", nullptr));
        btn_ProjFirst->setText(QApplication::translate("MainWindow", "first", nullptr));
        btn_ProjNext->setText(QApplication::translate("MainWindow", "next", nullptr));
        btn_ProjPrev->setText(QApplication::translate("MainWindow", "prev", nullptr));
        btn_ProjFinal->setText(QApplication::translate("MainWindow", "final", nullptr));
        btn_ProjPlay->setText(QApplication::translate("MainWindow", "play", nullptr));
        lab_algorithmImage->setText(QApplication::translate("MainWindow", "\345\256\232\344\275\215\345\233\276\345\203\217", nullptr));
        algorithmImageInfo->setText(QString());
        lab_calibrateImage->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\345\233\276\345\203\217", nullptr));
        calibrateImageInfo->setText(QString());
        lab_cameraVideo->setText(QApplication::translate("MainWindow", " \347\233\270\346\234\272\345\233\276\347\211\207", nullptr));
        cameraVideoInfo->setText(QString());
        groupBox_16->setTitle(QApplication::translate("MainWindow", " \345\235\220\346\240\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem = table_algorithmCoordinate->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\345\235\220\346\240\207\347\263\273\347\273\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_algorithmCoordinate->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\234\272\346\242\260\350\207\202\345\235\220\346\240\207\347\263\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table_algorithmCoordinate->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = table_algorithmCoordinate->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = table_calibrateCoordinate->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\345\235\220\346\240\207\347\263\273\347\273\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = table_calibrateCoordinate->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\346\234\272\346\242\260\350\207\202\345\235\220\346\240\207\347\263\273\347\273\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = table_calibrateCoordinate->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = table_calibrateCoordinate->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = table_calibrateCoordinate->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = table_calibrateCoordinate->verticalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = table_calibrateCoordinate->verticalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = table_calibrateCoordinate->verticalHeaderItem(5);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = table_calibrateCoordinate->verticalHeaderItem(6);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = table_calibrateCoordinate->verticalHeaderItem(7);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = table_calibrateCoordinate->verticalHeaderItem(8);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "9", nullptr));

        const bool __sortingEnabled = table_calibrateCoordinate->isSortingEnabled();
        table_calibrateCoordinate->setSortingEnabled(false);
        table_calibrateCoordinate->setSortingEnabled(__sortingEnabled);

        groupBox_17->setTitle(QApplication::translate("MainWindow", " \347\256\227\346\263\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = table_systemCalibrate->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\346\265\201\347\250\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = table_systemCalibrate->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\347\273\223\346\236\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = table_systemCalibrate->verticalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = table_systemCalibrate->verticalHeaderItem(1);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = table_preprocessAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225\345\210\227\350\241\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = table_preprocessAlgorithm->verticalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "1", nullptr));
        groupBox_15->setTitle(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\267\245\345\205\267", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = TWidget_toolList->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));

        const bool __sortingEnabled1 = TWidget_toolList->isSortingEnabled();
        TWidget_toolList->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = TWidget_toolList->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "\347\233\270\346\234\272", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = TWidget_toolList->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "\346\240\207\345\256\232", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "\342\221\240\346\240\207\345\256\232\346\235\277", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem3->child(0);
        ___qtreewidgetitem4->setText(0, QApplication::translate("MainWindow", "\346\226\271\345\275\242\346\243\213\347\233\230\346\240\274", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem3->child(1);
        ___qtreewidgetitem5->setText(0, QApplication::translate("MainWindow", "\345\234\206\345\275\242\346\243\213\347\233\230\346\240\274", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem3->child(2);
        ___qtreewidgetitem6->setText(0, QApplication::translate("MainWindow", "\345\234\206(\346\241\206\351\200\211)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem7->setText(0, QApplication::translate("MainWindow", "\342\221\241\346\230\240\345\260\204\347\237\251\351\230\265", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = TWidget_toolList->topLevelItem(2);
        ___qtreewidgetitem8->setText(0, QApplication::translate("MainWindow", "\347\256\227\346\263\225", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QApplication::translate("MainWindow", "\345\270\270\350\247\204", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem9->child(0);
        ___qtreewidgetitem10->setText(0, QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\217\226\345\217\215", nullptr));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem8->child(1);
        ___qtreewidgetitem11->setText(0, QApplication::translate("MainWindow", "\344\272\214\345\200\274\345\214\226", nullptr));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem11->child(0);
        ___qtreewidgetitem12->setText(0, QApplication::translate("MainWindow", "\345\205\250\345\261\200\344\272\214\345\200\274\345\214\226", nullptr));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem12->child(0);
        ___qtreewidgetitem13->setText(0, QApplication::translate("MainWindow", "\345\270\270\350\247\204\344\272\214\345\200\274\345\214\226", nullptr));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem12->child(1);
        ___qtreewidgetitem14->setText(0, QApplication::translate("MainWindow", "\345\270\270\350\247\204_\345\217\215\345\220\221\344\272\214\345\200\274\345\214\226", nullptr));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem12->child(2);
        ___qtreewidgetitem15->setText(0, QApplication::translate("MainWindow", "OTSU", nullptr));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem11->child(1);
        ___qtreewidgetitem16->setText(0, QApplication::translate("MainWindow", "\345\261\200\351\203\250\344\272\214\345\200\274\345\214\226", nullptr));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem16->child(0);
        ___qtreewidgetitem17->setText(0, QApplication::translate("MainWindow", "\345\210\206\345\235\227\344\272\214\345\200\274\345\214\226", nullptr));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem8->child(2);
        ___qtreewidgetitem18->setText(0, QApplication::translate("MainWindow", "\346\273\244\346\263\242", nullptr));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem18->child(0);
        ___qtreewidgetitem19->setText(0, QApplication::translate("MainWindow", "\345\235\207\345\200\274\346\273\244\346\263\242", nullptr));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem18->child(1);
        ___qtreewidgetitem20->setText(0, QApplication::translate("MainWindow", "\351\253\230\346\226\257\346\273\244\346\263\242", nullptr));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem18->child(2);
        ___qtreewidgetitem21->setText(0, QApplication::translate("MainWindow", "\344\270\255\345\200\274\346\273\244\346\263\242", nullptr));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem18->child(3);
        ___qtreewidgetitem22->setText(0, QApplication::translate("MainWindow", "\345\217\214\350\276\271\346\273\244\346\263\242", nullptr));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem8->child(3);
        ___qtreewidgetitem23->setText(0, QApplication::translate("MainWindow", "\345\275\242\346\200\201\345\255\246\346\223\215\344\275\234", nullptr));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem23->child(0);
        ___qtreewidgetitem24->setText(0, QApplication::translate("MainWindow", "\350\206\250\350\203\200", nullptr));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem23->child(1);
        ___qtreewidgetitem25->setText(0, QApplication::translate("MainWindow", "\350\205\220\350\232\200", nullptr));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem23->child(2);
        ___qtreewidgetitem26->setText(0, QApplication::translate("MainWindow", "\345\274\200", nullptr));
        QTreeWidgetItem *___qtreewidgetitem27 = ___qtreewidgetitem23->child(3);
        ___qtreewidgetitem27->setText(0, QApplication::translate("MainWindow", "\351\227\255", nullptr));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem23->child(4);
        ___qtreewidgetitem28->setText(0, QApplication::translate("MainWindow", "\345\275\242\346\200\201\345\255\246\346\242\257\345\272\246", nullptr));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem23->child(5);
        ___qtreewidgetitem29->setText(0, QApplication::translate("MainWindow", "\351\273\221\345\270\275", nullptr));
        QTreeWidgetItem *___qtreewidgetitem30 = ___qtreewidgetitem23->child(6);
        ___qtreewidgetitem30->setText(0, QApplication::translate("MainWindow", "\351\241\266\345\270\275", nullptr));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem8->child(4);
        ___qtreewidgetitem31->setText(0, QApplication::translate("MainWindow", "\350\275\256\345\273\223", nullptr));
        QTreeWidgetItem *___qtreewidgetitem32 = ___qtreewidgetitem31->child(0);
        ___qtreewidgetitem32->setText(0, QApplication::translate("MainWindow", "\346\237\245\346\211\276\350\275\256\345\273\223", nullptr));
        QTreeWidgetItem *___qtreewidgetitem33 = ___qtreewidgetitem8->child(5);
        ___qtreewidgetitem33->setText(0, QApplication::translate("MainWindow", "\351\234\215\345\244\253\345\234\206", nullptr));
        QTreeWidgetItem *___qtreewidgetitem34 = ___qtreewidgetitem33->child(0);
        ___qtreewidgetitem34->setText(0, QApplication::translate("MainWindow", "\346\237\245\346\211\276\351\234\215\345\244\253\345\234\206", nullptr));
        QTreeWidgetItem *___qtreewidgetitem35 = ___qtreewidgetitem8->child(6);
        ___qtreewidgetitem35->setText(0, QApplication::translate("MainWindow", "\351\200\232\347\224\250\345\234\206", nullptr));
        QTreeWidgetItem *___qtreewidgetitem36 = ___qtreewidgetitem35->child(0);
        ___qtreewidgetitem36->setText(0, QApplication::translate("MainWindow", "\346\237\245\346\211\276\345\234\206", nullptr));
        QTreeWidgetItem *___qtreewidgetitem37 = ___qtreewidgetitem8->child(7);
        ___qtreewidgetitem37->setText(0, QApplication::translate("MainWindow", "\347\211\271\345\276\201\347\202\271", nullptr));
        QTreeWidgetItem *___qtreewidgetitem38 = ___qtreewidgetitem37->child(0);
        ___qtreewidgetitem38->setText(0, QApplication::translate("MainWindow", "\346\226\271\345\275\242\346\243\213\347\233\230\346\240\274\347\211\271\345\276\201\347\202\271", nullptr));
        QTreeWidgetItem *___qtreewidgetitem39 = ___qtreewidgetitem8->child(8);
        ___qtreewidgetitem39->setText(0, QApplication::translate("MainWindow", "\345\214\271\351\205\215", nullptr));
        QTreeWidgetItem *___qtreewidgetitem40 = ___qtreewidgetitem39->child(0);
        ___qtreewidgetitem40->setText(0, QApplication::translate("MainWindow", "\350\275\256\345\273\223\345\214\271\351\205\215", nullptr));
        QTreeWidgetItem *___qtreewidgetitem41 = ___qtreewidgetitem39->child(1);
        ___qtreewidgetitem41->setText(0, QApplication::translate("MainWindow", "\346\250\241\346\235\277\345\214\271\351\205\215", nullptr));
        QTreeWidgetItem *___qtreewidgetitem42 = ___qtreewidgetitem39->child(2);
        ___qtreewidgetitem42->setText(0, QApplication::translate("MainWindow", "\347\211\271\345\276\201\347\202\271\345\214\271\351\205\215", nullptr));
        QTreeWidgetItem *___qtreewidgetitem43 = ___qtreewidgetitem8->child(9);
        ___qtreewidgetitem43->setText(0, QApplication::translate("MainWindow", "\345\235\220\346\240\207\347\263\273", nullptr));
        QTreeWidgetItem *___qtreewidgetitem44 = ___qtreewidgetitem43->child(0);
        ___qtreewidgetitem44->setText(0, QApplication::translate("MainWindow", "\347\233\270\346\234\272\345\235\220\346\240\207\347\263\273->\346\234\272\345\231\250\350\207\202\345\235\220\346\240\207\347\263\273", nullptr));
        QTreeWidgetItem *___qtreewidgetitem45 = TWidget_toolList->topLevelItem(3);
        ___qtreewidgetitem45->setText(0, QApplication::translate("MainWindow", "\351\200\232\344\277\241", nullptr));
        TWidget_toolList->setSortingEnabled(__sortingEnabled1);

        btn_toolConfirm->setText(QApplication::translate("MainWindow", " \347\241\256\345\256\232", nullptr));
        btn_AlgorithmExcute->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", nullptr));
        btn_AlgorithmRevocation->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\350\257\264\346\230\216", nullptr));
        textBrowser_20->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt;\">\345\233\276\345\203\217\344\272\214\345\200\274\345\214\226:\345\260\206\347\201\260\345\272\246\345\233\276\345\203\217\350\275\254\345\217\230\346\210\220\345\217\252\346\234\2110\345\222\214255\347\232\204\345\233\276\345\203\217</span><span style=\" font-size:14pt;\"> </span></p></body></html>", nullptr));
        textBrowser_21->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\346\245\267\344\275\223'; font-size:14pt;\">\345\210\206\345\235\227\344\272\214\345\200\274\345\214\226:\345\260\206\345\233\276\345\203\217\345\210\206\346\210\220N\345\235\227\357\274\214\346\257\217\344\270\252\345\261\200\351\203\250\345\233\276\345\203\217\350\207\252\345\212\250\350\256\241\347\256\227\344\272\214\345\200\274\345\214\226\351\230\210\345\200\274</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-blo"
                        "ck-indent:0; text-indent:0px; font-family:'\346\245\267\344\275\223'; font-size:14pt;\"><br /></p></body></html>", nullptr));
        textBrowser_7->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\342\221\240</span><span style=\" font-family:'Times New Roman'; font-size:7pt;\">\302\240\302\240\302\240 </span><span style=\" font-size:12pt;\">\350\211\262\345\275\251\347\263\273\346\225\260\357\274\232\345\200\274\350\266\212\345\244\247\357\274\214\350\257\245\345\203\217\347\264\240\351\242\206\345\237\237\345\206\205\346\234\211\350\266\212\345\271\277\347\232\204\351\242\234\350\211\262\344\274\232\350\242\253\346\267\267\345\220\210\345\210\260\344\270\200\350\265\267\357\274\214"
                        "\344\272\247\347\224\237\350\276\203\345\244\247\347\232\204\345\215\212\347\233\270\347\255\211\345\214\272\345\237\237</span><span style=\" font-size:16pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\342\221\241</span><span style=\" font-family:'Times New Roman'; font-size:7pt;\">\302\240\302\240\302\240 </span><span style=\" font-size:12pt;\">\347\251\272\351\227\264\347\263\273\346\225\260\357\274\232\345\200\274\350\266\212\345\244\247\357\274\214\346\204\217\345\221\263\347\235\200\350\266\212\350\277\234\347\232\204\345\203\217\347\264\240\344\274\232\347\233\270\344\272\222\345\275\261\345\223\215\357\274\214\344\273\216\350\200\214\344\275\277\346\233\264\345\244\247\347\232\204\345\214\272\345\237\237\344\270\255\350\266\263\345\244\237\347\233\270\344\274\274\347\232\204\351\242\234\350\211\262\350\216\267\345\217\226\347\233\270\345\220\214\347\232\204\351\242\234\350\211"
                        "\262</span><span style=\" font-size:16pt;\"> </span></p></body></html>", nullptr));
        textBrowser_9->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\350\205\220\350\232\200\357\274\232\345\260\206\351\273\221\350\211\262\345\233\276\346\241\210\345\217\230\345\244\247<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\350\206\250\350\203\200\357\274\232\345\260\206\351\273\221\350\211\262\345\233\276\346\241\210\345\217\230\345\260\217<span style=\" font-family:'\346\245\267\344\275\223';\"> </span>"
                        "</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\242\345\274\200\357\274\232\345\205\210\350\205\220\350\232\200\345\220\216\350\206\250\350\203\200\357\274\214\346\266\210\351\231\244\347\231\275\350\211\262\345\231\252\347\202\271<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\243\351\227\255\357\274\232\345\205\210\350\206\250\350\203\200\345\220\216\350\205\220\350\232\200\357\274\214\346\266\210\351\231\244\345\260\217\345\236\213\351\273\221\350\211\262\345\231\252\347\202\271<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\244\345\275\242\346\200\201\345\255\246\346\242\257\345\272\246\357\274\232\344\277"
                        "\235\347\225\231\347\211\251\344\275\223\350\276\271\347\274\230<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\245\351\273\221\345\270\275\357\274\232\347\252\201\345\207\272\346\257\224\345\216\237\350\275\256\345\273\223\345\221\250\345\233\264\346\233\264\346\232\227\347\232\204\345\214\272\345\237\237<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\246\351\241\266\345\270\275\357\274\232\345\210\206\347\246\273\346\257\224\350\276\203\344\272\256\347\232\204\346\226\221\345\235\227<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p></body></html>", nullptr));
        textBrowser_6->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240<span style=\" font-family:'Times New Roman';\">\302\240\302\240\302\240\302\240\302\240 </span>\350\242\253\346\237\245\346\211\276\347\232\204\350\275\256\345\273\223\347\232\204\345\233\276\347\211\207\345\277\205\351\241\273\346\230\257\351\273\221\345\272\225\347\231\275\350\275\256\345\273\223\357\274\214\345\246\202\346\236\234\344\274\240\345\205\245\347\232\204\345\233\276\347\211\207\344\270\215\346\273\241\350\266\263\350\277\231\344\270\252\345\211\215\346\217\220\357\274\214\345\210\231\345\205\210"
                        "\346\211\247\350\241\214\342\200\234\345\270\270\350\247\204\342\200\224\345\217\226\345\217\215\342\200\235\347\256\227\346\263\225\343\200\202<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241<span style=\" font-family:'Times New Roman';\">\302\240\302\240\302\240\302\240\302\240 </span>\350\275\256\345\273\223\346\234\200\345\260\217/\345\244\247\351\235\242\347\247\257\357\274\232\347\224\250\344\272\216\350\256\276\345\256\232\351\234\200\350\246\201\344\277\235\347\225\231\347\232\204\350\275\256\345\273\223\351\235\242\347\247\257\350\214\203\345\233\264\357\274\214\345\207\241\346\230\257\344\270\215\345\234\250\350\277\231\344\270\252\345\214\272\351\227\264\347\232\204\346\211\200\346\234\211\350\275\256\345\273\223\345\260\206\345\205\250\351\203\250\350\242\253\347\247\273\351\231\244\357\274\214\344\270\215\344\274\232\344\274\240\345\205\245"
                        "\344\270\213\344\270\200\347\272\247\347\256\227\346\263\225<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p></body></html>", nullptr));
        textBrowser_4->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\346\234\200\345\260\217\345\234\206\345\277\203\350\267\235\357\274\232\344\270\244\344\270\252\345\234\206\344\271\213\351\227\264\347\232\204\346\234\200\345\260\217\350\267\235\347\246\273\357\274\214\350\256\276\347\275\256\350\277\207\345\260\217\357\274\214\345\220\214\344\270\200\344\270\252\345\234\206\345\217\257\350\203\275\346\243\200\346\265\213\345\207\272\345\244\232\344\270\252\345\234\206<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; mar"
                        "gin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\350\276\271\346\262\277\351\230\210\345\200\274\357\274\232canny\347\256\227\345\255\220\347\232\204\351\253\230\351\230\210\345\200\274<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\242\345\234\206\347\264\257\345\212\240\345\231\250\351\230\210\345\200\274\357\274\232\345\275\242\346\210\220\344\270\200\344\270\252\345\234\206\347\232\204\346\234\200\345\260\221\345\203\217\347\264\240\347\202\271\347\232\204\344\270\252\346\225\260<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\243\346\234\200\345\244\247/\345\260\217\345\215\212\345\276\204\357\274\232\350\256\276\347\275\256\344\270\2720\357\274"
                        "\214\350\241\250\347\244\272\346\237\245\346\211\276\346\211\200\346\234\211\345\234\206<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p></body></html>", nullptr));
        textBrowser_8->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240<span style=\" font-family:'Times New Roman';\">\302\240</span>\350\257\204\345\210\206\357\274\232\345\210\244\345\256\232\345\233\276\345\203\217\350\276\271\346\262\277\347\202\271\345\234\250\344\275\240\345\222\214\345\207\272\346\235\245\347\232\204\345\234\206\345\274\247\344\270\212\347\232\204\347\202\271\347\232\204\347\231\276\345\210\206\346\257\224\357\274\214\346\257\224\345\200\274\346\234\200\345\244\247100\357\274\214\346\234\200\345\260\2170\357\274\214\350\257\204\345\210\206\350\266\212\351"
                        "\253\230\357\274\214\350\276\271\346\262\277\345\222\214\345\234\206\347\232\204\345\220\273\345\220\210\345\272\246\350\266\212\345\245\275\343\200\202<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\346\213\237\345\220\210\345\201\217\345\267\256\357\274\232\345\205\201\350\256\270\346\213\237\345\220\210\345\207\272\346\235\245\347\232\204\345\234\206\345\222\214\345\256\236\351\231\205\350\276\271\346\262\277\347\202\271\344\271\213\351\227\264\346\234\200\345\244\247\345\205\201\350\256\270\350\257\257\345\267\256\357\274\214\346\213\237\345\220\210\345\201\217\345\267\256\350\266\212\345\260\217\357\274\214\350\266\212\347\262\276\347\241\256<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\242"
                        "<span style=\" font-family:'Times New Roman';\">\302\240</span>\346\234\200\345\244\247/\345\260\217\345\215\212\345\276\204\357\274\232\350\256\276\347\275\256\344\270\2720\357\274\214\350\241\250\347\244\272\346\237\245\346\211\276\346\211\200\346\234\211\345\234\206<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\243<span style=\" font-family:'Times New Roman';\">\302\240</span>\344\272\214\345\200\274\345\214\226\351\230\210\345\200\274\357\274\232\347\263\273\347\273\237\350\256\276\347\275\256\344\272\206\350\207\252\351\200\202\345\272\224\344\272\214\345\200\274\345\214\226\347\256\227\346\263\225\357\274\214\345\246\202\346\236\234\345\217\221\347\216\260\350\207\252\351\200\202\345\272\224\344\272\214\345\200\274\345\214\226\344\270\215\345\256\236\347\224\250\346\227\266\357\274\214\346\211\215\350\256\276\347\275\256\350\257\245\345\200\274\357"
                        "\274\214\345\220\246\345\210\231\347\233\264\346\216\245\350\256\276\347\275\256\346\210\2200<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\244<span style=\" font-family:'Times New Roman';\">\302\240</span>\345\234\206\347\264\257\345\212\240\345\231\250\351\230\210\345\200\274\357\274\232\345\275\242\346\210\220\344\270\200\344\270\252\345\234\206\346\211\200\351\234\200\350\246\201\347\232\204\346\234\211\346\225\210\347\264\240\347\202\271\347\232\204\344\270\252\346\225\260\357\274\214\350\256\276\347\275\256\344\270\2720\357\274\214\347\263\273\347\273\237\344\270\215\350\200\203\350\231\221\350\257\245\345\210\244\345\256\232\346\240\207\345\207\206<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\343\200"
                        "\220\346\263\250\357\274\232\350\242\253\346\240\207\345\256\232\347\232\204\345\233\276\345\203\217\345\277\205\351\241\273\346\230\257\351\273\221\345\272\225\347\231\275\345\234\206\357\274\214\346\211\200\344\273\245\345\246\202\346\236\234\345\212\240\350\275\275\347\232\204\345\233\276\347\211\207\346\230\257\347\231\275\345\272\225\351\273\221\345\234\206\357\274\214\345\210\231\351\200\211\346\213\251\342\200\234\345\270\270\350\247\204/\345\217\226\345\217\215\342\200\235\347\256\227\346\263\225\343\200\221<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p></body></html>", nullptr));
        textBrowser_5->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\347\233\270\344\274\274\345\272\246\351\230\210\345\200\274\357\274\232\346\230\257\346\214\207\346\250\241\346\235\277\344\270\216\346\243\200\346\265\213\345\257\271\350\261\241\344\271\213\351\227\264\347\232\204\347\233\270\344\274\274\345\272\246\357\274\214\344\270\200\350\210\254\351\203\275\346\230\257\345\260\217\344\272\2160.1\343\200\202\343\200\220\345\246\202\346\236\234\351\207\207\347\224\250\347\211\271\345\276\201\347\202\271\345\214\271\351\205\215\357\274\214\345\210\231\350\257\245\345\217"
                        "\202\346\225\260\346\227\240\346\225\210\343\200\221<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\350\275\256\345\273\223\345\214\271\351\205\215\357\274\232\345\234\250\350\277\233\350\241\214\350\275\256\345\273\223\345\214\271\351\205\215\344\271\213\345\211\215\357\274\214\345\205\210\346\211\247\350\241\214\342\200\234\346\237\245\346\211\276\350\275\256\345\273\223\347\256\227\346\263\225\342\200\235<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\242\347\211\271\345\276\201\347\202\271/\346\250\241\346\235\277\345\214\271\351\205\215\357\274\232\350\257\245\347\256\227\346\263\225\345\217\252\345\234\250\345\276\205\346\243\200\346\265\213\345\233\276\345\203\217\344\270\255\346\237\245\346"
                        "\211\276\344\270\200\344\270\252\346\234\200\344\274\230\347\232\204\347\211\271\345\276\201\350\277\233\350\241\214\345\214\271\351\205\215\343\200\202<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p></body></html>", nullptr));
        textBrowser_11->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\346\243\213\347\233\230\346\240\274\345\210\227\346\225\260\357\274\232\346\243\213\347\233\230\346\240\274\346\257\217\344\270\200\350\241\214\346\234\211\345\244\232\345\260\221\344\270\252\346\226\271\345\235\227<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\346\243\213\347\233\230\346\240\274\350\241\214\346\225\260\357\274\232\346\243\213\347\233"
                        "\230\346\240\274\344\270\200\345\205\261\346\234\211\345\244\232\345\260\221\350\241\214<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p></body></html>", nullptr));
        textBrowser_12->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt;\">\345\233\276\345\203\217\345\217\226\345\217\215:\345\260\206\345\233\276\345\203\217\347\232\204\351\273\221\347\231\275\345\203\217\347\264\240\345\210\207\346\215\242</span><span style=\" font-size:14pt;\"> </span></p></body></html>", nullptr));
        textBrowser_15->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\233\276\345\203\217\347\232\204\347\237\251\357\274\232</p></body></html>", nullptr));
        textBrowser_13->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\350\257\245\350\275\257\344\273\266\344\275\234\344\270\272modbus master\357\274\214\345\257\271\345\272\224\347\232\204\351\200\232\350\256\257\350\256\276\345\244\207\345\272\224\350\257\245\344\275\234\344\270\272modbus Salve; </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\350\257\245\350\275\257\344\273\266\344\270\255modbus\350\257\273\345\222\214\345\206\231\346\230\257\345\210\206\345\274\200\347\232\204\344"
                        "\270\244\344\270\252modbus\346\250\241\345\235\227\357\274\214\350\257\267\346\263\250\346\204\217\350\257\273\345\222\214\345\206\231\347\232\204\347\253\257\345\217\243\345\217\267\344\270\200\345\256\232\344\270\215\350\203\275\347\233\270\345\220\214\357\274\214\345\220\246\345\210\231\351\200\232\350\256\257\345\217\257\350\203\275\345\274\202\345\270\270\357\274\233 </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\242\351\200\232\350\256\257\350\257\273\345\206\231\345\257\204\345\255\230\345\231\250\347\232\204\344\270\252\346\225\260\350\246\201\345\222\214modbus Salve\350\256\276\350\256\241\347\232\204\346\225\260\351\207\217\345\214\271\351\205\215\357\274\214\344\270\200\345\256\232\344\270\215\350\203\275\350\266\205\350\277\207\345\205\266\346\234\200\345\244\247\351\207\217 </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342"
                        "\221\243\346\234\254\346\254\241\351\200\232\344\277\241\347\232\204\345\257\271\350\261\241\346\230\257\345\235\220\346\240\207\357\274\214\346\225\205\345\205\250\351\203\250\351\207\207\347\224\250float32\347\232\204\346\225\260\346\215\256\347\261\273\345\236\213\357\274\214\350\257\267\346\263\250\346\204\217float32\346\225\260\346\215\256\347\261\273\345\236\213\347\232\204\350\247\243\346\236\220\346\250\241\345\274\217\345\222\214modbus Salve\350\246\201\344\270\200\350\207\264\357\274\214\345\220\246\345\210\231\345\207\272\347\216\260\344\271\261\347\240\201\343\200\202 </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\244\345\234\250\350\275\257\344\273\266\347\232\204\342\200\234\346\240\207\345\256\232\342\200\235\347\216\257\350\212\202\357\274\214\350\275\257\344\273\266\351\200\232\350\277\207\342\200\234modbus\342\200\224\350\257\273\345\217\226\342\200\235\345\260\206\346\240\207\345\256\232\345\235\220"
                        "\346\240\207\344\274\240\345\205\245\357\274\233 </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\245\345\234\250\350\275\257\344\273\266\347\232\204\342\200\234\345\256\232\344\275\215\342\200\235\347\216\257\350\212\202\357\274\214\350\275\257\344\273\266\351\200\232\350\277\207\342\200\234modbus\342\200\224\345\206\231\345\205\245\342\200\235\345\260\206\345\256\232\344\275\215\345\235\220\346\240\207\350\276\223\345\207\272 </p></body></html>", nullptr));
        textBrowser_3->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\350\257\204\345\210\206\357\274\232\345\210\244\345\256\232\345\233\276\345\203\217\350\276\271\346\262\277\347\202\271\345\234\250\344\275\240\345\222\214\345\207\272\346\235\245\347\232\204\345\234\206\345\274\247\344\270\212\347\232\204\347\202\271\347\232\204\347\231\276\345\210\206\346\257\224\357\274\214\346\257\224\345\200\274\346\234\200\345\244\247100\357\274\214\346\234\200\345\260\2170\357\274\214\350\257\204\345\210\206\350\266\212\351\253\230\357\274\214\350\276\271\346\262\277\345\222\214\345\234"
                        "\206\347\232\204\345\220\273\345\220\210\345\272\246\350\266\212\345\245\275\343\200\202<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\346\213\237\345\220\210\345\201\217\345\267\256\357\274\232\345\205\201\350\256\270\346\213\237\345\220\210\345\207\272\346\235\245\347\232\204\345\234\206\345\222\214\345\256\236\351\231\205\350\276\271\346\262\277\347\202\271\344\271\213\351\227\264\346\234\200\345\244\247\345\205\201\350\256\270\350\257\257\345\267\256\357\274\214\346\213\237\345\220\210\345\201\217\345\267\256\350\266\212\345\260\217\357\274\214\350\266\212\347\262\276\347\241\256<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\242\346\234\200\345\244\247/\345\260\217\345\215\212\345\276\204\357"
                        "\274\232\350\256\276\347\275\256\344\270\2720\357\274\214\350\241\250\347\244\272\346\237\245\346\211\276\346\211\200\346\234\211\345\234\206<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\243\344\272\214\345\200\274\345\214\226\351\230\210\345\200\274\357\274\232\347\263\273\347\273\237\350\256\276\347\275\256\344\272\206\350\207\252\351\200\202\345\272\224\344\272\214\345\200\274\345\214\226\347\256\227\346\263\225\357\274\214\345\246\202\346\236\234\345\217\221\347\216\260\350\207\252\351\200\202\345\272\224\344\272\214\345\200\274\345\214\226\344\270\215\345\256\236\347\224\250\346\227\266\357\274\214\346\211\215\350\256\276\347\275\256\350\257\245\345\200\274\357\274\214\345\220\246\345\210\231\347\233\264\346\216\245\350\256\276\347\275\256\346\210\2200<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\" margin-top:1"
                        "2px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\244\345\234\206\347\264\257\345\212\240\345\231\250\351\230\210\345\200\274\357\274\232\345\275\242\346\210\220\344\270\200\344\270\252\345\234\206\346\211\200\351\234\200\350\246\201\347\232\204\346\234\211\346\225\210\347\264\240\347\202\271\347\232\204\344\270\252\346\225\260\357\274\214\350\256\276\347\275\256\344\270\2720\357\274\214\347\263\273\347\273\237\344\270\215\350\200\203\350\231\221\350\257\245\345\210\244\345\256\232\346\240\207\345\207\206<span style=\" font-family:'\346\245\267\344\275\223';\"> </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:16pt; font-weight:600;\"><br /></p></body></html>", nullptr));
        textBrowser_18->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\233\270\346\234\272\350\256\276\347\275\256\345\214\205\346\213\254\344\270\244\344\270\252\351\203\250\345\210\206\357\274\232\345\217\202\346\225\260\350\256\276\347\275\256\345\222\214\345\233\276\347\211\207\344\277\235\345\255\230\350\267\257\345\276\204 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1\357\274\211\347\233\270\346\234\272\345\217\202\346\225\260\357\274\232 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; mar"
                        "gin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\346\233\235\345\205\211\357\274\232\347\233\270\346\234\272\347\232\204\346\233\235\345\205\211\346\227\266\351\227\264\357\274\233 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\345\270\247\347\216\207\357\274\232\347\233\270\346\234\272\347\232\204\351\207\207\351\233\206\345\270\247\347\216\207\357\274\210\345\215\263\357\274\232\346\257\217\347\247\222\351\207\207\351\233\206\347\232\204\345\233\276\345\203\217\347\232\204\345\274\240\346\225\260\357\274\211\357\274\233 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\242\350\247\246\345\217\221\346\250\241\345\274\217\357\274\232\350\277\236\347\273\255\351\207\207\351\233\206\343\200\201\350\275\257\344\273\266\350\247\246\345\217\221\343\200\201\345\244\226\351\203\250\350\247\246\345\217"
                        "\221\343\200\202 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">a)\350\277\236\347\273\255\351\207\207\351\233\206\357\274\232\350\277\236\346\216\245\344\270\212\347\233\270\346\234\272\344\271\213\345\220\216\357\274\214\347\263\273\347\273\237\346\240\271\350\256\276\347\275\256\345\270\247\347\216\207\350\207\252\345\212\250\351\207\207\351\233\206\345\233\276\347\211\207\357\274\233 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">b)\350\275\257\344\273\266\350\247\246\345\217\221\357\274\232\350\277\236\346\216\245\344\270\212\347\233\270\346\234\272\344\271\213\345\220\216\357\274\214\347\263\273\347\273\237\351\200\232\350\277\207\350\275\257\344\273\266\344\270\212\347\232\204\350\247\246\345\217\221\346\214\211\351\222\256\357\274\214\346\213\215\347\205\247\357\274\233 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0p"
                        "x; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c)\345\244\226\351\203\250\350\247\246\345\217\221\357\274\232\350\277\236\346\216\245\344\270\212\347\233\270\346\234\272\344\271\213\345\220\216\357\274\214\351\200\232\350\277\207\347\233\270\346\234\272\347\232\204IO\350\247\246\345\217\221\351\207\207\351\233\206\347\205\247\347\211\207\343\200\202 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2\357\274\211\345\233\276\347\211\207\344\277\235\345\255\230\345\217\202\346\225\260\357\274\232 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\240\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232\345\246\202\346\236\234\347\202\271\345\207\273\344\272\206\350\207\252\345\212\250\344\277\235\345\255\230\346\214\211\351\222\256\357\274\214\345\210\231\345\233\276\347\211\207\344\277\235\345\255\230\345\210\260\350\257\245\347"
                        "\233\256\345\275\225\344\270\213\357\274\233 </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\221\241\346\230\257\345\220\246\350\207\252\345\212\250\344\277\235\345\255\230\357\274\232\347\241\256\345\256\232\347\263\273\347\273\237\346\230\257\345\220\246\351\234\200\350\246\201\344\277\235\345\255\230\345\233\276\347\211\207\343\200\202 </p></body></html>", nullptr));
        textBrowser_19->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; font-weight:600;\">1.</span><span style=\" font-family:'Times New Roman'; font-size:7pt;\">\302\240\302\240\302\240\302\240\302\240 </span><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; font-weight:600;\">\347\263\273\347\273\237\346\240\207\345\256\232\346\246\202\350\277\260</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-bl"
                        "ock-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\347\263\273\347\273\237\346\240\207\345\256\232\347\232\204\345\212\237\350\203\275\344\270\273\350\246\201\346\230\257\350\216\267\345\217\226\347\233\270\346\234\272\345\235\220\346\240\207\347\263\273\345\210\260\346\234\272\346\242\260\350\207\202\347\232\204\344\270\226\347\225\214\345\235\220\346\240\207\347\263\273\347\232\204\346\230\240\345\260\204\347\237\251\351\230\265\357\274\214\347\263\273\347\273\237\346\240\207\345\256\232\346\230\257\344\270\200\345\210\207\345\256\232\344\275\215\347\256\227\346\263\225\347\232\204\345\211\215\346\217\220\343\200\202</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; font-weight:600;\">2.</span><span style=\" font-family:'Times New Roman'; font-size:"
                        "7pt;\">\302\240\302\240\302\240\302\240\302\240 </span><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; font-weight:600;\">\345\212\237\350\203\275\344\273\213\347\273\215</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\347\263\273\347\273\237\346\240\207\345\256\232\345\210\206\346\210\220\344\270\244\344\270\252\346\255\245\351\252\244\357\274\232\347\211\271\345\276\201\347\202\271\345\222\214\346\230\240\345\260\204\347\237\251\351\230\265\343\200\202</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\342\221\240</span><span style=\" font-family:'Times New Roman'; font-size:7pt;\">\302\240\302"
                        "\240\302\240 </span><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\347\211\271\345\276\201\347\202\271\357\274\232\346\234\254\347\263\273\347\273\237\344\270\273\350\246\201\346\217\220\344\276\233\346\226\271\345\275\242\346\243\213\347\233\230\346\240\274\345\222\214\345\234\206\345\275\242\346\243\213\347\233\230\346\240\274\344\270\244\347\247\215\346\237\245\346\211\276\347\211\271\345\276\201\347\202\271\347\232\204\346\226\271\345\274\217\343\200\202</span>   </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/icon/img/icon/calibratePlate1.png\" /><img src=\":/icon/img/icon/calibratePlate.png\" /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\342\221\241\346\230\240\345\260\204\347"
                        "\237\251\351\230\265\357\274\232\350\256\241\347\256\227\346\230\240\345\260\204\347\237\251\351\230\265\343\200\202</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; font-weight:600;\">3.</span><span style=\" font-family:'Times New Roman'; font-size:7pt;\">\302\240\302\240\302\240\302\240\302\240 </span><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; font-weight:600;\">\346\223\215\344\275\234\346\265\201\347\250\213\357\274\232</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Times New Roman'; font-size:7pt;\"> </span><span style=\" font-family:'\345\256\213\344\275\223'; font-size:12pt; color:#000000;\">\342\221\240</span><span style=\" font-family:'Times New Roman"
                        "'; font-size:7pt; color:#000000;\">\302\240 </span><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; color:#000000;\">\346\237\245\346\211\276\347\211\271\345\276\201\347\202\271\357\274\214\350\256\241\347\256\227\347\211\271\345\276\201\347\202\271\345\234\250\347\233\270\346\234\272\345\235\220\346\240\207\347\263\273\344\270\255\347\232\204\345\235\220\346\240\207</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\256\213\344\275\223'; font-size:12pt; color:#000000;\">\342\221\241</span><span style=\" font-family:'Times New Roman'; font-size:7pt; color:#000000;\">\302\240 </span><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; color:#000000;\">\350\216\267\345\217\226\347\211\271\345\276\201\347\202\271\345\257\271\345\272\224\347\232\204\346\234\272\346\242\260\350\207\202\344\270\226\347\225\214\345"
                        "\235\220\346\240\207\347\263\273\344\270\255\347\232\204\345\235\220\346\240\207\345\235\220\346\240\207</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:120%;\"><span style=\" font-family:'\345\256\213\344\275\223'; font-size:12pt; color:#000000;\">\342\221\242</span><span style=\" font-family:'Times New Roman'; font-size:7pt; color:#000000;\">\302\240 </span><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; color:#000000;\">\350\256\241\347\256\227\346\230\240\345\260\204\347\237\251\351\230\265</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\346\255\244\345\244\204\351\207\215\347\202\271\344\273\213\347\273\215\344\270\200\344\270\213\347\254\254\342\221\241\346\255\245\350\216\267"
                        "\345\217\226\347\211\271\345\276\201\347\202\271\345\234\250\344\270\226\347\225\214\345\235\220\346\240\207\347\263\273\344\270\255\347\232\204\345\235\220\346\240\207\357\274\214\347\233\256\345\211\215\347\263\273\347\273\237\346\224\257\346\214\201\344\270\244\347\247\215\346\226\271\345\274\217\357\274\232</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">a)\351\200\232\350\256\257\346\226\271\345\274\217\357\274\210\351\273\230\350\256\244\346\226\271\345\274\217\357\274\211\357\274\232\347\233\264\346\216\245\351\200\232\350\277\207\351\205\215\347\275\256\351\200\232\350\256\257\345\217\202\346\225\260\357\274\214\350\256\276\345\256\232\347\233\270\345\272\224\347\232\204\351\200\232\350\256\257\345\257\204\345\255\230\345\231\250\357\274\214\346\234\272\346\242\260\350\207\202\346\240\207\345\256\232\346\227\266\357\274"
                        "\214\345\260\206\345\257\271\345\272\224\347\232\204\345\235\220\346\240\207\345\275\225\345\205\245\347\233\270\345\272\224\347\232\204\345\257\204\345\255\230\345\231\250\344\270\255\357\274\214\347\263\273\347\273\237\350\207\252\345\212\250\350\257\273\345\217\226\345\235\220\346\240\207\357\274\233</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">b\357\274\211\346\211\213\345\212\250\350\276\223\345\205\245\346\226\271\345\274\217\357\274\232\351\200\232\350\277\207\351\205\215\347\275\256\351\200\232\350\256\257\345\217\202\346\225\260\357\274\214\345\274\200\345\220\257\342\200\234\346\240\207\345\256\232\345\235\220\346\240\207\346\211\213\345\212\250\350\276\223\345\205\245\342\200\235\357\274\214\346\234\272\346\242\260\350\207\202\346\240\207\345\256\232\346\227\266\357\274\214\345\260\206\345\257\271\345\272\224\347"
                        "\232\204\345\235\220\346\240\207\345\241\253\345\205\245\347\233\270\345\272\224\347\232\204\350\241\250\346\240\274\344\270\255\357\274\214\347\263\273\347\273\237\350\207\252\345\212\250\350\257\273\345\217\226\345\235\220\346\240\207\343\200\202</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> </p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        textBrowser_22->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\346\230\240\345\260\204\347\237\251\351\230\265\357\274\232\344\273\216\347\233\270\346\234\272\345\235\220\346\240\207\347\263\273\347\232\204\345\235\220\346\240\207\350\275\254\345\217\230\346\210\220\346\234\272\346\242\260\350\207\202\344\270\226\347\225\214\345\235\220\346\240\207\347\263\273\347\232\204\345\235\220\346\240\207\343\200\202</span> </p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bott"
                        "om:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        textBrowser_23->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\345\246\202\344\270\213\345\233\276\357\274\214\346\234\254\347\263\273\347\273\237\346\217\220\344\276\233\346\226\271\345\275\242\346\243\213\347\233\230\346\240\274\345\222\214\345\234\206\345\275\242\346\243\213\347\233\230\346\240\274\344\270\244\347\247\215\346\240\207\345\256\232\347\232\204\346\226\271\345\274\217\357\274\214\351\200\211\346\213\251\344\270\215\345\220\214\347\232\204\346\240\207\345\256\232\346\226\271"
                        "\345\274\217\343\200\202</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/icon/img/icon/calibratePlate1.png\" /><img src=\":/icon/img/icon/calibratePlate.png\" /></p></body></html>", nullptr));
        textBrowser_24->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt;\">\344\270\272\344\272\206\345\205\274\345\256\271\345\244\232\345\234\272\346\231\257\347\232\204\350\277\220\347\224\250\357\274\214\346\234\254\347\263\273\347\273\237\346\217\220\344\276\233\344\272\206\345\244\232\347\247\215\345\270\270\347\224\250\347\256\227\346\263\225\344\276\233\347\224\250\346\210\267\350\207\252\347\224\261\346\220\255\351\205\215\357\274\214\350\276\276\345\210\260\347\233\256\346\240\207\345\256\232"
                        "\344\275\215\347\232\204\344\275\234\347\224\250\343\200\202\345\256\232\344\275\215\347\256\227\346\263\225\347\232\204\346\223\215\344\275\234\346\265\201\347\250\213\357\274\232\345\233\276\345\203\217\351\242\204\345\244\204\347\220\206-&gt;\350\216\267\345\217\226\346\212\223\345\217\226\347\202\271-&gt;\345\235\220\346\240\207\347\263\273\350\275\254\346\215\242\343\200\202</span> </p></body></html>", nullptr));
        textBrowser_25->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\245\346\237\245\346\211\276\347\211\271\345\276\201\347\202\271\347\232\204\347\256\227\346\263\225\346\230\257\351\200\232\350\277\207\346\211\213\345\212\250\346\241\206\351\200\211\347\211\271\345\276\201\345\233\276\345\203\217\347\232\204\345\214\272\345\237\237\357\274\214\347\204\266\345\220\216\347\202\271\345\207\273\346\267\273\345\212\240\346\214\211\351\222\256\346\210\226\350\200\205\346\222\244\351\224\200\346\214\211\351\222\256\357\274\214\346\211\247\350\241\214\346\267\273\345\212\240\346\210\226"
                        "\350\200\205\346\211\247\350\241\214\347\211\271\345\276\201\347\202\271\347\232\204\346\223\215\344\275\234\343\200\202</p></body></html>", nullptr));
        groupBox_18->setTitle(QApplication::translate("MainWindow", " \347\274\226\350\276\221", nullptr));
        label_81->setText(QApplication::translate("MainWindow", "\351\230\210\345\200\274\357\274\232", nullptr));
        label_82->setText(QApplication::translate("MainWindow", "\345\210\206\345\235\227\345\244\247\345\260\217\357\274\232", nullptr));
        label_83->setText(QApplication::translate("MainWindow", " \345\206\205\346\240\270\345\256\275\357\274\232", nullptr));
        label_84->setText(QApplication::translate("MainWindow", " \345\206\205\346\240\270\351\253\230\357\274\232", nullptr));
        label_85->setText(QApplication::translate("MainWindow", " \350\211\262\345\275\251\347\263\273\346\225\260\357\274\232", nullptr));
        label_86->setText(QApplication::translate("MainWindow", "\344\275\215\347\275\256\347\263\273\346\225\260\357\274\232", nullptr));
        label_87->setText(QApplication::translate("MainWindow", " \345\206\205\346\240\270\345\256\275\357\274\232", nullptr));
        label_88->setText(QApplication::translate("MainWindow", " \345\206\205\346\240\270\351\253\230\357\274\232", nullptr));
        label_89->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\351\235\242\347\247\257\357\274\232", nullptr));
        label_90->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\351\235\242\347\247\257\357\274\232", nullptr));
        label_91->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\345\234\206\345\277\203\350\267\235\357\274\232", nullptr));
        label_92->setText(QApplication::translate("MainWindow", "\345\234\206\346\234\200\345\244\247\345\215\212\345\276\204\357\274\232", nullptr));
        label_93->setText(QApplication::translate("MainWindow", "\345\234\206\346\234\200\345\260\217\345\215\212\345\276\204\357\274\232", nullptr));
        label_94->setText(QApplication::translate("MainWindow", "\345\234\206\347\264\257\345\212\240\345\231\250\351\230\210\345\200\274\357\274\232", nullptr));
        label_95->setText(QApplication::translate("MainWindow", "\350\276\271\346\262\277\351\230\210\345\200\274\357\274\232", nullptr));
        label_96->setText(QApplication::translate("MainWindow", "\345\234\206\347\264\257\345\212\240\345\231\250\351\230\210\345\200\274", nullptr));
        label_97->setText(QApplication::translate("MainWindow", "\350\257\204\345\210\206\357\274\232", nullptr));
        label_98->setText(QApplication::translate("MainWindow", "\345\234\206\346\234\200\345\244\247\345\215\212\345\276\204\357\274\232", nullptr));
        label_99->setText(QApplication::translate("MainWindow", "\344\272\214\345\200\274\345\214\226\351\230\210\345\200\274\357\274\232", nullptr));
        label_100->setText(QApplication::translate("MainWindow", "\346\213\237\345\220\210\345\201\217\345\267\256\357\274\232", nullptr));
        label_101->setText(QApplication::translate("MainWindow", "\345\234\206\346\234\200\345\260\217\345\215\212\345\276\204\357\274\232", nullptr));
        label_102->setText(QApplication::translate("MainWindow", " \346\243\213\347\233\230\346\240\274\345\210\227\346\225\260\357\274\232", nullptr));
        label_103->setText(QApplication::translate("MainWindow", " \346\243\213\347\233\230\346\240\274\350\241\214\346\225\260\357\274\232", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "\345\234\206\347\264\257\345\212\240\345\231\250\351\230\210\345\200\274", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "\350\257\204\345\210\206\357\274\232", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "\344\272\214\345\200\274\345\214\226\351\230\210\345\200\274\357\274\232", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\213\237\345\220\210\345\201\217\345\267\256\357\274\232", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "\345\234\206\346\234\200\345\244\247\345\215\212\345\276\204\357\274\232", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "\345\234\206\346\234\200\345\260\217\345\215\212\345\276\204\357\274\232", nullptr));
        label_104->setText(QApplication::translate("MainWindow", "\347\233\270\344\274\274\345\272\246\351\230\210\345\200\274", nullptr));
        btn_addTemp->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\250\241\346\235\277", nullptr));
        lab_algorithmnTemp->setText(QApplication::translate("MainWindow", "\346\250\241\346\235\2771", nullptr));
        groupBox_20->setTitle(QApplication::translate("MainWindow", "\351\205\215\347\275\256", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "IP\357\274\232", nullptr));
        label_40->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\240\274\345\274\217\357\274\232", nullptr));
        label_45->setText(QApplication::translate("MainWindow", "\346\211\253\346\217\217\345\221\250\346\234\237\357\274\232", nullptr));
        label_36->setText(QApplication::translate("MainWindow", "TimeOut\357\274\232", nullptr));
        label_47->setText(QApplication::translate("MainWindow", "\351\207\215\350\277\236\346\254\241\346\225\260\357\274\232", nullptr));
        modbusIP->setText(QApplication::translate("MainWindow", "127.0.0.0", nullptr));
        modbusDataType->setItemText(0, QApplication::translate("MainWindow", "ABCD", nullptr));
        modbusDataType->setItemText(1, QApplication::translate("MainWindow", "CDAB", nullptr));
        modbusDataType->setItemText(2, QApplication::translate("MainWindow", "BADC", nullptr));
        modbusDataType->setItemText(3, QApplication::translate("MainWindow", "DCBA", nullptr));

        label_44->setText(QApplication::translate("MainWindow", "ms", nullptr));
        label_46->setText(QApplication::translate("MainWindow", "ms", nullptr));
        btn_modbusConnect->setText(QApplication::translate("MainWindow", " \350\277\236\346\216\245", nullptr));
        btn_modbusTest->setText(QApplication::translate("MainWindow", "\351\200\232\350\256\257\346\265\213\350\257\225", nullptr));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "modbus_\350\257\273\345\207\272", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        label_55->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250ID\357\274\232", nullptr));
        label_57->setText(QApplication::translate("MainWindow", "\345\257\204\345\255\230\345\231\250\350\265\267\345\247\213\345\234\260\345\235\200\357\274\232", nullptr));
        label_58->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\225\260\351\207\217\357\274\232", nullptr));
        label_59->setText(QApplication::translate("MainWindow", "\351\223\276\346\216\245\347\212\266\346\200\201\357\274\232", nullptr));
        label_139->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\345\235\220\346\240\207\346\211\213\345\212\250\350\276\223\345\205\245\357\274\232", nullptr));
        modbusStatus_R->setText(QApplication::translate("MainWindow", "\346\234\252\350\277\236\346\216\245", nullptr));
        btn_modbusclose_R->setText(QApplication::translate("MainWindow", "...", nullptr));
        lineEdit_9->setText(QApplication::translate("MainWindow", "\345\234\260\345\235\200", nullptr));
        lineEdit_24->setText(QApplication::translate("MainWindow", "0[0-1]", nullptr));
        lineEdit_25->setText(QApplication::translate("MainWindow", "1[2-3]", nullptr));
        lineEdit_12->setText(QApplication::translate("MainWindow", "\345\200\274", nullptr));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "modbus_\345\206\231\345\205\245", nullptr));
        label_41->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        label_42->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250ID\357\274\232", nullptr));
        label_37->setText(QApplication::translate("MainWindow", "\345\257\204\345\255\230\345\231\250\350\265\267\345\247\213\345\234\260\345\235\200\357\274\232", nullptr));
        label_38->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\225\260\351\207\217\357\274\232", nullptr));
        label_56->setText(QApplication::translate("MainWindow", "\351\223\276\346\216\245\347\212\266\346\200\201\357\274\232", nullptr));
        modbusStatus_W->setText(QApplication::translate("MainWindow", "\346\234\252\350\277\236\346\216\245", nullptr));
        lineEdit_6->setText(QApplication::translate("MainWindow", "\345\234\260\345\235\200", nullptr));
        lineEdit_20->setText(QApplication::translate("MainWindow", "0[0-1]", nullptr));
        lineEdit_21->setText(QApplication::translate("MainWindow", "1[2-3]", nullptr));
        lineEdit_7->setText(QApplication::translate("MainWindow", "\345\200\274", nullptr));
        groupBox_13->setTitle(QApplication::translate("MainWindow", "\347\233\270\346\234\272\350\256\276\347\275\256", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\347\233\270\346\234\272\357\274\232", nullptr));
        comB_cameraBrand->setItemText(0, QApplication::translate("MainWindow", "HIK", nullptr));
        comB_cameraBrand->setItemText(1, QApplication::translate("MainWindow", "Basler", nullptr));

        btn_connectCamera->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        label_48->setText(QApplication::translate("MainWindow", " \346\233\235\345\205\211\357\274\232", nullptr));
        label_49->setText(QApplication::translate("MainWindow", " \345\270\247\347\216\207\357\274\232", nullptr));
        label_50->setText(QApplication::translate("MainWindow", " \350\247\246\345\217\221\346\250\241\345\274\217\357\274\232", nullptr));
        camareTriggerType->setItemText(0, QApplication::translate("MainWindow", "\350\277\236\347\273\255\351\207\207\351\233\206", nullptr));
        camareTriggerType->setItemText(1, QApplication::translate("MainWindow", "\350\275\257\344\273\266\350\247\246\345\217\221", nullptr));
        camareTriggerType->setItemText(2, QApplication::translate("MainWindow", "\345\244\226\351\203\250\350\247\246\345\217\221", nullptr));

        groupBox_14->setTitle(QApplication::translate("MainWindow", "\350\267\257\345\276\204\350\256\276\347\275\256", nullptr));
        label_52->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", nullptr));
        btn_saveCameraImagePath->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_51->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\345\255\230\345\202\250\357\274\232", nullptr));
        btn_autosaveImage->setText(QApplication::translate("MainWindow", "...", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
        menu_File->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_help->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
