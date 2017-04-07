// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICompassView.h"
#include "CompassViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassViewInterop : public ICompassView, private Eegeo::NonCopyable
            {
            private:
                CompassView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;

            public:
                CompassViewInterop(CompassView* view);

                void OnCycle();

                void ShowGpsDisabledView();

                void ShowGpsFollowView();

                void ShowGpsCompassModeView();

                void NotifyGpsUnauthorized();
                
                void SetHeadingRadians(float heading);

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();
                
                void SetRotationHighlight(bool shouldShowRotationHighlight);

                void InsertCycledCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
