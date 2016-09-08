// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuInitiationViewInterop.h"
#include "DirectionsMenuInitiationView.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            void DirectionsMenuInitiationViewInterop::OnToggle(bool toggled)
            {
                m_callbacks.ExecuteCallbacks(toggled);
            }

            void DirectionsMenuInitiationViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue:value];
            }

            void DirectionsMenuInitiationViewInterop::SetFullyOnScreen()
            {
                [m_pView setFullyOnScreen];
            }

            void DirectionsMenuInitiationViewInterop::SetFullyOffScreen()
            {
                [m_pView setFullyOffScreen];
            }
            
            void InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback);
            
            void RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback);

            void DirectionsMenuInitiationViewInterop::InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void DirectionsMenuInitiationViewInterop::RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
        }
    }
}