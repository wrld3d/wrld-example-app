// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "IndoorLocation.h"
#import "SenionLabLocationManager.h"
#import "IIndoorLocationDeviceModel.h"
#import <SLIndoorLocation/SLCoordinate3D.h>
#import <SLIndoorLocation/SLIndoorLocationManager.h>

@interface SenionLabLocationManager()<SLIndoorLocationManagerDelegate>
{
    SLIndoorLocationManager *locationManager;
    ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *m_pDeviceModel;
    Eegeo::Resources::Interiors::InteriorId m_pBuildingID;
    std::map<int,int> m_senionFloorMap;
}
-(void)startOfSiteTesting;

@end

@implementation SenionLabLocationManager

#pragma mark init

-(instancetype)initWithAvtarModule:(ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *)deviceModel senionMapKey:(NSString*)mapKey senionCustomerID:(NSString*)customerID builidingID:(Eegeo::Resources::Interiors::InteriorId)bulidingID ndSenionFloorMap:(std::map<int,int>)senionFloorMap
{
    if (self = [super init])
    {
        [self initializeSDK:mapKey senionCustomerID:customerID];
        m_pDeviceModel = deviceModel;
        m_pBuildingID = bulidingID;
        m_senionFloorMap = senionFloorMap;
    }
    return self;
}

-(void)initializeSDK:(NSString*)mapKey senionCustomerID:(NSString*)customerID
{
    // Init SLIndoorLocationManager

    // If you want to change authorization method, this should be done before initialization.
    [SLIndoorLocationManager setIbeaconAuthorizationMethod:SLRequestWhenInUseAuthorization];
    locationManager = [[SLIndoorLocationManager alloc] initWithMapKey:mapKey andCustomerId:customerID];
    locationManager.delegate = self;
}

-(void)startOfSiteTesting
{
    int m_floorIndex = 1;   // for mock testing only
    
    if(m_pBuildingID.Value() == "westport_house")
    {
        // West Port Mock Data
        SLCoordinate3D *coordinate3d1 = [[SLCoordinate3D alloc] initWithLatitude:56.459875 andLongitude:-2.978198 andFloorNr:m_floorIndex];
        SLLocationState *locState1 = [[SLLocationState alloc]initWithLocation:coordinate3d1 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
        
        SLCoordinate3D *coordinate3d2 = [[SLCoordinate3D alloc] initWithLatitude:56.459959 andLongitude:-2.978228 andFloorNr:m_floorIndex];
        SLLocationState *locState2 = [[SLLocationState alloc]initWithLocation:coordinate3d2 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
        
        SLCoordinate3D *coordinate3d3 = [[SLCoordinate3D alloc] initWithLatitude:56.460009 andLongitude:-2.978240 andFloorNr:m_floorIndex];
        SLLocationState *locState3 = [[SLLocationState alloc]initWithLocation:coordinate3d3 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
        
        SLCoordinate3D *coordinate3d4 = [[SLCoordinate3D alloc] initWithLatitude:56.460046 andLongitude:-2.978339 andFloorNr:m_floorIndex];
        SLLocationState *locState4 = [[SLLocationState alloc]initWithLocation:coordinate3d4 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
        
        
        NSArray *locationStateArry = [[NSArray alloc] initWithObjects:locState1,locState2,locState3,locState4,nil];
        [locationManager startMockupLocationWithLocationStateArray:locationStateArry andTimeInterval:1];
        
    }
    
   else if (m_pBuildingID.Value() == "swallow_lon_citygatehouse")
   {
       
       SLCoordinate3D *coordinate3d1 = [[SLCoordinate3D alloc] initWithLatitude:51.520146 andLongitude:-0.086268 andFloorNr:m_floorIndex];
       SLLocationState *locState1 = [[SLLocationState alloc]initWithLocation:coordinate3d1 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
       
       SLCoordinate3D *coordinate3d2 = [[SLCoordinate3D alloc] initWithLatitude:51.520150 andLongitude:-0.086392 andFloorNr:m_floorIndex];
       SLLocationState *locState2 = [[SLLocationState alloc]initWithLocation:coordinate3d2 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
       
       NSArray *locationStateArry = [[NSArray alloc] initWithObjects:locState1,locState2,nil];
       [locationManager startMockupLocationWithLocationStateArray:locationStateArry andTimeInterval:1];
       
   }
    
    else if (m_pBuildingID.Value() == "swallow_lon_50finsbury")
    {

        SLCoordinate3D *coordinate3d1 = [[SLCoordinate3D alloc] initWithLatitude:51.520009 andLongitude:-0.087011 andFloorNr:m_floorIndex];
        SLLocationState *locState1 = [[SLLocationState alloc]initWithLocation:coordinate3d1 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
        
        SLCoordinate3D *coordinate3d2 = [[SLCoordinate3D alloc] initWithLatitude:51.520018 andLongitude:-0.087071 andFloorNr:m_floorIndex];
        SLLocationState *locState2 = [[SLLocationState alloc]initWithLocation:coordinate3d2 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
        
        NSArray *locationStateArry = [[NSArray alloc] initWithObjects:locState1,locState2,nil];
        [locationManager startMockupLocationWithLocationStateArray:locationStateArry andTimeInterval:1];
        
    }
}

-(void)stopUpdatingLocation
{
    [locationManager stopUpdatingMockupLocation];
    [locationManager stopUpdatingLocation];
}

-(BOOL)shouldShowAvatar:(int)senionID ndFloorNum:(int &)floorNum
{
    std::map<int,int>::iterator it = m_senionFloorMap.find(senionID);
    
    if(it != m_senionFloorMap.end())
    {
        floorNum = it->second;
        return true;
    }
    
    return false;
}

#pragma mark dealloc
- (void)dealloc
{
    [locationManager stopUpdatingLocation];
    [locationManager release];
    
    [super dealloc];
}

- (void) didFinishLoadingManager
{
    //[locationManager startUpdatingLocation];
    
    //#Mock Location Tesing Uncomment below line and comment above line
    [self startOfSiteTesting];
}
- (void)didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)radius andStatus:(SLLocationStatus)locationStatus
{
    int floorNum = -1;
    
    // TJ, TODO: the floor index needs a layer of indirection.
     if([self shouldShowAvatar:location.floorNr ndFloorNum:floorNum])
     {
        m_pDeviceModel->UpdateLocation(0, 0, location.latitude, location.longitude, m_pBuildingID, floorNum);
     }
}
- (void) didUpdateHeading:(double)heading withStatus:(BOOL)status
{
    m_pDeviceModel->UpdateHeading(heading);
}
- (void) didUpdateMotionType:(SLMotionState)motionState
{
    NSLog(@"didUpdateMotionType");
}
- (void) didFailInternetConnectionWithError:(NSError *)error
{
    NSLog(@"didFailInternetConnectionWithError");
}
- (void) didFailInvalidIds:(NSError *)error
{
    NSLog(@"didFailInvalidIds");
}
- (void) didFailLocationAuthorizationStatus
{
    NSLog(@"didFailLocationAuthorizationStatus");
}
- (void) didFailScanningBT
{
    NSLog(@"didFailScanningBT");
}

@end
