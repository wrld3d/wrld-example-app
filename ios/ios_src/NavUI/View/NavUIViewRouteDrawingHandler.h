// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>

#include "NavRouteDrawingController.h"

#include "WrldNav/WrldNav.h"

@interface NavUIViewRouteDrawingHandler : NSObject

- (instancetype) initWithDrawingController:(ExampleApp::NavRouting::SdkModel::NavRouteDrawingController*)drawingController
                    journeyModel:(WRLDNavModel*)journeyModel;

@end
