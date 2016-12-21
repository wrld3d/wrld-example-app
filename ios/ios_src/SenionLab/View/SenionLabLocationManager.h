// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "SenionLabLocationService.h"
#include "SenionLabLocationIncludes.h"
#include "BidirectionalBus.h"
#include <map>
#include <string>

@interface SenionLabLocationManager : NSObject
{
    ExampleApp::SenionLab::View::SenionLabLocationManagerInterop* m_pInterop;
}

-(instancetype) Init: (ExampleApp::SenionLab::SenionLabLocationService*) senionLabLocationService
        ndMessageBus: (ExampleApp::ExampleAppMessaging::TMessageBus&) messageBus;

-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap;
-(void) StopUpdatingLocation;
- (ExampleApp::SenionLab::View::SenionLabLocationManagerInterop*) getInterop;
@end
