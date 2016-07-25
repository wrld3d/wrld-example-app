// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "IndoorLocationDeviceModel.h"

#include <string>
#include "IpAddressHelpers.h"

namespace ExampleApp
{
    namespace IndoorLocation
    {
        namespace SdkModel
        {            
            IndoorLocationDeviceModel::IndoorLocationDeviceModel(){
                
            }
            IndoorLocationDeviceModel* IndoorLocationDeviceModel::CreateFrom()
            {
                // NOTES: iOS 7 and later don't let you access the MAC Address of a device, instead it recommends the identifierForVendor (appInfo.UserId)
                // TODO: What should DeviceUID be?
                // NOTE: Might need platform specific factories for this instead of jumping off the back of AppInfo.
//                std::string ipAddress = Helpers::IpAddressHelpers::GetWifiIpAddress();
                return Eegeo_NEW(IndoorLocationDeviceModel)();
            }
            const DeviceLocation& IndoorLocationDeviceModel::GetLocation() const
            {
                //Eegeo_ASSERT(m_isRegistered, "Cannot retrieve Device Location from unregistered device.");
                Eegeo_ASSERT(m_hasLocation, "Cannot retrieve Device Location. No location has been retrieved yet.");
                return m_location;
            }
            void IndoorLocationDeviceModel::UpdateLocation(float mapX, float mapY, double latitudeDegrees, double longitudeDegrees, const Eegeo::Resources::Interiors::InteriorId& building, int floor)
            {
               // Eegeo_ASSERT(m_isRegistered, "Cannot update location of unregistered device.");
                m_location.Update(mapX, mapY, latitudeDegrees, longitudeDegrees, building, floor);
                m_hasLocation = true;
                m_locationUpdatedCallbacks.ExecuteCallbacks();
                Eegeo_TTY("DEVICE LOCATION UPDATED: (%f, %f) %f, %f, %s, %d", mapX, mapY, latitudeDegrees, longitudeDegrees, building.Value().c_str(), floor);
            }
            void IndoorLocationDeviceModel:: UpdateHeading(double heading){
                m_location.setHeading(heading);
            }
            
            void IndoorLocationDeviceModel::AddLocationChangedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_locationUpdatedCallbacks.AddCallback(callback);
            }
            
            void IndoorLocationDeviceModel::RemoveLocationChangedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_locationUpdatedCallbacks.RemoveCallback(callback);
            }
        }
    }
}