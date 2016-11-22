// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationView.h"
#include "MyPinCreationConfirmationViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationView::MyPinCreationConfirmationView(const std::shared_ptr<WindowsNativeState>& windowsNativeState)
            {
                m_pImpl = Eegeo_NEW(MyPinCreationConfirmationViewImpl)(windowsNativeState);
            }

            MyPinCreationConfirmationView::~MyPinCreationConfirmationView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void MyPinCreationConfirmationView::OnConfirmed()
            {
                m_pImpl->OnConfirmed();
            }

            void MyPinCreationConfirmationView::OnDismissed()
            {
                m_pImpl->OnDismissed();
            }

            void MyPinCreationConfirmationView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertDismissedCallback(callback);
            }

            void MyPinCreationConfirmationView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveDismissedCallback(callback);
            }

            void MyPinCreationConfirmationView::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertConfirmedCallback(callback);
            }

            void MyPinCreationConfirmationView::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveConfirmedCallback(callback);
            }

            void MyPinCreationConfirmationView::SetOnScreenStateToIntermediateValue(float value)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(value);
            }

            void MyPinCreationConfirmationView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void MyPinCreationConfirmationView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }
        }
    }
}
