#-------------------------------------------------
#
# Project created by QtCreator 2016.4.18
#
#-------------------------------------------------

###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
#VERSION_MAJOR = 0  #single digit
#VERSION_MINOR = 1 #double digit
#VERSION_RIVISION = 1
#########################################################################
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] vvv
TARGET_NAME = umxCam
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] ^^^
###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
#DEMO_APP_PATH = ../../lib
TOPPATH = ../..
DEPLOYPATH = $${TOPPATH}/deploy
LAUNCHER_APP_PATH = ../libs
#########################################################################
#------------------------------------------------------------------

QT       -= core gui
TEMPLATE = lib

###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
#TARGET = $${DEMO_APP_PATH}/$${TARGET_NAME}_$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_RIVISION}
#Version changed by JJ to V1.0.0 at 20160627
VER_MAJ = 1
VER_MIN = 0
VER_PAT = 53
DEFINES += UMXCAM_MAJOR_VERSION=$${VER_MAJ}
DEFINES += UMXCAM_MINOR_VERSION=$${VER_MIN}
DEFINES += UMXCAM_REVISION=$${VER_PAT}

#Check fake face
#DEFINES += UMX_CHECK_FAKE_FACE

DEFINES += UMXCAM_USE_WHITE_LED

QT       -= core gui
TEMPLATE = lib

TARGET = $${LAUNCHER_APP_PATH}/$${TARGET_NAME}
#########################################################################

QMAKE_CXXFLAGS += -std=c++0x

linux-gnueabi-oe-g++ {
DEFINES += __IN_UMX_DEVICE__
    message(__IN_UMX_DEVICE__ defined)
} else {
    message(__IN_UMX_DEVICE__ NOT defined)
}

###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
# EF-45(unklee88)-55 : move deploy/include to include vvv
MAKE_UMXLIB = mkdir -p $${TOPPATH}/include/umxCamLib
#EF-45(unklee88)-32 : for umxLibAndUMXDemo.pro build
REMOVE_UMXLIB_HEADER = $${TOPPATH}/include/umxCamLib/umxCam.h $${TOPPATH}/include/umxCamLib/umxCamGlobal.h
# EF-45(unklee88)-55 : move deploy/include to include ^^^
REMOVE_LIBRARY = $${LAUNCHER_APP_PATH}/$${TARGET_NAME}.*
####################################################
# EF-45(unklee88)-55 : move deploy/include to include vvv
COPY_UMXLIB_HEADER = cp -f ./umxCam.h ./umxCamGlobal.h $${TOPPATH}/include/umxCamLib/.
# EF-45(unklee88)-55 : move deploy/include to include ^^^
#EF-45(unklee88)-32 : for umxLibAndUMXDemo.pro build
QMAKE_POST_LINK += $${MAKE_UMXLIB} && rm -f $${REMOVE_UMXLIB_HEADER} && $${COPY_UMXLIB_HEADER}
QMAKE_CLEAN += $${REMOVE_UMXLIB_HEADER} $${REMOVE_LIBRARY}
####################################################
#########################################################################

LIBS += -L../Poco \
        -lPocoData \
        -lPocoDataSQLite \
        -lPocoFoundation \
        -lPocoXML \
        -lPocoUtil \
        -lPocoNet \
        -L../NeoFace \
        -lneofacem400 \
        -L../Mirlin \
        -lMirlin.2.32 \
# EF-45(bkko)-27 : Added deltaID occlusion function vvv
        -L../DeltaId/ActiveIris \
        -liris_engine_lib_v3 \
# EF-45(bkko)-27 : Added deltaID occlusion function ^^^
        -fopenmp \
        -L../Neuro \
        -lNBiometricClient \
        -lNBiometrics \
        -lNDevices \
        -lNMedia \
        -lNLicensing \
        -lNCore \
        -lNMediaProc \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_objdetect \
        -lopencv_highgui \
###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
# EF-45(bkko)-6 : Added Iris recognition engine for DeltaID vvv
#        -L../DeltaId/ActiveIris \
#        -liris_engine_v3 \
# EF-45(bkko)-6 : Added Iris recognition engine for DeltaID ^^^
#### EF-45(unklee88)-29 : service/umxLuancher/libs -> service/lib/libs moved ####
        -L../libs \
#################################################################################
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] vvv
        -lumxAlgo
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] ^^^
#########################################################################

POCO_PATH = ../..
INCLUDEPATH += $$POCO_PATH/include ../../include/Neuro ../umxPeriDevLib/inc \
###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
# EF-45(unklee88)-55 : move deploy/include to include vvv
            $$TOPPATH/include/umxAlgoLib
# EF-45(unklee88)-55 : move deploy/include to include ^^^
#########################################################################

#If used X11 supported flag
DEFINES += UMX_X11_SUPPORTED
#
#

#If debug mode enabled
#DEFINES += UMXCAM_DEBUG_ENABLE

#Service memory leak resolve
DEFINES += UMX_SERVICE_MEMORY_LEAK_RESOLVE
#Library memory leak resolve
DEFINES += UMX_LIB_MEMORY_LEAK_RESOLVE

SOURCES += calibplane.cpp \
    cluster.cpp \
    clusterpoint.cpp \
    command.cpp \
    distestimator.cpp \
    mainimagerun.cpp \
    mainproc.cpp \
    motionobjdetector.cpp \
    narrowcamera.cpp \
    stereo.cpp \
    umxCam.cpp \
    umxcamera.cpp \
    umxeeprom.cpp \
    umximage.cpp \
    widecamera.cpp \
    capturerun.cpp \
    objdetector.cpp \
    labeling.cpp \
    eyefinder.cpp \
    faceeyerun.cpp \
    watermark.cpp
###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
#    ../umxAlgoLib/umxAlgo.cpp \
#    ../umxAlgoLib/mainalgo.cpp \
#    ../umxAlgoLib/iris/mirlinalgo.cpp \
#    ../umxAlgoLib/iris/verieyealgo.cpp \
#    ../umxAlgoLib/face/neofacealgo.cpp \
#    ../umxAlgoLib/face/verilookalgo.cpp \
#    ../umxAlgoLib/face/opencvalgo.cpp
#########################################################################

HEADERS  += calibplane.h \
    cluster.h \
    clusterpoint.h \
    command.h \
    distestimator.h \
    mainimagerun.h \
    mainproc.h \
    motionobjdetector.h \
    narrowcamera.h \
    stereo.h \
    umxcamera.h \
    umxeeprom.h \
    umximage.h \
    widecamera.h \
    capturerun.h \
    objdetector.h \
    labeling.h \
    eyefinder.h \
    point.h \
    pointf.h \
    rect.h \
    faceeyerun.h \
    umxCam.h \
    umxCamGlobal.h \
    watermark.h
###### EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ######
#    ../umxAlgoLib/umxAlgo.h \
#    ../umxAlgoLib/umxAlgoGlobal.h \
#    ../umxAlgoLib/mainalgo.h \
#    ../umxAlgoLib/iris/irisalgo.h \
#    ../umxAlgoLib/iris/mirlinalgo.h \
#    ../umxAlgoLib/iris/verieyealgo.h \
#    ../umxAlgoLib/face/facealgo.h \
#    ../umxAlgoLib/face/neofacealgo.h \
#    ../umxAlgoLib/face/verilookalgo.h \
#    ../umxAlgoLib/external/ROITemplateGenerator.hpp \
#    ../umxAlgoLib/external/Mirlin.h \
#    ../umxAlgoLib/external/NeoFace.hpp \
#    ../umxAlgoLib/face/opencvalgo.h
#########################################################################


