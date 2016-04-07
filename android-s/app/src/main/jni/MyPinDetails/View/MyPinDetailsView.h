// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
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
            class MyPinDetailsView: public IMyPinDetailsView
            {
            public:
                MyPinDetailsView(AndroidNativeState& nativeState);
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
                AndroidNativeState& m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_removePinCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
            };
        }
    }
}
