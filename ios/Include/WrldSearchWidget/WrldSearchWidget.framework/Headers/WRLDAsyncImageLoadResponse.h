#pragma once

#include <UIKit/UIKit.h>

typedef void (^AssignmentCallback) (UIImage*);
typedef void (^CancelAssignmentCallback) (void);

@interface WRLDAsyncImageLoadResponse : NSObject
- (instancetype) initWithAssignmentCallback:(AssignmentCallback) assignImage;
- (instancetype) initWithAssignmentCallback:(AssignmentCallback) assignImage cancellationCallback: (CancelAssignmentCallback) cancelAssignment;
- (void) assignImage: (UIImage *) image;
- (void) cancel;
@end
