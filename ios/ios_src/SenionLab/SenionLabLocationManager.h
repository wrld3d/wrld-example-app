// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "SenionLabLocationService.h"
#include <map>
#include <string>

@interface SenionLabLocationManager : NSObject

-(instancetype) Init: (ExampleApp::SenionLab::SenionLabLocationService*) senionLabLocationService;
-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap;
-(void) StopUpdatingLocation;

@end
