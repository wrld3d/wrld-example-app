// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICompassView.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "AndroidNativeState.h"
#include "INavWidgetView.h"

#include <string>

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
                AndroidNativeState& m_nativeState;
                Eegeo::Helpers::TCallback1<CompassView, NavRouting::View::INavWidgetView::THeight> m_navWidgetBottomHeightChangedCallback;

                Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetBottomHeightChangedCallbacks;

                jclass m_uiViewClass;
                jobject m_uiView;

                void CallVoidMethod(const std::string& methodName);

                void SetNavigationModeOffset(NavRouting::View::INavWidgetView::THeight& m_offset);
            public:
                CompassView(AndroidNativeState& nativeState,
                            Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& navViewBottomHeightChangedCallbacks);
                ~CompassView();

                void OnCycle();

                void ShowGpsDisabledView();

                void ShowGpsFollowView();

                void ShowGpsCompassModeView();

                void NotifyGpsUnauthorized();

                void SetHeadingRadians(float heading);

                void SetOnScreenStateToIntermediateValue(float value);

                void SetOnScreen();

                void SetOffScreen();

                void SetRotationHighlight(bool shouldShowRotationHighlight);

                void InsertCycledCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback);

                void SetState(ScreenControl::View::TScreenControlViewState state);
            };
        }
    }
}
