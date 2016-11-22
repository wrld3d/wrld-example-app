// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsView.h"
#include "MyPinCreationDetailsViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsView::MyPinCreationDetailsView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(MyPinCreationDetailsViewImpl)(nativeState);
            }

            MyPinCreationDetailsView::~MyPinCreationDetailsView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void MyPinCreationDetailsView::Open()
            {
                m_pImpl->Open();
            }

            void MyPinCreationDetailsView::Close()
            {
                m_pImpl->Close();
            }

            void MyPinCreationDetailsView::OnConfirmed()
            {
                m_pImpl->OnConfirmed();
            }

            void MyPinCreationDetailsView::OnDismissed()
            {
                m_pImpl->OnDismissed();
            }

            void MyPinCreationDetailsView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertDismissedCallback(callback);
            }

            void MyPinCreationDetailsView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveDismissedCallback(callback);
            }

            void MyPinCreationDetailsView::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertConfirmedCallback(callback);
            }

            void MyPinCreationDetailsView::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveConfirmedCallback(callback);
            }

            std::string MyPinCreationDetailsView::GetTitle() const
            {
                return m_pImpl->GetTitle();
            }

            std::string MyPinCreationDetailsView::GetDescription() const
            {
                return m_pImpl->GetDescription();
            }

            bool MyPinCreationDetailsView::ShareSelected() const
            {
                return m_pImpl->ShareSelected();
            }

            Byte* MyPinCreationDetailsView::GetImageBuffer() const
            {
                return m_pImpl->GetImageBuffer();
            }

            size_t MyPinCreationDetailsView::GetImageSize() const
            {
                return m_pImpl->GetImageSize();
            }

            void MyPinCreationDetailsView::ConnectivityChanged(const bool hasConnectivity, const bool shouldVerifyShareSettings)
            {
                m_pImpl->ConnectivityChanged(hasConnectivity, shouldVerifyShareSettings);
            }
        }
    }
}

