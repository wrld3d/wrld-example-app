// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsView.h"
#include "ICallback.h"
#include "AndroidNativeState.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsView: public IMyPinCreationDetailsView
            {
            public:
                MyPinCreationDetailsView(AndroidNativeState& nativeState);
                ~MyPinCreationDetailsView();

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

                AndroidNativeState& m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_confirmedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
            };
        }
    }
}
