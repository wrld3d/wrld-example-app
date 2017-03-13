// IndoorAtlas iOS SDK
// IAFloorPlan.h

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <IndoorAtlas/IAFloor.h>
#define INDOORATLAS_API __attribute__((visibility("default")))

/**
 * IAFloorPlan represents floor plan data received from service.
 */
INDOORATLAS_API
@interface IAFloorPlan : NSObject <NSCoding>

/**
 * @name Floor plan information
 */

/**
 * Identifier of the floor plan.
 */
@property (nonatomic, readonly, nullable) NSString *floorPlanId;

/**
 * Name of the floor plan.
 */
@property (nonatomic, readonly, nullable) NSString *name;

/**
 * Image URL of the floor plan.
 */
@property (nonatomic, readonly, nullable) NSURL *imageUrl;

/**
 * Width of the image bitmap in pixels.
 */
@property (nonatomic, readonly) NSUInteger width;

/**
 * Height of the image bitmap in pixels.
 */
@property (nonatomic, readonly) NSUInteger height;

/**
 * Conversion multiplier for pixels to meters.
 */
@property (nonatomic, readonly) float pixelToMeterConversion;

/**
 * Conversion multiplier for meters to pixels.
 */
@property (nonatomic, readonly) float meterToPixelConversion;

/**
 * Width of floor plan in meters.
 */
@property (nonatomic, readonly) float widthMeters;

/**
 * Height of floor plan in meters.
 */
@property (nonatomic, readonly) float heightMeters;

/**
 * Object containing the floor of floor plan.
 * If the object is nil, the floor is unspecified.
 */
@property (nonatomic, readonly, nullable) IAFloor *floor;

/**
 * The approximate bearing of left side of floor plan in
 * degrees East of true North.
 */
@property (nonatomic, readonly) double bearing;

/**
 * Corresponding WGS84 coordinate of center of floor plan bitmap placed 
 * on the surface of earth.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D center;

/**
 * Corresponding WGS84 coordinate of top left of floor plan bitmap placed
 * on the surface of earth.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D topLeft;

/**
 * Corresponding WGS84 coordinate of top right of floor plan bitmap placed
 * on the surface of earth.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D topRight;

/**
 * Corresponding WGS84 coordinate of bottom left of floor plan bitmap placed
 * on the surface of earth.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D bottomLeft;

/**
 * Converts coordinate to corresponding point.
 *
 * @param coord WGS84 coordinate
 * @return corresponding pixel point on floor plan bitmap
 */
- (CGPoint) coordinateToPoint:(CLLocationCoordinate2D) coord;

/**
 * Converts point to corresponding coordinate.
 *
 * @param point pixel point of floor plan bitmap
 * @return corresponding WGS84 coordinate
 */
- (CLLocationCoordinate2D) pointToCoordinate:(CGPoint) point;

/**
 * Initializes IAFloorPlan
 * @param floorPlanId is the identifier of floor plan
 * @param width is the width of floor plan image in pixels
 * @param height is the height of floor plan image in pixels
 * @param wgsToPixel is NSArray of 6 double values in row major order used for creating affine transform for point mapping
 * @param pixelToWgs is NSArray of 6 double values in row major order used for creating affine transform for point mapping
 */
- (nullable id)initWithId:(nullable NSString *)floorPlanId width:(NSUInteger)width height:(NSUInteger)height wgs2pix:(nullable NSArray*)wgsToPixel pix2wgs:(nullable NSArray*)pixelToWgs;

@end

#undef INDOORATLAS_API