//
//  MyGLView.h
//  OpenGLESShader
//
//  Created by FutureBoy on 10/27/15.
//  Copyright © 2015 Cyllenge. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KxMovieViewController.h"
#import <kazmath.h>

@class KxVideoFrame;
@class GLRenderLoop;

//void convertTexCoordWithLUT(P4C4T2f* vertices, GLsizei vertexCount);

@protocol GLRenderLoopDelegate <NSObject>

@required

- (void) glRenderLoopSetupGLRenderbuffer:(GLRenderLoop*)renderLoop;

@optional

- (void) glRenderLoop:(GLRenderLoop*)renderLoop frameTimeTicked:(int)millseconds;

@end


@interface GLRenderLoop : NSObject

+ (void) stopCurrentRenderLoop;

- (void) stopOtherRenderLoopIfAny;

- (instancetype) initWithDelegate:(id<GLRenderLoopDelegate>)delegate lutPath:(NSString*)lutPath lutSrcSizeL:(CGSize)lutSrcSizeL lutSrcSizeR:(CGSize)lutSrcSizeR inputFrameSize:(CGSize)inputFrameSize outputVideoBaseName:(NSString*)outputVideoBaseName encoderQualityLevel:(QualityLevel)qualityLevel forCapturing:(BOOL)forCapturing;

+ (NSString*) outputVideoBaseName:(NSString*)originalVideoName qualityLevel:(QualityLevel)qualityLevel;

- (void) invalidateRenderbuffer;

- (void) onGyroQuaternionChanged:(CMAttitude*)attitude orientation:(UIInterfaceOrientation)orientation startOrientation:(UIInterfaceOrientation)startOrientation;
- (void) onPanRecognized:(UIPanGestureRecognizer*)panRecognizer;
- (void) onPinchRecognized:(UIPinchGestureRecognizer*)pinchRecognizer;
- (void) onDoubleTapRecognized:(UITapGestureRecognizer*)doubleTapRecognizer;

- (void) setFOVRange:(int)initFOV maxFOV:(int)maxFOV minFOV:(int)minFOV;

- (void) setVideoRecorder:(NSString*)outputVideoBaseName qualityLevel:(QualityLevel)qualityLevel forCapturing:(BOOL)forCapturing;

- (void) setLUTPath:(NSString*)lutPath lutSrcSizeL:(CGSize)lutSrcSizeL lutSrcSizeR:(CGSize)lutSrcSizeR;

- (void) releaseGL;

- (void) requestRedraw;

- (void) draw;

- (void) draw: (UIImage *) image;
- (void) drawJPEG:(NSString*)filePath;
- (void) render: (KxVideoFrame *) frame;
- (void) drawStichedImageWithLeftImage:(UIImage*)leftImage rightImage:(UIImage*)rightImage;
- (void) renderImmediately: (KxVideoFrame *) frame;

- (void) setGyroMatrix:(float*)matrix rank:(int)rank;

- (void) pauseRendering;
- (void) resumeRendering;
- (void) stopRendering;
- (void) startRendering;
- (void) setShareMode;

- (void) stopEncoding;
- (void) setMadVData:(NSData*) MadVData;

- (void) takeSnapShot:(NSString*)destPath completion:(dispatch_block_t)completion;

@property (nonatomic, weak) id<GLRenderLoopDelegate> delegate;

@property (nonatomic, assign) int panoramaMode;

@property (nonatomic, assign) int filterID;

@property (nonatomic, assign) BOOL isGlassMode;

@property (nonatomic, assign) BOOL isYUVColorSpace;

//@property (nonatomic, assign) BOOL inCapturing;

@property (nonatomic, assign) QualityLevel encoderQualityLevel;

@property(nonatomic,strong) void(^encodingDoneBlock)(NSString*, NSError*);
@property(nonatomic,strong) void(^encodingFrameBlock)(float);
@property(nonatomic,strong) NSError* encodingError;

@property (nonatomic, strong) NSData* madVdata;
@property (nonatomic, assign) int64_t moovBoxSizeOffset;
@property (nonatomic, assign) int64_t videoTrakBoxSizeOffset;
@property (nonatomic, assign) int64_t videoTrakBoxEndOffset;
@end


@interface MyGLView : UIView

- (instancetype) initWithFrame:(CGRect)frame lutPath:(NSString*)lutPath lutSrcSizeL:(CGSize)lutSrcSizeL lutSrcSizeR:(CGSize)lutSrcSizeR outputVideoBaseName:(NSString*)outputVideoBaseName encoderQualityLevel:(QualityLevel)qualityLevel forCapturing:(BOOL)forCapturing;

@property (nonatomic, assign) int panoramaMode;

@property (nonatomic, assign) int filterID;

@property (nonatomic, assign) BOOL isGlassMode;

@property (nonatomic, assign) BOOL isYUVColorSpace;

- (void) willAppear;
- (void) willDisappear;

@property (nonatomic, readonly, strong) GLRenderLoop* glRenderLoop;

@property (nonatomic, assign) UIInterfaceOrientation interfaceOrientation;

- (void) resetViewPosition;

// eularDegrees.xyz = {yaw,pitch,bank}
- (void) lookAt:(kmVec3)eularDegrees;

- (void) startMotionManager;
- (void) stopMotionManager;

- (void) takeSnapShot:(NSString*)destPath completion:(dispatch_block_t)completion;

@end
