// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#pragma once

#include "ISenionLocationService.h"
#include "IIndoorLocationDeviceModel.h"
namespace ExampleApp
{
    
    namespace SenionLocation
    {
        
        namespace SdkModel
        {
            class LocationServiceFacade : public ISenionLocationService
            {
                
            private:
                Eegeo::Location::ILocationService& m_gpslocationService;
                Eegeo::Space::LatLong m_Senionlatlong;
                bool m_avatarVisiblityStatus;


            public:
                LocationServiceFacade(Eegeo::Location::ILocationService& locationService);
                ~LocationServiceFacade();
                
                const bool GetIsAuthorized() const { return m_gpslocationService.GetIsAuthorized(); }

                bool GetLocation(Eegeo::Space::LatLong& latlong);
                bool GetAltitude(double& altitude);
                bool GetHorizontalAccuracy(double& accuracy);
                bool GetHeadingDegrees(double& headingDegrees);
                void StopListening();
                
                
                void UpdateSenionLatLong(const Eegeo::Space::LatLong &latLong);
                void UpdateAvatarVisiblityStatus(bool status);
                bool isSenionMode();
                
                
            };
        }
    }
}