// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationViewInterop.h"
#include "MyPinCreationConfirmationView.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            void MyPinCreationConfirmationViewInterop::OnConfirmed()
            {
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationViewInterop::OnDismissed()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationViewInterop::InsertConfirmedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationViewInterop::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationViewInterop::InsertDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationViewInterop::RemoveDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationViewInterop::SetFullyOffScreen()
            {
                [m_pView setFullyOffScreen];
            }

            void MyPinCreationConfirmationViewInterop::SetFullyOnScreen()
            {
                [m_pView setFullyOnScreen];
            }

            void MyPinCreationConfirmationViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue: value];
            }
        }
    }
}