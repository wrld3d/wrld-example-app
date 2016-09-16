// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationConfirmationView.h"
#include "ICallback.h"
#include "AndroidNativeState.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationView: public IMyPinCreationConfirmationView
            {
            public:
                MyPinCreationConfirmationView(const std::shared_ptr<AndroidNativeState>& nativeState);
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

                const std::shared_ptr<AndroidNativeState> m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_confirmedCallbacks;

            };
        }
    }
}
