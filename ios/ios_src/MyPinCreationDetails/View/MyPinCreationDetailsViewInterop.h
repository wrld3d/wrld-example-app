// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsView.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsViewInterop : public IMyPinCreationDetailsView
            {
            public:

                MyPinCreationDetailsViewInterop(MyPinCreationDetailsView* pView)
                    : m_pView(pView)
                {
                }

                void Open();
                void Close();

                void OnDismissed();
                void OnConfirmed();

                void ConnectivityChanged(const bool hasConnectivity, const bool shouldVerifyShareSettings);

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback);

                std::string GetTitle() const;
                std::string GetDescription() const;
                bool ShareSelected() const;
                Byte* GetImageBuffer() const;
                size_t GetImageSize() const;

            private:

                MyPinCreationDetailsView* m_pView;

                Eegeo::Helpers::CallbackCollection0 m_confirmedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
            };
        }
    }
}
