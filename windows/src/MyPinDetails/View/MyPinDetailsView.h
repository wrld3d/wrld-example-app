// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "IMyPinDetailsView.h"
#include "MyPins.h"
#include "ICallback.h"
#include "CallbackCollection.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsView: public IMyPinDetailsView
            {
            public:
                MyPinDetailsView(WindowsNativeState& nativeState);
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
                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot <System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<System::String^, System::String^, System::String^> mDisplay;
                Helpers::ReflectionHelpers::Method<void> mDismiss;

                Eegeo::Helpers::CallbackCollection0 m_removePinCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
            };
        }
    }
}
