#pragma once

#import <CoreLocation/CoreLocation.h>
#import "WRLDBasicSearchResultModel.h"

/*!
 A Simple WRLDSearchResultModel with a latitude and longitude.
 */
@interface WRLDPositionedSearchResultModel : WRLDBasicSearchResultModel

/*!
 Create a new WRLDPositionedSearchResultModel.
 @param title A short string that represents the content of the result.  Displayed by the default WRLDSearchWidgetTableViewCells.
 @param subTitle A short string that represents additional info related to the result.  Displayed by the default WRLDSearchWidgetTableViewCells.
 @param iconKey A string that corresponds to an icon for this results.  The default WRLDSearchWidgetTableViewCells attempts to resolve this as a web URL.
 @param latLng The latLng that corresponds to this result.
 */
-(instancetype) initWithTitle:(NSString*) title subTitle:(NSString *)subTitle iconKey:(NSString *) iconKey latLng:(CLLocationCoordinate2D) latLng;

/*!
 @return Latitude and Longitude of the Search Results.
 */
@property (nonatomic) CLLocationCoordinate2D latLng;

@end




