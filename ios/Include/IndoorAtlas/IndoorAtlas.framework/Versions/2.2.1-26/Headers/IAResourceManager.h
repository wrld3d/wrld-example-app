// IndoorAtlas iOS SDK
// IAResourceManager.h

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <IndoorAtlas/IALocationManager.h>
#import <IndoorAtlas/IAFloorPlan.h>
#define INDOORATLAS_API __attribute__((visibility("default")))

/**
 * IAFetch protocol for controlling fetch requests.
 */
@protocol IAFetchTask <NSObject>

/**
 * Cancel fetch.
 *
 * Running fetch is canceled and the completion block will not be called.
 */
- (void)cancel;

@end

/**
 * IAResourceManager provides interface for downloading original bitmaps from IndoorAtlas services,
 * and protocol for watching floor plan changes during positioning.
 */
INDOORATLAS_API
@interface IAResourceManager : NSObject

/**
 * @name Read-only properties
 */

/**
 * Associated IALocationManager (read-only).
 */
@property (nonatomic, readonly, nullable) IALocationManager *locationManager;

/**
 * @name Accessing the Delegate
 */

/**
 * Returns new IAResourceManager associated with IALocationManager.
 *
 * @param locationManager Associated IALocationManager.
 *
 * @return IAResourceManager instance.
 */
+ (nullable IAResourceManager*)resourceManagerWithLocationManager:(nullable IALocationManager*)locationManager;

/**
 * Fetch floor plan metadata for floor plan id.
 *
 * @param floorPlanId Identifier of floor plan to fetch from server.
 * @param completionBlock A block to be called when floor plan fetch is completed.
 *
 *     - *floorplan*: A object representing fetched floor plan. If an error occured, this parameter is nil.
 *     - *error*: If an error occured, this object describes the error. If the operation completed successfully, this value is nil.
 *
 * @return IAFetchTask instance for the request.
 */
- (nullable id<IAFetchTask>)fetchFloorPlanWithId:(nullable NSString*)floorPlanId andCompletion:(nullable void(^)(IAFloorPlan * __nullable floorPlan, NSError * __nullable error))completionBlock;

/**
 * Fetch image file data for floor plan id
 *
 * @param floorPlanId Identifier of floor plan to fetch image file data for.
 * @param completionBlock A block to be called when image download is completed.
 *
 *     - *data*: Image file data. If an error occured, this parameter is nil.
 *     - *error*: If an error occured, this object describes the error. If the operation completed successfully, this value is nil.
 *
 * @return IAFetchTask instance for the request.
 */
- (nullable id<IAFetchTask>)fetchFloorPlanImageWithId:(nullable NSString*)floorPlanId andCompletion:(nullable void(^)(NSData * __nullable imageData, NSError * __nullable error))completionBlock __attribute((deprecated("Use fetchFloorPlanImageWithUrl instead")));

/**
 * Fetch image file data for floor plan url
 *
 * @param floorPlanUrl URL of floor plan to fetch image file data for.
 * @param completionBlock A block to be called when image download is completed.
 *
 *     - *data*: Image file data. If an error occured, this parameter is nil.
 *     - *error*: If an error occured, this object describes the error. If the operation completed successfully, this value is nil.
 *
 * @return IAFetchTask instance for the request.
 */
- (nullable id<IAFetchTask>)fetchFloorPlanImageWithUrl:(nonnull NSURL*)floorPlanUrl andCompletion:(nullable void(^)(NSData * __nullable imageData, NSError * __nullable error))completionBlock;
@end

#undef INDOORATLAS_API
