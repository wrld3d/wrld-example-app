#pragma once

#import <CoreLocation/CoreLocation.h>
#import "WRLDBasicSearchResultModel.h"

@interface WRLDPositionedSearchResultModel : WRLDBasicSearchResultModel

-(instancetype) initWithTitle:(NSString*) title subTitle:(NSString *)subTitle iconKey:(NSString *) iconKey latLng:(CLLocationCoordinate2D) latLng;

@property (nonatomic) CLLocationCoordinate2D latLng;

@end




