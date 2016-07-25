// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include <stdio.h>
#include "AvatarVisibilityObserver.h"
#include "ISenionLocationService.h"
namespace ExampleApp
{
    
    namespace SenionLocation
    {
        
            AvatarVisibilityObserver::AvatarVisibilityObserver(ExampleApp::Avatar::SdkModel::IAvatarModel& avatarModel,ExampleApp::SenionLocation::SdkModel::ISenionLocationService& locationService)
            :m_avatarModel(avatarModel)
            ,m_locationService(locationService)
            ,m_AvatarVisibiltyChangecallback(this, &AvatarVisibilityObserver::OnVisibilityChanged)
            ,m_AvatarLocationChangecallback(this, &AvatarVisibilityObserver::OnLocationChanged)
            {
                m_avatarModel.AddAvatarVisiblityChangedCallback(m_AvatarVisibiltyChangecallback);
                m_avatarModel.AddAvatarLocationChangedCallback(m_AvatarLocationChangecallback);
            }
            AvatarVisibilityObserver::~AvatarVisibilityObserver()
            {
                m_avatarModel.RemoveAvatarVisiblityChangedCallback(m_AvatarVisibiltyChangecallback);
                m_avatarModel.RemoveAvatarLocationChangedCallback(m_AvatarLocationChangecallback);
            }
            
            
            
            void AvatarVisibilityObserver::OnVisibilityChanged()
            {
                m_locationService.UpdateAvatarVisiblityStatus(m_avatarModel.GetAvatarVisibilityStatus());
            }
            void AvatarVisibilityObserver::OnLocationChanged()
            {
                m_locationService.UpdateSenionLatLong(m_avatarModel.GetPosition());
            }
        
    }
}