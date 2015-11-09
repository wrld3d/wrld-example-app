// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationConfirmationView.h"
#include "ICallback.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationView: public IMyPinCreationConfirmationView
            {
            public:
                MyPinCreationConfirmationView(WindowsNativeState& nativeState);
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
                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<float> mAnimateToIntermediateOnScreenState;
                Helpers::ReflectionHelpers::Method<void> mAnimateToActive;
                Helpers::ReflectionHelpers::Method<void> mAnimateToInactive;

                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_confirmedCallbacks;

            };
        }
    }
}
