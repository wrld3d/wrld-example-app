#pragma once

#include <UIKit/UIKit.h>

typedef void (^AssignmentCallback) (UIImage*);
typedef void (^CancelAssignmentCallback) (void);

/*!
 Used to assign image resources from asynchronous requests.
 */
@interface WRLDAsyncImageLoadResponse : NSObject


/*!
 Init the load response with callbacks to invoke when the image is loaded.
 @param assignImage The AssignmentCallback that takes a UIImage param to be called when the asyncronous load completes.
 */
- (instancetype) initWithAssignmentCallback:(AssignmentCallback) assignImage;

/*!
 Init the load response with callbacks to invoke when the image is loaded or when the assignment is cancelled.
 @param assignImage The AssignmentCallback that takes a UIImage param to be called when the asyncronous load completes.
 @param cancelAssignment The callback to be invoked when the assignment is cancelled.
 */
- (instancetype) initWithAssignmentCallback:(AssignmentCallback) assignImage cancellationCallback: (CancelAssignmentCallback) cancelAssignment;


/*!
 Calls the assignImage callback with the loaded image.
 */
- (void) assignImage: (UIImage *) image;


/*!
 Cancels the assignment request and invokes the cancellationCallback.
 */
- (void) cancel;
@end
