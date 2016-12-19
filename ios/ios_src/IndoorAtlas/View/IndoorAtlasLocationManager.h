// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "IndoorAtlasLocationService.h"
#include "IndoorAtlasLocationIncludes.h"
#include "BidirectionalBus.h"
#include <map>
#include <string>

@interface IndoorAtlasLocationManager : NSObject
{
    ExampleApp::IndoorAtlas::View::IndoorAtlasLocationManagerInterop* m_pInterop;
}

-(instancetype) Init: (ExampleApp::IndoorAtlas::IndoorAtlasLocationService*) indoorAtlasLocationService
        ndMessageBus: (ExampleApp::ExampleAppMessaging::TMessageBus&) messageBus;

-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap
                   floorIndex: (int) floorIndex;

-(void) StopUpdatingLocation;
-(void) SetFloorIndex: (int) floorIndex;
- (ExampleApp::IndoorAtlas::View::IndoorAtlasLocationManagerInterop*) getInterop;

@end
