// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewInterop.h"
#include "MyPinCreationDetailsView.h"
#include "IMyPinCreationDetailsViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            void MyPinCreationDetailsViewInterop::Open()
            {
                [m_pView setFullyActive];
                [m_pView.pTitleText becomeFirstResponder];
            }

            void MyPinCreationDetailsViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }

            void MyPinCreationDetailsViewInterop::OnConfirmed()
            {
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsViewInterop::OnDismissed()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsViewInterop::ConnectivityChanged(const bool hasConnectivity, const bool shouldVerifyShareSettings)
            {
                [m_pView setHasNetworkConnectivity:hasConnectivity :shouldVerifyShareSettings];
            }

            void MyPinCreationDetailsViewInterop::InsertConfirmedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsViewInterop::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationDetailsViewInterop::InsertDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsViewInterop::RemoveDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            std::string MyPinCreationDetailsViewInterop::GetTitle() const
            {
                NSString* title = m_pView.pTitleText.text;
                std::string titleAsString = (title != nil && title.length > 0) ? [title UTF8String] : "Untitled Pin";
                return titleAsString;
            }

            std::string MyPinCreationDetailsViewInterop::GetDescription() const
            {
                NSString* description = m_pView.pPoiDescriptionBox.text;
                std::string descriptionAsString = [description UTF8String];
                return descriptionAsString;
            }

            bool MyPinCreationDetailsViewInterop::ShareSelected() const
            {
                return m_pView.pCheckbox.selected;
            }

            Byte* MyPinCreationDetailsViewInterop::GetImageBuffer() const
            {
                return [m_pView getImageBuffer];
            }

            size_t MyPinCreationDetailsViewInterop::GetImageSize() const
            {
                return [m_pView getImageSize];
            }
        }
    }
}
