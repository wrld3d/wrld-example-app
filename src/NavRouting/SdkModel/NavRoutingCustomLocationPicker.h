// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "INavRoutingCustomLocationPicker.h"
#include "NavRouting.h"
#include "AppCamera.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingCustomLocationPicker : public INavRoutingCustomLocationPicker {
            public:

                NavRoutingCustomLocationPicker(INavRoutingModel& navRoutingModel,
                                               AppCamera::SdkModel::IAppCameraLocationPicker& cameraLocationPicker);
                ~NavRoutingCustomLocationPicker();

                void StartSearching(bool forStartLocation);
                void StopSearching();
                bool HandleTouchTap(float screenX, float screenY);

            private:

                INavRoutingModel& m_navRoutingModel;
                AppCamera::SdkModel::IAppCameraLocationPicker& m_cameraLocationPicker;

                bool m_isSearching;
                bool m_isStartLocation;

            };
        }
    }
}
