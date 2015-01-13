// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppLocationDelegate.h"
#include "ViewController.h"

@implementation AppLocationDelegateLocationListener

CLLocationManager* m_pLocationManager;
Eegeo::iOS::iOSLocationService* m_piOSLocationService;
UIViewController* m_pUIViewController;
AppLocationDelegate* m_pAppLocationDelegate;

-(void)start:(Eegeo::iOS::iOSLocationService *)piOSLocationService
    :(UIViewController*)pViewController
    :(AppLocationDelegate*)pAppLocationDelegate
{
	m_piOSLocationService = piOSLocationService;
	m_pUIViewController = pViewController;
    m_pAppLocationDelegate = pAppLocationDelegate;

	m_pLocationManager = [[CLLocationManager alloc] init];
	m_pLocationManager.delegate = self;
	m_pLocationManager.desiredAccuracy = kCLLocationAccuracyBest;
	m_pLocationManager.headingFilter = kCLHeadingFilterNone;

	if([m_pLocationManager respondsToSelector:@selector(requestWhenInUseAuthorization)])
	{
		[m_pLocationManager requestWhenInUseAuthorization];
	}

	[m_pLocationManager startUpdatingLocation];
	[m_pLocationManager startUpdatingHeading];
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
	m_piOSLocationService->FailedToGetLocation();
	m_piOSLocationService->FailedToGetHeading();
}


- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status
{
    if (status != kCLAuthorizationStatusNotDetermined)
    {
        m_pAppLocationDelegate->NotifyReceivedPermissionResponse();
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations
{
    CLLocation *currentLocation = [locations lastObject];
    
    if (currentLocation != nil)
    {
        double latDegrees = currentLocation.coordinate.latitude;
        double lonDegrees = currentLocation.coordinate.longitude;
        double altitudeMeters = currentLocation.altitude;
        double accuracyMeters = currentLocation.horizontalAccuracy;
        m_piOSLocationService->UpdateLocation(latDegrees, lonDegrees, altitudeMeters);
        m_piOSLocationService->UpdateHorizontalAccuracy(accuracyMeters);
    }
    else
    {
        m_piOSLocationService->FailedToGetLocation();
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
{
	if (newHeading.headingAccuracy >= 0)
	{
		float heading = static_cast<float>(newHeading.trueHeading);

		if (m_pUIViewController.interfaceOrientation == UIInterfaceOrientationLandscapeLeft)
		{
			heading -= 90.f;
		}
		else if (m_pUIViewController.interfaceOrientation == UIInterfaceOrientationLandscapeRight)
		{
			heading += 90.f;
		}
		else if (m_pUIViewController.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
		{
			heading += 180.f;
		}
		else
		{
			heading += 0.f;
		}

		heading = fmodf((heading + 360.f), 360.f);
		m_piOSLocationService->UpdateHeading(heading);
	}
	else
	{
		m_piOSLocationService->FailedToGetHeading();
	}
}

@end

AppLocationDelegate::AppLocationDelegate(Eegeo::iOS::iOSLocationService& iOSLocationService,
                                         UIViewController& viewController)
: m_receivedPermissionResponse(false)
{
	m_pAppLocationDelegateLocationListener = [[AppLocationDelegateLocationListener alloc] init];
	[m_pAppLocationDelegateLocationListener start:&iOSLocationService :&viewController: this];
}

AppLocationDelegate::~AppLocationDelegate()
{
	[m_pAppLocationDelegateLocationListener release];
	m_pAppLocationDelegateLocationListener = nil;
}

void AppLocationDelegate::NotifyReceivedPermissionResponse()
{
    m_receivedPermissionResponse = true;
}

bool AppLocationDelegate::HasReceivedPermissionResponse() const
{
    return m_receivedPermissionResponse;
}
