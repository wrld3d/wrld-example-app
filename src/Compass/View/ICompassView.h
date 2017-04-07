// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class ICompassView : public ScreenControl::View::IScreenControlView
            {
            public:
                virtual ~ICompassView() { };

                virtual void ShowGpsDisabledView() = 0;
                virtual void ShowGpsFollowView() = 0;
                virtual void ShowGpsCompassModeView() = 0;
                virtual void NotifyGpsUnauthorized() = 0;
                virtual void SetHeadingRadians(float heading) = 0;
                virtual void SetRotationHighlight(bool shouldShowRotationHighlight) = 0;
                virtual void InsertCycledCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
