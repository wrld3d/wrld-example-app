// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationViewInterop.h"
#include "MyPinCreationInitiationView.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            void MyPinCreationInitiationViewInterop::OnSelected()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void MyPinCreationInitiationViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue:value];
            }

            void MyPinCreationInitiationViewInterop::SetFullyOnScreen()
            {
                [m_pView setFullyOnScreen];
            }

            void MyPinCreationInitiationViewInterop::SetFullyOffScreen()
            {
                [m_pView setFullyOffScreen];
            }

            void MyPinCreationInitiationViewInterop::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void MyPinCreationInitiationViewInterop::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
        }
    }
}