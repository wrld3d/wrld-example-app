#pragma once

#include <UIKit/UIKit.h>
#include "WRLDAsyncImageLoadResponse.h"

@interface WRLDUrlImageLoader : NSObject

- (WRLDAsyncImageLoadResponse *) assignImageFromUrlString:(NSString*) urlString
                                       assignmentCallback: (AssignmentCallback) assignCallback
                                     cancellationCallback: (CancelAssignmentCallback) cancelCallback;

- (WRLDAsyncImageLoadResponse *) assignImageFromUrl:(NSURL*) url
                                 assignmentCallback: (AssignmentCallback) assignCallback
                               cancellationCallback: (CancelAssignmentCallback) cancelCallback;

@end
