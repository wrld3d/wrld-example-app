// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#import "SenionLabLocationManager.h"
#import <SLIndoorLocation/SLCoordinate3D.h>
#import <SLIndoorLocation/SLIndoorLocationManager.h>
#include "LatLongAltitude.h"

@interface SenionLabLocationManager()<SLIndoorLocationManagerDelegate>
{
    std::map<int, std::string> m_floorMap;
    int m_floorIndex;
    ExampleApp::SenionLab::SenionLabLocationService* m_pSenionLabLocationService;
}
@property (nonatomic, strong) SLIndoorLocationManager *locationManager;
@end

@implementation SenionLabLocationManager

-(instancetype) Init: (ExampleApp::SenionLab::SenionLabLocationService*) senionLabLocationService
{
    if(self = [super init])
    {
        m_pSenionLabLocationService = senionLabLocationService;
    }
    
    return self;
}

-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap
{
    [SLIndoorLocationManager setIbeaconAuthorizationMethod:SLRequestWhenInUseAuthorization];
    self.locationManager = [[SLIndoorLocationManager alloc] initWithMapKey:apiKey andCustomerId:apiSecret];
    self.locationManager.delegate = self;
    
    m_floorMap = floorMap;
}

-(void) StopUpdatingLocation
{
    [self.locationManager stopUpdatingLocation];
}

-(void) dealloc
{
    [self.locationManager stopUpdatingLocation];
    [self.locationManager release];
    [super dealloc];
}

-(void) didFinishLoadingManager
{
    [self.locationManager startUpdatingLocation];
}

-(void) didUpdateHeading:(double)heading withStatus:(BOOL)status
{
    m_pSenionLabLocationService->SetIsAuthorized(true);
}

-(void) didUpdateMotionType:(SLMotionState)motionState
{
    m_pSenionLabLocationService->SetIsAuthorized(true);
}

-(void) didFailInternetConnectionWithError:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInternetConnectionWithError");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(void) didFailInvalidIds:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInvalidIds");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(void) didFailLocationAuthorizationStatus
{
    NSLog(@"SenionLabLocationManager didFailLocationAuthorizationStatus");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(void) didFailScanningBT
{
    NSLog(@"SenionLabLocationManager didFailScanningBT");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(int) getFloorIndexFromSenionFloorIndex: (std::string) senionFloorIndex
{
    for(std::map<int, std::string>::iterator it = m_floorMap.begin(); it != m_floorMap.end(); ++it)
    {
        if(it->second == senionFloorIndex)
        {
            return it->first;
        }
    }
    
    return -1;
}

- (void)didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)uncertaintyRadius
{
    m_pSenionLabLocationService->SetIsAuthorized(true);

    Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(location.latitude, location.longitude);
    m_pSenionLabLocationService->SetLocation(latLong);

    int floorIndex = [self getFloorIndexFromSenionFloorIndex:std::to_string(location.floorNr)];
    m_pSenionLabLocationService->SetFloorIndex(floorIndex);
}

- (void)didUpdateLocationAvailability: (SLLocationAvailability)locationAvailability
{
    
}

@end
