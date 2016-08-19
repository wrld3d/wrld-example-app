// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IIndoorLocationDeviceModel.h"

#include "Types.h"
#include "Interiors.h"
#include "DeviceLocation.h"
#include "AppInfo.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include <string>

namespace ExampleApp
{
    namespace IndoorLocation
    {
        namespace SdkModel
        {
            class IndoorLocationDeviceModel : public IIndoorLocationDeviceModel
            {
            public:
                


                const DeviceLocation& GetLocation() const;
                void UpdateLocation(float mapX, float mapY, double latitudeDegrees, double longitudeDegrees, const Eegeo::Resources::Interiors::InteriorId& building, int floor, bool isBlueToothEnabled);
                void UpdateHeading(double heading);
                void AddLocationChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveLocationChangedCallback(Eegeo::Helpers::ICallback0& callback);
                static IndoorLocationDeviceModel* CreateFrom();
            private:
                
                IndoorLocationDeviceModel();
                std::string m_ipAddress;
                bool m_hasLocation;
                std::string m_deviceHandle;
                Eegeo::Helpers::CallbackCollection0 m_locationUpdatedCallbacks;
                DeviceLocation m_location;
                
                
            };
        }
    }
}