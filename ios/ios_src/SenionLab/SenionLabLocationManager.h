// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "SenionLabLocationService.h"
#include "iOSAlertBoxFactory.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include <map>
#include <string>
#include "BidirectionalBus.h"

@interface SenionLabLocationManager : NSObject

-(instancetype) Init: (ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService*) senionLabLocationService
  iOSAlertBoxFactory:(Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory*) iOSAlertBoxFactory
          messageBus:(ExampleApp::ExampleAppMessaging::TMessageBus*) messageBus;
-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap;
-(void) StopUpdatingLocation;

@end
