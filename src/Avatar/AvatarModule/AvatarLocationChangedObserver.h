// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "Types.h"
#include "Avatar.h"
#include "IndoorLocation.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace AvatarModule
        {
            class AvatarLocationChangedObserver
            {
            public:
                
                AvatarLocationChangedObserver(SdkModel::IAvatarController& avatarController, IndoorLocation::SdkModel::IIndoorLocationDeviceModel& deviceModel);
                ~AvatarLocationChangedObserver();
                
            private:
                
                void OnLocationChanged();
                
                SdkModel::IAvatarController& m_avatarController;
                IndoorLocation::SdkModel::IIndoorLocationDeviceModel& m_deviceModel;
                Eegeo::Helpers::TCallback0<AvatarLocationChangedObserver> m_callback;
            };
        }
    }
}