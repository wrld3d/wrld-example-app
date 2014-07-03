// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPLOCATIONDELEGATE_H_
#define APPLOCATIONDELEGATE_H_

#import <CoreLocation/CoreLocation.h>
#import <CoreLocation/CLLocationManagerDelegate.h>
#include "Types.h"
#include "iOSLocationService.h"

@interface AppLocationDelegateLocationListener : NSObject<CLLocationManagerDelegate>
{
    
}
@end

class AppLocationDelegate : protected Eegeo::NonCopyable
{
    AppLocationDelegateLocationListener* m_pAppLocationDelegateLocationListener;
    
public:
	AppLocationDelegate(Eegeo::iOS::iOSLocationService& m_iOSLocationService);
    ~AppLocationDelegate();
};

#endif