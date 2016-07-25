// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "LocationServiceFacade.h"
#include "ILocationService.h"


namespace ExampleApp
{
    
    namespace SenionLocation
    {
        
        namespace SdkModel
        {
 
            LocationServiceFacade::LocationServiceFacade(Eegeo::Location::ILocationService& locationService):m_gpslocationService(locationService)
            ,m_Senionlatlong((Eegeo::Space::LatLong::FromDegrees(0.0, 0.0)))
            ,m_avatarVisiblityStatus(false)
            {
                

            }
            
            LocationServiceFacade::~LocationServiceFacade()
            {
            
            }
            
            bool LocationServiceFacade::GetLocation(Eegeo::Space::LatLong& latlong)
            {
                if(m_avatarVisiblityStatus == true)
                {
                    
                    latlong = Eegeo::Space::LatLong::FromDegrees(m_Senionlatlong.GetLatitudeInDegrees(),m_Senionlatlong.GetLongitudeInDegrees());
                    return true;

                }
                else
                {
                    return m_gpslocationService.GetLocation(latlong);
                }
                
            }
            
            bool LocationServiceFacade::GetAltitude(double& altitude)
            {
                return m_gpslocationService.GetAltitude(altitude);
            }
            
            bool LocationServiceFacade::GetHorizontalAccuracy(double& accuracy)
            {
                
                return m_gpslocationService.GetHorizontalAccuracy(accuracy);
            }
            
            bool LocationServiceFacade::GetHeadingDegrees(double& headingDegrees)
            {
                return m_gpslocationService.GetHeadingDegrees(headingDegrees);
            }
            
            void LocationServiceFacade::StopListening()
            {
                m_gpslocationService.StopListening();
            }
            
            bool LocationServiceFacade::isSenionMode()
            {
                return m_avatarVisiblityStatus;
            }
            
            void LocationServiceFacade::UpdateSenionLatLong(const Eegeo::Space::LatLong &latLong)
            {
                m_Senionlatlong  = Eegeo::Space::LatLong::FromRadians(latLong.GetLatitude(), latLong.GetLongitude());
            }
            void LocationServiceFacade::UpdateAvatarVisiblityStatus(bool status)
            {
                m_avatarVisiblityStatus = status;
            }
            
        }
    }
}