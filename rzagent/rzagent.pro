#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:37:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x

TARGET = rzagent
TEMPLATE = app

DEFINES += UMX_X11_SUPPORTED
DEFINES += UMX_CHECK_FAKE_FACE

DEFINES += DESKTOP
DEFINES +=POCO_NO_SOO

target.file = $${TARGET}
target.path = /home/root
INSTALLS += target

REMOVE_OBJECT = rm -rf ./*.o
REMOVE_UI = rm -rf ./ui_*
REMOVE_MOC = rm -rf ./moc_*
QMAKE_CLEAN += rm -rf ./rzagent && \
               $${REMOVE_OBJECT} && \
               $${REMOVE_UI} && \
               $${REMOVE_MOC}

QMAKE_POST_LINK += $${REMOVE_OBJECT} && \
                   $${REMOVE_UI} && \
                   $${REMOVE_MOC}


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



INCLUDEPATH += ../lib \
               ../include \
               ../include/Poco/Poco_umx \
               ../include/umxAlgoLib \
               ../include/umxCamLib \
               ../include/umxCommonLib \
               ../include/umxDBLib \
               ../include/umxNetLib \
               ../lib/umxPeriDevLib/inc\
               /opt/poky/1.8.1/sysroots/cortexa9hf-vfp-neon-poky-linux-gnueabi/usr/include

LIBS += \
        -L../lib/NeoFace \
        -lneofacem400 \
        -L../lib/Neuro \
        -lNBiometricClient -lNBiometrics -lNDevices -lNMedia -lNLicensing -lNCore -lNMediaProc \
        -L../lib/libs -lumxAlgo -lumxCam -lumxNet -lumxDB -lumxCommon \
        -L../lib/umxPeriDevLib -lumxPeriDev \
        -L../lib/Poco -lPocoData -lPocoDataSQLite -lPocoFoundation -lPocoXML -lPocoUtil -lPocoNet \
        -fopenmp \
        -lopencv_core -lopencv_imgproc -lopencv_objdetect -lopencv_highgui \
        -L../lib/mcrypt \
        -lmcrypt

SOURCES += main.cpp\
        mainwindow.cpp \
    logentity.cpp \
    statusform.cpp \
    httpclient.cpp \
    utilshelper.cpp \
    myserver.cpp \
    algoutils.cpp \
    roothandler.cpp \
    myrequesthandler.cpp \
    myrequesthandlerfactory.cpp \
    serverthread.cpp \
    runtime.cpp \
    entities.cpp \
    CDeviceRs232.cpp \
    CDeviceRs485.cpp

HEADERS  += mainwindow.h \
    logentity.h \
    statusform.h \
    httpclient.h \
    utilshelper.h \
    myserver.h \
    algoutils.h \
    roothandler.h \
    myrequesthandler.h \
    myrequesthandlerfactory.h \
    serverthread.h \
    runtime.h \
    entities.h \
    CDeviceRs232.h \
    CDeviceRs485.h

FORMS    += mainwindow.ui \
    statusform.ui

RESOURCES += \
    images.qrc
