#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:37:53
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x

TARGET = rzagent
TEMPLATE = app

DEFINES += DESKTOP
DEFINES +=POCO_NO_SOO

target.file = $${TARGET}
target.path = /home/root
INSTALLS += target


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
               ../lib/umxPeriDevLib/inc

LIBS += \
        -L../lib/NeoFace \
        -lneofacem400 \
        -L../lib/Neuro \
        -lNBiometricClient -lNBiometrics -lNDevices -lNMedia -lNLicensing -lNCore -lNMediaProc \
        -L../lib/libs \
        -lumxAlgo \
        -lumxCam \
        -lumxNet \
        -lumxDB \
        -lumxCommon \
        -L../lib/umxPeriDevLib \
        -lumxPeriDev \
        -L../lib/Poco -lPocoData -lPocoDataSQLite -lPocoFoundation -lPocoXML -lPocoUtil -lPocoNet \
        -fopenmp \
        -lopencv_core -lopencv_imgproc -lopencv_objdetect -lopencv_highgui \
        -L../lib/mcrypt \
        -lmcrypt

SOURCES += main.cpp\
        mainwindow.cpp \
    logentity.cpp \
    serverlogentities.cpp \
    statusform.cpp \
    httpclient.cpp \
    utilshelper.cpp

HEADERS  += mainwindow.h \
    logentity.h \
    serverlogentities.h \
    statusform.h \
    httpclient.h \
    utilshelper.h

FORMS    += mainwindow.ui \
    statusform.ui

RESOURCES += \
    images.qrc
