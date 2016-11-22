// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationView.h"
#include "MyPinCreationInitiationViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationInitiationView::MyPinCreationInitiationView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(MyPinCreationInitiationViewImpl)(nativeState);
            }

            MyPinCreationInitiationView::~MyPinCreationInitiationView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void MyPinCreationInitiationView::OnSelected()
            {
                m_pImpl->OnSelected();
            }

            void MyPinCreationInitiationView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertSelectedCallback(callback);
            }

            void MyPinCreationInitiationView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveSelectedCallback(callback);
            }

            void MyPinCreationInitiationView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }

            void MyPinCreationInitiationView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void MyPinCreationInitiationView::SetOnScreenStateToIntermediateValue(float screenValue)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(screenValue);
            }

            void MyPinCreationInitiationView::ShouldOffsetButton(bool shouldOffset)
            {
                m_pImpl->ShouldOffsetButton(shouldOffset);
            }
        }
    }
}
