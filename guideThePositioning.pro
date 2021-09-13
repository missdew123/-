#-------------------------------------------------
#
# Project created by QtCreator 2020-06-01T15:33:35
#
#-------------------------------------------------

QT       += core gui serialbus serialport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guideThePositioning
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
		main.cpp \
		mainwindow.cpp \
	DM_Label.cpp \
	DM_Element.cpp \
	DM_Label.cpp \
	DM_Element.cpp \
	DM_Fit.cpp \
	DM_Label.cpp \
	DM_ImageAlgorith.cpp \
	DM_ImageFeature.cpp \
	DM_Modbus.cpp \
	DM_BaslerCamera.cpp \
	DM_FilmLabel.cpp \
	DM_Projector.cpp \
	flowlayout.cpp \
#    Dialog_Activate.cpp \
	Dialog_GetOpenProjectName.cpp \
	Dialog_GetProjectName.cpp \
	DM_BaslerCamera.cpp \
	DM_Dialog.cpp \
	DM_Element.cpp \
	DM_FilmLabel.cpp \
	DM_Fit.cpp \
	DM_ImageAlgorith.cpp \
	DM_ImageFeature.cpp \
	DM_Label.cpp \
	DM_Modbus.cpp \
	DM_Projector.cpp \
	flowlayout.cpp \
    MvCamera.cpp \
    DM_HIKCamera.cpp \
    DM_Slider.cpp

HEADERS += \
		mainwindow.h \
	DM_Label.h \
	DM_Element.h \
	DM_Label.h \
	DM_Element.h \
	DM_ErrorID.h \
	DM_Fit.h \
	DM_Label.h \
	DM_ImageAlgorithm.h \
	DM_ImageFeature.h \
	DM_Modbus.h \
	DM_BaslerCamera.h \
	DM_FilmLabel.h \
	DM_Projector.h \
	flowlayout.h \
#    Dialog_Activate.h \
	Dialog_GetOpenProjectName.h \
	Dialog_GetProjectName.h \
	DM_BaslerCamera.h \
	DM_Dialog.h \
	DM_Element.h \
	DM_ErrorID.h \
	DM_FilmLabel.h \
	DM_Fit.h \
	DM_ImageAlgorithm.h \
	DM_ImageFeature.h \
	DM_Label.h \
	DM_Modbus.h \
	DM_Projector.h \
	flowlayout.h \
	mainwindow.h \
    MvCamera.h \
    DM_HIKCamera.h \
    DM_Slider.h

FORMS += \
		mainwindow.ui \
#    Dialog_Activate.ui \
	Dialog_GetOpenProjectName.ui \
	Dialog_GetProjectName.ui

include(OpenCV341_Include.pri)
include(Basler.pri)
include(HIKCamera.pri)

RESOURCES += \
	resource.qrc

DISTFILES +=
