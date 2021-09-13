#opencv2413  目录下不能有空格和中文
#OPENCV_DIR = D:/OpenCV/opencv-2.4.13/build
#OPENCV_LIB_DIR = $${OPENCV_DIR}/x64/vc12/lib
#CV_VER = 2413


#opencv3.4.1
OPENCV_DIR = D:/opencv_contrib3.4.1/build
OPENCV_LIB_DIR = $${OPENCV_DIR}/x64/vc15/lib
CV_VER = 341





#如果是opencv3.0往后就改为下面
CV_LIB_NAMES = world
#CV_LIB_NAMES = core imgproc highgui calib3d


for(lib, CV_LIB_NAMES){
	CV_LIBS +=-lopencv_$$lib
}
CONFIG(release, debug|release){
	CV_LIB_PREFIX =$$CV_VER
}
else{
	CV_LIB_PREFIX = $${CV_VER}d
	CONFIG +=console
}
for(lib,CV_LIBS){
	CV_LIBS_NEW += $$lib$$CV_LIB_PREFIX
}

CV_LIBS = $$CV_LIBS_NEW $$CV_EXT_LIBS
LIBS += -L$$OPENCV_LIB_DIR $$CV_LIBS
INCLUDEPATH += $$OPENCV_DIR/include

DISTFILES += \
    $$PWD/Basler.pri \
    $$PWD/Basler.pri




