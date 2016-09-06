// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

@protocol ImageFetchOperationDelegate <NSObject>

- (void) onImageFetchComplete:(NSURL*)url :(UIImage*)image;

@end

@interface ImageFetchOperation : NSOperation

- (id)initWithUrl:(NSURL*)url;

- (id)initWithParams:(NSURL*)url :(float)cropSize;

@property (nonatomic, assign) id <ImageFetchOperationDelegate> delegate;

@end

