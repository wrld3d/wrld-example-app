// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            class IInteriorsNavigationService : protected Eegeo::NonCopyable
            {
            public:
                virtual ~IInteriorsNavigationService(){}
                
                virtual void SetGpsMode(Eegeo::Location::NavigationService::GpsMode mode) = 0;
                
                virtual Eegeo::Location::NavigationService::GpsMode GetGpsMode() const = 0;
                
                virtual void Update(float dt) = 0;
                
                virtual bool IsPositionInInterior() = 0;
            };
            
        }
    }
}