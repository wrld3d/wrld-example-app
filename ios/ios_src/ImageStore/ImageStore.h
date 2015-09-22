// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import "ImageFetchOperation.h"
#include <string>
#include <map>
#include <vector>

typedef void(^ImageLoadedCallback)(UIImage*);

@interface ImageStore : NSObject <ImageFetchOperationDelegate>

- (id) init;

- (void) loadImage:(std::string)urlString :(UIImageView*)targetView :(ImageLoadedCallback)callback;

- (void) loadImage:(std::string)urlString :(UIImageView*)targetView :(ImageLoadedCallback)callback :(float)cropSize;

- (void) onImageFetchComplete:(NSURL*)url :(UIImage*)image;

- (void) releaseImageForView:(UIImageView*)view;

@end