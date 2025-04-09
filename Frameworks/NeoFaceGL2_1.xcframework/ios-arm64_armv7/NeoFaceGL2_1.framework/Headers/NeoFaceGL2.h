/**********************************************************************/
/*                                                                    */
/*      Copyright (C) NEC Corporation 2016                            */
/*                                                                    */
/*      NEC CONFIDENTIAL AND PROPRIETARY                              */
/*      All rights reserved by NEC Corporation.                       */
/*      This program must be used solely for the purpose for which    */
/*      it was furnished by NEC Corporation.   No part of this        */
/*      program may be reproduced or disclosed to others, in any      */
/*      form, without the prior written permission of NEC             */
/*      Corporation.   Use of copyright notice dose not evidence      */
/*      publication of the program.                                   */
/*                                                                    */
/**********************************************************************/

/**
* @file    NeoFaceGL2.h
* @brief   VIDEO Facial Recognition API
*
* @version 1.0
* @author  NEC Confidential
* @author  Copyright(C) NEC Corporation 2016. All rights reserved.
*/
#ifndef NEOFACEG_NEOFACEL2_H
#define NEOFACEG_NEOFACEL2_H

#include <sstream>
#include <string>
#ifdef _WIN32
# include <Windows.h>
#else
# include <semaphore.h>
#endif // _WIN32

#include <vector>

#undef DLLEXPORT
#ifdef _WIN32
# define __CDECL cdecl
# define DLLEXPORT __declspec (dllexport)
#else // for linux gcc
# define __CDECL
# define DLLEXPORT
# define LONG    int
# define DWORD   unsigned int
# define BYTE    unsigned char
# define WORD    unsigned short
#endif // _WIN32

#ifdef _WIN32
#pragma warning(disable:4251)
#endif

namespace NeoFaceGL2
{
// Error code
#define NFGL_SUCCESS               (     1)  //!< Success
#define NFGL_FAILED                (     0)  //!< Failed
#define NFGL_CANNOT_FIND_FACE      (    99)  //!< Failed in finding a face
#define NFGL_FORMAT_ERROR          (-10101)  //!< Format error
#define NFGL_ILLEGAL_TYPE          (-10102)  //!< Illegal feature type
#define NFGL_ILLEGAL_DIM           (-10103)  //!< Illegal feature value data
#define NFGL_ARGUMENT_ERROR        (-10202)  //!< Illegal argument
#define NFGL_STATUS_ERROR          (-10203)  //!< Wrong status
#define NFGL_NOT_INITIALIZE_ERROR  (-10301)  //!< Initialization error
#define NFGL_PARAM_ERROR           (-10307)  //!< Internal parameter configuration error
#define NFGL_ESTIMATEPOSE_ERROR    (-10308)  //!< Front face judgement error
#define NFGL_CORE_ERROR            (-10399)  //!< Internal process error
#define NFGL_MEMORY_ERROR          (-90000)  //!< Memory allocation error
#define NFGL_DICTIONARY_ERROR      (-90001)  //!< Dictinary error
#define NFGL_LICENSE_ERROR         (-90002)  //!< License error

#define NFGL_LIVENESS_PH1_JUDGING       (  1000)  //!< Liveness phase1 Judging
#define NFGL_LIVENESS_PH1_2_JUDGING     (  1001)  //!< Liveness phase1-2 Judging
#define NFGL_LIVENESS_PH2_JUDGING       (  1100)  //!< Liveness phase2 Judging
#define NFGL_LIVENESS_WARN_TOO_CLOSE    (  1101)  //!< Liveness warning (Too close)
#define NFGL_LIVENESS_WARN_TOO_FAR      (  1102)  //!< Liveness warning (Too far)
#define NFGL_LIVENESS_WARN_TOO_RIGHT    (  1103)  //!< Liveness warning (Too right)
#define NFGL_LIVENESS_WARN_TOO_LEFT     (  1104)  //!< Liveness warning (Too left)
#define NFGL_LIVENESS_WARN_TOO_LOW      (  1105)  //!< Liveness warning (Too low)
#define NFGL_LIVENESS_WARN_TOO_HIGH     (  1106)  //!< Liveness warning (Too high)
#define NFGL_LIVENESS_WARN_MOVING       (  1107)  //!< Liveness warning (Too moving face)

/** @enum  NFGL_LIB_CODE
*   @brief Library code
*/
enum NFGL_LIB_CODE
{
    NFGL_LIB_DETECTION         = 0x0001,     //!< Detection class
    NFGL_LIB_TRACKING          = 0x0002,     //!< Tracking class
    NFGL_LIB_ATTRIBUTE         = 0x0004,     //!< Attribute judgement class
    NFGL_LIB_FEATURE           = 0x0008,     //!< Feature value generation class

    NFGL_LIB_VERIFY            = 0x0010,     //!< 1to1 matching class
    NFGL_LIB_IDENTIFY          = 0x0020,     //!< 1toN matching class
};

/** @enum  NFGL_CORRECT
*   @brief Correct mode
*/
enum NFGL_CORRECT
{
    NFGL_CORRECT_MODE_NONE   = 1,        //!< No correction
    NFGL_CORRECT_MODE_QUERY  = 2,        //!< Query correction
    NFGL_CORRECT_MODE_NONE_ORIGINAL = 3, //!< No correction(original)
    NFGL_CORRECT_MODE_QUERY_ORIGINAL = 4 //!< Query correction(original)
};

/** @enum  NFGL_SCORE
*   @brief Score scaling type
*/
enum NFGL_SCORE
{
    NFGL_SCORE_COMPATIBLE    = 1,        //!< compatible type
    NFGL_SCORE_ORIGINAL      = 2         //!< original type
};

/** @enum  NFGL_ALGORITHM
*   @brief Algorithm
*/
enum NFGL_ALGORITHM
{
    // CFaceAttribute Face attribute algorithm
    NFGL_ALGORITHM_L02 = 2,              //!< L02
    NFGL_ALGORITHM_L03 = 3,              //!< L03
    NFGL_ALGORITHM_L04 = 4,              //!< L04
    NFGL_ALGORITHM_L05 = 5,              //!< L05
    NFGL_ALGORITHM_L06 = 6,              //!< L06
    NFGL_ALGORITHM_L11 = 11,             //!< L11
    NFGL_ALGORITHM_L03L04 = 34,          //!< L03/L04
    NFGL_ALGORITHM_L03L06 = 36,          //!< L03/L06
    NFGL_ALGORITHM_L04L05 = 45,          //!< L04/L05
    NFGL_ALGORITHM_L03L04L06 = 346,      //!< L03/L04/L06
    NFGL_ALGORITHM_L04L05L06 = 456,      //!< L04/L05/L06
    NFGL_ALGORITHM_L26 = 26,             //!< L26
    NFGL_ALGORITHM_LH1 = 2611,           //!< LH1
};

/** @enum  NFGL_DETECTION_FAST_DETECT
*   @brief Partial detection mode
*/
enum NFGL_DETECTION_FAST_DETECT
{
    NFGL_DETECTION_FAST_DETECT_OFF = 1,     //!< Partial detect OFF
    NFGL_DETECTION_FAST_DETECT_ON = 2       //!< Partial detect ON
};

/** @enum  NFGL_DETECTION_RETRY
*   @brief Retry mode
*/
enum NFGL_DETECTION_RETRY
{
    NFGL_DETECTION_RETRY_OFF = 1,           //!< Retry OFF
    NFGL_DETECTION_RETRY_ON = 2             //!< Retry ON
};

/** @enum  NFGL_FEATURE_COMPATIBILITY
*   @brief Feature Compatibility Type
*/
enum NFGL_FEATURE_COMPATIBILITY
{
    NFGL_FEATURE_COMPATIBILITY_OFF = 1,     //!< Compatibility OFF
    NFGL_FEATURE_COMPATIBILITY_ON = 2       //!< Compatibility ON
};

/** @enum  NFGL_FEATURE_CHECK
*   @brief Check feature mode
*/
enum NFGL_FEATURE_CHECK
{
    NFGL_CHECK_FEATURE_OFF = 1,     //!< CheckFeature OFF
    NFGL_CHECK_FEATURE_ON = 2       //!< CheckFeature ON
};


#ifdef _WIN32
#else

#pragma pack(1)

#ifndef TAG_BITMAPINFOHEADER_NFGL2
/** @struct tagBITMAPINFOHEADER
*   @brief  Bitmap header info
*
*/
typedef struct tagBITMAPINFOHEADER
{
    DWORD           biSize;             //!< Header size
    LONG            biWidth;            //!< Image width, positive value, from left to right of the image.
    LONG            biHeight;           //!< Image height, positive value, from top to buttom of the image.
    WORD            biPlanes;           //!< Number of planes
    WORD            biBitCount;         //!< Bit count
    DWORD           biCompression;      //!< Compression type
    DWORD           biSizeImage;        //!< Size of image data part
    LONG            biXPelsPerMeter;    //!< Horizontal resolution
    LONG            biYPelsPerMeter;    //!< Vertical resolution
    DWORD           biClrUsed;          //!< Number of used palette
    DWORD           biClrImportant;     //!< Index of important palette
} BITMAPINFOHEADER;
#define TAG_BITMAPINFOHEADER_NFGL2
#endif // TAG_BITMAPINFOHEADER

#ifndef TAG_RGBQUAD_NFGL2
/** @struct tagRGBQUAD
*   @brief  Color pallet information
*/
typedef struct tagRGBQUAD
{
    BYTE            rgbBlue;            //!< Color palette (blue)
    BYTE            rgbGreen;           //!< Color palette (green)
    BYTE            rgbRed;             //!< Color palette (red)
    BYTE            rgbReserved;        //!< Reserved area
} RGBQUAD;
#define TAG_RGBQUAD_NFGL2
#endif // TAG_RGBQUAD

#ifndef TAG_BITMAPINFO_NFGL2
/** @struct tagBITMAPINFO
*   @brief  Bitmap info
*/
typedef struct tagBITMAPINFO
{
    BITMAPINFOHEADER    bmiHeader;      //!< Header of BITMAPINFOHEADER
    RGBQUAD             bmiColors[1];   //!< Color palette
} BITMAPINFO;
#define TAG_BITMAPINFO_NFGL2
#endif // TAG_BITMAPINFO

#pragma pack()

/** @struct tagPOINT
*   @brief  Point info
*/
typedef struct tagPOINT
{
    LONG            x;                  //!< specify a x-coordinate of the point
    LONG            y;                  //!< specify a y-coordinate of the point
} POINT;

/** @struct tagRECT
*   @brief  Coordinate info of the upper-left corner and buttom-right corner of a  rectangle
*/
typedef struct tagRECT
{
    LONG            left;               //!< x-coordinate of upper-left corner of a rectangle
    LONG            top;                //!< y-coordinate of upper-left corner of a rectangle
    LONG            right;              //!< x-coordinate of bottom-right corner of a rectangle
    LONG            bottom;             //!< y-coordinate of bottom-right corner of a rectangle
} RECT;

#endif // _WIN32

/** @struct tagPOINTF
*   @brief  float Point info
*/
typedef struct tagPOINTF
{
    float           x;                  //!< specify a x-coordinate of the point
    float           y;                  //!< specify a y-coordinate of the point
} POINTF;

#ifdef _WIN32
#define NFGL_INIT_SEMAPHORE_NAME    "NFGL_INIT_SEMAPHORE"
#define NFGL_SEMAPHORE_CNT          1
#else
extern sem_t initSem;
#endif

#if defined(__ANDROID__)
__attribute__ ((visibility("default"))) DLLEXPORT int Initialize(int iLibrary, const char* dicFolder = NULL, const char* licensePath = NULL, const char* licensePath2 = NULL, const char* work1 = NULL, const char* work2 = NULL);
#elif defined(__APPLE__)
__attribute__ ((visibility("default"))) DLLEXPORT int Initialize(int iLibrary, const char* dicFolder = NULL, const char* licenseFolder = NULL);
#else
__attribute__ ((visibility("default"))) DLLEXPORT int Initialize(int iLibrary, const char* dicFolder = NULL);
#endif
__attribute__ ((visibility("default"))) DLLEXPORT int Terminate (int iLibrary);

__attribute__ ((visibility("default"))) DLLEXPORT const char** GetVersion();

#if defined(__ANDROID__)
__attribute__ ((visibility("default"))) int CheckTerminalFree(const char *pcLicenseFile);
#endif

/**
* @class CFaceInfo
* @brief Face detecting function class
*/
class CFaceInfoCore;
__attribute__ ((visibility("default"))) class DLLEXPORT CFaceInfo
{
public:
    __attribute__ ((visibility("default"))) CFaceInfo();
    __attribute__ ((visibility("default"))) CFaceInfo(const CFaceInfo &obj);
    __attribute__ ((visibility("default"))) ~CFaceInfo();

    __attribute__ ((visibility("default"))) int  SetParamEyesMaxWidth(int iWidth);
    __attribute__ ((visibility("default"))) int  SetParamEyesMinWidth(int iWidth);
    __attribute__ ((visibility("default"))) int  SetParamMaxFace(int iMax);
    __attribute__ ((visibility("default"))) int  SetParamReliability(float iRel);
    __attribute__ ((visibility("default"))) int  SetParamFastDetection(int iMode);
    __attribute__ ((visibility("default"))) int  SetParamFastDetectionCycle(int iCycle);
    __attribute__ ((visibility("default"))) int  SetParamRetry(int iMode);

    __attribute__ ((visibility("default"))) int  FindFace(const BITMAPINFO &ImageInfo, const void *ImageBody);
    __attribute__ ((visibility("default"))) int  FindFace(const BYTE *iImage, int iWidth, int iHeight);
    __attribute__ ((visibility("default"))) int  GetWidth();
    __attribute__ ((visibility("default"))) int  GetHeight();
    __attribute__ ((visibility("default"))) int  GetFaceMax();
    __attribute__ ((visibility("default"))) float GetFaceScore(int iIndex = -1);
    __attribute__ ((visibility("default"))) int  SetFaceIndex(int iIndex);
    __attribute__ ((visibility("default"))) int  GetFaceIndex();
    __attribute__ ((visibility("default"))) POINT GetLeftEye(int iIndex = -1);
    __attribute__ ((visibility("default"))) POINT GetRightEye(int iIndex = -1);
    __attribute__ ((visibility("default"))) int  SetLeftEye(const POINT& point, int iIndex = -1);
    __attribute__ ((visibility("default"))) int  SetRightEye(const POINT& point, int iIndex = -1);
    __attribute__ ((visibility("default"))) RECT GetFace(int iIndex = -1);
    __attribute__ ((visibility("default"))) RECT GetHead(int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceQualityScore(int iIndex = -1);
    __attribute__ ((visibility("default"))) int  SetImage(const BITMAPINFO & ImageInfo, const void * ImageBody);
    __attribute__ ((visibility("default"))) int  SetImage(const BYTE * iImage, int iWidth, int iHeight);

    __attribute__ ((visibility("default"))) int  AddFace(const POINTF & right, const POINTF & left, bool frontal = true, float score = 0.0f);
    __attribute__ ((visibility("default"))) void Init();
    __attribute__ ((visibility("default"))) int  SetParamLog(int target_id, const std::string param_name, const std::string param_value);
    __attribute__ ((visibility("default"))) int  SetParameter(const std::string algorithm, const std::string param_name, const std::string param_value);

private:
    CFaceInfoCore* m_pFaceInfoCore;

    template<typename _T>
    std::string ToString(const _T val)
    {
        std::ostringstream os;
        os << val;

        return os.str();
    };

    friend class CFaceAttribute;
    friend class CFaceFeature;
    friend class CVerify;
    friend class CFaceTracking;
    friend class CCommonSub;
};

/**
* @class CFaceTracking
* @brief Face tracking function class
*/
class CFaceTrackingCore;
__attribute__ ((visibility("default"))) class DLLEXPORT CFaceTracking
{
public:
    __attribute__ ((visibility("default"))) CFaceTracking();
    __attribute__ ((visibility("default"))) CFaceTracking(const CFaceTracking &obj);
    __attribute__ ((visibility("default"))) ~CFaceTracking();

    __attribute__ ((visibility("default"))) void InitPersonID();
    __attribute__ ((visibility("default"))) int  CalcPersonID(CFaceInfo* pFaceInfo);
    __attribute__ ((visibility("default"))) int  GetPersonID(CFaceInfo* pFaceInfo, int iIndex = -1);

    __attribute__ ((visibility("default"))) void Init();
    __attribute__ ((visibility("default"))) int  SetParamLog(int target_id, const std::string param_name, const std::string param_value);
    __attribute__ ((visibility("default"))) int  SetParameter(const std::string algorithm, const std::string param_name, const std::string param_value);


private:
    CFaceTrackingCore* m_pFaceTrackingCore;
};

/**
* @class CFaceAttribute
* @brief Face attribute judging function class
*/
class CFaceAttributeCore;
__attribute__ ((visibility("default"))) class DLLEXPORT CFaceAttribute
{
public:
    __attribute__ ((visibility("default"))) CFaceAttribute();
    __attribute__ ((visibility("default"))) CFaceAttribute(const CFaceAttribute &obj);
    __attribute__ ((visibility("default"))) ~CFaceAttribute();

    __attribute__ ((visibility("default"))) float GetFrontalFaceScore(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFacePan(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceRoll(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceTilt(CFaceInfo* pFaceInfo, int iIndex = -1);

    __attribute__ ((visibility("default"))) float GetLeftEyeClosingScore(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetRightEyeClosingScore(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetSmileScore(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetGlassesConfidence(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetSunglassesConfidence(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetMaskConfidence(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetGazeVertical(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetGazeHorizontal(CFaceInfo* pFaceInfo, int iIndex = -1);

    __attribute__ ((visibility("default"))) int GetFaceLivenessStatus(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) int GetFaceLivenessResult(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceLivenessScore(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetLivenessProgress(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceSharpness(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetJpegQualityScore(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceQualityScore(CFaceInfo* pFaceInfo, int iIndex = -1);

    __attribute__ ((visibility("default"))) int SetParamCameraParameter(POINT focus, POINT center);
    __attribute__ ((visibility("default"))) int SetParamLivenessAlgorithm(int iAlgorithm);
    __attribute__ ((visibility("default"))) int ResetLiveness();
    __attribute__ ((visibility("default"))) int SetParamLivenessCycle(int intiCycle);

    __attribute__ ((visibility("default"))) int SetParamLog(int target_id, const std::string param_name, const std::string param_value);
    __attribute__ ((visibility("default"))) int SetParameter(const std::string algorithm, const std::string param_name, const std::string param_value);

    __attribute__ ((visibility("default"))) float GetFaceAspectRatio(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceBlurriness(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetFaceBrightness(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) float GetBackgroundBrightness(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) bool IsFaceDistorted(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) int SetParamMinFaceAspectRatio(float fRatio);
    __attribute__ ((visibility("default"))) int SetParamMaxFaceAspectRatio(float fRatio);
    __attribute__ ((visibility("default"))) bool IsFaceBlurred(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) int SetParamFaceBlurriness(float fBlur);
    __attribute__ ((visibility("default"))) bool IsFaceBright(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) int SetParamFaceBrightness(float fBright);
    __attribute__ ((visibility("default"))) bool IsImageBrightnessDifferent(CFaceInfo *pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) int SetParamBackgroundBrightness(float fBright);

private:
    CFaceAttributeCore* m_pFaceAttributeCore;

    template<typename _T>
    std::string ToString(const _T val)
    {
        std::ostringstream os;
        os << val;

        return os.str();
    };
};

/**
* @class CFaceFeature
* @brief Feature value generating function class
*/
class CFaceFeatureCore;
__attribute__ ((visibility("default"))) class DLLEXPORT CFaceFeature
{
public:
    __attribute__ ((visibility("default"))) CFaceFeature();
    __attribute__ ((visibility("default"))) CFaceFeature(const CFaceFeature &);
    __attribute__ ((visibility("default"))) ~CFaceFeature();

    __attribute__ ((visibility("default"))) int  CalcFeature(CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) int  Serialize(unsigned char** feature, long *size, CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) static void FreeSerializeData(unsigned char* feature);
    __attribute__ ((visibility("default"))) int ConvertFeature(unsigned char *srcFeat, unsigned char **dstFeat, long *destFeatSize);
    __attribute__ ((visibility("default"))) static void FreeConvertedFeature(unsigned char * feature);
    __attribute__ ((visibility("default"))) int CheckFeature(unsigned char * feature);

    __attribute__ ((visibility("default"))) int  GetAlignment(float** alignment, int* size, CFaceInfo* pFaceInfo, int iIndex = -1);
    __attribute__ ((visibility("default"))) void FreeAlignment(float* alignment);
    __attribute__ ((visibility("default"))) void Init();
    __attribute__ ((visibility("default"))) int  SetParamFeatureCompatibility(int iMode);

    __attribute__ ((visibility("default"))) int  SetParamLog(int target_id, const std::string param_name, const std::string param_value);

private:
    CFaceFeatureCore* m_pFaceFeatureCore;
};

/**
* @class CVerify
* @brief 1to1 matching function class
*/
class CVerifyCore;
__attribute__ ((visibility("default"))) class DLLEXPORT CVerify
{
public:
    __attribute__ ((visibility("default"))) CVerify();
    __attribute__ ((visibility("default"))) CVerify(const CVerify &);
    __attribute__ ((visibility("default"))) ~CVerify();

    __attribute__ ((visibility("default"))) int Verify(unsigned char * query, unsigned char * target, float * score);
    __attribute__ ((visibility("default"))) int Verify(CFaceInfo * query, CFaceInfo * target, float * score, int iQueryIndex = -1, int iTargetIndex = -1);
    __attribute__ ((visibility("default"))) int Verify(unsigned char * query, CFaceInfo * target, float * score, int iTargetIndex = -1);
    __attribute__ ((visibility("default"))) int Verify(CFaceInfo * query, unsigned char * target, float * score, int iQueryIndex = -1);

    __attribute__ ((visibility("default"))) int Verify(const unsigned long long qHandle, const unsigned long long tHandle, float *score);
    __attribute__ ((visibility("default"))) int Verify(unsigned char *query, const unsigned long long tHandle, float *score);
    __attribute__ ((visibility("default"))) int Verify(const unsigned long long qHandle, unsigned char *target, float *score);
    __attribute__ ((visibility("default"))) int Verify(CFaceInfo *query, const unsigned long long tHandle, float *score, const int iQueryIndex = -1);
    __attribute__ ((visibility("default"))) int Verify(const unsigned long long qHandle, CFaceInfo *target, float *score, const int iTargetIndex = -1);

    __attribute__ ((visibility("default"))) int AddFeature(unsigned char *feature, unsigned long long *handle);
    __attribute__ ((visibility("default"))) int DeleteFeature(const unsigned long long handle);
    __attribute__ ((visibility("default"))) void ResetFeature();
    __attribute__ ((visibility("default"))) int SetParamCheckFeature(int iMode);
    __attribute__ ((visibility("default"))) int SetParamScoreType(int iType);
    __attribute__ ((visibility("default"))) int SetParamLog(int target_id, const std::string param_name, const std::string param_value);

private:
    CVerifyCore* m_pVerifyCore;
};

/**
* @class CIdentify
* @brief 1toN matching function class
*/
class CIdentifyCore;
__attribute__ ((visibility("default"))) class DLLEXPORT CIdentify
{
public:
    __attribute__ ((visibility("default"))) CIdentify();
    __attribute__ ((visibility("default"))) CIdentify(const CIdentify &);
    __attribute__ ((visibility("default"))) ~CIdentify();

    __attribute__ ((visibility("default"))) int Init(int numTarget, int numTargetFeat, int maxNumTarget);
    __attribute__ ((visibility("default"))) int SetCorrectMode(int CorectMode);
    __attribute__ ((visibility("default"))) int GetCorrectMode();
    __attribute__ ((visibility("default"))) int ResetTargetFeature();
    __attribute__ ((visibility("default"))) int AddTargetFeature(unsigned char * target, int id);
    __attribute__ ((visibility("default"))) int Identify(unsigned char * query, std::vector<float> ** score, std::vector<long> ** iD);

    __attribute__ ((visibility("default"))) int SetParamCheckFeature(int iMode);
    __attribute__ ((visibility("default"))) int SetParamScoreType(int iType);
    __attribute__ ((visibility("default"))) int SetParamLog(int target_id, const std::string param_name, const std::string param_value);

private:
    CIdentifyCore* m_pIdentifyCore;
};

}

#endif // NEOFACEG_NEOFACEL_H
