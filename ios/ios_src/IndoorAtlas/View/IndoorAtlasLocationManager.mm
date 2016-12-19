// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#include "IndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationManagerInterop.h"
#import <IndoorAtlas/IALocationManager.h>
#include "LatLongAltitude.h"

@interface IndoorAtlasLocationManager()<IALocationManagerDelegate>
{
    std::map<int, std::string> m_floorMap;
    int m_floorIndex;
}
@property (nonatomic, strong) IALocationManager *locationManager;
@end

@implementation IndoorAtlasLocationManager

-(instancetype) Init: (ExampleApp::IndoorAtlas::IndoorAtlasLocationService*) indoorAtlasLocationService
        ndMessageBus: (ExampleApp::ExampleAppMessaging::TMessageBus&) messageBus
{
    if(self = [super init])
    {
        m_pInterop = Eegeo_NEW(ExampleApp::IndoorAtlas::View::IndoorAtlasLocationManagerInterop)(self, indoorAtlasLocationService, messageBus);
    }
    
    return self;
}

-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap
                   floorIndex: (int) floorIndex
{
    self.locationManager = [IALocationManager sharedInstance];
    [self.locationManager setApiKey:apiKey andSecret:apiSecret];
    self.locationManager.delegate = self;
    
    m_floorMap = floorMap;
    m_floorIndex = floorIndex;
    
    NSString* floorPlanId = [self getFloorPlanIdFromFloorIndex:floorIndex];
    
    if(floorPlanId)
    {
        IALocation *location = [IALocation locationWithFloorPlanId:floorPlanId];
        self.locationManager.location = location;
    }
    
    [self.locationManager startUpdatingLocation];
}

-(void) StopUpdatingLocation
{
    [self.locationManager stopUpdatingLocation];
}

-(void) SetFloorIndex: (int) floorIndex
{
    m_floorIndex = floorIndex;
    
    NSString* floorPlanId = [self getFloorPlanIdFromFloorIndex:floorIndex];
    
    if(floorPlanId)
    {
        IALocation *location = [IALocation locationWithFloorPlanId:floorPlanId];
        self.locationManager.location = location;
        m_pInterop->OnSetFloorIndex(m_floorIndex);
    }
}

- (ExampleApp::IndoorAtlas::View::IndoorAtlasLocationManagerInterop*) getInterop
{
    return m_pInterop;
}

-(void) dealloc
{
    Eegeo_DELETE m_pInterop;
    [self.locationManager stopUpdatingLocation];
    self.locationManager.delegate = nil;
    [super dealloc];
}

-(void) indoorLocationManager: (IALocationManager*) manager didUpdateLocations: (NSArray*) locations
{
    CLLocation *l = [(IALocation*)locations.lastObject location];
    Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(l.coordinate.latitude, l.coordinate.longitude);
    m_pInterop->OnLocationChanged(latLong);
}

-(NSString*) getFloorPlanIdFromFloorIndex: (int) floorIndex
{
    std::map<int, std::string>::iterator it = m_floorMap.find(floorIndex);
    
    if(it != m_floorMap.end())
    {
        return [NSString stringWithCString:it->second.c_str() encoding:[NSString defaultCStringEncoding]];
    }
    
    return nil;
}

@end
