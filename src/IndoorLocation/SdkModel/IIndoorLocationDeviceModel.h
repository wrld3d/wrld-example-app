// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "PlatformType.h"
#include "LatLongAltitude.h"
#include "DeviceLocation.h"
#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace IndoorLocation
    {
        namespace SdkModel
        {
            class IIndoorLocationDeviceModel
            {
            public:
                
                virtual ~IIndoorLocationDeviceModel() {}
                virtual const DeviceLocation& GetLocation() const = 0;
                virtual void UpdateLocation(float mapX, float mapY, double latitudeDegrees, double longitudeDegrees, const Eegeo::Resources::Interiors::InteriorId& building, int floor) = 0;
                virtual void UpdateHeading(double heading) = 0;
                virtual void AddLocationChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveLocationChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
            
            
        }
    }

}