// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Avatar.h"
#include "IAvatarModel.h"
#include "SenionLocation.h"
namespace ExampleApp
{
    
    namespace SenionLocation
    {
        
            
        class AvatarVisibilityObserver
        {
                
            public:
                
                AvatarVisibilityObserver(ExampleApp::Avatar::SdkModel::IAvatarModel& avatarModel,ExampleApp::SenionLocation::SdkModel::ISenionLocationService& locationService);
                ~AvatarVisibilityObserver();
                
            private:
                
                void OnVisibilityChanged();
                void OnLocationChanged();
                
                ExampleApp::Avatar::SdkModel::IAvatarModel& m_avatarModel;
                ExampleApp::SenionLocation::SdkModel::ISenionLocationService& m_locationService;
                Eegeo::Helpers::TCallback0<AvatarVisibilityObserver> m_AvatarVisibiltyChangecallback;
                Eegeo::Helpers::TCallback0<AvatarVisibilityObserver> m_AvatarLocationChangecallback;

                
        };
    
    }
}

