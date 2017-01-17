// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "SenionLabLocationService.h"
#include <map>
#include <string>
#include "BidirectionalBus.h"

@interface SenionLabLocationManager : NSObject

-(instancetype) Init: (ExampleApp::SenionLab::SenionLabLocationService*) senionLabLocationService
          messageBus:(ExampleApp::ExampleAppMessaging::TMessageBus*) messageBus;
-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap;
-(void) StopUpdatingLocation;

@end
