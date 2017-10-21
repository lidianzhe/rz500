#-------------------------------------------------
#
# Project created by QtCreator 2016.4.18
#
#-------------------------------------------------

#VERSION_MAJOR = 0  #single digit
#VERSION_MINOR = 1 #double digit
#VERSION_RIVISION = 1
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] vvv
TARGET_NAME = umxCommon
# EF-45(unklee88)-46 : rename the libraries (algo, umx, net, db, common) - umx[Name] ^^^
TOPPATH = ../..
DEPLOYPATH = $${TOPPATH}/deploy
#### EF-45(unklee88)-29 : service/umxLuancher/libs -> service/lib/libs moved ####
LAUNCHER_APP_PATH = ../libs
#################################################################################
#------------------------------------------------------------------

VER_MAJ = 0
VER_MIN = 1
VER_PAT = 18
DEFINES += UMXCOMMON_MAJOR_VERSION=$${VER_MAJ}
DEFINES += UMXCOMMON_MINOR_VERSION=$${VER_MIN}
DEFINES += UMXCOMMON_REVISION=$${VER_PAT}

QT       -= core gui
TEMPLATE = lib

TARGET = $${LAUNCHER_APP_PATH}/$${TARGET_NAME}

#public_headers.path = ../../deploy/include/umxCommonLib/cjson
#public_headers.files = cjson/*.h
#INSTALLS += public_headers

QMAKE_CXXFLAGS += -std=c++0x

linux-gnueabi-oe-g++ {
    DEFINES += __IN_UMX_DEVICE__
    message(__IN_UMX_DEVICE__ defined)
} else {
    message(__IN_UMX_DEVICE__ NOT defined)
}

# EF-45(unklee88)-55 : move deploy/include to include vvv
MAKE_COMMONLIB = mkdir -p $${TOPPATH}/include/umxCommonLib
MAKE_COMMONLIB_CJSON = mkdir -p $${TOPPATH}/include/umxCommonLib/cjson
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged vvv
# MAKE_COMMONLIB_DATATYPES = mkdir  -p $${TOPPATH}/include/umxCommonLib/DataTypes
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged ^^^
# EF-45(unklee88)-58 : recover Utils header vvv
# EF-45(unklee88)-56 : removed no essential header file in deploy vvv
MAKE_COMMONLIB_UTILS = mkdir -p $${TOPPATH}/include/umxCommonLib/Utils
# EF-45(unklee88)-56 : removed no essential header file in deploy ^^^
# EF-45(unklee88)-58 : recover Utils header ^^^
# EF-45(unklee88)-67 : umxCommonGlobal.h added vvv
REMOVE_COMMON_HEADER = rm -rf $${TOPPATH}/include/umxCommonLib/*.h
# EF-45(unklee88)-67 : umxCommonGlobal.h added ^^^
REMOVE_CJSON_HEADER = rm -rf $${TOPPATH}/include/umxCommonLib/cjson/*.h
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged vvv
# REMOVE_DATATYPES_HEADER = rm -rf $${TOPPATH}/include/umxCommonLib/DataTypes/*.h
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged ^^^
# EF-45(unklee88)-58 : recover Utils header vvv
# EF-45(unklee88)-56 : removed no essential header file in deploy vvv
REMOVE_UTILS_HEADER = rm -rf $${TOPPATH}/include/umxCommonLib/Utils/*.h
# EF-45(unklee88)-56 : removed no essential header file in deploy ^^^
# EF-45(unklee88)-58 : recover Utils header ^^^
# EF-45(unklee88)-55 : move deploy/include to include ^^^

REMOVE_LIBRARY = rm -rf $${LAUNCHER_APP_PATH}/$${TARGET_NAME}.*

# EF-45(unklee88)-67 : umxCommonGlobal.h added vvv
COPY_COMMON_HEADER = cp -f ./*.h $${TOPPATH}/include/umxCommonLib/.
# EF-45(unklee88)-67 : umxCommonGlobal.h added ^^^
# EF-45(unklee88)-55 : move deploy/include to include vvv
COPY_CJSON_HEADER = cp -f ./cjson/*.h $${TOPPATH}/include/umxCommonLib/cjson/.
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged vvv
# COPY_DATATYPES_HEADER = cp -f ./DataTypes/*.h $${TOPPATH}/include/umxCommonLib/DataTypes/.
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged ^^^
# EF-45(unklee88)-58 : recover Utils header vvv
# EF-45(unklee88)-56 : removed no essential header file in deploy vvv
COPY_UTILS_HEADER = cp -f ./Utils/*.h $${TOPPATH}/include/umxCommonLib/Utils/.
# EF-45(unklee88)-56 : removed no essential header file in deploy ^^^
# EF-45(unklee88)-58 : recover Utils header ^^^
# EF-45(unklee88)-55 : move deploy/include to include ^^^

# EF-45(unklee88)-58 : recover Utils header vvv
# EF-45(unklee88)-56 : removed no essential header file in deploy vvv
#QMAKE_POST_LINK += $${MAKE_COMMONLIB} && $${MAKE_COMMONLIB_CJSON} && $${MAKE_COMMONLIB_DATATYPES} && \
#$${REMOVE_CJSON_HEADER} && $${REMOVE_DATATYPES_HEADER} && \
#$${COPY_CJSON_HEADER} && $${COPY_DATATYPES_HEADER}

#QMAKE_CLEAN += $${REMOVE_CJSON_HEADER} && $${REMOVE_DATATYPES_HEADER} && $${REMOVE_LIBRARY}


QMAKE_PRE_LINK = rm -rf $${TOPPATH}/deploy && rm -rf rm -rf $${TOPPATH}/data.img && \
                make -C $${TOPPATH}/lib/umxPeriDevLib && \
                make -C $${TOPPATH}/lib/umxVoip

# EF-45(unklee88)-67 : umxCommonGlobal.h added vvv
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged vvv
QMAKE_POST_LINK += $${MAKE_COMMONLIB} && $${MAKE_COMMONLIB_CJSON} && $${MAKE_COMMONLIB_UTILS} && \
$${REMOVE_COMMON_HEADER} && $${REMOVE_CJSON_HEADER} && $${REMOVE_UTILS_HEADER} && \
$${COPY_COMMON_HEADER} && $${COPY_CJSON_HEADER} && $${COPY_UTILS_HEADER}

QMAKE_CLEAN += $${REMOVE_COMMON_HEADER} && $${REMOVE_CJSON_HEADER} && $${REMOVE_UTILS_HEADER} && $${REMOVE_LIBRARY}

# QMAKE_POST_LINK += $${MAKE_COMMONLIB} && $${MAKE_COMMONLIB_CJSON} && $${MAKE_COMMONLIB_DATATYPES} && $${MAKE_COMMONLIB_UTILS} && \
# $${REMOVE_COMMON_HEADER} && $${REMOVE_CJSON_HEADER} && $${REMOVE_DATATYPES_HEADER} && $${REMOVE_UTILS_HEADER} && \
# $${COPY_COMMON_HEADER} && $${COPY_CJSON_HEADER} && $${COPY_DATATYPES_HEADER} && $${COPY_UTILS_HEADER}

# QMAKE_CLEAN += $${REMOVE_COMMON_HEADER} && $${REMOVE_CJSON_HEADER} && $${REMOVE_DATATYPES_HEADER} $${REMOVE_UTILS_HEADER} && $${REMOVE_LIBRARY}
# EF-45(unklee88)-74 : umxCommonLib/DataTypes/* deploy header file arranged ^^^
# EF-45(unklee88)-67 : umxCommonGlobal.h added ^^^
# EF-45(unklee88)-56 : removed no essential header file in deploy ^^^
# EF-45(unklee88)-58 : recover Utils header ^^^

LIBS += -L../Poco \
        -lPocoData \
        -lPocoDataSQLite \
        -lPocoFoundation \
        -lPocoXML \
        -lPocoUtil \
        -lPocoNet 

#For using Poco library
POCO_PATH = ../../
INCLUDEPATH += $$POCO_PATH/include \
               ..

SOURCES += \ 
# EF-45(unklee88)-81 : get version arragned vvv
    umxCommon.cpp \
# EF-45(unklee88)-81 : get version arragned ^^^
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/BiometricData.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
    DataTypes/CameraConfiguration.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/CameraControlResponse.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib vvv
#    DataTypes/CameraInformation.cpp \
#    DataTypes/EnrolTemplate.cpp \
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib ^^^
    DataTypes/FaceData.cpp \
    DataTypes/FaceDataWithSubjectInfo.cpp \
    DataTypes/ImageCapture.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/Lock.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
    DataTypes/LogEntry.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/PreviewData.cpp \
#    DataTypes/SelectedData.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
    DataTypes/SubjectData.cpp \
    DataTypes/ImageToSaveData.cpp \
    DataTypes/UserInfoData.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/VersionConverter.cpp \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
    DataTypes/VersionData.cpp \
    cjson/cJSON.c

HEADERS  += \
# EF-45(unklee88)-81 : get version arragned vvv
    umxCommon.h \
# EF-45(unklee88)-81 : get version arragned ^^^
# EF-45(unklee88)-67 : umxCommonGlobal.h added vvv
    umxCommonGlobal.h \
# EF-45(unklee88)-67 : umxCommonGlobal.h added ^^^
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/BiometricData.h \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
# EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraConfiguration.h vvv
#    DataTypes/CameraConfiguration.h \
# EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraConfiguration.h ^^^
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/CameraControlResponse.h \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib vvv
#    DataTypes/CameraEncounter.h \
#    DataTypes/CameraInformation.h \
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib ^^^
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib vvv
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib vvv
# EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraMode.h vvv
#    DataTypes/CameraMode.h \
# EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraMode.h ^^^
# EF-45(unklee88)-43 : CameraMode class moved from umxCommonLib -> umxDBLib ^^^
# EF-45(unklee88)-47 : recover CameraMode.h from umxDBLib -> commonLib ^^^
# EF-45(unklee88)-42 : DualEyeImage, DualEyeQualityMetrics, DualEyeTemplate, FaceFeature, FaceImage, FaceInfo, SingleEyeImage,
#                      SingleEyeQualityMetrics, SingleEyeTemplate struct removed in umxConmmonLib vvv
#    DataTypes/DualEyeImage.h \
#    DataTypes/DualEyeQualityMetrics.h \
#    DataTypes/DualEyeTemplate.h \
# EF-45(unklee88)-42 : DualEyeImage, DualEyeQualityMetrics, DualEyeTemplate, FaceFeature, FaceImage, FaceInfo, SingleEyeImage,
#                      SingleEyeQualityMetrics, SingleEyeTemplate struct removed in umxConmmonLib ^^^
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib vvv
#    DataTypes/EnrolTemplate.h \
#    DataTypes/EnrollData.h \
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib ^^^
# EF-45(unklee88)-69 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceData.h vvv
#    DataTypes/FaceData.h \
# EF-45(unklee88)-69 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceData.h ^^^
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceDataWithSubjectInfo.h vvv
#    DataTypes/FaceDataWithSubjectInfo.h \
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceDataWithSubjectInfo.h ^^^
# EF-45(unklee88)-42 : DualEyeImage, DualEyeQualityMetrics, DualEyeTemplate, FaceFeature, FaceImage, FaceInfo, SingleEyeImage,
#                      SingleEyeQualityMetrics, SingleEyeTemplate struct removed in umxConmmonLib vvv
#    DataTypes/FaceFeature.h \
#    DataTypes/FaceImage.h \
#    DataTypes/FaceInfo.h \
# EF-45(unklee88)-42 : DualEyeImage, DualEyeQualityMetrics, DualEyeTemplate, FaceFeature, FaceImage, FaceInfo, SingleEyeImage,
#                      SingleEyeQualityMetrics, SingleEyeTemplate struct removed in umxConmmonLib ^^^
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h vvv
#    DataTypes/ImageCapture.h \
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h ^^^
# EF-45(unklee88)-73 : umxCommonLib/DataTypes/JSONHelper.h moved umxCommonLib/cjson folder vvv
    cjson/JSONHelper.h \
# EF-45(unklee88)-73 : umxCommonLib/DataTypes/JSONHelper.h moved umxCommonLib/cjson folder ^^^
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/Lock.h \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/LogEntry.h vvv
#    DataTypes/LogEntry.h \
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/LogEntry.h ^^^
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/PreviewData.h \
#    DataTypes/SelectedData.h \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
# EF-45(unklee88)-42 : DualEyeImage, DualEyeQualityMetrics, DualEyeTemplate, FaceFeature, FaceImage, FaceInfo, SingleEyeImage,
#                      SingleEyeQualityMetrics, SingleEyeTemplate struct removed in umxConmmonLib vvv
#    DataTypes/SingleEyeImage.h \
#    DataTypes/SingleEyeQualityMetrics.h \
#    DataTypes/SingleEyeTemplate.h \
# EF-45(unklee88)-42 : DualEyeImage, DualEyeQualityMetrics, DualEyeTemplate, FaceFeature, FaceImage, FaceInfo, SingleEyeImage,
#                      SingleEyeQualityMetrics, SingleEyeTemplate struct removed in umxConmmonLib ^^^
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/SubjectData.h vvv
#    DataTypes/SubjectData.h \
# EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/SubjectData.h ^^^
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib vvv
#    DataTypes/UpdateFaceDate.h \
# EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib ^^^
# EF-45(unklee88)-71 : umxCommonGlobal.h includes umxCommonLib/DataTypes/UserInfoData.h vvv
#    DataTypes/UserInfoData.h \
# EF-45(unklee88)-71 : umxCommonGlobal.h includes umxCommonLib/DataTypes/UserInfoData.h vvv
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#    DataTypes/VersionConverter.h \
# EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^
# EF-45(unklee88)-72 : umxCommonGlobal.h includes umxCommonLib/DataTypes/VersionData.h vvv
#    DataTypes/VersionData.h \
# EF-45(unklee88)-72 : umxCommonGlobal.h includes umxCommonLib/DataTypes/VersionData.h ^^^
    Utils/Base64ToTemplateConverter.h \
    Utils/TemplateToBase64Converter.h \
    cjson/cJSON.h \
    cjson/cJSONpp.h
