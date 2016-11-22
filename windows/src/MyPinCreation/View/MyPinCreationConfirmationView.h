// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationConfirmationView.h"
#include "ICallback.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationViewImpl;

            class MyPinCreationConfirmationView: public IMyPinCreationConfirmationView
            {
            public:
                MyPinCreationConfirmationView(const std::shared_ptr<WindowsNativeState>& nativeState);
                ~MyPinCreationConfirmationView();

                void OnDismissed();
                void OnConfirmed();

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();

            private:
                MyPinCreationConfirmationViewImpl* m_pImpl;
            };
        }
    }
}
