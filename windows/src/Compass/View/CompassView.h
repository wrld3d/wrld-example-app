// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICompassView.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "WindowsNativeState.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassView : public ICompassView, private Eegeo::NonCopyable
            {
            private:
                Eegeo::Helpers::CallbackCollection0 m_callbacks;
                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mShowGpsDisabledView;
                Helpers::ReflectionHelpers::Method<void> mShowGpsFollowView;
                Helpers::ReflectionHelpers::Method<void> mShowGpsCompassModeView;
                Helpers::ReflectionHelpers::Method<void> mNotifyGpsUnauthorized;
                Helpers::ReflectionHelpers::Method<float> mUpdateHeading;
                Helpers::ReflectionHelpers::Method<float> mAnimateToIntermediateOnScreenState;
                Helpers::ReflectionHelpers::Method<void> mAnimateToActive;
                Helpers::ReflectionHelpers::Method<void> mAnimateToInactive;
                Helpers::ReflectionHelpers::Method<bool> mSetRotationHighlight;

            public:
                CompassView(WindowsNativeState& nativeState,
                    bool isInKioskMode);
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

                void SetRotationHighlight(bool shouldShowRotationHighlight);

                void InsertCycledCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
