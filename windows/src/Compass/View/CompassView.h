// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICompassView.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "WindowsNativeState.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassViewImpl;

            class CompassView : public ICompassView, private Eegeo::NonCopyable
            {
            private:
                CompassViewImpl* m_pImpl;

            public:
                CompassView(const std::shared_ptr<WindowsNativeState>& nativeState);
                ~CompassView();

                void OnCycle();

                void ShowGpsDisabledView();

                void ShowGpsFollowView();

                void ShowGpsCompassModeView();

                void NotifyGpsUnauthorized();

                void SetHeadingRadians(float heading);

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void InsertCycledCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
