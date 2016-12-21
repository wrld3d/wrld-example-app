// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#import "SenionLabLocationManager.h"
#include "SenionLabLocationManagerInterop.h"
#import <SLIndoorLocation/SLCoordinate3D.h>
#import <SLIndoorLocation/SLIndoorLocationManager.h>
#include "LatLongAltitude.h"

@interface SenionLabLocationManager()<SLIndoorLocationManagerDelegate>
{
    std::map<int, std::string> m_floorMap;
    int m_floorIndex;
}
@property (nonatomic, strong) SLIndoorLocationManager *locationManager;
@end

@implementation SenionLabLocationManager

-(instancetype) Init: (ExampleApp::SenionLab::SenionLabLocationService*) senionLabLocationService
        ndMessageBus: (ExampleApp::ExampleAppMessaging::TMessageBus&) messageBus
{
    if(self = [super init])
    {
        m_pInterop = Eegeo_NEW(ExampleApp::SenionLab::View::SenionLabLocationManagerInterop)(self,
                                                                                             senionLabLocationService,
                                                                                             messageBus);
        
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

- (ExampleApp::SenionLab::View::SenionLabLocationManagerInterop*) getInterop
{
    return m_pInterop;
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

-(void) didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)radius andStatus:(SLLocationStatus)locationStatus
{
    m_pInterop->SetIsAuthorized(true);
    
    Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(location.latitude, location.longitude);
    m_pInterop->OnLocationChanged(latLong);
    
    int floorIndex = [self getFloorIndexFromSenionFloorIndex:std::to_string(location.floorNr)];
    m_pInterop->OnSetFloorIndex(floorIndex);
}

-(void) didUpdateHeading:(double)heading withStatus:(BOOL)status
{
    m_pInterop->SetIsAuthorized(true);
}

-(void) didUpdateMotionType:(SLMotionState)motionState
{
    m_pInterop->SetIsAuthorized(true);
}

-(void) didFailInternetConnectionWithError:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInternetConnectionWithError");
    m_pInterop->SetIsAuthorized(false);
}

-(void) didFailInvalidIds:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInvalidIds");
    m_pInterop->SetIsAuthorized(false);
}

-(void) didFailLocationAuthorizationStatus
{
    NSLog(@"SenionLabLocationManager didFailLocationAuthorizationStatus");
    m_pInterop->SetIsAuthorized(false);
}

-(void) didFailScanningBT
{
    NSLog(@"SenionLabLocationManager didFailScanningBT");
    m_pInterop->SetIsAuthorized(false);
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

@end
