// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "ICallback.h"
#include "NavRoutingLocationModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class INavWidgetView
            {
            public:
                virtual ~INavWidgetView() { };

                virtual void Show() = 0;

                virtual void Hide() = 0;

                virtual void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearStartLocation() = 0;

                virtual void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearEndLocation() = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
