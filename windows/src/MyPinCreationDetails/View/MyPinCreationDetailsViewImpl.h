// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsView.h"
#include "ICallback.h"
#include "WindowsNativeState.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "CallbackCollection.h"

#include <vcclr.h>
#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsViewImpl : public IMyPinCreationDetailsView
            {
            public:
                MyPinCreationDetailsViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState);
                ~MyPinCreationDetailsViewImpl();

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
                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mShow;
                Helpers::ReflectionHelpers::Method<void> mDismiss;
                
                Helpers::ReflectionHelpers::Method<void> mGetTitle;
                Helpers::ReflectionHelpers::Method<void> mGetDescription;
                Helpers::ReflectionHelpers::Method<void> mGetShouldShare;
                Helpers::ReflectionHelpers::Method<void> mGetImageBuffer;
                Helpers::ReflectionHelpers::Method<void> mGetImageBufferSize;

                const std::shared_ptr<WindowsNativeState> m_nativeState;

                Eegeo::Helpers::CallbackCollection0 m_confirmedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
            };
        }
    }
}
