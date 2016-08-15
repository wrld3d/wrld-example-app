// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <CoreLocation/CoreLocation.h>
#import <CoreLocation/CLLocationManagerDelegate.h>
#include "Types.h"
#include "iOSLocationService.h"
#include <memory>

@interface AppLocationDelegateLocationListener : NSObject<CLLocationManagerDelegate>
{

}
@end

class AppLocationDelegate : protected Eegeo::NonCopyable
{
    AppLocationDelegateLocationListener* m_pAppLocationDelegateLocationListener;
    bool m_receivedPermissionResponse;
public:
    AppLocationDelegate(const std::shared_ptr<Eegeo::iOS::iOSLocationService>& iOSLocationService,
                        UIViewController& viewController);

    ~AppLocationDelegate();

    void NotifyReceivedPermissionResponse();

    bool HasReceivedPermissionResponse() const;
};
