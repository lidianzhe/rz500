#-------------------------------------------------
#
# Project created by QtCreator 2016.4.18
#
#-------------------------------------------------

#VERSION_MAJOR = 0  #single digit
#VERSION_MINOR = 1 #double digit
#VERSION_RIVISION = 1
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] vvv
TARGET_NAME = umxAlgo
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] ^^^
TOPPATH = ../..
DEPLOYPATH = $${TOPPATH}/deploy
LAUNCHER_APP_PATH = ../libs
#------------------------------------------------------------------

VER_MAJ = 0
VER_MIN = 1
VER_PAT = 18
DEFINES += UMXALGO_MAJOR_VERSION=$${VER_MAJ}
DEFINES += UMXALGO_MINOR_VERSION=$${VER_MIN}
DEFINES += UMXALGO_REVISION=$${VER_PAT}

QT       -= core gui
TEMPLATE = lib

TARGET = $${LAUNCHER_APP_PATH}/$${TARGET_NAME}

QMAKE_CXXFLAGS += -std=c++0x

linux-gnueabi-oe-g++ {
    DEFINES += __IN_UMX_DEVICE__
    message(__IN_UMX_DEVICE__ defined)
} else {
    message(__IN_UMX_DEVICE__ NOT defined)
}

# EF-45(unklee88)-55 : move deploy/include to include vvv
MAKE_ALGOLIB = mkdir -p $${TOPPATH}/include/umxAlgoLib
#EF-45(unklee88)-32 : for umxLibAndUMXDemo.pro build
REMOVE_ALGOLIB_HEADER = $${TOPPATH}/include/umxAlgoLib/umxAlgo*.h
# EF-45(unklee88)-55 : move deploy/include to include ^^^
REMOVE_LIBRARY = $${LAUNCHER_APP_PATH}/$${TARGET_NAME}.*
####################################################
# EF-45(unklee88)-55 : move deploy/include to include vvv
COPY_ALGOLIB_HEADER = cp -f ./umxAlgo*.h $${TOPPATH}/include/umxAlgoLib/.
# EF-45(unklee88)-55 : move deploy/include to include ^^^

#EF-45(unklee88)-32 : for umxLibAndUMXDemo.pro build
QMAKE_POST_LINK += $${MAKE_ALGOLIB} && rm -f $${REMOVE_ALGOLIB_HEADER} && $${COPY_ALGOLIB_HEADER}
QMAKE_CLEAN += $${REMOVE_ALGOLIB_HEADER} $${REMOVE_LIBRARY}
####################################################

LIBS += \
	 -L../Poco \
#        -lPocoData \
#        -lPocoDataSQLite \
#        -lPocoFoundation \
#        -lPocoXML \
#        -lPocoUtil \
#        -lPocoNet \
        -L../NeoFace \
        -lneofacem400 \
        -L../Neuro \
        -lNBiometricClient \
        -lNBiometrics \
        -lNDevices \
        -lNMedia \
        -lNLicensing \
        -lNCore \
        -lNMediaProc \
        -L../Mirlin \
        -lMirlin.2.32 \
        -L../DeltaId/ActiveIris \
        -liris_engine_lib_v3 \
        -fopenmp \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_objdetect \
        -lopencv_highgui \

# EF-45(bkko)-27 : Added deltaID occlusion function vvv
#        -L../DeltaId/ActiveIris \
#        -liris_engine_v3
# EF-45(bkko)-27 : Added deltaID occlusion function ^^^

INCLUDEPATH += $${TOPPATH}/include \
            $${TOPPATH}/include/Neuro \
            $${TOPPATH}/include/DeltaId/ActiveIris \
            ..

SOURCES += \
        umxAlgo.cpp \
        mainalgo.cpp \
        iris/activeirisalgo.cpp \
        iris/mirlinalgo.cpp \
        iris/verieyealgo.cpp \
        face/neofacealgo.cpp \
        face/verilookalgo.cpp \
        face/opencvalgo.cpp \
        algomainrun.cpp \
        algosubrun.cpp

HEADERS  += \
        mainalgo.h \
        iris/activeirisalgo.h \
        iris/irisalgo.h \
        iris/mirlinalgo.h \
        iris/verieyealgo.h \
        face/facealgo.h \
        face/neofacealgo.h \
        face/verilookalgo.h \
        external/ROITemplateGenerator.hpp \
        external/Mirlin.h \
        external/NeoFace.hpp \
        face/opencvalgo.h \
        umxAlgo.h \
        umxAlgoGlobal.h \
        algomainrun.h \
        algosubrun.h



