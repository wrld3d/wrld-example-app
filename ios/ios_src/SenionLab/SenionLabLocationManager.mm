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
    NSMutableArray *locationManagerArray;
    Eegeo::Resources::Interiors::InteriorId m_pBuildingID;
}
-(void)startOfSiteTesting;
@end
@implementation SenionLabLocationManager

#pragma mark init
- (instancetype)init
{
    if (self = [super init])
    {
    
    }
    return self;
}
-(instancetype)initWithAvtarModule:(ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *)deviceModel senionMapKey:(NSString*)mapKey senionCustomerID:(NSString*)customerID builidingID:(Eegeo::Resources::Interiors::InteriorId)bulidingID
{
    if (self = [super init])
    {
        [self initializeSDK:mapKey senionCustomerID:customerID];
        m_pDeviceModel = deviceModel;
        m_pBuildingID = bulidingID;
    }
    return self;
}
-(instancetype)initWithAvtarModule:(ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *)deviceModel buildingMapKeyList:(NSMutableArray*)buildingMapList
{
    if (self = [super init])
    {
        locationManagerArray = [[NSMutableArray alloc]init];
        
        for(NSDictionary*building in buildingMapList)
        {
            NSString *mapKey = [building objectForKey:@"map_key"];
            NSString *customer_id = [building objectForKey:@"customer_id"];
            SLIndoorLocationManager *locationManager_  = [[SLIndoorLocationManager alloc] initWithMapKey:mapKey andCustomerId:customer_id];
            locationManager_.delegate = self;
            [locationManagerArray addObject:locationManager_];
            
        }
        m_pDeviceModel = deviceModel;
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
    
  
    SLCoordinate3D *coordinate3d1 = [[SLCoordinate3D alloc] initWithLatitude:56.459875 andLongitude:-2.978198 andFloorNr:2];
    SLLocationState *locState1 = [[SLLocationState alloc]initWithLocation:coordinate3d1 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
    
    SLCoordinate3D *coordinate3d2 = [[SLCoordinate3D alloc] initWithLatitude:56.459959 andLongitude:-2.978228 andFloorNr:2];
    SLLocationState *locState2 = [[SLLocationState alloc]initWithLocation:coordinate3d2 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];

    SLCoordinate3D *coordinate3d3 = [[SLCoordinate3D alloc] initWithLatitude:56.460009 andLongitude:-2.978240 andFloorNr:2];
    SLLocationState *locState3 = [[SLLocationState alloc]initWithLocation:coordinate3d3 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];
    
    SLCoordinate3D *coordinate3d4 = [[SLCoordinate3D alloc] initWithLatitude:56.460046 andLongitude:-2.978339 andFloorNr:2];
    SLLocationState *locState4 = [[SLLocationState alloc]initWithLocation:coordinate3d4 andLocationUncertainty:0.0 andLocationStatus:SLLocationStatusConfirmed];

    
    NSArray *locationStateArry = [[NSArray alloc] initWithObjects:locState1,locState2,locState3,locState4,nil];
    
    [locationManager startMockupLocationWithLocationStateArray:locationStateArry andTimeInterval:1];
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
    
    Eegeo::Resources::Interiors::InteriorId builingID(std::string("westport_house"));
    // TJ, TODO: the floor index needs a layer of indirection.
    m_pDeviceModel->UpdateLocation(0, 0, location.latitude, location.longitude, m_pBuildingID, 2);//location.floorNr);

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
