//
//  MultiCameraPreview.h
//  camerawesome
//
//  Created by Dimitri Dessus on 28/03/2023.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "MultiCameraPreview.h"
#import "CameraPreviewTexture.h"
#import "CameraQualities.h"
#import "CameraDeviceInfo.h"
#import "CameraPictureController.h"
#import "MotionController.h"
#import "ImageStreamController.h"
#import "PhysicalButtonController.h"
#import "AspectRatio.h"
#import "LocationController.h"
#import "CameraFlash.h"
#import "CaptureModes.h"

NS_ASSUME_NONNULL_BEGIN

@interface MultiCameraPreview : NSObject<AVCaptureVideoDataOutputSampleBufferDelegate,
AVCaptureAudioDataOutputSampleBufferDelegate>

@property (nonatomic, strong) AVCaptureMultiCamSession  *cameraSession;

@property (nonatomic, strong) NSArray<Sensor *> *sensors;
@property (nonatomic, strong) NSMutableArray<CameraDeviceInfo *> *devices;
@property (nonatomic, strong) dispatch_queue_t dataOutputQueue;
@property(readonly, nonatomic) AVCapturePhotoOutput *capturePhotoOutput;
@property(readonly, nonatomic) AspectRatio aspectRatio;
@property(readonly, nonatomic) LocationController *locationController;
@property(readonly, nonatomic) MotionController *motionController;
@property(readonly, nonatomic) PhysicalButtonController *physicalButtonController;
@property(readonly, nonatomic) bool saveGPSLocation;
@property(readonly, nonatomic) bool mirrorFrontCamera;
@property(nonatomic, nonatomic) NSMutableArray<CameraPreviewTexture *> *textures;
@property(nonatomic, copy) void (^onPreviewFrameAvailable)(NSNumber * _Nullable);

- (instancetype)initWithSensors:(NSArray<Sensor *> *)sensors mirrorFrontCamera:(BOOL)mirrorFrontCamera
           enablePhysicalButton:(BOOL)enablePhysicalButton
                aspectRatioMode:(AspectRatio)aspectRatioMode
                    captureMode:(CaptureModes)captureMode;
- (void)configSession:(NSArray<Sensor *> *)sensors;
- (void)start;
- (void)stop;
- (void)setPreviewSize:(CGSize)previewSize error:(FlutterError * _Nullable __autoreleasing * _Nonnull)error;
- (CGSize)getEffectivPreviewSize;
- (void)takePictureAtPath:(NSString *)path completion:(nonnull void (^)(NSNumber * _Nullable, FlutterError * _Nullable))completion;
- (void)dispose;
- (void)setAspectRatio:(AspectRatio)ratio;
- (void)setExifPreferencesGPSLocation:(bool)gpsLocation completion:(void(^)(NSNumber *_Nullable, FlutterError *_Nullable))completion;
- (void)setOrientationEventSink:(FlutterEventSink)orientationEventSink;
- (void)setPhysicalButtonEventSink:(FlutterEventSink)physicalButtonEventSink;

@end

NS_ASSUME_NONNULL_END
