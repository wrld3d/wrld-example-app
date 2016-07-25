// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "IndoorLocation.h"
#include "IIndoorLocationModule.h"
#include "AppInfo.h"
#include "Web.h"
#include <string>

namespace ExampleApp
{
    namespace IndoorLocation
    {
        namespace SdkModel
        {
            class IndoorLocationModule : public IIndoorLocationModule
            {
            public:
                
                IndoorLocationModule();
                ~IndoorLocationModule();
                IIndoorLocationDeviceModel& GetDeviceModel() const;
                
            private:
                IIndoorLocationDeviceModel* m_pDeviceModel;
            };
        }
    }
}