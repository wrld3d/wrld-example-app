// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewInterop.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            void FlattenButtonViewInterop::SetToggled(bool toggled)
            {
                [m_pView setSelected:toggled];
            }

            void FlattenButtonViewInterop::OnToggle(bool toggled)
            {
                m_callbacks.ExecuteCallbacks(toggled);
            }

            void FlattenButtonViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue:value];
            }

            void FlattenButtonViewInterop::SetFullyOnScreen()
            {
                [m_pView setFullyOnScreen];
            }

            void FlattenButtonViewInterop::SetFullyOffScreen()
            {
                [m_pView setFullyOffScreen];
            }

            void FlattenButtonViewInterop::InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void FlattenButtonViewInterop::RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
            void FlattenButtonViewInterop::SetViewEnabled(bool enabled)
            {
                m_pView.enabled = enabled;
            }
        }
    }
}