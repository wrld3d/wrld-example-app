// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "IndoorAtlasLocationService.h"
#include "iOSAlertBoxFactory.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include <map>
#include <string>

@interface IndoorAtlasLocationManager : NSObject

-(instancetype) Init: (ExampleApp::IndoorAtlas::IndoorAtlasLocationService*) indoorAtlasLocationService
  iOSAlertBoxFactory: (Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory*) iOSAlertBoxFactory;
-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap
                   floorIndex: (int) floorIndex;
-(void) StopUpdatingLocation;
-(void) SetFloorIndex: (int) floorIndex;

@end
