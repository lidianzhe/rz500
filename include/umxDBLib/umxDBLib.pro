#-------------------------------------------------
#
# Project created by QtCreator 2016.4.18
#
#-------------------------------------------------

#VERSION_MAJOR = 0  #single digit
#VERSION_MINOR = 1 #double digit
#VERSION_RIVISION = 1
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] vvv
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne vvv
TARGET_NAME = umxDB
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne ^^^
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] ^^^
TOPPATH = ../..
DEPLOYPATH = $${TOPPATH}/deploy
#### EF-45(unklee88)-29 : service/umxLuancher/libs -> service/lib/libs moved ####
LAUNCHER_APP_PATH = ../libs
#################################################################################
#------------------------------------------------------------------

VER_MAJ = 0
VER_MIN = 1
VER_PAT = 33
DEFINES += UMXDB_MAJOR_VERSION=$${VER_MAJ}
DEFINES += UMXDB_MINOR_VERSION=$${VER_MIN}
DEFINES += UMXDB_REVISION=$${VER_PAT}

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
MAKE_DBLIB = mkdir -p $${TOPPATH}/include/umxDBLib
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib vvv
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib vvv
#MAKE_DBLIB_DATATYPES = mkdir  -p $${DEPLOYPATH}/include/umxDBLib/DataTypes
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib ^^^
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib ^^^
#### EF-45(unklee88)-27 : remove include files not to need ####
#MAKE_DBLIB_DATAACCESS = mkdir -p $${DEPLOYPATH}/include/umxDBLib/DataAccess
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne vvv
REMOVE_DBLIB_HEADER = rm -f $${TOPPATH}/include/umxDBLib/umxDB*.h
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne ^^^
# EF-45(unklee88)-55 : move deploy/include to include ^^^
#REMOVE_DATACCESS_HEADER = rm -rf $${DEPLOYPATH}/include/umxDBLib/DataAccess/*.h
###############################################################
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib vvv
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib vvv
#REMOVE_DATATYPES_HEADER = rm -rf $${DEPLOYPATH}/include/umxDBLib/DataTypes/*.h
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib ^^^
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib ^^^
REMOVE_LIBRARY = rm -rf $${LAUNCHER_APP_PATH}/$${TARGET_NAME}.*
#### EF-45(unklee88)-27 : remove include files not to need ####
# EF-45(unklee88)-55 : move deploy/include to include vvv
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne vvv
COPY_DBLIB_HEADER = cp -f ./umxDB*.h $${TOPPATH}/include/umxDBLib/.
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne ^^^
# EF-45(unklee88)-55 : move deploy/include to include ^^^
#COPY_DATAACCESS_HEADER = cp -f ./DataAccess/*.h $${DEPLOYPATH}/include/umxDBLib/DataAccess/.
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib vvv
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib vvv
#COPY_DATATYPES_HEADER = cp -f ./DataTypes/*.h $${DEPLOYPATH}/include/umxDBLib/DataTypes/.

QMAKE_POST_LINK += $${MAKE_DBLIB} && \
$${REMOVE_DBLIB_HEADER} && \
$${COPY_DBLIB_HEADER}

QMAKE_CLEAN += $${REMOVE_DBLIB_HEADER} && $${REMOVE_LIBRARY}
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib ^^^
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib ^^^
###############################################################

LIBS += -L../Poco \
        -lPocoData \
        -lPocoDataSQLite \
        -lPocoFoundation \
        -lPocoXML \
        -lPocoUtil \
        -lPocoNet \
        -L$${LAUNCHER_APP_PATH} \
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] vvv
        -lumxCommon
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] ^^^

#For using Poco library
POCO_PATH = ../../
# EF-45(unklee88)-55 : move deploy/include to include vvv
COMMON_CJON_HEADER = $${TOPPATH}/include/umxCommonLib/
# EF-45(unklee88)-55 : move deploy/include to include ^^^
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne vvv
UMXCAM_HEADER = $${TOPPATH}/include/umxCamLib/
UMXALGO_HEADER = $${TOPPATH}/include/umxAlgoLib/
INCLUDEPATH += $$POCO_PATH/include ./DataAccess $${COMMON_CJON_HEADER} $${UMXCAM_HEADER} $${UMXALGO_HEADER} \
               ..
# EF-45(unklee88)-76 : umxDBLib's db.h, dbGlobal.h naming chagne ^^^

SOURCES += \ 
    umxDB.cpp \
    maindb.cpp \
    DataAccess/CameraConfigurationDataAccess.cpp \
    DataAccess/DataAccess.cpp \
    DataAccess/EventLogDataAccess.cpp \
    DataAccess/FaceDataAccess.cpp \
    DataAccess/ImageCaptureDataAccess.cpp \
    DataAccess/SubjectDataAccess.cpp \
    DataAccess/UserInfoDataAccess.cpp \
    DataAccess/VersionDataAccess.cpp \
    Crypto/KISA_SEED_CBC.c \
    Crypto/cryptoseed.cpp


HEADERS  += \ 
    maindb.h \
    DataAccess/CameraConfigurationDataAccess.h \
    DataAccess/DataAccess.h \
    DataAccess/DataAccessException.h \
    DataAccess/EventLogDataAccess.h \
    DataAccess/FaceDataAccess.h \
    DataAccess/ImageCaptureDataAccess.h \
    DataAccess/SubjectDataAccess.h \
    DataAccess/UserInfoDataAccess.h \
    DataAccess/VersionDataAccess.h \
    Crypto/KISA_SEED_CBC.h \
    Crypto/cryptoseed.h \
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib vvv
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib vvv
#    DataTypes/CameraMode.h
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib ^^^
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib ^^^
    umxDB.h \
    umxDBGlobal.h




