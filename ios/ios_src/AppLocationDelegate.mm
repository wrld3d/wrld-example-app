// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppLocationDelegate.h"

@implementation AppLocationDelegateLocationListener

CLLocationManager* m_pLocationManager;
Eegeo::iOS::iOSLocationService* m_piOSLocationService;

-(void)start:(Eegeo::iOS::iOSLocationService *)piOSLocationService
{
    m_piOSLocationService = piOSLocationService;
    
	m_pLocationManager = [[CLLocationManager alloc] init];
	m_pLocationManager.delegate = self;
	m_pLocationManager.desiredAccuracy = kCLLocationAccuracyBest;
	m_pLocationManager.headingFilter = kCLHeadingFilterNone;
    
	[m_pLocationManager startUpdatingLocation];
	[m_pLocationManager startUpdatingHeading];
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
	m_piOSLocationService->FailedToGetLocation();
	m_piOSLocationService->FailedToGetHeading();
}

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
	CLLocation *currentLocation = newLocation;
    
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
		m_piOSLocationService->UpdateHeading(newHeading.trueHeading);
	}
	else
	{
		m_piOSLocationService->FailedToGetHeading();
	}
}

@end

AppLocationDelegate::AppLocationDelegate(Eegeo::iOS::iOSLocationService& iOSLocationService)
{
	m_pAppLocationDelegateLocationListener = [[AppLocationDelegateLocationListener alloc] init];
    [m_pAppLocationDelegateLocationListener start:&iOSLocationService];
}

AppLocationDelegate::~AppLocationDelegate()
{
	[m_pAppLocationDelegateLocationListener release];
	m_pAppLocationDelegateLocationListener = nil;
}
