#ifndef __NEOFACE_H__
#define __NEOFACE_H__

#if defined(_WIN32) || defined(_WIN64)
#else
    #ifndef __LINUX
        #define __LINUX
    #endif
#endif

#if defined(_WIN32) || defined(_WIN64)
    #ifdef NEOFACEM_EXPORTS
        #define NEOFACEM_API __declspec(dllexport)
    #else
        #define NEOFACEM_API __declspec(dllimport)
    #endif
#else
    #define NEOFACEM_API __attribute__((visibility("default")))
	#define NEOFACEM_API_HIDDEN __attribute__((visibility("hidden")))
#endif

#ifdef NEOFACEM_STATIC
#undef NEOFACEM_API
#define NEOFACEM_API
#endif

#ifndef _NFP_DEFINED_
#define _NFP_DEFINED_

#include <string>

// All
//
/** Success  */
#define NFP_SUCCESS 1
/** Failure  */
#define NFP_FAILED  0
/** Fail to detect the face  */
#define NFP_CANNOT_FIND_FACE 99
/** Completion of data acquisition */
#define NFP_DATA_END 88
/**  Unable to find the specified key data */
#define NFP_NO_DATA  10

//
// System Error
//
/** File open error */
#define NFP_FILE_OPEN_ERROR     -10011
/** File read error */
#define NFP_FILE_READ_ERROR     -10012
/** File export error */
#define NFP_FILE_WRITE_ERROR    -10013
/** File seek error */
#define NFP_FILE_SEEK_ERROR     -10014
/** License error */
#define NFP_LICENSE_ERROR       -10098
/** Internal error */
#define NFP_INTERNAL            -10099

//
// Definition Error
//
/**  Format error */
#define NFP_FORMAT_ERROR        -10101
/** Invalid feature type */
#define NFP_ILLEGAL_TYPE        -10102
/** Invalid feature dimension */
#define NFP_ILLEGAL_DIM         -10103

//
// Condition Error
//
/** Invalid argument */
#define NFP_ARGUMENT_ERROR      -10202
/** Status error */
#define NFP_STATUS_ERROR        -10203


//
// Internal Error
//
/** Initialization error */
#define NFP_NOT_INITIALILZE_ERROR   -10301
/** Invalid parameter for feature conversion */
#define NFP_FET_PARAM_ERROR         -10302
/** Fail to generate the feature object */
#define NFP_FET_CREATE_ERROR        -10303
/** Fail to correct the eye position */
#define NFP_FET_ADJUST_ERROR        -10304
/** Fail to convert the feature data */
#define NFP_FET_CONVERT_ERROR       -10305
/** Database object has not been set */
#define NFP_NO_EXIST_DB_ERROR       -10306
/** Internal parameter error */
#define NFP_PARAM_ERROR             -10307
/** Frontal face judgment error */
#define NFP_ESTIMATEPOSE_ERROR      -10308
/** LocateEyes error */
#define NFP_LOCATEEYES_ERROR        -10309
/** Internal error */
#define NFP_CORE_ERROR              -10399
/** Fail to allocate the memory */
#define NFP_MEMORY_ERROR            -90000

#endif


//
// CFaceInfo
//
/** Detection Algorithm 9: highest-speed high-efficiency */
#define NFP_ALGORITHM009F6  0x000a0006
/** Detection Algorithm 9: highest-speed high-efficiency */
#define NFP_ALGORITHM009F7  0x000a0007


/** Sort detection results by score */
#define NFP_SCORE_ODERED    1
/** Sort detection results by distance */
#define NFP_DISTANCE_ODERED 2

/** Search mode: By depth */
#define NFP_MODE_DEPTH  2
/** Search mode: By time */
#define NFP_MODE_TIME   1

/** Detection mode: Quick mode + Eye correction */
#define NFP_FINDFACE_NORMAL 1
/** Detection mode: Quick mode only*/
/** Note: Do not proceed the face verification
        during Quick mode face detection. Before
        verification, you must correct the eye position
        by using “LocateEyes”.*/
#define NFP_FINDFACE_QUICK  2

/** LoacateEye Type **/
#define NFP_LOCATEEYES_DE   0

/** ON/OFF flag **/
#define NFP_FLG_OFF   0
#define NFP_FLG_ON    1

#if defined(_WIN32) || defined(_WIN64)
#else
    typedef int                 LONG;
    typedef unsigned int        DWORD;
    typedef unsigned char       BYTE;
    typedef unsigned short      WORD;

    typedef struct tagPOINT
    {
        LONG  x;
        LONG  y;
    } POINT;

    typedef struct _RECTL       /* rcl */
    {
        LONG    left;
        LONG    top;
        LONG    right;
        LONG    bottom;
    } RECT;

    typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
    } RGBQUAD;

    typedef struct tagBITMAPINFOHEADER{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
    } BITMAPINFOHEADER;

    typedef struct tagBITMAPINFO {
        BITMAPINFOHEADER    bmiHeader;
        RGBQUAD             bmiColors[1];
    } BITMAPINFO;
#endif


typedef struct tagNEO_POS
{
    POINT position;     /* position */
    float score;        /* score */
}NEO_POS;

/** Structure for face position*/
typedef struct tagNEO_FACEINFO
{
    int index;
    float frontalFaceScore;
    float faceRoll;
    float facePan;
    float faceTilt;
    float facialPosScore;
    float faceConfidence;
    float headConfidence;
    float faceScore;
    float headScore;
    RECT faceArea;
    RECT headArea;
    NEO_POS RightEye;
    NEO_POS LeftEye;
    NEO_POS REyeIn;
    NEO_POS LEyeIn;
    NEO_POS REyeTail;
    NEO_POS LEyeTail;
    NEO_POS CNose;
    NEO_POS RNose;
    NEO_POS LNose;
    NEO_POS TopNose;
    NEO_POS CMouth;
    NEO_POS RMouth;
    NEO_POS LMouth;
    NEO_POS TCUpperLip;
    NEO_POS BCUpperLip;
} NEO_FACEINFO;

/** Frontal face detection*/
#define NFP_FLONTAL_DETECTION     1
/** Nonfrontal face detection*/
#define NFP_NONFLONTAL_DETECTION  2

//
// CFaceFeature
//
/* Feature type: S16 */
#define NFP_FEATURE_S16 16

/** Serialized data element */
#define NFP_SERIALIZETYPE_COMPOUND         0x0008

namespace NeoFaceM
{

	NEOFACEM_API int Initialize();
	NEOFACEM_API int Terminate();
	NEOFACEM_API int SetDATFilePath(char* sPath);

	/**
	 * The class related to the face detection.
	 * Detects the face by extracting the image from
	 * the CImage object.
	 */
	class NEOFACEM_API CFaceInfo
	{
	    friend class CFaceFeature;
	public:
	    float GetFaceRoll();
	    float GetFaceScore();
	    float GetHeadScore();
	    float GetFaceConfidence();
	    float GetHeadConfidence();
	    int GetHeight();
	    int GetWidth();
	    int GetFaceMax();
	    int GetFaceIndex();
	    int SetFaceIndex(int iIndex);
	    int SetParamAlgorithm(int iAlgorithm);
	    int SetParamEyesMaxWidth(int iWidth);
	    int SetParamEyesMinWidth(int iWidth);
	    int SetParamEyesRoll(int iRoll);
	    int SetParamMaxFace(int iMax);
	    int SetParamReliability(float iRel);
	    int SetParamOrderingPolicy(int iOrder);
	    int SetParamDetectArea(const RECT & rect);
	    int SetParamShrinkFactor(int factor);

	    POINT GetRightEye();
	    POINT GetLeftEye();
	    RECT GetFace();
	    RECT GetHead();
	    int  SetRightEye(const POINT & point);
	    int  SetLeftEye(const POINT & point);
	    int  SetFace(const RECT & rect);
	    int  SetHead(const RECT & rect);
	    int SetRGBWeight(int iR, int iG, int iB);
	    int FindFace(const BITMAPINFO & ImageInfo,const void *ImageBody, int FindFaceType = NFP_FINDFACE_NORMAL);
	    int FindFace(const BYTE *raw, int width, int height, int FindFaceType = NFP_FINDFACE_NORMAL);
	    CFaceInfo();
	    virtual ~CFaceInfo();
	    const BYTE * GetRawImage();

	    float GetFrontalFaceScore();
	    float GetFacialPosScore();
	    float GetFacePan();
	    float GetFaceTilt();
	    NEO_FACEINFO GetFaceInfo();
	    int SetFaceInfo(const NEO_FACEINFO& faceInfo);
	    void SetFaceData(const NEO_FACEINFO &FaceInfo, void *pt);
	    int CheckFaceInfo(const NEO_FACEINFO &faceInfo,int width, int height);

	private:
	    void initFace();
	    void DeleteFaceInfo();
	    void* GetFpos();
	    void GetFaceData(void *pt);
	    int ConvertWithMaptoRaw(const BITMAPINFO & info,const void *body);
	    int Convert24toRaw(const BITMAPINFO & info,const void *body);
	    int ConvertImage(const BITMAPINFO & info,const void *body);
	    int Find(int FindFaceType=NFP_FINDFACE_NORMAL);
	    void init();
	    int SetParam(int customFlg=NFP_FLG_OFF);
	    bool EstimatePose();
	    int CheckParamAlgorithm();
	    int LocateEyes(int iType = NFP_LOCATEEYES_DE, int iInfoFlg = NFP_FLG_OFF);
	    int LocateEyes(const BYTE *raw, int width, int height, const POINT &leye, const POINT &reye, void* fpos);
	    int LocateEyes(const POINT& lEye, const POINT& rEye, const void* targetPos);
	    float CalcEyeDist(const void *pos);
	    int SetDetectState(int state, int index);
	    void GetDetectArea(void* area);
	    int Find_Face(void* fposes, void* area, int* faceNum);
	    /** Index for current face */
	    int m_iIndex;
	    /** Number of detected faces */
	    int m_iFaceNum;
	    /**  Detection algorithm */
	    int m_FasdAlgorithm;
	    /** Search mode */
	    int m_FasdDetectionMode;
	    /** Maximum eye distance */
	    int m_FasdEyesMaxWidth;
	    /** Minimum eye distance */
	    int m_FasdEyesMinWidth;
	    /** Eye roll angles */
	    int m_FasdEyesRoll;
	    /** Maximum number of the detected face */
	    int m_FasdMaxFace;
	    /** Reliability (detection threshold) */
	    float m_FasdReliability;
	    /** Maximum processing time */
	    int m_FasdProcessTime;
	    /** Search depth */
	    int m_FasdSearchDepth;
	    /** Face detection area */
	    RECT m_DetectArea;
	    /** Sorting order for search result */
	    int m_FasdOrderingPolicy;
	    /** Shrink factor */
	    int m_ShrinkFactor;

	    /** Image conversion factor: Red */
	    int m_iGtR;
	    /** Image conversion factor: Green */
	    int m_iGtG;
	    /** Image conversion factor: Blue */
	    int m_iGtB;

	    /** Raw data for face verification */
	    BYTE *m_RawImage;

	    /** Image width */
	    int m_width;
	    /** Image height */
	    int m_height;

	    /** The face position information used in FASL */
	    void *m_fpos;
	    /** The face position info array used in FASL */
	    void *m_fposes;

	    /** Pan angle of the detected face */
	    float m_FacePan;
	    /** Tilt angle of the detected face */
	    float m_FaceTilt;
	    /** Frontal face score */
	    float m_FrontalFaceScore;
	    /** The speciousness of the frontal face score */
	    float m_FacialPosScore;
	    /** Frontal face judgment flag */
	    bool m_FrontalFaceFlag;

	    int m_Use2ptEyesFlg;
	    int* m_DetectState;
	    /** face infomation */
	    NEO_FACEINFO m_FaceInfo;
	};


	/**
	 * The class related to the face feature management.
	 * Proceeds and monitors the feature data by receiving the face image object.
	 *
	 */
	class NEOFACEM_API CFaceFeature
	{
	    friend class CVerifier;
	    friend class CSerializeData;

	public:
	    static void FreeSerializeData(void *pData);
	    static void* GetFeatureData(void *pSerializeData, int &FeatureType);
	    int Serialize(void **pData, long *pSize, unsigned long SerializeType=NFP_SERIALIZETYPE_COMPOUND);
	    int CreateFeature(const BYTE *raw, int width, int height, const POINT &leye, const POINT &reye);
	    int CreateFeature(const BYTE *raw, int width, int height, const NEO_FACEINFO& faceInfo);
	    bool IsConverted();
	    int GetFeatureType();
	    int SetParamFeatureType(int iType);
	    int SetFeature(CFaceInfo *pFaceInfo);

	    CFaceFeature();
	    virtual ~CFaceFeature();

	private:
	    void* GetCompoundPointer();
	    int GetCompoundDim();
	    int _CreateFeature(const BYTE *raw, int width, int height, const POINT &leye,const POINT &reye,
		                void* pos, int f4flg = NFP_FLG_OFF);
	    static void GetPos13pt(int *pos13pt, void *pos);
	    int m_BufType;

	    /** Serialized type */
	    unsigned long m_SerializeType;

	    void* m_pFeatureData;
	    int m_featureSize;

	    /** Dimension of the simplex feature data */
	    int m_SimplexDim;
	    /** Dimension of the compound feature data  */
	    int m_CompoundDim;
	};


	 /**
	  * The abstract class related to the feature data verification.
	  * Returns the matching score by comparing each CFaceFeature.
	  */

	class NEOFACEM_API CVerifier
	{
	public:
	    int Verify(CFaceFeature *query, CFaceFeature *target, float *score);
	    int Verify(CFaceFeature *query, void *target, float *score);
	    int Verify(void *query, CFaceFeature *target, float *score);
	    int Verify(void *query, void *target, float *score);

	    CVerifier();
	    virtual ~CVerifier();

	private:
	};
}

#endif
