// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AvatarLocationChangedObserver.h"

#include "IAvatarController.h"
#include "IIndoorLocationDeviceModel.h"
#include "IndoorLocationDeviceModel.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace AvatarModule
        {
            AvatarLocationChangedObserver::AvatarLocationChangedObserver(SdkModel::IAvatarController& avatarController,
                                                                                 IndoorLocation::SdkModel::IIndoorLocationDeviceModel& deviceModel)
            : m_avatarController(avatarController)
            , m_deviceModel(deviceModel)
            , m_callback(this, &AvatarLocationChangedObserver::OnLocationChanged)
            {
                m_deviceModel.AddLocationChangedCallback(m_callback);
            }
            
            AvatarLocationChangedObserver::~AvatarLocationChangedObserver()
            {
                m_deviceModel.RemoveLocationChangedCallback(m_callback);
            }
            
            void AvatarLocationChangedObserver::OnLocationChanged()
            {
                m_avatarController.SetModelTarget(m_deviceModel.GetLocation().GetLatLong(), m_deviceModel.GetLocation().GetBuildingID(), m_deviceModel.GetLocation().GetFloor());
            }
        }
    }
}
