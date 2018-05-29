// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IOpenableControlViewModel.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingRouteModel.h"
#include "IReactionScreenStateProvider.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class INavWidgetViewModel
            {
            public:
                virtual ~INavWidgetViewModel() { }

                virtual bool IsOpen() const = 0;

                virtual void Open() = 0;

                virtual void Close() = 0;

                virtual void SetNavMode(SdkModel::NavRoutingMode mode) = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetOpenableControl() = 0;

                virtual Reaction::View::IReactionScreenStateProvider& GetCompassStateProvider() = 0;
                virtual Reaction::View::IReactionScreenStateProvider& GetInteriorsStateProvider() = 0;
            };
        }
    }
}
