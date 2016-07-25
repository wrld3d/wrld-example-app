// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "IndoorLocationModule.h"

#include <map>
#include "IndoorLocationDeviceModel.h"


namespace ExampleApp
{
    namespace IndoorLocation
    {
        namespace SdkModel
        {
            IndoorLocationModule::IndoorLocationModule()
            {
                m_pDeviceModel = IndoorLocationDeviceModel::CreateFrom();
            }
            
            IndoorLocationModule::~IndoorLocationModule()
            {
                Eegeo_DELETE m_pDeviceModel;
            }
            
            IIndoorLocationDeviceModel& IndoorLocationModule::GetDeviceModel() const
            {
                return *m_pDeviceModel;
            }
        }
    }
}