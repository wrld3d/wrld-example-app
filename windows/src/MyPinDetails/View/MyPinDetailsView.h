// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "IMyPinDetailsView.h"
#include "MyPins.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsViewImpl;

            class MyPinDetailsView: public IMyPinDetailsView
            {
            public:
                MyPinDetailsView(const std::shared_ptr<WindowsNativeState>& nativeState);
                ~MyPinDetailsView();

                void OpenWithModel(
                        const std::string& title,
                        const std::string& description,
                        const std::string& imagePath);

                void Close();

                void OnDismiss();
                void OnRemove();

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertRemovePinCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveRemovePinCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                MyPinDetailsViewImpl* m_pImpl;
            };
        }
    }
}
