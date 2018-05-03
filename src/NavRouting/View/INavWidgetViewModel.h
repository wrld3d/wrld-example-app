// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IOpenableControlViewModel.h"
#include "NavRoutingLocationModel.h"

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

                virtual bool TryAcquireReactorControl() = 0;

                virtual bool IsOpen() const = 0;

                virtual void Open() = 0;

                virtual void Close() = 0;

                virtual void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearStartLocation() = 0;

                virtual void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearEndLocation() = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void InsertStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback) = 0;

                virtual void RemoveStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback) = 0;

                virtual void InsertStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) = 0;

                virtual void RemoveStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) = 0;

                virtual void InsertEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback) = 0;

                virtual void RemoveEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback) = 0;

                virtual void InsertEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) = 0;

                virtual void RemoveEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetOpenableControl() = 0;
            };
        }
    }
}
