// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassViewInterop.h"
#include "CompassView.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassViewInterop::CompassViewInterop(CompassView* view) : m_pView(view)
            {
            }

            void CompassViewInterop::OnCycle()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void CompassViewInterop::ShowGpsDisabledView()
            {
                [m_pView showGpsDisabledView];
            }

            void CompassViewInterop::ShowGpsFollowView()
            {
                [m_pView showGpsFollowView];
            }

            void CompassViewInterop::ShowGpsCompassModeView()
            {
                [m_pView showGpsCompassModeView];
            }

            void CompassViewInterop::NotifyGpsUnauthorized()
            {
                [m_pView notifyGpsUnauthorized];
            }
            
            void CompassViewInterop::SetHeadingRadians(float heading)
            {
                [m_pView updateHeading:heading];
            }

            void CompassViewInterop::InsertCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void CompassViewInterop::RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

            void CompassViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue:value];
            }

            void CompassViewInterop::SetOnScreen()
            {
                [m_pView setFullyOnScreen];
            }

            void CompassViewInterop::SetOffScreen()
            {
                [m_pView setFullyOffScreen];
            }
            
            void CompassViewInterop::SetRotationHighlight(bool shouldShowRotationHighlight)
            {
                [m_pView setRotationHighlight:shouldShowRotationHighlight];
            }
            
            void CompassViewInterop::SetState(ScreenControl::View::TScreenControlViewState state)
            {
                BOOL isValidState = [m_pView isValidPositionState: state];
                Eegeo_ASSERT(isValidState, "Tried to set an invalid compass state");
                CompassPositionState viewState = (CompassPositionState) state;
                [m_pView setPositionState: viewState];
            }
        }
    }
}
