//
//  NeoFaceAccessor.h
//  NEC-DID-SDK
//
//  Copyright © 2022 NEC. All rights reserved.
//

#ifndef NeoFaceAccessor_h
#define NeoFaceAccessor_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

extern int const NFGLBR_SUCCESS;
extern int const NFGLBR_FAILED;
extern int const NFGLBR_CANNOT_FIND_FACE;
extern int const NFGLBR_FORMAT_ERROR;
extern int const NFGLBR_ILLEGAL_TYPE;
extern int const NFGLBR_ILLEGAL_DIM;
extern int const NFGLBR_ARGUMENT_ERROR;
extern int const NFGLBR_STATUS_ERROR;
extern int const NFGLBR_NOT_INITIALIZE_ERROR;
extern int const NFGLBR_PARAM_ERROR;
extern int const NFGLBR_ESTIMATEPOSE_ERROR;
extern int const NFGLBR_CORE_ERROR;
extern int const NFGLBR_MEMORY_ERROR;
extern int const NFGLBR_DICTIONARY_ERROR;
extern int const NFGLBR_LICENSE_ERROR;

extern int const NFGLBR_LIVENESS_PH1_JUDGING;
extern int const NFGLBR_LIVENESS_PH2_JUDGING;
extern int const NFGLBR_LIVENESS_WARN_TOO_CLOSE;
extern int const NFGLBR_LIVENESS_WARN_TOO_FAR;
extern int const NFGLBR_LIVENESS_WARN_TOO_RIGHT;
extern int const NFGLBR_LIVENESS_WARN_TOO_LEFT;
extern int const NFGLBR_LIVENESS_WARN_TOO_LOW;
extern int const NFGLBR_LIVENESS_WARN_TOO_HIGH;
extern int const NFGLBR_LIVENESS_WARN_MOVING;

extern int const NFGLBR_ALGORITHM_L26;
extern int const NFGLBR_ALGORITHM_LH1;

@interface NeoFaceGLBridge: NSObject

- (int)configureWithDictFolder: (const char *)dictFolder licensePath: (const char *)licensePath needVerify: (bool) needVerify;
- (int)configureWithMagicNumber: (int)magicNumber;
- (int)configureWithTotp: (int)totp;
- (const char **)getVersion;
- (const char *)getKey;
- (int)resetLiveness;
- (bool)canRunNeoFace;
- (void)prepareNFGL;
- (int)terminate;
- (void)releaseObjects;

///** CFaceInfo */
- (int)faceInfoSetParamEyesMaxWidth: (int)width;
- (int)faceInfoSetParamEyesMinWidth: (int)width;
- (int)faceInfoSetParamMaxFace: (int)maxFace;
- (int)faceInfoSetParamReliability: (float)reliability;
- (int)faceInfoSetParamFastDetection: (int)mode;
- (int)faceInfoSetParamFastDetectionCycle: (int)cycle;
- (int)faceInfoSetParamRetry: (int)mode;
- (int)faceInfoSetImage: (unsigned char *)image width: (int)width height: (int)height;
- (int)faceInfoFindFace: (unsigned char *)image width: (int)width height: (int)height;
- (int)faceInfoGetFaceMax;
- (float)faceInfoGetFaceScore;
- (int)faceInfoSetFaceIndex: (int)index;
- (int)faceInfoGetFaceIndex;
- (CGPoint)faceInfoGetLeftEye;
- (CGPoint)faceInfoGetLeftEye: (int)index;
- (CGPoint)faceInfoGetRightEye;
- (CGPoint)faceInfoGetRightEye: (int)index;
- (CGRect)faceInfoGetFace;
- (CGRect)faceInfoGetFace: (int)index;
- (CGRect)faceInfoGetHead;
- (CGRect)faceInfoGetHead: (int)index;
- (int)faceInfoAddFace: (CGPoint) right left: (CGPoint) left;
///** CFaceInfo */

///** CFaceAttribute */
- (int)faceAttributeResetLiveness;
- (float)faceAttributeGetFaceQualityScore;
- (int)faceAttributeGetFacePan;
- (int)faceAttributeGetFaceRoll;
- (int)faceAttributeGetFaceTilt;
- (float)faceAttributeGetGazeHorizontal;
- (float)faceAttributeGetGazeVertical;
- (float)faceAttributeGetSmileScore;
- (float)faceAttributeGetLeftEyeClosingScore;
- (float)faceAttributeGetRightEyeClosingScore;
- (float)faceAttributeGetGlassesConfidence;
- (float)faceAttributeGetSunglassesConfidence;
- (float)faceAttributeGetMaskConfidence;
- (float)faceAttributeGetFaceSharpnessScore;
- (float)faceAttributeGetFrontalFaceScore;
- (float)faceAttributeGetFaceLivenessScore;
- (int)faceAttributeGetFaceLivenessStatus;
- (int)faceAttributeGetFaceLivenessResult;
- (int)faceAttributeSetParameter: (NSString *) algorithm param_name: (NSString *) name param_value:(NSString *) value;
- (int)faceAttributeSetParamLivenessAlgorithm:(int)algorithm;
///** CFaceAttribute */
//
///** CFaceFeature */
- (int)queryFaceFeatureFromBytesArray: (unsigned char *)faceFeature;
- (int)targetFaceFeatureFromBytesArray: (unsigned char *)faceFeature;
- (int)faceFeatureSetParamFeatureCompatibility: (int)mode;
- (int)faceFeatureCalcFeature;
- (int)faceFeatureSerialize;
- (unsigned char *)faceFeatureGetSerializedData;
- (long)faceFeatureGetSerializedDataSize;
- (void)faceFeatureFreeSerializeData;
/** CFaceFeature */

/** CVerify */
- (int)newVerifyInstance;
- (int)verifyInstanceVerify: (unsigned char *) query target: (unsigned char *) target score: (float *) score;
///** CVerify */

@end
#endif /* NeoFaceAccessor_h */
