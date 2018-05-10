#pragma once

#include <UIKit/UIKit.h>
#include "WRLDAsyncImageLoadResponse.h"

/*!
 Resolves NSString URLS to UIImages.
 */
@interface WRLDUrlImageLoader : NSObject

/*!
 Attempts to generate a UIImage from a url.
 @param url URL of the image resources.
 @param assignCallback method to invoke if the URL successfully resolves to a UIImage.
 @param cancelCallback method to invoke if the URL fails to resolve to a UIImage.
 @return WRLDAsyncImageLoadResponse An async response object that allows the caller of the method to cancel the request.
 */
- (WRLDAsyncImageLoadResponse *) assignImageFromUrlString:(NSString*) url
                                       assignmentCallback: (AssignmentCallback) assignCallback
                                     cancellationCallback: (CancelAssignmentCallback) cancelCallback;

/*!
 Attempts to generate a UIImage from a url.
 @param url URL of the image resources.
 @param assignCallback method to invoke if the URL successfully resolves to a UIImage.
 @return WRLDAsyncImageLoadResponse An async response object that allows the caller of the method to cancel the request.
 */
- (WRLDAsyncImageLoadResponse *) assignImageFromUrl:(NSURL*) url
                                 assignmentCallback: (AssignmentCallback) assignCallback
                               cancellationCallback: (CancelAssignmentCallback) cancelCallback;

@end
